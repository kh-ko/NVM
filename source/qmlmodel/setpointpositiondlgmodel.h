#ifndef SETPOINTPOSITIONDLGMODEL_H
#define SETPOINTPOSITIONDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class SetPointPositionDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode        READ getAccessMode       NOTIFY signalEventChangedAccessMode      )
    Q_PROPERTY(bool     mIsRS232Test       READ getIsRS232Test      NOTIFY signalEventChangedIsRS232Test     )
    Q_PROPERTY(int      mPosResolution     READ getPosResolution    NOTIFY signalEventChangedPosResolution   )
    Q_PROPERTY(int      mPosition01        READ getPosition01       NOTIFY signalEventChangedPosition01      )
    Q_PROPERTY(int      mPosition02        READ getPosition02       NOTIFY signalEventChangedPosition02      )
    Q_PROPERTY(int      mPosition03        READ getPosition03       NOTIFY signalEventChangedPosition03      )
    Q_PROPERTY(int      mPosition04        READ getPosition04       NOTIFY signalEventChangedPosition04      )
    Q_PROPERTY(int      mPosition05        READ getPosition05       NOTIFY signalEventChangedPosition05      )
    Q_PROPERTY(int      mPosition06        READ getPosition06       NOTIFY signalEventChangedPosition06      )
    Q_PROPERTY(int      mPressure01        READ getPressure01       NOTIFY signalEventChangedPressure01      )
    Q_PROPERTY(int      mPressure02        READ getPressure02       NOTIFY signalEventChangedPressure02      )
    Q_PROPERTY(int      mPressure03        READ getPressure03       NOTIFY signalEventChangedPressure03      )
    Q_PROPERTY(int      mPressure04        READ getPressure04       NOTIFY signalEventChangedPressure04      )
    Q_PROPERTY(int      mPressure05        READ getPressure05       NOTIFY signalEventChangedPressure05      )
    Q_PROPERTY(int      mPressure06        READ getPressure06       NOTIFY signalEventChangedPressure06      )
    Q_PROPERTY(bool     mErrPosition01     READ getErrPosition01    NOTIFY signalEventChangedErrPosition01   )
    Q_PROPERTY(bool     mErrPosition02     READ getErrPosition02    NOTIFY signalEventChangedErrPosition02   )
    Q_PROPERTY(bool     mErrPosition03     READ getErrPosition03    NOTIFY signalEventChangedErrPosition03   )
    Q_PROPERTY(bool     mErrPosition04     READ getErrPosition04    NOTIFY signalEventChangedErrPosition04   )
    Q_PROPERTY(bool     mErrPosition05     READ getErrPosition05    NOTIFY signalEventChangedErrPosition05   )
    Q_PROPERTY(bool     mErrPosition06     READ getErrPosition06    NOTIFY signalEventChangedErrPosition06   )
    Q_PROPERTY(bool     mErrPressure01     READ getErrPressure01    NOTIFY signalEventChangedErrPressure01   )
    Q_PROPERTY(bool     mErrPressure02     READ getErrPressure02    NOTIFY signalEventChangedErrPressure02   )
    Q_PROPERTY(bool     mErrPressure03     READ getErrPressure03    NOTIFY signalEventChangedErrPressure03   )
    Q_PROPERTY(bool     mErrPressure04     READ getErrPressure04    NOTIFY signalEventChangedErrPressure04   )
    Q_PROPERTY(bool     mErrPressure05     READ getErrPressure05    NOTIFY signalEventChangedErrPressure05   )
    Q_PROPERTY(bool     mErrPressure06     READ getErrPressure06    NOTIFY signalEventChangedErrPressure06   )
    Q_PROPERTY(bool     mIsEdit            READ getIsEdit           NOTIFY signalEventChangedIsEdit          )
    Q_PROPERTY(QString  mStrStatus         READ getStrStatus        NOTIFY signalEventChangedStrStatus       )
    Q_PROPERTY(QString  mErrMsg            READ getErrMsg           NOTIFY signalEventChangedErrMsg          )
    Q_PROPERTY(QString  mErrMsg2           READ getErrMsg2          NOTIFY signalEventChangedErrMsg2         )
    Q_PROPERTY(int      mProgress          READ getProgress         NOTIFY signalEventChangedProgress        )

public:
    int     mAccessMode       = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test      = false;
    int     mPosResolution    = 10000;
    int     mPosition01       = 0;
    int     mPosition02       = 0;
    int     mPosition03       = 0;
    int     mPosition04       = 0;
    int     mPosition05       = 0;
    int     mPosition06       = 0;
    int     mPressure01       = 0;
    int     mPressure02       = 0;
    int     mPressure03       = 0;
    int     mPressure04       = 0;
    int     mPressure05       = 0;
    int     mPressure06       = 0;
    bool    mErrPosition01    = false;
    bool    mErrPosition02    = false;
    bool    mErrPosition03    = false;
    bool    mErrPosition04    = false;
    bool    mErrPosition05    = false;
    bool    mErrPosition06    = false;
    bool    mErrPressure01    = false;
    bool    mErrPressure02    = false;
    bool    mErrPressure03    = false;
    bool    mErrPressure04    = false;
    bool    mErrPressure05    = false;
    bool    mErrPressure06    = false;
    bool    mIsEdit           = false;
    QString mStrStatus        = "Loading";
    QString mErrMsg           = "";
    QString mErrMsg2          = "";
    int     mProgress         = 0 ;

    int     getAccessMode   (){ return mAccessMode   ;}
    bool    getIsRS232Test  (){ return mIsRS232Test  ;}
    int     getPosResolution(){ return mPosResolution;}
    int     getPosition01   (){ return mPosition01   ;}
    int     getPosition02   (){ return mPosition02   ;}
    int     getPosition03   (){ return mPosition03   ;}
    int     getPosition04   (){ return mPosition04   ;}
    int     getPosition05   (){ return mPosition05   ;}
    int     getPosition06   (){ return mPosition06   ;}
    int     getPressure01   (){ return mPressure01   ;}
    int     getPressure02   (){ return mPressure02   ;}
    int     getPressure03   (){ return mPressure03   ;}
    int     getPressure04   (){ return mPressure04   ;}
    int     getPressure05   (){ return mPressure05   ;}
    int     getPressure06   (){ return mPressure06   ;}
    bool    getErrPosition01(){ return mErrPosition01;}
    bool    getErrPosition02(){ return mErrPosition02;}
    bool    getErrPosition03(){ return mErrPosition03;}
    bool    getErrPosition04(){ return mErrPosition04;}
    bool    getErrPosition05(){ return mErrPosition05;}
    bool    getErrPosition06(){ return mErrPosition06;}
    bool    getErrPressure01(){ return mErrPressure01;}
    bool    getErrPressure02(){ return mErrPressure02;}
    bool    getErrPressure03(){ return mErrPressure03;}
    bool    getErrPressure04(){ return mErrPressure04;}
    bool    getErrPressure05(){ return mErrPressure05;}
    bool    getErrPressure06(){ return mErrPressure06;}
    bool    getIsEdit       (){ return mIsEdit       ;}
    QString getStrStatus    (){ return mStrStatus    ;}
    QString getErrMsg       (){ return mErrMsg       ;}
    QString getErrMsg2      (){ return mErrMsg2      ;}
    int     getProgress     (){ return mProgress     ;}

    void setAccessMode   (int     value){ if(mAccessMode    == value) return; mAccessMode    = value; emit signalEventChangedAccessMode   (value);}
    void setIsRS232Test  (bool    value){ if(mIsRS232Test   == value)return; mIsRS232Test    = value; emit signalEventChangedIsRS232Test  (value);}
    void setPosResolution(int     value){ if(mPosResolution == value) return; mPosResolution = value; emit signalEventChangedPosResolution(value);}
    void setPosition01   (int     value){ if(mPosition01    == value) return; mPosition01    = value; emit signalEventChangedPosition01   (value);}
    void setPosition02   (int     value){ if(mPosition02    == value) return; mPosition02    = value; emit signalEventChangedPosition02   (value);}
    void setPosition03   (int     value){ if(mPosition03    == value) return; mPosition03    = value; emit signalEventChangedPosition03   (value);}
    void setPosition04   (int     value){ if(mPosition04    == value) return; mPosition04    = value; emit signalEventChangedPosition04   (value);}
    void setPosition05   (int     value){ if(mPosition05    == value) return; mPosition05    = value; emit signalEventChangedPosition05   (value);}
    void setPosition06   (int     value){ if(mPosition06    == value) return; mPosition06    = value; emit signalEventChangedPosition06   (value);}
    void setPressure01   (int     value){ if(mPressure01    == value) return; mPressure01    = value; emit signalEventChangedPressure01   (value);}
    void setPressure02   (int     value){ if(mPressure02    == value) return; mPressure02    = value; emit signalEventChangedPressure02   (value);}
    void setPressure03   (int     value){ if(mPressure03    == value) return; mPressure03    = value; emit signalEventChangedPressure03   (value);}
    void setPressure04   (int     value){ if(mPressure04    == value) return; mPressure04    = value; emit signalEventChangedPressure04   (value);}
    void setPressure05   (int     value){ if(mPressure05    == value) return; mPressure05    = value; emit signalEventChangedPressure05   (value);}
    void setPressure06   (int     value){ if(mPressure06    == value) return; mPressure06    = value; emit signalEventChangedPressure06   (value);}
    void setErrPosition01(bool    value){ if(mErrPosition01 == value) return; mErrPosition01 = value; emit signalEventChangedErrPosition01(value);}
    void setErrPosition02(bool    value){ if(mErrPosition02 == value) return; mErrPosition02 = value; emit signalEventChangedErrPosition02(value);}
    void setErrPosition03(bool    value){ if(mErrPosition03 == value) return; mErrPosition03 = value; emit signalEventChangedErrPosition03(value);}
    void setErrPosition04(bool    value){ if(mErrPosition04 == value) return; mErrPosition04 = value; emit signalEventChangedErrPosition04(value);}
    void setErrPosition05(bool    value){ if(mErrPosition05 == value) return; mErrPosition05 = value; emit signalEventChangedErrPosition05(value);}
    void setErrPosition06(bool    value){ if(mErrPosition06 == value) return; mErrPosition06 = value; emit signalEventChangedErrPosition06(value);}
    void setErrPressure01(bool    value){ if(mErrPressure01 == value) return; mErrPressure01 = value; emit signalEventChangedErrPressure01(value);}
    void setErrPressure02(bool    value){ if(mErrPressure02 == value) return; mErrPressure02 = value; emit signalEventChangedErrPressure02(value);}
    void setErrPressure03(bool    value){ if(mErrPressure03 == value) return; mErrPressure03 = value; emit signalEventChangedErrPressure03(value);}
    void setErrPressure04(bool    value){ if(mErrPressure04 == value) return; mErrPressure04 = value; emit signalEventChangedErrPressure04(value);}
    void setErrPressure05(bool    value){ if(mErrPressure05 == value) return; mErrPressure05 = value; emit signalEventChangedErrPressure05(value);}
    void setErrPressure06(bool    value){ if(mErrPressure06 == value) return; mErrPressure06 = value; emit signalEventChangedErrPressure06(value);}
    void setIsEdit       (bool    value){ if(mIsEdit        == value) return; mIsEdit        = value; emit signalEventChangedIsEdit       (value);}
    void setStrStatus    (QString value){ if(mStrStatus     == value) return; mStrStatus     = value; emit signalEventChangedStrStatus    (value);}
    void setErrMsg       (QString value){ if(mErrMsg        == value) return; mErrMsg        = value; emit signalEventChangedErrMsg       (value);}
    void setErrMsg2      (QString value){ if(mErrMsg2       == value) return; mErrMsg2       = value; emit signalEventChangedErrMsg2      (value);}
    void setProgress     (int     value){ if(mProgress      == value) return; mProgress      = value; emit signalEventChangedProgress     (value);}

signals:
    void signalEventChangedAccessMode   (int     value);
    void signalEventChangedIsRS232Test  (bool    value);
    void signalEventChangedPosResolution(int     value);
    void signalEventChangedPosition01   (int     value);
    void signalEventChangedPosition02   (int     value);
    void signalEventChangedPosition03   (int     value);
    void signalEventChangedPosition04   (int     value);
    void signalEventChangedPosition05   (int     value);
    void signalEventChangedPosition06   (int     value);
    void signalEventChangedPressure01   (int     value);
    void signalEventChangedPressure02   (int     value);
    void signalEventChangedPressure03   (int     value);
    void signalEventChangedPressure04   (int     value);
    void signalEventChangedPressure05   (int     value);
    void signalEventChangedPressure06   (int     value);
    void signalEventChangedErrPosition01(bool    value);
    void signalEventChangedErrPosition02(bool    value);
    void signalEventChangedErrPosition03(bool    value);
    void signalEventChangedErrPosition04(bool    value);
    void signalEventChangedErrPosition05(bool    value);
    void signalEventChangedErrPosition06(bool    value);
    void signalEventChangedErrPressure01(bool    value);
    void signalEventChangedErrPressure02(bool    value);
    void signalEventChangedErrPressure03(bool    value);
    void signalEventChangedErrPressure04(bool    value);
    void signalEventChangedErrPressure05(bool    value);
    void signalEventChangedErrPressure06(bool    value);
    void signalEventChangedIsEdit       (bool    value);
    void signalEventChangedStrStatus    (QString value);
    void signalEventChangedErrMsg       (QString value);
    void signalEventChangedErrMsg2      (QString value);
    void signalEventChangedProgress     (int     value);


public:
    explicit SetPointPositionDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_CHANGED_POS_RESOLUTION;
        ENABLE_SLOT_VALVE_READED_SETPOINT_01;
        ENABLE_SLOT_VALVE_READED_SETPOINT_02;
        ENABLE_SLOT_VALVE_READED_SETPOINT_03;
        ENABLE_SLOT_VALVE_READED_SETPOINT_04;
        ENABLE_SLOT_VALVE_READED_SETPOINT_05;
        ENABLE_SLOT_VALVE_READED_SETPOINT_06;
        ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_01;
        ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_02;
        ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_03;
        ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_04;
        ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_05;
        ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_06;

        onValveChangedAccess();
        onValveChangedIsRS232Test();
        onValveChangedPositionResolution();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_POS_01);

    }
    ~SetPointPositionDlgModel()
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

    void onValveChangedPositionResolution()
    {
        setPosResolution(pValveSP->getPositionResolution());
    }
    void onValveReadedSetpoint01(ValveResponseSetPointDto dto)
    {
        if(mState != eState::STATE_READ_POS_01 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosition01(mWritePos01 != dto.mPosition);
            setErrPressure01(mWritePressure01 != dto.mPressure);
        }
        else
        {
            setPosition01(dto.mPosition);
            setPressure01(dto.mPressure);
        }

        setState((eState)(mState + 1));
    }
    void onValveReadedSetpoint02(ValveResponseSetPointDto dto)
    {
        if(mState != eState::STATE_READ_POS_02 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosition02(mWritePos02 != dto.mPosition);
            setErrPressure02(mWritePressure02 != dto.mPressure);
        }
        else
        {
            setPosition02(dto.mPosition);
            setPressure02(dto.mPressure);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedSetpoint03(ValveResponseSetPointDto dto)
    {
        if(mState != eState::STATE_READ_POS_03 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosition03(mWritePos03 != dto.mPosition);
            setErrPressure03(mWritePressure03 != dto.mPressure);
        }
        else
        {
            setPosition03(dto.mPosition);
            setPressure03(dto.mPressure);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedSetpoint04(ValveResponseSetPointDto dto)
    {
        if(mState != eState::STATE_READ_POS_04 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosition04(mWritePos04 != dto.mPosition);
            setErrPressure04(mWritePressure04 != dto.mPressure);
        }
        else
        {
            setPosition04(dto.mPosition);
            setPressure04(dto.mPressure);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedSetpoint05(ValveResponseSetPointDto dto)
    {
        if(mState != eState::STATE_READ_POS_05 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosition05(mWritePos05 != dto.mPosition);
            setErrPressure05(mWritePressure05 != dto.mPressure);
        }
        else
        {
            setPosition05(dto.mPosition);
            setPressure05(dto.mPressure);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedSetpoint06(ValveResponseSetPointDto dto)
    {
        if(mState != eState::STATE_READ_POS_06 || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosition06(mWritePos06 != dto.mPosition);
            setErrPressure06(mWritePressure06 != dto.mPressure);

            setIsEdit(getErrPosition01() || getErrPosition02() || getErrPosition03() || getErrPosition04() || getErrPosition05() || getErrPosition06()
                      || getErrPressure01() || getErrPressure02() || getErrPressure03() || getErrPressure04() || getErrPressure05() || getErrPressure06());
        }
        else
        {
            setPosition06(dto.mPosition);
            setPressure06(dto.mPressure);
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        if((mState >= STATE_READ_POS_01 && mState <= STATE_READ_POS_06) && value)
            return;

        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int pos01, int pos02, int pos03, int pos04, int pos05, int pos06, int pressure01, int pressure02, int pressure03, int pressure04, int pressure05, int pressure06)
    {
        mIsWritten  = true;
        mWritePos01 = pos01;
        mWritePos02 = pos02;
        mWritePos03 = pos03;
        mWritePos04 = pos04;
        mWritePos05 = pos05;
        mWritePos06 = pos06;
        mWritePressure01 = pressure01;
        mWritePressure02 = pressure02;
        mWritePressure03 = pressure03;
        mWritePressure04 = pressure04;
        mWritePressure05 = pressure05;
        mWritePressure06 = pressure06;

        setErrMsg2("");
        setState(eState::STATE_WRITE_POS_01);
    }

    void onValveWrittenSetPoint01(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_POS_01 || dto.mReqDto.mpRef != this)
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
    void onValveWrittenSetPoint02(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_POS_02 || dto.mReqDto.mpRef != this)
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
    void onValveWrittenSetPoint03(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_POS_03 || dto.mReqDto.mpRef != this)
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
    void onValveWrittenSetPoint04(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_POS_04 || dto.mReqDto.mpRef != this)
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
    void onValveWrittenSetPoint05(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_POS_05 || dto.mReqDto.mpRef != this)
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
    void onValveWrittenSetPoint06(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_POS_06 || dto.mReqDto.mpRef != this)
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
        STATE_WRITE_POS_01 = 0,
        STATE_WRITE_POS_02 = STATE_WRITE_POS_01 + 1,
        STATE_WRITE_POS_03 = STATE_WRITE_POS_02 + 1,
        STATE_WRITE_POS_04 = STATE_WRITE_POS_03 + 1,
        STATE_WRITE_POS_05 = STATE_WRITE_POS_04 + 1,
        STATE_WRITE_POS_06 = STATE_WRITE_POS_05 + 1,
        STATE_READ_POS_01  = STATE_WRITE_POS_06 + 1,
        STATE_READ_POS_02  = STATE_READ_POS_01  + 1,
        STATE_READ_POS_03  = STATE_READ_POS_02  + 1,
        STATE_READ_POS_04  = STATE_READ_POS_03  + 1,
        STATE_READ_POS_05  = STATE_READ_POS_04  + 1,
        STATE_READ_POS_06  = STATE_READ_POS_05  + 1,
        STATE_READY        = STATE_READ_POS_06  + 1,
    };

    QTimer mTimer;
    eState mState   = eState::STATE_READ_POS_01;

    bool mIsWritten = false;
    int mWritePos01 = -1;
    int mWritePos02 = -1;
    int mWritePos03 = -1;
    int mWritePos04 = -1;
    int mWritePos05 = -1;
    int mWritePos06 = -1;
    int mWritePressure01 = -1;
    int mWritePressure02 = -1;
    int mWritePressure03 = -1;
    int mWritePressure04 = -1;
    int mWritePressure05 = -1;
    int mWritePressure06 = -1;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        if(!mIsWritten && state == eState::STATE_READY)
        {
            //emit signalEventCompletedLoad();
        }

        mState = state;

        if(state < (int) eState::STATE_READY && state >= (int) eState::STATE_READ_POS_01)
        {
            setStrStatus("loading");
        }
        else if(state < (int) eState::STATE_READ_POS_01 && state >= (int) eState::STATE_WRITE_POS_01)
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
        case (int)eState::STATE_READ_POS_01: pValveSP->readSetPoint01(this); break;
        case (int)eState::STATE_READ_POS_02: pValveSP->readSetPoint02(this); break;
        case (int)eState::STATE_READ_POS_03: pValveSP->readSetPoint03(this); break;
        case (int)eState::STATE_READ_POS_04: pValveSP->readSetPoint04(this); break;
        case (int)eState::STATE_READ_POS_05: pValveSP->readSetPoint05(this); break;
        case (int)eState::STATE_READ_POS_06: pValveSP->readSetPoint06(this); break;

        case (int)eState::STATE_WRITE_POS_01: pValveSP->setSetPoint01(mWritePos01, mWritePressure01, this); break;
        case (int)eState::STATE_WRITE_POS_02: pValveSP->setSetPoint02(mWritePos02, mWritePressure02, this); break;
        case (int)eState::STATE_WRITE_POS_03: pValveSP->setSetPoint03(mWritePos03, mWritePressure03, this); break;
        case (int)eState::STATE_WRITE_POS_04: pValveSP->setSetPoint04(mWritePos04, mWritePressure04, this); break;
        case (int)eState::STATE_WRITE_POS_05: pValveSP->setSetPoint05(mWritePos05, mWritePressure05, this); break;
        case (int)eState::STATE_WRITE_POS_06: pValveSP->setSetPoint06(mWritePos06, mWritePressure06, this); break;
        }
    }
};
#endif // SETPOINTPOSITIONDLGMODEL_H
