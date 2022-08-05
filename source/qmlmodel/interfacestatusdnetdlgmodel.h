#ifndef INTERFACESTATUSDNETDLGMODEL_H
#define INTERFACESTATUSDNETDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class InterfaceStatusDNetDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode               READ getAccessMode        NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool     mIsRS232Test              READ getIsRS232Test       NOTIFY signalEventChangedIsRS232Test      )
    Q_PROPERTY(QString  mMacAddr                  READ getMacAddr           NOTIFY signalEventChangedMacAddr          )
    Q_PROPERTY(QString  mBaudrate                 READ getBaudrate          NOTIFY signalEventChangedBaudrate         )
    Q_PROPERTY(QString  mFirmwareID               READ getFirmwareID        NOTIFY signalEventChangedFirmwareID       )
    Q_PROPERTY(QString  mSerialNum                READ getSerialNum         NOTIFY signalEventChangedSerialNum        )
    Q_PROPERTY(int      mDIActivation             READ getDIActivation      NOTIFY signalEventChangedDIActivation     )
    Q_PROPERTY(int      mDIFunction               READ getDIFunction        NOTIFY signalEventChangedDIFunction       )
    Q_PROPERTY(int      mDIPolarity               READ getDIPolarity        NOTIFY signalEventChangedDIPolarity       )
    Q_PROPERTY(int      mDOActivation             READ getDOActivation      NOTIFY signalEventChangedDOActivation     )
    Q_PROPERTY(int      mDOFunction               READ getDOFunction        NOTIFY signalEventChangedDOFunction       )
    Q_PROPERTY(int      mDOPolarity               READ getDOPolarity        NOTIFY signalEventChangedDOPolarity       )
    Q_PROPERTY(int      mStatusDI                 READ getStatusDI          NOTIFY signalEventChangedStatusDI         )
    Q_PROPERTY(int      mStatusDO                 READ getStatusDO          NOTIFY signalEventChangedStatusDO         )
    Q_PROPERTY(bool     mErrMacAddr               READ getErrMacAddr        NOTIFY signalEventChangedErrMacAddr       )
    Q_PROPERTY(bool     mErrBaudrate              READ getErrBaudrate       NOTIFY signalEventChangedErrBaudrate      )
    Q_PROPERTY(bool     mErrFirmwareID            READ getErrFirmwareID     NOTIFY signalEventChangedErrFirmwareID    )
    Q_PROPERTY(bool     mErrSerialNum             READ getErrSerialNum      NOTIFY signalEventChangedErrSerialNum     )
    Q_PROPERTY(bool     mErrDIActivation          READ getErrDIActivation   NOTIFY signalEventChangedErrDIActivation  )
    Q_PROPERTY(bool     mErrDIFunction            READ getErrDIFunction     NOTIFY signalEventChangedErrDIFunction    )
    Q_PROPERTY(bool     mErrDIPolarity            READ getErrDIPolarity     NOTIFY signalEventChangedErrDIPolarity    )
    Q_PROPERTY(bool     mErrDOActivation          READ getErrDOActivation   NOTIFY signalEventChangedErrDOActivation  )
    Q_PROPERTY(bool     mErrDOFunction            READ getErrDOFunction     NOTIFY signalEventChangedErrDOFunction    )
    Q_PROPERTY(bool     mErrDOPolarity            READ getErrDOPolarity     NOTIFY signalEventChangedErrDOPolarity    )
    Q_PROPERTY(bool     mErrStatusDI              READ getErrStatusDI       NOTIFY signalEventChangedErrStatusDI      )
    Q_PROPERTY(bool     mErrStatusDO              READ getErrStatusDO       NOTIFY signalEventChangedErrStatusDO      )
    Q_PROPERTY(bool     mIsEdit                   READ getIsEdit            NOTIFY signalEventChangedIsEdit           )
    Q_PROPERTY(QString  mStrStatus                READ getStrStatus         NOTIFY signalEventChangedStrStatus        )
    Q_PROPERTY(QString  mErrMsg                   READ getErrMsg            NOTIFY signalEventChangedErrMsg           )
    Q_PROPERTY(int      mProgress                 READ getProgress          NOTIFY signalEventChangedProgress         )

public:
    int      mAccessMode      = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test     = false;
    QString  mMacAddr         = "unkonw";
    QString  mBaudrate        = "unknow";
    QString  mFirmwareID      = "unknow";
    QString  mSerialNum       = "unknow";
    int      mDIActivation    = 0;
    int      mDIFunction      = 0;
    int      mDIPolarity      = 0;
    int      mDOActivation    = 0;
    int      mDOFunction      = 0;
    int      mDOPolarity      = 0;
    int      mStatusDI        = 0;
    int      mStatusDO        = 0;
    bool     mErrMacAddr      = false;
    bool     mErrBaudrate     = false;
    bool     mErrFirmwareID   = false;
    bool     mErrSerialNum    = false;
    bool     mErrDIActivation = false;
    bool     mErrDIFunction   = false;
    bool     mErrDIPolarity   = false;
    bool     mErrDOActivation = false;
    bool     mErrDOFunction   = false;
    bool     mErrDOPolarity   = false;
    bool     mErrStatusDI     = false;
    bool     mErrStatusDO     = false;
    bool    mIsEdit           = false;
    QString mStrStatus        = "Loading";
    QString mErrMsg           = "";
    int     mProgress         = 0 ;

    int     getAccessMode     (){ return mAccessMode     ;}
    bool    getIsRS232Test    (){ return mIsRS232Test    ;}
    QString getMacAddr        (){ return mMacAddr        ;}
    QString getBaudrate       (){ return mBaudrate       ;}
    QString getFirmwareID     (){ return mFirmwareID     ;}
    QString getSerialNum      (){ return mSerialNum      ;}
    int     getDIActivation   (){ return mDIActivation   ;}
    int     getDIFunction     (){ return mDIFunction     ;}
    int     getDIPolarity     (){ return mDIPolarity     ;}
    int     getDOActivation   (){ return mDOActivation   ;}
    int     getDOFunction     (){ return mDOFunction     ;}
    int     getDOPolarity     (){ return mDOPolarity     ;}
    int     getStatusDI       (){ return mStatusDI       ;}
    int     getStatusDO       (){ return mStatusDO       ;}
    bool    getErrMacAddr     (){ return mErrMacAddr     ;}
    bool    getErrBaudrate    (){ return mErrBaudrate    ;}
    bool    getErrFirmwareID  (){ return mErrFirmwareID  ;}
    bool    getErrSerialNum   (){ return mErrSerialNum   ;}
    bool    getErrDIActivation(){ return mErrDIActivation;}
    bool    getErrDIFunction  (){ return mErrDIFunction  ;}
    bool    getErrDIPolarity  (){ return mErrDIPolarity  ;}
    bool    getErrDOActivation(){ return mErrDOActivation;}
    bool    getErrDOFunction  (){ return mErrDOFunction  ;}
    bool    getErrDOPolarity  (){ return mErrDOPolarity  ;}
    bool    getErrStatusDI    (){ return mErrStatusDI    ;}
    bool    getErrStatusDO    (){ return mErrStatusDO    ;}
    bool    getIsEdit         (){ return mIsEdit         ;}
    QString getStrStatus      (){ return mStrStatus      ;}
    QString getErrMsg         (){ return mErrMsg         ;}
    int     getProgress       (){ return mProgress       ;}

    void    setAccessMode     (int     value){ if(mAccessMode      == value) return; mAccessMode      = value; emit signalEventChangedAccessMode     (value);}
    void    setIsRS232Test    (bool    value){ if(mIsRS232Test     == value)return; mIsRS232Test      = value; emit signalEventChangedIsRS232Test    (value);}
    void    setMacAddr        (QString value){ if(mMacAddr         == value) return; mMacAddr         = value; emit signalEventChangedMacAddr        (value);}
    void    setBaudrate       (QString value){ if(mBaudrate        == value) return; mBaudrate        = value; emit signalEventChangedBaudrate       (value);}
    void    setFirmwareID     (QString value){ if(mFirmwareID      == value) return; mFirmwareID      = value; emit signalEventChangedFirmwareID     (value);}
    void    setSerialNum      (QString value){ if(mSerialNum       == value) return; mSerialNum       = value; emit signalEventChangedSerialNum      (value);}
    void    setDIActivation   (int     value){ if(mDIActivation    == value) return; mDIActivation    = value; emit signalEventChangedDIActivation   (value);}
    void    setDIFunction     (int     value){ if(mDIFunction      == value) return; mDIFunction      = value; emit signalEventChangedDIFunction     (value);}
    void    setDIPolarity     (int     value){ if(mDIPolarity      == value) return; mDIPolarity      = value; emit signalEventChangedDIPolarity     (value);}
    void    setDOActivation   (int     value){ if(mDOActivation    == value) return; mDOActivation    = value; emit signalEventChangedDOActivation   (value);}
    void    setDOFunction     (int     value){ if(mDOFunction      == value) return; mDOFunction      = value; emit signalEventChangedDOFunction     (value);}
    void    setDOPolarity     (int     value){ if(mDOPolarity      == value) return; mDOPolarity      = value; emit signalEventChangedDOPolarity     (value);}
    void    setStatusDI       (int     value){ if(mStatusDI        == value) return; mStatusDI        = value; emit signalEventChangedStatusDI       (value);}
    void    setStatusDO       (int     value){ if(mStatusDO        == value) return; mStatusDO        = value; emit signalEventChangedStatusDO       (value);}
    void    setErrMacAddr     (bool    value){ if(mErrMacAddr      == value) return; mErrMacAddr      = value; emit signalEventChangedErrMacAddr     (value);}
    void    setErrBaudrate    (bool    value){ if(mErrBaudrate     == value) return; mErrBaudrate     = value; emit signalEventChangedErrBaudrate    (value);}
    void    setErrFirmwareID  (bool    value){ if(mErrFirmwareID   == value) return; mErrFirmwareID   = value; emit signalEventChangedErrFirmwareID  (value);}
    void    setErrSerialNum   (bool    value){ if(mErrSerialNum    == value) return; mErrSerialNum    = value; emit signalEventChangedErrSerialNum   (value);}
    void    setErrDIActivation(bool    value){ if(mErrDIActivation == value) return; mErrDIActivation = value; emit signalEventChangedErrDIActivation(value);}
    void    setErrDIFunction  (bool    value){ if(mErrDIFunction   == value) return; mErrDIFunction   = value; emit signalEventChangedErrDIFunction  (value);}
    void    setErrDIPolarity  (bool    value){ if(mErrDIPolarity   == value) return; mErrDIPolarity   = value; emit signalEventChangedErrDIPolarity  (value);}
    void    setErrDOActivation(bool    value){ if(mErrDOActivation == value) return; mErrDOActivation = value; emit signalEventChangedErrDOActivation(value);}
    void    setErrDOFunction  (bool    value){ if(mErrDOFunction   == value) return; mErrDOFunction   = value; emit signalEventChangedErrDOFunction  (value);}
    void    setErrDOPolarity  (bool    value){ if(mErrDOPolarity   == value) return; mErrDOPolarity   = value; emit signalEventChangedErrDOPolarity  (value);}
    void    setErrStatusDI    (bool    value){ if(mErrStatusDI     == value) return; mErrStatusDI     = value; emit signalEventChangedErrStatusDI    (value);}
    void    setErrStatusDO    (bool    value){ if(mErrStatusDO     == value) return; mErrStatusDO     = value; emit signalEventChangedErrStatusDO    (value);}
    void    setIsEdit         (bool    value){ if(mIsEdit          == value) return; mIsEdit          = value; emit signalEventChangedIsEdit         (value);}
    void    setStrStatus      (QString value){ if(mStrStatus       == value) return; mStrStatus       = value; emit signalEventChangedStrStatus      (value);}
    void    setErrMsg         (QString value){ if(mErrMsg          == value) return; mErrMsg          = value; emit signalEventChangedErrMsg         (value);}
    void    setProgress       (int     value){ if(mProgress        == value) return; mProgress        = value; emit signalEventChangedProgress       (value);}

signals:
    void signalEventChangedAccessMode     (int     value);
    void signalEventChangedIsRS232Test    (bool    value);
    void signalEventChangedMacAddr        (QString value);
    void signalEventChangedBaudrate       (QString value);
    void signalEventChangedFirmwareID     (QString value);
    void signalEventChangedSerialNum      (QString value);
    void signalEventChangedDIActivation   (int     value);
    void signalEventChangedDIFunction     (int     value);
    void signalEventChangedDIPolarity     (int     value);
    void signalEventChangedDOActivation   (int     value);
    void signalEventChangedDOFunction     (int     value);
    void signalEventChangedDOPolarity     (int     value);
    void signalEventChangedStatusDI       (int     value);
    void signalEventChangedStatusDO       (int     value);
    void signalEventChangedErrMacAddr     (bool    value);
    void signalEventChangedErrBaudrate    (bool    value);
    void signalEventChangedErrFirmwareID  (bool    value);
    void signalEventChangedErrSerialNum   (bool    value);
    void signalEventChangedErrDIActivation(bool    value);
    void signalEventChangedErrDIFunction  (bool    value);
    void signalEventChangedErrDIPolarity  (bool    value);
    void signalEventChangedErrDOActivation(bool    value);
    void signalEventChangedErrDOFunction  (bool    value);
    void signalEventChangedErrDOPolarity  (bool    value);
    void signalEventChangedErrStatusDI    (bool    value);
    void signalEventChangedErrStatusDO    (bool    value);
    void signalEventChangedIsEdit         (bool    value);
    void signalEventChangedStrStatus      (QString value);
    void signalEventChangedErrMsg         (QString value);
    void signalEventChangedProgress       (int     value);

public:
    explicit InterfaceStatusDNetDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_MAC;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_BAUDRATE;
        ENABLE_SLOT_VALVE_READED_IF_DNET_FIRMWARE_ID;
        ENABLE_SLOT_VALVE_READED_IF_DNET_SERIAL_NUM;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DI;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DO;
        ENABLE_SLOT_VALVE_READED_IF_STATUS_DNET;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CFG_MAC);
    }
    ~InterfaceStatusDNetDlgModel()
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
    void onValveReadedInterfaceCfgDNetMAC(ValveResponseInterfaceConfigDNetMacDto dto)
    {
        if(mState != eState::STATE_READ_CFG_MAC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setMacAddr(QString("%1(0x%2)").arg(dto.mMacAddr).arg(dto.mMacAddr,2,16,QChar('0')));

        setState((eState)(mState + 1));

        return;
    }
    void onValveReadedInterfaceCfgDNetBaudrate(ValveResponseInterfaceConfigDNetBaudrateDto dto)
    {
        if(mState != eState::STATE_READ_CFG_BAUDRATE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setBaudrate(QString("%1kbaud").arg(dto.mBaudrate));

        setState((eState)(mState + 1));

        return;
    }

//    void onValveReadedInterfaceDNetFirmwareID(ValveResponseInterfaceDNetFirmwareIDDto dto)
//    {
//        if(mState != eState::STATE_READ_CFG_FIRMWARE_ID || dto.mReqDto.mpRef != this)
//            return;

//        setErrMsg(dto.mErrMsg);

//        if(!dto.mIsSucc)
//        {
//            setState(mState);
//            return;
//        }

//        setFirmwareID(dto.mFirmwareID);

//        setState((eState)(mState + 1));

//        return;
//    }

//    void onValveReadedInterfaceDNetSerialNum(ValveResponseInterfaceDNetSerialNumDto dto)
//    {
//        if(mState != eState::STATE_READ_CFG_SERIAL_NUM || dto.mReqDto.mpRef != this)
//            return;

//        setErrMsg(dto.mErrMsg);

//        if(!dto.mIsSucc)
//        {
//            setState(mState);
//            return;
//        }

//        setSerialNum(dto.mSerialNum);

//        setState((eState)(mState + 1));

//        return;
//    }

    void onValveReadedInterfaceCfgDNetDi(ValveResponseInterfaceConfigDNetDiDto dto)
    {
        if(mState != eState::STATE_READ_CFG_DI || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

//        qDebug() << "[khko_debug][" << Q_FUNC_INFO  << dto.toString();
        setDIActivation(dto.mDIActivation);
        setDIFunction  (dto.mDIFunction  );
        setDIPolarity  (dto.mDIPolarity  );

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceCfgDNetDo(ValveResponseInterfaceConfigDNetDoDto dto)
    {
        if(mState != eState::STATE_READ_CFG_DO || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setDOActivation(dto.mDOActivation);
        setDOFunction  (dto.mDOFunction  );
        setDOPolarity  (dto.mDOPolarity  );

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceStatusDNet(ValveResponseInterfaceStatusDNetDto dto)
    {
        if(mState != eState::STATE_READ_STATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setStatusDI(dto.mStatusDI);
        setStatusDO(dto.mStatusDO);

        setState((eState)(mState + 1));

        return;
    }


private:
    enum eState{
        STATE_READ_CFG_MAC         =  0,
        STATE_READ_CFG_BAUDRATE    = STATE_READ_CFG_MAC         + 1,
        //STATE_READ_CFG_FIRMWARE_ID = STATE_READ_CFG_BAUDRATE    + 1,
        //STATE_READ_CFG_SERIAL_NUM  = STATE_READ_CFG_FIRMWARE_ID + 1,
        STATE_READ_CFG_DI          = STATE_READ_CFG_BAUDRATE    + 1,
        STATE_READ_CFG_DO          = STATE_READ_CFG_DI          + 1,
        STATE_READ_STATUS          = STATE_READ_CFG_DO          + 1,
        STATE_OVER                 = STATE_READ_STATUS          + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CFG_MAC;
    qint64 mLastScanMSec  = 0;
    bool   mIsFirstRead   = false;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        qint64 currMSec;

        if(state == eState::STATE_OVER)
        {
            state = eState::STATE_READ_CFG_DI;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_STATUS));
        }
        else if(state == eState::STATE_READ_CFG_DI)
        {
            currMSec = QDateTime::currentMSecsSinceEpoch();

            setStrStatus(QString("scan-rate %1 ms").arg(currMSec - mLastScanMSec));
            setProgress(100);
            mLastScanMSec = currMSec;
        }

        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_CFG_MAC:
            pValveSP->readInterfaceConfigDNetMac(this);
            break;

        case (int)eState::STATE_READ_CFG_BAUDRATE:
            pValveSP->readInterfaceConfigDNetBaudrate(this);
            break;

//        case (int)eState::STATE_READ_CFG_FIRMWARE_ID:
//            pValveSP->readInterfaceDNetFirmwareID(this);
//            break;

//        case (int)eState::STATE_READ_CFG_SERIAL_NUM:
//            pValveSP->readInterfaceDNetSerialNum(this);
//            break;

        case (int)eState::STATE_READ_CFG_DI:
            pValveSP->readInterfaceConfigDNetDi(this);
            break;

        case (int)eState::STATE_READ_CFG_DO:
            pValveSP->readInterfaceConfigDNetDo(this);
            break;

        case (int)eState::STATE_READ_STATUS:
           pValveSP->readInterfaceStatusDNet(this);
            break;
        }
    }
};

#endif // INTERFACESTATUSDNETDLGMODEL_H
