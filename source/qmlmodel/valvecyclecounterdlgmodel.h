#ifndef VALVECYCLECOUNTERDLGMODEL_H
#define VALVECYCLECOUNTERDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ValveCycleCounterDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode               NOTIFY signalEventChangedAccessMode              )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test              NOTIFY signalEventChangedIsRS232Test             )
    Q_PROPERTY(qint64   mControlCycles           READ getControlCycles            NOTIFY signalEventChangedControlCycles           )
    Q_PROPERTY(qint64   mTotalControlCycles      READ getTotalControlCycles       NOTIFY signalEventChangedTotalControlCycles      )
    Q_PROPERTY(qint64   mIsolationCycles         READ getIsolationCycles          NOTIFY signalEventChangedIsolationCycles         )
    Q_PROPERTY(qint64   mTotalIsolationCycles    READ getTotalIsolationCycles     NOTIFY signalEventChangedTotalIsolationCycles    )
    Q_PROPERTY(bool     mErrControlCycles        READ getErrControlCycles         NOTIFY signalEventChangedErrControlCycles        )
    Q_PROPERTY(bool     mErrTotalControlCycles   READ getErrTotalControlCycles    NOTIFY signalEventChangedErrTotalControlCycles   )
    Q_PROPERTY(bool     mErrIsolationCycles      READ getErrIsolationCycles       NOTIFY signalEventChangedErrIsolationCycles      )
    Q_PROPERTY(bool     mErrTotalIsolationCycles READ getErrTotalIsolationCycles  NOTIFY signalEventChangedErrTotalIsolationCycles )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                   NOTIFY signalEventChangedIsEdit                  )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus                NOTIFY signalEventChangedStrStatus               )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                   NOTIFY signalEventChangedErrMsg                  )
    Q_PROPERTY(QString  mErrMsg2                 READ getErrMsg2                  NOTIFY signalEventChangedErrMsg2                 )
    Q_PROPERTY(int      mProgress                READ getProgress                 NOTIFY signalEventChangedProgress                )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test             = false;
    qint64  mControlCycles           = 0;
    qint64  mTotalControlCycles      = 0;
    qint64  mIsolationCycles         = 0;
    qint64  mTotalIsolationCycles    = 0;
    bool    mErrControlCycles        = false;
    bool    mErrTotalControlCycles   = false;
    bool    mErrIsolationCycles      = false;
    bool    mErrTotalIsolationCycles = false;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "Loading";
    QString mErrMsg                  = "";
    QString mErrMsg2                 = "";
    int     mProgress                = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    qint64  getControlCycles          (){ return mControlCycles          ;}
    qint64  getTotalControlCycles     (){ return mTotalControlCycles     ;}
    qint64  getIsolationCycles        (){ return mIsolationCycles        ;}
    qint64  getTotalIsolationCycles   (){ return mTotalIsolationCycles   ;}
    int     getErrControlCycles       (){ return mErrControlCycles       ;}
    int     getErrTotalControlCycles  (){ return mErrTotalControlCycles  ;}
    int     getErrIsolationCycles     (){ return mErrIsolationCycles     ;}
    int     getErrTotalIsolationCycles(){ return mErrTotalIsolationCycles;}
    int     getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setControlCycles          (qint64  value){ if(mControlCycles           == value)return; mControlCycles           = value; emit signalEventChangedControlCycles          (value);}
    void    setTotalControlCycles     (qint64  value){ if(mTotalControlCycles      == value)return; mTotalControlCycles      = value; emit signalEventChangedTotalControlCycles     (value);}
    void    setIsolationCycles        (qint64  value){ if(mIsolationCycles         == value)return; mIsolationCycles         = value; emit signalEventChangedIsolationCycles        (value);}
    void    setTotalIsolationCycles   (qint64  value){ if(mTotalIsolationCycles    == value)return; mTotalIsolationCycles    = value; emit signalEventChangedTotalIsolationCycles   (value);}
    void    setErrControlCycles       (bool    value){ if(mErrControlCycles        == value)return; mErrControlCycles        = value; emit signalEventChangedErrControlCycles       (value);}
    void    setErrTotalControlCycles  (bool    value){ if(mErrTotalControlCycles   == value)return; mErrTotalControlCycles   = value; emit signalEventChangedErrTotalControlCycles  (value);}
    void    setErrIsolationCycles     (bool    value){ if(mErrIsolationCycles      == value)return; mErrIsolationCycles      = value; emit signalEventChangedErrIsolationCycles     (value);}
    void    setErrTotalIsolationCycles(bool    value){ if(mErrTotalIsolationCycles == value)return; mErrTotalIsolationCycles = value; emit signalEventChangedErrTotalIsolationCycles(value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedControlCycles          (qint64  value);
    void signalEventChangedTotalControlCycles     (qint64  value);
    void signalEventChangedIsolationCycles        (qint64  value);
    void signalEventChangedTotalIsolationCycles   (qint64  value);
    void signalEventChangedErrControlCycles       (int     value);
    void signalEventChangedErrTotalControlCycles  (int     value);
    void signalEventChangedErrIsolationCycles     (int     value);
    void signalEventChangedErrTotalIsolationCycles(int     value);
    void signalEventChangedIsEdit                 (int     value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);

public:
    explicit ValveCycleCounterDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_CTRL_CYCLE;
        ENABLE_SLOT_VALVE_READED_TOTAL_CTRL_CYCLE;
        ENABLE_SLOT_VALVE_READED_ISOL_CYCLE;
        ENABLE_SLOT_VALVE_READED_TOTAL_ISOL_CYCLE;
        ENABLE_SLOT_VALVE_WRITTEN_CTRL_CYCLE_RESET;
        ENABLE_SLOT_VALVE_WRITTEN_ISOL_CYCLE_RESET;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CTRL_CNT);
    }
    ~ValveCycleCounterDlgModel()
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

    void onValveReadedControlCycles(ValveResponseControlCyclesDto dto)
    {
        if(mState != eState::STATE_READ_CTRL_CNT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setControlCycles(dto.mCycles);

        setState((eState)(mState + 1));
    }

    void onValveReadedTotalControlCycles(ValveResponseTotalControlCyclesDto dto)
    {
        if(mState != eState::STATE_READ_TOTAL_CTRL_CNT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setTotalControlCycles(dto.mCycles);

        setState((eState)(mState + 1));
    }

    void onValveReadedIsolationCycles(ValveResponseIsolationCyclesDto dto)
    {
        if(mState != eState::STATE_READ_ISOL_CNT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setIsolationCycles(dto.mCycles);

        setState((eState)(mState + 1));
    }

    void onValveReadedTotalIsolationCycles(ValveResponseTotalIsolationCyclesDto dto)
    {
        if(mState != eState::STATE_READ_TOTAL_ISOL_CNT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setTotalIsolationCycles(dto.mCycles);

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandControlCycleReset()
    {
        setState(eState::STATE_RESET_CTRL_CNT);
    }

    void onValveWrittenControlCyclesReset(ValveResponseDto dto)
    {
        if(mState != eState::STATE_RESET_CTRL_CNT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg2(dto.mErrMsg);

        setState(eState::STATE_READ_CTRL_CNT);
    }

    Q_INVOKABLE void onCommandIsolationCycleReset()
    {
        setState(eState::STATE_RESET_ISOL_CNT);
    }

    void onValveWrittenIsolationCyclesReset(ValveResponseDto dto)
    {
        if(mState != eState::STATE_RESET_ISOL_CNT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg2(dto.mErrMsg);

        setState(eState::STATE_READ_CTRL_CNT);
    }

private:
    enum eState{
        STATE_RESET_CTRL_CNT        = 0,
        STATE_RESET_ISOL_CNT        = STATE_RESET_CTRL_CNT + 1,
        STATE_READ_CTRL_CNT         = STATE_RESET_ISOL_CNT      + 1,
        STATE_READ_TOTAL_CTRL_CNT   = STATE_READ_CTRL_CNT       + 1,
        STATE_READ_ISOL_CNT         = STATE_READ_TOTAL_CTRL_CNT + 1,
        STATE_READ_TOTAL_ISOL_CNT   = STATE_READ_ISOL_CNT       + 1,
        STATE_OVER                  = STATE_READ_TOTAL_ISOL_CNT + 1
    };

    QTimer mTimer;
    bool   mIsFirstRead   = true;
    eState mState         = eState::STATE_READ_CTRL_CNT;
    qint64 mLastScanMSec  = 0;

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
            state = eState::STATE_READ_CTRL_CNT;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_TOTAL_ISOL_CNT));
        }
        else if( state == STATE_RESET_CTRL_CNT)
        {
            setStrStatus("reset...");
            setProgress(qFloor((state * 100) / eState::STATE_READ_TOTAL_ISOL_CNT));
        }
        else if( state == STATE_RESET_ISOL_CNT)
        {
            setStrStatus("reset...");
            setProgress(qFloor((state * 100) / eState::STATE_READ_TOTAL_ISOL_CNT));
        }
        else if(state == STATE_READ_CTRL_CNT)
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
        case eState::STATE_READ_CTRL_CNT:
            pValveSP->readControlCycles(this);
            break;

        case eState::STATE_READ_TOTAL_CTRL_CNT:
            pValveSP->readTotalControlCycles(this);
            break;

        case eState::STATE_READ_ISOL_CNT:
            pValveSP->readIsolationCycles(this);
            break;

        case eState::STATE_READ_TOTAL_ISOL_CNT:
            pValveSP->readTotalIsolationCycles(this);
            break;

        case eState::STATE_RESET_CTRL_CNT:
            pValveSP->controlCyclesReset(this);
            break;

        case eState::STATE_RESET_ISOL_CNT:
            pValveSP->isolationCyclesReset(this);
            break;
        }
    }
};
#endif // VALVECYCLECOUNTERDLGMODEL_H
