#ifndef PRESSURECTRLGAINMONITORDLGMODEL_H
#define PRESSURECTRLGAINMONITORDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class PressureCtrlGainMonitorDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mPresController READ getPresController NOTIFY signalEventChangedPresController )
    Q_PROPERTY(double   mAdapGainFac    READ getAdapGainFac    NOTIFY signalEventChangedAdapGainFac    )
    Q_PROPERTY(double   mAdapDeltaFac   READ getAdapDeltaFac   NOTIFY signalEventChangedAdapDeltaFac   )
    Q_PROPERTY(double   mFixedPGain     READ getFixedPGain     NOTIFY signalEventChangedFixedPGain     )
    Q_PROPERTY(double   mFixedIGain     READ getFixedIGain     NOTIFY signalEventChangedFixedIGain     )
    Q_PROPERTY(QString  mStrStatus      READ getStrStatus      NOTIFY signalEventChangedStrStatus      )
    Q_PROPERTY(QString  mErrMsg         READ getErrMsg         NOTIFY signalEventChangedErrMsg         )
    Q_PROPERTY(QString  mErrMsg2        READ getErrMsg2        NOTIFY signalEventChangedErrMsg2        )

public:
    int     mPresController = 0;
    double  mAdapGainFac    = 0;
    double  mAdapDeltaFac   = 0;
    double  mFixedPGain     = 0;
    double  mFixedIGain     = 0;
    QString mStrStatus      = "Loading";
    QString mErrMsg         = "";
    QString mErrMsg2        = "";

    int     getPresController(){ return mPresController; }
    double  getAdapGainFac   (){ return mAdapGainFac   ; }
    double  getAdapDeltaFac  (){ return mAdapDeltaFac  ; }
    double  getFixedPGain    (){ return mFixedPGain    ; }
    double  getFixedIGain    (){ return mFixedIGain    ; }
    QString getStrStatus     (){ return mStrStatus     ; }
    QString getErrMsg        (){ return mErrMsg        ; }
    QString getErrMsg2       (){ return mErrMsg2       ; }

    void setPresController(int     value){ if(mPresController == value) return; mPresController = value; emit signalEventChangedPresController(value); }
    void setAdapGainFac   (double  value){ if(mAdapGainFac    == value) return; mAdapGainFac    = value; emit signalEventChangedAdapGainFac   (value); }
    void setAdapDeltaFac  (double  value){ if(mAdapDeltaFac   == value) return; mAdapDeltaFac   = value; emit signalEventChangedAdapDeltaFac  (value); }
    void setFixedPGain    (double  value){ if(mFixedPGain     == value) return; mFixedPGain     = value; emit signalEventChangedFixedPGain    (value); }
    void setFixedIGain    (double  value){ if(mFixedIGain     == value) return; mFixedIGain     = value; emit signalEventChangedFixedIGain    (value); }
    void setStrStatus     (QString value){ if(mStrStatus      == value) return; mStrStatus      = value; emit signalEventChangedStrStatus     (value); }
    void setErrMsg        (QString value){ if(mErrMsg         == value) return; mErrMsg         = value; emit signalEventChangedErrMsg        (value); }
    void setErrMsg2       (QString value){ if(mErrMsg2        == value) return; mErrMsg2        = value; emit signalEventChangedErrMsg2       (value); }

signals:
    void signalEventChangedPresController(int     value);
    void signalEventChangedAdapGainFac   (double  value);
    void signalEventChangedAdapDeltaFac  (double  value);
    void signalEventChangedFixedPGain    (double  value);
    void signalEventChangedFixedIGain    (double  value);
    void signalEventChangedStrStatus     (QString value);
    void signalEventChangedErrMsg        (QString value);
    void signalEventChangedErrMsg2       (QString value);

public:
    explicit PressureCtrlGainMonitorDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        // todo signal connect
        ENABLE_SLOT_VALVE_CHANGED_PRESSURE_CTRL_MODE;
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;

        onValveChangedPressureCtrlMode();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        if(mPresController == ValveEnumDef::PRESSURE_CTRL_ADAPTIVE)
            setState(eState::STATE_READ_ADAP_GAIN_FAC);
        else if(mPresController == ValveEnumDef::PRESSURE_CTRL_FIXED_DOWN)
            setState(eState::STATE_READ_FIXED_01_P_GAIN);
        else if(mPresController == ValveEnumDef::PRESSURE_CTRL_FIXED_UP)
            setState(eState::STATE_READ_FIXED_02_P_GAIN);


        startTimer();
    }
    ~PressureCtrlGainMonitorDlgModel()
    {
    }

public slots:
    void onValveChangedPressureCtrlMode()
    {
        setPresController( pValveSP->getPressureCtrlMode() );
    }

    void onValveWrittenCustomRequest(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(dto.mIsSucc == false && dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(mState == eState::STATE_READ_ADAP_GAIN_FAC)
        {
            if(dto.mIsSucc == true && dto.mResData.startsWith("p:000B0711020300"))
            {
                double value = dto.mResData.mid(QString("p:000B071102030").length()).trimmed().toDouble();
                setAdapGainFac(value);
            }
            setState(eState::STATE_READ_ADAP_DELTA_FAC);
        }
        else if(mState == eState::STATE_READ_ADAP_DELTA_FAC)
        {
            if(dto.mIsSucc == true && dto.mResData.startsWith("p:000B0711020700"))
            {
                double value = dto.mResData.mid(QString("p:000B0711020700").length()).trimmed().toDouble();
                setAdapDeltaFac(value);
            }
            setState(eState::STATE_OVER);
        }
        else if(mState == eState::STATE_READ_FIXED_01_P_GAIN)
        {
            if(dto.mIsSucc == true && dto.mResData.startsWith("p:000B0712020100"))
            {
                double value = dto.mResData.mid(QString("p:000B0712020100").length()).trimmed().toDouble();
                setFixedPGain(value);
            }
            setState(eState::STATE_READ_FIXED_01_I_GAIN);
        }
        else if(mState == eState::STATE_READ_FIXED_01_I_GAIN)
        {
            if(dto.mIsSucc == true && dto.mResData.startsWith("p:000B0712020200"))
            {
                double value = dto.mResData.mid(QString("p:000B0712020200").length()).trimmed().toDouble();
                setFixedIGain(value);
            }
            setState(eState::STATE_OVER);
        }
        else if(mState == eState::STATE_READ_FIXED_02_P_GAIN)
        {
            if(dto.mIsSucc == true && dto.mResData.startsWith("p:000B0713020100"))
            {
                double value = dto.mResData.mid(QString("p:000B0713020100").length()).trimmed().toDouble();
                setFixedPGain(value);
            }
            setState(eState::STATE_READ_FIXED_02_I_GAIN);
        }
        else if(mState == eState::STATE_READ_FIXED_02_I_GAIN)
        {
            if(dto.mIsSucc == true && dto.mResData.startsWith("p:000B0713020200"))
            {
                double value = dto.mResData.mid(QString("p:000B0713020200").length()).trimmed().toDouble();
                setFixedIGain(value);
            }
            setState(eState::STATE_OVER);
        }
        return;
    }

private:
    enum eState{
        STATE_READ_ADAP_GAIN_FAC    = 0,
        STATE_READ_ADAP_DELTA_FAC   = STATE_READ_ADAP_GAIN_FAC   + 1,
        STATE_READ_FIXED_01_P_GAIN  = STATE_READ_ADAP_DELTA_FAC  + 1,
        STATE_READ_FIXED_01_I_GAIN  = STATE_READ_FIXED_01_P_GAIN + 1,
        STATE_READ_FIXED_02_P_GAIN  = STATE_READ_FIXED_01_I_GAIN + 1,
        STATE_READ_FIXED_02_I_GAIN  = STATE_READ_FIXED_02_P_GAIN + 1,
        STATE_OVER                  = STATE_READ_FIXED_02_I_GAIN + 1
    };

    QTimer mTimer;
    bool   mIsFirstRead   = true;
    eState mState         = eState::STATE_READ_ADAP_GAIN_FAC;
    qint64 mLastScanMSec  = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        qint64 currMSec;

        if(state == eState::STATE_OVER)
        {
            if(mPresController == ValveEnumDef::PRESSURE_CTRL_ADAPTIVE)
            {
                state = eState::STATE_READ_ADAP_GAIN_FAC;
            }
            else if(mPresController == ValveEnumDef::PRESSURE_CTRL_FIXED_DOWN)
            {
                state = eState::STATE_READ_FIXED_01_P_GAIN;
            }
            else if(mPresController == ValveEnumDef::PRESSURE_CTRL_FIXED_UP)
            {
                state = eState::STATE_READ_FIXED_02_P_GAIN;
            }
            mIsFirstRead = false;

            currMSec = QDateTime::currentMSecsSinceEpoch();
            setStrStatus(QString("scan-rate %1 ms").arg(currMSec - mLastScanMSec));
            mLastScanMSec = currMSec;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
        }

        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case eState::STATE_READ_ADAP_GAIN_FAC   : pValveSP->customRequest("p:0B0711020300", this); break;
        case eState::STATE_READ_ADAP_DELTA_FAC  : pValveSP->customRequest("p:0B0711020700", this); break;
        case eState::STATE_READ_FIXED_01_P_GAIN : pValveSP->customRequest("p:0B0712020100", this); break;
        case eState::STATE_READ_FIXED_01_I_GAIN : pValveSP->customRequest("p:0B0712020200", this); break;
        case eState::STATE_READ_FIXED_02_P_GAIN : pValveSP->customRequest("p:0B0713020100", this); break;
        case eState::STATE_READ_FIXED_02_I_GAIN : pValveSP->customRequest("p:0B0713020200", this); break;
        }
    }
};

#endif // PRESSURECTRLGAINMONITORDLGMODEL_H
