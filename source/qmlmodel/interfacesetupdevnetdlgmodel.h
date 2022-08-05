#ifndef INTERFACESETUPDEVNETDLGMODEL_H
#define INTERFACESETUPDEVNETDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class InterfaceSetupDevNetDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool     mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test            )

    Q_PROPERTY(QString  mMacAddr             READ getMacAddr             NOTIFY signalEventChangedMacAddr          )
    Q_PROPERTY(int      mBaudrate            READ getBaudrate            NOTIFY signalEventChangedBaudrate         )
    Q_PROPERTY(int      mDIActivation        READ getDIActivation        NOTIFY signalEventChangedDIActivation     )
    Q_PROPERTY(int      mDIFunction          READ getDIFunction          NOTIFY signalEventChangedDIFunction       )
    Q_PROPERTY(int      mDIPolarity          READ getDIPolarity          NOTIFY signalEventChangedDIPolarity       )
    Q_PROPERTY(int      mDOActivation        READ getDOActivation        NOTIFY signalEventChangedDOActivation     )
    Q_PROPERTY(int      mDOFunction          READ getDOFunction          NOTIFY signalEventChangedDOFunction       )
    Q_PROPERTY(int      mDOPolarity          READ getDOPolarity          NOTIFY signalEventChangedDOPolarity       )

    Q_PROPERTY(bool     mErrDIActivation     READ getErrDIActivation     NOTIFY signalEventChangedErrDIActivation  )
    Q_PROPERTY(bool     mErrDIFunction       READ getErrDIFunction       NOTIFY signalEventChangedErrDIFunction    )
    Q_PROPERTY(bool     mErrDIPolarity       READ getErrDIPolarity       NOTIFY signalEventChangedErrDIPolarity    )
    Q_PROPERTY(bool     mErrDOActivation     READ getErrDOActivation     NOTIFY signalEventChangedErrDOActivation  )
    Q_PROPERTY(bool     mErrDOFunction       READ getErrDOFunction       NOTIFY signalEventChangedErrDOFunction    )
    Q_PROPERTY(bool     mErrDOPolarity       READ getErrDOPolarity       NOTIFY signalEventChangedErrDOPolarity    )
    //Q_PROPERTY(bool     mErrDevID            READ getErrDevID            NOTIFY signalEventChangedErrDevID         )

    Q_PROPERTY(bool     mIsEdit              READ getIsEdit              NOTIFY signalEventChangedIsEdit           )
    Q_PROPERTY(QString  mStrStatus           READ getStrStatus           NOTIFY signalEventChangedStrStatus        )
    Q_PROPERTY(QString  mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg           )
    Q_PROPERTY(QString  mErrMsg2             READ getErrMsg2             NOTIFY signalEventChangedErrMsg2          )
    Q_PROPERTY(int      mProgress            READ getProgress            NOTIFY signalEventChangedProgress         )

public:
    int     mAccessMode    = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test   = false;

    QString  mMacAddr      = "0x00(unknow)";
    int      mBaudrate     = 0;
    int      mDIActivation = 0;
    int      mDIFunction   = 0;
    int      mDIPolarity   = 0;
    int      mDOActivation = 0;
    int      mDOFunction   = 0;
    int      mDOPolarity   = 0;

    bool     mErrDIActivation = false;
    bool     mErrDIFunction   = false;
    bool     mErrDIPolarity   = false;
    bool     mErrDOActivation = false;
    bool     mErrDOFunction   = false;
    bool     mErrDOPolarity   = false;

    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}

    QString getMacAddr                (){ return mMacAddr                ;}
    int     getBaudrate               (){ return mBaudrate               ;}
    int     getDIActivation           (){ return mDIActivation           ;}
    int     getDIFunction             (){ return mDIFunction             ;}
    int     getDIPolarity             (){ return mDIPolarity             ;}
    int     getDOActivation           (){ return mDOActivation           ;}
    int     getDOFunction             (){ return mDOFunction             ;}
    int     getDOPolarity             (){ return mDOPolarity             ;}

    bool    getErrDIActivation        (){ return mErrDIActivation        ;}
    bool    getErrDIFunction          (){ return mErrDIFunction          ;}
    bool    getErrDIPolarity          (){ return mErrDIPolarity          ;}
    bool    getErrDOActivation        (){ return mErrDOActivation        ;}
    bool    getErrDOFunction          (){ return mErrDOFunction          ;}
    bool    getErrDOPolarity          (){ return mErrDOPolarity          ;}

    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode      == value)return; mAccessMode      = value; emit signalEventChangedAccessMode     (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test     == value)return; mIsRS232Test     = value; emit signalEventChangedIsRS232Test    (value);}

    void    setMacAddr                (QString value){ if(mMacAddr         == value)return; mMacAddr         = value; emit signalEventChangedMacAddr        (value);}
    void    setBaudrate               (int     value){ if(mBaudrate        == value)return; mBaudrate        = value; emit signalEventChangedBaudrate       (value);}
    void    setDIActivation           (int     value){ if(mDIActivation    == value)return; mDIActivation    = value; emit signalEventChangedDIActivation   (value);}
    void    setDIFunction             (int     value){ if(mDIFunction      == value)return; mDIFunction      = value; emit signalEventChangedDIFunction     (value);}
    void    setDIPolarity             (int     value){ if(mDIPolarity      == value)return; mDIPolarity      = value; emit signalEventChangedDIPolarity     (value);}
    void    setDOActivation           (int     value){ if(mDOActivation    == value)return; mDOActivation    = value; emit signalEventChangedDOActivation   (value);}
    void    setDOFunction             (int     value){ if(mDOFunction      == value)return; mDOFunction      = value; emit signalEventChangedDOFunction     (value);}
    void    setDOPolarity             (int     value){ if(mDOPolarity      == value)return; mDOPolarity      = value; emit signalEventChangedDOPolarity     (value);}

    void    setErrDIActivation        (bool    value){ if(mErrDIActivation == value)return; mErrDIActivation = value; emit signalEventChangedErrDIActivation(value);}
    void    setErrDIFunction          (bool    value){ if(mErrDIFunction   == value)return; mErrDIFunction   = value; emit signalEventChangedErrDIFunction  (value);}
    void    setErrDIPolarity          (bool    value){ if(mErrDIPolarity   == value)return; mErrDIPolarity   = value; emit signalEventChangedErrDIPolarity  (value);}
    void    setErrDOActivation        (bool    value){ if(mErrDOActivation == value)return; mErrDOActivation = value; emit signalEventChangedErrDOActivation(value);}
    void    setErrDOFunction          (bool    value){ if(mErrDOFunction   == value)return; mErrDOFunction   = value; emit signalEventChangedErrDOFunction  (value);}
    void    setErrDOPolarity          (bool    value){ if(mErrDOPolarity   == value)return; mErrDOPolarity   = value; emit signalEventChangedErrDOPolarity  (value);}

    void    setIsEdit                 (bool    value){ if(mIsEdit          == value)return; mIsEdit          = value; emit signalEventChangedIsEdit         (value);}
    void    setStrStatus              (QString value){ if(mStrStatus       == value)return; mStrStatus       = value; emit signalEventChangedStrStatus      (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg          == value)return; mErrMsg          = value; emit signalEventChangedErrMsg         (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2         == value)return; mErrMsg2         = value; emit signalEventChangedErrMsg2        (value);}
    void    setProgress               (int     value){ if(mProgress        == value)return; mProgress        = value; emit signalEventChangedProgress       (value);}

signals:
    void signalEventChangedAccessMode     (int     value);
    void signalEventChangedIsRS232Test    (bool    value);

    void signalEventChangedMacAddr        (QString value);
    void signalEventChangedBaudrate       (int     value);
    void signalEventChangedDIActivation   (int     value);
    void signalEventChangedDIFunction     (int     value);
    void signalEventChangedDIPolarity     (int     value);
    void signalEventChangedDOActivation   (int     value);
    void signalEventChangedDOFunction     (int     value);
    void signalEventChangedDOPolarity     (int     value);

    void signalEventChangedErrDIActivation(bool    value);
    void signalEventChangedErrDIFunction  (bool    value);
    void signalEventChangedErrDIPolarity  (bool    value);
    void signalEventChangedErrDOActivation(bool    value);
    void signalEventChangedErrDOFunction  (bool    value);
    void signalEventChangedErrDOPolarity  (bool    value);

    void signalEventChangedIsEdit         (bool    value);
    void signalEventChangedStrStatus      (QString value);
    void signalEventChangedErrMsg         (QString value);
    void signalEventChangedErrMsg2        (QString value);
    void signalEventChangedProgress       (int     value);
    void signalEventCompletedLoad         (             );

public:
    explicit InterfaceSetupDevNetDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_MAC;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_BAUDRATE;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DI;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DO;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_DI;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_DO;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_MAC);
    }
    ~InterfaceSetupDevNetDlgModel()
    {
        pValveSP->reLoad();
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
        if(mState != eState::STATE_READ_MAC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setMacAddr(QString("0x%1").arg(dto.mMacAddr,2,16,QChar('0')));

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetBaudrate(ValveResponseInterfaceConfigDNetBaudrateDto dto)
    {
        if(mState != eState::STATE_READ_BAUDRATE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setBaudrate(transBaudrateToIdx(dto.mBaudrate));

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetDi(ValveResponseInterfaceConfigDNetDiDto dto)
    {
        if(mState != eState::STATE_READ_DI || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrDIActivation(dto.mDIActivation != mWriteDIActivation);
            setErrDIFunction  (dto.mDIFunction   != mWriteDIFunction  );
            setErrDIPolarity  (dto.mDIPolarity   != mWriteDIPolarity  );
        }
        else
        {
            setDIActivation(dto.mDIActivation);
            setDIFunction  (dto.mDIFunction  );
            setDIPolarity  (dto.mDIPolarity  );
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetDo(ValveResponseInterfaceConfigDNetDoDto dto)
    {
        if(mState != eState::STATE_READ_DO || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrDOActivation(dto.mDOActivation != mWriteDOActivation);
            setErrDOFunction  (dto.mDOFunction   != mWriteDOFunction  );
            setErrDOPolarity  (dto.mDOPolarity   != mWriteDOPolarity  );

            onCommandSetEdit(getErrDIActivation() || getErrDIFunction() || getErrDIPolarity() || getErrDOActivation() || getErrDOFunction() || getErrDOPolarity());
        }
        else
        {
            setDOActivation(dto.mDOActivation);
            setDOFunction  (dto.mDOFunction  );
            setDOPolarity  (dto.mDOPolarity  );
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int diActivation, int diFunction, int diPolarity, int doActivation, int doFunction, int doPolarity)
    {
        mIsWritten         = true        ;
        mWriteDIActivation = diActivation;
        mWriteDIFunction   = diFunction  ;
        mWriteDIPolarity   = diPolarity  ;
        mWriteDOActivation = doActivation;
        mWriteDOFunction   = doFunction  ;
        mWriteDOPolarity   = doPolarity  ;

        setIsEdit(false);

        setErrMsg("");
        setErrMsg2("");

        setState(eState::STATE_WRITE_DI);
    }

    void onValveWrittenInterfaceConfigDNetDi(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_DI || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenInterfaceConfigDNetDo(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_DO || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        setState((eState)(mState + 1));
    }

private:
    enum eState{
        STATE_WRITE_DI      =  0,
        STATE_WRITE_DO      = STATE_WRITE_DI      + 1,
        STATE_READ_MAC      = STATE_WRITE_DO      + 1,
        STATE_READ_BAUDRATE = STATE_READ_MAC      + 1,
        STATE_READ_DI       = STATE_READ_BAUDRATE + 1,
        STATE_READ_DO       = STATE_READ_DI       + 1,
        STATE_READY         = STATE_READ_DO       + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_WRITE_DI;

    bool mIsWritten       = false;
    int  mWriteDIActivation = 0;
    int  mWriteDIFunction   = 0;
    int  mWriteDIPolarity   = 0;
    int  mWriteDOActivation = 0;
    int  mWriteDOFunction   = 0;
    int  mWriteDOPolarity   = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        int progress = 0;
        QString strStatus;

        mState = state;

        if(mIsWritten == false && mState == STATE_READY)
        {
            onCommandSetEdit(false);

            emit signalEventCompletedLoad();
        }

        progress = ((mState) * 100) / STATE_READY;

        if(mState >= STATE_READ_MAC && mState <= STATE_READ_DO)
        {
            strStatus = "loading";
        }
        else if(mState >= STATE_WRITE_DI && mState <= STATE_WRITE_DO)
        {
            strStatus = "writting";
        }
        else
        {
            progress = 100;
            strStatus = "ready";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_MAC:
            pValveSP->readInterfaceConfigDNetMac(this);
            break;
        case (int)eState::STATE_READ_BAUDRATE:
            pValveSP->readInterfaceConfigDNetBaudrate(this);
            break;

        case (int)eState::STATE_READ_DI:
            pValveSP->readInterfaceConfigDNetDi(this);
            break;

        case (int)eState::STATE_READ_DO:
            pValveSP->readInterfaceConfigDNetDo(this);
            break;

        case (int)eState::STATE_WRITE_DI:
            pValveSP->setInterfaceConfigDNetDi(mWriteDIActivation, mWriteDIFunction, mWriteDIPolarity, this);
            break;

        case (int)eState::STATE_WRITE_DO:
            pValveSP->setInterfaceConfigDNetDo(mWriteDOActivation, mWriteDOFunction, mWriteDOPolarity, this);
            break;
        }
    }

private:
    int transBaudrateToIdx(int baudrate)
    {
        switch (baudrate) {
        case 125: return 1;
        case 250: return 2;
        case 500: return 3;
        }
        return 0;
    }
};

#endif // INTERFACESETUPDEVNETDLGMODEL_H
