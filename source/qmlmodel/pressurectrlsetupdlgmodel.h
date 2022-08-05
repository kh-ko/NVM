#ifndef PRESSURECTRLSETUPDLGMODEL_H
#define PRESSURECTRLSETUPDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class PressureCtrlSetupDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode        READ getAccessMode       NOTIFY signalEventChangedAccessMode      )
    Q_PROPERTY(bool     mIsRS232Test       READ getIsRS232Test      NOTIFY signalEventChangedIsRS232Test     )
    Q_PROPERTY(int      mControlMode       READ getControlMode      NOTIFY signalEventChangedControlMode     )
    Q_PROPERTY(int      mGainFactor        READ getGainFactor       NOTIFY signalEventChangedGainFactor      )
    Q_PROPERTY(int      mSensorDelay       READ getSensorDelay      NOTIFY signalEventChangedSensorDelay     )
    Q_PROPERTY(int      mRampTime          READ getRampTime         NOTIFY signalEventChangedRampTime        )
    Q_PROPERTY(bool     mErrValue          READ getErrValue         NOTIFY signalEventChangedErrValue        )
    Q_PROPERTY(bool     mIsEdit            READ getIsEdit           NOTIFY signalEventChangedIsEdit          )
    Q_PROPERTY(QString  mStrStatus         READ getStrStatus        NOTIFY signalEventChangedStrStatus       )
    Q_PROPERTY(QString  mErrMsg            READ getErrMsg           NOTIFY signalEventChangedErrMsg          )
    Q_PROPERTY(QString  mErrMsg2           READ getErrMsg2          NOTIFY signalEventChangedErrMsg2         )
    Q_PROPERTY(int      mProgress          READ getProgress         NOTIFY signalEventChangedProgress        )

public:
    int     mAccessMode        = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test       = false;
    int     mControlMode       = ValveEnumDef::PRESSURE_CTRL_ADAPTIVE;
    int     mGainFactor        = ValveEnumDef::PRESSURE_CTRL_GAIN_0_1;
    int     mSensorDelay       = ValveEnumDef::PRESSURE_CTRL_S_DELAY_0;
    int     mRampTime          = ValveEnumDef::PRESSURE_CTRL_RAMP_0;
    bool    mErrValue          = false;
    bool    mIsEdit            = false;
    QString mStrStatus         = "Loading";
    QString mErrMsg            = "";
    QString mErrMsg2           = "";
    int     mProgress          = 0 ;

    int     getAccessMode       (){ return mAccessMode       ; }
    bool    getIsRS232Test      (){ return mIsRS232Test      ;}
    int     getControlMode      (){ return mControlMode      ; }
    int     getGainFactor       (){ return mGainFactor       ; }
    int     getSensorDelay      (){ return mSensorDelay      ; }
    int     getRampTime         (){ return mRampTime         ; }
    bool    getErrValue         (){ return mErrValue         ; }
    bool    getIsEdit           (){ return mIsEdit           ; }
    QString getStrStatus        (){ return mStrStatus        ; }
    QString getErrMsg           (){ return mErrMsg           ; }
    QString getErrMsg2          (){ return mErrMsg2          ; }
    int     getProgress         (){ return mProgress         ; }

    void    setAccessMode       (int     value){ if(mAccessMode        == value)return; mAccessMode        = value; emit signalEventChangedAccessMode       (value);}
    void    setIsRS232Test      (bool    value){ if(mIsRS232Test       == value)return; mIsRS232Test       = value; emit signalEventChangedIsRS232Test      (value);}
    void    setControlMode      (int     value){ if(mControlMode       == value)return; mControlMode       = value; emit signalEventChangedControlMode      (value);}
    void    setGainFactor       (int     value){ if(mGainFactor        == value)return; mGainFactor        = value; emit signalEventChangedGainFactor       (value);}
    void    setSensorDelay      (int     value){ if(mSensorDelay       == value)return; mSensorDelay       = value; emit signalEventChangedSensorDelay      (value);}
    void    setRampTime         (int     value){ if(mRampTime          == value)return; mRampTime          = value; emit signalEventChangedRampTime         (value);}
    void    setErrValue         (bool    value){ if(mErrValue          == value)return; mErrValue          = value; emit signalEventChangedErrValue         (value);}
    void    setIsEdit           (bool    value){ if(mIsEdit            == value)return; mIsEdit            = value; emit signalEventChangedIsEdit           (value);}
    void    setStrStatus        (QString value){ if(mStrStatus         == value)return; mStrStatus         = value; emit signalEventChangedStrStatus        (value);}
    void    setErrMsg           (QString value){ if(mErrMsg            == value)return; mErrMsg            = value; emit signalEventChangedErrMsg           (value);}
    void    setErrMsg2          (QString value){ if(mErrMsg2           == value)return; mErrMsg2           = value; emit signalEventChangedErrMsg2          (value);}
    void    setProgress         (int     value){ if(mProgress          == value)return; mProgress          = value; emit signalEventChangedProgress         (value);}

signals:
    void signalEventChangedAccessMode       (int     value);
    void signalEventChangedIsRS232Test      (bool    value);
    void signalEventChangedControlMode      (int     value);
    void signalEventChangedGainFactor       (int     value);
    void signalEventChangedSensorDelay      (int     value);
    void signalEventChangedRampTime         (int     value);
    void signalEventChangedErrValue         (bool    value);
    void signalEventChangedIsEdit           (bool    value);
    void signalEventChangedStrStatus        (QString value);
    void signalEventChangedErrMsg           (QString value);
    void signalEventChangedErrMsg2          (QString value);
    void signalEventChangedProgress         (int     value);
    void signalEventCompletedLoad           (             );

public:
    explicit PressureCtrlSetupDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_PRESSURE_CTRL_CONFIG;
        ENABLE_SLOT_VALVE_WRITTEN_PRESSURE_CTRL_CONFIG;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ);
    }
    ~PressureCtrlSetupDlgModel()
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

    void onValveReadedPressureCtrlConfig (ValveResponsePressureCtrlConfigDto dto)
    {
        if(mState != eState::STATE_READ || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrValue((dto.mCtrlMode != mWriteControlMode) || (dto.mGainFactor != mWriteGainFac) || (dto.mSensorDelay != mWriteSensorDelay) || (dto.mRampTime != mWriteRampTime) );

            onCommandSetEdit(getErrValue());
        }
        else
        {
            setControlMode(dto.mCtrlMode   );
            setGainFactor (dto.mGainFactor );
            setSensorDelay(dto.mSensorDelay);
            setRampTime   (dto.mRampTime   );
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int controlMode, int gainFac, int sensorDelay, int rampTime)
    {
        mIsWritten       = true;

        mWriteControlMode = controlMode;
        mWriteGainFac     = gainFac    ;
        mWriteSensorDelay = sensorDelay;
        mWriteRampTime    = rampTime   ;
        setState(eState::STATE_WRITE);
    }

    void onValveWrittenPressureCtrlConfig(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg2(dto.mErrMsg);

        setState((eState)(mState + 1));
    }

private:
    enum eState{
        STATE_WRITE = 0,
        STATE_READ  = STATE_WRITE + 1,
        STATE_READY = STATE_READ  + 1,
    };

    QTimer mTimer;
    bool   mIsWritten     = false;
    eState mState         = eState::STATE_READ;

    int  mWriteControlMode;
    int  mWriteGainFac    ;
    int  mWriteSensorDelay;
    int  mWriteRampTime   ;

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

        if(state == STATE_READ)
        {
            setStrStatus("Loading");
        }
        else if(state == eState::STATE_WRITE)
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
        case (int)eState::STATE_READ:
            pValveSP->readPressureCtrlConfig(this);
            break;

        case (int)eState::STATE_WRITE:
            pValveSP->setPressureCtrlConfig(mWriteControlMode, mWriteGainFac, mWriteSensorDelay, mWriteRampTime, this);
            break;
        }
    }
};
#endif // PRESSURECTRLSETUPDLGMODEL_H
