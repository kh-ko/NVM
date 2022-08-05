#ifndef VALVEIDENTIFICATIONEXDLGMODEL_H
#define VALVEIDENTIFICATIONEXDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ValveIdentificationExDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode           READ getAccessMode           NOTIFY signalEventChangedAccessMode          )
    Q_PROPERTY(bool     mIsRS232Test          READ getIsRS232Test          NOTIFY signalEventChangedIsRS232Test         )
    Q_PROPERTY(QString  mSerialNumber         READ getSerialNumber         NOTIFY signalEventChangedSerialNumber        )
    Q_PROPERTY(int      mValveModel           READ getValveModel           NOTIFY signalEventChangedValveModel          )
    Q_PROPERTY(int      mValveType            READ getValveType            NOTIFY signalEventChangedValveType           )
    Q_PROPERTY(int      mSealingType          READ getSealingType          NOTIFY signalEventChangedSealingType         )
    Q_PROPERTY(int      mFlangeSize           READ getFlangeSize           NOTIFY signalEventChangedFlangeSize          )
    Q_PROPERTY(int      mMethodOfContract     READ getMethodOfContract     NOTIFY signalEventChangedMethodOfContract    )
    Q_PROPERTY(int      mBodyMaterial         READ getBodyMaterial         NOTIFY signalEventChangedBodyMaterial        )
    Q_PROPERTY(int      mCommInterface        READ getCommInterface        NOTIFY signalEventChangedCommInterface       )
    Q_PROPERTY(int      mPowerOption          READ getPowerOption          NOTIFY signalEventChangedPowerOption         )
    Q_PROPERTY(int      mQuantityOfSensors    READ getQuantityOfSensors    NOTIFY signalEventChangedQuantityOfSensors   )
    Q_PROPERTY(int      mVersion01            READ getVersion01            NOTIFY signalEventChangedVersion01           )
    Q_PROPERTY(int      mVersion02            READ getVersion02            NOTIFY signalEventChangedVersion02           )
    Q_PROPERTY(int      mVersion03            READ getVersion03            NOTIFY signalEventChangedVersion03           )
    Q_PROPERTY(int      mProductNumber        READ getProductNumber        NOTIFY signalEventChangedProductNumber       )
    Q_PROPERTY(QString  mFirmwareVersion      READ getFirmwareVersion      NOTIFY signalEventChangedFirmwareVersion     )
    Q_PROPERTY(bool     mErrSerialNumber      READ getErrSerialNumber      NOTIFY signalEventChangedErrSerialNumber     )
    Q_PROPERTY(bool     mErrValveModel        READ getErrValveModel        NOTIFY signalEventChangedErrValveModel       )
    Q_PROPERTY(bool     mErrValveType         READ getErrValveType         NOTIFY signalEventChangedErrValveType        )
    Q_PROPERTY(bool     mErrSealingType       READ getErrSealingType       NOTIFY signalEventChangedErrSealingType      )
    Q_PROPERTY(bool     mErrFlangeSize        READ getErrFlangeSize        NOTIFY signalEventChangedErrFlangeSize       )
    Q_PROPERTY(bool     mErrMethodOfContract  READ getErrMethodOfContract  NOTIFY signalEventChangedErrMethodOfContract )
    Q_PROPERTY(bool     mErrBodyMaterial      READ getErrBodyMaterial      NOTIFY signalEventChangedErrBodyMaterial     )
    Q_PROPERTY(bool     mErrCommInterface     READ getErrCommInterface     NOTIFY signalEventChangedErrCommInterface    )
    Q_PROPERTY(bool     mErrPowerOption       READ getErrPowerOption       NOTIFY signalEventChangedErrPowerOption      )
    Q_PROPERTY(bool     mErrQuantityOfSensors READ getErrQuantityOfSensors NOTIFY signalEventChangedErrQuantityOfSensors)
    Q_PROPERTY(bool     mErrVersion01         READ getErrVersion01         NOTIFY signalEventChangedErrVersion01        )
    Q_PROPERTY(bool     mErrVersion02         READ getErrVersion02         NOTIFY signalEventChangedErrVersion02        )
    Q_PROPERTY(bool     mErrVersion03         READ getErrVersion03         NOTIFY signalEventChangedErrVersion03        )
    Q_PROPERTY(bool     mErrProductNumber     READ getErrProductNumber     NOTIFY signalEventChangedErrProductNumber    )
    Q_PROPERTY(bool     mErrFirmwareVersion   READ getErrFirmwareVersion   NOTIFY signalEventChangedErrFirmwareVersion  )

    Q_PROPERTY(bool     mIsEdit               READ getIsEdit               NOTIFY signalEventChangedIsEdit              )
    Q_PROPERTY(QString  mStrStatus            READ getStrStatus            NOTIFY signalEventChangedStrStatus           )
    Q_PROPERTY(QString  mErrMsg               READ getErrMsg               NOTIFY signalEventChangedErrMsg              )
    Q_PROPERTY(QString  mErrMsg2              READ getErrMsg2              NOTIFY signalEventChangedErrMsg2             )
    Q_PROPERTY(int      mProgress             READ getProgress             NOTIFY signalEventChangedProgress            )

public:
    int     mAccessMode           = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test          = false;
    QString mSerialNumber         = "";
    int     mValveModel           = 0;
    int     mValveType            = 0;
    int     mSealingType          = 0;
    int     mFlangeSize           = 0;
    int     mMethodOfContract     = 0;
    int     mBodyMaterial         = 0;
    int     mCommInterface        = 0;
    int     mPowerOption          = 0;
    int     mQuantityOfSensors    = 0;
    int     mVersion01            = 0;
    int     mVersion02            = 0;
    int     mVersion03            = 0;
    int     mProductNumber        = 0;
    QString mFirmwareVersion      = 0;
    bool    mErrSerialNumber      = false;
    bool    mErrValveModel        = false;
    bool    mErrValveType         = false;
    bool    mErrSealingType       = false;
    bool    mErrFlangeSize        = false;
    bool    mErrMethodOfContract  = false;
    bool    mErrBodyMaterial      = false;
    bool    mErrCommInterface     = false;
    bool    mErrPowerOption       = false;
    bool    mErrQuantityOfSensors = false;
    bool    mErrVersion01         = false;
    bool    mErrVersion02         = false;
    bool    mErrVersion03         = false;
    bool    mErrProductNumber     = false;
    bool    mErrFirmwareVersion   = false;
    bool    mIsEdit               = false;
    QString mStrStatus            = "Loading";
    QString mErrMsg               = "";
    QString mErrMsg2              = "";
    int     mProgress             = 0 ;

    int     getAccessMode          (){ return mAccessMode          ;}
    bool    getIsRS232Test         (){ return mIsRS232Test         ;}
    QString getSerialNumber        (){ return mSerialNumber        ;}
    int     getValveModel          (){ return mValveModel          ;}
    int     getValveType           (){ return mValveType           ;}
    int     getSealingType         (){ return mSealingType         ;}
    int     getFlangeSize          (){ return mFlangeSize          ;}
    int     getMethodOfContract    (){ return mMethodOfContract    ;}
    int     getBodyMaterial        (){ return mBodyMaterial        ;}
    int     getCommInterface       (){ return mCommInterface       ;}
    int     getPowerOption         (){ return mPowerOption         ;}
    int     getQuantityOfSensors   (){ return mQuantityOfSensors   ;}
    int     getVersion01           (){ return mVersion01           ;}
    int     getVersion02           (){ return mVersion02           ;}
    int     getVersion03           (){ return mVersion03           ;}
    int     getProductNumber       (){ return mProductNumber       ;}
    QString getFirmwareVersion     (){ return mFirmwareVersion     ;}
    bool    getErrSerialNumber     (){ return mErrSerialNumber     ;}
    bool    getErrValveModel       (){ return mErrValveModel       ;}
    bool    getErrValveType        (){ return mErrValveType        ;}
    bool    getErrSealingType      (){ return mErrSealingType      ;}
    bool    getErrFlangeSize       (){ return mErrFlangeSize       ;}
    bool    getErrMethodOfContract (){ return mErrMethodOfContract ;}
    bool    getErrBodyMaterial     (){ return mErrBodyMaterial     ;}
    bool    getErrCommInterface    (){ return mErrCommInterface    ;}
    bool    getErrPowerOption      (){ return mErrPowerOption      ;}
    bool    getErrQuantityOfSensors(){ return mErrQuantityOfSensors;}
    bool    getErrVersion01        (){ return mErrVersion01        ;}
    bool    getErrVersion02        (){ return mErrVersion02        ;}
    bool    getErrVersion03        (){ return mErrVersion03        ;}
    bool    getErrProductNumber    (){ return mErrProductNumber    ;}
    bool    getErrFirmwareVersion  (){ return mErrFirmwareVersion  ;}
    bool    getIsEdit              (){ return mIsEdit              ;}
    QString getStrStatus           (){ return mStrStatus           ;}
    QString getErrMsg              (){ return mErrMsg              ;}
    QString getErrMsg2             (){ return mErrMsg2             ;}
    int     getProgress            (){ return mProgress            ;}

    void    setAccessMode          (int     value){ if(mAccessMode           == value)return; mAccessMode           = value; emit signalEventChangedAccessMode          (value);}
    void    setIsRS232Test         (bool    value){ if(mIsRS232Test          == value)return; mIsRS232Test          = value; emit signalEventChangedIsRS232Test         (value);}
    void    setSerialNumber        (QString value){ if(mSerialNumber         == value)return; mSerialNumber         = value; emit signalEventChangedSerialNumber        (value);}
    void    setValveModel          (int     value){ if(mValveModel           == value)return; mValveModel           = value; emit signalEventChangedValveModel          (value);}
    void    setValveType           (int     value){ if(mValveType            == value)return; mValveType            = value; emit signalEventChangedValveType           (value);}
    void    setSealingType         (int     value){ if(mSealingType          == value)return; mSealingType          = value; emit signalEventChangedSealingType         (value);}
    void    setFlangeSize          (int     value){ if(mFlangeSize           == value)return; mFlangeSize           = value; emit signalEventChangedFlangeSize          (value);}
    void    setMethodOfContract    (int     value){ if(mMethodOfContract     == value)return; mMethodOfContract     = value; emit signalEventChangedMethodOfContract    (value);}
    void    setBodyMaterial        (int     value){ if(mBodyMaterial         == value)return; mBodyMaterial         = value; emit signalEventChangedBodyMaterial        (value);}
    void    setCommInterface       (int     value){ if(mCommInterface        == value)return; mCommInterface        = value; emit signalEventChangedCommInterface       (value);}
    void    setPowerOption         (int     value){ if(mPowerOption          == value)return; mPowerOption          = value; emit signalEventChangedPowerOption         (value);}
    void    setQuantityOfSensors   (int     value){ if(mQuantityOfSensors    == value)return; mQuantityOfSensors    = value; emit signalEventChangedQuantityOfSensors   (value);}
    void    setVersion01           (int     value){ if(mVersion01            == value)return; mVersion01            = value; emit signalEventChangedVersion01           (value);}
    void    setVersion02           (int     value){ if(mVersion02            == value)return; mVersion02            = value; emit signalEventChangedVersion02           (value);}
    void    setVersion03           (int     value){ if(mVersion03            == value)return; mVersion03            = value; emit signalEventChangedVersion03           (value);}
    void    setProductNumber       (int     value){ if(mProductNumber        == value)return; mProductNumber        = value; emit signalEventChangedProductNumber       (value);}
    void    setFirmwareVersion     (QString value){ if(mFirmwareVersion      == value)return; mFirmwareVersion      = value; emit signalEventChangedFirmwareVersion     (value);}
    void    setErrSerialNumber     (bool    value){ if(mErrSerialNumber      == value)return; mErrSerialNumber      = value; emit signalEventChangedErrSerialNumber     (value);}
    void    setErrValveModel       (bool    value){ if(mErrValveModel        == value)return; mErrValveModel        = value; emit signalEventChangedErrValveModel       (value);}
    void    setErrValveType        (bool    value){ if(mErrValveType         == value)return; mErrValveType         = value; emit signalEventChangedErrValveType        (value);}
    void    setErrSealingType      (bool    value){ if(mErrSealingType       == value)return; mErrSealingType       = value; emit signalEventChangedErrSealingType      (value);}
    void    setErrFlangeSize       (bool    value){ if(mErrFlangeSize        == value)return; mErrFlangeSize        = value; emit signalEventChangedErrFlangeSize       (value);}
    void    setErrMethodOfContract (bool    value){ if(mErrMethodOfContract  == value)return; mErrMethodOfContract  = value; emit signalEventChangedErrMethodOfContract (value);}
    void    setErrBodyMaterial     (bool    value){ if(mErrBodyMaterial      == value)return; mErrBodyMaterial      = value; emit signalEventChangedErrBodyMaterial     (value);}
    void    setErrCommInterface    (bool    value){ if(mErrCommInterface     == value)return; mErrCommInterface     = value; emit signalEventChangedErrCommInterface    (value);}
    void    setErrPowerOption      (bool    value){ if(mErrPowerOption       == value)return; mErrPowerOption       = value; emit signalEventChangedErrPowerOption      (value);}
    void    setErrQuantityOfSensors(bool    value){ if(mErrQuantityOfSensors == value)return; mErrQuantityOfSensors = value; emit signalEventChangedErrQuantityOfSensors(value);}
    void    setErrVersion01        (bool    value){ if(mErrVersion01         == value)return; mErrVersion01         = value; emit signalEventChangedErrVersion01        (value);}
    void    setErrVersion02        (bool    value){ if(mErrVersion02         == value)return; mErrVersion02         = value; emit signalEventChangedErrVersion02        (value);}
    void    setErrVersion03        (bool    value){ if(mErrVersion03         == value)return; mErrVersion03         = value; emit signalEventChangedErrVersion03        (value);}
    void    setErrProductNumber    (bool    value){ if(mErrProductNumber     == value)return; mErrProductNumber     = value; emit signalEventChangedErrProductNumber    (value);}
    void    setErrFirmwareVersion  (bool    value){ if(mErrFirmwareVersion   == value)return; mErrFirmwareVersion   = value; emit signalEventChangedErrFirmwareVersion  (value);}
    void    setIsEdit              (bool    value){ if(mIsEdit               == value)return; mIsEdit               = value; emit signalEventChangedIsEdit              (value);}
    void    setStrStatus           (QString value){ if(mStrStatus            == value)return; mStrStatus            = value; emit signalEventChangedStrStatus           (value);}
    void    setErrMsg              (QString value){ if(mErrMsg               == value)return; mErrMsg               = value; emit signalEventChangedErrMsg              (value);}
    void    setErrMsg2             (QString value){ if(mErrMsg2              == value)return; mErrMsg2              = value; emit signalEventChangedErrMsg2             (value);}
    void    setProgress            (int     value){ if(mProgress             == value)return; mProgress             = value; emit signalEventChangedProgress            (value);}

signals:
    void signalEventChangedAccessMode          (int     value);
    void signalEventChangedIsRS232Test         (bool    value);
    void signalEventChangedSerialNumber        (QString value);
    void signalEventChangedValveModel          (int     value);
    void signalEventChangedValveType           (int     value);
    void signalEventChangedSealingType         (int     value);
    void signalEventChangedFlangeSize          (int     value);
    void signalEventChangedMethodOfContract    (int     value);
    void signalEventChangedBodyMaterial        (int     value);
    void signalEventChangedCommInterface       (int     value);
    void signalEventChangedPowerOption         (int     value);
    void signalEventChangedQuantityOfSensors   (int     value);
    void signalEventChangedVersion01           (int     value);
    void signalEventChangedVersion02           (int     value);
    void signalEventChangedVersion03           (int     value);
    void signalEventChangedProductNumber       (int     value);
    void signalEventChangedFirmwareVersion     (QString value);
    void signalEventChangedErrSerialNumber     (bool    value);
    void signalEventChangedErrValveModel       (bool    value);
    void signalEventChangedErrValveType        (bool    value);
    void signalEventChangedErrSealingType      (bool    value);
    void signalEventChangedErrFlangeSize       (bool    value);
    void signalEventChangedErrMethodOfContract (bool    value);
    void signalEventChangedErrBodyMaterial     (bool    value);
    void signalEventChangedErrCommInterface    (bool    value);
    void signalEventChangedErrPowerOption      (bool    value);
    void signalEventChangedErrQuantityOfSensors(bool    value);
    void signalEventChangedErrVersion01        (bool    value);
    void signalEventChangedErrVersion02        (bool    value);
    void signalEventChangedErrVersion03        (bool    value);
    void signalEventChangedErrProductNumber    (bool    value);
    void signalEventChangedErrFirmwareVersion  (bool    value);
    void signalEventChangedIsEdit              (bool    value);
    void signalEventChangedStrStatus           (QString value);
    void signalEventChangedErrMsg              (QString value);
    void signalEventChangedErrMsg2             (QString value);
    void signalEventChangedProgress            (int     value);
    void signalEventCompletedLoad              (             );
    void signalEventCompletedApply             (             );


public:
    explicit ValveIdentificationExDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_VALVE_ID;
        ENABLE_SLOT_VALVE_READED_FIRMWARE_VERSION;
        ENABLE_SLOT_VALVE_READED_VALVE_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_START;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_END;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_SERIALNUM);

    }
    ~ValveIdentificationExDlgModel()
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

    void onValveReadedValveID(ValveResponseValveIdDto dto)
    {
        if(mState != eState::STATE_READ_SERIALNUM || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setSerialNumber(dto.mValveID);

        setState((eState)(mState + 1));
    }

    void onValveReadedValveParam(ValveResponseValveParamDto dto)
    {
        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_VALVE_PARAM).length(), 2).toInt();

        if(id != convertParamID(mState) || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setParam(dto.mID, dto.mValue);

        setState((eState)(mState + 1));
    }

    void onValveReadedFirmwareVersion(ValveResponseFirmwareVersionDto dto)
    {
        if(mState != eState::STATE_READ_FIRMWAREVERSION || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setIsEdit(  getErrSerialNumber     () ||
                        getErrValveModel       () ||
                        getErrValveType        () ||
                        getErrSealingType      () ||
                        getErrFlangeSize       () ||
                        getErrMethodOfContract () ||
                        getErrBodyMaterial     () ||
                        getErrCommInterface    () ||
                        getErrPowerOption      () ||
                        getErrQuantityOfSensors() ||
                        getErrVersion01        () ||
                        getErrVersion02        () ||
                        getErrVersion03        () ||
                        getErrProductNumber    () ||
                        getErrFirmwareVersion  ()   );
        }
        setFirmwareVersion(dto.mFirmwareVersion);

        // < ver 2205260298  - adaptive delta gain not need

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int valveModelIdx, int valveTypeIdx, int sealingTypeIdx, int flangeSizeIdx, int methodOfContractIdx, int bodyMaterialIdx, int commInterfaceIdx, int powerOptionIdx, int quantityOfSensorsIdx, int version01Idx, int version02Idx, int version03Idx, int productNumberIdx)
    {
        mIsWritten = true;
        mWriteValveModelIdx        = valveModelIdx       ;
        mWriteValveTypeIdx         = valveTypeIdx        ;
        mWriteSealingTypeIdx       = sealingTypeIdx      ;
        mWriteFlangeSizeIdx        = flangeSizeIdx       ;
        mWriteMethodOfContractIdx  = methodOfContractIdx ;
        mWriteBodyMaterialIdx      = bodyMaterialIdx     ;
        mWriteCommInterfaceIdx     = commInterfaceIdx    ;
        mWritePowerOptionIdx       = powerOptionIdx      ;
        mWriteQuantityOfSensorsIdx = quantityOfSensorsIdx;
        mWriteVersion01Idx         = version01Idx        ;
        mWriteVersion02Idx         = version02Idx        ;
        mWriteVersion03Idx         = version03Idx        ;
        mWriteProductNumberIdx     = productNumberIdx    ;

        setErrMsg2("");
        setState(eState::STATE_WRITE_START);
    }

    void onValveWrittenValveParamStart(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_START || dto.mReqDto.mpRef != this)
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

    void onValveWrittenValveParam(ValveResponseDto dto)
    {
        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_WRITE_VALVE_PARAM).length(), 2).toInt();

        if(dto.mReqDto.mpRef != this || id != convertParamID(mState))
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

    void onValveWrittenValveParamEnd(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_END || dto.mReqDto.mpRef != this)
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
        STATE_WRITE_START             = 0,
        STATE_WRITE_VALVEMODEL        = STATE_WRITE_START             + 1,
        STATE_WRITE_VALVETYPE         = STATE_WRITE_VALVEMODEL        + 1,
        STATE_WRITE_SEALINGTYPE       = STATE_WRITE_VALVETYPE         + 1,
        STATE_WRITE_FLANGESIZE        = STATE_WRITE_SEALINGTYPE       + 1,
        STATE_WRITE_METHODOFCONTRACT  = STATE_WRITE_FLANGESIZE        + 1,
        STATE_WRITE_BODYMATERIAL      = STATE_WRITE_METHODOFCONTRACT  + 1,
        STATE_WRITE_COMMINTERFACE     = STATE_WRITE_BODYMATERIAL      + 1,
        STATE_WRITE_POWEROPTION       = STATE_WRITE_COMMINTERFACE     + 1,
        STATE_WRITE_QUANTITYOFSENSORS = STATE_WRITE_POWEROPTION       + 1,
        STATE_WRITE_VERSION_01        = STATE_WRITE_QUANTITYOFSENSORS + 1,
        STATE_WRITE_VERSION_02        = STATE_WRITE_VERSION_01        + 1,
        STATE_WRITE_VERSION_03        = STATE_WRITE_VERSION_02        + 1,
        STATE_WRITE_PRODUCTNUM        = STATE_WRITE_VERSION_03        + 1,
        STATE_WRITE_END               = STATE_WRITE_PRODUCTNUM        + 1,
        STATE_READ_SERIALNUM          = STATE_WRITE_END               + 1,
        STATE_READ_VALVEMODEL         = STATE_READ_SERIALNUM          + 1,
        STATE_READ_VALVETYPE          = STATE_READ_VALVEMODEL         + 1,
        STATE_READ_SEALINGTYPE        = STATE_READ_VALVETYPE          + 1,
        STATE_READ_FLANGESIZE         = STATE_READ_SEALINGTYPE        + 1,
        STATE_READ_METHODOFCONTRACT   = STATE_READ_FLANGESIZE         + 1,
        STATE_READ_BODYMATERIAL       = STATE_READ_METHODOFCONTRACT   + 1,
        STATE_READ_COMMINTERFACE      = STATE_READ_BODYMATERIAL       + 1,
        STATE_READ_POWEROPTION        = STATE_READ_COMMINTERFACE      + 1,
        STATE_READ_QUANTITYOFSENSORS  = STATE_READ_POWEROPTION        + 1,
        STATE_READ_VERSION_01         = STATE_READ_QUANTITYOFSENSORS  + 1,
        STATE_READ_VERSION_02         = STATE_READ_VERSION_01         + 1,
        STATE_READ_VERSION_03         = STATE_READ_VERSION_02         + 1,
        STATE_READ_PRODUCTNUM         = STATE_READ_VERSION_03         + 1,
        STATE_READ_FIRMWAREVERSION    = STATE_READ_PRODUCTNUM         + 1,
        STATE_READY                   = STATE_READ_FIRMWAREVERSION    + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_SERIALNUM;

    bool mIsWritten                 = false;
    int  mWriteValveModelIdx        = 0;
    int  mWriteValveTypeIdx         = 0;
    int  mWriteSealingTypeIdx       = 0;
    int  mWriteFlangeSizeIdx        = 0;
    int  mWriteMethodOfContractIdx  = 0;
    int  mWriteBodyMaterialIdx      = 0;
    int  mWriteCommInterfaceIdx     = 0;
    int  mWritePowerOptionIdx       = 0;
    int  mWriteQuantityOfSensorsIdx = 0;
    int  mWriteVersion01Idx         = 0;
    int  mWriteVersion02Idx         = 0;
    int  mWriteVersion03Idx         = 0;
    int  mWriteProductNumberIdx     = 0;

    int convertParamID(eState state)
    {
        if(state < eState::STATE_READ_SERIALNUM)
            return (int)state - (int)eState::STATE_WRITE_VALVEMODEL;
        else
            return (int)state - (int)eState::STATE_READ_VALVEMODEL;
    }

    int getWriteValueByState(eState state)
    {
        switch ((int)state) {
        case (int)eState::STATE_WRITE_VALVEMODEL       :
            return mWriteValveModelIdx                 ;
        case (int)eState::STATE_WRITE_VALVETYPE        :
            return mWriteValveTypeIdx                  ;
        case (int)eState::STATE_WRITE_SEALINGTYPE      :
            return mWriteSealingTypeIdx                ;
        case (int)eState::STATE_WRITE_FLANGESIZE       :
            return mWriteFlangeSizeIdx                 ;
        case (int)eState::STATE_WRITE_METHODOFCONTRACT :
            return mWriteMethodOfContractIdx           ;
        case (int)eState::STATE_WRITE_BODYMATERIAL     :
            return mWriteBodyMaterialIdx               ;
        case (int)eState::STATE_WRITE_COMMINTERFACE    :
            return mWriteCommInterfaceIdx              ;
        case (int)eState::STATE_WRITE_POWEROPTION      :
            return mWritePowerOptionIdx                ;
        case (int)eState::STATE_WRITE_QUANTITYOFSENSORS:
            return mWriteQuantityOfSensorsIdx          ;
        case (int)eState::STATE_WRITE_VERSION_01       :
            return mWriteVersion01Idx                  ;
        case (int)eState::STATE_WRITE_VERSION_02       :
            return mWriteVersion02Idx                  ;
        case (int)eState::STATE_WRITE_VERSION_03       :
            return mWriteVersion03Idx                  ;
        case (int)eState::STATE_WRITE_PRODUCTNUM       :
            return mWriteProductNumberIdx              ;
        }

        return 0;
    }

    void setParam(int paramID, QString paramValue)// khko : edit int to qstring
    {
        bool result = false;
        int idxValue = paramValue.toInt(&result, 16);

        switch (paramID) {
        case (int)QmlEnumDef::VALVEPARAM_VALVE_MODEL:
            if(mIsWritten == false)
            {
                setValveModel(idxValue);
            }
            else
            {
                setErrValveModel(mWriteValveModelIdx!= idxValue);
                setValveModel(mWriteValveModelIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_VALVE_TYPE:
            if(mIsWritten == false)
            {
                setValveType(idxValue);
            }
            else
            {
                setErrValveType(mWriteValveTypeIdx!= idxValue);
                setValveType(mWriteValveTypeIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_SEALING_TYPE:
            if(mIsWritten == false)
            {
                setSealingType(idxValue);
            }
            else
            {
                setErrSealingType(mWriteSealingTypeIdx!= idxValue);
                setSealingType(mWriteSealingTypeIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_FLANGE_SIZE:
            if(mIsWritten == false)
            {
                setFlangeSize(idxValue);
            }
            else
            {
                setErrFlangeSize(mWriteFlangeSizeIdx!= idxValue);
                setFlangeSize(mWriteFlangeSizeIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_METHOD_CONTRACT:
            if(mIsWritten == false)
            {
                setMethodOfContract(idxValue);
            }
            else
            {
                setErrMethodOfContract(mWriteMethodOfContractIdx!= idxValue);
                setMethodOfContract(mWriteMethodOfContractIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_BODY_MATERIAL:
            if(mIsWritten == false)
            {
                setBodyMaterial(idxValue);
            }
            else
            {
                setErrBodyMaterial(mWriteBodyMaterialIdx!= idxValue);
                setBodyMaterial(mWriteBodyMaterialIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_COMM_INTERFACE:
            if(mIsWritten == false)
            {
                setCommInterface(idxValue);
            }
            else
            {
                setErrCommInterface(mWriteCommInterfaceIdx!= idxValue);
                setCommInterface(mWriteCommInterfaceIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_POWER_OPTION:
            if(mIsWritten == false)
            {
                setPowerOption(idxValue);
            }
            else
            {
                setErrPowerOption(mWritePowerOptionIdx!= idxValue);
                setPowerOption(mWritePowerOptionIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_QUANTITY_SENSORS:
            if(mIsWritten == false)
            {
                setQuantityOfSensors(idxValue);
            }
            else
            {
                setErrQuantityOfSensors(mWriteQuantityOfSensorsIdx!= idxValue);
                setQuantityOfSensors(mWriteQuantityOfSensorsIdx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_VERSION_01:
            if(mIsWritten == false)
            {
                setVersion01(idxValue);
            }
            else
            {
                setErrVersion01(mWriteVersion01Idx!= idxValue);
                setVersion01(mWriteVersion01Idx);
            }
            break;
        case (int)QmlEnumDef::VALVEPARAM_VERSION_02:
            if(mIsWritten == false)
            {
                setVersion02(idxValue);
            }
            else
            {
                setErrVersion02(mWriteVersion02Idx!= idxValue);
                setVersion02(mWriteVersion02Idx);
            }
            break;

        case (int)QmlEnumDef::VALVEPARAM_VERSION_03:
            if(mIsWritten == false)
            {
                setVersion03(idxValue);
            }
            else
            {
                setErrVersion03(mWriteVersion03Idx!= idxValue);
                setVersion03(mWriteVersion03Idx);
            }
            break;

        case (int)QmlEnumDef::VALVEPARAM_PRODUCTNUM:
            if(mIsWritten == false)
            {
                setProductNumber(idxValue);
            }
            else
            {
                setErrProductNumber(mWriteProductNumberIdx!= idxValue);
                setProductNumber(mWriteProductNumberIdx);
            }
            break;
        }
    }

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        int progress = 0;
        QString strStatus;

        if(mIsWritten == false && state == eState::STATE_READY)
        {
            emit signalEventCompletedLoad();
        }
        mState = state;

        if(mState < (int)eState::STATE_READY && mState >= STATE_READ_SERIALNUM)
        {
            progress = (mState * 100) / eState::STATE_READY;
            strStatus = "Loading";
        }
        else if(mState == (int)eState::STATE_READY)
        {
            progress = 100;
            strStatus = "Ready";
        }
        else
        {
            progress = ((mState - eState::STATE_WRITE_VALVEMODEL) * 100) / (eState::STATE_WRITE_END + 1);
            strStatus = "Writting";
        }

        setProgress(progress);
        setStrStatus(strStatus);
        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_SERIALNUM:
            pValveSP->readValvedID(this);
            break;
        case (int)eState::STATE_READ_VALVEMODEL:
        case (int)eState::STATE_READ_VALVETYPE:
        case (int)eState::STATE_READ_SEALINGTYPE:
        case (int)eState::STATE_READ_FLANGESIZE:
        case (int)eState::STATE_READ_METHODOFCONTRACT:
        case (int)eState::STATE_READ_BODYMATERIAL:
        case (int)eState::STATE_READ_COMMINTERFACE:
        case (int)eState::STATE_READ_POWEROPTION:
        case (int)eState::STATE_READ_QUANTITYOFSENSORS:
        case (int)eState::STATE_READ_VERSION_01:
        case (int)eState::STATE_READ_VERSION_02:
        case (int)eState::STATE_READ_VERSION_03:
        case (int)eState::STATE_READ_PRODUCTNUM:
            pValveSP->readValveParam(convertParamID(mState), this);
            break;
        case (int)eState::STATE_READ_FIRMWAREVERSION:
            pValveSP->readFirmwareVersion(this);
            break;

        case (int)eState::STATE_WRITE_START:
            pValveSP->setValveParamStart(this);
            break;
        case (int)eState::STATE_WRITE_VALVEMODEL:
        case (int)eState::STATE_WRITE_VALVETYPE:
        case (int)eState::STATE_WRITE_SEALINGTYPE:
        case (int)eState::STATE_WRITE_FLANGESIZE:
        case (int)eState::STATE_WRITE_METHODOFCONTRACT:
        case (int)eState::STATE_WRITE_BODYMATERIAL:
        case (int)eState::STATE_WRITE_COMMINTERFACE:
        case (int)eState::STATE_WRITE_POWEROPTION:
        case (int)eState::STATE_WRITE_QUANTITYOFSENSORS:
        case (int)eState::STATE_WRITE_VERSION_01:
        case (int)eState::STATE_WRITE_VERSION_02:
        case (int)eState::STATE_WRITE_VERSION_03:
        case (int)eState::STATE_WRITE_PRODUCTNUM:
            pValveSP->setValveParam(convertParamID(mState), QString("%1").arg(getWriteValueByState(mState),6,16,QChar('0')), this); // khko : edit int to qstring
            break;

        case (int)eState::STATE_WRITE_END:
            pValveSP->setValveParamEnd(this);
            break;
        }
    }
};
#endif // VALVEIDENTIFICATIONEXDLGMODEL_H
