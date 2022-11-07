#ifndef INTERFACESETUPRS232DLGMODEL_H
#define INTERFACESETUPRS232DLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class InterfaceSetupRS232DlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode         )
    Q_PROPERTY(int      mInterface           READ getInterface           NOTIFY signalEventChangedInterface          )
    Q_PROPERTY(bool     mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test        )

    Q_PROPERTY(int      mBaudrateIdx         READ getBaudrateIdx         NOTIFY signalEventChangedBaudrateIdx        )
    Q_PROPERTY(int      mParityIdx           READ getParityIdx           NOTIFY signalEventChangedParityIdx          )
    Q_PROPERTY(int      mDataLenIdx          READ getDataLenIdx          NOTIFY signalEventChangedDataLenIdx         )
    Q_PROPERTY(int      mStopBitIdx          READ getStopBitIdx          NOTIFY signalEventChangedStopBitIdx         )
    Q_PROPERTY(int      mOperationModeIdx    READ getOperationModeIdx    NOTIFY signalEventChangedOperationModeIdx   )
    Q_PROPERTY(int      mDuplexModeIdx       READ getDuplexModeIdx       NOTIFY signalEventChangedDuplexModeIdx      )
    Q_PROPERTY(int      mDevAddr             READ getDevAddr             NOTIFY signalEventChangedDevAddr            )
    Q_PROPERTY(int      mTerminationIdx      READ getTerminationIdx      NOTIFY signalEventChangedTerminationIdx     )
    Q_PROPERTY(int      mPosRangeIdx         READ getPosRangeIdx         NOTIFY signalEventChangedPosRangeIdx        )
    Q_PROPERTY(int      mPressureRange       READ getPressureRange       NOTIFY signalEventChangedPressureRange      )
    Q_PROPERTY(int      mCommandSetIdx       READ getCommandSetIdx       NOTIFY signalEventChangedCommandSetIdx      )
    Q_PROPERTY(int      mSecondAnswerIdx     READ getSecondAnswerIdx     NOTIFY signalEventChangedSecondAnswerIdx    )
    Q_PROPERTY(int      mDIOpenValveIdx      READ getDIOpenValveIdx      NOTIFY signalEventChangedDIOpenValveIdx     )
    Q_PROPERTY(int      mDICloseValveIdx     READ getDICloseValveIdx     NOTIFY signalEventChangedDICloseValveIdx    )
    Q_PROPERTY(bool     mErrBaudrateIdx      READ getErrBaudrateIdx      NOTIFY signalEventChangedErrBaudrateIdx     )
    Q_PROPERTY(bool     mErrParityIdx        READ getErrParityIdx        NOTIFY signalEventChangedErrParityIdx       )
    Q_PROPERTY(bool     mErrDataLenIdx       READ getErrDataLenIdx       NOTIFY signalEventChangedErrDataLenIdx      )
    Q_PROPERTY(bool     mErrStopBitIdx       READ getErrStopBitIdx       NOTIFY signalEventChangedErrStopBitIdx      )
    Q_PROPERTY(bool     mErrOperationModeIdx READ getErrOperationModeIdx NOTIFY signalEventChangedErrOperationModeIdx)
    Q_PROPERTY(bool     mErrDuplexModeIdx    READ getErrDuplexModeIdx    NOTIFY signalEventChangedErrDuplexModeIdx   )
    Q_PROPERTY(bool     mErrDevAddr          READ getErrDevAddr          NOTIFY signalEventChangedErrDevAddr         )
    Q_PROPERTY(bool     mErrTerminationIdx   READ getErrTerminationIdx   NOTIFY signalEventChangedErrTerminationIdx  )
    Q_PROPERTY(bool     mErrPosRangeIdx      READ getErrPosRangeIdx      NOTIFY signalEventChangedErrPosRangeIdx     )
    Q_PROPERTY(bool     mErrPressureRange    READ getErrPressureRange    NOTIFY signalEventChangedErrPressureRange   )
    Q_PROPERTY(bool     mErrCommandSetIdx    READ getErrCommandSetIdx    NOTIFY signalEventChangedErrCommandSetIdx   )
    Q_PROPERTY(bool     mErrSecondAnswerIdx  READ getErrSecondAnswerIdx  NOTIFY signalEventChangedErrSecondAnswerIdx )
    Q_PROPERTY(bool     mErrDIOpenValveIdx   READ getErrDIOpenValveIdx   NOTIFY signalEventChangedErrDIOpenValveIdx  )
    Q_PROPERTY(bool     mErrDICloseValveIdx  READ getErrDICloseValveIdx  NOTIFY signalEventChangedErrDICloseValveIdx )
    Q_PROPERTY(bool     mIsEdit              READ getIsEdit              NOTIFY signalEventChangedIsEdit             )
    Q_PROPERTY(QString  mStrStatus           READ getStrStatus           NOTIFY signalEventChangedStrStatus          )
    Q_PROPERTY(QString  mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg             )
    Q_PROPERTY(QString  mErrMsg2             READ getErrMsg2             NOTIFY signalEventChangedErrMsg2            )
    Q_PROPERTY(int      mProgress            READ getProgress            NOTIFY signalEventChangedProgress           )

public:
    int     mAccessMode          = ValveEnumDef::ACCESS_LOCAL;
    int     mInterface           = ValveEnumDef::INTERFACE_RS232_WITH_ANALOGOUTPUT;
    bool    mIsRS232Test         = false;

    int     mBaudrateIdx         = 0;
    int     mParityIdx           = 0;
    int     mDataLenIdx          = 0;
    int     mStopBitIdx          = 0;
    int     mOperationModeIdx    = 0;
    int     mDuplexModeIdx       = 0;
    int     mDevAddr             = 0;
    int     mTerminationIdx      = 0;
    int     mPosRangeIdx         = 0;
    int     mPressureRange       = 0;
    int     mCommandSetIdx       = 0;
    int     mSecondAnswerIdx     = 0;
    int     mDIOpenValveIdx      = 0;
    int     mDICloseValveIdx     = 0;
    bool    mErrBaudrateIdx      = false;
    bool    mErrParityIdx        = false;
    bool    mErrDataLenIdx       = false;
    bool    mErrStopBitIdx       = false;
    bool    mErrOperationModeIdx = false;
    bool    mErrDuplexModeIdx    = false;
    bool    mErrDevAddr          = false;
    bool    mErrTerminationIdx   = false;
    bool    mErrPosRangeIdx      = false;
    bool    mErrPressureRange    = false;
    bool    mErrCommandSetIdx    = false;
    bool    mErrSecondAnswerIdx  = false;
    bool    mErrDIOpenValveIdx   = false;
    bool    mErrDICloseValveIdx  = false;

    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    int     getInterface              (){ return mInterface              ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}

    int     getBaudrateIdx            (){ return mBaudrateIdx            ;}
    int     getParityIdx              (){ return mParityIdx              ;}
    int     getDataLenIdx             (){ return mDataLenIdx             ;}
    int     getStopBitIdx             (){ return mStopBitIdx             ;}
    int     getOperationModeIdx       (){ return mOperationModeIdx       ;}
    int     getDuplexModeIdx          (){ return mDuplexModeIdx          ;}
    int     getDevAddr                (){ return mDevAddr                ;}
    int     getTerminationIdx         (){ return mTerminationIdx         ;}
    int     getPosRangeIdx            (){ return mPosRangeIdx            ;}
    int     getPressureRange          (){ return mPressureRange          ;}
    int     getCommandSetIdx          (){ return mCommandSetIdx          ;}
    int     getSecondAnswerIdx        (){ return mSecondAnswerIdx        ;}
    int     getDIOpenValveIdx         (){ return mDIOpenValveIdx         ;}
    int     getDICloseValveIdx        (){ return mDICloseValveIdx        ;}
    bool    getErrBaudrateIdx         (){ return mErrBaudrateIdx         ;}
    bool    getErrParityIdx           (){ return mErrParityIdx           ;}
    bool    getErrDataLenIdx          (){ return mErrDataLenIdx          ;}
    bool    getErrStopBitIdx          (){ return mErrStopBitIdx          ;}
    bool    getErrOperationModeIdx    (){ return mErrOperationModeIdx    ;}
    bool    getErrDuplexModeIdx       (){ return mErrDuplexModeIdx       ;}
    bool    getErrDevAddr             (){ return mErrDevAddr             ;}
    bool    getErrTerminationIdx      (){ return mErrTerminationIdx      ;}
    bool    getErrPosRangeIdx         (){ return mErrPosRangeIdx         ;}
    bool    getErrPressureRange       (){ return mErrPressureRange       ;}
    bool    getErrCommandSetIdx       (){ return mErrCommandSetIdx       ;}
    bool    getErrSecondAnswerIdx     (){ return mErrSecondAnswerIdx     ;}
    bool    getErrDIOpenValveIdx      (){ return mErrDIOpenValveIdx      ;}
    bool    getErrDICloseValveIdx     (){ return mErrDICloseValveIdx     ;}

    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode          == value)return; mAccessMode          = value; emit signalEventChangedAccessMode         (value);}
    void    setInterface              (int     value){ if(mInterface           == value)return; mInterface           = value; emit signalEventChangedInterface          (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test         == value)return; mIsRS232Test         = value; emit signalEventChangedIsRS232Test        (value);}

    void    setBaudrateIdx            (int     value){ if(mBaudrateIdx         == value)return; mBaudrateIdx         = value; emit signalEventChangedBaudrateIdx        (value);}
    void    setParityIdx              (int     value){ if(mParityIdx           == value)return; mParityIdx           = value; emit signalEventChangedParityIdx          (value);}
    void    setDataLenIdx             (int     value){ if(mDataLenIdx          == value)return; mDataLenIdx          = value; emit signalEventChangedDataLenIdx         (value);}
    void    setStopBitIdx             (int     value){ if(mStopBitIdx          == value)return; mStopBitIdx          = value; emit signalEventChangedStopBitIdx         (value);}
    void    setOperationModeIdx       (int     value){ if(mOperationModeIdx    == value)return; mOperationModeIdx    = value; emit signalEventChangedOperationModeIdx   (value);}
    void    setDuplexModeIdx          (int     value){ if(mDuplexModeIdx       == value)return; mDuplexModeIdx       = value; emit signalEventChangedDuplexModeIdx      (value);}
    void    setDevAddr                (int     value){ if(mDevAddr             == value)return; mDevAddr             = value; emit signalEventChangedDevAddr            (value);}
    void    setTerminationIdx         (int     value){ if(mTerminationIdx      == value)return; mTerminationIdx      = value; emit signalEventChangedTerminationIdx     (value);}
    void    setPosRangeIdx            (int     value){ if(mPosRangeIdx         == value)return; mPosRangeIdx         = value; emit signalEventChangedPosRangeIdx        (value);}
    void    setPressureRange          (int     value){ if(mPressureRange       == value)return; mPressureRange       = value; emit signalEventChangedPressureRange      (value);}
    void    setCommandSetIdx          (int     value){ if(mCommandSetIdx       == value)return; mCommandSetIdx       = value; emit signalEventChangedCommandSetIdx      (value);}
    void    setSecondAnswerIdx        (int     value){ if(mSecondAnswerIdx     == value)return; mSecondAnswerIdx     = value; emit signalEventChangedSecondAnswerIdx    (value);}
    void    setDIOpenValveIdx         (int     value){ if(mDIOpenValveIdx      == value)return; mDIOpenValveIdx      = value; emit signalEventChangedDIOpenValveIdx     (value);}
    void    setDICloseValveIdx        (int     value){ if(mDICloseValveIdx     == value)return; mDICloseValveIdx     = value; emit signalEventChangedDICloseValveIdx    (value);}
    void    setErrBaudrateIdx         (bool    value){ if(mErrBaudrateIdx      == value)return; mErrBaudrateIdx      = value; emit signalEventChangedErrBaudrateIdx     (value);}
    void    setErrParityIdx           (bool    value){ if(mErrParityIdx        == value)return; mErrParityIdx        = value; emit signalEventChangedErrParityIdx       (value);}
    void    setErrDataLenIdx          (bool    value){ if(mErrDataLenIdx       == value)return; mErrDataLenIdx       = value; emit signalEventChangedErrDataLenIdx      (value);}
    void    setErrStopBitIdx          (bool    value){ if(mErrStopBitIdx       == value)return; mErrStopBitIdx       = value; emit signalEventChangedErrStopBitIdx      (value);}
    void    setErrOperationModeIdx    (bool    value){ if(mErrOperationModeIdx == value)return; mErrOperationModeIdx = value; emit signalEventChangedErrOperationModeIdx(value);}
    void    setErrDuplexModeIdx       (bool    value){ if(mErrDuplexModeIdx    == value)return; mErrDuplexModeIdx    = value; emit signalEventChangedErrDuplexModeIdx   (value);}
    void    setErrDevAddr             (bool    value){ if(mErrDevAddr          == value)return; mErrDevAddr          = value; emit signalEventChangedErrDevAddr         (value);}
    void    setErrTerminationIdx      (bool    value){ if(mErrTerminationIdx   == value)return; mErrTerminationIdx   = value; emit signalEventChangedErrTerminationIdx  (value);}
    void    setErrPosRangeIdx         (bool    value){ if(mErrPosRangeIdx      == value)return; mErrPosRangeIdx      = value; emit signalEventChangedErrPosRangeIdx     (value);}
    void    setErrPressureRange       (bool    value){ if(mErrPressureRange    == value)return; mErrPressureRange    = value; emit signalEventChangedErrPressureRange   (value);}
    void    setErrCommandSetIdx       (bool    value){ if(mErrCommandSetIdx    == value)return; mErrCommandSetIdx    = value; emit signalEventChangedErrCommandSetIdx   (value);}
    void    setErrSecondAnswerIdx     (bool    value){ if(mErrSecondAnswerIdx  == value)return; mErrSecondAnswerIdx  = value; emit signalEventChangedErrSecondAnswerIdx (value);}
    void    setErrDIOpenValveIdx      (bool    value){ if(mErrDIOpenValveIdx   == value)return; mErrDIOpenValveIdx   = value; emit signalEventChangedErrDIOpenValveIdx  (value);}
    void    setErrDICloseValveIdx     (bool    value){ if(mErrDICloseValveIdx  == value)return; mErrDICloseValveIdx  = value; emit signalEventChangedErrDICloseValveIdx (value);}

    void    setIsEdit                 (bool    value){ if(mIsEdit              == value)return; mIsEdit              = value; emit signalEventChangedIsEdit             (value);}
    void    setStrStatus              (QString value){ if(mStrStatus           == value)return; mStrStatus           = value; emit signalEventChangedStrStatus          (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg              == value)return; mErrMsg              = value; emit signalEventChangedErrMsg             (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2             == value)return; mErrMsg2             = value; emit signalEventChangedErrMsg2            (value);}
    void    setProgress               (int     value){ if(mProgress            == value)return; mProgress            = value; emit signalEventChangedProgress           (value);}

signals:
    void signalEventChangedAccessMode         (int     value);
    void signalEventChangedInterface          (int     value);
    void signalEventChangedIsRS232Test        (bool    value);

    void signalEventChangedBaudrateIdx        (int     value);
    void signalEventChangedParityIdx          (int     value);
    void signalEventChangedDataLenIdx         (int     value);
    void signalEventChangedStopBitIdx         (int     value);
    void signalEventChangedOperationModeIdx   (int     value);
    void signalEventChangedDuplexModeIdx      (int     value);
    void signalEventChangedDevAddr            (int     value);
    void signalEventChangedTerminationIdx     (int     value);
    void signalEventChangedPosRangeIdx        (int     value);
    void signalEventChangedPressureRange      (int     value);
    void signalEventChangedCommandSetIdx      (int     value);
    void signalEventChangedSecondAnswerIdx    (int     value);
    void signalEventChangedDIOpenValveIdx     (int     value);
    void signalEventChangedDICloseValveIdx    (int     value);
    void signalEventChangedErrBaudrateIdx     (bool    value);
    void signalEventChangedErrParityIdx       (bool    value);
    void signalEventChangedErrDataLenIdx      (bool    value);
    void signalEventChangedErrStopBitIdx      (bool    value);
    void signalEventChangedErrOperationModeIdx(bool    value);
    void signalEventChangedErrDuplexModeIdx   (bool    value);
    void signalEventChangedErrDevAddr         (bool    value);
    void signalEventChangedErrTerminationIdx  (bool    value);
    void signalEventChangedErrPosRangeIdx     (bool    value);
    void signalEventChangedErrPressureRange   (bool    value);
    void signalEventChangedErrCommandSetIdx   (bool    value);
    void signalEventChangedErrSecondAnswerIdx (bool    value);
    void signalEventChangedErrDIOpenValveIdx  (bool    value);
    void signalEventChangedErrDICloseValveIdx (bool    value);

    void signalEventChangedIsEdit            (bool    value);
    void signalEventChangedStrStatus         (QString value);
    void signalEventChangedErrMsg            (QString value);
    void signalEventChangedErrMsg2           (QString value);
    void signalEventChangedProgress          (int     value);
    void signalEventCompletedLoad            (             );

public:
    explicit InterfaceSetupRS232DlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS232;
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS485;
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS232_RANGE;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS232;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS485;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS232_RANGE;
        ENABLE_SLOT_VALVE_CHANGED_VALVE_INTERFACE;

        onValveChangedAccess();
        onValveChangedInterface();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CFG);
    }
    ~InterfaceSetupRS232DlgModel()
    {
        pValveSP->reLoad();
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedInterface()
    {
        setInterface(pValveSP->getInterface());
    }

    void onValveChangedIsRS232Test()
    {
        setIsRS232Test(pValveSP->getIsRS232Test());
    }

    void onValveReadedInterfaceCfgRS232(ValveResponseInterfaceConfigRS232Dto dto)
    {
        if(mState != eState::STATE_READ_CFG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrBaudrateIdx    (dto.mBaudrateIdx     != mWriteBaudrateIdx    );
            setErrParityIdx      (dto.mParityIdx       != mWriteParityIdx      );
            setErrDataLenIdx     (dto.mDataLenIdx      != mWriteDataLenIdx     );
            setErrStopBitIdx     (dto.mStopBitIdx      != mWriteStopBitIdx     );
            setErrCommandSetIdx  (dto.mCommandSetIdx   != mWriteCommandSetIdx  );
            setErrSecondAnswerIdx(dto.mSecondAnswerIdx != mWriteSecondAnswerIdx);
            setErrDIOpenValveIdx (dto.mDIOpenValveIdx  != mWriteDIOpenValveIdx );
            setErrDICloseValveIdx(dto.mDICloseValveIdx != mWriteDICloseValveIdx);
        }
        else
        {
            setBaudrateIdx    (dto.mBaudrateIdx    );
            setParityIdx      (dto.mParityIdx      );
            setDataLenIdx     (dto.mDataLenIdx     );
            setStopBitIdx     (dto.mStopBitIdx     );
            setCommandSetIdx  (dto.mCommandSetIdx  );
            setSecondAnswerIdx(dto.mSecondAnswerIdx);
            setDIOpenValveIdx (dto.mDIOpenValveIdx );
            setDICloseValveIdx(dto.mDICloseValveIdx);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgRS232Range(ValveResponseInterfaceConfigRS232RangeDto dto)
    {
        if(mState != eState::STATE_READ_RANGE || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrPosRangeIdx  (dto.mPosRangeIdx   != mWritePosRangeIdx  );
            setErrPressureRange(dto.mPressureRange != mWritePressureRange);

            onCommandSetEdit(getErrBaudrateIdx() || getErrParityIdx() || getErrDataLenIdx() || getErrStopBitIdx() || getErrCommandSetIdx() || getErrSecondAnswerIdx() || getErrDIOpenValveIdx() || getErrDICloseValveIdx() || getErrPosRangeIdx() || getErrPressureRange());
        }
        else
        {
            setPosRangeIdx  (dto.mPosRangeIdx  );
            setPressureRange(dto.mPressureRange);
        }

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgRS485(ValveResponseInterfaceConfigRS485Dto dto)
    {
        if(mState != eState::STATE_READ_RS485_CFG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrOperationModeIdx(dto.mOperationModeIdx != mWriteOperationModeIdx);
            setErrDuplexModeIdx   (dto.mDuplexModeIdx    != mWriteDuplexModeIdx   );
            setErrDevAddr         (dto.mDevAddr          != mWriteDevAddr         );
            setErrTerminationIdx  (dto.mTerminationIdx   != mWriteTerminationIdx  );
        }
        else
        {
            setOperationModeIdx(dto.mOperationModeIdx);
            setDuplexModeIdx   (dto.mDuplexModeIdx   );
            setDevAddr         (dto.mDevAddr         );
            setTerminationIdx  (dto.mTerminationIdx  );
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int baudrateIdx, int parityIdx,int dataLenIdx, int stopBitIdx, int operationModeIdx, int duplexModeIdx, int devAddr, int terminationIdx  ,int commandSetIdx, int secondAnswerIdx, int diOpenValveIdx, int diCloseValveIdx, int posRangeIdx, int pressureRange)
    {
        mIsWritten             = true            ;
        mWriteBaudrateIdx      = baudrateIdx     ;
        mWriteParityIdx        = parityIdx       ;
        mWriteDataLenIdx       = dataLenIdx      ;
        mWriteStopBitIdx       = stopBitIdx      ;
        mWriteOperationModeIdx = operationModeIdx;
        mWriteDuplexModeIdx    = duplexModeIdx   ;
        mWriteDevAddr          = devAddr         ;
        mWriteTerminationIdx   = terminationIdx  ;
        mWriteCommandSetIdx    = commandSetIdx   ;
        mWriteSecondAnswerIdx  = secondAnswerIdx ;
        mWriteDIOpenValveIdx   = diOpenValveIdx  ;
        mWriteDICloseValveIdx  = diCloseValveIdx ;
        mWritePosRangeIdx      = posRangeIdx     ;
        mWritePressureRange    = pressureRange   ;

        setIsEdit(false);

        setErrMsg("");
        setErrMsg2("");

        setState(eState::STATE_WRITE_CFG);
    }

    void onValveWrittenInterfaceCfgRS232(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_CFG || dto.mReqDto.mpRef != this)
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

    void onValveWrittenInterfaceCfgRS232Range(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_RANGE || dto.mReqDto.mpRef != this)
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

    void onValveWrittenInterfaceCfgRS485(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_RS485_CFG || dto.mReqDto.mpRef != this)
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
        STATE_WRITE_CFG       =  0,
        STATE_WRITE_RS485_CFG = STATE_WRITE_CFG       + 1,
        STATE_WRITE_RANGE     = STATE_WRITE_RS485_CFG + 1,
        STATE_READ_CFG        = STATE_WRITE_RANGE     + 1,
        STATE_READ_RS485_CFG  = STATE_READ_CFG        + 1,
        STATE_READ_RANGE      = STATE_READ_RS485_CFG  + 1,
        STATE_READY           = STATE_READ_RANGE      + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CFG;

    bool mIsWritten             = false;
    int  mWriteBaudrateIdx      = 0;
    int  mWriteParityIdx        = 0;
    int  mWriteDataLenIdx       = 0;
    int  mWriteStopBitIdx       = 0;
    int  mWriteOperationModeIdx = 0;
    int  mWriteDuplexModeIdx    = 0;
    int  mWriteDevAddr          = 0;
    int  mWriteTerminationIdx   = 0;
    int  mWriteCommandSetIdx    = 0;
    int  mWriteSecondAnswerIdx  = 0;
    int  mWriteDIOpenValveIdx   = 0;
    int  mWriteDICloseValveIdx  = 0;
    int  mWritePosRangeIdx      = 0;
    int  mWritePressureRange    = 0;

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

        if((getInterface() == ValveEnumDef::INTERFACE_RS232 || getInterface() == ValveEnumDef::INTERFACE_RS232_WITH_ANALOGOUTPUT)
                && (mState == STATE_READ_RS485_CFG || mState == STATE_WRITE_RS485_CFG))
        {
            setState((eState)(mState + 1));
            return;
        }

        progress = ((mState) * 100) / STATE_READY;

        if(mState >= STATE_READ_CFG && mState <= STATE_READ_RANGE)
        {
            strStatus = "loading";
        }
        else if(mState >= STATE_WRITE_CFG && mState <= STATE_WRITE_RANGE)
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
        case (int)eState::STATE_READ_CFG:
            pValveSP->readInterfaceConfigRS232(this);
            break;

        case (int)eState::STATE_READ_RS485_CFG:
            pValveSP->readInterfaceConfigRS485(this);
            break;

        case (int)eState::STATE_READ_RANGE:
            pValveSP->readInterfaceConfigRS232Range(this);
            break;

        case (int)eState::STATE_WRITE_CFG:
            pValveSP->setInterfaceConfigRS232(mWriteBaudrateIdx, mWriteParityIdx, mWriteDataLenIdx, mWriteStopBitIdx, mWriteCommandSetIdx, mWriteSecondAnswerIdx, mWriteDIOpenValveIdx, mWriteDICloseValveIdx, this);
            break;

        case (int)eState::STATE_WRITE_RS485_CFG:
            pValveSP->setInterfaceConfigRS485(mWriteOperationModeIdx, mWriteDuplexModeIdx, mWriteDevAddr, mWriteTerminationIdx, this);
            break;
        case (int)eState::STATE_WRITE_RANGE:
            pValveSP->setInterfaceConfigRS232Range(mWritePosRangeIdx, mWritePressureRange, this);
            break;
        }
    }

};
#endif // INTERFACESETUPRS232DLGMODEL_H
