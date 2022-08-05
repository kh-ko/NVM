#ifndef CONTROLZERODLGMODEL_H
#define CONTROLZERODLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ControlZeroDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode            NOTIFY signalEventChangedAccessMode             )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test           NOTIFY signalEventChangedIsRS232Test            )
    Q_PROPERTY(int      mSensorOp                READ getSensorOp              NOTIFY signalEventChangedSensorOp               )
    Q_PROPERTY(int      mZeroEnable              READ getZeroEnable            NOTIFY signalEventChangedZeroEnable             )
    Q_PROPERTY(int      mPosPosition             READ getPosPosition           NOTIFY signalEventChangedPosPosition            )
    Q_PROPERTY(bool     mIsOpenedValve           READ getIsOpenedValve         NOTIFY signalEventChangedIsOpenedValve          )
    Q_PROPERTY(int      mSensor01Offset          READ getSensor01Offset        NOTIFY signalEventChangedSensor01Offset         )
    Q_PROPERTY(int      mSensor02Offset          READ getSensor02Offset        NOTIFY signalEventChangedSensor02Offset         )
    Q_PROPERTY(bool     mErrSensor01Offset       READ getErrSensor01Offset     NOTIFY signalEventChangedErrSensor01Offset      )
    Q_PROPERTY(bool     mErrSensor02Offset       READ getErrSensor02Offset     NOTIFY signalEventChangedErrSensor02Offset      )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                NOTIFY signalEventChangedIsEdit                 )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus             NOTIFY signalEventChangedStrStatus              )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                NOTIFY signalEventChangedErrMsg                 )
    Q_PROPERTY(QString  mErrMsg2                 READ getErrMsg2               NOTIFY signalEventChangedErrMsg2                )
    Q_PROPERTY(int      mProgress                READ getProgress              NOTIFY signalEventChangedProgress               )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test             = false;
    int     mSensorOp                = ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT;
    bool    mZeroEnable              = false;
    int     mPosPosition             = 0;
    bool    mIsOpenedValve           = false;
    int     mSensor01Offset          = 0;
    int     mSensor02Offset          = 0;
    bool    mErrSensor01Offset       = 0;
    bool    mErrSensor02Offset       = 0;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "ready";
    QString mErrMsg                  = "";
    QString mErrMsg2                 = "";
    int     mProgress                = 100 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    int     getSensorOp               (){ return mSensorOp               ;}
    bool    getZeroEnable             (){ return mZeroEnable             ;}
    int     getPosPosition            (){ return mPosPosition            ;}
    bool    getIsOpenedValve          (){ return mIsOpenedValve          ;}
    int     getSensor01Offset         (){ return mSensor01Offset         ;}
    int     getSensor02Offset         (){ return mSensor02Offset         ;}
    bool    getErrSensor01Offset      (){ return mErrSensor01Offset      ;}
    bool    getErrSensor02Offset      (){ return mErrSensor02Offset      ;}
    int     getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setSensorOp               (int     value){ if(mSensorOp                == value)return; mSensorOp                = value; emit signalEventChangedSensorOp               (value);}
    void    setZeroEnable             (bool    value){ if(mZeroEnable              == value)return; mZeroEnable              = value; emit signalEventChangedZeroEnable             (value);}
    void    setPosPosition            (int     value){ if(mPosPosition             == value)return; mPosPosition             = value; emit signalEventChangedPosPosition            (value);}
    void    setIsOpenedValve          (bool    value){ if(mIsOpenedValve           == value)return; mIsOpenedValve           = value; emit signalEventChangedIsOpenedValve          (value);}
    void    setSensor01Offset         (int     value){ if(mSensor01Offset          == value)return; mSensor01Offset          = value; emit signalEventChangedSensor01Offset         (value);}
    void    setSensor02Offset         (int     value){ if(mSensor02Offset          == value)return; mSensor02Offset          = value; emit signalEventChangedSensor02Offset         (value);}
    void    setErrSensor01Offset      (bool    value){ if(mErrSensor01Offset       == value)return; mErrSensor01Offset       = value; emit signalEventChangedErrSensor01Offset      (value);}
    void    setErrSensor02Offset      (bool    value){ if(mErrSensor02Offset       == value)return; mErrSensor02Offset       = value; emit signalEventChangedErrSensor02Offset      (value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedSensorOp               (int     value);
    void signalEventChangedZeroEnable             (bool    value);
    void signalEventChangedPosPosition            (int     value);
    void signalEventChangedIsOpenedValve          (bool    value);
    void signalEventChangedSensor01Offset         (int     value);
    void signalEventChangedSensor02Offset         (int     value);
    void signalEventChangedErrSensor01Offset      (bool    value);
    void signalEventChangedErrSensor02Offset      (bool    value);
    void signalEventChangedIsEdit                 (int     value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);

public:
    explicit ControlZeroDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_MODE;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_OP;
        ENABLE_SLOT_VALVE_CHANGED_CURR_POS;
        ENABLE_SLOT_VALVE_READED_SENSOR01_OFFSET;
        ENABLE_SLOT_VALVE_READED_SENSOR02_OFFSET;
        ENABLE_SLOT_VALVE_READED_SENSOR_CONFIG;
        ENABLE_SLOT_VALVE_WRITTEN_SENSOR_ZERO;
        ENABLE_SLOT_VALVE_WRITTEN_OPEN_POS;
        ENABLE_SLOT_VALVE_WRITTEN_SENSOR_CONFIG;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedSensorOperation();
        onValveChangedCurrPosition();
        onValveChangedMode();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        if(getSensorOp() == ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT)
            setState(eState::STATE_READ_S02);
        else
            setState(eState::STATE_READ_S01);
    }
    ~ControlZeroDlgModel()
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

    void onValveChangedSensorOperation()
    {
        setSensorOp(pValveSP->getSensorOperation());
    }

    void onValveChangedMode()
    {
        //setIsOpenedValve(pValveSP->getMode() == ValveEnumDef::MODE_OPEN);
    }

    void onValveChangedCurrPosition()
    {
        int posPosition = qFloor(((double)pValveSP->getCurrPosition() / 100000.0) * 100);
        setPosPosition(posPosition);

        setIsOpenedValve(pValveSP->getCurrPosition() == 100000);
    }

    void onValveReadedSensorConfig(ValveResponseSensorConfigDto dto)
    {
        if(mState != eState::STATE_READ_CONFIG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsSucc)
        {
            mSensorRatio = dto.mFullScaleRatio;
            setZeroEnable(dto.mZeroEnable);
            setState((eState)(mState + 1));
        }
        else
        {
            setState(mState);
            return;
        }
    }

    void onValveReadedSensor01Offset(ValveResponseSensorOffsetDto dto)
    {
        if(mState != eState::STATE_READ_S01 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        setErrSensor01Offset(!dto.mIsSucc);

        if(dto.mIsSucc)
        {
            setSensor01Offset(dto.mVoltage);
            setState((eState)(mState + 1));
        }
        else
        {
            setState((eState)(mState));
        }

        return;
    }

    void onValveReadedSensor02Offset(ValveResponseSensorOffsetDto dto)
    {
        if(mState != eState::STATE_READ_S02 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        setErrSensor02Offset(!dto.mIsSucc);

        if(dto.mIsSucc)
        {
            setSensor02Offset(dto.mVoltage);
            setState((eState)(mState + 1));
        }
        else
        {
            setState((eState)(mState));
        }

        return;
    }

    Q_INVOKABLE void onCommandOpenValve()
    {
        setState(eState::STATE_WRITE_OPEN_VALVE);
    }

    void onValveWrittenOpenPosition(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_OPEN_VALVE || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg2(dto.mErrMsg);

        setState(eState::STATE_READ_CONFIG);
    }

    Q_INVOKABLE void onCommandZero()
    {
        setState(eState::STATE_WRITE_ZERO);
    }

    void onValveWrittenSensorZero(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_ZERO || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg(dto.mErrMsg);

        setState(eState::STATE_READ_CONFIG);
    }

    Q_INVOKABLE void onCommandZeroEnable()
    {
        setState(eState::STATE_WRITE_ZERO_ENABLE);
    }

    void onValveWrittenSensorConfig(ValveResponseDto  dto)
    {
        if(mState != eState::STATE_WRITE_ZERO_ENABLE || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg(dto.mErrMsg);

        setState(eState::STATE_READ_CONFIG);
    }


private:
    enum eState{
        STATE_WRITE_OPEN_VALVE      = 0,
        STATE_WRITE_ZERO_ENABLE     = STATE_WRITE_OPEN_VALVE  + 1,
        STATE_WRITE_ZERO            = STATE_WRITE_ZERO_ENABLE + 1,
        STATE_READ_CONFIG           = STATE_WRITE_ZERO        + 1,
        STATE_READ_S01              = STATE_READ_CONFIG       + 1,
        STATE_READ_S02              = STATE_READ_S01          + 1,
        STATE_OVER                  = STATE_READ_S02          + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CONFIG;
    bool   mIsFirstRead   = true;
    qint64 mLastScanMSec  = 0;
    qint64 mSensorRatio   = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        qint64 currMSec;

        if(getSensorOp() == ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT && state == eState::STATE_READ_S01)
            state = STATE_READ_S02;
        else if(getSensorOp() == ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT && state == eState::STATE_READ_S02)
            state = STATE_OVER;

        if(state == eState::STATE_OVER)
        {
            state = eState::STATE_READ_CONFIG;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_S02));
        }
        else if(state == eState::STATE_READ_CONFIG)
        {
            currMSec = QDateTime::currentMSecsSinceEpoch();
            setStrStatus(QString("scan-rate %1 ms").arg(currMSec - mLastScanMSec));
            setProgress(100);
            mLastScanMSec = currMSec;
        }
        else if(state >= STATE_WRITE_OPEN_VALVE && state <= STATE_WRITE_ZERO)
        {
            setStrStatus("writting");
            setProgress(qFloor((state * 100) / eState::STATE_READ_S02));
        }

        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_S01:
            pValveSP->readSensor01Offset(this);
            break;

        case (int)eState::STATE_READ_S02:
            pValveSP->readSensor02Offset(this);
            break;

        case (int)eState::STATE_READ_CONFIG:
            pValveSP->readSensorConfig(this);
            break;

        case (int)eState::STATE_WRITE_OPEN_VALVE:
            pValveSP->openPosition(this);
            break;

        case (int)eState::STATE_WRITE_ZERO_ENABLE:
            pValveSP->setSensorConfig(mSensorOp, true, mSensorRatio, this);
            break;

        case (int)eState::STATE_WRITE_ZERO:
            pValveSP->setSensorZero(this);
            break;
        }
    }
};
#endif // CONTROLZERODLGMODEL_H
