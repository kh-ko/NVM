#ifndef INTERFACESETUPPROFIBUSDLGMODEL_H
#define INTERFACESETUPPROFIBUSDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

class InterfaceSetupProfibusDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool     mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test      )

    Q_PROPERTY(int      mDIFunction          READ getDIFunction          NOTIFY signalEventChangedDIFunction       )
    Q_PROPERTY(int      mDIMode              READ getDIMode              NOTIFY signalEventChangedDIMode           )
    Q_PROPERTY(int      mDIInput             READ getDIInput             NOTIFY signalEventChangedDIInput          )
    Q_PROPERTY(int      mDOFunction          READ getDOFunction          NOTIFY signalEventChangedDOFunction       )
    Q_PROPERTY(int      mDOMode              READ getDOMode              NOTIFY signalEventChangedDOMode           )
    Q_PROPERTY(int      mDOOutput            READ getDOOutput            NOTIFY signalEventChangedDOOutput         )
    Q_PROPERTY(int      mNodeAddr            READ getNodeAddr            NOTIFY signalEventChangedNodeAddr         )
    Q_PROPERTY(int      mBaudrateIdx         READ getBaudrateIdx         NOTIFY signalEventChangedBaudrateIdx      )

    Q_PROPERTY(bool     mErrDIFunction       READ getErrDIFunction       NOTIFY signalEventChangedErrDIFunction    )
    Q_PROPERTY(bool     mErrDIMode           READ getErrDIMode           NOTIFY signalEventChangedErrDIMode        )
    Q_PROPERTY(bool     mErrDIInput          READ getErrDIInput          NOTIFY signalEventChangedErrDIInput       )
    Q_PROPERTY(bool     mErrDOFunction       READ getErrDOFunction       NOTIFY signalEventChangedErrDOFunction    )
    Q_PROPERTY(bool     mErrDOMode           READ getErrDOMode           NOTIFY signalEventChangedErrDOMode        )
    Q_PROPERTY(bool     mErrDOOutput         READ getErrDOOutput         NOTIFY signalEventChangedErrDOOutput      )
    Q_PROPERTY(bool     mErrNodeAddr         READ getErrNodeAddr         NOTIFY signalEventChangedErrNodeAddr      )

    Q_PROPERTY(bool     mIsEdit              READ getIsEdit              NOTIFY signalEventChangedIsEdit           )
    Q_PROPERTY(QString  mStrStatus           READ getStrStatus           NOTIFY signalEventChangedStrStatus        )
    Q_PROPERTY(QString  mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg           )
    Q_PROPERTY(QString  mErrMsg2             READ getErrMsg2             NOTIFY signalEventChangedErrMsg2          )
    Q_PROPERTY(int      mProgress            READ getProgress            NOTIFY signalEventChangedProgress         )

public:
    int      mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test             = false;
    int      mDIFunction              = 0;
    int      mDIMode                  = 0;
    int      mDIInput                 = 0;
    int      mDOFunction              = 0;
    int      mDOMode                  = 0;
    int      mDOOutput                = 0;
    int      mNodeAddr                = 0;
    int      mBaudrateIdx             = 0;

    bool     mErrDIFunction           = 0;
    bool     mErrDIMode               = 0;
    bool     mErrDIInput              = 0;
    bool     mErrDOFunction           = 0;
    bool     mErrDOMode               = 0;
    bool     mErrDOOutput             = 0;
    bool     mErrNodeAddr             = 0;

    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){return mIsRS232Test             ;}

    int     getDIFunction             (){ return mDIFunction             ;}
    int     getDIMode                 (){ return mDIMode                 ;}
    int     getDIInput                (){ return mDIInput                ;}
    int     getDOFunction             (){ return mDOFunction             ;}
    int     getDOMode                 (){ return mDOMode                 ;}
    int     getDOOutput               (){ return mDOOutput               ;}
    int     getNodeAddr               (){ return mNodeAddr               ;}
    int     getBaudrateIdx            (){ return mBaudrateIdx            ;}

    bool    getErrDIFunction          (){ return mErrDIFunction          ;}
    bool    getErrDIMode              (){ return mErrDIMode              ;}
    bool    getErrDIInput             (){ return mErrDIInput             ;}
    bool    getErrDOFunction          (){ return mErrDOFunction          ;}
    bool    getErrDOMode              (){ return mErrDOMode              ;}
    bool    getErrDOOutput            (){ return mErrDOOutput            ;}
    bool    getErrNodeAddr            (){ return mErrNodeAddr            ;}

    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}

    void    setDIFunction             (int     value){ if(mDIFunction              == value)return; mDIFunction              = value; emit signalEventChangedDIFunction             (value);}
    void    setDIMode                 (int     value){ if(mDIMode                  == value)return; mDIMode                  = value; emit signalEventChangedDIMode                 (value);}
    void    setDIInput                (int     value){ if(mDIInput                 == value)return; mDIInput                 = value; emit signalEventChangedDIInput                (value);}
    void    setDOFunction             (int     value){ if(mDOFunction              == value)return; mDOFunction              = value; emit signalEventChangedDOFunction             (value);}
    void    setDOMode                 (int     value){ if(mDOMode                  == value)return; mDOMode                  = value; emit signalEventChangedDOMode                 (value);}
    void    setDOOutput               (int     value){ if(mDOOutput                == value)return; mDOOutput                = value; emit signalEventChangedDOOutput               (value);}
    void    setNodeAddr               (int     value){ if(mNodeAddr                == value)return; mNodeAddr                = value; emit signalEventChangedNodeAddr               (value);}
    void    setBaudrateIdx            (int     value){ if(mBaudrateIdx             == value)return; mBaudrateIdx             = value; emit signalEventChangedBaudrateIdx            (value);}

    void    setErrDIFunction          (bool    value){ if(mErrDIFunction           == value)return; mErrDIFunction           = value; emit signalEventChangedErrDIFunction          (value);}
    void    setErrDIMode              (bool    value){ if(mErrDIMode               == value)return; mErrDIMode               = value; emit signalEventChangedErrDIMode              (value);}
    void    setErrDIInput             (bool    value){ if(mErrDIInput              == value)return; mErrDIInput              = value; emit signalEventChangedErrDIInput             (value);}
    void    setErrDOFunction          (bool    value){ if(mErrDOFunction           == value)return; mErrDOFunction           = value; emit signalEventChangedErrDOFunction          (value);}
    void    setErrDOMode              (bool    value){ if(mErrDOMode               == value)return; mErrDOMode               = value; emit signalEventChangedErrDOMode              (value);}
    void    setErrDOOutput            (bool    value){ if(mErrDOOutput             == value)return; mErrDOOutput             = value; emit signalEventChangedErrDOOutput            (value);}
    void    setErrNodeAddr            (bool    value){ if(mErrNodeAddr             == value)return; mErrNodeAddr             = value; emit signalEventChangedErrNodeAddr            (value);}

    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);

    void signalEventChangedDIFunction             (int     value);
    void signalEventChangedDIMode                 (int     value);
    void signalEventChangedDIInput                (int     value);
    void signalEventChangedDOFunction             (int     value);
    void signalEventChangedDOMode                 (int     value);
    void signalEventChangedDOOutput               (int     value);
    void signalEventChangedNodeAddr               (int     value);
    void signalEventChangedBaudrateIdx            (int     value);

    void signalEventChangedErrDIFunction          (bool    value);
    void signalEventChangedErrDIMode              (bool    value);
    void signalEventChangedErrDIInput             (bool    value);
    void signalEventChangedErrDOFunction          (bool    value);
    void signalEventChangedErrDOMode              (bool    value);
    void signalEventChangedErrDOOutput            (bool    value);
    void signalEventChangedErrNodeAddr            (bool    value);

    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );

public:
    explicit InterfaceSetupProfibusDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DI;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DO;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_ETHCAT_DI;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_ETHCAT_DO;
        ENABLE_SLOT_VALVE_READED_IF_CFG_FIELDBUS_NODE_ADDR;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_FIELDBUS_NODE_ADDR;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_DI);
    }
    ~InterfaceSetupProfibusDlgModel()
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

    void onValveReadedInterfaceConfigEthCATDi(ValveResponseInterfaceConfigEthCATDiDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << "Func = " << dto.mDIFunction << ", Mode =" <<  dto.mDIMode << ", Input = " << dto.mDIInput;

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
            setErrDIFunction(dto.mDIFunction != mWriteDIFunction);
            setErrDIMode    (dto.mDIMode     != mWriteDIMode    );
            setErrDIInput   (dto.mDIInput    != mWriteDIInput   );
        }
        else
        {
            setDIFunction (dto.mDIFunction);
            setDIMode     (dto.mDIMode    );
            setDIInput    (dto.mDIInput   );
        }

        mReadedDIFunction = dto.mDIFunction;
        mReadedDIMode     = dto.mDIMode;
        mReadedDIInput    = dto.mDIInput;

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceConfigEthCATDo(ValveResponseInterfaceConfigEthCATDoDto dto)
    {
        if(mState != eState::STATE_READ_DO || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << "Func = " << dto.mDOFunction << ", Mode =" <<  dto.mDOMode << ", Input = " << dto.mDOOutput;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrDOFunction(dto.mDOFunction != mWriteDOFunction);
            setErrDOMode    (dto.mDOMode     != mWriteDOMode    );
            setErrDOOutput  (dto.mDOOutput   != mWriteDOOutput  );

            //onCommandSetEdit(getErrDIFunction() || getErrDIMode() || getErrDIInput() || getErrDOFunction() || getErrDOMode() || getErrDOOutput());
        }
        else
        {
            setDOFunction (dto.mDOFunction);
            setDOMode     (dto.mDOMode    );
            setDOOutput   (dto.mDOOutput  );
        }

        mReadedDOFunction = dto.mDOFunction;
        mReadedDOMode     = dto.mDOMode;
        mReadedDOOutput   = dto.mDOOutput;

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgFieldbusNodeAddr(ValveResponseInterfaceConfigFieldbusNodeAddrDto dto)
    {
        if(mState != eState::STATE_READ_NODE_ADDR || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrNodeAddr(dto.mNodeAddr != mWriteNodeAddr);
        }
        else
        {
            setNodeAddr(dto.mNodeAddr);
        }

        mReadedNodeAddr = dto.mNodeAddr;

        setState((eState)(mState + 1));
    }

    void onEditItem(bool isEdit)
    {
        if(isEdit)
            setIsEdit(isEdit);
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int diFunction, int diMode, int diInput, int doFunction, int doMode, int doOutput,int nodeAddr)
    {
        mIsWritten       = true      ;
        mWriteDIFunction = diFunction;
        mWriteDIMode     = diMode    ;
        mWriteDIInput    = diInput   ;
        mWriteDOFunction = doFunction;
        mWriteDOMode     = doMode    ;
        mWriteDOOutput   = doOutput  ;
        mWriteNodeAddr   = nodeAddr  ;

        setIsEdit(false);

        setErrMsg("");
        setErrMsg2("");

        setState(eState::STATE_WRITE_DI);
    }

    void onValveWrittenInterfaceConfigEthCATDi(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_DI || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

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

    void onValveWrittenInterfaceConfigEthCATDo(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE_DO || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

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

    void onValveWrittenInterfaceCfgFieldbusNodeAddr(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_NODE_ADDR || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

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
        STATE_WRITE_DI        =  0,
        STATE_WRITE_DO        = STATE_WRITE_DI        + 1,
        STATE_WRITE_NODE_ADDR = STATE_WRITE_DO        + 1,
        STATE_READ_DI         = STATE_WRITE_NODE_ADDR + 1,
        STATE_READ_DO         = STATE_READ_DI         +1,
        STATE_READ_NODE_ADDR  = STATE_READ_DO         + 1,
        STATE_READY           = STATE_READ_NODE_ADDR  + 1
    };

    QTimer mTimer;
    eState mState          = eState::STATE_WRITE_DI;

    bool mIsWritten        = false;
    int  mWriteDIFunction  = 0;
    int  mWriteDIMode      = 0;
    int  mWriteDIInput     = 0;
    int  mWriteDOFunction  = 0;
    int  mWriteDOMode      = 0;
    int  mWriteDOOutput    = 0;
    int  mWriteNodeAddr    = 0;

    int  mReadedDIFunction = 0;
    int  mReadedDIMode     = 0;
    int  mReadedDIInput    = 0;
    int  mReadedDOFunction = 0;
    int  mReadedDOMode     = 0;
    int  mReadedDOOutput   = 0;
    int  mReadedNodeAddr   = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state, bool immediately = false)
    {
        int progress = 0;
        QString strStatus;

        mState = state;

        if(mIsWritten == false && mState == STATE_READY)
        {
            emit signalEventCompletedLoad();
        }

        if(mState >= STATE_READ_DI && mState <= STATE_READ_NODE_ADDR)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "loading";
        }
        else if(mState >= STATE_WRITE_DI && mState <= STATE_WRITE_NODE_ADDR)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "writting";
        }
        else
        {
            progress = 100;
            strStatus = "ready";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        if(immediately)
            onTimeout();
        else
            startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_DI:
            if(   mReadedDIFunction == mWriteDIFunction && mErrDIFunction == false
               && mReadedDIMode     == mWriteDIMode     && mErrDIMode     == false
               && mReadedDIInput    == mWriteDIInput    && mErrDIInput    == false
               && mIsWritten)
            {
                setState((eState)(mState + 1), true);
                return;
            }
            pValveSP->readInterfaceConfigEthCATDi(this);
            break;

        case (int)eState::STATE_READ_DO:
            if(   mReadedDOFunction == mWriteDOFunction && mErrDOFunction == false
               && mReadedDOMode     == mWriteDOMode     && mErrDOMode     == false
               && mReadedDOOutput   == mWriteDOOutput   && mErrDOOutput   == false
               && mIsWritten)
            {
                setState((eState)(mState + 1), true);
                return;
            }
            pValveSP->readInterfaceConfigEthCATDo(this);
            break;

        case (int)eState::STATE_READ_NODE_ADDR:
            if(   mReadedNodeAddr == mWriteNodeAddr && mErrNodeAddr == false && mIsWritten)
            {
                setState((eState)(mState + 1), true);
                return;
            }
            pValveSP->readInterfaceConfigFieldbusNodeAddr(this);
            break;

        case (int)eState::STATE_WRITE_DI:
            if(   mReadedDIFunction == mWriteDIFunction && mErrDIFunction == false
               && mReadedDIMode     == mWriteDIMode     && mErrDIMode     == false
               && mReadedDIInput    == mWriteDIInput    && mErrDIInput    == false)
            {
                setState((eState)(mState + 1), true);
                return;
            }
            pValveSP->setInterfaceConfigEthCATDi(mWriteDIFunction, mWriteDIMode, mWriteDIInput, this);
            break;

        case (int)eState::STATE_WRITE_DO:
            if(  mReadedDOFunction == mWriteDOFunction && mErrDOFunction == false
               &&mReadedDOMode     == mWriteDOMode     && mErrDOMode     == false
               &&mReadedDOOutput   == mWriteDOOutput   && mErrDOOutput   == false)
            {
                setState((eState)(mState + 1), true);
                return;
            }
            pValveSP->setInterfaceConfigEthCATDo(mWriteDOFunction, mWriteDOMode, mWriteDOOutput, this);
            break;

        case (int)eState::STATE_WRITE_NODE_ADDR:
            pValveSP->setInterfaceConfigFieldbusNodeAddr(mWriteNodeAddr, this);
            break;

        default:
            break;
        }
    }
};
#endif // INTERFACESETUPPROFIBUSDLGMODEL_H
