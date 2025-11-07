#ifndef VALVEFIRMWAREUPGRADEWORKER_H
#define VALVEFIRMWAREUPGRADEWORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtMath>
#include <QFile>
#include <QFileInfo>

#include "source/service/util/unitutil.h"
#include "source/service/valve/ftdhelper.h"
#include "source/service/valve/ValveConnection.h"
#include "source/service/valve/valvesproviderdtoex.h"

#define DFU_CPU1					0x0100
#define DFU_CPU2					0x0200
#define ERASE_CPU1					0x0300
#define ERASE_CPU2					0x0400
#define VERIFY_CPU1					0x0500
#define VERIFY_CPU2					0x0600
#define LIVE_DFU_CPU1               0x0700
#define CPU1_UNLOCK_Z1				0x000A
#define CPU1_UNLOCK_Z2				0x000B
#define CPU2_UNLOCK_Z1				0x000C
#define CPU2_UNLOCK_Z2				0x000D
#define RUN_CPU1					0x000E
#define RESET_CPU1					0x000F
#define RUN_CPU1_BOOT_CPU2			0x0004
#define RESET_CPU1_BOOT_CPU2        0x0007
#define RUN_CPU2					0x0010
#define RESET_CPU2					0x0020
#define RUN_CPU1_LOAD_CM            0x0030
#define RESET_CPU1_LOAD_CM          0x0040
#define DFU_CM                      0x0050
#define ERASE_CM                    0x0060
#define VERIFY_CM                   0x0070
#define CM_UNLOCK_Z1                0x0080
#define CM_UNLOCK_Z2                0x0090
#define RUN_CM                      0x00A0
#define RESET_CM                    0x00B0

#define NO_ERROR					0x1000
#define BLANK_ERROR					0x2000
#define VERIFY_ERROR				0x3000
#define PROGRAM_ERROR				0x4000
#define COMMAND_ERROR				0x5000
#define UNLOCK_ERROR				0x6000

#define INCORRECT_DATA_BUFFER_LENGTH         0x7000
#define INCORRECT_ECC_BUFFER_LENGTH          0x8000
#define DATA_ECC_BUFFER_LENGTH_MISMATCH      0x9000
#define FLASH_REGS_NOT_WRITABLE              0xA000
#define FEATURE_NOT_AVAILABLE                0xB000
#define INVALID_ADDRESS                      0xC000
#define INVALID_CPUID                        0xD000
#define FAILURE                              0xE000
#define NOT_RECOGNIZED                       0xF000

#define ACK						0x2D
#define NAK						0xA5

#define g_bBlockSize            0x80

class ValveFirmwareUpgradeDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eStep)

public:
    enum eStep{
        READY          = 0,
        SET_BOOTMODE   = READY          + 1,
        CONNECT_SERIAL = SET_BOOTMODE   + 1,
        CPU1_DN_KERNEL = CONNECT_SERIAL + 1,
        CPU1_ERASE     = CPU1_DN_KERNEL + 1,
        CPU1_DN_APP    = CPU1_ERASE     + 1,
        CPU1_VERIFY    = CPU1_DN_APP    + 1,
        CPU1_RESET     = CPU1_VERIFY    + 1,
        CPU2_DN_KERNEL = CPU1_RESET     + 1,
        CPU2_ERASE     = CPU2_DN_KERNEL + 1,
        CPU2_DN_APP    = CPU2_ERASE     + 1,
        CPU2_VERIFY    = CPU2_DN_APP    + 1,
        CPU2_RESET     = CPU2_VERIFY    + 1,
        COMPLETE       = CPU2_RESET     + 1,
    };
};
class ValveFirmwareUpgradeWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mStep              READ getStep              NOTIFY signalEventChangedStep             )
    Q_PROPERTY(int      mPercentCpu1Kernel READ getPercentCpu1Kernel NOTIFY signalEventChangedPercentCpu1Kernel)
    Q_PROPERTY(int      mPercentCpu2Kernel READ getPercentCpu2Kernel NOTIFY signalEventChangedPercentCpu2Kernel)
    Q_PROPERTY(int      mPercentCpu1App    READ getPercentCpu1App    NOTIFY signalEventChangedPercentCpu1App   )
    Q_PROPERTY(int      mPercentCpu2App    READ getPercentCpu2App    NOTIFY signalEventChangedPercentCpu2App   )
    Q_PROPERTY(int      mPercentCpu1Verify READ getPercentCpu1Verify NOTIFY signalEventChangedPercentCpu1Verify)
    Q_PROPERTY(int      mPercentCpu2Verify READ getPercentCpu2Verify NOTIFY signalEventChangedPercentCpu2Verify)

private:
    /* member */
    int           mStep           = (int)ValveFirmwareUpgradeDef::READY;
    int           mPercentCpu1Kernel = 0;
    int           mPercentCpu2Kernel = 0;
    int           mPercentCpu1App    = 0;
    int           mPercentCpu2App    = 0;
    int           mPercentCpu1Verify = 0;
    int           mPercentCpu2Verify = 0;
    QTimer      * mpTimer         = nullptr;
    SerialValve * mpValve         = nullptr;
    QString       mServicePortType = "";
    QString       mComPort        ;
    QSerialPort::BaudRate mBaudRate;
    QSerialPort::DataBits mDataBit ;
    QSerialPort::StopBits mStopBit ;
    QSerialPort::Parity   mParity  ;
    qint64        mCpu1KernelByteSize = 0;
    qint64        mCpu2KernelByteSize = 0;
    qint64        mCpu1AppByteSize    = 0;
    qint64        mCpu2AppByteSize    = 0;

    qint64        mReadedByteSize     = 0;
    QString       mCpu1KernelFile     = "";
    QString       mCpu2KernelFile     = "";
    QString       mCpu1AppFile        = "";
    QString       mCpu2AppFile        = "";

public:
    int getStep             (){ return mStep             ; }
    int getPercentCpu1Kernel(){ return mPercentCpu1Kernel; }
    int getPercentCpu2Kernel(){ return mPercentCpu2Kernel; }
    int getPercentCpu1App   (){ return mPercentCpu1App   ; }
    int getPercentCpu2App   (){ return mPercentCpu2App   ; }
    int getPercentCpu1Verify(){ return mPercentCpu1Verify; }
    int getPercentCpu2Verify(){ return mPercentCpu2Verify; }

    void setStep(int value)
    {
        if(mStep == value)
            return;

        mStep = value;

        if(mStep == (int)ValveFirmwareUpgradeDef::READY && mpValve != nullptr)
        {
            delete mpValve;
            mpValve = nullptr;
        }

        if(mStep == ValveFirmwareUpgradeDef::READY)
        {
            setPercentCpu1Kernel(0);
            setPercentCpu2Kernel(0);
            setPercentCpu1App   (0);
            setPercentCpu2App   (0);
            setPercentCpu1Verify(0);
            setPercentCpu2Verify(0);
        }

        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "] step = " << value;

        emit signalEventChangedStep(value);
    }
    void setPercentCpu1Kernel(int value){ if(mPercentCpu1Kernel == value)return; mPercentCpu1Kernel = value; emit signalEventChangedPercentCpu1Kernel(value);}
    void setPercentCpu2Kernel(int value){ if(mPercentCpu2Kernel == value)return; mPercentCpu2Kernel = value; emit signalEventChangedPercentCpu2Kernel(value);}
    void setPercentCpu1App   (int value){ if(mPercentCpu1App    == value)return; mPercentCpu1App    = value; emit signalEventChangedPercentCpu1App   (value);}
    void setPercentCpu2App   (int value){ if(mPercentCpu2App    == value)return; mPercentCpu2App    = value; emit signalEventChangedPercentCpu2App   (value);}
    void setPercentCpu1Verify(int value){ if(mPercentCpu1Verify == value)return; mPercentCpu1Verify = value; emit signalEventChangedPercentCpu1Verify(value);}
    void setPercentCpu2Verify(int value){ if(mPercentCpu2Verify == value)return; mPercentCpu2Verify = value; emit signalEventChangedPercentCpu2Verify(value);}

signals:
    void signalEventChangedStep             (int value);
    void signalEventChangedPercentCpu1Kernel(int value);
    void signalEventChangedPercentCpu2Kernel(int value);
    void signalEventChangedPercentCpu1App   (int value);
    void signalEventChangedPercentCpu2App   (int value);
    void signalEventChangedPercentCpu1Verify(int value);
    void signalEventChangedPercentCpu2Verify(int value);

    void signalEventResult(bool result, QString resultMsg);

public slots:
    void onTimeout()
    {
        //FT_HANDLE ftHandle;

        QString errMsg;

        qDebug() << "[" << Q_FUNC_INFO << "]step = " << mStep;

        switch (mStep) {
        case (int)ValveFirmwareUpgradeDef::SET_BOOTMODE:
            qDebug() << "[" << Q_FUNC_INFO << "]step = BOOT";
            if(setBootMode(errMsg)){ setStep(ValveFirmwareUpgradeDef::CONNECT_SERIAL); startTimer(1000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;
        case (int)ValveFirmwareUpgradeDef::CONNECT_SERIAL:
            if(connectSerial(errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU1_DN_KERNEL); startTimer(1000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;
        case (int)ValveFirmwareUpgradeDef::CPU1_DN_KERNEL:
            if(downloadKernel(mpValve, mCpu1KernelFile, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU1_ERASE); startTimer(3006);}
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU1_ERASE    :
            if(eraseCPU(mpValve, ERASE_CPU1, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU1_DN_APP); startTimer(2000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU1_DN_APP   :
            if(downloadApp(mpValve, DFU_CPU1, mCpu1AppFile, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU1_VERIFY); startTimer(2000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU1_VERIFY   :
            if(downloadApp(mpValve, VERIFY_CPU1, mCpu1AppFile, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU1_RESET); startTimer(2000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU1_RESET    :
            if(resetCPU(mpValve, RESET_CPU1_BOOT_CPU2, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU2_DN_KERNEL); startTimer(2000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU2_DN_KERNEL:
            if(downloadKernel(mpValve, mCpu2KernelFile, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU2_ERASE); startTimer(3006); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU2_ERASE    :
            if(eraseCPU(mpValve, ERASE_CPU2, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU2_DN_APP); startTimer(2000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU2_DN_APP   :
            if(downloadApp(mpValve, DFU_CPU2, mCpu2AppFile, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU2_VERIFY); startTimer(2000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU2_VERIFY   :
            if(downloadApp(mpValve, VERIFY_CPU2, mCpu2AppFile, errMsg)){ setStep(ValveFirmwareUpgradeDef::CPU2_RESET); startTimer(2000); }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::CPU2_RESET    :
            if(resetCPU(mpValve, RESET_CPU2, errMsg))
            {
                setStep(ValveFirmwareUpgradeDef::COMPLETE); startTimer(2000);
            }
            else{setStep(ValveFirmwareUpgradeDef::READY); emit signalEventResult(false, errMsg);}
            return;

        case (int)ValveFirmwareUpgradeDef::COMPLETE      :
            setStep(ValveFirmwareUpgradeDef::READY);
            resetBootMode(errMsg);
            emit signalEventResult(true, "");
            return;
        }
    }
    void onCommandUpgrade(QString servicePortType, QString comPort, int baudRate, int dataBit, int stopBit, int parity, QString cpu1KernelFile, QString cpu2KernelFile, QString cpu1AppFile, QString cpu2AppFile)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        if(getStep() != ValveFirmwareUpgradeDef::READY)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] already upgrade";

            emit signalEventResult(false, "not ready");
            return;
        }

        mServicePortType = servicePortType;
        mComPort  = comPort;
        mBaudRate = (QSerialPort::BaudRate)baudRate;
        mDataBit  = (QSerialPort::DataBits)dataBit;
        mStopBit  = (QSerialPort::StopBits)stopBit;
        mParity   = (QSerialPort::Parity)parity;

        mCpu1KernelByteSize = QFileInfo(cpu1KernelFile).size();
        mCpu2KernelByteSize = QFileInfo(cpu2KernelFile).size();
        mCpu1AppByteSize    = QFileInfo(cpu1AppFile   ).size();
        mCpu2AppByteSize    = QFileInfo(cpu2AppFile   ).size();

        mCpu1KernelFile = cpu1KernelFile;
        mCpu1AppFile    = cpu1AppFile   ;
        mCpu2KernelFile = cpu2KernelFile;
        mCpu2AppFile    = cpu2AppFile   ;
        setStep(ValveFirmwareUpgradeDef::SET_BOOTMODE);

        startTimer(1000);
    }



public:
    explicit ValveFirmwareUpgradeWorker(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
    }
    ~ValveFirmwareUpgradeWorker()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
    }

private:
    void startTimer(qint64 msec)
    {
        if(mpTimer == nullptr)
        {
            mpTimer = new QTimer;
            mpTimer->setSingleShot(true);
            connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
        }

        mpTimer->stop();
        mpTimer->start(msec);
    }

    bool setBootMode(QString errMsg)
    {
        qDebug() << "[" << Q_FUNC_INFO << "] service port type = " << mServicePortType;

        if(mServicePortType != "USB")
            return true;

        FTDHelper ftdHelper;

        if(ftdHelper.readyPort(mComPort.mid(3).toLong(), errMsg) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << errMsg;
            return false;
        }
        return true;
    }

    bool resetBootMode(QString errMsg)
    {
        if(mServicePortType != "USB")
            return true;

        FTDHelper ftdHelper;

        if(ftdHelper.finishPort(mComPort.mid(3).toLong(), errMsg) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << errMsg;
            return false;
        }
        return true;
    }

    bool connectSerial(QString errMsg)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        mpValve = new SerialValve();

        if(mpValve->connectValve(mComPort, QSerialPort::BaudRate::Baud19200 /*(QSerialPort::BaudRate)mBaudRate*/, (QSerialPort::DataBits)mDataBit, (QSerialPort::StopBits)mStopBit, (QSerialPort::Parity)mParity) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] can not connect valve";

            delete mpValve;
            mpValve = nullptr;

            errMsg = "can not connect valve";
            return false;
        }

        //setStep(ValveFirmwareUpgradeDef::CPU1_DN_KERNEL);

        //startTimer(1000);

        return true;
    }

    bool downloadKernel(SerialValve * pValve, QString fileName, QString &errMsg)
    {
        QFile file;

        qDebug() << "[" << Q_FUNC_INFO << "]";

        file.setFileName(fileName);
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] file open failed";

            errMsg.append(QString("open failed : ").arg(fileName));
            return false;
        }

        if(autoBaudLock(pValve) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] autoBaudLock failed";

            errMsg.append(QString("auto baud lock failed"));
            return false;
        }

        if(loadProgram(pValve, &file) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] load failed";

            errMsg.append(QString("load failed : ").arg(fileName));
            file.close();
            pValve->clearReadBuffer();
            return false;
        }

        file.close();

        pValve->clearReadBuffer();

        return true;
    }

    bool eraseCPU(SerialValve * pValve, quint16 cmd, QString &errMsg)
    {
        quint32 sectorMask = 0x00003FFF;

        if(autoBaudLock(pValve) == false)
        {
            errMsg.append(QString("Command [%1] error : at auto baud lock").arg(cmd));
            return false;
        }

        if(sendPacket(pValve, constructPacket(cmd, 4, (char *)&sectorMask)))
        {
            if(getPacket(pValve, cmd))
            {
                return true;
            }
        }

        qDebug() << "[" << Q_FUNC_INFO << "]" << QString("Command [%1] error").arg(cmd);

        errMsg.append(QString("Command [%1] error").arg(cmd));
        return false;
    }

    bool downloadApp(SerialValve * pValve, quint16 cmd, QString fileName, QString &errMsg)
    {
        QFile file;
        QList<quint16> rcvData;

        file.setFileName(fileName);
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            errMsg.append(QString("open failed : ").arg(fileName));
            return false;
        }

        if(sendPacket(pValve, constructPacket(cmd, 0, nullptr)))
        {
            if(downloadImage(pValve, &file))
            {
                if(getPacketEx(pValve, cmd, &rcvData))
                {
                    if(rcvData[0] != NO_ERROR)
                    {
                        pValve->clearReadBuffer();
                        file.close();
                        errMsg.append(QString("%1<br>%2").arg(getStrErrStatus(rcvData[0])).arg(getStrFlashAPIErr(rcvData[3])));

                        return false;
                    }

                    pValve->clearReadBuffer();
                    file.close();
                    return true;
                }
            }
        }

        pValve->clearReadBuffer();
        file.close();
        errMsg.append(QString("Command [%1] error").arg(cmd));
        return false;
    }

    bool resetCPU(SerialValve * pValve, quint16 cmd, QString &errMsg)
    {
        if(sendPacket(pValve, constructPacket(cmd, 0, nullptr)))
        {
            return true;
        }
        errMsg.append(QString("Command [%1] error").arg(cmd));
        return false;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool downloadImage(SerialValve * pValve, QFile * pFile)
    {
        QByteArray writeData(1,0);
        QByteArray readData;

        quint8  writtenValue;
        quint16 checksum = 0;
        quint16 rcvChecksum = 0;
        quint8  rcvLSB = 0;
        quint8  rcvMSB = 0;
        quint16 blockSize = 0;

        qDebug() << "[" << Q_FUNC_INFO << "]";

        mReadedByteSize = 0;


        //First 22 bytes are initialization data
        for (int i = 0; i < 22; i++)
        {
            if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
            {
                return false;
            }
        }

        //Device will immediately ask for checksum
        if(readByteFromValve(pValve, rcvLSB) == false)
            return false;

        if(readByteFromValve(pValve, rcvMSB) == false)
            return false;

        rcvChecksum = (((quint16)rcvMSB << 8) & 0xFF00) | ((quint16)rcvLSB & 0x00FF);

        //Ensure checksum matches
        if (checksum != rcvChecksum)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]checksum error, checksum = " << checksum << ", rcvChecksum = " << rcvChecksum;
            return false;
        }

        while(!pFile->atEnd())// check end of file // while (fileStatus == 1)
        {
            //Read next block size (2 bytes) from hex2000 text file
            if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
            {
                return false;
            }

            blockSize = (quint16)writtenValue & 0xFF;

            if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
            {
                return false;
            }

            blockSize = (((quint16)writtenValue << 8) & 0xFF00) | (blockSize & 0xFF);

            if (blockSize == 0x0000) //end of file
            {
                if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_DN_APP)
                {
                    setPercentCpu1App(100);
                }
                else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU2_DN_APP)
                {
                    setPercentCpu2App(100);
                }
                else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_VERIFY)
                {
                    setPercentCpu1Verify(100);
                }
                else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU2_VERIFY)
                {
                    setPercentCpu2Verify(100);
                }
                break;
            }

            //read next red next read
            //Read next destination address from hex2000 text file (4 bytes, 32 bits)
            if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
            {
                return false;
            }

            if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
            {
                return false;
            }

            if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
            {
                return false;
            }

            if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
            {
                return false;
            }

            for (quint16 j = 0; j < blockSize; j++)
            {
                if (((j % g_bBlockSize == 0) && (j > 0)) || ((blockSize < g_bBlockSize) && (j == blockSize)))
                {
                    //receive checksum
                    if(readByteFromValve(pValve, rcvLSB) == false)
                        return false;

                    if(readByteFromValve(pValve, rcvMSB) == false)
                        return false;

                    rcvChecksum = (((quint16)rcvMSB << 8) & 0xFF00) | ((quint16)rcvLSB & 0xFF);

                    //Ensure checksum matches
                    if ((checksum & 0xFFFF) != rcvChecksum)
                    {
                        qDebug() << "[" << Q_FUNC_INFO << "]checksum error, checksum = " << checksum << ", rcvChecksum = " << rcvChecksum;
                        return false;
                    }
                }

                //send word data
                if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
                {
                    return false;
                }
                if(writeHexFileToValve(pFile, pValve, writtenValue, checksum) == false)
                {
                    return false;
                }

                if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_DN_APP)
                {
                    setPercentCpu1App((mReadedByteSize * 100) / mCpu1AppByteSize);
                }
                else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU2_DN_APP)
                {
                    setPercentCpu2App((mReadedByteSize * 100) / mCpu2AppByteSize);
                }
                else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_VERIFY)
                {
                    setPercentCpu1Verify((mReadedByteSize * 100) / mCpu1AppByteSize);
                }
                else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU2_VERIFY)
                {
                    setPercentCpu2Verify((mReadedByteSize * 100) / mCpu2AppByteSize);
                }
            }

            //receive checksum
            if(readByteFromValve(pValve, rcvLSB) == false)
                return false;

            if(readByteFromValve(pValve, rcvMSB) == false)
                return false;

            rcvChecksum = (((quint16)rcvMSB << 8) & 0xFF00) | ((quint16)rcvLSB & 0xFF);

            //Ensure checksum matches
            if ((checksum & 0xFFFF) != rcvChecksum)
            {
                return false;
            }

            if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_DN_APP)
            {
                setPercentCpu1App((mReadedByteSize * 100) / mCpu1AppByteSize);
            }
            else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU2_DN_APP)
            {
                setPercentCpu2App((mReadedByteSize * 100) / mCpu2AppByteSize);
            }
            else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_VERIFY)
            {
                setPercentCpu1Verify((mReadedByteSize * 100) / mCpu1AppByteSize);
            }
            else if(getStep() == (int)ValveFirmwareUpgradeDef::CPU2_VERIFY)
            {
                setPercentCpu2Verify((mReadedByteSize * 100) / mCpu2AppByteSize);
            }
        }

        return true;
    }

    bool loadProgram(SerialValve * pValve, QFile * pFile)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        QByteArray writeBuff(1,0);
        QByteArray readBuff;

        quint8 readValue;

        mReadedByteSize = 0;

        while(readHexFile(pFile, readValue))
        {
            if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_DN_KERNEL)
            {
                setPercentCpu1Kernel((mReadedByteSize * 100) / mCpu1KernelByteSize);
            }
            else
            {
                setPercentCpu2Kernel((mReadedByteSize * 100) / mCpu2KernelByteSize);
            }
            writeBuff[0] = readValue;

            if(pValve->write(writeBuff,10000) == false)
            {
                qDebug() << "[" << Q_FUNC_INFO << "] write failed";
                return false;
            }

            readBuff  = pValve->read("\0", 1, 10000);

            if(readBuff.size() != 1)
            {
                qDebug() << "[" << Q_FUNC_INFO << "]readBuff.size() != 1";
                return false;
            }

            if(readBuff[0] != writeBuff[0])
            {
                qDebug() << "[" << Q_FUNC_INFO << "] readBuff[0] = " << readBuff[0] << ", writeBuff[0] = " << writeBuff[0];
                return false;
            }
        }

        if(getStep() == (int)ValveFirmwareUpgradeDef::CPU1_DN_KERNEL)
        {
            setPercentCpu1Kernel((mReadedByteSize * 100) / mCpu1KernelByteSize);
        }
        else
        {
            setPercentCpu2Kernel((mReadedByteSize * 100) / mCpu2KernelByteSize);
        }

        return true;
    }

    bool autoBaudLock(SerialValve * pValve)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        QByteArray key(1, 'A');
        QByteArray responseBuf;

        pValve->write( key, 10000);

        responseBuf = pValve->read("\0", 1, 10000);

        if(responseBuf.size() != 1)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]responseBuf.size() != 1";

            return false;
        }

        if(responseBuf[0] != key[0])
        {
            qDebug() << "[" << Q_FUNC_INFO << "] responseBuf[0] = " << responseBuf[0] << ", key[0] = " << key[0];
            return false;
        }

        return true;
    }

    QByteArray constructPacket(quint16 cmd, quint16 length, char * data)
    {
        quint16 checksum = 0; //checksum of the Command and the Data
        QByteArray retBuffer;
        retBuffer.append( 0xE4); //start LSB
        retBuffer.append( 0x1B); //start MSB
        retBuffer.append( (quint8)( length & 0xFF  )      ); //length LSB
        retBuffer.append( (quint8)((length & 0xFF00) >> 8)); //length MSB
        retBuffer.append( (quint8)( cmd    & 0xFF  )      ); checksum += (cmd & 0xFF);//command LSB
        retBuffer.append( (quint8)((cmd    & 0xFF00) >> 8)); checksum += ((cmd & 0xFF00) >> 8); //command MSB

        for (int i = 0; i < length; i++) //swap order of the data buffer
        {
            checksum = checksum + (((quint16)(data[i])) & 0xFF);

            retBuffer.append(data[i]);
        }

        retBuffer.append( (quint8) (checksum & 0xFF  )      ); //checksum LSB
        retBuffer.append( (quint8)((checksum & 0xFF00) >> 8)); //checksum MSB
        retBuffer.append( 0x1B                              ); //end LSB
        retBuffer.append( 0xE4                              ); //end MSB

        return retBuffer;
    }

    bool sendPacket(SerialValve * pValve, QByteArray data)
    {
        QByteArray readBuf;

        if(pValve->write(data, 10000) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] sendPacket : write error" ;
            return false;
        }

        readBuf = pValve->read("\0", 1, 10000);

        if(readBuf.size() != 1)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] sendPacket : read error" ;
            return false;
        }

        if (ACK != readBuf[0]) //Check return byte
        {
            qDebug() << "[" << Q_FUNC_INFO << "] sendPacket : ack error = " <<  readBuf[0];
            return false;
        }
        return true;
    }

    bool getPacket(SerialValve * pValve, quint16 verifyCmd)
    {
        bool    result;
        quint16 cmd;
        quint16 word;
        quint16 length;
        quint16 checksum = 0;
        quint16 dataChecksum = 0;

        QList<quint16> data;

        pValve->clearReadBuffer();

        word = getWord(pValve, checksum, result);

        if (word != 0x1BE4 || result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found STX" ;
            return false;
        }

        length = getWord(pValve, checksum, result);

        if(result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found packet length" ;
            return false;
        }

        checksum = 0;
        cmd = getWord(pValve, dataChecksum, result);

        if(result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found packet command" ;
            return false;
        }

        for (int i = 0; i < (length) / 2; i++)
        {
            data.append(getWord(pValve, dataChecksum, result));

            if(result == false)
            {
                qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found packet body" ;
                return false;
            }
        }
        quint16 recievedChecksum = getWord(pValve, checksum, result);

        if (dataChecksum != recievedChecksum || result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : checksum error, dataChecksum = " << dataChecksum << ", recievedChecksum = " << recievedChecksum ;
            return false;
        }

        word = getWord(pValve, checksum, result);

        if (word != 0xE41B || result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found ETX" ;
            return false;
        }

        if(sendACK(pValve) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : sendACK() failed" ;
            return false;
        }

        return cmd == verifyCmd;
    }

    bool getPacketEx(SerialValve * pValve, quint16 verifyCmd, QList<quint16> *pData)
    {
        bool    result;
        quint16 cmd;
        quint16 word;
        quint16 length;
        quint16 checksum = 0;
        quint16 dataChecksum = 0;

        //QList<quint16> data;

        pValve->clearReadBuffer();

        word = getWord(pValve, checksum, result);

        if (word != 0x1BE4 || result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found STX" ;
            return false;
        }

        length = getWord(pValve, checksum, result);

        if(result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found packet length" ;
            return false;
        }

        checksum = 0;
        cmd = getWord(pValve, dataChecksum, result);

        if(result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found packet command" ;
            return false;
        }

        for (int i = 0; i < (length) / 2; i++)
        {
            pData->append(getWord(pValve, dataChecksum, result));

            if(result == false)
            {
                qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found packet body" ;
                return false;
            }
        }
        quint16 recievedChecksum = getWord(pValve, checksum, result);

        if (dataChecksum != recievedChecksum || result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : checksum error, dataChecksum = " << dataChecksum << ", recievedChecksum = " << recievedChecksum ;
            return false;
        }

        word = getWord(pValve, checksum, result);

        if (word != 0xE41B || result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : can not found ETX" ;
            return false;
        }

        if(sendACK(pValve) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : sendACK() failed" ;
            return false;
        }

        return cmd == verifyCmd;
    }

    quint16 getWord(SerialValve * pValve, quint16 &checkSum, bool &result)
    {
        QByteArray word;
        quint32 rcvData = 0;
        quint32 rcvDataH = 0;

        result = false;
        word = pValve->read("\0", 1, 10000);

        if(word.size() != 1)
            return 0;

        rcvData = ((quint32)word.at(0)) & 0x000000FF;

        checkSum = checkSum + (((quint16)word.at(0)) & 0xFF);

        if(sendACK(pValve) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : sendACK() failed" ;
            return 0;
        }

        word = pValve->read("\0", 1, 10000);

        if(word.size() != 1)
            return 0;

        rcvDataH =((quint32)word.at(0)) & 0x000000FF;

        checkSum = checkSum + (((quint16)word.at(0)) & 0xFF);

        if(sendACK(pValve) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] getPacket : sendACK() failed" ;
            return 0;
        }

        result = true;

        return((rcvDataH << 8) | rcvData);
    }

    bool sendACK(SerialValve * pValve)
    {
        QByteArray buff(1, ACK);

        return pValve->write( buff, 10000);
    }

    bool readByteFromValve(SerialValve *pValve, quint8 &readValue)
    {
        QByteArray readBuff;
        static QByteArray writeBuff(1,ACK);

        readBuff = pValve->read("\0", 1, 10000);

        if(readBuff.size() != 1)
            return false;

        readValue = readBuff[0];

        return pValve->write(writeBuff, 10000);
    }

    bool writeHexFileToValve(QFile *pFile, SerialValve *pValve, quint8 &wrttenValue, quint16 &checksum)
    {
        static QByteArray writeBuff(1,0);

        if(readHexFile(pFile, wrttenValue) == false)
            return false;

        writeBuff[0] = wrttenValue;

        if(pValve->write(writeBuff,10000) == false)
        {
            return false;
        }

        checksum = checksum + ((quint16)wrttenValue & 0x00FF);

        return true;
    }

    bool readHexFile(QFile *pFile, quint8 &out)
    {
        char readChar;
        qint64 readCount = 0;
        QString hexString;
        bool convertResult;

        do{
            readCount = pFile->read(&readChar,1);

            mReadedByteSize = mReadedByteSize + readCount;
            //setPercent((mReadedByteSize * 100) / mTotalByteSize);

            if(((readChar <= 'z' && readChar >= 'a')||
                (readChar <= 'Z' && readChar >= 'A')||
                (readChar <= '9' && readChar >= '0')  ) && readCount == 1)
            {
                hexString.append(readChar);
            }
            else
            {
                if(hexString.size() != 0)
                {
                    out = hexString.toUInt(&convertResult, 16);
                    return true;
                }
            }
        }while (readCount == 1);

        return false;
    }

    QString getStrErrStatus(quint16 err)
    {
        switch (err)
        {
        case BLANK_ERROR:
            return "ERROR Status: BLANK_ERROR";
        case VERIFY_ERROR:
            return "ERROR Status: VERIFY_ERROR";
            break;
        case PROGRAM_ERROR:
            return "ERROR Status: PROGRAM_ERROR";
            break;
        case COMMAND_ERROR:
            return "ERROR Status: COMMAND_ERROR";
            break;
        case UNLOCK_ERROR:
            return "ERROR Status: UNLOCK_ERROR";
            break;
        default:
            return "ERROR Status: Not Recognized Error";
        }

    }

    QString getStrFlashAPIErr(quint16 err)
    {
        switch (err)
        {
        case INCORRECT_DATA_BUFFER_LENGTH:
            return "Flash API Error: Incorrect Data Buffer Length";
        case INCORRECT_ECC_BUFFER_LENGTH:
            return "Flash API Error: Incorrect ECC Buffer Length";
        case DATA_ECC_BUFFER_LENGTH_MISMATCH:
            return "Flash API Error: Data ECC Buffer Length Mismatch";
        case FLASH_REGS_NOT_WRITABLE:
            return "Flash API Error: Flash Registers not Writable";
        case FEATURE_NOT_AVAILABLE:
            return "Flash API Error: Feature not Available";
        case INVALID_ADDRESS:
            return "Flash API Error: Invalid Address";
        case INVALID_CPUID:
            return "Flash API Error: Invalid CPUID";
        case FAILURE:
            return "Flash API Error: Failure";
        default:
            return "Error not recognized";
        }
    }
};
#endif // VALVEFIRMWAREUPGRADEWORKER_H
