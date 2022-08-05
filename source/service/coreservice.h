#ifndef CORESERVICE_H
#define CORESERVICE_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>

#include "source/service/localsetting/localsettingsprovider.h"
#include "source/service/valve/valvesprovider.h"

#define pCoreService CoreService::getInstance()

#define ENABLE_SLOT_CORE_START connect(CoreService::getInstance(), SIGNAL(signalEventStarted()), this, SLOT(onCoreStartedService()))
#define ENABLE_SLOT_CORE_STOP  connect(CoreService::getInstance(), SIGNAL(signalEventStopped()), this, SLOT(onCoreStoppedService()))

class CoreService : public QObject
{
    Q_OBJECT
public:
    static CoreService * getInstance()
    {
        static CoreService *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new CoreService();
        }

        return mpSelf;
    }

public:
    bool mIsRunning = false;

    void start(QObject * context)
    {
        ENABLE_SLOT_VALVE_CHANGED_ISRUNNING;

        pLSettingSP->start();
        pValveSP->start();
    }
    void stop()
    {
        pValveSP->stop();

        mIsRunning = false;
    }

signals:
    void signalEventStarted();
    void signalEventCoreStopped();

public slots:
    void onValveChangedIsRunning(bool value)
    {
        if(value == false)
            return;

        mIsRunning = true;

        emit signalEventStarted();
    }

public:
    explicit CoreService(QObject *parent = nullptr):QObject(parent)
    {
    }
    ~CoreService()
    {
        stop();
    }

};

#endif // CORESERVICE_H
