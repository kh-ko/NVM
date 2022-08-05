#ifndef CONTROLLEARNDLGMODEL_H
#define CONTROLLEARNDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ControlLearnDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode               NOTIFY signalEventChangedAccessMode             )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test              NOTIFY signalEventChangedIsRS232Test            )
    Q_PROPERTY(int      mSensorFullScaleUnit     READ getSensorFullScaleUnit      NOTIFY signalEventChangedSensorFullScaleUnit    )
    Q_PROPERTY(double   mSensorFullScale         READ getSensorFullScale          NOTIFY signalEventChangedSensorFullScale        )
    Q_PROPERTY(int      mPressureLimit           READ getPressureLimit            NOTIFY signalEventChangedPressureLimit          )
    Q_PROPERTY(int      mRunning                 READ getRunning                  NOTIFY signalEventChangedRunning                )
    Q_PROPERTY(int      mDataSetPresent          READ getDataSetPresent           NOTIFY signalEventChangedDataSetPresent         )
    Q_PROPERTY(int      mAbort                   READ getAbort                    NOTIFY signalEventChangedAbort                  )
    Q_PROPERTY(int      mIsOKOpenPressure        READ getIsOKOpenPressure         NOTIFY signalEventChangedIsOKOpenPressure       )
    Q_PROPERTY(int      mIsOKClosePressure       READ getIsOKClosePressure        NOTIFY signalEventChangedIsOKClosePressure      )
    Q_PROPERTY(int      mPressureRaising         READ getPressureRaising          NOTIFY signalEventChangedPressureRaising        )
    Q_PROPERTY(int      mPressureStability       READ getPressureStability        NOTIFY signalEventChangedPressureStability      )
    Q_PROPERTY(bool     mIsShowState             READ getIsShowState              NOTIFY signalEventChangedIsShowState            )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                   NOTIFY signalEventChangedIsEdit                 )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus                NOTIFY signalEventChangedStrStatus              )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                   NOTIFY signalEventChangedErrMsg                 )
    Q_PROPERTY(QString  mErrMsg2                 READ getErrMsg2                  NOTIFY signalEventChangedErrMsg2                )
    Q_PROPERTY(int      mProgress                READ getProgress                 NOTIFY signalEventChangedProgress               )

public:
    int     mAccessMode          = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test         = false;
    int     mSensorFullScaleUnit = ValveEnumDef::PRESSURE_UNIT_TORR;
    double  mSensorFullScale     = 0;
    int     mPressureLimit       = 1000000;
    int     mRunning             = ValveEnumDef::LEARN_RUN_STATE_NOT_RUNNING;
    int     mDataSetPresent      = ValveEnumDef::LEARN_DATASET_NOT_PRESENT;
    int     mAbort               = ValveEnumDef::LEARN_ABORT_OK;
    int     mIsOKOpenPressure    = ValveEnumDef::LEARN_OPEN_PRESSURE_OK;
    int     mIsOKClosePressure   = ValveEnumDef::LEARN_CLOSE_PRESSURE_OK;
    int     mPressureRaising     = ValveEnumDef::LEARN_PRESSURE_RAISING_OK;
    int     mPressureStability   = ValveEnumDef::LEARN_PRESSURE_STABLE_OK;
    bool    mIsShowState         = false;
    bool    mIsEdit              = false;
    QString mStrStatus           = "";
    QString mErrMsg              = "";
    QString mErrMsg2             = "";
    int     mProgress            = 0 ;

    int     getAccessMode         (){return mAccessMode         ;}
    bool    getIsRS232Test        (){return mIsRS232Test        ;}
    int     getSensorFullScaleUnit(){return mSensorFullScaleUnit;}
    double  getSensorFullScale    (){return mSensorFullScale    ;}
    int     getPressureLimit      (){return mPressureLimit      ;}
    int     getRunning            (){return mRunning            ;}
    int     getDataSetPresent     (){return mDataSetPresent     ;}
    int     getAbort              (){return mAbort              ;}
    int     getIsOKOpenPressure   (){return mIsOKOpenPressure   ;}
    int     getIsOKClosePressure  (){return mIsOKClosePressure  ;}
    int     getPressureRaising    (){return mPressureRaising    ;}
    int     getPressureStability  (){return mPressureStability  ;}
    bool    getIsShowState        (){return mIsShowState        ;}
    bool    getIsEdit             (){return mIsEdit             ;}
    QString getStrStatus          (){return mStrStatus          ;}
    QString getErrMsg             (){return mErrMsg             ;}
    QString getErrMsg2            (){return mErrMsg2            ;}
    int     getProgress           (){return mProgress           ;}

    void    setAccessMode         (int     value){ if(mAccessMode              == value)return; mAccessMode          = value; emit signalEventChangedAccessMode               (value);}
    void    setIsRS232Test        (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test          = value; emit signalEventChangedIsRS232Test             (value);}
    void    setSensorFullScaleUnit(int     value){ if(mSensorFullScaleUnit     == value)return; mSensorFullScaleUnit = value; emit signalEventChangedSensorFullScaleUnit      (value);}
    void    setSensorFullScale    (double  value){ if(mSensorFullScale         == value)return; mSensorFullScale     = value; emit signalEventChangedSensorFullScale          (value);}
    void    setPressureLimit      (int     value){ if(mPressureLimit           == value)return; mPressureLimit       = value; emit signalEventChangedPressureLimit            (value);}
    void    setRunning            (int     value){ if(mRunning                 == value)return; mRunning             = value; emit signalEventChangedRunning                  (value);}
    void    setDataSetPresent     (int     value){ if(mDataSetPresent          == value)return; mDataSetPresent      = value; emit signalEventChangedDataSetPresent           (value);}
    void    setAbort              (int     value){ if(mAbort                   == value)return; mAbort               = value; emit signalEventChangedAbort                    (value);}
    void    setIsOKOpenPressure   (int     value){ if(mIsOKOpenPressure        == value)return; mIsOKOpenPressure    = value; emit signalEventChangedIsOKOpenPressure         (value);}
    void    setIsOKClosePressure  (int     value){ if(mIsOKClosePressure       == value)return; mIsOKClosePressure   = value; emit signalEventChangedIsOKClosePressure        (value);}
    void    setPressureRaising    (int     value){ if(mPressureRaising         == value)return; mPressureRaising     = value; emit signalEventChangedPressureRaising          (value);}
    void    setPressureStability  (int     value){ if(mPressureStability       == value)return; mPressureStability   = value; emit signalEventChangedPressureStability        (value);}
    void    setIsShowState        (bool    value){ if(mIsShowState             == value)return; mIsShowState         = value; emit signalEventChangedIsShowState              (value);}
    void    setIsEdit             (bool    value){ if(mIsEdit                  == value)return; mIsEdit              = value; emit signalEventChangedIsEdit                   (value);}
    void    setStrStatus          (QString value){ if(mStrStatus               == value)return; mStrStatus           = value; emit signalEventChangedStrStatus                (value);}
    void    setErrMsg             (QString value){ if(mErrMsg                  == value)return; mErrMsg              = value; emit signalEventChangedErrMsg                   (value);}
    void    setErrMsg2            (QString value){ if(mErrMsg2                 == value)return; mErrMsg2             = value; emit signalEventChangedErrMsg2                  (value);}
    void    setProgress           (int     value){ if(mProgress                == value)return; mProgress            = value; emit signalEventChangedProgress                 (value);}

signals:
    void signalEventChangedAccessMode          (int     value);
    void signalEventChangedIsRS232Test         (bool    value);
    void signalEventChangedSensorFullScaleUnit (int     value);
    void signalEventChangedSensorFullScale     (double  value);
    void signalEventChangedPressureLimit       (int     value);
    void signalEventChangedRunning             (int     value);
    void signalEventChangedDataSetPresent      (int     value);
    void signalEventChangedAbort               (int     value);
    void signalEventChangedIsOKOpenPressure    (int     value);
    void signalEventChangedIsOKClosePressure   (int     value);
    void signalEventChangedPressureRaising     (int     value);
    void signalEventChangedPressureStability   (int     value);
    void signalEventChangedIsShowState         (bool    value);
    void signalEventChangedIsEdit              (bool    value);
    void signalEventChangedStrStatus           (QString value);
    void signalEventChangedErrMsg              (QString value);
    void signalEventChangedErrMsg2             (QString value);
    void signalEventChangedProgress            (int     value);


public:
    explicit ControlLearnDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_S01_FULLSCALE;
        ENABLE_SLOT_VALVE_CHANGED_S02_FULLSCALE;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_OP;
        ENABLE_SLOT_VALVE_READED_LEARN_STATUS;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_RUN;
        ENABLE_SLOT_VALVE_WRITTEN_TARGET_POSITION;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedSensorOperation();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        //setState(eState::STATE_INIT);
    }
    ~ControlLearnDlgModel()
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

    void onValveChangedS01FullScale()
    {
        if(pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT && pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01)
        {
            return;
        }

        setSensorFullScale(pValveSP->getS01FullScale());
        setSensorFullScaleUnit(pValveSP->getS01SullScaleUnit());

    }
    void onValveChangedS02FullScale()
    {
        if(pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT && pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02)
        {
            return;
        }

        setSensorFullScale(pValveSP->getS02FullScale());
        setSensorFullScaleUnit(pValveSP->getS02SullScaleUnit());
    }
    void onValveChangedSensorOperation()
    {
        onValveChangedS01FullScale();
        onValveChangedS02FullScale();
    }

    void onValveReadedLearnStatus(ValveResponseLearnStatusDto dto)
    {
        bool isFinish = false;

        if((mState != eState::STATE_READ_STATUS && mState != eState::STATE_INIT) || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if((getRunning() == ValveEnumDef::LEARN_RUN_STATE_RUNNING && dto.mRunning == ValveEnumDef::LEARN_RUN_STATE_NOT_RUNNING) || (getIsShowState() && dto.mRunning == ValveEnumDef::LEARN_RUN_STATE_NOT_RUNNING ))
        {
            isFinish = true;
        }

        setLearnState(dto);

        if(dto.mRunning == ValveEnumDef::LEARN_RUN_STATE_RUNNING || isFinish)
            setIsShowState(true);

        if(isFinish)
            setState(STATE_FINISH);
        else if(dto.mRunning == ValveEnumDef::LEARN_RUN_STATE_RUNNING)
            setState(STATE_READ_STATUS);
        else if(mState == STATE_INIT)
            setState(STATE_READY);
    }

    Q_INVOKABLE void onCommandDlgOpened()
    {
        if(mState == STATE_NOT_INIT)
            setState(STATE_INIT);
    }

    Q_INVOKABLE void onCommandDlgClosed()
    {
        if(mState == STATE_FINISH)
            setState(STATE_READY);
    }

    Q_INVOKABLE void onCommandLearn(int pressureLimit)
    {
        mWritePressLimit = pressureLimit;
        setState(eState::STATE_WRITE_LEARN);
        setErrMsg2("");
    }

    void onValveWrittenLearnRun(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_LEARN  || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg2(dto.mErrMsg);

        if(dto.mIsSucc)
            setIsShowState(true);

        setState(eState::STATE_READ_STATUS);
    }

    Q_INVOKABLE void onCommandTerminateLearn()
    {
        setState(eState::STATE_WRITE_LEARN_TERMINATE);
        setErrMsg2("");
    }

    void onValveWrittenTargetPosition(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_LEARN_TERMINATE  || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg2(dto.mErrMsg);

        setState(eState::STATE_READ_STATUS);
    }

private:
    enum eState{
        STATE_NOT_INIT              = 0,
        STATE_INIT                  = STATE_NOT_INIT              + 1,
        STATE_READ_STATUS           = STATE_INIT                  + 1,
        STATE_WRITE_LEARN           = STATE_READ_STATUS           + 1,
        STATE_WRITE_LEARN_TERMINATE = STATE_WRITE_LEARN           + 1,
        STATE_FINISH                = STATE_WRITE_LEARN_TERMINATE + 1,
        STATE_READY                 = STATE_FINISH                + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_NOT_INIT;
    qint64 mLastScanMSec  = 0;

    int    mWritePressLimit = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setLearnState(ValveResponseLearnStatusDto dto)
    {
        setRunning          (dto.mRunning          );
        setDataSetPresent   (dto.mDataSetPresent   );
        setAbort            (dto.mAbort            );
        setIsOKOpenPressure (dto.mIsOKOpenPressure );
        setIsOKClosePressure(dto.mIsOKClosePressure);
        setPressureRaising  (dto.mPressureRaising  );
        setPressureStability(dto.mPressureStability);
    }
    void setState(eState state)
    {
        qint64 currMSec;//
        mState = state;

        switch ((int)state)
        {
        case eState::STATE_WRITE_LEARN:
            setStrStatus("writting");
            setProgress(0);
            startTimer();
            break;

        case eState::STATE_WRITE_LEARN_TERMINATE:
            setStrStatus("terminating");
            setProgress(0);
            startTimer();
            break;

        case eState::STATE_READ_STATUS:
            currMSec = QDateTime::currentMSecsSinceEpoch();
            setStrStatus(QString("scan-rate %1 ms").arg(currMSec - mLastScanMSec));
            mLastScanMSec = currMSec;
            setProgress(100);
            startTimer();
            break;

        case eState::STATE_FINISH:
            setProgress(100);
            setStrStatus("finished");
            break;

        case eState::STATE_INIT:
            currMSec = QDateTime::currentMSecsSinceEpoch();
            setStrStatus("loading");
            setIsShowState(false);
            mLastScanMSec = currMSec;
            setProgress(0);
            startTimer();
            break;

        case eState::STATE_READY:
            setProgress(100);
            setStrStatus("ready");
            setIsShowState(false);
            break;
        }
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case eState::STATE_INIT:
            pValveSP->readLearnStatus(this);
            break;

        case eState::STATE_READ_STATUS:
            pValveSP->readLearnStatus(this);
            break;

        case eState::STATE_WRITE_LEARN:
            pValveSP->learnRun(mWritePressLimit, this);
            break;

        case eState::STATE_WRITE_LEARN_TERMINATE:
            pValveSP->setTargetPosition(pValveSP->getCurrPosition(), this);
            break;
        }
    }
};
#endif // CONTROLLEARNDLGMODEL_H
