#ifndef INTERFACESETUPPROFIBUSDLGMODEL_H
#define INTERFACESETUPPROFIBUSDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"



class InterfaceSetupProfibusItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsEdit       READ getIsEdit       WRITE setIsEdit       NOTIFY signalEventChangedIsEdit      )
    Q_PROPERTY(bool    mErrDataType  READ getErrDataType  WRITE setErrDataType  NOTIFY signalEventChangedErrDataType )
    Q_PROPERTY(bool    mErrRangeFrom READ getErrRangeFrom WRITE setErrRangeFrom NOTIFY signalEventChangedErrRangeFrom)
    Q_PROPERTY(bool    mErrRangeTo   READ getErrRangeTo   WRITE setErrRangeTo   NOTIFY signalEventChangedErrRangeTo  )
    Q_PROPERTY(int     mDataType     READ getDataType     WRITE setDataType     NOTIFY signalEventChangedDataType    )
    Q_PROPERTY(QString mRangeFrom    READ getRangeFrom    WRITE setRangeFrom    NOTIFY signalEventChangedRangeFrom   )
    Q_PROPERTY(QString mRangeTo      READ getRangeTo      WRITE setRangeTo      NOTIFY signalEventChangedRangeTo     )

public:
    bool    mIsEdit       = false;
    bool    mErrDataType  = false;
    bool    mErrRangeFrom = false;
    bool    mErrRangeTo   = false;
    int     mDataType     = 0;
    QString mRangeFrom    = "0";
    QString mRangeTo      = "1000000";

public slots:
    bool    getIsEdit      (){ return mIsEdit      ; }
    bool    getErrDataType (){ return mErrDataType ; }
    bool    getErrRangeFrom(){ return mErrRangeFrom; }
    bool    getErrRangeTo  (){ return mErrRangeTo  ; }
    int     getDataType    (){ return mDataType    ; }
    QString getRangeFrom   (){ return mRangeFrom   ; }
    QString getRangeTo     (){ return mRangeTo     ; }

    void setIsEdit      (bool    value){ if(mIsEdit       == value) return; mIsEdit       = value; emit signalEventChangedIsEdit      (value); }
    void setErrDataType (bool    value){ if(mErrDataType  == value) return; mErrDataType  = value; emit signalEventChangedErrDataType (value); setIsEdit(true); }
    void setErrRangeFrom(bool    value){ if(mErrRangeFrom == value) return; mErrRangeFrom = value; emit signalEventChangedErrRangeFrom(value); setIsEdit(true); }
    void setErrRangeTo  (bool    value){ if(mErrRangeTo   == value) return; mErrRangeTo   = value; emit signalEventChangedErrRangeTo  (value); setIsEdit(true); }
    void setDataType    (int     value){ if(mDataType     == value) return; mDataType     = value; emit signalEventChangedDataType    (value); setIsEdit(true); }
    void setRangeFrom   (QString value){ if(mRangeFrom    == value) return; mRangeFrom    = value; emit signalEventChangedRangeFrom   (value); setIsEdit(true); }
    void setRangeTo     (QString value){ if(mRangeTo      == value) return; mRangeTo      = value; emit signalEventChangedRangeTo     (value); setIsEdit(true); }

signals:
    void signalEventChangedIsEdit      (bool    value);
    void signalEventChangedErrDataType (bool    value);
    void signalEventChangedErrRangeFrom(bool    value);
    void signalEventChangedErrRangeTo  (bool    value);
    void signalEventChangedDataType    (int     value);
    void signalEventChangedRangeFrom   (QString value);
    void signalEventChangedRangeTo     (QString value);

public:
    void    reset()
    {
        setIsEdit      (false    );
        setErrDataType (false    );
        setErrRangeFrom(false    );
        setErrRangeTo  (false    );
        setDataType    (0        );
        setRangeFrom   ("0"      );
        setRangeTo     ("1000000");
    }

    explicit InterfaceSetupProfibusItemModel(QObject *parent = nullptr): QObject(parent)
    {
    }

    ~InterfaceSetupProfibusItemModel()
    {
    }

};

class InterfaceSetupProfibusDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool     mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test      )

    Q_PROPERTY(int      mTypeIdx             READ getTypeIdx             NOTIFY signalEventChangedTypeIdx          )
    Q_PROPERTY(int      mDIOpenValveIdx      READ getDIOpenValveIdx      NOTIFY signalEventChangedDIOpenValveIdx   )
    Q_PROPERTY(int      mDICloseValveIdx     READ getDICloseValveIdx     NOTIFY signalEventChangedDICloseValveIdx  )
    Q_PROPERTY(int      mNodeAddr            READ getNodeAddr            NOTIFY signalEventChangedNodeAddr         )
    Q_PROPERTY(int      mBaudrateIdx         READ getBaudrateIdx         NOTIFY signalEventChangedBaudrateIdx      )

    Q_PROPERTY(bool     mErrTypeIdx          READ getErrTypeIdx          NOTIFY signalEventChangedErrTypeIdx         )
    Q_PROPERTY(bool     mErrDIOpenValveIdx   READ getErrDIOpenValveIdx   NOTIFY signalEventChangedErrDIOpenValveIdx  )
    Q_PROPERTY(bool     mErrDICloseValveIdx  READ getErrDICloseValveIdx  NOTIFY signalEventChangedErrDICloseValveIdx )
    Q_PROPERTY(bool     mErrNodeAddr         READ getErrNodeAddr         NOTIFY signalEventChangedErrNodeAddr        )

    Q_PROPERTY(bool     mIsEdit              READ getIsEdit              NOTIFY signalEventChangedIsEdit           )
    Q_PROPERTY(QString  mStrStatus           READ getStrStatus           NOTIFY signalEventChangedStrStatus        )
    Q_PROPERTY(QString  mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg           )
    Q_PROPERTY(QString  mErrMsg2             READ getErrMsg2             NOTIFY signalEventChangedErrMsg2          )
    Q_PROPERTY(int      mProgress            READ getProgress            NOTIFY signalEventChangedProgress         )

public:
    int      mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test             = false;
    int      mTypeIdx                 = 0;
    int      mDIOpenValveIdx          = 0;
    int      mDICloseValveIdx         = 0;
    int      mNodeAddr                = 0;
    int      mBaudrateIdx             = 0;

    bool     mErrTypeIdx              = false;
    bool     mErrDIOpenValveIdx       = false;
    bool     mErrDICloseValveIdx      = false;
    //bool     mErrDIFunction           = 0;
    //bool     mErrDIMode               = 0;
    //bool     mErrDIInput              = 0;
    //bool     mErrDOFunction           = 0;
    //bool     mErrDOMode               = 0;
    //bool     mErrDOOutput             = 0;
    bool     mErrNodeAddr             = 0;

    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}

    int     getTypeIdx                (){ return mTypeIdx                ;}
    int     getDIOpenValveIdx         (){ return mDIOpenValveIdx         ;}
    int     getDICloseValveIdx        (){ return mDICloseValveIdx        ;}
    int     getNodeAddr               (){ return mNodeAddr               ;}
    int     getBaudrateIdx            (){ return mBaudrateIdx            ;}

    bool    getErrTypeIdx           (){ return mErrTypeIdx               ;}
    bool    getErrDIOpenValveIdx    (){ return mErrDIOpenValveIdx        ;}
    bool    getErrDICloseValveIdx   (){ return mErrDICloseValveIdx       ;}
    bool    getErrNodeAddr            (){ return mErrNodeAddr            ;}

    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}

    void    setTypeIdx                (int     value){ if(mTypeIdx                 == value)return; mTypeIdx                 = value; emit signalEventChangedTypeIdx                (value);}
    void    setDIOpenValveIdx         (int     value){ if(mDIOpenValveIdx          == value)return; mDIOpenValveIdx          = value; emit signalEventChangedDIOpenValveIdx         (value);}
    void    setDICloseValveIdx        (int     value){ if(mDICloseValveIdx         == value)return; mDICloseValveIdx         = value; emit signalEventChangedDICloseValveIdx        (value);}
    void    setNodeAddr               (int     value){ if(mNodeAddr                == value)return; mNodeAddr                = value; emit signalEventChangedNodeAddr               (value);}
    void    setBaudrateIdx            (int     value){ if(mBaudrateIdx             == value)return; mBaudrateIdx             = value; emit signalEventChangedBaudrateIdx            (value);}

    void    setErrTypeIdx             (bool    value){ if(mErrTypeIdx              == value)return; mErrTypeIdx              = value; emit signalEventChangedErrTypeIdx             (value);}
    void    setErrDIOpenValveIdx      (bool    value){ if(mDIOpenValveIdx          == value)return; mErrDIOpenValveIdx       = value; emit signalEventChangedErrDIOpenValveIdx      (value);}
    void    setErrDICloseValveIdx     (bool    value){ if(mDICloseValveIdx         == value)return; mErrDICloseValveIdx      = value; emit signalEventChangedErrDICloseValveIdx     (value);}
    void    setErrNodeAddr            (bool    value){ if(mErrNodeAddr             == value)return; mErrNodeAddr             = value; emit signalEventChangedErrNodeAddr            (value);}

    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);

    void signalEventChangedTypeIdx                (int     value);
    void signalEventChangedDIOpenValveIdx         (int     value);
    void signalEventChangedDICloseValveIdx        (int     value);

    void signalEventChangedNodeAddr               (int     value);
    void signalEventChangedBaudrateIdx            (int     value);

    void signalEventChangedErrTypeIdx             (bool    value);
    void signalEventChangedErrDIOpenValveIdx      (bool    value);
    void signalEventChangedErrDICloseValveIdx     (bool    value);
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
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS232;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS232;
        ENABLE_SLOT_VALVE_READED_IF_CFG_FIELDBUS_NODE_ADDR;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_FIELDBUS_NODE_ADDR;
        ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_DATA_TYPE;
        ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_RANGE;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_DATA_TYPE;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_RANGE;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        for(int i = 0; i < 100; i ++)
        {
            InterfaceSetupProfibusItemModel * pItemModel = new InterfaceSetupProfibusItemModel(this);
            connect(pItemModel, SIGNAL(signalEventChangedIsEdit(bool)), this, SLOT(onEditItem(bool)));
            mPDOList.append(pItemModel);
        }

        setState(eState::STATE_READ_NODE_ADDR);
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

    void onValveReadedInterfaceCfgFieldbusNodeAddr(ValveResponseInterfaceConfigFieldbusNodeAddrDto dto)
    {
        if(mState != eState::STATE_READ_NODE_ADDR || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << dto.mResData;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrNodeAddr       (dto.mNodeAddr != mWriteNodeAddr       );
            setErrTypeIdx        (dto.mType     != mWriteType           );
            setErrDIOpenValveIdx (dto.mDiOpen   != mWriteDIOpenValveIdx );
            setErrDICloseValveIdx(dto.mDiClose  != mWriteDICloseValveIdx);
        }
        else
        {
            setNodeAddr       (dto.mNodeAddr);
            setTypeIdx        (dto.mType    );
            setDIOpenValveIdx (dto.mDiOpen  );
            setDICloseValveIdx(dto.mDiClose );
        }

        mReadedNodeAddr = dto.mNodeAddr;

        setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgEthCATPDODataType(ValveResponseInterfaceConfigEthCATPDODataTypeDto dto)
    {
        int idx = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).length(), 2).toInt();

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << dto.mResData;

        if(idx != convertPDOIdx(mState) || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc)
        {
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }

        setErrMsg("");

        setPDOItemDataType(idx, dto.mDataType); // , dto.mRangeFrom, dto.mRangeTo

        //setState((eState)(mState + 1));
    }

    void onValveReadedInterfaceCfgEthCATPDORange(ValveResponseInterfaceConfigEthCATPDORangeDto dto)
    {
        int idx = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_RANGE).length(), 2).toInt();

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << dto.mResData;

        if(idx != convertPDOIdx(mState) || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc)
        {
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }

        setErrMsg("");

        setPDOItemRange(idx, dto.mRangeFrom, dto.mRangeTo);

        setState((eState)(mState + 1));
    }

    void onEditItem(bool isEdit)
    {
        if(isEdit)
            setIsEdit(isEdit);
    }


    Q_INVOKABLE void onCommandChangeDataType(int selDatType)
    {
        //for(int i = 0; i < mPDOList.count(); i ++)
        //{
        //    mPDOList[i]->setDataType(selDatType);
        //}
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE InterfaceSetupProfibusItemModel * onCommandGetPDOItem(int idx)
    {
        if(idx >= mPDOList.count())
            return &mDummyPDOItem;

        return mPDOList[idx];
    }

    Q_INVOKABLE int onCommandGetPDOItemCount()
    {
        return mPDOList.count();
    }

    Q_INVOKABLE void onCommandApply(int type, int diOpenIdx, int diCloseIdx,int nodeAddr)
    {
        mIsWritten       = true      ;

        mWriteType            = type      ;
        mWriteDIOpenValveIdx  = diOpenIdx ;
        mWriteDICloseValveIdx = diCloseIdx;

        //mWriteDIFunction = diFunction;
        //mWriteDIMode     = diMode    ;
        //mWriteDIInput    = diInput   ;
        //mWriteDOFunction = doFunction;
        //mWriteDOMode     = doMode    ;
        //mWriteDOOutput   = doOutput  ;
        mWriteNodeAddr   = nodeAddr  ;

        setIsEdit(false);

        setErrMsg("");
        setErrMsg2("");

        setState(eState::STATE_WRITE_NODE_ADDR);
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

    void onValveWrittenInterfaceCfgEthCATPDODataType(ValveResponseDto dto)
    {
        int idx = dto.mReqDto.mReqCommand.mid(QString(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).length(), 2).toInt();

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << convertPDOIdx(mState);

        if(idx != convertPDOIdx(mState) || dto.mReqDto.mpRef != this)
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
    }

    void onValveWrittenInterfaceCfgEthCATPDORange(ValveResponseDto dto)
    {
        int idx = dto.mReqDto.mReqCommand.mid(QString(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_RANGE).length(), 2).toInt();

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << convertPDOIdx(mState);

        if(idx != convertPDOIdx(mState) || dto.mReqDto.mpRef != this)
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
    QList<InterfaceSetupProfibusItemModel *>  mPDOList;
    InterfaceSetupProfibusItemModel           mDummyPDOItem;

private:
    enum eState{
        STATE_WRITE_NODE_ADDR = 0,
        STATE_WRITE_PDO_START = STATE_WRITE_NODE_ADDR + 1,
        STATE_WRITE_PDO_END   = STATE_WRITE_PDO_START + 11,
        STATE_READ_NODE_ADDR  = STATE_WRITE_PDO_END   + 1,
        STATE_READ_PDO_START  = STATE_READ_NODE_ADDR  + 1,
        STATE_READ_PDO_END    = STATE_READ_PDO_START  + 11,
        STATE_READY           = STATE_READ_PDO_END    + 1
    };

    QTimer mTimer;
    eState mState          = eState::STATE_WRITE_NODE_ADDR;

    bool mIsWritten        = false;
    int  mWriteType            = 0;
    int  mWriteDIOpenValveIdx  = 0;
    int  mWriteDICloseValveIdx = 0;
    //int  mWriteDIFunction  = 0;
    //int  mWriteDIMode      = 0;
    //int  mWriteDIInput     = 0;
    //int  mWriteDOFunction  = 0;
    //int  mWriteDOMode      = 0;
    //int  mWriteDOOutput    = 0;
    int  mWriteNodeAddr    = 0;

    //int  mReadedDIFunction = 0;
    //int  mReadedDIMode     = 0;
    //int  mReadedDIInput    = 0;
    //int  mReadedDOFunction = 0;
    //int  mReadedDOMode     = 0;
    //int  mReadedDOOutput   = 0;
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

        if(mState >= STATE_READ_NODE_ADDR && mState <= STATE_READ_PDO_END)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "loading";

            if(mState == STATE_READ_PDO_END)
            {
                bool isPDOErr = false;
                foreach(InterfaceSetupProfibusItemModel * pItem, mPDOList)
                {
                    if(pItem->getErrDataType() || pItem->getErrRangeFrom() || pItem->getErrRangeTo())
                        isPDOErr = true;
                }
                onCommandSetEdit(isPDOErr || getErrDIOpenValveIdx() || getErrDICloseValveIdx() || getErrNodeAddr() || getErrTypeIdx());
            }
        }
        else if(mState >= STATE_WRITE_NODE_ADDR && mState <= STATE_WRITE_PDO_END)
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
        case (int)eState::STATE_READ_NODE_ADDR:
            pValveSP->readInterfaceConfigFieldbusNodeAddr(this);
            break;

        case (int)eState::STATE_WRITE_NODE_ADDR:
            pValveSP->setInterfaceConfigFieldbusNodeAddr(mWriteNodeAddr, mWriteType, mWriteDIOpenValveIdx,  mWriteDICloseValveIdx, this);
            break;

        default:
            if(mState >= STATE_READ_PDO_START && mState <= STATE_READ_PDO_END)
            {


                if(mPDOList[convertPDOIdx(mState)]->getIsEdit() == false && mPDOList[convertPDOIdx(mState)]->getErrDataType() == false && mPDOList[convertPDOIdx(mState)]->getErrRangeFrom() == false && mPDOList[convertPDOIdx(mState)]->getErrRangeTo() == false && mIsWritten)
                {
                    setState((eState)(mState + 1), true);
                    return;
                }

                qDebug() << "[khko_debug][" << Q_FUNC_INFO << "is edit = " << mPDOList[convertPDOIdx(mState)]->getIsEdit();

                mPDOList[convertPDOIdx(mState)]->setIsEdit(false);
                pValveSP->readInterfaceConfigEthCATPDODataType(convertPDOIdx(mState), this);
                pValveSP->readInterfaceConfigEthCATPDORange(convertPDOIdx(mState), this);
            }
            else if(mState >= STATE_WRITE_PDO_START && mState <= STATE_WRITE_PDO_END)
            {
                if(mPDOList[convertPDOIdx(mState)]->getIsEdit() == false && mPDOList[convertPDOIdx(mState)]->getErrDataType() == false && mPDOList[convertPDOIdx(mState)]->getErrRangeFrom() == false && mPDOList[convertPDOIdx(mState)]->getErrRangeTo() == false)
                {
                    setState((eState)(mState + 1), true);
                    return;
                }

                qDebug() << "[khko_debug][" << Q_FUNC_INFO << "is edit = " << mPDOList[convertPDOIdx(mState)]->getIsEdit();

                int dataType = mPDOList[convertPDOIdx(mState)]->getDataType();
                QString Range = QString("%1to%2").arg(mPDOList[convertPDOIdx(mState)]->getRangeFrom()).arg(mPDOList[convertPDOIdx(mState)]->getRangeTo());
                pValveSP->setInterfaceConfigEthCATPDODataType(convertPDOIdx(mState), dataType,this);
                pValveSP->setInterfaceConfigEthCATPDORange(convertPDOIdx(mState), Range,this);
            }
        }
    }

private:
    int convertPDOIdx(int state)
    {
        if(mState >= STATE_READ_PDO_START && mState <= STATE_READ_PDO_END)
            return (int)state - (int)eState::STATE_READ_PDO_START;
        else if(mState >= STATE_WRITE_PDO_START && mState <= STATE_WRITE_PDO_END)
            return state - (int)eState::STATE_WRITE_PDO_START;

        return 0;
    }

    void setPDOItemDataType(int itemIdx, int dataType)
    {
        if(mIsWritten)
        {
            mPDOList[itemIdx]->setErrDataType(mPDOList[itemIdx]->getDataType() != dataType);

            if(mPDOList[itemIdx]->getDataType() != dataType)
                mPDOList[itemIdx]->setIsEdit(true);
        }
        else
        {
            //mPDOList[itemIdx]->setErrDataType(dataType != 0);

            //if(dataType != 0)
            //    mPDOList[itemIdx]->setIsEdit(true);
            //else
                mPDOList[itemIdx]->setIsEdit(false);

            mPDOList[itemIdx]->setDataType(dataType); // only supported unsigned integer
            mPDOList[itemIdx]->setIsEdit(false);
        }

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]after : " << mPDOList[itemIdx]->getIsEdit();
    }

    void setPDOItemRange(int itemIdx, QString from, QString to)
    {
        if(mIsWritten)
        {
            mPDOList[itemIdx]->setErrRangeFrom(qAbs(mPDOList[itemIdx]->getRangeFrom().toDouble() - from.toDouble()) >= 0.00001);//mPDOList[itemIdx]->getRangeFrom() != from);
            mPDOList[itemIdx]->setErrRangeTo(qAbs(mPDOList[itemIdx]->getRangeTo().toDouble() - to.toDouble()) >= 0.00001); //mPDOList[itemIdx]->getRangeTo() != to);

            if(mPDOList[itemIdx]->getErrRangeFrom() || mPDOList[itemIdx]->getErrRangeTo())
                mPDOList[itemIdx]->setIsEdit(true);
        }
        else
        {
            mPDOList[itemIdx]->setRangeFrom(from);
            mPDOList[itemIdx]->setRangeTo(to);
            mPDOList[itemIdx]->setIsEdit(false);
        }
    }

    QString getDataTypeString(int idx)
    {
        switch(mPDOList[idx]->getDataType())
        {
        case 0: return "DINT";
        case 1: return "REAL";
        }

        return "DINT";
    }
};
#endif // INTERFACESETUPPROFIBUSDLGMODEL_H
