#ifndef VALVEPOWERFAILSTATUSDLGMODEL_H
#define VALVEPOWERFAILSTATUSDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ValvePowerFailStatusDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode           NOTIFY signalEventChangedAccessMode        )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test          NOTIFY signalEventChangedIsRS232Test       )
    Q_PROPERTY(bool     mEnablePFO               READ getEnablePFO            NOTIFY signalEventChangedEnablePFO         )
    Q_PROPERTY(int      mPerformedCycles         READ getPerformedCycles      NOTIFY signalEventChangedPerformedCycles   )
    Q_PROPERTY(int      mCurrentVoltage          READ getCurrentVoltage       NOTIFY signalEventChangedCurrentVoltage    )
    Q_PROPERTY(int      mXRangeSec               READ getXRangeSec            NOTIFY signalEventChangedXRangeSec         )
    Q_PROPERTY(bool     mAutoScale               READ getAutoScale            NOTIFY signalEventChangedAutoScale         )
    Q_PROPERTY(bool     mErrPerformedCycles      READ getErrPerformedCycles   NOTIFY signalEventChangedErrPerformedCycles)
    Q_PROPERTY(bool     mErrCurrentVoltage       READ getErrCurrentVoltage    NOTIFY signalEventChangedErrCurrentVoltage )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit               NOTIFY signalEventChangedIsEdit            )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus            NOTIFY signalEventChangedStrStatus         )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg               NOTIFY signalEventChangedErrMsg            )
    Q_PROPERTY(QString  mErrMsg2                 READ getErrMsg2              NOTIFY signalEventChangedErrMsg2           )
    Q_PROPERTY(int      mProgress                READ getProgress             NOTIFY signalEventChangedProgress          )

public:
    int     mXRangeArray[4]          = {30, 60, 120, 300};
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test             = false;
    bool    mEnablePFO               = false;
    int     mPerformedCycles         = 0;
    int     mCurrentVoltage          = 0;
    int     mXRangeSec               = mXRangeArray[0];
    bool    mAutoScale               = false;
    bool    mErrPerformedCycles      = false;
    bool    mErrCurrentVoltage       = false;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "Loading";
    QString mErrMsg                  = "";
    QString mErrMsg2                 = "";
    int     mProgress                = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    bool    getEnablePFO              (){ return mEnablePFO              ;}
    int     getPerformedCycles        (){ return mPerformedCycles        ;}
    int     getCurrentVoltage         (){ return mCurrentVoltage         ;}
    int     getXRangeSec              (){ return mXRangeSec              ;}
    bool    getAutoScale              (){ return mAutoScale              ;}
    bool    getErrPerformedCycles     (){ return mErrPerformedCycles     ;}
    bool    getErrCurrentVoltage      (){ return mErrCurrentVoltage      ;}
    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setEnablePFO              (bool    value){ if(mEnablePFO               == value)return; mEnablePFO               = value; emit signalEventChangedEnablePFO              (value);}
    void    setPerformedCycles        (int     value){ if(mPerformedCycles         == value)return; mPerformedCycles         = value; emit signalEventChangedPerformedCycles        (value);}
    void    setCurrentVoltage         (int     value){ if(mCurrentVoltage          == value)return; mCurrentVoltage          = value; emit signalEventChangedCurrentVoltage         (value);}
    void    setXRangeSec              (int     value){ if(mXRangeSec               == value)return; mXRangeSec               = value; emit signalEventChangedXRangeSec              (value);}
    void    setAutoScale              (bool    value){ if(mAutoScale               == value)return; mAutoScale               = value; emit signalEventChangedAutoScale              (value);}
    void    setErrPerformedCycles     (bool    value){ if(mErrPerformedCycles      == value)return; mErrPerformedCycles      = value; emit signalEventChangedErrPerformedCycles     (value);}
    void    setErrCurrentVoltage      (bool    value){ if(mErrCurrentVoltage       == value)return; mErrCurrentVoltage       = value; emit signalEventChangedErrCurrentVoltage      (value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedEnablePFO              (bool    value);
    void signalEventChangedPerformedCycles        (int     value);
    void signalEventChangedCurrentVoltage         (int     value);
    void signalEventChangedXRangeSec              (int     value);
    void signalEventChangedAutoScale              (bool    value);
    void signalEventChangedErrPerformedCycles     (bool    value);
    void signalEventChangedErrCurrentVoltage      (bool    value);
    void signalEventChangedIsEdit                 (int     value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventAddedVoltagePoint             (int msec, int  mvolt);

public:
    explicit ValvePowerFailStatusDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_ENABLE_PFO;
        ENABLE_SLOT_VALVE_CHANGED_PFO_NOT_READY;
        ENABLE_SLOT_VALVE_READED_PFO_CURRENT_VOLTAGE;
        ENABLE_SLOT_VALVE_READED_PFO_PERFORMED_CYCLES;
        ENABLE_SLOT_VALVE_WRITTEN_ENABLE_PFO;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedEnablePFO();
        onValveChangedPFONotReady();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        mLastScanMSec = QDateTime::currentMSecsSinceEpoch();

        setState(eState::STATE_READ_VOLTAGE);
    }
    ~ValvePowerFailStatusDlgModel()
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

    void onValveChangedEnablePFO()
    {
        setEnablePFO(pValveSP->getEnablePFO());

        if(pValveSP->getEnablePFO() && pValveSP->getPFONotReady())
            setErrMsg("PFO is charging and thus not ready!");
        else
            setErrMsg("");
    }

    void onValveChangedPFONotReady()
    {
        if(pValveSP->getEnablePFO() && pValveSP->getPFONotReady())
            setErrMsg("PFO is charging and thus not ready!");
        else
            setErrMsg("");
    }

    void onValveReadedPFOCurrentVoltage(ValveResponsePFOCurrentVoltageDto dto)
    {
        if(dto.mReqDto.mpRef != mpReqtag)
            return;

        if(dto.mIsSucc)
        {
            setCurrentVoltage(dto.mCurrentVoltage);
            emit signalEventAddedVoltagePoint(dto.mResDateTime.time().msecsSinceStartOfDay(), dto.mCurrentVoltage);
        }

        setErrCurrentVoltage(!dto.mIsSucc && !dto.mIsNetworkErr);

        if(mVoltageReadCnt % 10 == 0)
            setState((eState)(mState + 1));
        else
            setState(mState);
    }

    void onValveReadedPFOPerformedCycles(ValveResponsePFOPerformedCyclesDto dto)
    {
        if(dto.mReqDto.mpRef != mpReqtag)
            return;

        if(dto.mIsSucc)
        {
            setPerformedCycles(dto.mCycles);
        }

        setErrPerformedCycles(!dto.mIsSucc && !dto.mIsNetworkErr);

        setState((eState)(mState + 1));
    }

    void onValveWrittenEnablePFO(ValveResponseDto dto)
    {
        if(dto.mReqDto.mpRef != mpReqtag)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg2(dto.mErrMsg);

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetAutoScale()
    {
        setAutoScale(!getAutoScale());
    }

    Q_INVOKABLE void onCommandSetXRangeIdx(int idx)
    {
        setXRangeSec(mXRangeArray[idx]);
    }

    Q_INVOKABLE void onCommandEnablePFO()
    {
        cancelReqTag();
        setState(eState::STATE_WRITE_PFO_ENABLE);
    }

private:
    enum eState{
        STATE_WRITE_PFO_ENABLE      =  0,
        STATE_READ_VOLTAGE          =  STATE_WRITE_PFO_ENABLE      + 1,
        STATE_READ_PERFORMED_CYCLES =  STATE_READ_VOLTAGE          + 1,
        STATE_OVER                  =  STATE_READ_PERFORMED_CYCLES + 1,
    };

    QTimer  mTimer;

    bool    mIsFirstRead     = true;
    eState  mState           = eState::STATE_READ_VOLTAGE;
    qint64  mLastScanMSec    = 0;
    quint32 mVoltageReadCnt  = 0;

    ReqCommandUserData *mpReqtag = nullptr;

    void startTimer(qint64 delay)
    {
        mTimer.stop();
        mTimer.start(delay);
    }

    void setState(eState state)
    {
        qint64 currMSec;

        if(state == eState::STATE_OVER)
        {
            state = eState::STATE_READ_VOLTAGE;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_PERFORMED_CYCLES));
        }
        else if(mState == eState::STATE_READ_VOLTAGE)
        {
            currMSec = QDateTime::currentMSecsSinceEpoch();
            setStrStatus(QString("scan-rate %1 ms").arg(currMSec - mLastScanMSec));
            setProgress(100);
            mLastScanMSec = currMSec;
        }
        else if(mState == eState::STATE_WRITE_PFO_ENABLE)
        {
            setStrStatus("writting");
            setProgress(qFloor((state * 100) / eState::STATE_READ_PERFORMED_CYCLES));
        }

        startTimer(70);
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_VOLTAGE:
            mVoltageReadCnt++;
            mpReqtag = createReqTag();
            pValveSP->readPFOCurrentVoltage(mpReqtag);
            break;

        case (int)eState::STATE_READ_PERFORMED_CYCLES:
            mpReqtag = createReqTag();
            pValveSP->readPFOPerformedCycles(mpReqtag);
            break;

        case (int)eState::STATE_WRITE_PFO_ENABLE:
            mpReqtag = createReqTag();
            pValveSP->enablePFO(!pValveSP->getEnablePFO(), mpReqtag);
            break;
        }
    }

private:
    ReqCommandUserData * createReqTag()
    {
        cancelReqTag();

        return new ReqCommandUserData();
    }

    void cancelReqTag()
    {
        if(mpReqtag != nullptr)
            delete mpReqtag;

        mpReqtag = nullptr;
    }
};
#endif // VALVEPOWERFAILSTATUSDLGMODEL_H
