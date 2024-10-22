#ifndef SEARCHDEVICEDLGMODEL_H
#define SEARCHDEVICEDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class PortInfo
{
public:
    QString   mConnType  = "";
    QString   mPortName  = "";
    QString   mSerial    = "";
    bool      mIsReady   = false;

    PortInfo(){}
    PortInfo(const PortInfo& copy) :
        mConnType(copy.mConnType),
        mPortName(copy.mPortName),
        mSerial  (copy.mSerial  ),
        mIsReady (copy.mIsReady ){}

    ~PortInfo(){}

    PortInfo& operator=(const PortInfo& other)
    {
        mConnType = other.mConnType;
        mPortName = other.mPortName;
        mSerial   = other.mSerial  ;
        mIsReady  = other.mIsReady ;

        return *this;
    }

    bool compare(const PortInfo& other)
    {
        if(   mConnType == other.mConnType
           && mPortName == other.mPortName
           && mSerial   == other.mSerial
           && mIsReady  == other.mIsReady)
            return true;

        return false;
    }
};
Q_DECLARE_METATYPE(PortInfo);

class SearchDeviceDlgModel : public QObject
{
    Q_OBJECT

public:
    QList<PortInfo> mPortList;

signals:
    void signalEventChangedPortList();

public slots:
    void onValveSearchedDevice(QStringList portList)
    {
        if(compareAndCopy(portList) == false)
            emit signalEventChangedPortList();
    }

    Q_INVOKABLE int onCommandGetPortListCount()
    {
        return mPortList.count();
    }

    Q_INVOKABLE QString onCommandGetConnType(int idx)
    {
        if(mPortList.count() <= idx)
            return "";
        return mPortList[idx].mConnType;
    }

    Q_INVOKABLE QString onCommandGetPortName(int idx)
    {
        if(mPortList.count() <= idx)
            return "";
        return mPortList[idx].mPortName;
    }

    Q_INVOKABLE QString onCommandGetSerial(int idx)
    {
        if(mPortList.count() <= idx)
            return "";
        return mPortList[idx].mSerial;
    }

    Q_INVOKABLE bool onCommandIsReady(int idx)
    {
        if(mPortList.count() <= idx)
            return false;

        return mPortList[idx].mIsReady;
    }

    Q_INVOKABLE int onCommandGetOptionCount()
    {
        return optionList.count();
    }

    Q_INVOKABLE QString onCommandGetOptionName(int idx)
    {
        return optionList[idx].mName;
    }

    Q_INVOKABLE bool onCommandGetOptionIsSelect(int idx)
    {
        return optionList[idx].mIsSelect;
    }

    Q_INVOKABLE void onCommandSelOption(int idx)
    {
        optionList[idx].mIsSelect = !optionList[idx].mIsSelect;

        ValveConnectOption::getInstance()->setConnectionList(optionList);
        return ;
    }

public:
    explicit SearchDeviceDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_SEARCHED_DEVICE;

        optionList = ValveConnectOption::getInstance()->getAllConnectionList();

        pValveSP->search();
    }
    ~SearchDeviceDlgModel()
    {
        pValveSP->searchStop();
    }

private:
    QList<SerialConnectionOpt> optionList;

    bool compareAndCopy(QStringList portList)
    {
        QList<PortInfo> newPortList;
        bool compareResult = true;

        for(int i = 0; i < portList.count(); i ++)
        {
            PortInfo portInfo;
            QStringList infoList = portList[i].split(":");
            portInfo.mConnType = infoList[0];
            portInfo.mIsReady  = (infoList[1] == "A" ? true : false);
            portInfo.mPortName = infoList[2];
            portInfo.mSerial   = infoList[3];

            newPortList.append(portInfo);
        }

        if(mPortList.count() != newPortList.count())
        {
            compareResult = false;
        }
        else
        {
            for(int i = 0; i < portList.count(); i ++)
            {
                if(mPortList[i].compare(newPortList[i]) == false)
                {
                    compareResult = false;
                    break;
                }
            }
        }

        if(compareResult == false)
        {
            mPortList.clear();
            mPortList = newPortList;
        }

        return compareResult;
    }

};
#endif // SEARCHDEVICEDLGMODEL_H
