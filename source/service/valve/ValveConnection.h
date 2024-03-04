#ifndef VALVECONNECTION_H
#define VALVECONNECTION_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "source/service/valve/device/serialvalve.h"

class ValveConnEnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eConnectType)

public:
    enum eConnectType{
        CONNECT_UNKNOW  = -1,
        CONNECT_SERIAL  = 0,
        CONNECT_UDP     = 1,
        CONNECT_TCP     = 2,
    };
};

class ValveConnection : public QObject
{
    Q_OBJECT
private:
    QObject                         *mpValve = nullptr;
    ValveConnEnumDef::eConnectType   mLastConnType = ValveConnEnumDef::CONNECT_UNKNOW;
    QString                          mValveAddr = "";

public:
    static ValveConnEnumDef::eConnectType getConnTypeByString(QString typeStr)
    {
        if(typeStr == "Serial")
            return ValveConnEnumDef::CONNECT_SERIAL;
        else if(typeStr == "TCP")
            return ValveConnEnumDef::CONNECT_TCP;
        else if(typeStr == "UDP")
            return ValveConnEnumDef::CONNECT_UDP;
        else
            return ValveConnEnumDef::CONNECT_SERIAL;
    }

    explicit ValveConnection(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[ValveConnection]Create";
    }
    ~ValveConnection()
    {
        qDebug() << "[ValveConnection]Destruction";
        if(mpValve != nullptr)
            delete mpValve;
    }

    QObject * getConnectionPtr()
    {
        return mpValve;
    }

    QString getConnectionInfo()
    {
        if(mpValve != nullptr)
            return qobject_cast<IValve*>(mpValve)->getConnectionInfo();

        return "";
    }

    bool IsConnected()
    {
        if(mpValve != nullptr)
            return true;

        return false;
    }

    QStringList searchDevice(QString additionalInfo = "")
    {
        QStringList deviceList;

        deviceList = searchDeviceSerial(additionalInfo);

        for(int i = 0; i < deviceList.size(); i ++)
        {
            deviceList[i] = QString("Serial:%1").arg(deviceList[i]);
        }

        return deviceList;
    }

    bool connectValve(ValveConnEnumDef::eConnectType type, QString valveAddr)
    {
        qDebug() << "[ValveConnection][connectValve]type = " << type << ", valveAddr = "<< valveAddr;

        disconnectValve();

        switch ((int)type) {
        case (int)ValveConnEnumDef::CONNECT_SERIAL:
            mpValve = new SerialValve();
        break;

        case (int)ValveConnEnumDef::CONNECT_TCP:
            //mpValve = new SerialValve(this);
        break;

        case (int)ValveConnEnumDef::CONNECT_UDP:
            //mpValve = new SerialValve(this);
        break;
        }

        if(qobject_cast<IValve*>(mpValve)->connectValve(valveAddr) == false)
        {
            qDebug() << "[ValveConnection][connectValve]failed";
            disconnectValve();
            mLastConnType = ValveConnEnumDef::CONNECT_UNKNOW;
            return false;
        }

        mLastConnType = type;
        mValveAddr    = valveAddr;
        return true;
    }

    bool reConnectValve()
    {
        qDebug() << "[ValveConnection][reConnectValve]";

        if(mLastConnType == ValveConnEnumDef::CONNECT_UNKNOW)
            return false;


        ValveConnEnumDef::eConnectType type      = mLastConnType;
        QString                        valveAddr = mValveAddr;

        return connectValve(type, valveAddr);
    }

    void disconnectValve()
    {
        qDebug() << "[" << Q_FUNC_INFO <<"]";
        if(mpValve != nullptr)
        {
            delete mpValve;
        }

        mpValve = nullptr;

        qDebug() << "[" << Q_FUNC_INFO <<"] END";
    }

    bool sendCmd(QString cmd, QString value, QString checkPreFix, int checkLength, QString & resValue, qint64 timeout, IValve::eValveError * pOErr = nullptr)
    {
        if(mpValve == nullptr)
            return false;

        return qobject_cast<IValve*>(mpValve)->sendCmd(cmd, value, checkPreFix, checkLength, resValue, timeout, pOErr);
    }

private:
    QStringList searchDeviceSerial(QString additionalInfo = "") // additionalInfo is port of tcp / udp
    {
        SerialValve * pSerialValve = nullptr;

        if(mpValve != nullptr && (qobject_cast<IValve*>(mpValve)->getConnectTypeNmae() == "Serial"))
        {
            pSerialValve = qobject_cast<SerialValve*>(mpValve);
        }
        else
        {
            pSerialValve = new SerialValve();
        }

        qDebug() << "[" << Q_FUNC_INFO << "]";

        QStringList portList = pSerialValve->searchDevice("i:83","","i:83", 0, additionalInfo);

        if(pSerialValve != mpValve)
            delete  pSerialValve;

        return portList;
    }
};
#endif // VALVECONNECTION_H
