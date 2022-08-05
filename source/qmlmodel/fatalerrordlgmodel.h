#ifndef FATALERRORDLGMODEL_H
#define FATALERRORDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class FatalErrorDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode           NOTIFY signalEventChangedAccessMode        )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test          NOTIFY signalEventChangedIsRS232Test            )
    Q_PROPERTY(int      mFatalErrStatus          READ getFatalErrStatus       NOTIFY signalEventChangedFatalErrStatus    )
    Q_PROPERTY(int      mErr01Pos                READ getErr01Pos             NOTIFY signalEventChangedErr01Pos          )
    Q_PROPERTY(int      mErr01TotalPos           READ getErr01TotalPos        NOTIFY signalEventChangedErr01TotalPos     )
    Q_PROPERTY(int      mErr02Pos                READ getErr02Pos             NOTIFY signalEventChangedErr02Pos          )
    Q_PROPERTY(int      mErr02TotalPos           READ getErr02TotalPos        NOTIFY signalEventChangedErr02TotalPos     )
    Q_PROPERTY(int      mErr03Pos                READ getErr03Pos             NOTIFY signalEventChangedErr03Pos          )
    Q_PROPERTY(int      mErr03TotalPos           READ getErr03TotalPos        NOTIFY signalEventChangedErr03TotalPos     )
    Q_PROPERTY(bool     mSupport01Pos            READ getSupport01Pos         NOTIFY signalEventChangedSupport01Pos      )
    Q_PROPERTY(bool     mSupport02Pos            READ getSupport02Pos         NOTIFY signalEventChangedSupport02Pos      )
    Q_PROPERTY(bool     mSupport03Pos            READ getSupport03Pos         NOTIFY signalEventChangedSupport03Pos      )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit               NOTIFY signalEventChangedIsEdit            )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus            NOTIFY signalEventChangedStrStatus         )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg               NOTIFY signalEventChangedErrMsg            )
    Q_PROPERTY(int      mProgress                READ getProgress             NOTIFY signalEventChangedProgress          )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test             = false;
    int     mFatalErrStatus          = 0;
    int     mErr01Pos                = 0;
    int     mErr01TotalPos           = 0;
    int     mErr02Pos                = 0;
    int     mErr02TotalPos           = 0;
    int     mErr03Pos                = 0;
    int     mErr03TotalPos           = 0;
    bool    mSupport01Pos            = true;
    bool    mSupport02Pos            = true;
    bool    mSupport03Pos            = true;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "Loading";
    QString mErrMsg                  = "";
    int     mProgress                = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    int     getFatalErrStatus         (){ return mFatalErrStatus         ;}
    int     getErr01Pos               (){ return mErr01Pos               ;}
    int     getErr01TotalPos          (){ return mErr01TotalPos          ;}
    int     getErr02Pos               (){ return mErr02Pos               ;}
    int     getErr02TotalPos          (){ return mErr02TotalPos          ;}
    int     getErr03Pos               (){ return mErr03Pos               ;}
    int     getErr03TotalPos          (){ return mErr03TotalPos          ;}
    bool    getSupport01Pos           (){ return mSupport01Pos           ;}
    bool    getSupport02Pos           (){ return mSupport02Pos           ;}
    bool    getSupport03Pos           (){ return mSupport03Pos           ;}
    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setFatalErrStatus         (int     value){ if(mFatalErrStatus          == value)return; mFatalErrStatus          = value; emit signalEventChangedFatalErrStatus         (value);}
    void    setErr01Pos               (int     value){ if(mErr01Pos                == value)return; mErr01Pos                = value; emit signalEventChangedErr01Pos               (value);}
    void    setErr01TotalPos          (int     value){ if(mErr01TotalPos           == value)return; mErr01TotalPos           = value; emit signalEventChangedErr01TotalPos          (value);}
    void    setErr02Pos               (int     value){ if(mErr02Pos                == value)return; mErr02Pos                = value; emit signalEventChangedErr02Pos               (value);}
    void    setErr02TotalPos          (int     value){ if(mErr02TotalPos           == value)return; mErr02TotalPos           = value; emit signalEventChangedErr02TotalPos          (value);}
    void    setErr03Pos               (int     value){ if(mErr03Pos                == value)return; mErr03Pos                = value; emit signalEventChangedErr03Pos               (value);}
    void    setErr03TotalPos          (int     value){ if(mErr03TotalPos           == value)return; mErr03TotalPos           = value; emit signalEventChangedErr03TotalPos          (value);}
    void    setSupport01Pos           (bool    value){ if(mSupport01Pos            == value)return; mSupport01Pos            = value; emit signalEventChangedSupport01Pos           (value);}
    void    setSupport02Pos           (bool    value){ if(mSupport02Pos            == value)return; mSupport02Pos            = value; emit signalEventChangedSupport02Pos           (value);}
    void    setSupport03Pos           (bool    value){ if(mSupport03Pos            == value)return; mSupport03Pos            = value; emit signalEventChangedSupport03Pos           (value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedFatalErrStatus         (int     value);
    void signalEventChangedErr01Pos               (int     value);
    void signalEventChangedErr01TotalPos          (int     value);
    void signalEventChangedErr02Pos               (int     value);
    void signalEventChangedErr02TotalPos          (int     value);
    void signalEventChangedErr03Pos               (int     value);
    void signalEventChangedErr03TotalPos          (int     value);
    void signalEventChangedSupport01Pos           (bool    value);
    void signalEventChangedSupport02Pos           (bool    value);
    void signalEventChangedSupport03Pos           (bool    value);
    void signalEventChangedIsEdit                 (int     value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );

public:
    explicit FatalErrorDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_FATAL_ERR_STATUS;
        ENABLE_SLOT_VALVE_READED_FATAL_ERR_01_POS;
        ENABLE_SLOT_VALVE_READED_FATAL_ERR_02_POS;
        ENABLE_SLOT_VALVE_READED_FATAL_ERR_03_POS;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_STATUS);
    }
    ~FatalErrorDlgModel()
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

    void onValveReadedFatalErrStatus(ValveResponseFatalErrStatusDto dto)
    {
        if(mState != eState::STATE_READ_STATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsSucc)
        {
            setFatalErrStatus(dto.mErrorCode);
            setState((eState)(mState + 1));
        }
        else
        {
            setState(mState);
            return;
        }
    }

    void onValveReadedFatalErr01Pos(ValveResponseFatalErrPosDto dto)
    {
        if(mState != eState::STATE_READ_ERR_01_POS || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsSucc)
        {
            setSupport01Pos(true);
            setErr01Pos(dto.mErrPosition);
            setErr01TotalPos(dto.mTotalPosition);
            setState((eState)(mState + 1));
        }
        else if(dto.mIsNetworkErr == false)
        {
            setSupport01Pos(false);
            setState((eState)(mState + 1));
        }
        else
        {
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }
    }

    void onValveReadedFatalErr02Pos(ValveResponseFatalErrPosDto dto)
    {
        if(mState != eState::STATE_READ_ERR_02_POS || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsSucc)
        {
            setSupport02Pos(true);
            setErr02Pos(dto.mErrPosition);
            setErr02TotalPos(dto.mTotalPosition);
            setState((eState)(mState + 1));
        }
        else if(dto.mIsNetworkErr == false)
        {
            setSupport02Pos(false);
            setState((eState)(mState + 1));
        }
        else
        {
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }
    }

    void onValveReadedFatalErr03Pos(ValveResponseFatalErrPosDto dto)
    {
        if(mState != eState::STATE_READ_ERR_03_POS || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsSucc)
        {
            setSupport03Pos(true);
            setErr03Pos(dto.mErrPosition);
            setErr03TotalPos(dto.mTotalPosition);
            setState((eState)(mState + 1));
        }
        else if(dto.mIsNetworkErr == false)
        {
            setSupport03Pos(false);
            setState((eState)(mState + 1));
        }
        else
        {   
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }
    }

private:
    enum eState{
        STATE_READ_STATUS     =  0,
        STATE_READ_ERR_01_POS =  STATE_READ_STATUS     + 1,
        STATE_READ_ERR_02_POS =  STATE_READ_ERR_01_POS + 1,
        STATE_READ_ERR_03_POS =  STATE_READ_ERR_02_POS + 1,
        STATE_OVER            =  STATE_READ_ERR_03_POS + 1
    };

    QTimer mTimer;
    bool   mIsFirstRead = true;
    eState mState         = eState::STATE_READ_STATUS;
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
            state = eState::STATE_READ_STATUS;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_ERR_03_POS));
        }
        else if(state == eState::STATE_READ_STATUS)
        {
            currMSec = QDateTime::currentMSecsSinceEpoch();

            setErrMsg("");
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
        case (int)eState::STATE_READ_STATUS:
            pValveSP->readFatalErrStatus(this);
            break;
        case (int)eState::STATE_READ_ERR_01_POS:
            pValveSP->readFatalErr01Pos(this);
            break;
        case (int)eState::STATE_READ_ERR_02_POS:
            pValveSP->readFatalErr02Pos(this);
            break;
        case (int)eState::STATE_READ_ERR_03_POS:
            pValveSP->readFatalErr03Pos(this);
            break;
        }
    }
};

#endif // FATALERRORDLGMODEL_H
