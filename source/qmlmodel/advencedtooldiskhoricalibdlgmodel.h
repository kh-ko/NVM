#ifndef ADVENCEDTOOLDISKHORICALIBDLGMODEL_H
#define ADVENCEDTOOLDISKHORICALIBDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class AdvancedToolDiskHoriCalibDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode         )
    Q_PROPERTY(bool     mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test        )
    Q_PROPERTY(int      mCurrSyncOffset      READ getCurrSyncOffset      NOTIFY signalEventChangedCurrSyncOffset     )
    Q_PROPERTY(int      mTargetPos           READ getTargetPos           NOTIFY signalEventChangedTargetPos          )
    Q_PROPERTY(int      mCurrPos             READ getCurrPos             NOTIFY signalEventChangedCurrPos            )
    Q_PROPERTY(bool     mIsEdit              READ getIsEdit              NOTIFY signalEventChangedIsEdit             )
    Q_PROPERTY(QString  mStrStatus           READ getStrStatus           NOTIFY signalEventChangedStrStatus          )
    Q_PROPERTY(QString  mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg             )
    Q_PROPERTY(QString  mErrMsg2             READ getErrMsg2             NOTIFY signalEventChangedErrMsg2            )
    Q_PROPERTY(int      mProgress            READ getProgress            NOTIFY signalEventChangedProgress           )

public:
    int     mAccessMode          = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test         = false;
    int     mCurrSyncOffset      = 0;
    int     mTargetPos           = 0;
    int     mCurrPos             = 0;
    bool    mIsEdit              = false;
    QString mStrStatus           = "Loading";
    QString mErrMsg              = "";
    QString mErrMsg2             = "";
    int     mProgress            = 0 ;

    int     getAccessMode    (){ return mAccessMode    ;}
    bool    getIsRS232Test   (){ return mIsRS232Test   ;}
    int     getCurrSyncOffset(){ return mCurrSyncOffset;}
    int     getTargetPos     (){ return mTargetPos     ;}
    int     getCurrPos       (){ return mCurrPos       ;}
    bool    getIsEdit        (){ return mIsEdit        ;}
    QString getStrStatus     (){ return mStrStatus     ;}
    QString getErrMsg        (){ return mErrMsg        ;}
    QString getErrMsg2       (){ return mErrMsg2       ;}
    int     getProgress      (){ return mProgress      ;}

    void    setAccessMode    (int     value){ if(mAccessMode     == value)return; mAccessMode     = value; emit signalEventChangedAccessMode    (value);}
    void    setIsRS232Test   (bool    value){ if(mIsRS232Test    == value)return; mIsRS232Test    = value; emit signalEventChangedIsRS232Test   (value);}
    void    setCurrSyncOffset(int     value){ if(mCurrSyncOffset == value)return; mCurrSyncOffset = value; emit signalEventChangedCurrSyncOffset(value);}
    void    setTargetPos     (int     value){ if(mTargetPos      == value)return; mTargetPos      = value; emit signalEventChangedTargetPos     (value);}
    void    setCurrPos       (int     value){ if(mCurrPos        == value)return; mCurrPos        = value; emit signalEventChangedCurrPos       (value);}
    void    setIsEdit        (bool    value){ if(mIsEdit         == value)return; mIsEdit         = value; emit signalEventChangedIsEdit        (value);}
    void    setStrStatus     (QString value){ if(mStrStatus      == value)return; mStrStatus      = value; emit signalEventChangedStrStatus     (value);}
    void    setErrMsg        (QString value){ if(mErrMsg         == value)return; mErrMsg         = value; emit signalEventChangedErrMsg        (value);}
    void    setErrMsg2       (QString value){ if(mErrMsg2        == value)return; mErrMsg2        = value; emit signalEventChangedErrMsg2       (value);}
    void    setProgress      (int     value){ if(mProgress       == value)return; mProgress       = value; emit signalEventChangedProgress      (value);}

signals:
    void signalEventChangedAccessMode    (int     value);
    void signalEventChangedIsRS232Test   (bool    value);
    void signalEventChangedCurrSyncOffset(bool    value);
    void signalEventChangedTargetPos     (bool    value);
    void signalEventChangedCurrPos       (bool    value);
    void signalEventChangedIsEdit        (bool    value);
    void signalEventChangedStrStatus     (QString value);
    void signalEventChangedErrMsg        (QString value);
    void signalEventChangedErrMsg2       (QString value);
    void signalEventChangedProgress      (int     value);
    void signalEventCompletedLoad        (             );

public:
    explicit AdvancedToolDiskHoriCalibDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_CURR_POS;
        ENABLE_SLOT_VALVE_CHANGED_LOAD_PROGRESS;
        ENABLE_SLOT_VALVE_READED_VALVE_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_START;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_END;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedCurrPosition();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_SYNC);
    }
    ~AdvancedToolDiskHoriCalibDlgModel()
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

    void onValveChangedCurrPosition()
    {
        setCurrPos(pValveSP->getCurrPosition()/10);
    }

    void onValveChangedLoadProgress(int value)
    {
        if(value == ValveEnumDef::LOAD_COMPLETED && mState == STATE_WRITE_REBOOT_WAIT)
        {
            setState(STATE_READ_SYNC);
        }
    }

    void onValveReadedValveParam(ValveResponseValveParamDto dto)
    {
        int tempValue;
        if(dto.mValue.contains("-"))
        {
            tempValue = dto.mValue.replace("-","0").toInt(nullptr, 16) * -1;
        }
        else
        {
            tempValue = dto.mValue.toInt(nullptr, 16);
        }
        setCurrSyncOffset(tempValue);

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandReboot()
    {
        setErrMsg("");
        setErrMsg2("");

        setState(STATE_WRITE_REBOOT);
    }

    Q_INVOKABLE void onCommandSetSyncOffset(int value)
    {
        setErrMsg("");
        setErrMsg2("");

        if(value < 0)
        {
            mWriteSyncOffset = QString("-%1").arg(value * -1, 5, 16, QChar('0'));
        }
        else
        {
            mWriteSyncOffset = QString("%1").arg(value, 6, 16, QChar('0'));
        }
        setState(STATE_WRITE_START);
    }

    Q_INVOKABLE void onCommandPosition(int value)
    {
        pValveSP->setTargetPosition(value * 10, this);
    }

    void onValveWrittenValveParam(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_SYNC || dto.mReqDto.mpRef != this)
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
    void onValveWrittenValveParamStart(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_START || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setState((eState)(mState + 1));
    }
    void onValveWrittenValveParamEnd(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_END || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setState((eState)(mState + 1));
    }


private:
    enum eState{
        STATE_WRITE_REBOOT      = 0,
        STATE_WRITE_REBOOT_WAIT = STATE_WRITE_REBOOT      + 1,
        STATE_WRITE_START       = STATE_WRITE_REBOOT_WAIT + 1,
        STATE_WRITE_SYNC        = STATE_WRITE_START       + 1,
        STATE_WRITE_END         = STATE_WRITE_SYNC        + 1,
        STATE_READ_SYNC         = STATE_WRITE_END         + 1,
        STATE_READY             = STATE_READ_SYNC         + 1
    };

    QTimer mTimer;
    eState mState;
    bool   mIsFirstRead = true;
    QString mWriteSyncOffset = "";

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

        if(mIsFirstRead && mState == STATE_READY)
        {
            mIsFirstRead = false;
            emit signalEventCompletedLoad();
        }

        progress = ((mState) * 100) / STATE_READY;

        if(mState == STATE_READ_SYNC)
        {
            strStatus = "loading";
        }
        else if(mState >= STATE_WRITE_REBOOT && mState <= STATE_WRITE_END)
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
        case (int)STATE_WRITE_REBOOT:
            pValveSP->reboot(this);
            setState((eState)(mState + 1));
            break;
        //case (int)STATE_WRITE_REBOOT_WAIT:
        //    break;
        case (int)STATE_WRITE_START:
            pValveSP->setValveParamStart(this);
            break;
        case (int)STATE_WRITE_SYNC:
            pValveSP->setValveParam(51, mWriteSyncOffset, this);
            break;
        case (int)STATE_WRITE_END:
            pValveSP->setValveParamEnd(this);
            break;
        case (int)STATE_READ_SYNC:
            pValveSP->readValveParam(51/*sync offset param idx*/, this);
            break;
        }
    }

};
#endif // ADVENCEDTOOLDISKHORICALIBDLGMODEL_H
