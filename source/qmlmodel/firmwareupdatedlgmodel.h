#ifndef FIRMWAREUPDATEDLGMODEL_H
#define FIRMWAREUPDATEDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class FirmwareUpdateUiStepDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eUiStep)

public:
    enum eUiStep{
        DISCONNECT_CABLE = 0,
        CONNECT_ADAPTER  = DISCONNECT_CABLE + 1,
        CONNECT_CABLE    = CONNECT_ADAPTER  + 1,
        REBOOT_VALVE     = CONNECT_CABLE    + 1,
        SELECT_FILE_PORT = REBOOT_VALVE     + 1,
        START_UPDATE     = SELECT_FILE_PORT + 1,
        CONNECT_SERIAL   = START_UPDATE     + 1,
        CPU1_DN_KERNEL   = CONNECT_SERIAL   + 1,
        CPU1_ERASE       = CPU1_DN_KERNEL   + 1,
        CPU1_DN_APP      = CPU1_ERASE       + 1,
        CPU1_VERIFY      = CPU1_DN_APP      + 1,
        CPU1_RESET       = CPU1_VERIFY      + 1,
        CPU2_DN_KERNEL   = CPU1_RESET       + 1,
        CPU2_ERASE       = CPU2_DN_KERNEL   + 1,
        CPU2_DN_APP      = CPU2_ERASE       + 1,
        CPU2_VERIFY      = CPU2_DN_APP      + 1,
        CPU2_RESET       = CPU2_VERIFY      + 1,
        COMPLETE         = CPU2_RESET       + 1
    };
};
class FirmwareUpdateDlgModel : public QObject
{
    Q_OBJECT
    Q_ENUMS(eUiStep)
    Q_PROPERTY(int     mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool    mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test      )
    Q_PROPERTY(QString mCpu1KernelFile      READ getCpu1KernelFile      NOTIFY signalEventChangedCpu1KernelFile   )
    Q_PROPERTY(QString mCpu2KernelFile      READ getCpu2KernelFile      NOTIFY signalEventChangedCpu2KernelFile   )
    Q_PROPERTY(int     mDFUStep             READ getDFUStep             NOTIFY signalEventChangedDFUStep          )
    Q_PROPERTY(int     mPercentCpu1Kernel   READ getPercentCpu1Kernel   NOTIFY signalEventChangedPercentCpu1Kernel)
    Q_PROPERTY(int     mPercentCpu2Kernel   READ getPercentCpu2Kernel   NOTIFY signalEventChangedPercentCpu2Kernel)
    Q_PROPERTY(int     mPercentCpu1App      READ getPercentCpu1App      NOTIFY signalEventChangedPercentCpu1App   )
    Q_PROPERTY(int     mPercentCpu2App      READ getPercentCpu2App      NOTIFY signalEventChangedPercentCpu2App   )
    Q_PROPERTY(int     mPercentCpu1Verify   READ getPercentCpu1Verify   NOTIFY signalEventChangedPercentCpu1Verify)
    Q_PROPERTY(int     mPercentCpu2Verify   READ getPercentCpu2Verify   NOTIFY signalEventChangedPercentCpu2Verify)
    Q_PROPERTY(QString mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg           )

public:
    int         mAccessMode         = ValveEnumDef::ACCESS_LOCAL;
    bool        mIsRS232Test        = false;
    QString     mCpu1KernelFile     = "";
    QString     mCpu2KernelFile     = "";
    int         mDFUStep            = -1;
    int         mPercentCpu1Kernel  = 0;
    int         mPercentCpu2Kernel  = 0;
    int         mPercentCpu1App     = 0;
    int         mPercentCpu2App     = 0;
    int         mPercentCpu1Verify  = 0;
    int         mPercentCpu2Verify  = 0;
    QString     mErrMsg             = "";

    int     getAccessMode        (){ return mAccessMode        ;}
    bool    getIsRS232Test       (){ return mIsRS232Test       ;}
    QString getCpu1KernelFile    (){ return mCpu1KernelFile    ;}
    QString getCpu2KernelFile    (){ return mCpu2KernelFile    ;}
    int     getDFUStep           (){ return mDFUStep           ;}
    int     getPercentCpu1Kernel (){ return mPercentCpu1Kernel ;}
    int     getPercentCpu2Kernel (){ return mPercentCpu2Kernel ;}
    int     getPercentCpu1App    (){ return mPercentCpu1App    ;}
    int     getPercentCpu2App    (){ return mPercentCpu2App    ;}
    int     getPercentCpu1Verify (){ return mPercentCpu1Verify ;}
    int     getPercentCpu2Verify (){ return mPercentCpu2Verify ;}
    QString getErrMsg            (){ return mErrMsg            ;}

    void    setAccessMode        (int     value){ if(mAccessMode         == value) return; mAccessMode         = value; emit signalEventChangedAccessMode        (value); }
    void    setIsRS232Test       (bool    value){ if(mIsRS232Test        == value) return; mIsRS232Test        = value; emit signalEventChangedIsRS232Test       (value); }
    void    setCpu1KernelFile    (QString value){ if(mCpu1KernelFile     == value) return; mCpu1KernelFile     = value; emit signalEventChangedCpu1KernelFile    (value); }
    void    setCpu2KernelFile    (QString value){ if(mCpu2KernelFile     == value) return; mCpu2KernelFile     = value; emit signalEventChangedCpu2KernelFile    (value); }
    void    setDFUStep           (int     value){ if(mDFUStep            == value) return; mDFUStep            = value; emit signalEventChangedDFUStep           (value); }
    void    setPercentCpu1Kernel (int     value){ if(mPercentCpu1Kernel  == value) return; mPercentCpu1Kernel  = value; emit signalEventChangedPercentCpu1Kernel (value); }
    void    setPercentCpu2Kernel (int     value){ if(mPercentCpu2Kernel  == value) return; mPercentCpu2Kernel  = value; emit signalEventChangedPercentCpu2Kernel (value); }
    void    setPercentCpu1App    (int     value){ if(mPercentCpu1App     == value) return; mPercentCpu1App     = value; emit signalEventChangedPercentCpu1App    (value); }
    void    setPercentCpu2App    (int     value){ if(mPercentCpu2App     == value) return; mPercentCpu2App     = value; emit signalEventChangedPercentCpu2App    (value); }
    void    setPercentCpu1Verify (int     value){ if(mPercentCpu1Verify  == value) return; mPercentCpu1Verify  = value; emit signalEventChangedPercentCpu1Verify (value); }
    void    setPercentCpu2Verify (int     value){ if(mPercentCpu2Verify  == value) return; mPercentCpu2Verify  = value; emit signalEventChangedPercentCpu2Verify (value); }
    void    setErrMsg            (QString value){ if(mErrMsg             == value) return; mErrMsg             = value; emit signalEventChangedErrMsg            (value); }

signals:
    void signalEventChangedAccessMode        (int     value);
    void signalEventChangedIsRS232Test       (bool    value);
    void signalEventChangedCpu1KernelFile    (QString value);
    void signalEventChangedCpu2KernelFile    (QString value);
    void signalEventChangedDFUStep           (int     value);
    void signalEventChangedPercentCpu1Kernel (int     value);
    void signalEventChangedPercentCpu2Kernel (int     value);
    void signalEventChangedPercentCpu1App    (int     value);
    void signalEventChangedPercentCpu2App    (int     value);
    void signalEventChangedPercentCpu1Verify (int     value);
    void signalEventChangedPercentCpu2Verify (int     value);
    void signalEventChangedErrMsg            (QString value);

    void signalEventCompleted(bool result, QString errMsg);

public:
    explicit FirmwareUpdateDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_RESULT_READY_DFU;
        ENABLE_SLOT_VALVE_CHANGED_DFU_STEP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_KERNEL;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_KERNEL;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_APP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_APP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_VERIFY;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_VERIFY;
        ENABLE_SLOT_VALVE_RESULT_DFU;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedDFUStep();
        onValveChangedDFUPctCpu1Kernel();
        onValveChangedDFUPctCpu2Kernel();
        onValveChangedDFUPctCpu1App();
        onValveChangedDFUPctCpu2App();
        onValveChangedDFUPctCpu1Verify();
        onValveChangedDFUPctCpu2Verify();

        QString defalutKernelFile = QString("%1/firmware/kernel_cpu01.txt").arg(QApplication::applicationDirPath());
        if(QFile::exists(defalutKernelFile))
            setCpu1KernelFile(defalutKernelFile);
        defalutKernelFile = QString("%1/firmware/kernel_cpu02.txt").arg(QApplication::applicationDirPath());
        if(QFile::exists(defalutKernelFile))
            setCpu2KernelFile(defalutKernelFile);

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    }
    ~FirmwareUpdateDlgModel()
    {
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedIsRS232Test()
    {
        setIsRS232Test(pValveSP->getIsRS232Test());
    }

    void onValveChangedDFUStep()
    {
        if(pValveSP->getDFUStep() == ValveFirmwareUpgradeDef::READY || pValveSP->getDFUStep() == ValveFirmwareUpgradeDef::COMPLETE)
            setDFUStep(FirmwareUpdateUiStepDef::DISCONNECT_CABLE);
        else
            setDFUStep(convertUIStep(pValveSP->getDFUStep()));
    }

    void onValveChangedDFUPctCpu1Kernel(){setPercentCpu1Kernel(pValveSP->getDFUPctCpu1Kernel());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu1Kernel;}
    void onValveChangedDFUPctCpu2Kernel(){setPercentCpu2Kernel(pValveSP->getDFUPctCpu2Kernel());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu2Kernel;}
    void onValveChangedDFUPctCpu1App   (){setPercentCpu1App   (pValveSP->getDFUPctCpu1App   ());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu1App   ;}
    void onValveChangedDFUPctCpu2App   (){setPercentCpu2App   (pValveSP->getDFUPctCpu2App   ());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu2App   ;}
    void onValveChangedDFUPctCpu1Verify(){setPercentCpu1Verify(pValveSP->getDFUPctCpu1Verify());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu1Verify;}
    void onValveChangedDFUPctCpu2Verify(){setPercentCpu2Verify(pValveSP->getDFUPctCpu2Verify());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu2Verify;}

    Q_INVOKABLE QString onCommandGetSelComPort()
    {
        return (pValveSP->getRetryConnect() || pValveSP->getIsConnected()) ? pValveSP->getConnectionInfo().split("-")[0] : "";
    }

    Q_INVOKABLE void onCommandSearchComPort()
    {
        QList<QSerialPortInfo> infoList = QSerialPortInfo::availablePorts();

        mComPortList.clear();

        foreach(QSerialPortInfo info, infoList)
        {
            mComPortList.append(info.portName());
        }
    }

    Q_INVOKABLE int onCommandGetComPortCount()
    {
        return mComPortList.size();
    }

    Q_INVOKABLE QString onCommandGetComPortName(int idx)
    {
        if(idx < mComPortList.size())
            return mComPortList[idx];

        return "";
    }

    Q_INVOKABLE void onCommandNext()
    {
        setDFUStep(getDFUStep() + 1);

        if(getDFUStep() == FirmwareUpdateUiStepDef::REBOOT_VALVE)
            pValveSP->readyFirmwareUpdate();
    }

    Q_INVOKABLE void onCommandUpdate(QString comport, QString cpu1KernelFile, QString cpu1AppFile, QString cpu2KernelFile, QString cpu2AppFile)
    {
        qDebug() << "[" << Q_FUNC_INFO << "] comport = " << comport << ", cpu1KernelFile = " << cpu1KernelFile << ", cpu1AppFile = "<< cpu1AppFile << ", cpu2KernelFile = " << cpu2KernelFile << ", cpu2AppFile = " << cpu2AppFile;

        mSelComPort     = comport;
        setCpu1KernelFile(cpu1KernelFile);
        mCpu1AppFile    = cpu1AppFile;
        setCpu2KernelFile(cpu2KernelFile);
        mCpu2AppFile    = cpu2AppFile;

        qDebug() << "[" << Q_FUNC_INFO << "] RetryConnect = "  << pValveSP->getRetryConnect() << ", IsConnected = " << pValveSP->getIsConnected();

//        setDFUStep(FirmwareUpdateUiStepDef::REBOOT_SCI_MODE);

//        if(pValveSP->getRetryConnect() || pValveSP->getIsConnected())
//        {
//            qDebug() << "[" << Q_FUNC_INFO << "]ready DFU";
//            pValveSP->readyFirmwareUpdate();

//        }
//        else
        {
            qDebug() << "[" << Q_FUNC_INFO << "]directly DFU";
            //onValveResultReadyDFU(true);
            pValveSP->firmwareUpdate(mSelComPort, QSerialPort::Baud38400, QSerialPort::Data8, QSerialPort::OneStop, QSerialPort::NoParity, mCpu1KernelFile, mCpu2KernelFile, mCpu1AppFile, mCpu2AppFile);
        }
    }

    void onValveResultReadyDFU(bool result)
    {
        if(result)
        {
       //     startTimer();
        }
    }

    void onValveResultDFU(bool result, QString errMsg)
    {
        if(result == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]Error = " << errMsg;


        }

        setErrMsg(errMsg);
        setDFUStep(FirmwareUpdateUiStepDef::COMPLETE);

        //emit signalEventCompleted(result, errMsg);
    }

private:
    QTimer      mTimer;
    QString     mSelComPort    ="";
    QStringList mComPortList   ;
    QString     mCpu1AppFile   ;
    QString     mCpu2AppFile   ;

    int convertUIStep(int dfuStep)
    {
        switch (dfuStep) {
        case (int)ValveFirmwareUpgradeDef::CONNECT_SERIAL : return FirmwareUpdateUiStepDef::CONNECT_SERIAL;
        case (int)ValveFirmwareUpgradeDef::CPU1_DN_KERNEL : return FirmwareUpdateUiStepDef::CPU1_DN_KERNEL;
        case (int)ValveFirmwareUpgradeDef::CPU1_ERASE     : return FirmwareUpdateUiStepDef::CPU1_ERASE    ;
        case (int)ValveFirmwareUpgradeDef::CPU1_DN_APP    : return FirmwareUpdateUiStepDef::CPU1_DN_APP   ;
        case (int)ValveFirmwareUpgradeDef::CPU1_VERIFY    : return FirmwareUpdateUiStepDef::CPU1_VERIFY   ;
        case (int)ValveFirmwareUpgradeDef::CPU1_RESET     : return FirmwareUpdateUiStepDef::CPU1_RESET    ;
        case (int)ValveFirmwareUpgradeDef::CPU2_DN_KERNEL : return FirmwareUpdateUiStepDef::CPU2_DN_KERNEL;
        case (int)ValveFirmwareUpgradeDef::CPU2_ERASE     : return FirmwareUpdateUiStepDef::CPU2_ERASE    ;
        case (int)ValveFirmwareUpgradeDef::CPU2_DN_APP    : return FirmwareUpdateUiStepDef::CPU2_DN_APP   ;
        case (int)ValveFirmwareUpgradeDef::CPU2_VERIFY    : return FirmwareUpdateUiStepDef::CPU2_VERIFY   ;
        case (int)ValveFirmwareUpgradeDef::CPU2_RESET     : return FirmwareUpdateUiStepDef::CPU2_RESET    ;
        default: return mDFUStep;
        }
    }

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(5000);
    }

public slots:
    void onTimeout()
    {
//        if(getDFUStep() == FirmwareUpdateUiStepDef::REBOOT_SCI_MODE)
//            pValveSP->firmwareUpdate(mSelComPort, QSerialPort::Baud38400, QSerialPort::Data8, QSerialPort::OneStop, QSerialPort::NoParity, mCpu1KernelFile, mCpu2KernelFile, mCpu1AppFile, mCpu2AppFile);
    }
};
#endif // FIRMWAREUPDATEDLGMODEL_H
