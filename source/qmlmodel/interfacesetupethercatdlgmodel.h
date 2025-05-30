#ifndef INTERFACESETUPETHERCATDLGMODEL_H
#define INTERFACESETUPETHERCATDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

class InterfaceSetupEthCATItemModel : public QObject
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

    explicit InterfaceSetupEthCATItemModel(QObject *parent = nullptr): QObject(parent)
    {
    }

    ~InterfaceSetupEthCATItemModel()
    {
    }

};

class InterfaceSetupEtherCATDlgModel : public QObject
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
    Q_PROPERTY(int      mDevID               READ getDevID               NOTIFY signalEventChangedDevID            )

    Q_PROPERTY(bool     mErrDIFunction       READ getErrDIFunction       NOTIFY signalEventChangedErrDIFunction    )
    Q_PROPERTY(bool     mErrDIMode           READ getErrDIMode           NOTIFY signalEventChangedErrDIMode        )
    Q_PROPERTY(bool     mErrDIInput          READ getErrDIInput          NOTIFY signalEventChangedErrDIInput       )
    Q_PROPERTY(bool     mErrDOFunction       READ getErrDOFunction       NOTIFY signalEventChangedErrDOFunction    )
    Q_PROPERTY(bool     mErrDOMode           READ getErrDOMode           NOTIFY signalEventChangedErrDOMode        )
    Q_PROPERTY(bool     mErrDOOutput         READ getErrDOOutput         NOTIFY signalEventChangedErrDOOutput      )
    Q_PROPERTY(bool     mErrDevID            READ getErrDevID            NOTIFY signalEventChangedErrDevID         )

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
    int      mDevID                   = 0;

    bool     mErrDIFunction           = 0;
    bool     mErrDIMode               = 0;
    bool     mErrDIInput              = 0;
    bool     mErrDOFunction           = 0;
    bool     mErrDOMode               = 0;
    bool     mErrDOOutput             = 0;
    bool     mErrDevID                = 0;

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
    int     getDevID                  (){ return mDevID                  ;}

    bool    getErrDIFunction          (){ return mErrDIFunction          ;}
    bool    getErrDIMode              (){ return mErrDIMode              ;}
    bool    getErrDIInput             (){ return mErrDIInput             ;}
    bool    getErrDOFunction          (){ return mErrDOFunction          ;}
    bool    getErrDOMode              (){ return mErrDOMode              ;}
    bool    getErrDOOutput            (){ return mErrDOOutput            ;}
    bool    getErrDevID               (){ return mErrDevID               ;}

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
    void    setDevID                  (int     value){ if(mDevID                   == value)return; mDevID                   = value; emit signalEventChangedDevID                  (value);}

    void    setErrDIFunction          (bool    value){ if(mErrDIFunction           == value)return; mErrDIFunction           = value; emit signalEventChangedErrDIFunction          (value);}
    void    setErrDIMode              (bool    value){ if(mErrDIMode               == value)return; mErrDIMode               = value; emit signalEventChangedErrDIMode              (value);}
    void    setErrDIInput             (bool    value){ if(mErrDIInput              == value)return; mErrDIInput              = value; emit signalEventChangedErrDIInput             (value);}
    void    setErrDOFunction          (bool    value){ if(mErrDOFunction           == value)return; mErrDOFunction           = value; emit signalEventChangedErrDOFunction          (value);}
    void    setErrDOMode              (bool    value){ if(mErrDOMode               == value)return; mErrDOMode               = value; emit signalEventChangedErrDOMode              (value);}
    void    setErrDOOutput            (bool    value){ if(mErrDOOutput             == value)return; mErrDOOutput             = value; emit signalEventChangedErrDOOutput            (value);}
    void    setErrDevID               (bool    value){ if(mErrDevID                == value)return; mErrDevID                = value; emit signalEventChangedErrDevID               (value);}

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
    void signalEventChangedDevID                  (int     value);

    void signalEventChangedErrDIFunction          (bool    value);
    void signalEventChangedErrDIMode              (bool    value);
    void signalEventChangedErrDIInput             (bool    value);
    void signalEventChangedErrDOFunction          (bool    value);
    void signalEventChangedErrDOMode              (bool    value);
    void signalEventChangedErrDOOutput            (bool    value);
    void signalEventChangedErrDevID               (bool    value);

    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );

public:
    explicit InterfaceSetupEtherCATDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DI;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DO;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_ETHCAT_DI;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_ETHCAT_DO;
        ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_DEV_ID;
        ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_DATA_TYPE;
        ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_RANGE;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_DEV_ID;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_DATA_TYPE;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_RANGE;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        for(int i = 0; i < 100; i ++)
        {
            InterfaceSetupEthCATItemModel * pItemModel = new InterfaceSetupEthCATItemModel(this);
            connect(pItemModel, SIGNAL(signalEventChangedIsEdit(bool)), this, SLOT(onEditItem(bool)));
            mPDOList.append(pItemModel);
        }

        setState(eState::STATE_READ_DI);
    }
    ~InterfaceSetupEtherCATDlgModel()
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
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

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

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

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

    void onValveReadedInterfaceCfgEthCATDevID(ValveResponseInterfaceConfigEthCATDevIDDto dto)
    {
        if(mState != eState::STATE_READ_DEV_ID || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]";

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setDevID (dto.mDevID);

        mReadedDevID = dto.mDevID;

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

    Q_INVOKABLE InterfaceSetupEthCATItemModel * onCommandGetPDOItem(int idx)
    {
        if(idx >= mPDOList.count())
            return &mDummyPDOItem;

        return mPDOList[idx];
    }

    Q_INVOKABLE int onCommandGetPDOItemCount()
    {
        return mPDOList.count();
    }

    Q_INVOKABLE void onCommandExportXML(QString filePath)
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

        contents = createXMLContents();

        foreach(QString line, contents)
        {
            file.appendLine(line);
        }

        file.close();
        return;
    }

    Q_INVOKABLE void onCommandApply(int diFunction, int diMode, int diInput, int doFunction, int doMode, int doOutput,int devID)
    {
        mIsWritten       = true      ;
        mWriteDIFunction = diFunction;
        mWriteDIMode     = diMode    ;
        mWriteDIInput    = diInput   ;
        mWriteDOFunction = doFunction;
        mWriteDOMode     = doMode    ;
        mWriteDOOutput   = doOutput  ;
        mWriteDevID      = devID     ;

        setIsEdit(false);
//        foreach(InterfaceSetupEthCATItemModel * pItem, mPDOList)
//        {
//            pItem->setIsEdit(false);
//        }

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

    void onValveWrittenInterfaceCfgEthCATDevID(ValveResponseDto dto)
    {
        //if(mState != STATE_WRITE_DEV_ID || dto.mReqDto.mpRef != this)
        //    return;

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
    QList<InterfaceSetupEthCATItemModel *>  mPDOList;
    InterfaceSetupEthCATItemModel           mDummyPDOItem;

private:
    enum eState{
        STATE_WRITE_DI        =  0,
        STATE_WRITE_DO        = STATE_WRITE_DI        + 1,
        //STATE_WRITE_DEV_ID    = STATE_WRITE_DO        + 1,
        STATE_WRITE_PDO_START = STATE_WRITE_DO    + 1,
        STATE_WRITE_PDO_END   = STATE_WRITE_PDO_START + 11,
        STATE_READ_DI         = STATE_WRITE_PDO_END   + 1,
        STATE_READ_DO         = STATE_READ_DI         +1,
        STATE_READ_DEV_ID     = STATE_READ_DO         + 1,
        STATE_READ_PDO_START  = STATE_READ_DEV_ID     + 1,
        STATE_READ_PDO_END    = STATE_READ_PDO_START  + 11,
        STATE_READY           = STATE_READ_PDO_END    + 1
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
    int  mWriteDevID       = 0;

    int  mReadedDIFunction = 0;
    int  mReadedDIMode     = 0;
    int  mReadedDIInput    = 0;
    int  mReadedDOFunction = 0;
    int  mReadedDOMode     = 0;
    int  mReadedDOOutput   = 0;
    int  mReadedDevID      = 0;

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
//            foreach(InterfaceSetupEthCATItemModel * pItem, mPDOList)
//            {
//                pItem->setIsEdit(false);
//            }
//            onCommandSetEdit(false);

            emit signalEventCompletedLoad();
        }

        if(mState == STATE_READ_PDO_END)
        {
            bool isPDOErr = false;
            foreach(InterfaceSetupEthCATItemModel * pItem, mPDOList)
            {
                if(pItem->getErrDataType() || pItem->getErrRangeFrom() || pItem->getErrRangeTo())
                    isPDOErr = true;
            }
            onCommandSetEdit(isPDOErr || getErrDIFunction() || getErrDIMode() || getErrDIInput() || getErrDOFunction() || getErrDOMode() || getErrDOOutput() || getErrDevID());
        }

        if(mState >= STATE_READ_DI && mState <= STATE_READ_PDO_END)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "loading";
        }
        else if(mState >= STATE_WRITE_DI && mState <= STATE_WRITE_PDO_END)
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

        case (int)eState::STATE_READ_DEV_ID:
            if(   mReadedDevID == mWriteDevID && mErrDevID == false && mIsWritten)
            {
                setState((eState)(mState + 1), true);
                return;
            }
            pValveSP->readInterfaceConfigEthCATDevID(this);
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

        //case (int)eState::STATE_WRITE_DEV_ID:
        //    pValveSP->setInterfaceConfigEthCATDevID(mWriteDevID, this);
        //    break;

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

    QStringList createXMLContents()
    {
        QStringList contents;
        QFile file;

        file.setFileName(QString("%1/ref_sample/ethercat_sample.XML").arg(QApplication::applicationDirPath()));
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

            if     (line.contains("<Name>Pressure</Name>"                               )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 0))); }
            else if(line.contains("<Name>Pressure sensor 1</Name>"                      )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 1))); }
            else if(line.contains("<Name>Pressure sensor 2</Name>"                      )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 2))); }
            else if(line.contains("<Name>Position</Name>"                               )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 3))); }
            else if(line.contains("<Name>Target position</Name>"                        )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 4))); }
            else if(line.contains("<Name>Cluster valve position</Name>"                 )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 5))); }
            else if(line.contains("<Name>Pressure setpoint</Name>"                      )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 6))); }
            else if(line.contains("<Name>Position setpoint</Name>"                      )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 7))); }
            else if(line.contains("<Name>Pressure alignment setpoint</Name>"            )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 8))); }
            else if(line.contains("<Name>External digital pressure sensor 1</Name>"     )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString( 9))); }
            else if(line.contains("<Name>External digital pressure sensor 2</Name>"     )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString(10))); }
            else if(line.contains("<Name>Cluster valve freeze position setpoint</Name>" )){contents.append(line); line = out.readLine(); contents.append(QString(line).arg(getDataTypeString(11))); }
            else
            {
                contents.append(line);
            }
        }while(!out.atEnd());

        file.close();
        return contents;
    }

};
#endif // INTERFACESETUPETHERCATDLGMODEL_H
