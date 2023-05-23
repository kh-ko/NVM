#ifndef VALVESPROVIDERDTOEX_H
#define VALVESPROVIDERDTOEX_H

#include <QObject>
#include <QDateTime>
#include <QtMath>

class ValveRequestDto
{
public:
    void      * mpValveSProvider = nullptr;
    void      (* mMainProcFunc)(void * pResData) = nullptr;
    void      (* mSubProcFunc )(void * pResData) = nullptr;
    QString   mReqCommand   = "";
    QString   mCheckString  = "";
    int       mCheckLen     = 0;
    int       mRetryCnt     = 0;
    void    * mpRef         = nullptr;

    ValveRequestDto(){}
    ValveRequestDto(void * pValveSProvider,
                    void (* mainProcFunc)(void * pResData),
                    void (* subProcFunc )(void * pResData),
                    QString reqCommand, QString checkString, int checkLen, int retryCnt, void * pRef)
    {
        mpValveSProvider = pValveSProvider;
        mMainProcFunc    = mainProcFunc;
        mSubProcFunc     = subProcFunc ;
        mReqCommand      = reqCommand  ;
        mCheckString     = checkString ;
        mCheckLen        = checkLen    ;
        mRetryCnt        = retryCnt    ;
        mpRef            = pRef        ;
    }
    ValveRequestDto(const ValveRequestDto& copy) :
        mpValveSProvider(copy.mpValveSProvider),
        mMainProcFunc   (copy.mMainProcFunc   ),
        mSubProcFunc    (copy.mSubProcFunc    ),
        mReqCommand     (copy.mReqCommand     ),
        mCheckString    (copy.mCheckString    ),
        mCheckLen       (copy.mCheckLen       ),
        mRetryCnt       (copy.mRetryCnt       ),
        mpRef           (copy.mpRef           ){}

    ~ValveRequestDto(){}

    ValveRequestDto& operator=(const ValveRequestDto& other)
    {
        mpValveSProvider = other.mpValveSProvider;
        mMainProcFunc    = other.mMainProcFunc   ;
        mSubProcFunc     = other.mSubProcFunc    ;
        mReqCommand      = other.mReqCommand     ;
        mCheckString     = other.mCheckString    ;
        mCheckLen        = other.mCheckLen       ;
        mRetryCnt        = other.mRetryCnt       ;
        mpRef            = other.mpRef           ;

        return *this;
    }

    QString toString()
    {
        return QString("mReqCommand = %1, mCheckString = %2, mCheckLen = %3, mRetryCnt = %4, mpRef = %5").arg(mReqCommand).arg(mCheckString).arg(mCheckLen).arg(mRetryCnt).arg((quint64)mpRef);
    }
};
Q_DECLARE_METATYPE(ValveRequestDto);

class ValveResponseDto
{
public:
    ValveRequestDto mReqDto;

    QDateTime mResDateTime;
    QString   mResData      = "";
    bool      mIsParsed     = false;
    bool      mIsSucc       = false;
    bool      mIsNetworkErr = false;
    QString   mErrMsg       = "";

    ValveResponseDto(){}
    ValveResponseDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg ="")
    {
        mReqDto       = reqDto      ;
        mResDateTime  = resDateTime ;
        mResData      = resData     ;
        mIsParsed     = isParsed    ;
        mIsSucc       = isSucc      ;
        mIsNetworkErr = isNetworkErr;
        mErrMsg       = errMsg      ;
    }
    ValveResponseDto(const ValveResponseDto& copy) :
        mReqDto      (copy.mReqDto      ),
        mResDateTime (copy.mResDateTime ),
        mResData     (copy.mResData     ),
        mIsParsed    (copy.mIsParsed    ),
        mIsSucc      (copy.mIsSucc      ),
        mIsNetworkErr(copy.mIsNetworkErr),
        mErrMsg      (copy.mErrMsg      ){}

    ~ValveResponseDto(){}

    ValveResponseDto& operator=(const ValveResponseDto& other)
    {
        mReqDto       = other.mReqDto      ;
        mResDateTime  = other.mResDateTime ;
        mResData      = other.mResData     ;
        mIsParsed     = other.mIsParsed    ;
        mIsSucc       = other.mIsSucc      ;
        mIsNetworkErr = other.mIsNetworkErr;
        mErrMsg       = other.mErrMsg      ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mResDateTime = %2  mResponseData = %3, mIsSucc = %4, mIsNetworkErr = %5, mErrMsg = %6").arg(mReqDto.toString()).arg(mResDateTime.toString("mm-hh-ss.zzz")).arg(mResData).arg(mIsSucc).arg(mIsNetworkErr).arg(mErrMsg);
    }
};
Q_DECLARE_METATYPE(ValveResponseDto);

class ValveResponseHWConfigDto : public ValveResponseDto
{
public:
    bool             mIsSupportPFO = false;
    bool             mIsSupportSPS = false;
    int              mInterface    = 0;
    int              mSensorVerion = 1;

    ValveResponseHWConfigDto(){}
    ValveResponseHWConfigDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseHWConfigDto(ValveResponseDto baseDto): ValveResponseDto(baseDto){}
    ValveResponseHWConfigDto(const ValveResponseHWConfigDto& copy):ValveResponseDto(copy),
        mIsSupportPFO(copy.mIsSupportPFO),
        mIsSupportSPS(copy.mIsSupportSPS),
        mInterface   (copy.mInterface   ),
        mSensorVerion(copy.mSensorVerion){}

    ~ValveResponseHWConfigDto(){}

    ValveResponseHWConfigDto& operator=(const ValveResponseHWConfigDto& other)
    {
        ValveResponseDto::operator=(other);

        mIsSupportPFO = other.mIsSupportPFO;
        mIsSupportSPS = other.mIsSupportSPS;
        mInterface    = other.mInterface   ;
        mSensorVerion = other.mSensorVerion;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mIsSupportPFO = %2, mIsSupportSPS = %3, mInterface = %4, mSensorVerion = %5").arg(ValveResponseDto::toString()).arg(mIsSupportPFO).arg(mIsSupportSPS).arg(mInterface).arg(mSensorVerion);
    }
};

Q_DECLARE_METATYPE(ValveResponseHWConfigDto);

class ValveResponseFirmwareVersionDto : public ValveResponseDto
{
public:
    QString mFirmwareVersion = "";

    ValveResponseFirmwareVersionDto(){}
    ValveResponseFirmwareVersionDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseFirmwareVersionDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseFirmwareVersionDto(const ValveResponseFirmwareVersionDto& copy) : ValveResponseDto(copy),
        mFirmwareVersion(copy.mFirmwareVersion){}

    ~ValveResponseFirmwareVersionDto(){}

    ValveResponseFirmwareVersionDto& operator=(const ValveResponseFirmwareVersionDto& other)
    {
        ValveResponseDto::operator=(other);

        mFirmwareVersion = other.mFirmwareVersion;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mFirmwareVersion = %2").arg(ValveResponseDto::toString()).arg(mFirmwareVersion);
    }
};

Q_DECLARE_METATYPE(ValveResponseFirmwareVersionDto);

class ValveResponseValveIdDto : public ValveResponseDto
{
public:
    QString mValveID = "";

    ValveResponseValveIdDto(){}
    ValveResponseValveIdDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseValveIdDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseValveIdDto(const ValveResponseValveIdDto& copy) : ValveResponseDto(copy),
        mValveID(copy.mValveID){}

    ~ValveResponseValveIdDto(){}

    ValveResponseValveIdDto& operator=(const ValveResponseValveIdDto& other)
    {
        ValveResponseDto::operator=(other);

        mValveID = other.mValveID;

        return *this;
    }

    QString toString()
    {
        return QString("%1, valveID = %2").arg(ValveResponseDto::toString()).arg(mValveID);
    }
};

Q_DECLARE_METATYPE(ValveResponseValveIdDto);

class ValveResponseSensorConfigDto : public ValveResponseDto
{
public:
    int    mSensorOperation = 0;
    bool   mZeroEnable      = false;
    qint64 mFullScaleRatio  = 0;


    ValveResponseSensorConfigDto(){}
    ValveResponseSensorConfigDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSensorConfigDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSensorConfigDto(const ValveResponseSensorConfigDto& copy) : ValveResponseDto(copy),
        mSensorOperation(copy.mSensorOperation),
        mZeroEnable     (copy.mZeroEnable     ),
        mFullScaleRatio (copy.mFullScaleRatio ){}

    ~ValveResponseSensorConfigDto(){}

    ValveResponseSensorConfigDto& operator=(const ValveResponseSensorConfigDto& other)
    {
        ValveResponseDto::operator=(other);

        mSensorOperation = other.mSensorOperation;
        mZeroEnable      = other.mZeroEnable     ;
        mFullScaleRatio  = other.mFullScaleRatio ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, SensorOp = %2, ZeroEnable = %3, FullScaleRatio = %4").arg(ValveResponseDto::toString()).arg(mSensorOperation).arg(mZeroEnable).arg(mFullScaleRatio);
    }
};

Q_DECLARE_METATYPE(ValveResponseSensorConfigDto);

class ValveResponseSensorOffsetValuesDto : public ValveResponseDto
{
public:
    double mS01Offset = 0;
    double mS02Offset = 0;

    ValveResponseSensorOffsetValuesDto(){}
    ValveResponseSensorOffsetValuesDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSensorOffsetValuesDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSensorOffsetValuesDto(const ValveResponseSensorOffsetValuesDto& copy) : ValveResponseDto(copy),
        mS01Offset(copy.mS01Offset),
        mS02Offset(copy.mS02Offset){}

    ~ValveResponseSensorOffsetValuesDto(){}

    ValveResponseSensorOffsetValuesDto& operator=(const ValveResponseSensorOffsetValuesDto& other)
    {
        ValveResponseDto::operator=(other);

        mS01Offset = other.mS01Offset;
        mS02Offset = other.mS02Offset;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mS01Offset = %2, mS02Offset = %3").arg(ValveResponseDto::toString()).arg(mS01Offset).arg(mS02Offset);
    }
};

Q_DECLARE_METATYPE(ValveResponseSensorOffsetValuesDto);

class ValveResponseSensorValueDto : public ValveResponseDto
{
public:
    double mResultingValue = 0;
    double mS01Value       = 0;
    double mS02Value       = 0;

    ValveResponseSensorValueDto(){}
    ValveResponseSensorValueDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSensorValueDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSensorValueDto(const ValveResponseSensorValueDto& copy) : ValveResponseDto(copy),
        mResultingValue(copy.mResultingValue),
        mS01Value      (copy.mS01Value      ),
        mS02Value      (copy.mS02Value      ){}

    ~ValveResponseSensorValueDto(){}

    ValveResponseSensorValueDto& operator=(const ValveResponseSensorValueDto& other)
    {
        ValveResponseDto::operator=(other);

        mResultingValue  = other.mResultingValue;
        mS01Value        = other.mS01Value      ;
        mS02Value        = other.mS02Value      ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mResultingValue = %2, mS01Value = %3, mS02Value = %4").arg(ValveResponseDto::toString()).arg(mResultingValue).arg(mS01Value).arg(mS02Value);
    }
};

Q_DECLARE_METATYPE(ValveResponseSensorValueDto);

class ValveResponseSensorSelectionDto : public ValveResponseDto
{
public:
    bool mS01Selected = false;
    bool mS02Selected = false;

    ValveResponseSensorSelectionDto(){}
    ValveResponseSensorSelectionDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSensorSelectionDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSensorSelectionDto(const ValveResponseSensorSelectionDto& copy) : ValveResponseDto(copy),
        mS01Selected(copy.mS01Selected),
        mS02Selected(copy.mS02Selected){}

    ~ValveResponseSensorSelectionDto(){}

    ValveResponseSensorSelectionDto& operator=(const ValveResponseSensorSelectionDto& other)
    {
        ValveResponseDto::operator=(other);

        mS01Selected = other.mS01Selected;
        mS02Selected = other.mS02Selected;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mS01Selected = %2, mS02Selected = %3").arg(ValveResponseDto::toString()).arg(mS01Selected).arg(mS02Selected);
    }
};

Q_DECLARE_METATYPE(ValveResponseSensorSelectionDto);

class ValveResponsePressureCtrlConfigDto : public ValveResponseDto
{
public:
    int mCtrlMode    = 0;
    int mGainFactor  = 0;
    int mSensorDelay = 0;
    int mRampTime    = 0;

    ValveResponsePressureCtrlConfigDto(){}
    ValveResponsePressureCtrlConfigDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponsePressureCtrlConfigDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponsePressureCtrlConfigDto(const ValveResponsePressureCtrlConfigDto& copy) : ValveResponseDto(copy),
        mCtrlMode   (copy.mCtrlMode   ),
        mGainFactor (copy.mGainFactor ),
        mSensorDelay(copy.mSensorDelay),
        mRampTime   (copy.mRampTime   ){}

    ~ValveResponsePressureCtrlConfigDto(){}

    ValveResponsePressureCtrlConfigDto& operator=(const ValveResponsePressureCtrlConfigDto& other)
    {
        ValveResponseDto::operator=(other);

        mCtrlMode    = other.mCtrlMode   ;
        mGainFactor  = other.mGainFactor ;
        mSensorDelay = other.mSensorDelay;
        mRampTime    = other.mRampTime   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, CtrlMode = %2, GainFactor = %3, SensorDelay = %4, RampTime = %5").arg(ValveResponseDto::toString()).arg(mCtrlMode).arg(mGainFactor).arg(mSensorDelay).arg(mRampTime);
    }
};

Q_DECLARE_METATYPE(ValveResponsePressureCtrlConfigDto);

class ValveResponseSelControlModeDto : public ValveResponseDto
{
public:
    int mCtrlMode    = 0;

    ValveResponseSelControlModeDto(){}
    ValveResponseSelControlModeDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSelControlModeDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSelControlModeDto(const ValveResponseSelControlModeDto& copy) : ValveResponseDto(copy),
        mCtrlMode   (copy.mCtrlMode   ){}

    ~ValveResponseSelControlModeDto(){}

    ValveResponseSelControlModeDto& operator=(const ValveResponseSelControlModeDto& other)
    {
        ValveResponseDto::operator=(other);

        mCtrlMode    = other.mCtrlMode   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, CtrlMode = %2").arg(ValveResponseDto::toString()).arg(mCtrlMode);
    }
};

Q_DECLARE_METATYPE(ValveResponseSelControlModeDto);

class ValveResponseGainFactorDto : public ValveResponseDto
{
public:
    QString mGainFactor    = "0";

    ValveResponseGainFactorDto(){}
    ValveResponseGainFactorDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseGainFactorDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseGainFactorDto(const ValveResponseGainFactorDto& copy) : ValveResponseDto(copy),
        mGainFactor   (copy.mGainFactor   ){}

    ~ValveResponseGainFactorDto(){}

    ValveResponseGainFactorDto& operator=(const ValveResponseGainFactorDto& other)
    {
        ValveResponseDto::operator=(other);

        mGainFactor    = other.mGainFactor   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mGainFactor = %2").arg(ValveResponseDto::toString()).arg(mGainFactor);
    }
};

Q_DECLARE_METATYPE(ValveResponseGainFactorDto);

class ValveResponseDeltaFactorDto : public ValveResponseDto
{
public:
    QString mDeltaFactor    = "0";

    ValveResponseDeltaFactorDto(){}
    ValveResponseDeltaFactorDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseDeltaFactorDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseDeltaFactorDto(const ValveResponseDeltaFactorDto& copy) : ValveResponseDto(copy),
        mDeltaFactor   (copy.mDeltaFactor   ){}

    ~ValveResponseDeltaFactorDto(){}

    ValveResponseDeltaFactorDto& operator=(const ValveResponseDeltaFactorDto& other)
    {
        ValveResponseDto::operator=(other);

        mDeltaFactor    = other.mDeltaFactor   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDeltaFactor = %2").arg(ValveResponseDto::toString()).arg(mDeltaFactor);
    }
};

Q_DECLARE_METATYPE(ValveResponseDeltaFactorDto);

class ValveResponsePGainDto : public ValveResponseDto
{
public:
    QString mPGain    = "0";

    ValveResponsePGainDto(){}
    ValveResponsePGainDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponsePGainDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponsePGainDto(const ValveResponsePGainDto& copy) : ValveResponseDto(copy),
        mPGain   (copy.mPGain   ){}

    ~ValveResponsePGainDto(){}

    ValveResponsePGainDto& operator=(const ValveResponsePGainDto& other)
    {
        ValveResponseDto::operator=(other);

        mPGain    = other.mPGain   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mPGain = %2").arg(ValveResponseDto::toString()).arg(mPGain);
    }
};

Q_DECLARE_METATYPE(ValveResponsePGainDto);

class ValveResponseIGainDto : public ValveResponseDto
{
public:
    QString mIGain    = "0";

    ValveResponseIGainDto(){}
    ValveResponseIGainDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseIGainDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseIGainDto(const ValveResponseIGainDto& copy) : ValveResponseDto(copy),
        mIGain   (copy.mIGain   ){}

    ~ValveResponseIGainDto(){}

    ValveResponseIGainDto& operator=(const ValveResponseIGainDto& other)
    {
        ValveResponseDto::operator=(other);

        mIGain    = other.mIGain   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mIGain = %2").arg(ValveResponseDto::toString()).arg(mIGain);
    }
};

Q_DECLARE_METATYPE(ValveResponseIGainDto);

class ValveResponseSensorDelayDto : public ValveResponseDto
{
public:
    QString mSensorDelay    = "0";

    ValveResponseSensorDelayDto(){}
    ValveResponseSensorDelayDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSensorDelayDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSensorDelayDto(const ValveResponseSensorDelayDto& copy) : ValveResponseDto(copy),
        mSensorDelay   (copy.mSensorDelay   ){}

    ~ValveResponseSensorDelayDto(){}

    ValveResponseSensorDelayDto& operator=(const ValveResponseSensorDelayDto& other)
    {
        ValveResponseDto::operator=(other);

        mSensorDelay    = other.mSensorDelay   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mSensorDelay = %2").arg(ValveResponseDto::toString()).arg(mSensorDelay);
    }
};

Q_DECLARE_METATYPE(ValveResponseSensorDelayDto);

class ValveResponseRampTimeDto : public ValveResponseDto
{
public:
    QString mRampTime    = "0";

    ValveResponseRampTimeDto(){}
    ValveResponseRampTimeDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseRampTimeDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseRampTimeDto(const ValveResponseRampTimeDto& copy) : ValveResponseDto(copy),
        mRampTime   (copy.mRampTime   ){}

    ~ValveResponseRampTimeDto(){}

    ValveResponseRampTimeDto& operator=(const ValveResponseRampTimeDto& other)
    {
        ValveResponseDto::operator=(other);

        mRampTime    = other.mRampTime   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mRampTime = %2").arg(ValveResponseDto::toString()).arg(mRampTime);
    }
};

Q_DECLARE_METATYPE(ValveResponseRampTimeDto);

class ValveResponseRampModeDto : public ValveResponseDto
{
public:
    int mRampMode = 0;

    ValveResponseRampModeDto(){}
    ValveResponseRampModeDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseRampModeDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseRampModeDto(const ValveResponseRampModeDto& copy) : ValveResponseDto(copy),
        mRampMode   (copy.mRampMode   ){}

    ~ValveResponseRampModeDto(){}

    ValveResponseRampModeDto& operator=(const ValveResponseRampModeDto& other)
    {
        ValveResponseDto::operator=(other);

        mRampMode    = other.mRampMode   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mRampMode = %2").arg(ValveResponseDto::toString()).arg(mRampMode);
    }
};

Q_DECLARE_METATYPE(ValveResponseRampModeDto);

class ValveResponseCtrlDirDto : public ValveResponseDto
{
public:
    int mControlDir = 0;

    ValveResponseCtrlDirDto(){}
    ValveResponseCtrlDirDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseCtrlDirDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseCtrlDirDto(const ValveResponseCtrlDirDto& copy) : ValveResponseDto(copy),
        mControlDir   (copy.mControlDir   ){}

    ~ValveResponseCtrlDirDto(){}

    ValveResponseCtrlDirDto& operator=(const ValveResponseCtrlDirDto& other)
    {
        ValveResponseDto::operator=(other);

        mControlDir    = other.mControlDir   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mControlDir = %2").arg(ValveResponseDto::toString()).arg(mControlDir);
    }
};

Q_DECLARE_METATYPE(ValveResponseCtrlDirDto);

class ValveResponseValveSetupDto : public ValveResponseDto
{
public:
    int mTargetPosSync        = 0;
    int mEventSync            = 0;
    int mSyncMode             = 0;
    int mStrokeLimitation     = 0;
    int mTargetPosPowerFail   = 0;
    int mTargetPosNetworkFail = 0;

    ValveResponseValveSetupDto(){}
    ValveResponseValveSetupDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseValveSetupDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseValveSetupDto(const ValveResponseValveSetupDto& copy) : ValveResponseDto(copy),
        mTargetPosSync       (copy.mTargetPosSync       ),
        mEventSync           (copy.mEventSync           ),
        mSyncMode            (copy.mSyncMode            ),
        mStrokeLimitation    (copy.mStrokeLimitation    ),
        mTargetPosPowerFail  (copy.mTargetPosPowerFail  ),
        mTargetPosNetworkFail(copy.mTargetPosNetworkFail){}

    ~ValveResponseValveSetupDto(){}

    ValveResponseValveSetupDto& operator=(const ValveResponseValveSetupDto& other)
    {
        ValveResponseDto::operator=(other);

        mTargetPosSync        = other.mTargetPosSync       ;
        mEventSync            = other.mEventSync           ;
        mSyncMode             = other.mSyncMode            ;
        mStrokeLimitation     = other.mStrokeLimitation    ;
        mTargetPosPowerFail   = other.mTargetPosPowerFail  ;
        mTargetPosNetworkFail = other.mTargetPosNetworkFail;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mTargetPosSync = %2, mEventSync = %3, mSyncMode = %4, mStrokeLimitation = %5, mTargetPosPowerFail = %6, mTargetPosNetworkFail = %7").arg(ValveResponseDto::toString())
                        .arg(mTargetPosSync).arg(mEventSync).arg(mSyncMode).arg(mStrokeLimitation).arg(mTargetPosPowerFail).arg(mTargetPosNetworkFail);
    }
};

Q_DECLARE_METATYPE(ValveResponseValveSetupDto);

class ValveResponseInterfaceConfigLogicDto : public ValveResponseDto
{
public:
    int mDIOpen     = 0;
    int mDIClose    = 0;
    int mDOOpen     = 0;
    int mDOClose    = 0;
    int mLearnRange = 0;

    ValveResponseInterfaceConfigLogicDto(){}
    ValveResponseInterfaceConfigLogicDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigLogicDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigLogicDto(const ValveResponseInterfaceConfigLogicDto& copy) : ValveResponseDto(copy),
        mDIOpen    (copy.mDIOpen    ),
        mDIClose   (copy.mDIClose   ),
        mDOOpen    (copy.mDOOpen    ),
        mDOClose   (copy.mDOClose   ),
        mLearnRange(copy.mLearnRange){}

    ~ValveResponseInterfaceConfigLogicDto(){}

    ValveResponseInterfaceConfigLogicDto& operator=(const ValveResponseInterfaceConfigLogicDto& other)
    {
        ValveResponseDto::operator=(other);

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
                               .arg(ValveResponseDto::toString()).arg(mDIOpen).arg(mDIClose).arg(mDOOpen).arg(mDOClose)
                               .arg(mLearnRange);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigLogicDto);

class ValveResponseInterfaceConfigEthCATDiDto : public ValveResponseDto
{
public:
    int mDIFunction  = 0;
    int mDIMode      = 0;
    int mDIInput     = 0;

    ValveResponseInterfaceConfigEthCATDiDto(){}
    ValveResponseInterfaceConfigEthCATDiDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigEthCATDiDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigEthCATDiDto(const ValveResponseInterfaceConfigEthCATDiDto& copy) : ValveResponseDto(copy),
        mDIFunction(copy.mDIFunction),
        mDIMode    (copy.mDIMode    ),
        mDIInput   (copy.mDIInput   ){}

    ~ValveResponseInterfaceConfigEthCATDiDto(){}

    ValveResponseInterfaceConfigEthCATDiDto& operator=(const ValveResponseInterfaceConfigEthCATDiDto& other)
    {
        ValveResponseDto::operator=(other);

        mDIFunction = other.mDIFunction;
        mDIMode     = other.mDIMode    ;
        mDIInput    = other.mDIInput   ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDIFunction = %2, mDIMode = %3, mDIInput = %4")
                               .arg(ValveResponseDto::toString()).arg(mDIFunction).arg(mDIMode).arg(mDIInput);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigEthCATDiDto);

class ValveResponseInterfaceConfigEthCATDoDto : public ValveResponseDto
{
public:
    int mDOFunction  = 0;
    int mDOMode      = 0;
    int mDOOutput    = 0;

    ValveResponseInterfaceConfigEthCATDoDto(){}
    ValveResponseInterfaceConfigEthCATDoDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigEthCATDoDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigEthCATDoDto(const ValveResponseInterfaceConfigEthCATDoDto& copy) : ValveResponseDto(copy),
        mDOFunction(copy.mDOFunction),
        mDOMode    (copy.mDOMode    ),
        mDOOutput  (copy.mDOOutput  ){}

    ~ValveResponseInterfaceConfigEthCATDoDto(){}

    ValveResponseInterfaceConfigEthCATDoDto& operator=(const ValveResponseInterfaceConfigEthCATDoDto& other)
    {
        ValveResponseDto::operator=(other);

        mDOFunction = other.mDOFunction;
        mDOMode     = other.mDOMode    ;
        mDOOutput   = other.mDOOutput  ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDOFunction = %2, mDOMode = %3, mDOOutput = %4")
                               .arg(ValveResponseDto::toString()).arg(mDOFunction).arg(mDOMode).arg(mDOOutput);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigEthCATDoDto);

class ValveResponseInterfaceConfigEthCATDevIDDto : public ValveResponseDto
{
public:
    int mDevID  = 0;

    ValveResponseInterfaceConfigEthCATDevIDDto(){}
    ValveResponseInterfaceConfigEthCATDevIDDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigEthCATDevIDDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigEthCATDevIDDto(const ValveResponseInterfaceConfigEthCATDevIDDto& copy) : ValveResponseDto(copy),
        mDevID(copy.mDevID){}

    ~ValveResponseInterfaceConfigEthCATDevIDDto(){}

    ValveResponseInterfaceConfigEthCATDevIDDto& operator=(const ValveResponseInterfaceConfigEthCATDevIDDto& other)
    {
        ValveResponseDto::operator=(other);

        mDevID = other.mDevID;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDevID = %2").arg(ValveResponseDto::toString()).arg(mDevID);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigEthCATDevIDDto);

class ValveResponseInterfaceConfigEthCATPDODataTypeDto : public ValveResponseDto
{
public:
    int mDataType  = 0;

    ValveResponseInterfaceConfigEthCATPDODataTypeDto(){}
    ValveResponseInterfaceConfigEthCATPDODataTypeDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigEthCATPDODataTypeDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigEthCATPDODataTypeDto(const ValveResponseInterfaceConfigEthCATPDODataTypeDto& copy) : ValveResponseDto(copy),
        mDataType(copy.mDataType){}

    ~ValveResponseInterfaceConfigEthCATPDODataTypeDto(){}

    ValveResponseInterfaceConfigEthCATPDODataTypeDto& operator=(const ValveResponseInterfaceConfigEthCATPDODataTypeDto& other)
    {
        ValveResponseDto::operator=(other);

        mDataType = other.mDataType;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDataType = %2").arg(ValveResponseDto::toString()).arg(mDataType);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigEthCATPDODataTypeDto);

class ValveResponseInterfaceConfigEthCATPDORangeDto : public ValveResponseDto
{
public:
    QString mRangeFrom  = "0";
    QString mRangeTo    = "1000000";

    ValveResponseInterfaceConfigEthCATPDORangeDto(){}
    ValveResponseInterfaceConfigEthCATPDORangeDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigEthCATPDORangeDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigEthCATPDORangeDto(const ValveResponseInterfaceConfigEthCATPDORangeDto& copy) : ValveResponseDto(copy),
        mRangeFrom(copy.mRangeFrom),
        mRangeTo  (copy.mRangeTo){}

    ~ValveResponseInterfaceConfigEthCATPDORangeDto(){}

    ValveResponseInterfaceConfigEthCATPDORangeDto& operator=(const ValveResponseInterfaceConfigEthCATPDORangeDto& other)
    {
        ValveResponseDto::operator=(other);

        mRangeFrom = other.mRangeFrom;
        mRangeTo   = other.mRangeTo;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mRangeFrom = %2, mRangeTo = %3").arg(ValveResponseDto::toString()).arg(mRangeFrom).arg(mRangeTo);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigEthCATPDORangeDto);

class ValveResponseInterfaceConfigDNetMacDto : public ValveResponseDto
{
public:
    int mMacAddr  = 0;

    ValveResponseInterfaceConfigDNetMacDto(){}
    ValveResponseInterfaceConfigDNetMacDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigDNetMacDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigDNetMacDto(const ValveResponseInterfaceConfigDNetMacDto& copy) : ValveResponseDto(copy),
        mMacAddr    (copy.mMacAddr    ){}

    ~ValveResponseInterfaceConfigDNetMacDto(){}

    ValveResponseInterfaceConfigDNetMacDto& operator=(const ValveResponseInterfaceConfigDNetMacDto& other)
    {
        ValveResponseDto::operator=(other);

        mMacAddr     = other.mMacAddr    ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mMacAddr = %2").arg(ValveResponseDto::toString()).arg(mMacAddr);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigDNetMacDto);

class ValveResponseInterfaceConfigDNetBaudrateDto : public ValveResponseDto
{
public:
    int mBaudrate  = 0;

    ValveResponseInterfaceConfigDNetBaudrateDto(){}
    ValveResponseInterfaceConfigDNetBaudrateDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigDNetBaudrateDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigDNetBaudrateDto(const ValveResponseInterfaceConfigDNetBaudrateDto& copy) : ValveResponseDto(copy),
        mBaudrate    (copy.mBaudrate    ){}

    ~ValveResponseInterfaceConfigDNetBaudrateDto(){}

    ValveResponseInterfaceConfigDNetBaudrateDto& operator=(const ValveResponseInterfaceConfigDNetBaudrateDto& other)
    {
        ValveResponseDto::operator=(other);

        mBaudrate     = other.mBaudrate    ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mBaudrate = %2").arg(ValveResponseDto::toString()).arg(mBaudrate);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigDNetBaudrateDto);

class ValveResponseInterfaceConfigDNetDiDto : public ValveResponseDto
{
public:
    int mDIActivation = 0;
    int mDIFunction  = 0;
    int mDIPolarity  = 0;

    ValveResponseInterfaceConfigDNetDiDto(){}
    ValveResponseInterfaceConfigDNetDiDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigDNetDiDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigDNetDiDto(const ValveResponseInterfaceConfigDNetDiDto& copy) : ValveResponseDto(copy),
        mDIActivation(copy.mDIActivation),
        mDIFunction  (copy.mDIFunction),
        mDIPolarity  (copy.mDIPolarity){}

    ~ValveResponseInterfaceConfigDNetDiDto(){}

    ValveResponseInterfaceConfigDNetDiDto& operator=(const ValveResponseInterfaceConfigDNetDiDto& other)
    {
        ValveResponseDto::operator=(other);

        mDIActivation = other.mDIActivation;
        mDIFunction   = other.mDIFunction;
        mDIPolarity   = other.mDIPolarity;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDIActivation = %2, mDIFunction = %3, mDIPolarity = %4")
                               .arg(ValveResponseDto::toString()).arg(mDIActivation).arg(mDIFunction).arg(mDIPolarity);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigDNetDiDto);

class ValveResponseInterfaceConfigDNetDoDto : public ValveResponseDto
{
public:
    int mDOActivation = 0;
    int mDOFunction   = 0;
    int mDOPolarity   = 0;

    ValveResponseInterfaceConfigDNetDoDto(){}
    ValveResponseInterfaceConfigDNetDoDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigDNetDoDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigDNetDoDto(const ValveResponseInterfaceConfigDNetDoDto& copy) : ValveResponseDto(copy),
        mDOActivation(copy.mDOActivation),
        mDOFunction  (copy.mDOFunction  ),
        mDOPolarity  (copy.mDOPolarity  ){}

    ~ValveResponseInterfaceConfigDNetDoDto(){}

    ValveResponseInterfaceConfigDNetDoDto& operator=(const ValveResponseInterfaceConfigDNetDoDto& other)
    {
        ValveResponseDto::operator=(other);

        mDOActivation = other.mDOActivation;
        mDOFunction   = other.mDOFunction  ;
        mDOPolarity   = other.mDOPolarity  ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mDOActivation = %2, mDOFunction = %3, mDOPolarity = %4")
                               .arg(ValveResponseDto::toString()).arg(mDOActivation).arg(mDOFunction).arg(mDOPolarity);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigDNetDoDto);

class ValveResponseInterfaceConfigRS232Dto : public ValveResponseDto
{
public:
    int mBaudrateIdx     = 0;
    int mParityIdx       = 0;
    int mDataLenIdx      = 0;
    int mStopBitIdx      = 0;
    int mCommandSetIdx   = 0;
    int mSecondAnswerIdx = 0;
    int mDIOpenValveIdx  = 0;
    int mDICloseValveIdx = 0;

    ValveResponseInterfaceConfigRS232Dto(){}
    ValveResponseInterfaceConfigRS232Dto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigRS232Dto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigRS232Dto(const ValveResponseInterfaceConfigRS232Dto& copy) : ValveResponseDto(copy),
        mBaudrateIdx    (copy.mBaudrateIdx    ),
        mParityIdx      (copy.mParityIdx      ),
        mDataLenIdx     (copy.mDataLenIdx     ),
        mStopBitIdx     (copy.mStopBitIdx     ),
        mCommandSetIdx  (copy.mCommandSetIdx  ),
        mSecondAnswerIdx(copy.mSecondAnswerIdx),
        mDIOpenValveIdx (copy.mDIOpenValveIdx ),
        mDICloseValveIdx(copy.mDICloseValveIdx){}

    ~ValveResponseInterfaceConfigRS232Dto(){}

    ValveResponseInterfaceConfigRS232Dto& operator=(const ValveResponseInterfaceConfigRS232Dto& other)
    {
        ValveResponseDto::operator=(other);

        mBaudrateIdx     = other.mBaudrateIdx    ;
        mParityIdx       = other.mParityIdx      ;
        mDataLenIdx      = other.mDataLenIdx     ;
        mStopBitIdx      = other.mStopBitIdx     ;
        mCommandSetIdx   = other.mCommandSetIdx  ;
        mSecondAnswerIdx = other.mSecondAnswerIdx;
        mDIOpenValveIdx  = other.mDIOpenValveIdx ;
        mDICloseValveIdx = other.mDICloseValveIdx;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mBaudrateIdx = %2, mParityIdx = %3, mDataLenIdx = %4, mStopBitIdx = %5, mCommandSetIdx = %6, mSecondAnswerIdx = %7, mDIOpenValveIdx = %8, mDICloseValveIdx = %9 ")
                               .arg(ValveResponseDto::toString()).arg(mBaudrateIdx).arg(mParityIdx).arg(mDataLenIdx).arg(mStopBitIdx).arg(mCommandSetIdx).arg(mSecondAnswerIdx).arg(mDIOpenValveIdx).arg(mDICloseValveIdx);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigRS232Dto);

class ValveResponseInterfaceConfigRS485Dto : public ValveResponseDto
{
public:
    int mOperationModeIdx = 0;
    int mDuplexModeIdx    = 0;
    int mDevAddr          = 0;
    int mTerminationIdx   = 0;

    ValveResponseInterfaceConfigRS485Dto(){}
    ValveResponseInterfaceConfigRS485Dto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigRS485Dto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigRS485Dto(const ValveResponseInterfaceConfigRS485Dto& copy) : ValveResponseDto(copy),
        mOperationModeIdx(copy.mOperationModeIdx),
        mDuplexModeIdx   (copy.mDuplexModeIdx   ),
        mDevAddr         (copy.mDevAddr         ),
        mTerminationIdx  (copy.mTerminationIdx  ){}

    ~ValveResponseInterfaceConfigRS485Dto(){}

    ValveResponseInterfaceConfigRS485Dto& operator=(const ValveResponseInterfaceConfigRS485Dto& other)
    {
        ValveResponseDto::operator=(other);

        mOperationModeIdx = other.mOperationModeIdx;
        mDuplexModeIdx    = other.mDuplexModeIdx   ;
        mDevAddr          = other.mDevAddr         ;
        mTerminationIdx   = other.mTerminationIdx  ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mOperationModeIdx = %2, mDuplexModeIdx = %3, mDevAddr = %4, mTerminationIdx = %5")
                               .arg(ValveResponseDto::toString()).arg(mOperationModeIdx).arg(mDuplexModeIdx).arg(mDevAddr).arg(mTerminationIdx);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigRS485Dto);

class ValveResponseInterfaceConfigRS232RangeDto : public ValveResponseDto
{
public:
    int mPosRangeIdx   = 0;
    int mPressureRange = 0;

    ValveResponseInterfaceConfigRS232RangeDto(){}
    ValveResponseInterfaceConfigRS232RangeDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceConfigRS232RangeDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceConfigRS232RangeDto(const ValveResponseInterfaceConfigRS232RangeDto& copy) : ValveResponseDto(copy),
        mPosRangeIdx  (copy.mPosRangeIdx  ),
        mPressureRange(copy.mPressureRange){}

    ~ValveResponseInterfaceConfigRS232RangeDto(){}

    ValveResponseInterfaceConfigRS232RangeDto& operator=(const ValveResponseInterfaceConfigRS232RangeDto& other)
    {
        ValveResponseDto::operator=(other);

        mPosRangeIdx   = other.mPosRangeIdx  ;
        mPressureRange = other.mPressureRange;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mPosRangeIdx = %2, mPressureRange = %3")
                               .arg(ValveResponseDto::toString()).arg(mPosRangeIdx).arg(mPressureRange);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceConfigRS232RangeDto);

class ValveResponseInterfaceStatusRS232Dto : public ValveResponseDto
{
public:
    int mStatusDIOpen  = 0;
    int mStatusDIClose = 0;
    int mStatusDOOpen  = 0;
    int mStatusDOClose = 0;

    ValveResponseInterfaceStatusRS232Dto(){}
    ValveResponseInterfaceStatusRS232Dto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceStatusRS232Dto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceStatusRS232Dto(const ValveResponseInterfaceStatusRS232Dto& copy) : ValveResponseDto(copy),
        mStatusDIOpen (copy.mStatusDIOpen ),
        mStatusDIClose(copy.mStatusDIClose),
        mStatusDOOpen (copy.mStatusDOOpen ),
        mStatusDOClose(copy.mStatusDOClose){}

    ~ValveResponseInterfaceStatusRS232Dto(){}

    ValveResponseInterfaceStatusRS232Dto& operator=(const ValveResponseInterfaceStatusRS232Dto& other)
    {
        ValveResponseDto::operator=(other);

        mStatusDIOpen  = other.mStatusDIOpen ;
        mStatusDIClose = other.mStatusDIClose;
        mStatusDOOpen  = other.mStatusDOOpen ;
        mStatusDOClose = other.mStatusDOClose;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mStatusDIOpen = %2, mStatusDIClose = %3, mStatusDOOpen = %4, mStatusDOClose = %5")
                               .arg(ValveResponseDto::toString()).arg(mStatusDIOpen).arg(mStatusDIClose).arg(mStatusDOOpen).arg(mStatusDOClose);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceStatusRS232Dto);

class ValveResponseLearnStatusDto : public ValveResponseDto
{
public:
    int mRunning           = 0;
    int mDataSetPresent    = 0;
    int mAbort             = 0;
    int mIsOKOpenPressure  = 0;
    int mIsOKClosePressure = 0;
    int mPressureRaising   = 0;
    int mPressureStability = 0;

    ValveResponseLearnStatusDto(){}
    ValveResponseLearnStatusDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseLearnStatusDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseLearnStatusDto(const ValveResponseLearnStatusDto& copy) : ValveResponseDto(copy),
        mRunning          (copy.mRunning          ),
        mDataSetPresent   (copy.mDataSetPresent   ),
        mAbort            (copy.mAbort            ),
        mIsOKOpenPressure (copy.mIsOKOpenPressure ),
        mIsOKClosePressure(copy.mIsOKClosePressure),
        mPressureRaising  (copy.mPressureRaising  ),
        mPressureStability(copy.mPressureStability){}

    ~ValveResponseLearnStatusDto(){}

    ValveResponseLearnStatusDto& operator=(const ValveResponseLearnStatusDto& other)
    {
        ValveResponseDto::operator=(other);

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
                        .arg(ValveResponseDto::toString())
                        .arg(mRunning          )
                        .arg(mDataSetPresent   )
                        .arg(mAbort            )
                        .arg(mIsOKOpenPressure )
                        .arg(mIsOKClosePressure)
                        .arg(mPressureRaising  )
                        .arg(mPressureStability);
    }
};

Q_DECLARE_METATYPE(ValveResponseLearnStatusDto);

class ValveResponseLearnPressureLimitDto : public ValveResponseDto
{
public:
    int mPressureLimit = 0;

    ValveResponseLearnPressureLimitDto(){}
    ValveResponseLearnPressureLimitDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseLearnPressureLimitDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseLearnPressureLimitDto(const ValveResponseLearnPressureLimitDto& copy) : ValveResponseDto(copy),
        mPressureLimit(copy.mPressureLimit){}

    ~ValveResponseLearnPressureLimitDto(){}

    ValveResponseLearnPressureLimitDto& operator=(const ValveResponseLearnPressureLimitDto& other)
    {
        ValveResponseDto::operator=(other);

        mPressureLimit = other.mPressureLimit;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mPressureLimit = %2").arg(ValveResponseDto::toString()).arg(mPressureLimit);
    }
};

Q_DECLARE_METATYPE(ValveResponseLearnPressureLimitDto);

class ValveResponseFatalErrStatusDto : public ValveResponseDto
{
public:
    int mErrorCode = 0;

    ValveResponseFatalErrStatusDto(){}
    ValveResponseFatalErrStatusDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseFatalErrStatusDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseFatalErrStatusDto(const ValveResponseFatalErrStatusDto& copy) : ValveResponseDto(copy),
        mErrorCode(copy.mErrorCode){}

    ~ValveResponseFatalErrStatusDto(){}

    ValveResponseFatalErrStatusDto& operator=(const ValveResponseFatalErrStatusDto& other)
    {
        ValveResponseDto::operator=(other);

        mErrorCode = other.mErrorCode;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mErrorCode = %2").arg(ValveResponseDto::toString()).arg(mErrorCode);
    }
};

Q_DECLARE_METATYPE(ValveResponseFatalErrStatusDto);

class ValveResponseWarningsDto : public ValveResponseDto
{
public:
    int mIsServiceRequest = 0;

    ValveResponseWarningsDto(){}
    ValveResponseWarningsDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseWarningsDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseWarningsDto(const ValveResponseWarningsDto& copy) : ValveResponseDto(copy),
        mIsServiceRequest(copy.mIsServiceRequest){}

    ~ValveResponseWarningsDto(){}

    ValveResponseWarningsDto& operator=(const ValveResponseWarningsDto& other)
    {
        ValveResponseDto::operator=(other);

        mIsServiceRequest = other.mIsServiceRequest;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mIsServiceRequest = %2").arg(ValveResponseDto::toString()).arg(mIsServiceRequest);
    }
};

Q_DECLARE_METATYPE(ValveResponseWarningsDto);

class ValveResponseSensorOffsetDto : public ValveResponseDto
{
public:
    int mVoltage = 0;

    ValveResponseSensorOffsetDto(){}
    ValveResponseSensorOffsetDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSensorOffsetDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSensorOffsetDto(const ValveResponseSensorOffsetDto& copy) : ValveResponseDto(copy),
        mVoltage(copy.mVoltage){}

    ~ValveResponseSensorOffsetDto(){}

    ValveResponseSensorOffsetDto& operator=(const ValveResponseSensorOffsetDto& other)
    {
        ValveResponseDto::operator=(other);

        mVoltage = other.mVoltage;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mVoltage = %2").arg(ValveResponseDto::toString()).arg(mVoltage);
    }
};

Q_DECLARE_METATYPE(ValveResponseSensorOffsetDto);

class ValveResponseControlCyclesDto : public ValveResponseDto
{
public:
    int mCycles = 0;

    ValveResponseControlCyclesDto(){}
    ValveResponseControlCyclesDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseControlCyclesDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseControlCyclesDto(const ValveResponseControlCyclesDto& copy) : ValveResponseDto(copy),
        mCycles(copy.mCycles){}

    ~ValveResponseControlCyclesDto(){}

    ValveResponseControlCyclesDto& operator=(const ValveResponseControlCyclesDto& other)
    {
        ValveResponseDto::operator=(other);

        mCycles = other.mCycles;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mCycles = %2").arg(ValveResponseDto::toString()).arg(mCycles);
    }
};

Q_DECLARE_METATYPE(ValveResponseControlCyclesDto);

class ValveResponseIsolationCyclesDto : public ValveResponseDto
{
public:
    int mCycles = 0;

    ValveResponseIsolationCyclesDto(){}
    ValveResponseIsolationCyclesDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseIsolationCyclesDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseIsolationCyclesDto(const ValveResponseIsolationCyclesDto& copy) : ValveResponseDto(copy),
        mCycles(copy.mCycles){}

    ~ValveResponseIsolationCyclesDto(){}

    ValveResponseIsolationCyclesDto& operator=(const ValveResponseIsolationCyclesDto& other)
    {
        ValveResponseDto::operator=(other);

        mCycles = other.mCycles;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mCycles = %2").arg(ValveResponseDto::toString()).arg(mCycles);
    }
};

Q_DECLARE_METATYPE(ValveResponseIsolationCyclesDto);

class ValveResponseSensorScaleDto : public ValveResponseDto
{
public:
    int  mSensor01Unit     ;
    int  mSensor01FullScale;
    int  mSensor01SignExp  ;
    int  mSensor01Exp      ;
    int  mSensor02Unit     ;
    int  mSensor02FullScale;
    int  mSensor02SignExp  ;
    int  mSensor02Exp      ;

    ValveResponseSensorScaleDto(){}
    ValveResponseSensorScaleDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSensorScaleDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSensorScaleDto(const ValveResponseSensorScaleDto& copy) : ValveResponseDto(copy),
        mSensor01Unit     (copy.mSensor01Unit     ),
        mSensor01FullScale(copy.mSensor01FullScale),
        mSensor01SignExp  (copy.mSensor01SignExp  ),
        mSensor01Exp      (copy.mSensor01Exp      ),
        mSensor02Unit     (copy.mSensor02Unit     ),
        mSensor02FullScale(copy.mSensor02FullScale),
        mSensor02SignExp  (copy.mSensor02SignExp  ),
        mSensor02Exp      (copy.mSensor02Exp      ){}

    ~ValveResponseSensorScaleDto(){}

    ValveResponseSensorScaleDto& operator=(const ValveResponseSensorScaleDto& other)
    {
        ValveResponseDto::operator=(other);

        mSensor01Unit      = other.mSensor01Unit     ;
        mSensor01FullScale = other.mSensor01FullScale;
        mSensor01SignExp   = other.mSensor01SignExp  ;
        mSensor01Exp       = other.mSensor01Exp      ;
        mSensor02Unit      = other.mSensor02Unit     ;
        mSensor02FullScale = other.mSensor02FullScale;
        mSensor02SignExp   = other.mSensor02SignExp  ;
        mSensor02Exp       = other.mSensor02Exp      ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mSensor01Unit = %2, mSensor01FullScale = %3, mSensor01SignExp = %4, mSensor01Exp = %5, mSensor02Unit = %6, mSensor02FullScale = %7, mSensor02SignExp = %8, mSensor02Exp = %9")
                        .arg(ValveResponseDto::toString())
                        .arg(mSensor01Unit     )
                        .arg(mSensor01FullScale)
                        .arg(mSensor01SignExp  )
                        .arg(mSensor01Exp      )
                        .arg(mSensor02Unit     )
                        .arg(mSensor02FullScale)
                        .arg(mSensor02SignExp  )
                        .arg(mSensor02Exp      );
    }
};

Q_DECLARE_METATYPE(ValveResponseSensorScaleDto);

class ValveResponseSetPointDto : public ValveResponseDto
{
public:
    int mPosition;
    int mPressure;

    ValveResponseSetPointDto(){}
    ValveResponseSetPointDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSetPointDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSetPointDto(const ValveResponseSetPointDto& copy) : ValveResponseDto(copy),
        mPosition(copy.mPosition),
        mPressure(copy.mPressure){}

    ~ValveResponseSetPointDto(){}

    ValveResponseSetPointDto& operator=(const ValveResponseSetPointDto& other)
    {
        ValveResponseDto::operator=(other);

        mPosition = other.mPosition;
        mPressure = other.mPressure;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mPosition = %2, mPressure = %3")
                .arg(ValveResponseDto::toString())
                .arg(mPosition)
                .arg(mPressure);
    }
};

Q_DECLARE_METATYPE(ValveResponseSetPointDto);

class ValveResponseDisplayConfigDto : public ValveResponseDto
{
public:
    int mPositionResolution  = 0;
    int mPressureDpUnit      = 0;
    int mPressureAxisMapping = 0;
    int mPressureDecades     = 5;

    ValveResponseDisplayConfigDto(){}
    ValveResponseDisplayConfigDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseDisplayConfigDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseDisplayConfigDto(const ValveResponseDisplayConfigDto& copy) : ValveResponseDto(copy),
        mPositionResolution (copy.mPositionResolution ),
        mPressureDpUnit     (copy.mPressureDpUnit     ),
        mPressureAxisMapping(copy.mPressureAxisMapping),
        mPressureDecades    (copy.mPressureDecades    ){}

    ~ValveResponseDisplayConfigDto(){}

    ValveResponseDisplayConfigDto& operator=(const ValveResponseDisplayConfigDto& other)
    {
        ValveResponseDto::operator=(other);

        mPositionResolution  = other.mPositionResolution ;
        mPressureDpUnit      = other.mPressureDpUnit     ;
        mPressureAxisMapping = other.mPressureAxisMapping;
        mPressureDecades     = other.mPressureDecades    ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, PositionResolution = %2, PressureDpUnit = %3, PressureAxisMapping = %4, PressureDecades = %5")
                              .arg(ValveResponseDto::toString()).arg(mPositionResolution).arg(mPressureDpUnit).arg(mPressureAxisMapping).arg(mPressureDecades);
    }
};

Q_DECLARE_METATYPE(ValveResponseDisplayConfigDto);

class ValveResponseValveParamDto : public ValveResponseDto
{
public:
    int     mID    = 0;
    QString mValue = 0;

    ValveResponseValveParamDto(){}
    ValveResponseValveParamDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseValveParamDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseValveParamDto(const ValveResponseValveParamDto& copy) : ValveResponseDto(copy),
        mID   (copy.mID   ),
        mValue(copy.mValue){}

    ~ValveResponseValveParamDto(){}

    ValveResponseValveParamDto& operator=(const ValveResponseValveParamDto& other)
    {
        ValveResponseDto::operator=(other);

        mID    = other.mID   ;
        mValue = other.mValue;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mID = %2, value = %3").arg(ValveResponseDto::toString()).arg(mID).arg(mValue);
    }
};

Q_DECLARE_METATYPE(ValveResponseValveParamDto);

class ValveResponseTotalControlCyclesDto : public ValveResponseDto
{
public:
    int mCycles = 0;

    ValveResponseTotalControlCyclesDto(){}
    ValveResponseTotalControlCyclesDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseTotalControlCyclesDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseTotalControlCyclesDto(const ValveResponseTotalControlCyclesDto& copy) : ValveResponseDto(copy),
        mCycles(copy.mCycles){}

    ~ValveResponseTotalControlCyclesDto(){}

    ValveResponseTotalControlCyclesDto& operator=(const ValveResponseTotalControlCyclesDto& other)
    {
        ValveResponseDto::operator=(other);

        mCycles = other.mCycles;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mCycles = %2").arg(ValveResponseDto::toString()).arg(mCycles);
    }
};

Q_DECLARE_METATYPE(ValveResponseTotalControlCyclesDto);

class ValveResponseTotalIsolationCyclesDto : public ValveResponseDto
{
public:
    int mCycles = 0;

    ValveResponseTotalIsolationCyclesDto(){}
    ValveResponseTotalIsolationCyclesDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseTotalIsolationCyclesDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseTotalIsolationCyclesDto(const ValveResponseTotalIsolationCyclesDto& copy) : ValveResponseDto(copy),
        mCycles(copy.mCycles){}

    ~ValveResponseTotalIsolationCyclesDto(){}

    ValveResponseTotalIsolationCyclesDto& operator=(const ValveResponseTotalIsolationCyclesDto& other)
    {
        ValveResponseDto::operator=(other);

        mCycles = other.mCycles;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mCycles = %2").arg(ValveResponseDto::toString()).arg(mCycles);
    }
};

Q_DECLARE_METATYPE(ValveResponseTotalIsolationCyclesDto);

class ValveResponsePFOPerformedCyclesDto : public ValveResponseDto
{
public:
    int mCycles = 0;

    ValveResponsePFOPerformedCyclesDto(){}
    ValveResponsePFOPerformedCyclesDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponsePFOPerformedCyclesDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponsePFOPerformedCyclesDto(const ValveResponsePFOPerformedCyclesDto& copy) : ValveResponseDto(copy),
        mCycles(copy.mCycles){}

    ~ValveResponsePFOPerformedCyclesDto(){}

    ValveResponsePFOPerformedCyclesDto& operator=(const ValveResponsePFOPerformedCyclesDto& other)
    {
        ValveResponseDto::operator=(other);

        mCycles = other.mCycles;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mCycles = %2").arg(ValveResponseDto::toString()).arg(mCycles);
    }
};

Q_DECLARE_METATYPE(ValveResponsePFOPerformedCyclesDto);

class ValveResponsePFOCurrentVoltageDto : public ValveResponseDto
{
public:
    int       mCurrentVoltage;

    ValveResponsePFOCurrentVoltageDto(){}
    ValveResponsePFOCurrentVoltageDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponsePFOCurrentVoltageDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponsePFOCurrentVoltageDto(const ValveResponsePFOCurrentVoltageDto& copy) : ValveResponseDto(copy),
        mCurrentVoltage(copy.mCurrentVoltage){}

    ~ValveResponsePFOCurrentVoltageDto(){}

    ValveResponsePFOCurrentVoltageDto& operator=(const ValveResponsePFOCurrentVoltageDto& other)
    {
        ValveResponseDto::operator=(other);

        mCurrentVoltage = other.mCurrentVoltage;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mCurrentVoltage = %2")
                        .arg(ValveResponseDto::toString())
                        .arg(mCurrentVoltage);
    }
};

Q_DECLARE_METATYPE(ValveResponsePFOCurrentVoltageDto);

class ValveResponseFatalErrPosDto : public ValveResponseDto
{
public:
    int mErrPosition  ;
    int mTotalPosition;

    ValveResponseFatalErrPosDto(){}
    ValveResponseFatalErrPosDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseFatalErrPosDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseFatalErrPosDto(const ValveResponseFatalErrPosDto& copy) : ValveResponseDto(copy),
        mErrPosition  (copy.mErrPosition  ),
        mTotalPosition(copy.mTotalPosition){}

    ~ValveResponseFatalErrPosDto(){}

    ValveResponseFatalErrPosDto& operator=(const ValveResponseFatalErrPosDto& other)
    {
        ValveResponseDto::operator=(other);

        mErrPosition   = other.mErrPosition  ;
        mTotalPosition = other.mTotalPosition;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mErrPosition = %2, mTotalPosition = %3")
                .arg(ValveResponseDto::toString())
                .arg(mErrPosition  )
                .arg(mTotalPosition);
    }
};

Q_DECLARE_METATYPE(ValveResponseFatalErrPosDto);

class ValveResponseLearnParamDto : public ValveResponseDto
{
public:
    int     mIdx        = 0;
    QString mPointValue = "";
    QString mValue      = "";

    ValveResponseLearnParamDto(){}
    ValveResponseLearnParamDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseLearnParamDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseLearnParamDto(const ValveResponseLearnParamDto& copy) : ValveResponseDto(copy),
        mIdx       (copy.mIdx       ),
        mPointValue(copy.mPointValue),
        mValue     (copy.mValue     ){}

    ~ValveResponseLearnParamDto(){}

    ValveResponseLearnParamDto& operator=(const ValveResponseLearnParamDto& other)
    {
        ValveResponseDto::operator=(other);

        mIdx        = other.mIdx       ;
        mPointValue = other.mPointValue;
        mValue      = other.mValue     ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mIdx = %2, mValue = %3").arg(ValveResponseDto::toString()).arg(mIdx).arg(mValue);
    }
};

Q_DECLARE_METATYPE(ValveResponseLearnParamDto);

class ValveResponseValveStatusDto : public ValveResponseDto
{
public:
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
    bool      mTestMode         ;
    bool      mFieldBusError    ;
    bool      mIsSaving         ;
    bool      mFirmwareError    ;
    bool      mUnknowInterface  ;
    bool      mNoSensorSignal   ;
    bool      mNoAnalogSignal   ;
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

    ValveResponseValveStatusDto(){}
    ValveResponseValveStatusDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseValveStatusDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseValveStatusDto(const ValveResponseValveStatusDto& copy) : ValveResponseDto(copy),
        mCurrPosition   (copy.mCurrPosition     ),
        mCurrPressure   (copy.mCurrPressure     ),
        mTargetValue    (copy.mTargetValue      ),
        mTargetPosition (copy.mTargetPosition   ),
        mTargetPressure (copy.mTargetPressure   ),
        mValveSpeed     (copy.mValveSpeed       ),
        mGainFactor     (copy.mGainFactor       ),
        mAccess         (copy.mAccess           ),
        mMode           (copy.mMode             ),
        mControlMode    (copy.mControlMode      ),
        mReserved01     (copy.mReserved01       ),
        mIsSimulation   (copy.mIsSimulation     ),
        mEnablePFO      (copy.mEnablePFO        ),
        mTestMode       (copy.mTestMode         ),
        mFieldBusError  (copy.mFieldBusError    ),
        mIsSaving       (copy.mIsSaving         ),
        mFirmwareError  (copy.mFirmwareError    ),
        mUnknowInterface(copy.mUnknowInterface  ),
        mNoSensorSignal (copy.mNoSensorSignal   ),
        mNoAnalogSignal (copy.mNoAnalogSignal   ),
        mNetworkFailure (copy.mNetworkFailure   ),
        mSlaveOffline   (copy.mSlaveOffline     ),
        mIsolationValve (copy.mIsolationValve   ),
        mSensorError    (copy.mSensorError      ),
        mSvcRequest     (copy.mSvcRequest       ),
        mLearnNotPresent(copy.mLearnNotPresent  ),
        mAirNotReady    (copy.mAirNotReady      ),
        mPFONotReady    (copy.mPFONotReady      ),
        mSensorDelay    (copy.mSensorDelay      ),
        mRampTime       (copy.mRampTime         ){}

    ~ValveResponseValveStatusDto(){}

    ValveResponseValveStatusDto& operator=(const ValveResponseValveStatusDto& other)
    {
        ValveResponseDto::operator=(other);

        mCurrPosition    = other.mCurrPosition     ;
        mCurrPressure    = other.mCurrPressure     ;
        mTargetValue     = other.mTargetValue      ;
        mTargetPosition  = other.mTargetPosition   ;
        mTargetPressure  = other.mTargetPressure   ;
        mValveSpeed      = other.mValveSpeed       ;
        mGainFactor      = other.mGainFactor       ;
        mAccess          = other.mAccess           ;
        mMode            = other.mMode             ;
        mControlMode     = other.mControlMode      ;
        mReserved01      = other.mReserved01       ;
        mIsSimulation    = other.mIsSimulation     ;
        mEnablePFO       = other.mEnablePFO        ;
        mTestMode        = other.mTestMode         ;
        mFieldBusError   = other.mFieldBusError    ;
        mIsSaving        = other.mIsSaving         ;
        mFirmwareError   = other.mFirmwareError    ;
        mUnknowInterface = other.mUnknowInterface  ;
        mNoSensorSignal  = other.mNoSensorSignal   ;
        mNoAnalogSignal  = other.mNoAnalogSignal   ;
        mNetworkFailure  = other.mNetworkFailure   ;
        mSlaveOffline    = other.mSlaveOffline     ;
        mIsolationValve  = other.mIsolationValve   ;
        mSensorError     = other.mSensorError      ;
        mSvcRequest      = other.mSvcRequest       ;
        mLearnNotPresent = other.mLearnNotPresent  ;
        mAirNotReady     = other.mAirNotReady      ;
        mPFONotReady     = other.mPFONotReady      ;
        mSensorDelay     = other.mSensorDelay      ;
        mRampTime        = other.mRampTime         ;

        return *this;
    }

    QString toString()
    {
        return QString("%1, currPos = %2, currPress = %3, TargetVale = %4, ValveSpeed = %5, gainFac = %6, access = %7, mode = %8, sensor delay = %9, ramp time = %10, is sim = %11, enable PFO = %12, test mode = %13, FieldBusE = %14, FirmwareE = %15, UnknowInterface = %16, NoSensorSignal = %17, NoAnalogSignal = %18, Network Fail = %19, SlaveOffline = %20, mIsolationValve = %21, mSensorError = %22, svcReq = %23, Learn Not = %24, AirNot = %25, PFONot = %26, mControlMode = %27")
                      .arg(ValveResponseDto::toString()).arg((int)mCurrPosition).arg((int)mCurrPressure).arg(mTargetValue).arg(mValveSpeed)
                      .arg(mGainFactor).arg(mAccess).arg(mMode).arg(mSensorDelay).arg(mRampTime).arg(mIsSimulation).arg(mEnablePFO).arg(mTestMode)
                      .arg(mFieldBusError).arg(mFirmwareError).arg(mUnknowInterface).arg(mNoSensorSignal).arg(mNoAnalogSignal).arg(mNetworkFailure).arg(mSlaveOffline).arg(mIsolationValve).arg(mSensorError)
                      .arg(mSvcRequest).arg(mLearnNotPresent).arg(mAirNotReady).arg(mPFONotReady).arg(mControlMode);
    }
};

Q_DECLARE_METATYPE(ValveResponseValveStatusDto);

class ValveResponseInterfaceStatusLogicDto : public ValveResponseDto
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

    ValveResponseInterfaceStatusLogicDto(){}
    ValveResponseInterfaceStatusLogicDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceStatusLogicDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceStatusLogicDto(const ValveResponseInterfaceStatusLogicDto& copy) : ValveResponseDto(copy),
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

    ~ValveResponseInterfaceStatusLogicDto(){}

    ValveResponseInterfaceStatusLogicDto& operator=(const ValveResponseInterfaceStatusLogicDto& other)
    {
        ValveResponseDto::operator=(other);

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
                               .arg(ValveResponseDto::toString()).arg(mStatusDIOpen).arg(mStatusDIClose).arg(mStatusDICtrlModel).arg(mStatusDILearn)
                               .arg(mStatusDIZero).arg(mStatusDILocked).arg(mStatusDIHold).arg(mStatusDISetPointRange).arg(mStatusDOOpen)
                               .arg(mStatusDOClose).arg(mStatusDOAlarm).arg(mStatusDOReady).arg(mAlogInputVoltage);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceStatusLogicDto);

class ValveResponseInterfaceStatusEtherCATDto : public ValveResponseDto
{
public:
    int mStatusDI = 0;
    int mStatusDO = 0;

    ValveResponseInterfaceStatusEtherCATDto(){}
    ValveResponseInterfaceStatusEtherCATDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceStatusEtherCATDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceStatusEtherCATDto(const ValveResponseInterfaceStatusEtherCATDto& copy) : ValveResponseDto(copy),
        mStatusDI(copy.mStatusDI),
        mStatusDO(copy.mStatusDO){}

    ~ValveResponseInterfaceStatusEtherCATDto(){}

    ValveResponseInterfaceStatusEtherCATDto& operator=(const ValveResponseInterfaceStatusEtherCATDto& other)
    {
        ValveResponseDto::operator=(other);

        mStatusDI = other.mStatusDI;
        mStatusDO = other.mStatusDO;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mStatusDI = %2, mStatusDO = %3").arg(ValveResponseDto::toString()).arg(mStatusDI).arg(mStatusDO);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceStatusEtherCATDto);

class ValveResponseInterfaceStatusDNetDto : public ValveResponseDto
{
public:
    int mStatusDI = 0;
    int mStatusDO = 0;

    ValveResponseInterfaceStatusDNetDto(){}
    ValveResponseInterfaceStatusDNetDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceStatusDNetDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceStatusDNetDto(const ValveResponseInterfaceStatusDNetDto& copy) : ValveResponseDto(copy),
        mStatusDI(copy.mStatusDI),
        mStatusDO(copy.mStatusDO){}

    ~ValveResponseInterfaceStatusDNetDto(){}

    ValveResponseInterfaceStatusDNetDto& operator=(const ValveResponseInterfaceStatusDNetDto& other)
    {
        ValveResponseDto::operator=(other);

        mStatusDI = other.mStatusDI;
        mStatusDO = other.mStatusDO;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mStatusDI = %2, mStatusDO = %3").arg(ValveResponseDto::toString()).arg(mStatusDI).arg(mStatusDO);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceStatusDNetDto);

class ValveResponseInterfaceDNetFirmwareIDDto : public ValveResponseDto
{
public:
    QString mFirmwareID = "";

    ValveResponseInterfaceDNetFirmwareIDDto(){}
    ValveResponseInterfaceDNetFirmwareIDDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceDNetFirmwareIDDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceDNetFirmwareIDDto(const ValveResponseInterfaceDNetFirmwareIDDto& copy) : ValveResponseDto(copy),
        mFirmwareID(copy.mFirmwareID){}

    ~ValveResponseInterfaceDNetFirmwareIDDto(){}

    ValveResponseInterfaceDNetFirmwareIDDto& operator=(const ValveResponseInterfaceDNetFirmwareIDDto& other)
    {
        ValveResponseDto::operator=(other);

        mFirmwareID = other.mFirmwareID;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mFirmwareID = %2, mStatusDO = %3").arg(ValveResponseDto::toString()).arg(mFirmwareID);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceDNetFirmwareIDDto);

class ValveResponseInterfaceDNetSerialNumDto : public ValveResponseDto
{
public:
    QString mSerialNum = "";

    ValveResponseInterfaceDNetSerialNumDto(){}
    ValveResponseInterfaceDNetSerialNumDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseInterfaceDNetSerialNumDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseInterfaceDNetSerialNumDto(const ValveResponseInterfaceDNetSerialNumDto& copy) : ValveResponseDto(copy),
        mSerialNum(copy.mSerialNum){}

    ~ValveResponseInterfaceDNetSerialNumDto(){}

    ValveResponseInterfaceDNetSerialNumDto& operator=(const ValveResponseInterfaceDNetSerialNumDto& other)
    {
        ValveResponseDto::operator=(other);

        mSerialNum = other.mSerialNum;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mSerialNum = %2").arg(ValveResponseDto::toString()).arg(mSerialNum);
    }
};

Q_DECLARE_METATYPE(ValveResponseInterfaceDNetSerialNumDto);

class ValveResponseSimpleValueDto : public ValveResponseDto
{
public:
    QString mValue = "";

    ValveResponseSimpleValueDto(){}
    ValveResponseSimpleValueDto(ValveRequestDto reqDto, QDateTime resDateTime, QString resData, bool isParsed, bool isSucc, bool isNetworkErr, QString errMsg =""):ValveResponseDto(reqDto, resDateTime, resData, isParsed, isSucc, isNetworkErr, errMsg){}
    ValveResponseSimpleValueDto(ValveResponseDto baseDto) : ValveResponseDto(baseDto){}
    ValveResponseSimpleValueDto(const ValveResponseSimpleValueDto& copy) : ValveResponseDto(copy),
        mValue(copy.mValue){}

    ~ValveResponseSimpleValueDto(){}

    ValveResponseSimpleValueDto& operator=(const ValveResponseSimpleValueDto& other)
    {
        ValveResponseDto::operator=(other);

        mValue = other.mValue;

        return *this;
    }

    QString toString()
    {
        return QString("%1, mValue = %2").arg(ValveResponseDto::toString()).arg(mValue);
    }
};
Q_DECLARE_METATYPE(ValveResponseSimpleValueDto);
#endif // VALVESPROVIDERDTOEX_H
