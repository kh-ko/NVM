#ifndef ADVANCEDTOOLBACKUPNRESTOREDLGMODEL_H
#define ADVANCEDTOOLBACKUPNRESTOREDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class ValveCommandItem
{
public:
    QString mReadCommand;
    QString mWriteCommand;
    QString mValue;

    ValveCommandItem(){}
    ValveCommandItem(const ValveCommandItem& copy):mReadCommand (copy.mReadCommand ),
                                                   mWriteCommand(copy.mWriteCommand),
                                                   mValue       (copy.mValue       ){}

    ~ValveCommandItem(){}

    ValveCommandItem& operator=(const ValveCommandItem& other)
    {

        mReadCommand  = other.mReadCommand ;
        mWriteCommand = other.mWriteCommand;
        mValue        = other.mValue       ;

        return *this;
    }

    void setCommand(QString readCmd, QString writeCmd)
    {
        mReadCommand = readCmd;
        mWriteCommand = writeCmd;
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

private:
    QList<ValveCommandItem> mCmdList;

public:
    explicit AdvancedToolBackupNRestoreDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ValveCommandItem tempItem;

        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_TEST_MODE;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;

        onValveChangedAccess();
        onValveChangedIsRS232Test();


        /*interface settings*/
        switch (pValveSP->getInterface()) {
        case ValveEnumDef::INTERFACE_RS232_WITH_ANALOGOUTPUT:
        case ValveEnumDef::INTERFACE_RS232:
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF  ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF  )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM)); mCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_DEVICENET:
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_MAC          ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_MAC_ADDR     )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_BAUDRATE     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_BAUDRATE     )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_POS_UNIT     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_UNIT     )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_POS_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_GAIN     )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_PRESSURE_UNIT), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_PRESSURE_UNIT)); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_S01_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S01_GAIN     )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_S02_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S02_GAIN     )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_IN_ASS       ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_IN_ASS       )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_ASS      ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_ASS      )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_DI           ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DI           )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_DO           ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DO           )); mCmdList.append(tempItem);
            break;


        case ValveEnumDef::INTERFACE_ETHERNET:
        case ValveEnumDef::INTERFACE_ETHERNET_WITH_ANALOGOUTPUT:
            break;

        case ValveEnumDef::INTERFACE_RS485:
        case ValveEnumDef::INTERFACE_RS485_HV:
        case ValveEnumDef::INTERFACE_RS485_WITH_ANALOGOUTPUT:
        case ValveEnumDef::INTERFACE_RS485_HV_WITH_ANALOGOUTPUT:
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF  ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF  )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM)); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS485_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS485_IF  )); mCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_ETHERCAT:
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_ETHCAT_DI ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DI )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_ETHCAT_DO ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DO )); mCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_ETHCAT_DEV_ID), QString("%1").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_DEV_ID)); mCmdList.append(tempItem);
            for(int i = 0; i < 12; i ++)
            {
                tempItem.setCommand(QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).arg(i,2,10,QChar('0')), QString("%1%2").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).arg(i,2,10,QChar('0'))); mCmdList.append(tempItem);
                tempItem.setCommand(QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_RANGE    ).arg(i,2,10,QChar('0')), QString("%1%2").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_RANGE).arg(i,2,10,QChar('0')    )); mCmdList.append(tempItem);
            }
            break;

        default:
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_LOGIC), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_LOGIC)); mCmdList.append(tempItem);
            break;
        }

        /* NVM Settings */
        tempItem.setCommand(QString("%1").arg(REQ_READ_DP_CONFIG), QString("%1").arg(REQ_WRITE_DISPLAY_CONFIG)); mCmdList.append(tempItem);

        /* Pressure control float setup */
        tempItem.setCommand(QString("%1").arg(REQ_READ_SELECT_CTRL_MODE      ), QString("%1").arg(REQ_WRITE_SEL_CTRL_MODE         )); mCmdList.append(tempItem);  // ( if it is not supported, load "Pressure control setup")
        tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_GAIN_FAC    ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_GAIN_FAC    )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_DELTA_FAC   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_DELTA_FAC   )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_SENSOR_DELAY), QString("%1").arg(REQ_WRITE_ADAP_CTRL_SENSOR_DELAY)); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_RAMP_TIME   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_RAMP_TIME   )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_RAMP_MODE   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_RAMP_MODE   )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_P_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_P_GAIN    )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_I_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_I_GAIN    )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_RAMP_TIME ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_RAMP_TIME )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_RAMP_MODE ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_RAMP_MODE )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_DIR       ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_DIR       )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_P_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_P_GAIN    )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_I_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_I_GAIN    )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_RAMP_TIME ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_RAMP_TIME )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_RAMP_MODE ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_RAMP_MODE )); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_DIR       ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_DIR       )); mCmdList.append(tempItem);

        /* Pressure control setup */
        tempItem.setCommand(QString("%1").arg(REQ_READ_PRESSURE_CTRL_CONFIG), QString("%1").arg(REQ_WRITE_PRESSURE_CTRL_CONFIG)); mCmdList.append(tempItem);

        /* Pressure control learn param */
        for(int i = 0; i < 103; i ++)
        {
            tempItem.setCommand(QString("%1%2").arg(REQ_READ_LEARN_PARAM).arg(i, 3, 10, QChar('0')), QString("%1%2").arg(REQ_WRITE_LEARN_PARAM).arg(i, 3, 10, QChar('0'))); mCmdList.append(tempItem);
        }

        /* Sensor setup ex*/
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_SEL                        ), QString("%1").arg(REQ_WRITE_SENSEX_SEL                        )); mCmdList.append(tempItem);  //( if it is not supported, load "sensor setup")
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ANAL_ACTIVE            ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ANAL_ACTIVE            )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SRC                    ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SRC                    )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_UNIT                   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_UNIT                   )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_FULLSCALE              ), QString("%1").arg(REQ_WRITE_SENSEX_S01_FULLSCALE              )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_DIGI                   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_DIGI                   )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_ENABLE            ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_ENABLE            )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_MIN               ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_MIN               )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_MAX               ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_MAX               )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_VALUE             ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_VALUE             )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SCALE_OFFSET           ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE_OFFSET           )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SCALE                  ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE                  )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SCALE_Z_POINT          ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE_Z_POINT          )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_FILTER_SEC             ), QString("%1").arg(REQ_WRITE_SENSEX_S01_FILTER_SEC             )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_LINEARIZE     ), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_LINEARIZE     )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_VOLT_DECADE   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_DECADE   )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE)); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ANAL_ACTIVE            ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ANAL_ACTIVE            )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SRC                    ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SRC                    )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_UNIT                   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_UNIT                   )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_FULLSCALE              ), QString("%1").arg(REQ_WRITE_SENSEX_S02_FULLSCALE              )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_DIGI                   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_DIGI                   )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_ENABLE            ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_ENABLE            )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_MIN               ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_MIN               )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_MAX               ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_MAX               )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_VALUE             ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_VALUE             )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SCALE_OFFSET           ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE_OFFSET           )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SCALE                  ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE                  )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SCALE_Z_POINT          ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE_Z_POINT          )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_FILTER_SEC             ), QString("%1").arg(REQ_WRITE_SENSEX_S02_FILTER_SEC             )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_LINEARIZE     ), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_LINEARIZE     )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_VOLT_DECADE   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_DECADE   )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE)); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_MOD              ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_MOD              )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_LOW              ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_LOW              )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_HIGH             ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_HIGH             )); mCmdList.append(tempItem);  //
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_DELA             ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_DELA             )); mCmdList.append(tempItem);  //


        /* Sensor setup */
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSOR_CONFIG), QString("%1").arg(REQ_WRITE_SENSOR_CONFIG)); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SENSOR_SCALE ), QString("%1").arg(REQ_WRITE_SENSOR_SCALE )); mCmdList.append(tempItem);

        /* set point */
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_01), QString("%1").arg(REQ_WRITE_SETPOINT_01)); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_02), QString("%1").arg(REQ_WRITE_SETPOINT_02)); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_03), QString("%1").arg(REQ_WRITE_SETPOINT_03)); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_04), QString("%1").arg(REQ_WRITE_SETPOINT_04)); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_05), QString("%1").arg(REQ_WRITE_SETPOINT_05)); mCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_06), QString("%1").arg(REQ_WRITE_SETPOINT_06)); mCmdList.append(tempItem);

         /* valve setup */
         tempItem.setCommand(QString("%1").arg(REQ_WRITE_VALVE_SPEED), QString("%1").arg(REQ_WRITE_VALVE_SPEED)) ; mCmdList.append(tempItem);
         tempItem.setCommand(QString("%1").arg(REQ_READ_VALVE_SETUP ), QString("%1").arg(REQ_WRITE_VALVE_SETUP)); mCmdList.append(tempItem);

//        mTimer.setSingleShot(true);
//        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

//        setState(eState::STATE_NONE);

    }
    ~AdvancedToolBackupNRestoreDlgModel()
    {
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

    void onValveWrittenCustomRequest(ValveResponseDto dto)
    {

    }

    Q_INVOKABLE void onCommandReadFromFile(QString filePath)
    {
    }

    Q_INVOKABLE void onCommandWriteToFile(QString filePath)
    {
    }

};
#endif // ADVANCEDTOOLBACKUPNRESTOREDLGMODEL_H
