#ifndef DEBUGGINGMODEL_H
#define DEBUGGINGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/unitutil.h"
#include "source/service/util/mathutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"
#include "source/service/def/datetimeform.h"

class DebuggingModel : public QObject
{
    Q_OBJECT

public:
    QString mPckSensorSetting = "";

    explicit DebuggingModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_CORE_START;
    }
    ~DebuggingModel()
    {
    }

public slots:
    void onCoreStartedService()
    {
        ENABLE_SLOT_VALVE_CHANGED_ISCONNECTED;
        ENABLE_SLOT_VALVE_CHANGED_LOAD_PROGRESS;
        ENABLE_SLOT_VALVE_CHANGED_CONNECTIONINFO;

        ENABLE_SLOT_VALVE_CHANGED_VALVE_STATUS;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_SETTING;

        ENABLE_SLOT_VALVE_READED_FATAL_ERR_STATUS;
    }

    void onValveChangedIsConnected(bool value)
    {
        qDebug() << "[STATUS][" << Q_FUNC_INFO << "]" << value;
    }
    void onValveChangedLoadProgress(int value)
    {
        qDebug() << "[STATUS][" << Q_FUNC_INFO << "]" << value;
    }
    void onValveChangedConnectionInfo(QString value)
    {
        qDebug() << "[STATUS][" << Q_FUNC_INFO << "]" << value;
    }

    void onValveReadedFatalErrStatus(ValveResponseFatalErrStatusDto dto)
    {
        if(dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[STATUS] Fatal error = " << dto.mResData;
    }
    void onValveChangedValveStatus(QString value)
    {
        static QString strTargetValue = "";
        static QString strCurrentPositionValue = "";
        static QString strCurrentPressureValue = "";
        static QString strAccessMode = "";
        static QString strValveMode = "";
        static QString strPressureCtrlMode = "";
        static QString strDevStatus= "";
        static QString strWarning01Mask= "";
        static QString strWarning02Mask= "";
        static QString strWarning03Mask= "";
        static QString strWarning04Mask= "";

        bool isChanged = false;
        int startIdx = 0;
        QString dummy;
        QString contents = value.mid(QString("%1").arg(REQ_READ_STATUS).length()).trimmed();


        strCurrentPositionValue = contents.mid(startIdx,6); startIdx += 6;
        strCurrentPressureValue = contents.mid(startIdx,8); startIdx += 8;

        dummy = contents.mid(startIdx,8); startIdx += 8;
        if(dummy != strTargetValue)
        {
            isChanged = true;
        }
        strTargetValue = dummy;

        dummy = contents.mid(startIdx,4); startIdx += 4;
        dummy = contents.mid(startIdx,1); startIdx += 1;

        dummy = contents.mid(startIdx,1); startIdx += 1;
        if(dummy != strAccessMode)
        {
            isChanged = true;
        }
        strAccessMode = dummy;

        dummy = contents.mid(startIdx,1)              ; startIdx += 1;
        if(dummy != strValveMode)
        {
            isChanged = true;
        }
        strValveMode = dummy;

        dummy = contents.mid(startIdx,1)              ; startIdx += 1;
        if(dummy != strPressureCtrlMode)
        {
            isChanged = true;
        }
        strPressureCtrlMode = dummy;

        dummy = contents.mid(startIdx,1)              ; startIdx += 1;
        if(dummy != strDevStatus)
        {
            isChanged = true;
        }
        strDevStatus = dummy;

        dummy = contents.mid(startIdx,1)              ; startIdx += 1;
        if(dummy != strWarning01Mask)
        {
            isChanged = true;
        }
        strWarning01Mask = dummy;

        dummy = contents.mid(startIdx,1)              ; startIdx += 1;
        if(dummy != strWarning02Mask)
        {
            isChanged = true;
        }
        strWarning02Mask = dummy;

        dummy = contents.mid(startIdx,1)              ; startIdx += 1;
        if(dummy != strWarning03Mask)
        {
            isChanged = true;
        }
        strWarning03Mask = dummy;

        dummy = contents.mid(startIdx,1)              ; startIdx += 1;
        if(dummy != strWarning04Mask)
        {
            isChanged = true;
        }
        strWarning04Mask = dummy;

        if(isChanged)
        {
            qDebug() << "[STATUS][" << Q_FUNC_INFO << "]" << value;

            qDebug() << "[STATUS] Access mode = " << convertAccessModeStr(strAccessMode);
            qDebug() << "[STATUS] Valve mode = " << convertValveModeStr(strValveMode);
            qDebug() << "[STATUS] Pressure control mode = " << convertPressureControlModeStr(strPressureCtrlMode);
            qDebug() << "[STATUS] Target value = " << strTargetValue;
            qDebug() << "[STATUS] Current position value = " << strCurrentPositionValue;
            qDebug() << "[STATUS] Current pressure value = " << strCurrentPressureValue;

            int flags = convertAbcNumberToInt(strDevStatus);
            qDebug() << "[STATUS] Device status : Simulator  :" << ((flags & DEVSTATUS_SIM_MASK      ) != 0 ? "on" : "off");
            qDebug() << "[STATUS] Device status : Enable PFO :" << ((flags & DEVSTATUS_PFO_MASK      ) != 0 ? "true" : "false");
            qDebug() << "[STATUS] Device status : Test mode  :" << ((flags & DEVSTATUS_TEST_MODE_MASK) != 0 ? "on" : "off");

            flags = convertAbcNumberToInt(strWarning01Mask);
            if((flags & FIELDBUS_ERR_ORIGINAL_MASK) != 0){ qDebug() << "[STATUS] Warnings 01: Field bus error";}
            if((flags & FIELDBUS_ERR_SAVING_MASK  ) != 0){ qDebug() << "[STATUS] Warnings 01: Data saving"    ;}
            if((flags & FIELDBUS_ERR_ID_MISS_MASK ) != 0){ qDebug() << "[STATUS] Warnings 01: ID missing"     ;}
            if((flags & FIELDBUS_ERR_PFO_MISS_MASK) != 0){ qDebug() << "[STATUS] Warnings 01: PFO missing"    ;}

            flags = convertAbcNumberToInt(strWarning02Mask);
            if((flags & WARNING2_FIRMWARE_MEMORY_MASK ) != 0){ qDebug() << "[STATUS] Warnings 02: Firmware momory" ;}
            if((flags & WARNING2_UNKNOW_INTERFACE_MASK) != 0){ qDebug() << "[STATUS] Warnings 02: Unknow interface";}
            if((flags & WARNING2_NO_SENSOR_SIG_MASK   ) != 0){ qDebug() << "[STATUS] Warnings 02: No sensor signal";}
            if((flags & WARNING2_NO_ANALOG_SIG_MASK   ) != 0){ qDebug() << "[STATUS] Warnings 02: No analog signal";}

            flags = convertAbcNumberToInt(strWarning03Mask);
            if((flags & WARNING3_NETWORK_FAILURE_MASK) != 0){ qDebug() << "[STATUS] Warnings 03: Network failure" ;}
            if((flags & WARNING3_SLAVE_OFFLINE_MASK  ) != 0){ qDebug() << "[STATUS] Warnings 03: Slave offline";}
            if((flags & WARNING3_ISOLATION_VALVE_MASK) != 0){ qDebug() << "[STATUS] Warnings 03: Isolation valve";}
            if((flags & WARNING3_SENSOR_ERROR_MASK   ) != 0){ qDebug() << "[STATUS] Warnings 03: Sensor error";}

            flags = convertAbcNumberToInt(strWarning04Mask);
            if((flags & WARNING4_SVC_REQ_MASK  ) != 0){ qDebug() << "[STATUS] Warnings 04: Service request" ;}
            if((flags & WARNING4_LEARN_NOT_MASK) != 0){ qDebug() << "[STATUS] Warnings 04: Learn not present";}
            if((flags & WARNING4_AIR_NOT_MASK  ) != 0){ qDebug() << "[STATUS] Warnings 04: Air warning";}
            if((flags & WARNING4_PFO_NOT_MASK  ) != 0){ qDebug() << "[STATUS] Warnings 04: PFO warning";}

            pValveSP->readFatalErrStatus(this);
        }
    }
    void onValveChangedSensorSetting(QString value)
    {
        if(mPckSensorSetting == value)
            return;

        mPckSensorSetting = value;
        qDebug() << "[STATUS][" << Q_FUNC_INFO << "]" << value;

    }

private:
    QString convertAccessModeStr(QString str)
    {
        int tempIntValue = convertAbcNumberToInt(str);

        switch (tempIntValue) {
        case (int)ValveEnumDef::ACCESS_LOCAL        : return "local";
        case (int)ValveEnumDef::ACCESS_REMOTE       : return "remote";
        case (int)ValveEnumDef::ACCESS_LOCKED_REMOTE: return "locked remote";
        }
        return "";
    }
    QString convertValveModeStr(QString str)
    {
        int tempIntValue = convertAbcNumberToInt(str);

        switch (tempIntValue) {
        case (int)ValveEnumDef::MODE_INIT              : return "initialize";
        case (int)ValveEnumDef::MODE_SYNC              : return "synchronize";
        case (int)ValveEnumDef::MODE_POSITION          : return "position";
        case (int)ValveEnumDef::MODE_CLOSED            : return "close";
        case (int)ValveEnumDef::MODE_OPEN              : return "open";
        case (int)ValveEnumDef::MODE_PRESSURE          : return "pressure";
        case (int)ValveEnumDef::MODE_HOLD              : return "hold";
        case (int)ValveEnumDef::MODE_LEARN             : return "learn";
        case (int)ValveEnumDef::MODE_INTERLOCK_OPEN_DI : return "inter lock open";
        case (int)ValveEnumDef::MODE_INTERLOCK_CLOSE_DI: return "inter lock close";
        case (int)ValveEnumDef::MODE_UNKONW_01         : return "Unknow 1";
        case (int)ValveEnumDef::MODE_UNKONW_02         : return "Unknow 2";
        case (int)ValveEnumDef::MODE_POWER_FAILURE     : return "power failure";
        case (int)ValveEnumDef::MODE_SAFETY            : return "safety";
        case (int)ValveEnumDef::MODE_FATAL_ERROR       : return "fatal error";
        }
        return "";
    }

    QString convertPressureControlModeStr(QString str)
    {
        int tempIntValue = convertAbcNumberToInt(str);

        switch (tempIntValue) {
        case (int)ValveEnumDef::PRESSURE_CTRL_ADAPTIVE  : return "Adaptive";
        case (int)ValveEnumDef::PRESSURE_CTRL_FIXED_DOWN: return "Fixed 1";
        case (int)ValveEnumDef::PRESSURE_CTRL_FIXED_UP  : return "Fixed 2";
        case (int)ValveEnumDef::PRESSURE_CTRL_SOFT_DUMP : return "Softdump";
        }
        return "";
    }


    int convertAbcNumberToInt(QString str)
    {
        char value = str.toUtf8().constData()[0];
        if('0' <= value && '9' >= value)
            return value - '0';
        if('A' <= value && 'Z' >= value)
            return (value - 'A') + 10;

        return (value - 'a') + 10;
    }
};

#endif // DEBUGGINGMODEL_H
