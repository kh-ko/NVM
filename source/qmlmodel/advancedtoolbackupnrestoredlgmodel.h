#ifndef ADVANCEDTOOLBACKUPNRESTOREDLGMODEL_H
#define ADVANCEDTOOLBACKUPNRESTOREDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

class ValveCommandItem
{
public:
    QString mVarName;
    QString mReadCommand;
    QString mReadResCommand = "";
    QString mWriteCommand;
    QString mValue;

    ValveCommandItem(){}
    ValveCommandItem(const ValveCommandItem& copy):mVarName       (copy.mVarName       ),
                                                   mReadCommand   (copy.mReadCommand   ),
                                                   mReadResCommand(copy.mReadResCommand),
                                                   mWriteCommand  (copy.mWriteCommand  ),
                                                   mValue         (copy.mValue         ){}

    ~ValveCommandItem(){}

    ValveCommandItem& operator=(const ValveCommandItem& other)
    {
        mVarName        = other.mVarName       ;
        mReadCommand    = other.mReadCommand   ;
        mReadResCommand = other.mReadResCommand;
        mWriteCommand   = other.mWriteCommand  ;
        mValue          = other.mValue         ;

        return *this;
    }

    void setCommand(QString varName, QString readCmd, QString writeCmd, QString readResCmd = "")
    {
        mVarName        = varName;
        mReadCommand    = readCmd;
        mReadResCommand = readResCmd;
        mWriteCommand   = writeCmd;
    }
};

Q_DECLARE_METATYPE(ValveCommandItem);

class AdvancedToolBackupNRestoreDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode               NOTIFY signalEventChangedAccessMode         )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test              NOTIFY signalEventChangedIsRS232Test        )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                   NOTIFY signalEventChangedIsEdit             )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus                NOTIFY signalEventChangedStrStatus          )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                   NOTIFY signalEventChangedErrMsg             )
    Q_PROPERTY(int      mProgress                READ getProgress                 NOTIFY signalEventChangedProgress           )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "ready";
    QString mErrMsg                  = "";
    int     mProgress                = 100 ;

    int     getAccessMode (){ return mAccessMode; }
    bool    getIsRS232Test(){ return pValveSP->getIsRS232Test(); }
    bool    getIsEdit     (){ return mIsEdit    ; }
    QString getStrStatus  (){ return mStrStatus ; }
    QString getErrMsg     (){ return mErrMsg    ; }
    int     getProgress   (){ return mProgress  ; }

    void    setAccessMode (int     value){if(mAccessMode                == value)return; mAccessMode              = value; emit signalEventChangedAccessMode (value);}
    void    setIsEdit     (bool    value){if(mIsEdit                    == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit     (value);}
    void    setStrStatus  (QString value){if(mStrStatus                 == value)return; mStrStatus               = value; emit signalEventChangedStrStatus  (value);}
    void    setErrMsg     (QString value){if(mErrMsg                    == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg     (value);}
    void    setProgress   (int     value){if(mProgress                  == value)return; mProgress                = value; emit signalEventChangedProgress   (value);}

signals:

    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );
    void signalEventCompletedApply                (             );
    void signalEventCompletedExport               (             );
    void signalEventWrittenSettingToFile          (             );
    void signalEventWrittenSettingToValve         (             );

private:
    QString exportFilePath;
    int                     mExportCmdIdx = 0;
    int                     mExportLearnListIdx = 0;
    QList<ValveCommandItem> mExportCmdList;
    int                     mImportCmdIdx = 0;
    QList<QString>          mImportCmdList;

    /* Sensor setup */
    QList<ValveCommandItem> mSensorCmdList;
    /* Sensor setup ex*/
    QList<ValveCommandItem> mSensorExCmdList;
    /* Pressure control setup */
    QList<ValveCommandItem> mPressureCtrlCmdList;
    /* Pressure control float setup */
    QList<ValveCommandItem> mPressureCtrlFloatCmdList;
    /* Interface logic*/
    QList<ValveCommandItem> mIFLogicCmdList;
    /* Interface ether cat*/
    QList<ValveCommandItem> mIFEtherCATCmdList;
    /* Interface RS485*/
    QList<ValveCommandItem> mIFRS485CmdList;
    /* Interface ether net*/
    QList<ValveCommandItem> mIFEtherNETCmdList;
    /* Interface d-net*/
    QList<ValveCommandItem> mIFDevNETCmdList;
    /* Interface RS232*/
    QList<ValveCommandItem> mIFRS232CmdList;

public:
    explicit AdvancedToolBackupNRestoreDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ValveCommandItem tempItem;

        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        //ENABLE_SLOT_VALVE_CHANGED_IS_TEST_MODE;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_SENSEX_SEL;
        ENABLE_SLOT_VALVE_READED_SEL_CONTROL_MODE;
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READY);
    }
    ~AdvancedToolBackupNRestoreDlgModel()
    {
    }

private:
    enum eState{
        STATE_EXPORT_SENSOR_CHECK        = 0,
        STATE_EXPORT_PRESSURE_CTRL_CHECK = STATE_EXPORT_SENSOR_CHECK        + 1,
        STATE_EXPORT_SETTING             = STATE_EXPORT_PRESSURE_CTRL_CHECK + 1,
        STATE_EXPORT_LEARNLIST           = STATE_EXPORT_SETTING             + 1,
        STATE_IMPORT_SETTING             = STATE_EXPORT_LEARNLIST           + 1,
        STATE_READY                      = STATE_IMPORT_SETTING             + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READY;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state, bool immediately = false)
    {
        mState = state;

        if(state < (int) eState::STATE_READY && state >= (int) eState::STATE_IMPORT_SETTING)
        {
            setStrStatus("import");
        }
        else if(state < (int) eState::STATE_IMPORT_SETTING && state >= (int) eState::STATE_EXPORT_SENSOR_CHECK)
        {
            setStrStatus("export");
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
            if(state <= (int) eState::STATE_EXPORT_LEARNLIST && state >= (int) eState::STATE_EXPORT_SENSOR_CHECK)
                setProgress(qFloor((mExportCmdIdx * 80 ) / mExportCmdList.size()));
            else
                setProgress(qFloor((mImportCmdIdx * 100) / mImportCmdList.size()));

            if(immediately)
                onTimeout();
            else
                startTimer();
        }
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedIsRS232Test()
    {
        emit signalEventChangedIsRS232Test(getIsRS232Test());
    }

    void onValveReadedSensorExSelection(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        ValveCommandItem tempItem;

        if(mState != eState::STATE_EXPORT_SENSOR_CHECK || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc && dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            tempItem.setCommand("Sensor Config",QString("%1").arg(REQ_READ_SENSOR_CONFIG), QString("%1").arg(REQ_WRITE_SENSOR_CONFIG)); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor Scale" ,QString("%1").arg(REQ_READ_SENSOR_SCALE ), QString("%1").arg(REQ_WRITE_SENSOR_SCALE )); mExportCmdList.append(tempItem);
        }
        else
        {
            tempItem.setCommand("Sensor Selection"                              , QString("%1").arg(REQ_READ_SENSEX_SEL                        ), QString("%1").arg(REQ_WRITE_SENSEX_SEL                        )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Analog Active"                        , QString("%1").arg(REQ_READ_SENSEX_S01_ANAL_ACTIVE            ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ANAL_ACTIVE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Source"                               , QString("%1").arg(REQ_READ_SENSEX_S01_SRC                    ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SRC                    )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Unit"                                 , QString("%1").arg(REQ_READ_SENSEX_S01_UNIT                   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_UNIT                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Full Scale"                           , QString("%1").arg(REQ_READ_SENSEX_S01_FULLSCALE              ), QString("%1").arg(REQ_WRITE_SENSEX_S01_FULLSCALE              )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Digital value"                        , QString("%1").arg(REQ_READ_SENSEX_S01_DIGI                   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_DIGI                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Zero Enable"                          , QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_ENABLE            ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_ENABLE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Zero Min"                             , QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_MIN               ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_MIN               )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Zero Max"                             , QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_MAX               ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_MAX               )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Zero Value"                           , QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_VALUE             ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_VALUE             )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Scale Offset"                         , QString("%1").arg(REQ_READ_SENSEX_S01_SCALE_OFFSET           ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE_OFFSET           )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Scale Value"                          , QString("%1").arg(REQ_READ_SENSEX_S01_SCALE                  ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE                  )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Scale Z Point"                        , QString("%1").arg(REQ_READ_SENSEX_S01_SCALE_Z_POINT          ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE_Z_POINT          )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Filter Source"                        , QString("%1").arg(REQ_READ_SENSEX_S01_FILTER_SEC             ), QString("%1").arg(REQ_WRITE_SENSEX_S01_FILTER_SEC             )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 Linearize"                            , QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_LINEARIZE     ), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_LINEARIZE     )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 logarithmic sensor Voltage Decade"    , QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_VOLT_DECADE   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_DECADE   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 1 logarithmic sensor Voltage Full Scale", QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE)); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Analog Active"                        , QString("%1").arg(REQ_READ_SENSEX_S02_ANAL_ACTIVE            ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ANAL_ACTIVE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Source"                               , QString("%1").arg(REQ_READ_SENSEX_S02_SRC                    ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SRC                    )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Unit"                                 , QString("%1").arg(REQ_READ_SENSEX_S02_UNIT                   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_UNIT                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Full Scale"                           , QString("%1").arg(REQ_READ_SENSEX_S02_FULLSCALE              ), QString("%1").arg(REQ_WRITE_SENSEX_S02_FULLSCALE              )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Digital value"                        , QString("%1").arg(REQ_READ_SENSEX_S02_DIGI                   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_DIGI                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Zero Enable"                          , QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_ENABLE            ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_ENABLE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Zero Min"                             , QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_MIN               ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_MIN               )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Zero Max"                             , QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_MAX               ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_MAX               )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Zero Value"                           , QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_VALUE             ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_VALUE             )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Scale Offset"                         , QString("%1").arg(REQ_READ_SENSEX_S02_SCALE_OFFSET           ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE_OFFSET           )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Scale Value"                          , QString("%1").arg(REQ_READ_SENSEX_S02_SCALE                  ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE                  )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Scale Z Point"                        , QString("%1").arg(REQ_READ_SENSEX_S02_SCALE_Z_POINT          ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE_Z_POINT          )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Filter Source"                        , QString("%1").arg(REQ_READ_SENSEX_S02_FILTER_SEC             ), QString("%1").arg(REQ_WRITE_SENSEX_S02_FILTER_SEC             )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 Linearize"                            , QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_LINEARIZE     ), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_LINEARIZE     )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 logarithmic sensor Voltage Decade"    , QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_VOLT_DECADE   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_DECADE   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor 2 logarithmic sensor Voltage Full Scale", QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE)); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor Crossover Mode"                         , QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_MOD              ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_MOD              )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor Crossover Low"                          , QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_LOW              ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_LOW              )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor Crossover High"                         , QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_HIGH             ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_HIGH             )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Sensor Crossover Delta"                        , QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_DELA             ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_DELA             )); mExportCmdList.append(tempItem);
        }
        setState((eState)(mState + 1));
    }

    void onValveReadedSelControlMode (ValveResponseSelControlModeDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        int firmwareVer;
        ValveCommandItem tempItem;

        if(mState != eState::STATE_EXPORT_PRESSURE_CTRL_CHECK || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc && dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            tempItem.setCommand("Pressure Control Configuration", QString("%1").arg(REQ_READ_PRESSURE_CTRL_CONFIG), QString("%1").arg(REQ_WRITE_PRESSURE_CTRL_CONFIG)); mExportCmdList.append(tempItem);
        }
        else
        {
            tempItem.setCommand("Pressure Control Configuration Mode"        , QString("%1").arg(REQ_READ_SELECT_CTRL_MODE      ), QString("%1").arg(REQ_WRITE_SEL_CTRL_MODE         )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Adaptive-Gain Factor)" , QString("%1").arg(REQ_READ_ADAP_CTRL_GAIN_FAC    ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_GAIN_FAC    )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Adaptive-Delta Factor)", QString("%1").arg(REQ_READ_ADAP_CTRL_DELTA_FAC   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_DELTA_FAC   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Adaptive-Sensor Delay)", QString("%1").arg(REQ_READ_ADAP_CTRL_SENSOR_DELAY), QString("%1").arg(REQ_WRITE_ADAP_CTRL_SENSOR_DELAY)); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Adaptive-Ramp Time)"   , QString("%1").arg(REQ_READ_ADAP_CTRL_RAMP_TIME   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_RAMP_TIME   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Adaptive-Ramp Mode)"   , QString("%1").arg(REQ_READ_ADAP_CTRL_RAMP_MODE   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_RAMP_MODE   )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 1-P Gain)"       , QString("%1").arg(REQ_READ_FIXED1_CTRL_P_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_P_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 1-I Gain)"       , QString("%1").arg(REQ_READ_FIXED1_CTRL_I_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_I_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 1-Ramp Time)"    , QString("%1").arg(REQ_READ_FIXED1_CTRL_RAMP_TIME ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_RAMP_TIME )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 1-Ramp Mode)"    , QString("%1").arg(REQ_READ_FIXED1_CTRL_RAMP_MODE ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_RAMP_MODE )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 1-Direction)"    , QString("%1").arg(REQ_READ_FIXED1_CTRL_DIR       ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_DIR       )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 2-P Gain)"       , QString("%1").arg(REQ_READ_FIXED2_CTRL_P_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_P_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 2-I Gain)"       , QString("%1").arg(REQ_READ_FIXED2_CTRL_I_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_I_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 2-Ramp Time)"    , QString("%1").arg(REQ_READ_FIXED2_CTRL_RAMP_TIME ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_RAMP_TIME )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 2-Ramp Mode)"    , QString("%1").arg(REQ_READ_FIXED2_CTRL_RAMP_MODE ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_RAMP_MODE )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Pressure Control Configuration(Fixed 2-Direction)"    , QString("%1").arg(REQ_READ_FIXED2_CTRL_DIR       ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_DIR       )); mExportCmdList.append(tempItem);
        }


        /* pressure control for pm protocol */
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Algorithm Mode)"       , QString("p:0B0711010000"), QString("p:010711010000"), QString("p:000B0711010000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Gain Factor)"          , QString("p:0B0711020300"), QString("p:010711020300"), QString("p:000B0711020300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Delta Factor)"         , QString("p:0B0711020700"), QString("p:010711020700"), QString("p:000B0711020700")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Sensor Delay)"         , QString("p:0B0711020400"), QString("p:010711020400"), QString("p:000B0711020400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Learn Data Selection)" , QString("p:0B0711020500"), QString("p:010711020500"), QString("p:000B0711020500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Direction)"            , QString("p:0B0711020600"), QString("p:010711020600"), QString("p:000B0711020600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 P Gain Factor)"        , QString("p:0B0711020100"), QString("p:010711020100"), QString("p:000B0711020100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 I Gain Factor)"        , QString("p:0B0711020200"), QString("p:010711020200"), QString("p:000B0711020200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Pressure Scaler)"      , QString("p:0B0711022300"), QString("p:010711022300"), QString("p:000B0711022300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Ramp Enable)"          , QString("p:0B0711030100"), QString("p:010711030100"), QString("p:000B0711030100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Ramp Time)"            , QString("p:0B0711030200"), QString("p:010711030200"), QString("p:000B0711030200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Ramp Slope)"           , QString("p:0B0711030300"), QString("p:010711030300"), QString("p:000B0711030300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Ramp Mode)"            , QString("p:0B0711030400"), QString("p:010711030400"), QString("p:000B0711030400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Ramp StartValue)"      , QString("p:0B0711030500"), QString("p:010711030500"), QString("p:000B0711030500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 1 Ramp Type)"            , QString("p:0B0711030600"), QString("p:010711030600"), QString("p:000B0711030600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Algorithm Mode)"       , QString("p:0B0712010000"), QString("p:010712010000"), QString("p:000B0712010000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Gain Factor)"          , QString("p:0B0712020300"), QString("p:010712020300"), QString("p:000B0712020300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Delta Factor)"         , QString("p:0B0712020700"), QString("p:010712020700"), QString("p:000B0712020700")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Sensor Delay)"         , QString("p:0B0712020400"), QString("p:010712020400"), QString("p:000B0712020400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Learn Data Selection)" , QString("p:0B0712020500"), QString("p:010712020500"), QString("p:000B0712020500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Direction)"            , QString("p:0B0712020600"), QString("p:010712020600"), QString("p:000B0712020600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 P Gain Factor)"        , QString("p:0B0712020100"), QString("p:010712020100"), QString("p:000B0712020100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 I Gain Factor)"        , QString("p:0B0712020200"), QString("p:010712020200"), QString("p:000B0712020200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Pressure Scaler)"      , QString("p:0B0712022300"), QString("p:010712022300"), QString("p:000B0712022300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Ramp Enable)"          , QString("p:0B0712030100"), QString("p:010712030100"), QString("p:000B0712030100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Ramp Time)"            , QString("p:0B0712030200"), QString("p:010712030200"), QString("p:000B0712030200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Ramp Slope)"           , QString("p:0B0712030300"), QString("p:010712030300"), QString("p:000B0712030300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Ramp Mode)"            , QString("p:0B0712030400"), QString("p:010712030400"), QString("p:000B0712030400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Ramp StartValue)"      , QString("p:0B0712030500"), QString("p:010712030500"), QString("p:000B0712030500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 2 Ramp Type)"            , QString("p:0B0712030600"), QString("p:010712030600"), QString("p:000B0712030600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Algorithm Mode)"       , QString("p:0B0713010000"), QString("p:010713010000"), QString("p:000B0713010000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Gain Factor)"          , QString("p:0B0713020300"), QString("p:010713020300"), QString("p:000B0713020300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Delta Factor)"         , QString("p:0B0713020700"), QString("p:010713020700"), QString("p:000B0713020700")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Sensor Delay)"         , QString("p:0B0713020400"), QString("p:010713020400"), QString("p:000B0713020400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Learn Data Selection)" , QString("p:0B0713020500"), QString("p:010713020500"), QString("p:000B0713020500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Direction)"            , QString("p:0B0713020600"), QString("p:010713020600"), QString("p:000B0713020600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 P Gain Factor)"        , QString("p:0B0713020100"), QString("p:010713020100"), QString("p:000B0713020100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 I Gain Factor)"        , QString("p:0B0713020200"), QString("p:010713020200"), QString("p:000B0713020200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Pressure Scaler)"      , QString("p:0B0713022300"), QString("p:010713022300"), QString("p:000B0713022300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Ramp Enable)"          , QString("p:0B0713030100"), QString("p:010713030100"), QString("p:000B0713030100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Ramp Time)"            , QString("p:0B0713030200"), QString("p:010713030200"), QString("p:000B0713030200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Ramp Slope)"           , QString("p:0B0713030300"), QString("p:010713030300"), QString("p:000B0713030300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Ramp Mode)"            , QString("p:0B0713030400"), QString("p:010713030400"), QString("p:000B0713030400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Ramp StartValue)"      , QString("p:0B0713030500"), QString("p:010713030500"), QString("p:000B0713030500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 3 Ramp Type)"            , QString("p:0B0713030600"), QString("p:010713030600"), QString("p:000B0713030600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Algorithm Mode)"       , QString("p:0B0714010000"), QString("p:010714010000"), QString("p:000B0714010000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Gain Factor)"          , QString("p:0B0714020300"), QString("p:010714020300"), QString("p:000B0714020300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Delta Factor)"         , QString("p:0B0714020700"), QString("p:010714020700"), QString("p:000B0714020700")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Sensor Delay)"         , QString("p:0B0714020400"), QString("p:010714020400"), QString("p:000B0714020400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Learn Data Selection)" , QString("p:0B0714020500"), QString("p:010714020500"), QString("p:000B0714020500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Direction)"            , QString("p:0B0714020600"), QString("p:010714020600"), QString("p:000B0714020600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 P Gain Factor)"        , QString("p:0B0714020100"), QString("p:010714020100"), QString("p:000B0714020100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 I Gain Factor)"        , QString("p:0B0714020200"), QString("p:010714020200"), QString("p:000B0714020200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Pressure Scaler)"      , QString("p:0B0714022300"), QString("p:010714022300"), QString("p:000B0714022300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Ramp Enable)"          , QString("p:0B0714030100"), QString("p:010714030100"), QString("p:000B0714030100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Ramp Time)"            , QString("p:0B0714030200"), QString("p:010714030200"), QString("p:000B0714030200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Ramp Slope)"           , QString("p:0B0714030300"), QString("p:010714030300"), QString("p:000B0714030300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Ramp Mode)"            , QString("p:0B0714030400"), QString("p:010714030400"), QString("p:000B0714030400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Ramp StartValue)"      , QString("p:0B0714030500"), QString("p:010714030500"), QString("p:000B0714030500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller 4 Ramp Type)"            , QString("p:0B0714030600"), QString("p:010714030600"), QString("p:000B0714030600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (controller S LECTOR)"               , QString("p:0B0710000000"), QString("p:010710000000"), QString("p:000B0710000000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Default Selected Contrller)"        , QString("p:0B0705000000"), QString("p:010705000000"), QString("p:000B0705000000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Position Restriction Enable)"       , QString("p:0B0730120100"), QString("p:010730120100"), QString("p:000B0730120100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Position Restriction Max)"          , QString("p:0B0730120300"), QString("p:010730120300"), QString("p:000B0730120300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Position Restriction Min)"          , QString("p:0B0730120200"), QString("p:010730120200"), QString("p:000B0730120200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Enable)"             , QString("p:0B0730170100"), QString("p:010730170100"), QString("p:000B0730170100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Mode)"               , QString("p:0B0730170200"), QString("p:010730170200"), QString("p:000B0730170200")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Pressure Rising)"    , QString("p:0B0730172000"), QString("p:010730172000"), QString("p:000B0730172000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Pressure Falling)"   , QString("p:0B0730172100"), QString("p:010730172100"), QString("p:000B0730172100")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection bitmap)"             , QString("p:0B0730170300"), QString("p:010730170300"), QString("p:000B0730170300")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Threshold Condition)", QString("p:0B0730171000"), QString("p:010730171000"), QString("p:000B0730171000")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Threshold 1)"        , QString("p:0B0730170400"), QString("p:010730170400"), QString("p:000B0730170400")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Threshold 2)"        , QString("p:0B0730170500"), QString("p:010730170500"), QString("p:000B0730170500")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Threshold 3)"        , QString("p:0B0730170600"), QString("p:010730170600"), QString("p:000B0730170600")); mExportCmdList.append(tempItem);
        tempItem.setCommand("Pressure Control Advenced Configuration (Auto Selection Threshold 4)"        , QString("p:0B0730170700"), QString("p:010730170700"), QString("p:000B0730170700")); mExportCmdList.append(tempItem);

        /* device net advenced range backup */
        //firmwareVer = pValveSP->getFirmwareVersion().mid(4).toInt(nullptr, 16);

        //if(firmwareVer > 0x600 && pValveSP->getInterface() ==  ValveEnumDef::INTERFACE_DEVICENET)
        //{
        //    tempItem.setCommand("Interface(Device Net) Advenced 1 Position Unit", QString("a:7250000B"), QString("a:7250010B")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 2 Pressure Unit", QString("a:7250000A"), QString("a:7250010A")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 1 Range Type"  , QString("i:2300"), QString("s:2300")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 2 Range Type"  , QString("i:2301"), QString("s:2301")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 3 Range Type"  , QString("i:2302"), QString("s:2302")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 4 Range Type"  , QString("i:2303"), QString("s:2303")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 5 Range Type"  , QString("i:2304"), QString("s:2304")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 6 Range Type"  , QString("i:2305"), QString("s:2305")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 7 Range Type"  , QString("i:2306"), QString("s:2306")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 8 Range Type"  , QString("i:2307"), QString("s:2307")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 9 Range Type"  , QString("i:2308"), QString("s:2308")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 10 Range Type" , QString("i:2309"), QString("s:2309")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 11 Range Type" , QString("i:2310"), QString("s:2310")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 12 Range Type" , QString("i:2311"), QString("s:2311")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 1 Range Value" , QString("i:2400"), QString("s:2400")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 2 Range Value" , QString("i:2401"), QString("s:2401")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 3 Range Value" , QString("i:2402"), QString("s:2402")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 4 Range Value" , QString("i:2403"), QString("s:2403")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 5 Range Value" , QString("i:2404"), QString("s:2404")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 6 Range Value" , QString("i:2405"), QString("s:2405")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 7 Range Value" , QString("i:2406"), QString("s:2406")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 8 Range Value" , QString("i:2407"), QString("s:2407")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 9 Range Value" , QString("i:2408"), QString("s:2408")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 10 Range Value", QString("i:2409"), QString("s:2409")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 11 Range Value", QString("i:2410"), QString("s:2410")); mExportCmdList.append(tempItem);
        //    tempItem.setCommand("Interface(Device Net) Advenced 12 Range Value", QString("i:2411"), QString("s:2411")); mExportCmdList.append(tempItem);
        //}
        setState((eState)(mState + 1));
    }

    void onValveWrittenCustomRequest(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(dto.mIsSucc == false && dto.mIsNetworkErr)
        {
            setErrMsg("communication error");
            setState(eState::STATE_READY);
            return;
        }

        if(mState == eState::STATE_EXPORT_SETTING)
        {
            if(dto.mResData.startsWith("p:") && dto.mResData.startsWith("p:00") == false )
            {
                dto.mIsSucc = false;
            }

            if(dto.mIsSucc == true)
            {
                if(mExportCmdList[mExportCmdIdx].mReadResCommand.length() > 0)
                {
                    mExportCmdList[mExportCmdIdx].mValue = dto.mResData.mid(mExportCmdList[mExportCmdIdx].mReadResCommand.length());
                }
                else
                {
                    mExportCmdList[mExportCmdIdx].mValue = dto.mResData.mid(mExportCmdList[mExportCmdIdx].mReadCommand.length());
                }
            }
            else
            {
                mExportCmdList[mExportCmdIdx].mValue = "skip";
            }
            mExportCmdIdx++;

            if(mExportCmdIdx == mExportCmdList.size())
            {
                //emit signalEventCompletedExport();
                setState(eState::STATE_EXPORT_LEARNLIST);
                return;
            }
        }
        else if(mState == eState::STATE_EXPORT_LEARNLIST)
        {
            ValveCommandItem tempItem;
            int lastIdx;
            if(dto.mIsSucc == true && mExportLearnListIdx == 0)
            {
                tempItem.setCommand("Lean List Start", QString("-"), QString("%1").arg(REQ_WRITE_LEARN_LIST_START)); mExportCmdList.append(tempItem);
            }
            else if(dto.mIsSucc == false)
            {
                tempItem.setCommand("Lean List End", QString("-"), QString("%1").arg(REQ_WRITE_LEARN_LIST_END)); mExportCmdList.append(tempItem);
                emit signalEventCompletedExport();
                setState(eState::STATE_READY);
                return;
            }

            tempItem.setCommand("Lean List Value",QString("%1%2").arg(REQ_READ_LEARN_LIST).arg(mExportLearnListIdx, 4,10,QChar('0')), QString("%1%2").arg(REQ_WRITE_LEARN_LIST).arg(mExportLearnListIdx, 4,10,QChar('0'))); mExportCmdList.append(tempItem);
            lastIdx = mExportCmdList.size() - 1;

            if(mExportCmdList[lastIdx].mReadResCommand.length() > 0)
            {
                mExportCmdList[lastIdx].mValue = dto.mResData.mid(mExportCmdList[lastIdx].mReadResCommand.length());
            }
            else
            {
                mExportCmdList[lastIdx].mValue = dto.mResData.mid(mExportCmdList[lastIdx].mReadCommand.length());
            }

            mExportLearnListIdx++;
        }
        else if(mState == eState::STATE_IMPORT_SETTING)
        {
            mImportCmdIdx++;

            if(mImportCmdIdx == mImportCmdList.size())
            {
                emit signalEventWrittenSettingToValve();
                setState(eState::STATE_READY);
                return;
            }
        }

        setState(mState);

        return;
    }

    Q_INVOKABLE void onCommandImportSetting(QString filePath)
    {
        QFile file;
        file.setFileName(filePath);
        file.open(QFile::ReadOnly);

        setErrMsg("");
        mImportCmdList.clear();
        mImportCmdIdx = 0;

        if(file.isOpen() == false)
        {
            setErrMsg("File read failed.");
            return;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");

        do{
            QStringList line = out.readLine().split(",");

            if(line.count() > 1)
                mImportCmdList.append(line[1].trimmed());

        }while(!out.atEnd());

        file.close();
        setState(eState::STATE_IMPORT_SETTING);
    }

    Q_INVOKABLE void onCommandSaveFile(QString filePath)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        FileWriterEx file;

        if(filePath == "")
        {
            filePath = QString("%1/setting_backup_%2.txt").arg(QApplication::applicationDirPath()).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd-hh-mm-ss"));
        }

        qDebug() << "[" << Q_FUNC_INFO << "]" << filePath;

        int splitIdx = filePath.lastIndexOf("/")+1;
        QString dir = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        if(file.open(dir, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]File save failed.";
            return;
        }

        foreach(ValveCommandItem item, mExportCmdList)
        {
            if(item.mValue != "skip")
                file.appendLine(QString("%1, %2%3").arg(item.mVarName).arg(item.mWriteCommand).arg(item.mValue));
        }
        file.close();

        emit signalEventWrittenSettingToFile();
    }

    Q_INVOKABLE void onCommandExportSetting(bool isForUpdate)
    {
        int nfirmwareVer;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]isForUpdate = " << isForUpdate;

        pConfigSP->loadValveParams();

        ValveCommandItem tempItem;

        mExportCmdIdx = 0;
        mExportLearnListIdx = 0;
        mExportCmdList.clear();
        setErrMsg("");

        /* valve setup */
        tempItem.setCommand("Valve Speed", QString("-")                           , QString("%1").arg(REQ_WRITE_VALVE_SPEED)); tempItem.mValue = QString("%1").arg(pValveSP->getValveSpeed(), 4, 10, QChar('0')); mExportCmdList.append(tempItem);
        tempItem.setCommand("Valve Setup", QString("%1").arg(REQ_READ_VALVE_SETUP), QString("%1").arg(REQ_WRITE_VALVE_SETUP)); mExportCmdList.append(tempItem);

        /* set point */
        tempItem.setCommand("Set Point 1", QString("%1").arg(REQ_READ_SETPOINT_01), QString("%1").arg(REQ_WRITE_SETPOINT_01)); mExportCmdList.append(tempItem);
        tempItem.setCommand("Set Point 2", QString("%1").arg(REQ_READ_SETPOINT_02), QString("%1").arg(REQ_WRITE_SETPOINT_02)); mExportCmdList.append(tempItem);
        tempItem.setCommand("Set Point 3", QString("%1").arg(REQ_READ_SETPOINT_03), QString("%1").arg(REQ_WRITE_SETPOINT_03)); mExportCmdList.append(tempItem);
        tempItem.setCommand("Set Point 4", QString("%1").arg(REQ_READ_SETPOINT_04), QString("%1").arg(REQ_WRITE_SETPOINT_04)); mExportCmdList.append(tempItem);
        tempItem.setCommand("Set Point 5", QString("%1").arg(REQ_READ_SETPOINT_05), QString("%1").arg(REQ_WRITE_SETPOINT_05)); mExportCmdList.append(tempItem);
        tempItem.setCommand("Set Point 6", QString("%1").arg(REQ_READ_SETPOINT_06), QString("%1").arg(REQ_WRITE_SETPOINT_06)); mExportCmdList.append(tempItem);

        if(isForUpdate == false)
        {
            int nfirmwareVer = pValveSP->getFirmwareVersion().right(4).toInt(nullptr, 16);
            if(nfirmwareVer >= 0x600)
            {
                int paramCount = pConfigSP->getValveParamDescCount();

                pConfigSP->loadValveParams();

                for(int i = 0; i < paramCount; i ++)
                {
                    if(i < 14 || i == 51)
                        continue;

                    QString paramDesc = pConfigSP->getValveParamDesc(i);
                    if((paramDesc.length() > 0) && (paramDesc.contains("(read)", Qt::CaseInsensitive)))
                    {
                        continue;
                    }

                    QString readCmd  = QString("p:0BB0000100%1").arg(i, 2, 16, QChar('0'));
                    QString writeCmd = QString("p:01B0000100%1").arg(i, 2, 16, QChar('0'));

                    tempItem.setCommand(QString("Param Value(%1)").arg(i), readCmd, writeCmd, "p:000BB000010000"); mExportCmdList.append(tempItem);
                }
            }
            else
            {
            /* valve params */
                tempItem.setCommand("Param Start", QString("-"), QString("%1").arg(REQ_WRITE_VALVE_PARAM_START));
                tempItem.mValue = ""; mExportCmdList.append(tempItem);
                for(int i = 0; i < 100; i ++)
                {
                    if(i < 14 || i == 51)
                        continue;

                    QString paramDesc = pConfigSP->getValveParamDesc(i);
                    if((paramDesc.length() > 0) && (paramDesc.contains("(read)", Qt::CaseInsensitive)))
                    {
                        continue;
                    }

                    tempItem.setCommand(QString("Param Value(%1)").arg(i), QString("%1%2").arg(REQ_READ_VALVE_PARAM).arg(i, 2, 10, QChar('0')), QString("%1%2").arg(REQ_WRITE_VALVE_PARAM).arg(i, 2, 10, QChar('0'))); mExportCmdList.append(tempItem);
                }
                tempItem.setCommand("Param End", QString("-"), QString("%1").arg(REQ_WRITE_VALVE_PARAM_END));
                tempItem.mValue = ""; mExportCmdList.append(tempItem);
            }
        }


        if(pValveSP->getLearnNotPresent() == false)
        {
            /* Pressure control learn param */
            for(int i = 0; i < 104; i ++)
            {
                tempItem.setCommand(QString("Learn Param(%1)").arg(i), QString("%1%2").arg(REQ_READ_LEARN_PARAM).arg(i, 3, 10, QChar('0')), QString("%1%2").arg(REQ_WRITE_LEARN_PARAM).arg(i, 3, 10, QChar('0'))); mExportCmdList.append(tempItem);
            }
        }

        /* NVM Settings */
        tempItem.setCommand("Display Config", QString("%1").arg(REQ_READ_DP_CONFIG), QString("%1").arg(REQ_WRITE_DISPLAY_CONFIG)); mExportCmdList.append(tempItem);

        switch (pValveSP->getInterface()) {
        case ValveEnumDef::INTERFACE_RS232_WITH_ANALOGOUTPUT:
        case ValveEnumDef::INTERFACE_RS232:/* Interface RS232*/
            tempItem.setCommand("Interface(RS232) Communication Setup", QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF  ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF  )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(RS232) Range Setup"        , QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM)); mExportCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_DEVICENET:
            /* Interface d-net*/
            tempItem.setCommand("Interface(Device Net) MAC"                   , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_MAC          ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_MAC_ADDR     )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Device Net) Baudrate"              , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_BAUDRATE     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_BAUDRATE     )); mExportCmdList.append(tempItem);

            if(pLSettingSP->mCompany != ValveEnumDef::COMPANY_APSYS)
            {
                tempItem.setCommand("Interface (Device Net) DI", QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_DI           ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DI           )); mExportCmdList.append(tempItem);
                tempItem.setCommand("Interface (Device Net) DO", QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_DO           ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DO           )); mExportCmdList.append(tempItem);
            }

            tempItem.setCommand("Interface(Device Net) Position Unit"         , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_POS_UNIT     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_UNIT     )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Device Net) Position Gain"         , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_POS_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_GAIN     )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Device Net) Pressure Unit"         , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_PRESSURE_UNIT), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_PRESSURE_UNIT)); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Device Net) Pressure Sensor 1 Gain", QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_S01_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S01_GAIN     )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Device Net) Pressure Sensor 2 Gain", QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_S02_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S02_GAIN     )); mExportCmdList.append(tempItem);

            nfirmwareVer = pValveSP->getFirmwareVersion().right(4).toInt(nullptr, 16);
            if(nfirmwareVer >= 0x604)
            {
                tempItem.setCommand("Interface(Device Net) Out Position Unit"         , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_POS_UNIT     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_POS_UNIT     )); mExportCmdList.append(tempItem);
                tempItem.setCommand("Interface(Device Net) Out Position Gain"         , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_POS_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_POS_GAIN     )); mExportCmdList.append(tempItem);
                tempItem.setCommand("Interface(Device Net) Out Pressure Unit"         , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_PRESSURE_UNIT), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_PRESSURE_UNIT)); mExportCmdList.append(tempItem);
                tempItem.setCommand("Interface(Device Net) Out Pressure Sensor 1 Gain", QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_S01_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_S01_GAIN     )); mExportCmdList.append(tempItem);
                tempItem.setCommand("Interface(Device Net) Out Pressure Sensor 2 Gain", QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_S02_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_S02_GAIN     )); mExportCmdList.append(tempItem);
            }

            tempItem.setCommand("Interface(Device Net) input assembly"        , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_IN_ASS       ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_IN_ASS       )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Device Net) output assembly"       , QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_ASS      ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_ASS      )); mExportCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_ETHERNET:
        case ValveEnumDef::INTERFACE_ETHERNET_WITH_ANALOGOUTPUT:
            tempItem.setCommand("Interface(Ethernet) ip"           , QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_IP           ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_IP              ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) Subnet Mask"  , QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_SUBNET       ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_SUBNET          ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) Gateway"      , QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_GATEWAY      ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_GATEWAY         ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) DHCP"         , QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_DHCP         ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_DHCP            ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) Port 1"       , QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_PORT01       ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_PORT01          ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) Port 2"       , QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_PORT02       ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_PORT02          ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) Communication", QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF       ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF          )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) Termination"  , QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS485_COMM     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS485_IF          )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(Ethernet) Range"        , QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM        )); mExportCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_RS485:
        case ValveEnumDef::INTERFACE_RS485_HV:
        case ValveEnumDef::INTERFACE_RS485_WITH_ANALOGOUTPUT:
        case ValveEnumDef::INTERFACE_RS485_HV_WITH_ANALOGOUTPUT:
            /* Interface RS485*/
            tempItem.setCommand("Interface(RS485) Communication Setup-1", QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF  ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF  )); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(RS485) Range Setup"          , QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM)); mExportCmdList.append(tempItem);
            tempItem.setCommand("Interface(RS485) Communication Setup-2", QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS485_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS485_IF  )); mExportCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_PROFIBUS:
        case ValveEnumDef::INTERFACE_ETHERCAT:/* Interface ether cat*/
            if(pLSettingSP->mCompany != ValveEnumDef::COMPANY_APSYS)
            {
                tempItem.setCommand("Interface(EtherCAT) DI", QString("%1").arg(REQ_READ_INTERFACE_CONFIG_ETHCAT_DI ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DI )); mExportCmdList.append(tempItem);
                tempItem.setCommand("Interface(EtherCAT) DO", QString("%1").arg(REQ_READ_INTERFACE_CONFIG_ETHCAT_DO ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DO )); mExportCmdList.append(tempItem);
            }
            //tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_ETHCAT_DEV_ID), QString("%1").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_DEV_ID)); mExportCmdList.append(tempItem);
            for(int i = 0; i < 12; i ++)
            {
                tempItem.setCommand(QString("Interface(EtherCAT) Type(%1)" ).arg(i), QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).arg(i,2,10,QChar('0')), QString("%1%2").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).arg(i,2,10,QChar('0'))); mExportCmdList.append(tempItem);
                tempItem.setCommand(QString("Interface(EtherCAT) Rnage(%1)").arg(i), QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_RANGE    ).arg(i,2,10,QChar('0')), QString("%1%2").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_RANGE).arg(i,2,10,QChar('0')    )); mExportCmdList.append(tempItem);
            }
            break;

        default:/* Interface logic*/
            tempItem.setCommand("Interface(Logic)", QString("%1").arg(REQ_READ_INTERFACE_CONFIG_LOGIC), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_LOGIC)); mExportCmdList.append(tempItem);
            break;
        }

        setState(eState::STATE_EXPORT_SENSOR_CHECK);
    }

    void onTimeout()
    {
        switch ((int)mState)
        {
        case STATE_EXPORT_SENSOR_CHECK:
            pValveSP->readSensorExSelection(this);
            break;

        case STATE_EXPORT_PRESSURE_CTRL_CHECK :
            pValveSP->readSelectControlMode(this);
            break;

        case STATE_EXPORT_SETTING:
            if(mExportCmdList.at(mExportCmdIdx).mReadCommand == "-")
            {
                mExportCmdIdx++;
                setState(mState);
            }
            else
            {
                pValveSP->customRequest(mExportCmdList.at(mExportCmdIdx).mReadCommand, this);
            }
            break;

        case STATE_EXPORT_LEARNLIST:
            {
                QString cmd = QString("%1%2").arg(REQ_READ_LEARN_LIST).arg(mExportLearnListIdx,4,10,QChar('0'));
                pValveSP->customRequest(cmd, this);
            }
            break;

        case STATE_IMPORT_SETTING:
            pValveSP->customRequest(mImportCmdList.at(mImportCmdIdx), this);
            break;
        }
    }
};
#endif // ADVANCEDTOOLBACKUPNRESTOREDLGMODEL_H
