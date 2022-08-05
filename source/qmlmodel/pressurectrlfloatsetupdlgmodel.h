#ifndef PRESSURECTRLFLOATSETUPDLGMODEL_H
#define PRESSURECTRLFLOATSETUPDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class PressureCtrlFloatSetupDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     mEnableDeltaFactor    READ getEnableDeltaFactor      NOTIFY signalEventChangedEnableDeltaFactor    )
    Q_PROPERTY(int      mAccessMode           READ getAccessMode             NOTIFY signalEventChangedAccessMode           )
    Q_PROPERTY(bool     mIsRS232Test          READ getIsRS232Test            NOTIFY signalEventChangedIsRS232Test          )
    Q_PROPERTY(int      mSelControl           READ getSelControl             NOTIFY signalEventChangedSelControl           )
    Q_PROPERTY(QString  mAdapGainFactor       READ getAdapGainFactor         NOTIFY signalEventChangedAdapGainFactor       )
    Q_PROPERTY(QString  mAdapDeltaFactor      READ getAdapDeltaFactor        NOTIFY signalEventChangedAdapDeltaFactor      )
    Q_PROPERTY(QString  mAdapSensorDelay      READ getAdapSensorDelay        NOTIFY signalEventChangedAdapSensorDelay      )
    Q_PROPERTY(QString  mAdapRampTime         READ getAdapRampTime           NOTIFY signalEventChangedAdapRampTime         )
    Q_PROPERTY(int      mAdapRampMode         READ getAdapRampMode           NOTIFY signalEventChangedAdapRampMode         )
    Q_PROPERTY(QString  mFixed1PGain          READ getFixed1PGain            NOTIFY signalEventChangedFixed1PGain          )
    Q_PROPERTY(QString  mFixed1IGain          READ getFixed1IGain            NOTIFY signalEventChangedFixed1IGain          )
    Q_PROPERTY(QString  mFixed1RampTime       READ getFixed1RampTime         NOTIFY signalEventChangedFixed1RampTime       )
    Q_PROPERTY(int      mFixed1RampMode       READ getFixed1RampMode         NOTIFY signalEventChangedFixed1RampMode       )
    Q_PROPERTY(int      mFixed1CtrlDir        READ getFixed1CtrlDir          NOTIFY signalEventChangedFixed1CtrlDir        )
    Q_PROPERTY(QString  mFixed2PGain          READ getFixed2PGain            NOTIFY signalEventChangedFixed2PGain          )
    Q_PROPERTY(QString  mFixed2IGain          READ getFixed2IGain            NOTIFY signalEventChangedFixed2IGain          )
    Q_PROPERTY(QString  mFixed2RampTime       READ getFixed2RampTime         NOTIFY signalEventChangedFixed2RampTime       )
    Q_PROPERTY(int      mFixed2RampMode       READ getFixed2RampMode         NOTIFY signalEventChangedFixed2RampMode       )
    Q_PROPERTY(int      mFixed2CtrlDir        READ getFixed2CtrlDir          NOTIFY signalEventChangedFixed2CtrlDir        )
    Q_PROPERTY(bool     mErrSelControl        READ getErrSelControl          NOTIFY signalEventChangedErrSelControl        )
    Q_PROPERTY(bool     mErrAdapGainFactor    READ getErrAdapGainFactor      NOTIFY signalEventChangedErrAdapGainFactor    )
    Q_PROPERTY(bool     mErrAdapDeltaFactor   READ getErrAdapDeltaFactor     NOTIFY signalEventChangedErrAdapDeltaFactor   )
    Q_PROPERTY(bool     mErrAdapSensorDelay   READ getErrAdapSensorDelay     NOTIFY signalEventChangedErrAdapSensorDelay   )
    Q_PROPERTY(bool     mErrAdapRampTime      READ getErrAdapRampTime        NOTIFY signalEventChangedErrAdapRampTime      )
    Q_PROPERTY(bool     mErrAdapRampMode      READ getErrAdapRampMode        NOTIFY signalEventChangedErrAdapRampMode      )
    Q_PROPERTY(bool     mErrFixed1PGain       READ getErrFixed1PGain         NOTIFY signalEventChangedErrFixed1PGain       )
    Q_PROPERTY(bool     mErrFixed1IGain       READ getErrFixed1IGain         NOTIFY signalEventChangedErrFixed1IGain       )
    Q_PROPERTY(bool     mErrFixed1RampTime    READ getErrFixed1RampTime      NOTIFY signalEventChangedErrFixed1RampTime    )
    Q_PROPERTY(bool     mErrFixed1RampMode    READ getErrFixed1RampMode      NOTIFY signalEventChangedErrFixed1RampMode    )
    Q_PROPERTY(bool     mErrFixed1CtrlDir     READ getErrFixed1CtrlDir       NOTIFY signalEventChangedErrFixed1CtrlDir     )
    Q_PROPERTY(bool     mErrFixed2PGain       READ getErrFixed2PGain         NOTIFY signalEventChangedErrFixed2PGain       )
    Q_PROPERTY(bool     mErrFixed2IGain       READ getErrFixed2IGain         NOTIFY signalEventChangedErrFixed2IGain       )
    Q_PROPERTY(bool     mErrFixed2RampTime    READ getErrFixed2RampTime      NOTIFY signalEventChangedErrFixed2RampTime    )
    Q_PROPERTY(bool     mErrFixed2RampMode    READ getErrFixed2RampMode      NOTIFY signalEventChangedErrFixed2RampMode    )
    Q_PROPERTY(bool     mErrFixed2CtrlDir     READ getErrFixed2CtrlDir       NOTIFY signalEventChangedErrFixed2CtrlDir     )
    Q_PROPERTY(bool     mIsEdit               READ getIsEdit                 NOTIFY signalEventChangedIsEdit               )
    Q_PROPERTY(QString  mStrStatus            READ getStrStatus              NOTIFY signalEventChangedStrStatus            )
    Q_PROPERTY(QString  mErrMsg               READ getErrMsg                 NOTIFY signalEventChangedErrMsg               )
    Q_PROPERTY(QString  mErrMsg2              READ getErrMsg2                NOTIFY signalEventChangedErrMsg2              )
    Q_PROPERTY(int      mProgress             READ getProgress               NOTIFY signalEventChangedProgress             )

public:
    bool     mEnableDeltaFactor   = false;
    int      mAccessMode          = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test         = false;
    int      mSelControl          = ValveEnumDef::PRESSURE_CTRL_ADAPTIVE;
    QString  mAdapGainFactor      ;
    QString  mAdapDeltaFactor     ;
    QString  mAdapSensorDelay     ;
    QString  mAdapRampTime        ;
    int      mAdapRampMode        ;
    QString  mFixed1PGain         ;
    QString  mFixed1IGain         ;
    QString  mFixed1RampTime      ;
    int      mFixed1RampMode      ;
    int      mFixed1CtrlDir       ;
    QString  mFixed2PGain         ;
    QString  mFixed2IGain         ;
    QString  mFixed2RampTime      ;
    int      mFixed2RampMode      ;
    int      mFixed2CtrlDir       ;
    bool     mErrSelControl       = false;
    bool     mErrAdapGainFactor   = false;
    bool     mErrAdapDeltaFactor  = false;
    bool     mErrAdapSensorDelay  = false;
    bool     mErrAdapRampTime     = false;
    bool     mErrAdapRampMode     = false;
    bool     mErrFixed1PGain      = false;
    bool     mErrFixed1IGain      = false;
    bool     mErrFixed1RampTime   = false;
    bool     mErrFixed1RampMode   = false;
    bool     mErrFixed1CtrlDir    = false;
    bool     mErrFixed2PGain      = false;
    bool     mErrFixed2IGain      = false;
    bool     mErrFixed2RampTime   = false;
    bool     mErrFixed2RampMode   = false;
    bool     mErrFixed2CtrlDir    = false;
    bool     mIsEdit              = false;
    QString  mStrStatus           = "Loading";
    QString  mErrMsg              = "";
    QString  mErrMsg2             = "";
    int      mProgress            = 0 ;

    bool     getEnableDeltaFactor  (){ return mEnableDeltaFactor  ;}
    int      getAccessMode         (){ return mAccessMode         ;}
    bool     getIsRS232Test        (){ return mIsRS232Test        ;}
    int      getSelControl         (){ return mSelControl         ;}
    QString  getAdapGainFactor     (){ return mAdapGainFactor     ;}
    QString  getAdapDeltaFactor    (){ return mAdapDeltaFactor    ;}
    QString  getAdapSensorDelay    (){ return mAdapSensorDelay    ;}
    QString  getAdapRampTime       (){ return mAdapRampTime       ;}
    int      getAdapRampMode       (){ return mAdapRampMode       ;}
    QString  getFixed1PGain        (){ return mFixed1PGain        ;}
    QString  getFixed1IGain        (){ return mFixed1IGain        ;}
    QString  getFixed1RampTime     (){ return mFixed1RampTime     ;}
    int      getFixed1RampMode     (){ return mFixed1RampMode     ;}
    int      getFixed1CtrlDir      (){ return mFixed1CtrlDir      ;}
    QString  getFixed2PGain        (){ return mFixed2PGain        ;}
    QString  getFixed2IGain        (){ return mFixed2IGain        ;}
    QString  getFixed2RampTime     (){ return mFixed2RampTime     ;}
    int      getFixed2RampMode     (){ return mFixed2RampMode     ;}
    int      getFixed2CtrlDir      (){ return mFixed2CtrlDir      ;}
    bool     getErrSelControl      (){ return mErrSelControl      ;}
    bool     getErrAdapGainFactor  (){ return mErrAdapGainFactor  ;}
    bool     getErrAdapDeltaFactor (){ return mErrAdapDeltaFactor ;}
    bool     getErrAdapSensorDelay (){ return mErrAdapSensorDelay ;}
    bool     getErrAdapRampTime    (){ return mErrAdapRampTime    ;}
    bool     getErrAdapRampMode    (){ return mErrAdapRampMode    ;}
    bool     getErrFixed1PGain     (){ return mErrFixed1PGain     ;}
    bool     getErrFixed1IGain     (){ return mErrFixed1IGain     ;}
    bool     getErrFixed1RampTime  (){ return mErrFixed1RampTime  ;}
    bool     getErrFixed1RampMode  (){ return mErrFixed1RampMode  ;}
    bool     getErrFixed1CtrlDir   (){ return mErrFixed1CtrlDir   ;}
    bool     getErrFixed2PGain     (){ return mErrFixed2PGain     ;}
    bool     getErrFixed2IGain     (){ return mErrFixed2IGain     ;}
    bool     getErrFixed2RampTime  (){ return mErrFixed2RampTime  ;}
    bool     getErrFixed2RampMode  (){ return mErrFixed2RampMode  ;}
    bool     getErrFixed2CtrlDir   (){ return mErrFixed2CtrlDir   ;}
    bool     getIsEdit             (){ return mIsEdit             ;}
    QString  getStrStatus          (){ return mStrStatus          ;}
    QString  getErrMsg             (){ return mErrMsg             ;}
    QString  getErrMsg2            (){ return mErrMsg2            ;}
    int      getProgress           (){ return mProgress           ;}

    void     setEnableDeltaFactor  (bool    value){ if(mEnableDeltaFactor   == value) return; mEnableDeltaFactor   = value; emit signalEventChangedEnableDeltaFactor  (value);}
    void     setAccessMode         (int     value){ if(mAccessMode          == value) return; mAccessMode          = value; emit signalEventChangedAccessMode         (value);}
    void     setIsRS232Test        (bool    value){ if(mIsRS232Test         == value)return; mIsRS232Test          = value; emit signalEventChangedIsRS232Test        (value);}
    void     setSelControl         (int     value){ if(mSelControl          == value) return; mSelControl          = value; emit signalEventChangedSelControl         (value);}
    void     setAdapGainFactor     (QString value){ if(mAdapGainFactor      == value) return; mAdapGainFactor      = value; emit signalEventChangedAdapGainFactor     (value);}
    void     setAdapDeltaFactor    (QString value){ if(mAdapDeltaFactor     == value) return; mAdapDeltaFactor     = value; emit signalEventChangedAdapDeltaFactor    (value);}
    void     setAdapSensorDelay    (QString value){ if(mAdapSensorDelay     == value) return; mAdapSensorDelay     = value; emit signalEventChangedAdapSensorDelay    (value);}
    void     setAdapRampTime       (QString value){ if(mAdapRampTime        == value) return; mAdapRampTime        = value; emit signalEventChangedAdapRampTime       (value);}
    void     setAdapRampMode       (int     value){ if(mAdapRampMode        == value) return; mAdapRampMode        = value; emit signalEventChangedAdapRampMode       (value);}
    void     setFixed1PGain        (QString value){ if(mFixed1PGain         == value) return; mFixed1PGain         = value; emit signalEventChangedFixed1PGain        (value);}
    void     setFixed1IGain        (QString value){ if(mFixed1IGain         == value) return; mFixed1IGain         = value; emit signalEventChangedFixed1IGain        (value);}
    void     setFixed1RampTime     (QString value){ if(mFixed1RampTime      == value) return; mFixed1RampTime      = value; emit signalEventChangedFixed1RampTime     (value);}
    void     setFixed1RampMode     (int     value){ if(mFixed1RampMode      == value) return; mFixed1RampMode      = value; emit signalEventChangedFixed1RampMode     (value);}
    void     setFixed1CtrlDir      (int     value){ if(mFixed1CtrlDir       == value) return; mFixed1CtrlDir       = value; emit signalEventChangedFixed1CtrlDir      (value);}
    void     setFixed2PGain        (QString value){ if(mFixed2PGain         == value) return; mFixed2PGain         = value; emit signalEventChangedFixed2PGain        (value);}
    void     setFixed2IGain        (QString value){ if(mFixed2IGain         == value) return; mFixed2IGain         = value; emit signalEventChangedFixed2IGain        (value);}
    void     setFixed2RampTime     (QString value){ if(mFixed2RampTime      == value) return; mFixed2RampTime      = value; emit signalEventChangedFixed2RampTime     (value);}
    void     setFixed2RampMode     (int     value){ if(mFixed2RampMode      == value) return; mFixed2RampMode      = value; emit signalEventChangedFixed2RampMode     (value);}
    void     setFixed2CtrlDir      (int     value){ if(mFixed2CtrlDir       == value) return; mFixed2CtrlDir       = value; emit signalEventChangedFixed2CtrlDir      (value);}
    void     setErrSelControl      (bool    value){ if(mErrSelControl       == value) return; mErrSelControl       = value; emit signalEventChangedErrSelControl      (value);}
    void     setErrAdapGainFactor  (bool    value){ if(mErrAdapGainFactor   == value) return; mErrAdapGainFactor   = value; emit signalEventChangedErrAdapGainFactor  (value);}
    void     setErrAdapDeltaFactor (bool    value){ if(mErrAdapDeltaFactor  == value) return; mErrAdapDeltaFactor  = value; emit signalEventChangedErrAdapDeltaFactor (value);}
    void     setErrAdapSensorDelay (bool    value){ if(mErrAdapSensorDelay  == value) return; mErrAdapSensorDelay  = value; emit signalEventChangedErrAdapSensorDelay (value);}
    void     setErrAdapRampTime    (bool    value){ if(mErrAdapRampTime     == value) return; mErrAdapRampTime     = value; emit signalEventChangedErrAdapRampTime    (value);}
    void     setErrAdapRampMode    (bool    value){ if(mErrAdapRampMode     == value) return; mErrAdapRampMode     = value; emit signalEventChangedErrAdapRampMode    (value);}
    void     setErrFixed1PGain     (bool    value){ if(mErrFixed1PGain      == value) return; mErrFixed1PGain      = value; emit signalEventChangedErrFixed1PGain     (value);}
    void     setErrFixed1IGain     (bool    value){ if(mErrFixed1IGain      == value) return; mErrFixed1IGain      = value; emit signalEventChangedErrFixed1IGain     (value);}
    void     setErrFixed1RampTime  (bool    value){ if(mErrFixed1RampTime   == value) return; mErrFixed1RampTime   = value; emit signalEventChangedErrFixed1RampTime  (value);}
    void     setErrFixed1RampMode  (bool    value){ if(mErrFixed1RampMode   == value) return; mErrFixed1RampMode   = value; emit signalEventChangedErrFixed1RampMode  (value);}
    void     setErrFixed1CtrlDir   (bool    value){ if(mErrFixed1CtrlDir    == value) return; mErrFixed1CtrlDir    = value; emit signalEventChangedErrFixed1CtrlDir   (value);}
    void     setErrFixed2PGain     (bool    value){ if(mErrFixed2PGain      == value) return; mErrFixed2PGain      = value; emit signalEventChangedErrFixed2PGain     (value);}
    void     setErrFixed2IGain     (bool    value){ if(mErrFixed2IGain      == value) return; mErrFixed2IGain      = value; emit signalEventChangedErrFixed2IGain     (value);}
    void     setErrFixed2RampTime  (bool    value){ if(mErrFixed2RampTime   == value) return; mErrFixed2RampTime   = value; emit signalEventChangedErrFixed2RampTime  (value);}
    void     setErrFixed2RampMode  (bool    value){ if(mErrFixed2RampMode   == value) return; mErrFixed2RampMode   = value; emit signalEventChangedErrFixed2RampMode  (value);}
    void     setErrFixed2CtrlDir   (bool    value){ if(mErrFixed2CtrlDir    == value) return; mErrFixed2CtrlDir    = value; emit signalEventChangedErrFixed2CtrlDir   (value);}
    void     setIsEdit             (bool    value){ if(mIsEdit              == value) return; mIsEdit              = value; emit signalEventChangedIsEdit             (value);}
    void     setStrStatus          (QString value){ if(mStrStatus           == value) return; mStrStatus           = value; emit signalEventChangedStrStatus          (value);}
    void     setErrMsg             (QString value){ if(mErrMsg              == value) return; mErrMsg              = value; emit signalEventChangedErrMsg             (value);}
    void     setErrMsg2            (QString value){ if(mErrMsg2             == value) return; mErrMsg2             = value; emit signalEventChangedErrMsg2            (value);}
    void     setProgress           (int     value){ if(mProgress            == value) return; mProgress            = value; emit signalEventChangedProgress           (value);}

signals:
    void signalEventChangedEnableDeltaFactor  (bool    value);
    void signalEventChangedAccessMode         (int     value);
    void signalEventChangedIsRS232Test        (bool    value);
    void signalEventChangedSelControl         (int     value);
    void signalEventChangedAdapGainFactor     (QString value);
    void signalEventChangedAdapDeltaFactor    (QString value);
    void signalEventChangedAdapSensorDelay    (QString value);
    void signalEventChangedAdapRampTime       (QString value);
    void signalEventChangedAdapRampMode       (int     value);
    void signalEventChangedFixed1PGain        (QString value);
    void signalEventChangedFixed1IGain        (QString value);
    void signalEventChangedFixed1RampTime     (QString value);
    void signalEventChangedFixed1RampMode     (int     value);
    void signalEventChangedFixed1CtrlDir      (int     value);
    void signalEventChangedFixed2PGain        (QString value);
    void signalEventChangedFixed2IGain        (QString value);
    void signalEventChangedFixed2RampTime     (QString value);
    void signalEventChangedFixed2RampMode     (int     value);
    void signalEventChangedFixed2CtrlDir      (int     value);
    void signalEventChangedErrSelControl      (bool    value);
    void signalEventChangedErrAdapGainFactor  (bool    value);
    void signalEventChangedErrAdapDeltaFactor (bool    value);
    void signalEventChangedErrAdapSensorDelay (bool    value);
    void signalEventChangedErrAdapRampTime    (bool    value);
    void signalEventChangedErrAdapRampMode    (bool    value);
    void signalEventChangedErrFixed1PGain     (bool    value);
    void signalEventChangedErrFixed1IGain     (bool    value);
    void signalEventChangedErrFixed1RampTime  (bool    value);
    void signalEventChangedErrFixed1RampMode  (bool    value);
    void signalEventChangedErrFixed1CtrlDir   (bool    value);
    void signalEventChangedErrFixed2PGain     (bool    value);
    void signalEventChangedErrFixed2IGain     (bool    value);
    void signalEventChangedErrFixed2RampTime  (bool    value);
    void signalEventChangedErrFixed2RampMode  (bool    value);
    void signalEventChangedErrFixed2CtrlDir   (bool    value);
    void signalEventChangedIsEdit             (bool    value);
    void signalEventChangedStrStatus          (QString value);
    void signalEventChangedErrMsg             (QString value);
    void signalEventChangedErrMsg2            (QString value);
    void signalEventChangedProgress           (int     value);
    void signalEventOccurErr                  (             );
    void signalEventCompletedLoad             (             );

public:
    explicit PressureCtrlFloatSetupDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_FIRMWARE_VER      ;
        ENABLE_SLOT_VALVE_READED_SEL_CONTROL_MODE   ;
        ENABLE_SLOT_VALVE_READED_ADAP_GAIN_FACTOR   ;
        ENABLE_SLOT_VALVE_READED_ADAP_DELTA_FACTOR  ;
        ENABLE_SLOT_VALVE_READED_ADAP_SENSOR_DELAY  ;
        ENABLE_SLOT_VALVE_READED_ADAP_RAMP_TIME     ;
        ENABLE_SLOT_VALVE_READED_ADAP_RAMP_MODE     ;
        ENABLE_SLOT_VALVE_READED_FIXED1_P_GAIN      ;
        ENABLE_SLOT_VALVE_READED_FIXED1_I_GAIN      ;
        ENABLE_SLOT_VALVE_READED_FIXED1_RAMP_TIME   ;
        ENABLE_SLOT_VALVE_READED_FIXED1_RAMP_MODE   ;
        ENABLE_SLOT_VALVE_READED_FIXED1_CTRL_DIR    ;
        ENABLE_SLOT_VALVE_READED_FIXED2_P_GAIN      ;
        ENABLE_SLOT_VALVE_READED_FIXED2_I_GAIN      ;
        ENABLE_SLOT_VALVE_READED_FIXED2_RAMP_TIME   ;
        ENABLE_SLOT_VALVE_READED_FIXED2_RAMP_MODE   ;
        ENABLE_SLOT_VALVE_READED_FIXED2_CTRL_DIR    ;
        ENABLE_SLOT_VALVE_WRITTEN_SEL_CONTROL_MODE  ;
        ENABLE_SLOT_VALVE_WRITTEN_ADAP_GAIN_FACTOR  ;
        ENABLE_SLOT_VALVE_WRITTEN_ADAP_DELTA_FACTOR ;
        ENABLE_SLOT_VALVE_WRITTEN_ADAP_SENSOR_DELAY ;
        ENABLE_SLOT_VALVE_WRITTEN_ADAP_RAMP_TIME    ;
        ENABLE_SLOT_VALVE_WRITTEN_ADAP_RAMP_MODE    ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED1_P_GAIN     ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED1_I_GAIN     ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED1_RAMP_TIME  ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED1_RAMP_MODE  ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED1_CTRL_DIR   ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED2_P_GAIN     ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED2_I_GAIN     ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED2_RAMP_TIME  ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED2_RAMP_MODE  ;
        ENABLE_SLOT_VALVE_WRITTEN_FIXED2_CTRL_DIR   ;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedFirmwareVersion();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_SEL_CONTROL);
    }
    ~PressureCtrlFloatSetupDlgModel()
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

    void onValveChangedFirmwareVersion()
    {
        bool result;
        setEnableDeltaFactor(pValveSP->getFirmwareVersion().toULongLong(&result, 16) > 0x2205260298);

        qDebug() << "[" << Q_FUNC_INFO << "] version = " <<  pValveSP->getFirmwareVersion();
    }

    void onValveReadedSelControlMode (ValveResponseSelControlModeDto dto)
    {
        if(mState != eState::STATE_READ_SEL_CONTROL || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc && !dto.mIsNetworkErr)
        {
            emit signalEventOccurErr();
            return;
        }

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrSelControl(dto.mCtrlMode != mWriteSelControl);
        }
        else
        {
            setSelControl(dto.mCtrlMode);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedAdapGainFactor(ValveResponseGainFactorDto dto)
    {
        if(mState != eState::STATE_READ_ADAP_GAIN_FACTOR || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {

            //setErrAdapGainFactor(dto.mGainFactor != mWriteAdapGainFactor);
            setErrAdapGainFactor(qAbs(dto.mGainFactor.toDouble() - mWriteAdapGainFactor.toDouble()) > 0.00001);
        }
        else
        {
            setAdapGainFactor(dto.mGainFactor);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedAdapDeltaFactor(ValveResponseDeltaFactorDto dto)
    {
        if(mState != eState::STATE_READ_ADAP_DELTA_FACTOR || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrAdapGainFactor(dto.mGainFactor != mWriteAdapGainFactor);
            setErrAdapDeltaFactor(qAbs(dto.mDeltaFactor.toDouble() - mWriteAdapDeltaFactor.toDouble()) > 0.00001);
        }
        else
        {
            setAdapDeltaFactor(dto.mDeltaFactor);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedAdapSensorDelay(ValveResponseSensorDelayDto dto)
    {
        if(mState != eState::STATE_READ_ADAP_SENSOR_DELAY || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrAdapSensorDelay(dto.mSensorDelay != mWriteAdapSensorDelay);
            setErrAdapSensorDelay(qAbs(dto.mSensorDelay.toDouble() - mWriteAdapSensorDelay.toDouble()) > 0.00001);
        }
        else
        {
            setAdapSensorDelay(dto.mSensorDelay);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedAdapRampTime(ValveResponseRampTimeDto dto)
    {
        if(mState != eState::STATE_READ_ADAP_RAMP_TIME || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrAdapRampTime(dto.mRampTime != mWriteAdapRampTime);
            setErrAdapRampTime(qAbs(dto.mRampTime.toDouble() - mWriteAdapRampTime.toDouble()) > 0.00001);
        }
        else
        {
            setAdapRampTime(dto.mRampTime);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedAdapRampMode(ValveResponseRampModeDto dto)
    {
        if(mState != eState::STATE_READ_ADAP_RAMP_MODE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrAdapRampMode(dto.mRampMode != mWriteAdapRampMode);
        }
        else
        {
            setAdapRampMode(dto.mRampMode);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed1PGain(ValveResponsePGainDto dto)
    {
        if(mState != eState::STATE_READ_FIXED1_P_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrFixed1PGain(dto.mPGain != mWriteFixed1PGain);
            setErrFixed1PGain(qAbs(dto.mPGain.toDouble() - mWriteFixed1PGain.toDouble()) > 0.00001);
        }
        else
        {
            setFixed1PGain(dto.mPGain);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed1IGain(ValveResponseIGainDto dto)
    {
        if(mState != eState::STATE_READ_FIXED1_I_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrFixed1IGain(dto.mIGain != mWriteFixed1IGain);
            setErrFixed1IGain(qAbs(dto.mIGain.toDouble() - mWriteFixed1IGain.toDouble()) > 0.00001);
        }
        else
        {
            setFixed1IGain(dto.mIGain);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed1RampTime(ValveResponseRampTimeDto dto)
    {
        if(mState != eState::STATE_READ_FIXED1_RAMP_TIME || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrFixed1RampTime(dto.mRampTime != mWriteFixed1RampTime);
            setErrFixed1RampTime(qAbs(dto.mRampTime.toDouble() - mWriteFixed1RampTime.toDouble()) > 0.00001);
        }
        else
        {
            setFixed1RampTime(dto.mRampTime);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed1RampMode(ValveResponseRampModeDto dto)
    {
        if(mState != eState::STATE_READ_FIXED1_RAMP_MODE|| dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrFixed1RampMode(dto.mRampMode != mWriteFixed1RampMode);
        }
        else
        {
            setFixed1RampMode(dto.mRampMode);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed1CtrlDir(ValveResponseCtrlDirDto dto)
    {
        if(mState != eState::STATE_READ_FIXED1_CTRL_DIR|| dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrFixed1CtrlDir(dto.mControlDir != mWriteFixed1CtrlDir);
        }
        else
        {
            setFixed1CtrlDir(dto.mControlDir);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed2PGain(ValveResponsePGainDto dto)
    {
        if(mState != eState::STATE_READ_FIXED2_P_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrFixed2PGain(dto.mPGain != mWriteFixed2PGain);
            setErrFixed2PGain(qAbs(dto.mPGain.toDouble() - mWriteFixed2PGain.toDouble()) > 0.00001);
        }
        else
        {
            setFixed2PGain(dto.mPGain);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed2IGain(ValveResponseIGainDto dto)
    {
        if(mState != eState::STATE_READ_FIXED2_I_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrFixed2IGain(dto.mIGain != mWriteFixed2IGain);
            setErrFixed2IGain(qAbs(dto.mIGain.toDouble() - mWriteFixed2IGain.toDouble()) > 0.00001);
        }
        else
        {
            setFixed2IGain(dto.mIGain);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed2RampTime(ValveResponseRampTimeDto dto)
    {
        if(mState != eState::STATE_READ_FIXED2_RAMP_TIME || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            //setErrFixed2RampTime(dto.mRampTime != mWriteFixed2RampTime);
            setErrFixed2RampTime(qAbs(dto.mRampTime.toDouble() - mWriteFixed2RampTime.toDouble()) > 0.00001);
        }
        else
        {
            setFixed2RampTime(dto.mRampTime);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed2RampMode(ValveResponseRampModeDto dto)
    {
        if(mState != eState::STATE_READ_FIXED2_RAMP_MODE|| dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrFixed2RampMode(dto.mRampMode != mWriteFixed2RampMode);
        }
        else
        {
            setFixed2RampMode(dto.mRampMode);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedFixed2CtrlDir(ValveResponseCtrlDirDto dto)
    {
        if(mState != eState::STATE_READ_FIXED2_CTRL_DIR|| dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrFixed2CtrlDir(dto.mControlDir != mWriteFixed2CtrlDir);

            onCommandSetEdit(getErrSelControl      () ||
                             getErrAdapGainFactor  () ||
                             getErrAdapDeltaFactor () ||
                             getErrAdapSensorDelay () ||
                             getErrAdapRampTime    () ||
                             getErrAdapRampMode    () ||
                             getErrFixed1PGain     () ||
                             getErrFixed1IGain     () ||
                             getErrFixed1RampTime  () ||
                             getErrFixed1RampMode  () ||
                             getErrFixed1CtrlDir   () ||
                             getErrFixed2PGain     () ||
                             getErrFixed2IGain     () ||
                             getErrFixed2RampTime  () ||
                             getErrFixed2RampMode  () ||
                             getErrFixed2CtrlDir   () );
        }
        else
        {
            setFixed2CtrlDir(dto.mControlDir);
        }

        setState((eState)(mState + 1));
    }


    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int     selControl      ,
                                    QString adapGainFactor  ,
                                    QString adapDeltaFactor ,
                                    QString adapSensorDelay ,
                                    QString adapRampTime    ,
                                    int     adapRampMode    ,
                                    QString fixed1PGain     ,
                                    QString fixed1IGain     ,
                                    QString fixed1RampTime  ,
                                    int     fixed1RampMode  ,
                                    int     fixed1CtrlDir   ,
                                    QString fixed2PGain     ,
                                    QString fixed2IGain     ,
                                    QString fixed2RampTime  ,
                                    int     fixed2RampMode  ,
                                    int     fixed2CtrlDir   )
    {
        mIsWritten       = true;

        mWriteSelControl       = selControl      ;
        mWriteAdapGainFactor   = adapGainFactor  ;
        mWriteAdapDeltaFactor  = adapDeltaFactor ;
        mWriteAdapSensorDelay  = adapSensorDelay ;
        mWriteAdapRampTime     = adapRampTime    ;
        mWriteAdapRampMode     = adapRampMode    ;
        mWriteFixed1PGain      = fixed1PGain     ;
        mWriteFixed1IGain      = fixed1IGain     ;
        mWriteFixed1RampTime   = fixed1RampTime  ;
        mWriteFixed1RampMode   = fixed1RampMode  ;
        mWriteFixed1CtrlDir    = fixed1CtrlDir   ;
        mWriteFixed2PGain      = fixed2PGain     ;
        mWriteFixed2IGain      = fixed2IGain     ;
        mWriteFixed2RampTime   = fixed2RampTime  ;
        mWriteFixed2RampMode   = fixed2RampMode  ;
        mWriteFixed2CtrlDir    = fixed2CtrlDir   ;

        setErrMsg2("");

        setState(eState::STATE_WRITE_SEL_CONTROL);
    }

    void onValveWrittenSelContrlMode(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_SEL_CONTROL || dto.mReqDto.mpRef != this)
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

    void onValveWrittenAdapGainFactor(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_ADAP_GAIN_FACTOR || dto.mReqDto.mpRef != this)
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

    void onValveWrittenAdapDeltaFactor(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_ADAP_DELTA_FACTOR || dto.mReqDto.mpRef != this)
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

    void onValveWrittenAdapSensorDelay(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_ADAP_SENSOR_DELAY || dto.mReqDto.mpRef != this)
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

    void onValveWrittenAdapRampTime(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_ADAP_RAMP_TIME|| dto.mReqDto.mpRef != this)
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

    void onValveWrittenAdapRampMode(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_ADAP_RAMP_MODE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed1PGain(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED1_P_GAIN || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed1IGain(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED1_I_GAIN || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed1RampTime(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED1_RAMP_TIME || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed1RampMode(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED1_RAMP_MODE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed1CtrlDir(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED1_CTRL_DIR || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed2PGain(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED2_P_GAIN || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed2IGain(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED2_I_GAIN || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed2RampTime(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED2_RAMP_TIME || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed2RampMode(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED2_RAMP_MODE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenFixed2CtrlDir(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_FIXED2_CTRL_DIR || dto.mReqDto.mpRef != this)
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
        STATE_WRITE_SEL_CONTROL         = 0,
        STATE_WRITE_ADAP_GAIN_FACTOR    = STATE_WRITE_SEL_CONTROL        + 1,
        STATE_WRITE_ADAP_DELTA_FACTOR   = STATE_WRITE_ADAP_GAIN_FACTOR   + 1,
        STATE_WRITE_ADAP_SENSOR_DELAY   = STATE_WRITE_ADAP_DELTA_FACTOR  + 1,
        STATE_WRITE_ADAP_RAMP_TIME      = STATE_WRITE_ADAP_SENSOR_DELAY  + 1,
        STATE_WRITE_ADAP_RAMP_MODE      = STATE_WRITE_ADAP_RAMP_TIME     + 1,
        STATE_WRITE_FIXED1_P_GAIN       = STATE_WRITE_ADAP_RAMP_MODE     + 1,
        STATE_WRITE_FIXED1_I_GAIN       = STATE_WRITE_FIXED1_P_GAIN      + 1,
        STATE_WRITE_FIXED1_RAMP_TIME    = STATE_WRITE_FIXED1_I_GAIN      + 1,
        STATE_WRITE_FIXED1_RAMP_MODE    = STATE_WRITE_FIXED1_RAMP_TIME   + 1,
        STATE_WRITE_FIXED1_CTRL_DIR     = STATE_WRITE_FIXED1_RAMP_MODE   + 1,
        STATE_WRITE_FIXED2_P_GAIN       = STATE_WRITE_FIXED1_CTRL_DIR    + 1,
        STATE_WRITE_FIXED2_I_GAIN       = STATE_WRITE_FIXED2_P_GAIN      + 1,
        STATE_WRITE_FIXED2_RAMP_TIME    = STATE_WRITE_FIXED2_I_GAIN      + 1,
        STATE_WRITE_FIXED2_RAMP_MODE    = STATE_WRITE_FIXED2_RAMP_TIME   + 1,
        STATE_WRITE_FIXED2_CTRL_DIR     = STATE_WRITE_FIXED2_RAMP_MODE   + 1,
        STATE_READ_SEL_CONTROL          = STATE_WRITE_FIXED2_CTRL_DIR    + 1,
        STATE_READ_ADAP_GAIN_FACTOR     = STATE_READ_SEL_CONTROL         + 1,
        STATE_READ_ADAP_DELTA_FACTOR    = STATE_READ_ADAP_GAIN_FACTOR    + 1,
        STATE_READ_ADAP_SENSOR_DELAY    = STATE_READ_ADAP_DELTA_FACTOR   + 1,
        STATE_READ_ADAP_RAMP_TIME       = STATE_READ_ADAP_SENSOR_DELAY   + 1,
        STATE_READ_ADAP_RAMP_MODE       = STATE_READ_ADAP_RAMP_TIME      + 1,
        STATE_READ_FIXED1_P_GAIN        = STATE_READ_ADAP_RAMP_MODE      + 1,
        STATE_READ_FIXED1_I_GAIN        = STATE_READ_FIXED1_P_GAIN       + 1,
        STATE_READ_FIXED1_RAMP_TIME     = STATE_READ_FIXED1_I_GAIN       + 1,
        STATE_READ_FIXED1_RAMP_MODE     = STATE_READ_FIXED1_RAMP_TIME    + 1,
        STATE_READ_FIXED1_CTRL_DIR      = STATE_READ_FIXED1_RAMP_MODE    + 1,
        STATE_READ_FIXED2_P_GAIN        = STATE_READ_FIXED1_CTRL_DIR     + 1,
        STATE_READ_FIXED2_I_GAIN        = STATE_READ_FIXED2_P_GAIN       + 1,
        STATE_READ_FIXED2_RAMP_TIME     = STATE_READ_FIXED2_I_GAIN       + 1,
        STATE_READ_FIXED2_RAMP_MODE     = STATE_READ_FIXED2_RAMP_TIME    + 1,
        STATE_READ_FIXED2_CTRL_DIR      = STATE_READ_FIXED2_RAMP_MODE    + 1,
        STATE_READY                     = STATE_READ_FIXED2_CTRL_DIR     + 1,
    };

    QTimer mTimer;
    bool   mIsWritten     = false;
    eState mState         = eState::STATE_READ_SEL_CONTROL;

    int     mWriteSelControl      ;
    QString mWriteAdapGainFactor  ;
    QString mWriteAdapDeltaFactor ;
    QString mWriteAdapSensorDelay ;
    QString mWriteAdapRampTime    ;
    int     mWriteAdapRampMode    ;
    QString mWriteFixed1PGain     ;
    QString mWriteFixed1IGain     ;
    QString mWriteFixed1RampTime  ;
    int     mWriteFixed1RampMode  ;
    int     mWriteFixed1CtrlDir   ;
    QString mWriteFixed2PGain     ;
    QString mWriteFixed2IGain     ;
    QString mWriteFixed2RampTime  ;
    int     mWriteFixed2RampMode  ;
    int     mWriteFixed2CtrlDir   ;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(70);
    }

    void setState(eState state)
    {
        if(!mIsWritten && state == eState::STATE_READY)
        {
            emit signalEventCompletedLoad();
        }

        mState = state;

        if((mState == STATE_READ_ADAP_DELTA_FACTOR || mState == STATE_WRITE_ADAP_DELTA_FACTOR) && mEnableDeltaFactor == false)
        {
            mState = (eState)(mState + 1);
        }

        if(state >= STATE_READ_SEL_CONTROL && state <= STATE_READ_FIXED2_CTRL_DIR)
        {
            setStrStatus("Loading");
        }
        else if(state >= STATE_WRITE_SEL_CONTROL && state <= STATE_WRITE_FIXED2_CTRL_DIR)
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
        case (int)STATE_WRITE_SEL_CONTROL       : pValveSP->setSelectControlMode(mWriteSelControl, this)               ;break;
        case (int)STATE_WRITE_ADAP_GAIN_FACTOR  : pValveSP->setAdaptiveControlGainFactor(mWriteAdapGainFactor, this)   ;break;
        case (int)STATE_WRITE_ADAP_DELTA_FACTOR : pValveSP->setAdaptiveControlDeltaFactor(mWriteAdapDeltaFactor, this) ;break;
        case (int)STATE_WRITE_ADAP_SENSOR_DELAY : pValveSP->setAdaptiveControlSensorDelay(mWriteAdapSensorDelay, this) ;break;
        case (int)STATE_WRITE_ADAP_RAMP_TIME    : pValveSP->setAdaptiveControlRampTime(mWriteAdapRampTime, this)       ;break;
        case (int)STATE_WRITE_ADAP_RAMP_MODE    : pValveSP->setAdaptiveControlRampMode(mWriteAdapRampMode, this)       ;break;
        case (int)STATE_WRITE_FIXED1_P_GAIN     : pValveSP->setFixed1ControlPGain(mWriteFixed1PGain, this)             ;break;
        case (int)STATE_WRITE_FIXED1_I_GAIN     : pValveSP->setFixed1ControlIGain(mWriteFixed1IGain, this)             ;break;
        case (int)STATE_WRITE_FIXED1_RAMP_TIME  : pValveSP->setFixed1ControlRampTime(mWriteFixed1RampTime, this)       ;break;
        case (int)STATE_WRITE_FIXED1_RAMP_MODE  : pValveSP->setFixed1ControlRampMode(mWriteFixed1RampMode, this)       ;break;
        case (int)STATE_WRITE_FIXED1_CTRL_DIR   : pValveSP->setFixed1ControlDirection(mWriteFixed1CtrlDir, this)       ;break;
        case (int)STATE_WRITE_FIXED2_P_GAIN     : pValveSP->setFixed2ControlPGain(mWriteFixed2PGain, this)             ;break;
        case (int)STATE_WRITE_FIXED2_I_GAIN     : pValveSP->setFixed2ControlIGain(mWriteFixed2IGain, this)             ;break;
        case (int)STATE_WRITE_FIXED2_RAMP_TIME  : pValveSP->setFixed2ControlRampTime(mWriteFixed2RampTime, this)       ;break;
        case (int)STATE_WRITE_FIXED2_RAMP_MODE  : pValveSP->setFixed2ControlRampMode(mWriteFixed2RampMode, this)       ;break;
        case (int)STATE_WRITE_FIXED2_CTRL_DIR   : pValveSP->setFixed2ControlDirection(mWriteFixed2CtrlDir, this)       ;break;

        case (int)STATE_READ_SEL_CONTROL        : pValveSP->readSelectControlMode(this)                                ;break;
        case (int)STATE_READ_ADAP_GAIN_FACTOR   : pValveSP->readAdaptiveControlGainFactor(this)                        ;break;
        case (int)STATE_READ_ADAP_DELTA_FACTOR  : pValveSP->readAdaptiveControlDeltaFactor(this)                       ;break;
        case (int)STATE_READ_ADAP_SENSOR_DELAY  : pValveSP->readAdaptiveControlSensorDelay(this)                       ;break;
        case (int)STATE_READ_ADAP_RAMP_TIME     : pValveSP->readAdaptiveControlRampTime(this)                          ;break;
        case (int)STATE_READ_ADAP_RAMP_MODE     : pValveSP->readAdaptiveControlRampMode(this)                          ;break;
        case (int)STATE_READ_FIXED1_P_GAIN      : pValveSP->readFixed1ControlPGain(this)                               ;break;
        case (int)STATE_READ_FIXED1_I_GAIN      : pValveSP->readFixed1ControlIGain(this)                               ;break;
        case (int)STATE_READ_FIXED1_RAMP_TIME   : pValveSP->readFixed1ControlRampTime(this)                            ;break;
        case (int)STATE_READ_FIXED1_RAMP_MODE   : pValveSP->readFixed1ControlRampMode(this)                            ;break;
        case (int)STATE_READ_FIXED1_CTRL_DIR    : pValveSP->readFixed1ControlDirection(this)                           ;break;
        case (int)STATE_READ_FIXED2_P_GAIN      : pValveSP->readFixed2ControlPGain(this)                               ;break;
        case (int)STATE_READ_FIXED2_I_GAIN      : pValveSP->readFixed2ControlIGain(this)                               ;break;
        case (int)STATE_READ_FIXED2_RAMP_TIME   : pValveSP->readFixed2ControlRampTime(this)                            ;break;
        case (int)STATE_READ_FIXED2_RAMP_MODE   : pValveSP->readFixed2ControlRampMode(this)                            ;break;
        case (int)STATE_READ_FIXED2_CTRL_DIR    : pValveSP->readFixed2ControlDirection(this)                           ;break;
        }
    }
};
#endif // PRESSURECTRLFLOATSETUPDLGMODEL_H
