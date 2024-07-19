#ifndef VALVESETUPDLGMODEL_H
#define VALVESETUPDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ValveSetupDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode                NOTIFY signalEventChangedAccessMode             )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test               NOTIFY signalEventChangedIsRS232Test            )
    Q_PROPERTY(bool     mIsSupportPFO            READ getIsSupportPFO              NOTIFY signalEventChangedIsSupportPFO           )
    Q_PROPERTY(int      mInterface               READ getInterface                 NOTIFY signalEventChangedInterface              )
    Q_PROPERTY(int      mValveSpeed              READ getValveSpeed                NOTIFY signalEventChangedValveSpeed             )
    Q_PROPERTY(int      mValveMaxSpeed           READ getValveMaxSpeed             NOTIFY signalEventChangedValveMaxSpeed          )
    Q_PROPERTY(int      mTargetPosSync           READ getTargetPosSync             NOTIFY signalEventChangedTargetPosSync          )
    Q_PROPERTY(int      mEventSync               READ getEventSync                 NOTIFY signalEventChangedEventSync              )
    Q_PROPERTY(int      mSyncMode                READ getSyncMode                  NOTIFY signalEventChangedSyncMode               )
    Q_PROPERTY(int      mStrokeLimitation        READ getStrokeLimitation          NOTIFY signalEventChangedStrokeLimitation       )
    Q_PROPERTY(int      mTargetPosPowerFail      READ getTargetPosPowerFail        NOTIFY signalEventChangedTargetPosPowerFail     )
    Q_PROPERTY(int      mTargetPosNetworkFail    READ getTargetPosNetworkFail      NOTIFY signalEventChangedTargetPosNetworkFail   )
    Q_PROPERTY(bool     mErrValveSpeed           READ getErrValveSpeed             NOTIFY signalEventChangedErrValveSpeed          )
    Q_PROPERTY(bool     mErrTargetPosSync        READ getErrTargetPosSync          NOTIFY signalEventChangedErrTargetPosSync       )
    Q_PROPERTY(bool     mErrEventSync            READ getErrEventSync              NOTIFY signalEventChangedErrEventSync           )
    Q_PROPERTY(bool     mErrSyncMode             READ getErrSyncMode               NOTIFY signalEventChangedErrSyncMode            )
    Q_PROPERTY(bool     mErrStrokeLimitation     READ getErrStrokeLimitation       NOTIFY signalEventChangedErrStrokeLimitation    )
    Q_PROPERTY(bool     mErrTargetPosPowerFail   READ getErrTargetPosPowerFail     NOTIFY signalEventChangedErrTargetPosPowerFail  )
    Q_PROPERTY(bool     mErrTargetPosNetworkFail READ getErrTargetPosNetworkFail   NOTIFY signalEventChangedErrTargetPosNetworkFail)
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                    NOTIFY signalEventChangedIsEdit                 )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus                 NOTIFY signalEventChangedStrStatus              )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                    NOTIFY signalEventChangedErrMsg                 )
    Q_PROPERTY(int      mProgress                READ getProgress                  NOTIFY signalEventChangedProgress               )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test             = false;
    bool    mIsSupportPFO            = false;
    int     mInterface               = ValveEnumDef::INTERFACE_LOGIC;
    int     mValveSpeed              = 1000;
    int     mValveMaxSpeed           = 1000;
    int     mTargetPosSync           = ValveEnumDef::TARGET_POS_SYNC_CLOSE;
    int     mEventSync               = ValveEnumDef::EVENT_SYNC_DEFAULT;
    int     mSyncMode                = ValveEnumDef::SYNC_MODE_SHORT;
    int     mStrokeLimitation        = 0;
    int     mTargetPosPowerFail      = ValveEnumDef::TARGET_POS_PF_CLOSE;
    int     mTargetPosNetworkFail    = ValveEnumDef::TARGET_POS_NF_CLOSE;
    bool    mErrValveSpeed           = false;
    bool    mErrTargetPosSync        = false;
    bool    mErrEventSync            = false;
    bool    mErrSyncMode             = false;
    bool    mErrStrokeLimitation     = false;
    bool    mErrTargetPosPowerFail   = false;
    bool    mErrTargetPosNetworkFail = false;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "Loading";
    QString mErrMsg                  = "";
    int     mProgress                = 0 ;

    int     getAccessMode             (){ return mAccessMode             ; }
    bool    getIsRS232Test            (){ return mIsRS232Test            ; }
    bool    getIsSupportPFO           (){ return mIsSupportPFO           ; }
    int     getInterface              (){ return mInterface              ; }
    int     getValveSpeed             (){ return mValveSpeed             ; }
    int     getValveMaxSpeed          (){ return mValveMaxSpeed          ; }
    int     getTargetPosSync          (){ return mTargetPosSync          ; }
    int     getEventSync              (){ return mEventSync              ; }
    int     getSyncMode               (){ return mSyncMode               ; }
    int     getStrokeLimitation       (){ return mStrokeLimitation       ; }
    int     getTargetPosPowerFail     (){ return mTargetPosPowerFail     ; }
    int     getTargetPosNetworkFail   (){ return mTargetPosNetworkFail   ; }
    bool    getErrValveSpeed          (){ return mErrValveSpeed          ; }
    bool    getErrTargetPosSync       (){ return mErrTargetPosSync       ; }
    bool    getErrEventSync           (){ return mErrEventSync           ; }
    bool    getErrSyncMode            (){ return mErrSyncMode            ; }
    bool    getErrStrokeLimitation    (){ return mErrStrokeLimitation    ; }
    bool    getErrTargetPosPowerFail  (){ return mErrTargetPosPowerFail  ; }
    bool    getErrTargetPosNetworkFail(){ return mErrTargetPosNetworkFail; }
    bool    getIsEdit                 (){ return mIsEdit                 ; }
    QString getStrStatus              (){ return mStrStatus              ; }
    QString getErrMsg                 (){ return mErrMsg                 ; }
    int     getProgress               (){ return mProgress               ; }

    void    setAccessMode             (int     value){if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setIsSupportPFO           (bool    value){if(mIsSupportPFO            == value)return; mIsSupportPFO            = value; emit signalEventChangedIsSupportPFO           (value);}
    void    setInterface              (int     value){if(mInterface               == value)return; mInterface               = value; emit signalEventChangedInterface              (value);}
    void    setValveSpeed             (int     value){if(mValveSpeed              == value)return; mValveSpeed              = value; emit signalEventChangedValveSpeed             (value);}
    void    setValveMaxSpeed          (int     value){if(mValveMaxSpeed           == value)return; mValveMaxSpeed           = value; emit signalEventChangedValveMaxSpeed          (value);}
    void    setTargetPosSync          (int     value){if(mTargetPosSync           == value)return; mTargetPosSync           = value; emit signalEventChangedTargetPosSync          (value);}
    void    setEventSync              (int     value){if(mEventSync               == value)return; mEventSync               = value; emit signalEventChangedEventSync              (value);}
    void    setSyncMode               (int     value){if(mSyncMode                == value)return; mSyncMode                = value; emit signalEventChangedSyncMode               (value);}
    void    setStrokeLimitation       (int     value){if(mStrokeLimitation        == value)return; mStrokeLimitation        = value; emit signalEventChangedStrokeLimitation       (value);}
    void    setTargetPosPowerFail     (int     value){if(mTargetPosPowerFail      == value)return; mTargetPosPowerFail      = value; emit signalEventChangedTargetPosPowerFail     (value);}
    void    setTargetPosNetworkFail   (int     value){if(mTargetPosNetworkFail    == value)return; mTargetPosNetworkFail    = value; emit signalEventChangedTargetPosNetworkFail   (value);}
    void    setErrValveSpeed          (bool    value){if(mErrValveSpeed           == value)return; mErrValveSpeed           = value; emit signalEventChangedErrValveSpeed          (value);}
    void    setErrTargetPosSync       (bool    value){if(mErrTargetPosSync        == value)return; mErrTargetPosSync        = value; emit signalEventChangedErrTargetPosSync       (value);}
    void    setErrEventSync           (bool    value){if(mErrEventSync            == value)return; mErrEventSync            = value; emit signalEventChangedErrEventSync           (value);}
    void    setErrSyncMode            (bool    value){if(mErrSyncMode             == value)return; mErrSyncMode             = value; emit signalEventChangedErrSyncMode            (value);}
    void    setErrStrokeLimitation    (bool    value){if(mErrStrokeLimitation     == value)return; mErrStrokeLimitation     = value; emit signalEventChangedErrStrokeLimitation    (value);}
    void    setErrTargetPosPowerFail  (bool    value){if(mErrTargetPosPowerFail   == value)return; mErrTargetPosPowerFail   = value; emit signalEventChangedErrTargetPosPowerFail  (value);}
    void    setErrTargetPosNetworkFail(bool    value){if(mErrTargetPosNetworkFail == value)return; mErrTargetPosNetworkFail = value; emit signalEventChangedErrTargetPosNetworkFail(value);}
    void    setIsEdit                 (bool    value){if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setProgress               (int     value){if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:

    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedIsSupportPFO           (bool    value);
    void signalEventChangedInterface              (int     value);
    void signalEventChangedValveSpeed             (int     value);
    void signalEventChangedValveMaxSpeed          (int     value);
    void signalEventChangedTargetPosSync          (int     value);
    void signalEventChangedEventSync              (int     value);
    void signalEventChangedSyncMode               (int     value);
    void signalEventChangedStrokeLimitation       (int     value);
    void signalEventChangedTargetPosPowerFail     (int     value);
    void signalEventChangedTargetPosNetworkFail   (int     value);
    void signalEventChangedErrValveSpeed          (bool    value);
    void signalEventChangedErrTargetPosSync       (bool    value);
    void signalEventChangedErrEventSync           (bool    value);
    void signalEventChangedErrSyncMode            (bool    value);
    void signalEventChangedErrStrokeLimitation    (bool    value);
    void signalEventChangedErrTargetPosPowerFail  (bool    value);
    void signalEventChangedErrTargetPosNetworkFail(bool    value);
    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );
    void signalEventCompletedApply                (             );


public:
    explicit ValveSetupDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;

        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_IS_SUPPORT_PFO;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_INTERFACE;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_MAX_SPEED;
        ENABLE_SLOT_VALVE_READED_VALVE_SETUP;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_SPEED;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_SETUP;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedIsSupportPFO();
        onValveChangedInterface();
        onValveChangedValveMaxSpeed();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_SPEED);
    }
    ~ValveSetupDlgModel()
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

    void onValveChangedIsSupportPFO()
    {
        setIsSupportPFO(pValveSP->getIsSupportPFO());
    }

    void onValveChangedInterface()
    {
        setInterface(pValveSP->getInterface());
    }

    void onValveReadedValveSpeed()
    {
        if(mIsWritten)
        {
            setErrValveSpeed(pValveSP->getValveSpeed() != mWriteSpeed);
        }
        else
        {
            setValveSpeed(pValveSP->getValveSpeed());
        }
        setState((eState)(mState + 1));
    }

    void onValveChangedValveMaxSpeed()
    {
        setValveMaxSpeed(pValveSP->getValveMaxSpeed());
    }

    void onValveReadedValveSetup(ValveResponseValveSetupDto dto)
    {
        if(mState != eState::STATE_READ_SETUP || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrTargetPosSync       (dto.mTargetPosSync        != mWriteTargetPosSync       );
            setErrEventSync           (dto.mEventSync            != mWriteEventSync           );
            setErrSyncMode            (dto.mSyncMode             != mWriteSyncMode            );
            setErrStrokeLimitation    (dto.mStrokeLimitation     != mWriteStrokeLimit         );
            setErrTargetPosPowerFail  (dto.mTargetPosPowerFail   != mWriteTargetPosPowerFail  );
            setErrTargetPosNetworkFail(dto.mTargetPosNetworkFail != mWriteTargetPosNetworkFail);

            onCommandSetEdit(getErrValveSpeed() || getErrTargetPosSync() || getErrEventSync() || getErrSyncMode() || getErrStrokeLimitation() || getErrTargetPosPowerFail() || getErrTargetPosNetworkFail());
        }
        else
        {
            setTargetPosSync       (dto.mTargetPosSync       );
            setEventSync           (dto.mEventSync           );
            setSyncMode            (dto.mSyncMode            );
            setStrokeLimitation    (dto.mStrokeLimitation    );
            setTargetPosPowerFail  (dto.mTargetPosPowerFail  );
            setTargetPosNetworkFail(dto.mTargetPosNetworkFail);
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int speed, int targetPosSync, int eventSync, int syncMode, int strokeLimit, int targetPosPowerFail, int targetPosNetworkFail)
    {
        mIsWritten = true;
        mWriteSpeed = speed;
        mWriteTargetPosSync = targetPosSync;
        mWriteEventSync = eventSync;
        mWriteSyncMode  = syncMode;
        mWriteStrokeLimit  = strokeLimit;
        mWriteTargetPosPowerFail = pValveSP->getIsSupportPFO() ? targetPosPowerFail : 0;
        mWriteTargetPosNetworkFail = /*pValveSP->getInterface() == ValveEnumDef::INTERFACE_LOGIC ? 0 :*/ targetPosNetworkFail;

        setErrMsg("");

        setState(eState::STATE_WRITE_SPEED);
    }

    void onValveWrittenValveSpeed(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_SPEED || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
            setErrMsg(dto.mErrMsg);

        setState((eState)(mState + 1));
    }

    void onValveWrittenValveSetup(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_SETUP || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
            setErrMsg(dto.mErrMsg);

        setState((eState)(mState + 1));
    }

private:
    enum eState{
        STATE_WRITE_SPEED =  0,
        STATE_WRITE_SETUP =  STATE_WRITE_SPEED + 1,
        STATE_READ_SPEED  =  STATE_WRITE_SETUP + 1,
        STATE_READ_SETUP  =  STATE_READ_SPEED  + 1,
        STATE_READY       =  STATE_READ_SETUP  + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_SPEED;

    bool mIsWritten = false;
    int  mWriteSpeed = 0;
    int  mWriteTargetPosSync = 0;
    int  mWriteEventSync = 0;
    int  mWriteSyncMode  = 0;
    int  mWriteStrokeLimit = 0;
    int  mWriteTargetPosPowerFail = 0;
    int  mWriteTargetPosNetworkFail = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        if(!mIsWritten && state == eState::STATE_READY)
        {
            emit signalEventCompletedLoad();
        }

        mState = state;

        if(state < (int) eState::STATE_READY && state >= (int) eState::STATE_READ_SPEED)
        {
            setStrStatus("loading");
        }
        else if(state < (int) eState::STATE_READ_SPEED && state >= (int) eState::STATE_WRITE_SETUP)
        {
            setStrStatus("writting");
        }
        else
        {
            setStrStatus("ready");
        }

        if(state == eState::STATE_READY)
        {
            setProgress(100);
        }
        else
        {
            setProgress(qFloor((state * 100) / eState::STATE_READY));
            startTimer();
        }
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_SPEED:
            onValveReadedValveSpeed();
            break;

        case (int)eState::STATE_READ_SETUP:
            pValveSP->readValveSetup(this);
            break;

        case (int)eState::STATE_WRITE_SPEED:
            pValveSP->setValveSpeed(mWriteSpeed, this);
            break;

        case (int)eState::STATE_WRITE_SETUP:
            pValveSP->setValveSetup(mWriteTargetPosSync, mWriteEventSync, mWriteSyncMode, mWriteStrokeLimit, mWriteTargetPosPowerFail, mWriteTargetPosNetworkFail, this);
            break;
        }
    }

};
#endif // VALVESETUPDLGMODEL_H
