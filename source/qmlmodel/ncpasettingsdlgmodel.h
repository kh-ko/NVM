#ifndef NCPASETTINGSDLGMODEL_H
#define NCPASETTINGSDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class NCPASettingsDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode              NOTIFY signalEventChangedAccessMode             )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test             NOTIFY signalEventChangedIsRS232Test            )
    Q_PROPERTY(int      mPosResolutionIdx        READ getPosResolutionIdx        NOTIFY signalEventChangedPosResolutionIdx       )
    Q_PROPERTY(int      mPressureDpUnitIdx       READ getPressureDpUnitIdx       NOTIFY signalEventChangedPressureDpUnitIdx      )
    Q_PROPERTY(bool     mIsDrawCurrPos           READ getIsDrawCurrPos           NOTIFY signalEventChangedIsDrawCurrPos          )
    Q_PROPERTY(bool     mIsDrawTargetPos         READ getIsDrawTargetPos         NOTIFY signalEventChangedIsDrawTargetPos        )
    Q_PROPERTY(bool     mIsDrawCurrPressure      READ getIsDrawCurrPressure      NOTIFY signalEventChangedIsDrawCurrPressure     )
    Q_PROPERTY(bool     mIsDrawTargetPressure    READ getIsDrawTargetPressure    NOTIFY signalEventChangedIsDrawTargetPressure   )
    Q_PROPERTY(int      mPressureAxisMappingIdx  READ getPressureAxisMappingIdx  NOTIFY signalEventChangedPressureAxisMappingIdx )
    Q_PROPERTY(int      mPressureDecadesIdx      READ getPressureDecadesIdx      NOTIFY signalEventChangedPressureDecadesIdx     )
    Q_PROPERTY(bool     mIsAutoScalePos          READ getIsAutoScalePos          NOTIFY signalEventChangedIsAutoScalePos         )
    Q_PROPERTY(bool     mIsAutoScalePressure     READ getIsAutoScalePressure     NOTIFY signalEventChangedIsAutoScalePressure    )
    Q_PROPERTY(int      mChartMSecIdx            READ getChartMSecIdx            NOTIFY signalEventChangedChartMSecIdx           )
    Q_PROPERTY(int      mUserPressureFixedN      READ getUserPressureFixedN      NOTIFY signalEventChangedUserPressureFixedN     )
    Q_PROPERTY(double   mAutoScaleMinMargin      READ getAutoScaleMinMargin      NOTIFY signalEventChangedAutoScaleMinMargin     )
    Q_PROPERTY(bool     mErrPosResolution        READ getErrPosResolution        NOTIFY signalEventChangedErrPosResolution       )
    Q_PROPERTY(bool     mErrPressureDpUnit       READ getErrPressureDpUnit       NOTIFY signalEventChangedErrPressureDpUnit      )
    Q_PROPERTY(bool     mErrIsDrawCurrPos        READ getErrIsDrawCurrPos        NOTIFY signalEventChangedErrIsDrawCurrPos       )
    Q_PROPERTY(bool     mErrIsDrawTargetPos      READ getErrIsDrawTargetPos      NOTIFY signalEventChangedErrIsDrawTargetPos     )
    Q_PROPERTY(bool     mErrIsDrawCurrPressure   READ getErrIsDrawCurrPressure   NOTIFY signalEventChangedErrIsDrawCurrPressure  )
    Q_PROPERTY(bool     mErrIsDrawTargetPressure READ getErrIsDrawTargetPressure NOTIFY signalEventChangedErrIsDrawTargetPressure)
    Q_PROPERTY(bool     mErrPressureAxisMapping  READ getErrPressureAxisMapping  NOTIFY signalEventChangedErrPressureAxisMapping )
    Q_PROPERTY(bool     mErrPressureDecades      READ getErrPressureDecades      NOTIFY signalEventChangedErrPressureDecades     )
    Q_PROPERTY(bool     mErrChartMSec            READ getErrChartMSec            NOTIFY signalEventChangedErrChartMSec           )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                  NOTIFY signalEventChangedIsEdit                 )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus               NOTIFY signalEventChangedStrStatus              )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                  NOTIFY signalEventChangedErrMsg                 )
    Q_PROPERTY(QString  mErrMsg2                 READ getErrMsg2                 NOTIFY signalEventChangedErrMsg2                )
    Q_PROPERTY(int      mProgress                READ getProgress                NOTIFY signalEventChangedProgress               )

public:
    int     mAccessMode               = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test              = false;
    int     mPosResolutionIdx         = 1;
    int     mPressureDpUnitIdx        = ValveEnumDef::PRESSURE_UNIT_TORR;
    bool    mIsDrawCurrPos            = true;
    bool    mIsDrawTargetPos          = true;
    bool    mIsDrawCurrPressure       = true;
    bool    mIsDrawTargetPressure     = true;
    int     mPressureAxisMappingIdx   = ValveEnumDef::PRESSURE_AXIS_LINEAR;
    int     mPressureDecadesIdx       = 4;
    bool    mIsAutoScalePos           = false;
    bool    mIsAutoScalePressure      = false;
    int     mChartMSecIdx             = 0;
    int     mUserPressureFixedN       = 0;
    double  mAutoScaleMinMargin       = 0.1;
    bool    mErrPosResolution         = false;
    bool    mErrPressureDpUnit        = false;
    bool    mErrIsDrawCurrPos         = false;
    bool    mErrIsDrawTargetPos       = false;
    bool    mErrIsDrawCurrPressure    = false;
    bool    mErrIsDrawTargetPressure  = false;
    bool    mErrPressureAxisMapping   = false;
    bool    mErrPressureDecades       = false;
    bool    mErrChartMSec             = false;
    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    int     getPosResolutionIdx       (){ return mPosResolutionIdx       ;}
    int     getPressureDpUnitIdx      (){ return mPressureDpUnitIdx      ;}
    bool    getIsDrawCurrPos          (){ return mIsDrawCurrPos          ;}
    bool    getIsDrawTargetPos        (){ return mIsDrawTargetPos        ;}
    bool    getIsDrawCurrPressure     (){ return mIsDrawCurrPressure     ;}
    bool    getIsDrawTargetPressure   (){ return mIsDrawTargetPressure   ;}
    int     getPressureAxisMappingIdx (){ return mPressureAxisMappingIdx ;}
    int     getPressureDecadesIdx     (){ return mPressureDecadesIdx     ;}
    bool    getIsAutoScalePos         (){ return mIsAutoScalePos         ;}
    bool    getIsAutoScalePressure    (){ return mIsAutoScalePressure    ;}
    int     getChartMSecIdx           (){ return mChartMSecIdx           ;}
    int     getUserPressureFixedN     (){ return mUserPressureFixedN     ;}
    double  getAutoScaleMinMargin     (){ return mAutoScaleMinMargin     ;}
    bool    getErrPosResolution       (){ return mErrPosResolution       ;}
    bool    getErrPressureDpUnit      (){ return mErrPressureDpUnit      ;}
    bool    getErrIsDrawCurrPos       (){ return mErrIsDrawCurrPos       ;}
    bool    getErrIsDrawTargetPos     (){ return mErrIsDrawTargetPos     ;}
    bool    getErrIsDrawCurrPressure  (){ return mErrIsDrawCurrPressure  ;}
    bool    getErrIsDrawTargetPressure(){ return mErrIsDrawTargetPressure;}
    bool    getErrPressureAxisMapping (){ return mErrPressureAxisMapping ;}
    bool    getErrPressureDecades     (){ return mErrPressureDecades     ;}
    bool    getErrChartMSec           (){ return mErrChartMSec           ;}
    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test             (value);}
    void    setPosResolutionIdx       (int     value){ if(mPosResolutionIdx        == value)return; mPosResolutionIdx        = value; emit signalEventChangedPosResolutionIdx       (value);}
    void    setPressureDpUnitIdx      (int     value){ if(mPressureDpUnitIdx       == value)return; mPressureDpUnitIdx       = value; emit signalEventChangedPressureDpUnitIdx      (value);}
    void    setIsDrawCurrPos          (bool    value){ if(mIsDrawCurrPos           == value)return; mIsDrawCurrPos           = value; emit signalEventChangedIsDrawCurrPos          (value);}
    void    setIsDrawTargetPos        (bool    value){ if(mIsDrawTargetPos         == value)return; mIsDrawTargetPos         = value; emit signalEventChangedIsDrawTargetPos        (value);}
    void    setIsDrawCurrPressure     (bool    value){ if(mIsDrawCurrPressure      == value)return; mIsDrawCurrPressure      = value; emit signalEventChangedIsDrawCurrPressure     (value);}
    void    setIsDrawTargetPressure   (bool    value){ if(mIsDrawTargetPressure    == value)return; mIsDrawTargetPressure    = value; emit signalEventChangedIsDrawTargetPressure   (value);}
    void    setPressureAxisMappingIdx (int     value){ if(mPressureAxisMappingIdx  == value)return; mPressureAxisMappingIdx  = value; emit signalEventChangedPressureAxisMappingIdx (value);}
    void    setPressureDecadesIdx     (int     value){ if(mPressureDecadesIdx      == value)return; mPressureDecadesIdx      = value; emit signalEventChangedPressureDecadesIdx     (value);}
    void    setIsAutoScalePos         (bool    value){ if(mIsAutoScalePos          == value)return; mIsAutoScalePos          = value; emit signalEventChangedIsAutoScalePos         (value);}
    void    setIsAutoScalePressure    (bool    value){ if(mIsAutoScalePressure     == value)return; mIsAutoScalePressure     = value; emit signalEventChangedIsAutoScalePressure    (value);}
    void    setChartMSecIdx           (int     value){ if(mChartMSecIdx            == value)return; mChartMSecIdx            = value; emit signalEventChangedChartMSecIdx           (value);}
    void    setUserPressureFixedN     (int     value){ if(mUserPressureFixedN      == value)return; mUserPressureFixedN      = value; emit signalEventChangedUserPressureFixedN     (value);}
    void    setAutoScaleMinMargin     (double  value){ if(mAutoScaleMinMargin      == value)return; mAutoScaleMinMargin      = value; emit signalEventChangedAutoScaleMinMargin     (value);}
    void    setErrPosResolution       (bool    value){ if(mErrPosResolution        == value)return; mErrPosResolution        = value; emit signalEventChangedErrPosResolution       (value);}
    void    setErrPressureDpUnit      (bool    value){ if(mErrPressureDpUnit       == value)return; mErrPressureDpUnit       = value; emit signalEventChangedErrPressureDpUnit      (value);}
    void    setErrIsDrawCurrPos       (bool    value){ if(mErrIsDrawCurrPos        == value)return; mErrIsDrawCurrPos        = value; emit signalEventChangedErrIsDrawCurrPos       (value);}
    void    setErrIsDrawTargetPos     (bool    value){ if(mErrIsDrawTargetPos      == value)return; mErrIsDrawTargetPos      = value; emit signalEventChangedErrIsDrawTargetPos     (value);}
    void    setErrIsDrawCurrPressure  (bool    value){ if(mErrIsDrawCurrPressure   == value)return; mErrIsDrawCurrPressure   = value; emit signalEventChangedErrIsDrawCurrPressure  (value);}
    void    setErrIsDrawTargetPressure(bool    value){ if(mErrIsDrawTargetPressure == value)return; mErrIsDrawTargetPressure = value; emit signalEventChangedErrIsDrawTargetPressure(value);}
    void    setErrPressureAxisMapping (bool    value){ if(mErrPressureAxisMapping  == value)return; mErrPressureAxisMapping  = value; emit signalEventChangedErrPressureAxisMapping (value);}
    void    setErrPressureDecades     (bool    value){ if(mErrPressureDecades      == value)return; mErrPressureDecades      = value; emit signalEventChangedErrPressureDecades     (value);}
    void    setErrChartMSec           (bool    value){ if(mErrChartMSec            == value)return; mErrChartMSec            = value; emit signalEventChangedErrChartMSec           (value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedPosResolutionIdx       (int     value);
    void signalEventChangedPressureDpUnitIdx      (int     value);
    void signalEventChangedIsDrawCurrPos          (bool    value);
    void signalEventChangedIsDrawTargetPos        (bool    value);
    void signalEventChangedIsDrawCurrPressure     (bool    value);
    void signalEventChangedIsDrawTargetPressure   (bool    value);
    void signalEventChangedPressureAxisMappingIdx (int     value);
    void signalEventChangedPressureDecadesIdx     (int     value);
    void signalEventChangedIsAutoScalePos         (bool    value);
    void signalEventChangedIsAutoScalePressure    (bool    value);
    void signalEventChangedChartMSecIdx           (int     value);
    void signalEventChangedUserPressureFixedN     (int     value);
    void signalEventChangedAutoScaleMinMargin     (double  value);
    void signalEventChangedErrPosResolution       (bool    value);
    void signalEventChangedErrPressureDpUnit      (bool    value);
    void signalEventChangedErrIsDrawCurrPos       (bool    value);
    void signalEventChangedErrIsDrawTargetPos     (bool    value);
    void signalEventChangedErrIsDrawCurrPressure  (bool    value);
    void signalEventChangedErrIsDrawTargetPressure(bool    value);
    void signalEventChangedErrPressureAxisMapping (bool    value);
    void signalEventChangedErrPressureDecades     (bool    value);
    void signalEventChangedErrChartMSec           (bool    value);
    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );

public:
    explicit NCPASettingsDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_DP_CONFIG;
        ENABLE_SLOT_VALVE_WRITTEN_DP_CONFIG;

        setIsDrawCurrPos       (pLSettingSP->mIsDrawCurrPos       );
        setIsDrawTargetPos     (pLSettingSP->mIsDrawTargetPos     );
        setIsDrawCurrPressure  (pLSettingSP->mIsDrawCurrPressure  );
        setIsDrawTargetPressure(pLSettingSP->mIsDrawTargetPressure);
        setIsAutoScalePos      (pLSettingSP->mIsAutoScalePos      );
        setIsAutoScalePressure (pLSettingSP->mIsAutoScalePressure );
        setChartMSecIdx        (pLSettingSP->convertChartMSecValueToIdx(pLSettingSP->mChartMSec));
        setUserPressureFixedN  (pLSettingSP->mUserPressureFixedN  );
        setAutoScaleMinMargin  (pLSettingSP->mAutoScaleMinMargin  );

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ);
    }
    ~NCPASettingsDlgModel()
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

    void onValveReadedDisplayConfig(ValveResponseDisplayConfigDto dto)
    {
        if(mState != eState::STATE_READ || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosResolution       (dto.mPositionResolution  != mWritePosResolution         );
            setErrPressureDpUnit      (dto.mPressureDpUnit      != mWritePressureDpUnitIdx     );
            setErrPressureAxisMapping (dto.mPressureAxisMapping != mWritePressureAxisMappingIdx);
            setErrPressureDecades     (dto.mPressureDecades     != mWritePressureDecades       );

            onCommandSetEdit(getErrPosResolution() || getErrPressureDpUnit() || getErrPressureAxisMapping() || getErrPressureDecades());
        }
        else
        {
            setPosResolutionIdx      (pValveSP->convertPosResolutionValueToIdx(dto.mPositionResolution));
            setPressureDpUnitIdx     (dto.mPressureDpUnit                                              );
            setPressureAxisMappingIdx(dto.mPressureAxisMapping                                         );
            setPressureDecadesIdx    (pValveSP->convertPressureDecadesValueToIdx(dto.mPressureDecades) );
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int posResolutionIdx, int pressureDpUnitIdx, bool isDrawCurrPos, bool isDrawTargetPos, bool isDrawCurrPressure, bool isDrawTargetPressure, int pressureAxisMappingIdx, int pressureDecadesIdx, bool isAutoScalePos, bool isAutoScalePressure, int chartMSecIdx, int userPressurePrecision, double autoScaleMinMarginRatio)
    {
        mIsWritten       = true;

        pLSettingSP->setIsDrawCurrPos(isDrawCurrPos);
        pLSettingSP->setIsDrawTargetPos(isDrawTargetPos);
        pLSettingSP->setIsDrawCurrPressure(isDrawCurrPressure);
        pLSettingSP->setIsDrawTargetPressure(isDrawTargetPressure);
        pLSettingSP->setIsAutoScalePos(isAutoScalePos);
        pLSettingSP->setIsAutoScalePressure(isAutoScalePressure);
        pLSettingSP->setChartMSec(pLSettingSP->convertChartMSecIdxToValue(chartMSecIdx));
        pLSettingSP->setUserPressureFixedN(userPressurePrecision);
        pLSettingSP->setAutoScaleMinMargin(autoScaleMinMarginRatio);

        int posResolution = pValveSP->convertPosResolutionIdxToValue(posResolutionIdx);
        int pressureDecades = pValveSP->convertPressureDecadesIdxToValue(pressureDecadesIdx);

        mWritePosResolution          = posResolution;
        mWritePressureDpUnitIdx      = pressureDpUnitIdx;
        mWritePressureAxisMappingIdx = pressureAxisMappingIdx;
        mWritePressureDecades        = pressureDecades;
        setState(eState::STATE_WRITE);

        setErrMsg2("");
    }

    void onValveWrittenDisplayConfig(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg2(dto.mErrMsg);

        setState((eState)(mState + 1));
    }

private:
    enum eState{
        STATE_WRITE = 0,
        STATE_READ  = STATE_WRITE + 1,
        STATE_READY = STATE_READ  + 1,
    };

    QTimer mTimer;
    bool   mIsWritten     = false;
    eState mState         = eState::STATE_READ;

    int  mWritePosResolution          ;
    int  mWritePressureDpUnitIdx      ;
    int  mWritePressureAxisMappingIdx ;
    int  mWritePressureDecades        ;

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

        if(state == STATE_READ)
        {
            setStrStatus("Loading");
            setIsDrawCurrPos       (pLSettingSP->mIsDrawCurrPos       );
            setIsDrawTargetPos     (pLSettingSP->mIsDrawTargetPos     );
            setIsDrawCurrPressure  (pLSettingSP->mIsDrawCurrPressure  );
            setIsDrawTargetPressure(pLSettingSP->mIsDrawTargetPressure);
            setIsAutoScalePos      (pLSettingSP->mIsAutoScalePos      );
            setIsAutoScalePressure (pLSettingSP->mIsAutoScalePressure );
            setChartMSecIdx        (pLSettingSP->convertChartMSecValueToIdx(pLSettingSP->mChartMSec));
            setUserPressureFixedN  (pLSettingSP->mUserPressureFixedN  );
            setAutoScaleMinMargin  (pLSettingSP->mAutoScaleMinMargin  );
        }
        else if(state == eState::STATE_WRITE)
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

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ:
            pValveSP->readDisplayConfig(this);
            break;

        case (int)eState::STATE_WRITE:
            pValveSP->setDisplayConfig(mWritePosResolution, mWritePressureDpUnitIdx, mWritePressureAxisMappingIdx, mWritePressureDecades, this);
            break;
        }
    }

};
#endif // NCPASETTINGSDLGMODEL_H
