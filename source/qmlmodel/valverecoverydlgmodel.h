#ifndef VALVERECOVERYDLGMODEL_H
#define VALVERECOVERYDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ValveRecoveryDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode           NOTIFY signalEventChangedAccessMode        )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test          NOTIFY signalEventChangedIsRS232Test       )
    Q_PROPERTY(int      mFatalErrStatus          READ getFatalErrStatus       NOTIFY signalEventChangedFatalErrStatus    )
    Q_PROPERTY(bool     mIsSvcRequest            READ getIsSvcRequest         NOTIFY signalEventChangedIsSvcRequest      )
    Q_PROPERTY(bool     mReConnect               READ getReConnect            NOTIFY signalEventChangedReConnect         )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit               NOTIFY signalEventChangedIsEdit            )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus            NOTIFY signalEventChangedStrStatus         )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg               NOTIFY signalEventChangedErrMsg            )
    Q_PROPERTY(QString  mErrMsg2                 READ getErrMsg2              NOTIFY signalEventChangedErrMsg2           )
    Q_PROPERTY(int      mProgress                READ getProgress             NOTIFY signalEventChangedProgress          )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test             = false;
    int     mFatalErrStatus          = 0;
    bool    mIsSvcRequest            = false;
    bool    mReConnect               = false;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "Loading";
    QString mErrMsg                  = "";
    QString mErrMsg2                 = "";
    int     mProgress                = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    int     getFatalErrStatus         (){ return mFatalErrStatus         ;}
    bool    getIsSvcRequest           (){ return mIsSvcRequest           ;}
    bool    getReConnect              (){ return mReConnect              ;}
    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setFatalErrStatus         (int     value){ if(mFatalErrStatus          == value)return; mFatalErrStatus          = value; emit signalEventChangedFatalErrStatus         (value);}
    void    setIsSvcRequest           (bool    value){ if(mIsSvcRequest            == value)return; mIsSvcRequest            = value; emit signalEventChangedIsSvcRequest           (value);}
    void    setReConnect              (bool    value){ if(mReConnect               == value)return; mReConnect               = value; emit signalEventChangedReConnect              (value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedFatalErrStatus         (int     value);
    void signalEventChangedIsSvcRequest           (bool    value);
    void signalEventChangedReConnect              (bool    value);
    void signalEventChangedIsEdit                 (int     value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );

public:
    explicit ValveRecoveryDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_LOAD_PROGRESS;
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_RESULT_CONNECT;
        ENABLE_SLOT_VALVE_READED_FATAL_ERR_STATUS;
        ENABLE_SLOT_VALVE_READED_WARNINGS;
        ENABLE_SLOT_VALVE_WRITTEN_REBOOT;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_FATAL);
    }
    ~ValveRecoveryDlgModel()
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
        if(mState != STATE_READ_FATAL || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setFatalErrStatus(dto.mErrorCode);

        setState((eState)(mState + 1));
    }

    void onValveReadedWarnings(ValveResponseWarningsDto dto)
    {
        if(mState != STATE_READ_WARNING || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setIsSvcRequest(dto.mIsServiceRequest == 1 ? true : false);

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandReboot()
    {
        setState(eState::STATE_WRITE_REBOOT);
    }

    void onValveWrittenReboot(ValveResponseDto dto)
    {

    }

    void onValveChangedLoadProgress(int progress)
    {
        if(mState != eState::STATE_RECONNECT)
            return;

        if(progress == ValveEnumDef::LOAD_COMPLETED)
        {
            setState((eState)(mState + 1));
        }
        else
        {
            setProgress(qRound(((double)progress / (double)ValveEnumDef::LOAD_COMPLETED) * 100.0));
        }
    }

    void onValveResultConnect(bool isConnected, QString connectInfo)
    {
        Q_UNUSED(connectInfo)

        if(mState != eState::STATE_WRITE_REBOOT_WAIT)
            return;

        if(!isConnected)
        {
            setState(mState);
        }
        else if(isConnected)
        {
            setState((eState)(mState + 1));
        }
    }

private:
    enum eState{
        STATE_WRITE_REBOOT      = 0,
        STATE_WRITE_REBOOT_WAIT = STATE_WRITE_REBOOT      + 1,
        STATE_RECONNECT         = STATE_WRITE_REBOOT_WAIT + 1,
        STATE_READ_FATAL        = STATE_RECONNECT         + 1,
        STATE_READ_WARNING      = STATE_READ_FATAL        + 1,
        STATE_OVER              = STATE_READ_WARNING      + 1
    };

    QTimer mTimer;
    bool   mIsFirstRead  = true;
    eState mState        = eState::STATE_READ_FATAL;
    qint64 mLastScanMSec = 0;

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
            state = eState::STATE_READ_FATAL;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_WARNING));
        }
        if( state == STATE_WRITE_REBOOT)
        {
            setStrStatus("reboot");
            setProgress(0);
        }
        else if( state == STATE_WRITE_REBOOT_WAIT)
        {
            setReConnect(true);
            setStrStatus("reboot wait");
            setProgress(0);
        }
        else if( state == STATE_RECONNECT)
        {
            setStrStatus("reconnect...");
            setProgress(0);
        }
        else if(state == STATE_READ_FATAL)
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
        case (int)eState::STATE_READ_FATAL:
            pValveSP->readFatalErrStatus(this);
            break;

        case (int)eState::STATE_READ_WARNING:
            pValveSP->readWarnings(this);
            break;

        case (int)eState::STATE_WRITE_REBOOT:
            pValveSP->reboot(this);
            setState((eState)(mState + 1));
            break;

        case (int)eState::STATE_WRITE_REBOOT_WAIT:
            pValveSP->reConnectDevice();
            break;
        }
    }
};

#endif // VALVERECOVERYDLGMODEL_H
