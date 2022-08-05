#ifndef VALVECARIBRATIONDLGMODEL_H
#define VALVECARIBRATIONDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ValveCariblationDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode               NOTIFY signalEventChangedAccessMode              )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test              NOTIFY signalEventChangedIsRS232Test             )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                   NOTIFY signalEventChangedIsEdit                  )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus                NOTIFY signalEventChangedStrStatus               )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                   NOTIFY signalEventChangedErrMsg                  )
    Q_PROPERTY(int      mProgress                READ getProgress                 NOTIFY signalEventChangedProgress                )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test             = false;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "ready";
    QString mErrMsg                  = "";
    int     mProgress                = 100 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    int     getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedIsEdit                 (int     value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventResult                        (bool isSucc, QString errMsg);

public:
    explicit ValveCariblationDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_WRITTEN_ADC_GAINZERO;
        ENABLE_SLOT_VALVE_WRITTEN_SENSOR_ZERO;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READY);
    }
    ~ValveCariblationDlgModel()
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

    Q_INVOKABLE void onCommandGainCalibration()
    {
        setState(eState::STATE_WRITE_GAIN);
    }

    void onValveWrittenAdcGainZero(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_GAIN || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg(dto.mErrMsg);

        emit signalEventResult(dto.mIsSucc, dto.mErrMsg);

        setState(STATE_READY);
    }

    Q_INVOKABLE void onCommandZeroCalibration()
    {
        setState(eState::STATE_WRITE_ZERO);
    }

    void onValveWrittenSensorZero(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_ZERO || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg(dto.mErrMsg);

        emit signalEventResult(dto.mIsSucc, dto.mErrMsg);

        setState(STATE_READY);
    }

private:
    enum eState{
        STATE_WRITE_ZERO            =  0,
        STATE_WRITE_GAIN            =  STATE_WRITE_ZERO + 1,
        STATE_READY                 =  STATE_WRITE_GAIN + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READY;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        mState = state;

        if(state == eState::STATE_READY)
        {
            setProgress(100);
            setStrStatus("ready");
        }
        else
        {
            setStrStatus("writting");
            setProgress(qFloor((state * 100) / eState::STATE_READY));
            startTimer();
        }
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_WRITE_GAIN:
            pValveSP->setAdcGainZero(this);
            break;

        case (int)eState::STATE_WRITE_ZERO:
            pValveSP->setSensorZero(this);
            break;
        }
    }
};
#endif // VALVECARIBRATIONDLGMODEL_H
