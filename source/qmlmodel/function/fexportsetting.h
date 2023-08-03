#ifndef FEXPORTSETTING_H
#define FEXPORTSETTING_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

class ValveSettingCmdItem
{
public:
    QString mReadCommand;
    QString mWriteCommand;
    QString mValue;

    ValveSettingCmdItem(){}
    ValveSettingCmdItem(const ValveSettingCmdItem& copy):mReadCommand (copy.mReadCommand ),
                                                   mWriteCommand(copy.mWriteCommand),
                                                   mValue       (copy.mValue       ){}

    ~ValveSettingCmdItem(){}

    ValveSettingCmdItem& operator=(const ValveSettingCmdItem& other)
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

class FExportSetting : public QObject
{
    Q_OBJECT

public:
    int     mProgress                = 0 ;
    int     getProgress   (){ return mProgress  ; }
    void    setProgress   (int     value){if(mProgress                  == value)return; mProgress                = value; emit signalEventChangedProgress   (value);}

signals:
    void signalEventChangedProgress  (int     value);
    void signalEventCompleted        (bool bErr, QString value);


public:
    explicit FExportSetting(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_READED_SENSEX_SEL;
        ENABLE_SLOT_VALVE_READED_SEL_CONTROL_MODE;
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READY);

    }
    ~FExportSetting()
    {
    }

    void run()
    {
        if(mState != STATE_READY)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        ValveSettingCmdItem tempItem;

        mExportCmdIdx = 0;
        mExportCmdList.clear();

        /* valve setup */
        //tempItem.setCommand(QString("%1").arg(REQ_READ_VALVE_SPEED), QString("%1").arg(REQ_WRITE_VALVE_SPEED)); mValveSetupCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_VALVE_SETUP), QString("%1").arg(REQ_WRITE_VALVE_SETUP)); mExportCmdList.append(tempItem);

        /* set point */
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_01), QString("%1").arg(REQ_WRITE_SETPOINT_01)); mExportCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_02), QString("%1").arg(REQ_WRITE_SETPOINT_02)); mExportCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_03), QString("%1").arg(REQ_WRITE_SETPOINT_03)); mExportCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_04), QString("%1").arg(REQ_WRITE_SETPOINT_04)); mExportCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_05), QString("%1").arg(REQ_WRITE_SETPOINT_05)); mExportCmdList.append(tempItem);
        tempItem.setCommand(QString("%1").arg(REQ_READ_SETPOINT_06), QString("%1").arg(REQ_WRITE_SETPOINT_06)); mExportCmdList.append(tempItem);

        /* valve params*/
        tempItem.setCommand(QString("-"), QString("%1").arg(REQ_WRITE_VALVE_PARAM_START));
        tempItem.mValue = ""; mExportCmdList.append(tempItem);
        for(int i = 18; i < 100; i ++)
        {
            tempItem.setCommand(QString("%1%2").arg(REQ_READ_VALVE_PARAM).arg(i, 2, 10, QChar('0')), QString("%1%2").arg(REQ_WRITE_VALVE_PARAM).arg(i, 2, 10, QChar('0'))); mExportCmdList.append(tempItem);
        }
        tempItem.setCommand(QString("-"), QString("%1").arg(REQ_WRITE_VALVE_PARAM_END));
        tempItem.mValue = ""; mExportCmdList.append(tempItem);

        /* Pressure control learn param */
        for(int i = 0; i < 103; i ++)
        {
            tempItem.setCommand(QString("%1%2").arg(REQ_READ_LEARN_PARAM).arg(i, 3, 10, QChar('0')), QString("%1%2").arg(REQ_WRITE_LEARN_PARAM).arg(i, 3, 10, QChar('0'))); mExportCmdList.append(tempItem);
        }

        /* NVM Settings */
        tempItem.setCommand(QString("%1").arg(REQ_READ_DP_CONFIG), QString("%1").arg(REQ_WRITE_DISPLAY_CONFIG)); mExportCmdList.append(tempItem);

        switch (pValveSP->getInterface()) {
        case ValveEnumDef::INTERFACE_RS232_WITH_ANALOGOUTPUT:
        case ValveEnumDef::INTERFACE_RS232:/* Interface RS232*/
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF  ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF  )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM)); mExportCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_DEVICENET:
            /* Interface d-net*/
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_MAC          ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_MAC_ADDR     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_BAUDRATE     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_BAUDRATE     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_POS_UNIT     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_UNIT     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_POS_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_GAIN     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_PRESSURE_UNIT), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_PRESSURE_UNIT)); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_S01_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S01_GAIN     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_S02_GAIN     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S02_GAIN     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_IN_ASS       ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_IN_ASS       )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_OUT_ASS      ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_ASS      )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_DI           ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DI           )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_DNET_DO           ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DO           )); mExportCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_ETHERNET:
        case ValveEnumDef::INTERFACE_ETHERNET_WITH_ANALOGOUTPUT:
            break;

        case ValveEnumDef::INTERFACE_RS485:
        case ValveEnumDef::INTERFACE_RS485_HV:
        case ValveEnumDef::INTERFACE_RS485_WITH_ANALOGOUTPUT:
        case ValveEnumDef::INTERFACE_RS485_HV_WITH_ANALOGOUTPUT:
            /* Interface RS485*/
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF  ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF  )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM)); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS485_COMM), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS485_IF  )); mExportCmdList.append(tempItem);
            break;

        case ValveEnumDef::INTERFACE_ETHERCAT:/* Interface ether cat*/
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_ETHCAT_DI ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DI )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_ETHCAT_DO ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DO )); mExportCmdList.append(tempItem);
            //tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CFG_ETHCAT_DEV_ID), QString("%1").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_DEV_ID)); mExportCmdList.append(tempItem);
            for(int i = 0; i < 12; i ++)
            {
                tempItem.setCommand(QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).arg(i,2,10,QChar('0')), QString("%1%2").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).arg(i,2,10,QChar('0'))); mExportCmdList.append(tempItem);
                tempItem.setCommand(QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_RANGE    ).arg(i,2,10,QChar('0')), QString("%1%2").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_RANGE).arg(i,2,10,QChar('0')    )); mExportCmdList.append(tempItem);
            }
            break;

        default:/* Interface logic*/
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_LOGIC), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_LOGIC)); mExportCmdList.append(tempItem);
            break;
        }

        setState(STATE_SENSOR_CHECK);
    }

    void stop()
    {
        setState(STATE_READY);
        mTimer.stop();
    }

    bool saveAsFile(QString filePath)
    {
        if(mState != STATE_READY)
            return false;

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
            return false;
        }

        foreach(ValveSettingCmdItem item, mExportCmdList)
        {
            if(item.mValue != "skip")
                file.appendLine(QString("%1%2").arg(item.mWriteCommand).arg(item.mValue));
        }
        file.close();

        return true;
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case STATE_SENSOR_CHECK :
            pValveSP->readSensorExSelection(this);
            break;

        case STATE_PRESSURE_CTRL_CHECK :
            pValveSP->readSelectControlMode(this);
            break;

        case STATE_EXPORT:
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
        }
    }

    void onValveReadedSensorExSelection(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        ValveSettingCmdItem tempItem;

        if(mState != eState::STATE_SENSOR_CHECK || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc && dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSOR_CONFIG), QString("%1").arg(REQ_WRITE_SENSOR_CONFIG)); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSOR_SCALE ), QString("%1").arg(REQ_WRITE_SENSOR_SCALE )); mExportCmdList.append(tempItem);
        }
        else
        {
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_SEL                        ), QString("%1").arg(REQ_WRITE_SENSEX_SEL                        )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ANAL_ACTIVE            ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ANAL_ACTIVE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SRC                    ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SRC                    )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_UNIT                   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_UNIT                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_FULLSCALE              ), QString("%1").arg(REQ_WRITE_SENSEX_S01_FULLSCALE              )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_DIGI                   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_DIGI                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_ENABLE            ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_ENABLE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_MIN               ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_MIN               )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_MAX               ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_MAX               )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_ZERO_VALUE             ), QString("%1").arg(REQ_WRITE_SENSEX_S01_ZERO_VALUE             )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SCALE_OFFSET           ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE_OFFSET           )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SCALE                  ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE                  )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_SCALE_Z_POINT          ), QString("%1").arg(REQ_WRITE_SENSEX_S01_SCALE_Z_POINT          )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_FILTER_SEC             ), QString("%1").arg(REQ_WRITE_SENSEX_S01_FILTER_SEC             )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_LINEARIZE     ), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_LINEARIZE     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_VOLT_DECADE   ), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_DECADE   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE), QString("%1").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE)); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ANAL_ACTIVE            ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ANAL_ACTIVE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SRC                    ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SRC                    )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_UNIT                   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_UNIT                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_FULLSCALE              ), QString("%1").arg(REQ_WRITE_SENSEX_S02_FULLSCALE              )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_DIGI                   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_DIGI                   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_ENABLE            ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_ENABLE            )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_MIN               ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_MIN               )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_MAX               ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_MAX               )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_ZERO_VALUE             ), QString("%1").arg(REQ_WRITE_SENSEX_S02_ZERO_VALUE             )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SCALE_OFFSET           ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE_OFFSET           )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SCALE                  ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE                  )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_SCALE_Z_POINT          ), QString("%1").arg(REQ_WRITE_SENSEX_S02_SCALE_Z_POINT          )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_FILTER_SEC             ), QString("%1").arg(REQ_WRITE_SENSEX_S02_FILTER_SEC             )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_LINEARIZE     ), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_LINEARIZE     )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_VOLT_DECADE   ), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_DECADE   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE), QString("%1").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE)); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_MOD              ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_MOD              )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_LOW              ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_LOW              )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_HIGH             ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_HIGH             )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_SENSEX_CROSSOVER_DELA             ), QString("%1").arg(REQ_WRITE_SENSEX_CROSSOVER_DELA             )); mExportCmdList.append(tempItem);
        }
        setState((eState)(mState + 1));
    }

    void onValveReadedSelControlMode (ValveResponseSelControlModeDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        ValveSettingCmdItem tempItem;

        if(mState != eState::STATE_PRESSURE_CTRL_CHECK || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc && dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            tempItem.setCommand(QString("%1").arg(REQ_READ_PRESSURE_CTRL_CONFIG), QString("%1").arg(REQ_WRITE_PRESSURE_CTRL_CONFIG)); mExportCmdList.append(tempItem);
        }
        else
        {
            tempItem.setCommand(QString("%1").arg(REQ_READ_SELECT_CTRL_MODE      ), QString("%1").arg(REQ_WRITE_SEL_CTRL_MODE         )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_GAIN_FAC    ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_GAIN_FAC    )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_DELTA_FAC   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_DELTA_FAC   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_SENSOR_DELAY), QString("%1").arg(REQ_WRITE_ADAP_CTRL_SENSOR_DELAY)); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_RAMP_TIME   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_RAMP_TIME   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_ADAP_CTRL_RAMP_MODE   ), QString("%1").arg(REQ_WRITE_ADAP_CTRL_RAMP_MODE   )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_P_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_P_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_I_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_I_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_RAMP_TIME ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_RAMP_TIME )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_RAMP_MODE ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_RAMP_MODE )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED1_CTRL_DIR       ), QString("%1").arg(REQ_WRITE_FIXED1_CTRL_DIR       )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_P_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_P_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_I_GAIN    ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_I_GAIN    )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_RAMP_TIME ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_RAMP_TIME )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_RAMP_MODE ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_RAMP_MODE )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_FIXED2_CTRL_DIR       ), QString("%1").arg(REQ_WRITE_FIXED2_CTRL_DIR       )); mExportCmdList.append(tempItem);
        }
        setState((eState)(mState + 1));
    }

    void onValveWrittenCustomRequest(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(dto.mIsSucc == false && dto.mIsNetworkErr)
        {
            emit signalEventCompleted(true, "communication error");
            setState(eState::STATE_READY);
            return;
        }

        if(dto.mIsSucc == true)
        {
            mExportCmdList[mExportCmdIdx].mValue = dto.mResData.mid(mExportCmdList[mExportCmdIdx].mReadCommand.length());
        }
        else
        {
            mExportCmdList[mExportCmdIdx].mValue = "skip";
        }
        mExportCmdIdx++;

        if(mExportCmdIdx == mExportCmdList.size())
        {
            emit signalEventCompleted(false, "");
            setState(eState::STATE_READY);
            return;
        }

        setState(mState);

        return;
    }

private:
    enum eState{
        STATE_READY               = 0,
        STATE_SENSOR_CHECK        = STATE_READY               + 1,
        STATE_PRESSURE_CTRL_CHECK = STATE_SENSOR_CHECK        + 1,
        STATE_EXPORT              = STATE_PRESSURE_CTRL_CHECK + 1,

    };

    int mExportCmdIdx = 0;
    QList<ValveSettingCmdItem> mExportCmdList;

    QTimer mTimer;
    eState mState         = eState::STATE_READY;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        mState = state;

        if(state == eState::STATE_READY)
        {
            setProgress(100);
        }
        else
        {
            setProgress(qFloor((mExportCmdIdx * 100) / mExportCmdList.size()));
            startTimer();
        }
    }
};
#endif // FEXPORTSETTING_H
