#ifndef FWRITEFIRMWARE_H
#define FWRITEFIRMWARE_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class FWriteFirmware : public QObject
{
    Q_OBJECT

public:
    int         mPercentCpu1Kernel  = 0;
    int         mPercentCpu2Kernel  = 0;
    int         mPercentCpu1App     = 0;
    int         mPercentCpu2App     = 0;
    int         mPercentCpu1Verify  = 0;
    int         mPercentCpu2Verify  = 0;

    int     getPercentCpu1Kernel (){ return mPercentCpu1Kernel ;}
    int     getPercentCpu2Kernel (){ return mPercentCpu2Kernel ;}
    int     getPercentCpu1App    (){ return mPercentCpu1App    ;}
    int     getPercentCpu2App    (){ return mPercentCpu2App    ;}
    int     getPercentCpu1Verify (){ return mPercentCpu1Verify ;}
    int     getPercentCpu2Verify (){ return mPercentCpu2Verify ;}

    void    setPercentCpu1Kernel (int     value){ if(mPercentCpu1Kernel  == value) return; mPercentCpu1Kernel  = value; emit signalEventChangedPercentCpu1Kernel (value); }
    void    setPercentCpu2Kernel (int     value){ if(mPercentCpu2Kernel  == value) return; mPercentCpu2Kernel  = value; emit signalEventChangedPercentCpu2Kernel (value); }
    void    setPercentCpu1App    (int     value){ if(mPercentCpu1App     == value) return; mPercentCpu1App     = value; emit signalEventChangedPercentCpu1App    (value); }
    void    setPercentCpu2App    (int     value){ if(mPercentCpu2App     == value) return; mPercentCpu2App     = value; emit signalEventChangedPercentCpu2App    (value); }
    void    setPercentCpu1Verify (int     value){ if(mPercentCpu1Verify  == value) return; mPercentCpu1Verify  = value; emit signalEventChangedPercentCpu1Verify (value); }
    void    setPercentCpu2Verify (int     value){ if(mPercentCpu2Verify  == value) return; mPercentCpu2Verify  = value; emit signalEventChangedPercentCpu2Verify (value); }

signals:
    void signalEventChangedPercentCpu1Kernel (int     value);
    void signalEventChangedPercentCpu2Kernel (int     value);
    void signalEventChangedPercentCpu1App    (int     value);
    void signalEventChangedPercentCpu2App    (int     value);
    void signalEventChangedPercentCpu1Verify (int     value);
    void signalEventChangedPercentCpu2Verify (int     value);

    void signalEventCompleted(bool bErr, QString errMsg);

public:
    explicit FWriteFirmware(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_KERNEL;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_KERNEL;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_APP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_APP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_VERIFY;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_VERIFY;
        ENABLE_SLOT_VALVE_RESULT_READY_DFU;
        ENABLE_SLOT_VALVE_RESULT_DFU;

        onValveChangedDFUPctCpu1Kernel();
        onValveChangedDFUPctCpu2Kernel();
        onValveChangedDFUPctCpu1App();
        onValveChangedDFUPctCpu2App();
        onValveChangedDFUPctCpu1Verify();
        onValveChangedDFUPctCpu2Verify();
    }
    ~FWriteFirmware()
    {
    }

    void ready()
    {
        pValveSP->readyFirmwareUpdate();
    }

    void run(QString comport, QString cpu1KernelFile, QString cpu1AppFile, QString cpu2KernelFile, QString cpu2AppFile)
    {
        qDebug() << "[" << Q_FUNC_INFO << "] RetryConnect = "  << pValveSP->getRetryConnect() << ", IsConnected = " << pValveSP->getIsConnected();
        pValveSP->firmwareUpdate(comport, QSerialPort::Baud38400, QSerialPort::Data8, QSerialPort::OneStop, QSerialPort::NoParity, cpu1KernelFile, cpu2KernelFile, cpu1AppFile, cpu2AppFile);
    }

public slots:
    void onValveChangedDFUPctCpu1Kernel(){setPercentCpu1Kernel(pValveSP->getDFUPctCpu1Kernel());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu1Kernel;}
    void onValveChangedDFUPctCpu2Kernel(){setPercentCpu2Kernel(pValveSP->getDFUPctCpu2Kernel());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu2Kernel;}
    void onValveChangedDFUPctCpu1App   (){setPercentCpu1App   (pValveSP->getDFUPctCpu1App   ());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu1App   ;}
    void onValveChangedDFUPctCpu2App   (){setPercentCpu2App   (pValveSP->getDFUPctCpu2App   ());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu2App   ;}
    void onValveChangedDFUPctCpu1Verify(){setPercentCpu1Verify(pValveSP->getDFUPctCpu1Verify());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu1Verify;}
    void onValveChangedDFUPctCpu2Verify(){setPercentCpu2Verify(pValveSP->getDFUPctCpu2Verify());qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << mPercentCpu2Verify;}

    void onValveResultReadyDFU(bool result)
    {
        Q_UNUSED(result)
    }

    void onValveResultDFU(bool result, QString errMsg)
    {
        emit signalEventCompleted(!result, errMsg);
    }
};

#endif // FWRITEFIRMWARE_H
