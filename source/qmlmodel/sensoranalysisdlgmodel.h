#ifndef SENSORANALYSISDLGMODEL_H
#define SENSORANALYSISDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/mathutil.h"
#include "source/service/coreservice.h"


class SensorAnalysisDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mAccessMode            READ getAccessMode            NOTIFY signalEventChangedAccessMode           )
    Q_PROPERTY(bool    mIsRS232Test           READ getIsRS232Test           NOTIFY signalEventChangedIsRS232Test          )
    Q_PROPERTY(bool    mIsSensor02Support     READ getIsSensor02Support     NOTIFY signalEventChangedIsSensor02Support    )
    Q_PROPERTY(bool    mIsS01HighSensor       READ getIsS01HighSensor       NOTIFY signalEventChangedIsS01HighSensor      )
    Q_PROPERTY(bool    mIsEnableZero          READ getIsEnableZero          NOTIFY signalEventChangedIsEnableZero         )
    Q_PROPERTY(double  mSensorFactor          READ getSensorFactor          NOTIFY signalEventChangedSensorFactor         )
    Q_PROPERTY(double  mResultingOriPressure  READ getResultingOriPressure  NOTIFY signalEventChangedResultingOriPressure )
    Q_PROPERTY(QString mStrResultingPressure  READ getStrResultingPressure  NOTIFY signalEventChangedStrResultingPressure )
    Q_PROPERTY(bool    mS01Selction           READ getS01Selction           NOTIFY signalEventChangedS01Selction          )
    Q_PROPERTY(int     mS01Unit               READ getS01Unit               NOTIFY signalEventChangedS01Unit              )
    Q_PROPERTY(double  mS01FullScale          READ getS01FullScale          NOTIFY signalEventChangedS01FullScale         )
    Q_PROPERTY(double  mS01GraphConvertFactor READ getS01GraphConvertFactor NOTIFY signalEventChangedS01GraphConvertFactor)
    Q_PROPERTY(int     mS01GraphPrecN         READ getS01GraphPrecN         NOTIFY signalEventChangedS01GraphPrecN        )
    Q_PROPERTY(QString mStrS01FullScale       READ getStrS01FullScale       NOTIFY signalEventChangedStrS01FullScale      )
    Q_PROPERTY(int     mS01Exponent           READ getS01Exponent           NOTIFY signalEventChangedS01Exponent          )
    Q_PROPERTY(bool    mS01IsProcessing       READ getS01IsProcessing       NOTIFY signalEventChangedS01IsProcessing      )
    Q_PROPERTY(int     mS01ProcessingPct      READ getS01ProcessingPct      NOTIFY signalEventChangedS01ProcessingPct     )
    Q_PROPERTY(double  mS01MeasuredOriValue   READ getS01MeasuredOriValue   NOTIFY signalEventChangedS01MeasuredOriValue  )
    Q_PROPERTY(QString mStrS01MeasuredValue   READ getStrS01MeasuredValue   NOTIFY signalEventChangedStrS01MeasuredValue  )
    Q_PROPERTY(double  mS01OffsetOriValue     READ getS01OffsetOriValue     NOTIFY signalEventChangedS01OffsetOriValue    )
    Q_PROPERTY(QString mStrS01OffsetValue     READ getStrS01OffsetValue     NOTIFY signalEventChangedStrS01OffsetValue    )
    Q_PROPERTY(double  mS01OriValue           READ getS01OriValue           NOTIFY signalEventChangedS01OriValue          )
    Q_PROPERTY(QString mStrS01Value           READ getStrS01Value           NOTIFY signalEventChangedStrS01Value          )
    Q_PROPERTY(bool    mS02Selction           READ getS02Selction           NOTIFY signalEventChangedS02Selction          )
    Q_PROPERTY(int     mS02Unit               READ getS02Unit               NOTIFY signalEventChangedS02Unit              )
    Q_PROPERTY(double  mS02FullScale          READ getS02FullScale          NOTIFY signalEventChangedS02FullScale         )
    Q_PROPERTY(double  mS02GraphConvertFactor READ getS02GraphConvertFactor NOTIFY signalEventChangedS02GraphConvertFactor)
    Q_PROPERTY(int     mS02GraphPrecN         READ getS02GraphPrecN         NOTIFY signalEventChangedS02GraphPrecN        )
    Q_PROPERTY(QString mStrS02FullScale       READ getStrS02FullScale       NOTIFY signalEventChangedStrS02FullScale      )
    Q_PROPERTY(int     mS02Exponent           READ getS02Exponent           NOTIFY signalEventChangedS02Exponent          )
    Q_PROPERTY(bool    mS02IsProcessing       READ getS02IsProcessing       NOTIFY signalEventChangedS02IsProcessing      )
    Q_PROPERTY(int     mS02ProcessingPct      READ getS02ProcessingPct      NOTIFY signalEventChangedS02ProcessingPct     )
    Q_PROPERTY(double  mS02MeasuredOriValue   READ getS02MeasuredOriValue   NOTIFY signalEventChangedS02MeasuredOriValue  )
    Q_PROPERTY(QString mStrS02MeasuredValue   READ getStrS02MeasuredValue   NOTIFY signalEventChangedStrS02MeasuredValue  )
    Q_PROPERTY(double  mS02OffsetOriValue     READ getS02OffsetOriValue     NOTIFY signalEventChangedS02OffsetOriValue    )
    Q_PROPERTY(QString mStrS02OffsetValue     READ getStrS02OffsetValue     NOTIFY signalEventChangedStrS02OffsetValue    )
    Q_PROPERTY(double  mS02OriValue           READ getS02OriValue           NOTIFY signalEventChangedS02OriValue          )
    Q_PROPERTY(QString mStrS02Value           READ getStrS02Value           NOTIFY signalEventChangedStrS02Value          )
    Q_PROPERTY(int     mDpUnit                READ getDpUnit                NOTIFY signalEventChangedDpUnit               )
    Q_PROPERTY(bool    mAutoScale             READ getAutoScale             NOTIFY signalEventChangedAutoScale            )
    Q_PROPERTY(int     mPrecN                 READ getPrecN                 NOTIFY signalEventChangedPrecN                )
    Q_PROPERTY(int     mXMsec                 READ getXMsec                 NOTIFY signalEventChangedXMsec                )
    Q_PROPERTY(double  mSensor01Min           READ getSensor01Min           NOTIFY signalEventChangedSensor01Min          )
    Q_PROPERTY(double  mSensor01Max           READ getSensor01Max           NOTIFY signalEventChangedSensor01Max          )
    Q_PROPERTY(double  mSensor02Min           READ getSensor02Min           NOTIFY signalEventChangedSensor02Min          )
    Q_PROPERTY(double  mSensor02Max           READ getSensor02Max           NOTIFY signalEventChangedSensor02Max          )
    Q_PROPERTY(int     mIsEditDpUnit          READ getIsEditDpUnit          NOTIFY signalEventChangedIsEditDpUnit         )
    Q_PROPERTY(bool    mIsEditAutoScale       READ getIsEditAutoScale       NOTIFY signalEventChangedIsEditAutoScale      )
    Q_PROPERTY(int     mIsEditXMsec           READ getIsEditXMsec           NOTIFY signalEventChangedIsEditXMsec          )
    Q_PROPERTY(bool    mIsEditSensor01Min     READ getIsEditSensor01Min     NOTIFY signalEventChangedIsEditSensor01Min    )
    Q_PROPERTY(bool    mIsEditSensor01Max     READ getIsEditSensor01Max     NOTIFY signalEventChangedIsEditSensor01Max    )
    Q_PROPERTY(bool    mIsEditSensor02Min     READ getIsEditSensor02Min     NOTIFY signalEventChangedIsEditSensor02Min    )
    Q_PROPERTY(bool    mIsEditSensor02Max     READ getIsEditSensor02Max     NOTIFY signalEventChangedIsEditSensor02Max    )
    Q_PROPERTY(bool    mIsEdit                READ getIsEdit                NOTIFY signalEventChangedIsEdit               )
    Q_PROPERTY(bool    mIsErrSensor01MinMax   READ getIsErrSensor01MinMax   NOTIFY signalEventChangedIsErrSensor01MinMax  )
    Q_PROPERTY(bool    mIsErrSensor02MinMax   READ getIsErrSensor02MinMax   NOTIFY signalEventChangedIsErrSensor02MinMax  )
    Q_PROPERTY(QString mStrStatus             READ getStrStatus             NOTIFY signalEventChangedStrStatus            )
    Q_PROPERTY(QString mErrMsg                READ getErrMsg                NOTIFY signalEventChangedErrMsg               )
    Q_PROPERTY(QString mErrMsg2               READ getErrMsg2               NOTIFY signalEventChangedErrMsg2              )
    Q_PROPERTY(int     mProgress              READ getProgress              NOTIFY signalEventChangedProgress             )

public:
    int     mAccessMode            = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test           = false;
    bool    mIsSensor02Support     = false;
    bool    mIsS01HighSensor       = true;
    bool    mIsEnableZero          = false;
    double  mSensorFactor          = 0;
    double  mResultingOriPressure  = 0;
    QString mStrResultingPressure  = "0";
    bool    mS01Selction           = true;
    int     mS01Unit               = ValveEnumDef::PRESSURE_UNIT_TORR;
    double  mS01FullScale          = 1000;
    double  mS01GraphConvertFactor = 1;
    int     mS01GraphPrecN         = 0;
    QString mStrS01FullScale       = "0";
    int     mS01Exponent           = 3;
    bool    mS01IsProcessing       = false;
    int     mS01ProcessingPct      = 0;
    double  mS01MeasuredOriValue   = 0;
    QString mStrS01MeasuredValue   = "0";
    double  mS01OffsetOriValue     = 0;
    QString mStrS01OffsetValue     = "0";
    double  mS01OriValue           = 0;
    QString mStrS01Value           = "0";
    bool    mS02Selction           = true;
    int     mS02Unit               = ValveEnumDef::PRESSURE_UNIT_TORR;
    double  mS02FullScale          = 1000;
    double  mS02GraphConvertFactor = 1;
    int     mS02GraphPrecN         = 0;
    QString mStrS02FullScale       = "0";
    int     mS02Exponent           = 3;
    bool    mS02IsProcessing       = false;
    int     mS02ProcessingPct      = 0;
    double  mS02MeasuredOriValue   = 0;
    QString mStrS02MeasuredValue   = "0";
    double  mS02OffsetOriValue     = 0;
    QString mStrS02OffsetValue     = "0";
    double  mS02OriValue           = 0;
    QString mStrS02Value           = "0";
    int     mDpUnit                = ValveEnumDef::PRESSURE_UNIT_TORR;
    bool    mAutoScale             = true;
    int     mPrecN                 = 6;
    int     mXMsec                 = 30000;
    double  mSensor01Min           = 0;
    double  mSensor01Max           = 0;
    double  mSensor02Min           = 0;
    double  mSensor02Max           = 0;
    bool    mIsEditDpUnit          = false;
    bool    mIsEditAutoScale       = false;
    bool    mIsEditXMsec           = false;
    bool    mIsEditSensor01Min     = false;
    bool    mIsEditSensor01Max     = false;
    bool    mIsEditSensor02Min     = false;
    bool    mIsEditSensor02Max     = false;
    bool    mIsEdit                = false;
    bool    mIsErrSensor01MinMax   = false;
    bool    mIsErrSensor02MinMax   = false;
    QString mStrStatus             = "Loading";
    QString mErrMsg                = "";
    QString mErrMsg2               = "";
    int     mProgress              = 0 ;

    int     getAccessMode           (){ return mAccessMode           ; }
    bool    getIsRS232Test          (){ return mIsRS232Test          ; }
    bool    getIsSensor02Support    (){ return mIsSensor02Support    ; }
    bool    getIsS01HighSensor      (){ return mIsS01HighSensor      ; }
    bool    getIsEnableZero         (){ return mIsEnableZero         ; }
    double  getSensorFactor         (){ return mSensorFactor         ; }
    double  getResultingOriPressure (){ return mResultingOriPressure ; }
    QString getStrResultingPressure (){ return mStrResultingPressure ; }
    bool    getS01Selction          (){ return mS01Selction          ; }
    int     getS01Unit              (){ return mS01Unit              ; }
    double  getS01FullScale         (){ return mS01FullScale         ; }
    double  getS01GraphConvertFactor(){ return mS01GraphConvertFactor; }
    int     getS01GraphPrecN        (){ return mS01GraphPrecN        ; }
    QString getStrS01FullScale      (){ return mStrS01FullScale      ; }
    int     getS01Exponent          (){ return mS01Exponent          ; }
    bool    getS01IsProcessing      (){ return mS01IsProcessing      ; }
    int     getS01ProcessingPct     (){ return mS01ProcessingPct     ; }
    double  getS01MeasuredOriValue  (){ return mS01MeasuredOriValue  ; }
    QString getStrS01MeasuredValue  (){ return mStrS01MeasuredValue  ; }
    double  getS01OffsetOriValue    (){ return mS01OffsetOriValue    ; }
    QString getStrS01OffsetValue    (){ return mStrS01OffsetValue    ; }
    double  getS01OriValue          (){ return mS01OriValue          ; }
    QString getStrS01Value          (){ return mStrS01Value          ; }
    bool    getS02Selction          (){ return mS02Selction          ; }
    int     getS02Unit              (){ return mS02Unit              ; }
    double  getS02FullScale         (){ return mS02FullScale         ; }
    double  getS02GraphConvertFactor(){ return mS02GraphConvertFactor; }
    int     getS02GraphPrecN        (){ return mS02GraphPrecN        ; }
    QString getStrS02FullScale      (){ return mStrS02FullScale      ; }
    int     getS02Exponent          (){ return mS02Exponent          ; }
    bool    getS02IsProcessing      (){ return mS02IsProcessing      ; }
    int     getS02ProcessingPct     (){ return mS02ProcessingPct     ; }
    double  getS02MeasuredOriValue  (){ return mS02MeasuredOriValue  ; }
    QString getStrS02MeasuredValue  (){ return mStrS02MeasuredValue  ; }
    double  getS02OffsetOriValue    (){ return mS02OffsetOriValue    ; }
    QString getStrS02OffsetValue    (){ return mStrS02OffsetValue    ; }
    double  getS02OriValue          (){ return mS02OriValue          ; }
    QString getStrS02Value          (){ return mStrS02Value          ; }
    int     getDpUnit               (){ return mDpUnit               ; }
    bool    getAutoScale            (){ return mAutoScale            ; }
    int     getPrecN                (){ return mPrecN                ; }
    int     getXMsec                (){ return mXMsec                ; }
    double  getSensor01Min          (){ return mSensor01Min          ; }
    double  getSensor01Max          (){ return mSensor01Max          ; }
    double  getSensor02Min          (){ return mSensor02Min          ; }
    double  getSensor02Max          (){ return mSensor02Max          ; }
    bool    getIsEditDpUnit         (){ return mIsEditDpUnit         ; }
    bool    getIsEditAutoScale      (){ return mIsEditAutoScale      ; }
    bool    getIsEditXMsec          (){ return mIsEditXMsec          ; }
    bool    getIsEditSensor01Min    (){ return mIsEditSensor01Min    ; }
    bool    getIsEditSensor01Max    (){ return mIsEditSensor01Max    ; }
    bool    getIsEditSensor02Min    (){ return mIsEditSensor02Min    ; }
    bool    getIsEditSensor02Max    (){ return mIsEditSensor02Max    ; }
    bool    getIsEdit               (){ return mIsEdit               ; }
    bool    getIsErrSensor01MinMax  (){ return mIsErrSensor01MinMax  ; }
    bool    getIsErrSensor02MinMax  (){ return mIsErrSensor02MinMax  ; }
    QString getStrStatus            (){ return mStrStatus            ; }
    QString getErrMsg               (){ return mErrMsg               ; }
    QString getErrMsg2              (){ return mErrMsg2              ; }
    int     getProgress             (){ return mProgress             ; }

    void    setAccessMode           (int     value){ if(mAccessMode            == value)return; mAccessMode            = value; emit signalEventChangedAccessMode           (value);}
    void    setIsRS232Test          (bool    value){ if(mIsRS232Test           == value)return; mIsRS232Test           = value; emit signalEventChangedIsRS232Test          (value);}
    void    setIsSensor02Support    (bool    value){ if(mIsSensor02Support     == value)return; mIsSensor02Support     = value; emit signalEventChangedIsSensor02Support    (value);}
    void    setIsS01HighSensor      (bool    value){ if(mIsS01HighSensor       == value)return; mIsS01HighSensor       = value; emit signalEventChangedIsS01HighSensor      (value);}
    void    setIsEnableZero         (bool    value){ if(mIsEnableZero          == value)return; mIsEnableZero          = value; emit signalEventChangedIsEnableZero         (value);}
    void    setSensorFactor         (double  value){ if(mSensorFactor          == value)return; mSensorFactor          = value; emit signalEventChangedSensorFactor         (value);}
    void    setResultingOriPressure (double  value){ if(mResultingOriPressure  == value)return; mResultingOriPressure  = value; emit signalEventChangedResultingOriPressure (value);}
    void    setStrResultingPressure (QString value){ if(mStrResultingPressure  == value)return; mStrResultingPressure  = value; emit signalEventChangedStrResultingPressure (value);}
    void    setS01Selction          (bool    value){ if(mS01Selction           == value)return; mS01Selction           = value; emit signalEventChangedS01Selction          (value);}
    void    setS01Unit              (int     value){ if(mS01Unit               == value)return; mS01Unit               = value; emit signalEventChangedS01Unit              (value);}
    void    setS01FullScale         (double  value){ if(mS01FullScale          == value)return; mS01FullScale          = value; emit signalEventChangedS01FullScale         (value);}
    void    setS01GraphConvertFactor(double  value){ if(mS01GraphConvertFactor == value)return; mS01GraphConvertFactor = value; emit signalEventChangedS01GraphConvertFactor(value);}
    void    setS01GraphPrecN        (int     value){ if(mS01GraphPrecN         == value)return; mS01GraphPrecN         = value; emit signalEventChangedS01GraphPrecN        (value);}
    void    setStrS01FullScale      (QString value){ if(mStrS01FullScale       == value)return; mStrS01FullScale       = value; emit signalEventChangedStrS01FullScale      (value);}
    void    setS01Exponent          (int     value){ if(mS01Exponent           == value)return; mS01Exponent           = value; emit signalEventChangedS01Exponent          (value);}
    void    setS01IsProcessing      (bool    value){ if(mS01IsProcessing       == value)return; mS01IsProcessing       = value; emit signalEventChangedS01IsProcessing      (value);}
    void    setS01ProcessingPct     (int     value){ if(mS01ProcessingPct      == value)return; mS01ProcessingPct      = value; emit signalEventChangedS01ProcessingPct     (value);}
    void    setS01MeasuredOriValue  (double  value){ if(mS01MeasuredOriValue   == value)return; mS01MeasuredOriValue   = value; emit signalEventChangedS01MeasuredOriValue  (value);}
    void    setStrS01MeasuredValue  (QString value){ if(mStrS01MeasuredValue   == value)return; mStrS01MeasuredValue   = value; emit signalEventChangedStrS01MeasuredValue  (value);}
    void    setS01OffsetOriValue    (double  value){ if(mS01OffsetOriValue     == value)return; mS01OffsetOriValue     = value; emit signalEventChangedS01OffsetOriValue    (value);}
    void    setStrS01OffsetValue    (QString value){ if(mStrS01OffsetValue     == value)return; mStrS01OffsetValue     = value; emit signalEventChangedStrS01OffsetValue    (value);}
    void    setS01OriValue          (double  value){ if(mS01OriValue           == value)return; mS01OriValue           = value; emit signalEventChangedS01OriValue          (value);}
    void    setStrS01Value          (QString value){ if(mStrS01Value           == value)return; mStrS01Value           = value; emit signalEventChangedStrS01Value          (value);}
    void    setS02Selction          (bool    value){ if(mS02Selction           == value)return; mS02Selction           = value; emit signalEventChangedS02Selction          (value);}
    void    setS02Unit              (int     value){ if(mS02Unit               == value)return; mS02Unit               = value; emit signalEventChangedS02Unit              (value);}
    void    setS02FullScale         (double  value){ if(mS02FullScale          == value)return; mS02FullScale          = value; emit signalEventChangedS02FullScale         (value);}
    void    setS02GraphConvertFactor(double  value){ if(mS02GraphConvertFactor == value)return; mS02GraphConvertFactor = value; emit signalEventChangedS02GraphConvertFactor(value);}
    void    setS02GraphPrecN        (int     value){ if(mS02GraphPrecN         == value)return; mS02GraphPrecN         = value; emit signalEventChangedS02GraphPrecN        (value);}
    void    setStrS02FullScale      (QString value){ if(mStrS02FullScale       == value)return; mStrS02FullScale       = value; emit signalEventChangedStrS02FullScale      (value);}
    void    setS02Exponent          (int     value){ if(mS02Exponent           == value)return; mS02Exponent           = value; emit signalEventChangedS02Exponent          (value);}
    void    setS02IsProcessing      (bool    value){ if(mS02IsProcessing       == value)return; mS02IsProcessing       = value; emit signalEventChangedS02IsProcessing      (value);}
    void    setS02ProcessingPct     (int     value){ if(mS02ProcessingPct      == value)return; mS02ProcessingPct      = value; emit signalEventChangedS02ProcessingPct     (value);}
    void    setS02MeasuredOriValue  (double  value){ if(mS02MeasuredOriValue   == value)return; mS02MeasuredOriValue   = value; emit signalEventChangedS02MeasuredOriValue  (value);}
    void    setStrS02MeasuredValue  (QString value){ if(mStrS02MeasuredValue   == value)return; mStrS02MeasuredValue   = value; emit signalEventChangedStrS02MeasuredValue  (value);}
    void    setS02OffsetOriValue    (double  value){ if(mS02OffsetOriValue     == value)return; mS02OffsetOriValue     = value; emit signalEventChangedS02OffsetOriValue    (value);}
    void    setStrS02OffsetValue    (QString value){ if(mStrS02OffsetValue     == value)return; mStrS02OffsetValue     = value; emit signalEventChangedStrS02OffsetValue    (value);}
    void    setS02OriValue          (double  value){ if(mS02OriValue           == value)return; mS02OriValue           = value; emit signalEventChangedS02OriValue          (value);}
    void    setStrS02Value          (QString value){ if(mStrS02Value           == value)return; mStrS02Value           = value; emit signalEventChangedStrS02Value          (value);}
    void    setDpUnit               (int     value){ if(mDpUnit                == value)return; mDpUnit                = value; emit signalEventChangedDpUnit               (value);}
    void    setAutoScale            (bool    value){ if(mAutoScale             == value)return; mAutoScale             = value; emit signalEventChangedAutoScale            (value);}
    void    setPrecN                (int     value){ if(mPrecN                 == value)return; mPrecN                 = value; emit signalEventChangedPrecN                (value);}
    void    setXMsec                (int     value){ if(mXMsec                 == value)return; mXMsec                 = value; emit signalEventChangedXMsec                (value);}
    void    setSensor01Min          (double  value){ if(mSensor01Min           == value)return; mSensor01Min           = value; emit signalEventChangedSensor01Min          (value);}
    void    setSensor01Max          (double  value){ if(mSensor01Max           == value)return; mSensor01Max           = value; emit signalEventChangedSensor01Max          (value);}
    void    setSensor02Min          (double  value){ if(mSensor02Min           == value)return; mSensor02Min           = value; emit signalEventChangedSensor02Min          (value);}
    void    setSensor02Max          (double  value){ if(mSensor02Max           == value)return; mSensor02Max           = value; emit signalEventChangedSensor02Max          (value);}
    void    setIsEditDpUnit         (bool    value){ if(mIsEditDpUnit          == value)return; mIsEditDpUnit          = value; emit signalEventChangedIsEditDpUnit         (value);}
    void    setIsEditAutoScale      (bool    value){ if(mIsEditAutoScale       == value)return; mIsEditAutoScale       = value; emit signalEventChangedIsEditAutoScale      (value);}
    void    setIsEditXMsec          (bool    value){ if(mIsEditXMsec           == value)return; mIsEditXMsec           = value; emit signalEventChangedIsEditXMsec          (value);}
    void    setIsEditSensor01Min    (bool    value){ if(mIsEditSensor01Min     == value)return; mIsEditSensor01Min     = value; emit signalEventChangedIsEditSensor01Min    (value);}
    void    setIsEditSensor01Max    (bool    value){ if(mIsEditSensor01Max     == value)return; mIsEditSensor01Max     = value; emit signalEventChangedIsEditSensor01Max    (value);}
    void    setIsEditSensor02Min    (bool    value){ if(mIsEditSensor02Min     == value)return; mIsEditSensor02Min     = value; emit signalEventChangedIsEditSensor02Min    (value);}
    void    setIsEditSensor02Max    (bool    value){ if(mIsEditSensor02Max     == value)return; mIsEditSensor02Max     = value; emit signalEventChangedIsEditSensor02Max    (value);}
    void    setIsEdit               (bool    value){ if(mIsEdit                == value)return; mIsEdit                = value; emit signalEventChangedIsEdit               (value);}
    void    setIsErrSensor01MinMax  (bool    value){ if(mIsErrSensor01MinMax   == value)return; mIsErrSensor01MinMax   = value; emit signalEventChangedIsErrSensor01MinMax  (value);}
    void    setIsErrSensor02MinMax  (bool    value){ if(mIsErrSensor02MinMax   == value)return; mIsErrSensor02MinMax   = value; emit signalEventChangedIsErrSensor02MinMax  (value);}
    void    setStrStatus            (QString value){ if(mStrStatus             == value)return; mStrStatus             = value; emit signalEventChangedStrStatus            (value);}
    void    setErrMsg               (QString value){ if(mErrMsg                == value)return; mErrMsg                = value; emit signalEventChangedErrMsg               (value);}
    void    setErrMsg2              (QString value){ if(mErrMsg2               == value)return; mErrMsg2               = value; emit signalEventChangedErrMsg2              (value);}
    void    setProgress             (int     value){ if(mProgress              == value)return; mProgress              = value; emit signalEventChangedProgress             (value);}

signals:
    void signalEventChangedAccessMode           (int     value);
    void signalEventChangedIsRS232Test          (bool    value);
    void signalEventChangedIsSensor02Support    (bool    value);
    void signalEventChangedIsS01HighSensor      (bool    value);
    void signalEventChangedIsEnableZero         (bool    value);
    void signalEventChangedSensorFactor         (double  value);
    void signalEventChangedResultingOriPressure (double  value);
    void signalEventChangedStrResultingPressure (QString value);
    void signalEventChangedS01Selction          (bool    value);
    void signalEventChangedS01Unit              (int     value);
    void signalEventChangedS01FullScale         (double  value);
    void signalEventChangedS01GraphConvertFactor(double  value);
    void signalEventChangedS01GraphPrecN        (int     value);
    void signalEventChangedStrS01FullScale      (QString value);
    void signalEventChangedS01Exponent          (int     value);
    void signalEventChangedS01IsProcessing      (bool    value);
    void signalEventChangedS01ProcessingPct     (int     value);
    void signalEventChangedS01MeasuredOriValue  (double  value);
    void signalEventChangedStrS01MeasuredValue  (QString value);
    void signalEventChangedS01OffsetOriValue    (double  value);
    void signalEventChangedStrS01OffsetValue    (QString value);
    void signalEventChangedS01OriValue          (double  value);
    void signalEventChangedStrS01Value          (QString value);
    void signalEventChangedS02Selction          (bool    value);
    void signalEventChangedS02Unit              (int     value);
    void signalEventChangedS02FullScale         (double  value);
    void signalEventChangedS02GraphConvertFactor(double  value);
    void signalEventChangedS02GraphPrecN        (int     value);
    void signalEventChangedStrS02FullScale      (QString value);
    void signalEventChangedS02Exponent          (int     value);
    void signalEventChangedS02IsProcessing      (bool    value);
    void signalEventChangedS02ProcessingPct     (int     value);
    void signalEventChangedS02MeasuredOriValue  (double  value);
    void signalEventChangedStrS02MeasuredValue  (QString value);
    void signalEventChangedS02OffsetOriValue    (double  value);
    void signalEventChangedStrS02OffsetValue    (QString value);
    void signalEventChangedS02OriValue          (double  value);
    void signalEventChangedStrS02Value          (QString value);
    void signalEventChangedDpUnit               (int     value);
    void signalEventChangedAutoScale            (bool    value);
    void signalEventChangedPrecN                (int     value);
    void signalEventChangedXMsec                (int     value);
    void signalEventChangedSensor01Min          (double  value);
    void signalEventChangedSensor01Max          (double  value);
    void signalEventChangedSensor02Min          (double  value);
    void signalEventChangedSensor02Max          (double  value);
    void signalEventChangedIsEditDpUnit         (bool    value);
    void signalEventChangedIsEditAutoScale      (bool    value);
    void signalEventChangedIsEditXMsec          (bool    value);
    void signalEventChangedIsEditSensor01Min    (bool    value);
    void signalEventChangedIsEditSensor01Max    (bool    value);
    void signalEventChangedIsEditSensor02Min    (bool    value);
    void signalEventChangedIsEditSensor02Max    (bool    value);
    void signalEventChangedIsEdit               (bool    value);
    void signalEventChangedIsErrSensor01MinMax  (bool    value);
    void signalEventChangedIsErrSensor02MinMax  (bool    value);
    void signalEventChangedStrStatus            (QString value);
    void signalEventChangedErrMsg               (QString value);
    void signalEventChangedErrMsg2              (QString value);
    void signalEventChangedProgress             (int     value);
    void signalEventChangedGraphSetting         (             );

    void signalEventAddSensorValue(qint64 msec, double sensor01Value, double sensor02Value);

public:
    explicit SensorAnalysisDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_VERSION;
        //ENABLE_SLOT_VALVE_CHANGED_PRESSURE_DB_UNIT;
        ENABLE_SLOT_VALVE_READED_SENSOR_CONFIG;
        ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_HIGH;
        ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_LOW;
        ENABLE_SLOT_VALVE_READED_SENSOR_SCALE;
        ENABLE_SLOT_VALVE_READED_SENSOR_OFFSET;
        ENABLE_SLOT_VALVE_READED_SENSOR_VALUE;
        //ENABLE_SLOT_VALVE_READED_SENSOR_SELECTION;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedSensorVersion();
        setDpUnit(pValveSP->getPressureDpUnit());
        //onValveChangedPressureDpUnit();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CONFIG);
    }
    ~SensorAnalysisDlgModel()
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

    void onValveChangedPressureDpUnit()
    {
        setDpUnit(pValveSP->getPressureDpUnit());
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

        switch (dto.mSensorOperation)
        {
        case ValveEnumDef::SENSOROP_01_SENSOR_01_INPUT:
            setIsS01HighSensor(true);
            setS01Selction(true);
            setS02Selction(false);
            break;

        case ValveEnumDef::SENSOROP_01_SENSOR_02_INPUT:
            setIsS01HighSensor(false);
            setS01Selction(false);
            setS02Selction(true);
            break;

        case ValveEnumDef::SENSOROP_02_SENSOR_LOW_01_HIGHT_02:
            setIsS01HighSensor(false);
            setS01Selction(true);
            setS02Selction(true);
            break;

        case ValveEnumDef::SENSOROP_02_SENSOR_LOW_02_HIGHT_01:
            setIsS01HighSensor(true);
            setS01Selction(true);
            setS02Selction(true);
            break;
        }

        setIsEnableZero(dto.mZeroEnable);


        setState((eState)(mState + 1));
    }

    void onValveReadedCrossoverHigh(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_CROSSOVER_HIGH || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        mSwitchHigh = dto.mValue.toDouble() / 10000;

        setState((eState)(mState + 1));
    }

    void onValveReadedCrossoverLow(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_CROSSOVER_LOW || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        mSwitchLow = dto.mValue.toDouble() / 10000;

        setState((eState)(mState + 1));
    }

    void onValveReadedSensorScale(ValveResponseSensorScaleDto dto)
    {
        double s01FullScale;
        double s02FullScale;

        if(mState != eState::STATE_READ_SCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setS01Unit(dto.mSensor01Unit);
        setS02Unit(dto.mSensor02Unit);
        setDpUnit(getIsS01HighSensor() ? getS01Unit() : getS02Unit());

        setS01FullScale((double)dto.mSensor01FullScale * qPow(10, dto.mSensor01Exp) * 0.0001);
        setS02FullScale((double)dto.mSensor02FullScale * qPow(10, dto.mSensor02Exp) * 0.0001);
        setS01Exponent(dto.mSensor01Exp);
        setS02Exponent(dto.mSensor02Exp);

        s01FullScale = UNITUTIL_CONVERT(getS01Unit(), getS01FullScale(), getDpUnit());
        s02FullScale = UNITUTIL_CONVERT(getS02Unit(), getS02FullScale(), getDpUnit());

        setSensor01Min(0);
        setSensor01Max(s01FullScale);
        setSensor02Min(0);
        setSensor02Max(s02FullScale);

        setState((eState)(mState + 1));
    }

    void onValveReadedSensorOffset(ValveResponseSensorOffsetValuesDto dto)
    {
        if(mState != eState::STATE_READ_OFFSET || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setS01OffsetOriValue(dto.mS01Offset);
        setS02OffsetOriValue(dto.mS02Offset);

        calValueByDpUnit();

        setState((eState)(mState + 1));
    }

    void onValveReadedSensorValue(ValveResponseSensorValueDto dto)
    {
        double resultingValue;
        double s01Value;
        double s02Value;
        double s01MeasuredValue;
        double s02MeasuredValue;
        int    sensorHighUnit = getIsS01HighSensor() ? getS01Unit() : getS02Unit();
        double fullScale      = getIsS01HighSensor() ? getS01FullScale() : getS02FullScale();

        if(mState != eState::STATE_READ_VALUE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setS01OriValue          (dto.mS01Value);
        setS02OriValue          (dto.mS02Value);
        setS01GraphConvertFactor(getStrS01FullScale().toDouble() * 0.000001);
        setS02GraphConvertFactor(getStrS02FullScale().toDouble() * 0.000001);
        setResultingOriPressure (dto.mResultingValue);

        if(getDpUnit() == ValveEnumDef::PRESSURE_UNIT_VOLT)
        {
            s01Value         = getS01OriValue()          * 0.00001;
            s02Value         = getS02OriValue()          * 0.00001;
            resultingValue   = getResultingOriPressure() * 0.00001;

            s01MeasuredValue = ((getS01OriValue() + getS01OffsetOriValue())*0.00001);
            s02MeasuredValue = ((getS02OriValue() + getS02OffsetOriValue())*0.00001);
        }
        else if(getDpUnit() == ValveEnumDef::PRESSURE_UNIT_MVOLT)
        {
            s01Value         = getS01OriValue()          * 0.01;
            s02Value         = getS02OriValue()          * 0.01;
            resultingValue   = getResultingOriPressure() * 0.01;

            s01MeasuredValue = ((getS01OriValue() + getS01OffsetOriValue())*0.01);
            s02MeasuredValue = ((getS02OriValue() + getS02OffsetOriValue())*0.01);
        }
        else
        {
            s01Value       = UNITUTIL_CONVERT(getS01Unit()  , getS01FullScale() * (getS01OriValue() *0.000001), getDpUnit());
            s02Value       = UNITUTIL_CONVERT(getS02Unit()  , getS02FullScale() * (getS02OriValue() *0.000001), getDpUnit());
            resultingValue = UNITUTIL_CONVERT(sensorHighUnit, fullScale * (getResultingOriPressure()*0.000001), getDpUnit());

            s01MeasuredValue = UNITUTIL_CONVERT(getS01Unit(), getS01FullScale() * ((getS01OriValue() + getS01OffsetOriValue())*0.000001), getDpUnit());
            s02MeasuredValue = UNITUTIL_CONVERT(getS02Unit(), getS02FullScale() * ((getS02OriValue() + getS02OffsetOriValue())*0.000001), getDpUnit());
        }

        setStrS01Value         (QString("%1").arg(s01Value));
        setStrS01MeasuredValue (QString("%1").arg(s01MeasuredValue));
        setStrS02Value         (QString("%1").arg(s02Value));
        setStrS02MeasuredValue (QString("%1").arg(s02MeasuredValue));
        setStrResultingPressure(QString("%1").arg(resultingValue));

        calcSwitchProcessing();

        emit signalEventAddSensorValue(QDateTime::currentDateTime().time().msecsSinceStartOfDay(), getS01OriValue(), getS02OriValue());

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetDpUnit(int unitIdx)
    {
        setDpUnit(unitIdx);

        calValueByDpUnit();
    }

    Q_INVOKABLE void onCommandSetTimeInterval(int intervalIdx)
    {
        setXMsec(mTimeIntervalList.at(intervalIdx));
    }

    Q_INVOKABLE void onCommandSetAutoScale(bool value)
    {
        setAutoScale(value);
    }

    Q_INVOKABLE void onCommandSetSensor01Min(double value)
    {
    }

    Q_INVOKABLE void onCommandSetSensor01Max(double value)
    {
    }

    Q_INVOKABLE void onCommandSetSensor02Min(double value)
    {
    }

    Q_INVOKABLE void onCommandSetSensor02Max(double value)
    {
    }

    Q_INVOKABLE void onCommandSetGraphSetting(int unitIdx, int intervalIdx, bool autoScale, double s01Min, double s01Max, double s02Min, double s02Max)
    {
        setIsErrSensor01MinMax(false);
        setIsErrSensor02MinMax(false);

        if(autoScale == false)
        {
            if(mS01Selction)
            {
                setIsErrSensor01MinMax(!(s01Min < s01Max));
            }
            if(mS02Selction)
            {
                setIsErrSensor02MinMax(!(s02Min < s02Max));
            }

            if(mIsErrSensor01MinMax || mIsErrSensor02MinMax)
                return;
        }

        setIsEditSensor01Min  (false);
        setIsEditSensor01Max  (false);
        setIsEditSensor02Min  (false);
        setIsEditSensor02Max  (false);
        setIsEditDpUnit       (false);
        setIsEditAutoScale    (false);
        setIsEditXMsec        (false);
        setIsEdit             (false);

        setDpUnit(unitIdx);
        setSensor01Min(s01Min);
        setSensor01Max(s01Max);
        setSensor02Min(s02Min);
        setSensor02Max(s02Max);
        setXMsec(mTimeIntervalList.at(intervalIdx));
        setAutoScale(autoScale);
        calValueByDpUnit();

        emit signalEventChangedGraphSetting();
    }

    Q_INVOKABLE void onCommandSetIsEditDpUnit(bool value)
    {
        setIsEditDpUnit   (value);
        setIsEdit         (value);
    }
    Q_INVOKABLE void onCommandSetIsEditAutoScale(bool value)
    {
        setIsEditAutoScale(value);
        setIsEdit         (value);
    }
    Q_INVOKABLE void onCommandSetIsEditXMsec(bool value)
    {
        setIsEditXMsec    (value);
        setIsEdit         (value);
    }

    Q_INVOKABLE void onCommandSetIsEditSensor01Min(bool value)
    {
        setIsEditSensor01Min(value);
        setIsEdit           (value);
    }

    Q_INVOKABLE void onCommandSetIsEditSensor01Max(bool value)
    {
        setIsEditSensor01Max(value);
        setIsEdit           (value);
    }

    Q_INVOKABLE void onCommandSetIsEditSensor02Min(bool value)
    {
        setIsEditSensor02Min(value);
        setIsEdit           (value);
    }

    Q_INVOKABLE void onCommandSetIsEditSensor02Max(bool value)
    {
        setIsEditSensor02Max(value);
        setIsEdit           (value);
    }

    Q_INVOKABLE void onCommandSetIsEdit(bool value)
    {
        setIsEditSensor01Min(value);
        setIsEditSensor01Max(value);
        setIsEditSensor02Min(value);
        setIsEditSensor02Max(value);
        setIsEditDpUnit     (value);
        setIsEditAutoScale  (value);
        setIsEditXMsec      (value);
        setIsEdit           (value);
    }

private:
    enum eState{
        STATE_READ_CONFIG         = 0,
        STATE_READ_CROSSOVER_HIGH = STATE_READ_CONFIG         + 1,
        STATE_READ_CROSSOVER_LOW  = STATE_READ_CROSSOVER_HIGH + 1,
        STATE_READ_SCALE          = STATE_READ_CROSSOVER_LOW  + 1,
        STATE_READ_OFFSET         = STATE_READ_SCALE          + 1,
        STATE_READ_VALUE          = STATE_READ_OFFSET         + 1,
        STATE_READY               = STATE_READ_VALUE          + 1,
    };

    QList<int> mTimeIntervalList = {30000, 60000, 120000, 300000};
    QTimer mTimer;
    eState mState         = eState::STATE_READ_CONFIG;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        mState = state;

        if(mState >= STATE_READY)
        {
            mState = STATE_READ_VALUE;
        }

        if(state < (int) eState::STATE_READ_OFFSET && state >= (int) eState::STATE_READ_CONFIG)
        {
            setProgress(qFloor((state * 100) / eState::STATE_READ_OFFSET));
            setStrStatus("loading");
        }
        else
        {
            setProgress(100);
            setStrStatus("scan");
        }

        startTimer();

    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_CONFIG:
            pValveSP->readSensorConfig(this);
            break;

        case (int)eState::STATE_READ_CROSSOVER_LOW:
            pValveSP->readCrossoverLow(this);
            break;

        case (int)eState::STATE_READ_CROSSOVER_HIGH:
            pValveSP->readCrossoverHigh(this);
            break;

        case (int)eState::STATE_READ_SCALE:
            pValveSP->readSensorScale(this);
            break;

        case (int)eState::STATE_READ_OFFSET:
            pValveSP->readSensorOffset(this);
            break;

        case (int)eState::STATE_READ_VALUE :
            pValveSP->readSensorValue(this);
            break;
        }
    }

private:
    double mSwitchHigh = 0;
    double mSwitchLow  = 0;

    void calValueByDpUnit()
    {
        double s01FullScale;
        double s02FullScale;
        double s01Offset;
        double s02Offset;

        if(getDpUnit() == ValveEnumDef::PRESSURE_UNIT_VOLT)
        {

            setStrS01FullScale(QString("%1").arg("10"));
            setStrS02FullScale(QString("%1").arg("10"));
            setS01GraphPrecN(5);
            setS02GraphPrecN(5);
            setStrS01OffsetValue(QString("%1").arg((getS01OffsetOriValue()*0.00001)));
            setStrS02OffsetValue(QString("%1").arg((getS02OffsetOriValue()*0.00001)));
            return;
        }
        else if(getDpUnit() == ValveEnumDef::PRESSURE_UNIT_MVOLT)
        {

            setStrS01FullScale(QString("%1").arg("10000"));
            setStrS02FullScale(QString("%1").arg("10000"));
            setS01GraphPrecN(2);
            setS02GraphPrecN(2);
            setStrS01OffsetValue(QString("%1").arg((getS01OffsetOriValue()*0.01)));
            setStrS02OffsetValue(QString("%1").arg((getS02OffsetOriValue()*0.01)));
            return;
        }

        s01FullScale = UNITUTIL_CONVERT(getS01Unit(), getS01FullScale(), getDpUnit());
        s02FullScale = UNITUTIL_CONVERT(getS02Unit(), getS02FullScale(), getDpUnit());

        setStrS01FullScale(QString("%1").arg(s01FullScale));
        setStrS02FullScale(QString("%1").arg(s02FullScale));

        int precision01 = pValveSP->getS01FullScalePrec() + UNITUTIL_ADD_PRECISION(pValveSP->getS01SullScaleUnit(), getDpUnit());
        precision01 = precision01 < 0 ? 0 : precision01 > 6 ? 6 : precision01;
        int precision02 = pValveSP->getS02FullScalePrec() + UNITUTIL_ADD_PRECISION(pValveSP->getS02SullScaleUnit(), getDpUnit());
        precision02 = precision02 < 0 ? 0 : precision02 > 6 ? 6 : precision02;

        setS01GraphPrecN(precision01);
        setS02GraphPrecN(precision02);

        s01Offset = UNITUTIL_CONVERT(getS01Unit(), getS01FullScale() * (getS01OffsetOriValue()*0.000001), getDpUnit());
        s02Offset = UNITUTIL_CONVERT(getS02Unit(), getS02FullScale() * (getS02OffsetOriValue()*0.000001), getDpUnit());

        setStrS01OffsetValue(QString("%1").arg(s01Offset));
        setStrS02OffsetValue(QString("%1").arg(s02Offset));
    }

    void calcSwitchProcessing()
    {
        int procPct = 0;

        if(getS01Selction() && !getS02Selction())
        {
            setS01IsProcessing(true);
            setS01ProcessingPct(100);
            setS02IsProcessing(false);
            setS02ProcessingPct(0);
            return;
        }

        if(!getS01Selction() && getS02Selction())
        {
            setS01IsProcessing(false);
            setS01ProcessingPct(0);
            setS02IsProcessing(true);
            setS02ProcessingPct(100);
            return;
        }

        if(getIsS01HighSensor())  // low is sensor 2
        {
            int pct = (getS02OriValue() / 1000000) * 100;

            if(pct >= mSwitchHigh)
            {
                setS01IsProcessing(true);
                setS01ProcessingPct(100);
                setS02IsProcessing(false);
                setS02ProcessingPct(0);
                return;
            }
            else if(pct <= mSwitchLow)
            {
                setS01IsProcessing(false);
                setS01ProcessingPct(0);
                setS02IsProcessing(true);
                setS02ProcessingPct(100);
                return;
            }
            else
            {
                procPct = ((pct - mSwitchLow) / (mSwitchHigh - mSwitchLow)) * 100;

                setS01IsProcessing(true);
                setS01ProcessingPct(procPct);
                setS02IsProcessing(true);
                setS02ProcessingPct(100 - procPct);
                return;
            }
        }
        else                      // low is sensor 1
        {
            int pct = (getS01OriValue() / 1000000) * 100;

            if(pct >= mSwitchHigh)
            {
                setS01IsProcessing(false);
                setS01ProcessingPct(0);
                setS02IsProcessing(true);
                setS02ProcessingPct(100);
                return;
            }
            else if(pct <= mSwitchLow)
            {
                setS01IsProcessing(true);
                setS01ProcessingPct(100);
                setS02IsProcessing(false);
                setS02ProcessingPct(0);
                return;
            }
            else
            {
                procPct = ((pct - mSwitchLow) / (mSwitchHigh - mSwitchLow)) * 100;

                setS01IsProcessing(true);
                setS01ProcessingPct(100 - procPct);
                setS02IsProcessing(true);
                setS02ProcessingPct(procPct);
                return;
            }
        }
    }
};
#endif // SENSORANALYSISDLGMODEL_H
