#ifndef INTERFACESETUPDEVNETDLGMODEL_H
#define INTERFACESETUPDEVNETDLGMODEL_H

#include <QObject>
#include <QDateTime>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/def/datetimeform.h"
#include "source/service/util/unitutil.h"
#include "source/service/util/filewriterex.h"
#include "source/service/coreservice.h"
#include "source/qmlmodel/interfacesetupdevnetassemblyitemmodel.h"

class InterfaceSetupDevNetDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode             READ getAccessMode             NOTIFY signalEventChangedAccessMode           )
    Q_PROPERTY(bool     mIsRS232Test            READ getIsRS232Test            NOTIFY signalEventChangedIsRS232Test          )

    Q_PROPERTY(QString  mMacAddr                READ getMacAddr                NOTIFY signalEventChangedMacAddr              )
    Q_PROPERTY(int      mBaudrateIdx            READ getBaudrateIdx            NOTIFY signalEventChangedBaudrateIdx          )
    Q_PROPERTY(int      mDataTypeIdx            READ getDataTypeIdx            NOTIFY signalEventChangedDataTypeIdx          )
    Q_PROPERTY(int      mPositionUnitIdx        READ getPositionUnitIdx        NOTIFY signalEventChangedPositionUnitIdx      )
    Q_PROPERTY(double   mPositionRange          READ getPositionRange          NOTIFY signalEventChangedPositionRange        )
    Q_PROPERTY(int      mPressureUnitIdx        READ getPressureUnitIdx        NOTIFY signalEventChangedPressureUnitIdx      )
    Q_PROPERTY(double   mSensor01Range          READ getSensor01Range          NOTIFY signalEventChangedSensor01Range        )
    Q_PROPERTY(double   mSensor02Range          READ getSensor02Range          NOTIFY signalEventChangedSensor02Range        )
    Q_PROPERTY(int      mInAssTableIdx          READ getInAssTableIdx          NOTIFY signalEventChangedInAssTableIdx        )
    Q_PROPERTY(int      mOutAssTableIdx         READ getOutAssTableIdx         NOTIFY signalEventChangedOutAssTableIdx       )
    Q_PROPERTY(int      mDIActivation           READ getDIActivation           NOTIFY signalEventChangedDIActivation         )
    Q_PROPERTY(int      mDIFunction             READ getDIFunction             NOTIFY signalEventChangedDIFunction           )
    Q_PROPERTY(int      mDIPolarity             READ getDIPolarity             NOTIFY signalEventChangedDIPolarity           )
    Q_PROPERTY(int      mDOActivation           READ getDOActivation           NOTIFY signalEventChangedDOActivation         )
    Q_PROPERTY(int      mDOFunction             READ getDOFunction             NOTIFY signalEventChangedDOFunction           )
    Q_PROPERTY(int      mDOPolarity             READ getDOPolarity             NOTIFY signalEventChangedDOPolarity           )

    Q_PROPERTY(bool     mErrMacAddr             READ getErrMacAddr             NOTIFY signalEventChangedErrMacAddr           )
    Q_PROPERTY(bool     mErrBaudrateIdx         READ getErrBaudrateIdx         NOTIFY signalEventChangedErrBaudrateIdx       )
    Q_PROPERTY(bool     mErrDataTypeIdx         READ getErrDataTypeIdx         NOTIFY signalEventChangedErrDataTypeIdx       )
    Q_PROPERTY(bool     mErrPositionUnitIdx     READ getErrPositionUnitIdx     NOTIFY signalEventChangedErrPositionUnitIdx   )
    Q_PROPERTY(bool     mErrPositionRange       READ getErrPositionRange       NOTIFY signalEventChangedErrPositionRange     )
    Q_PROPERTY(bool     mErrPressureUnitIdx     READ getErrPressureUnitIdx     NOTIFY signalEventChangedErrPressureUnitIdx   )
    Q_PROPERTY(bool     mErrSensor01Range       READ getErrSensor01Range       NOTIFY signalEventChangedErrSensor01Range     )
    Q_PROPERTY(bool     mErrSensor02Range       READ getErrSensor02Range       NOTIFY signalEventChangedErrSensor02Range     )
    Q_PROPERTY(bool     mErrInAssTableIdx       READ getErrInAssTableIdx       NOTIFY signalEventChangedErrInAssTableIdx     )
    Q_PROPERTY(bool     mErrOutAssTableIdx      READ getErrOutAssTableIdx      NOTIFY signalEventChangedErrOutAssTableIdx    )
    Q_PROPERTY(bool     mErrDIActivation        READ getErrDIActivation        NOTIFY signalEventChangedErrDIActivation      )
    Q_PROPERTY(bool     mErrDIFunction          READ getErrDIFunction          NOTIFY signalEventChangedErrDIFunction        )
    Q_PROPERTY(bool     mErrDIPolarity          READ getErrDIPolarity          NOTIFY signalEventChangedErrDIPolarity        )
    Q_PROPERTY(bool     mErrDOActivation        READ getErrDOActivation        NOTIFY signalEventChangedErrDOActivation      )
    Q_PROPERTY(bool     mErrDOFunction          READ getErrDOFunction          NOTIFY signalEventChangedErrDOFunction        )
    Q_PROPERTY(bool     mErrDOPolarity          READ getErrDOPolarity          NOTIFY signalEventChangedErrDOPolarity        )

    Q_PROPERTY(bool     mEnableMacAddr          READ getEnableMacAddr          NOTIFY signalEventChangedEnableMacAddr        )
    Q_PROPERTY(bool     mEnableBaudrateIdx      READ getEnableBaudrateIdx      NOTIFY signalEventChangedEnableBaudrateIdx    )
    Q_PROPERTY(bool     mEnableDataTypeIdx      READ getEnableDataTypeIdx      NOTIFY signalEventChangedEnableDataTypeIdx    )
    Q_PROPERTY(bool     mEnablePositionUnitIdx  READ getEnablePositionUnitIdx  NOTIFY signalEventChangedEnablePositionUnitIdx)
    Q_PROPERTY(bool     mEnablePositionRange    READ getEnablePositionRange    NOTIFY signalEventChangedEnablePositionRange  )
    Q_PROPERTY(bool     mEnablePressureUnitIdx  READ getEnablePressureUnitIdx  NOTIFY signalEventChangedEnablePressureUnitIdx)
    Q_PROPERTY(bool     mEnableSensor01Range    READ getEnableSensor01Range    NOTIFY signalEventChangedEnableSensor01Range  )
    Q_PROPERTY(bool     mEnableSensor02Range    READ getEnableSensor02Range    NOTIFY signalEventChangedEnableSensor02Range  )
    Q_PROPERTY(bool     mEnableInAssTableIdx    READ getEnableInAssTableIdx    NOTIFY signalEventChangedEnableInAssTableIdx  )
    Q_PROPERTY(bool     mEnableOutAssTableIdx   READ getEnableOutAssTableIdx   NOTIFY signalEventChangedEnableOutAssTableIdx )
    Q_PROPERTY(bool     mEnableDIActivation     READ getEnableDIActivation     NOTIFY signalEventChangedEnableDIActivation   )
    Q_PROPERTY(bool     mEnableDIFunction       READ getEnableDIFunction       NOTIFY signalEventChangedEnableDIFunction     )
    Q_PROPERTY(bool     mEnableDIPolarity       READ getEnableDIPolarity       NOTIFY signalEventChangedEnableDIPolarity     )
    Q_PROPERTY(bool     mEnableDOActivation     READ getEnableDOActivation     NOTIFY signalEventChangedEnableDOActivation   )
    Q_PROPERTY(bool     mEnableDOFunction       READ getEnableDOFunction       NOTIFY signalEventChangedEnableDOFunction     )
    Q_PROPERTY(bool     mEnableDOPolarity       READ getEnableDOPolarity       NOTIFY signalEventChangedEnableDOPolarity     )

    Q_PROPERTY(bool     mIsEdit                 READ getIsEdit                 NOTIFY signalEventChangedIsEdit               )
    Q_PROPERTY(QString  mStrStatus              READ getStrStatus              NOTIFY signalEventChangedStrStatus            )
    Q_PROPERTY(QString  mErrMsg                 READ getErrMsg                 NOTIFY signalEventChangedErrMsg               )
    Q_PROPERTY(QString  mErrMsg2                READ getErrMsg2                NOTIFY signalEventChangedErrMsg2              )
    Q_PROPERTY(int      mProgress               READ getProgress               NOTIFY signalEventChangedProgress             )

public:
    int     mAccessMode    = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test   = false;

    QString  mMacAddr             = "00(unknow)";
    int      mBaudrateIdx         = 0;
    int      mDataTypeIdx         = 0;
    int      mPositionUnitIdx     = 0;
    double   mPositionRange       = 0;
    int      mPressureUnitIdx     = 0;
    double   mSensor01Range       = 0;
    double   mSensor02Range       = 0;
    int      mInAssTableIdx       = 0;
    int      mOutAssTableIdx      = 0;
    int      mDIActivation        = 0;
    int      mDIFunction          = 0;
    int      mDIPolarity          = 0;
    int      mDOActivation        = 0;
    int      mDOFunction          = 0;
    int      mDOPolarity          = 0;

    bool     mErrMacAddr         = false;
    bool     mErrBaudrateIdx     = false;
    bool     mErrDataTypeIdx     = false;
    bool     mErrPositionUnitIdx = false;
    bool     mErrPositionRange   = false;
    bool     mErrPressureUnitIdx = false;
    bool     mErrSensor01Range   = false;
    bool     mErrSensor02Range   = false;
    bool     mErrInAssTableIdx   = false;
    bool     mErrOutAssTableIdx  = false;
    bool     mErrDIActivation    = false;
    bool     mErrDIFunction      = false;
    bool     mErrDIPolarity      = false;
    bool     mErrDOActivation    = false;
    bool     mErrDOFunction      = false;
    bool     mErrDOPolarity      = false;

    bool     mEnableMacAddr         = true;
    bool     mEnableBaudrateIdx     = true;
    bool     mEnableDataTypeIdx     = true;
    bool     mEnablePositionUnitIdx = true;
    bool     mEnablePositionRange   = true;
    bool     mEnablePressureUnitIdx = true;
    bool     mEnableSensor01Range   = true;
    bool     mEnableSensor02Range   = true;
    bool     mEnableInAssTableIdx   = true;
    bool     mEnableOutAssTableIdx  = true;
    bool     mEnableDIActivation    = true;
    bool     mEnableDIFunction      = true;
    bool     mEnableDIPolarity      = true;
    bool     mEnableDOActivation    = true;
    bool     mEnableDOFunction      = true;
    bool     mEnableDOPolarity      = true;

    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){return mAccessMode           ;}
    bool    getIsRS232Test            (){return mIsRS232Test          ;}
    QString getMacAddr                (){return mMacAddr              ;}
    int     getBaudrateIdx            (){return mBaudrateIdx          ;}
    int     getDataTypeIdx            (){return mDataTypeIdx          ;}
    int     getPositionUnitIdx        (){return mPositionUnitIdx      ;}
    double  getPositionRange          (){return mPositionRange        ;}
    int     getPressureUnitIdx        (){return mPressureUnitIdx      ;}
    double  getSensor01Range          (){return mSensor01Range        ;}
    double  getSensor02Range          (){return mSensor02Range        ;}
    int     getInAssTableIdx          (){return mInAssTableIdx        ;}
    int     getOutAssTableIdx         (){return mOutAssTableIdx       ;}
    int     getDIActivation           (){return mDIActivation         ;}
    int     getDIFunction             (){return mDIFunction           ;}
    int     getDIPolarity             (){return mDIPolarity           ;}
    int     getDOActivation           (){return mDOActivation         ;}
    int     getDOFunction             (){return mDOFunction           ;}
    int     getDOPolarity             (){return mDOPolarity           ;}
    bool    getErrMacAddr             (){return mErrMacAddr           ;}
    bool    getErrBaudrateIdx         (){return mErrBaudrateIdx       ;}
    bool    getErrDataTypeIdx         (){return mErrDataTypeIdx       ;}
    bool    getErrPositionUnitIdx     (){return mErrPositionUnitIdx   ;}
    bool    getErrPositionRange       (){return mErrPositionRange     ;}
    bool    getErrPressureUnitIdx     (){return mErrPressureUnitIdx   ;}
    bool    getErrSensor01Range       (){return mErrSensor01Range     ;}
    bool    getErrSensor02Range       (){return mErrSensor02Range     ;}
    bool    getErrInAssTableIdx       (){return mErrInAssTableIdx     ;}
    bool    getErrOutAssTableIdx      (){return mErrOutAssTableIdx    ;}
    bool    getErrDIActivation        (){return mErrDIActivation      ;}
    bool    getErrDIFunction          (){return mErrDIFunction        ;}
    bool    getErrDIPolarity          (){return mErrDIPolarity        ;}
    bool    getErrDOActivation        (){return mErrDOActivation      ;}
    bool    getErrDOFunction          (){return mErrDOFunction        ;}
    bool    getErrDOPolarity          (){return mErrDOPolarity        ;}
    bool    getEnableMacAddr          (){return mEnableMacAddr        ;}
    bool    getEnableBaudrateIdx      (){return mEnableBaudrateIdx    ;}
    bool    getEnableDataTypeIdx      (){return mEnableDataTypeIdx    ;}
    bool    getEnablePositionUnitIdx  (){return mEnablePositionUnitIdx;}
    bool    getEnablePositionRange    (){return mEnablePositionRange  ;}
    bool    getEnablePressureUnitIdx  (){return mEnablePressureUnitIdx;}
    bool    getEnableSensor01Range    (){return mEnableSensor01Range  ;}
    bool    getEnableSensor02Range    (){return mEnableSensor02Range  ;}
    bool    getEnableInAssTableIdx    (){return mEnableInAssTableIdx  ;}
    bool    getEnableOutAssTableIdx   (){return mEnableOutAssTableIdx ;}
    bool    getEnableDIActivation     (){return mEnableDIActivation   ;}
    bool    getEnableDIFunction       (){return mEnableDIFunction     ;}
    bool    getEnableDIPolarity       (){return mEnableDIPolarity     ;}
    bool    getEnableDOActivation     (){return mEnableDOActivation   ;}
    bool    getEnableDOFunction       (){return mEnableDOFunction     ;}
    bool    getEnableDOPolarity       (){return mEnableDOPolarity     ;}
    bool    getIsEdit                 (){return mIsEdit               ;}
    QString getStrStatus              (){return mStrStatus            ;}
    QString getErrMsg                 (){return mErrMsg               ;}
    QString getErrMsg2                (){return mErrMsg2              ;}
    int     getProgress               (){return mProgress             ;}

    void setAccessMode           (int     value){if(mAccessMode            == value)return; mAccessMode            = value; emit signalEventChangedAccessMode           (value);}
    void setIsRS232Test          (bool    value){if(mIsRS232Test           == value)return; mIsRS232Test           = value; emit signalEventChangedIsRS232Test          (value);}
    void setMacAddr              (QString value){if(mMacAddr               == value)return; mMacAddr               = value; emit signalEventChangedMacAddr              (value);}
    void setBaudrateIdx          (int     value){if(mBaudrateIdx           == value)return; mBaudrateIdx           = value; emit signalEventChangedBaudrateIdx          (value);}
    void setDataTypeIdx          (int     value){if(mDataTypeIdx           == value)return; mDataTypeIdx           = value; emit signalEventChangedDataTypeIdx          (value);}
    void setPositionUnitIdx      (int     value){if(mPositionUnitIdx       == value)return; mPositionUnitIdx       = value; emit signalEventChangedPositionUnitIdx      (value);}
    void setPositionRange        (double  value){if(mPositionRange         == value)return; mPositionRange         = value; emit signalEventChangedPositionRange        (value);}
    void setPressureUnitIdx      (int     value){if(mPressureUnitIdx       == value)return; mPressureUnitIdx       = value; emit signalEventChangedPressureUnitIdx      (value);}
    void setSensor01Range        (double  value){if(mSensor01Range         == value)return; mSensor01Range         = value; emit signalEventChangedSensor01Range        (value);}
    void setSensor02Range        (double  value){if(mSensor02Range         == value)return; mSensor02Range         = value; emit signalEventChangedSensor02Range        (value);}
    void setInAssTableIdx        (int     value){if(mInAssTableIdx         == value)return; mInAssTableIdx         = value; emit signalEventChangedInAssTableIdx        (value);}
    void setOutAssTableIdx       (int     value){if(mOutAssTableIdx        == value)return; mOutAssTableIdx        = value; emit signalEventChangedOutAssTableIdx       (value);}
    void setDIActivation         (int     value){if(mDIActivation          == value)return; mDIActivation          = value; emit signalEventChangedDIActivation         (value);}
    void setDIFunction           (int     value){if(mDIFunction            == value)return; mDIFunction            = value; emit signalEventChangedDIFunction           (value);}
    void setDIPolarity           (int     value){if(mDIPolarity            == value)return; mDIPolarity            = value; emit signalEventChangedDIPolarity           (value);}
    void setDOActivation         (int     value){if(mDOActivation          == value)return; mDOActivation          = value; emit signalEventChangedDOActivation         (value);}
    void setDOFunction           (int     value){if(mDOFunction            == value)return; mDOFunction            = value; emit signalEventChangedDOFunction           (value);}
    void setDOPolarity           (int     value){if(mDOPolarity            == value)return; mDOPolarity            = value; emit signalEventChangedDOPolarity           (value);}
    void setErrMacAddr           (bool    value){if(mErrMacAddr            == value)return; mErrMacAddr            = value; emit signalEventChangedErrMacAddr           (value);}
    void setErrBaudrateIdx       (bool    value){if(mErrBaudrateIdx        == value)return; mErrBaudrateIdx        = value; emit signalEventChangedErrBaudrateIdx       (value);}
    void setErrDataTypeIdx       (bool    value){if(mErrDataTypeIdx        == value)return; mErrDataTypeIdx        = value; emit signalEventChangedErrDataTypeIdx       (value);}
    void setErrPositionUnitIdx   (bool    value){if(mErrPositionUnitIdx    == value)return; mErrPositionUnitIdx    = value; emit signalEventChangedErrPositionUnitIdx   (value);}
    void setErrPositionRange     (bool    value){if(mErrPositionRange      == value)return; mErrPositionRange      = value; emit signalEventChangedErrPositionRange     (value);}
    void setErrPressureUnitIdx   (bool    value){if(mErrPressureUnitIdx    == value)return; mErrPressureUnitIdx    = value; emit signalEventChangedErrPressureUnitIdx   (value);}
    void setErrSensor01Range     (bool    value){if(mErrSensor01Range      == value)return; mErrSensor01Range      = value; emit signalEventChangedErrSensor01Range     (value);}
    void setErrSensor02Range     (bool    value){if(mErrSensor02Range      == value)return; mErrSensor02Range      = value; emit signalEventChangedErrSensor02Range     (value);}
    void setErrInAssTableIdx     (bool    value){if(mErrInAssTableIdx      == value)return; mErrInAssTableIdx      = value; emit signalEventChangedErrInAssTableIdx     (value);}
    void setErrOutAssTableIdx    (bool    value){if(mErrOutAssTableIdx     == value)return; mErrOutAssTableIdx     = value; emit signalEventChangedErrOutAssTableIdx    (value);}
    void setErrDIActivation      (bool    value){if(mErrDIActivation       == value)return; mErrDIActivation       = value; emit signalEventChangedErrDIActivation      (value);}
    void setErrDIFunction        (bool    value){if(mErrDIFunction         == value)return; mErrDIFunction         = value; emit signalEventChangedErrDIFunction        (value);}
    void setErrDIPolarity        (bool    value){if(mErrDIPolarity         == value)return; mErrDIPolarity         = value; emit signalEventChangedErrDIPolarity        (value);}
    void setErrDOActivation      (bool    value){if(mErrDOActivation       == value)return; mErrDOActivation       = value; emit signalEventChangedErrDOActivation      (value);}
    void setErrDOFunction        (bool    value){if(mErrDOFunction         == value)return; mErrDOFunction         = value; emit signalEventChangedErrDOFunction        (value);}
    void setErrDOPolarity        (bool    value){if(mErrDOPolarity         == value)return; mErrDOPolarity         = value; emit signalEventChangedErrDOPolarity        (value);}
    void setEnableMacAddr        (bool    value){if(mEnableMacAddr         == value)return; mEnableMacAddr         = value; emit signalEventChangedEnableMacAddr        (value);}
    void setEnableBaudrateIdx    (bool    value){if(mEnableBaudrateIdx     == value)return; mEnableBaudrateIdx     = value; emit signalEventChangedEnableBaudrateIdx    (value);}
    void setEnableDataTypeIdx    (bool    value){if(mEnableDataTypeIdx     == value)return; mEnableDataTypeIdx     = value; emit signalEventChangedEnableDataTypeIdx    (value);}
    void setEnablePositionUnitIdx(bool    value){if(mEnablePositionUnitIdx == value)return; mEnablePositionUnitIdx = value; emit signalEventChangedEnablePositionUnitIdx(value);}
    void setEnablePositionRange  (bool    value){if(mEnablePositionRange   == value)return; mEnablePositionRange   = value; emit signalEventChangedEnablePositionRange  (value);}
    void setEnablePressureUnitIdx(bool    value){if(mEnablePressureUnitIdx == value)return; mEnablePressureUnitIdx = value; emit signalEventChangedEnablePressureUnitIdx(value);}
    void setEnableSensor01Range  (bool    value){if(mEnableSensor01Range   == value)return; mEnableSensor01Range   = value; emit signalEventChangedEnableSensor01Range  (value);}
    void setEnableSensor02Range  (bool    value){if(mEnableSensor02Range   == value)return; mEnableSensor02Range   = value; emit signalEventChangedEnableSensor02Range  (value);}
    void setEnableInAssTableIdx  (bool    value){if(mEnableInAssTableIdx   == value)return; mEnableInAssTableIdx   = value; emit signalEventChangedEnableInAssTableIdx  (value);}
    void setEnableOutAssTableIdx (bool    value){if(mEnableOutAssTableIdx  == value)return; mEnableOutAssTableIdx  = value; emit signalEventChangedEnableOutAssTableIdx (value);}
    void setEnableDIActivation   (bool    value){if(mEnableDIActivation    == value)return; mEnableDIActivation    = value; emit signalEventChangedEnableDIActivation   (value);}
    void setEnableDIFunction     (bool    value){if(mEnableDIFunction      == value)return; mEnableDIFunction      = value; emit signalEventChangedEnableDIFunction     (value);}
    void setEnableDIPolarity     (bool    value){if(mEnableDIPolarity      == value)return; mEnableDIPolarity      = value; emit signalEventChangedEnableDIPolarity     (value);}
    void setEnableDOActivation   (bool    value){if(mEnableDOActivation    == value)return; mEnableDOActivation    = value; emit signalEventChangedEnableDOActivation   (value);}
    void setEnableDOFunction     (bool    value){if(mEnableDOFunction      == value)return; mEnableDOFunction      = value; emit signalEventChangedEnableDOFunction     (value);}
    void setEnableDOPolarity     (bool    value){if(mEnableDOPolarity      == value)return; mEnableDOPolarity      = value; emit signalEventChangedEnableDOPolarity     (value);}
    void setIsEdit               (bool    value){if(mIsEdit                == value)return; mIsEdit                = value; emit signalEventChangedIsEdit               (value);}
    void setStrStatus            (QString value){if(mStrStatus             == value)return; mStrStatus             = value; emit signalEventChangedStrStatus            (value);}
    void setErrMsg               (QString value){if(mErrMsg                == value)return; mErrMsg                = value; emit signalEventChangedErrMsg               (value);}
    void setErrMsg2              (QString value){if(mErrMsg2               == value)return; mErrMsg2               = value; emit signalEventChangedErrMsg2              (value);}
    void setProgress             (int     value){if(mProgress              == value)return; mProgress              = value; emit signalEventChangedProgress             (value);}

signals:
    void signalEventChangedAccessMode           (int     value);
    void signalEventChangedIsRS232Test          (bool    value);
    void signalEventChangedMacAddr              (QString value);
    void signalEventChangedBaudrateIdx          (int     value);
    void signalEventChangedDataTypeIdx          (int     value);
    void signalEventChangedPositionUnitIdx      (int     value);
    void signalEventChangedPositionRange        (double  value);
    void signalEventChangedPressureUnitIdx      (int     value);
    void signalEventChangedSensor01Range        (double  value);
    void signalEventChangedSensor02Range        (double  value);
    void signalEventChangedInAssTableIdx        (int     value);
    void signalEventChangedOutAssTableIdx       (int     value);
    void signalEventChangedDIActivation         (int     value);
    void signalEventChangedDIFunction           (int     value);
    void signalEventChangedDIPolarity           (int     value);
    void signalEventChangedDOActivation         (int     value);
    void signalEventChangedDOFunction           (int     value);
    void signalEventChangedDOPolarity           (int     value);
    void signalEventChangedErrMacAddr           (bool    value);
    void signalEventChangedErrBaudrateIdx       (bool    value);
    void signalEventChangedErrDataTypeIdx       (bool    value);
    void signalEventChangedErrPositionUnitIdx   (bool    value);
    void signalEventChangedErrPositionRange     (bool    value);
    void signalEventChangedErrPressureUnitIdx   (bool    value);
    void signalEventChangedErrSensor01Range     (bool    value);
    void signalEventChangedErrSensor02Range     (bool    value);
    void signalEventChangedErrInAssTableIdx     (bool    value);
    void signalEventChangedErrOutAssTableIdx    (bool    value);
    void signalEventChangedErrDIActivation      (bool    value);
    void signalEventChangedErrDIFunction        (bool    value);
    void signalEventChangedErrDIPolarity        (bool    value);
    void signalEventChangedErrDOActivation      (bool    value);
    void signalEventChangedErrDOFunction        (bool    value);
    void signalEventChangedErrDOPolarity        (bool    value);
    void signalEventChangedEnableMacAddr        (bool    value);
    void signalEventChangedEnableBaudrateIdx    (bool    value);
    void signalEventChangedEnableDataTypeIdx    (bool    value);
    void signalEventChangedEnablePositionUnitIdx(bool    value);
    void signalEventChangedEnablePositionRange  (bool    value);
    void signalEventChangedEnablePressureUnitIdx(bool    value);
    void signalEventChangedEnableSensor01Range  (bool    value);
    void signalEventChangedEnableSensor02Range  (bool    value);
    void signalEventChangedEnableInAssTableIdx  (bool    value);
    void signalEventChangedEnableOutAssTableIdx (bool    value);
    void signalEventChangedEnableDIActivation   (bool    value);
    void signalEventChangedEnableDIFunction     (bool    value);
    void signalEventChangedEnableDIPolarity     (bool    value);
    void signalEventChangedEnableDOActivation   (bool    value);
    void signalEventChangedEnableDOFunction     (bool    value);
    void signalEventChangedEnableDOPolarity     (bool    value);
    void signalEventChangedIsEdit               (bool    value);
    void signalEventChangedStrStatus            (QString value);
    void signalEventChangedErrMsg               (QString value);
    void signalEventChangedErrMsg2              (QString value);
    void signalEventChangedProgress             (int     value);
    void signalEventCompletedLoad               (             );

public:
    explicit InterfaceSetupDevNetDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS                      ;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST               ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_MAC              ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_BAUDRATE         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_POS_UNIT         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_POS_GAIN         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_PRESSURE_UNIT    ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_S01_GAIN         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_S02_GAIN         ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_INPUT_ASS        ;
        ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_OUTPUT_ASS       ;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DI            ;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DO            ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_MAC_ADDR     ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_BAUDRATE     ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_POS_UNIT     ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_POS_GAIN     ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_PRESSURE_UNIT;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_S01_GAIN     ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_S02_GAIN     ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_INPUT_ASS    ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_OUTPUT_ASS   ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_DI           ;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_DO           ;

        pConfigSP->loadInterfaceDNetAssembly();
        loadAssemblyTable();

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_MAC);
    }
    ~InterfaceSetupDevNetDlgModel()
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

    void onValveReadedInterfaceCfgDNetMAC(ValveResponseInterfaceConfigDNetMacDto dto)
    {
        if(mState != eState::STATE_READ_MAC || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc/* || dto.mMacAddr > 100*/)
        {
            setState(mState);
            return;
        }

        setEnableMacAddr(true); // mac addr is not editable

        if(mIsWritten)
        {
            //setErrMacAddr(mWriteMAC != dto.mMacAddr);
        }
        else
        {
            setMacAddr(QString("%1").arg(dto.mMacAddr,2,10,QChar('0')));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetBaudrate(ValveResponseInterfaceConfigDNetBaudrateDto dto)
    {
        if(mState != eState::STATE_READ_BAUDRATE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setEnableBaudrateIdx(true); // mac addr is not editable

        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << QString("res = %1, write = %2, baudrate = %3").arg(dto.mResData).arg(mWriteBaudrateIdx).arg(dto.mBaudrate);

        if(mIsWritten)
        {
            setErrBaudrateIdx(mWriteBaudrateIdx != dto.mBaudrate);
        }
        else
        {
            setBaudrateIdx(dto.mBaudrate);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetPosUnit(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_POS_UNIT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPositionUnitIdx(mWritePosUnit != dto.mValue.toLower());
        }
        else
        {
            setPositionUnitIdx(transUnitToPosIdx(dto.mValue));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetPosGain(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_POS_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPositionRange((mWritePosGain != dto.mValue.toLower()));
        }
        else
        {
            setPositionRange(calRange(dto.mValue));
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetPressureUnit(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_PRESSURE_UNIT || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPressureUnitIdx(mWritePressureUnit != dto.mValue.toLower());
        }
        else
        {
            setPressureUnitIdx(transUnitToPressureIdx(dto.mValue));
        }

        setState((eState)(mState + 1));
    }
    void onValveReadedInterfaceCfgDNetSensor01Gain(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_S01_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrSensor01Range((mWriteSensor01Gain != dto.mValue.toLower()));
        }
        else
        {
            setSensor01Range(calRange(dto.mValue));
        }

        setState((eState)(mState + 1));
    }
    void onValveReadedInterfaceCfgDNetSensor02Gain(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_S02_GAIN || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrSensor01Range((mWriteSensor02Gain != dto.mValue.toLower()));
        }
        else
        {
            setSensor02Range(calRange(dto.mValue));
        }

        setState((eState)(mState + 1));
    }
    void onValveReadedInterfaceCfgDNetInputAss(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_IN_ASS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrInAssTableIdx(mWriteInAssembly != dto.mValue.toLower());
        }
        else
        {
            setInputAssemblySeqArrayByHexValue(dto.mValue);
        }

        setState((eState)(mState + 1));
    }
    void onValveReadedInterfaceCfgDNetOutputAss(ValveResponseSimpleValueDto dto)
    {
        if(mState != eState::STATE_READ_OUT_ASS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrOutAssTableIdx(mWriteOutAssembly != dto.mValue.toLower());
        }
        else
        {
            setOutputAssemblySeqArrayByHexValue(dto.mValue);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetDi(ValveResponseInterfaceConfigDNetDiDto dto)
    {
        if(mState != eState::STATE_READ_DI || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrDIActivation(dto.mDIActivation != mWriteDIActivation);
            setErrDIFunction  (dto.mDIFunction   != mWriteDIFunction  );
            setErrDIPolarity  (dto.mDIPolarity   != mWriteDIPolarity  );
        }
        else
        {
            setDIActivation(dto.mDIActivation);
            setDIFunction  (dto.mDIFunction  );
            setDIPolarity  (dto.mDIPolarity  );
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgDNetDo(ValveResponseInterfaceConfigDNetDoDto dto)
    {
        if(mState != eState::STATE_READ_DO || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrDOActivation(dto.mDOActivation != mWriteDOActivation);
            setErrDOFunction  (dto.mDOFunction   != mWriteDOFunction  );
            setErrDOPolarity  (dto.mDOPolarity   != mWriteDOPolarity  );

            onCommandSetEdit(getErrDataTypeIdx    ()||
                             getErrPositionUnitIdx()||
                             getErrPositionRange  ()||
                             getErrPressureUnitIdx()||
                             getErrSensor01Range  ()||
                             getErrSensor02Range  ()||
                             getErrInAssTableIdx  ()||
                             getErrOutAssTableIdx ()||
                             getErrDIActivation   ()||
                             getErrDIFunction     ()||
                             getErrDIPolarity     ()||
                             getErrDOActivation   ()||
                             getErrDOFunction     ()||
                             getErrDOPolarity     ());
        }
        else
        {
            setDOActivation(dto.mDOActivation);
            setDOFunction  (dto.mDOFunction  );
            setDOPolarity  (dto.mDOPolarity  );
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE int onCommandGetInputAssemblyItemCount()
    {
        return mInputTable.size();
    }

    Q_INVOKABLE InterfaceSetupDevNetAssemblyItemModel * onCommandGetInputAssemblyItem(int seq)
    {
        if(seq < 1)
            return nullptr;

        return mInputTable.at(seq - 1);
    }

    Q_INVOKABLE void onCommandSelectInputAssemblyItem(int seq, bool isSelect)
    {
        InterfaceSetupDevNetAssemblyItemModel * pSelectedItem = onCommandGetInputAssemblyItem(seq);
        InterfaceSetupDevNetAssemblyItemModel * pDependentItem = onCommandGetInputAssemblyItem(pSelectedItem->getDepSeq());

        pSelectedItem->setIsSelected(isSelect);

        if(pDependentItem != nullptr && isSelect)
        {
            pDependentItem->setIsSelected(!isSelect);
        }

        int nextIdx = 0;

        foreach(InterfaceSetupDevNetAssemblyItemModel * pItem, mInputTable)
        {
            if(pItem->getIsSelected())
            {
                pItem->setIndex(nextIdx);
                nextIdx = nextIdx + pItem->getLength();
            }
        }
    }

    Q_INVOKABLE int onCommandGetOutputAssemblyItemCount()
    {
        return mOutputTable.size();
    }

    Q_INVOKABLE InterfaceSetupDevNetAssemblyItemModel * onCommandGetOutputAssemblyItem(int seq)
    {
        if(seq < 1)
            return nullptr;

        return mOutputTable.at(seq - 1);
    }

    Q_INVOKABLE void onCommandSelectOutputAssemblyItem(int seq, bool isSelect)
    {
        InterfaceSetupDevNetAssemblyItemModel * pSelectedItem = onCommandGetOutputAssemblyItem(seq);
        InterfaceSetupDevNetAssemblyItemModel * pDependentItem = onCommandGetOutputAssemblyItem(pSelectedItem->getDepSeq());

        pSelectedItem->setIsSelected(isSelect);

        if(pDependentItem != nullptr && isSelect)
        {
            pDependentItem->setIsSelected(!isSelect);
        }

        int nextIdx = 0;

        foreach(InterfaceSetupDevNetAssemblyItemModel * pItem, mOutputTable)
        {
            if(pItem->getIsSelected())
            {
                pItem->setIndex(nextIdx);
                nextIdx = nextIdx + pItem->getLength();
            }
        }
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int mac, int baudrateIdx, int posUnitIdx, double posRange, int pressureUnitIdx, double s01Range, double s02Range, int diActivation, int diFunction, int diPolarity, int doActivation, int doFunction, int doPolarity)
    {
        mIsWritten         = true        ;

        mWriteMAC             = mac;
        mWriteBaudrateIdx     = baudrateIdx;
        mWritePosUnit         = transIdxToPosUnit                    (posUnitIdx     );
        mWritePosGain         = calGain                              (posRange       );
        mWritePressureUnit    = transIdxToPressureUnit               (pressureUnitIdx);
        mWriteSensor01Gain    = calGain                              (s01Range       );
        mWriteSensor02Gain    = calGain                              (s02Range       );
        mWriteInAssembly      = transInputAssemblySeqArrayToHexValue (               );
        mWriteOutAssembly     = transOutputAssemblySeqArrayToHexValue(               );

        mWriteDIActivation = diActivation;
        mWriteDIFunction   = diFunction  ;
        mWriteDIPolarity   = diPolarity  ;
        mWriteDOActivation = doActivation;
        mWriteDOFunction   = doFunction  ;
        mWriteDOPolarity   = doPolarity  ;


        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << "mWriteBaudrateIdx = " << mWriteBaudrateIdx;

        setIsEdit(false);

        setErrMsg("");
        setErrMsg2("");

        setState(eState::STATE_WRITE_MAC);
    }

    Q_INVOKABLE double onCommandGetS01FullScale(int unitIdx)
    {
        double fullScale = UNITUTIL_CONVERT(pValveSP->getS01SullScaleUnit(), pValveSP->getS01FullScale(), transIdxToDpUnit(unitIdx));
        return fullScale;

    }
    Q_INVOKABLE double onCommandGetS02FullScale(int unitIdx)
    {
        if(pValveSP->getSensorVersion() == 1)
            return 0;

        double fullScale = UNITUTIL_CONVERT(pValveSP->getS02SullScaleUnit(), pValveSP->getS02FullScale(), transIdxToDpUnit(unitIdx));
        return fullScale;
    }

    Q_INVOKABLE int onCommandGetSensorRange01FixedN(int unitIdx)
    {
        return calPressureFixedN(unitIdx, pValveSP->getS01FullScalePrec(),  pValveSP->getS01SullScaleUnit());
    }
    Q_INVOKABLE int onCommandGetSensorRange02FixedN(int unitIdx)
    {
        return calPressureFixedN(unitIdx, pValveSP->getS02FullScalePrec(),  pValveSP->getS02SullScaleUnit());
    }

    Q_INVOKABLE void onCommandExportEDS(QString filePath)
    {
        FileWriterEx file;
        QStringList contents;
        int splitIdx = filePath.lastIndexOf("/")+1;
        QString dir = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        if(file.open(dir, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            setErrMsg2("export failed(1)");
            return;
        }

        contents = createEDSContents();

        foreach(QString line, contents)
        {
            file.appendLine(line);
        }

        file.close();
        return;
    }

    void onValveWrittenInterfaceConfigDNetMacAddr(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_MAC || dto.mReqDto.mpRef != this)
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

    void onValveWrittenInterfaceConfigDNetBaudrate(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_BAUDRATE || dto.mReqDto.mpRef != this)
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


    void onValveWrittenInterfaceConfigDNetPosUnit(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_POS_UNIT || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetPosGain     (ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_POS_GAIN || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetPressureUnit(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_PRESSURE_UNIT || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetSensor01Gain(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_S01_GAIN || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetSensor02Gain(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_S02_GAIN || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetInputAss(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_IN_ASS || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetOutputAss(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_OUT_ASS || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetDi(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_DI || dto.mReqDto.mpRef != this)
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
    void onValveWrittenInterfaceConfigDNetDo(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_DO || dto.mReqDto.mpRef != this)
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
    enum eState{
        STATE_WRITE_MAC           = 0                            ,
        STATE_WRITE_BAUDRATE      = STATE_WRITE_MAC           + 1,
        STATE_WRITE_POS_UNIT      = STATE_WRITE_BAUDRATE      + 1,
        STATE_WRITE_POS_GAIN      = STATE_WRITE_POS_UNIT      + 1,
        STATE_WRITE_PRESSURE_UNIT = STATE_WRITE_POS_GAIN      + 1,
        STATE_WRITE_S01_GAIN      = STATE_WRITE_PRESSURE_UNIT + 1,
        STATE_WRITE_S02_GAIN      = STATE_WRITE_S01_GAIN      + 1,
        STATE_WRITE_IN_ASS        = STATE_WRITE_S02_GAIN      + 1,
        STATE_WRITE_OUT_ASS       = STATE_WRITE_IN_ASS        + 1,
        STATE_WRITE_DI            = STATE_WRITE_OUT_ASS       + 1,
        STATE_WRITE_DO            = STATE_WRITE_DI            + 1,
        STATE_READ_MAC            = STATE_WRITE_DO            + 1,
        STATE_READ_BAUDRATE       = STATE_READ_MAC            + 1,
        STATE_READ_POS_UNIT       = STATE_READ_BAUDRATE       + 1,
        STATE_READ_POS_GAIN       = STATE_READ_POS_UNIT       + 1,
        STATE_READ_PRESSURE_UNIT  = STATE_READ_POS_GAIN       + 1,
        STATE_READ_S01_GAIN       = STATE_READ_PRESSURE_UNIT  + 1,
        STATE_READ_S02_GAIN       = STATE_READ_S01_GAIN       + 1,
        STATE_READ_IN_ASS         = STATE_READ_S02_GAIN       + 1,
        STATE_READ_OUT_ASS        = STATE_READ_IN_ASS         + 1,
        STATE_READ_DI             = STATE_READ_OUT_ASS        + 1,
        STATE_READ_DO             = STATE_READ_DI             + 1,
        STATE_READY               = STATE_READ_DO             + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_MAC;

    QList<InterfaceSetupDevNetAssemblyItemModel *>mInputTable;
    QList<InterfaceSetupDevNetAssemblyItemModel *>mOutputTable;

    bool    mIsWritten            = false;
    int     mWriteMAC             = 0;
    int     mWriteBaudrateIdx     = 0;
    QString mWritePosUnit         = "1001";
    QString mWritePosGain         = "3F800000";
    QString mWritePressureUnit    = "1001";
    QString mWriteSensor01Gain    = "3F800000";
    QString mWriteSensor02Gain    = "3F800000";
    QString mWriteInAssembly      = "00";
    QString mWriteOutAssembly     = "00";
    int     mWriteDIActivation    = 0;
    int     mWriteDIFunction      = 0;
    int     mWriteDIPolarity      = 0;
    int     mWriteDOActivation    = 0;
    int     mWriteDOFunction      = 0;
    int     mWriteDOPolarity      = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        int progress = 0;
        QString strStatus;

        mState = state;

        if(mIsWritten == false && mState == STATE_READY)
        {
            onCommandSetEdit(false);

            emit signalEventCompletedLoad();
        }

        progress = ((mState) * 100) / STATE_READY;

        if(mState >= STATE_READ_MAC && mState <= STATE_READ_DO)
        {
            strStatus = "loading";
        }
        else if(mState >= STATE_WRITE_POS_UNIT && mState <= STATE_WRITE_DO)
        {
            strStatus = "writting";
        }
        else
        {
            progress = 100;
            strStatus = "ready";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)STATE_WRITE_MAC          : pValveSP->setInterfaceConfigDNetMacAddress   (QString("%1").arg(mWriteMAC, 2, 16, QChar('0'))        , this); break;
        case (int)STATE_WRITE_BAUDRATE     : pValveSP->setInterfaceConfigDNetBaudrate     (QString("%1").arg(mWriteBaudrateIdx, 2, 10, QChar('0')), this); break;
        case (int)STATE_WRITE_POS_UNIT     : pValveSP->setInterfaceConfigDNetPosUnit      (mWritePosUnit                                          , this); break;
        case (int)STATE_WRITE_POS_GAIN     : pValveSP->setInterfaceConfigDNetPosGain      (mWritePosGain                                          , this); break;
        case (int)STATE_WRITE_PRESSURE_UNIT: pValveSP->setInterfaceConfigDNetPressureUnit (mWritePressureUnit                                     , this); break;
        case (int)STATE_WRITE_S01_GAIN     : pValveSP->setInterfaceConfigDNetSensor01Gain (mWriteSensor01Gain                                     , this); break;
        case (int)STATE_WRITE_S02_GAIN     : pValveSP->setInterfaceConfigDNetSensor02Gain (mWriteSensor02Gain                                     , this); break;
        case (int)STATE_WRITE_IN_ASS       : pValveSP->setInterfaceConfigDNetInputAss     (mWriteInAssembly                                       , this); break;
        case (int)STATE_WRITE_OUT_ASS      : pValveSP->setInterfaceConfigDNetOutputAss    (mWriteOutAssembly                                      , this); break;
        case (int)STATE_WRITE_DI           : pValveSP->setInterfaceConfigDNetDi           (mWriteDIActivation, mWriteDIFunction, mWriteDIPolarity , this); break;
        case (int)STATE_WRITE_DO           : pValveSP->setInterfaceConfigDNetDo           (mWriteDOActivation, mWriteDOFunction, mWriteDOPolarity , this); break;
        case (int)STATE_READ_MAC           : pValveSP->readInterfaceConfigDNetMac         (this); break;
        case (int)STATE_READ_BAUDRATE      : pValveSP->readInterfaceConfigDNetBaudrate    (this); break;
        case (int)STATE_READ_POS_UNIT      : pValveSP->readInterfaceConfigDNetPosUnit     (this); break;
        case (int)STATE_READ_POS_GAIN      : pValveSP->readInterfaceConfigDNetPosGain     (this); break;
        case (int)STATE_READ_PRESSURE_UNIT : pValveSP->readInterfaceConfigDNetPressureUnit(this); break;
        case (int)STATE_READ_S01_GAIN      : pValveSP->readInterfaceConfigDNetSensor01Gain(this); break;
        case (int)STATE_READ_S02_GAIN      : pValveSP->readInterfaceConfigDNetSensor02Gain(this); break;
        case (int)STATE_READ_IN_ASS        : pValveSP->readInterfaceConfigDNetInputAss    (this); break;
        case (int)STATE_READ_OUT_ASS       : pValveSP->readInterfaceConfigDNetOutputAss   (this); break;
        case (int)STATE_READ_DI            : pValveSP->readInterfaceConfigDNetDi          (this); break;
        case (int)STATE_READ_DO            : pValveSP->readInterfaceConfigDNetDo          (this); break;
        }
    }

private:
    int transDataTypeToIdx(QString value)
    {
        int type = value.toInt(nullptr, 16);
        switch (type) {
        case 195: return 0; // 0xC3 - INT
        case 202: return 1; // 0xCA - REAL
        }
        return 0;
    }

    int transUnitToPosIdx(QString value)
    {
        int unit = value.toInt(nullptr, 16);
        switch (unit) {
        case 4097: return 0; // 0x1001 - counts
        case 4103: return 1; // 0x1007 - percent
        case 5891: return 2; // 0x1703 - degree
        }
        return 0;
    }

    int transUnitToPressureIdx(QString value)
    {
        int unit = value.toInt(nullptr, 16);
        switch (unit) {
        case 4097: return 0; // 0x1001 - counts
        case 4103: return 1; // 0x1007 - percent
        case 4864: return 2; // 0x1300 - psi
        case 4865: return 3; // 0x1301 - Torr
        case 4866: return 4; // 0x1302 - mTorr
        case 4871: return 5; // 0x1307 - bar
        case 4872: return 6; // 0x1308 - mbar
        case 4873: return 6; // 0x1309 - pa
        case 4875: return 6; // 0x120B - atm
        }
        return 0;
    }

    double calRange(QString value)
    {
        float gain;
        QByteArray hexBuff;
        QByteArray floatBuff;

        hexBuff.append(value.at(6));
        hexBuff.append(value.at(7));
        hexBuff.append(value.at(4));
        hexBuff.append(value.at(5));
        hexBuff.append(value.at(2));
        hexBuff.append(value.at(3));
        hexBuff.append(value.at(0));
        hexBuff.append(value.at(1));

        floatBuff = QByteArray::fromHex(hexBuff);

        gain = *((float *)floatBuff.data());

        return gain;
    }

//    double calRange(QString value)
//    {
//        float gain;
//        QByteArray hexBuff;
//        QByteArray floatBuff;

//        hexBuff.append(value.at(6));
//        hexBuff.append(value.at(7));
//        hexBuff.append(value.at(4));
//        hexBuff.append(value.at(5));
//        hexBuff.append(value.at(2));
//        hexBuff.append(value.at(3));
//        hexBuff.append(value.at(0));
//        hexBuff.append(value.at(1));

//        floatBuff = QByteArray::fromHex(hexBuff);

//        gain = *((float *)floatBuff.data());

//        return 10000.0 * gain;
//    }

    void setInputAssemblySeqArrayByHexValue(QString value)
    {
        quint32 maskedValue = value.toUInt(nullptr, 16);

        for(quint32 shift = 0; shift < 32 && shift < (quint32)mInputTable.size(); shift++)
        {
            quint32 mask = (0x00000001 << shift) & 0xFFFFFFFF;
            onCommandSelectInputAssemblyItem(shift + 1, (maskedValue & mask) != 0);
        }
    }

    void setOutputAssemblySeqArrayByHexValue(QString value)
    {
        quint32 maskedValue = value.toUInt(nullptr, 16);

        for(quint32 shift = 0; shift < 32 && shift < (quint32)mOutputTable.size(); shift++)
        {
            quint32 mask = (0x00000001 << shift) & 0xFFFFFFFF;
            onCommandSelectOutputAssemblyItem(shift + 1, (maskedValue & mask) != 0);
        }
    }

    int transIdxToDpUnit(int idx)
    {
        switch(idx)
        {
        case 2:
            return UnitUtilEnumDef::PRESSURE_UNIT_PSI;
        case 3:
            return UnitUtilEnumDef::PRESSURE_UNIT_TORR;
        case 4:
            return UnitUtilEnumDef::PRESSURE_UNIT_MTORR;
        case 5:
            return UnitUtilEnumDef::PRESSURE_UNIT_BAR;
        case 6:
            return UnitUtilEnumDef::PRESSURE_UNIT_MBAR;
        case 7:
            return UnitUtilEnumDef::PRESSURE_UNIT_PA;
        case 8:
            return UnitUtilEnumDef::PRESSURE_UNIT_ATM;
        }
        return UnitUtilEnumDef::PRESSURE_UNIT_TORR;
    }

    QString transIdxToDataType(int idx)
    {
        switch (idx) {
        //case 0: return QString("%1").arg(195,2,16,QChar('0'));
        case 1: return QString("%1").arg(202,2,16,QChar('0'));
        default: return QString("%1").arg(195,2,16,QChar('0'));
        }
    }
    QString transIdxToPosUnit(int idx)
    {
        switch (idx) {
        //case 0: return QString("%1").arg(4097,4,10,QChar('0'));
        case 1: return QString("%1").arg(4103,4,16,QChar('0'));
        case 2: return QString("%1").arg(5891,4,16,QChar('0'));
        default: return QString("%1").arg(4097,4,16,QChar('0'));
        }
    }
    QString calGain(double range)
    {
        float gain = range / 1;

        //qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]gain = " << QString("%1").arg(gain,0,'f',10);
        QByteArray gainBuff;
        gainBuff.append(((char *)&gain)[3]);
        gainBuff.append(((char *)&gain)[2]);
        gainBuff.append(((char *)&gain)[1]);
        gainBuff.append(((char *)&gain)[0]);

        return gainBuff.toHex();
    }
//    QString calGain(double range)
//    {
//        float gain = range / 10000.0;

//        //qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]gain = " << QString("%1").arg(gain,0,'f',10);
//        QByteArray gainBuff;
//        gainBuff.append(((char *)&gain)[3]);
//        gainBuff.append(((char *)&gain)[2]);
//        gainBuff.append(((char *)&gain)[1]);
//        gainBuff.append(((char *)&gain)[0]);

//        return gainBuff.toHex();
//    }
    QString transIdxToPressureUnit(int idx)
    {
        switch (idx) {
        //case 0: return QString("%1").arg(1001,4,10,QChar('0'));  // count
        case 1: return QString("%1").arg(4103,4,16,QChar('0'));  // percent
        case 2: return QString("%1").arg(4864,4,16,QChar('0'));  // psi
        case 3: return QString("%1").arg(4865,4,16,QChar('0'));  // torr
        case 4: return QString("%1").arg(4866,4,16,QChar('0'));  // mtorr
        case 5: return QString("%1").arg(4871,4,16,QChar('0'));  // bar
        case 6: return QString("%1").arg(4872,4,16,QChar('0'));  // mbar
        case 7: return QString("%1").arg(4873,4,16,QChar('0'));  // pa
        case 8: return QString("%1").arg(4875,4,16,QChar('0'));  // atm
        default: return QString("%1").arg(4097,4,16,QChar('0'));  // count
        }
    }
    QString transInputAssemblySeqArrayToHexValue()
    {
        quint32 value = 0;
        quint32 mask = 0x00000001;

        for(int idx = 0; idx < mInputTable.size(); idx++)
        {
            if(mInputTable.at(idx)->getIsSelected())
                value = value | ((mask << idx) & 0xFFFFFFFF);
        }
        return QString("%1").arg(value,8,16,QChar('0'));
    }
    QString transOutputAssemblySeqArrayToHexValue()
    {
        quint32 value = 0;
        quint32 mask = 0x00000001;

        for(int idx = 0; idx < mOutputTable.size(); idx++)
        {
            if(mOutputTable.at(idx)->getIsSelected())
                value = value | ((mask << idx) & 0xFFFFFFFF);
        }
        return QString("%1").arg(value,8,16,QChar('0'));
    }

    int calPressureFixedN(int unitIdx, int fullScalePrec, int fullScaleUnit)
    {
        int selUnit;
        int precision;

        switch (unitIdx) {
        case 2: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_PSI  ;break;  // psi
        case 3: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_TORR ;break;  // torr
        case 4: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_MTORR;break;  // mtorr
        case 5: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_BAR  ;break;  // bar
        case 6: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_MBAR ;break;  // mbar
        case 7: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_PA   ;break;  // pa
        case 8: selUnit = UnitUtilEnumDef::PRESSURE_UNIT_ATM  ;break;  // atm
            break;
        default: precision = 3; return precision;
        }

        precision = fullScalePrec + UNITUTIL_ADD_PRECISION(fullScaleUnit, selUnit);
        precision = precision < 0 ? 0 : precision > 6 ? 6 : precision;

        return precision;
    }

    void loadAssemblyTable()
    {
        int itemCount;

        itemCount = pConfigSP->mInputAssemblyTable.size();

        foreach(DNetAssemblyItem item, pConfigSP->mInputAssemblyTable)
        {
            InterfaceSetupDevNetAssemblyItemModel * pQmlItem = new InterfaceSetupDevNetAssemblyItemModel(item, this);
            mInputTable.append(pQmlItem);
        }

        itemCount = pConfigSP->mOutputAssemblyTable.size();

        foreach(DNetAssemblyItem item, pConfigSP->mOutputAssemblyTable)
        {
            InterfaceSetupDevNetAssemblyItemModel * pQmlItem = new InterfaceSetupDevNetAssemblyItemModel(item, this);
            mOutputTable.append(pQmlItem);
        }
    }

    QStringList createEDSContents()
    {
        QStringList contents;
        QFile file;
        int inputLength = 0;
        int outputLength = 0;
        QString inputObjectNames;
        QString outputObjectNames;

        foreach(InterfaceSetupDevNetAssemblyItemModel * pItem, mInputTable)
        {
            if(pItem->getIsSelected())
            {
                inputLength = inputLength + pItem->getLength();

                if(inputObjectNames.length() != 0)
                    inputObjectNames.append(",");

                inputObjectNames.append(pItem->getName());
            }
        }

        if((inputLength % 2) != 0)  // 바이트 수는 짝수만 설정가능
            inputLength = inputLength + 1;

        foreach(InterfaceSetupDevNetAssemblyItemModel * pItem, mOutputTable)
        {
            if(pItem->getIsSelected())
            {
                outputLength = outputLength + pItem->getLength();

                if(outputObjectNames.length() != 0)
                    outputObjectNames.append(",");

                outputObjectNames.append(pItem->getName());
            }
        }

        if((outputLength % 2) != 0)  // 바이트 수는 짝수만 설정가능
            outputLength = outputLength + 1;

        file.setFileName(QString("%1/ref_sample/eds_sample.txt").arg(QApplication::applicationDirPath()));
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            setErrMsg2("export failed(2)");
            return contents;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");

        do{
            QString line = out.readLine();

            if     (line.contains("DescText"   )){line.append(QString(" %1;").arg("\"NOVASEN EDS FILE\""                          ));}
            else if(line.contains("CreateDate" )){line.append(QString(" %1;").arg(QDate::currentDate().toString(EDS_FILE_DATE_FMT)));}
            else if(line.contains("CreateTime" )){line.append(QString(" %1;").arg(QDateTime::currentDateTime().toString(TIME_FMT) ));}
            else if(line.contains("ModDate"    )){line.append(QString(" %1;").arg(QDate::currentDate().toString(EDS_FILE_DATE_FMT)));}
            else if(line.contains("ModTime"    )){line.append(QString(" %1;").arg(QDateTime::currentDateTime().toString(TIME_FMT) ));}
            else if(line.contains("Revision"   )){line.append(QString(" %1;").arg("0.0"                                           ));}
            else if(line.contains("VendCode"   )){line.append(QString(" %1;").arg("0"                                             ));}
            else if(line.contains("VendName"   )){line.append(QString(" %1;").arg("\"NOVASEN\""                                   ));}
            else if(line.contains("ProdTypeStr")){line.append(QString(" %1;").arg("\"\""                                          ));}
            else if(line.contains("ProdType"   )){line.append(QString(" %1;").arg("0"                                             ));}
            else if(line.contains("ProdCode"   )){line.append(QString(" %1;").arg("0"                                             ));}
            else if(line.contains("MajRev"     )){line.append(QString(" %1;").arg("0"                                             ));}
            else if(line.contains("MinRev"     )){line.append(QString(" %1;").arg("0"                                             ));}
            else if(line.contains("ProdName"   )){line.append(QString(" %1;").arg("\"NOVASEN_APC_VALVE\""                         ));}
            else if(line.contains("Catalog"    )){line.append(QString(" %1;").arg("\"0\""                                         ));}
            else if(line.contains("Default"    )){line.append(QString(" %1;").arg("0x0001"                                        ));}
            else if(line.contains("PollInfo"   )){line.append(QString(" %1;").arg("0x0001,1,1"                                    ));}
            else if(line.contains("StrobeInfo" )){line.append(QString(" %1;").arg("0x0002,1,1"                                    ));}
            else if(line.contains("COSInfo"    )){line.append(QString(" %1;").arg("0x0004,1,1"                                    ));}
            else if(line.contains("CyclicInfo" )){line.append(QString(" %1;").arg("0x0008,1,1"                                    ));}
            else if(line.contains("Input1"     )){line.append(QString(" %1,0,0x000F,\"Input Assembly 1\",6,\"20 02 24 01 30 03\",\"%2\";").arg(inputLength).arg(inputObjectNames));}
            else if(line.contains("Output1"    )){line.append(QString(" %1,0,0x000F,\"Output Assembly 2\",6,\"20 02 24 02 30 03\",\"%2\";").arg(outputLength).arg(outputObjectNames));}

            contents.append(line);

        }while(!out.atEnd());

        file.close();
        return contents;
    }
};

#endif // INTERFACESETUPDEVNETDLGMODEL_H
