#ifndef VALVECONNECTOPTION_H
#define VALVECONNECTOPTION_H

#include <QObject>
#include <QMutex>
#include <QDir>

#include "source/service/valve/device/serialvalve.h"

class ValveConnectOption : public QObject
{
    Q_OBJECT
private:
    mutable QMutex m_mutex;


public :
    static ValveConnectOption * getInstance()
    {
        static ValveConnectOption *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new ValveConnectOption();
        }

        return mpSelf;
    }

    explicit ValveConnectOption(QObject *parent = nullptr):QObject(parent)
    {
    }
    ~ValveConnectOption()
    {
    }

    void setConnectionList(QList<SerialConnectionOpt> list)
    {
        QMutexLocker locker(&m_mutex);  // 뮤텍스 잠금

        QString dirPath = QString("%1/config").arg(QApplication::applicationDirPath());
        QDir dir(dirPath);
        if (!dir.exists())
        {
            if (!dir.mkpath("."))
            {
                qDebug() << "[ValveConnectOption::writeFile] 디렉토리 생성 실패:" << dirPath;
                return;
            }
        }

        QFile file;
        QString filePath = dir.filePath("connection_option.json");
        file.setFileName(filePath);

        if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        {
            qDebug() << "[ValveConnectOption::writeFile] 파일 열기 실패:" << filePath;
            return;
        }

        QJsonArray jsonArray;

        for (const SerialConnectionOpt& opt : list)
        {
            QJsonObject obj;
            obj["name"]     = opt.mName;
            obj["isSelect"] = opt.mIsSelect;
            obj["baudrate"] = static_cast<int>(opt.mBaudRate);
            obj["dataBits"] = static_cast<int>(opt.mDataBits);
            obj["stopBits"] = static_cast<int>(opt.mStopBits);
            obj["parity"]   = static_cast<int>(opt.mParity);

            jsonArray.append(obj);
        }

        QJsonDocument doc(jsonArray);
        QByteArray byteArray = doc.toJson(QJsonDocument::Indented);

        qint64 bytesWritten = file.write(byteArray);

        if (bytesWritten == -1)
        {
            qDebug() << "[ValveConnectOption::writeFile] 파일 쓰기 실패";
        }
        else
        {
            qDebug() << "[ValveConnectOption::writeFile] 파일 쓰기 성공, 크기:" << bytesWritten << "bytes";
        }

        file.close();
    }

    QByteArray readFile()
    {
        QMutexLocker locker(&m_mutex);  // 뮤텍스 잠금
        QFile file;
        QJsonDocument doc;
        QByteArray retByteArray;

        file.setFileName(QString("%1/config/connection_option.json").arg(QApplication::applicationDirPath()));
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]fail";
            return retByteArray;
        }

        retByteArray = file.readAll();

        file.close();

        return retByteArray;
    }

    QList<SerialConnectionOpt> getConnectionList()
    {
        QList<SerialConnectionOpt> list;
        QJsonDocument doc;
        QByteArray loadData = readFile();

        if(loadData.count() < 1)
        {
            return list;
        }

        try{
            doc = QJsonDocument::fromJson(loadData);

            QJsonArray array = doc.array();

            for(int idx = 0; idx < array.count(); idx++)
            {
                SerialConnectionOpt opt;
                QJsonObject obj = array.at(idx).toObject();

                opt.mName     =                        obj.value("name").toString()  ;
                opt.mIsSelect =                        obj.value("isSelect").toBool();
                opt.mBaudRate = (QSerialPort::BaudRate)obj.value("baudrate").toInt() ;
                opt.mDataBits = (QSerialPort::DataBits)obj.value("dataBits").toInt() ;
                opt.mStopBits = (QSerialPort::StopBits)obj.value("stopBits").toInt() ;
                opt.mParity   = (QSerialPort::Parity  )obj.value("parity").toInt()   ;

                qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]mName = "<< opt.mName << ",mIsSelect =" << opt.mIsSelect << ",mBaudRate = " << opt.mBaudRate << ", mDataBits = " << opt.mDataBits << ", mStopBits = " << opt.mStopBits << ", mParity = " << opt.mParity;

                if(opt.mIsSelect)
                    list.append(opt);
            }
        }
        catch (int ex)
        {
            qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]exception";
        }

        return list;
    }

    QList<SerialConnectionOpt> getAllConnectionList()
    {
        QList<SerialConnectionOpt> list;
        QJsonDocument doc;
        QByteArray loadData = readFile();

        if(loadData.count() < 1)
        {
            return list;
        }

        try{
            doc = QJsonDocument::fromJson(loadData);

            QJsonArray array = doc.array();

            for(int idx = 0; idx < array.count(); idx++)
            {
                SerialConnectionOpt opt;
                QJsonObject obj = array.at(idx).toObject();

                opt.mName     =                        obj.value("name").toString()  ;
                opt.mIsSelect =                        obj.value("isSelect").toBool();
                opt.mBaudRate = (QSerialPort::BaudRate)obj.value("baudrate").toInt() ;
                opt.mDataBits = (QSerialPort::DataBits)obj.value("dataBits").toInt() ;
                opt.mStopBits = (QSerialPort::StopBits)obj.value("stopBits").toInt() ;
                opt.mParity   = (QSerialPort::Parity  )obj.value("parity").toInt()   ;

                list.append(opt);
                qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]mName = "<< opt.mName << ",mIsSelect =" << opt.mIsSelect << ",mBaudRate = " << opt.mBaudRate << ", mDataBits = " << opt.mDataBits << ", mStopBits = " << opt.mStopBits << ", mParity = " << opt.mParity;
            }
        }
        catch (int ex)
        {
            qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]exception";
        }

        return list;
    }
};
#endif // VALVECONNECTOPTION_H
