#ifndef QMLCOREMODEL_H
#define QMLCOREMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/fuactivekey.h"
#include "source/service/util/unitutil.h"
#include "source/service/util/mathutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"
#include "source/service/def/datetimeform.h"

class QmlCoreModel : public QObject
{
    Q_OBJECT
    // main view properties
    Q_PROPERTY(bool    mIsDevMode             READ getIsDevMode             NOTIFY signalEventChangedIsDevMode             )
    Q_PROPERTY(qint64  mStdFullScale          READ getStdFullScale          NOTIFY signalEventChangedStdFullScale          )
    Q_PROPERTY(double  mPressureConvertFactor READ getPressureConvertFactor NOTIFY signalEventChangedPressureConvertFactor )
    Q_PROPERTY(QString mNCPAVersion           READ getNCPAVersion           NOTIFY signalEventChangedNCPAVersion           )
    Q_PROPERTY(bool    mIsWithoutLogo         READ getIsWithoutLogo         NOTIFY signalEventChangedIsWithoutLogo         )
    Q_PROPERTY(int     mCompany               READ getCompany               NOTIFY signalEventChangedCompany               )
    Q_PROPERTY(bool    mIsValveConnect        READ getIsValeConnect         NOTIFY signalEventChangedIsValveConnect        )
    Q_PROPERTY(QString mErrMsg                READ getErrMsg                NOTIFY signalEventChangedErrMsg                )
    Q_PROPERTY(int     mLoadProgress          READ getLoadProgress          NOTIFY signalEventChangedLoadProgress          )
    Q_PROPERTY(QString mConnectionInfo        READ getConnectionInfo        NOTIFY signalEventChangedConnectionInfo        )
    Q_PROPERTY(QString mValveID               READ getValveID               NOTIFY signalEventChangedValveID               )
    Q_PROPERTY(QString mFirmwareVersion       READ getFirmwareVersion       NOTIFY signalEventChangedFirmwareVersion       )
    Q_PROPERTY(int     mInterface             READ getInterface             NOTIFY signalEventChangedInterface             )
    Q_PROPERTY(bool    mIsSupportPFO          READ getIsSupportPFO          NOTIFY signalEventChangedIsSupportPFO          )
    Q_PROPERTY(int     mSensorVersion         READ getSensorVersion         NOTIFY signalEventChangedSensorVersion         )
    Q_PROPERTY(int     mScanRate              READ getScanRate              NOTIFY signalEventChangedScanRate              )
    Q_PROPERTY(int     mAccess                READ getAccess                NOTIFY signalEventChangedAccess                )
    Q_PROPERTY(int     mMode                  READ getMode                  NOTIFY signalEventChangedMode                  )
    Q_PROPERTY(int     mControlMode           READ getControlMode           NOTIFY signalEventChangedControlMode           )
    Q_PROPERTY(qint64  mValveSpeed            READ getValveSpeed            NOTIFY signalEventChangedValveSpeed            )
    Q_PROPERTY(bool    mIsOpen                READ getIsOpen                NOTIFY signalEventChangedIsOpen                )
    Q_PROPERTY(bool    mIsClose               READ getIsClose               NOTIFY signalEventChangedIsClose               )
    Q_PROPERTY(qint64  mCurrPos               READ getCurrPos               NOTIFY signalEventChangedCurrPos               )
    Q_PROPERTY(qint64  mCurrPressure          READ getCurrPressure          NOTIFY signalEventChangedCurrPressure          )
    Q_PROPERTY(qint64  mTargetPos             READ getTargetPos             NOTIFY signalEventChangedTargetPos             )
    Q_PROPERTY(qint64  mTargetPressure        READ getTargetPressure        NOTIFY signalEventChangedTargetPressure        )
    Q_PROPERTY(qint64  mPosResolution         READ getPosResolution         NOTIFY signalEventChangedPosResolution         )
    Q_PROPERTY(int     mSensorOffset          READ getSensorOffset          NOTIFY signalEventChangedSensorOffset          )
    Q_PROPERTY(bool    mZeroEnable            READ getZeroEnable            NOTIFY signalEventChangedZeroEnable            )
    Q_PROPERTY(int     mFullScaleUnit         READ getFullScaleUnit         NOTIFY signalEventChangedFullScaleUnit         )
    Q_PROPERTY(double  mFullScale             READ getFullScale             NOTIFY signalEventChangedFullScale             )
    Q_PROPERTY(int     mPressureDpUnit        READ getPressureDpUnit        NOTIFY signalEventChangedPressureDpUnit        )
    Q_PROPERTY(int     mCtrlAlgo              READ getCtrlAlgo              NOTIFY signalEventChangedCtrlAlgo              )
    Q_PROPERTY(bool    mEnablePFO             READ getEnablePFO             NOTIFY signalEventChangedEnablePFO             )
    Q_PROPERTY(bool    mIsSimulation          READ getIsSimulation          NOTIFY signalEventChangedIsSimulation          )
    Q_PROPERTY(bool    mIsTestMode            READ getIsTestMode            NOTIFY signalEventChangedIsTestMode            )
    Q_PROPERTY(bool    mIsRS232Test           READ getIsRS232Test           NOTIFY signalEventChangedIsRS232Test           )
    Q_PROPERTY(bool    mFieldBusError         READ getFieldBusError         NOTIFY signalEventChangedFieldBusError         )
    Q_PROPERTY(bool    mIsSaving              READ getIsSaving              NOTIFY signalEventChangedIsSaving              )
    Q_PROPERTY(bool    mIsIDMissing           READ getIsIDMissing           NOTIFY signalEventChangedIsIDMissing           )
    Q_PROPERTY(bool    mIsPFOMissing          READ getIsPFOMissing          NOTIFY signalEventChangedIsPFOMissing          )
    Q_PROPERTY(bool    mFirmwareError         READ getFirmwareError         NOTIFY signalEventChangedFirmwareError         )
    Q_PROPERTY(bool    mUnknowInterface       READ getUnknowInterface       NOTIFY signalEventChangedUnknowInterface       )
    Q_PROPERTY(bool    mNoSensorSignal        READ getNoSensorSignal        NOTIFY signalEventChangedNoSensorSignal        )
    Q_PROPERTY(bool    mNoAnalogSignal        READ getNoAnalogSignal        NOTIFY signalEventChangedNoAnalogSignal        )
    Q_PROPERTY(bool    mNetworkFailure        READ getNetworkFailure        NOTIFY signalEventChangedNetworkFailure        )
    Q_PROPERTY(bool    mSlaveOffline          READ getSlaveOffline          NOTIFY signalEventChangedSlaveOffline          )
    Q_PROPERTY(bool    mIsolationValve        READ getIsolationValve        NOTIFY signalEventChangedIsolationValve        )
    Q_PROPERTY(bool    mSensorError           READ getSensorError           NOTIFY signalEventChangedSensorError           )
    Q_PROPERTY(bool    mSvcRequest            READ getSvcRequest            NOTIFY signalEventChangedSvcRequest            )
    Q_PROPERTY(bool    mLearnNotPresent       READ getLearnNotPresent       NOTIFY signalEventChangedLearnNotPresent       )
    Q_PROPERTY(bool    mAirNotReady           READ getAirNotReady           NOTIFY signalEventChangedAirNotReady           )
    Q_PROPERTY(bool    mPFONotReady           READ getPFONotReady           NOTIFY signalEventChangedPFONotReady           )
    Q_PROPERTY(bool    mIsCurrPosDraw         READ getIsCurrPosDraw         NOTIFY signalEventChangedIsCurrPosDraw         )
    Q_PROPERTY(bool    mIsCurrPressureDraw    READ getIsCurrPressureDraw    NOTIFY signalEventChangedIsCurrPressureDraw    )
    Q_PROPERTY(bool    mIsTargetPosDraw       READ getIsTargetPosDraw       NOTIFY signalEventChangedIsTargetPosDraw       )
    Q_PROPERTY(bool    mIsTargetPressureDraw  READ getIsTargetPressureDraw  NOTIFY signalEventChangedIsTargetPressureDraw  )
    Q_PROPERTY(bool    mIsPause               READ getIsPause               NOTIFY signalEventChangedIsPause               )
    Q_PROPERTY(int     mChartMSec             READ getChartMSec             NOTIFY signalEventChangedChartMSec             )
    Q_PROPERTY(bool    mIsPosAutoScaling      READ getIsPosAutoScaling      NOTIFY signalEventChangedIsPosAutoScaling      )
    Q_PROPERTY(bool    mIsPressureAutoScaling READ getIsPressureAutoScaling NOTIFY signalEventChangedIsPressureAutoScaling )
    Q_PROPERTY(bool    mIsPressureLogType     READ getIsPressureLogType     NOTIFY signalEventChangedIsPressureLogType     )
    Q_PROPERTY(int     mPressureDecades       READ getPressureDecades       NOTIFY signalEventChangedPressureDecades       )
    Q_PROPERTY(double  mMinMainPressureChart  READ getMinMainPressureChart  NOTIFY signalEventChangedMinMainPressureChart  )
    Q_PROPERTY(double  mMaxMainPressureChart  READ getMaxMainPressureChart  NOTIFY signalEventChangedMaxMainPressureChart  )
    Q_PROPERTY(int     mUserPressureFixedN    READ getUserPressureFixedN    NOTIFY signalEventChangedUserPressureFixedN    )
    Q_PROPERTY(int     mMinPressureFixedN     READ getMinPressureFixedN     NOTIFY signalEventChangedMinPressureFixedN     )
    Q_PROPERTY(double  mAutoScaleMinMargin    READ getAutoScaleMinMargin    NOTIFY signalEventChangedAutoScaleMinMargin    )
    Q_PROPERTY(double  mConvertedFullScale    READ getConvertedFullScale    NOTIFY signalEventChangedConvertedFullScale    )
    Q_PROPERTY(double  mConvertedTPressure    READ getConvertedTPressure    NOTIFY signalEventChangedConvertedTPressure    )
    Q_PROPERTY(double  mConvertedRTPressure   READ getConvertedRTPressure   NOTIFY signalEventChangedConvertedRTPressure   )
    Q_PROPERTY(double  mSetPoint01Position    READ getSetPoint01Position    NOTIFY signalEventChangedSetPoint01Position    )
    Q_PROPERTY(double  mSetPoint02Position    READ getSetPoint02Position    NOTIFY signalEventChangedSetPoint02Position    )
    Q_PROPERTY(double  mSetPoint03Position    READ getSetPoint03Position    NOTIFY signalEventChangedSetPoint03Position    )
    Q_PROPERTY(double  mSetPoint04Position    READ getSetPoint04Position    NOTIFY signalEventChangedSetPoint04Position    )
    Q_PROPERTY(double  mSetPoint05Position    READ getSetPoint05Position    NOTIFY signalEventChangedSetPoint05Position    )
    Q_PROPERTY(double  mSetPoint06Position    READ getSetPoint06Position    NOTIFY signalEventChangedSetPoint06Position    )
    Q_PROPERTY(double  mSetPoint01Pressure    READ getSetPoint01Pressure    NOTIFY signalEventChangedSetPoint01Pressure    )
    Q_PROPERTY(double  mSetPoint02Pressure    READ getSetPoint02Pressure    NOTIFY signalEventChangedSetPoint02Pressure    )
    Q_PROPERTY(double  mSetPoint03Pressure    READ getSetPoint03Pressure    NOTIFY signalEventChangedSetPoint03Pressure    )
    Q_PROPERTY(double  mSetPoint04Pressure    READ getSetPoint04Pressure    NOTIFY signalEventChangedSetPoint04Pressure    )
    Q_PROPERTY(double  mSetPoint05Pressure    READ getSetPoint05Pressure    NOTIFY signalEventChangedSetPoint05Pressure    )
    Q_PROPERTY(double  mSetPoint06Pressure    READ getSetPoint06Pressure    NOTIFY signalEventChangedSetPoint06Pressure    )
    Q_PROPERTY(int     mPressureFixedN        READ getPressureFixedN        NOTIFY signalEventChangedPressureFixedN        )
    Q_PROPERTY(bool    mIsRecord              READ getIsRecord              NOTIFY signalEventChangedIsRecord              )
    Q_PROPERTY(bool    mIsAutoRecord          READ getIsAutoRecord          NOTIFY signalEventChangedIsAutoRecord          )
    Q_PROPERTY(qint64  mRecordTime            READ getRecordTime            NOTIFY signalEventChangedRecordTime            )
    Q_PROPERTY(qint64  mAutoRecordTime        READ getAutoRecordTime        NOTIFY signalEventChangedAutoRecordTime        )


private:
    qint64        mConMSec                  ;
    qint64        mLastSaveTime             ;
    QList<qint64> mRecordTimestampList      ;
    QList<qint64> mRecordCurrentPosList     ;
    QList<qint64> mRecordTargetPosList      ;
    QList<qint64> mRecordCurrentPressureList;
    QList<qint64> mRecordTargetPressureList ;
    QList<qint64> mAutoRecordTimestampList      ;
    QList<qint64> mAutoRecordCurrentPosList     ;
    QList<qint64> mAutoRecordTargetPosList      ;
    QList<qint64> mAutoRecordCurrentPressureList;
    QList<qint64> mAutoRecordTargetPressureList ;

public:
    bool     mIsDevMode             = false                               ;
    qint64   mStdFullScale          = 1000000                             ;
    double   mPressureConvertFactor = 1                                   ;
    bool     mIsValveConnect        = false                               ;
    QString  mErrMsg                = ""                                  ;
    int      mLoadProgress          = 0                                   ;
    QString  mConnectionInfo        = ""                                  ;
    QString  mValveID               = ""                                  ;
    QString  mFirmwareVersion       = ""                                  ;
    int      mInterface             = ValveEnumDef::INTERFACE_LOGIC       ;
    bool     mIsSupportPFO          = false                               ;
    int      mSensorVersion         = 1                                   ;
    int      mScanRate              = 0                                   ;
    int      mAccess                = ValveEnumDef::ACCESS_REMOTE         ;
    int      mMode                  = ValveEnumDef::MODE_INIT             ;
    int      mControlMode           = ValveEnumDef::MODE_INIT             ;
    bool     mIsOpen                = false                               ;
    bool     mIsClose               = false                               ;
    qint64   mValveSpeed            = 0                                   ;
    qint64   mCurrPos               = 0                                   ;
    qint64   mCurrPressure          = 0                                   ;
    qint64   mTargetPos             = 0                                   ;
    qint64   mTargetPressure        = 0                                   ;
    qint64   mPosResolution         = 100                                 ;
    int      mSensorOffset          = 0                                   ;
    bool     mZeroEnable            = false                               ;
    int      mFullScaleUnit         = ValveEnumDef::PRESSURE_UNIT_TORR    ;
    double   mFullScale             = 1000                                ;
    int      mPressureDpUnit        = ValveEnumDef::PRESSURE_UNIT_TORR    ;
    int      mCtrlAlgo              = ValveEnumDef::PRESSURE_CTRL_ADAPTIVE;
    bool     mEnablePFO             = false                               ;
    bool     mIsSimulation          = false                               ;
    bool     mIsTestMode            = false                               ;
    bool     mIsRS232Test           = false                               ;
    bool     mFieldBusError         = false                               ;
    bool     mIsSaving              = false                               ;
    bool     mIsIDMissing           = false                               ;
    bool     mIsPFOMissing          = false                               ;
    bool     mFirmwareError         = false                               ;
    bool     mUnknowInterface       = false                               ;
    bool     mNoSensorSignal        = false                               ;
    bool     mNoAnalogSignal        = false                               ;
    bool     mNetworkFailure        = false                               ;
    bool     mSlaveOffline          = false                               ;
    bool     mIsolationValve        = false                               ;
    bool     mSensorError           = false                               ;
    bool     mSvcRequest            = false                               ;
    bool     mLearnNotPresent       = false                               ;
    bool     mAirNotReady           = false                               ;
    bool     mPFONotReady           = false                               ;
    bool     mIsCurrPosDraw         = true                                ;
    bool     mIsCurrPressureDraw    = true                                ;
    bool     mIsTargetPosDraw       = true                                ;
    bool     mIsTargetPressureDraw  = true                                ;
    bool     mIsPause               = false                               ;
    int      mChartMSec             = 30000                               ;
    bool     mIsPosAutoScaling      = false                               ;
    bool     mIsPressureAutoScaling = false                               ;
    bool     mIsPressureLogType     = false                               ;
    int      mPressureDecades       = 5                                   ;
    double   mMinMainPressureChart  = 0                                   ;
    double   mMaxMainPressureChart  = 1                                   ;
    double   mAutoScaleMinMargin    = 0.3f                                ;
    int      mUserPressureFixedN    = 0                                   ;
    int      mMinPressureFixedN     = 0                                   ;
    double   mConvertedFullScale    = 1000000                             ;
    double   mConvertedTPressure    = 0.0000001                           ;
    double   mConvertedRTPressure   = 0.0000001                           ;
    double   mSetPoint01Position    = 0;
    double   mSetPoint02Position    = 0;
    double   mSetPoint03Position    = 0;
    double   mSetPoint04Position    = 0;
    double   mSetPoint05Position    = 0;
    double   mSetPoint06Position    = 0;
    double   mSetPoint01Pressure    = 0;
    double   mSetPoint02Pressure    = 0;
    double   mSetPoint03Pressure    = 0;
    double   mSetPoint04Pressure    = 0;
    double   mSetPoint05Pressure    = 0;
    double   mSetPoint06Pressure    = 0;
    //int      mPressureFixedN        = 0                                   ;
    bool     mIsRecord              = false                               ;
    bool     mIsAutoRecord          = false                               ;
    qint64   mRecordStartTime       = 0                                   ;
    qint64   mRecordCurrTime        = 0                                   ;
    qint64   mAutoRecordStartTime   = 0                                   ;
    qint64   mAutoRecordCurrTime    = 0                                   ;


    bool    getIsDevMode            (){ return mIsDevMode                ;}
    qint64  getStdFullScale         (){ return mStdFullScale             ;}
    double  getPressureConvertFactor(){ return mPressureConvertFactor    ;}
    QString getNCPAVersion          (){ return pLSettingSP->mBuildVersion;}
    bool    getIsWithoutLogo        (){ return pLSettingSP->mIsWithoutLogo;}
    int     getCompany              (){ return pLSettingSP->mCompany     ;}
    bool    getIsValeConnect        (){ return mIsValveConnect           ;}
    QString getErrMsg               (){ return mErrMsg                   ;}
    int     getLoadProgress         (){ return mLoadProgress             ;}
    QString getConnectionInfo       (){ return mConnectionInfo           ;}
    QString getValveID              (){ return mValveID                  ;}
    QString getFirmwareVersion      (){ return mFirmwareVersion          ;}
    int     getInterface            (){ return mInterface                ;}
    int     getIsSupportPFO         (){ return mIsSupportPFO             ;}
    int     getSensorVersion        (){ return mSensorVersion            ;}
    int     getScanRate             (){ return mScanRate                 ;}
    int     getAccess               (){ return mAccess                   ;}
    int     getMode                 (){ return mMode                     ;}
    int     getControlMode          (){ return mControlMode              ;}
    bool    getIsOpen               (){ return mIsOpen                   ;}
    bool    getIsClose              (){ return mIsClose                  ;}
    qint64  getValveSpeed           (){ return mValveSpeed               ;}
    qint64  getCurrPos              (){ return mCurrPos                  ;}
    qint64  getCurrPressure         (){ return mCurrPressure             ;}
    qint64  getTargetPos            (){ return mTargetPos                ;}
    qint64  getTargetPressure       (){ return mTargetPressure           ;}
    qint64  getPosResolution        (){ return mPosResolution            ;}
    int     getSensorOffset         (){ return mSensorOffset             ;}
    bool    getZeroEnable           (){ return mZeroEnable               ;}
    int     getFullScaleUnit        (){ return mFullScaleUnit            ;}
    double  getFullScale            (){ return mFullScale                ;}
    int     getPressureDpUnit       (){ return mPressureDpUnit           ;}
    int     getCtrlAlgo             (){ return mCtrlAlgo                 ;}
    bool    getEnablePFO            (){ return mEnablePFO                ;}
    bool    getIsSimulation         (){ return mIsSimulation             ;}
    bool    getIsTestMode           (){ return mIsTestMode               ;}
    bool    getIsRS232Test          (){ return mIsRS232Test              ;}
    bool    getFieldBusError        (){ return mFieldBusError            ;}
    bool    getIsSaving             (){ return mIsSaving                 ;}
    bool    getIsIDMissing          (){ return mIsIDMissing              ;}
    bool    getIsPFOMissing         (){ return mIsPFOMissing             ;}
    bool    getFirmwareError        (){ return mFirmwareError            ;}
    bool    getUnknowInterface      (){ return mUnknowInterface          ;}
    bool    getNoSensorSignal       (){ return mNoSensorSignal           ;}
    bool    getNoAnalogSignal       (){ return mNoAnalogSignal           ;}
    bool    getNetworkFailure       (){ return mNetworkFailure           ;}
    bool    getSlaveOffline         (){ return mSlaveOffline             ;}
    bool    getIsolationValve       (){ return mIsolationValve           ;}
    bool    getSensorError          (){ return mSensorError              ;}
    bool    getSvcRequest           (){ return mSvcRequest               ;}
    bool    getLearnNotPresent      (){ return mLearnNotPresent          ;}
    bool    getAirNotReady          (){ return mAirNotReady              ;}
    bool    getPFONotReady          (){ return mPFONotReady              ;}
    bool    getIsCurrPosDraw        (){ return mIsCurrPosDraw            ;}
    bool    getIsCurrPressureDraw   (){ return mIsCurrPressureDraw       ;}
    bool    getIsTargetPosDraw      (){ return mIsTargetPosDraw          ;}
    bool    getIsTargetPressureDraw (){ return mIsTargetPressureDraw     ;}
    bool    getIsPause              (){ return mIsPause                  ;}
    int     getChartMSec            (){ return mChartMSec                ;}
    bool    getIsPosAutoScaling     (){ return mIsPosAutoScaling         ;}
    bool    getIsPressureAutoScaling(){ return mIsPressureAutoScaling    ;}
    bool    getIsPressureLogType    (){ return mIsPressureLogType        ;}
    int     getPressureDecades      (){ return mPressureDecades          ;}
    double  getMinMainPressureChart (){ return mMinMainPressureChart     ;}
    double  getMaxMainPressureChart (){ return mMaxMainPressureChart     ;}
    double  getAutoScaleMinMargin   (){ return mAutoScaleMinMargin       ;}
    int     getUserPressureFixedN   (){ return mUserPressureFixedN       ;}
    int     getMinPressureFixedN    (){ return mMinPressureFixedN        ;}
    double  getConvertedFullScale   (){ return mConvertedFullScale       ;}
    double  getConvertedTPressure   (){ return mConvertedTPressure       ;}
    double  getConvertedRTPressure  (){ return mConvertedRTPressure      ;}
    double  getSetPoint01Position   (){ return mSetPoint01Position       ;}
    double  getSetPoint02Position   (){ return mSetPoint02Position       ;}
    double  getSetPoint03Position   (){ return mSetPoint03Position       ;}
    double  getSetPoint04Position   (){ return mSetPoint04Position       ;}
    double  getSetPoint05Position   (){ return mSetPoint05Position       ;}
    double  getSetPoint06Position   (){ return mSetPoint06Position       ;}
    double  getSetPoint01Pressure   (){ return mSetPoint01Pressure       ;}
    double  getSetPoint02Pressure   (){ return mSetPoint02Pressure       ;}
    double  getSetPoint03Pressure   (){ return mSetPoint03Pressure       ;}
    double  getSetPoint04Pressure   (){ return mSetPoint04Pressure       ;}
    double  getSetPoint05Pressure   (){ return mSetPoint05Pressure       ;}
    double  getSetPoint06Pressure   (){ return mSetPoint06Pressure       ;}
    int     getPressureFixedN       (){ return mMinPressureFixedN > mUserPressureFixedN? mMinPressureFixedN : mUserPressureFixedN;}
    bool    getIsRecord             (){ return mIsRecord                 ;}
    bool    getIsAutoRecord         (){ return mIsAutoRecord             ;}
    qint64  getRecordTime           (){ return (mRecordCurrTime - mRecordStartTime);}
    qint64  getAutoRecordTime       (){ return (mAutoRecordCurrTime - mAutoRecordStartTime);}

    void setIsDevMode            (bool              value){ if(mIsDevMode             == value) return; mIsDevMode             = value; emit signalEventChangedIsDevMode            (value);}
    void setStdFullScale         (qint64            value){ if(mStdFullScale          == value) return; mStdFullScale          = value; emit signalEventChangedStdFullScale         (value);}
    void setPressureConvertFactor(double            value){ if(mPressureConvertFactor == value) return; mPressureConvertFactor = value; emit signalEventChangedPressureConvertFactor(value);}
    void setIsValeConnect        (bool              value){ if(mIsValveConnect        == value) return; mIsValveConnect        = value; emit signalEventChangedIsValveConnect       (value);}
    void setErrMsg               (QString           value){ if(mErrMsg                == value) return; mErrMsg                = value; emit signalEventChangedErrMsg               (value);}
    void setLoadProgress         (int               value){ if(mLoadProgress          == value) return; mLoadProgress          = value; emit signalEventChangedLoadProgress         (value);}
    void setConnectionInfo       (QString           value){ if(mConnectionInfo        == value) return; mConnectionInfo        = value; emit signalEventChangedConnectionInfo       (value);}
    void setValveID              (QString           value){ if(mValveID               == value) return; mValveID               = value; emit signalEventChangedValveID              (value);}
    void setFirmwareVersion      (QString           value){ if(mFirmwareVersion       == value) return; mFirmwareVersion       = value; emit signalEventChangedFirmwareVersion      (value);}
    void setInterface            (int               value){ if(mInterface             == value) return; mInterface             = value; emit signalEventChangedInterface            (value);}
    void setIsSupportPFO         (bool              value){ if(mIsSupportPFO          == value) return; mIsSupportPFO          = value; emit signalEventChangedIsSupportPFO         (value);}
    void setSensorVersion        (int               value){ if(mSensorVersion         == value) return; mSensorVersion         = value; emit signalEventChangedSensorVersion        (value);}
    void setScanRate             (int               value){ if(mScanRate              == value) return; mScanRate              = value; emit signalEventChangedScanRate             (value);}
    void setAccess               (int               value){ if(mAccess                == value) return; mAccess                = value; emit signalEventChangedAccess               (value);}
    void setMode                 (int               value){ if(mMode                  == value) return; mMode                  = value; emit signalEventChangedMode                 (value);}
    void setControlMode          (int               value){ if(mControlMode           == value) return; mControlMode           = value; emit signalEventChangedControlMode          (value);}
    void setIsOpen               (bool              value){ if(mIsOpen                == value) return; mIsOpen                = value; emit signalEventChangedIsOpen               (value);}
    void setIsClose              (bool              value){ if(mIsClose               == value) return; mIsClose               = value; emit signalEventChangedIsClose              (value);}
    void setValveSpeed           (qint64            value){ if(mValveSpeed            == value) return; mValveSpeed            = value; emit signalEventChangedValveSpeed           (value);}
    void setCurrPos              (qint64            value){ if(mCurrPos               == value) return; mCurrPos               = value; emit signalEventChangedCurrPos              (value);}
    void setCurrPressure         (qint64            value){ if(mCurrPressure          == value) return; mCurrPressure          = value; emit signalEventChangedCurrPressure         (value);}
    void setTargetPos            (qint64            value){ if(mTargetPos             == value) return; mTargetPos             = value; emit signalEventChangedTargetPos            (value);}
    void setTargetPressure       (qint64            value){ if(mTargetPressure        == value) return; mTargetPressure        = value; emit signalEventChangedTargetPressure       (value);}
    void setPosResolution        (qint64            value){ if(mPosResolution         == value) return; mPosResolution         = value; emit signalEventChangedPosResolution        (value);}
    void setSensorOffset         (int               value){ if(mSensorOffset          == value) return; mSensorOffset          = value; emit signalEventChangedSensorOffset         (value);}
    void setZeroEnable           (bool              value){ if(mZeroEnable            == value) return; mZeroEnable            = value; emit signalEventChangedZeroEnable           (value);}
    void setPressureDpUnit       (int               value){ if(mPressureDpUnit        == value) return; mPressureDpUnit        = value; emit signalEventChangedPressureDpUnit       (value);}
    void setCtrlAlgo             (int               value){ if(mCtrlAlgo              == value) return; mCtrlAlgo              = value; emit signalEventChangedCtrlAlgo             (value);}
    void setEnablePFO            (bool              value){ if(mEnablePFO             == value) return; mEnablePFO             = value; emit signalEventChangedEnablePFO            (value);}
    void setIsSimulation         (bool              value){ if(mIsSimulation          == value) return; mIsSimulation          = value; emit signalEventChangedIsSimulation         (value);}
    void setIsTestMode           (bool              value){ if(mIsTestMode            == value) return; mIsTestMode            = value; emit signalEventChangedIsTestMode           (value);}
    void setIsRS232Test          (bool              value){ if(mIsRS232Test           == value) return; mIsRS232Test           = value; emit signalEventChangedIsRS232Test          (value);}
    void setFieldBusError        (bool              value){ if(mFieldBusError         == value) return; mFieldBusError         = value; emit signalEventChangedFieldBusError        (value);}
    void setIsSaving             (bool              value){ if(mIsSaving              == value) return; mIsSaving              = value; emit signalEventChangedIsSaving             (value);}
    void setIsIDMissing          (bool              value){ if(mIsIDMissing           == value) return; mIsIDMissing           = value; emit signalEventChangedIsIDMissing          (value);}
    void setIsPFOMissing         (bool              value){ if(mIsPFOMissing          == value) return; mIsPFOMissing          = value; emit signalEventChangedIsPFOMissing         (value);}
    void setFirmwareError        (bool              value){ if(mFirmwareError         == value) return; mFirmwareError         = value; emit signalEventChangedFirmwareError        (value);}
    void setUnknowInterface      (bool              value){ if(mUnknowInterface       == value) return; mUnknowInterface       = value; emit signalEventChangedUnknowInterface      (value);}
    void setNoSensorSignal       (bool              value){ if(mNoSensorSignal        == value) return; mNoSensorSignal        = value; emit signalEventChangedNoSensorSignal       (value);}
    void setNoAnalogSignal       (bool              value){ if(mNoAnalogSignal        == value) return; mNoAnalogSignal        = value; emit signalEventChangedNoAnalogSignal       (value);}
    void setNetworkFailure       (bool              value){ if(mNetworkFailure        == value) return; mNetworkFailure        = value; emit signalEventChangedNetworkFailure       (value);}
    void setSlaveOffline         (bool              value){ if(mSlaveOffline          == value) return; mSlaveOffline          = value; emit signalEventChangedSlaveOffline         (value);}
    void setIsolationValve       (bool              value){ if(mIsolationValve        == value) return; mIsolationValve        = value; emit signalEventChangedIsolationValve       (value);}
    void setSensorError          (bool              value){ if(mSensorError           == value) return; mSensorError           = value; emit signalEventChangedSensorError          (value);}
    void setSvcRequest           (bool              value){ if(mSvcRequest            == value) return; mSvcRequest            = value; emit signalEventChangedSvcRequest           (value);}
    void setLearnNotPresent      (bool              value){ if(mLearnNotPresent       == value) return; mLearnNotPresent       = value; emit signalEventChangedLearnNotPresent      (value);}
    void setAirNotReady          (bool              value){ if(mAirNotReady           == value) return; mAirNotReady           = value; emit signalEventChangedAirNotReady          (value);}
    void setPFONotReady          (bool              value){ if(mPFONotReady           == value) return; mPFONotReady           = value; emit signalEventChangedPFONotReady          (value);}
    void setIsCurrPosDraw        (bool              value){ if(mIsCurrPosDraw         == value) return; mIsCurrPosDraw         = value; emit signalEventChangedIsCurrPosDraw        (value);}
    void setIsCurrPressureDraw   (bool              value){ if(mIsCurrPressureDraw    == value) return; mIsCurrPressureDraw    = value; emit signalEventChangedIsCurrPressureDraw   (value);}
    void setIsTargetPosDraw      (bool              value){ if(mIsTargetPosDraw       == value) return; mIsTargetPosDraw       = value; emit signalEventChangedIsTargetPosDraw      (value);}
    void setIsTargetPressureDraw (bool              value){ if(mIsTargetPressureDraw  == value) return; mIsTargetPressureDraw  = value; emit signalEventChangedIsTargetPressureDraw (value);}
    void setIsPause              (bool              value){ if(mIsPause               == value) return; mIsPause               = value; emit signalEventChangedIsPause              (value);}
    void setChartMSec            (int               value){ if(mChartMSec             == value) return; mChartMSec             = value; emit signalEventChangedChartMSec            (value);}
    void setIsPosAutoScaling     (bool              value){ if(mIsPosAutoScaling      == value) return; mIsPosAutoScaling      = value; emit signalEventChangedIsPosAutoScaling     (value);}
    void setIsPressureAutoScaling(bool              value){ if(mIsPressureAutoScaling == value) return; mIsPressureAutoScaling = value; emit signalEventChangedIsPressureAutoScaling(value);}
    void setIsPressureLogType    (bool              value){ if(mIsPressureLogType     == value) return; mIsPressureLogType     = value; emit signalEventChangedIsPressureLogType    (value);}
    void setPressureDecades      (int               value){ if(mPressureDecades       == value) return; mPressureDecades       = value; emit signalEventChangedPressureDecades      (value);}
    void setMinMainPressureChart (double            value){ if(mMinMainPressureChart  == value) return; mMinMainPressureChart  = value; emit signalEventChangedMinMainPressureChart (value);}
    void setMaxMainPressureChart (double            value){ if(mMaxMainPressureChart  == value) return; mMaxMainPressureChart  = value; emit signalEventChangedMaxMainPressureChart (value);}
    void setAutoScaleMinMargin   (double            value){ if(mAutoScaleMinMargin    == value) return; mAutoScaleMinMargin    = value; emit signalEventChangedAutoScaleMinMargin   (value);}
    void setUserPressureFixedN   (int               value){ if(mUserPressureFixedN    == value) return; mUserPressureFixedN    = value; emit signalEventChangedUserPressureFixedN   (value);emit signalEventChangedPressureFixedN(getPressureFixedN());}
    void setMinPressureFixedN    (int               value){ if(mMinPressureFixedN     == value) return; mMinPressureFixedN     = value; emit signalEventChangedMinPressureFixedN    (value);emit signalEventChangedPressureFixedN(getPressureFixedN());}
    void setConvertedFullScale   (double            value){ if(mConvertedFullScale    == value) return; mConvertedFullScale    = value; emit signalEventChangedConvertedFullScale   (value);}
    void setConvertedTPressure   (double            value){ if(mConvertedTPressure    == value) return; mConvertedTPressure    = value; emit signalEventChangedConvertedTPressure   (value);}
    void setConvertedRTPressure  (double            value){ if(mConvertedRTPressure   == value) return; mConvertedRTPressure   = value; emit signalEventChangedConvertedRTPressure  (value);}
    void setSetPoint01Position   (double            value){ if(mSetPoint01Position    == value) return; mSetPoint01Position    = value; emit signalEventChangedSetPoint01Position   (value);}
    void setSetPoint02Position   (double            value){ if(mSetPoint02Position    == value) return; mSetPoint02Position    = value; emit signalEventChangedSetPoint02Position   (value);}
    void setSetPoint03Position   (double            value){ if(mSetPoint03Position    == value) return; mSetPoint03Position    = value; emit signalEventChangedSetPoint03Position   (value);}
    void setSetPoint04Position   (double            value){ if(mSetPoint04Position    == value) return; mSetPoint04Position    = value; emit signalEventChangedSetPoint04Position   (value);}
    void setSetPoint05Position   (double            value){ if(mSetPoint05Position    == value) return; mSetPoint05Position    = value; emit signalEventChangedSetPoint05Position   (value);}
    void setSetPoint06Position   (double            value){ if(mSetPoint06Position    == value) return; mSetPoint06Position    = value; emit signalEventChangedSetPoint06Position   (value);}
    void setSetPoint01Pressure   (double            value){ if(mSetPoint01Pressure    == value) return; mSetPoint01Pressure    = value; emit signalEventChangedSetPoint01Pressure   (value);}
    void setSetPoint02Pressure   (double            value){ if(mSetPoint02Pressure    == value) return; mSetPoint02Pressure    = value; emit signalEventChangedSetPoint02Pressure   (value);}
    void setSetPoint03Pressure   (double            value){ if(mSetPoint03Pressure    == value) return; mSetPoint03Pressure    = value; emit signalEventChangedSetPoint03Pressure   (value);}
    void setSetPoint04Pressure   (double            value){ if(mSetPoint04Pressure    == value) return; mSetPoint04Pressure    = value; emit signalEventChangedSetPoint04Pressure   (value);}
    void setSetPoint05Pressure   (double            value){ if(mSetPoint05Pressure    == value) return; mSetPoint05Pressure    = value; emit signalEventChangedSetPoint05Pressure   (value);}
    void setSetPoint06Pressure   (double            value){ if(mSetPoint06Pressure    == value) return; mSetPoint06Pressure    = value; emit signalEventChangedSetPoint06Pressure   (value);}
    //void setPressureFixedN       (int               value){ if(mPressureFixedN        == value) return; mPressureFixedN        = value; }
    void setSensorFullScale      (int unit, double  value){ if(mFullScaleUnit == unit && mFullScale == value) return; mFullScaleUnit = unit; mFullScale = value; emit signalEventChangedFullScaleUnit(unit); emit signalEventChangedFullScale(value);}
    void setIsRecord             (bool              value){ if(mIsRecord              == value) return; mIsRecord              = value; emit signalEventChangedIsRecord             (value);}
    void setIsAutoRecord         (bool              value){ if(mIsAutoRecord          == value) return; mIsAutoRecord          = value; emit signalEventChangedIsAutoRecord         (value);}
    void setRecordTime           (qint64            value){                                             mRecordCurrTime        = value; emit signalEventChangedRecordTime           (getRecordTime());}
    void setAutoRecordTime       (qint64            value){                                             mAutoRecordCurrTime    = value; emit signalEventChangedAutoRecordTime       (getAutoRecordTime());}

signals:
    void signalEventChangedIsDevMode            (bool    value);
    void signalEventChangedStdFullScale         (qint64  value);
    void signalEventChangedPressureConvertFactor(double  value);
    void signalEventChangedNCPAVersion          (QString value);
    void signalEventChangedIsWithoutLogo        (bool    value);
    void signalEventChangedCompany              (int     value);
    void signalEventChangedIsValveConnect       (bool    value);
    void signalEventChangedErrMsg               (QString value);
    void signalEventChangedLoadProgress         (int     value);
    void signalEventChangedConnectionInfo       (QString value);
    void signalEventChangedValveID              (QString value);
    void signalEventChangedFirmwareVersion      (QString value);
    void signalEventChangedInterface            (int     value);
    void signalEventChangedIsSupportPFO         (bool    value);
    void signalEventChangedSensorVersion        (int     value);
    void signalEventChangedScanRate             (int     value);
    void signalEventChangedAccess               (int     value);
    void signalEventChangedMode                 (int     value);
    void signalEventChangedControlMode          (int     value);
    void signalEventChangedIsOpen               (bool    value);
    void signalEventChangedIsClose              (bool    value);
    void signalEventChangedValveSpeed           (qint64  value);
    void signalEventChangedCurrPos              (qint64  value);
    void signalEventChangedCurrPressure         (qint64  value);
    void signalEventChangedTargetPos            (qint64  value);
    void signalEventChangedTargetPressure       (qint64  value);
    void signalEventChangedPosResolution        (qint64  value);
    void signalEventChangedSensorOffset         (int     value);
    void signalEventChangedZeroEnable           (bool    value);
    void signalEventChangedFullScaleUnit        (int     value);
    void signalEventChangedFullScale            (double  value);
    void signalEventChangedPressureDpUnit       (int     value);
    void signalEventChangedCtrlAlgo             (int     value);
    void signalEventChangedEnablePFO            (bool    value);
    void signalEventChangedIsSimulation         (bool    value);
    void signalEventChangedIsTestMode           (bool    value);
    void signalEventChangedIsRS232Test          (bool    value);
    void signalEventChangedFieldBusError        (bool    value);
    void signalEventChangedIsSaving             (bool    value);
    void signalEventChangedIsIDMissing          (bool    value);
    void signalEventChangedIsPFOMissing         (bool    value);
    void signalEventChangedFirmwareError        (bool    value);
    void signalEventChangedUnknowInterface      (bool    value);
    void signalEventChangedNoSensorSignal       (bool    value);
    void signalEventChangedNoAnalogSignal       (bool    value);
    void signalEventChangedNetworkFailure       (bool    value);
    void signalEventChangedSlaveOffline         (bool    value);
    void signalEventChangedIsolationValve       (bool    value);
    void signalEventChangedSensorError          (bool    value);
    void signalEventChangedSvcRequest           (bool    value);
    void signalEventChangedLearnNotPresent      (bool    value);
    void signalEventChangedAirNotReady          (bool    value);
    void signalEventChangedPFONotReady          (bool    value);
    void signalEventChangedIsCurrPosDraw        (bool    value);
    void signalEventChangedIsCurrPressureDraw   (bool    value);
    void signalEventChangedIsTargetPosDraw      (bool    value);
    void signalEventChangedIsTargetPressureDraw (bool    value);
    void signalEventChangedIsPause              (bool    value);
    void signalEventChangedChartMSec            (int     value);
    void signalEventChangedIsPosAutoScaling     (bool    value);
    void signalEventChangedIsPressureAutoScaling(bool    value);
    void signalEventChangedIsPressureLogType    (bool    value);
    void signalEventChangedPressureDecades      (int     value);
    void signalEventChangedMinMainPressureChart (double  value);
    void signalEventChangedMaxMainPressureChart (double  value);
    void signalEventChangedAutoScaleMinMargin   (double  value);
    void signalEventChangedUserPressureFixedN   (int     value);
    void signalEventChangedMinPressureFixedN    (int     value);
    void signalEventChangedConvertedFullScale   (double  value);
    void signalEventChangedConvertedTPressure   (double  value);
    void signalEventChangedConvertedRTPressure  (double  value);
    void signalEventChangedSetPoint01Position   (double  value);
    void signalEventChangedSetPoint02Position   (double  value);
    void signalEventChangedSetPoint03Position   (double  value);
    void signalEventChangedSetPoint04Position   (double  value);
    void signalEventChangedSetPoint05Position   (double  value);
    void signalEventChangedSetPoint06Position   (double  value);
    void signalEventChangedSetPoint01Pressure   (double  value);
    void signalEventChangedSetPoint02Pressure   (double  value);
    void signalEventChangedSetPoint03Pressure   (double  value);
    void signalEventChangedSetPoint04Pressure   (double  value);
    void signalEventChangedSetPoint05Pressure   (double  value);
    void signalEventChangedSetPoint06Pressure   (double  value);
    void signalEventChangedPressureFixedN       (int     value);
    void signalEventChangedIsRecord             (bool    value);
    void signalEventChangedIsAutoRecord         (bool    value);
    void signalEventChangedRecordTime           (qint64  value);
    void signalEventChangedAutoRecordTime       (qint64  value);
    void signalEventAddGraphPoint               (qint64 msec, qint64 currPos, qint64 currPressure, qint64 targetPos, qint64 targetPressure);
    void signalEventOccurError                  (QString value);

public slots:
    void onCoreStartedService()
    {
        ENABLE_SLOT_VALVE_CHANGED_ISCONNECTED;
        ENABLE_SLOT_VALVE_CHANGED_LOAD_PROGRESS;
        ENABLE_SLOT_VALVE_CHANGED_CONNECTIONINFO;

        ENABLE_SLOT_VALVE_CHANGED_VALVE_ID;
        ENABLE_SLOT_VALVE_CHANGED_FIRMWARE_VER;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_INTERFACE;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_IS_SUPPORT_PFO;
        ENABLE_SLOT_VALVE_CHANGED_ENABLE_PFO;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_VERSION;
        ENABLE_SLOT_VALVE_CHANGED_SCAN_RATE;
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_MODE;
        ENABLE_SLOT_VALVE_CHANGED_CTRL_MODE;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_SPEED;
        ENABLE_SLOT_VALVE_CHANGED_IS_SIM;
        ENABLE_SLOT_VALVE_CHANGED_IS_TEST_MODE;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_FIELDBUS_ERR;
        ENABLE_SLOT_VALVE_CHANGED_FIRMWARE_ERR;
        ENABLE_SLOT_VALVE_CHANGED_IS_SAVING;
        ENABLE_SLOT_VALVE_CHANGED_UNKNOW_INTERFACE;
        ENABLE_SLOT_VALVE_CHANGED_NO_SENSOR_SIG   ;
        ENABLE_SLOT_VALVE_CHANGED_NO_ANALOG_SIG   ;
        ENABLE_SLOT_VALVE_CHANGED_NETWORK_FAIL;
        ENABLE_SLOT_VALVE_CHANGED_SLAVE_OFFLINE;
        ENABLE_SLOT_VALVE_CHANGED_ISOLATION_VALVE;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_ERR;
        ENABLE_SLOT_VALVE_CHANGED_SVC_REQ;
        ENABLE_SLOT_VALVE_CHANGED_LEARN_NOT_PRESENT;
        ENABLE_SLOT_VALVE_CHANGED_AIR_NOT_READY;
        ENABLE_SLOT_VALVE_CHANGED_PFO_NOT_READY;

        ENABLE_SLOT_VALVE_CHANGED_CURR_POS;
        ENABLE_SLOT_VALVE_CHANGED_CURR_PRESSURE;
        ENABLE_SLOT_VALVE_CHANGED_TARGET_POS;
        ENABLE_SLOT_VALVE_CHANGED_TARGET_PRESSURE;
        ENABLE_SLOT_VALVE_CHANGED_S01_FULLSCALE;
        ENABLE_SLOT_VALVE_CHANGED_S02_FULLSCALE;
        //ENABLE_SLOT_VALVE_CHANGED_S01_FULLSCALE_PREC;
        //ENABLE_SLOT_VALVE_CHANGED_S02_FULLSCALE_PREC;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_OP;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_01_OFFSET;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_02_OFFSET;
        ENABLE_SLOT_VALVE_CHANGED_ZERO_ENABLE;
        ENABLE_SLOT_VALVE_CHANGED_POS_RESOLUTION;
        ENABLE_SLOT_VALVE_CHANGED_PRESSURE_DB_UNIT;
        ENABLE_SLOT_VALVE_CHANGED_PRESSURE_AXIS_MODE;
        ENABLE_SLOT_VALVE_CHANGED_PRESSURE_DECADES;
        ENABLE_SLOT_VALVE_CHANGED_PRESSURE_CTRL_MODE;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_01_POSITION;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_02_POSITION;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_03_POSITION;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_04_POSITION;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_05_POSITION;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_06_POSITION;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_01_PRESSURE;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_02_PRESSURE;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_03_PRESSURE;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_04_PRESSURE;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_05_PRESSURE;
        ENABLE_SLOT_VALVE_CHANGED_SETPOINT_06_PRESSURE;

        ENABLE_SLOT_LSETTING_CHANGED_MONITORING_CYCLE;
        ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_CURR_POS;
        ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_TARGET_POS;
        ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_CURR_PRESSURE;
        ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_TARGET_PRESSURE;
        ENABLE_SLOT_LSETTING_CHANGED_IS_AUTOSCALE_POS;
        ENABLE_SLOT_LSETTING_CHANGED_IS_AUTOSCALE_PRESSURE;
        ENABLE_SLOT_LSETTING_CHANGED_CHART_MSEC;
        //ENABLE_SLOT_LSETTING_CHANGED_MIN_PRESSURE_CHART;
        //ENABLE_SLOT_LSETTING_CHANGED_MAX_PRESSURE_CHART;
        ENABLE_SLOT_LSETTING_CHANGED_USER_PRESSURE_FIXED_N;
        ENABLE_SLOT_LSETTING_CHANGED_AUTOSCALE_MIN_MARGIN;

        ENABLE_SLOT_VALVE_READED_VALVE_STATUS;

        ENABLE_SLOT_VALVE_WRITTEN_ACCESS;
        ENABLE_SLOT_VALVE_WRITTEN_TARGET_POSITION;
        ENABLE_SLOT_VALVE_WRITTEN_TARGET_PRESSURE;

        setIsDevMode(pLSettingSP->mDevModeIsOn);
        setIsRS232Test(pValveSP->getIsRS232Test());

        onLSettingChangedMonitoringCycle     ();
        onLSettingChangedIsDrawCurrPos       ();
        onLSettingChangedIsDrawTargetPos     ();
        onLSettingChangedIsDrawCurrPressure  ();
        onLSettingChangedIsDrawTargetPressure();
        onLSettingChangedIsAutoScalePos      ();
        onLSettingChangedIsAutoScalePressure ();
        onLSettingChangedChartMSec           ();
        //onLSettingChangedMinMainPressureChart();
        //onLSettingChangedMaxMainPressureChart();
        onLSettingChangedUserPressureFixedN  ();
        onLSettingChangedAutoScaleMinMargin  ();
    }

    void onValveChangedIsConnected            (bool    value){ setIsValeConnect(value);if(value)mConMSec = QDateTime::currentDateTime().toMSecsSinceEpoch();}
    void onValveChangedConnectionInfo         (QString value){ setConnectionInfo(value)                                                                ;}
    void onValveChangedValveID                (             ){ setValveID(pValveSP->getValveID())                                                      ;}
    void onValveChangedFirmwareVersion        (             ){ setFirmwareVersion(pValveSP->getFirmwareVersion())                                      ;}
    void onValveChangedInterface              (             ){ setInterface(pValveSP->getInterface())                                                  ;}
    void onValveChangedIsSupportPFO           (             ){ setIsSupportPFO(pValveSP->getIsSupportPFO())                                            ;}
    void onValveChangedSensorVersion          (             ){ setSensorVersion(pValveSP->getSensorVersion())                                          ;}
    void onValveChangedScanRate               (             ){ setScanRate(pValveSP->getScanRate())                                                    ;}
    void onValveChangedAccess                 (             ){ setAccess(pValveSP->getAccess())                                                        ;}
    void onValveChangedMode                   (             )
    {
        if(mMode == ValveEnumDef::MODE_INIT && pValveSP->getMode() != ValveEnumDef::MODE_INIT)
        {
            pValveSP->reLoad();
        }

        setMode(pValveSP->getMode());
    }
    void onValveChangedControlMode            (             ){ setControlMode(pValveSP->getControlMode())                                              ;}
    void onValveChangedValveSpeed             (             ){ setValveSpeed(pValveSP->getValveSpeed())                                                ;}
    void onValveChangedEnablePFO              (             ){ setEnablePFO(pValveSP->getEnablePFO())                                                  ;}
    void onValveChangedIsSimulation           (             ){ setIsSimulation(pValveSP->getIsSimulation())                                            ;}
    void onValveChangedIsTestMode             (             ){ setIsTestMode(pValveSP->getIsTestMode())                                                ;}
    void onValveChangedIsRS232Test            (             ){ setIsRS232Test(pValveSP->getIsRS232Test())                                              ;}
    void onValveChangedFieldBusError          (             ){ setFieldBusError(pValveSP->getFieldBusError())                                          ;}
    void onValveChangedIsSaving               (             ){ setIsSaving(pValveSP->getIsSaving())                                                    ;}
    void onValveChangedIsIDMissing            (             ){ setIsSaving(pValveSP->getIsIDMissing())                                                 ;}
    void onValveChangedIsPFOMissing           (             ){ setIsSaving(pValveSP->getIsPFOMissing())                                                ;}
    void onValveChangedFirmwareError          (             ){ setFirmwareError(pValveSP->getFirmwareError())                                          ;}
    void onValveChangedUnknowInterface        (             ){ setUnknowInterface(pValveSP->getUnknowInterface())                                      ;}
    void onValveChangedNoSensorSignal         (             ){ setNoSensorSignal (pValveSP->getNoSensorSignal ())                                      ;}
    void onValveChangedNoAnalogSignal         (             ){ setNoAnalogSignal (pValveSP->getNoAnalogSignal ())                                      ;}
    void onValveChangedNetworkFailure         (             ){ setNetworkFailure(pValveSP->getNetworkFailure())                                        ;}
    void onValveChangedSlaveOffline           (             ){ setSlaveOffline(pValveSP->getSlaveOffline())                                            ;}
    void onValveChangedIsolationValve         (             ){ setIsolationValve(pValveSP->getIsolationValve())                                        ;}
    void onValveChangedSensorError            (             ){ setSensorError(pValveSP->getSensorError())                                              ;}
    void onValveChangedSvcRequest             (             ){ setSvcRequest(pValveSP->getSvcRequest())                                                ;}
    void onValveChangedLearnNotPresent        (             ){ setLearnNotPresent(pValveSP->getLearnNotPresent())                                      ;}
    void onValveChangedAirNotReady            (             ){ setAirNotReady(pValveSP->getAirNotReady())                                              ;}
    void onValveChangedPFONotReady            (             ){ setPFONotReady(pValveSP->getPFONotReady())                                              ;}
    void onValveChangedCurrPosition           (             ){ setCurrPos(pValveSP->getCurrPosition())                                                 ;}
    void onValveChangedTargetPosition         (             ){ setTargetPos(pValveSP->getTargetPosition())                                             ;}
    void onValveChangedPositionResolution     (             ){ setPosResolution(pValveSP->getPositionResolution())                                     ;}
    void onValveChangedPressureDpUnit         (             ){ setPressureDpUnit(pValveSP->getPressureDpUnit());                     convertFullScale();}
    void onValveChangedPressureAxisMode       (             ){ setIsPressureLogType(pValveSP->getPressureAxisMode() == ValveEnumDef::PRESSURE_AXIS_LOG);}
    void onValveChangedPressureDecades        (             ){ setPressureDecades(pValveSP->getPressureDecades())                                      ;}
    void onValveChangedPressureCtrlMode       (             ){ setCtrlAlgo(pValveSP->getPressureCtrlMode())                                            ;}
    void onValveChangedSetPoint01Position     (             ){ setSetPoint01Position(pValveSP->getSetPoint01Position())                                ;}
    void onValveChangedSetPoint02Position     (             ){ setSetPoint02Position(pValveSP->getSetPoint02Position())                                ;}
    void onValveChangedSetPoint03Position     (             ){ setSetPoint03Position(pValveSP->getSetPoint03Position())                                ;}
    void onValveChangedSetPoint04Position     (             ){ setSetPoint04Position(pValveSP->getSetPoint04Position())                                ;}
    void onValveChangedSetPoint05Position     (             ){ setSetPoint05Position(pValveSP->getSetPoint05Position())                                ;}
    void onValveChangedSetPoint06Position     (             ){ setSetPoint06Position(pValveSP->getSetPoint06Position())                                ;}
    void onValveChangedSetPoint01Pressure     (             ){ setSetPoint01Pressure(convertPressure(pValveSP->getSetPoint01Pressure()))               ;}
    void onValveChangedSetPoint02Pressure     (             ){ setSetPoint02Pressure(convertPressure(pValveSP->getSetPoint02Pressure()))               ;}
    void onValveChangedSetPoint03Pressure     (             ){ setSetPoint03Pressure(convertPressure(pValveSP->getSetPoint03Pressure()))               ;}
    void onValveChangedSetPoint04Pressure     (             ){ setSetPoint04Pressure(convertPressure(pValveSP->getSetPoint04Pressure()))               ;}
    void onValveChangedSetPoint05Pressure     (             ){ setSetPoint05Pressure(convertPressure(pValveSP->getSetPoint05Pressure()))               ;}
    void onValveChangedSetPoint06Pressure     (             ){ setSetPoint06Pressure(convertPressure(pValveSP->getSetPoint06Pressure()))               ;}

    void onLSettingChangedMonitoringCycle     (             ){ pValveSP->setMonitoringCycle(pLSettingSP->mMonitoringCycle)                             ;}
    void onLSettingChangedIsDrawCurrPos       (             ){ setIsCurrPosDraw        (pLSettingSP->mIsDrawCurrPos)                                   ;}
    void onLSettingChangedIsDrawTargetPos     (             ){ setIsTargetPosDraw      (pLSettingSP->mIsDrawTargetPos)                                 ;}
    void onLSettingChangedIsDrawCurrPressure  (             ){ setIsCurrPressureDraw   (pLSettingSP->mIsDrawCurrPressure)                              ;}
    void onLSettingChangedIsDrawTargetPressure(             ){ setIsTargetPressureDraw (pLSettingSP->mIsDrawTargetPressure)                            ;}
    void onLSettingChangedIsAutoScalePos      (             ){ setIsPosAutoScaling     (pLSettingSP->mIsAutoScalePos)                                  ;}
    void onLSettingChangedIsAutoScalePressure (             ){ setIsPressureAutoScaling(pLSettingSP->mIsAutoScalePressure)                             ;}
    void onLSettingChangedChartMSec           (             ){ setChartMSec            (pLSettingSP->mChartMSec)                                       ;}
    //void onLSettingChangedMinMainPressureChart(             ){ setMinMainPressureChart (pLSettingSP->mMinMainPressureChart)                            ;}
    //void onLSettingChangedMaxMainPressureChart(             ){ setMaxMainPressureChart (pLSettingSP->mMaxMainPressureChart)                            ;}
    void onLSettingChangedUserPressureFixedN  (             ){ setUserPressureFixedN   (pLSettingSP->mUserPressureFixedN)                              ;}
    void onLSettingChangedAutoScaleMinMargin  (             ){ setAutoScaleMinMargin   (pLSettingSP->mAutoScaleMinMargin)                              ;}

    void onValveChangedLoadProgress(int value)
    {
        if(value == ValveEnumDef::LOAD_COMPLETED)
        {
            setLoadProgress(100);
        }
        else
        {
            setLoadProgress(qRound(((double)value / (double)ValveEnumDef::LOAD_COMPLETED) * 100.0));
        }
    }

    void onValveChangedS01FullScale()
    {
        if(pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT || pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02)
        {
            int precision = pValveSP->getS01FullScalePrec() + UNITUTIL_ADD_PRECISION(pValveSP->getS01SullScaleUnit(), pValveSP->getPressureDpUnit());
            precision = precision < 0 ? 0 : precision > 6 ? 6 : precision;
            setMinPressureFixedN(precision);
        }

        if(pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT && pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01)
        {
            return;
        }

        setSensorFullScale(pValveSP->getS01SullScaleUnit(), pValveSP->getS01FullScale());

        convertFullScale();
    }
    void onValveChangedS02FullScale()
    {
        if(pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT || pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01)
        {
            int precision = pValveSP->getS02FullScalePrec() + UNITUTIL_ADD_PRECISION(pValveSP->getS02SullScaleUnit(), pValveSP->getPressureDpUnit());
            precision = precision < 0 ? 0 : precision > 6 ? 6 : precision;
            setMinPressureFixedN(precision);
        }

        if(pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT && pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02)
        {
            return;
        }

        setSensorFullScale(pValveSP->getS02SullScaleUnit(), pValveSP->getS02FullScale());

        convertFullScale();
    }
    void onValveChangedSensorOperation()
    {
        onValveChangedS01FullScale();
        onValveChangedS02FullScale();
        onValveChangedSensor01Offset();
        onValveChangedSensor02Offset();
    }

    void onValveChangedSensor01Offset()
    {
        if(pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT && pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01)
        {
            return;
        }

        setSensorOffset(pValveSP->getSensor01Offset());
    }

    void onValveChangedSensor02Offset()
    {
        if(pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT && pValveSP->getSensorOperation() != ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02)
        {
            return;
        }

        setSensorOffset(pValveSP->getSensor02Offset());
    }

    void onValveChangedZeroEnable()
    {
        setZeroEnable(pValveSP->getZeroEnable());
    }

    void onValveChangedCurrPressure()
    {
        setCurrPressure(pValveSP->getCurrPressure());
        convertCurrPressure();
    }
    void onValveChangedTargetPressure()
    {
        setTargetPressure(pValveSP->getTargetPressure());
        convertTargetPressure();
    }

    void onValveReadedValveStatus(ValveResponseValveStatusDto dto)
    {
        qint64 msec;
        qint64 currPos;
        qint64 targetPos;
        qint64 currPressure;
        qint64 targetPressure;

        if(!dto.mIsSucc)
            return;

        msec         = dto.mResDateTime.toMSecsSinceEpoch();// .time().msecsSinceStartOfDay();
        currPos      = dto.mCurrPosition;
        currPressure = dto.mCurrPressure;

        //if(dto.mControlMode == ValveEnumDef::MODE_PRESSURE)
        //{
            targetPos      = dto.mTargetPosition;
            targetPressure = dto.mTargetPressure;

        //}
        //else
        //{
        //    targetPos      = dto.mTargetValue;
        //    targetPressure = pValveSP->getTargetPressure();
        //}

        setIsOpen (currPos == 100000 && getMode() != ValveEnumDef::MODE_SAFETY);
        setIsClose(currPos == 0      && getMode() == ValveEnumDef::MODE_CLOSED);

        //if(!pValveSP->getIsSealingType())
        //{
        //    setIsClose(currPos == 0  && getMode() != ValveEnumDef::MODE_SAFETY);
        //}
        //else
        //{
        //    setIsClose(mMode == ValveEnumDef::MODE_CLOSED);
        //}

        emit signalEventAddGraphPoint(dto.mResDateTime.time().msecsSinceStartOfDay(), currPos, currPressure, targetPos, targetPressure);

        if(getIsRecord())
        {
            setRecordTime(QDateTime::currentMSecsSinceEpoch());
            recordPoint(msec, currPos, targetPos, currPressure, targetPressure);
        }

        if(getIsAutoRecord())
        {
            setAutoRecordTime(QDateTime::currentMSecsSinceEpoch());
            autoRecordPoint(msec, currPos, targetPos, currPressure, targetPressure);
        }
    }

    void onValveWrittenAcces(ValveResponseDto dto)
    {
        if(dto.mIsSucc == false && dto.mReqDto.mpRef == this && !dto.mIsNetworkErr)
            emit signalEventOccurError(dto.mErrMsg);
    }
    void onValveWrittenTargetPosition(ValveResponseDto dto)
    {
        if(dto.mIsSucc == false && dto.mReqDto.mpRef == this && !dto.mIsNetworkErr)
            emit signalEventOccurError(dto.mErrMsg);
    }
    void onValveWrittenTargetPressure(ValveResponseDto dto)
    {
        if(dto.mIsSucc == false && dto.mReqDto.mpRef == this && !dto.mIsNetworkErr)
            emit signalEventOccurError(dto.mErrMsg);
    }

    Q_INVOKABLE void onCommandConnect(QString connType, QString portName)
    {
        ValveConnEnumDef::eConnectType eConnType = ValveConnection::getConnTypeByString(connType);
        pValveSP->connectDevice(eConnType, portName);
    }

    Q_INVOKABLE void onCommandWriteAccess(int access)
    {
        pValveSP->setAccess(access, this);
    }

    Q_INVOKABLE void onCommandWritePosition(qint64 pos)
    {
        //qDebug() << "[khko_debug][qmlcoremodel][onCommandWritePosition]" << pos;
        pValveSP->setTargetPosition(pos, this);
    }

    Q_INVOKABLE void onCommandWritePressure(qint64 pos)
    {
        pValveSP->setTargetPressure(pos, this);
    }

    Q_INVOKABLE void onCommandClickRecord()
    {
        setIsRecord(!getIsRecord());

        if(getIsRecord())
        {
            clearRecordData();
            mRecordStartTime = QDateTime::currentMSecsSinceEpoch();
        }
        else
        {
            mRecordStartTime = 0;
            setRecordTime(0);
        }
    }

    Q_INVOKABLE void onCommandClickAutoRecord()
    {
        setIsAutoRecord(!getIsAutoRecord());

        if(getIsAutoRecord())
        {
            clearAutoRecordData();
            mLastSaveTime = mAutoRecordStartTime = QDateTime::currentMSecsSinceEpoch();
        }
        else
        {
            autoSaveRecordData(true);

            mLastSaveTime = mAutoRecordStartTime = 0;
            setAutoRecordTime(0);
        }
    }

    Q_INVOKABLE void onCommandClickPause()
    {
        setIsPause(!getIsPause());
    }

    Q_INVOKABLE void onCommandSaveRecordData(QString filePath)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        saveRecordData(filePath);
    }

    Q_INVOKABLE void onCommandSimulation()
    {
        pValveSP->setSimulation(!pValveSP->getIsSimulation(), this);
    }

    Q_INVOKABLE void onCommandHoldPosition()
    {
        if(pValveSP->getMode() == ValveEnumDef::MODE_HOLD)
        {
            if(pValveSP->getControlMode() == ValveEnumDef::MODE_POSITION)
            {
                pValveSP->setTargetPosition(pValveSP->getTargetPosition(), this);
            }
            else if(pValveSP->getControlMode() == ValveEnumDef::MODE_PRESSURE)
            {
                pValveSP->setTargetPressure(pValveSP->getTargetPressure(), this);
            }
        }
        else
        {
            pValveSP->holdPosition(this);
        }
    }

    Q_INVOKABLE void onCommandOpenPosition()
    {
        pValveSP->openPosition(this);
    }

    Q_INVOKABLE void onCommandClosePosition()
    {
        pValveSP->closePosition(this);
    }

    Q_INVOKABLE void onCommandSoftOpen()
    {
        pValveSP->softOpen(this);
    }

    Q_INVOKABLE void onCommandSoftClose()
    {
        pValveSP->softClose(this);
    }

    Q_INVOKABLE void onCommandSetMinMaxPressureChart(double min, double max)
    {
        setMinMainPressureChart(min);
        setMaxMainPressureChart(max);
    }

    //Q_INVOKABLE void onCommandSetUserPressureFixedN(int value)
    //{
    //    setUserPressureFixedN(value);
    //}

    //Q_INVOKABLE void onCommandSetAutoScaleMinMargin(double value)
    //{
    //    setAutoScaleMinMargin(value);
    //}

public:
    explicit QmlCoreModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_CORE_START;

        pCoreService->start(this);

    }
    ~QmlCoreModel()
    {
        pCoreService->stop();
    }

private:
    void convertFullScale()
    {
        static double lastConvertedFullScale = 0.0f;

        double convertedFullScale  = UNITUTIL_CONVERT(getFullScaleUnit(), getFullScale(), getPressureDpUnit());

        //if(getMaxMainPressureChart() == 0)
        //{
        //    pLSettingSP->setMinMainPressureChart(0);
        //    pLSettingSP->setMaxMainPressureChart(convertedFullScale);
            //setMinMainPressureChart(0);
            //setMaxMainPressureChart(convertedFullScale);
        //}
        if(lastConvertedFullScale != convertedFullScale)
        {
            setMinMainPressureChart(0);
            setMaxMainPressureChart(convertedFullScale);
        }

        lastConvertedFullScale = convertedFullScale;
        //int pressureFixedN = MATHUTIL_LOG10ROUND(mStdFullScale) - MATHUTIL_LOG10ROUND(convertedFullScale);
        //pressureFixedN = pressureFixedN > 0 ? pressureFixedN : 0;
        //QString strFullScale = QString("%1").arg(convertedFullScale, 0, 'f', 18);
        //int pressureFixedN = 3 - MATHUTIL_LOG10ROUND(convertedFullScale);
        //qDebug() << "[khko] convertedFullScale = " << convertedFullScale << ", pressureFixedN = " << pressureFixedN;
        //pressureFixedN = pressureFixedN < 0 ? 0 : (pressureFixedN > 6 ? 6 : pressureFixedN);
        //qDebug() << "[khko] calc fixedN = " << pressureFixedN;
        //setPressureFixedN(pressureFixedN);

        setConvertedFullScale(convertedFullScale);

        setPressureConvertFactor((double)getFullScale() / (double)getStdFullScale());

        convertCurrPressure();
        convertTargetPressure();
    }

    void convertCurrPressure()
    {
        //if(getPressureDpUnit() == ValveEnumDef::PRESSURE_UNIT_PSF)
        //double convertedCurrPressure    = UNITUTIL_CONVERT(getFullScaleUnit(), getFullScale() * ((double)getCurrPressure() / (double)getStdFullScale()), getPressureDpUnit());

        double convertedCurrPressure    = UNITUTIL_CONVERT(getFullScaleUnit(), (double)getCurrPressure() * mPressureConvertFactor, getPressureDpUnit());
        setConvertedRTPressure(convertedCurrPressure);
    }

    void convertTargetPressure()
    {
        //double convertedTargetPressure    = UNITUTIL_CONVERT(getFullScaleUnit(), getFullScale() * ((double)getTargetPressure() / (double)getStdFullScale()), getPressureDpUnit());
        double convertedTargetPressure    = UNITUTIL_CONVERT(getFullScaleUnit(), (double)getTargetPressure() * mPressureConvertFactor, getPressureDpUnit());
        setConvertedTPressure(convertedTargetPressure);
    }

    double convertPressure(int pressure)
    {
        double convertedPressure    = UNITUTIL_CONVERT(getFullScaleUnit(), (double)pressure * mPressureConvertFactor, getPressureDpUnit());
        return convertedPressure;
    }

    void clearAutoRecordData()
    {
        mAutoRecordTimestampList.clear();
        mAutoRecordCurrentPosList.clear();
        mAutoRecordTargetPosList.clear();
        mAutoRecordCurrentPressureList.clear();
        mAutoRecordTargetPressureList.clear();
    }

    void autoRecordPoint(qint64 msec, qint64 currPos, qint64 targetPos, qint64 currPressure, qint64 targetPressure)
    {
        autoSaveRecordData();

        mAutoRecordTimestampList.append(msec);
        mAutoRecordCurrentPosList.append(currPos);
        mAutoRecordTargetPosList.append(targetPos);
        mAutoRecordCurrentPressureList.append(currPressure);
        mAutoRecordTargetPressureList.append(targetPressure);
    }


    void clearRecordData()
    {
        mRecordTimestampList.clear();
        mRecordCurrentPosList.clear();
        mRecordTargetPosList.clear();
        mRecordCurrentPressureList.clear();
        mRecordTargetPressureList.clear();
    }

    void recordPoint(qint64 msec, qint64 currPos, qint64 targetPos, qint64 currPressure, qint64 targetPressure)
    {
        mRecordTimestampList.append(msec);
        mRecordCurrentPosList.append(currPos);
        mRecordTargetPosList.append(targetPos);
        mRecordCurrentPressureList.append(currPressure);
        mRecordTargetPressureList.append(targetPressure);
    }

    void autoSaveRecordData(bool isForceSave = false)
    {
        qint64 curr = QDateTime::currentMSecsSinceEpoch();

        if((mLastSaveTime > (curr - (1000 * 60 * 60))) && isForceSave == false)
            return;

        if (QDir(QString("%1/autosave").arg(QApplication::applicationDirPath())).exists() == false)
        {
            QDir().mkdir(QString("%1/autosave").arg(QApplication::applicationDirPath()));
        }

        saveRecordData(QString("%1/%2/%3.txt").arg(QApplication::applicationDirPath()).arg("autosave").arg(QDateTime::fromMSecsSinceEpoch(mLastSaveTime).toString("yyyy-MM-dd-hh-mm-ss")), true);

        mLastSaveTime = curr;
        clearAutoRecordData();
    }

    void saveRecordData(QString filePath, bool isAutoRecord = false)
    {
        double convertedFullScale  = UNITUTIL_CONVERT(getFullScaleUnit(), getFullScale(), getPressureDpUnit());
        int pressureFixedN = MATHUTIL_LOG10ROUND(mStdFullScale) - MATHUTIL_LOG10ROUND(convertedFullScale);
        pressureFixedN = pressureFixedN > 0 ? pressureFixedN : 0;

        FileWriterEx file;

        if(filePath == "")
        {
            filePath = QString("%1/%2.txt").arg(QApplication::applicationDirPath()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
        }

        qDebug() << "[" << Q_FUNC_INFO << "]" << filePath;

        int splitIdx = filePath.lastIndexOf("/")+1;
        QString dir = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        if(file.open(dir, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            emit signalEventOccurError("File save failed.");
            return;
        }

        file.appendLine(QString("NOVASEN - NCPA(%1)").arg(getNCPAVersion()));
        file.appendLine(QString("save datetime : %1").arg(QDateTime::currentDateTime().toString(DATE_TIME_FMT)));
        file.appendLine(QString(" "));
        file.appendLine(QString("---------------------------------------------"));
        file.appendLine(QString(" "));
        file.appendLine(QString("Pressure ctrl mode    : %1").arg(mCtrlAlgo == ValveEnumDef::PRESSURE_CTRL_ADAPTIVE ? "Adaptive" : mCtrlAlgo == ValveEnumDef::PRESSURE_CTRL_FIXED_DOWN ? "Fixed" : "etc"));
        if(mCtrlAlgo == (int)ValveEnumDef::PRESSURE_CTRL_ADAPTIVE)
        {
            file.appendLine(QString("Adaptive Gain Factor  : %1").arg(pValveSP->getAdaptiveGainFactor()));
            file.appendLine(QString("Adaptive Delta Factor : %1").arg(pValveSP->getAdaptiveDeltaFactor()));
            file.appendLine(QString("Adaptive Sensor Delay : %1").arg(pValveSP->getAdaptiveSensorDelay()));
            file.appendLine(QString("Adaptive Ramp Time    : %1").arg(pValveSP->getAdaptiveRampTime()));
            file.appendLine(QString("Adaptive Ramp Mode    : %1").arg(pValveSP->getAdaptiveRampMode() == 0 ? "constant time" : "constant slope"));
        }
        else if(mCtrlAlgo == (int)ValveEnumDef::PRESSURE_CTRL_FIXED_DOWN)
        {
            file.appendLine(QString("Fixed P Gain          : %1").arg(pValveSP->getFixed1PGain()));
            file.appendLine(QString("Fixed I Gain          : %1").arg(pValveSP->getFixed1IGain()));
            file.appendLine(QString("Fixed Ramp Time       : %1").arg(pValveSP->getFixed1RampTime()));
            file.appendLine(QString("Fixed Ramp Mode       : %1").arg(pValveSP->getFixed1RampMode() == 0 ? "constant time" : "constant slope"));
            file.appendLine(QString("Fixed Direction       : %1").arg(pValveSP->getFixed1Dir() == 0 ? "downstream": "upstream"));
        }
        else if(mCtrlAlgo == (int)ValveEnumDef::PRESSURE_CTRL_FIXED_UP)
        {
            file.appendLine(QString("Fixed P Gain          : %1").arg(pValveSP->getFixed2PGain()));
            file.appendLine(QString("Fixed I Gain          : %1").arg(pValveSP->getFixed2IGain()));
            file.appendLine(QString("Fixed Ramp Time       : %1").arg(pValveSP->getFixed2RampTime()));
            file.appendLine(QString("Fixed Ramp Mode       : %1").arg(pValveSP->getFixed2RampMode() == 0 ? "constant time" : "constant slope"));
            file.appendLine(QString("Fixed Direction       : %1").arg(pValveSP->getFixed2Dir() == 0 ? "downstream": "upstream"));
        }
        else
        {
            file.appendLine(QString("Unknow"));
            file.appendLine(QString("Unknow"));
            file.appendLine(QString("Unknow"));
            file.appendLine(QString("Unknow"));
            file.appendLine(QString("Unknow"));
        }

        file.appendLine(QString("Position resolution   : %1").arg(mPosResolution));
        file.appendLine(QString("Sensor offset         : %1 mv").arg((double)mSensorOffset/100.0, 10, 'f', 2, QChar(' ')));
        file.appendLine(QString("Sensor full scale     : %1 %2").arg(mFullScale).arg(UNITUTIL_TO_STR(mFullScaleUnit)));
        file.appendLine(QString("pressure display unit : %1").arg(UNITUTIL_TO_STR(mPressureDpUnit)));
        file.appendLine(QString(" "));
        file.appendLine(QString("Record data :"));
        file.appendLine(QString("timestamp(second)         actual_position    target_position    actual_pressure    target_pressure"));

        qint64 firstMsec;
        qint64 msec;
        double actualPos;
        double targetPos;
        double actualPressure;
        double targetPressure;
        int    posFixedN = MATHUTIL_LOG10ROUND(10000) - MATHUTIL_LOG10ROUND(mPosResolution);
        double convertPosFactor = qPow(10, -1*(posFixedN+1));

        if(isAutoRecord)
        {
            for(int i = 0; i < mAutoRecordTimestampList.size(); i ++)
            {
                msec = mAutoRecordTimestampList[i];

                if(i == 0)
                {
                    firstMsec = msec;
                }

                msec           = msec - firstMsec;
                actualPos      = ((double)mAutoRecordCurrentPosList[i]) * convertPosFactor;
                targetPos      = ((double)mAutoRecordTargetPosList[i] ) * convertPosFactor;
                actualPressure = UNITUTIL_CONVERT(getFullScaleUnit(), ((double)mAutoRecordCurrentPressureList[i]) * mPressureConvertFactor, getPressureDpUnit());
                targetPressure = UNITUTIL_CONVERT(getFullScaleUnit(), ((double)mAutoRecordTargetPressureList[i] ) * mPressureConvertFactor, getPressureDpUnit());
                file.appendLine(QString("%1.%2    %3    %4    %5    %6")
                                        .arg((msec/1000)   , 18, 10                  , QChar('0'))
                                        .arg((msec%1000)   ,  3, 10                  , QChar('0'))
                                        .arg(actualPos     , 15, 'f', posFixedN      , QChar(' '))
                                        .arg(targetPos     , 15, 'f', posFixedN      , QChar(' '))
                                        .arg(actualPressure, 15, 'f', pressureFixedN , QChar(' '))
                                        .arg(targetPressure, 15, 'f', pressureFixedN , QChar(' ')));
            }
        }
        else
        {
            for(int i = 0; i < mRecordTimestampList.size(); i ++)
            {
                msec = mRecordTimestampList[i];

                if(i == 0)
                {
                    firstMsec = msec;
                }

                msec           = msec - firstMsec;
                actualPos      = ((double)mRecordCurrentPosList[i]) * convertPosFactor;
                targetPos      = ((double)mRecordTargetPosList[i] ) * convertPosFactor;
                actualPressure = UNITUTIL_CONVERT(getFullScaleUnit(), ((double)mRecordCurrentPressureList[i]) * mPressureConvertFactor, getPressureDpUnit());
                targetPressure = UNITUTIL_CONVERT(getFullScaleUnit(), ((double)mRecordTargetPressureList[i] ) * mPressureConvertFactor, getPressureDpUnit());
                file.appendLine(QString("%1.%2    %3    %4    %5    %6")
                                        .arg((msec/1000)   , 18, 10                  , QChar('0'))
                                        .arg((msec%1000)   ,  3, 10                  , QChar('0'))
                                        .arg(actualPos     , 15, 'f', posFixedN      , QChar(' '))
                                        .arg(targetPos     , 15, 'f', posFixedN      , QChar(' '))
                                        .arg(actualPressure, 15, 'f', pressureFixedN , QChar(' '))
                                        .arg(targetPressure, 15, 'f', pressureFixedN , QChar(' ')));
            }
        }

        file.close();
        return;
    }
};


#endif // QMLCOREMODEL_H
