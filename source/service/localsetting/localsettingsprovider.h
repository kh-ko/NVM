#ifndef LOCALSETTINGSPROVIDER_H
#define LOCALSETTINGSPROVIDER_H

#include <QObject>
#include <QDebug>
#include <QDateTime>
#include <QSettings>
#include <QTimer>

#include "source/service/util/exceptionutil.h"
#include "source/service/util/unitutil.h"

#define pLSettingSP LocalSettingSProvider::getInstance()

#define ENABLE_SLOT_LSETTING_START                           connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventStarted                     ()), this, SLOT(onLSettingStartedService              ()))
#define ENABLE_SLOT_LSETTING_STOP                            connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventStopped                     ()), this, SLOT(onLSettingStoppedService              ()))
#define ENABLE_SLOT_LSETTING_CHANGED_MONITORING_CYCLE        connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedMonitoringCycle      ()), this, SLOT(onLSettingChangedMonitoringCycle      ()))
#define ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_CURR_POS        connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedIsDrawCurrPos        ()), this, SLOT(onLSettingChangedIsDrawCurrPos        ()))
#define ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_TARGET_POS      connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedIsDrawTargetPos      ()), this, SLOT(onLSettingChangedIsDrawTargetPos      ()))
#define ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_CURR_PRESSURE   connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedIsDrawCurrPressure   ()), this, SLOT(onLSettingChangedIsDrawCurrPressure   ()))
#define ENABLE_SLOT_LSETTING_CHANGED_IS_DRAW_TARGET_PRESSURE connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedIsDrawTargetPressure ()), this, SLOT(onLSettingChangedIsDrawTargetPressure ()))
#define ENABLE_SLOT_LSETTING_CHANGED_IS_AUTOSCALE_POS        connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedIsAutoScalePos       ()), this, SLOT(onLSettingChangedIsAutoScalePos       ()))
#define ENABLE_SLOT_LSETTING_CHANGED_IS_AUTOSCALE_PRESSURE   connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedIsAutoScalePressure  ()), this, SLOT(onLSettingChangedIsAutoScalePressure  ()))
#define ENABLE_SLOT_LSETTING_CHANGED_CHART_MSEC              connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedChartMSec            ()), this, SLOT(onLSettingChangedChartMSec            ()))
//#define ENABLE_SLOT_LSETTING_CHANGED_MIN_PRESSURE_CHART      connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedMinMainPressureChart ()), this, SLOT(onLSettingChangedMinMainPressureChart ()))
//#define ENABLE_SLOT_LSETTING_CHANGED_MAX_PRESSURE_CHART      connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedMaxMainPressureChart ()), this, SLOT(onLSettingChangedMaxMainPressureChart ()))
#define ENABLE_SLOT_LSETTING_CHANGED_USER_PRESSURE_FIXED_N   connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedUserPressureFixedN   ()), this, SLOT(onLSettingChangedUserPressureFixedN   ()))
#define ENABLE_SLOT_LSETTING_CHANGED_AUTOSCALE_MIN_MARGIN    connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedAutoScaleMinMargin   ()), this, SLOT(onLSettingChangedAutoScaleMinMargin   ()))
#define ENABLE_SLOT_LSETTING_CHANGED_SEQ_PERFORMED_CNT       connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedSequencerPerformedCnt()), this, SLOT(onLSettingChangedSequencerPerformedCnt()))
#define ENABLE_SLOT_LSETTING_CHANGED_DEV_MODE_IS_ON          connect(LocalSettingSProvider::getInstance(), SIGNAL(signalEventChangedDevModeIsOn          ()), this, SLOT(onLSettingChangedDevModeIsOn          ()))

class LocalSettingSProvider : public QObject
{
    Q_OBJECT

private:
    const QString mBuildVersionKey          = "build/version"                  ;
    const QString mMonitoringCycleKey       = "monitoring/monitoring_cycle"    ;

    const QString mIsDrawCurrPosKey         = "display/is_draw_curr_pos"       ;
    const QString mIsDrawTargetPosKey       = "display/is_draw_target_pos"     ;
    const QString mIsDrawCurrPressureKey    = "display/is_draw_curr_pressure"  ;
    const QString mIsDrawTargetPressureKey  = "display/is_draw_target_pressure";
    const QString mIsAutoScalePosKey        = "display/is_auto_scale_posKey"   ;
    const QString mIsAutoScalePressureKey   = "display/is_auto_scale_pressure" ;
    //const QString mMinMainPressureChartKey  = "display/min_pressure_chart"     ;
    //const QString mMaxMainPressureChartKey  = "display/max_pressure_chart"     ;
    const QString mUserPressureFixedNKey    = "display/user_pressure_percision";
    const QString mAutoScaleMinMarginKey    = "display/auto_scale_min_margin"  ;
    const QString mChartMSecKey             = "display/chart_msec"             ;
    const QString mSequencerPerformedCntKey = "sequencer/performedcounter"     ;
    const QString mDevModeIsOnKey           = "dev/is_on"                      ;

public:
    static LocalSettingSProvider * getInstance()
    {
        static LocalSettingSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new LocalSettingSProvider();
        }

        return mpSelf;
    }

    QList<int> mChartMSecOption = {30000, 60000, 120000, 300000};

    qint64  mMonitoringCycle       = 10;
    QString mBuildVersion          = "1.9.52";
    bool    mIsWithoutLogo         = true;

    bool    mIsDrawCurrPos         = true ;
    bool    mIsDrawTargetPos       = true ;
    bool    mIsDrawCurrPressure    = true ;
    bool    mIsDrawTargetPressure  = true ;
    bool    mIsAutoScalePos        = false;
    bool    mIsAutoScalePressure   = false;
    qint64  mChartMSec             = 30000;
    //double  mMinMainPressureChart  = 0;
    //double  mMaxMainPressureChart  = 0;
    int     mUserPressureFixedN    = 0;
    double  mAutoScaleMinMargin    = 0.1f;
    qint64  mSequencerPerformedCnt = 0;
    bool    mDevModeIsOn           = false;

    explicit LocalSettingSProvider(QObject * parent = nullptr):QObject(parent)
    {
        qDebug() << "[LocalSettingSProvider]Create";

        mpSetting = new QSettings("novasen", "NCAP", this);
    }
    ~LocalSettingSProvider()
    {
        qDebug() << "[LocalSettingSProvider]Destruction";
    }

    void start()
    {
        qDebug() << "[LocalSettingSProvider][start]";
        load();

        mIsRunning = true;
        emit signalEventStarted();
    }

    void stop()
    {
        qDebug() << "[LocalSettingSProvider][stop]";

        mIsRunning = false;
        emit signalEventStopped();
    }

    void setMonitoringCycle      (qint64 value){ CHECK_FALSE_RETURN(mIsRunning); internalSetMonitoringCycle      (value); emit signalEventChangedMonitoringCycle      ();}
    void setIsDrawCurrPos        (bool   value){ CHECK_FALSE_RETURN(mIsRunning); internalSetIsDrawCurrPos        (value); emit signalEventChangedIsDrawCurrPos        ();}
    void setIsDrawTargetPos      (bool   value){ CHECK_FALSE_RETURN(mIsRunning); internalSetIsDrawTargetPos      (value); emit signalEventChangedIsDrawTargetPos      ();}
    void setIsDrawCurrPressure   (bool   value){ CHECK_FALSE_RETURN(mIsRunning); internalSetIsDrawCurrPressure   (value); emit signalEventChangedIsDrawCurrPressure   ();}
    void setIsDrawTargetPressure (bool   value){ CHECK_FALSE_RETURN(mIsRunning); internalSetIsDrawTargetPressure (value); emit signalEventChangedIsDrawTargetPressure ();}
    void setIsAutoScalePos       (bool   value){ CHECK_FALSE_RETURN(mIsRunning); internalSetIsAutoScalePos       (value); emit signalEventChangedIsAutoScalePos       ();}
    void setIsAutoScalePressure  (bool   value){ CHECK_FALSE_RETURN(mIsRunning); internalSetIsAutoScalePressure  (value); emit signalEventChangedIsAutoScalePressure  ();}
    void setChartMSec            (qint64 value){ CHECK_FALSE_RETURN(mIsRunning); internalSetChartMSec            (value); emit signalEventChangedChartMSec            ();}
    //void setMinMainPressureChart (double value){ CHECK_FALSE_RETURN(mIsRunning); internalMinMainPressureChart    (value); emit signalEventChangedMinMainPressureChart ();}
    //void setMaxMainPressureChart (double value){ CHECK_FALSE_RETURN(mIsRunning); internalMaxMainPressureChart    (value); emit signalEventChangedMaxMainPressureChart ();}
    void setUserPressureFixedN   (int    value){ CHECK_FALSE_RETURN(mIsRunning); internalUserPressureFixedN      (value); emit signalEventChangedUserPressureFixedN   ();}
    void setAutoScaleMinMargin   (double value){ CHECK_FALSE_RETURN(mIsRunning); internalAutoScaleMinMargin      (value); emit signalEventChangedAutoScaleMinMargin   ();}
    void setSequencerPerformedCnt(qint64 value){ CHECK_FALSE_RETURN(mIsRunning); internalSetSequencerPerformedCnt(value); emit signalEventChangedSequencerPerformedCnt();}
    void setDevModeIsOn          (bool   value){ CHECK_FALSE_RETURN(mIsRunning); internalSetDevModeIsOn          (value); emit signalEventChangedDevModeIsOn          ();}

    qint64 convertChartMSecIdxToValue(int idx)
    {
        if(idx >= mChartMSecOption.count())
            return mChartMSecOption[0];

        return mChartMSecOption[idx];
    }

    int convertChartMSecValueToIdx(int value)
    {
        for(int i = 0; i < mChartMSecOption.count(); i++ )
        {
            if(mChartMSecOption[i] == value)
                return i;
        }
        return 0;
    }

private:
    QTimer         mLanguageLoadTimer;
    QObject      * mpContext = nullptr;
    QSettings    * mpSetting   = nullptr;
    bool           mIsRunning  = false;

    void load()
    {
        QString oldVersion = "";
        qDebug() << "[LocalSettingSProvider::load]";

        oldVersion = mpSetting->value(mBuildVersionKey, mBuildVersion).toString();
        mpSetting->setValue(mBuildVersionKey, mBuildVersion);

        mMonitoringCycle       = mpSetting->value(mMonitoringCycleKey      , 10   ).toLongLong();
        mIsDrawCurrPos         = mpSetting->value(mIsDrawCurrPosKey        , true ).toBool()    ;
        mIsDrawTargetPos       = mpSetting->value(mIsDrawTargetPosKey      , true ).toBool()    ;
        mIsDrawCurrPressure    = mpSetting->value(mIsDrawCurrPressureKey   , true ).toBool()    ;
        mIsDrawTargetPressure  = mpSetting->value(mIsDrawTargetPressureKey , true ).toBool()    ;
        mIsAutoScalePos        = mpSetting->value(mIsAutoScalePosKey       , false).toBool()    ;
        mIsAutoScalePressure   = mpSetting->value(mIsAutoScalePressureKey  , false).toBool()    ;
        mChartMSec             = mpSetting->value(mChartMSecKey            , 30000).toLongLong();
        //mMinMainPressureChart  = mpSetting->value(mMinMainPressureChartKey , 0    ).toDouble()  ;
        //mMaxMainPressureChart  = mpSetting->value(mMaxMainPressureChartKey , 0    ).toDouble()  ;
        mUserPressureFixedN    = mpSetting->value(mUserPressureFixedNKey   , 0    ).toUInt()    ;
        mAutoScaleMinMargin    = mpSetting->value(mAutoScaleMinMarginKey   , 0.1  ).toDouble()  ;
        mSequencerPerformedCnt = mpSetting->value(mSequencerPerformedCntKey, 0    ).toLongLong();
        mDevModeIsOn           = mpSetting->value(mDevModeIsOnKey          , false).toBool()    ;

        internalSetMonitoringCycle      (mMonitoringCycle      );
        internalSetIsDrawCurrPos        (mIsDrawCurrPos        );
        internalSetIsDrawTargetPos      (mIsDrawTargetPos      );
        internalSetIsDrawCurrPressure   (mIsDrawCurrPressure   );
        internalSetIsDrawTargetPressure (mIsDrawTargetPressure );
        internalSetIsAutoScalePos       (mIsAutoScalePos       );
        internalSetIsAutoScalePressure  (mIsAutoScalePressure  );
        internalSetChartMSec            (mChartMSec            );
        //internalMinMainPressureChart    (mMinMainPressureChart );
        //internalMaxMainPressureChart    (mMaxMainPressureChart );
        internalUserPressureFixedN      (mUserPressureFixedN   );
        internalAutoScaleMinMargin      (mAutoScaleMinMargin   );
        internalSetSequencerPerformedCnt(mSequencerPerformedCnt);
        internalSetDevModeIsOn          (mDevModeIsOn          );
    }

    void internalSetMonitoringCycle      (qint64 value){ mMonitoringCycle       = value; mpSetting->setValue(mMonitoringCycleKey      , value);}
    void internalSetIsDrawCurrPos        (bool   value){ mIsDrawCurrPos         = value; mpSetting->setValue(mIsDrawCurrPosKey        , value);}
    void internalSetIsDrawTargetPos      (bool   value){ mIsDrawTargetPos       = value; mpSetting->setValue(mIsDrawTargetPosKey      , value);}
    void internalSetIsDrawCurrPressure   (bool   value){ mIsDrawCurrPressure    = value; mpSetting->setValue(mIsDrawCurrPressureKey   , value);}
    void internalSetIsDrawTargetPressure (bool   value){ mIsDrawTargetPressure  = value; mpSetting->setValue(mIsDrawTargetPressureKey , value);}
    void internalSetIsAutoScalePos       (bool   value){ mIsAutoScalePos        = value; mpSetting->setValue(mIsAutoScalePosKey       , value);}
    void internalSetIsAutoScalePressure  (bool   value){ mIsAutoScalePressure   = value; mpSetting->setValue(mIsAutoScalePressureKey  , value);}
    void internalSetChartMSec            (qint64 value){ mChartMSec             = value; mpSetting->setValue(mChartMSecKey            , value);}
    //void internalMinMainPressureChart    (double value){ mMinMainPressureChart  = value; mpSetting->setValue(mMinMainPressureChartKey , value);}
    //void internalMaxMainPressureChart    (double value){ mMaxMainPressureChart  = value; mpSetting->setValue(mMaxMainPressureChartKey , value);}
    void internalUserPressureFixedN      (int    value){ mUserPressureFixedN    = value; mpSetting->setValue(mUserPressureFixedNKey   , value);}
    void internalAutoScaleMinMargin      (double value){ mAutoScaleMinMargin    = value; mpSetting->setValue(mAutoScaleMinMarginKey   , value);}
    void internalSetSequencerPerformedCnt(qint64 value){ mSequencerPerformedCnt = value; mpSetting->setValue(mSequencerPerformedCntKey, value);}
    void internalSetDevModeIsOn          (bool   value){ mDevModeIsOn           = value; mpSetting->setValue(mDevModeIsOnKey          , value);}

signals:
    void signalEventStarted                     ();
    void signalEventStopped                     ();
    void signalEventChangedMonitoringCycle      ();
    void signalEventChangedIsDrawCurrPos        ();
    void signalEventChangedIsDrawTargetPos      ();
    void signalEventChangedIsDrawCurrPressure   ();
    void signalEventChangedIsDrawTargetPressure ();
    void signalEventChangedIsAutoScalePos       ();
    void signalEventChangedIsAutoScalePressure  ();
    void signalEventChangedChartMSec            ();
    //void signalEventChangedMinMainPressureChart ();
    //void signalEventChangedMaxMainPressureChart ();
    void signalEventChangedUserPressureFixedN   ();
    void signalEventChangedAutoScaleMinMargin   ();
    void signalEventChangedSequencerPerformedCnt();
    void signalEventChangedDevModeIsOn          ();
};
#endif // LOCALSETTINGSPROVIDER_H
