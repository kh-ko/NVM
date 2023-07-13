#ifndef SENSORSETUPEXDLGMODEL_H
#define SENSORSETUPEXDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/mathutil.h"
#include "source/service/util/mathutil.h"
#include "source/service/coreservice.h"

class SensorSetupExDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode                       READ getAccessMode                     NOTIFY signalEventChangedAccessMode                      )
    Q_PROPERTY(bool     mIsRS232Test                      READ getIsRS232Test                    NOTIFY signalEventChangedIsRS232Test                     )
    Q_PROPERTY(bool     mIsSensor02Support                READ getIsSensor02Support              NOTIFY signalEventChangedIsSensor02Support               )
    Q_PROPERTY(int      mS01AnalActive                    READ getS01AnalActive                  NOTIFY signalEventChangedS01AnalActive                   )
    Q_PROPERTY(int      mS01Selection                     READ getS01Selection                   NOTIFY signalEventChangedS01Selection                    )
    Q_PROPERTY(int      mS01SourceIdx                     READ getS01SourceIdx                   NOTIFY signalEventChangedS01SourceIdx                    )
    Q_PROPERTY(int      mS01UnitIdx                       READ getS01UnitIdx                     NOTIFY signalEventChangedS01UnitIdx                      )
    Q_PROPERTY(QString  mS01FullScale                     READ getS01FullScale                   NOTIFY signalEventChangedS01FullScale                    )
    Q_PROPERTY(QString  mS01DigiValue                     READ getS01DigiValue                   NOTIFY signalEventChangedS01DigiValue                    )
    Q_PROPERTY(int      mS01ZeroAdjEnable                 READ getS01ZeroAdjEnable               NOTIFY signalEventChangedS01ZeroAdjEnable                )
    Q_PROPERTY(QString  mS01ZeroAdjOffsetLimMin           READ getS01ZeroAdjOffsetLimMin         NOTIFY signalEventChangedS01ZeroAdjOffsetLimMin          )
    Q_PROPERTY(QString  mS01ZeroAdjOffsetLimMax           READ getS01ZeroAdjOffsetLimMax         NOTIFY signalEventChangedS01ZeroAdjOffsetLimMax          )
    Q_PROPERTY(QString  mS01ZeroAdjOffsetValue            READ getS01ZeroAdjOffsetValue          NOTIFY signalEventChangedS01ZeroAdjOffsetValue           )
    Q_PROPERTY(QString  mS01ScaleOffset                   READ getS01ScaleOffset                 NOTIFY signalEventChangedS01ScaleOffset                  )
    Q_PROPERTY(QString  mS01Scale                         READ getS01Scale                       NOTIFY signalEventChangedS01Scale                        )
    Q_PROPERTY(int      mS01ScaleZeroPoint                READ getS01ScaleZeroPoint              NOTIFY signalEventChangedS01ScaleZeroPoint               )
    Q_PROPERTY(QString  mS01FilterSec                     READ getS01FilterSec                   NOTIFY signalEventChangedS01FilterSec                    )
    Q_PROPERTY(int      mS01LogSensorLinearize            READ getS01LogSensorLinearize          NOTIFY signalEventChangedS01LogSensorLinearize           )
    Q_PROPERTY(QString  mS01LogSensorVoltPerDecade        READ getS01LogSensorVoltPerDecade      NOTIFY signalEventChangedS01LogSensorVoltPerDecade       )
    Q_PROPERTY(QString  mS01LogSensorVoltAtFullScale      READ getS01LogSensorVoltAtFullScale    NOTIFY signalEventChangedS01LogSensorVoltAtFullScale     )
    Q_PROPERTY(int      mS02AnalActive                    READ getS02AnalActive                  NOTIFY signalEventChangedS02AnalActive                   )
    Q_PROPERTY(int      mS02Selection                     READ getS02Selection                   NOTIFY signalEventChangedS02Selection                    )
    Q_PROPERTY(int      mS02SourceIdx                     READ getS02SourceIdx                   NOTIFY signalEventChangedS02SourceIdx                    )
    Q_PROPERTY(int      mS02UnitIdx                       READ getS02UnitIdx                     NOTIFY signalEventChangedS02UnitIdx                      )
    Q_PROPERTY(QString  mS02FullScale                     READ getS02FullScale                   NOTIFY signalEventChangedS02FullScale                    )
    Q_PROPERTY(QString  mS02DigiValue                     READ getS02DigiValue                   NOTIFY signalEventChangedS02DigiValue                    )
    Q_PROPERTY(int      mS02ZeroAdjEnable                 READ getS02ZeroAdjEnable               NOTIFY signalEventChangedS02ZeroAdjEnable                )
    Q_PROPERTY(QString  mS02ZeroAdjOffsetLimMin           READ getS02ZeroAdjOffsetLimMin         NOTIFY signalEventChangedS02ZeroAdjOffsetLimMin          )
    Q_PROPERTY(QString  mS02ZeroAdjOffsetLimMax           READ getS02ZeroAdjOffsetLimMax         NOTIFY signalEventChangedS02ZeroAdjOffsetLimMax          )
    Q_PROPERTY(QString  mS02ZeroAdjOffsetValue            READ getS02ZeroAdjOffsetValue          NOTIFY signalEventChangedS02ZeroAdjOffsetValue           )
    Q_PROPERTY(QString  mS02ScaleOffset                   READ getS02ScaleOffset                 NOTIFY signalEventChangedS02ScaleOffset                  )
    Q_PROPERTY(QString  mS02Scale                         READ getS02Scale                       NOTIFY signalEventChangedS02Scale                        )
    Q_PROPERTY(int      mS02ScaleZeroPoint                READ getS02ScaleZeroPoint              NOTIFY signalEventChangedS02ScaleZeroPoint               )
    Q_PROPERTY(QString  mS02FilterSec                     READ getS02FilterSec                   NOTIFY signalEventChangedS02FilterSec                    )
    Q_PROPERTY(int      mS02LogSensorLinearize            READ getS02LogSensorLinearize          NOTIFY signalEventChangedS02LogSensorLinearize           )
    Q_PROPERTY(QString  mS02LogSensorVoltPerDecade        READ getS02LogSensorVoltPerDecade      NOTIFY signalEventChangedS02LogSensorVoltPerDecade       )
    Q_PROPERTY(QString  mS02LogSensorVoltAtFullScale      READ getS02LogSensorVoltAtFullScale    NOTIFY signalEventChangedS02LogSensorVoltAtFullScale     )
    Q_PROPERTY(int      mCrossoverModIdx                  READ getCrossoverModIdx                NOTIFY signalEventChangedCrossoverModIdx                 )
    Q_PROPERTY(QString  mCrossoverLow                     READ getCrossoverLow                   NOTIFY signalEventChangedCrossoverLow                    )
    Q_PROPERTY(QString  mCrossoverHigh                    READ getCrossoverHigh                  NOTIFY signalEventChangedCrossoverHigh                   )
    Q_PROPERTY(QString  mCrossoverDela                    READ getCrossoverDela                  NOTIFY signalEventChangedCrossoverDela                   )
    Q_PROPERTY(bool     mErrS01AnalActive                 READ getErrS01AnalActive               NOTIFY signalEventChangedErrS01AnalActive                )
    Q_PROPERTY(bool     mErrS01Selection                  READ getErrS01Selection                NOTIFY signalEventChangedErrS01Selection                 )
    Q_PROPERTY(bool     mErrS01SourceIdx                  READ getErrS01SourceIdx                NOTIFY signalEventChangedErrS01SourceIdx                 )
    Q_PROPERTY(bool     mErrS01UnitIdx                    READ getErrS01UnitIdx                  NOTIFY signalEventChangedErrS01UnitIdx                   )
    Q_PROPERTY(bool     mErrS01FullScale                  READ getErrS01FullScale                NOTIFY signalEventChangedErrS01FullScale                 )
    Q_PROPERTY(bool     mErrS01DigiValue                  READ getErrS01DigiValue                NOTIFY signalEventChangedErrS01DigiValue                 )
    Q_PROPERTY(bool     mErrS01ZeroAdjEnable              READ getErrS01ZeroAdjEnable            NOTIFY signalEventChangedErrS01ZeroAdjEnable             )
    Q_PROPERTY(bool     mErrS01ZeroAdjOffsetLimMin        READ getErrS01ZeroAdjOffsetLimMin      NOTIFY signalEventChangedErrS01ZeroAdjOffsetLimMin       )
    Q_PROPERTY(bool     mErrS01ZeroAdjOffsetLimMax        READ getErrS01ZeroAdjOffsetLimMax      NOTIFY signalEventChangedErrS01ZeroAdjOffsetLimMax       )
    Q_PROPERTY(bool     mErrS01ZeroAdjOffsetValue         READ getErrS01ZeroAdjOffsetValue       NOTIFY signalEventChangedErrS01ZeroAdjOffsetValue        )
    Q_PROPERTY(bool     mErrS01ScaleOffset                READ getErrS01ScaleOffset              NOTIFY signalEventChangedErrS01ScaleOffset               )
    Q_PROPERTY(bool     mErrS01Scale                      READ getErrS01Scale                    NOTIFY signalEventChangedErrS01Scale                     )
    Q_PROPERTY(bool     mErrS01ScaleZeroPoint             READ getErrS01ScaleZeroPoint           NOTIFY signalEventChangedErrS01ScaleZeroPoint            )
    Q_PROPERTY(bool     mErrS01FilterSec                  READ getErrS01FilterSec                NOTIFY signalEventChangedErrS01FilterSec                 )
    Q_PROPERTY(bool     mErrS01LogSensorLinearize         READ getErrS01LogSensorLinearize       NOTIFY signalEventChangedErrS01LogSensorLinearize        )
    Q_PROPERTY(bool     mErrS01LogSensorVoltPerDecade     READ getErrS01LogSensorVoltPerDecade   NOTIFY signalEventChangedErrS01LogSensorVoltPerDecade    )
    Q_PROPERTY(bool     mErrS01LogSensorVoltAtFullScale   READ getErrS01LogSensorVoltAtFullScale NOTIFY signalEventChangedErrS01LogSensorVoltAtFullScale  )
    Q_PROPERTY(bool     mErrS02AnalActive                 READ getErrS02AnalActive               NOTIFY signalEventChangedErrS02AnalActive                )
    Q_PROPERTY(bool     mErrS02Selection                  READ getErrS02Selection                NOTIFY signalEventChangedErrS02Selection                 )
    Q_PROPERTY(bool     mErrS02SourceIdx                  READ getErrS02SourceIdx                NOTIFY signalEventChangedErrS02SourceIdx                 )
    Q_PROPERTY(bool     mErrS02UnitIdx                    READ getErrS02UnitIdx                  NOTIFY signalEventChangedErrS02UnitIdx                   )
    Q_PROPERTY(bool     mErrS02FullScale                  READ getErrS02FullScale                NOTIFY signalEventChangedErrS02FullScale                 )
    Q_PROPERTY(bool     mErrS02DigiValue                  READ getErrS02DigiValue                NOTIFY signalEventChangedErrS02DigiValue                 )
    Q_PROPERTY(bool     mErrS02ZeroAdjEnable              READ getErrS02ZeroAdjEnable            NOTIFY signalEventChangedErrS02ZeroAdjEnable             )
    Q_PROPERTY(bool     mErrS02ZeroAdjOffsetLimMin        READ getErrS02ZeroAdjOffsetLimMin      NOTIFY signalEventChangedErrS02ZeroAdjOffsetLimMin       )
    Q_PROPERTY(bool     mErrS02ZeroAdjOffsetLimMax        READ getErrS02ZeroAdjOffsetLimMax      NOTIFY signalEventChangedErrS02ZeroAdjOffsetLimMax       )
    Q_PROPERTY(bool     mErrS02ZeroAdjOffsetValue         READ getErrS02ZeroAdjOffsetValue       NOTIFY signalEventChangedErrS02ZeroAdjOffsetValue        )
    Q_PROPERTY(bool     mErrS02ScaleOffset                READ getErrS02ScaleOffset              NOTIFY signalEventChangedErrS02ScaleOffset               )
    Q_PROPERTY(bool     mErrS02Scale                      READ getErrS02Scale                    NOTIFY signalEventChangedErrS02Scale                     )
    Q_PROPERTY(bool     mErrS02ScaleZeroPoint             READ getErrS02ScaleZeroPoint           NOTIFY signalEventChangedErrS02ScaleZeroPoint            )
    Q_PROPERTY(bool     mErrS02FilterSec                  READ getErrS02FilterSec                NOTIFY signalEventChangedErrS02FilterSec                 )
    Q_PROPERTY(bool     mErrS02LogSensorLinearize         READ getErrS02LogSensorLinearize       NOTIFY signalEventChangedErrS02LogSensorLinearize        )
    Q_PROPERTY(bool     mErrS02LogSensorVoltPerDecade     READ getErrS02LogSensorVoltPerDecade   NOTIFY signalEventChangedErrS02LogSensorVoltPerDecade    )
    Q_PROPERTY(bool     mErrS02LogSensorVoltAtFullScale   READ getErrS02LogSensorVoltAtFullScale NOTIFY signalEventChangedErrS02LogSensorVoltAtFullScale  )
    Q_PROPERTY(bool     mErrCrossoverModIdx               READ getErrCrossoverModIdx             NOTIFY signalEventChangedErrCrossoverModIdx              )
    Q_PROPERTY(bool     mErrCrossoverLow                  READ getErrCrossoverLow                NOTIFY signalEventChangedErrCrossoverLow                 )
    Q_PROPERTY(bool     mErrCrossoverHigh                 READ getErrCrossoverHigh               NOTIFY signalEventChangedErrCrossoverHigh                )
    Q_PROPERTY(bool     mErrCrossoverDela                 READ getErrCrossoverDela               NOTIFY signalEventChangedErrCrossoverDela                )
    Q_PROPERTY(bool     mIsEdit                           READ getIsEdit                         NOTIFY signalEventChangedIsEdit                          )
    Q_PROPERTY(QString  mStrStatus                        READ getStrStatus                      NOTIFY signalEventChangedStrStatus                       )
    Q_PROPERTY(QString  mErrMsg                           READ getErrMsg                         NOTIFY signalEventChangedErrMsg                          )
    Q_PROPERTY(QString  mErrMsg2                          READ getErrMsg2                        NOTIFY signalEventChangedErrMsg2                         )
    Q_PROPERTY(int      mProgress                         READ getProgress                       NOTIFY signalEventChangedProgress                        )

public:
    int      mAccessMode                     = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test                    = false;
    bool     mIsSensor02Support              = false;
    int      mS01AnalActive                  = 0;
    int      mS01Selection                   = 0;
    int      mS01SourceIdx                   = 0;
    int      mS01UnitIdx                     = 0;
    QString  mS01FullScale                   = 0;
    QString  mS01DigiValue                   = 0;
    int      mS01ZeroAdjEnable               = 0;
    QString  mS01ZeroAdjOffsetLimMin         = 0;
    QString  mS01ZeroAdjOffsetLimMax         = 0;
    QString  mS01ZeroAdjOffsetValue          = 0;
    QString  mS01ScaleOffset                 = 0;
    QString  mS01Scale                       = 0;
    int      mS01ScaleZeroPoint              = 0;
    QString  mS01FilterSec                   = 0;
    int      mS01LogSensorLinearize          = 0;
    QString  mS01LogSensorVoltPerDecade      = 0;
    QString  mS01LogSensorVoltAtFullScale    = 0;
    int      mS02AnalActive                  = 0;
    int      mS02Selection                   = 0;
    int      mS02SourceIdx                   = 0;
    int      mS02UnitIdx                     = 0;
    QString  mS02FullScale                   = 0;
    QString  mS02DigiValue                   = 0;
    int      mS02ZeroAdjEnable               = 0;
    QString  mS02ZeroAdjOffsetLimMin         = 0;
    QString  mS02ZeroAdjOffsetLimMax         = 0;
    QString  mS02ZeroAdjOffsetValue          = 0;
    QString  mS02ScaleOffset                 = 0;
    QString  mS02Scale                       = 0;
    int      mS02ScaleZeroPoint              = 0;
    QString  mS02FilterSec                   = 0;
    int      mS02LogSensorLinearize          = 0;
    QString  mS02LogSensorVoltPerDecade      = 0;
    QString  mS02LogSensorVoltAtFullScale    = 0;
    int      mCrossoverModIdx                = 0;
    QString  mCrossoverLow                   = 0;
    QString  mCrossoverHigh                  = 0;
    QString  mCrossoverDela                  = 0;
    bool     mErrS01AnalActive               = false;
    bool     mErrS01Selection                = false;
    bool     mErrS01SourceIdx                = false;
    bool     mErrS01UnitIdx                  = false;
    bool     mErrS01FullScale                = false;
    bool     mErrS01DigiValue                = false;
    bool     mErrS01ZeroAdjEnable            = false;
    bool     mErrS01ZeroAdjOffsetLimMin      = false;
    bool     mErrS01ZeroAdjOffsetLimMax      = false;
    bool     mErrS01ZeroAdjOffsetValue       = false;
    bool     mErrS01ScaleOffset              = false;
    bool     mErrS01Scale                    = false;
    bool     mErrS01ScaleZeroPoint           = false;
    bool     mErrS01FilterSec                = false;
    bool     mErrS01LogSensorLinearize       = false;
    bool     mErrS01LogSensorVoltPerDecade   = false;
    bool     mErrS01LogSensorVoltAtFullScale = false;
    bool     mErrS02AnalActive               = false;
    bool     mErrS02Selection                = false;
    bool     mErrS02SourceIdx                = false;
    bool     mErrS02UnitIdx                  = false;
    bool     mErrS02FullScale                = false;
    bool     mErrS02DigiValue                = false;
    bool     mErrS02ZeroAdjEnable            = false;
    bool     mErrS02ZeroAdjOffsetLimMin      = false;
    bool     mErrS02ZeroAdjOffsetLimMax      = false;
    bool     mErrS02ZeroAdjOffsetValue       = false;
    bool     mErrS02ScaleOffset              = false;
    bool     mErrS02Scale                    = false;
    bool     mErrS02ScaleZeroPoint           = false;
    bool     mErrS02FilterSec                = false;
    bool     mErrS02LogSensorLinearize       = false;
    bool     mErrS02LogSensorVoltPerDecade   = false;
    bool     mErrS02LogSensorVoltAtFullScale = false;
    bool     mErrCrossoverModIdx             = false;
    bool     mErrCrossoverLow                = false;
    bool     mErrCrossoverHigh               = false;
    bool     mErrCrossoverDela               = false;
    bool     mIsEdit             = false;
    QString  mStrStatus          = "Loading";
    QString  mErrMsg             = "";
    QString  mErrMsg2            = "";
    int      mProgress           = 0 ;

    int      getAccessMode                    (){ return mAccessMode                    ; }
    bool     getIsRS232Test                   (){ return mIsRS232Test                   ; }
    bool     getIsSensor02Support             (){ return mIsSensor02Support             ; }
    int      getS01AnalActive                 (){ return mS01AnalActive                 ; }
    int      getS01Selection                  (){ return mS01Selection                  ; }
    int      getS01SourceIdx                  (){ return mS01SourceIdx                  ; }
    int      getS01UnitIdx                    (){ return mS01UnitIdx                    ; }
    QString  getS01FullScale                  (){ return mS01FullScale                  ; }
    QString  getS01DigiValue                  (){ return mS01DigiValue                  ; }
    int      getS01ZeroAdjEnable              (){ return mS01ZeroAdjEnable              ; }
    QString  getS01ZeroAdjOffsetLimMin        (){ return mS01ZeroAdjOffsetLimMin        ; }
    QString  getS01ZeroAdjOffsetLimMax        (){ return mS01ZeroAdjOffsetLimMax        ; }
    QString  getS01ZeroAdjOffsetValue         (){ return mS01ZeroAdjOffsetValue         ; }
    QString  getS01ScaleOffset                (){ return mS01ScaleOffset                ; }
    QString  getS01Scale                      (){ return mS01Scale                      ; }
    int      getS01ScaleZeroPoint             (){ return mS01ScaleZeroPoint             ; }
    QString  getS01FilterSec                  (){ return mS01FilterSec                  ; }
    int      getS01LogSensorLinearize         (){ return mS01LogSensorLinearize         ; }
    QString  getS01LogSensorVoltPerDecade     (){ return mS01LogSensorVoltPerDecade     ; }
    QString  getS01LogSensorVoltAtFullScale   (){ return mS01LogSensorVoltAtFullScale   ; }
    int      getS02AnalActive                 (){ return mS02AnalActive                 ; }
    int      getS02Selection                  (){ return mS02Selection                  ; }
    int      getS02SourceIdx                  (){ return mS02SourceIdx                  ; }
    int      getS02UnitIdx                    (){ return mS02UnitIdx                    ; }
    QString  getS02FullScale                  (){ return mS02FullScale                  ; }
    QString  getS02DigiValue                  (){ return mS02DigiValue                  ; }
    int      getS02ZeroAdjEnable              (){ return mS02ZeroAdjEnable              ; }
    QString  getS02ZeroAdjOffsetLimMin        (){ return mS02ZeroAdjOffsetLimMin        ; }
    QString  getS02ZeroAdjOffsetLimMax        (){ return mS02ZeroAdjOffsetLimMax        ; }
    QString  getS02ZeroAdjOffsetValue         (){ return mS02ZeroAdjOffsetValue         ; }
    QString  getS02ScaleOffset                (){ return mS02ScaleOffset                ; }
    QString  getS02Scale                      (){ return mS02Scale                      ; }
    int      getS02ScaleZeroPoint             (){ return mS02ScaleZeroPoint             ; }
    QString  getS02FilterSec                  (){ return mS02FilterSec                  ; }
    int      getS02LogSensorLinearize         (){ return mS02LogSensorLinearize         ; }
    QString  getS02LogSensorVoltPerDecade     (){ return mS02LogSensorVoltPerDecade     ; }
    QString  getS02LogSensorVoltAtFullScale   (){ return mS02LogSensorVoltAtFullScale   ; }
    int      getCrossoverModIdx               (){ return mCrossoverModIdx               ; }
    QString  getCrossoverLow                  (){ return mCrossoverLow                  ; }
    QString  getCrossoverHigh                 (){ return mCrossoverHigh                 ; }
    QString  getCrossoverDela                 (){ return mCrossoverDela                 ; }
    bool     getErrS01AnalActive              (){ return mErrS01AnalActive              ; }
    bool     getErrS01Selection               (){ return mErrS01Selection               ; }
    bool     getErrS01SourceIdx               (){ return mErrS01SourceIdx               ; }
    bool     getErrS01UnitIdx                 (){ return mErrS01UnitIdx                 ; }
    bool     getErrS01FullScale               (){ return mErrS01FullScale               ; }
    bool     getErrS01DigiValue               (){ return mErrS01DigiValue               ; }
    bool     getErrS01ZeroAdjEnable           (){ return mErrS01ZeroAdjEnable           ; }
    bool     getErrS01ZeroAdjOffsetLimMin     (){ return mErrS01ZeroAdjOffsetLimMin     ; }
    bool     getErrS01ZeroAdjOffsetLimMax     (){ return mErrS01ZeroAdjOffsetLimMax     ; }
    bool     getErrS01ZeroAdjOffsetValue      (){ return mErrS01ZeroAdjOffsetValue      ; }
    bool     getErrS01ScaleOffset             (){ return mErrS01ScaleOffset             ; }
    bool     getErrS01Scale                   (){ return mErrS01Scale                   ; }
    bool     getErrS01ScaleZeroPoint          (){ return mErrS01ScaleZeroPoint          ; }
    bool     getErrS01FilterSec               (){ return mErrS01FilterSec               ; }
    bool     getErrS01LogSensorLinearize      (){ return mErrS01LogSensorLinearize      ; }
    bool     getErrS01LogSensorVoltPerDecade  (){ return mErrS01LogSensorVoltPerDecade  ; }
    bool     getErrS01LogSensorVoltAtFullScale(){ return mErrS01LogSensorVoltAtFullScale; }
    bool     getErrS02AnalActive              (){ return mErrS02AnalActive              ; }
    bool     getErrS02Selection               (){ return mErrS02Selection               ; }
    bool     getErrS02SourceIdx               (){ return mErrS02SourceIdx               ; }
    bool     getErrS02UnitIdx                 (){ return mErrS02UnitIdx                 ; }
    bool     getErrS02FullScale               (){ return mErrS02FullScale               ; }
    bool     getErrS02DigiValue               (){ return mErrS02DigiValue               ; }
    bool     getErrS02ZeroAdjEnable           (){ return mErrS02ZeroAdjEnable           ; }
    bool     getErrS02ZeroAdjOffsetLimMin     (){ return mErrS02ZeroAdjOffsetLimMin     ; }
    bool     getErrS02ZeroAdjOffsetLimMax     (){ return mErrS02ZeroAdjOffsetLimMax     ; }
    bool     getErrS02ZeroAdjOffsetValue      (){ return mErrS02ZeroAdjOffsetValue      ; }
    bool     getErrS02ScaleOffset             (){ return mErrS02ScaleOffset             ; }
    bool     getErrS02Scale                   (){ return mErrS02Scale                   ; }
    bool     getErrS02ScaleZeroPoint          (){ return mErrS02ScaleZeroPoint          ; }
    bool     getErrS02FilterSec               (){ return mErrS02FilterSec               ; }
    bool     getErrS02LogSensorLinearize      (){ return mErrS02LogSensorLinearize      ; }
    bool     getErrS02LogSensorVoltPerDecade  (){ return mErrS02LogSensorVoltPerDecade  ; }
    bool     getErrS02LogSensorVoltAtFullScale(){ return mErrS02LogSensorVoltAtFullScale; }
    bool     getErrCrossoverModIdx            (){ return mErrCrossoverModIdx            ; }
    bool     getErrCrossoverLow               (){ return mErrCrossoverLow               ; }
    bool     getErrCrossoverHigh              (){ return mErrCrossoverHigh              ; }
    bool     getErrCrossoverDela              (){ return mErrCrossoverDela              ; }
    bool     getIsEdit           (){ return mIsEdit           ; }
    QString  getStrStatus        (){ return mStrStatus        ; }
    QString  getErrMsg           (){ return mErrMsg           ; }
    QString  getErrMsg2          (){ return mErrMsg2          ; }
    int      getProgress         (){ return mProgress         ; }

    void    setAccessMode                    (int     value){ if(mAccessMode                     == value) return; mAccessMode                     = value; emit signalEventChangedAccessMode                    (value);}
    void    setIsRS232Test                   (bool    value){ if(mIsRS232Test                    == value) return; mIsRS232Test                    = value; emit signalEventChangedIsRS232Test                   (value);}
    void    setIsSensor02Support             (bool    value){ if(mIsSensor02Support              == value) return; mIsSensor02Support              = value; emit signalEventChangedIsSensor02Support             (value);}
    void    setS01AnalActive                 (int     value){ if(mS01AnalActive                  == value) return; mS01AnalActive                  = value; emit signalEventChangedS01AnalActive                 (value);}
    void    setS01Selection                  (int     value){ if(mS01Selection                   == value) return; mS01Selection                   = value; emit signalEventChangedS01Selection                  (value);}
    void    setS01SourceIdx                  (int     value){ if(mS01SourceIdx                   == value) return; mS01SourceIdx                   = value; emit signalEventChangedS01SourceIdx                  (value);}
    void    setS01UnitIdx                    (int     value){ if(mS01UnitIdx                     == value) return; mS01UnitIdx                     = value; emit signalEventChangedS01UnitIdx                    (value);}
    void    setS01FullScale                  (QString value){ if(mS01FullScale                   == value) return; mS01FullScale                   = value; emit signalEventChangedS01FullScale                  (value);}
    void    setS01DigiValue                  (QString value){ if(mS01DigiValue                   == value) return; mS01DigiValue                   = value; emit signalEventChangedS01DigiValue                  (value);}
    void    setS01ZeroAdjEnable              (int     value){ if(mS01ZeroAdjEnable               == value) return; mS01ZeroAdjEnable               = value; emit signalEventChangedS01ZeroAdjEnable              (value);}
    void    setS01ZeroAdjOffsetLimMin        (QString value){ if(mS01ZeroAdjOffsetLimMin         == value) return; mS01ZeroAdjOffsetLimMin         = value; emit signalEventChangedS01ZeroAdjOffsetLimMin        (value);}
    void    setS01ZeroAdjOffsetLimMax        (QString value){ if(mS01ZeroAdjOffsetLimMax         == value) return; mS01ZeroAdjOffsetLimMax         = value; emit signalEventChangedS01ZeroAdjOffsetLimMax        (value);}
    void    setS01ZeroAdjOffsetValue         (QString value){ if(mS01ZeroAdjOffsetValue          == value) return; mS01ZeroAdjOffsetValue          = value; emit signalEventChangedS01ZeroAdjOffsetValue         (value);}
    void    setS01ScaleOffset                (QString value){ if(mS01ScaleOffset                 == value) return; mS01ScaleOffset                 = value; emit signalEventChangedS01ScaleOffset                (value);}
    void    setS01Scale                      (QString value){ if(mS01Scale                       == value) return; mS01Scale                       = value; emit signalEventChangedS01Scale                      (value);}
    void    setS01ScaleZeroPoint             (int     value){ if(mS01ScaleZeroPoint              == value) return; mS01ScaleZeroPoint              = value; emit signalEventChangedS01ScaleZeroPoint             (value);}
    void    setS01FilterSec                  (QString value){ if(mS01FilterSec                   == value) return; mS01FilterSec                   = value; emit signalEventChangedS01FilterSec                  (value);}
    void    setS01LogSensorLinearize         (int     value){ if(mS01LogSensorLinearize          == value) return; mS01LogSensorLinearize          = value; emit signalEventChangedS01LogSensorLinearize         (value);}
    void    setS01LogSensorVoltPerDecade     (QString value){ if(mS01LogSensorVoltPerDecade      == value) return; mS01LogSensorVoltPerDecade      = value; emit signalEventChangedS01LogSensorVoltPerDecade     (value);}
    void    setS01LogSensorVoltAtFullScale   (QString value){ if(mS01LogSensorVoltAtFullScale    == value) return; mS01LogSensorVoltAtFullScale    = value; emit signalEventChangedS01LogSensorVoltAtFullScale   (value);}
    void    setS02AnalActive                 (int     value){ if(mS02AnalActive                  == value) return; mS02AnalActive                  = value; emit signalEventChangedS02AnalActive                 (value);}
    void    setS02Selection                  (int     value){ if(mS02Selection                   == value) return; mS02Selection                   = value; emit signalEventChangedS02Selection                  (value);}
    void    setS02SourceIdx                  (int     value){ if(mS02SourceIdx                   == value) return; mS02SourceIdx                   = value; emit signalEventChangedS02SourceIdx                  (value);}
    void    setS02UnitIdx                    (int     value){ if(mS02UnitIdx                     == value) return; mS02UnitIdx                     = value; emit signalEventChangedS02UnitIdx                    (value);}
    void    setS02FullScale                  (QString value){ if(mS02FullScale                   == value) return; mS02FullScale                   = value; emit signalEventChangedS02FullScale                  (value);}
    void    setS02DigiValue                  (QString value){ if(mS02DigiValue                   == value) return; mS02DigiValue                   = value; emit signalEventChangedS02DigiValue                  (value);}
    void    setS02ZeroAdjEnable              (int     value){ if(mS02ZeroAdjEnable               == value) return; mS02ZeroAdjEnable               = value; emit signalEventChangedS02ZeroAdjEnable              (value);}
    void    setS02ZeroAdjOffsetLimMin        (QString value){ if(mS02ZeroAdjOffsetLimMin         == value) return; mS02ZeroAdjOffsetLimMin         = value; emit signalEventChangedS02ZeroAdjOffsetLimMin        (value);}
    void    setS02ZeroAdjOffsetLimMax        (QString value){ if(mS02ZeroAdjOffsetLimMax         == value) return; mS02ZeroAdjOffsetLimMax         = value; emit signalEventChangedS02ZeroAdjOffsetLimMax        (value);}
    void    setS02ZeroAdjOffsetValue         (QString value){ if(mS02ZeroAdjOffsetValue          == value) return; mS02ZeroAdjOffsetValue          = value; emit signalEventChangedS02ZeroAdjOffsetValue         (value);}
    void    setS02ScaleOffset                (QString value){ if(mS02ScaleOffset                 == value) return; mS02ScaleOffset                 = value; emit signalEventChangedS02ScaleOffset                (value);}
    void    setS02Scale                      (QString value){ if(mS02Scale                       == value) return; mS02Scale                       = value; emit signalEventChangedS02Scale                      (value);}
    void    setS02ScaleZeroPoint             (int     value){ if(mS02ScaleZeroPoint              == value) return; mS02ScaleZeroPoint              = value; emit signalEventChangedS02ScaleZeroPoint             (value);}
    void    setS02FilterSec                  (QString value){ if(mS02FilterSec                   == value) return; mS02FilterSec                   = value; emit signalEventChangedS02FilterSec                  (value);}
    void    setS02LogSensorLinearize         (int     value){ if(mS02LogSensorLinearize          == value) return; mS02LogSensorLinearize          = value; emit signalEventChangedS02LogSensorLinearize         (value);}
    void    setS02LogSensorVoltPerDecade     (QString value){ if(mS02LogSensorVoltPerDecade      == value) return; mS02LogSensorVoltPerDecade      = value; emit signalEventChangedS02LogSensorVoltPerDecade     (value);}
    void    setS02LogSensorVoltAtFullScale   (QString value){ if(mS02LogSensorVoltAtFullScale    == value) return; mS02LogSensorVoltAtFullScale    = value; emit signalEventChangedS02LogSensorVoltAtFullScale   (value);}
    void    setCrossoverModIdx               (int     value){ if(mCrossoverModIdx                == value) return; mCrossoverModIdx                = value; emit signalEventChangedCrossoverModIdx               (value);}
    void    setCrossoverLow                  (QString value){ if(mCrossoverLow                   == value) return; mCrossoverLow                   = value; emit signalEventChangedCrossoverLow                  (value);}
    void    setCrossoverHigh                 (QString value){ if(mCrossoverHigh                  == value) return; mCrossoverHigh                  = value; emit signalEventChangedCrossoverHigh                 (value);}
    void    setCrossoverDela                 (QString value){ if(mCrossoverDela                  == value) return; mCrossoverDela                  = value; emit signalEventChangedCrossoverDela                 (value);}
    void    setErrS01AnalActive              (bool    value){ if(mErrS01AnalActive               == value) return; mErrS01AnalActive               = value; emit signalEventChangedErrS01AnalActive              (value);}
    void    setErrS01Selection               (bool    value){ if(mErrS01Selection                == value) return; mErrS01Selection                = value; emit signalEventChangedErrS01Selection               (value);}
    void    setErrS01SourceIdx               (bool    value){ if(mErrS01SourceIdx                == value) return; mErrS01SourceIdx                = value; emit signalEventChangedErrS01SourceIdx               (value);}
    void    setErrS01UnitIdx                 (bool    value){ if(mErrS01UnitIdx                  == value) return; mErrS01UnitIdx                  = value; emit signalEventChangedErrS01UnitIdx                 (value);}
    void    setErrS01FullScale               (bool    value){ if(mErrS01FullScale                == value) return; mErrS01FullScale                = value; emit signalEventChangedErrS01FullScale               (value);}
    void    setErrS01DigiValue               (bool    value){ if(mErrS01DigiValue                == value) return; mErrS01DigiValue                = value; emit signalEventChangedErrS01DigiValue               (value);}
    void    setErrS01ZeroAdjEnable           (bool    value){ if(mErrS01ZeroAdjEnable            == value) return; mErrS01ZeroAdjEnable            = value; emit signalEventChangedErrS01ZeroAdjEnable           (value);}
    void    setErrS01ZeroAdjOffsetLimMin     (bool    value){ if(mErrS01ZeroAdjOffsetLimMin      == value) return; mErrS01ZeroAdjOffsetLimMin      = value; emit signalEventChangedErrS01ZeroAdjOffsetLimMin     (value);}
    void    setErrS01ZeroAdjOffsetLimMax     (bool    value){ if(mErrS01ZeroAdjOffsetLimMax      == value) return; mErrS01ZeroAdjOffsetLimMax      = value; emit signalEventChangedErrS01ZeroAdjOffsetLimMax     (value);}
    void    setErrS01ZeroAdjOffsetValue      (bool    value){ if(mErrS01ZeroAdjOffsetValue       == value) return; mErrS01ZeroAdjOffsetValue       = value; emit signalEventChangedErrS01ZeroAdjOffsetValue      (value);}
    void    setErrS01ScaleOffset             (bool    value){ if(mErrS01ScaleOffset              == value) return; mErrS01ScaleOffset              = value; emit signalEventChangedErrS01ScaleOffset             (value);}
    void    setErrS01Scale                   (bool    value){ if(mErrS01Scale                    == value) return; mErrS01Scale                    = value; emit signalEventChangedErrS01Scale                   (value);}
    void    setErrS01ScaleZeroPoint          (bool    value){ if(mErrS01ScaleZeroPoint           == value) return; mErrS01ScaleZeroPoint           = value; emit signalEventChangedErrS01ScaleZeroPoint          (value);}
    void    setErrS01FilterSec               (bool    value){ if(mErrS01FilterSec                == value) return; mErrS01FilterSec                = value; emit signalEventChangedErrS01FilterSec               (value);}
    void    setErrS01LogSensorLinearize      (bool    value){ if(mErrS01LogSensorLinearize       == value) return; mErrS01LogSensorLinearize       = value; emit signalEventChangedErrS01LogSensorLinearize      (value);}
    void    setErrS01LogSensorVoltPerDecade  (bool    value){ if(mErrS01LogSensorVoltPerDecade   == value) return; mErrS01LogSensorVoltPerDecade   = value; emit signalEventChangedErrS01LogSensorVoltPerDecade  (value);}
    void    setErrS01LogSensorVoltAtFullScale(bool    value){ if(mErrS01LogSensorVoltAtFullScale == value) return; mErrS01LogSensorVoltAtFullScale = value; emit signalEventChangedErrS01LogSensorVoltAtFullScale(value);}
    void    setErrS02AnalActive              (bool    value){ if(mErrS02AnalActive               == value) return; mErrS02AnalActive               = value; emit signalEventChangedErrS02AnalActive              (value);}
    void    setErrS02Selection               (bool    value){ if(mErrS02Selection                == value) return; mErrS02Selection                = value; emit signalEventChangedErrS02Selection               (value);}
    void    setErrS02SourceIdx               (bool    value){ if(mErrS02SourceIdx                == value) return; mErrS02SourceIdx                = value; emit signalEventChangedErrS02SourceIdx               (value);}
    void    setErrS02UnitIdx                 (bool    value){ if(mErrS02UnitIdx                  == value) return; mErrS02UnitIdx                  = value; emit signalEventChangedErrS02UnitIdx                 (value);}
    void    setErrS02FullScale               (bool    value){ if(mErrS02FullScale                == value) return; mErrS02FullScale                = value; emit signalEventChangedErrS02FullScale               (value);}
    void    setErrS02DigiValue               (bool    value){ if(mErrS02DigiValue                == value) return; mErrS02DigiValue                = value; emit signalEventChangedErrS02DigiValue               (value);}
    void    setErrS02ZeroAdjEnable           (bool    value){ if(mErrS02ZeroAdjEnable            == value) return; mErrS02ZeroAdjEnable            = value; emit signalEventChangedErrS02ZeroAdjEnable           (value);}
    void    setErrS02ZeroAdjOffsetLimMin     (bool    value){ if(mErrS02ZeroAdjOffsetLimMin      == value) return; mErrS02ZeroAdjOffsetLimMin      = value; emit signalEventChangedErrS02ZeroAdjOffsetLimMin     (value);}
    void    setErrS02ZeroAdjOffsetLimMax     (bool    value){ if(mErrS02ZeroAdjOffsetLimMax      == value) return; mErrS02ZeroAdjOffsetLimMax      = value; emit signalEventChangedErrS02ZeroAdjOffsetLimMax     (value);}
    void    setErrS02ZeroAdjOffsetValue      (bool    value){ if(mErrS02ZeroAdjOffsetValue       == value) return; mErrS02ZeroAdjOffsetValue       = value; emit signalEventChangedErrS02ZeroAdjOffsetValue      (value);}
    void    setErrS02ScaleOffset             (bool    value){ if(mErrS02ScaleOffset              == value) return; mErrS02ScaleOffset              = value; emit signalEventChangedErrS02ScaleOffset             (value);}
    void    setErrS02Scale                   (bool    value){ if(mErrS02Scale                    == value) return; mErrS02Scale                    = value; emit signalEventChangedErrS02Scale                   (value);}
    void    setErrS02ScaleZeroPoint          (bool    value){ if(mErrS02ScaleZeroPoint           == value) return; mErrS02ScaleZeroPoint           = value; emit signalEventChangedErrS02ScaleZeroPoint          (value);}
    void    setErrS02FilterSec               (bool    value){ if(mErrS02FilterSec                == value) return; mErrS02FilterSec                = value; emit signalEventChangedErrS02FilterSec               (value);}
    void    setErrS02LogSensorLinearize      (bool    value){ if(mErrS02LogSensorLinearize       == value) return; mErrS02LogSensorLinearize       = value; emit signalEventChangedErrS02LogSensorLinearize      (value);}
    void    setErrS02LogSensorVoltPerDecade  (bool    value){ if(mErrS02LogSensorVoltPerDecade   == value) return; mErrS02LogSensorVoltPerDecade   = value; emit signalEventChangedErrS02LogSensorVoltPerDecade  (value);}
    void    setErrS02LogSensorVoltAtFullScale(bool    value){ if(mErrS02LogSensorVoltAtFullScale == value) return; mErrS02LogSensorVoltAtFullScale = value; emit signalEventChangedErrS02LogSensorVoltAtFullScale(value);}
    void    setErrCrossoverModIdx            (bool    value){ if(mErrCrossoverModIdx             == value) return; mErrCrossoverModIdx             = value; emit signalEventChangedErrCrossoverModIdx            (value);}
    void    setErrCrossoverLow               (bool    value){ if(mErrCrossoverLow                == value) return; mErrCrossoverLow                = value; emit signalEventChangedErrCrossoverLow               (value);}
    void    setErrCrossoverHigh              (bool    value){ if(mErrCrossoverHigh               == value) return; mErrCrossoverHigh               = value; emit signalEventChangedErrCrossoverHigh              (value);}
    void    setErrCrossoverDela              (bool    value){ if(mErrCrossoverDela               == value) return; mErrCrossoverDela               = value; emit signalEventChangedErrCrossoverDela              (value);}
    void    setIsEdit                        (bool    value){ if(mIsEdit                         == value)return; mIsEdit                          = value; emit signalEventChangedIsEdit                        (value);}
    void    setStrStatus                     (QString value){ if(mStrStatus                      == value)return; mStrStatus                       = value; emit signalEventChangedStrStatus                     (value);}
    void    setErrMsg                        (QString value){ if(mErrMsg                         == value)return; mErrMsg                          = value; emit signalEventChangedErrMsg                        (value);}
    void    setErrMsg2                       (QString value){ if(mErrMsg2                        == value)return; mErrMsg2                         = value; emit signalEventChangedErrMsg2                       (value);}
    void    setProgress                      (int     value){ if(mProgress                       == value)return; mProgress                        = value; emit signalEventChangedProgress                      (value);}

signals:
    void signalEventChangedAccessMode                    (int     value);
    void signalEventChangedIsRS232Test                   (bool    value);
    void signalEventChangedIsSensor02Support             (bool    value);
    void signalEventChangedS01AnalActive                 (int     value);
    void signalEventChangedS01Selection                  (int     value);
    void signalEventChangedS01SourceIdx                  (int     value);
    void signalEventChangedS01UnitIdx                    (int     value);
    void signalEventChangedS01FullScale                  (QString value);
    void signalEventChangedS01DigiValue                  (QString value);
    void signalEventChangedS01ZeroAdjEnable              (int     value);
    void signalEventChangedS01ZeroAdjOffsetLimMin        (QString value);
    void signalEventChangedS01ZeroAdjOffsetLimMax        (QString value);
    void signalEventChangedS01ZeroAdjOffsetValue         (QString value);
    void signalEventChangedS01ScaleOffset                (QString value);
    void signalEventChangedS01Scale                      (QString value);
    void signalEventChangedS01ScaleZeroPoint             (int     value);
    void signalEventChangedS01FilterSec                  (QString value);
    void signalEventChangedS01LogSensorLinearize         (int     value);
    void signalEventChangedS01LogSensorVoltPerDecade     (QString value);
    void signalEventChangedS01LogSensorVoltAtFullScale   (QString value);
    void signalEventChangedS02AnalActive                 (int     value);
    void signalEventChangedS02Selection                  (int     value);
    void signalEventChangedS02SourceIdx                  (int     value);
    void signalEventChangedS02UnitIdx                    (int     value);
    void signalEventChangedS02FullScale                  (QString value);
    void signalEventChangedS02DigiValue                  (QString value);
    void signalEventChangedS02ZeroAdjEnable              (int     value);
    void signalEventChangedS02ZeroAdjOffsetLimMin        (QString value);
    void signalEventChangedS02ZeroAdjOffsetLimMax        (QString value);
    void signalEventChangedS02ZeroAdjOffsetValue         (QString value);
    void signalEventChangedS02ScaleOffset                (QString value);
    void signalEventChangedS02Scale                      (QString value);
    void signalEventChangedS02ScaleZeroPoint             (int     value);
    void signalEventChangedS02FilterSec                  (QString value);
    void signalEventChangedS02LogSensorLinearize         (int     value);
    void signalEventChangedS02LogSensorVoltPerDecade     (QString value);
    void signalEventChangedS02LogSensorVoltAtFullScale   (QString value);
    void signalEventChangedCrossoverModIdx               (int     value);
    void signalEventChangedCrossoverLow                  (QString value);
    void signalEventChangedCrossoverHigh                 (QString value);
    void signalEventChangedCrossoverDela                 (QString value);
    void signalEventChangedErrS01AnalActive              (bool    value);
    void signalEventChangedErrS01Selection               (bool    value);
    void signalEventChangedErrS01SourceIdx               (bool    value);
    void signalEventChangedErrS01UnitIdx                 (bool    value);
    void signalEventChangedErrS01FullScale               (bool    value);
    void signalEventChangedErrS01DigiValue               (bool    value);
    void signalEventChangedErrS01ZeroAdjEnable           (bool    value);
    void signalEventChangedErrS01ZeroAdjOffsetLimMin     (bool    value);
    void signalEventChangedErrS01ZeroAdjOffsetLimMax     (bool    value);
    void signalEventChangedErrS01ZeroAdjOffsetValue      (bool    value);
    void signalEventChangedErrS01ScaleOffset             (bool    value);
    void signalEventChangedErrS01Scale                   (bool    value);
    void signalEventChangedErrS01ScaleZeroPoint          (bool    value);
    void signalEventChangedErrS01FilterSec               (bool    value);
    void signalEventChangedErrS01LogSensorLinearize      (bool    value);
    void signalEventChangedErrS01LogSensorVoltPerDecade  (bool    value);
    void signalEventChangedErrS01LogSensorVoltAtFullScale(bool    value);
    void signalEventChangedErrS02AnalActive              (bool    value);
    void signalEventChangedErrS02Selection               (bool    value);
    void signalEventChangedErrS02SourceIdx               (bool    value);
    void signalEventChangedErrS02UnitIdx                 (bool    value);
    void signalEventChangedErrS02FullScale               (bool    value);
    void signalEventChangedErrS02DigiValue               (bool    value);
    void signalEventChangedErrS02ZeroAdjEnable           (bool    value);
    void signalEventChangedErrS02ZeroAdjOffsetLimMin     (bool    value);
    void signalEventChangedErrS02ZeroAdjOffsetLimMax     (bool    value);
    void signalEventChangedErrS02ZeroAdjOffsetValue      (bool    value);
    void signalEventChangedErrS02ScaleOffset             (bool    value);
    void signalEventChangedErrS02Scale                   (bool    value);
    void signalEventChangedErrS02ScaleZeroPoint          (bool    value);
    void signalEventChangedErrS02FilterSec               (bool    value);
    void signalEventChangedErrS02LogSensorLinearize      (bool    value);
    void signalEventChangedErrS02LogSensorVoltPerDecade  (bool    value);
    void signalEventChangedErrS02LogSensorVoltAtFullScale(bool    value);
    void signalEventChangedErrCrossoverModIdx            (bool    value);
    void signalEventChangedErrCrossoverLow               (bool    value);
    void signalEventChangedErrCrossoverHigh              (bool    value);
    void signalEventChangedErrCrossoverDela              (bool    value);
    void signalEventChangedIsEdit                        (bool    value);
    void signalEventChangedStrStatus                     (QString value);
    void signalEventChangedErrMsg                        (QString value);
    void signalEventChangedErrMsg2                       (QString value);
    void signalEventChangedProgress                      (int     value);
    void signalEventCompletedLoad                        (             );
    void signalEventCompletedApply                       (             );
    void signalEventOccurErr                             (             );

public:
    explicit SensorSetupExDlgModel(QObject *parent = nullptr): QObject(parent)
    {

        ENABLE_SLOT_VALVE_CHANGED_ACCESS                            ;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST                     ;
        ENABLE_SLOT_VALVE_CHANGED_SENSOR_VERSION                    ;
        ENABLE_SLOT_VALVE_READED_SENSEX_SEL                         ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_ANAL_ACTIVE             ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_SRC                     ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_UNIT                    ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_FULLSCALE               ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_DIGI                    ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_ENABLE             ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_MIN                ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_MAX                ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_VALUE              ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_SCALE_OFFSET            ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_SCALE                   ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_SCALE_Z_POINT           ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_FILTER_SEC              ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_LOG_SENS_LINEARIZE      ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_LOG_SENS_VOLT_DECADE    ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_ANAL_ACTIVE             ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_SRC                     ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_UNIT                    ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_FULLSCALE               ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_DIGI                    ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_ENABLE             ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_MIN                ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_MAX                ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_VALUE              ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_SCALE_OFFSET            ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_SCALE                   ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_SCALE_Z_POINT           ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_FILTER_SEC              ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_LOG_SENS_LINEARIZE      ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_LOG_SENS_VOLT_DECADE    ;
        ENABLE_SLOT_VALVE_READED_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE ;
        ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_MOD               ;
        ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_LOW               ;
        ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_HIGH              ;
        ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_DELA              ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_SEL                        ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ANAL_ACTIVE            ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SRC                    ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_UNIT                   ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_FULLSCALE              ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_DIGI                   ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_ENABLE            ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_MIN               ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_MAX               ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_VALUE             ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SCALE_OFFSET           ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SCALE                  ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SCALE_Z_POINT          ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_FILTER_SEC             ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_LOG_SENS_LINEARIZE     ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_LOG_SENS_VOLT_DECADE   ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ANAL_ACTIVE            ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SRC                    ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_UNIT                   ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_FULLSCALE              ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_DIGI                   ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_ENABLE            ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_MIN               ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_MAX               ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_VALUE             ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SCALE_OFFSET           ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SCALE                  ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SCALE_Z_POINT          ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_FILTER_SEC             ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_LOG_SENS_LINEARIZE     ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_LOG_SENS_VOLT_DECADE   ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_MOD              ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_LOW              ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_HIGH             ;
        ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_DELA             ;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedSensorVersion();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_SELECTION);
    }
    ~SensorSetupExDlgModel()
    {
        pValveSP->reLoad();
    }


public slots:
    Q_INVOKABLE QString onCommandCheckDigitalValue(QString fullScale, QString inputDigiStr)
    {
        QString protocolDigiValue = QString("%1").arg(qRound((inputDigiStr.toDouble() * 1000000.0)/ fullScale.toDouble()));

        return QString::number(((protocolDigiValue.toDouble() * fullScale.toDouble()) / 1000000), 'f', 6);

    }

    Q_INVOKABLE void onCommandSetEdit                           (bool value){setIsEdit(value)                       ;}
    Q_INVOKABLE void onCommandSetEditSelection                  (          ){mEditSelection                   = true;}
    Q_INVOKABLE void onCommandSetEditS01AnalActive              (          ){mEditS01AnalActive               = true;}
    Q_INVOKABLE void onCommandSetEditS01SourceIdx               (          ){mEditS01SourceIdx                = true;}
    Q_INVOKABLE void onCommandSetEditS01UnitIdx                 (          ){mEditS01UnitIdx                  = true;}
    Q_INVOKABLE void onCommandSetEditS01FullScale               (          ){mEditS01FullScale                = true;}
    Q_INVOKABLE void onCommandSetEditS01DigiValue               (          ){mEditS01DigiValue                = true;}
    Q_INVOKABLE void onCommandSetEditS01ZeroAdjEnable           (          ){mEditS01ZeroAdjEnable            = true;}
    Q_INVOKABLE void onCommandSetEditS01ZeroAdjOffsetLimMin     (          ){mEditS01ZeroAdjOffsetLimMin      = true;}
    Q_INVOKABLE void onCommandSetEditS01ZeroAdjOffsetLimMax     (          ){mEditS01ZeroAdjOffsetLimMax      = true;}
    Q_INVOKABLE void onCommandSetEditS01ZeroAdjOffsetValue      (          ){mEditS01ZeroAdjOffsetValue       = true;}
    Q_INVOKABLE void onCommandSetEditS01ScaleOffset             (          ){mEditS01ScaleOffset              = true;}
    Q_INVOKABLE void onCommandSetEditS01Scale                   (          ){mEditS01Scale                    = true;}
    Q_INVOKABLE void onCommandSetEditS01ScaleZeroPoint          (          ){mEditS01ScaleZeroPoint           = true;}
    Q_INVOKABLE void onCommandSetEditS01FilterSec               (          ){mEditS01FilterSec                = true;}
    Q_INVOKABLE void onCommandSetEditS01LogSensorLinearize      (          ){mEditS01LogSensorLinearize       = true;}
    Q_INVOKABLE void onCommandSetEditS01LogSensorVoltPerDecade  (          ){mEditS01LogSensorVoltPerDecade   = true;}
    Q_INVOKABLE void onCommandSetEditS01LogSensorVoltAtFullScale(          ){mEditS01LogSensorVoltAtFullScale = true;}
    Q_INVOKABLE void onCommandSetEditS02AnalActive              (          ){mEditS02AnalActive               = true;}
    Q_INVOKABLE void onCommandSetEditS02SourceIdx               (          ){mEditS02SourceIdx                = true;}
    Q_INVOKABLE void onCommandSetEditS02UnitIdx                 (          ){mEditS02UnitIdx                  = true;}
    Q_INVOKABLE void onCommandSetEditS02FullScale               (          ){mEditS02FullScale                = true;}
    Q_INVOKABLE void onCommandSetEditS02DigiValue               (          ){mEditS02DigiValue                = true;}
    Q_INVOKABLE void onCommandSetEditS02ZeroAdjEnable           (          ){mEditS02ZeroAdjEnable            = true;}
    Q_INVOKABLE void onCommandSetEditS02ZeroAdjOffsetLimMin     (          ){mEditS02ZeroAdjOffsetLimMin      = true;}
    Q_INVOKABLE void onCommandSetEditS02ZeroAdjOffsetLimMax     (          ){mEditS02ZeroAdjOffsetLimMax      = true;}
    Q_INVOKABLE void onCommandSetEditS02ZeroAdjOffsetValue      (          ){mEditS02ZeroAdjOffsetValue       = true;}
    Q_INVOKABLE void onCommandSetEditS02ScaleOffset             (          ){mEditS02ScaleOffset              = true;}
    Q_INVOKABLE void onCommandSetEditS02Scale                   (          ){mEditS02Scale                    = true;}
    Q_INVOKABLE void onCommandSetEditS02ScaleZeroPoint          (          ){mEditS02ScaleZeroPoint           = true;}
    Q_INVOKABLE void onCommandSetEditS02FilterSec               (          ){mEditS02FilterSec                = true;}
    Q_INVOKABLE void onCommandSetEditS02LogSensorLinearize      (          ){mEditS02LogSensorLinearize       = true;}
    Q_INVOKABLE void onCommandSetEditS02LogSensorVoltPerDecade  (          ){mEditS02LogSensorVoltPerDecade   = true;}
    Q_INVOKABLE void onCommandSetEditS02LogSensorVoltAtFullScale(          ){mEditS02LogSensorVoltAtFullScale = true;}
    Q_INVOKABLE void onCommandSetEditCrossoverModIdx            (          ){mEditCrossoverModIdx             = true;}
    Q_INVOKABLE void onCommandSetEditCrossoverLow               (          ){mEditCrossoverLow                = true;}
    Q_INVOKABLE void onCommandSetEditCrossoverHigh              (          ){mEditCrossoverHigh               = true;}
    Q_INVOKABLE void onCommandSetEditCrossoverDela              (          ){mEditCrossoverDela               = true;}

    Q_INVOKABLE void onCommandApply(int     s01AnalActive              ,
                                    int     s01Selection               ,
                                    int     s01SourceIdx               ,
                                    int     s01UnitIdx                 ,
                                    QString s01FullScale               ,
                                    QString s01DigiValue               ,
                                    int     s01ZeroAdjEnable           ,
                                    QString s01ZeroAdjOffsetLimMin     ,
                                    QString s01ZeroAdjOffsetLimMax     ,
                                    QString s01ZeroAdjOffsetValue      ,
                                    QString s01ScaleOffset             ,
                                    QString s01Scale                   ,
                                    int     s01ScaleZeroPoint          ,
                                    QString s01FilterSec               ,
                                    int     s01LogSensorLinearize      ,
                                    QString s01LogSensorVoltPerDecade  ,
                                    QString s01LogSensorVoltAtFullScale,
                                    int     s02AnalActive              ,
                                    int     s02Selection               ,
                                    int     s02SourceIdx               ,
                                    int     s02UnitIdx                 ,
                                    QString s02FullScale               ,
                                    QString s02DigiValue               ,
                                    int     s02ZeroAdjEnable           ,
                                    QString s02ZeroAdjOffsetLimMin     ,
                                    QString s02ZeroAdjOffsetLimMax     ,
                                    QString s02ZeroAdjOffsetValue      ,
                                    QString s02ScaleOffset             ,
                                    QString s02Scale                   ,
                                    int     s02ScaleZeroPoint          ,
                                    QString s02FilterSec               ,
                                    int     s02LogSensorLinearize      ,
                                    QString s02LogSensorVoltPerDecade  ,
                                    QString s02LogSensorVoltAtFullScale,
                                    int     crossoverMod               ,
                                    QString crossoverLow               ,
                                    QString crossoverHigh              ,
                                    QString crossoverDela               )
    {

        mIsWritten              = true;

        mWriteSelection                   = ( s01Selection & 0x01 ) | (( s02Selection & 0x01 ) << 1 );
        mWriteS01AnalActive               = s01AnalActive              ;
        mWriteS01SourceIdx                = s01SourceIdx               ;
        mWriteS01UnitIdx                  = s01UnitIdx                 ;
        mWriteS01FullScale                = s01FullScale               ;
        mWriteS01DigiValue                = QString("%1").arg(qRound((s01DigiValue.toDouble() * 1000000.0)/ s01FullScale.toDouble()));
        mWriteS01ZeroAdjEnable            = s01ZeroAdjEnable           ;
        mWriteS01ZeroAdjOffsetLimMin      = QString("%1").arg(qRound(s01ZeroAdjOffsetLimMin.toDouble() * 10000));
        mWriteS01ZeroAdjOffsetLimMax      = QString("%1").arg(qRound(s01ZeroAdjOffsetLimMax.toDouble() * 10000));
        mWriteS01ZeroAdjOffsetValue       = QString("%1").arg(qRound(s01ZeroAdjOffsetValue.toDouble()  * 10000));
        mWriteS01ScaleOffset              = QString("%1").arg(qRound(s01ScaleOffset.toDouble()         * 100000));
        mWriteS01Scale                    = s01Scale                   ;
        mWriteS01ScaleZeroPoint           = s01ScaleZeroPoint          ;
        mWriteS01FilterSec                = s01FilterSec               ;
        mWriteS01LogSensorLinearize       = s01LogSensorLinearize      ;
        mWriteS01LogSensorVoltPerDecade   = s01LogSensorVoltPerDecade  ;
        mWriteS01LogSensorVoltAtFullScale = s01LogSensorVoltAtFullScale;
        mWriteS02AnalActive               = s02AnalActive              ;
        mWriteS02SourceIdx                = s02SourceIdx               ;
        mWriteS02UnitIdx                  = s02UnitIdx                 ;
        mWriteS02FullScale                = s02FullScale               ;
        mWriteS02DigiValue                = QString("%1").arg(qRound((s02DigiValue.toDouble() * 1000000.0)/ s02FullScale.toDouble()));
        mWriteS02ZeroAdjEnable            = s02ZeroAdjEnable           ;
        mWriteS02ZeroAdjOffsetLimMin      = QString("%1").arg(qRound(s02ZeroAdjOffsetLimMin.toDouble() * 10000));
        mWriteS02ZeroAdjOffsetLimMax      = QString("%1").arg(qRound(s02ZeroAdjOffsetLimMax.toDouble() * 10000));
        mWriteS02ZeroAdjOffsetValue       = QString("%1").arg(qRound(s02ZeroAdjOffsetValue.toDouble()  * 10000));
        mWriteS02ScaleOffset              = QString("%1").arg(qRound(s02ScaleOffset.toDouble()         * 100000));
        mWriteS02Scale                    = s02Scale                   ;
        mWriteS02ScaleZeroPoint           = s02ScaleZeroPoint          ;
        mWriteS02FilterSec                = s02FilterSec               ;
        mWriteS02LogSensorLinearize       = s02LogSensorLinearize      ;
        mWriteS02LogSensorVoltPerDecade   = s02LogSensorVoltPerDecade  ;
        mWriteS02LogSensorVoltAtFullScale = s02LogSensorVoltAtFullScale;
        mWriteCrossoverModIdx             = crossoverMod               ;
        mWriteCrossoverLow                = QString("%1").arg(qRound(crossoverLow.toDouble()  * 10000));
        mWriteCrossoverHigh               = QString("%1").arg(qRound(crossoverHigh.toDouble() * 10000));
        mWriteCrossoverDela               = crossoverDela              ;

        setErrS01AnalActive              (false);
        setErrS01Selection               (false);
        setErrS01SourceIdx               (false);
        setErrS01UnitIdx                 (false);
        setErrS01FullScale               (false);
        setErrS01DigiValue               (false);
        setErrS01ZeroAdjEnable           (false);
        setErrS01ZeroAdjOffsetLimMin     (false);
        setErrS01ZeroAdjOffsetLimMax     (false);
        setErrS01ZeroAdjOffsetValue      (false);
        setErrS01ScaleOffset             (false);
        setErrS01Scale                   (false);
        setErrS01ScaleZeroPoint          (false);
        setErrS01FilterSec               (false);
        setErrS01LogSensorLinearize      (false);
        setErrS01LogSensorVoltPerDecade  (false);
        setErrS01LogSensorVoltAtFullScale(false);
        setErrS02AnalActive              (false);
        setErrS02Selection               (false);
        setErrS02SourceIdx               (false);
        setErrS02UnitIdx                 (false);
        setErrS02FullScale               (false);
        setErrS02DigiValue               (false);
        setErrS02ZeroAdjEnable           (false);
        setErrS02ZeroAdjOffsetLimMin     (false);
        setErrS02ZeroAdjOffsetLimMax     (false);
        setErrS02ZeroAdjOffsetValue      (false);
        setErrS02ScaleOffset             (false);
        setErrS02Scale                   (false);
        setErrS02ScaleZeroPoint          (false);
        setErrS02FilterSec               (false);
        setErrS02LogSensorLinearize      (false);
        setErrS02LogSensorVoltPerDecade  (false);
        setErrS02LogSensorVoltAtFullScale(false);
        setErrCrossoverModIdx            (false);
        setErrCrossoverLow               (false);
        setErrCrossoverHigh              (false);
        setErrCrossoverDela              (false);

        setErrMsg2("");
        setState(eState::STATE_WRITE_SELECTION);
    }

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

    void onValveReadedSensorExSelection(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_SELECTION || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc && !dto.mIsNetworkErr)
        {
            emit signalEventOccurErr();
            return;
        }

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        int selS01 = (dto.mValue.toInt() & 0x01) != 0 ? 1 : 0;
        int selS02 = (dto.mValue.toInt() & 0x02) != 0 ? 1 : 0;

        if(mIsWritten)
        {
            setErrS01Selection(selS01 != (((mWriteSelection & 0x01) != 0 ? 1 : 0)));
            setErrS02Selection(selS02 != (((mWriteSelection & 0x02) != 0 ? 1 : 0)));
        }
        else
        {
            setS01Selection(selS01);
            setS02Selection(selS02);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExAnalActive(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_ANAL_ACTIVE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01AnalActive(dto.mValue.toInt() != mWriteS01AnalActive);
        }
        else
        {
            setS01AnalActive(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExSource(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_SRC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01SourceIdx(dto.mValue.toInt() != mWriteS01SourceIdx);
        }
        else
        {
            setS01SourceIdx(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExUnit(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_UNIT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01UnitIdx(dto.mValue.toInt() != mWriteS01UnitIdx);
        }
        else
        {
            setS01UnitIdx(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExFullScale(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_FULLSCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01FullScale(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 4).toDouble(), mWriteS01FullScale.toDouble()));

            //if(mWriteS01FullScale.toDouble() == 0)
            //{
            //    setErrS01FullScale(dto.mValue.toDouble() != mWriteS01FullScale.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS01FullScale.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.0001 ? 0.00011 : cmpDiff + 0.00001;
            //    setErrS01FullScale(qAbs(dto.mValue.toDouble() - mWriteS01FullScale.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS01FullScale(QString::number(dto.mValue.toDouble(), 'f', 4));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExDigiValue(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_DIGI || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01DigiValue(dto.mValue.toInt() != mWriteS01DigiValue.toInt());
        }
        else
        {
            setS01DigiValue(QString::number(((dto.mValue.toDouble() * getS01FullScale().toDouble()) / 1000000), 'f', 6));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExZeroAdjEnable(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_ZERO_ENABLE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01ZeroAdjEnable(dto.mValue.toInt() != mWriteS01ZeroAdjEnable);
        }
        else
        {
            setS01ZeroAdjEnable(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExZeroAdjOffsetLimMin(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_ZERO_MIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
             setErrS01ZeroAdjOffsetLimMin(dto.mValue.toInt() != mWriteS01ZeroAdjOffsetLimMin.toInt());
        }
        else
        {
            setS01ZeroAdjOffsetLimMin(QString::number((dto.mValue.toDouble() / 10000), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExZeroAdjOffsetLimMax(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_ZERO_MAX || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
             setErrS01ZeroAdjOffsetLimMax(dto.mValue.toInt() != mWriteS01ZeroAdjOffsetLimMax.toInt());
        }
        else
        {
            setS01ZeroAdjOffsetLimMax(QString::number((dto.mValue.toDouble() / 10000), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExZeroAdjOffsetValue(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_ZERO_VALUE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01ZeroAdjOffsetValue(dto.mValue.toInt() != mWriteS01ZeroAdjOffsetValue.toInt());
        }
        else
        {
            setS01ZeroAdjOffsetValue(QString::number((dto.mValue.toDouble() / 10000), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExScaleOffset(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_SCALE_OFFSET || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
             setErrS01ScaleOffset(dto.mValue.toInt() != mWriteS01ScaleOffset.toInt());
        }
        else
        {
            setS01ScaleOffset(QString::number((dto.mValue.toDouble() / 100000), 'f', 3));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExScale(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_SCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01Scale(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 6).toDouble(), mWriteS01Scale.toDouble()));
            //if(mWriteS01Scale.toDouble() == 0)
            //{
            //    setErrS01Scale(dto.mValue.toDouble() != mWriteS01Scale.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS01Scale.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.000001 ? 0.0000011 : cmpDiff + 0.0000001;
            //
            //    setErrS01Scale(qAbs(dto.mValue.toDouble() - mWriteS01Scale.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS01Scale(QString::number(dto.mValue.toDouble(), 'f', 6));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExScaleZeroPoint(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_SCALE_Z_POINT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01ScaleZeroPoint(dto.mValue.toInt() != mWriteS01ScaleZeroPoint);
        }
        else
        {
            setS01ScaleZeroPoint(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExFilterSec(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_FILTER_SEC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01FilterSec(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 2).toDouble(), mWriteS01FilterSec.toDouble()));

            //if(mWriteS01FilterSec.toDouble() == 0)
            //{
            //    setErrS01FilterSec(dto.mValue.toDouble() != mWriteS01FilterSec.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS01FilterSec.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.01 ? 0.011 : cmpDiff + 0.001;
            //    setErrS01FilterSec(qAbs(dto.mValue.toDouble() - mWriteS01FilterSec.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS01FilterSec(QString::number(dto.mValue.toDouble(), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExLogSensorLinearize(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_LOG_SENS_LINEARIZE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01LogSensorLinearize(dto.mValue.toInt() != mWriteS01LogSensorLinearize);
        }
        else
        {
            setS01LogSensorLinearize(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExLogSensorVoltPerDecade(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_LOG_SENS_VOLT_DECADE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01LogSensorVoltPerDecade(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 3).toDouble(), mWriteS01LogSensorVoltPerDecade.toDouble()));

            //if(mWriteS01LogSensorVoltPerDecade.toDouble() == 0)
            //{
            //    setErrS01LogSensorVoltPerDecade(dto.mValue.toDouble() != mWriteS01LogSensorVoltPerDecade.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS01LogSensorVoltPerDecade.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.01 ? 0.011 : cmpDiff + 0.001;
            //    setErrS01LogSensorVoltPerDecade(qAbs(dto.mValue.toDouble() - mWriteS01LogSensorVoltPerDecade.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS01LogSensorVoltPerDecade(QString::number(dto.mValue.toDouble(), 'f', 3));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS01ExLogSensorVoltAtFullScale(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S01_LOG_SENS_VOLT_FULLSCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS01LogSensorVoltAtFullScale(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 6).toDouble(), mWriteS01LogSensorVoltAtFullScale.toDouble()));

            //if(mWriteS01LogSensorVoltAtFullScale.toDouble() == 0)
            //{
            //    setErrS01LogSensorVoltAtFullScale(dto.mValue.toDouble() != mWriteS01LogSensorVoltAtFullScale.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS01LogSensorVoltAtFullScale.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.000001 ? 0.0000011 : cmpDiff + 0.0000001;
            //    setErrS01LogSensorVoltAtFullScale(qAbs(dto.mValue.toDouble() - mWriteS01LogSensorVoltAtFullScale.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS01LogSensorVoltAtFullScale(QString::number(dto.mValue.toDouble(), 'f', 6));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExAnalActive(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_ANAL_ACTIVE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02AnalActive(dto.mValue.toInt() != mWriteS02AnalActive);
        }
        else
        {
            setS02AnalActive(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExSource(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_SRC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02SourceIdx(dto.mValue.toInt() != mWriteS02SourceIdx);
        }
        else
        {
            setS02SourceIdx(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExUnit(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_UNIT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02UnitIdx(dto.mValue.toInt() != mWriteS02UnitIdx);
        }
        else
        {
            setS02UnitIdx(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExFullScale(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_FULLSCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02FullScale(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 4).toDouble(), mWriteS02FullScale.toDouble()));

            //if(mWriteS02FullScale.toDouble() == 0)
            //{
            //    setErrS02FullScale(dto.mValue.toDouble() != mWriteS02FullScale.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS02FullScale.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.0001 ? 0.00011 : cmpDiff + 00001;
            //    setErrS02FullScale(qAbs(dto.mValue.toDouble() - mWriteS02FullScale.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS02FullScale(QString::number(dto.mValue.toDouble(), 'f', 4));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExDigiValue(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_DIGI || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02DigiValue(dto.mValue.toInt() != mWriteS02DigiValue.toInt());
        }
        else
        {
            setS02DigiValue(QString::number(((dto.mValue.toDouble() * getS02FullScale().toDouble()) / 1000000), 'f', 6));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExZeroAdjEnable(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_ZERO_ENABLE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02ZeroAdjEnable(dto.mValue.toInt() != mWriteS02ZeroAdjEnable);
        }
        else
        {
            setS02ZeroAdjEnable(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExZeroAdjOffsetLimMin(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_ZERO_MIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
             setErrS02ZeroAdjOffsetLimMin(dto.mValue.toInt() != mWriteS02ZeroAdjOffsetLimMin.toInt());
        }
        else
        {
            setS02ZeroAdjOffsetLimMin(QString::number((dto.mValue.toDouble() / 10000), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExZeroAdjOffsetLimMax(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_ZERO_MAX || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
             setErrS02ZeroAdjOffsetLimMax(dto.mValue.toInt() != mWriteS02ZeroAdjOffsetLimMax.toInt());
        }
        else
        {
            setS02ZeroAdjOffsetLimMax(QString::number((dto.mValue.toDouble() / 10000), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExZeroAdjOffsetValue(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_ZERO_VALUE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
             setErrS02ZeroAdjOffsetValue(dto.mValue.toInt() != mWriteS02ZeroAdjOffsetValue.toInt());
        }
        else
        {
            setS02ZeroAdjOffsetValue(QString::number((dto.mValue.toDouble() / 10000), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExScaleOffset(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_SCALE_OFFSET || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
             setErrS02ScaleOffset(dto.mValue.toInt() != mWriteS02ScaleOffset.toInt());
        }
        else
        {
            setS02ScaleOffset(QString::number((dto.mValue.toDouble() / 100000), 'f', 3));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExScale(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_SCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02Scale(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 6).toDouble(), mWriteS02Scale.toDouble()));

             //if(mWriteS02Scale.toDouble() == 0)
             //{
             //    setErrS02Scale(dto.mValue.toDouble() != mWriteS02Scale.toDouble());
             //}
             //else
             //{
             //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS02Scale.toDouble()));
             //    double cmpDiff = qPow(10, (exp + 1) - 7);
             //    cmpDiff = cmpDiff < 0.000001 ? 0.0000011 : cmpDiff + 0.0000001;
             //    setErrS02Scale(qAbs(dto.mValue.toDouble() - mWriteS02Scale.toDouble()) > cmpDiff);
             //}
        }
        else
        {
            setS02Scale(QString::number(dto.mValue.toDouble(), 'f', 6));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExScaleZeroPoint(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_SCALE_Z_POINT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02ScaleZeroPoint(dto.mValue.toInt() != mWriteS02ScaleZeroPoint);
        }
        else
        {
            setS02ScaleZeroPoint(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExFilterSec(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_FILTER_SEC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02FilterSec(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 2).toDouble(), mWriteS02FilterSec.toDouble()));

            //if(mWriteS02FilterSec.toDouble() == 0)
            //{
            //    setErrS02FilterSec(dto.mValue.toDouble() != mWriteS02FilterSec.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS02FilterSec.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.01 ? 0.011 : cmpDiff + 0.001;
            //    setErrS02FilterSec(qAbs(dto.mValue.toDouble() - mWriteS02FilterSec.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS02FilterSec(QString::number(dto.mValue.toDouble(), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExLogSensorLinearize(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_LOG_SENS_LINEARIZE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02LogSensorLinearize(dto.mValue.toInt() != mWriteS02LogSensorLinearize);
        }
        else
        {
            setS02LogSensorLinearize(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExLogSensorVoltPerDecade(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_LOG_SENS_VOLT_DECADE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02LogSensorVoltPerDecade(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 3).toDouble(), mWriteS02LogSensorVoltPerDecade.toDouble()));

            //if(mWriteS02LogSensorVoltPerDecade.toDouble() == 0)
            //{
            //    setErrS02LogSensorVoltPerDecade(dto.mValue.toDouble() != mWriteS02LogSensorVoltPerDecade.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS02LogSensorVoltPerDecade.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.01 ? 0.011 : cmpDiff + 0.001;
            //    setErrS02LogSensorVoltPerDecade(qAbs(dto.mValue.toDouble() - mWriteS02LogSensorVoltPerDecade.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS02LogSensorVoltPerDecade(QString::number(dto.mValue.toDouble(), 'f', 3));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedS02ExLogSensorVoltAtFullScale(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_S02_LOG_SENS_VOLT_FULLSCALE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrS02LogSensorVoltAtFullScale(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 6).toDouble(), mWriteS02LogSensorVoltAtFullScale.toDouble()));

            //if(mWriteS02LogSensorVoltAtFullScale.toDouble() == 0)
            //{
            //    setErrS02LogSensorVoltAtFullScale(dto.mValue.toDouble() != mWriteS02LogSensorVoltAtFullScale.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteS02LogSensorVoltAtFullScale.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.000001 ? 0.0000011 : cmpDiff + 0.0000001;
            //    setErrS02LogSensorVoltAtFullScale(qAbs(dto.mValue.toDouble() - mWriteS02LogSensorVoltAtFullScale.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setS02LogSensorVoltAtFullScale(QString::number(dto.mValue.toDouble(), 'f', 6));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedCrossoverMod(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_CROSSOVER_MOD || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrCrossoverModIdx(dto.mValue.toInt() != mWriteCrossoverModIdx);
        }
        else
        {
            setCrossoverModIdx(dto.mValue.toInt());
        }

        setState((eState)(mState + 1));
    }
    void onValveReadedCrossoverLow(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_CROSSOVER_LOW || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrCrossoverLow(dto.mValue.toInt() != mWriteCrossoverLow.toInt());
        }
        else
        {
            setCrossoverLow(QString::number(dto.mValue.toDouble() / 10000, 'f', 4));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedCrossoverHigh(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_CROSSOVER_HIGH || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrCrossoverHigh(dto.mValue.toInt() != mWriteCrossoverHigh.toInt());
        }
        else
        {
            setCrossoverHigh(QString::number(dto.mValue.toDouble() / 10000, 'f', 4));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedCrossoverDela(ValveResponseSimpleValueDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mResData;

        if(mState != eState::STATE_READ_CROSSOVER_DELA || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrCrossoverDela(!qFuzzyCompare(QString::number(dto.mValue.toDouble(), 'f', 2).toDouble(), mWriteCrossoverDela.toDouble()));
            //if(mWriteCrossoverDela.toDouble() == 0)
            //{
            //    setErrCrossoverDela(dto.mValue.toDouble() != mWriteCrossoverDela.toDouble());
            //}
            //else
            //{
            //    int exp = MATHUTIL_LOG10FLOOR(qAbs(mWriteCrossoverDela.toDouble()));
            //    double cmpDiff = qPow(10, (exp + 1) - 7);
            //
            //    cmpDiff = cmpDiff < 0.000001 ? 0.0000011 : cmpDiff + 0.0000001;
            //    setErrCrossoverDela(qAbs(dto.mValue.toDouble() - mWriteCrossoverDela.toDouble()) > cmpDiff);
            //}
        }
        else
        {
            setCrossoverDela(QString::number(dto.mValue.toDouble(), 'f', 2));
        }

        setState((eState)(mState + 1));
    }

    void onValveWrittenSensorExSelection(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_SELECTION || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExAnalActive(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_ANAL_ACTIVE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExSource(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_SRC || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExUnit(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_UNIT || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExFullScale(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_FULLSCALE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExDigiValue(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_DIGI || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExZeroAdjEnable(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_ZERO_ENABLE || dto.mReqDto.mpRef != this)
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
    void onValveWrittenS01ExZeroAdjOffsetLimMin(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_ZERO_MIN || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExZeroAdjOffsetLimMax(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_ZERO_MAX || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExZeroAdjOffsetValue(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_ZERO_VALUE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExScaleOffset(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_SCALE_OFFSET || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExScale(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_SCALE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExScaleZeroPoint(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_SCALE_Z_POINT || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExFilterSec(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_FILTER_SEC || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExLogSensorLinearize(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_LOG_SENS_LINEARIZE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExLogSensorVoltPerDecade(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_LOG_SENS_VOLT_DECADE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS01ExLogSensorVoltAtFullScale(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S01_LOG_SENS_VOLT_FULLSCALE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExAnalActive(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_ANAL_ACTIVE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExSource(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_SRC || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExUnit(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_UNIT || dto.mReqDto.mpRef != this)
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


    void onValveWrittenS02ExFullScale(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_FULLSCALE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExDigiValue(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_DIGI || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExZeroAdjEnable(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_ZERO_ENABLE || dto.mReqDto.mpRef != this)
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
    void onValveWrittenS02ExZeroAdjOffsetLimMin(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_ZERO_MIN || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExZeroAdjOffsetLimMax(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_ZERO_MAX || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExZeroAdjOffsetValue(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_ZERO_VALUE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExScaleOffset(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_SCALE_OFFSET || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExScale(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_SCALE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExScaleZeroPoint(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_SCALE_Z_POINT || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExFilterSec(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_FILTER_SEC || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExLogSensorLinearize(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_LOG_SENS_LINEARIZE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExLogSensorVoltPerDecade(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_LOG_SENS_VOLT_DECADE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenS02ExLogSensorVoltAtFullScale(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_S02_LOG_SENS_VOLT_FULLSCALE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenCrossoverMod(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_CROSSOVER_MOD || dto.mReqDto.mpRef != this)
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

    void onValveWrittenCrossoverLow(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_CROSSOVER_LOW || dto.mReqDto.mpRef != this)
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

    void onValveWrittenCrossoverHigh(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_CROSSOVER_HIGH || dto.mReqDto.mpRef != this)
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

    void onValveWrittenCrossoverDela(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]";

        if(mState != eState::STATE_WRITE_CROSSOVER_DELA || dto.mReqDto.mpRef != this)
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
        STATE_WRITE_SELECTION                   = 0,
        STATE_WRITE_S01_ANAL_ACTIVE             = STATE_WRITE_SELECTION                   + 1,
        STATE_WRITE_S01_SRC                     = STATE_WRITE_S01_ANAL_ACTIVE             + 1,
        STATE_WRITE_S01_UNIT                    = STATE_WRITE_S01_SRC                     + 1,
        STATE_WRITE_S01_FULLSCALE               = STATE_WRITE_S01_UNIT                    + 1,
        STATE_WRITE_S01_DIGI                    = STATE_WRITE_S01_FULLSCALE               + 1,
        STATE_WRITE_S01_ZERO_ENABLE             = STATE_WRITE_S01_DIGI                    + 1,
        STATE_WRITE_S01_ZERO_MIN                = STATE_WRITE_S01_ZERO_ENABLE             + 1,
        STATE_WRITE_S01_ZERO_MAX                = STATE_WRITE_S01_ZERO_MIN                + 1,
        STATE_WRITE_S01_ZERO_VALUE              = STATE_WRITE_S01_ZERO_MAX                + 1,
        STATE_WRITE_S01_SCALE_OFFSET            = STATE_WRITE_S01_ZERO_VALUE              + 1,
        STATE_WRITE_S01_SCALE                   = STATE_WRITE_S01_SCALE_OFFSET            + 1,
        STATE_WRITE_S01_SCALE_Z_POINT           = STATE_WRITE_S01_SCALE                   + 1,
        STATE_WRITE_S01_FILTER_SEC              = STATE_WRITE_S01_SCALE_Z_POINT           + 1,
        STATE_WRITE_S01_LOG_SENS_LINEARIZE      = STATE_WRITE_S01_FILTER_SEC              + 1,
        STATE_WRITE_S01_LOG_SENS_VOLT_DECADE    = STATE_WRITE_S01_LOG_SENS_LINEARIZE      + 1,
        STATE_WRITE_S01_LOG_SENS_VOLT_FULLSCALE = STATE_WRITE_S01_LOG_SENS_VOLT_DECADE    + 1,
        STATE_WRITE_S02_ANAL_ACTIVE             = STATE_WRITE_S01_LOG_SENS_VOLT_FULLSCALE + 1,
        STATE_WRITE_S02_SRC                     = STATE_WRITE_S02_ANAL_ACTIVE             + 1,
        STATE_WRITE_S02_UNIT                    = STATE_WRITE_S02_SRC                     + 1,
        STATE_WRITE_S02_FULLSCALE               = STATE_WRITE_S02_UNIT                    + 1,
        STATE_WRITE_S02_DIGI                    = STATE_WRITE_S02_FULLSCALE               + 1,
        STATE_WRITE_S02_ZERO_ENABLE             = STATE_WRITE_S02_DIGI                    + 1,
        STATE_WRITE_S02_ZERO_MIN                = STATE_WRITE_S02_ZERO_ENABLE             + 1,
        STATE_WRITE_S02_ZERO_MAX                = STATE_WRITE_S02_ZERO_MIN                + 1,
        STATE_WRITE_S02_ZERO_VALUE              = STATE_WRITE_S02_ZERO_MAX                + 1,
        STATE_WRITE_S02_SCALE_OFFSET            = STATE_WRITE_S02_ZERO_VALUE              + 1,
        STATE_WRITE_S02_SCALE                   = STATE_WRITE_S02_SCALE_OFFSET            + 1,
        STATE_WRITE_S02_SCALE_Z_POINT           = STATE_WRITE_S02_SCALE                   + 1,
        STATE_WRITE_S02_FILTER_SEC              = STATE_WRITE_S02_SCALE_Z_POINT           + 1,
        STATE_WRITE_S02_LOG_SENS_LINEARIZE      = STATE_WRITE_S02_FILTER_SEC              + 1,
        STATE_WRITE_S02_LOG_SENS_VOLT_DECADE    = STATE_WRITE_S02_LOG_SENS_LINEARIZE      + 1,
        STATE_WRITE_S02_LOG_SENS_VOLT_FULLSCALE = STATE_WRITE_S02_LOG_SENS_VOLT_DECADE    + 1,
        STATE_WRITE_CROSSOVER_MOD               = STATE_WRITE_S02_LOG_SENS_VOLT_FULLSCALE + 1,
        STATE_WRITE_CROSSOVER_LOW               = STATE_WRITE_CROSSOVER_MOD               + 1,
        STATE_WRITE_CROSSOVER_HIGH              = STATE_WRITE_CROSSOVER_LOW               + 1,
        STATE_WRITE_CROSSOVER_DELA              = STATE_WRITE_CROSSOVER_HIGH              + 1,
        STATE_READ_SELECTION                    = STATE_WRITE_CROSSOVER_DELA              + 1,
        STATE_READ_S01_ANAL_ACTIVE              = STATE_READ_SELECTION                    + 1,
        STATE_READ_S01_SRC                      = STATE_READ_S01_ANAL_ACTIVE              + 1,
        STATE_READ_S01_UNIT                     = STATE_READ_S01_SRC                      + 1,
        STATE_READ_S01_FULLSCALE                = STATE_READ_S01_UNIT                     + 1,
        STATE_READ_S01_DIGI                     = STATE_READ_S01_FULLSCALE                + 1,
        STATE_READ_S01_ZERO_ENABLE              = STATE_READ_S01_DIGI                     + 1,
        STATE_READ_S01_ZERO_MIN                 = STATE_READ_S01_ZERO_ENABLE              + 1,
        STATE_READ_S01_ZERO_MAX                 = STATE_READ_S01_ZERO_MIN                 + 1,
        STATE_READ_S01_ZERO_VALUE               = STATE_READ_S01_ZERO_MAX                 + 1,
        STATE_READ_S01_SCALE_OFFSET             = STATE_READ_S01_ZERO_VALUE               + 1,
        STATE_READ_S01_SCALE                    = STATE_READ_S01_SCALE_OFFSET             + 1,
        STATE_READ_S01_SCALE_Z_POINT            = STATE_READ_S01_SCALE                    + 1,
        STATE_READ_S01_FILTER_SEC               = STATE_READ_S01_SCALE_Z_POINT            + 1,
        STATE_READ_S01_LOG_SENS_LINEARIZE       = STATE_READ_S01_FILTER_SEC               + 1,
        STATE_READ_S01_LOG_SENS_VOLT_DECADE     = STATE_READ_S01_LOG_SENS_LINEARIZE       + 1,
        STATE_READ_S01_LOG_SENS_VOLT_FULLSCALE  = STATE_READ_S01_LOG_SENS_VOLT_DECADE     + 1,
        STATE_READ_S02_ANAL_ACTIVE              = STATE_READ_S01_LOG_SENS_VOLT_FULLSCALE  + 1,
        STATE_READ_S02_SRC                      = STATE_READ_S02_ANAL_ACTIVE              + 1,
        STATE_READ_S02_UNIT                     = STATE_READ_S02_SRC                      + 1,
        STATE_READ_S02_FULLSCALE                = STATE_READ_S02_UNIT                     + 1,
        STATE_READ_S02_DIGI                     = STATE_READ_S02_FULLSCALE                + 1,
        STATE_READ_S02_ZERO_ENABLE              = STATE_READ_S02_DIGI                     + 1,
        STATE_READ_S02_ZERO_MIN                 = STATE_READ_S02_ZERO_ENABLE              + 1,
        STATE_READ_S02_ZERO_MAX                 = STATE_READ_S02_ZERO_MIN                 + 1,
        STATE_READ_S02_ZERO_VALUE               = STATE_READ_S02_ZERO_MAX                 + 1,
        STATE_READ_S02_SCALE_OFFSET             = STATE_READ_S02_ZERO_VALUE               + 1,
        STATE_READ_S02_SCALE                    = STATE_READ_S02_SCALE_OFFSET             + 1,
        STATE_READ_S02_SCALE_Z_POINT            = STATE_READ_S02_SCALE                    + 1,
        STATE_READ_S02_FILTER_SEC               = STATE_READ_S02_SCALE_Z_POINT            + 1,
        STATE_READ_S02_LOG_SENS_LINEARIZE       = STATE_READ_S02_FILTER_SEC               + 1,
        STATE_READ_S02_LOG_SENS_VOLT_DECADE     = STATE_READ_S02_LOG_SENS_LINEARIZE       + 1,
        STATE_READ_S02_LOG_SENS_VOLT_FULLSCALE  = STATE_READ_S02_LOG_SENS_VOLT_DECADE     + 1,
        STATE_READ_CROSSOVER_MOD                = STATE_READ_S02_LOG_SENS_VOLT_FULLSCALE  + 1,
        STATE_READ_CROSSOVER_LOW                = STATE_READ_CROSSOVER_MOD                + 1,
        STATE_READ_CROSSOVER_HIGH               = STATE_READ_CROSSOVER_LOW                + 1,
        STATE_READ_CROSSOVER_DELA               = STATE_READ_CROSSOVER_HIGH               + 1,
        STATE_READY                             = STATE_READ_CROSSOVER_DELA               + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_WRITE_SELECTION;

    bool    mIsWritten                        = false;
    int     mWriteSelection                   = 0;
    int     mWriteS01AnalActive               = 0;
    int     mWriteS01SourceIdx                = 0;
    int     mWriteS01UnitIdx                  = 0;
    QString mWriteS01FullScale                = "0";
    QString mWriteS01DigiValue                = "0";
    int     mWriteS01ZeroAdjEnable            = 0;
    QString mWriteS01ZeroAdjOffsetLimMin      = "0";
    QString mWriteS01ZeroAdjOffsetLimMax      = "0";
    QString mWriteS01ZeroAdjOffsetValue       = "0";
    QString mWriteS01ScaleOffset              = "0";
    QString mWriteS01Scale                    = "0";
    int     mWriteS01ScaleZeroPoint           = 0;
    QString mWriteS01FilterSec                = "0";
    int     mWriteS01LogSensorLinearize       = 0;
    QString mWriteS01LogSensorVoltPerDecade   = "0";
    QString mWriteS01LogSensorVoltAtFullScale = "0";
    int     mWriteS02AnalActive               = 0;
    int     mWriteS02SourceIdx                = 0;
    int     mWriteS02UnitIdx                  = 0;
    QString mWriteS02FullScale                = "0";
    QString mWriteS02DigiValue                = "0";
    int     mWriteS02ZeroAdjEnable            = 0;
    QString mWriteS02ZeroAdjOffsetLimMin      = "0";
    QString mWriteS02ZeroAdjOffsetLimMax      = "0";
    QString mWriteS02ZeroAdjOffsetValue       = "0";
    QString mWriteS02ScaleOffset              = "0";
    QString mWriteS02Scale                    = "0";
    int     mWriteS02ScaleZeroPoint           = 0;
    QString mWriteS02FilterSec                = "0";
    int     mWriteS02LogSensorLinearize       = 0;
    QString mWriteS02LogSensorVoltPerDecade   = "0";
    QString mWriteS02LogSensorVoltAtFullScale = "0";
    int     mWriteCrossoverModIdx             = 0;
    QString mWriteCrossoverLow                = "0";
    QString mWriteCrossoverHigh               = "0";
    QString mWriteCrossoverDela               = "0";

    bool    mEditSelection                   = false;
    bool    mEditS01AnalActive               = false;
    bool    mEditS01SourceIdx                = false;
    bool    mEditS01UnitIdx                  = false;
    bool    mEditS01FullScale                = false;
    bool    mEditS01DigiValue                = false;
    bool    mEditS01ZeroAdjEnable            = false;
    bool    mEditS01ZeroAdjOffsetLimMin      = false;
    bool    mEditS01ZeroAdjOffsetLimMax      = false;
    bool    mEditS01ZeroAdjOffsetValue       = false;
    bool    mEditS01ScaleOffset              = false;
    bool    mEditS01Scale                    = false;
    bool    mEditS01ScaleZeroPoint           = false;
    bool    mEditS01FilterSec                = false;
    bool    mEditS01LogSensorLinearize       = false;
    bool    mEditS01LogSensorVoltPerDecade   = false;
    bool    mEditS01LogSensorVoltAtFullScale = false;
    bool    mEditS02AnalActive               = false;
    bool    mEditS02SourceIdx                = false;
    bool    mEditS02UnitIdx                  = false;
    bool    mEditS02FullScale                = false;
    bool    mEditS02DigiValue                = false;
    bool    mEditS02ZeroAdjEnable            = false;
    bool    mEditS02ZeroAdjOffsetLimMin      = false;
    bool    mEditS02ZeroAdjOffsetLimMax      = false;
    bool    mEditS02ZeroAdjOffsetValue       = false;
    bool    mEditS02ScaleOffset              = false;
    bool    mEditS02Scale                    = false;
    bool    mEditS02ScaleZeroPoint           = false;
    bool    mEditS02FilterSec                = false;
    bool    mEditS02LogSensorLinearize       = false;
    bool    mEditS02LogSensorVoltPerDecade   = false;
    bool    mEditS02LogSensorVoltAtFullScale = false;
    bool    mEditCrossoverModIdx             = false;
    bool    mEditCrossoverLow                = false;
    bool    mEditCrossoverHigh               = false;
    bool    mEditCrossoverDela               = false;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state, bool immediately = false)
    {
        if(!mIsWritten && state == eState::STATE_READY)
        {
            emit signalEventCompletedLoad();
        }

        mState = state;

        if(state < (int) eState::STATE_READY && state >= (int) eState::STATE_READ_SELECTION)
        {
            setStrStatus("loading");
        }
        else if(state < (int) eState::STATE_READ_SELECTION && state >= (int) eState::STATE_WRITE_SELECTION)
        {
            setStrStatus("writting");
        }
        else
        {
            setStrStatus("ready");
        }

        if(state == eState::STATE_READY)
        {
            mEditSelection                   = false;
            mEditS01AnalActive               = false;
            mEditS01SourceIdx                = false;
            mEditS01UnitIdx                  = false;
            mEditS01FullScale                = false;
            mEditS01DigiValue                = false;
            mEditS01ZeroAdjEnable            = false;
            mEditS01ZeroAdjOffsetLimMin      = false;
            mEditS01ZeroAdjOffsetLimMax      = false;
            mEditS01ZeroAdjOffsetValue       = false;
            mEditS01ScaleOffset              = false;
            mEditS01Scale                    = false;
            mEditS01ScaleZeroPoint           = false;
            mEditS01FilterSec                = false;
            mEditS01LogSensorLinearize       = false;
            mEditS01LogSensorVoltPerDecade   = false;
            mEditS01LogSensorVoltAtFullScale = false;
            mEditS02AnalActive               = false;
            mEditS02SourceIdx                = false;
            mEditS02UnitIdx                  = false;
            mEditS02FullScale                = false;
            mEditS02DigiValue                = false;
            mEditS02ZeroAdjEnable            = false;
            mEditS02ZeroAdjOffsetLimMin      = false;
            mEditS02ZeroAdjOffsetLimMax      = false;
            mEditS02ZeroAdjOffsetValue       = false;
            mEditS02ScaleOffset              = false;
            mEditS02Scale                    = false;
            mEditS02ScaleZeroPoint           = false;
            mEditS02FilterSec                = false;
            mEditS02LogSensorLinearize       = false;
            mEditS02LogSensorVoltPerDecade   = false;
            mEditS02LogSensorVoltAtFullScale = false;
            mEditCrossoverModIdx             = false;
            mEditCrossoverLow                = false;
            mEditCrossoverHigh               = false;
            mEditCrossoverDela               = false;

            onCommandSetEdit(getErrS01AnalActive              () ||
                             getErrS01Selection               () ||
                             getErrS01SourceIdx               () ||
                             getErrS01UnitIdx                 () ||
                             getErrS01FullScale               () ||
                             getErrS01DigiValue               () ||
                             getErrS01ZeroAdjEnable           () ||
                             getErrS01ZeroAdjOffsetLimMin     () ||
                             getErrS01ZeroAdjOffsetLimMax     () ||
                             getErrS01ZeroAdjOffsetValue      () ||
                             getErrS01ScaleOffset             () ||
                             getErrS01Scale                   () ||
                             getErrS01ScaleZeroPoint          () ||
                             getErrS01FilterSec               () ||
                             getErrS01LogSensorLinearize      () ||
                             getErrS01LogSensorVoltPerDecade  () ||
                             getErrS01LogSensorVoltAtFullScale() ||
                             getErrS02AnalActive              () ||
                             getErrS02Selection               () ||
                             getErrS02SourceIdx               () ||
                             getErrS02UnitIdx                 () ||
                             getErrS02FullScale               () ||
                             getErrS02DigiValue               () ||
                             getErrS02ZeroAdjEnable           () ||
                             getErrS02ZeroAdjOffsetLimMin     () ||
                             getErrS02ZeroAdjOffsetLimMax     () ||
                             getErrS02ZeroAdjOffsetValue      () ||
                             getErrS02ScaleOffset             () ||
                             getErrS02Scale                   () ||
                             getErrS02ScaleZeroPoint          () ||
                             getErrS02FilterSec               () ||
                             getErrS02LogSensorLinearize      () ||
                             getErrS02LogSensorVoltPerDecade  () ||
                             getErrS02LogSensorVoltAtFullScale() ||
                             getErrCrossoverModIdx            () ||
                             getErrCrossoverLow               () ||
                             getErrCrossoverHigh              () ||
                             getErrCrossoverDela              ());

            setProgress(100);
        }
        else
        {
            setProgress(qFloor((state * 100) / eState::STATE_READY));

            if(immediately)
                onTimeout();
            else
                startTimer();
        }
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case STATE_WRITE_SELECTION                  : if(!mEditSelection                   && !getErrS01Selection() && !getErrS02Selection()    ){setState((eState)(mState + 1), true); return;} pValveSP->setSensorExSelection             (mWriteSelection                  , this);break;
        case STATE_WRITE_S01_ANAL_ACTIVE            : if(!mEditS01AnalActive               && !getErrS01AnalActive              ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExAnalActive               (mWriteS01AnalActive              , this);break;
        case STATE_WRITE_S01_SRC                    : if(!mEditS01SourceIdx                && !getErrS01SourceIdx               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExSource                   (mWriteS01SourceIdx               , this);break;
        case STATE_WRITE_S01_UNIT                   : if(!mEditS01UnitIdx                  && !getErrS01UnitIdx                 ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExUnit                     (mWriteS01UnitIdx                 , this);break;
        case STATE_WRITE_S01_FULLSCALE              : if(!mEditS01FullScale                && !getErrS01FullScale               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExFullScale                (mWriteS01FullScale               , this);break;
        case STATE_WRITE_S01_DIGI                   : if(!mEditS01DigiValue                && !getErrS01DigiValue               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExDigiValue                (mWriteS01DigiValue               , this);break;
        case STATE_WRITE_S01_ZERO_ENABLE            : if(!mEditS01ZeroAdjEnable            && !getErrS01ZeroAdjEnable           ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExZeroAdjEnable            (mWriteS01ZeroAdjEnable           , this);break;
        case STATE_WRITE_S01_ZERO_MIN               : if(!mEditS01ZeroAdjOffsetLimMin      && !getErrS01ZeroAdjOffsetLimMin     ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExZeroAdjOffsetLimMin      (mWriteS01ZeroAdjOffsetLimMin     , this);break;
        case STATE_WRITE_S01_ZERO_MAX               : if(!mEditS01ZeroAdjOffsetLimMax      && !getErrS01ZeroAdjOffsetLimMax     ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExZeroAdjOffsetLimMax      (mWriteS01ZeroAdjOffsetLimMax     , this);break;
        case STATE_WRITE_S01_ZERO_VALUE             : if(!mEditS01ZeroAdjOffsetValue       && !getErrS01ZeroAdjOffsetValue      ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExZeroAdjOffsetValue       (mWriteS01ZeroAdjOffsetValue      , this);break;
        case STATE_WRITE_S01_SCALE_OFFSET           : if(!mEditS01ScaleOffset              && !getErrS01ScaleOffset             ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExScaleOffset              (mWriteS01ScaleOffset             , this);break;
        case STATE_WRITE_S01_SCALE                  : if(!mEditS01Scale                    && !getErrS01Scale                   ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExScale                    (mWriteS01Scale                   , this);break;
        case STATE_WRITE_S01_SCALE_Z_POINT          : if(!mEditS01ScaleZeroPoint           && !getErrS01ScaleZeroPoint          ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExScaleZeroPoint           (mWriteS01ScaleZeroPoint          , this);break;
        case STATE_WRITE_S01_FILTER_SEC             : if(!mEditS01FilterSec                && !getErrS01FilterSec               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExFilterSec                (mWriteS01FilterSec               , this);break;
        case STATE_WRITE_S01_LOG_SENS_LINEARIZE     : if(!mEditS01LogSensorLinearize       && !getErrS01LogSensorLinearize      ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExLogSensorLinearize       (mWriteS01LogSensorLinearize      , this);break;
        case STATE_WRITE_S01_LOG_SENS_VOLT_DECADE   : if(!mEditS01LogSensorVoltPerDecade   && !getErrS01LogSensorVoltPerDecade  ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExLogSensorVoltPerDecade   (mWriteS01LogSensorVoltPerDecade  , this);break;
        case STATE_WRITE_S01_LOG_SENS_VOLT_FULLSCALE: if(!mEditS01LogSensorVoltAtFullScale && !getErrS01LogSensorVoltAtFullScale()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS01ExLogSensorVoltAtFullScale (mWriteS01LogSensorVoltAtFullScale, this);break;
        case STATE_WRITE_S02_ANAL_ACTIVE            : if(!mEditS02AnalActive               && !getErrS02AnalActive              ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExAnalActive               (mWriteS02AnalActive              , this);break;
        case STATE_WRITE_S02_SRC                    : if(!mEditS02SourceIdx                && !getErrS02SourceIdx               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExSource                   (mWriteS02SourceIdx               , this);break;
        case STATE_WRITE_S02_UNIT                   : if(!mEditS02UnitIdx                  && !getErrS02UnitIdx                 ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExUnit                     (mWriteS02UnitIdx                 , this);break;
        case STATE_WRITE_S02_FULLSCALE              : if(!mEditS02FullScale                && !getErrS02FullScale               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExFullScale                (mWriteS02FullScale               , this);break;
        case STATE_WRITE_S02_DIGI                   : if(!mEditS02DigiValue                && !getErrS02DigiValue               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExDigiValue                (mWriteS02DigiValue               , this);break;
        case STATE_WRITE_S02_ZERO_ENABLE            : if(!mEditS02ZeroAdjEnable            && !getErrS02ZeroAdjEnable           ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExZeroAdjEnable            (mWriteS02ZeroAdjEnable           , this);break;
        case STATE_WRITE_S02_ZERO_MIN               : if(!mEditS02ZeroAdjOffsetLimMin      && !getErrS02ZeroAdjOffsetLimMin     ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExZeroAdjOffsetLimMin      (mWriteS02ZeroAdjOffsetLimMin     , this);break;
        case STATE_WRITE_S02_ZERO_MAX               : if(!mEditS02ZeroAdjOffsetLimMax      && !getErrS02ZeroAdjOffsetLimMax     ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExZeroAdjOffsetLimMax      (mWriteS02ZeroAdjOffsetLimMax     , this);break;
        case STATE_WRITE_S02_ZERO_VALUE             : if(!mEditS02ZeroAdjOffsetValue       && !getErrS02ZeroAdjOffsetValue      ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExZeroAdjOffsetValue       (mWriteS02ZeroAdjOffsetValue      , this);break;
        case STATE_WRITE_S02_SCALE_OFFSET           : if(!mEditS02ScaleOffset              && !getErrS02ScaleOffset             ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExScaleOffset              (mWriteS02ScaleOffset             , this);break;
        case STATE_WRITE_S02_SCALE                  : if(!mEditS02Scale                    && !getErrS02Scale                   ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExScale                    (mWriteS02Scale                   , this);break;
        case STATE_WRITE_S02_SCALE_Z_POINT          : if(!mEditS02ScaleZeroPoint           && !getErrS02ScaleZeroPoint          ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExScaleZeroPoint           (mWriteS02ScaleZeroPoint          , this);break;
        case STATE_WRITE_S02_FILTER_SEC             : if(!mEditS02FilterSec                && !getErrS02FilterSec               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExFilterSec                (mWriteS02FilterSec               , this);break;
        case STATE_WRITE_S02_LOG_SENS_LINEARIZE     : if(!mEditS02LogSensorLinearize       && !getErrS02LogSensorLinearize      ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExLogSensorLinearize       (mWriteS02LogSensorLinearize      , this);break;
        case STATE_WRITE_S02_LOG_SENS_VOLT_DECADE   : if(!mEditS02LogSensorVoltPerDecade   && !getErrS02LogSensorVoltPerDecade  ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExLogSensorVoltPerDecade   (mWriteS02LogSensorVoltPerDecade  , this);break;
        case STATE_WRITE_S02_LOG_SENS_VOLT_FULLSCALE: if(!mEditS02LogSensorVoltAtFullScale && !getErrS02LogSensorVoltAtFullScale()              ){setState((eState)(mState + 1), true); return;} pValveSP->setS02ExLogSensorVoltAtFullScale (mWriteS02LogSensorVoltAtFullScale, this);break;
        case STATE_WRITE_CROSSOVER_MOD              : if(!mEditCrossoverModIdx             && !getErrCrossoverModIdx            ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setCrossoverMod                  (mWriteCrossoverModIdx            , this);break;
        case STATE_WRITE_CROSSOVER_LOW              : if(!mEditCrossoverLow                && !getErrCrossoverLow               ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setCrossoverLow                  (mWriteCrossoverLow               , this);break;
        case STATE_WRITE_CROSSOVER_HIGH             : if(!mEditCrossoverHigh               && !getErrCrossoverHigh              ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setCrossoverHigh                 (mWriteCrossoverHigh              , this);break;
        case STATE_WRITE_CROSSOVER_DELA             : if(!mEditCrossoverDela               && !getErrCrossoverDela              ()              ){setState((eState)(mState + 1), true); return;} pValveSP->setCrossoverDela                 (mWriteCrossoverDela              , this);break;
        case STATE_READ_SELECTION                   : if(!mEditSelection         && !getErrS01Selection() && !getErrS02Selection() && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readSensorExSelection            (this                                   ); break;
        case STATE_READ_S01_ANAL_ACTIVE             : if(!mEditS01AnalActive               && !getErrS01AnalActive              () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExAnalActive              (this                                   ); break;
        case STATE_READ_S01_SRC                     : if(!mEditS01SourceIdx                && !getErrS01SourceIdx               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExSource                  (this                                   ); break;
        case STATE_READ_S01_UNIT                    : if(!mEditS01UnitIdx                  && !getErrS01UnitIdx                 () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExUnit                    (this                                   ); break;
        case STATE_READ_S01_FULLSCALE               : if(!mEditS01FullScale                && !getErrS01FullScale               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExFullScale               (this                                   ); break;
        case STATE_READ_S01_DIGI                    : if(!mEditS01DigiValue                && !getErrS01DigiValue               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExDigiValue               (this                                   ); break;
        case STATE_READ_S01_ZERO_ENABLE             : if(!mEditS01ZeroAdjEnable            && !getErrS01ZeroAdjEnable           () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExZeroAdjEnable           (this                                   ); break;
        case STATE_READ_S01_ZERO_MIN                : if(!mEditS01ZeroAdjOffsetLimMin      && !getErrS01ZeroAdjOffsetLimMin     () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExZeroAdjOffsetLimMin     (this                                   ); break;
        case STATE_READ_S01_ZERO_MAX                : if(!mEditS01ZeroAdjOffsetLimMax      && !getErrS01ZeroAdjOffsetLimMax     () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExZeroAdjOffsetLimMax     (this                                   ); break;
        case STATE_READ_S01_ZERO_VALUE              : if(!mEditS01ZeroAdjOffsetValue       && !getErrS01ZeroAdjOffsetValue      () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExZeroAdjOffsetValue      (this                                   ); break;
        case STATE_READ_S01_SCALE_OFFSET            : if(!mEditS01ScaleOffset              && !getErrS01ScaleOffset             () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExScaleOffset             (this                                   ); break;
        case STATE_READ_S01_SCALE                   : if(!mEditS01Scale                    && !getErrS01Scale                   () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExScale                   (this                                   ); break;
        case STATE_READ_S01_SCALE_Z_POINT           : if(!mEditS01ScaleZeroPoint           && !getErrS01ScaleZeroPoint          () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExScaleZeroPoint          (this                                   ); break;
        case STATE_READ_S01_FILTER_SEC              : if(!mEditS01FilterSec                && !getErrS01FilterSec               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExFilterSec               (this                                   ); break;
        case STATE_READ_S01_LOG_SENS_LINEARIZE      : if(!mEditS01LogSensorLinearize       && !getErrS01LogSensorLinearize      () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExLogSensorLinearize      (this                                   ); break;
        case STATE_READ_S01_LOG_SENS_VOLT_DECADE    : if(!mEditS01LogSensorVoltPerDecade   && !getErrS01LogSensorVoltPerDecade  () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExLogSensorVoltPerDecade  (this                                   ); break;
        case STATE_READ_S01_LOG_SENS_VOLT_FULLSCALE : if(!mEditS01LogSensorVoltAtFullScale && !getErrS01LogSensorVoltAtFullScale() && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS01ExLogSensorVoltAtFullScale(this                                   ); break;
        case STATE_READ_S02_ANAL_ACTIVE             : if(!mEditS02AnalActive               && !getErrS02AnalActive              () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExAnalActive              (this                                   ); break;
        case STATE_READ_S02_SRC                     : if(!mEditS02SourceIdx                && !getErrS02SourceIdx               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExSource                  (this                                   ); break;
        case STATE_READ_S02_UNIT                    : if(!mEditS02UnitIdx                  && !getErrS02UnitIdx                 () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExUnit                    (this                                   ); break;
        case STATE_READ_S02_FULLSCALE               : if(!mEditS02FullScale                && !getErrS02FullScale               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExFullScale               (this                                   ); break;
        case STATE_READ_S02_DIGI                    : if(!mEditS02DigiValue                && !getErrS02DigiValue               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExDigiValue               (this                                   ); break;
        case STATE_READ_S02_ZERO_ENABLE             : if(!mEditS02ZeroAdjEnable            && !getErrS02ZeroAdjEnable           () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExZeroAdjEnable           (this                                   ); break;
        case STATE_READ_S02_ZERO_MIN                : if(!mEditS02ZeroAdjOffsetLimMin      && !getErrS02ZeroAdjOffsetLimMin     () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExZeroAdjOffsetLimMin     (this                                   ); break;
        case STATE_READ_S02_ZERO_MAX                : if(!mEditS02ZeroAdjOffsetLimMax      && !getErrS02ZeroAdjOffsetLimMax     () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExZeroAdjOffsetLimMax     (this                                   ); break;
        case STATE_READ_S02_ZERO_VALUE              : if(!mEditS02ZeroAdjOffsetValue       && !getErrS02ZeroAdjOffsetValue      () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExZeroAdjOffsetValue      (this                                   ); break;
        case STATE_READ_S02_SCALE_OFFSET            : if(!mEditS02ScaleOffset              && !getErrS02ScaleOffset             () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExScaleOffset             (this                                   ); break;
        case STATE_READ_S02_SCALE                   : if(!mEditS02Scale                    && !getErrS02Scale                   () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExScale                   (this                                   ); break;
        case STATE_READ_S02_SCALE_Z_POINT           : if(!mEditS02ScaleZeroPoint           && !getErrS02ScaleZeroPoint          () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExScaleZeroPoint          (this                                   ); break;
        case STATE_READ_S02_FILTER_SEC              : if(!mEditS02FilterSec                && !getErrS02FilterSec               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExFilterSec               (this                                   ); break;
        case STATE_READ_S02_LOG_SENS_LINEARIZE      : if(!mEditS02LogSensorLinearize       && !getErrS02LogSensorLinearize      () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExLogSensorLinearize      (this                                   ); break;
        case STATE_READ_S02_LOG_SENS_VOLT_DECADE    : if(!mEditS02LogSensorVoltPerDecade   && !getErrS02LogSensorVoltPerDecade  () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExLogSensorVoltPerDecade  (this                                   ); break;
        case STATE_READ_S02_LOG_SENS_VOLT_FULLSCALE : if(!mEditS02LogSensorVoltAtFullScale && !getErrS02LogSensorVoltAtFullScale() && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readS02ExLogSensorVoltAtFullScale(this                                   ); break;
        case STATE_READ_CROSSOVER_MOD               : if(!mEditCrossoverModIdx             && !getErrCrossoverModIdx            () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readCrossoverMod                 (this                                   ); break;
        case STATE_READ_CROSSOVER_LOW               : if(!mEditCrossoverLow                && !getErrCrossoverLow               () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readCrossoverLow                 (this                                   ); break;
        case STATE_READ_CROSSOVER_HIGH              : if(!mEditCrossoverHigh               && !getErrCrossoverHigh              () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readCrossoverHigh                (this                                   ); break;
        case STATE_READ_CROSSOVER_DELA              : if(!mEditCrossoverDela               && !getErrCrossoverDela              () && mIsWritten){setState((eState)(mState + 1), true); return;} pValveSP->readCrossoverDela                (this                                   ); break;
        }
    }
};
#endif // SENSORSETUPEXDLGMODEL_H
