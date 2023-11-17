#ifndef INTERFACESTATUSDNETDLGMODEL_H
#define INTERFACESTATUSDNETDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/qmlmodel/interfacesetupdevnetassemblyitemmodel.h"

class InterfaceStatusDNetDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mAccessMode               READ getAccessMode          NOTIFY signalEventChangedAccessMode         )
    Q_PROPERTY(bool    mIsRS232Test              READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test        )
    Q_PROPERTY(QString mMacValue                 READ getMacValue            NOTIFY signalEventChangedMacValue           )
    Q_PROPERTY(QString mBaudrate                 READ getBaudrate            NOTIFY signalEventChangedBaudrate           )
    Q_PROPERTY(QString mFirmwareValue            READ getFirmwareValue       NOTIFY signalEventChangedFirmwareValue      )
    Q_PROPERTY(QString mSerialNumValue           READ getSerialNumValue      NOTIFY signalEventChangedSerialNumValue     )
    Q_PROPERTY(QString mInputAssemblyValue       READ getInputAssemblyValue  NOTIFY signalEventChangedInputAssemblyValue )
    Q_PROPERTY(QString mOutputAssemblyValue      READ getOutputAssemblyValue NOTIFY signalEventChangedOutputAssemblyValue)
    Q_PROPERTY(QString mPositionUnitValue        READ getPositionUnitValue   NOTIFY signalEventChangedPositionUnitValue  )
    Q_PROPERTY(QString mPositionRangeValue       READ getPositionRangeValue  NOTIFY signalEventChangedPositionRangeValue )
    Q_PROPERTY(QString mPressureUnitValue        READ getPressureUnitValue   NOTIFY signalEventChangedPressureUnitValue  )
    Q_PROPERTY(QString mSensor01RangeValue       READ getSensor01RangeValue  NOTIFY signalEventChangedSensor01RangeValue )
    Q_PROPERTY(QString mSensor02RangeValue       READ getSensor02RangeValue  NOTIFY signalEventChangedSensor02RangeValue )
    Q_PROPERTY(int     mDIActivation             READ getDIActivation        NOTIFY signalEventChangedDIActivation       )
    Q_PROPERTY(int     mDIFunction               READ getDIFunction          NOTIFY signalEventChangedDIFunction         )
    Q_PROPERTY(int     mDIPolarity               READ getDIPolarity          NOTIFY signalEventChangedDIPolarity         )
    Q_PROPERTY(int     mDOActivation             READ getDOActivation        NOTIFY signalEventChangedDOActivation       )
    Q_PROPERTY(int     mDOFunction               READ getDOFunction          NOTIFY signalEventChangedDOFunction         )
    Q_PROPERTY(int     mDOPolarity               READ getDOPolarity          NOTIFY signalEventChangedDOPolarity         )
    Q_PROPERTY(int     mStatusDI                 READ getStatusDI            NOTIFY signalEventChangedStatusDI           )
    Q_PROPERTY(int     mStatusDO                 READ getStatusDO            NOTIFY signalEventChangedStatusDO           )
    Q_PROPERTY(QString mDevStatus                READ getDevStatus           NOTIFY signalEventChangedDevStatus          )
    Q_PROPERTY(bool    mAlarmDevComm             READ getAlarmDevComm        NOTIFY signalEventChangedAlarmDevComm       )
    Q_PROPERTY(bool    mAlarmDevSpecific         READ getAlarmDevSpecific    NOTIFY signalEventChangedAlarmDevSpecific   )
    Q_PROPERTY(bool    mAlarmMenuSpecific        READ getAlarmMenuSpecific   NOTIFY signalEventChangedAlarmMenuSpecific  )
    Q_PROPERTY(bool    mWarningDevComm           READ getWarningDevComm      NOTIFY signalEventChangedWarningDevComm     )
    Q_PROPERTY(bool    mWarningDevSpecific       READ getWarningDevSpecific  NOTIFY signalEventChangedWarningDevSpecific )
    Q_PROPERTY(bool    mWarningMenuSpecific      READ getWarningMenuSpecific NOTIFY signalEventChangedWarningMenuSpecific)
    Q_PROPERTY(bool    mExpandedMode             READ getExpandedMode        NOTIFY signalEventChangedExpandedMode       )
    Q_PROPERTY(bool    mEnableDI                 READ getEnableDI            NOTIFY signalEventChangedEnableDI           )
    Q_PROPERTY(bool    mEnableDO                 READ getEnableDO            NOTIFY signalEventChangedEnableDO           )
    Q_PROPERTY(bool    mEnableDevStatus          READ getEnableDevStatus     NOTIFY signalEventChangedEnableDevStatus    )
    Q_PROPERTY(bool    mEnableExStatus           READ getEnableExStatus      NOTIFY signalEventChangedEnableExStatus     )
    Q_PROPERTY(bool    mIsEdit                   READ getIsEdit              NOTIFY signalEventChangedIsEdit             )
    Q_PROPERTY(QString mStrStatus                READ getStrStatus           NOTIFY signalEventChangedStrStatus          )
    Q_PROPERTY(QString mErrMsg                   READ getErrMsg              NOTIFY signalEventChangedErrMsg             )
    Q_PROPERTY(int     mProgress                 READ getProgress            NOTIFY signalEventChangedProgress           )

public:
    int     mAccessMode          = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test         = false;
    QString mMacValue            = "unknow";
    QString mBaudrate            = "";
    QString mFirmwareValue       = "not supported";
    QString mSerialNumValue      = "not supported";
    QString mInputAssemblyValue  = "-";
    QString mOutputAssemblyValue = "-";
    QString mPositionUnitValue   = "unknow";
    QString mPositionRangeValue  = 0;
    QString mPressureUnitValue   = "unknow";
    QString mSensor01RangeValue  = 0;
    QString mSensor02RangeValue  = 0;
    int     mDIActivation        = 0;
    int     mDIFunction          = 0;
    int     mDIPolarity          = 0;
    int     mDOActivation        = 0;
    int     mDOFunction          = 0;
    int     mDOPolarity          = 0;
    int     mStatusDI            = 0;
    int     mStatusDO            = 0;
    QString mDevStatus           = "undefined";
    bool    mAlarmDevComm        = false;
    bool    mAlarmDevSpecific    = false;
    bool    mAlarmMenuSpecific   = false;
    bool    mWarningDevComm      = false;
    bool    mWarningDevSpecific  = false;
    bool    mWarningMenuSpecific = false;
    bool    mExpandedMode        = false;
    bool    mEnableDI            = false;
    bool    mEnableDO            = false;
    bool    mEnableDevStatus     = false;
    bool    mEnableExStatus      = false;
    bool    mIsEdit              = false;
    QString mStrStatus           = "Loading";
    QString mErrMsg              = "";
    int     mProgress            = 0 ;

    int     getAccessMode         (){return mAccessMode         ;}
    bool    getIsRS232Test        (){return mIsRS232Test        ;}
    QString getMacValue           (){return mMacValue           ;}
    QString getBaudrate           (){return mBaudrate           ;}
    QString getFirmwareValue      (){return mFirmwareValue      ;}
    QString getSerialNumValue     (){return mSerialNumValue     ;}
    QString getInputAssemblyValue (){return mInputAssemblyValue ;}
    QString getOutputAssemblyValue(){return mOutputAssemblyValue;}
    QString getPositionUnitValue  (){return mPositionUnitValue  ;}
    QString getPositionRangeValue (){return mPositionRangeValue ;}
    QString getPressureUnitValue  (){return mPressureUnitValue  ;}
    QString getSensor01RangeValue (){return mSensor01RangeValue ;}
    QString getSensor02RangeValue (){return mSensor02RangeValue ;}
    int     getDIActivation       (){return mDIActivation       ;}
    int     getDIFunction         (){return mDIFunction         ;}
    int     getDIPolarity         (){return mDIPolarity         ;}
    int     getDOActivation       (){return mDOActivation       ;}
    int     getDOFunction         (){return mDOFunction         ;}
    int     getDOPolarity         (){return mDOPolarity         ;}
    int     getStatusDI           (){return mStatusDI           ;}
    int     getStatusDO           (){return mStatusDO           ;}
    QString getDevStatus          (){return mDevStatus          ;}
    bool    getAlarmDevComm       (){return mAlarmDevComm       ;}
    bool    getAlarmDevSpecific   (){return mAlarmDevSpecific   ;}
    bool    getAlarmMenuSpecific  (){return mAlarmMenuSpecific  ;}
    bool    getWarningDevComm     (){return mWarningDevComm     ;}
    bool    getWarningDevSpecific (){return mWarningDevSpecific ;}
    bool    getWarningMenuSpecific(){return mWarningMenuSpecific;}
    bool    getExpandedMode       (){return mExpandedMode       ;}
    bool    getEnableDI           (){return mEnableDI           ;}
    bool    getEnableDO           (){return mEnableDO           ;}
    bool    getEnableDevStatus    (){return mEnableDevStatus    ;}
    bool    getEnableExStatus     (){return mEnableExStatus     ;}
    bool    getIsEdit             (){return mIsEdit             ;}
    QString getStrStatus          (){return mStrStatus          ;}
    QString getErrMsg             (){return mErrMsg             ;}
    int     getProgress           (){return mProgress           ;}

    void setAccessMode         (int     value){if(mAccessMode          == value)return; mAccessMode          = value; emit signalEventChangedAccessMode         (value);}
    void setIsRS232Test        (bool    value){if(mIsRS232Test         == value)return; mIsRS232Test         = value; emit signalEventChangedIsRS232Test        (value);}
    void setMacValue           (QString value){if(mMacValue            == value)return; mMacValue            = value; emit signalEventChangedMacValue           (value);}
    void setBaudrate           (QString value){                                         mBaudrate            = value; emit signalEventChangedBaudrate           (value);}
    void setFirmwareValue      (QString value){if(mFirmwareValue       == value)return; mFirmwareValue       = value; emit signalEventChangedFirmwareValue      (value);}
    void setSerialNumValue     (QString value){if(mSerialNumValue      == value)return; mSerialNumValue      = value; emit signalEventChangedSerialNumValue     (value);}
    void setInputAssemblyValue (QString value){if(mInputAssemblyValue  == value)return; mInputAssemblyValue  = value; emit signalEventChangedInputAssemblyValue (value);}
    void setOutputAssemblyValue(QString value){if(mOutputAssemblyValue == value)return; mOutputAssemblyValue = value; emit signalEventChangedOutputAssemblyValue(value);}
    void setPositionUnitValue  (QString value){if(mPositionUnitValue   == value)return; mPositionUnitValue   = value; emit signalEventChangedPositionUnitValue  (value);}
    void setPositionRangeValue (QString value){if(mPositionRangeValue  == value)return; mPositionRangeValue  = value; emit signalEventChangedPositionRangeValue (value);}
    void setPressureUnitValue  (QString value){if(mPressureUnitValue   == value)return; mPressureUnitValue   = value; emit signalEventChangedPressureUnitValue  (value);}
    void setSensor01RangeValue (QString value){if(mSensor01RangeValue  == value)return; mSensor01RangeValue  = value; emit signalEventChangedSensor01RangeValue (value);}
    void setSensor02RangeValue (QString value){if(mSensor02RangeValue  == value)return; mSensor02RangeValue  = value; emit signalEventChangedSensor02RangeValue (value);}
    void setDIActivation       (int     value){if(mDIActivation        == value)return; mDIActivation        = value; emit signalEventChangedDIActivation       (value);}
    void setDIFunction         (int     value){if(mDIFunction          == value)return; mDIFunction          = value; emit signalEventChangedDIFunction         (value);}
    void setDIPolarity         (int     value){if(mDIPolarity          == value)return; mDIPolarity          = value; emit signalEventChangedDIPolarity         (value);}
    void setDOActivation       (int     value){if(mDOActivation        == value)return; mDOActivation        = value; emit signalEventChangedDOActivation       (value);}
    void setDOFunction         (int     value){if(mDOFunction          == value)return; mDOFunction          = value; emit signalEventChangedDOFunction         (value);}
    void setDOPolarity         (int     value){if(mDOPolarity          == value)return; mDOPolarity          = value; emit signalEventChangedDOPolarity         (value);}
    void setStatusDI           (int     value){if(mStatusDI            == value)return; mStatusDI            = value; emit signalEventChangedStatusDI           (value);}
    void setStatusDO           (int     value){if(mStatusDO            == value)return; mStatusDO            = value; emit signalEventChangedStatusDO           (value);}
    void setDevStatus          (QString value){if(mDevStatus           == value)return; mDevStatus           = value; emit signalEventChangedDevStatus          (value);}
    void setAlarmDevComm       (bool    value){if(mAlarmDevComm        == value)return; mAlarmDevComm        = value; emit signalEventChangedAlarmDevComm       (value);}
    void setAlarmDevSpecific   (bool    value){if(mAlarmDevSpecific    == value)return; mAlarmDevSpecific    = value; emit signalEventChangedAlarmDevSpecific   (value);}
    void setAlarmMenuSpecific  (bool    value){if(mAlarmMenuSpecific   == value)return; mAlarmMenuSpecific   = value; emit signalEventChangedAlarmMenuSpecific  (value);}
    void setWarningDevComm     (bool    value){if(mWarningDevComm      == value)return; mWarningDevComm      = value; emit signalEventChangedWarningDevComm     (value);}
    void setWarningDevSpecific (bool    value){if(mWarningDevSpecific  == value)return; mWarningDevSpecific  = value; emit signalEventChangedWarningDevSpecific (value);}
    void setWarningMenuSpecific(bool    value){if(mWarningMenuSpecific == value)return; mWarningMenuSpecific = value; emit signalEventChangedWarningMenuSpecific(value);}
    void setExpandedMode       (bool    value){if(mExpandedMode        == value)return; mExpandedMode        = value; emit signalEventChangedExpandedMode       (value);}
    void setEnableDI           (bool    value){if(mEnableDI            == value)return; mEnableDI            = value; emit signalEventChangedEnableDI           (value);}
    void setEnableDO           (bool    value){if(mEnableDO            == value)return; mEnableDO            = value; emit signalEventChangedEnableDO           (value);}
    void setEnableDevStatus    (bool    value){if(mEnableDevStatus     == value)return; mEnableDevStatus     = value; emit signalEventChangedEnableDevStatus    (value);}
    void setEnableExStatus     (bool    value){if(mEnableExStatus      == value)return; mEnableExStatus      = value; emit signalEventChangedEnableExStatus     (value);}
    void setIsEdit             (bool    value){if(mIsEdit              == value)return; mIsEdit              = value; emit signalEventChangedIsEdit             (value);}
    void setStrStatus          (QString value){if(mStrStatus           == value)return; mStrStatus           = value; emit signalEventChangedStrStatus          (value);}
    void setErrMsg             (QString value){if(mErrMsg              == value)return; mErrMsg              = value; emit signalEventChangedErrMsg             (value);}
    void setProgress           (int     value){if(mProgress            == value)return; mProgress            = value; emit signalEventChangedProgress           (value);}


signals:
    void signalEventChangedAccessMode         (int     value);
    void signalEventChangedIsRS232Test        (bool    value);
    void signalEventChangedMacValue           (QString value);
    void signalEventChangedBaudrate           (QString value);
    void signalEventChangedFirmwareValue      (QString value);
    void signalEventChangedSerialNumValue     (QString value);
    void signalEventChangedInputAssemblyValue (QString value);
    void signalEventChangedOutputAssemblyValue(QString value);
    void signalEventChangedPositionUnitValue  (QString value);
    void signalEventChangedPositionRangeValue (QString value);
    void signalEventChangedPressureUnitValue  (QString value);
    void signalEventChangedSensor01RangeValue (QString value);
    void signalEventChangedSensor02RangeValue (QString value);
    void signalEventChangedDIActivation       (int     value);
    void signalEventChangedDIFunction         (int     value);
    void signalEventChangedDIPolarity         (int     value);
    void signalEventChangedDOActivation       (int     value);
    void signalEventChangedDOFunction         (int     value);
    void signalEventChangedDOPolarity         (int     value);
    void signalEventChangedStatusDI           (int     value);
    void signalEventChangedStatusDO           (int     value);
    void signalEventChangedDevStatus          (QString value);
    void signalEventChangedAlarmDevComm       (bool    value);
    void signalEventChangedAlarmDevSpecific   (bool    value);
    void signalEventChangedAlarmMenuSpecific  (bool    value);
    void signalEventChangedWarningDevComm     (bool    value);
    void signalEventChangedWarningDevSpecific (bool    value);
    void signalEventChangedWarningMenuSpecific(bool    value);
    void signalEventChangedExpandedMode       (bool    value);
    void signalEventChangedEnableDI           (bool    value);
    void signalEventChangedEnableDO           (bool    value);
    void signalEventChangedEnableDevStatus    (bool    value);
    void signalEventChangedEnableExStatus     (bool    value);
    void signalEventChangedIsEdit             (bool    value);
    void signalEventChangedStrStatus          (QString value);
    void signalEventChangedErrMsg             (QString value);
    void signalEventChangedProgress           (int     value);

public:
    explicit InterfaceStatusDNetDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS                      ;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST               ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_MAC              ;
        ENABLE_SLOT_VALVE_READED_IF_DNET_FIRMWARE_ID          ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_BAUDRATE         ;
        ENABLE_SLOT_VALVE_READED_IF_DNET_SERIAL_NUM           ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_POS_UNIT         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_POS_GAIN         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_PRESSURE_UNIT    ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_S01_GAIN         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_S02_GAIN         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_INPUT_ASS        ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_OUTPUT_ASS       ;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DI            ;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DO            ;
        ENABLE_SLOT_VALVE_READED_IF_STATUS_DNET               ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_DEV_STATUS       ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_EX_STATUS        ;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        pConfigSP->loadInterfaceDNetAssembly();
        loadAssemblyTable();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_FIRMWARE_ID);
    }
    ~InterfaceStatusDNetDlgModel()
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

    void onValveReadedInterfaceCfgDNetMAC(ValveResponseInterfaceConfigDNetMacDto dto)
    {
        if(mState != eState::STATE_READ_MAC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
            setMacValue(QString("%1").arg(dto.mMacAddr,2,10,QChar('0')));
        else
            setMacValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetBaudrate(ValveResponseInterfaceConfigDNetBaudrateDto dto)
    {
        if(mState != eState::STATE_READ_BAUDRATE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
        {
            switch (dto.mBaudrate)
            {
            case 0: setBaudrate("125k"); break;
            case 1: setBaudrate("250k"); break;
            case 2: setBaudrate("500k"); break;
            case 3: setBaudrate("auto"); break;
            }
        }
        else
            setBaudrate("auto");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceDNetFirmwareID(ValveResponseInterfaceDNetFirmwareIDDto dto)
    {
        if(mState != eState::STATE_READ_FIRMWARE_ID || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
            setFirmwareValue(dto.mFirmwareID);
        else
            setFirmwareValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceDNetSerialNum(ValveResponseInterfaceDNetSerialNumDto dto)
    {
        if(mState != eState::STATE_READ_SERIALNUM || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
            setSerialNumValue(dto.mSerialNum);
        else
            setSerialNumValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetPosUnit(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_POS_UNIT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
            setPositionUnitValue(transValueToUnitStr(dto.mValue));
        else
            setPositionUnitValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetPosGain(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_POS_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
        {
            int prec = 3;//calPositionFixedN(getPositionUnitIdx(getPositionUnitValue()));
            setPositionRangeValue(QString("%1").arg(calRange(dto.mValue),  0, 'f', prec)); // todo fixed (3)
        }
        else
            setPositionRangeValue("not supported");


        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetPressureUnit(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_PRESSURE_UNIT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
            setPressureUnitValue(transValueToUnitStr(dto.mValue));
        else
            setPressureUnitValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetSensor01Gain(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_S01_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
        {
            int prec = 3;//calPressureFixedN(getPressureUnitIdx(getPressureUnitValue()), pValveSP->getS01FullScalePrec(), pValveSP->getS01SullScaleUnit());
            setSensor01RangeValue(QString("%1").arg(calRange(dto.mValue),  0, 'f', prec)); // todo fixed (3)
        }
        else
            setSensor01RangeValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetSensor02Gain(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_S02_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
        {
            int prec = 3;//calPressureFixedN(getPressureUnitIdx(getPressureUnitValue()), pValveSP->getS02FullScalePrec(), pValveSP->getS02SullScaleUnit());
            setSensor02RangeValue(QString("%1").arg(calRange(dto.mValue),  0, 'f', prec)); // todo fixed (3)
        }
        else
            setSensor02RangeValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetInputAss(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_IN_ASS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
            setInputAssemblySeqArrayByHexValue(dto.mValue);
        else
            setInputAssemblyValue("not supported");

        setState((eState)(mState + 1));
    }
    void onValveReadedInterfaceCfgDNetOutputAss(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_OUT_ASS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
            setOutputAssemblySeqArrayByHexValue(dto.mValue);
        else
            setOutputAssemblyValue("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetDi(ValveResponseInterfaceConfigDNetDiDto dto)
    {
        if(mState != eState::STATE_READ_DI || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setEnableDI(dto.mIsSucc);

        if(dto.mIsSucc)
        {
            setDIActivation(dto.mDIActivation);
            setDIFunction  (dto.mDIFunction  );
            setDIPolarity  (dto.mDIPolarity  );
        }

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceCfgDNetDo(ValveResponseInterfaceConfigDNetDoDto dto)
    {
        if(mState != eState::STATE_READ_DO || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setEnableDO(dto.mIsSucc);

        if(dto.mIsSucc)
        {
            setDOActivation(dto.mDOActivation);
            setDOFunction  (dto.mDOFunction  );
            setDOPolarity  (dto.mDOPolarity  );
        }

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceStatusDNet(ValveResponseInterfaceStatusDNetDto dto)
    {
        if(mState != eState::STATE_READ_IO_STATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(dto.mIsSucc)
        {
            setStatusDI(dto.mStatusDI);
            setStatusDO(dto.mStatusDO);
        }
        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceCfgDNetDevStatus(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_DSTATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setEnableDevStatus(dto.mIsSucc);

        if(dto.mIsSucc)
        {
            setDevStatus(transMaskValueToDevStatus(dto.mValue));
        }
        else
            setDevStatus("not supported");

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetExStatus(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_EX_STATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setEnableExStatus(dto.mIsSucc);

        if(dto.mIsSucc)
        {
            int masked = dto.mValue.toInt(nullptr, 16);

            setAlarmDevComm       ((masked & 0x01) != 0);
            setAlarmDevSpecific   ((masked & 0x02) != 0);
            setAlarmMenuSpecific  ((masked & 0x04) != 0);
            setWarningDevComm     ((masked & 0x10) != 0);
            setWarningDevSpecific ((masked & 0x20) != 0);
            setWarningMenuSpecific((masked & 0x40) != 0);
            setExpandedMode       ((masked & 0x80) != 0);
        }
        else
        {
            setAlarmDevComm       (false);
            setAlarmDevSpecific   (false);
            setAlarmMenuSpecific  (false);
            setWarningDevComm     (false);
            setWarningDevSpecific (false);
            setWarningMenuSpecific(false);
            setExpandedMode       (false);
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE int onCommandGetInputAssemblyItemCount()
    {
        return mInputTable.size();
    }

    Q_INVOKABLE InterfaceSetupDevNetAssemblyItemModel * onCommandGetInputAssemblyItem(int seq)
    {
        if(seq < 1)
            return nullptr;

        return mInputTable.at(seq - 1);
    }

    Q_INVOKABLE void onCommandSelectInputAssemblyItem(int seq, bool isSelect)
    {
        int procSeq = 1;
        InterfaceSetupDevNetAssemblyItemModel * pSelectedItem = onCommandGetInputAssemblyItem(seq);
        InterfaceSetupDevNetAssemblyItemModel * pDependentItem = onCommandGetInputAssemblyItem(pSelectedItem->getDepSeq());

        pSelectedItem->setIsSelected(isSelect);
        procSeq = seq;

        if(pDependentItem != nullptr && isSelect)
        {
            pDependentItem->setIsSelected(!isSelect);
        }

        int nextIdx = 0;

        foreach(InterfaceSetupDevNetAssemblyItemModel * pItem, mInputTable)
        {
            if(pItem->getIsSelected())
            {
                pItem->setIndex(nextIdx);
                nextIdx = nextIdx + pItem->getLength();
            }
        }
    }

    Q_INVOKABLE int onCommandGetOutputAssemblyItemCount()
    {
        return mOutputTable.size();
    }

    Q_INVOKABLE InterfaceSetupDevNetAssemblyItemModel * onCommandGetOutputAssemblyItem(int seq)
    {
        if(seq < 1)
            return nullptr;

        return mOutputTable.at(seq - 1);
    }

    Q_INVOKABLE void onCommandSelectOutputAssemblyItem(int seq, bool isSelect)
    {
        int procSeq = 1;
        InterfaceSetupDevNetAssemblyItemModel * pSelectedItem = onCommandGetOutputAssemblyItem(seq);
        InterfaceSetupDevNetAssemblyItemModel * pDependentItem = onCommandGetOutputAssemblyItem(pSelectedItem->getDepSeq());

        pSelectedItem->setIsSelected(isSelect);
        procSeq = seq;

        if(pDependentItem != nullptr && isSelect)
        {
            pDependentItem->setIsSelected(!isSelect);
        }

        int nextIdx = 0;

        foreach(InterfaceSetupDevNetAssemblyItemModel * pItem, mOutputTable)
        {
            if(pItem->getIsSelected())
            {
                pItem->setIndex(nextIdx);
                nextIdx = nextIdx + pItem->getLength();
            }
        }
    }

private:
    enum eState{
        STATE_READ_FIRMWARE_ID    = 0,
        STATE_READ_SERIALNUM      = STATE_READ_FIRMWARE_ID   + 1,
        STATE_READ_POS_UNIT       = STATE_READ_SERIALNUM     + 1,
        STATE_READ_POS_GAIN       = STATE_READ_POS_UNIT      + 1,
        STATE_READ_PRESSURE_UNIT  = STATE_READ_POS_GAIN      + 1,
        STATE_READ_S01_GAIN       = STATE_READ_PRESSURE_UNIT + 1,
        STATE_READ_S02_GAIN       = STATE_READ_S01_GAIN      + 1,
        STATE_READ_IN_ASS         = STATE_READ_S02_GAIN      + 1,
        STATE_READ_OUT_ASS        = STATE_READ_IN_ASS        + 1,
        STATE_READ_DI             = STATE_READ_OUT_ASS       + 1,
        STATE_READ_DO             = STATE_READ_DI            + 1,
        STATE_READ_IO_STATUS      = STATE_READ_DO            + 1,
        STATE_READ_DSTATUS        = STATE_READ_IO_STATUS     + 1,
        STATE_READ_EX_STATUS      = STATE_READ_DSTATUS       + 1,
        STATE_READ_BAUDRATE       = STATE_READ_EX_STATUS     + 1,
        STATE_READ_MAC            = STATE_READ_BAUDRATE      + 1,
        STATE_OVER                = STATE_READ_MAC           + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_FIRMWARE_ID;
    qint64 mLastScanMSec  = 0;
    bool   mIsFirstRead   = true;

    QList<InterfaceSetupDevNetAssemblyItemModel *>mInputTable;
    QList<InterfaceSetupDevNetAssemblyItemModel *>mOutputTable;

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
            state = eState::STATE_READ_IO_STATUS;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_EX_STATUS));
        }
        else if(state == eState::STATE_READ_IO_STATUS)
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
        case (int)eState::STATE_READ_MAC          : pValveSP->readInterfaceConfigDNetMac         (this); break;
        case (int)eState::STATE_READ_BAUDRATE     : pValveSP->readInterfaceConfigDNetBaudrate    (this); break;
        case (int)eState::STATE_READ_FIRMWARE_ID  : pValveSP->readInterfaceDNetFirmwareID        (this); break;
        case (int)eState::STATE_READ_SERIALNUM    : pValveSP->readInterfaceDNetSerialNum         (this); break;
        case (int)eState::STATE_READ_POS_UNIT     : pValveSP->readInterfaceConfigDNetPosUnit     (this); break;
        case (int)eState::STATE_READ_POS_GAIN     : pValveSP->readInterfaceConfigDNetPosGain     (this); break;
        case (int)eState::STATE_READ_PRESSURE_UNIT: pValveSP->readInterfaceConfigDNetPressureUnit(this); break;
        case (int)eState::STATE_READ_S01_GAIN     : pValveSP->readInterfaceConfigDNetSensor01Gain(this); break;
        case (int)eState::STATE_READ_S02_GAIN     : pValveSP->readInterfaceConfigDNetSensor02Gain(this); break;
        case (int)eState::STATE_READ_IN_ASS       : pValveSP->readInterfaceConfigDNetInputAss    (this); break;
        case (int)eState::STATE_READ_OUT_ASS      : pValveSP->readInterfaceConfigDNetOutputAss   (this); break;
        case (int)eState::STATE_READ_DI           : pValveSP->readInterfaceConfigDNetDi          (this); break;
        case (int)eState::STATE_READ_DO           : pValveSP->readInterfaceConfigDNetDo          (this); break;
        case (int)eState::STATE_READ_IO_STATUS    : pValveSP->readInterfaceStatusDNet            (this); break;
        case (int)eState::STATE_READ_DSTATUS      : pValveSP->readInterfaceConfigDNetDevStatus   (this); break;
        case (int)eState::STATE_READ_EX_STATUS    : pValveSP->readInterfaceConfigDNetExStatus    (this); break;
        }
    }

private:
    QString transMaskValueToDevStatus(QString value)
    {
        int status = value.toInt(nullptr, 16);

        switch (status) {
        case 0x01: return "synchronization";
        case 0x02: return "POSITION CONTROL";
        case 0x03: return "CLOSED";
        case 0x04: return "OPEN";
        case 0x05: return "PRESSURE CONTROL";
        case 0x06: return "HOLD";
        case 0x07: return "LEARN";
        case 0x0C: return "power failure";
        case 0x0D: return "safety mode";
        case 0x0E: return "fatal error";
        }

        return "undefined";
    }
    QString transValueToUnitStr(QString value)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << value;
        int unit = value.toInt(nullptr, 16);

        switch (unit) {
        case 4097: return "counts" ; // 0x1001
        case 4103: return "percent"; // 0x1007
        case 4864: return "psi"    ; // 0x1300
        case 4865: return "Torr"   ; // 0x1301
        case 4866: return "mTorr"  ; // 0x1302
        case 4871: return "bar"    ; // 0x1307
        case 4872: return "mbar"   ; // 0x1308
        case 4873: return "pa"     ; // 0x1309
        case 4875: return "atm"    ; // 0x120B
        case 5891: return "degree" ; // 0x1703
        }
        return "unknow";
    }

    double calRange(QString value)
    {
        float gain;
        QByteArray hexBuff;
        QByteArray floatBuff;

        hexBuff.append(value.at(6));
        hexBuff.append(value.at(7));
        hexBuff.append(value.at(4));
        hexBuff.append(value.at(5));
        hexBuff.append(value.at(2));
        hexBuff.append(value.at(3));
        hexBuff.append(value.at(0));
        hexBuff.append(value.at(1));

        floatBuff = QByteArray::fromHex(hexBuff);

        gain = *((float *)floatBuff.data());

        return gain;
    }

//    double calRange(QString value)
//    {
//        float gain;
//        QByteArray hexBuff;
//        QByteArray floatBuff;

//        hexBuff.append(value.at(6));
//        hexBuff.append(value.at(7));
//        hexBuff.append(value.at(4));
//        hexBuff.append(value.at(5));
//        hexBuff.append(value.at(2));
//        hexBuff.append(value.at(3));
//        hexBuff.append(value.at(0));
//        hexBuff.append(value.at(1));

//        floatBuff = QByteArray::fromHex(hexBuff);

//        gain = *((float *)floatBuff.data());

//        return 10000.0 * gain;
//    }

    void setInputAssemblySeqArrayByHexValue(QString value)
    {
        quint32 maskedValue = value.toUInt(nullptr, 16);

        for(quint32 shift = 0; shift < 32 && shift < (quint32)mInputTable.size(); shift++)
        {
            quint32 mask = (0x00000001 << shift) & 0xFFFFFFFF;
            onCommandSelectInputAssemblyItem(shift + 1, (maskedValue & mask) != 0);
        }
    }

    void setOutputAssemblySeqArrayByHexValue(QString value)
    {
        quint32 maskedValue = value.toUInt(nullptr, 16);

        for(quint32 shift = 0; shift < 32 && shift < (quint32)mOutputTable.size(); shift++)
        {
            quint32 mask = (0x00000001 << shift) & 0xFFFFFFFF;
            onCommandSelectOutputAssemblyItem(shift + 1, (maskedValue & mask) != 0);
        }
    }

    int getPositionUnitIdx(QString unitValue)
    {
        if     (unitValue == "counts ")return 0;
        else if(unitValue == "percent")return 1;
        else if(unitValue == "degree ")return 2;

        return 0;
    }
    int getPressureUnitIdx(QString unitValue)
    {
        if     (unitValue == "counts ")return 0;
        else if(unitValue == "percent")return 1;
        else if(unitValue == "psi    ")return 2;
        else if(unitValue == "Torr   ")return 3;
        else if(unitValue == "mTorr  ")return 4;
        else if(unitValue == "bar    ")return 5;
        else if(unitValue == "mbar   ")return 6;
        else if(unitValue == "pa     ")return 7;
        else if(unitValue == "atm    ")return 8;

        return 0;
    }

    int calPositionFixedN(int unitIdx)
    {
        switch (unitIdx) {
        case 1: return 0;
        case 2: return 0;
        default: return 3;
        }
    }

    int calPressureFixedN(int unitIdx, int fullScalePrec, int fullScaleUnit)
    {
        int selUnit;
        int precision;

        switch (unitIdx) {
        case 1: precision = 0; return precision;
        case 2: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_PSI  ;break;  // psi
        case 3: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_TORR ;break;  // torr
        case 4: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_MTORR;break;  // mtorr
        case 5: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_BAR  ;break;  // bar
        case 6: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_MBAR ;break;  // mbar
        case 7: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_PA   ;break;  // pa
        case 8: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_ATM  ;break;  // atm
            break;
        default: precision = 3; return precision;
        }

        precision = fullScalePrec + UNITUTIL_ADD_PRECISION(fullScaleUnit, selUnit);
        precision = precision < 0 ? 0 : precision > 6 ? 6 : precision;

        return precision;
    }

    void loadAssemblyTable()
    {
        int itemCount;

        itemCount = pConfigSP->mInputAssemblyTable.size();

        foreach(DNetAssemblyItem item, pConfigSP->mInputAssemblyTable)
        {
            InterfaceSetupDevNetAssemblyItemModel * pQmlItem = new InterfaceSetupDevNetAssemblyItemModel(item);
            mInputTable.append(pQmlItem);
        }

        itemCount = pConfigSP->mOutputAssemblyTable.size();

        foreach(DNetAssemblyItem item, pConfigSP->mOutputAssemblyTable)
        {
            InterfaceSetupDevNetAssemblyItemModel * pQmlItem = new InterfaceSetupDevNetAssemblyItemModel(item);
            mOutputTable.append(pQmlItem);
        }
    }
};

#endif // INTERFACESTATUSDNETDLGMODEL_H
