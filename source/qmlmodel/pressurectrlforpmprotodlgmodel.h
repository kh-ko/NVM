#ifndef PRESSURECTRLFORPMPROTODLGMODEL_H
#define PRESSURECTRLFORPMPROTODLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QVariantMap>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/unitutil.h"
#include "source/service/util/mathutil.h"

class DoubleCmp{
public:
    static bool Equal(QString v1, QString v2){
        bool ret = false;

        double dv1 = v1.toDouble();
        double dv2 = v2.toDouble();

        double min = qMin(dv1,dv2);
        double diff = qAbs(dv1 - dv2);

        min = qAbs(min);

        ret = (diff < min * 0.000001);

        return ret;
    }
};

class InterfaceScaleConvert{
public:
    int    mPosiScaleMode        = 0;
    double mPosiScaleCloseValue  = 0;
    double mPosiScaleOpenValue   = 100;

    double mSensorMaxUi          = 1;
    int    mPresPrecision        = 0;
    int    mPresScaleMode        = 4;
    double mPresScaleMin         = 0;
    double mPresScaleMax         = 1000;

    InterfaceScaleConvert()
    {
        if(pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT || pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01)
        {
            mSensorMaxUi = UNITUTIL_CONVERT(pValveSP->getS01SullScaleUnit(), pValveSP->getS01FullScale(), pValveSP->getPressureDpUnit());
        }
        else if(pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT || pValveSP->getSensorOperation() == ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02)
        {
            mSensorMaxUi = UNITUTIL_CONVERT(pValveSP->getS02SullScaleUnit(), pValveSP->getS02FullScale(), pValveSP->getPressureDpUnit());
        }
        else
        {
            double sensor01 = UNITUTIL_CONVERT(pValveSP->getS01SullScaleUnit(), pValveSP->getS01FullScale(), pValveSP->getPressureDpUnit());
            double sensor02 = UNITUTIL_CONVERT(pValveSP->getS02SullScaleUnit(), pValveSP->getS02FullScale(), pValveSP->getPressureDpUnit());

            mSensorMaxUi = qMax(sensor01, sensor02);
        }
    }

    QString formatDoubleToString(double value, int prec)
    {
        // 0. 0은 0으로 처리
        if (value == 0.0)
        {
            return QString("0");
        }

        // 1. 유효숫자 자릿수(sig_prec)를 기반으로 'f' 포맷에 사용할
        //    소수점 이하 자릿수(f_prec)를 계산합니다.

        // 값의 크기(지수)를 구합니다. (예: 123.45 -> 2, 0.00123 -> -3)
        int magnitude = qFloor(qLn(value)/ qLn(10));

        // (필요한 유효숫자) - (정수부 자릿수) = (필요한 소수점 이하 자릿수)
        int f_prec = prec - int(magnitude) - 1;

        if (f_prec < 0)
        {
            f_prec = 0;
        }

        //qDebug

        // 3. 'f' 포맷으로 문자열 변환
        QString str = QString::number(value, 'f', f_prec);

        // 4. 기존 로직을 그대로 사용하여 불필요한 0과 . 제거
        if (str.contains('.'))
        {
            while (str.endsWith('0'))
            {
                str.chop(1);
            }

            if (str.endsWith('.'))
            {
                str.chop(1);
            }
        }
        return str;
    }
    QString convertToNVMPosi(QString value)
    {
        double procValue = value.toDouble();
        double width = 0; // mPosiScaleOpenValue - mPosiScaleCloseValue;

        // 0:0-1, 1:0-10, 2:0-90, 3:0-100, 4:0-1000, 5:0-10000, 6:0-100000, 7:User specific
        switch(mPosiScaleMode)
        {
        case 0: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 1     ; break;
        case 1: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 10    ; break;
        case 2: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 90    ; break;
        case 3: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 100   ; break;
        case 4: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 1000  ; break;
        case 5: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 10000 ; break;
        case 6: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 100000; break;
        }

        width = mPosiScaleOpenValue - mPosiScaleCloseValue;

        if(width == 0.0)
            return "";

        procValue = procValue - mPosiScaleCloseValue;
        procValue = pValveSP->getPositionResolution() * (procValue / width);

        return formatDoubleToString(procValue, 6);
    }

    QString convertToNVMPres(QString value)
    {
        QString ret;
        double procValue = value.toDouble();
        double width = 0; //mPresScaleMax - mPresScaleMin;

        // 0:Pa, 1:kPa, 2:bar, 3:mbar, 4:Torr, 5:mTorr, 6:psi, 7:User specific
        switch(mPresScaleMode)
        {
        case 0: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_PA   )        ; break;
        case 1: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_PA   ) * 0.001; break;
        case 2: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_BAR  )        ; break;
        case 3: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_MBAR )        ; break;
        case 4: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_TORR )        ; break;
        case 5: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_MTORR)        ; break;
        case 6: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_PSI  )        ; break;
        }

        width = mPresScaleMax - mPresScaleMin;

        if(width == 0.0)
            return "";

        procValue = procValue - mPresScaleMin;
        procValue = mSensorMaxUi * (procValue / width);

        ret = formatDoubleToString(procValue, 6);

        qDebug() << "[" << Q_FUNC_INFO << "]" << value << ", convert str = " << ret << ", ui max = " << mSensorMaxUi << ", mPresScaleMin = " << mPresScaleMin << ", mPresScaleMax = " << mPresScaleMax;

        return ret;
    }

    QString convertToIFPosi(QString value)
    {
        double procValue = value.toDouble();
        double width = 0; // mPosiScaleOpenValue - mPosiScaleCloseValue;

        // 0:0-1, 1:0-10, 2:0-90, 3:0-100, 4:0-1000, 5:0-10000, 6:0-100000, 7:User specific
        switch(mPosiScaleMode)
        {
        case 0: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 1     ; break;
        case 1: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 10    ; break;
        case 2: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 90    ; break;
        case 3: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 100   ; break;
        case 4: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 1000  ; break;
        case 5: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 10000 ; break;
        case 6: mPosiScaleCloseValue = 0; mPosiScaleOpenValue = 100000; break;
        }

        width = mPosiScaleOpenValue - mPosiScaleCloseValue;

        if(width == 0.0)
            return "0";

        procValue = mPosiScaleCloseValue + (width * (procValue / pValveSP->getPositionResolution()));

        return formatDoubleToString(procValue, 6);
    }

    QString convertToIFPres(QString value)
    {
        QString ret;
        double procValue = value.toDouble();
        double width = 0; //mPresScaleMax - mPresScaleMin;

        // 0:Pa, 1:kPa, 2:bar, 3:mbar, 4:Torr, 5:mTorr, 6:psi, 7:User specific
        switch(mPresScaleMode)
        {
        case 0: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_PA   )        ; break;
        case 1: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_PA   ) * 0.001; break;
        case 2: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_BAR  )        ; break;
        case 3: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_MBAR )        ; break;
        case 4: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_TORR )        ; break;
        case 5: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_MTORR)        ; break;
        case 6: mPresScaleMin = 0; mPresScaleMax = UNITUTIL_CONVERT(pValveSP->getPressureDpUnit(), mSensorMaxUi, (int)UnitUtilEnumDef::PRESSURE_UNIT_PSI  )        ; break;
        }

        width = mPresScaleMax - mPresScaleMin;

        if(width == 0.0)
            return "0";

        procValue = mPresScaleMin + (width * (procValue / mSensorMaxUi));

        ret = formatDoubleToString(procValue, 6);

        qDebug() << "[" << Q_FUNC_INFO << "]" << value << ", convert str = " << ret << ", ui max = " << mSensorMaxUi << ", mPresScaleMin = " << mPresScaleMin << ", mPresScaleMax = " << mPresScaleMax;

        return ret;
    }
};

class PressureCtrlControllerItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mControllerAlgorithmMode             READ getControllerAlgorithmMode             NOTIFY signalEventChangedControllerAlgorithmMode            )
    Q_PROPERTY(QString  mControllerGainFactor                READ getControllerGainFactor                NOTIFY signalEventChangedControllerGainFactor               )
    Q_PROPERTY(QString  mControllerDeltaFactor               READ getControllerDeltaFactor               NOTIFY signalEventChangedControllerDeltaFactor              )
    Q_PROPERTY(QString  mControllerSensorDelay               READ getControllerSensorDelay               NOTIFY signalEventChangedControllerSensorDelay              )
    Q_PROPERTY(int      mControllerLearnDataSelection        READ getControllerLearnDataSelection        NOTIFY signalEventChangedControllerLearnDataSelection       )
    Q_PROPERTY(int      mControllerDirection                 READ getControllerDirection                 NOTIFY signalEventChangedControllerDirection                )
    Q_PROPERTY(QString  mControllerPGainFactor               READ getControllerPGainFactor               NOTIFY signalEventChangedControllerPGainFactor              )
    Q_PROPERTY(QString  mControllerIGainFactor               READ getControllerIGainFactor               NOTIFY signalEventChangedControllerIGainFactor              )
    Q_PROPERTY(int      mControllerPressureScaler            READ getControllerPressureScaler            NOTIFY signalEventChangedControllerPressureScaler           )
    Q_PROPERTY(int      mControllerRampEnable                READ getControllerRampEnable                NOTIFY signalEventChangedControllerRampEnable               )
    Q_PROPERTY(QString  mControllerRampTime                  READ getControllerRampTime                  NOTIFY signalEventChangedControllerRampTime                 )
    Q_PROPERTY(QString  mControllerRampSlope                 READ getControllerRampSlope                 NOTIFY signalEventChangedControllerRampSlope                )
    Q_PROPERTY(int      mControllerRampMode                  READ getControllerRampMode                  NOTIFY signalEventChangedControllerRampMode                 )
    Q_PROPERTY(int      mControllerRampStartValue            READ getControllerRampStartValue            NOTIFY signalEventChangedControllerRampStartValue           )
    Q_PROPERTY(int      mControllerRampType                  READ getControllerRampType                  NOTIFY signalEventChangedControllerRampType                 )

    Q_PROPERTY(bool     mIsEditControllerAlgorithmMode       READ getIsEditControllerAlgorithmMode       NOTIFY signalEventChangedIsEditControllerAlgorithmMode      )
    Q_PROPERTY(bool     mIsEditControllerGainFactor          READ getIsEditControllerGainFactor          NOTIFY signalEventChangedIsEditControllerGainFactor         )
    Q_PROPERTY(bool     mIsEditControllerDeltaFactor         READ getIsEditControllerDeltaFactor         NOTIFY signalEventChangedIsEditControllerDeltaFactor        )
    Q_PROPERTY(bool     mIsEditControllerSensorDelay         READ getIsEditControllerSensorDelay         NOTIFY signalEventChangedIsEditControllerSensorDelay        )
    Q_PROPERTY(bool     mIsEditControllerLearnDataSelection  READ getIsEditControllerLearnDataSelection  NOTIFY signalEventChangedIsEditControllerLearnDataSelection )
    Q_PROPERTY(bool     mIsEditControllerDirection           READ getIsEditControllerDirection           NOTIFY signalEventChangedIsEditControllerDirection          )
    Q_PROPERTY(bool     mIsEditControllerPGainFactor         READ getIsEditControllerPGainFactor         NOTIFY signalEventChangedIsEditControllerPGainFactor        )
    Q_PROPERTY(bool     mIsEditControllerIGainFactor         READ getIsEditControllerIGainFactor         NOTIFY signalEventChangedIsEditControllerIGainFactor        )
    Q_PROPERTY(bool     mIsEditControllerPressureScaler      READ getIsEditControllerPressureScaler      NOTIFY signalEventChangedIsEditControllerPressureScaler     )
    Q_PROPERTY(bool     mIsEditControllerRampEnable          READ getIsEditControllerRampEnable          NOTIFY signalEventChangedIsEditControllerRampEnable         )
    Q_PROPERTY(bool     mIsEditControllerRampTime            READ getIsEditControllerRampTime            NOTIFY signalEventChangedIsEditControllerRampTime           )
    Q_PROPERTY(bool     mIsEditControllerRampSlope           READ getIsEditControllerRampSlope           NOTIFY signalEventChangedIsEditControllerRampSlope          )
    Q_PROPERTY(bool     mIsEditControllerRampMode            READ getIsEditControllerRampMode            NOTIFY signalEventChangedIsEditControllerRampMode           )
    Q_PROPERTY(bool     mIsEditControllerRampStartValue      READ getIsEditControllerRampStartValue      NOTIFY signalEventChangedIsEditControllerRampStartValue     )
    Q_PROPERTY(bool     mIsEditControllerRampType            READ getIsEditControllerRampType            NOTIFY signalEventChangedIsEditControllerRampType           )

    Q_PROPERTY(bool     mErrControllerAlgorithmMode          READ getErrControllerAlgorithmMode          NOTIFY signalEventChangedErrControllerAlgorithmMode         )
    Q_PROPERTY(bool     mErrControllerGainFactor             READ getErrControllerGainFactor             NOTIFY signalEventChangedErrControllerGainFactor            )
    Q_PROPERTY(bool     mErrControllerDeltaFactor            READ getErrControllerDeltaFactor            NOTIFY signalEventChangedErrControllerDeltaFactor           )
    Q_PROPERTY(bool     mErrControllerSensorDelay            READ getErrControllerSensorDelay            NOTIFY signalEventChangedErrControllerSensorDelay           )
    Q_PROPERTY(bool     mErrControllerLearnDataSelection     READ getErrControllerLearnDataSelection     NOTIFY signalEventChangedErrControllerLearnDataSelection    )
    Q_PROPERTY(bool     mErrControllerDirection              READ getErrControllerDirection              NOTIFY signalEventChangedErrControllerDirection             )
    Q_PROPERTY(bool     mErrControllerPGainFactor            READ getErrControllerPGainFactor            NOTIFY signalEventChangedErrControllerPGainFactor           )
    Q_PROPERTY(bool     mErrControllerIGainFactor            READ getErrControllerIGainFactor            NOTIFY signalEventChangedErrControllerIGainFactor           )
    Q_PROPERTY(bool     mErrControllerPressureScaler         READ getErrControllerPressureScaler         NOTIFY signalEventChangedErrControllerPressureScaler        )
    Q_PROPERTY(bool     mErrControllerRampEnable             READ getErrControllerRampEnable             NOTIFY signalEventChangedErrControllerRampEnable            )
    Q_PROPERTY(bool     mErrControllerRampTime               READ getErrControllerRampTime               NOTIFY signalEventChangedErrControllerRampTime              )
    Q_PROPERTY(bool     mErrControllerRampSlope              READ getErrControllerRampSlope              NOTIFY signalEventChangedErrControllerRampSlope             )
    Q_PROPERTY(bool     mErrControllerRampMode               READ getErrControllerRampMode               NOTIFY signalEventChangedErrControllerRampMode              )
    Q_PROPERTY(bool     mErrControllerRampStartValue         READ getErrControllerRampStartValue         NOTIFY signalEventChangedErrControllerRampStartValue        )
    Q_PROPERTY(bool     mErrControllerRampType               READ getErrControllerRampType               NOTIFY signalEventChangedErrControllerRampType              )

public:
    int      mId = 0;

    int      mControllerAlgorithmMode            = 0;
    QString  mControllerGainFactor               = "";
    QString  mControllerDeltaFactor              = "";
    QString  mControllerSensorDelay              = "";
    int      mControllerLearnDataSelection       = 0;
    int      mControllerDirection                = 0;
    QString  mControllerPGainFactor              = "";
    QString  mControllerIGainFactor              = "";
    int      mControllerPressureScaler           = 0;
    int      mControllerRampEnable               = 0;
    QString  mControllerRampTime                 = "";
    QString  mControllerRampSlope                = "";
    int      mControllerRampMode                 = 0;
    int      mControllerRampStartValue           = 0;
    int      mControllerRampType                 = 0;

    bool     mIsEditControllerAlgorithmMode      = false;
    bool     mIsEditControllerGainFactor         = false;
    bool     mIsEditControllerDeltaFactor        = false;
    bool     mIsEditControllerSensorDelay        = false;
    bool     mIsEditControllerLearnDataSelection = false;
    bool     mIsEditControllerDirection          = false;
    bool     mIsEditControllerPGainFactor        = false;
    bool     mIsEditControllerIGainFactor        = false;
    bool     mIsEditControllerPressureScaler     = false;
    bool     mIsEditControllerRampEnable         = false;
    bool     mIsEditControllerRampTime           = false;
    bool     mIsEditControllerRampSlope          = false;
    bool     mIsEditControllerRampMode           = false;
    bool     mIsEditControllerRampStartValue     = false;
    bool     mIsEditControllerRampType           = false;

    bool     mErrControllerAlgorithmMode         = false;
    bool     mErrControllerGainFactor            = false;
    bool     mErrControllerDeltaFactor           = false;
    bool     mErrControllerSensorDelay           = false;
    bool     mErrControllerLearnDataSelection    = false;
    bool     mErrControllerDirection             = false;
    bool     mErrControllerPGainFactor           = false;
    bool     mErrControllerIGainFactor           = false;
    bool     mErrControllerPressureScaler        = false;
    bool     mErrControllerRampEnable            = false;
    bool     mErrControllerRampTime              = false;
    bool     mErrControllerRampSlope             = false;
    bool     mErrControllerRampMode              = false;
    bool     mErrControllerRampStartValue        = false;
    bool     mErrControllerRampType              = false;

    int      getControllerAlgorithmMode           (){ return mControllerAlgorithmMode           ; }
    QString  getControllerGainFactor              (){ return mControllerGainFactor              ; }
    QString  getControllerDeltaFactor             (){ return mControllerDeltaFactor             ; }
    QString  getControllerSensorDelay             (){ return mControllerSensorDelay             ; }
    int      getControllerLearnDataSelection      (){ return mControllerLearnDataSelection      ; }
    int      getControllerDirection               (){ return mControllerDirection               ; }
    QString  getControllerPGainFactor             (){ return mControllerPGainFactor             ; }
    QString  getControllerIGainFactor             (){ return mControllerIGainFactor             ; }
    int      getControllerPressureScaler          (){ return mControllerPressureScaler          ; }
    int      getControllerRampEnable              (){ return mControllerRampEnable              ; }
    QString  getControllerRampTime                (){ return mControllerRampTime                ; }
    QString  getControllerRampSlope               (){ return mControllerRampSlope               ; }
    int      getControllerRampMode                (){ return mControllerRampMode                ; }
    int      getControllerRampStartValue          (){ return mControllerRampStartValue          ; }
    int      getControllerRampType                (){ return mControllerRampType                ; }

    bool     getIsEditControllerAlgorithmMode     (){ return mIsEditControllerAlgorithmMode     ; }
    bool     getIsEditControllerGainFactor        (){ return mIsEditControllerGainFactor        ; }
    bool     getIsEditControllerDeltaFactor       (){ return mIsEditControllerDeltaFactor       ; }
    bool     getIsEditControllerSensorDelay       (){ return mIsEditControllerSensorDelay       ; }
    bool     getIsEditControllerLearnDataSelection(){ return mIsEditControllerLearnDataSelection; }
    bool     getIsEditControllerDirection         (){ return mIsEditControllerDirection         ; }
    bool     getIsEditControllerPGainFactor       (){ return mIsEditControllerPGainFactor       ; }
    bool     getIsEditControllerIGainFactor       (){ return mIsEditControllerIGainFactor       ; }
    bool     getIsEditControllerPressureScaler    (){ return mIsEditControllerPressureScaler    ; }
    bool     getIsEditControllerRampEnable        (){ return mIsEditControllerRampEnable        ; }
    bool     getIsEditControllerRampTime          (){ return mIsEditControllerRampTime          ; }
    bool     getIsEditControllerRampSlope         (){ return mIsEditControllerRampSlope         ; }
    bool     getIsEditControllerRampMode          (){ return mIsEditControllerRampMode          ; }
    bool     getIsEditControllerRampStartValue    (){ return mIsEditControllerRampStartValue    ; }
    bool     getIsEditControllerRampType          (){ return mIsEditControllerRampType          ; }

    bool     getErrControllerAlgorithmMode        (){ return mErrControllerAlgorithmMode        ; }
    bool     getErrControllerGainFactor           (){ return mErrControllerGainFactor           ; }
    bool     getErrControllerDeltaFactor          (){ return mErrControllerDeltaFactor          ; }
    bool     getErrControllerSensorDelay          (){ return mErrControllerSensorDelay          ; }
    bool     getErrControllerLearnDataSelection   (){ return mErrControllerLearnDataSelection   ; }
    bool     getErrControllerDirection            (){ return mErrControllerDirection            ; }
    bool     getErrControllerPGainFactor          (){ return mErrControllerPGainFactor          ; }
    bool     getErrControllerIGainFactor          (){ return mErrControllerIGainFactor          ; }
    bool     getErrControllerPressureScaler       (){ return mErrControllerPressureScaler       ; }
    bool     getErrControllerRampEnable           (){ return mErrControllerRampEnable           ; }
    bool     getErrControllerRampTime             (){ return mErrControllerRampTime             ; }
    bool     getErrControllerRampSlope            (){ return mErrControllerRampSlope            ; }
    bool     getErrControllerRampMode             (){ return mErrControllerRampMode             ; }
    bool     getErrControllerRampStartValue       (){ return mErrControllerRampStartValue       ; }
    bool     getErrControllerRampType             (){ return mErrControllerRampType             ; }

    void     setControllerAlgorithmMode           (int     value){ if(mControllerAlgorithmMode            == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerAlgorithmMode            = value; emit signalEventChangedControllerAlgorithmMode           (value); }
    void     setControllerGainFactor              (QString value){ if(mControllerGainFactor               == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerGainFactor               = value; emit signalEventChangedControllerGainFactor              (value); }
    void     setControllerDeltaFactor             (QString value){ if(mControllerDeltaFactor              == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerDeltaFactor              = value; emit signalEventChangedControllerDeltaFactor             (value); }
    void     setControllerSensorDelay             (QString value){ if(mControllerSensorDelay              == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerSensorDelay              = value; emit signalEventChangedControllerSensorDelay             (value); }
    void     setControllerLearnDataSelection      (int     value){ if(mControllerLearnDataSelection       == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerLearnDataSelection       = value; emit signalEventChangedControllerLearnDataSelection      (value); }
    void     setControllerDirection               (int     value){ if(mControllerDirection                == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerDirection                = value; emit signalEventChangedControllerDirection               (value); }
    void     setControllerPGainFactor             (QString value){ if(mControllerPGainFactor              == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerPGainFactor              = value; emit signalEventChangedControllerPGainFactor             (value); }
    void     setControllerIGainFactor             (QString value){ if(mControllerIGainFactor              == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerIGainFactor              = value; emit signalEventChangedControllerIGainFactor             (value); }
    void     setControllerPressureScaler          (int     value){ if(mControllerPressureScaler           == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerPressureScaler           = value; emit signalEventChangedControllerPressureScaler          (value); }
    void     setControllerRampEnable              (int     value){ if(mControllerRampEnable               == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerRampEnable               = value; emit signalEventChangedControllerRampEnable              (value); }
    void     setControllerRampTime                (QString value){ if(mControllerRampTime                 == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerRampTime                 = value; emit signalEventChangedControllerRampTime                (value); }
    void     setControllerRampSlope               (QString value){ if(mControllerRampSlope                == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerRampSlope                = value; emit signalEventChangedControllerRampSlope               (value); }
    void     setControllerRampMode                (int     value){ if(mControllerRampMode                 == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerRampMode                 = value; emit signalEventChangedControllerRampMode                (value); }
    void     setControllerRampStartValue          (int     value){ if(mControllerRampStartValue           == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerRampStartValue           = value; emit signalEventChangedControllerRampStartValue          (value); }
    void     setControllerRampType                (int     value){ if(mControllerRampType                 == value) return; qDebug() << "[" << Q_FUNC_INFO << "] value = " << value; mControllerRampType                 = value; emit signalEventChangedControllerRampType                (value); }

    void     setIsEditControllerAlgorithmMode     (bool    value){ if(mIsEditControllerAlgorithmMode      == value) return; mIsEditControllerAlgorithmMode      = value; emit signalEventChangedIsEditControllerAlgorithmMode     (value); }
    void     setIsEditControllerGainFactor        (bool    value){ if(mIsEditControllerGainFactor         == value) return; mIsEditControllerGainFactor         = value; emit signalEventChangedIsEditControllerGainFactor        (value); }
    void     setIsEditControllerDeltaFactor       (bool    value){ if(mIsEditControllerDeltaFactor        == value) return; mIsEditControllerDeltaFactor        = value; emit signalEventChangedIsEditControllerDeltaFactor       (value); }
    void     setIsEditControllerSensorDelay       (bool    value){ if(mIsEditControllerSensorDelay        == value) return; mIsEditControllerSensorDelay        = value; emit signalEventChangedIsEditControllerSensorDelay       (value); }
    void     setIsEditControllerLearnDataSelection(bool    value){ if(mIsEditControllerLearnDataSelection == value) return; mIsEditControllerLearnDataSelection = value; emit signalEventChangedIsEditControllerLearnDataSelection(value); }
    void     setIsEditControllerDirection         (bool    value){ if(mIsEditControllerDirection          == value) return; mIsEditControllerDirection          = value; emit signalEventChangedIsEditControllerDirection         (value); }
    void     setIsEditControllerPGainFactor       (bool    value){ if(mIsEditControllerPGainFactor        == value) return; mIsEditControllerPGainFactor        = value; emit signalEventChangedIsEditControllerPGainFactor       (value); }
    void     setIsEditControllerIGainFactor       (bool    value){ if(mIsEditControllerIGainFactor        == value) return; mIsEditControllerIGainFactor        = value; emit signalEventChangedIsEditControllerIGainFactor       (value); }
    void     setIsEditControllerPressureScaler    (bool    value){ if(mIsEditControllerPressureScaler     == value) return; mIsEditControllerPressureScaler     = value; emit signalEventChangedIsEditControllerPressureScaler    (value); }
    void     setIsEditControllerRampEnable        (bool    value){ if(mIsEditControllerRampEnable         == value) return; mIsEditControllerRampEnable         = value; emit signalEventChangedIsEditControllerRampEnable        (value); }
    void     setIsEditControllerRampTime          (bool    value){ if(mIsEditControllerRampTime           == value) return; mIsEditControllerRampTime           = value; emit signalEventChangedIsEditControllerRampTime          (value); }
    void     setIsEditControllerRampSlope         (bool    value){ if(mIsEditControllerRampSlope          == value) return; mIsEditControllerRampSlope          = value; emit signalEventChangedIsEditControllerRampSlope         (value); }
    void     setIsEditControllerRampMode          (bool    value){ if(mIsEditControllerRampMode           == value) return; mIsEditControllerRampMode           = value; emit signalEventChangedIsEditControllerRampMode          (value); }
    void     setIsEditControllerRampStartValue    (bool    value){ if(mIsEditControllerRampStartValue     == value) return; mIsEditControllerRampStartValue     = value; emit signalEventChangedIsEditControllerRampStartValue    (value); }
    void     setIsEditControllerRampType          (bool    value){ if(mIsEditControllerRampType           == value) return; mIsEditControllerRampType           = value; emit signalEventChangedIsEditControllerRampType          (value); }

    void     setErrControllerAlgorithmMode        (bool    value){ if(mErrControllerAlgorithmMode         == value) return; mErrControllerAlgorithmMode         = value; emit signalEventChangedErrControllerAlgorithmMode        (value); }
    void     setErrControllerGainFactor           (bool    value){ if(mErrControllerGainFactor            == value) return; mErrControllerGainFactor            = value; emit signalEventChangedErrControllerGainFactor           (value); }
    void     setErrControllerDeltaFactor          (bool    value){ if(mErrControllerDeltaFactor           == value) return; mErrControllerDeltaFactor           = value; emit signalEventChangedErrControllerDeltaFactor          (value); }
    void     setErrControllerSensorDelay          (bool    value){ if(mErrControllerSensorDelay           == value) return; mErrControllerSensorDelay           = value; emit signalEventChangedErrControllerSensorDelay          (value); }
    void     setErrControllerLearnDataSelection   (bool    value){ if(mErrControllerLearnDataSelection    == value) return; mErrControllerLearnDataSelection    = value; emit signalEventChangedErrControllerLearnDataSelection   (value); }
    void     setErrControllerDirection            (bool    value){ if(mErrControllerDirection             == value) return; mErrControllerDirection             = value; emit signalEventChangedErrControllerDirection            (value); }
    void     setErrControllerPGainFactor          (bool    value){ if(mErrControllerPGainFactor           == value) return; mErrControllerPGainFactor           = value; emit signalEventChangedErrControllerPGainFactor          (value); }
    void     setErrControllerIGainFactor          (bool    value){ if(mErrControllerIGainFactor           == value) return; mErrControllerIGainFactor           = value; emit signalEventChangedErrControllerIGainFactor          (value); }
    void     setErrControllerPressureScaler       (bool    value){ if(mErrControllerPressureScaler        == value) return; mErrControllerPressureScaler        = value; emit signalEventChangedErrControllerPressureScaler       (value); }
    void     setErrControllerRampEnable           (bool    value){ if(mErrControllerRampEnable            == value) return; mErrControllerRampEnable            = value; emit signalEventChangedErrControllerRampEnable           (value); }
    void     setErrControllerRampTime             (bool    value){ if(mErrControllerRampTime              == value) return; mErrControllerRampTime              = value; emit signalEventChangedErrControllerRampTime             (value); }
    void     setErrControllerRampSlope            (bool    value){ if(mErrControllerRampSlope             == value) return; mErrControllerRampSlope             = value; emit signalEventChangedErrControllerRampSlope            (value); }
    void     setErrControllerRampMode             (bool    value){ if(mErrControllerRampMode              == value) return; mErrControllerRampMode              = value; emit signalEventChangedErrControllerRampMode             (value); }
    void     setErrControllerRampStartValue       (bool    value){ if(mErrControllerRampStartValue        == value) return; mErrControllerRampStartValue        = value; emit signalEventChangedErrControllerRampStartValue       (value); }
    void     setErrControllerRampType             (bool    value){ if(mErrControllerRampType              == value) return; mErrControllerRampType              = value; emit signalEventChangedErrControllerRampType             (value); }

signals:
    void signalEventChangedControllerAlgorithmMode           (int     value);
    void signalEventChangedControllerGainFactor              (QString value);
    void signalEventChangedControllerDeltaFactor             (QString value);
    void signalEventChangedControllerSensorDelay             (QString value);
    void signalEventChangedControllerLearnDataSelection      (int     value);
    void signalEventChangedControllerDirection               (int     value);
    void signalEventChangedControllerPGainFactor             (QString value);
    void signalEventChangedControllerIGainFactor             (QString value);
    void signalEventChangedControllerPressureScaler          (int     value);
    void signalEventChangedControllerRampEnable              (int     value);
    void signalEventChangedControllerRampTime                (QString value);
    void signalEventChangedControllerRampSlope               (QString value);
    void signalEventChangedControllerRampMode                (int     value);
    void signalEventChangedControllerRampStartValue          (int     value);
    void signalEventChangedControllerRampType                (int     value);
    void signalEventChangedIsEditControllerAlgorithmMode     (bool    value);
    void signalEventChangedIsEditControllerGainFactor        (bool    value);
    void signalEventChangedIsEditControllerDeltaFactor       (bool    value);
    void signalEventChangedIsEditControllerSensorDelay       (bool    value);
    void signalEventChangedIsEditControllerLearnDataSelection(bool    value);
    void signalEventChangedIsEditControllerDirection         (bool    value);
    void signalEventChangedIsEditControllerPGainFactor       (bool    value);
    void signalEventChangedIsEditControllerIGainFactor       (bool    value);
    void signalEventChangedIsEditControllerPressureScaler    (bool    value);
    void signalEventChangedIsEditControllerRampEnable        (bool    value);
    void signalEventChangedIsEditControllerRampTime          (bool    value);
    void signalEventChangedIsEditControllerRampSlope         (bool    value);
    void signalEventChangedIsEditControllerRampMode          (bool    value);
    void signalEventChangedIsEditControllerRampStartValue    (bool    value);
    void signalEventChangedIsEditControllerRampType          (bool    value);
    void signalEventChangedErrControllerAlgorithmMode        (bool    value);
    void signalEventChangedErrControllerGainFactor           (bool    value);
    void signalEventChangedErrControllerDeltaFactor          (bool    value);
    void signalEventChangedErrControllerSensorDelay          (bool    value);
    void signalEventChangedErrControllerLearnDataSelection   (bool    value);
    void signalEventChangedErrControllerDirection            (bool    value);
    void signalEventChangedErrControllerPGainFactor          (bool    value);
    void signalEventChangedErrControllerIGainFactor          (bool    value);
    void signalEventChangedErrControllerPressureScaler       (bool    value);
    void signalEventChangedErrControllerRampEnable           (bool    value);
    void signalEventChangedErrControllerRampTime             (bool    value);
    void signalEventChangedErrControllerRampSlope            (bool    value);
    void signalEventChangedErrControllerRampMode             (bool    value);
    void signalEventChangedErrControllerRampStartValue       (bool    value);
    void signalEventChangedErrControllerRampType             (bool    value);

public:
    explicit PressureCtrlControllerItem(QObject *parent = nullptr): QObject(parent){}
    ~PressureCtrlControllerItem(){}

    Q_INVOKABLE void onCommandSetEditControllerAlgorithmMode     (int     value){ mWriteControllerAlgorithmMode      = value; setIsEditControllerAlgorithmMode     (true); }
    Q_INVOKABLE void onCommandSetEditControllerGainFactor        (QString value){ mWriteControllerGainFactor         = value; setIsEditControllerGainFactor        (true); }
    Q_INVOKABLE void onCommandSetEditControllerDeltaFactor       (QString value){ mWriteControllerDeltaFactor        = value; setIsEditControllerDeltaFactor       (true); }
    Q_INVOKABLE void onCommandSetEditControllerSensorDelay       (QString value){ mWriteControllerSensorDelay        = value; setIsEditControllerSensorDelay       (true); }
    Q_INVOKABLE void onCommandSetEditControllerLearnDataSelection(int     value){ mWriteControllerLearnDataSelection = value; setIsEditControllerLearnDataSelection(true); }
    Q_INVOKABLE void onCommandSetEditControllerDirection         (int     value){ mWriteControllerDirection          = value; setIsEditControllerDirection         (true); }
    Q_INVOKABLE void onCommandSetEditControllerPGainFactor       (QString value){ mWriteControllerPGainFactor        = value; setIsEditControllerPGainFactor       (true); }
    Q_INVOKABLE void onCommandSetEditControllerIGainFactor       (QString value){ mWriteControllerIGainFactor        = value; setIsEditControllerIGainFactor       (true); }
    Q_INVOKABLE void onCommandSetEditControllerPressureScaler    (int     value){ mWriteControllerPressureScaler     = value; setIsEditControllerPressureScaler    (true); }
    Q_INVOKABLE void onCommandSetEditControllerRampEnable        (int     value){ mWriteControllerRampEnable         = value; setIsEditControllerRampEnable        (true); }
    Q_INVOKABLE void onCommandSetEditControllerRampTime          (QString value){ mWriteControllerRampTime           = value; setIsEditControllerRampTime          (true); }
    Q_INVOKABLE void onCommandSetEditControllerRampSlope         (QString value){ mWriteControllerRampSlope          = value; setIsEditControllerRampSlope         (true); }
    Q_INVOKABLE void onCommandSetEditControllerRampMode          (int     value){ mWriteControllerRampMode           = value; setIsEditControllerRampMode          (true); }
    Q_INVOKABLE void onCommandSetEditControllerRampStartValue    (int     value){ mWriteControllerRampStartValue     = value; setIsEditControllerRampStartValue    (true); }
    Q_INVOKABLE void onCommandSetEditControllerRampType          (int     value){ mWriteControllerRampType           = value; setIsEditControllerRampType          (true); }

    bool IsNeedWriteAlgorithmMode     (){ return (getIsEditControllerAlgorithmMode      () || getErrControllerAlgorithmMode      () ); }
    bool IsNeedWriteGainFactor        (){ return (getIsEditControllerGainFactor         () || getErrControllerGainFactor         () ); }
    bool IsNeedWriteDeltaFactor       (){ return (getIsEditControllerDeltaFactor        () || getErrControllerDeltaFactor        () ); }
    bool IsNeedWriteSensorDelay       (){ return (getIsEditControllerSensorDelay        () || getErrControllerSensorDelay        () ); }
    bool IsNeedWriteLearnDataSelection(){ return (getIsEditControllerLearnDataSelection () || getErrControllerLearnDataSelection () ); }
    bool IsNeedWriteDirection         (){ return (getIsEditControllerDirection          () || getErrControllerDirection          () ); }
    bool IsNeedWritePGainFactor       (){ return (getIsEditControllerPGainFactor        () || getErrControllerPGainFactor        () ); }
    bool IsNeedWriteIGainFactor       (){ return (getIsEditControllerIGainFactor        () || getErrControllerIGainFactor        () ); }
    bool IsNeedWritePressureScaler    (){ return (getIsEditControllerPressureScaler     () || getErrControllerPressureScaler     () ); }
    bool IsNeedWriteRampEnable        (){ return (getIsEditControllerRampEnable         () || getErrControllerRampEnable         () ); }
    bool IsNeedWriteRampTime          (){ return (getIsEditControllerRampTime           () || getErrControllerRampTime           () ); }
    bool IsNeedWriteRampSlope         (){ return (getIsEditControllerRampSlope          () || getErrControllerRampSlope          () ); }
    bool IsNeedWriteRampMode          (){ return (getIsEditControllerRampMode           () || getErrControllerRampMode           () ); }
    bool IsNeedWriteRampStartValue    (){ return (getIsEditControllerRampStartValue     () || getErrControllerRampStartValue     () ); }
    bool IsNeedWriteRampType          (){ return (getIsEditControllerRampType           () || getErrControllerRampType           () ); }

    bool getError()
    {
        return (getErrControllerAlgorithmMode     () ||
                getErrControllerGainFactor        () ||
                getErrControllerDeltaFactor       () ||
                getErrControllerSensorDelay       () ||
                getErrControllerLearnDataSelection() ||
                getErrControllerDirection         () ||
                getErrControllerPGainFactor       () ||
                getErrControllerIGainFactor       () ||
                getErrControllerPressureScaler    () ||
                getErrControllerRampEnable        () ||
                getErrControllerRampTime          () ||
                getErrControllerRampSlope         () ||
                getErrControllerRampMode          () ||
                getErrControllerRampStartValue    () ||
                getErrControllerRampType          () );
    }

    void setIsEditReset(){
        setIsEditControllerAlgorithmMode     (false);
        setIsEditControllerGainFactor        (false);
        setIsEditControllerDeltaFactor       (false);
        setIsEditControllerSensorDelay       (false);
        setIsEditControllerLearnDataSelection(false);
        setIsEditControllerDirection         (false);
        setIsEditControllerPGainFactor       (false);
        setIsEditControllerIGainFactor       (false);
        setIsEditControllerPressureScaler    (false);
        setIsEditControllerRampEnable        (false);
        setIsEditControllerRampTime          (false);
        setIsEditControllerRampSlope         (false);
        setIsEditControllerRampMode          (false);
        setIsEditControllerRampStartValue    (false);
        setIsEditControllerRampType          (false);
    }

    void checkErrControllerAlgorithmMode     (QString res){int     value = res.mid(16).toInt(); setErrControllerAlgorithmMode      ( mWriteControllerAlgorithmMode      != value);}
    void checkErrControllerGainFactor        (QString res){QString value = res.mid(16)        ; setErrControllerGainFactor         ( DoubleCmp::Equal(mWriteControllerGainFactor , value) == false);}
    void checkErrControllerDeltaFactor       (QString res){QString value = res.mid(16)        ; setErrControllerDeltaFactor        ( DoubleCmp::Equal(mWriteControllerDeltaFactor, value) == false);}
    void checkErrControllerSensorDelay       (QString res){QString value = res.mid(16)        ; setErrControllerSensorDelay        ( DoubleCmp::Equal(mWriteControllerSensorDelay, value) == false);}
    void checkErrControllerLearnDataSelection(QString res){int     value = res.mid(16).toInt(); setErrControllerLearnDataSelection ( mWriteControllerLearnDataSelection != value);}
    void checkErrControllerDirection         (QString res){int     value = res.mid(16).toInt(); setErrControllerDirection          ( mWriteControllerDirection          != value);}
    void checkErrControllerPGainFactor       (QString res){QString value = res.mid(16)        ; setErrControllerPGainFactor        ( DoubleCmp::Equal(mWriteControllerPGainFactor, value) == false);}
    void checkErrControllerIGainFactor       (QString res){QString value = res.mid(16)        ; setErrControllerIGainFactor        ( DoubleCmp::Equal(mWriteControllerIGainFactor, value) == false);}
    void checkErrControllerPressureScaler    (QString res){int     value = res.mid(16).toInt(); setErrControllerPressureScaler     ( mWriteControllerPressureScaler     != value);}
    void checkErrControllerRampEnable        (QString res){int     value = res.mid(16).toInt(); setErrControllerRampEnable         ( mWriteControllerRampEnable         != value);}
    void checkErrControllerRampTime          (QString res){QString value = res.mid(16)        ; setErrControllerRampTime           ( DoubleCmp::Equal(mWriteControllerRampTime, value) == false);}
    void checkErrControllerRampSlope         (QString res){QString value = res.mid(16)        ; setErrControllerRampSlope          ( DoubleCmp::Equal(mWriteControllerRampSlope, mIfScaleConverter->convertToNVMPres(value)) == false);}
    void checkErrControllerRampMode          (QString res){int     value = res.mid(16).toInt(); setErrControllerRampMode           ( mWriteControllerRampMode           != value);}
    void checkErrControllerRampStartValue    (QString res){int     value = res.mid(16).toInt(); setErrControllerRampStartValue     ( mWriteControllerRampStartValue     != value);}
    void checkErrControllerRampType          (QString res){int     value = res.mid(16).toInt(); setErrControllerRampType           ( mWriteControllerRampType           != value);}

    void setValueControllerAlgorithmMode     (QString res){int     value = res.mid(16).toInt(); setControllerAlgorithmMode      (value);}
    void setValueControllerGainFactor        (QString res){QString value = res.mid(16)        ; setControllerGainFactor         (value);}
    void setValueControllerDeltaFactor       (QString res){QString value = res.mid(16)        ; setControllerDeltaFactor        (value);}
    void setValueControllerSensorDelay       (QString res){QString value = res.mid(16)        ; setControllerSensorDelay        (value);}
    void setValueControllerLearnDataSelection(QString res){int     value = res.mid(16).toInt(); setControllerLearnDataSelection (value);}
    void setValueControllerDirection         (QString res){int     value = res.mid(16).toInt(); setControllerDirection          (value);}
    void setValueControllerPGainFactor       (QString res){QString value = res.mid(16)        ; setControllerPGainFactor        (value);}
    void setValueControllerIGainFactor       (QString res){QString value = res.mid(16)        ; setControllerIGainFactor        (value);}
    void setValueControllerPressureScaler    (QString res){int     value = res.mid(16).toInt(); setControllerPressureScaler     (value);}
    void setValueControllerRampEnable        (QString res){int     value = res.mid(16).toInt(); setControllerRampEnable         (value);}
    void setValueControllerRampTime          (QString res){QString value = res.mid(16)        ; setControllerRampTime           (value);}
    void setValueControllerRampSlope         (QString res){QString value = res.mid(16)        ; value = mIfScaleConverter->convertToNVMPres(value); setControllerRampSlope(value);}
    void setValueControllerRampMode          (QString res){int     value = res.mid(16).toInt(); setControllerRampMode           (value);}
    void setValueControllerRampStartValue    (QString res){int     value = res.mid(16).toInt(); setControllerRampStartValue     (value);}
    void setValueControllerRampType          (QString res){int     value = res.mid(16).toInt(); setControllerRampType           (value);}

public:
    InterfaceScaleConvert  * mIfScaleConverter;

    int      mWriteControllerAlgorithmMode            = 0;
    QString  mWriteControllerGainFactor               = "";
    QString  mWriteControllerDeltaFactor              = "";
    QString  mWriteControllerSensorDelay              = "";
    int      mWriteControllerLearnDataSelection       = 0;
    int      mWriteControllerDirection                = 0;
    QString  mWriteControllerPGainFactor              = "";
    QString  mWriteControllerIGainFactor              = "";
    int      mWriteControllerPressureScaler           = 0;
    int      mWriteControllerRampEnable               = 0;
    QString  mWriteControllerRampTime                 = "";
    QString  mWriteControllerRampSlope                = "";
    int      mWriteControllerRampMode                 = 0;
    int      mWriteControllerRampStartValue           = 0;
    int      mWriteControllerRampType                 = 0;
};

class PressureCtrlForPmProtoDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mAccessMode                          READ getAccessMode                        NOTIFY signalEventChangedAccessMode                        )
    Q_PROPERTY(bool    mIsRS232Test                         READ getIsRS232Test                       NOTIFY signalEventChangedIsRS232Test                       )

    // only read
    Q_PROPERTY(int     mControllerSelectorUsed              READ getControllerSelectorUsed            NOTIFY signalEventChangedControllerSelectorUsed            )
    Q_PROPERTY(QString mConductance                         READ getConductance                       NOTIFY signalEventChangedConductance                       )
    Q_PROPERTY(QString mMfcFlow                             READ getMfcFlow                           NOTIFY signalEventChangedMfcFlow                           )
    Q_PROPERTY(int     mMfcFlowUnit                         READ getMfcFlowUnit                       NOTIFY signalEventChangedMfcFlowUnit                       )
    Q_PROPERTY(QString mChamberVol                          READ getChamberVol                        NOTIFY signalEventChangedChamberVol                        )
    Q_PROPERTY(QString mAdaptiveConductanceGain             READ getAdaptiveConductanceGain           NOTIFY signalEventChangedAdaptiveConductanceGain           )
    Q_PROPERTY(QString mAdaptiveFlowGain                    READ getAdaptiveFlowGain                  NOTIFY signalEventChangedAdaptiveFlowGain                  )
    Q_PROPERTY(QString mAdaptiveTotalGain                   READ getAdaptiveTotalGain                 NOTIFY signalEventChangedAdaptiveTotalGain                 )

    // read write
    Q_PROPERTY(int     mControllerSelector                  READ getControllerSelector                NOTIFY signalEventChangedControllerSelector                )
    Q_PROPERTY(QString mPresCtrlSpeed                       READ getPresCtrlSpeed                     NOTIFY signalEventChangedPresCtrlSpeed                     )
    Q_PROPERTY(int     mCtrlPosiRestrictionEnable           READ getCtrlPosiRestrictionEnable         NOTIFY signalEventChangedCtrlPosiRestrictionEnable         )
    Q_PROPERTY(QString mCtrlPosiRestrictionMax              READ getCtrlPosiRestrictionMax            NOTIFY signalEventChangedCtrlPosiRestrictionMax            )
    Q_PROPERTY(QString mCtrlPosiRestrictionMin              READ getCtrlPosiRestrictionMin            NOTIFY signalEventChangedCtrlPosiRestrictionMin            )
    Q_PROPERTY(int     mAutoControllerSelectEnable          READ getAutoControllerSelectEnable        NOTIFY signalEventChangedAutoControllerSelectEnable        )
    Q_PROPERTY(int     mAutoControllerSelectMode            READ getAutoControllerSelectMode          NOTIFY signalEventChangedAutoControllerSelectMode          )
    Q_PROPERTY(int     mAutoControllerPresRising            READ getAutoControllerPresRising          NOTIFY signalEventChangedAutoControllerPresRising          )
    Q_PROPERTY(int     mAutoControllerPresFalling           READ getAutoControllerPresFalling         NOTIFY signalEventChangedAutoControllerPresFalling         )
    Q_PROPERTY(int     mAutoControllerSelectBitmap          READ getAutoControllerSelectBitmap        NOTIFY signalEventChangedAutoControllerSelectBitmap        )
    Q_PROPERTY(int     mAutoControllerThreCondition         READ getAutoControllerThreCondition       NOTIFY signalEventChangedAutoControllerThreCondition       )
    Q_PROPERTY(QString mAutoController1ThreValue            READ getAutoController1ThreValue          NOTIFY signalEventChangedAutoController1ThreValue          )
    Q_PROPERTY(QString mAutoController2ThreValue            READ getAutoController2ThreValue          NOTIFY signalEventChangedAutoController2ThreValue          )
    Q_PROPERTY(QString mAutoController3ThreValue            READ getAutoController3ThreValue          NOTIFY signalEventChangedAutoController3ThreValue          )
    Q_PROPERTY(QString mAutoController4ThreValue            READ getAutoController4ThreValue          NOTIFY signalEventChangedAutoController4ThreValue          )

    // edit flag
    Q_PROPERTY(bool    mIsEditControllerSelector            READ getIsEditControllerSelector          NOTIFY signalEventChangedIsEditControllerSelector          )
    Q_PROPERTY(bool    mIsEditPresCtrlSpeed                 READ getIsEditPresCtrlSpeed               NOTIFY signalEventChangedIsEditPresCtrlSpeed               )
    Q_PROPERTY(bool    mIsEditCtrlPosiRestrictionEnable     READ getIsEditCtrlPosiRestrictionEnable   NOTIFY signalEventChangedIsEditCtrlPosiRestrictionEnable   )
    Q_PROPERTY(bool    mIsEditCtrlPosiRestrictionMax        READ getIsEditCtrlPosiRestrictionMax      NOTIFY signalEventChangedIsEditCtrlPosiRestrictionMax      )
    Q_PROPERTY(bool    mIsEditCtrlPosiRestrictionMin        READ getIsEditCtrlPosiRestrictionMin      NOTIFY signalEventChangedIsEditCtrlPosiRestrictionMin      )
    Q_PROPERTY(bool    mIsEditAutoControllerSelectEnable    READ getIsEditAutoControllerSelectEnable  NOTIFY signalEventChangedIsEditAutoControllerSelectEnable  )
    Q_PROPERTY(bool    mIsEditAutoControllerSelectMode      READ getIsEditAutoControllerSelectMode    NOTIFY signalEventChangedIsEditAutoControllerSelectMode    )
    Q_PROPERTY(bool    mIsEditAutoControllerPresRising      READ getIsEditAutoControllerPresRising    NOTIFY signalEventChangedIsEditAutoControllerPresRising    )
    Q_PROPERTY(bool    mIsEditAutoControllerPresFalling     READ getIsEditAutoControllerPresFalling   NOTIFY signalEventChangedIsEditAutoControllerPresFalling   )
    Q_PROPERTY(bool    mIsEditAutoControllerSelectBitmap    READ getIsEditAutoControllerSelectBitmap  NOTIFY signalEventChangedIsEditAutoControllerSelectBitmap  )
    Q_PROPERTY(bool    mIsEditAutoControllerThreCondition   READ getIsEditAutoControllerThreCondition NOTIFY signalEventChangedIsEditAutoControllerThreCondition )
    Q_PROPERTY(bool    mIsEditAutoController1ThreValue      READ getIsEditAutoController1ThreValue    NOTIFY signalEventChangedIsEditAutoController1ThreValue    )
    Q_PROPERTY(bool    mIsEditAutoController2ThreValue      READ getIsEditAutoController2ThreValue    NOTIFY signalEventChangedIsEditAutoController2ThreValue    )
    Q_PROPERTY(bool    mIsEditAutoController3ThreValue      READ getIsEditAutoController3ThreValue    NOTIFY signalEventChangedIsEditAutoController3ThreValue    )
    Q_PROPERTY(bool    mIsEditAutoController4ThreValue      READ getIsEditAutoController4ThreValue    NOTIFY signalEventChangedIsEditAutoController4ThreValue    )

    // err flag
    Q_PROPERTY(bool    mErrControllerSelector               READ getErrControllerSelector             NOTIFY signalEventChangedErrControllerSelector             )
    Q_PROPERTY(bool    mErrPresCtrlSpeed                    READ getErrPresCtrlSpeed                  NOTIFY signalEventChangedErrPresCtrlSpeed                  )
    Q_PROPERTY(bool    mErrCtrlPosiRestrictionEnable        READ getErrCtrlPosiRestrictionEnable      NOTIFY signalEventChangedErrCtrlPosiRestrictionEnable      )
    Q_PROPERTY(bool    mErrCtrlPosiRestrictionMax           READ getErrCtrlPosiRestrictionMax         NOTIFY signalEventChangedErrCtrlPosiRestrictionMax         )
    Q_PROPERTY(bool    mErrCtrlPosiRestrictionMin           READ getErrCtrlPosiRestrictionMin         NOTIFY signalEventChangedErrCtrlPosiRestrictionMin         )
    Q_PROPERTY(bool    mErrAutoControllerSelectEnable       READ getErrAutoControllerSelectEnable     NOTIFY signalEventChangedErrAutoControllerSelectEnable     )
    Q_PROPERTY(bool    mErrAutoControllerSelectMode         READ getErrAutoControllerSelectMode       NOTIFY signalEventChangedErrAutoControllerSelectMode       )
    Q_PROPERTY(bool    mErrAutoControllerPresRising         READ getErrAutoControllerPresRising       NOTIFY signalEventChangedErrAutoControllerPresRising       )
    Q_PROPERTY(bool    mErrAutoControllerPresFalling        READ getErrAutoControllerPresFalling      NOTIFY signalEventChangedErrAutoControllerPresFalling      )
    Q_PROPERTY(bool    mErrAutoControllerSelectBitmap       READ getErrAutoControllerSelectBitmap     NOTIFY signalEventChangedErrAutoControllerSelectBitmap     )
    Q_PROPERTY(bool    mErrAutoControllerThreCondition      READ getErrAutoControllerThreCondition    NOTIFY signalEventChangedErrAutoControllerThreCondition    )
    Q_PROPERTY(bool    mErrAutoController1ThreValue         READ getErrAutoController1ThreValue       NOTIFY signalEventChangedErrAutoController1ThreValue       )
    Q_PROPERTY(bool    mErrAutoController2ThreValue         READ getErrAutoController2ThreValue       NOTIFY signalEventChangedErrAutoController2ThreValue       )
    Q_PROPERTY(bool    mErrAutoController3ThreValue         READ getErrAutoController3ThreValue       NOTIFY signalEventChangedErrAutoController3ThreValue       )
    Q_PROPERTY(bool    mErrAutoController4ThreValue         READ getErrAutoController4ThreValue       NOTIFY signalEventChangedErrAutoController4ThreValue       )

    // status flag
    Q_PROPERTY(bool     mIsEdit                             READ getIsEdit                            NOTIFY signalEventChangedIsEdit                            )
    Q_PROPERTY(QString  mStrStatus                          READ getStrStatus                         NOTIFY signalEventChangedStrStatus                         )
    Q_PROPERTY(QString  mErrMsg                             READ getErrMsg                            NOTIFY signalEventChangedErrMsg                            )
    Q_PROPERTY(QString  mErrMsg2                            READ getErrMsg2                           NOTIFY signalEventChangedErrMsg2                           )
    Q_PROPERTY(int      mProgress                           READ getProgress                          NOTIFY signalEventChangedProgress                          )

public:
    QList<PressureCtrlControllerItem *> mControllerItemList; // = new QList<PressureCtrlControllerItem *>();

    int      mAccessMode                        = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test                       = false;

    // only read
    int      mControllerSelectorUsed            = 0;
    QString  mConductance                       = "";
    QString  mMfcFlow                           = "";
    int      mMfcFlowUnit                       = 0;
    QString  mChamberVol                        = "";
    QString  mAdaptiveConductanceGain           = "";
    QString  mAdaptiveFlowGain                  = "";
    QString  mAdaptiveTotalGain                 = "";

    // read write
    int      mControllerSelector                = 0;
    QString  mPresCtrlSpeed                     = "";
    int      mCtrlPosiRestrictionEnable         = 0;
    QString  mCtrlPosiRestrictionMax            = "";
    QString  mCtrlPosiRestrictionMin            = "";
    int      mAutoControllerSelectEnable        = 0;
    int      mAutoControllerSelectMode          = 0;
    int      mAutoControllerPresRising          = 0;
    int      mAutoControllerPresFalling         = 0;
    int      mAutoControllerSelectBitmap        = 0;
    int      mAutoControllerThreCondition       = 0;
    QString  mAutoController1ThreValue          = "";
    QString  mAutoController2ThreValue          = "";
    QString  mAutoController3ThreValue          = "";
    QString  mAutoController4ThreValue          = "";

    // edit flag
    bool     mIsEditControllerSelector          = false;
    bool     mIsEditPresCtrlSpeed               = false;
    bool     mIsEditCtrlPosiRestrictionEnable   = false;
    bool     mIsEditCtrlPosiRestrictionMax      = false;
    bool     mIsEditCtrlPosiRestrictionMin      = false;
    bool     mIsEditAutoControllerSelectEnable  = false;
    bool     mIsEditAutoControllerSelectMode    = false;
    bool     mIsEditAutoControllerPresRising    = false;
    bool     mIsEditAutoControllerPresFalling   = false;
    bool     mIsEditAutoControllerSelectBitmap  = false;
    bool     mIsEditAutoControllerThreCondition = false;
    bool     mIsEditAutoController1ThreValue    = false;
    bool     mIsEditAutoController2ThreValue    = false;
    bool     mIsEditAutoController3ThreValue    = false;
    bool     mIsEditAutoController4ThreValue    = false;

    // err flag
    bool     mErrControllerSelector             = false;
    bool     mErrPresCtrlSpeed                  = false;
    bool     mErrCtrlPosiRestrictionEnable      = false;
    bool     mErrCtrlPosiRestrictionMax         = false;
    bool     mErrCtrlPosiRestrictionMin         = false;
    bool     mErrAutoControllerSelectEnable     = false;
    bool     mErrAutoControllerSelectMode       = false;
    bool     mErrAutoControllerPresRising       = false;
    bool     mErrAutoControllerPresFalling      = false;
    bool     mErrAutoControllerSelectBitmap     = false;
    bool     mErrAutoControllerThreCondition    = false;
    bool     mErrAutoController1ThreValue       = false;
    bool     mErrAutoController2ThreValue       = false;
    bool     mErrAutoController3ThreValue       = false;
    bool     mErrAutoController4ThreValue       = false;

    // status flag
    bool     mIsEdit               = false;
    QString  mStrStatus           = "Loading";
    QString  mErrMsg              = "";
    QString  mErrMsg2             = "";
    int      mProgress            = 0 ;

    int      getAccessMode                       (){ return mAccessMode                        ;}
    bool     getIsRS232Test                      (){ return mIsRS232Test                       ;}

    // only read
    int      getControllerSelectorUsed           (){ return mControllerSelectorUsed            ;}
    QString  getConductance                      (){ return mConductance                       ;}
    QString  getMfcFlow                          (){ return mMfcFlow                           ;}
    int      getMfcFlowUnit                      (){ return mMfcFlowUnit                       ;}
    QString  getChamberVol                       (){ return mChamberVol                        ;}
    QString  getAdaptiveConductanceGain          (){ return mAdaptiveConductanceGain           ;}
    QString  getAdaptiveFlowGain                 (){ return mAdaptiveFlowGain                  ;}
    QString  getAdaptiveTotalGain                (){ return mAdaptiveTotalGain                 ;}

    // read write
    int      getControllerSelector               (){ return mControllerSelector                ;}
    QString  getPresCtrlSpeed                    (){ return mPresCtrlSpeed                     ;}
    int      getCtrlPosiRestrictionEnable        (){ return mCtrlPosiRestrictionEnable         ;}
    QString  getCtrlPosiRestrictionMax           (){ return mCtrlPosiRestrictionMax            ;}
    QString  getCtrlPosiRestrictionMin           (){ return mCtrlPosiRestrictionMin            ;}
    int      getAutoControllerSelectEnable       (){ return mAutoControllerSelectEnable        ;}
    int      getAutoControllerSelectMode         (){ return mAutoControllerSelectMode          ;}
    int      getAutoControllerPresRising         (){ return mAutoControllerPresRising          ;}
    int      getAutoControllerPresFalling        (){ return mAutoControllerPresFalling         ;}
    int      getAutoControllerSelectBitmap       (){ return mAutoControllerSelectBitmap        ;}
    int      getAutoControllerThreCondition      (){ return mAutoControllerThreCondition       ;}
    QString  getAutoController1ThreValue         (){ return mAutoController1ThreValue          ;}
    QString  getAutoController2ThreValue         (){ return mAutoController2ThreValue          ;}
    QString  getAutoController3ThreValue         (){ return mAutoController3ThreValue          ;}
    QString  getAutoController4ThreValue         (){ return mAutoController4ThreValue          ;}

    // edit flag
    bool     getIsEditControllerSelector         (){ return mIsEditControllerSelector          ;}
    bool     getIsEditPresCtrlSpeed              (){ return mIsEditPresCtrlSpeed               ;}
    bool     getIsEditCtrlPosiRestrictionEnable  (){ return mIsEditCtrlPosiRestrictionEnable   ;}
    bool     getIsEditCtrlPosiRestrictionMax     (){ return mIsEditCtrlPosiRestrictionMax      ;}
    bool     getIsEditCtrlPosiRestrictionMin     (){ return mIsEditCtrlPosiRestrictionMin      ;}
    bool     getIsEditAutoControllerSelectEnable (){ return mIsEditAutoControllerSelectEnable  ;}
    bool     getIsEditAutoControllerSelectMode   (){ return mIsEditAutoControllerSelectMode    ;}
    bool     getIsEditAutoControllerPresRising   (){ return mIsEditAutoControllerPresRising    ;}
    bool     getIsEditAutoControllerPresFalling  (){ return mIsEditAutoControllerPresFalling   ;}
    bool     getIsEditAutoControllerSelectBitmap (){ return mIsEditAutoControllerSelectBitmap  ;}
    bool     getIsEditAutoControllerThreCondition(){ return mIsEditAutoControllerThreCondition ;}
    bool     getIsEditAutoController1ThreValue   (){ return mIsEditAutoController1ThreValue    ;}
    bool     getIsEditAutoController2ThreValue   (){ return mIsEditAutoController2ThreValue    ;}
    bool     getIsEditAutoController3ThreValue   (){ return mIsEditAutoController3ThreValue    ;}
    bool     getIsEditAutoController4ThreValue   (){ return mIsEditAutoController4ThreValue    ;}

    // err flag
    bool     getErrControllerSelector            (){ return mErrControllerSelector             ;}
    bool     getErrPresCtrlSpeed                 (){ return mErrPresCtrlSpeed                  ;}
    bool     getErrCtrlPosiRestrictionEnable     (){ return mErrCtrlPosiRestrictionEnable      ;}
    bool     getErrCtrlPosiRestrictionMax        (){ return mErrCtrlPosiRestrictionMax         ;}
    bool     getErrCtrlPosiRestrictionMin        (){ return mErrCtrlPosiRestrictionMin         ;}
    bool     getErrAutoControllerSelectEnable    (){ return mErrAutoControllerSelectEnable     ;}
    bool     getErrAutoControllerSelectMode      (){ return mErrAutoControllerSelectMode       ;}
    bool     getErrAutoControllerPresRising      (){ return mErrAutoControllerPresRising       ;}
    bool     getErrAutoControllerPresFalling     (){ return mErrAutoControllerPresFalling      ;}
    bool     getErrAutoControllerSelectBitmap    (){ return mErrAutoControllerSelectBitmap     ;}
    bool     getErrAutoControllerThreCondition   (){ return mErrAutoControllerThreCondition    ;}
    bool     getErrAutoController1ThreValue      (){ return mErrAutoController1ThreValue       ;}
    bool     getErrAutoController2ThreValue      (){ return mErrAutoController2ThreValue       ;}
    bool     getErrAutoController3ThreValue      (){ return mErrAutoController3ThreValue       ;}
    bool     getErrAutoController4ThreValue      (){ return mErrAutoController4ThreValue       ;}

    // status flag
    bool     getIsEdit             (){ return mIsEdit             ;}
    QString  getStrStatus          (){ return mStrStatus          ;}
    QString  getErrMsg             (){ return mErrMsg             ;}
    QString  getErrMsg2            (){ return mErrMsg2            ;}
    int      getProgress           (){ return mProgress           ;}

    void     setAccessMode                                (int     value){ if(mAccessMode                         == value) return; mAccessMode                        = value; emit signalEventChangedAccessMode                     (value);}
    void     setIsRS232Test                               (bool    value){ if(mIsRS232Test                        == value) return; mIsRS232Test                       = value; emit signalEventChangedIsRS232Test                    (value);}

    void     setControllerSelectorUsed                    (int     value){ if(mControllerSelectorUsed             == value) return; mControllerSelectorUsed            = value; emit signalEventChangedControllerSelectorUsed         (value);}
    void     setConductance                               (QString value){ if(mConductance                        == value) return; mConductance                       = value; emit signalEventChangedConductance                    (value);}
    void     setMfcFlow                                   (QString value){ if(mMfcFlow                            == value) return; mMfcFlow                           = value; emit signalEventChangedMfcFlow                        (value);}
    void     setMfcFlowUnit                               (int     value){ if(mMfcFlowUnit                        == value) return; mMfcFlowUnit                       = value; emit signalEventChangedMfcFlowUnit                    (value);}
    void     setChamberVol                                (QString value){ if(mChamberVol                         == value) return; mChamberVol                        = value; emit signalEventChangedChamberVol                     (value);}
    void     setAdaptiveConductanceGain                   (QString value){ if(mAdaptiveConductanceGain            == value) return; mAdaptiveConductanceGain           = value; emit signalEventChangedAdaptiveConductanceGain        (value);}
    void     setAdaptiveFlowGain                          (QString value){ if(mAdaptiveFlowGain                   == value) return; mAdaptiveFlowGain                  = value; emit signalEventChangedAdaptiveFlowGain               (value);}
    void     setAdaptiveTotalGain                         (QString value){ if(mAdaptiveTotalGain                  == value) return; mAdaptiveTotalGain                 = value; emit signalEventChangedAdaptiveTotalGain              (value);}

    void     setControllerSelector                        (int     value){ if(mControllerSelector                == value) return; mControllerSelector                = value; emit signalEventChangedControllerSelector               (value);}
    void     setPresCtrlSpeed                             (QString value){ if(mPresCtrlSpeed                     == value) return; mPresCtrlSpeed                     = value; emit signalEventChangedPresCtrlSpeed                    (value);}
    void     setCtrlPosiRestrictionEnable                 (int     value){ if(mCtrlPosiRestrictionEnable         == value) return; mCtrlPosiRestrictionEnable         = value; emit signalEventChangedCtrlPosiRestrictionEnable        (value);}
    void     setCtrlPosiRestrictionMax                    (QString value){ if(mCtrlPosiRestrictionMax            == value) return; mCtrlPosiRestrictionMax            = value; emit signalEventChangedCtrlPosiRestrictionMax           (value);}
    void     setCtrlPosiRestrictionMin                    (QString value){ if(mCtrlPosiRestrictionMin            == value) return; mCtrlPosiRestrictionMin            = value; emit signalEventChangedCtrlPosiRestrictionMin           (value);}
    void     setAutoControllerSelectEnable                (int     value){ if(mAutoControllerSelectEnable        == value) return; mAutoControllerSelectEnable        = value; emit signalEventChangedAutoControllerSelectEnable       (value);}
    void     setAutoControllerSelectMode                  (int     value){ if(mAutoControllerSelectMode          == value) return; mAutoControllerSelectMode          = value; emit signalEventChangedAutoControllerSelectMode         (value);}
    void     setAutoControllerPresRising                  (int     value){ if(mAutoControllerPresRising          == value) return; mAutoControllerPresRising          = value; emit signalEventChangedAutoControllerPresRising         (value);}
    void     setAutoControllerPresFalling                 (int     value){ if(mAutoControllerPresFalling         == value) return; mAutoControllerPresFalling         = value; emit signalEventChangedAutoControllerPresFalling        (value);}
    void     setAutoControllerSelectBitmap                (int     value){ if(mAutoControllerSelectBitmap        == value) return; mAutoControllerSelectBitmap        = value; emit signalEventChangedAutoControllerSelectBitmap       (value);}
    void     setAutoControllerThreCondition               (int     value){ if(mAutoControllerThreCondition       == value) return; mAutoControllerThreCondition       = value; emit signalEventChangedAutoControllerThreCondition      (value);}
    void     setAutoController1ThreValue                  (QString value){ if(mAutoController1ThreValue          == value) return; mAutoController1ThreValue          = value; emit signalEventChangedAutoController1ThreValue         (value);}
    void     setAutoController2ThreValue                  (QString value){ if(mAutoController2ThreValue          == value) return; mAutoController2ThreValue          = value; emit signalEventChangedAutoController2ThreValue         (value);}
    void     setAutoController3ThreValue                  (QString value){ if(mAutoController3ThreValue          == value) return; mAutoController3ThreValue          = value; emit signalEventChangedAutoController3ThreValue         (value);}
    void     setAutoController4ThreValue                  (QString value){ if(mAutoController4ThreValue          == value) return; mAutoController4ThreValue          = value; emit signalEventChangedAutoController4ThreValue         (value);}

    void     setIsEditControllerSelector                  (bool    value){ if(mIsEditControllerSelector          == value) return; mIsEditControllerSelector          = value; emit signalEventChangedIsEditControllerSelector         (value);}
    void     setIsEditPresCtrlSpeed                       (bool    value){ if(mIsEditPresCtrlSpeed               == value) return; mIsEditPresCtrlSpeed               = value; emit signalEventChangedIsEditPresCtrlSpeed              (value);}
    void     setIsEditCtrlPosiRestrictionEnable           (bool    value){ if(mIsEditCtrlPosiRestrictionEnable   == value) return; mIsEditCtrlPosiRestrictionEnable   = value; emit signalEventChangedIsEditCtrlPosiRestrictionEnable  (value);}
    void     setIsEditCtrlPosiRestrictionMax              (bool    value){ if(mIsEditCtrlPosiRestrictionMax      == value) return; mIsEditCtrlPosiRestrictionMax      = value; emit signalEventChangedIsEditCtrlPosiRestrictionMax     (value);}
    void     setIsEditCtrlPosiRestrictionMin              (bool    value){ if(mIsEditCtrlPosiRestrictionMin      == value) return; mIsEditCtrlPosiRestrictionMin      = value; emit signalEventChangedIsEditCtrlPosiRestrictionMin     (value);}
    void     setIsEditAutoControllerSelectEnable          (bool    value){ if(mIsEditAutoControllerSelectEnable  == value) return; mIsEditAutoControllerSelectEnable  = value; emit signalEventChangedIsEditAutoControllerSelectEnable (value);}
    void     setIsEditAutoControllerSelectMode            (bool    value){ if(mIsEditAutoControllerSelectMode    == value) return; mIsEditAutoControllerSelectMode    = value; emit signalEventChangedIsEditAutoControllerSelectMode   (value);}
    void     setIsEditAutoControllerPresRising            (bool    value){ if(mIsEditAutoControllerPresRising    == value) return; mIsEditAutoControllerPresRising    = value; emit signalEventChangedIsEditAutoControllerPresRising   (value);}
    void     setIsEditAutoControllerPresFalling           (bool    value){ if(mIsEditAutoControllerPresFalling   == value) return; mIsEditAutoControllerPresFalling   = value; emit signalEventChangedIsEditAutoControllerPresFalling  (value);}
    void     setIsEditAutoControllerSelectBitmap          (bool    value){ if(mIsEditAutoControllerSelectBitmap  == value) return; mIsEditAutoControllerSelectBitmap  = value; emit signalEventChangedIsEditAutoControllerSelectBitmap (value);}
    void     setIsEditAutoControllerThreCondition         (bool    value){ if(mIsEditAutoControllerThreCondition == value) return; mIsEditAutoControllerThreCondition = value; emit signalEventChangedIsEditAutoControllerThreCondition(value);}
    void     setIsEditAutoController1ThreValue            (bool    value){ if(mIsEditAutoController1ThreValue    == value) return; mIsEditAutoController1ThreValue    = value; emit signalEventChangedIsEditAutoController1ThreValue   (value);}
    void     setIsEditAutoController2ThreValue            (bool    value){ if(mIsEditAutoController2ThreValue    == value) return; mIsEditAutoController2ThreValue    = value; emit signalEventChangedIsEditAutoController2ThreValue   (value);}
    void     setIsEditAutoController3ThreValue            (bool    value){ if(mIsEditAutoController3ThreValue    == value) return; mIsEditAutoController3ThreValue    = value; emit signalEventChangedIsEditAutoController3ThreValue   (value);}
    void     setIsEditAutoController4ThreValue            (bool    value){ if(mIsEditAutoController4ThreValue    == value) return; mIsEditAutoController4ThreValue    = value; emit signalEventChangedIsEditAutoController4ThreValue   (value);}

    void     setErrControllerSelector                     (bool    value){ if(mErrControllerSelector             == value) return; mErrControllerSelector             = value; emit signalEventChangedErrControllerSelector            (value);}
    void     setErrPresCtrlSpeed                          (bool    value){ if(mErrPresCtrlSpeed                  == value) return; mErrPresCtrlSpeed                  = value; emit signalEventChangedErrPresCtrlSpeed                 (value);}
    void     setErrCtrlPosiRestrictionEnable              (bool    value){ if(mErrCtrlPosiRestrictionEnable      == value) return; mErrCtrlPosiRestrictionEnable      = value; emit signalEventChangedErrCtrlPosiRestrictionEnable     (value);}
    void     setErrCtrlPosiRestrictionMax                 (bool    value){ if(mErrCtrlPosiRestrictionMax         == value) return; mErrCtrlPosiRestrictionMax         = value; emit signalEventChangedErrCtrlPosiRestrictionMax        (value);}
    void     setErrCtrlPosiRestrictionMin                 (bool    value){ if(mErrCtrlPosiRestrictionMin         == value) return; mErrCtrlPosiRestrictionMin         = value; emit signalEventChangedErrCtrlPosiRestrictionMin        (value);}
    void     setErrAutoControllerSelectEnable             (bool    value){ if(mErrAutoControllerSelectEnable     == value) return; mErrAutoControllerSelectEnable     = value; emit signalEventChangedErrAutoControllerSelectEnable    (value);}
    void     setErrAutoControllerSelectMode               (bool    value){ if(mErrAutoControllerSelectMode       == value) return; mErrAutoControllerSelectMode       = value; emit signalEventChangedErrAutoControllerSelectMode      (value);}
    void     setErrAutoControllerPresRising               (bool    value){ if(mErrAutoControllerPresRising       == value) return; mErrAutoControllerPresRising       = value; emit signalEventChangedErrAutoControllerPresRising      (value);}
    void     setErrAutoControllerPresFalling              (bool    value){ if(mErrAutoControllerPresFalling      == value) return; mErrAutoControllerPresFalling      = value; emit signalEventChangedErrAutoControllerPresFalling     (value);}
    void     setErrAutoControllerSelectBitmap             (bool    value){ if(mErrAutoControllerSelectBitmap     == value) return; mErrAutoControllerSelectBitmap     = value; emit signalEventChangedErrAutoControllerSelectBitmap    (value);}
    void     setErrAutoControllerThreCondition            (bool    value){ if(mErrAutoControllerThreCondition    == value) return; mErrAutoControllerThreCondition    = value; emit signalEventChangedErrAutoControllerThreCondition   (value);}
    void     setErrAutoController1ThreValue               (bool    value){ if(mErrAutoController1ThreValue       == value) return; mErrAutoController1ThreValue       = value; emit signalEventChangedErrAutoController1ThreValue      (value);}
    void     setErrAutoController2ThreValue               (bool    value){ if(mErrAutoController2ThreValue       == value) return; mErrAutoController2ThreValue       = value; emit signalEventChangedErrAutoController2ThreValue      (value);}
    void     setErrAutoController3ThreValue               (bool    value){ if(mErrAutoController3ThreValue       == value) return; mErrAutoController3ThreValue       = value; emit signalEventChangedErrAutoController3ThreValue      (value);}
    void     setErrAutoController4ThreValue               (bool    value){ if(mErrAutoController4ThreValue       == value) return; mErrAutoController4ThreValue       = value; emit signalEventChangedErrAutoController4ThreValue      (value);}

    void     setIsEdit             (bool    value){ if(mIsEdit              == value) return; mIsEdit              = value; emit signalEventChangedIsEdit             (value);}
    void     setStrStatus          (QString value){ if(mStrStatus           == value) return; mStrStatus           = value; emit signalEventChangedStrStatus          (value);}
    void     setErrMsg             (QString value){ if(mErrMsg              == value) return; mErrMsg              = value; emit signalEventChangedErrMsg             (value);}
    void     setErrMsg2            (QString value){ if(mErrMsg2             == value) return; mErrMsg2             = value; emit signalEventChangedErrMsg2            (value);}
    void     setProgress           (int     value){ if(mProgress            == value) return; mProgress            = value; emit signalEventChangedProgress           (value);}

signals:
    void signalEventChangedAccessMode                       (int     value);
    void signalEventChangedIsRS232Test                      (bool    value);

    void signalEventChangedControllerSelectorUsed           (int     value);
    void signalEventChangedConductance                      (QString value);
    void signalEventChangedMfcFlow                          (QString value);
    void signalEventChangedMfcFlowUnit                      (int     value);
    void signalEventChangedChamberVol                       (QString value);
    void signalEventChangedAdaptiveConductanceGain          (QString value);
    void signalEventChangedAdaptiveFlowGain                 (QString value);
    void signalEventChangedAdaptiveTotalGain                (QString value);

    void signalEventChangedControllerSelector               (int     value);
    void signalEventChangedPresCtrlSpeed                    (QString value);
    void signalEventChangedCtrlPosiRestrictionEnable        (int     value);
    void signalEventChangedCtrlPosiRestrictionMax           (QString value);
    void signalEventChangedCtrlPosiRestrictionMin           (QString value);
    void signalEventChangedAutoControllerSelectEnable       (int     value);
    void signalEventChangedAutoControllerSelectMode         (int     value);
    void signalEventChangedAutoControllerPresRising         (int     value);
    void signalEventChangedAutoControllerPresFalling        (int     value);
    void signalEventChangedAutoControllerSelectBitmap       (int     value);
    void signalEventChangedAutoControllerThreCondition      (int     value);
    void signalEventChangedAutoController1ThreValue         (QString value);
    void signalEventChangedAutoController2ThreValue         (QString value);
    void signalEventChangedAutoController3ThreValue         (QString value);
    void signalEventChangedAutoController4ThreValue         (QString value);

    void signalEventChangedIsEditControllerSelector         (bool value   );
    void signalEventChangedIsEditPresCtrlSpeed              (bool value   );
    void signalEventChangedIsEditCtrlPosiRestrictionEnable  (bool value   );
    void signalEventChangedIsEditCtrlPosiRestrictionMax     (bool value   );
    void signalEventChangedIsEditCtrlPosiRestrictionMin     (bool value   );
    void signalEventChangedIsEditAutoControllerSelectEnable (bool value   );
    void signalEventChangedIsEditAutoControllerSelectMode   (bool value   );
    void signalEventChangedIsEditAutoControllerPresRising   (bool value   );
    void signalEventChangedIsEditAutoControllerPresFalling  (bool value   );
    void signalEventChangedIsEditAutoControllerSelectBitmap (bool value   );
    void signalEventChangedIsEditAutoControllerThreCondition(bool value   );
    void signalEventChangedIsEditAutoController1ThreValue   (bool value   );
    void signalEventChangedIsEditAutoController2ThreValue   (bool value   );
    void signalEventChangedIsEditAutoController3ThreValue   (bool value   );
    void signalEventChangedIsEditAutoController4ThreValue   (bool value   );

    void signalEventChangedErrControllerSelector            (bool value   );
    void signalEventChangedErrPresCtrlSpeed                 (bool value   );
    void signalEventChangedErrCtrlPosiRestrictionEnable     (bool value   );
    void signalEventChangedErrCtrlPosiRestrictionMax        (bool value   );
    void signalEventChangedErrCtrlPosiRestrictionMin        (bool value   );
    void signalEventChangedErrAutoControllerSelectEnable    (bool value   );
    void signalEventChangedErrAutoControllerSelectMode      (bool value   );
    void signalEventChangedErrAutoControllerPresRising      (bool value   );
    void signalEventChangedErrAutoControllerPresFalling     (bool value   );
    void signalEventChangedErrAutoControllerSelectBitmap    (bool value   );
    void signalEventChangedErrAutoControllerThreCondition   (bool value   );
    void signalEventChangedErrAutoController1ThreValue      (bool value   );
    void signalEventChangedErrAutoController2ThreValue      (bool value   );
    void signalEventChangedErrAutoController3ThreValue      (bool value   );
    void signalEventChangedErrAutoController4ThreValue      (bool value   );

    void signalEventChangedIsEdit             (bool    value);
    void signalEventChangedStrStatus          (QString value);
    void signalEventChangedErrMsg             (QString value);
    void signalEventChangedErrMsg2            (QString value);
    void signalEventChangedProgress           (int     value);

    void signalEventOccurErr                  (             );

public:
    explicit PressureCtrlForPmProtoDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        //ENABLE_SLOT_VALVE_CHANGED_FIRMWARE_VER ;
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        //mControllerItemList = new QList<PressureCtrlControllerItem *>();
        mControllerItemList.append(new PressureCtrlControllerItem(this));
        mControllerItemList.append(new PressureCtrlControllerItem(this));
        mControllerItemList.append(new PressureCtrlControllerItem(this));
        mControllerItemList.append(new PressureCtrlControllerItem(this));

        mControllerItemList[0]->mId = 1;
        mControllerItemList[1]->mId = 2;
        mControllerItemList[2]->mId = 3;
        mControllerItemList[3]->mId = 4;
        mControllerItemList[0]->mIfScaleConverter = &mIfScaleConverter;
        mControllerItemList[1]->mIfScaleConverter = &mIfScaleConverter;
        mControllerItemList[2]->mIfScaleConverter = &mIfScaleConverter;
        mControllerItemList[3]->mIfScaleConverter = &mIfScaleConverter;


        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        mIsWritten = false;
        setState(eState::STATE_INIT);
    }
    ~PressureCtrlForPmProtoDlgModel()
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

    void onValveWrittenCustomRequest(ValveResponseDto dto){
        setErrMsg(dto.mErrMsg);

        //if(mState >= eState::STATE_READ_CTRL_SELECTOR_USED || mState >= eState::STATE_READ_CTRL_SELECTOR)
        //if(mState == eState::STATE_WRITE_CTRL_1_RampSlope || mState == eState::STATE_READ_CTRL_1_RampSlope)
        //if(mState == eState::STATE_READ_PRES_CTRL_SPEED || mState == eState::STATE_WRITE_PRES_CTRL_SPEED)
        if(mState != STATE_READ_CTRL_SELECTOR_USED)
        {
            qDebug() << "[" << Q_FUNC_INFO << "] state" << mState << ", req = " << dto.mReqDto.mReqCommand << ", res = " << dto.mResData;
        }

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        switch((int)mState)
        {
            case (int)STATE_READ_POSI_SCALE_MODE            : if(dto.mReqDto.mReqCommand.startsWith("p:0BA112010100") == false) return; break;
            case (int)STATE_READ_POSI_SCALE_CLOSE_VALUE     : if(dto.mReqDto.mReqCommand.startsWith("p:0BA112010200") == false) return; break;
            case (int)STATE_READ_POSI_SCALE_OPEN_VALUE      : if(dto.mReqDto.mReqCommand.startsWith("p:0BA112010300") == false) return; break;
            case (int)STATE_READ_PRES_SCALE_MODE            : if(dto.mReqDto.mReqCommand.startsWith("p:0BA112020100") == false) return; break;
            case (int)STATE_READ_PRES_SCALE_MIN_VALUE       : if(dto.mReqDto.mReqCommand.startsWith("p:0BA112020200") == false) return; break;
            case (int)STATE_READ_PRES_SCALE_MAX_VALUE       : if(dto.mReqDto.mReqCommand.startsWith("p:0BA112020300") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_AlgorithmMode      : if(dto.mReqDto.mReqCommand.startsWith("p:010711010000") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_GainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:010711020300") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_DeltaFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010711020700") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_SensorDelay        : if(dto.mReqDto.mReqCommand.startsWith("p:010711020400") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_LearnDataSelection : if(dto.mReqDto.mReqCommand.startsWith("p:010711020500") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_Direction          : if(dto.mReqDto.mReqCommand.startsWith("p:010711020600") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_PGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010711020100") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_IGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010711020200") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_PressureScaler     : if(dto.mReqDto.mReqCommand.startsWith("p:010711022300") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_RampEnable         : if(dto.mReqDto.mReqCommand.startsWith("p:010711030100") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_RampTime           : if(dto.mReqDto.mReqCommand.startsWith("p:010711030200") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_RampSlope          : if(dto.mReqDto.mReqCommand.startsWith("p:010711030300") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_RampMode           : if(dto.mReqDto.mReqCommand.startsWith("p:010711030400") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_RampStartValue     : if(dto.mReqDto.mReqCommand.startsWith("p:010711030500") == false) return; break;
            case (int)STATE_WRITE_CTRL_1_RampType           : if(dto.mReqDto.mReqCommand.startsWith("p:010711030600") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_AlgorithmMode      : if(dto.mReqDto.mReqCommand.startsWith("p:010712010000") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_GainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:010712020300") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_DeltaFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010712020700") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_SensorDelay        : if(dto.mReqDto.mReqCommand.startsWith("p:010712020400") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_LearnDataSelection : if(dto.mReqDto.mReqCommand.startsWith("p:010712020500") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_Direction          : if(dto.mReqDto.mReqCommand.startsWith("p:010712020600") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_PGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010712020100") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_IGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010712020200") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_PressureScaler     : if(dto.mReqDto.mReqCommand.startsWith("p:010712022300") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_RampEnable         : if(dto.mReqDto.mReqCommand.startsWith("p:010712030100") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_RampTime           : if(dto.mReqDto.mReqCommand.startsWith("p:010712030200") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_RampSlope          : if(dto.mReqDto.mReqCommand.startsWith("p:010712030300") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_RampMode           : if(dto.mReqDto.mReqCommand.startsWith("p:010712030400") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_RampStartValue     : if(dto.mReqDto.mReqCommand.startsWith("p:010712030500") == false) return; break;
            case (int)STATE_WRITE_CTRL_2_RampType           : if(dto.mReqDto.mReqCommand.startsWith("p:010712030600") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_AlgorithmMode      : if(dto.mReqDto.mReqCommand.startsWith("p:010713010000") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_GainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:010713020300") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_DeltaFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010713020700") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_SensorDelay        : if(dto.mReqDto.mReqCommand.startsWith("p:010713020400") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_LearnDataSelection : if(dto.mReqDto.mReqCommand.startsWith("p:010713020500") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_Direction          : if(dto.mReqDto.mReqCommand.startsWith("p:010713020600") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_PGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010713020100") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_IGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010713020200") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_PressureScaler     : if(dto.mReqDto.mReqCommand.startsWith("p:010713022300") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_RampEnable         : if(dto.mReqDto.mReqCommand.startsWith("p:010713030100") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_RampTime           : if(dto.mReqDto.mReqCommand.startsWith("p:010713030200") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_RampSlope          : if(dto.mReqDto.mReqCommand.startsWith("p:010713030300") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_RampMode           : if(dto.mReqDto.mReqCommand.startsWith("p:010713030400") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_RampStartValue     : if(dto.mReqDto.mReqCommand.startsWith("p:010713030500") == false) return; break;
            case (int)STATE_WRITE_CTRL_3_RampType           : if(dto.mReqDto.mReqCommand.startsWith("p:010713030600") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_AlgorithmMode      : if(dto.mReqDto.mReqCommand.startsWith("p:010714010000") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_GainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:010714020300") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_DeltaFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010714020700") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_SensorDelay        : if(dto.mReqDto.mReqCommand.startsWith("p:010714020400") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_LearnDataSelection : if(dto.mReqDto.mReqCommand.startsWith("p:010714020500") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_Direction          : if(dto.mReqDto.mReqCommand.startsWith("p:010714020600") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_PGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010714020100") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_IGainFactor        : if(dto.mReqDto.mReqCommand.startsWith("p:010714020200") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_PressureScaler     : if(dto.mReqDto.mReqCommand.startsWith("p:010714022300") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_RampEnable         : if(dto.mReqDto.mReqCommand.startsWith("p:010714030100") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_RampTime           : if(dto.mReqDto.mReqCommand.startsWith("p:010714030200") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_RampSlope          : if(dto.mReqDto.mReqCommand.startsWith("p:010714030300") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_RampMode           : if(dto.mReqDto.mReqCommand.startsWith("p:010714030400") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_RampStartValue     : if(dto.mReqDto.mReqCommand.startsWith("p:010714030500") == false) return; break;
            case (int)STATE_WRITE_CTRL_4_RampType           : if(dto.mReqDto.mReqCommand.startsWith("p:010714030600") == false) return; break;
            case (int)STATE_WRITE_CTRL_SELECTOR             : if(dto.mReqDto.mReqCommand.startsWith("p:010710000000") == false) return; break;
            case (int)STATE_WRITE_PRES_CTRL_SPEED           : if(dto.mReqDto.mReqCommand.startsWith("p:010705000000") == false) return; break;
            case (int)STATE_WRITE_POSI_RESTRICTION_ENABLE   : if(dto.mReqDto.mReqCommand.startsWith("p:010730120100") == false) return; break;
            case (int)STATE_WRITE_POSI_RESTRICTION_MAX      : if(dto.mReqDto.mReqCommand.startsWith("p:010730120300") == false) return; break;
            case (int)STATE_WRITE_POSI_RESTRICTION_MIN      : if(dto.mReqDto.mReqCommand.startsWith("p:010730120200") == false) return; break;
            case (int)STATE_WRITE_AUTO_SEL_ENABLE           : if(dto.mReqDto.mReqCommand.startsWith("p:010730170100") == false) return; break;
            case (int)STATE_WRITE_AUTO_SEL_MODE             : if(dto.mReqDto.mReqCommand.startsWith("p:010730170200") == false) return; break;
            case (int)STATE_WRITE_AUTO_PRES_RISING          : if(dto.mReqDto.mReqCommand.startsWith("p:010730172000") == false) return; break;
            case (int)STATE_WRITE_AUTO_PRES_FALLING         : if(dto.mReqDto.mReqCommand.startsWith("p:010730172100") == false) return; break;
            case (int)STATE_WRITE_AUTO_SEL_BITMAP           : if(dto.mReqDto.mReqCommand.startsWith("p:010730170300") == false) return; break;
            case (int)STATE_WRITE_AUTO_TRES_CONDITION       : if(dto.mReqDto.mReqCommand.startsWith("p:010730171000") == false) return; break;
            case (int)STATE_WRITE_AUTO_THRES_1              : if(dto.mReqDto.mReqCommand.startsWith("p:010730170400") == false) return; break;
            case (int)STATE_WRITE_AUTO_THRES_2              : if(dto.mReqDto.mReqCommand.startsWith("p:010730170500") == false) return; break;
            case (int)STATE_WRITE_AUTO_THRES_3              : if(dto.mReqDto.mReqCommand.startsWith("p:010730170600") == false) return; break;
            case (int)STATE_WRITE_AUTO_THRES_4              : if(dto.mReqDto.mReqCommand.startsWith("p:010730170700") == false) return; break;
            case (int)STATE_READ_CTRL_1_AlgorithmMode       : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711010000") == false) return; break;
            case (int)STATE_READ_CTRL_1_GainFactor          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711020300") == false) return; break;
            case (int)STATE_READ_CTRL_1_DeltaFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711020700") == false) return; break;
            case (int)STATE_READ_CTRL_1_SensorDelay         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711020400") == false) return; break;
            case (int)STATE_READ_CTRL_1_LearnDataSelection  : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711020500") == false) return; break;
            case (int)STATE_READ_CTRL_1_Direction           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711020600") == false) return; break;
            case (int)STATE_READ_CTRL_1_PGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711020100") == false) return; break;
            case (int)STATE_READ_CTRL_1_IGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711020200") == false) return; break;
            case (int)STATE_READ_CTRL_1_PressureScaler      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711022300") == false) return; break;
            case (int)STATE_READ_CTRL_1_RampEnable          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711030100") == false) return; break;
            case (int)STATE_READ_CTRL_1_RampTime            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711030200") == false) return; break;
            case (int)STATE_READ_CTRL_1_RampSlope           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711030300") == false) return; break;
            case (int)STATE_READ_CTRL_1_RampMode            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711030400") == false) return; break;
            case (int)STATE_READ_CTRL_1_RampStartValue      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711030500") == false) return; break;
            case (int)STATE_READ_CTRL_1_RampType            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0711030600") == false) return; break;
            case (int)STATE_READ_CTRL_2_AlgorithmMode       : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712010000") == false) return; break;
            case (int)STATE_READ_CTRL_2_GainFactor          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712020300") == false) return; break;
            case (int)STATE_READ_CTRL_2_DeltaFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712020700") == false) return; break;
            case (int)STATE_READ_CTRL_2_SensorDelay         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712020400") == false) return; break;
            case (int)STATE_READ_CTRL_2_LearnDataSelection  : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712020500") == false) return; break;
            case (int)STATE_READ_CTRL_2_Direction           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712020600") == false) return; break;
            case (int)STATE_READ_CTRL_2_PGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712020100") == false) return; break;
            case (int)STATE_READ_CTRL_2_IGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712020200") == false) return; break;
            case (int)STATE_READ_CTRL_2_PressureScaler      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712022300") == false) return; break;
            case (int)STATE_READ_CTRL_2_RampEnable          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712030100") == false) return; break;
            case (int)STATE_READ_CTRL_2_RampTime            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712030200") == false) return; break;
            case (int)STATE_READ_CTRL_2_RampSlope           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712030300") == false) return; break;
            case (int)STATE_READ_CTRL_2_RampMode            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712030400") == false) return; break;
            case (int)STATE_READ_CTRL_2_RampStartValue      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712030500") == false) return; break;
            case (int)STATE_READ_CTRL_2_RampType            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0712030600") == false) return; break;
            case (int)STATE_READ_CTRL_3_AlgorithmMode       : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713010000") == false) return; break;
            case (int)STATE_READ_CTRL_3_GainFactor          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713020300") == false) return; break;
            case (int)STATE_READ_CTRL_3_DeltaFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713020700") == false) return; break;
            case (int)STATE_READ_CTRL_3_SensorDelay         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713020400") == false) return; break;
            case (int)STATE_READ_CTRL_3_LearnDataSelection  : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713020500") == false) return; break;
            case (int)STATE_READ_CTRL_3_Direction           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713020600") == false) return; break;
            case (int)STATE_READ_CTRL_3_PGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713020100") == false) return; break;
            case (int)STATE_READ_CTRL_3_IGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713020200") == false) return; break;
            case (int)STATE_READ_CTRL_3_PressureScaler      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713022300") == false) return; break;
            case (int)STATE_READ_CTRL_3_RampEnable          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713030100") == false) return; break;
            case (int)STATE_READ_CTRL_3_RampTime            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713030200") == false) return; break;
            case (int)STATE_READ_CTRL_3_RampSlope           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713030300") == false) return; break;
            case (int)STATE_READ_CTRL_3_RampMode            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713030400") == false) return; break;
            case (int)STATE_READ_CTRL_3_RampStartValue      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713030500") == false) return; break;
            case (int)STATE_READ_CTRL_3_RampType            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0713030600") == false) return; break;
            case (int)STATE_READ_CTRL_4_AlgorithmMode       : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714010000") == false) return; break;
            case (int)STATE_READ_CTRL_4_GainFactor          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714020300") == false) return; break;
            case (int)STATE_READ_CTRL_4_DeltaFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714020700") == false) return; break;
            case (int)STATE_READ_CTRL_4_SensorDelay         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714020400") == false) return; break;
            case (int)STATE_READ_CTRL_4_LearnDataSelection  : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714020500") == false) return; break;
            case (int)STATE_READ_CTRL_4_Direction           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714020600") == false) return; break;
            case (int)STATE_READ_CTRL_4_PGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714020100") == false) return; break;
            case (int)STATE_READ_CTRL_4_IGainFactor         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714020200") == false) return; break;
            case (int)STATE_READ_CTRL_4_PressureScaler      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714022300") == false) return; break;
            case (int)STATE_READ_CTRL_4_RampEnable          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714030100") == false) return; break;
            case (int)STATE_READ_CTRL_4_RampTime            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714030200") == false) return; break;
            case (int)STATE_READ_CTRL_4_RampSlope           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714030300") == false) return; break;
            case (int)STATE_READ_CTRL_4_RampMode            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714030400") == false) return; break;
            case (int)STATE_READ_CTRL_4_RampStartValue      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714030500") == false) return; break;
            case (int)STATE_READ_CTRL_4_RampType            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0714030600") == false) return; break;
            case (int)STATE_READ_CTRL_SELECTOR              : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710000000") == false) return; break;
            case (int)STATE_READ_PRES_CTRL_SPEED            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0705000000") == false) return; break;
            case (int)STATE_READ_POSI_RESTRICTION_ENABLE    : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730120100") == false) return; break;
            case (int)STATE_READ_POSI_RESTRICTION_MAX       : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730120300") == false) return; break;
            case (int)STATE_READ_POSI_RESTRICTION_MIN       : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730120200") == false) return; break;
            case (int)STATE_READ_AUTO_SEL_ENABLE            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730170100") == false) return; break;
            case (int)STATE_READ_AUTO_SEL_MODE              : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730170200") == false) return; break;
            case (int)STATE_READ_AUTO_PRES_RISING           : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730172000") == false) return; break;
            case (int)STATE_READ_AUTO_PRES_FALLING          : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730172100") == false) return; break;
            case (int)STATE_READ_AUTO_SEL_BITMAP            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730170300") == false) return; break;
            case (int)STATE_READ_AUTO_TRES_CONDITION        : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730171000") == false) return; break;
            case (int)STATE_READ_AUTO_THRES_1               : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730170400") == false) return; break;
            case (int)STATE_READ_AUTO_THRES_2               : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730170500") == false) return; break;
            case (int)STATE_READ_AUTO_THRES_3               : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730170600") == false) return; break;
            case (int)STATE_READ_AUTO_THRES_4               : if(dto.mReqDto.mReqCommand.startsWith("p:0B0730170700") == false) return; break;
            case (int)STATE_READ_CTRL_SELECTOR_USED         : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710010000") == false) return; break;
            //case (int)STATE_READ_CONDUCTANCE                : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710020000") == false) return; break;
            //case (int)STATE_READ_MFC_FLOW                   : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710030000") == false) return; break;
            //case (int)STATE_READ_MFC_FLOW_UNIT              : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710040000") == false) return; break;
            //case (int)STATE_READ_CHANBER_VOL                : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710080000") == false) return; break;
            //case (int)STATE_READ_ADAP_CONDUCTANCE_GAIN      : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710050000") == false) return; break;
            //case (int)STATE_READ_ADAP_FLOW_GAIN             : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710060000") == false) return; break;
            //case (int)STATE_READ_ADAP_TOTAL_GAIN            : if(dto.mReqDto.mReqCommand.startsWith("p:0B0710070000") == false) return; break;
        }


        switch ((int)mState) {
            case (int)STATE_READ_CTRL_SELECTOR_USED         : if(dto.mResData.startsWith("p:00") == true){setControllerSelectorUsed  ( dto.mResData.mid(16).toInt())   ;} break;
            //case (int)STATE_READ_CONDUCTANCE                : if(dto.mResData.startsWith("p:00") == true){setConductance             ( dto.mResData.mid(16)        )   ;} break;
            //case (int)STATE_READ_MFC_FLOW                   : if(dto.mResData.startsWith("p:00") == true){setMfcFlow                 ( dto.mResData.mid(16)        )   ;} break;
            //case (int)STATE_READ_MFC_FLOW_UNIT              : if(dto.mResData.startsWith("p:00") == true){setMfcFlowUnit             ( dto.mResData.mid(16).toInt())   ;} break;
            //case (int)STATE_READ_CHANBER_VOL                : if(dto.mResData.startsWith("p:00") == true){setChamberVol              ( dto.mResData.mid(16)        )   ;} break;
            //case (int)STATE_READ_ADAP_CONDUCTANCE_GAIN      : if(dto.mResData.startsWith("p:00") == true){setAdaptiveConductanceGain ( dto.mResData.mid(16)        )   ;} break;
            //case (int)STATE_READ_ADAP_FLOW_GAIN             : if(dto.mResData.startsWith("p:00") == true){setAdaptiveFlowGain        ( dto.mResData.mid(16)        )   ;} break;
            //case (int)STATE_READ_ADAP_TOTAL_GAIN            : if(dto.mResData.startsWith("p:00") == true){setAdaptiveTotalGain       ( dto.mResData.mid(16)        )   ;} break;
            case (int)STATE_READ_POSI_SCALE_MODE            : if(dto.mResData.startsWith("p:00") == true){mIfScaleConverter.mPosiScaleMode       = dto.mResData.mid(16).toInt()    ;} break;
            case (int)STATE_READ_POSI_SCALE_CLOSE_VALUE     : if(dto.mResData.startsWith("p:00") == true){mIfScaleConverter.mPosiScaleCloseValue = dto.mResData.mid(16).toDouble() ;} break;
            case (int)STATE_READ_POSI_SCALE_OPEN_VALUE      : if(dto.mResData.startsWith("p:00") == true){mIfScaleConverter.mPosiScaleOpenValue  = dto.mResData.mid(16).toDouble() ;} break;
            case (int)STATE_READ_PRES_SCALE_MODE            : if(dto.mResData.startsWith("p:00") == true){mIfScaleConverter.mPresScaleMode       = dto.mResData.mid(16).toInt();   ;} break;
            case (int)STATE_READ_PRES_SCALE_MIN_VALUE       : if(dto.mResData.startsWith("p:00") == true){mIfScaleConverter.mPresScaleMin        = dto.mResData.mid(16).toDouble() ;} break;
            case (int)STATE_READ_PRES_SCALE_MAX_VALUE       : if(dto.mResData.startsWith("p:00") == true){mIfScaleConverter.mPresScaleMax        = dto.mResData.mid(16).toDouble() ;} break;
            default:
                if(mIsWritten)
                {
                    if(mState >= eState::STATE_READ_CTRL_1_AlgorithmMode && mState <= eState::STATE_READ_AUTO_THRES_4)
                        checkTotalErrState(mState, dto.mResData);
                }
                else
                {
                    if(mState >= eState::STATE_READ_CTRL_1_AlgorithmMode && mState <= eState::STATE_READ_AUTO_THRES_4)
                        setTotalValue(mState, dto.mResData);
                }
                break;
        }

        if(mState == STATE_READ_PRES_SCALE_MAX_VALUE)
        {
            //qDebug() << "PosiScaleMode       : " << mIfScaleConverter.mPosiScaleMode       ;
            //qDebug() << "PosiScaleCloseValue : " << mIfScaleConverter.mPosiScaleCloseValue ;
            //qDebug() << "PosiScaleOpenValue  : " << mIfScaleConverter.mPosiScaleOpenValue  ;
            //qDebug() << "PresScaleMode       : " << mIfScaleConverter.mPresScaleMode       ;
            //qDebug() << "PresScaleMin        : " << mIfScaleConverter.mPresScaleMin        ;
            //qDebug() << "PresScaleMax        : " << mIfScaleConverter.mPresScaleMax        ;
        }
        if(mState == STATE_READ_AUTO_THRES_4)
        {
            checkTotalWriteValue();
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEditController                 (             ){ setIsEdit(true); }
    Q_INVOKABLE void onCommandSetEditControllerSelector         (int     value){ mWriteControllerSelector          = value; setIsEditControllerSelector         (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditPresCtrlSpeed              (QString value){ mWritePresCtrlSpeed               = value; setIsEditPresCtrlSpeed              (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditCtrlPosiRestrictionEnable  (int     value){ mWriteCtrlPosiRestrictionEnable   = value; setIsEditCtrlPosiRestrictionEnable  (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditCtrlPosiRestrictionMax     (QString value){ mWriteCtrlPosiRestrictionMax      = value; setIsEditCtrlPosiRestrictionMax     (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditCtrlPosiRestrictionMin     (QString value){ mWriteCtrlPosiRestrictionMin      = value; setIsEditCtrlPosiRestrictionMin     (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoControllerSelectEnable (int     value){ mWriteAutoControllerSelectEnable  = value; setIsEditAutoControllerSelectEnable (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoControllerSelectMode   (int     value){ mWriteAutoControllerSelectMode    = value; setIsEditAutoControllerSelectMode   (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoControllerPresRising   (int     value){ mWriteAutoControllerPresRising    = value; setIsEditAutoControllerPresRising   (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoControllerPresFalling  (int     value){ mWriteAutoControllerPresFalling   = value; setIsEditAutoControllerPresFalling  (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoControllerSelectBitmap (bool value, int bitIndex)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value << ", bitIndex = " <<  bitIndex;
        int mask = 1 << bitIndex;
        if (value == false) {
            mWriteAutoControllerSelectBitmap &= ~mask;
        } else {
            mWriteAutoControllerSelectBitmap |= mask;
        }
        setIsEditAutoControllerSelectBitmap (true);
        setIsEdit(true);
    }
    Q_INVOKABLE void onCommandSetEditAutoControllerThreCondition(int     value){ mWriteAutoControllerThreCondition = value; setIsEditAutoControllerThreCondition(true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoController1ThreValue   (QString value){ mWriteAutoController1ThreValue    = value; setIsEditAutoController1ThreValue   (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoController2ThreValue   (QString value){ mWriteAutoController2ThreValue    = value; setIsEditAutoController2ThreValue   (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoController3ThreValue   (QString value){ mWriteAutoController3ThreValue    = value; setIsEditAutoController3ThreValue   (true); setIsEdit(true);}
    Q_INVOKABLE void onCommandSetEditAutoController4ThreValue   (QString value){ mWriteAutoController4ThreValue    = value; setIsEditAutoController4ThreValue   (true); setIsEdit(true);}

    Q_INVOKABLE PressureCtrlControllerItem * onCommandGetControllerItem(int idx)
    {
        return mControllerItemList[idx];
    }

    Q_INVOKABLE void onCommandApply()
    {
        mIsWritten       = true;

        setErrMsg2("");

        setState(eState::STATE_WRITE_CTRL_1_AlgorithmMode);
    }

private:
    enum eState{
        STATE_INIT                              = 0,
        STATE_READ_POSI_SCALE_MODE              = STATE_INIT + 1,
        STATE_READ_POSI_SCALE_CLOSE_VALUE       = STATE_READ_POSI_SCALE_MODE             + 1,
        STATE_READ_POSI_SCALE_OPEN_VALUE        = STATE_READ_POSI_SCALE_CLOSE_VALUE      + 1,
        STATE_READ_PRES_SCALE_MODE              = STATE_READ_POSI_SCALE_OPEN_VALUE       + 1,
        STATE_READ_PRES_SCALE_MIN_VALUE         = STATE_READ_PRES_SCALE_MODE             + 1,
        STATE_READ_PRES_SCALE_MAX_VALUE         = STATE_READ_PRES_SCALE_MIN_VALUE        + 1,
        STATE_WRITE_CTRL_1_AlgorithmMode        = STATE_READ_PRES_SCALE_MAX_VALUE        + 1,
        STATE_WRITE_CTRL_1_GainFactor           = STATE_WRITE_CTRL_1_AlgorithmMode       + 1,
        STATE_WRITE_CTRL_1_DeltaFactor          = STATE_WRITE_CTRL_1_GainFactor          + 1,
        STATE_WRITE_CTRL_1_SensorDelay          = STATE_WRITE_CTRL_1_DeltaFactor         + 1,
        STATE_WRITE_CTRL_1_LearnDataSelection   = STATE_WRITE_CTRL_1_SensorDelay         + 1,
        STATE_WRITE_CTRL_1_Direction            = STATE_WRITE_CTRL_1_LearnDataSelection  + 1,
        STATE_WRITE_CTRL_1_PGainFactor          = STATE_WRITE_CTRL_1_Direction           + 1,
        STATE_WRITE_CTRL_1_IGainFactor          = STATE_WRITE_CTRL_1_PGainFactor         + 1,
        STATE_WRITE_CTRL_1_PressureScaler       = STATE_WRITE_CTRL_1_IGainFactor         + 1,
        STATE_WRITE_CTRL_1_RampEnable           = STATE_WRITE_CTRL_1_PressureScaler      + 1,
        STATE_WRITE_CTRL_1_RampTime             = STATE_WRITE_CTRL_1_RampEnable          + 1,
        STATE_WRITE_CTRL_1_RampSlope            = STATE_WRITE_CTRL_1_RampTime            + 1,
        STATE_WRITE_CTRL_1_RampMode             = STATE_WRITE_CTRL_1_RampSlope           + 1,
        STATE_WRITE_CTRL_1_RampStartValue       = STATE_WRITE_CTRL_1_RampMode            + 1,
        STATE_WRITE_CTRL_1_RampType             = STATE_WRITE_CTRL_1_RampStartValue      + 1,
        STATE_WRITE_CTRL_2_AlgorithmMode        = STATE_WRITE_CTRL_1_RampType            + 1,
        STATE_WRITE_CTRL_2_GainFactor           = STATE_WRITE_CTRL_2_AlgorithmMode       + 1,
        STATE_WRITE_CTRL_2_DeltaFactor          = STATE_WRITE_CTRL_2_GainFactor          + 1,
        STATE_WRITE_CTRL_2_SensorDelay          = STATE_WRITE_CTRL_2_DeltaFactor         + 1,
        STATE_WRITE_CTRL_2_LearnDataSelection   = STATE_WRITE_CTRL_2_SensorDelay         + 1,
        STATE_WRITE_CTRL_2_Direction            = STATE_WRITE_CTRL_2_LearnDataSelection  + 1,
        STATE_WRITE_CTRL_2_PGainFactor          = STATE_WRITE_CTRL_2_Direction           + 1,
        STATE_WRITE_CTRL_2_IGainFactor          = STATE_WRITE_CTRL_2_PGainFactor         + 1,
        STATE_WRITE_CTRL_2_PressureScaler       = STATE_WRITE_CTRL_2_IGainFactor         + 1,
        STATE_WRITE_CTRL_2_RampEnable           = STATE_WRITE_CTRL_2_PressureScaler      + 1,
        STATE_WRITE_CTRL_2_RampTime             = STATE_WRITE_CTRL_2_RampEnable          + 1,
        STATE_WRITE_CTRL_2_RampSlope            = STATE_WRITE_CTRL_2_RampTime            + 1,
        STATE_WRITE_CTRL_2_RampMode             = STATE_WRITE_CTRL_2_RampSlope           + 1,
        STATE_WRITE_CTRL_2_RampStartValue       = STATE_WRITE_CTRL_2_RampMode            + 1,
        STATE_WRITE_CTRL_2_RampType             = STATE_WRITE_CTRL_2_RampStartValue      + 1,
        STATE_WRITE_CTRL_3_AlgorithmMode        = STATE_WRITE_CTRL_2_RampType            + 1,
        STATE_WRITE_CTRL_3_GainFactor           = STATE_WRITE_CTRL_3_AlgorithmMode       + 1,
        STATE_WRITE_CTRL_3_DeltaFactor          = STATE_WRITE_CTRL_3_GainFactor          + 1,
        STATE_WRITE_CTRL_3_SensorDelay          = STATE_WRITE_CTRL_3_DeltaFactor         + 1,
        STATE_WRITE_CTRL_3_LearnDataSelection   = STATE_WRITE_CTRL_3_SensorDelay         + 1,
        STATE_WRITE_CTRL_3_Direction            = STATE_WRITE_CTRL_3_LearnDataSelection  + 1,
        STATE_WRITE_CTRL_3_PGainFactor          = STATE_WRITE_CTRL_3_Direction           + 1,
        STATE_WRITE_CTRL_3_IGainFactor          = STATE_WRITE_CTRL_3_PGainFactor         + 1,
        STATE_WRITE_CTRL_3_PressureScaler       = STATE_WRITE_CTRL_3_IGainFactor         + 1,
        STATE_WRITE_CTRL_3_RampEnable           = STATE_WRITE_CTRL_3_PressureScaler      + 1,
        STATE_WRITE_CTRL_3_RampTime             = STATE_WRITE_CTRL_3_RampEnable          + 1,
        STATE_WRITE_CTRL_3_RampSlope            = STATE_WRITE_CTRL_3_RampTime            + 1,
        STATE_WRITE_CTRL_3_RampMode             = STATE_WRITE_CTRL_3_RampSlope           + 1,
        STATE_WRITE_CTRL_3_RampStartValue       = STATE_WRITE_CTRL_3_RampMode            + 1,
        STATE_WRITE_CTRL_3_RampType             = STATE_WRITE_CTRL_3_RampStartValue      + 1,
        STATE_WRITE_CTRL_4_AlgorithmMode        = STATE_WRITE_CTRL_3_RampType            + 1,
        STATE_WRITE_CTRL_4_GainFactor           = STATE_WRITE_CTRL_4_AlgorithmMode       + 1,
        STATE_WRITE_CTRL_4_DeltaFactor          = STATE_WRITE_CTRL_4_GainFactor          + 1,
        STATE_WRITE_CTRL_4_SensorDelay          = STATE_WRITE_CTRL_4_DeltaFactor         + 1,
        STATE_WRITE_CTRL_4_LearnDataSelection   = STATE_WRITE_CTRL_4_SensorDelay         + 1,
        STATE_WRITE_CTRL_4_Direction            = STATE_WRITE_CTRL_4_LearnDataSelection  + 1,
        STATE_WRITE_CTRL_4_PGainFactor          = STATE_WRITE_CTRL_4_Direction           + 1,
        STATE_WRITE_CTRL_4_IGainFactor          = STATE_WRITE_CTRL_4_PGainFactor         + 1,
        STATE_WRITE_CTRL_4_PressureScaler       = STATE_WRITE_CTRL_4_IGainFactor         + 1,
        STATE_WRITE_CTRL_4_RampEnable           = STATE_WRITE_CTRL_4_PressureScaler      + 1,
        STATE_WRITE_CTRL_4_RampTime             = STATE_WRITE_CTRL_4_RampEnable          + 1,
        STATE_WRITE_CTRL_4_RampSlope            = STATE_WRITE_CTRL_4_RampTime            + 1,
        STATE_WRITE_CTRL_4_RampMode             = STATE_WRITE_CTRL_4_RampSlope           + 1,
        STATE_WRITE_CTRL_4_RampStartValue       = STATE_WRITE_CTRL_4_RampMode            + 1,
        STATE_WRITE_CTRL_4_RampType             = STATE_WRITE_CTRL_4_RampStartValue      + 1,
        STATE_WRITE_CTRL_SELECTOR               = STATE_WRITE_CTRL_4_RampType            + 1,
        STATE_WRITE_PRES_CTRL_SPEED             = STATE_WRITE_CTRL_SELECTOR              + 1,
        STATE_WRITE_POSI_RESTRICTION_ENABLE     = STATE_WRITE_PRES_CTRL_SPEED            + 1,
        STATE_WRITE_POSI_RESTRICTION_MAX        = STATE_WRITE_POSI_RESTRICTION_ENABLE    + 1,
        STATE_WRITE_POSI_RESTRICTION_MIN        = STATE_WRITE_POSI_RESTRICTION_MAX       + 1,
        STATE_WRITE_AUTO_SEL_ENABLE             = STATE_WRITE_POSI_RESTRICTION_MIN       + 1,
        STATE_WRITE_AUTO_SEL_MODE               = STATE_WRITE_AUTO_SEL_ENABLE            + 1,
        STATE_WRITE_AUTO_PRES_RISING            = STATE_WRITE_AUTO_SEL_MODE              + 1,
        STATE_WRITE_AUTO_PRES_FALLING           = STATE_WRITE_AUTO_PRES_RISING           + 1,
        STATE_WRITE_AUTO_SEL_BITMAP             = STATE_WRITE_AUTO_PRES_FALLING          + 1,
        STATE_WRITE_AUTO_TRES_CONDITION         = STATE_WRITE_AUTO_SEL_BITMAP            + 1,
        STATE_WRITE_AUTO_THRES_1                = STATE_WRITE_AUTO_TRES_CONDITION        + 1,
        STATE_WRITE_AUTO_THRES_2                = STATE_WRITE_AUTO_THRES_1               + 1,
        STATE_WRITE_AUTO_THRES_3                = STATE_WRITE_AUTO_THRES_2               + 1,
        STATE_WRITE_AUTO_THRES_4                = STATE_WRITE_AUTO_THRES_3               + 1,
        STATE_READ_CTRL_1_AlgorithmMode         = STATE_WRITE_AUTO_THRES_4               + 1,
        STATE_READ_CTRL_1_GainFactor            = STATE_READ_CTRL_1_AlgorithmMode        + 1,
        STATE_READ_CTRL_1_DeltaFactor           = STATE_READ_CTRL_1_GainFactor           + 1,
        STATE_READ_CTRL_1_SensorDelay           = STATE_READ_CTRL_1_DeltaFactor          + 1,
        STATE_READ_CTRL_1_LearnDataSelection    = STATE_READ_CTRL_1_SensorDelay          + 1,
        STATE_READ_CTRL_1_Direction             = STATE_READ_CTRL_1_LearnDataSelection   + 1,
        STATE_READ_CTRL_1_PGainFactor           = STATE_READ_CTRL_1_Direction            + 1,
        STATE_READ_CTRL_1_IGainFactor           = STATE_READ_CTRL_1_PGainFactor          + 1,
        STATE_READ_CTRL_1_PressureScaler        = STATE_READ_CTRL_1_IGainFactor          + 1,
        STATE_READ_CTRL_1_RampEnable            = STATE_READ_CTRL_1_PressureScaler       + 1,
        STATE_READ_CTRL_1_RampTime              = STATE_READ_CTRL_1_RampEnable           + 1,
        STATE_READ_CTRL_1_RampSlope             = STATE_READ_CTRL_1_RampTime             + 1,
        STATE_READ_CTRL_1_RampMode              = STATE_READ_CTRL_1_RampSlope            + 1,
        STATE_READ_CTRL_1_RampStartValue        = STATE_READ_CTRL_1_RampMode             + 1,
        STATE_READ_CTRL_1_RampType              = STATE_READ_CTRL_1_RampStartValue       + 1,
        STATE_READ_CTRL_2_AlgorithmMode         = STATE_READ_CTRL_1_RampType             + 1,
        STATE_READ_CTRL_2_GainFactor            = STATE_READ_CTRL_2_AlgorithmMode        + 1,
        STATE_READ_CTRL_2_DeltaFactor           = STATE_READ_CTRL_2_GainFactor           + 1,
        STATE_READ_CTRL_2_SensorDelay           = STATE_READ_CTRL_2_DeltaFactor          + 1,
        STATE_READ_CTRL_2_LearnDataSelection    = STATE_READ_CTRL_2_SensorDelay          + 1,
        STATE_READ_CTRL_2_Direction             = STATE_READ_CTRL_2_LearnDataSelection   + 1,
        STATE_READ_CTRL_2_PGainFactor           = STATE_READ_CTRL_2_Direction            + 1,
        STATE_READ_CTRL_2_IGainFactor           = STATE_READ_CTRL_2_PGainFactor          + 1,
        STATE_READ_CTRL_2_PressureScaler        = STATE_READ_CTRL_2_IGainFactor          + 1,
        STATE_READ_CTRL_2_RampEnable            = STATE_READ_CTRL_2_PressureScaler       + 1,
        STATE_READ_CTRL_2_RampTime              = STATE_READ_CTRL_2_RampEnable           + 1,
        STATE_READ_CTRL_2_RampSlope             = STATE_READ_CTRL_2_RampTime             + 1,
        STATE_READ_CTRL_2_RampMode              = STATE_READ_CTRL_2_RampSlope            + 1,
        STATE_READ_CTRL_2_RampStartValue        = STATE_READ_CTRL_2_RampMode             + 1,
        STATE_READ_CTRL_2_RampType              = STATE_READ_CTRL_2_RampStartValue       + 1,
        STATE_READ_CTRL_3_AlgorithmMode         = STATE_READ_CTRL_2_RampType             + 1,
        STATE_READ_CTRL_3_GainFactor            = STATE_READ_CTRL_3_AlgorithmMode        + 1,
        STATE_READ_CTRL_3_DeltaFactor           = STATE_READ_CTRL_3_GainFactor           + 1,
        STATE_READ_CTRL_3_SensorDelay           = STATE_READ_CTRL_3_DeltaFactor          + 1,
        STATE_READ_CTRL_3_LearnDataSelection    = STATE_READ_CTRL_3_SensorDelay          + 1,
        STATE_READ_CTRL_3_Direction             = STATE_READ_CTRL_3_LearnDataSelection   + 1,
        STATE_READ_CTRL_3_PGainFactor           = STATE_READ_CTRL_3_Direction            + 1,
        STATE_READ_CTRL_3_IGainFactor           = STATE_READ_CTRL_3_PGainFactor          + 1,
        STATE_READ_CTRL_3_PressureScaler        = STATE_READ_CTRL_3_IGainFactor          + 1,
        STATE_READ_CTRL_3_RampEnable            = STATE_READ_CTRL_3_PressureScaler       + 1,
        STATE_READ_CTRL_3_RampTime              = STATE_READ_CTRL_3_RampEnable           + 1,
        STATE_READ_CTRL_3_RampSlope             = STATE_READ_CTRL_3_RampTime             + 1,
        STATE_READ_CTRL_3_RampMode              = STATE_READ_CTRL_3_RampSlope            + 1,
        STATE_READ_CTRL_3_RampStartValue        = STATE_READ_CTRL_3_RampMode             + 1,
        STATE_READ_CTRL_3_RampType              = STATE_READ_CTRL_3_RampStartValue       + 1,
        STATE_READ_CTRL_4_AlgorithmMode         = STATE_READ_CTRL_3_RampType             + 1,
        STATE_READ_CTRL_4_GainFactor            = STATE_READ_CTRL_4_AlgorithmMode        + 1,
        STATE_READ_CTRL_4_DeltaFactor           = STATE_READ_CTRL_4_GainFactor           + 1,
        STATE_READ_CTRL_4_SensorDelay           = STATE_READ_CTRL_4_DeltaFactor          + 1,
        STATE_READ_CTRL_4_LearnDataSelection    = STATE_READ_CTRL_4_SensorDelay          + 1,
        STATE_READ_CTRL_4_Direction             = STATE_READ_CTRL_4_LearnDataSelection   + 1,
        STATE_READ_CTRL_4_PGainFactor           = STATE_READ_CTRL_4_Direction            + 1,
        STATE_READ_CTRL_4_IGainFactor           = STATE_READ_CTRL_4_PGainFactor          + 1,
        STATE_READ_CTRL_4_PressureScaler        = STATE_READ_CTRL_4_IGainFactor          + 1,
        STATE_READ_CTRL_4_RampEnable            = STATE_READ_CTRL_4_PressureScaler       + 1,
        STATE_READ_CTRL_4_RampTime              = STATE_READ_CTRL_4_RampEnable           + 1,
        STATE_READ_CTRL_4_RampSlope             = STATE_READ_CTRL_4_RampTime             + 1,
        STATE_READ_CTRL_4_RampMode              = STATE_READ_CTRL_4_RampSlope            + 1,
        STATE_READ_CTRL_4_RampStartValue        = STATE_READ_CTRL_4_RampMode             + 1,
        STATE_READ_CTRL_4_RampType              = STATE_READ_CTRL_4_RampStartValue       + 1,
        STATE_READ_CTRL_SELECTOR                = STATE_READ_CTRL_4_RampType             + 1,
        STATE_READ_PRES_CTRL_SPEED              = STATE_READ_CTRL_SELECTOR               + 1,
        STATE_READ_POSI_RESTRICTION_ENABLE      = STATE_READ_PRES_CTRL_SPEED             + 1,
        STATE_READ_POSI_RESTRICTION_MAX         = STATE_READ_POSI_RESTRICTION_ENABLE     + 1,
        STATE_READ_POSI_RESTRICTION_MIN         = STATE_READ_POSI_RESTRICTION_MAX        + 1,
        STATE_READ_AUTO_SEL_ENABLE              = STATE_READ_POSI_RESTRICTION_MIN        + 1,
        STATE_READ_AUTO_SEL_MODE                = STATE_READ_AUTO_SEL_ENABLE             + 1,
        STATE_READ_AUTO_PRES_RISING             = STATE_READ_AUTO_SEL_MODE               + 1,
        STATE_READ_AUTO_PRES_FALLING            = STATE_READ_AUTO_PRES_RISING            + 1,
        STATE_READ_AUTO_SEL_BITMAP              = STATE_READ_AUTO_PRES_FALLING           + 1,
        STATE_READ_AUTO_TRES_CONDITION          = STATE_READ_AUTO_SEL_BITMAP             + 1,
        STATE_READ_AUTO_THRES_1                 = STATE_READ_AUTO_TRES_CONDITION         + 1,
        STATE_READ_AUTO_THRES_2                 = STATE_READ_AUTO_THRES_1                + 1,
        STATE_READ_AUTO_THRES_3                 = STATE_READ_AUTO_THRES_2                + 1,
        STATE_READ_AUTO_THRES_4                 = STATE_READ_AUTO_THRES_3                + 1,
        STATE_READ_CTRL_SELECTOR_USED           = STATE_READ_AUTO_THRES_4                + 1,
        //STATE_READ_CONDUCTANCE                  = STATE_READ_CTRL_SELECTOR_USED          + 1,
        //STATE_READ_MFC_FLOW                     = STATE_READ_CONDUCTANCE                 + 1,
        //STATE_READ_MFC_FLOW_UNIT                = STATE_READ_MFC_FLOW                    + 1,
        //STATE_READ_CHANBER_VOL                  = STATE_READ_MFC_FLOW_UNIT               + 1,
        //STATE_READ_ADAP_CONDUCTANCE_GAIN        = STATE_READ_CHANBER_VOL                 + 1,
        //STATE_READ_ADAP_FLOW_GAIN               = STATE_READ_ADAP_CONDUCTANCE_GAIN       + 1,
        //STATE_READ_ADAP_TOTAL_GAIN              = STATE_READ_ADAP_FLOW_GAIN              + 1,
        STATE_OVER                               = STATE_READ_CTRL_SELECTOR_USED         + 1
    };

    QTimer mTimer;
    InterfaceScaleConvert mIfScaleConverter;
    bool   mIsWritten     = false;

    int     mWriteControllerSelector          = 0;
    QString mWritePresCtrlSpeed               = "";
    int     mWriteCtrlPosiRestrictionEnable   = 0;
    QString mWriteCtrlPosiRestrictionMax      = "";
    QString mWriteCtrlPosiRestrictionMin      = "";
    int     mWriteAutoControllerSelectEnable  = 0;
    int     mWriteAutoControllerSelectMode    = 0;
    int     mWriteAutoControllerPresRising    = 0;
    int     mWriteAutoControllerPresFalling   = 0;
    int     mWriteAutoControllerSelectBitmap  = 0;
    int     mWriteAutoControllerThreCondition = 0;
    QString mWriteAutoController1ThreValue    = "";
    QString mWriteAutoController2ThreValue    = "";
    QString mWriteAutoController3ThreValue    = "";
    QString mWriteAutoController4ThreValue    = "";

    eState mState         = eState::STATE_INIT;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(20);
    }

    void setState(eState state, bool immediately = false)
    {
        if(!mIsWritten && state == eState::STATE_READ_CTRL_SELECTOR_USED)
        {
            mWriteAutoControllerSelectBitmap = getAutoControllerSelectBitmap();
            setTotalEditReset();
        }

        mState = state;

        if(state >= STATE_READ_CTRL_1_AlgorithmMode && state <= STATE_READ_AUTO_THRES_4)
        {
            setStrStatus("Loading");
        }
        else if(state >= STATE_WRITE_CTRL_1_AlgorithmMode && state <= STATE_WRITE_AUTO_THRES_4)
        {
            setStrStatus("writting");
        }
        else
        {
            setStrStatus("ready");
        }

        if((state >= eState::STATE_READ_POSI_SCALE_MODE       && state <= eState::STATE_READ_PRES_SCALE_MAX_VALUE) ||
           (state >= eState::STATE_WRITE_CTRL_1_AlgorithmMode && state <= eState::STATE_READ_AUTO_THRES_4        )   )
        {
            setProgress(qFloor((state * 100) / eState::STATE_OVER));
        }
        else
        {
            setProgress(100);
        }

        if(state == eState::STATE_OVER)
        {
            mState = STATE_READ_CTRL_SELECTOR_USED;
            startTimer();
        }
        else
        {
            if(immediately)
                onTimeout();
            else
                startTimer();
        }
    }

public slots:
    void onTimeout()
    {
        switch((int)mState)
        {
            case (int)STATE_INIT: setTotalEditReset(); setState((eState)(mState + 1)); break;
            case (int)STATE_READ_POSI_SCALE_MODE            : pValveSP->customRequest("p:0BA112010100", this); break;
            case (int)STATE_READ_POSI_SCALE_CLOSE_VALUE     : pValveSP->customRequest("p:0BA112010200", this); break;
            case (int)STATE_READ_POSI_SCALE_OPEN_VALUE      : pValveSP->customRequest("p:0BA112010300", this); break;
            case (int)STATE_READ_PRES_SCALE_MODE            : pValveSP->customRequest("p:0BA112020100", this); break;
            case (int)STATE_READ_PRES_SCALE_MIN_VALUE       : pValveSP->customRequest("p:0BA112020200", this); break;
            case (int)STATE_READ_PRES_SCALE_MAX_VALUE       : pValveSP->customRequest("p:0BA112020300", this); break;
            case (int)STATE_WRITE_CTRL_1_AlgorithmMode      : if(mControllerItemList[0]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711010000%1").arg(mControllerItemList[0]->mWriteControllerAlgorithmMode      ), this); break;
            case (int)STATE_WRITE_CTRL_1_GainFactor         : if(mControllerItemList[0]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711020300%1").arg(mControllerItemList[0]->mWriteControllerGainFactor         ), this); break;
            case (int)STATE_WRITE_CTRL_1_DeltaFactor        : if(mControllerItemList[0]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711020700%1").arg(mControllerItemList[0]->mWriteControllerDeltaFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_1_SensorDelay        : if(mControllerItemList[0]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711020400%1").arg(mControllerItemList[0]->mWriteControllerSensorDelay        ), this); break;
            case (int)STATE_WRITE_CTRL_1_LearnDataSelection : if(mControllerItemList[0]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711020500%1").arg(mControllerItemList[0]->mWriteControllerLearnDataSelection ), this); break;
            case (int)STATE_WRITE_CTRL_1_Direction          : if(mControllerItemList[0]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711020600%1").arg(mControllerItemList[0]->mWriteControllerDirection          ), this); break;
            case (int)STATE_WRITE_CTRL_1_PGainFactor        : if(mControllerItemList[0]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711020100%1").arg(mControllerItemList[0]->mWriteControllerPGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_1_IGainFactor        : if(mControllerItemList[0]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711020200%1").arg(mControllerItemList[0]->mWriteControllerIGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_1_PressureScaler     : if(mControllerItemList[0]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711022300%1").arg(mControllerItemList[0]->mWriteControllerPressureScaler     ), this); break;
            case (int)STATE_WRITE_CTRL_1_RampEnable         : if(mControllerItemList[0]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711030100%1").arg(mControllerItemList[0]->mWriteControllerRampEnable         ), this); break;
            case (int)STATE_WRITE_CTRL_1_RampTime           : if(mControllerItemList[0]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711030200%1").arg(mControllerItemList[0]->mWriteControllerRampTime           ), this); break;
            case (int)STATE_WRITE_CTRL_1_RampSlope          : if(mControllerItemList[0]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711030300%1").arg(mIfScaleConverter.convertToIFPres(mControllerItemList[0]->mWriteControllerRampSlope)), this); break;
            case (int)STATE_WRITE_CTRL_1_RampMode           : if(mControllerItemList[0]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711030400%1").arg(mControllerItemList[0]->mWriteControllerRampMode           ), this); break;
            case (int)STATE_WRITE_CTRL_1_RampStartValue     : if(mControllerItemList[0]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711030500%1").arg(mControllerItemList[0]->mWriteControllerRampStartValue     ), this); break;
            case (int)STATE_WRITE_CTRL_1_RampType           : if(mControllerItemList[0]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010711030600%1").arg(mControllerItemList[0]->mWriteControllerRampType           ), this); break;
            case (int)STATE_WRITE_CTRL_2_AlgorithmMode      : if(mControllerItemList[1]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712010000%1").arg(mControllerItemList[1]->mWriteControllerAlgorithmMode      ), this); break;
            case (int)STATE_WRITE_CTRL_2_GainFactor         : if(mControllerItemList[1]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712020300%1").arg(mControllerItemList[1]->mWriteControllerGainFactor         ), this); break;
            case (int)STATE_WRITE_CTRL_2_DeltaFactor        : if(mControllerItemList[1]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712020700%1").arg(mControllerItemList[1]->mWriteControllerDeltaFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_2_SensorDelay        : if(mControllerItemList[1]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712020400%1").arg(mControllerItemList[1]->mWriteControllerSensorDelay        ), this); break;
            case (int)STATE_WRITE_CTRL_2_LearnDataSelection : if(mControllerItemList[1]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712020500%1").arg(mControllerItemList[1]->mWriteControllerLearnDataSelection ), this); break;
            case (int)STATE_WRITE_CTRL_2_Direction          : if(mControllerItemList[1]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712020600%1").arg(mControllerItemList[1]->mWriteControllerDirection          ), this); break;
            case (int)STATE_WRITE_CTRL_2_PGainFactor        : if(mControllerItemList[1]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712020100%1").arg(mControllerItemList[1]->mWriteControllerPGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_2_IGainFactor        : if(mControllerItemList[1]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712020200%1").arg(mControllerItemList[1]->mWriteControllerIGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_2_PressureScaler     : if(mControllerItemList[1]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712022300%1").arg(mControllerItemList[1]->mWriteControllerPressureScaler     ), this); break;
            case (int)STATE_WRITE_CTRL_2_RampEnable         : if(mControllerItemList[1]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712030100%1").arg(mControllerItemList[1]->mWriteControllerRampEnable         ), this); break;
            case (int)STATE_WRITE_CTRL_2_RampTime           : if(mControllerItemList[1]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712030200%1").arg(mControllerItemList[1]->mWriteControllerRampTime           ), this); break;
            case (int)STATE_WRITE_CTRL_2_RampSlope          : if(mControllerItemList[1]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712030300%1").arg(mIfScaleConverter.convertToIFPres(mControllerItemList[1]->mWriteControllerRampSlope)), this); break;
            case (int)STATE_WRITE_CTRL_2_RampMode           : if(mControllerItemList[1]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712030400%1").arg(mControllerItemList[1]->mWriteControllerRampMode           ), this); break;
            case (int)STATE_WRITE_CTRL_2_RampStartValue     : if(mControllerItemList[1]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712030500%1").arg(mControllerItemList[1]->mWriteControllerRampStartValue     ), this); break;
            case (int)STATE_WRITE_CTRL_2_RampType           : if(mControllerItemList[1]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010712030600%1").arg(mControllerItemList[1]->mWriteControllerRampType           ), this); break;
            case (int)STATE_WRITE_CTRL_3_AlgorithmMode      : if(mControllerItemList[2]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713010000%1").arg(mControllerItemList[2]->mWriteControllerAlgorithmMode      ), this); break;
            case (int)STATE_WRITE_CTRL_3_GainFactor         : if(mControllerItemList[2]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713020300%1").arg(mControllerItemList[2]->mWriteControllerGainFactor         ), this); break;
            case (int)STATE_WRITE_CTRL_3_DeltaFactor        : if(mControllerItemList[2]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713020700%1").arg(mControllerItemList[2]->mWriteControllerDeltaFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_3_SensorDelay        : if(mControllerItemList[2]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713020400%1").arg(mControllerItemList[2]->mWriteControllerSensorDelay        ), this); break;
            case (int)STATE_WRITE_CTRL_3_LearnDataSelection : if(mControllerItemList[2]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713020500%1").arg(mControllerItemList[2]->mWriteControllerLearnDataSelection ), this); break;
            case (int)STATE_WRITE_CTRL_3_Direction          : if(mControllerItemList[2]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713020600%1").arg(mControllerItemList[2]->mWriteControllerDirection          ), this); break;
            case (int)STATE_WRITE_CTRL_3_PGainFactor        : if(mControllerItemList[2]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713020100%1").arg(mControllerItemList[2]->mWriteControllerPGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_3_IGainFactor        : if(mControllerItemList[2]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713020200%1").arg(mControllerItemList[2]->mWriteControllerIGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_3_PressureScaler     : if(mControllerItemList[2]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713022300%1").arg(mControllerItemList[2]->mWriteControllerPressureScaler     ), this); break;
            case (int)STATE_WRITE_CTRL_3_RampEnable         : if(mControllerItemList[2]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713030100%1").arg(mControllerItemList[2]->mWriteControllerRampEnable         ), this); break;
            case (int)STATE_WRITE_CTRL_3_RampTime           : if(mControllerItemList[2]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713030200%1").arg(mControllerItemList[2]->mWriteControllerRampTime           ), this); break;
            case (int)STATE_WRITE_CTRL_3_RampSlope          : if(mControllerItemList[2]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713030300%1").arg(mIfScaleConverter.convertToIFPres(mControllerItemList[2]->mWriteControllerRampSlope)), this); break;
            case (int)STATE_WRITE_CTRL_3_RampMode           : if(mControllerItemList[2]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713030400%1").arg(mControllerItemList[2]->mWriteControllerRampMode           ), this); break;
            case (int)STATE_WRITE_CTRL_3_RampStartValue     : if(mControllerItemList[2]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713030500%1").arg(mControllerItemList[2]->mWriteControllerRampStartValue     ), this); break;
            case (int)STATE_WRITE_CTRL_3_RampType           : if(mControllerItemList[2]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010713030600%1").arg(mControllerItemList[2]->mWriteControllerRampType           ), this); break;
            case (int)STATE_WRITE_CTRL_4_AlgorithmMode      : if(mControllerItemList[3]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714010000%1").arg(mControllerItemList[3]->mWriteControllerAlgorithmMode      ), this); break;
            case (int)STATE_WRITE_CTRL_4_GainFactor         : if(mControllerItemList[3]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714020300%1").arg(mControllerItemList[3]->mWriteControllerGainFactor         ), this); break;
            case (int)STATE_WRITE_CTRL_4_DeltaFactor        : if(mControllerItemList[3]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714020700%1").arg(mControllerItemList[3]->mWriteControllerDeltaFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_4_SensorDelay        : if(mControllerItemList[3]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714020400%1").arg(mControllerItemList[3]->mWriteControllerSensorDelay        ), this); break;
            case (int)STATE_WRITE_CTRL_4_LearnDataSelection : if(mControllerItemList[3]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714020500%1").arg(mControllerItemList[3]->mWriteControllerLearnDataSelection ), this); break;
            case (int)STATE_WRITE_CTRL_4_Direction          : if(mControllerItemList[3]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714020600%1").arg(mControllerItemList[3]->mWriteControllerDirection          ), this); break;
            case (int)STATE_WRITE_CTRL_4_PGainFactor        : if(mControllerItemList[3]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714020100%1").arg(mControllerItemList[3]->mWriteControllerPGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_4_IGainFactor        : if(mControllerItemList[3]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714020200%1").arg(mControllerItemList[3]->mWriteControllerIGainFactor        ), this); break;
            case (int)STATE_WRITE_CTRL_4_PressureScaler     : if(mControllerItemList[3]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714022300%1").arg(mControllerItemList[3]->mWriteControllerPressureScaler     ), this); break;
            case (int)STATE_WRITE_CTRL_4_RampEnable         : if(mControllerItemList[3]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714030100%1").arg(mControllerItemList[3]->mWriteControllerRampEnable         ), this); break;
            case (int)STATE_WRITE_CTRL_4_RampTime           : if(mControllerItemList[3]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714030200%1").arg(mControllerItemList[3]->mWriteControllerRampTime           ), this); break;
            case (int)STATE_WRITE_CTRL_4_RampSlope          : if(mControllerItemList[3]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714030300%1").arg(mIfScaleConverter.convertToIFPres(mControllerItemList[3]->mWriteControllerRampSlope)), this); break;
            case (int)STATE_WRITE_CTRL_4_RampMode           : if(mControllerItemList[3]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714030400%1").arg(mControllerItemList[3]->mWriteControllerRampMode           ), this); break;
            case (int)STATE_WRITE_CTRL_4_RampStartValue     : if(mControllerItemList[3]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714030500%1").arg(mControllerItemList[3]->mWriteControllerRampStartValue     ), this); break;
            case (int)STATE_WRITE_CTRL_4_RampType           : if(mControllerItemList[3]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010714030600%1").arg(mControllerItemList[3]->mWriteControllerRampType           ), this); break;
            case (int)STATE_WRITE_CTRL_SELECTOR             : if(IsNeedWriteControllerSelector         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010710000000%1").arg(mWriteControllerSelector                                   ), this); break;
            case (int)STATE_WRITE_PRES_CTRL_SPEED           : if(IsNeedWritePresCtrlSpeed              () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010705000000%1").arg(mWritePresCtrlSpeed                                        ), this); break;
            case (int)STATE_WRITE_POSI_RESTRICTION_ENABLE   : if(IsNeedWriteCtrlPosiRestrictionEnable  () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730120100%1").arg(mWriteCtrlPosiRestrictionEnable                            ), this); break;
            case (int)STATE_WRITE_POSI_RESTRICTION_MAX      : if(IsNeedWriteCtrlPosiRestrictionMax     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730120300%1").arg(mIfScaleConverter.convertToIFPosi(mWriteCtrlPosiRestrictionMax)), this); break;
            case (int)STATE_WRITE_POSI_RESTRICTION_MIN      : if(IsNeedWriteCtrlPosiRestrictionMin     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730120200%1").arg(mIfScaleConverter.convertToIFPosi(mWriteCtrlPosiRestrictionMin)), this); break;
            case (int)STATE_WRITE_AUTO_SEL_ENABLE           : if(IsNeedWriteAutoControllerSelectEnable () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730170100%1").arg(mWriteAutoControllerSelectEnable                           ), this); break;
            case (int)STATE_WRITE_AUTO_SEL_MODE             : if(IsNeedWriteAutoControllerSelectMode   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730170200%1").arg(mWriteAutoControllerSelectMode                             ), this); break;
            case (int)STATE_WRITE_AUTO_PRES_RISING          : if(IsNeedWriteAutoControllerPresRising   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730172000%1").arg(mWriteAutoControllerPresRising                             ), this); break;
            case (int)STATE_WRITE_AUTO_PRES_FALLING         : if(IsNeedWriteAutoControllerPresFalling  () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730172100%1").arg(mWriteAutoControllerPresFalling                            ), this); break;
            case (int)STATE_WRITE_AUTO_SEL_BITMAP           : if(IsNeedWriteAutoControllerSelectBitmap () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730170300%1").arg(mWriteAutoControllerSelectBitmap                           ), this); break;
            case (int)STATE_WRITE_AUTO_TRES_CONDITION       : if(IsNeedWriteAutoControllerThreCondition() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730171000%1").arg(mWriteAutoControllerThreCondition                          ), this); break;
            case (int)STATE_WRITE_AUTO_THRES_1              : if(IsNeedWriteAutoController1ThreValue   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730170400%1").arg(mIfScaleConverter.convertToIFPres(mWriteAutoController1ThreValue)), this); break;
            case (int)STATE_WRITE_AUTO_THRES_2              : if(IsNeedWriteAutoController2ThreValue   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730170500%1").arg(mIfScaleConverter.convertToIFPres(mWriteAutoController2ThreValue)), this); break;
            case (int)STATE_WRITE_AUTO_THRES_3              : if(IsNeedWriteAutoController3ThreValue   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730170600%1").arg(mIfScaleConverter.convertToIFPres(mWriteAutoController3ThreValue)), this); break;
            case (int)STATE_WRITE_AUTO_THRES_4              : if(IsNeedWriteAutoController4ThreValue   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest(QString("p:010730170700%1").arg(mIfScaleConverter.convertToIFPres(mWriteAutoController4ThreValue)), this); break;
            case (int)STATE_READ_CTRL_1_AlgorithmMode       : if(mIsWritten && mControllerItemList[0]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711010000", this); break;
            case (int)STATE_READ_CTRL_1_GainFactor          : if(mIsWritten && mControllerItemList[0]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711020300", this); break;
            case (int)STATE_READ_CTRL_1_DeltaFactor         : if(mIsWritten && mControllerItemList[0]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711020700", this); break;
            case (int)STATE_READ_CTRL_1_SensorDelay         : if(mIsWritten && mControllerItemList[0]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711020400", this); break;
            case (int)STATE_READ_CTRL_1_LearnDataSelection  : if(mIsWritten && mControllerItemList[0]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711020500", this); break;
            case (int)STATE_READ_CTRL_1_Direction           : if(mIsWritten && mControllerItemList[0]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711020600", this); break;
            case (int)STATE_READ_CTRL_1_PGainFactor         : if(mIsWritten && mControllerItemList[0]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711020100", this); break;
            case (int)STATE_READ_CTRL_1_IGainFactor         : if(mIsWritten && mControllerItemList[0]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711020200", this); break;
            case (int)STATE_READ_CTRL_1_PressureScaler      : if(mIsWritten && mControllerItemList[0]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711022300", this); break;
            case (int)STATE_READ_CTRL_1_RampEnable          : if(mIsWritten && mControllerItemList[0]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711030100", this); break;
            case (int)STATE_READ_CTRL_1_RampTime            : if(mIsWritten && mControllerItemList[0]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711030200", this); break;
            case (int)STATE_READ_CTRL_1_RampSlope           : if(mIsWritten && mControllerItemList[0]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711030300", this); break;
            case (int)STATE_READ_CTRL_1_RampMode            : if(mIsWritten && mControllerItemList[0]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711030400", this); break;
            case (int)STATE_READ_CTRL_1_RampStartValue      : if(mIsWritten && mControllerItemList[0]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711030500", this); break;
            case (int)STATE_READ_CTRL_1_RampType            : if(mIsWritten && mControllerItemList[0]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0711030600", this); break;
            case (int)STATE_READ_CTRL_2_AlgorithmMode       : if(mIsWritten && mControllerItemList[1]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712010000", this); break;
            case (int)STATE_READ_CTRL_2_GainFactor          : if(mIsWritten && mControllerItemList[1]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712020300", this); break;
            case (int)STATE_READ_CTRL_2_DeltaFactor         : if(mIsWritten && mControllerItemList[1]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712020700", this); break;
            case (int)STATE_READ_CTRL_2_SensorDelay         : if(mIsWritten && mControllerItemList[1]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712020400", this); break;
            case (int)STATE_READ_CTRL_2_LearnDataSelection  : if(mIsWritten && mControllerItemList[1]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712020500", this); break;
            case (int)STATE_READ_CTRL_2_Direction           : if(mIsWritten && mControllerItemList[1]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712020600", this); break;
            case (int)STATE_READ_CTRL_2_PGainFactor         : if(mIsWritten && mControllerItemList[1]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712020100", this); break;
            case (int)STATE_READ_CTRL_2_IGainFactor         : if(mIsWritten && mControllerItemList[1]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712020200", this); break;
            case (int)STATE_READ_CTRL_2_PressureScaler      : if(mIsWritten && mControllerItemList[1]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712022300", this); break;
            case (int)STATE_READ_CTRL_2_RampEnable          : if(mIsWritten && mControllerItemList[1]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712030100", this); break;
            case (int)STATE_READ_CTRL_2_RampTime            : if(mIsWritten && mControllerItemList[1]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712030200", this); break;
            case (int)STATE_READ_CTRL_2_RampSlope           : if(mIsWritten && mControllerItemList[1]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712030300", this); break;
            case (int)STATE_READ_CTRL_2_RampMode            : if(mIsWritten && mControllerItemList[1]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712030400", this); break;
            case (int)STATE_READ_CTRL_2_RampStartValue      : if(mIsWritten && mControllerItemList[1]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712030500", this); break;
            case (int)STATE_READ_CTRL_2_RampType            : if(mIsWritten && mControllerItemList[1]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0712030600", this); break;
            case (int)STATE_READ_CTRL_3_AlgorithmMode       : if(mIsWritten && mControllerItemList[2]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713010000", this); break;
            case (int)STATE_READ_CTRL_3_GainFactor          : if(mIsWritten && mControllerItemList[2]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713020300", this); break;
            case (int)STATE_READ_CTRL_3_DeltaFactor         : if(mIsWritten && mControllerItemList[2]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713020700", this); break;
            case (int)STATE_READ_CTRL_3_SensorDelay         : if(mIsWritten && mControllerItemList[2]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713020400", this); break;
            case (int)STATE_READ_CTRL_3_LearnDataSelection  : if(mIsWritten && mControllerItemList[2]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713020500", this); break;
            case (int)STATE_READ_CTRL_3_Direction           : if(mIsWritten && mControllerItemList[2]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713020600", this); break;
            case (int)STATE_READ_CTRL_3_PGainFactor         : if(mIsWritten && mControllerItemList[2]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713020100", this); break;
            case (int)STATE_READ_CTRL_3_IGainFactor         : if(mIsWritten && mControllerItemList[2]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713020200", this); break;
            case (int)STATE_READ_CTRL_3_PressureScaler      : if(mIsWritten && mControllerItemList[2]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713022300", this); break;
            case (int)STATE_READ_CTRL_3_RampEnable          : if(mIsWritten && mControllerItemList[2]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713030100", this); break;
            case (int)STATE_READ_CTRL_3_RampTime            : if(mIsWritten && mControllerItemList[2]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713030200", this); break;
            case (int)STATE_READ_CTRL_3_RampSlope           : if(mIsWritten && mControllerItemList[2]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713030300", this); break;
            case (int)STATE_READ_CTRL_3_RampMode            : if(mIsWritten && mControllerItemList[2]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713030400", this); break;
            case (int)STATE_READ_CTRL_3_RampStartValue      : if(mIsWritten && mControllerItemList[2]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713030500", this); break;
            case (int)STATE_READ_CTRL_3_RampType            : if(mIsWritten && mControllerItemList[2]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0713030600", this); break;
            case (int)STATE_READ_CTRL_4_AlgorithmMode       : if(mIsWritten && mControllerItemList[3]->IsNeedWriteAlgorithmMode     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714010000", this); break;
            case (int)STATE_READ_CTRL_4_GainFactor          : if(mIsWritten && mControllerItemList[3]->IsNeedWriteGainFactor        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714020300", this); break;
            case (int)STATE_READ_CTRL_4_DeltaFactor         : if(mIsWritten && mControllerItemList[3]->IsNeedWriteDeltaFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714020700", this); break;
            case (int)STATE_READ_CTRL_4_SensorDelay         : if(mIsWritten && mControllerItemList[3]->IsNeedWriteSensorDelay       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714020400", this); break;
            case (int)STATE_READ_CTRL_4_LearnDataSelection  : if(mIsWritten && mControllerItemList[3]->IsNeedWriteLearnDataSelection() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714020500", this); break;
            case (int)STATE_READ_CTRL_4_Direction           : if(mIsWritten && mControllerItemList[3]->IsNeedWriteDirection         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714020600", this); break;
            case (int)STATE_READ_CTRL_4_PGainFactor         : if(mIsWritten && mControllerItemList[3]->IsNeedWritePGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714020100", this); break;
            case (int)STATE_READ_CTRL_4_IGainFactor         : if(mIsWritten && mControllerItemList[3]->IsNeedWriteIGainFactor       () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714020200", this); break;
            case (int)STATE_READ_CTRL_4_PressureScaler      : if(mIsWritten && mControllerItemList[3]->IsNeedWritePressureScaler    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714022300", this); break;
            case (int)STATE_READ_CTRL_4_RampEnable          : if(mIsWritten && mControllerItemList[3]->IsNeedWriteRampEnable        () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714030100", this); break;
            case (int)STATE_READ_CTRL_4_RampTime            : if(mIsWritten && mControllerItemList[3]->IsNeedWriteRampTime          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714030200", this); break;
            case (int)STATE_READ_CTRL_4_RampSlope           : if(mIsWritten && mControllerItemList[3]->IsNeedWriteRampSlope         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714030300", this); break;
            case (int)STATE_READ_CTRL_4_RampMode            : if(mIsWritten && mControllerItemList[3]->IsNeedWriteRampMode          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714030400", this); break;
            case (int)STATE_READ_CTRL_4_RampStartValue      : if(mIsWritten && mControllerItemList[3]->IsNeedWriteRampStartValue    () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714030500", this); break;
            case (int)STATE_READ_CTRL_4_RampType            : if(mIsWritten && mControllerItemList[3]->IsNeedWriteRampType          () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0714030600", this); break;
            case (int)STATE_READ_CTRL_SELECTOR              : if(mIsWritten && IsNeedWriteControllerSelector         () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0710000000", this); break;
            case (int)STATE_READ_PRES_CTRL_SPEED            : if(mIsWritten && IsNeedWritePresCtrlSpeed              () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0705000000", this); break;
            case (int)STATE_READ_POSI_RESTRICTION_ENABLE    : if(mIsWritten && IsNeedWriteCtrlPosiRestrictionEnable  () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730120100", this); break;
            case (int)STATE_READ_POSI_RESTRICTION_MAX       : if(mIsWritten && IsNeedWriteCtrlPosiRestrictionMax     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730120300", this); break;
            case (int)STATE_READ_POSI_RESTRICTION_MIN       : if(mIsWritten && IsNeedWriteCtrlPosiRestrictionMin     () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730120200", this); break;
            case (int)STATE_READ_AUTO_SEL_ENABLE            : if(mIsWritten && IsNeedWriteAutoControllerSelectEnable () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730170100", this); break;
            case (int)STATE_READ_AUTO_SEL_MODE              : if(mIsWritten && IsNeedWriteAutoControllerSelectMode   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730170200", this); break;
            case (int)STATE_READ_AUTO_PRES_RISING           : if(mIsWritten && IsNeedWriteAutoControllerPresRising   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730172000", this); break;
            case (int)STATE_READ_AUTO_PRES_FALLING          : if(mIsWritten && IsNeedWriteAutoControllerPresFalling  () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730172100", this); break;
            case (int)STATE_READ_AUTO_SEL_BITMAP            : if(mIsWritten && IsNeedWriteAutoControllerSelectBitmap () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730170300", this); break;
            case (int)STATE_READ_AUTO_TRES_CONDITION        : if(mIsWritten && IsNeedWriteAutoControllerThreCondition() == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730171000", this); break;
            case (int)STATE_READ_AUTO_THRES_1               : if(mIsWritten && IsNeedWriteAutoController1ThreValue   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730170400", this); break;
            case (int)STATE_READ_AUTO_THRES_2               : if(mIsWritten && IsNeedWriteAutoController2ThreValue   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730170500", this); break;
            case (int)STATE_READ_AUTO_THRES_3               : if(mIsWritten && IsNeedWriteAutoController3ThreValue   () == false){setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730170600", this); break;
            case (int)STATE_READ_AUTO_THRES_4               : if(mIsWritten && IsNeedWriteAutoController4ThreValue   () == false){checkTotalWriteValue(); setState((eState)(mState + 1), true); return;} pValveSP->customRequest("p:0B0730170700", this); break;
            case (int)STATE_READ_CTRL_SELECTOR_USED         : pValveSP->customRequest("p:0B0710010000", this); break;
            //case (int)STATE_READ_CONDUCTANCE                : pValveSP->customRequest("p:0B0710020000", this); break;
            //case (int)STATE_READ_MFC_FLOW                   : pValveSP->customRequest("p:0B0710030000", this); break;
            //case (int)STATE_READ_MFC_FLOW_UNIT              : pValveSP->customRequest("p:0B0710040000", this); break;
            //case (int)STATE_READ_CHANBER_VOL                : pValveSP->customRequest("p:0B0710080000", this); break;
            //case (int)STATE_READ_ADAP_CONDUCTANCE_GAIN      : pValveSP->customRequest("p:0B0710050000", this); break;
            //case (int)STATE_READ_ADAP_FLOW_GAIN             : pValveSP->customRequest("p:0B0710060000", this); break;
            //case (int)STATE_READ_ADAP_TOTAL_GAIN            : pValveSP->customRequest("p:0B0710070000", this); break;

        }
    }

    bool IsNeedWriteControllerSelector         (){ return (getIsEditControllerSelector         () || getErrControllerSelector         () ); }
    bool IsNeedWritePresCtrlSpeed              (){ return (getIsEditPresCtrlSpeed              () || getErrPresCtrlSpeed              () ); }
    bool IsNeedWriteCtrlPosiRestrictionEnable  (){ return (getIsEditCtrlPosiRestrictionEnable  () || getErrCtrlPosiRestrictionEnable  () ); }
    bool IsNeedWriteCtrlPosiRestrictionMax     (){ return (getIsEditCtrlPosiRestrictionMax     () || getErrCtrlPosiRestrictionMax     () ); }
    bool IsNeedWriteCtrlPosiRestrictionMin     (){ return (getIsEditCtrlPosiRestrictionMin     () || getErrCtrlPosiRestrictionMin     () ); }
    bool IsNeedWriteAutoControllerSelectEnable (){ return (getIsEditAutoControllerSelectEnable () || getErrAutoControllerSelectEnable () ); }
    bool IsNeedWriteAutoControllerSelectMode   (){ return (getIsEditAutoControllerSelectMode   () || getErrAutoControllerSelectMode   () ); }
    bool IsNeedWriteAutoControllerPresRising   (){ return (getIsEditAutoControllerPresRising   () || getErrAutoControllerPresRising   () ); }
    bool IsNeedWriteAutoControllerPresFalling  (){ return (getIsEditAutoControllerPresFalling  () || getErrAutoControllerPresFalling  () ); }
    bool IsNeedWriteAutoControllerSelectBitmap (){ return (getIsEditAutoControllerSelectBitmap () || getErrAutoControllerSelectBitmap () ); }
    bool IsNeedWriteAutoControllerThreCondition(){ return (getIsEditAutoControllerThreCondition() || getErrAutoControllerThreCondition() ); }
    bool IsNeedWriteAutoController1ThreValue   (){ return (getIsEditAutoController1ThreValue   () || getErrAutoController1ThreValue   () ); }
    bool IsNeedWriteAutoController2ThreValue   (){ return (getIsEditAutoController2ThreValue   () || getErrAutoController2ThreValue   () ); }
    bool IsNeedWriteAutoController3ThreValue   (){ return (getIsEditAutoController3ThreValue   () || getErrAutoController3ThreValue   () ); }
    bool IsNeedWriteAutoController4ThreValue   (){ return (getIsEditAutoController4ThreValue   () || getErrAutoController4ThreValue   () ); }

    void checkErrControllerSelector         (QString res){int     value = res.mid(16).toInt(); setErrControllerSelector         ( mWriteControllerSelector          != value);}
    void checkErrPresCtrlSpeed              (QString res){QString value = res.mid(16)        ; setErrPresCtrlSpeed              ( false == DoubleCmp::Equal(mWritePresCtrlSpeed, value));}
    void checkErrCtrlPosiRestrictionEnable  (QString res){int     value = res.mid(16).toInt(); setErrCtrlPosiRestrictionEnable  ( mWriteCtrlPosiRestrictionEnable   != value);}
    void checkErrCtrlPosiRestrictionMax     (QString res){QString value = res.mid(16)        ; setErrCtrlPosiRestrictionMax     ( false == DoubleCmp::Equal(mIfScaleConverter.convertToIFPosi(mWriteCtrlPosiRestrictionMax), value));}
    void checkErrCtrlPosiRestrictionMin     (QString res){QString value = res.mid(16)        ; setErrCtrlPosiRestrictionMin     ( false == DoubleCmp::Equal(mIfScaleConverter.convertToIFPosi(mWriteCtrlPosiRestrictionMin), value));}
    void checkErrAutoControllerSelectEnable (QString res){int     value = res.mid(16).toInt(); setErrAutoControllerSelectEnable ( mWriteAutoControllerSelectEnable  != value);}
    void checkErrAutoControllerSelectMode   (QString res){int     value = res.mid(16).toInt(); setErrAutoControllerSelectMode   ( mWriteAutoControllerSelectMode    != value);}
    void checkErrAutoControllerPresRising   (QString res){int     value = res.mid(16).toInt(); setErrAutoControllerPresRising   ( mWriteAutoControllerPresRising    != value);}
    void checkErrAutoControllerPresFalling  (QString res){int     value = res.mid(16).toInt(); setErrAutoControllerPresFalling  ( mWriteAutoControllerPresFalling   != value);}
    void checkErrAutoControllerSelectBitmap (QString res){int     value = res.mid(16).toInt(); setErrAutoControllerSelectBitmap ( mWriteAutoControllerSelectBitmap  != value);}
    void checkErrAutoControllerThreCondition(QString res){int     value = res.mid(16).toInt(); setErrAutoControllerThreCondition( mWriteAutoControllerThreCondition != value);}
    void checkErrAutoController1ThreValue   (QString res){QString value = res.mid(16)        ; setErrAutoController1ThreValue   ( false == DoubleCmp::Equal(mIfScaleConverter.convertToIFPres(mWriteAutoController1ThreValue), value));}
    void checkErrAutoController2ThreValue   (QString res){QString value = res.mid(16)        ; setErrAutoController2ThreValue   ( false == DoubleCmp::Equal(mIfScaleConverter.convertToIFPres(mWriteAutoController2ThreValue), value));}
    void checkErrAutoController3ThreValue   (QString res){QString value = res.mid(16)        ; setErrAutoController3ThreValue   ( false == DoubleCmp::Equal(mIfScaleConverter.convertToIFPres(mWriteAutoController3ThreValue), value));}
    void checkErrAutoController4ThreValue   (QString res){QString value = res.mid(16)        ; setErrAutoController4ThreValue   ( false == DoubleCmp::Equal(mIfScaleConverter.convertToIFPres(mWriteAutoController4ThreValue), value));}

    void setValueControllerSelector         (QString res){int     value = res.mid(16).toInt(); setControllerSelector         (value);}
    void setValuePresCtrlSpeed              (QString res){QString value = res.mid(16)        ; setPresCtrlSpeed              (value);}
    void setValueCtrlPosiRestrictionEnable  (QString res){int     value = res.mid(16).toInt(); setCtrlPosiRestrictionEnable  (value);}
    void setValueCtrlPosiRestrictionMax     (QString res){QString value = res.mid(16)        ; value = mIfScaleConverter.convertToNVMPosi(value); setCtrlPosiRestrictionMax(value);}
    void setValueCtrlPosiRestrictionMin     (QString res){QString value = res.mid(16)        ; value = mIfScaleConverter.convertToNVMPosi(value); setCtrlPosiRestrictionMin(value);}
    void setValueAutoControllerSelectEnable (QString res){int     value = res.mid(16).toInt(); setAutoControllerSelectEnable (value);}
    void setValueAutoControllerSelectMode   (QString res){int     value = res.mid(16).toInt(); setAutoControllerSelectMode   (value);}
    void setValueAutoControllerPresRising   (QString res){int     value = res.mid(16).toInt(); setAutoControllerPresRising   (value);}
    void setValueAutoControllerPresFalling  (QString res){int     value = res.mid(16).toInt(); setAutoControllerPresFalling  (value);}
    void setValueAutoControllerSelectBitmap (QString res){int     value = res.mid(16).toInt(); setAutoControllerSelectBitmap (value);}
    void setValueAutoControllerThreCondition(QString res){int     value = res.mid(16).toInt(); setAutoControllerThreCondition(value);}
    void setValueAutoController1ThreValue   (QString res){QString value = res.mid(16)        ; value = mIfScaleConverter.convertToNVMPres(value); setAutoController1ThreValue(value);}
    void setValueAutoController2ThreValue   (QString res){QString value = res.mid(16)        ; value = mIfScaleConverter.convertToNVMPres(value); setAutoController2ThreValue(value);}
    void setValueAutoController3ThreValue   (QString res){QString value = res.mid(16)        ; value = mIfScaleConverter.convertToNVMPres(value); setAutoController3ThreValue(value);}
    void setValueAutoController4ThreValue   (QString res){QString value = res.mid(16)        ; value = mIfScaleConverter.convertToNVMPres(value); setAutoController4ThreValue(value);}


    void checkTotalWriteValue()
    {
        if(mIsWritten)
        {
            setTotalEditReset();
            setIsEdit(mControllerItemList[0]->getError () ||
                      mControllerItemList[1]->getError () ||
                      mControllerItemList[2]->getError () ||
                      mControllerItemList[3]->getError () ||
                      getErrControllerSelector         () ||
                      getErrPresCtrlSpeed              () ||
                      getErrCtrlPosiRestrictionEnable  () ||
                      getErrCtrlPosiRestrictionMax     () ||
                      getErrCtrlPosiRestrictionMin     () ||
                      getErrAutoControllerSelectEnable () ||
                      getErrAutoControllerSelectMode   () ||
                      getErrAutoControllerPresRising   () ||
                      getErrAutoControllerPresFalling  () ||
                      getErrAutoControllerSelectBitmap () ||
                      getErrAutoControllerThreCondition() ||
                      getErrAutoController1ThreValue   () ||
                      getErrAutoController2ThreValue   () ||
                      getErrAutoController3ThreValue   () ||
                      getErrAutoController4ThreValue   () );
            return;
        }
    }

    void checkTotalErrState(eState state, QString res)
    {
        switch((int)state)
        {
            case (int)STATE_READ_CTRL_1_AlgorithmMode       : mControllerItemList[0]->checkErrControllerAlgorithmMode     (res); break;
            case (int)STATE_READ_CTRL_1_GainFactor          : mControllerItemList[0]->checkErrControllerGainFactor        (res); break;
            case (int)STATE_READ_CTRL_1_DeltaFactor         : mControllerItemList[0]->checkErrControllerDeltaFactor       (res); break;
            case (int)STATE_READ_CTRL_1_SensorDelay         : mControllerItemList[0]->checkErrControllerSensorDelay       (res); break;
            case (int)STATE_READ_CTRL_1_LearnDataSelection  : mControllerItemList[0]->checkErrControllerLearnDataSelection(res); break;
            case (int)STATE_READ_CTRL_1_Direction           : mControllerItemList[0]->checkErrControllerDirection         (res); break;
            case (int)STATE_READ_CTRL_1_PGainFactor         : mControllerItemList[0]->checkErrControllerPGainFactor       (res); break;
            case (int)STATE_READ_CTRL_1_IGainFactor         : mControllerItemList[0]->checkErrControllerIGainFactor       (res); break;
            case (int)STATE_READ_CTRL_1_PressureScaler      : mControllerItemList[0]->checkErrControllerPressureScaler    (res); break;
            case (int)STATE_READ_CTRL_1_RampEnable          : mControllerItemList[0]->checkErrControllerRampEnable        (res); break;
            case (int)STATE_READ_CTRL_1_RampTime            : mControllerItemList[0]->checkErrControllerRampTime          (res); break;
            case (int)STATE_READ_CTRL_1_RampSlope           : mControllerItemList[0]->checkErrControllerRampSlope         (res); break;
            case (int)STATE_READ_CTRL_1_RampMode            : mControllerItemList[0]->checkErrControllerRampMode          (res); break;
            case (int)STATE_READ_CTRL_1_RampStartValue      : mControllerItemList[0]->checkErrControllerRampStartValue    (res); break;
            case (int)STATE_READ_CTRL_1_RampType            : mControllerItemList[0]->checkErrControllerRampType          (res); break;
            case (int)STATE_READ_CTRL_2_AlgorithmMode       : mControllerItemList[1]->checkErrControllerAlgorithmMode     (res); break;
            case (int)STATE_READ_CTRL_2_GainFactor          : mControllerItemList[1]->checkErrControllerGainFactor        (res); break;
            case (int)STATE_READ_CTRL_2_DeltaFactor         : mControllerItemList[1]->checkErrControllerDeltaFactor       (res); break;
            case (int)STATE_READ_CTRL_2_SensorDelay         : mControllerItemList[1]->checkErrControllerSensorDelay       (res); break;
            case (int)STATE_READ_CTRL_2_LearnDataSelection  : mControllerItemList[1]->checkErrControllerLearnDataSelection(res); break;
            case (int)STATE_READ_CTRL_2_Direction           : mControllerItemList[1]->checkErrControllerDirection         (res); break;
            case (int)STATE_READ_CTRL_2_PGainFactor         : mControllerItemList[1]->checkErrControllerPGainFactor       (res); break;
            case (int)STATE_READ_CTRL_2_IGainFactor         : mControllerItemList[1]->checkErrControllerIGainFactor       (res); break;
            case (int)STATE_READ_CTRL_2_PressureScaler      : mControllerItemList[1]->checkErrControllerPressureScaler    (res); break;
            case (int)STATE_READ_CTRL_2_RampEnable          : mControllerItemList[1]->checkErrControllerRampEnable        (res); break;
            case (int)STATE_READ_CTRL_2_RampTime            : mControllerItemList[1]->checkErrControllerRampTime          (res); break;
            case (int)STATE_READ_CTRL_2_RampSlope           : mControllerItemList[1]->checkErrControllerRampSlope         (res); break;
            case (int)STATE_READ_CTRL_2_RampMode            : mControllerItemList[1]->checkErrControllerRampMode          (res); break;
            case (int)STATE_READ_CTRL_2_RampStartValue      : mControllerItemList[1]->checkErrControllerRampStartValue    (res); break;
            case (int)STATE_READ_CTRL_2_RampType            : mControllerItemList[1]->checkErrControllerRampType          (res); break;
            case (int)STATE_READ_CTRL_3_AlgorithmMode       : mControllerItemList[2]->checkErrControllerAlgorithmMode     (res);break;
            case (int)STATE_READ_CTRL_3_GainFactor          : mControllerItemList[2]->checkErrControllerGainFactor        (res);break;
            case (int)STATE_READ_CTRL_3_DeltaFactor         : mControllerItemList[2]->checkErrControllerDeltaFactor       (res);break;
            case (int)STATE_READ_CTRL_3_SensorDelay         : mControllerItemList[2]->checkErrControllerSensorDelay       (res);break;
            case (int)STATE_READ_CTRL_3_LearnDataSelection  : mControllerItemList[2]->checkErrControllerLearnDataSelection(res);break;
            case (int)STATE_READ_CTRL_3_Direction           : mControllerItemList[2]->checkErrControllerDirection         (res);break;
            case (int)STATE_READ_CTRL_3_PGainFactor         : mControllerItemList[2]->checkErrControllerPGainFactor       (res);break;
            case (int)STATE_READ_CTRL_3_IGainFactor         : mControllerItemList[2]->checkErrControllerIGainFactor       (res);break;
            case (int)STATE_READ_CTRL_3_PressureScaler      : mControllerItemList[2]->checkErrControllerPressureScaler    (res);break;
            case (int)STATE_READ_CTRL_3_RampEnable          : mControllerItemList[2]->checkErrControllerRampEnable        (res);break;
            case (int)STATE_READ_CTRL_3_RampTime            : mControllerItemList[2]->checkErrControllerRampTime          (res);break;
            case (int)STATE_READ_CTRL_3_RampSlope           : mControllerItemList[2]->checkErrControllerRampSlope         (res);break;
            case (int)STATE_READ_CTRL_3_RampMode            : mControllerItemList[2]->checkErrControllerRampMode          (res);break;
            case (int)STATE_READ_CTRL_3_RampStartValue      : mControllerItemList[2]->checkErrControllerRampStartValue    (res);break;
            case (int)STATE_READ_CTRL_3_RampType            : mControllerItemList[2]->checkErrControllerRampType          (res);break;
            case (int)STATE_READ_CTRL_4_AlgorithmMode       : mControllerItemList[3]->checkErrControllerAlgorithmMode     (res);break;
            case (int)STATE_READ_CTRL_4_GainFactor          : mControllerItemList[3]->checkErrControllerGainFactor        (res);break;
            case (int)STATE_READ_CTRL_4_DeltaFactor         : mControllerItemList[3]->checkErrControllerDeltaFactor       (res);break;
            case (int)STATE_READ_CTRL_4_SensorDelay         : mControllerItemList[3]->checkErrControllerSensorDelay       (res);break;
            case (int)STATE_READ_CTRL_4_LearnDataSelection  : mControllerItemList[3]->checkErrControllerLearnDataSelection(res);break;
            case (int)STATE_READ_CTRL_4_Direction           : mControllerItemList[3]->checkErrControllerDirection         (res);break;
            case (int)STATE_READ_CTRL_4_PGainFactor         : mControllerItemList[3]->checkErrControllerPGainFactor       (res);break;
            case (int)STATE_READ_CTRL_4_IGainFactor         : mControllerItemList[3]->checkErrControllerIGainFactor       (res);break;
            case (int)STATE_READ_CTRL_4_PressureScaler      : mControllerItemList[3]->checkErrControllerPressureScaler    (res);break;
            case (int)STATE_READ_CTRL_4_RampEnable          : mControllerItemList[3]->checkErrControllerRampEnable        (res);break;
            case (int)STATE_READ_CTRL_4_RampTime            : mControllerItemList[3]->checkErrControllerRampTime          (res);break;
            case (int)STATE_READ_CTRL_4_RampSlope           : mControllerItemList[3]->checkErrControllerRampSlope         (res);break;
            case (int)STATE_READ_CTRL_4_RampMode            : mControllerItemList[3]->checkErrControllerRampMode          (res);break;
            case (int)STATE_READ_CTRL_4_RampStartValue      : mControllerItemList[3]->checkErrControllerRampStartValue    (res);break;
            case (int)STATE_READ_CTRL_4_RampType            : mControllerItemList[3]->checkErrControllerRampType          (res);break;
            case (int)STATE_READ_CTRL_SELECTOR              : checkErrControllerSelector         (res); break;
            case (int)STATE_READ_PRES_CTRL_SPEED            : checkErrPresCtrlSpeed              (res); break;
            case (int)STATE_READ_POSI_RESTRICTION_ENABLE    : checkErrCtrlPosiRestrictionEnable  (res); break;
            case (int)STATE_READ_POSI_RESTRICTION_MAX       : checkErrCtrlPosiRestrictionMax     (res); break;
            case (int)STATE_READ_POSI_RESTRICTION_MIN       : checkErrCtrlPosiRestrictionMin     (res); break;
            case (int)STATE_READ_AUTO_SEL_ENABLE            : checkErrAutoControllerSelectEnable (res); break;
            case (int)STATE_READ_AUTO_SEL_MODE              : checkErrAutoControllerSelectMode   (res); break;
            case (int)STATE_READ_AUTO_PRES_RISING           : checkErrAutoControllerPresRising   (res); break;
            case (int)STATE_READ_AUTO_PRES_FALLING          : checkErrAutoControllerPresFalling  (res); break;
            case (int)STATE_READ_AUTO_SEL_BITMAP            : checkErrAutoControllerSelectBitmap (res); break;
            case (int)STATE_READ_AUTO_TRES_CONDITION        : checkErrAutoControllerThreCondition(res); break;
            case (int)STATE_READ_AUTO_THRES_1               : checkErrAutoController1ThreValue   (res); break;
            case (int)STATE_READ_AUTO_THRES_2               : checkErrAutoController2ThreValue   (res); break;
            case (int)STATE_READ_AUTO_THRES_3               : checkErrAutoController3ThreValue   (res); break;
            case (int)STATE_READ_AUTO_THRES_4               : checkErrAutoController4ThreValue   (res); break;
        }
    }

    void setTotalValue(eState state, QString res)
    {
        switch((int)state)
        {
            case (int)STATE_READ_CTRL_1_AlgorithmMode       : mControllerItemList[0]->setValueControllerAlgorithmMode     (res);break;
            case (int)STATE_READ_CTRL_1_GainFactor          : mControllerItemList[0]->setValueControllerGainFactor        (res);break;
            case (int)STATE_READ_CTRL_1_DeltaFactor         : mControllerItemList[0]->setValueControllerDeltaFactor       (res);break;
            case (int)STATE_READ_CTRL_1_SensorDelay         : mControllerItemList[0]->setValueControllerSensorDelay       (res);break;
            case (int)STATE_READ_CTRL_1_LearnDataSelection  : mControllerItemList[0]->setValueControllerLearnDataSelection(res);break;
            case (int)STATE_READ_CTRL_1_Direction           : mControllerItemList[0]->setValueControllerDirection         (res);break;
            case (int)STATE_READ_CTRL_1_PGainFactor         : mControllerItemList[0]->setValueControllerPGainFactor       (res);break;
            case (int)STATE_READ_CTRL_1_IGainFactor         : mControllerItemList[0]->setValueControllerIGainFactor       (res);break;
            case (int)STATE_READ_CTRL_1_PressureScaler      : mControllerItemList[0]->setValueControllerPressureScaler    (res);break;
            case (int)STATE_READ_CTRL_1_RampEnable          : mControllerItemList[0]->setValueControllerRampEnable        (res);break;
            case (int)STATE_READ_CTRL_1_RampTime            : mControllerItemList[0]->setValueControllerRampTime          (res);break;
            case (int)STATE_READ_CTRL_1_RampSlope           : mControllerItemList[0]->setValueControllerRampSlope         (res);break;
            case (int)STATE_READ_CTRL_1_RampMode            : mControllerItemList[0]->setValueControllerRampMode          (res);break;
            case (int)STATE_READ_CTRL_1_RampStartValue      : mControllerItemList[0]->setValueControllerRampStartValue    (res);break;
            case (int)STATE_READ_CTRL_1_RampType            : mControllerItemList[0]->setValueControllerRampType          (res);break;
            case (int)STATE_READ_CTRL_2_AlgorithmMode       : mControllerItemList[1]->setValueControllerAlgorithmMode     (res);break;
            case (int)STATE_READ_CTRL_2_GainFactor          : mControllerItemList[1]->setValueControllerGainFactor        (res);break;
            case (int)STATE_READ_CTRL_2_DeltaFactor         : mControllerItemList[1]->setValueControllerDeltaFactor       (res);break;
            case (int)STATE_READ_CTRL_2_SensorDelay         : mControllerItemList[1]->setValueControllerSensorDelay       (res);break;
            case (int)STATE_READ_CTRL_2_LearnDataSelection  : mControllerItemList[1]->setValueControllerLearnDataSelection(res);break;
            case (int)STATE_READ_CTRL_2_Direction           : mControllerItemList[1]->setValueControllerDirection         (res);break;
            case (int)STATE_READ_CTRL_2_PGainFactor         : mControllerItemList[1]->setValueControllerPGainFactor       (res);break;
            case (int)STATE_READ_CTRL_2_IGainFactor         : mControllerItemList[1]->setValueControllerIGainFactor       (res);break;
            case (int)STATE_READ_CTRL_2_PressureScaler      : mControllerItemList[1]->setValueControllerPressureScaler    (res);break;
            case (int)STATE_READ_CTRL_2_RampEnable          : mControllerItemList[1]->setValueControllerRampEnable        (res);break;
            case (int)STATE_READ_CTRL_2_RampTime            : mControllerItemList[1]->setValueControllerRampTime          (res);break;
            case (int)STATE_READ_CTRL_2_RampSlope           : mControllerItemList[1]->setValueControllerRampSlope         (res);break;
            case (int)STATE_READ_CTRL_2_RampMode            : mControllerItemList[1]->setValueControllerRampMode          (res);break;
            case (int)STATE_READ_CTRL_2_RampStartValue      : mControllerItemList[1]->setValueControllerRampStartValue    (res);break;
            case (int)STATE_READ_CTRL_2_RampType            : mControllerItemList[1]->setValueControllerRampType          (res);break;
            case (int)STATE_READ_CTRL_3_AlgorithmMode       : mControllerItemList[2]->setValueControllerAlgorithmMode     (res);break;
            case (int)STATE_READ_CTRL_3_GainFactor          : mControllerItemList[2]->setValueControllerGainFactor        (res);break;
            case (int)STATE_READ_CTRL_3_DeltaFactor         : mControllerItemList[2]->setValueControllerDeltaFactor       (res);break;
            case (int)STATE_READ_CTRL_3_SensorDelay         : mControllerItemList[2]->setValueControllerSensorDelay       (res);break;
            case (int)STATE_READ_CTRL_3_LearnDataSelection  : mControllerItemList[2]->setValueControllerLearnDataSelection(res);break;
            case (int)STATE_READ_CTRL_3_Direction           : mControllerItemList[2]->setValueControllerDirection         (res);break;
            case (int)STATE_READ_CTRL_3_PGainFactor         : mControllerItemList[2]->setValueControllerPGainFactor       (res);break;
            case (int)STATE_READ_CTRL_3_IGainFactor         : mControllerItemList[2]->setValueControllerIGainFactor       (res);break;
            case (int)STATE_READ_CTRL_3_PressureScaler      : mControllerItemList[2]->setValueControllerPressureScaler    (res);break;
            case (int)STATE_READ_CTRL_3_RampEnable          : mControllerItemList[2]->setValueControllerRampEnable        (res);break;
            case (int)STATE_READ_CTRL_3_RampTime            : mControllerItemList[2]->setValueControllerRampTime          (res);break;
            case (int)STATE_READ_CTRL_3_RampSlope           : mControllerItemList[2]->setValueControllerRampSlope         (res);break;
            case (int)STATE_READ_CTRL_3_RampMode            : mControllerItemList[2]->setValueControllerRampMode          (res);break;
            case (int)STATE_READ_CTRL_3_RampStartValue      : mControllerItemList[2]->setValueControllerRampStartValue    (res);break;
            case (int)STATE_READ_CTRL_3_RampType            : mControllerItemList[2]->setValueControllerRampType          (res);break;
            case (int)STATE_READ_CTRL_4_AlgorithmMode       : mControllerItemList[3]->setValueControllerAlgorithmMode     (res);break;
            case (int)STATE_READ_CTRL_4_GainFactor          : mControllerItemList[3]->setValueControllerGainFactor        (res);break;
            case (int)STATE_READ_CTRL_4_DeltaFactor         : mControllerItemList[3]->setValueControllerDeltaFactor       (res);break;
            case (int)STATE_READ_CTRL_4_SensorDelay         : mControllerItemList[3]->setValueControllerSensorDelay       (res);break;
            case (int)STATE_READ_CTRL_4_LearnDataSelection  : mControllerItemList[3]->setValueControllerLearnDataSelection(res);break;
            case (int)STATE_READ_CTRL_4_Direction           : mControllerItemList[3]->setValueControllerDirection         (res);break;
            case (int)STATE_READ_CTRL_4_PGainFactor         : mControllerItemList[3]->setValueControllerPGainFactor       (res);break;
            case (int)STATE_READ_CTRL_4_IGainFactor         : mControllerItemList[3]->setValueControllerIGainFactor       (res);break;
            case (int)STATE_READ_CTRL_4_PressureScaler      : mControllerItemList[3]->setValueControllerPressureScaler    (res);break;
            case (int)STATE_READ_CTRL_4_RampEnable          : mControllerItemList[3]->setValueControllerRampEnable        (res);break;
            case (int)STATE_READ_CTRL_4_RampTime            : mControllerItemList[3]->setValueControllerRampTime          (res);break;
            case (int)STATE_READ_CTRL_4_RampSlope           : mControllerItemList[3]->setValueControllerRampSlope         (res);break;
            case (int)STATE_READ_CTRL_4_RampMode            : mControllerItemList[3]->setValueControllerRampMode          (res);break;
            case (int)STATE_READ_CTRL_4_RampStartValue      : mControllerItemList[3]->setValueControllerRampStartValue    (res);break;
            case (int)STATE_READ_CTRL_4_RampType            : mControllerItemList[3]->setValueControllerRampType          (res);break;
            case (int)STATE_READ_CTRL_SELECTOR              : setValueControllerSelector         (res); break;
            case (int)STATE_READ_PRES_CTRL_SPEED            : setValuePresCtrlSpeed              (res); break;
            case (int)STATE_READ_POSI_RESTRICTION_ENABLE    : setValueCtrlPosiRestrictionEnable  (res); break;
            case (int)STATE_READ_POSI_RESTRICTION_MAX       : setValueCtrlPosiRestrictionMax     (res); break;
            case (int)STATE_READ_POSI_RESTRICTION_MIN       : setValueCtrlPosiRestrictionMin     (res); break;
            case (int)STATE_READ_AUTO_SEL_ENABLE            : setValueAutoControllerSelectEnable (res); break;
            case (int)STATE_READ_AUTO_SEL_MODE              : setValueAutoControllerSelectMode   (res); break;
            case (int)STATE_READ_AUTO_PRES_RISING           : setValueAutoControllerPresRising   (res); break;
            case (int)STATE_READ_AUTO_PRES_FALLING          : setValueAutoControllerPresFalling  (res); break;
            case (int)STATE_READ_AUTO_SEL_BITMAP            : setValueAutoControllerSelectBitmap (res); break;
            case (int)STATE_READ_AUTO_TRES_CONDITION        : setValueAutoControllerThreCondition(res); break;
            case (int)STATE_READ_AUTO_THRES_1               : setValueAutoController1ThreValue   (res); break;
            case (int)STATE_READ_AUTO_THRES_2               : setValueAutoController2ThreValue   (res); break;
            case (int)STATE_READ_AUTO_THRES_3               : setValueAutoController3ThreValue   (res); break;
            case (int)STATE_READ_AUTO_THRES_4               : setValueAutoController4ThreValue   (res); break;
        }
    }

    void setTotalEditReset()
    {
        mControllerItemList[0]->setIsEditReset();
        mControllerItemList[1]->setIsEditReset();
        mControllerItemList[2]->setIsEditReset();
        mControllerItemList[3]->setIsEditReset();

        setIsEditControllerSelector         (false);
        setIsEditPresCtrlSpeed              (false);
        setIsEditCtrlPosiRestrictionEnable  (false);
        setIsEditCtrlPosiRestrictionMax     (false);
        setIsEditCtrlPosiRestrictionMin     (false);
        setIsEditAutoControllerSelectEnable (false);
        setIsEditAutoControllerSelectMode   (false);
        setIsEditAutoControllerPresRising   (false);
        setIsEditAutoControllerPresFalling  (false);
        setIsEditAutoControllerSelectBitmap (false);
        setIsEditAutoControllerThreCondition(false);
        setIsEditAutoController1ThreValue   (false);
        setIsEditAutoController2ThreValue   (false);
        setIsEditAutoController3ThreValue   (false);
        setIsEditAutoController4ThreValue   (false);

        setIsEdit(false);
    }
};
#endif // PRESSURECTRLFORPMPROTODLGMODEL_H
