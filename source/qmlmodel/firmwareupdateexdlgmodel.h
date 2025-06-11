#ifndef FIRMWAREUPDATEEXDLGMODEL_H
#define FIRMWAREUPDATEEXDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QFile>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/fuactivekey.h"
#include "source/qmlmodel/function/fdownloadfirmware.h"

class FirmwareUpdateExDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool    mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test      )
    Q_PROPERTY(QString mServicePortType     READ getServicePortType     NOTIFY signalEventChangedServicePortType  )
    Q_PROPERTY(bool    mIsReboot            READ getIsReboot            NOTIFY signalEventChangedIsReboot         )
    Q_PROPERTY(bool    mIsUpdating          READ getIsUpdating          NOTIFY signalEventChangedIsUpdating       )
    Q_PROPERTY(int     mUpdateStep          READ getUpdateStep          NOTIFY signalEventChangedUpdateStep       )
    Q_PROPERTY(int     mUpdateProgress      READ getUpdateProgress      NOTIFY signalEventChangedUpdateProgress   )
    Q_PROPERTY(bool    mIsVersionProc       READ getIsVersionProc       NOTIFY signalEventChangedIsVersionProc    )
    Q_PROPERTY(bool    mIsErrVersion        READ getIsErrVersion        NOTIFY signalEventChangedIsErrVersion     )
    //Q_PROPERTY(int     mDnPctCpu1Kernel     READ getDnPctCpu1Kernel     NOTIFY signalEventChangedDnPctCpu1Kernel  )
    //Q_PROPERTY(int     mDnPctCpu2Kernel     READ getDnPctCpu2Kernel     NOTIFY signalEventChangedDnPctCpu2Kernel  )
    Q_PROPERTY(int     mDnPctCpu1App        READ getDnPctCpu1App        NOTIFY signalEventChangedDnPctCpu1App     )
    Q_PROPERTY(int     mDnPctCpu2App        READ getDnPctCpu2App        NOTIFY signalEventChangedDnPctCpu2App     )
    Q_PROPERTY(int     mDFUPctCpu1Kernel    READ getDFUPctCpu1Kernel    NOTIFY signalEventChangedDFUPctCpu1Kernel )
    Q_PROPERTY(int     mDFUPctCpu1App       READ getDFUPctCpu1App       NOTIFY signalEventChangedDFUPctCpu1App    )
    Q_PROPERTY(int     mDFUPctCpu1Verify    READ getDFUPctCpu1Verify    NOTIFY signalEventChangedDFUPctCpu1Verify )
    Q_PROPERTY(int     mDFUPctCpu2Kernel    READ getDFUPctCpu2Kernel    NOTIFY signalEventChangedDFUPctCpu2Kernel )
    Q_PROPERTY(int     mDFUPctCpu2App       READ getDFUPctCpu2App       NOTIFY signalEventChangedDFUPctCpu2App    )
    Q_PROPERTY(int     mDFUPctCpu2Verify    READ getDFUPctCpu2Verify    NOTIFY signalEventChangedDFUPctCpu2Verify )
    Q_PROPERTY(int     mFUCount             READ getFUCount             NOTIFY signalEventChangedFUCount          )
    Q_PROPERTY(QString mFUUnLockCode        READ getFUUnLockCode        NOTIFY signalEventChangedFUUnLockCode     )

public:
    int     mAccessMode         = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test        = false;
    QString mServicePortType    = "";
    bool    mIsReboot           = false;
    bool    mIsUpdating         = false;
    int     mUpdateStep         = 0;
    int     mUpdateProgress     = 0;
    bool    mIsVersionProc      = false;
    bool    mIsErrVersion       = false;
    //int     mDnPctCpu1Kernel    = 0;
    //int     mDnPctCpu2Kernel    = 0;
    int     mDnPctCpu1App       = 0;
    int     mDnPctCpu2App       = 0;
    int     mDFUPctCpu1Kernel   = 0;
    int     mDFUPctCpu1App      = 0;
    int     mDFUPctCpu1Verify   = 0;
    int     mDFUPctCpu2Kernel   = 0;
    int     mDFUPctCpu2App      = 0;
    int     mDFUPctCpu2Verify   = 0;
    int     mFUCount            = 0;
    QString mFUUnLockCode       = "";

    int     getAccessMode      (){ return mAccessMode      ;}
    bool    getIsRS232Test     (){ return mIsRS232Test     ;}
    QString getServicePortType (){ return mServicePortType ;}
    bool    getIsReboot        (){ return mIsReboot        ;}
    bool    getIsUpdating      (){ return mIsUpdating      ;}
    int     getUpdateStep      (){ return mUpdateStep      ;}
    int     getUpdateProgress  (){ return mUpdateProgress  ;}
    bool    getIsVersionProc   (){ return mIsVersionProc   ;}
    bool    getIsErrVersion    (){ return mIsErrVersion    ;}
    //int     getDnPctCpu1Kernel (){ return mDnPctCpu1Kernel ;}
    //int     getDnPctCpu2Kernel (){ return mDnPctCpu2Kernel ;}
    int     getDnPctCpu1App    (){ return mDnPctCpu1App    ;}
    int     getDnPctCpu2App    (){ return mDnPctCpu2App    ;}
    int     getDFUPctCpu1Kernel(){ return mDFUPctCpu1Kernel;}
    int     getDFUPctCpu1App   (){ return mDFUPctCpu1App   ;}
    int     getDFUPctCpu1Verify(){ return mDFUPctCpu1Verify;}
    int     getDFUPctCpu2Kernel(){ return mDFUPctCpu2Kernel;}
    int     getDFUPctCpu2App   (){ return mDFUPctCpu2App   ;}
    int     getDFUPctCpu2Verify(){ return mDFUPctCpu2Verify;}
    int     getFUCount         (){ return mFUCount         ;}
    QString getFUUnLockCode    (){ return mFUUnLockCode    ;}

    void    setAccessMode      (int     value){ if(mAccessMode       == value) return; mAccessMode       = value; emit signalEventChangedAccessMode      (value); }
    void    setIsRS232Test     (bool    value){ if(mIsRS232Test      == value) return; mIsRS232Test      = value; emit signalEventChangedIsRS232Test     (value); }
    void    setServicePortType (QString value){ if(mServicePortType  == value) return; mServicePortType  = value; emit signalEventChangedServicePortType (value); }
    void    setIsReboot        (bool    value){ if(mIsReboot         == value) return; mIsReboot         = value; emit signalEventChangedIsReboot        (value); }
    void    setIsUpdating      (bool    value){ if(mIsUpdating       == value) return; mIsUpdating       = value; emit signalEventChangedIsUpdating      (value); }
    void    setUpdateStep      (int     value){ if(mUpdateStep       == value) return; mUpdateStep       = value; setUpdateProgress(0) ;emit signalEventChangedUpdateStep    (value); }
    void    setUpdateProgress  (int     value){ if(mUpdateProgress   == value) return; mUpdateProgress   = value; emit signalEventChangedUpdateProgress  (value); }
    void    setIsVersionProc   (bool    value){ if(mIsVersionProc    == value) return; mIsVersionProc    = value; emit signalEventChangedIsVersionProc   (value); }
    void    setIsErrVersion    (bool    value){ if(mIsErrVersion     == value) return; mIsErrVersion     = value; emit signalEventChangedIsErrVersion    (value); }
    //void    setDnPctCpu1Kernel (int  value){ if(mDnPctCpu1Kernel  == value) return; mDnPctCpu1Kernel  = value; emit signalEventChangedDnPctCpu1Kernel (value); }
    //void    setDnPctCpu2Kernel (int  value){ if(mDnPctCpu2Kernel  == value) return; mDnPctCpu2Kernel  = value; emit signalEventChangedDnPctCpu2Kernel (value); }
    void    setDnPctCpu1App    (int     value){ if(mDnPctCpu1App     == value) return; mDnPctCpu1App     = value; emit signalEventChangedDnPctCpu1App    (value); }
    void    setDnPctCpu2App    (int     value){ if(mDnPctCpu2App     == value) return; mDnPctCpu2App     = value; emit signalEventChangedDnPctCpu2App    (value); }
    void    setDFUPctCpu1Kernel(int     value){ if(mDFUPctCpu1Kernel == value) return; mDFUPctCpu1Kernel = value; emit signalEventChangedDFUPctCpu1Kernel(value); }
    void    setDFUPctCpu1App   (int     value){ if(mDFUPctCpu1App    == value) return; mDFUPctCpu1App    = value; emit signalEventChangedDFUPctCpu1App   (value); }
    void    setDFUPctCpu1Verify(int     value){ if(mDFUPctCpu1Verify == value) return; mDFUPctCpu1Verify = value; emit signalEventChangedDFUPctCpu1Verify(value); }
    void    setDFUPctCpu2Kernel(int     value){ if(mDFUPctCpu2Kernel == value) return; mDFUPctCpu2Kernel = value; emit signalEventChangedDFUPctCpu2Kernel(value); }
    void    setDFUPctCpu2App   (int     value){ if(mDFUPctCpu2App    == value) return; mDFUPctCpu2App    = value; emit signalEventChangedDFUPctCpu2App   (value); }
    void    setDFUPctCpu2Verify(int     value){ if(mDFUPctCpu2Verify == value) return; mDFUPctCpu2Verify = value; emit signalEventChangedDFUPctCpu2Verify(value); }
    void    setFUCount         (int     value){ if(mFUCount          == value) return; mFUCount          = value; emit signalEventChangedFUCount         (value); }
    void    setFUUnLockCode    (QString value){ if(mFUUnLockCode     == value) return; mFUUnLockCode     = value; emit signalEventChangedFUUnLockCode    (value); }

signals:
    void signalEventChangedAccessMode      (int  value);
    void signalEventChangedIsRS232Test     (bool value);
    void signalEventChangedServicePortType (QString value);
    void signalEventChangedIsReboot        (bool value);
    void signalEventChangedIsUpdating      (bool value);
    void signalEventChangedUpdateStep      (int  value);
    void signalEventChangedUpdateProgress  (int  value);
    void signalEventChangedIsVersionProc   (bool value);
    void signalEventChangedIsErrVersion    (bool value);
    //void signalEventChangedDnPctCpu1Kernel (int value);
    //void signalEventChangedDnPctCpu2Kernel (int value);
    void signalEventChangedDnPctCpu1App    (int value);
    void signalEventChangedDnPctCpu2App    (int value);
    void signalEventChangedDFUPctCpu1Kernel(int value);
    void signalEventChangedDFUPctCpu1App   (int value);
    void signalEventChangedDFUPctCpu1Verify(int value);
    void signalEventChangedDFUPctCpu2Kernel(int value);
    void signalEventChangedDFUPctCpu2App   (int value);
    void signalEventChangedDFUPctCpu2Verify(int value);
    void signalEventChangedFUCount         (int value);
    void signalEventChangedFUUnLockCode    (QString value);

    void signalEventResultSearchVer();
    void signalEventResultUpdate(bool bErr, QString errMsg);
    void signalEventCompletedFactoryReset();
    void signalOverFUCount();

public:
    explicit FirmwareUpdateExDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        qDebug() << "[" << Q_FUNC_INFO << "[FirmwareUpdateExDlgModel]" ;

        FUActiveKey fk;
        setFUUnLockCode(fk.GetKey());


        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_LOAD_PROGRESS;
        ENABLE_SLOT_VALVE_SEARCHED_DEVICE;
        ENABLE_SLOT_VALVE_RESULT_READY_DFU;
        ENABLE_SLOT_VALVE_CHANGED_DFU_STEP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_KERNEL;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_KERNEL;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_APP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_APP;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_VERIFY;
        ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_VERIFY;
        ENABLE_SLOT_VALVE_RESULT_DFU;

        connect(&mfDownloadFirmware, SIGNAL(signalEventReadedVer(QStringList)), this, SLOT(onReadedVer(QStringList)));
        //connect(&mfDownloadFirmware, SIGNAL(signalEventChangedFtpProgressCpu1Kernel(qint64)        ), this, SLOT(onChangedDnProgressCpu1Kernel(qint64        )));
        //connect(&mfDownloadFirmware, SIGNAL(signalEventChangedFtpProgressCpu2Kernel(qint64)        ), this, SLOT(onChangedDnProgressCpu2Kernel(qint64        )));
        connect(&mfDownloadFirmware, SIGNAL(signalEventChangedFtpProgressCpu1App   (qint64)        ), this, SLOT(onChangedDnProgressCpu1App   (qint64        )));
        connect(&mfDownloadFirmware, SIGNAL(signalEventChangedFtpProgressCpu2App   (qint64)        ), this, SLOT(onChangedDnProgressCpu2App   (qint64        )));
        connect(&mfDownloadFirmware, SIGNAL(signalEventChangedDownloadStep         (int)           ), this, SLOT(onChangedDownloadStep        (int           )));
        connect(&mfDownloadFirmware, SIGNAL(signalEventCompleted                   (bool , QString)), this, SLOT(onResultDownload             (bool , QString)));

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedDFUStep();
        onValveChangedDFUPctCpu1Kernel();
        onValveChangedDFUPctCpu2Kernel();
        onValveChangedDFUPctCpu1App();
        onValveChangedDFUPctCpu2App();
        onValveChangedDFUPctCpu1Verify();
        onValveChangedDFUPctCpu2Verify();

        pValveSP->readyFirmwareUpdate();
    }
    ~FirmwareUpdateExDlgModel()
    {
        pValveSP->searchStop();
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

    Q_INVOKABLE void onCommandSetServicePortType(QString value)
    {
        setServicePortType(value);
    }

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
    Q_INVOKABLE void onCommandSearchVersion()
    {
        qDebug() << "[" << Q_FUNC_INFO << "][debug_khko]";
        setIsVersionProc(true);

        mVersionList.clear();
        mfDownloadFirmware.getVerList();
    }

    void onReadedVer(QStringList verList)
    {
        setIsVersionProc(false);

        if(verList.size() < 1)
        {
            setIsErrVersion(true);
            return;
        }

        foreach(QString temp, verList)
        {
            mVersionList.append(temp.trimmed());
        }
        emit signalEventResultSearchVer();
    }

    Q_INVOKABLE int onCommandGetVersionCount()
    {
        return mVersionList.size();
    }

    Q_INVOKABLE QString onCommandGetVersionName(int idx)
    {
        if(idx < mVersionList.size())
            return mVersionList[idx];

        return "";
    }

    Q_INVOKABLE void onCommandUpdateFromInternalFile(QString comport)
    {
        qDebug() << "[" << Q_FUNC_INFO << "] comport = " << comport;

        QString appPath = QApplication::applicationDirPath();
        QString fLicense = QString("%1/qdatetimelim.dll").arg(appPath);
        QString fcpu01 = QString("%1/qfcpua.dll").arg(appPath);
        QString fcpu02 = QString("%1/qfcpub.dll").arg(appPath);
        int timeLimit;

        pLSettingSP->setFUCount(pLSettingSP->mFUCount + 1);

        if(pLSettingSP->mFUCount > 500)
        {
            qDebug() << "[update start 02]";
            emit signalOverFUCount();
            return;
        }

        if(QFile::exists(fLicense) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]invalid(1) file.";
            emit signalEventResultUpdate(true, "invalid(1) file.");
            return;
        }

        QFile file;
        file.setFileName(fLicense);
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]invalid(2) file.";
            emit signalEventResultUpdate(true, "invalid(2) file.");
            return;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");
        timeLimit = out.readAll().replace(".","").toInt();
        file.close();

        QDateTime now = QDateTime::currentDateTime();

        if(now.date().year() * 10000 + now.date().month() * 100 + now.date().day() > timeLimit)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]invalid(3) file.";
            emit signalEventResultUpdate(true, "invalid(3) file.");
            return;
        }

        if(QFile::exists(fcpu01) == false || QFile::exists(fcpu02) == false)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]invalid(4) file.";
            emit signalEventResultUpdate(true, "invalid(4) file.");
            return;
        }

        onCommandUpdateFromLocal(comport, fcpu01, fcpu02);
    }

    Q_INVOKABLE void onCommandUpdateFromNetwork(QString comport, QString verName)
    {
        setUpdateStep(0);
        setIsUpdating(true);
        mSelComPort = comport;

        if(verName == "LATEST" && mVersionList.size() > 0)
            verName = mVersionList.at(0);

        pLSettingSP->setFUCount(pLSettingSP->mFUCount + 1);

        qDebug() << "[" << Q_FUNC_INFO << "] comport = " << comport << ", verName = " << verName;

        if(pLSettingSP->mFUCount > 500)
        {
            qDebug() << "[update start 01]";
            emit signalOverFUCount();
            return;
        }

        mfDownloadFirmware.run(verName);
    }

    //void onChangedDnProgressCpu1Kernel(qint64 value){setUpdateProgress(value); setDnPctCpu1Kernel(value); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << value;}
    //void onChangedDnProgressCpu2Kernel(qint64 value){setUpdateProgress(value); setDnPctCpu2Kernel(value); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << value;}
    void onChangedDnProgressCpu1App   (qint64 value){setUpdateProgress(value); setDnPctCpu1App   (value); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << value;}
    void onChangedDnProgressCpu2App   (qint64 value){setUpdateProgress(value); setDnPctCpu2App   (value); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << value;}

    void onChangedDownloadStep(int value)
    {
        setUpdateStep(value);
    }

    void onResultDownload(bool bErr, QString errMsg)
    {
        setIsUpdating(false);

        if(bErr)
        {
            emit signalEventResultUpdate(bErr, errMsg);
            return;
        }

        onCommandUpdateFromLocal(mSelComPort, mfDownloadFirmware.getCpu01FilePath(), mfDownloadFirmware.getCpu02FilePath());
    }

    Q_INVOKABLE void onCommandUpdateFromLocal(QString comport, QString cpu1AppFile, QString cpu2AppFile)
    {
        qDebug() << "[" << Q_FUNC_INFO << "] comport = " << comport << ", cpu1AppFile = "<< cpu1AppFile << ", cpu2AppFile = " << cpu2AppFile;
        qDebug() << "[" << Q_FUNC_INFO << "] RetryConnect = "  << pValveSP->getRetryConnect() << ", IsConnected = " << pValveSP->getIsConnected();

        setUpdateStep(2);
        setIsUpdating(true);
        mSelComPort = comport;
        pValveSP->firmwareUpdate(mServicePortType, comport, QSerialPort::Baud38400, QSerialPort::Data8, QSerialPort::OneStop, QSerialPort::NoParity,
                                 QString("%1/firmware/kernel_cpu01.txt").arg(QApplication::applicationDirPath()),
                                 QString("%1/firmware/kernel_cpu02.txt").arg(QApplication::applicationDirPath()),
                                 cpu1AppFile,
                                 cpu2AppFile);
    }

    Q_INVOKABLE void onCommandResetFUCount()
    {
        qDebug() << "[update fail]";
        pLSettingSP->setFUCount(0);
    }
    void onValveResultReadyDFU(bool result){if(result){}}

    void onValveChangedDFUStep()
    {
        setUpdateStep(convertUIStep(pValveSP->getDFUStep()));
    }

    void onValveChangedDFUPctCpu1Kernel(){setUpdateProgress(pValveSP->getDFUPctCpu1Kernel()); setDFUPctCpu1Kernel(pValveSP->getDFUPctCpu1Kernel()); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << pValveSP->getDFUPctCpu1Kernel();}
    void onValveChangedDFUPctCpu2Kernel(){setUpdateProgress(pValveSP->getDFUPctCpu2Kernel()); setDFUPctCpu2Kernel(pValveSP->getDFUPctCpu2Kernel()); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << pValveSP->getDFUPctCpu2Kernel();}
    void onValveChangedDFUPctCpu1App   (){setUpdateProgress(pValveSP->getDFUPctCpu1App   ()); setDFUPctCpu1App   (pValveSP->getDFUPctCpu1App   ()); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << pValveSP->getDFUPctCpu1App   ();}
    void onValveChangedDFUPctCpu2App   (){setUpdateProgress(pValveSP->getDFUPctCpu2App   ()); setDFUPctCpu2App   (pValveSP->getDFUPctCpu2App   ()); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << pValveSP->getDFUPctCpu2App   ();}
    void onValveChangedDFUPctCpu1Verify(){setUpdateProgress(pValveSP->getDFUPctCpu1Verify()); setDFUPctCpu1Verify(pValveSP->getDFUPctCpu1Verify()); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << pValveSP->getDFUPctCpu1Verify();}
    void onValveChangedDFUPctCpu2Verify(){setUpdateProgress(pValveSP->getDFUPctCpu2Verify()); setDFUPctCpu2Verify(pValveSP->getDFUPctCpu2Verify()); qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << pValveSP->getDFUPctCpu2Verify();}

    void onValveResultDFU(bool result, QString errMsg)
    {
        setIsUpdating(false);
        emit signalEventResultUpdate(!result, errMsg);

        if(result)
        {
            searchValve();
        }
    }

    void searchValve()
    {
        pValveSP->search();
    }

    void onValveSearchedDevice(QStringList list)
    {
        foreach(QString portInfo, list)
        {
            QStringList infoList = portInfo.split(":");
            bool isReady = (infoList[1] == "A" ? true : false);
            QString portName = infoList[2];

            if(isReady && portName == mSelComPort)
            {
                pValveSP->searchStop();
                pValveSP->connectDevice(ValveConnEnumDef::CONNECT_SERIAL, mSelComPort);
            }
        }
    }

    void onValveChangedLoadProgress(int value)
    {
        if(mStartFactorReset)
            emit signalEventCompletedFactoryReset();

        if(value == ValveEnumDef::LOAD_COMPLETED)
            setIsReboot(true);
    }

    Q_INVOKABLE void onCommandFactoryReset()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
        pValveSP->setAccess(ValveEnumDef::ACCESS_LOCAL, this);
        pValveSP->factoryReset(this);
        mStartFactorReset = true;
    }

private:
    bool        mStartFactorReset = false;
    QTimer      mTimer;
    QString     mSelComPort    ="";
    QStringList mComPortList   ;
    QStringList mVersionList   ;
    FDownloadFirmware mfDownloadFirmware;

    int convertUIStep(int dfuStep)
    {
        switch (dfuStep) {
        case (int)ValveFirmwareUpgradeDef::SET_BOOTMODE   : return 2 ;
        case (int)ValveFirmwareUpgradeDef::CONNECT_SERIAL : return 2 ;
        case (int)ValveFirmwareUpgradeDef::CPU1_DN_KERNEL : return 3 ;
        case (int)ValveFirmwareUpgradeDef::CPU1_ERASE     : return 4 ;
        case (int)ValveFirmwareUpgradeDef::CPU1_DN_APP    : return 5 ;
        case (int)ValveFirmwareUpgradeDef::CPU1_VERIFY    : return 6 ;
        case (int)ValveFirmwareUpgradeDef::CPU1_RESET     : return 7 ;
        case (int)ValveFirmwareUpgradeDef::CPU2_DN_KERNEL : return 8;
        case (int)ValveFirmwareUpgradeDef::CPU2_ERASE     : return 9;
        case (int)ValveFirmwareUpgradeDef::CPU2_DN_APP    : return 10;
        case (int)ValveFirmwareUpgradeDef::CPU2_VERIFY    : return 11;
        case (int)ValveFirmwareUpgradeDef::CPU2_RESET     : return 12;
        case (int)ValveFirmwareUpgradeDef::COMPLETE       : return 12;
        }
        return 0;
    }
    void startTimer()
    {
        mTimer.stop();
        mTimer.start(5000);
    }
};
#endif // FIRMWAREUPDATEEXDLGMODEL_H
