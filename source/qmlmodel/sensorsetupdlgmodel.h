#ifndef SENSORSETUPDLGMODEL_H
#define SENSORSETUPDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/mathutil.h"
#include "source/service/coreservice.h"


class SensorSetupDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode        READ getAccessMode        NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool     mIsRS232Test       READ getIsRS232Test       NOTIFY signalEventChangedIsRS232Test      )
    Q_PROPERTY(bool     mIsSensor02Support READ getIsSensor02Support NOTIFY signalEventChangedIsSensor02Support)
    Q_PROPERTY(bool     mSensor01Selction  READ getSensor01Selction  NOTIFY signalEventChangedSensor01Selction )
    Q_PROPERTY(int      mSensor01Unit      READ getSensor01Unit      NOTIFY signalEventChangedSensor01Unit     )
    Q_PROPERTY(double   mSensor01FullScale READ getSensor01FullScale NOTIFY signalEventChangedSensor01FullScale)
    Q_PROPERTY(int      mSensor01Exponent  READ getSensor01Exponent  NOTIFY signalEventChangedSensor01Exponent )
    Q_PROPERTY(bool     mSensor02Selction  READ getSensor02Selction  NOTIFY signalEventChangedSensor02Selction )
    Q_PROPERTY(int      mSensor02Unit      READ getSensor02Unit      NOTIFY signalEventChangedSensor02Unit     )
    Q_PROPERTY(double   mSensor02FullScale READ getSensor02FullScale NOTIFY signalEventChangedSensor02FullScale)
    Q_PROPERTY(int      mSensor02Exponent  READ getSensor02Exponent  NOTIFY signalEventChangedSensor02Exponent )
    Q_PROPERTY(bool     mIsEnableZero      READ getIsEnableZero      NOTIFY signalEventChangedIsEnableZero     )
    Q_PROPERTY(bool     mErrSensorScale    READ getErrSensorScale    NOTIFY signalEventChangedErrSensorScale   )
    Q_PROPERTY(bool     mErrSensorSelction READ getErrSensorSelction NOTIFY signalEventChangedErrSensorSelction)
    Q_PROPERTY(bool     mIsEdit            READ getIsEdit            NOTIFY signalEventChangedIsEdit           )
    Q_PROPERTY(QString  mStrStatus         READ getStrStatus         NOTIFY signalEventChangedStrStatus        )
    Q_PROPERTY(QString  mErrMsg            READ getErrMsg            NOTIFY signalEventChangedErrMsg           )
    Q_PROPERTY(QString  mErrMsg2           READ getErrMsg2           NOTIFY signalEventChangedErrMsg2          )
    Q_PROPERTY(int      mProgress          READ getProgress          NOTIFY signalEventChangedProgress         )

public:
    int     mAccessMode         = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test        = false;
    bool    mIsSensor02Support  = false;
    bool    mSensor01Selction   = true;
    int     mSensor01Unit       = ValveEnumDef::PRESSURE_UNIT_TORR;
    double  mSensor01FullScale  = 1000;
    int     mSensor01Exponent   = 3;
    bool    mSensor02Selction   = false;
    int     mSensor02Unit       = ValveEnumDef::PRESSURE_UNIT_TORR;
    double  mSensor02FullScale  = 1000;
    int     mSensor02Exponent   = 3;
    bool    mIsEnableZero       = false;
    bool    mErrSensorScale     = false;
    bool    mErrSensorSelction  = false;
    bool    mIsEdit             = false;
    QString mStrStatus          = "Loading";
    QString mErrMsg             = "";
    QString mErrMsg2            = "";
    int     mProgress           = 0 ;

    int     getAccessMode       (){ return mAccessMode       ; }
    bool    getIsRS232Test      (){ return mIsRS232Test      ; }
    bool    getIsSensor02Support(){ return mIsSensor02Support; }
    bool    getSensor01Selction (){ return mSensor01Selction ; }
    int     getSensor01Unit     (){ return mSensor01Unit     ; }
    double  getSensor01FullScale(){ return mSensor01FullScale; }
    int     getSensor01Exponent (){ return mSensor01Exponent ; }
    bool    getSensor02Selction (){ return mSensor02Selction ; }
    int     getSensor02Unit     (){ return mSensor02Unit     ; }
    double  getSensor02FullScale(){ return mSensor02FullScale; }
    int     getSensor02Exponent (){ return mSensor02Exponent ; }
    bool    getIsEnableZero     (){ return mIsEnableZero     ; }
    bool    getErrSensorScale   (){ return mErrSensorScale   ; }
    bool    getErrSensorSelction(){ return mErrSensorSelction; }
    bool    getIsEdit           (){ return mIsEdit           ; }
    QString getStrStatus        (){ return mStrStatus        ; }
    QString getErrMsg           (){ return mErrMsg           ; }
    QString getErrMsg2          (){ return mErrMsg2          ; }
    int     getProgress         (){ return mProgress         ; }

    void    setAccessMode       (int     value){ if(mAccessMode        == value)return; mAccessMode        = value; emit signalEventChangedAccessMode       (value);}
    void    setIsRS232Test      (bool    value){ if(mIsRS232Test       == value)return; mIsRS232Test       = value; emit signalEventChangedIsRS232Test      (value);}
    void    setIsSensor02Support(bool    value){ if(mIsSensor02Support == value)return; mIsSensor02Support = value; emit signalEventChangedIsSensor02Support(value);}
    void    setSensor01Selction (bool    value){ if(mSensor01Selction  == value)return; mSensor01Selction  = value; emit signalEventChangedSensor01Selction (value);}
    void    setSensor01Unit     (int     value){ if(mSensor01Unit      == value)return; mSensor01Unit      = value; emit signalEventChangedSensor01Unit     (value);}
    void    setSensor01FullScale(double  value){ if(mSensor01FullScale == value)return; mSensor01FullScale = value; emit signalEventChangedSensor01FullScale(value);}
    void    setSensor01Exponent (int     value){ if(mSensor01Exponent  == value)return; mSensor01Exponent  = value; emit signalEventChangedSensor01Exponent (value);}
    void    setSensor02Selction (bool    value){ if(mSensor02Selction  == value)return; mSensor02Selction  = value; emit signalEventChangedSensor02Selction (value);}
    void    setSensor02Unit     (int     value){ if(mSensor02Unit      == value)return; mSensor02Unit      = value; emit signalEventChangedSensor02Unit     (value);}
    void    setSensor02FullScale(double  value){ if(mSensor02FullScale == value)return; mSensor02FullScale = value; emit signalEventChangedSensor02FullScale(value);}
    void    setSensor02Exponent (int     value){ if(mSensor02Exponent  == value)return; mSensor02Exponent  = value; emit signalEventChangedSensor02Exponent (value);}
    void    setIsEnableZero     (bool    value){ if(mIsEnableZero      == value)return; mIsEnableZero      = value; emit signalEventChangedIsEnableZero     (value);}
    void    setErrSensorScale   (bool    value){ if(mErrSensorScale    == value)return; mErrSensorScale    = value; emit signalEventChangedErrSensorScale   (value);}
    void    setErrSensorSelction(bool    value){ if(mErrSensorSelction == value)return; mErrSensorSelction = value; emit signalEventChangedErrSensorSelction(value);}
    void    setIsEdit           (bool    value){ if(mIsEdit            == value)return; mIsEdit            = value; emit signalEventChangedIsEdit           (value);}
    void    setStrStatus        (QString value){ if(mStrStatus         == value)return; mStrStatus         = value; emit signalEventChangedStrStatus        (value);}
    void    setErrMsg           (QString value){ if(mErrMsg            == value)return; mErrMsg            = value; emit signalEventChangedErrMsg           (value);}
    void    setErrMsg2          (QString value){ if(mErrMsg2           == value)return; mErrMsg2           = value; emit signalEventChangedErrMsg2          (value);}
    void    setProgress         (int     value){ if(mProgress          == value)return; mProgress          = value; emit signalEventChangedProgress         (value);}

signals:
    void signalEventChangedAccessMode       (int     value);
    void signalEventChangedIsRS232Test      (bool    value);
    void signalEventChangedIsSensor02Support(bool    value);
    void signalEventChangedSensor01Selction (bool    value);
    void signalEventChangedSensor01Unit     (int     value);
    void signalEventChangedSensor01FullScale(double  value);
    void signalEventChangedSensor01Exponent (int     value);
    void signalEventChangedSensor02Selction (bool    value);
    void signalEventChangedSensor02Unit     (int     value);
    void signalEventChangedSensor02FullScale(double  value);
    void signalEventChangedSensor02Exponent (int     value);
    void signalEventChangedIsEnableZero     (bool    value);
    void signalEventChangedErrSensorScale   (bool    value);
    void signalEventChangedErrSensorSelction(bool    value);
    void signalEventChangedIsEdit           (bool    value);
    void signalEventChangedStrStatus        (QString value);
    void signalEventChangedErrMsg           (QString value);
    void signalEventChangedErrMsg2          (QString value);
    void signalEventChangedProgress         (int     value);
    void signalEventCompletedLoad           (             );
    void signalEventCompletedApply          (             );

public:
    explicit SensorSetupDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_VERSION;
        ENABLE_SLOT_VALVE_READED_SENSOR_CONFIG;
        ENABLE_SLOT_VALVE_READED_SENSOR_SCALE;
        ENABLE_SLOT_VALVE_WRITTEN_SENSOR_CONFIG;
        ENABLE_SLOT_VALVE_WRITTEN_SENSOR_SCALE;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedSensorVersion();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CONFIG);
    }
    ~SensorSetupDlgModel()
    {
        pValveSP->reLoad();
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

    void onValveChangedSensorVersion()
    {
        setIsSensor02Support(pValveSP->getSensorVersion() == 2);
    }

    void onValveReadedSensorConfig(ValveResponseSensorConfigDto dto)
    {
        if(mState != eState::STATE_READ_CONFIG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrSensorSelction(dto.mSensorOperation != mWriteSensorOp    );
            //setErrEnableZero    (dto.mZeroEnable      != mWriteIsEnableZero);
        }
        else
        {
            switch (dto.mSensorOperation)
            {
            case ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT:
                setSensor01Selction(true);
                setSensor02Selction(false);
                break;
            case ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT:
                setSensor01Selction(false);
                setSensor02Selction(true);
                break;
            case ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02:
            case ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01:
                setSensor01Selction(true);
                setSensor02Selction(true);
                break;
            }

            setIsEnableZero(dto.mZeroEnable);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedSensorScale(ValveResponseSensorScaleDto dto)
    {
        if(mState != eState::STATE_READ_SCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrSensorScale( (dto.mSensor01Unit != mWriteSensor01Unit) || (dto.mSensor01FullScale != mWriteSensor01FullScale) || (dto.mSensor01Exp != (mWriteSensor01Exp * (mWriteSensor01SignExp == 0 ? -1 : 1)))
                             ||(dto.mSensor02Unit != mWriteSensor02Unit) || (dto.mSensor02FullScale != mWriteSensor02FullScale) || (dto.mSensor02Exp != (mWriteSensor02Exp * (mWriteSensor02SignExp == 0 ? -1 : 1))));

//            qDebug() << "[khko_debug] mSensor01Unit = "           << dto.mSensor01Unit   ;
//            qDebug() << "[khko_debug] mWriteSensor01Unit = "      << mWriteSensor01Unit  ;
//            qDebug() << "[khko_debug] mSensor01FullScale = "      << dto.mSensor01FullScale;
//            qDebug() << "[khko_debug] mWriteSensor01FullScale = " << mWriteSensor01FullScale;
//            qDebug() << "[khko_debug] mSensor01Exp = "            << dto.mSensor01Exp;
//            qDebug() << "[khko_debug] mWriteSensor01Exp = "       << mWriteSensor01Exp << ", sign = " << mWriteSensor01SignExp;
//            qDebug() << "[khko_debug] mSensor02Unit = "           << dto.mSensor02Unit;
//            qDebug() << "[khko_debug] mWriteSensor02Unit = "      << mWriteSensor02Unit;
//            qDebug() << "[khko_debug] mSensor02FullScale = "      << dto.mSensor02FullScale;
//            qDebug() << "[khko_debug] mWriteSensor02FullScale = " << mWriteSensor02FullScale;
//            qDebug() << "[khko_debug] mSensor02Exp = "            << dto.mSensor02Exp;
//            qDebug() << "[khko_debug] mWriteSensor02Exp = "       << mWriteSensor02Exp << ", sign = " << mWriteSensor02SignExp;

            onCommandSetEdit(getErrSensorScale() || getErrSensorSelction());
        }
        else
        {
            setSensor01Unit(dto.mSensor01Unit);
            setSensor02Unit(dto.mSensor02Unit);

            setSensor01FullScale((double)dto.mSensor01FullScale * qPow(10, dto.mSensor01Exp) * 0.0001);
            setSensor02FullScale((double)dto.mSensor02FullScale * qPow(10, dto.mSensor02Exp) * 0.0001);
            setSensor01Exponent(dto.mSensor01Exp);
            setSensor02Exponent(dto.mSensor02Exp);
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(bool sensor01Selction, int sensor01Unit, QString strSensor01FullScale, bool sensor02Selction, int sensor02Unit, QString strSensor02FullScale, bool isEnableZero)
    {
        int sensorOperate;
        int sensorRatio = 100000;

        if((sensor01Selction == false && getIsSensor02Support() == false)
          ||(sensor01Selction == false && sensor02Selction == false))
        {
            setErrMsg("No sensor select");
            setErrSensorSelction(true);
            return;
        }

        int intS01FullScale;
        int s01ExpSign;
        int s01Exp;
        int intS02FullScale;
        int s02ExpSign;
        int s02Exp;

        convertIntegerStr(strSensor01FullScale, intS01FullScale, s01ExpSign, s01Exp);
        convertIntegerStr(strSensor02FullScale, intS02FullScale, s02ExpSign, s02Exp);


        double convertedS01FullScale  = UNITUTIL_CONVERT(sensor01Unit, strSensor01FullScale.toDouble(), pValveSP->getPressureDpUnit());
        double convertedS02FullScale  = UNITUTIL_CONVERT(sensor02Unit, strSensor02FullScale.toDouble(), pValveSP->getPressureDpUnit());

        if(sensor01Selction == true && sensor02Selction == false)
        {
            sensorOperate = ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT;
        }
        else if(sensor01Selction == false && sensor02Selction == true)
        {
            sensorOperate = ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT;
        }
        else if( convertedS01FullScale < convertedS02FullScale)
        {
            sensorOperate = ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02;

            if(intS01FullScale != 0)
                sensorRatio = (convertedS02FullScale / convertedS01FullScale) * 1000;
        }
        else
        {
            sensorOperate = ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01;

            if(intS02FullScale != 0)
                sensorRatio = (convertedS01FullScale / convertedS02FullScale) * 1000;
        }

        mIsWritten              = true;
        mWriteSensorOp          = sensorOperate;
        mWriteHighLowRatio      = sensorRatio;
        mWriteIsSensor02Support = getIsSensor02Support();
        mWriteSensor01Unit      = sensor01Unit;
        mWriteSensor01FullScale = intS01FullScale;
        mWriteSensor01SignExp   = s01ExpSign;
        mWriteSensor01Exp       = s01Exp;
        mWriteSensor02Unit      = sensor02Unit;
        mWriteSensor02FullScale = intS02FullScale;
        mWriteSensor02SignExp   = s02ExpSign;
        mWriteSensor02Exp       = s02Exp;
        mWriteIsEnableZero      = isEnableZero;

        setErrMsg2("");
        setState(eState::STATE_WRITE_CONFIG);
    }

    void onValveWrittenSensorConfig(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_CONFIG || dto.mReqDto.mpRef != this)
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

    void onValveWrittenSensorScale(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_SCALE || dto.mReqDto.mpRef != this)
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
    int getExponent(QString strFullScale)
    {
        int exponent;
        int dotIdx = strFullScale.indexOf(".");

        if(dotIdx == -1)
        {
            exponent = strFullScale.length() - 1;
        }
        else
        {
            exponent = dotIdx - 1;
        }
        exponent = exponent > 4 ? 4 : exponent;

        return exponent;
    }

private:
    enum eState{
        STATE_WRITE_CONFIG =  0,
        STATE_WRITE_SCALE  = STATE_WRITE_CONFIG + 1,
        STATE_READ_CONFIG  = STATE_WRITE_SCALE  + 1,
        STATE_READ_SCALE   = STATE_READ_CONFIG  + 1,
        STATE_READY        = STATE_READ_SCALE   + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CONFIG;

    bool mIsWritten              = false;
    int  mWriteSensorOp          ;
    int  mWriteHighLowRatio      ;
    bool mWriteIsSensor02Support ;
    int  mWriteSensor01Unit      ;
    int  mWriteSensor01FullScale ;
    int  mWriteSensor01SignExp   ;
    int  mWriteSensor01Exp       ;
    int  mWriteSensor02Unit      ;
    int  mWriteSensor02FullScale ;
    int  mWriteSensor02SignExp   ;
    int  mWriteSensor02Exp       ;
    bool mWriteIsEnableZero      ;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        if(!mIsWritten && state == eState::STATE_READY)
        {
            emit signalEventCompletedLoad();
        }

        mState = state;

        if(state < (int) eState::STATE_READY && state >= (int) eState::STATE_READ_CONFIG)
        {
            setStrStatus("loading");
        }
        else if(state < (int) eState::STATE_READ_CONFIG && state >= (int) eState::STATE_WRITE_CONFIG)
        {
            setStrStatus("writting");
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
            setProgress(qFloor((state * 100) / eState::STATE_READY));
            startTimer();
        }
    }

    void convertIntegerStr(QString value, int &intValue, int &expSign, int &exp)
    {
        double oriValue  = value.toDouble() + 0.0000001;
        intValue = QString("%1%2").arg(value.replace(".","").toInt()).arg("00000").left(5).toInt();
        double tempValue = QString("%1").arg(intValue).insert(1, QChar('.')).toDouble() + 0.0000001;

        int oriExp = MATHUTIL_ABS_LOG10FLOOR(oriValue);
        int tempExp = MATHUTIL_ABS_LOG10FLOOR(tempValue);

        expSign = oriExp < tempExp ? 0 : 1;
        exp     = qAbs(oriExp - tempExp);
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_CONFIG:
            pValveSP->readSensorConfig(this);
            break;

        case (int)eState::STATE_READ_SCALE:
            pValveSP->readSensorScale(this);
            break;

        case (int)eState::STATE_WRITE_CONFIG:
            pValveSP->setSensorConfig(mWriteSensorOp, mWriteIsEnableZero, mWriteHighLowRatio, this);
            break;

        case (int)eState::STATE_WRITE_SCALE:
            pValveSP->setSensorScale(mWriteSensor01Unit, mWriteSensor01FullScale, mWriteSensor01SignExp, mWriteSensor01Exp, mWriteSensor02Unit, mWriteSensor02FullScale, mWriteSensor02SignExp, mWriteSensor02Exp, this);
            break;
        }
    }
};
#endif // SENSORSETUPDLGMODEL_H
