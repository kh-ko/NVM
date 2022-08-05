#ifndef VALVESPROVIDERDTO_H
#define VALVESPROVIDERDTO_H

#include <QObject>
#include <QDateTime>
#include <QtMath>

class ValveSProviderDto
{
public:
    bool      mIsSucc       = false;
    bool      mIsNetworkErr = false;
    QString   mErrMsg       = "";
    int       mRetryCnt     = 0;
    void    * mpRef         = nullptr;

    ValveSProviderDto(){}
    ValveSProviderDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef)
    {
        mIsSucc       = isSucc;
        mIsNetworkErr = isNetworkErr;
        mErrMsg       = errMsg;
        mRetryCnt     = retryCnt;
        mpRef         = pRef;
    }
    ValveSProviderDto(const ValveSProviderDto& copy) :
        mIsSucc      (copy.mIsSucc      ),
        mIsNetworkErr(copy.mIsNetworkErr),
        mErrMsg      (copy.mErrMsg      ),
        mRetryCnt    (copy.mRetryCnt    ),
        mpRef        (copy.mpRef        ){}

    ~ValveSProviderDto(){}

    ValveSProviderDto& operator=(const ValveSProviderDto& other)
    {
        mIsSucc       = other.mIsSucc   ;
        mIsNetworkErr = other.mIsNetworkErr;
        mErrMsg       = other.mErrMsg   ;
        mRetryCnt     = other.mRetryCnt ;
        mpRef         = other.mpRef     ;

        return *this;
    }

    QString toString()
    {
        return QString("isSucc = %1, errMsg = %2, mIsNetworkErr = %3, mRetryCnt = %4").arg(mIsSucc).arg(mErrMsg).arg(mIsNetworkErr).arg(mRetryCnt);
    }
};
Q_DECLARE_METATYPE(ValveSProviderDto);

class ValveSProviderValveIdDto : public ValveSProviderDto
{
public:
    QString mValveID = "";

    ValveSProviderValveIdDto(){}
    ValveSProviderValveIdDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderValveIdDto(const ValveSProviderValveIdDto& copy) : ValveSProviderDto(copy),
        mValveID(copy.mValveID){}

    ~ValveSProviderValveIdDto(){}

    ValveSProviderValveIdDto& operator=(const ValveSProviderValveIdDto& other)
    {
        ValveSProviderDto::operator=(other);

        mValveID = other.mValveID;

        return *this;
    }

    QString toString()
    {
        return QString("%1, valveID = %2").arg(ValveSProviderDto::toString()).arg(mValveID);
    }
};

Q_DECLARE_METATYPE(ValveSProviderValveIdDto);

class ValveSProviderHWConfigDto : public ValveSProviderDto
{
public:
    bool mIsSupportPFO = false;
    bool mIsSupportSPS = false;
    int  mInterface    = 0;
    int  mSensorVerion = 1;

    ValveSProviderHWConfigDto(){}
    ValveSProviderHWConfigDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderHWConfigDto(const ValveSProviderHWConfigDto& copy) : ValveSProviderDto(copy),
        mIsSupportPFO(copy.mIsSupportPFO),
        mIsSupportSPS(copy.mIsSupportSPS),
        mInterface   (copy.mInterface   ),
        mSensorVerion(copy.mSensorVerion){}

    ~ValveSProviderHWConfigDto(){}

    ValveSProviderHWConfigDto& operator=(const ValveSProviderHWConfigDto& other)
    {
        ValveSProviderDto::operator=(other);

        mIsSupportPFO = other.mIsSupportPFO;
        mIsSupportSPS = other.mIsSupportSPS;
        mInterface    = other.mInterface   ;
        mSensorVerion = other.mSensorVerion;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mIsSupportPFO = %2, mIsSupportSPS = %3, mInterface = %4, mSensorVerion = %5").arg(ValveSProviderDto::toString()).arg(mIsSupportPFO).arg(mIsSupportSPS).arg(mInterface).arg(mSensorVerion);
    }
};

Q_DECLARE_METATYPE(ValveSProviderHWConfigDto);

class ValveSProviderFirmwareVersionDto : public ValveSProviderDto
{
public:
    QString mFirmwareVersion = "";

    ValveSProviderFirmwareVersionDto(){}
    ValveSProviderFirmwareVersionDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderFirmwareVersionDto(const ValveSProviderFirmwareVersionDto& copy) : ValveSProviderDto(copy),
        mFirmwareVersion(copy.mFirmwareVersion){}

    ~ValveSProviderFirmwareVersionDto(){}

    ValveSProviderFirmwareVersionDto& operator=(const ValveSProviderFirmwareVersionDto& other)
    {
        ValveSProviderDto::operator=(other);

        mFirmwareVersion = other.mFirmwareVersion;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mFirmwareVersion = %2").arg(ValveSProviderDto::toString()).arg(mFirmwareVersion);
    }
};

Q_DECLARE_METATYPE(ValveSProviderFirmwareVersionDto);

class ValveSProviderValveStatusDto : public ValveSProviderDto
{
public:
    QDateTime mDateTime;
    qint64    mCurrPosition     ;
    qint64    mCurrPressure     ;
    qint64    mTargetValue      ;
    qint64    mTargetPosition   ;
    qint64    mTargetPressure   ;
    qint64    mValveSpeed       ;
    int       mGainFactor       ;
    int       mAccess           ;
    int       mMode             ;
    int       mControlMode      ;
    int       mReserved01       ;
    bool      mIsSimulation     ;
    bool      mEnablePFO        ;
    bool      mFieldBusError    ;
    bool      mFirmwareError    ;
    bool      mNetworkFailure   ;
    bool      mSlaveOffline     ;
    bool      mIsolationValve   ;
    bool      mSensorError      ;
    bool      mSvcRequest       ;
    bool      mLearnNotPresent  ;
    bool      mAirNotReady      ;
    bool      mPFONotReady      ;
    int       mSensorDelay      ;
    int       mRampTime         ;

    ValveSProviderValveStatusDto(){}
    ValveSProviderValveStatusDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderValveStatusDto(const ValveSProviderValveStatusDto& copy) : ValveSProviderDto(copy),
        mDateTime         (copy.mDateTime         ),
        mCurrPosition     (copy.mCurrPosition     ),
        mCurrPressure     (copy.mCurrPressure     ),
        mTargetValue      (copy.mTargetValue      ),
        mTargetPosition   (copy.mTargetPosition   ),
        mTargetPressure   (copy.mTargetPressure   ),
        mValveSpeed       (copy.mValveSpeed       ),
        mGainFactor       (copy.mGainFactor       ),
        mAccess           (copy.mAccess           ),
        mMode             (copy.mMode             ),
        mControlMode      (copy.mControlMode      ),
        mReserved01       (copy.mReserved01       ),
        mIsSimulation     (copy.mIsSimulation     ),
        mEnablePFO        (copy.mEnablePFO        ),
        mFieldBusError    (copy.mFieldBusError    ),
        mFirmwareError    (copy.mFirmwareError    ),
        mNetworkFailure   (copy.mNetworkFailure   ),
        mSlaveOffline     (copy.mSlaveOffline     ),
        mIsolationValve   (copy.mIsolationValve   ),
        mSensorError      (copy.mSensorError      ),
        mSvcRequest       (copy.mSvcRequest       ),
        mLearnNotPresent  (copy.mLearnNotPresent  ),
        mAirNotReady      (copy.mAirNotReady      ),
        mPFONotReady      (copy.mPFONotReady      ),
        mSensorDelay      (copy.mSensorDelay      ),
        mRampTime         (copy.mRampTime         ){}

    ~ValveSProviderValveStatusDto(){}

    ValveSProviderValveStatusDto& operator=(const ValveSProviderValveStatusDto& other)
    {
        ValveSProviderDto::operator=(other);

        mDateTime          = other.mDateTime         ;
        mCurrPosition      = other.mCurrPosition     ;
        mCurrPressure      = other.mCurrPressure     ;
        mTargetValue       = other.mTargetValue      ;
        mTargetPosition    = other.mTargetPosition   ;
        mTargetPressure    = other.mTargetPressure   ;
        mValveSpeed        = other.mValveSpeed       ;
        mGainFactor        = other.mGainFactor       ;
        mAccess            = other.mAccess           ;
        mMode              = other.mMode             ;
        mControlMode       = other.mControlMode      ;
        mReserved01        = other.mReserved01       ;
        mIsSimulation      = other.mIsSimulation     ;
        mEnablePFO         = other.mEnablePFO        ;
        mFieldBusError     = other.mFieldBusError    ;
        mFirmwareError     = other.mFirmwareError    ;
        mNetworkFailure    = other.mNetworkFailure   ;
        mSlaveOffline      = other.mSlaveOffline     ;
        mIsolationValve    = other.mIsolationValve   ;
        mSensorError       = other.mSensorError      ;
        mSvcRequest        = other.mSvcRequest       ;
        mLearnNotPresent   = other.mLearnNotPresent  ;
        mAirNotReady       = other.mAirNotReady      ;
        mPFONotReady       = other.mPFONotReady      ;
        mSensorDelay       = other.mSensorDelay      ;
        mRampTime          = other.mRampTime         ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, currPos = %2, currPress = %3, TargetVale = %4, ValveSpeed = %5, gainFac = %6, access = %7, mode = %8, sensor delay = %9, ramp time = %10, is sim = %11, enable PFO = %12, FieldBusE = %13, FirmwareE = %14, Network Fail = %15, SlaveOffline = %16, mIsolationValve = %17, mSensorError = %18, svcReq = %19, Learn Not = %20, AirNot = %21, PFONot = %22, mControlMode = %23")
                      .arg(ValveSProviderDto::toString()).arg((int)mCurrPosition).arg((int)mCurrPressure).arg(mTargetValue).arg(mValveSpeed)
                      .arg(mGainFactor).arg(mAccess).arg(mMode).arg(mSensorDelay).arg(mRampTime).arg(mIsSimulation).arg(mEnablePFO)
                      .arg(mFieldBusError).arg(mFirmwareError).arg(mNetworkFailure).arg(mSlaveOffline).arg(mIsolationValve).arg(mSensorError)
                      .arg(mSvcRequest).arg(mLearnNotPresent).arg(mAirNotReady).arg(mPFONotReady).arg(mControlMode);
    }
};

Q_DECLARE_METATYPE(ValveSProviderValveStatusDto);

class ValveSProviderSensorScaleDto : public ValveSProviderDto
{
public:
    int    mS01Unit      = 0;
    int    mS01FullScale = 0;
    int    mS01Exponent  = 0;
    int    mS02Unit      = 0;
    int    mS02FullScale = 0;
    int    mS02Exponent  = 0;

    ValveSProviderSensorScaleDto(){}
    ValveSProviderSensorScaleDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderSensorScaleDto(const ValveSProviderSensorScaleDto& copy) : ValveSProviderDto(copy),
        mS01Unit     (copy.mS01Unit     ),
        mS01FullScale(copy.mS01FullScale),
        mS01Exponent (copy.mS01Exponent ),
        mS02Unit     (copy.mS02Unit     ),
        mS02FullScale(copy.mS02FullScale),
        mS02Exponent(copy.mS02Exponent  ){}

    ~ValveSProviderSensorScaleDto(){}

    ValveSProviderSensorScaleDto& operator=(const ValveSProviderSensorScaleDto& other)
    {
        ValveSProviderDto::operator=(other);

        mS01Unit      = other.mS01Unit     ;
        mS01FullScale = other.mS01FullScale;
        mS01Exponent  = other.mS01Exponent ;
        mS02Unit      = other.mS02Unit     ;
        mS02FullScale = other.mS02FullScale;
        mS02Exponent  = other.mS02Exponent ;

        return *this;
    }

    double getS01FullScale()
    {
        return ((double)mS01FullScale * 0.0001) * qPow(10 , mS01Exponent);
    }

    double getS02FullScale()
    {
        return ((double)mS02FullScale * 0.0001) * qPow(10 , mS02Exponent);
    }

    QString toString()
    {
        return QString("%1, S01Unit = %2, S01FullScale = %3, S02Unit = %4, S02FullScale = %5")
                      .arg(ValveSProviderDto::toString()).arg(mS01Unit).arg(getS01FullScale()).arg(mS02Unit).arg(getS02FullScale());
    }
};

Q_DECLARE_METATYPE(ValveSProviderSensorScaleDto);

class ValveSProviderSensorConfigDto : public ValveSProviderDto
{
public:
    int    mSensorOperation = 0;
    bool   mZeroEnable      = false;
    qint64 mFullScaleRatio  = 0;

    ValveSProviderSensorConfigDto(){}
    ValveSProviderSensorConfigDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderSensorConfigDto(const ValveSProviderSensorConfigDto& copy) : ValveSProviderDto(copy),
        mSensorOperation(copy.mSensorOperation),
        mZeroEnable     (copy.mZeroEnable     ),
        mFullScaleRatio (copy.mFullScaleRatio ){}

    ~ValveSProviderSensorConfigDto(){}

    ValveSProviderSensorConfigDto& operator=(const ValveSProviderSensorConfigDto& other)
    {
        ValveSProviderDto::operator=(other);

        mSensorOperation = other.mSensorOperation;
        mZeroEnable      = other.mZeroEnable     ;
        mFullScaleRatio  = other.mFullScaleRatio ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, SensorOp = %2, ZeroEnable = %3, FullScaleRatio = %4").arg(ValveSProviderDto::toString()).arg(mSensorOperation).arg(mZeroEnable).arg(mFullScaleRatio);
    }
};

Q_DECLARE_METATYPE(ValveSProviderSensorConfigDto);

class ValveSProviderDpConfigDto : public ValveSProviderDto
{
public:
    int mPositionResolution  = 0;
    int mPressureDpUnit      = 0;
    int mPressureAxisMapping = 0;
    int mPressureDecades     = 5;

    ValveSProviderDpConfigDto(){}
    ValveSProviderDpConfigDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderDpConfigDto(const ValveSProviderDpConfigDto& copy) : ValveSProviderDto(copy),
        mPositionResolution (copy.mPositionResolution ),
        mPressureDpUnit     (copy.mPressureDpUnit     ),
        mPressureAxisMapping(copy.mPressureAxisMapping),
        mPressureDecades    (copy.mPressureDecades    ){}

    ~ValveSProviderDpConfigDto(){}

    ValveSProviderDpConfigDto& operator=(const ValveSProviderDpConfigDto& other)
    {
        ValveSProviderDto::operator=(other);

        mPositionResolution  = other.mPositionResolution ;
        mPressureDpUnit      = other.mPressureDpUnit     ;
        mPressureAxisMapping = other.mPressureAxisMapping;
        mPressureDecades     = other.mPressureDecades    ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, PositionResolution = %2, PressureDpUnit = %3, PressureAxisMapping = %4, PressureDecades = %5")
                      .arg(ValveSProviderDto::toString()).arg(mPositionResolution).arg(mPressureDpUnit).arg(mPressureAxisMapping).arg(mPressureDecades);
    }
};

Q_DECLARE_METATYPE(ValveSProviderDpConfigDto);

class ValveSProviderPressureCtrlConfigDto : public ValveSProviderDto
{
public:
    int mCtrlMode    = 0;
    int mGainFactor  = 0;
    int mSensorDelay = 0;
    int mRampTime    = 0;

    ValveSProviderPressureCtrlConfigDto(){}
    ValveSProviderPressureCtrlConfigDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderPressureCtrlConfigDto(const ValveSProviderPressureCtrlConfigDto& copy) : ValveSProviderDto(copy),
        mCtrlMode   (copy.mCtrlMode   ),
        mGainFactor (copy.mGainFactor ),
        mSensorDelay(copy.mSensorDelay),
        mRampTime   (copy.mRampTime   ){}

    ~ValveSProviderPressureCtrlConfigDto(){}

    ValveSProviderPressureCtrlConfigDto& operator=(const ValveSProviderPressureCtrlConfigDto& other)
    {
        ValveSProviderDto::operator=(other);

        mCtrlMode    = other.mCtrlMode   ;
        mGainFactor  = other.mGainFactor ;
        mSensorDelay = other.mSensorDelay;
        mRampTime    = other.mRampTime   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, CtrlMode = %2, GainFactor = %3, SensorDelay = %4, RampTime = %5").arg(ValveSProviderDto::toString()).arg(mCtrlMode).arg(mGainFactor).arg(mSensorDelay).arg(mRampTime);
    }
};

Q_DECLARE_METATYPE(ValveSProviderPressureCtrlConfigDto);


class ValveSProviderValveSpeedDto : public ValveSProviderDto
{
public:
    int mValveSpeed = 0;

    ValveSProviderValveSpeedDto(){}
    ValveSProviderValveSpeedDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderValveSpeedDto(const ValveSProviderValveSpeedDto& copy) : ValveSProviderDto(copy),
        mValveSpeed(copy.mValveSpeed){}

    ValveSProviderValveSpeedDto& operator=(const ValveSProviderValveSpeedDto& other)
    {
        ValveSProviderDto::operator=(other);

        mValveSpeed  = other.mValveSpeed;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mValveSpeed = %2, mEventSync = %3, mStrokeLimitation = %4, mTargetPosPowerFail = %5, mTargetPosNetworkFail = %6").arg(ValveSProviderDto::toString()).arg(mValveSpeed);
    }
};

Q_DECLARE_METATYPE(ValveSProviderValveSpeedDto);

class ValveSProviderValveSetupDto : public ValveSProviderDto
{
public:
    int mTargetPosSync        = 0;
    int mEventSync            = 0;
    int mStrokeLimitation     = 0;
    int mTargetPosPowerFail   = 0;
    int mTargetPosNetworkFail = 0;

    ValveSProviderValveSetupDto(){}
    ValveSProviderValveSetupDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderValveSetupDto(const ValveSProviderValveSetupDto& copy) : ValveSProviderDto(copy),
        mTargetPosSync       (copy.mTargetPosSync       ),
        mEventSync           (copy.mEventSync           ),
        mStrokeLimitation    (copy.mStrokeLimitation    ),
        mTargetPosPowerFail  (copy.mTargetPosPowerFail  ),
        mTargetPosNetworkFail(copy.mTargetPosNetworkFail){}

    ValveSProviderValveSetupDto& operator=(const ValveSProviderValveSetupDto& other)
    {
        ValveSProviderDto::operator=(other);

        mTargetPosSync        = other.mTargetPosSync       ;
        mEventSync            = other.mEventSync           ;
        mStrokeLimitation     = other.mStrokeLimitation    ;
        mTargetPosPowerFail   = other.mTargetPosPowerFail  ;
        mTargetPosNetworkFail = other.mTargetPosNetworkFail;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mTargetPosSync = %2, mEventSync = %3, mStrokeLimitation = %4, mTargetPosPowerFail = %5, mTargetPosNetworkFail = %6").arg(ValveSProviderDto::toString())
                .arg(mTargetPosSync).arg(mEventSync).arg(mStrokeLimitation).arg(mTargetPosPowerFail).arg(mTargetPosNetworkFail);
    }
};

Q_DECLARE_METATYPE(ValveSProviderValveSetupDto);

class ValveSProviderValveParamDto : public ValveSProviderDto
{
public:
    int     mID    = 0;
    QString mValue = 0;

    ValveSProviderValveParamDto(){}
    ValveSProviderValveParamDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderValveParamDto(const ValveSProviderValveParamDto& copy) : ValveSProviderDto(copy),
        mID   (copy.mID   ),
        mValue(copy.mValue){}

    ValveSProviderValveParamDto& operator=(const ValveSProviderValveParamDto& other)
    {
        ValveSProviderDto::operator=(other);

        mID    = other.mID   ;
        mValue = other.mValue;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mID = %2, value = %3").arg(ValveSProviderDto::toString()).arg(mID).arg(mValue);
    }
};

Q_DECLARE_METATYPE(ValveSProviderValveParamDto);

class ValveSProviderFatalErrStatusDto : public ValveSProviderDto
{
public:
    int mErrorCode = 0;

    ValveSProviderFatalErrStatusDto(){}
    ValveSProviderFatalErrStatusDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderFatalErrStatusDto(const ValveSProviderFatalErrStatusDto& copy) : ValveSProviderDto(copy),
        mErrorCode   (copy.mErrorCode){}

    ValveSProviderFatalErrStatusDto& operator=(const ValveSProviderFatalErrStatusDto& other)
    {
        ValveSProviderDto::operator=(other);

        mErrorCode = other.mErrorCode   ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mErrorCode = %3").arg(mIsSucc).arg(mErrMsg).arg(mErrorCode);
    }
};

Q_DECLARE_METATYPE(ValveSProviderFatalErrStatusDto);

class ValveSProviderWarningsDto : public ValveSProviderDto
{
public:
    int mIsServiceRequest = 0;

    ValveSProviderWarningsDto(){}
    ValveSProviderWarningsDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWarningsDto(const ValveSProviderWarningsDto& copy) : ValveSProviderDto(copy),
        mIsServiceRequest   (copy.mIsServiceRequest){}

    ValveSProviderWarningsDto& operator=(const ValveSProviderWarningsDto& other)
    {
        ValveSProviderDto::operator=(other);

        mIsServiceRequest = other.mIsServiceRequest   ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mIsServiceReqeust = %2").arg(ValveSProviderDto::toString()).arg(mIsServiceRequest);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWarningsDto);

class ValveSProviderLearnParamDto : public ValveSProviderDto
{
public:
    int mIdx            = 0;
    QString mPointValue = "";
    QString mValue      = "";

    ValveSProviderLearnParamDto(){}
    ValveSProviderLearnParamDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderLearnParamDto(const ValveSProviderLearnParamDto& copy) : ValveSProviderDto(copy),
        mIdx       (copy.mIdx       ),
        mPointValue(copy.mPointValue),
        mValue     (copy.mValue     ){}

    ValveSProviderLearnParamDto& operator=(const ValveSProviderLearnParamDto& other)
    {
        ValveSProviderDto::operator=(other);

        mIdx        = other.mIdx       ;
        mPointValue = other.mPointValue;
        mValue      = other.mValue     ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mIdx = %2, mValue = %3").arg(ValveSProviderDto::toString()).arg(mIdx).arg(mValue);
    }
};

Q_DECLARE_METATYPE(ValveSProviderLearnParamDto);

class ValveSProviderInterfaceConfigLogicDto : public ValveSProviderDto
{
public:
    int mDIOpen     = 0;
    int mDIClose    = 0;
    int mDOOpen     = 0;
    int mDOClose    = 0;
    int mLearnRange = 0;

    ValveSProviderInterfaceConfigLogicDto(){}
    ValveSProviderInterfaceConfigLogicDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderInterfaceConfigLogicDto(const ValveSProviderInterfaceConfigLogicDto& copy) : ValveSProviderDto(copy),
        mDIOpen    (copy.mDIOpen    ),
        mDIClose   (copy.mDIClose   ),
        mDOOpen    (copy.mDOOpen    ),
        mDOClose   (copy.mDOClose   ),
        mLearnRange(copy.mLearnRange){}

    ValveSProviderInterfaceConfigLogicDto& operator=(const ValveSProviderInterfaceConfigLogicDto& other)
    {
        ValveSProviderDto::operator=(other);

        mDIOpen     = other.mDIOpen    ;
        mDIClose    = other.mDIClose   ;
        mDOOpen     = other.mDOOpen    ;
        mDOClose    = other.mDOClose   ;
        mLearnRange = other.mLearnRange;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mDIOpen = %2, mDIClose = %3, mDOOpen = %4, mDOClose = %5, mLearnRange = %6 ")
                       .arg(ValveSProviderDto::toString()).arg(mDIOpen).arg(mDIClose).arg(mDOOpen).arg(mDOClose)
                       .arg(mLearnRange);
    }
};

Q_DECLARE_METATYPE(ValveSProviderInterfaceConfigLogicDto);

class ValveSProviderInterfaceConfigEthCATDiDto : public ValveSProviderDto
{
public:
    int mDIFunction  = 0;
    int mDIMode      = 0;
    int mDIInput     = 0;

    ValveSProviderInterfaceConfigEthCATDiDto(){}
    ValveSProviderInterfaceConfigEthCATDiDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderInterfaceConfigEthCATDiDto(const ValveSProviderInterfaceConfigEthCATDiDto& copy) : ValveSProviderDto(copy),
        mDIFunction(copy.mDIFunction),
        mDIMode    (copy.mDIMode    ),
        mDIInput   (copy.mDIInput   ){}

    ValveSProviderInterfaceConfigEthCATDiDto& operator=(const ValveSProviderInterfaceConfigEthCATDiDto& other)
    {
        ValveSProviderDto::operator=(other);

        mDIFunction = other.mDIFunction;
        mDIMode     = other.mDIMode    ;
        mDIInput    = other.mDIInput   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDIFunction = %2, mDIMode = %3, mDIInput = %4")
                       .arg(ValveSProviderDto::toString()).arg(mDIFunction).arg(mDIMode).arg(mDIInput);
    }
};

Q_DECLARE_METATYPE(ValveSProviderInterfaceConfigEthCATDiDto);

class ValveSProviderInterfaceConfigEthCATDoDto : public ValveSProviderDto
{
public:
    int mDOFunction  = 0;
    int mDOMode      = 0;
    int mDOOutput    = 0;

    ValveSProviderInterfaceConfigEthCATDoDto(){}
    ValveSProviderInterfaceConfigEthCATDoDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderInterfaceConfigEthCATDoDto(const ValveSProviderInterfaceConfigEthCATDoDto& copy) : ValveSProviderDto(copy),
        mDOFunction(copy.mDOFunction),
        mDOMode    (copy.mDOMode    ),
        mDOOutput  (copy.mDOOutput  ){}

    ValveSProviderInterfaceConfigEthCATDoDto& operator=(const ValveSProviderInterfaceConfigEthCATDoDto& other)
    {
        ValveSProviderDto::operator=(other);

        mDOFunction = other.mDOFunction;
        mDOMode     = other.mDOMode    ;
        mDOOutput   = other.mDOOutput  ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDOFunction = %2, mDOMode = %3, mDOOutput = %4")
                       .arg(ValveSProviderDto::toString()).arg(mDOFunction).arg(mDOMode).arg(mDOOutput);
    }
};

Q_DECLARE_METATYPE(ValveSProviderInterfaceConfigEthCATDoDto);

class ValveSProviderInterfaceStatusLogicDto : public ValveSProviderDto
{
public:
    int mStatusDIOpen          = 0;
    int mStatusDIClose         = 0;
    int mStatusDICtrlModel     = 0;
    int mStatusDILearn         = 0;
    int mStatusDIZero          = 0;
    int mStatusDILocked        = 0;
    int mStatusDIHold          = 0;
    int mStatusDISetPointRange = 0;
    int mStatusDOOpen          = 0;
    int mStatusDOClose         = 0;
    int mStatusDOAlarm         = 0;
    int mStatusDOReady         = 0;
    int mAlogInputVoltage      = 0;

    ValveSProviderInterfaceStatusLogicDto(){}
    ValveSProviderInterfaceStatusLogicDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderInterfaceStatusLogicDto(const ValveSProviderInterfaceStatusLogicDto& copy) : ValveSProviderDto(copy),
        mStatusDIOpen         (copy.mStatusDIOpen         ),
        mStatusDIClose        (copy.mStatusDIClose        ),
        mStatusDICtrlModel    (copy.mStatusDICtrlModel    ),
        mStatusDILearn        (copy.mStatusDILearn        ),
        mStatusDIZero         (copy.mStatusDIZero         ),
        mStatusDILocked       (copy.mStatusDILocked       ),
        mStatusDIHold         (copy.mStatusDIHold         ),
        mStatusDISetPointRange(copy.mStatusDISetPointRange),
        mStatusDOOpen         (copy.mStatusDOOpen         ),
        mStatusDOClose        (copy.mStatusDOClose        ),
        mStatusDOAlarm        (copy.mStatusDOAlarm        ),
        mStatusDOReady        (copy.mStatusDOReady        ),
        mAlogInputVoltage     (copy.mAlogInputVoltage     ){}

    ValveSProviderInterfaceStatusLogicDto& operator=(const ValveSProviderInterfaceStatusLogicDto& other)
    {
        ValveSProviderDto::operator=(other);

        mStatusDIOpen          = other.mStatusDIOpen         ;
        mStatusDIClose         = other.mStatusDIClose        ;
        mStatusDICtrlModel     = other.mStatusDICtrlModel    ;
        mStatusDILearn         = other.mStatusDILearn        ;
        mStatusDIZero          = other.mStatusDIZero         ;
        mStatusDILocked        = other.mStatusDILocked       ;
        mStatusDIHold          = other.mStatusDIHold         ;
        mStatusDISetPointRange = other.mStatusDISetPointRange;
        mStatusDOOpen          = other.mStatusDOOpen         ;
        mStatusDOClose         = other.mStatusDOClose        ;
        mStatusDOAlarm         = other.mStatusDOAlarm        ;
        mStatusDOReady         = other.mStatusDOReady        ;
        mAlogInputVoltage      = other.mAlogInputVoltage     ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mStatusDIOpen = %2, mStatusDIClose = %3, mStatusDICtrlModel = %4, mStatusDILearn = %5, mStatusDIZero = %6, mStatusDILocked = %7, mStatusDIHold = %8, mStatusDISetPointRange = %9, mStatusDOOpen = %10, mStatusDOClose = %11, mStatusDOAlarm = %12, mStatusDOReady = %13, mAlogInputVoltage = %14")
                       .arg(ValveSProviderDto::toString()).arg(mStatusDIOpen).arg(mStatusDIClose).arg(mStatusDICtrlModel).arg(mStatusDILearn)
                       .arg(mStatusDIZero).arg(mStatusDILocked).arg(mStatusDIHold).arg(mStatusDISetPointRange).arg(mStatusDOOpen)
                       .arg(mStatusDOClose).arg(mStatusDOAlarm).arg(mStatusDOReady).arg(mAlogInputVoltage);
    }
};

Q_DECLARE_METATYPE(ValveSProviderInterfaceStatusLogicDto);

class ValveSProviderInterfaceStatusEtherCATDto : public ValveSProviderDto
{
public:
    int mStatusDI = 0;
    int mStatusDO = 0;

    ValveSProviderInterfaceStatusEtherCATDto(){}
    ValveSProviderInterfaceStatusEtherCATDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderInterfaceStatusEtherCATDto(const ValveSProviderInterfaceStatusEtherCATDto& copy) : ValveSProviderDto(copy),
        mStatusDI(copy.mStatusDI),
        mStatusDO(copy.mStatusDO){}

    ValveSProviderInterfaceStatusEtherCATDto& operator=(const ValveSProviderInterfaceStatusEtherCATDto& other)
    {
        ValveSProviderDto::operator=(other);

        mStatusDI = other.mStatusDI;
        mStatusDO = other.mStatusDO;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mStatusDI = %2, mStatusDO = %3")
                       .arg(ValveSProviderDto::toString()).arg(mStatusDI).arg(mStatusDO);
    }
};

Q_DECLARE_METATYPE(ValveSProviderInterfaceStatusEtherCATDto);

class ValveSProviderCycleCounterDto : public ValveSProviderDto
{
public:
    qint64 mCycles = 0;

    ValveSProviderCycleCounterDto(){}
    ValveSProviderCycleCounterDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderCycleCounterDto(const ValveSProviderCycleCounterDto& copy) : ValveSProviderDto(copy),
        mCycles   (copy.mCycles){}

    ValveSProviderCycleCounterDto& operator=(const ValveSProviderCycleCounterDto& other)
    {
        ValveSProviderDto::operator=(other);

        mCycles = other.mCycles   ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mCycles = %2").arg(ValveSProviderDto::toString()).arg(mCycles);
    }
};

Q_DECLARE_METATYPE(ValveSProviderCycleCounterDto);

class ValveSProviderSensorOffsetDto : public ValveSProviderDto
{
public:
    int mVoltage = 0;

    ValveSProviderSensorOffsetDto(){}
    ValveSProviderSensorOffsetDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderSensorOffsetDto(const ValveSProviderSensorOffsetDto& copy) : ValveSProviderDto(copy),
        mVoltage   (copy.mVoltage){}

    ValveSProviderSensorOffsetDto& operator=(const ValveSProviderSensorOffsetDto& other)
    {
        ValveSProviderDto::operator=(other);

        mVoltage = other.mVoltage   ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mVoltage = %2").arg(ValveSProviderDto::toString()).arg(mVoltage);
    }
};

Q_DECLARE_METATYPE(ValveSProviderSensorOffsetDto);

class ValveSProviderLearnPressureLimitDto : public ValveSProviderDto
{
public:
    int mPressureLimit = 0;

    ValveSProviderLearnPressureLimitDto(){}
    ValveSProviderLearnPressureLimitDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderLearnPressureLimitDto(const ValveSProviderLearnPressureLimitDto& copy) : ValveSProviderDto(copy),
        mPressureLimit   (copy.mPressureLimit){}

    ValveSProviderLearnPressureLimitDto& operator=(const ValveSProviderLearnPressureLimitDto& other)
    {
        ValveSProviderDto::operator=(other);

        mPressureLimit = other.mPressureLimit   ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mPressureLimit = %2").arg(ValveSProviderDto::toString()).arg(mPressureLimit);
    }
};

Q_DECLARE_METATYPE(ValveSProviderLearnPressureLimitDto);

class ValveSProviderLearnStatusDto : public ValveSProviderDto
{
public:
    int mRunning           = 0;
    int mDataSetPresent    = 0;
    int mAbort             = 0;
    int mIsOKOpenPressure  = 0;
    int mIsOKClosePressure = 0;
    int mPressureRaising   = 0;
    int mPressureStability = 0;

    ValveSProviderLearnStatusDto(){}
    ValveSProviderLearnStatusDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderLearnStatusDto(const ValveSProviderLearnStatusDto& copy) : ValveSProviderDto(copy),
        mRunning          (copy.mRunning          ),
        mDataSetPresent   (copy.mDataSetPresent   ),
        mAbort            (copy.mAbort            ),
        mIsOKOpenPressure (copy.mIsOKOpenPressure ),
        mIsOKClosePressure(copy.mIsOKClosePressure),
        mPressureRaising  (copy.mPressureRaising  ),
        mPressureStability(copy.mPressureStability){}

    ValveSProviderLearnStatusDto& operator=(const ValveSProviderLearnStatusDto& other)
    {
        ValveSProviderDto::operator=(other);

        mRunning           = other.mRunning          ;
        mDataSetPresent    = other.mDataSetPresent   ;
        mAbort             = other.mAbort            ;
        mIsOKOpenPressure  = other.mIsOKOpenPressure ;
        mIsOKClosePressure = other.mIsOKClosePressure;
        mPressureRaising   = other.mPressureRaising  ;
        mPressureStability = other.mPressureStability;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mRunning = %2, mDataSetPresent = %3, mAbort = %4, mIsOKOpenPressure = %5, mIsOKClosePressure = %6, mPressureRaising = %7,, mPressureStability = %8")
                .arg(ValveSProviderDto::toString())
                .arg(mRunning          )
                .arg(mDataSetPresent   )
                .arg(mAbort            )
                .arg(mIsOKOpenPressure )
                .arg(mIsOKClosePressure)
                .arg(mPressureRaising  )
                .arg(mPressureStability);
    }
};

Q_DECLARE_METATYPE(ValveSProviderLearnStatusDto);

class ValveSProviderWriteAccessDto : public ValveSProviderDto
{
public:
    int mReqAccess;

    ValveSProviderWriteAccessDto(){}
    ValveSProviderWriteAccessDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteAccessDto(const ValveSProviderWriteAccessDto& copy) : ValveSProviderDto(copy),
        mReqAccess(copy.mReqAccess){}

    ValveSProviderWriteAccessDto& operator=(const ValveSProviderWriteAccessDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqAccess = other.mReqAccess;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqAccess = %2")
                .arg(ValveSProviderDto::toString())
                .arg(mReqAccess);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteAccessDto);

class ValveSProviderWritePositionDto : public ValveSProviderDto
{
public:
    qint64 mReqPosition;

    ValveSProviderWritePositionDto(){}
    ValveSProviderWritePositionDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWritePositionDto(const ValveSProviderWritePositionDto& copy) : ValveSProviderDto(copy),
        mReqPosition(copy.mReqPosition){}

    ValveSProviderWritePositionDto& operator=(const ValveSProviderWritePositionDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqPosition = other.mReqPosition;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqPosition = %2")
                .arg(ValveSProviderDto::toString())
                .arg(mReqPosition);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWritePositionDto);

class ValveSProviderWritePressureDto : public ValveSProviderDto
{
public:
    qint64 mReqPressure;

    ValveSProviderWritePressureDto(){}
    ValveSProviderWritePressureDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWritePressureDto(const ValveSProviderWritePressureDto& copy) : ValveSProviderDto(copy),
        mReqPressure(copy.mReqPressure){}

    ValveSProviderWritePressureDto& operator=(const ValveSProviderWritePressureDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqPressure = other.mReqPressure;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqPressure = %2")
                .arg(ValveSProviderDto::toString())
                .arg(mReqPressure);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWritePressureDto);

class ValveSProviderWriteValveSpeedDto : public ValveSProviderDto
{
public:
    int mReqSpeed;

    ValveSProviderWriteValveSpeedDto(){}
    ValveSProviderWriteValveSpeedDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteValveSpeedDto(const ValveSProviderWriteValveSpeedDto& copy) : ValveSProviderDto(copy),
        mReqSpeed(copy.mReqSpeed){}

    ValveSProviderWriteValveSpeedDto& operator=(const ValveSProviderWriteValveSpeedDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqSpeed = other.mReqSpeed;
        return *this;
    }

    QString toString()
    {
        return QString("%1, retryCnt = %2, mReqSpeed = %3")
                .arg(ValveSProviderDto::toString())
                .arg(mRetryCnt   )
                .arg(mReqSpeed   );
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteValveSpeedDto);

class ValveSProviderWriteValveSetupDto : public ValveSProviderDto
{
public:
    int mReqTargetPosSync       ;
    int mReqEventSync           ;
    int mReqStrokeLimitation    ;
    int mReqTargetPosPowerFail  ;
    int mReqTargetPosNetworkFail;

    ValveSProviderWriteValveSetupDto(){}
    ValveSProviderWriteValveSetupDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteValveSetupDto(const ValveSProviderWriteValveSetupDto& copy) : ValveSProviderDto(copy),
        mReqTargetPosSync       (copy.mReqTargetPosSync       ),
        mReqEventSync           (copy.mReqEventSync           ),
        mReqStrokeLimitation    (copy.mReqStrokeLimitation    ),
        mReqTargetPosPowerFail  (copy.mReqTargetPosPowerFail  ),
        mReqTargetPosNetworkFail(copy.mReqTargetPosNetworkFail){}

    ValveSProviderWriteValveSetupDto& operator=(const ValveSProviderWriteValveSetupDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqTargetPosSync        = other.mReqTargetPosSync       ;
        mReqEventSync            = other.mReqEventSync           ;
        mReqStrokeLimitation     = other.mReqStrokeLimitation    ;
        mReqTargetPosPowerFail   = other.mReqTargetPosPowerFail  ;
        mReqTargetPosNetworkFail = other.mReqTargetPosNetworkFail;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqTargetPosSync = %2, mReqEventSync = %3, mReqStrokeLimitation = %4, mReqTargetPosPowerFail = %5, mReqTargetPosNetworkFail = %6")
                .arg(ValveSProviderDto::toString())
                .arg(mReqTargetPosSync       )
                .arg(mReqEventSync           )
                .arg(mReqStrokeLimitation    )
                .arg(mReqTargetPosPowerFail  )
                .arg(mReqTargetPosNetworkFail);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteValveSetupDto);

class ValveSProviderWriteSensorConfigDto : public ValveSProviderDto
{
public:
    int  mReqSensorOp    ;
    bool mZeroEnable      = false;
    int  mReqHighLowRatio;

    ValveSProviderWriteSensorConfigDto(){}
    ValveSProviderWriteSensorConfigDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteSensorConfigDto(const ValveSProviderWriteSensorConfigDto& copy) : ValveSProviderDto(copy),
        mReqSensorOp    (copy.mReqSensorOp    ),
        mZeroEnable     (copy.mZeroEnable     ),
        mReqHighLowRatio(copy.mReqHighLowRatio){}

    ValveSProviderWriteSensorConfigDto& operator=(const ValveSProviderWriteSensorConfigDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqSensorOp     = other.mReqSensorOp    ;
        mZeroEnable      = other.mZeroEnable     ;
        mReqHighLowRatio = other.mReqHighLowRatio;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqSensorOp = %2, mZeroEnable = %3, mReqHighLowRatio = %4")
                .arg(ValveSProviderDto::toString())
                .arg(mReqSensorOp    )
                .arg(mZeroEnable     )
                .arg(mReqHighLowRatio);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteSensorConfigDto);

class ValveSProviderWriteSensorScaleDto : public ValveSProviderDto
{
public:
    //bool mReqIsSensor02Support;
    int  mReqSensor01Unit     ;
    int  mReqSensor01FullScale;
    int  mReqSensor01SignExp  ;
    int  mReqSensor01Exp      ;
    int  mReqSensor02Unit     ;
    int  mReqSensor02FullScale;
    int  mReqSensor02SignExp  ;
    int  mReqSensor02Exp      ;

    ValveSProviderWriteSensorScaleDto(){}
    ValveSProviderWriteSensorScaleDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteSensorScaleDto(const ValveSProviderWriteSensorScaleDto& copy) : ValveSProviderDto(copy),
        mReqSensor01Unit     (copy.mReqSensor01Unit     ),
        mReqSensor01FullScale(copy.mReqSensor01FullScale),
        mReqSensor01SignExp  (copy.mReqSensor01SignExp  ),
        mReqSensor01Exp      (copy.mReqSensor01Exp      ),
        mReqSensor02Unit     (copy.mReqSensor02Unit     ),
        mReqSensor02FullScale(copy.mReqSensor02FullScale),
        mReqSensor02SignExp  (copy.mReqSensor02SignExp  ),
        mReqSensor02Exp      (copy.mReqSensor02Exp      ){}

    ValveSProviderWriteSensorScaleDto& operator=(const ValveSProviderWriteSensorScaleDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqSensor01Unit      = other.mReqSensor01Unit     ;
        mReqSensor01FullScale = other.mReqSensor01FullScale;
        mReqSensor01SignExp   = other.mReqSensor01SignExp  ;
        mReqSensor01Exp       = other.mReqSensor01Exp      ;
        mReqSensor02Unit      = other.mReqSensor02Unit     ;
        mReqSensor02FullScale = other.mReqSensor02FullScale;
        mReqSensor02SignExp   = other.mReqSensor02SignExp  ;
        mReqSensor02Exp       = other.mReqSensor02Exp      ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqSensor01Unit = %2, mReqSensor01FullScale = %3, mReqSensor01SignExp = %4, mReqSensor01Exp = %5, mReqSensor02Unit = %6, mReqSensor02FullScale = %7, mReqSensor02SignExp = %8, mReqSensor02Exp = %9")
                .arg(ValveSProviderDto::toString())
                .arg(mReqSensor01Unit     )
                .arg(mReqSensor01FullScale)
                .arg(mReqSensor01SignExp  )
                .arg(mReqSensor01Exp      )
                .arg(mReqSensor02Unit     )
                .arg(mReqSensor02FullScale)
                .arg(mReqSensor02SignExp  )
                .arg(mReqSensor02Exp      );
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteSensorScaleDto);

class ValveSProviderWriteDisplayConfigDto : public ValveSProviderDto
{
public:
    int mReqPositionResolution ;
    int mReqPressureDpUnit     ;
    int mReqPressureAxisMapping;
    int mReqPressureDecades    ;

    ValveSProviderWriteDisplayConfigDto(){}
    ValveSProviderWriteDisplayConfigDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteDisplayConfigDto(const ValveSProviderWriteDisplayConfigDto& copy) : ValveSProviderDto(copy),
        mReqPositionResolution (copy.mReqPositionResolution ),
        mReqPressureDpUnit     (copy.mReqPressureDpUnit     ),
        mReqPressureAxisMapping(copy.mReqPressureAxisMapping),
        mReqPressureDecades    (copy.mReqPressureDecades    ){}

    ValveSProviderWriteDisplayConfigDto& operator=(const ValveSProviderWriteDisplayConfigDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqPositionResolution  = other.mReqPositionResolution ;
        mReqPressureDpUnit      = other.mReqPressureDpUnit     ;
        mReqPressureAxisMapping = other.mReqPressureAxisMapping;
        mReqPressureDecades     = other.mReqPressureDecades    ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqPositionResolution = %2, mReqPressureDpUnit = %3, mReqPressureAxisMapping = %4, mReqPressureDecades = %5")
                .arg(ValveSProviderDto::toString())
                .arg(mReqPositionResolution )
                .arg(mReqPressureDpUnit     )
                .arg(mReqPressureAxisMapping)
                .arg(mReqPressureDecades    );
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteDisplayConfigDto);

class ValveSProviderWritePressureCtrlConfigDto : public ValveSProviderDto
{
public:
    int mReqGainFac    ;
    int mReqSensorDelay;
    int mReqRampTime   ;

    ValveSProviderWritePressureCtrlConfigDto(){}
    ValveSProviderWritePressureCtrlConfigDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWritePressureCtrlConfigDto(const ValveSProviderWritePressureCtrlConfigDto& copy) : ValveSProviderDto(copy),
        mReqGainFac    (copy.mReqGainFac    ),
        mReqSensorDelay(copy.mReqSensorDelay),
        mReqRampTime   (copy.mReqRampTime   ){}

    ValveSProviderWritePressureCtrlConfigDto& operator=(const ValveSProviderWritePressureCtrlConfigDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqGainFac     = other.mReqGainFac    ;
        mReqSensorDelay = other.mReqSensorDelay;
        mReqRampTime    = other.mReqRampTime   ;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqGainFac = %2, mReqSensorDelay = %3, mReqRampTime = %4")
                .arg(ValveSProviderDto::toString())
                .arg(mReqGainFac    )
                .arg(mReqSensorDelay)
                .arg(mReqRampTime   );
    }
};

Q_DECLARE_METATYPE(ValveSProviderWritePressureCtrlConfigDto);

class ValveSProviderWriteInterfaceConfigLogicDto : public ValveSProviderDto
{
public:
    int mReqDiOpen    ;
    int mReqDiClose   ;
    int mReqDoOpen    ;
    int mReqDoClose   ;
    int mReqLearnRange;

    ValveSProviderWriteInterfaceConfigLogicDto(){}
    ValveSProviderWriteInterfaceConfigLogicDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteInterfaceConfigLogicDto(const ValveSProviderWriteInterfaceConfigLogicDto& copy) : ValveSProviderDto(copy),
        mReqDiOpen    (copy.mReqDiOpen    ),
        mReqDiClose   (copy.mReqDiClose   ),
        mReqDoOpen    (copy.mReqDoOpen    ),
        mReqDoClose   (copy.mReqDoClose   ),
        mReqLearnRange(copy.mReqLearnRange){}

    ValveSProviderWriteInterfaceConfigLogicDto& operator=(const ValveSProviderWriteInterfaceConfigLogicDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqDiOpen     = other.mReqDiOpen    ;
        mReqDiClose    = other.mReqDiClose   ;
        mReqDoOpen     = other.mReqDoOpen    ;
        mReqDoClose    = other.mReqDoClose   ;
        mReqLearnRange = other.mReqLearnRange;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqDiOpen = %2, mReqDiClose = %3, mReqDoOpen = %4 , mReqDoClose = %5, mReqLearnRange = %6")
                .arg(ValveSProviderDto::toString())
                .arg(mReqDiOpen     )
                .arg(mReqDiClose    )
                .arg(mReqDoOpen     )
                .arg(mReqDoClose    )
                .arg(mReqLearnRange );
    }
};
Q_DECLARE_METATYPE(ValveSProviderWriteInterfaceConfigLogicDto);

class ValveSProviderWriteInterfaceConfigEthCATDiDto : public ValveSProviderDto
{
public:
    int mReqDiFunction;
    int mReqDiMode    ;
    int mReqDiInput   ;

    ValveSProviderWriteInterfaceConfigEthCATDiDto(){}
    ValveSProviderWriteInterfaceConfigEthCATDiDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteInterfaceConfigEthCATDiDto(const ValveSProviderWriteInterfaceConfigEthCATDiDto& copy) : ValveSProviderDto(copy),
        mReqDiFunction(copy.mReqDiFunction),
        mReqDiMode    (copy.mReqDiMode    ),
        mReqDiInput   (copy.mReqDiInput   ){}

    ValveSProviderWriteInterfaceConfigEthCATDiDto& operator=(const ValveSProviderWriteInterfaceConfigEthCATDiDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqDiFunction = other.mReqDiFunction;
        mReqDiMode     = other.mReqDiMode    ;
        mReqDiInput    = other.mReqDiInput   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqDiFunction = %2, mReqDiMode = %3, mReqDiInput = %4,")
                .arg(ValveSProviderDto::toString())
                .arg(mReqDiFunction)
                .arg(mReqDiMode    )
                .arg(mReqDiInput   );
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteInterfaceConfigEthCATDiDto);

class ValveSProviderWriteInterfaceConfigEthCATDoDto : public ValveSProviderDto
{
public:
    int mReqDoFunction;
    int mReqDoMode    ;
    int mReqDoOutput  ;

    ValveSProviderWriteInterfaceConfigEthCATDoDto(){}
    ValveSProviderWriteInterfaceConfigEthCATDoDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteInterfaceConfigEthCATDoDto(const ValveSProviderWriteInterfaceConfigEthCATDoDto& copy) : ValveSProviderDto(copy),
        mReqDoFunction(copy.mReqDoFunction),
        mReqDoMode    (copy.mReqDoMode    ),
        mReqDoOutput  (copy.mReqDoOutput  ){}

    ValveSProviderWriteInterfaceConfigEthCATDoDto& operator=(const ValveSProviderWriteInterfaceConfigEthCATDoDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqDoFunction = other.mReqDoFunction;
        mReqDoMode     = other.mReqDoMode    ;
        mReqDoOutput   = other.mReqDoOutput  ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqDoFunction = %2, mReqDoMode = %3, mReqDoOutput = %4 ")
                .arg(ValveSProviderDto::toString())
                .arg(mReqDoFunction)
                .arg(mReqDoMode    )
                .arg(mReqDoOutput  );
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteInterfaceConfigEthCATDoDto);

class ValveSProviderWriteLearnDto : public ValveSProviderDto
{
public:
    int mReqPressureLimit;

    ValveSProviderWriteLearnDto(){}
    ValveSProviderWriteLearnDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteLearnDto(const ValveSProviderWriteLearnDto& copy) : ValveSProviderDto(copy),
        mReqPressureLimit(copy.mReqPressureLimit){}

    ValveSProviderWriteLearnDto& operator=(const ValveSProviderWriteLearnDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqPressureLimit = other.mReqPressureLimit;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqPressureLimit = %2")
                .arg(ValveSProviderDto::toString())
                .arg(mReqPressureLimit);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteLearnDto);

class ValveSProviderWriteSimulationDto : public ValveSProviderDto
{
public:
    int mReqIsSim;

    ValveSProviderWriteSimulationDto(){}
    ValveSProviderWriteSimulationDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderWriteSimulationDto(const ValveSProviderWriteSimulationDto& copy) : ValveSProviderDto(copy),
        mReqIsSim(copy.mReqIsSim){}

    ValveSProviderWriteSimulationDto& operator=(const ValveSProviderWriteSimulationDto& other)
    {
        ValveSProviderDto::operator=(other);

        mReqIsSim = other.mReqIsSim;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mReqIsSim = %2")
                .arg(ValveSProviderDto::toString())
                .arg(mReqIsSim);
    }
};

Q_DECLARE_METATYPE(ValveSProviderWriteSimulationDto);

class ValveSProviderSetPointDto : public ValveSProviderDto
{
public:
    int mPosition;
    int mPressure;

    ValveSProviderSetPointDto(){}
    ValveSProviderSetPointDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderSetPointDto(const ValveSProviderSetPointDto& copy) : ValveSProviderDto(copy),
        mPosition(copy.mPosition),
        mPressure(copy.mPressure){}

    ValveSProviderSetPointDto& operator=(const ValveSProviderSetPointDto& other)
    {
        ValveSProviderDto::operator=(other);

        mPosition = other.mPosition;
        mPressure = other.mPressure;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mPosition = %2, mPressure = %3")
                .arg(ValveSProviderDto::toString())
                .arg(mPosition)
                .arg(mPressure);
    }
};

Q_DECLARE_METATYPE(ValveSProviderSetPointDto);

class ValveSProviderPFOPerformedCyclesDto : public ValveSProviderDto
{
public:
    int mPerformedCycles;

    ValveSProviderPFOPerformedCyclesDto(){}
    ValveSProviderPFOPerformedCyclesDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderPFOPerformedCyclesDto(const ValveSProviderPFOPerformedCyclesDto& copy) : ValveSProviderDto(copy),
        mPerformedCycles(copy.mPerformedCycles){}

    ValveSProviderPFOPerformedCyclesDto& operator=(const ValveSProviderPFOPerformedCyclesDto& other)
    {
        ValveSProviderDto::operator=(other);

        mPerformedCycles = other.mPerformedCycles;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mPerformedCycles = %2")
                .arg(ValveSProviderDto::toString())
                .arg(mPerformedCycles);
    }
};

Q_DECLARE_METATYPE(ValveSProviderPFOPerformedCyclesDto);

class ValveSProviderPFOCurrentVoltageDto : public ValveSProviderDto
{
public:
    QDateTime mDateTime;
    int       mCurrentVoltage;

    ValveSProviderPFOCurrentVoltageDto(){}
    ValveSProviderPFOCurrentVoltageDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderPFOCurrentVoltageDto(const ValveSProviderPFOCurrentVoltageDto& copy) : ValveSProviderDto(copy),
        mDateTime      (copy.mDateTime      ),
        mCurrentVoltage(copy.mCurrentVoltage){}

    ValveSProviderPFOCurrentVoltageDto& operator=(const ValveSProviderPFOCurrentVoltageDto& other)
    {
        ValveSProviderDto::operator=(other);

        mDateTime       = other.mDateTime      ;
        mCurrentVoltage = other.mCurrentVoltage;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mDateTime = %2, mCurrentVoltage = %3")
                .arg(ValveSProviderDto::toString())
                .arg(mDateTime.toString())
                .arg(mCurrentVoltage);
    }
};

Q_DECLARE_METATYPE(ValveSProviderPFOCurrentVoltageDto);

class ValveSProviderFatalErrPosDto : public ValveSProviderDto
{
public:
    int mErrPosition  ;
    int mTotalPosition;

    ValveSProviderFatalErrPosDto(){}
    ValveSProviderFatalErrPosDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderFatalErrPosDto(const ValveSProviderFatalErrPosDto& copy) : ValveSProviderDto(copy),
        mErrPosition  (copy.mErrPosition  ),
        mTotalPosition(copy.mTotalPosition){}

    ValveSProviderFatalErrPosDto& operator=(const ValveSProviderFatalErrPosDto& other)
    {
        ValveSProviderDto::operator=(other);

        mErrPosition   = other.mErrPosition  ;
        mTotalPosition = other.mTotalPosition;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mErrPosition = %2, mTotalPosition = %3")
                .arg(ValveSProviderDto::toString())
                .arg(mErrPosition  )
                .arg(mTotalPosition);
    }
};

Q_DECLARE_METATYPE(ValveSProviderFatalErrPosDto);

class ValveSProviderSimpleValueDto : public ValveSProviderDto
{
public:
    QString mStrValue;

    ValveSProviderSimpleValueDto(){}
    ValveSProviderSimpleValueDto(bool isSucc, bool isNetworkErr, QString errMsg, int retryCnt, void * pRef) : ValveSProviderDto(isSucc, isNetworkErr, errMsg, retryCnt, pRef){}
    ValveSProviderSimpleValueDto(const ValveSProviderSimpleValueDto& copy) : ValveSProviderDto(copy),
        mStrValue(copy.mStrValue){}

    ValveSProviderSimpleValueDto& operator=(const ValveSProviderSimpleValueDto& other)
    {
        ValveSProviderDto::operator=(other);

        mStrValue = other.mStrValue;
        return *this;
    }

    QString toString()
    {
        return QString("%1, mStrValue = %2")
                .arg(ValveSProviderDto::toString())
                .arg(mStrValue  );
    }
};

Q_DECLARE_METATYPE(ValveSProviderSimpleValueDto);
#endif // VALVESPROVIDERDTO_H
