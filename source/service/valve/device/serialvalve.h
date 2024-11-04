#ifndef SERIALVALVE_H
#define SERIALVALVE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QHash>

#include "source/service/valve/device/ivalve.h"
#include <QFile>
#include <QApplication>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

class SerialValve : public QObject, public IValve
{
    Q_OBJECT
    Q_INTERFACES(IValve)
signals:
    void signalEventAddLog(QString connType, bool isSucc, QString send, QString rcv);

private:
    QSerialPort mSerialPort;
    QObject *mpCommunicationTraceDlgModel = nullptr;

    static QHash<QString, SerialConnectionOpt> * getConnectionHash()
    {
        static QHash<QString, SerialConnectionOpt>  mConnections;

        return &mConnections;
    }

public:
    explicit SerialValve(QObject *parent = nullptr):QObject(parent)
    {
    }
    explicit SerialValve(QObject *pCommunicationTraceDlgModel, QObject *parent = nullptr):QObject(parent)
    {
        mpCommunicationTraceDlgModel = pCommunicationTraceDlgModel;
        connect(this, SIGNAL(signalEventAddLog(QString, bool, QString, QString)), pCommunicationTraceDlgModel, SLOT(onSignalEventAddLog(QString, bool,QString, QString)));
    }
    ~SerialValve()
    {
        if(mpCommunicationTraceDlgModel != nullptr)
            disconnect(this, SIGNAL(signalEventAddLog(QString, bool,QString, QString)), mpCommunicationTraceDlgModel, SLOT(onSignalEventAddLog(QString, bool,QString, QString)));

        qDebug() << "[" << Q_FUNC_INFO << "]";
        disconnectValve();
    }

    QString getConnectionInfo()
    {
        QString parity = mSerialPort.parity() == QSerialPort::NoParity ? "N"
                         : mSerialPort.parity() == QSerialPort::EvenParity ? "E"
                         : mSerialPort.parity() == QSerialPort::OddParity ? "O"
                         : mSerialPort.parity() == QSerialPort::SpaceParity ? "S"
                         : mSerialPort.parity() == QSerialPort::SpaceParity ? "M" : "U";

        return QString("%1-%2-%3-%4-%5").arg(mSerialPort.portName()).arg(mSerialPort.baudRate()).arg(mSerialPort.dataBits()).arg(mSerialPort.stopBits()).arg(parity);
    }

    QString getConnectTypeNmae()
    {
        return "Serial";
    }

    QString getValveAddr()
    {
        return mSerialPort.portName();
    }

    QSerialPort * getSerialPort()
    {
        return &mSerialPort;
    }

    void clearReadBuffer()
    {
        if(mSerialPort.isOpen())
            mSerialPort.readAll();
    }
    QStringList searchDevice(QList<SerialConnectionOpt>connList, QString cmd, QString value, QString checkPreFix, int checkLength, QString additionalInfo = "")
    {
        Q_UNUSED(additionalInfo);

//        QString dummy;
//        QStringList portList;
//        QSerialPort *pSearchPort = nullptr;

//        QList<QSerialPortInfo> infoList = QSerialPortInfo::availablePorts();

//        foreach(QSerialPortInfo info, infoList)
//        {
//            bool result = false;
//            QString readData;

//            if(mSerialPort.portName() == info.portName())
//            {
//                pSearchPort = &mSerialPort;
//            }
//            else
//            {
//                pSearchPort = new QSerialPort();
//                pSearchPort->setPortName(info.portName());
//                pSearchPort->setBaudRate(QSerialPort::Baud38400);
//                pSearchPort->setDataBits(QSerialPort::Data7);
//                pSearchPort->setStopBits(QSerialPort::OneStop);
//                pSearchPort->setParity(QSerialPort::EvenParity);

//                if(pSearchPort->open(QIODevice::ReadWrite) == false)
//                {
//                    portList.append(QString("D:%1:").arg(info.portName()));
//                    continue;
//                }
//            }

//            if(sendCmd(pSearchPort, cmd, value, checkPreFix, checkLength, dummy, 300))
//            {
//                QString value = getValue(checkPreFix, dummy);

//                portList.append(QString("A:%1:%2").arg(info.portName()).arg(value));
//            }
//            else
//            {
//                portList.append(QString("D:%1:").arg(info.portName()));
//            }

//            if(mSerialPort.portName() != info.portName())
//            {
//                pSearchPort->close();
//                delete pSearchPort;
//                pSearchPort = nullptr;
//            }
//        }
//        return portList;

        getConnectionHash()->clear();
        //readConnectionOptions();


        QString dummy;
        QStringList portList;
        SerialValve * pSeacherValve = nullptr;

        QList<QSerialPortInfo> infoList = QSerialPortInfo::availablePorts();

        foreach(QSerialPortInfo info, infoList)
        {
            bool result = false;
            QString readData;

            if(mSerialPort.portName() == info.portName())
            {
                SerialConnectionOpt opt;

                opt.mBaudRate = (QSerialPort::BaudRate)(mSerialPort.baudRate());
                opt.mDataBits = mSerialPort.dataBits();
                opt.mStopBits = mSerialPort.stopBits();
                opt.mParity   = mSerialPort.parity()  ;

                result = sendCmdInt(cmd, value, checkPreFix, checkLength, dummy, 300);

                getConnectionHash()->insert(info.portName(), opt);

                qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]connected port["<< info.portName() <<"] search : result = " << result;
            }
            else
            {
                for(int connIdx = 0; connIdx< connList.count() && result == false; connIdx++)
                {
                    qDebug() << "[khko_debug][" << Q_FUNC_INFO << "] port[" << info.portName() <<"] TRY";

                    pSeacherValve = new SerialValve();

                    SerialConnectionOpt opt = connList[connIdx];

                    if(pSeacherValve->connectValve(info.portName(), opt.mBaudRate, opt.mDataBits, opt.mStopBits, opt.mParity))
                    {
                        result = pSeacherValve->sendCmdInt(cmd, value, checkPreFix, checkLength, dummy, 300);

                        if(result)
                        {
                            qDebug() << "[" << Q_FUNC_INFO << "]Inerted connection info : " << info.portName() << ", baudRate = " << opt.mBaudRate << ", dataBit = " << opt.mDataBits << ", stopBit = " << opt.mStopBits << ", parity = " << opt.mParity;
                            getConnectionHash()->insert(info.portName(), opt);
                        }

                        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]port["<< info.portName() <<"] search : result = " << result;
                    }
                    else
                    {
                        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "] port[" << info.portName() <<"] is open fail";
                    }

                    pSeacherValve->disconnectValve();
                    delete pSeacherValve;
                    pSeacherValve = nullptr;
                }
            }

            if(result)
            {
                QString value = getValue(checkPreFix, dummy);

                portList.append(QString("A:%1:%2").arg(info.portName()).arg(value));
            }
            else
            {
                portList.append(QString("D:%1:").arg(info.portName()));
            }
        }
        return portList;
    }


    bool connectValve(QString portName)
    {
        QString readData;
        SerialConnectionOpt opt;

        qDebug() << "[" << Q_FUNC_INFO << "]" << portName;

        disconnectValve();

        if(getConnectionHash()->contains(portName))
        {
            qDebug() << "[" << Q_FUNC_INFO << "] port found";
            opt = getConnectionHash()->find(portName).value();
        }

        mSerialPort.setPortName(portName);
        mSerialPort.setBaudRate(opt.mBaudRate /*QSerialPort::Baud38400*/ );
        mSerialPort.setDataBits(opt.mDataBits /*QSerialPort::Data7*/     );
        mSerialPort.setStopBits(opt.mStopBits /*QSerialPort::OneStop*/   );
        mSerialPort.setParity  (opt.mParity   /*QSerialPort::EvenParity*/);

        qDebug() << "[SerialValve][connectValve]" << portName << ", baudRate = " << opt.mBaudRate << ", dataBit = " << opt.mDataBits << ", stopBit = " << opt.mStopBits << ", parity = " << opt.mParity;

        if(mSerialPort.open(QIODevice::ReadWrite) == false)
        {
            qDebug() << "[SerialValve][connectValve]failed";
             return false;
        }
        return true;
    }


    bool connectValve(QString portName, QSerialPort::BaudRate baudRate, QSerialPort::DataBits dataBit, QSerialPort::StopBits stopBit, QSerialPort::Parity parity)
    {
        QString readData;

        qDebug() << "[" << Q_FUNC_INFO << "]" << portName << ", baudRate = " << baudRate << ", dataBit = " << dataBit << ", stopBit = " << stopBit << ", parity = " << parity;

        disconnectValve();

        mSerialPort.setPortName(portName);
        mSerialPort.setBaudRate(baudRate /*QSerialPort::Baud38400*/);
        mSerialPort.setDataBits(dataBit/*QSerialPort::Data7*/);
        mSerialPort.setStopBits(stopBit/*QSerialPort::OneStop*/);
        mSerialPort.setParity(parity/*QSerialPort::EvenParity*/);

        if(mSerialPort.open(QIODevice::ReadWrite) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] failed : " << mSerialPort.error();
             return false;
        }
        return true;
    }

    void disconnectValve()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        if(mSerialPort.isOpen())
        {
            qDebug() << "[" << Q_FUNC_INFO << "]Is Open";
            mSerialPort.close();
        }
        qDebug() << "[" << Q_FUNC_INFO << "]END";
    }

    bool sendCmd(QString cmd, QString value, QString checkPreFix, int checkLength, QString & resValue, qint64 timeout, eValveError * pOErrs = nullptr) // khko add proc disconnect
    {
        return sendCmdInt(cmd, value, checkPreFix, checkLength, resValue, timeout, pOErrs); // khko add proc disconnect
    }

    bool sendCmdInt(QString cmd, QString value, QString checkPreFix, int checkLength, QString & resValue, qint64 timeout, eValveError * pOErrs = nullptr) // khko add proc disconnect
    {
        static bool sema =false;

        if(sema == true)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]error";
        }

        sema = true;

        QString sndFrame = QString("%1%2\r\n").arg(cmd).arg(value);
        QByteArray sndFrameBuffer = sndFrame.toUtf8();
        QByteArray readFramBuffer;

        // 남아 있는 버퍼 청소
        {
            QByteArray dummyBuff = mSerialPort.readAll();

            if(dummyBuff.size() > 0)
                qDebug() << "[SerialValve][sendCmd]remained buffer = " << QString(dummyBuff);
        }

        if(write(sndFrameBuffer, timeout, pOErrs) == false)
        {
            sema = false;
            return false;
        }

        readFramBuffer = read("\r\n", -1, timeout, pOErrs);

        if(readFramBuffer.size() == 0)
        {
            sema = false;
            return false;
        }

        resValue = QString(readFramBuffer);

        if(checkLength != 0)
            checkLength = checkPreFix.length() + checkLength;

        if((!resValue.startsWith(checkPreFix) && !resValue.startsWith("E:") && checkPreFix != "") || (resValue.length() < checkLength && resValue.startsWith(checkPreFix)))
        {
            qDebug() << "[" << Q_FUNC_INFO << "] reponse invaild packet : data = " << resValue;
            //if(pOErrs != nullptr)  // khko_need del
            //    *pOErrs = eValveError::ResourceError;

            sema = false;
            return false;
        }

        sema = false;
        return true;
    }

    bool write(QByteArray data, qint64 timeout, eValveError * pOErrs = nullptr) // khko add proc disconnect
    {
        qint64 msec;

        if(mSerialPort.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] port is not openned";

            if(pOErrs != nullptr)
                *pOErrs= eValveError::OpenError;
            return false;
        }

        mSerialPort.clearError();

        msec = QDateTime::currentMSecsSinceEpoch();

        qint64 bytesWritten = mSerialPort.write(data);

        if (bytesWritten != -1 && bytesWritten == data.size() && mSerialPort.waitForBytesWritten(timeout))
        {
            if(pOErrs != nullptr)
                *pOErrs= eValveError::NoError;

            return true;
        }

        qDebug() << "[" << Q_FUNC_INFO << "]write error, req time = " << msec << ", cmp time = "<< QDateTime::currentMSecsSinceEpoch() <<", data = " << QString(data);

        if(bytesWritten == -1 || bytesWritten == data.size())
        {
            qDebug() << "[" << Q_FUNC_INFO << "]write str = write size error";

            if(pOErrs != nullptr)
                *pOErrs = WriteError;
        }
        else
        {
            if(mSerialPort.error() != QSerialPort::NoError)
            {
                qDebug() << "[" << Q_FUNC_INFO << "]write error = " << mSerialPort.error();

                if(pOErrs != nullptr)
                    *pOErrs = convertValveError(mSerialPort.error());
            }
            else
            {
                qDebug() << "[" << Q_FUNC_INFO << "]write error = unknow error";

                if(pOErrs != nullptr)
                    *pOErrs = WriteError;
            }
        }

        return false;
    }

    QByteArray read(const char * endChar, int maxLen, qint64 timeout, eValveError * pOErrs = nullptr) // khko add proc disconnect
    {
        QByteArray readBuf;
        qint64 msec;

        //qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mSerialPort.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] port is not openned";

            if(pOErrs != nullptr)
                *pOErrs= eValveError::OpenError;

            return readBuf;
        }

        mSerialPort.clearError();

        msec = QDateTime::currentMSecsSinceEpoch();

        while (true) {
            mSerialPort.waitForReadyRead(10);

            QByteArray tempBuf = mSerialPort.readAll();

            //qDebug() << "[khko_debug][" << Q_FUNC_INFO << "] read data = " << QString(tempBuf);

            foreach(char tempData, tempBuf)
            {
                readBuf.append(tempData);

                if(readBuf.endsWith(endChar) || readBuf.size() >= maxLen)
                {
                    if(pOErrs != nullptr)
                        * pOErrs = NoError;
                    readBuf.replace(endChar, "");

                    if(readBuf.size() != maxLen)
                        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]size = "<< readBuf.size()  <<", read data = " << QString(readBuf);

                    return readBuf;
                }
            }

            if(timeout < (QDateTime::currentMSecsSinceEpoch() - msec))
                break;
        }

        qDebug() << "[" << Q_FUNC_INFO << "]read error, req time = " << msec << ", cmp time = "<< QDateTime::currentMSecsSinceEpoch() <<", data = " << QString(readBuf);

        readBuf.clear();

        if(mSerialPort.error() == QSerialPort::NoError)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]read error(user error) = unknow error";

            if(pOErrs != nullptr)
                *pOErrs = ReadError;
        }
        else
        {
            qDebug() << "[" << Q_FUNC_INFO << "]read error(system error) = " << mSerialPort.error();

            if(pOErrs != nullptr)
                *pOErrs = convertValveError(mSerialPort.error());
        }

        return readBuf;
    }

    QString mTraceReadBuffer;
    void startTrace()
    {
        mTraceReadBuffer = "";
    }
    QString readTarce(const char * endChar) // khko add proc disconnect
    {
        QString ret = "";

        if(mSerialPort.isOpen() == false)
        {
            return ret;
        }

        mSerialPort.clearError();

        QByteArray recv = mSerialPort.readAll();

        qDebug() << "[" << Q_FUNC_INFO << "])recv = " << QString(recv);

        mTraceReadBuffer.append(recv);

        if(mTraceReadBuffer.endsWith(endChar))
        {
            ret = mTraceReadBuffer;
            mTraceReadBuffer.clear();
        }
        return ret;
    }

    QString getValue(QString checkPrefix, QString readData)
    {
        if(readData.startsWith("E:"))
        {
            return "";
        }

        if(readData.startsWith(checkPrefix) == false)
        {
            return "";
        }

        QString value = readData.mid(checkPrefix.length());

        if(value == nullptr || value.length() < 1)
        {
            return "";
        }

        return value;
    }

    eValveError convertValveError(QSerialPort::SerialPortError err)
    {
        switch (err) {
        case QSerialPort::NoError                  : return eValveError::NoError                  ;
        case QSerialPort::DeviceNotFoundError      : return eValveError::DeviceNotFoundError      ;
        case QSerialPort::PermissionError          : return eValveError::PermissionError          ;
        case QSerialPort::OpenError                : return eValveError::OpenError                ;
        case QSerialPort::ParityError              : return eValveError::ParityError              ;
        case QSerialPort::FramingError             : return eValveError::FramingError             ;
        case QSerialPort::BreakConditionError      : return eValveError::BreakConditionError      ;
        case QSerialPort::WriteError               : return eValveError::WriteError               ;
        case QSerialPort::ReadError                : return eValveError::ReadError                ;
        case QSerialPort::ResourceError            : return eValveError::ResourceError            ;
        case QSerialPort::UnsupportedOperationError: return eValveError::UnsupportedOperationError;
        case QSerialPort::TimeoutError             : return eValveError::TimeoutError             ;
        case QSerialPort::NotOpenError             : return eValveError::NotOpenError             ;
        default                                    : return eValveError::UnknownError             ;
        }
    }
};

#endif // SERIALVALVE_H

//    bool sendCmd(QSerialPort * pSerialPort, QString cmd, QString value, QString checkPreFix, int checkLength, QString & resValue, qint64 timeout, eValveError * pOErrs = nullptr) // khko add proc disconnect
//    {
//        static bool sema =false;

//        if(sema == true)
//        {
//            qDebug() << "[SerialValve][sendCmd]sema error";
//        }

//        sema = true;
//        qint64 msec; // khko_debug
//        QByteArray responseBuffer;

//        if(pSerialPort == nullptr)
//        {
//            sema = false;
//            return false;
//        }

//        if(!pSerialPort->isOpen())
//        {
//            qDebug() << "[SerialValve][sendCmd]port is not opened";
//            sema = false;
//            return false;
//        }

//        msec = QDateTime::currentMSecsSinceEpoch(); // khko_debug

//        QString frame = QString("%1%2\r\n").arg(cmd).arg(value);
//        QByteArray frameBuffer = frame.toUtf8();

//        QByteArray dummyBuff = pSerialPort->readAll(); // khko_debug

//        if(dummyBuff.size() > 0)
//            qDebug() << "[SerialValve][sendCmd]remained buffer = " << QString(dummyBuff);

//        qint64 bytesWritten = pSerialPort->write(frameBuffer);

//        if (bytesWritten == -1 || bytesWritten != frameBuffer.size()) {
//            qDebug() << "[SerialValve][sendCmd]writing is failed : data = " << frame;

//            if(pSerialPort->error() != QSerialPort::NoError)
//            {
//                qDebug() << "[SerialValve][sendCmd]write error = "<< pSerialPort->error();
//            }

//            if(pSerialPort->error() == QSerialPort::ResourceError && pOErrs != nullptr) // khko add proc disconnect
//                *pOErrs = eValveError::ResourceError;

//            sema = false;
//            return false;
//        }
//        else if (!pSerialPort->waitForBytesWritten(timeout)) {
//            if(QDateTime::currentMSecsSinceEpoch() - msec < timeout)
//            {
//                qDebug() << "[SerialValve][sendCmd]wait for written : timeout " << msec << " ~ " << QDateTime::currentMSecsSinceEpoch() << " : data = " << frame;
//            }

//            if(pSerialPort->error() != QSerialPort::NoError)
//            {
//                qDebug() << "[SerialValve][sendCmd]write(wait) error = "<< pSerialPort->error();
//            }

//            if(pSerialPort->error() == QSerialPort::ResourceError && pOErrs != nullptr) // khko add proc disconnect
//                *pOErrs = eValveError::ResourceError;

//            sema = false;
//            return false;
//        }

//        pSerialPort->waitForReadyRead(timeout);

//        do
//        {
//            QByteArray tempBuf = pSerialPort->readAll();

//            responseBuffer.append(tempBuf);

//            if(responseBuffer.endsWith("\r\n"))
//            {
//                QString responseStr(responseBuffer);

//                resValue = responseStr.replace("\r\n", "");

//                if((!responseStr.startsWith(checkPreFix) && !responseStr.startsWith("E:") && checkPreFix != "") || (resValue.length() < checkLength && responseStr.startsWith(checkPreFix)))
//                {
//                    qDebug() << "[SerialValve][sendCmd][rcv error][sent time =" << msec << ", rcv time = " <<  QDateTime::currentMSecsSinceEpoch() << "]sent data = " << frame << ", rcv data = " << QString(responseBuffer) << ", err = " << pSerialPort->errorString();
//                    //if(pOErrs != nullptr)
//                    //    *pOErrs = eValveError::ResourceError;
//                    sema = false;
//                    return false;
//                }

//                sema = false;
//                return true;

//                //if(responseStr.startsWith(checkPreFix) || responseStr.startsWith("E:"))
//                //{
//                //    resValue = responseStr;
//                //    return true;
//                //}
//            }
//        }while (pSerialPort->waitForReadyRead(timeout));


//        if(pSerialPort->error() != QSerialPort::NoError)
//        {
//            qDebug() << "[SerialValve][sendCmd]read timeout error = "<< pSerialPort->errorString() << ",sent data = " << frame ;
//        }

//        if(QDateTime::currentMSecsSinceEpoch() - msec < timeout)
//        {
//            qDebug() << "[SerialValve][sendCmd][rcv timeout][sent time =" << msec << ", rcv time = " <<  QDateTime::currentMSecsSinceEpoch() << "]sent data = " << frame << ", rcv data = " << QString(responseBuffer);
//        }
//        else
//        {
//            qDebug() << "[SerialValve][sendCmd][rcv timeout][sent time =" << msec << ", rcv time = " <<  QDateTime::currentMSecsSinceEpoch() << "]sent data = " << frame << ", rcv data = " << QString(responseBuffer);
//        }

//        sema = false;
//        return false;
//    }
