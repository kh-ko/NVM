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
    QString mReadCommand;
    QString mReadResCommand = "";
    QString mWriteCommand;
    QString mValue;

    ValveCommandItem(){}
    ValveCommandItem(const ValveCommandItem& copy):mReadCommand   (copy.mReadCommand   ),
                                                   mReadResCommand(copy.mReadResCommand),
                                                   mWriteCommand  (copy.mWriteCommand  ),
                                                   mValue         (copy.mValue         ){}

    ~ValveCommandItem(){}

    ValveCommandItem& operator=(const ValveCommandItem& other)
    {

        mReadCommand    = other.mReadCommand   ;
        mReadResCommand = other.mReadResCommand;
        mWriteCommand   = other.mWriteCommand  ;
        mValue          = other.mValue         ;

        return *this;
    }

    void setCommand(QString readCmd, QString writeCmd, QString readResCmd = "")
    {
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
        STATE_IMPORT_SETTING             = STATE_EXPORT_SETTING             + 1,
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
            if(state <= (int) eState::STATE_EXPORT_SETTING && state >= (int) eState::STATE_EXPORT_SENSOR_CHECK)
                setProgress(qFloor((mExportCmdIdx * 100) / mExportCmdList.size()));
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
            setErrMsg("communication error");
            setState(eState::STATE_READY);
            return;
        }

        if(mState == eState::STATE_EXPORT_SETTING)
        {
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
                emit signalEventCompletedExport();
                setState(eState::STATE_READY);
                return;
            }
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
            QString line = out.readLine();
            mImportCmdList.append(line);
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
                file.appendLine(QString("%1%2").arg(item.mWriteCommand).arg(item.mValue));
        }
        file.close();

        emit signalEventWrittenSettingToFile();
    }

    Q_INVOKABLE void onCommandExportSetting()
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        ValveCommandItem tempItem;

        mExportCmdIdx = 0;
        mExportCmdList.clear();
        setErrMsg("");

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
        for(int i = 0; i < 104; i ++)
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
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_IP           ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_IP              ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_SUBNET       ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_SUBNET          ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_GATEWAY      ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_GATEWAY         ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_DHCP         ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_DHCP            ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_PORT01       ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_PORT01          ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_ETHERNET_PORT02       ), QString("%1").arg(REQ_WRITE_INTERFACE_EHTERNET_PORT02          ), RES_READ_INTERFACE_ETHERNET_INFO); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_IF       ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF          )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS485_COMM     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS485_IF          )); mExportCmdList.append(tempItem);
            tempItem.setCommand(QString("%1").arg(REQ_READ_INTERFACE_CONFIG_RS232_COMM     ), QString("%1").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM        )); mExportCmdList.append(tempItem);
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
        setState(eState::STATE_EXPORT_SENSOR_CHECK);
    }

    void onTimeout()
    {
        switch ((int)mState)
        {
        case STATE_EXPORT_SENSOR_CHECK        : pValveSP->readSensorExSelection(this);                                       break;
        case STATE_EXPORT_PRESSURE_CTRL_CHECK : pValveSP->readSelectControlMode(this);                                       break;
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
        case STATE_IMPORT_SETTING             : pValveSP->customRequest(mImportCmdList.at(mImportCmdIdx), this);             break;
        }
    }
};
#endif // ADVANCEDTOOLBACKUPNRESTOREDLGMODEL_H
