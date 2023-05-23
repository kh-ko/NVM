#ifndef VALVEPARAMEXDLGMODEL_H
#define VALVEPARAMEXDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QFile>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/filewriterex.h"
#include "source/service/coreservice.h"

class ValveParamExItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsPresent READ getIsPresent NOTIFY signalEventChangedIsPresent)
    Q_PROPERTY(bool    mIsEdit    READ getIsEdit    NOTIFY signalEventChangedIsEdit   )
    Q_PROPERTY(bool    mIsErr     READ getIsErr     NOTIFY signalEventChangedIsErr    )
    Q_PROPERTY(QString mTextID    READ getTextID    NOTIFY signalEventChangedTextID   )
    Q_PROPERTY(QString mTextValue READ getTextValue NOTIFY signalEventChangedTextValue)
    Q_PROPERTY(QString mDesc      READ getDesc      NOTIFY signalEventChangedDesc     )

public:
    bool    mIsPresent = true ;
    bool    mIsEdit    = false;
    bool    mIsErr     = false;
    int     mId        = 0;
    // khko : edit int to qstring //int     mValue     = 0;
    QString mValue     = "";
    QString mDesc      = "";
    qint32  mIntValue  = 0;

    bool    getIsPresent(){ return mIsPresent; }
    bool    getIsEdit   (){ return mIsEdit   ; }
    bool    getIsErr    (){ return mIsErr    ; }
    QString getTextID   (){ return QString("%1").arg(mId, 2, 10, QChar('0'))   ; }
    // khko : edit int to qstring //QString getTextValue(){ return QString("%1").arg(mValue, 6, 10, QChar('0')); }
    QString getTextValue(){ return mValue    ; }
    QString getDesc     (){ return mDesc     ; }

    void    setIsPresent(bool    value){ if(mIsPresent == value) return; mIsPresent = value; emit signalEventChangedIsPresent(value         );}
    void    setIsEdit   (bool    value){ if(mIsEdit    == value) return; mIsEdit    = value; emit signalEventChangedIsEdit   (value         );}
    void    setIsErr    (bool    value){ if(mIsErr     == value) return; mIsErr     = value; emit signalEventChangedIsErr    (value         );}
    void    setId       (int     value){ if(mId        == value) return; mId        = value; emit signalEventChangedTextID   (getTextID()   );}
    // khko : edit int to qstring //void    setValue    (int    value){ if(mValue     == value) return; mValue     = value; emit signalEventChangedTextValue(getTextValue());}
    void    setValue    (QString value){ if(mValue     == value) return; mValue     = value; mIntValue = value.toInt(); emit signalEventChangedTextValue(getTextValue());}
    void    setValue    (qint32  value){setValue(QString("%1").arg(value)); }
    void    setDesc     (QString value){ if(mDesc      == value) return; mDesc      = value; emit signalEventChangedDesc     (value         );}
    void    reset()
    {
        setIsPresent(false); setIsEdit(false); setIsErr(false); setValue("0");
    }

public slots:
    Q_INVOKABLE void editValue(qint32 value)
    {
        setValue(QString("%1").arg(value));
        setIsEdit(true);
    }
signals:

    void signalEventChangedIsPresent(bool    value);
    void signalEventChangedIsEdit   (bool    value);
    void signalEventChangedIsErr    (bool    value);
    void signalEventChangedTextID   (QString value);
    void signalEventChangedTextValue(QString value);
    void signalEventChangedDesc     (QString value);

public:
    explicit ValveParamExItemModel(QObject *parent = nullptr): QObject(parent)
    {
    }

    explicit ValveParamExItemModel(int id, QObject *parent = nullptr): QObject(parent)
    {
        setId(id);
    }
    ~ValveParamExItemModel()
    {
    }

};

class ValveParamExDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode        READ getAccessMode       NOTIFY signalEventChangedAccessMode      )
    Q_PROPERTY(bool     mIsRS232Test       READ getIsRS232Test      NOTIFY signalEventChangedIsRS232Test     )
    Q_PROPERTY(bool     mIsEdit            READ getIsEdit           NOTIFY signalEventChangedIsEdit          )
    Q_PROPERTY(QString  mStrStatus         READ getStrStatus        NOTIFY signalEventChangedStrStatus       )
    Q_PROPERTY(QString  mErrMsg            READ getErrMsg           NOTIFY signalEventChangedErrMsg          )
    Q_PROPERTY(QString  mErrMsg2           READ getErrMsg2          NOTIFY signalEventChangedErrMsg2         )
    Q_PROPERTY(int      mProgress          READ getProgress         NOTIFY signalEventChangedProgress        )

public:
    int     mAccessMode        = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test       = false;
    bool    mIsEdit            = false;
    QString mStrStatus         = "Loading";
    QString mErrMsg            = "";
    QString mErrMsg2           = "";
    int     mProgress          = 0 ;

    int     getAccessMode       (){ return mAccessMode       ; }
    bool    getIsRS232Test      (){return mIsRS232Test       ; }
    bool    getIsEdit           (){ return mIsEdit           ; }
    QString getStrStatus        (){ return mStrStatus        ; }
    QString getErrMsg           (){ return mErrMsg           ; }
    QString getErrMsg2          (){ return mErrMsg2          ; }
    int     getProgress         (){ return mProgress         ; }

    void    setAccessMode       (int     value){ if(mAccessMode        == value)return; mAccessMode        = value; emit signalEventChangedAccessMode       (value);}
    void    setIsRS232Test      (bool    value){ if(mIsRS232Test       == value)return; mIsRS232Test       = value; emit signalEventChangedIsRS232Test      (value);}
    void    setIsEdit           (bool    value){ if(mIsEdit            == value)return; mIsEdit            = value; emit signalEventChangedIsEdit           (value);}
    void    setStrStatus        (QString value){ if(mStrStatus         == value)return; mStrStatus         = value; emit signalEventChangedStrStatus        (value);}
    void    setErrMsg           (QString value){ if(mErrMsg            == value)return; mErrMsg            = value; emit signalEventChangedErrMsg           (value);}
    void    setErrMsg2          (QString value){ if(mErrMsg2           == value)return; mErrMsg2           = value; emit signalEventChangedErrMsg2          (value);}
    void    setProgress         (int     value){ if(mProgress          == value)return; mProgress          = value; emit signalEventChangedProgress         (value);}

signals:
    void signalEventChangedAccessMode       (int     value);
    void signalEventChangedIsRS232Test      (bool    value);
    void signalEventChangedIsEdit           (bool    value);
    void signalEventChangedStrStatus        (QString value);
    void signalEventChangedErrMsg           (QString value);
    void signalEventChangedErrMsg2           (QString value);
    void signalEventChangedProgress         (int     value);
    void signalEventProcIdx                 (int     idx  );

public:
    explicit ValveParamExDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_VALVE_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_START;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_END;
        ENABLE_SLOT_VALVE_WRITTEN_FACTORY_RESET;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_RESET;

        pConfigSP->loadValveParams();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        for(int i = 0; i < 100; i ++)
        {
            ValveParamExItemModel * pItemModel = new ValveParamExItemModel(i, this);
            pItemModel->setDesc(pConfigSP->getValveParamDesc(i));
            connect(pItemModel, SIGNAL(signalEventChangedIsEdit(bool)), this, SLOT(onEditItem(bool)));
            mpParamList.append(pItemModel);
        }

        setState(eState::STATE_READY);
    }
    ~ValveParamExDlgModel()
    {
        if(mState <= STATE_WRITE_END && mState >= STATE_WRITE_START)
            pValveSP->setValveParamEnd(nullptr);

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

    void onEditItem(bool isEdit)
    {
        if(isEdit)
            setIsEdit(isEdit);
    }

    Q_INVOKABLE void onCommandReadFromController()
    {
        setState(eState::STATE_TOTAL_LOAD);
    }

    void onValveReadedValveParam(ValveResponseValveParamDto dto)
    {
        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_VALVE_PARAM).length(), 2).toInt();

        if(id != convertParamID(mState) || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }

        setErrMsg("");

        int tempValue;
        if(dto.mValue.contains("-"))
        {
            tempValue = dto.mValue.replace("-","0").toInt(nullptr, 16) * -1;
        }
        else
        {
            tempValue = dto.mValue.toInt(nullptr, 16);
        }

        setParamByController(dto.mIsSucc, id, tempValue);

        emit signalEventProcIdx(convertParamID(mState));

        setState(mState + 1);
    }


    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandWriteToController(bool isReboot = false)
    {
        mRebootCheck = isReboot;
        setState(eState::STATE_WRITE_START);
    }

    void onValveWrittenValveParamStart(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_START || dto.mReqDto.mpRef != this)
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

    void onValveWrittenValveParam(ValveResponseDto dto)
    {
        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_VALVE_PARAM).length(), 2).toInt();

        if(id != convertParamID(mState) || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        emit signalEventProcIdx(convertParamID(mState));

        setState((eState)(mState + 1));
    }

    void onValveWrittenValveParamEnd(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_END || dto.mReqDto.mpRef != this)
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

        if(mRebootCheck)
        {
            mRebootCheck = false;
            setState(STATE_WRITE_REBOOT);
        }
        else
        {
            setState(mState + 1);
        }
    }


    Q_INVOKABLE void onCommandWriteFactoryReset()
    {
        setErrMsg2("");
        setState(eState::STATE_WRITE_FR);
    }

    void onValveWrittenFactoryReset(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_FR || dto.mReqDto.mpRef != this)
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

        setState(STATE_TOTAL_LOAD);
    }

    Q_INVOKABLE void onCommandWriteParamReset(bool isReboot = false)
    {
        mRebootCheck = isReboot;
        setErrMsg2("");
        setState(eState::STATE_WRITE_PARAM_RESET);
    }

    void onValveWrittenValveParamReset(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_PARAM_RESET || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][onValveWrittenValveParamReset]" << dto.mResData << ", isSucc = " << dto.mIsSucc;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        if(mRebootCheck)
        {
            mRebootCheck = false;
            setState(STATE_WRITE_REBOOT);
        }
        else
        {
            setState(STATE_TOTAL_LOAD);
        }
    }

    Q_INVOKABLE void onCommandReadFromFile(QString filePath)
    {
        QFile file;
        file.setFileName(filePath);
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            setErrMsg("File open failed!");
            return;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");

        do{
            QString value = out.readLine();
            int id = value.mid(0,2).toInt();
            int tempValue;
            value = value.mid(2,value.length() - 2);

            if(id < 100)
            {
                if(value.contains("-"))
                {
                    tempValue = value.replace("-","0").toInt(nullptr, 16) * -1;
                }
                else
                {
                    tempValue = value.toInt(nullptr, 16);
                }
                setParamByFile(true, id, tempValue);
            }

            emit signalEventProcIdx(id);

        }while(!out.atEnd());

        file.close();
    }

    Q_INVOKABLE void onCommandWriteToFile(QString filePath)
    {
        FileWriterEx file;
        int splitIdx = filePath.lastIndexOf("/")+1;
        QString dir = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        //setState(eState::STATE_WRITE_START, true);

        setErrMsg2("");

        if(file.open(dir, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            setErrMsg2("File open failed!");
            return;
        }

        for(int i = 0; i < mpParamList.count(); i ++)
        {
            if(mpParamList[i]->getIsPresent() && mpParamList[i]->getTextValue().length() > 0)
            {
                if(mpParamList[i]->mIntValue < 0)
                {
                    file.appendLine(QString("%1-%2").arg(mpParamList[i]->getTextID()).arg(QString("%1").arg(mpParamList[i]->mIntValue * -1, 5, 16, QChar('0'))));
                }
                else
                {
                    file.appendLine(QString("%1%2").arg(mpParamList[i]->getTextID()).arg(QString("%1").arg(mpParamList[i]->mIntValue, 6, 16, QChar('0'))));
                }
                emit signalEventProcIdx(i);
            }
        }

        file.close();
        return;
    }


    Q_INVOKABLE ValveParamExItemModel * onCommandGetParamItem(int idx)
    {
        if(idx >= mpParamList.count())
            return &mDummyParamItem;

        return mpParamList[idx];
    }

    Q_INVOKABLE int onCommandItemCount()
    {
        return 100;
    }

private:
    bool                            mRebootCheck = false;
    QList<ValveParamExItemModel *>  mpParamList;
    ValveParamExItemModel           mDummyParamItem;

private:
    enum eState{
        STATE_WRITE_REBOOT          = 0,
        STATE_WRITE_REBOOT_WAIT     = STATE_WRITE_REBOOT      + 1,
        STATE_WRITE_FR              = STATE_WRITE_REBOOT_WAIT + 1,
        STATE_WRITE_PARAM_RESET     = STATE_WRITE_FR          + 1,
        STATE_WRITE_START           = STATE_WRITE_PARAM_RESET + 1,
        STATE_WRITE                 = STATE_WRITE_START       + 1,
        // ...00 ~ 99 STATE_WRITE_ING
        STATE_WRITE_END             = STATE_WRITE             + 100,
        STATE_LOAD_ONLY_WRITTEN     = STATE_WRITE_END         + 1,
        // ... 00 ~ 99 STATE_LOAD_ING  =  1,
        STATE_READY                 = STATE_LOAD_ONLY_WRITTEN + 100,
        STATE_TOTAL_LOAD            = STATE_READY             + 1,
        STATE_TOTAL_LOAD_END        = STATE_TOTAL_LOAD        + 100,
    };

    QTimer mTimer;
    int    mState         = eState::STATE_READY;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(int state, bool doNotTimer = false)
    {
        int progress = 0;
        QString strStatus;

        mState = state == STATE_TOTAL_LOAD_END ? STATE_READY : state;

        if(mState >= STATE_LOAD_ONLY_WRITTEN && mState < STATE_READY)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "loading";
        }
        else if(mState >= STATE_TOTAL_LOAD && mState < STATE_TOTAL_LOAD_END)
        {
            progress = ((mState) * 100) / STATE_TOTAL_LOAD_END;
            strStatus = "loading";
        }
        else if(mState == STATE_READY)
        {
            progress = 100;
            strStatus = "ready";
        }
        else if(mState == STATE_WRITE_FR)
        {
            progress = 50;
            strStatus = "factory reset";
        }
        else if(mState == STATE_WRITE_PARAM_RESET)
        {
            progress = 50;
            strStatus = "param reset";
        }
        else
        {
            progress = ((mState) * 100) / STATE_WRITE_END;
            strStatus = "writting";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        if(mState == STATE_TOTAL_LOAD)
        {
            setIsEdit(false);
            setErrMsg("");

            for(int i = 0; i < 100; i ++)
            {
                mpParamList[i]->reset();
            }
        }
        else if(mState == STATE_WRITE_START)
        {
            setIsEdit(false);
            setErrMsg2("");
        }
        else if(mState == STATE_READY)
        {
            for(int i = 0; i < 100; i ++)
            {
                if(mpParamList[i]->getIsErr())
                {
                    setIsEdit(true);
                }
            }
        }

        if(!doNotTimer)
            startTimer();
    }

public slots:
    void onTimeout()
    {
        if(mState >= STATE_LOAD_ONLY_WRITTEN && mState < STATE_READY)
        {
            for(;mState < STATE_READY; mState++)
            {
                if(mpParamList[convertParamID(mState)]->getIsEdit())
                {
                    pValveSP->readValveParam(convertParamID(mState), this);
                    return;
                }
            }

            setState(STATE_READY);
        }
        if(mState >= STATE_TOTAL_LOAD && mState < STATE_TOTAL_LOAD_END)
        {
            pValveSP->readValveParam(convertParamID(mState), this);
        }
        else if(mState == STATE_WRITE_START)
        {
            pValveSP->setValveParamStart(this);
        }
        else if(mState >= STATE_WRITE && mState <STATE_WRITE_END)
        {
            for(;mState < STATE_WRITE_END; mState++)
            {
                if(mpParamList[convertParamID(mState)]->getIsPresent() && mpParamList[convertParamID(mState)]->getIsEdit())
                {
                    if(mpParamList[convertParamID(mState)]->mIntValue < 0)
                    {
                        pValveSP->setValveParam(convertParamID(mState), QString("-%1").arg(mpParamList[convertParamID(mState)]->mIntValue * -1, 5, 16, QChar('0')) , this);
                    }
                    else
                    {
                        pValveSP->setValveParam(convertParamID(mState), QString("%1").arg(mpParamList[convertParamID(mState)]->mIntValue, 6, 16, QChar('0')) , this);
                    }

                    return;
                }
            }
            setState(STATE_WRITE_END);
        }
        else if(mState == STATE_WRITE_END)
        {
            pValveSP->setValveParamEnd(this);
        }
        else if(mState == STATE_WRITE_FR)
        {
            pValveSP->factoryReset(this);
        }
        else if(mState == STATE_WRITE_PARAM_RESET)
        {
            pValveSP->valveParamReset(this);
        }
    }

private:
    int convertParamID(int state)
    {
        if(state < eState::STATE_WRITE_END)
            return (int)state - (int)eState::STATE_WRITE;
        else if(state < eState::STATE_READY)
            return state - (int)eState::STATE_LOAD_ONLY_WRITTEN;
        else if(state < eState::STATE_TOTAL_LOAD_END)
            return state - (int)eState::STATE_TOTAL_LOAD;

        return 0;
    }

    void setParamByController(bool isPresent, int paramID, qint32 paramValue)
    {
        mpParamList[paramID]->setIsPresent(isPresent);
        //mpParamList[paramID]->setValue(isPresent ? paramValue : "000000");
        mpParamList[paramID]->setValue(isPresent ? paramValue : 0);

        mpParamList[paramID]->setIsErr(mpParamList[paramID]->getIsEdit() && mpParamList[paramID]->mIntValue != paramValue && isPresent);

        mpParamList[paramID]->setIsEdit(false);
    }

    void setParamByFile(bool isPresent, int paramID, qint32 paramValue)
    {
        if( mpParamList[paramID]->getIsPresent() == false)
            return;

        mpParamList[paramID]->setValue(isPresent ? paramValue : 0);
        mpParamList[paramID]->setIsErr(false);
        mpParamList[paramID]->setIsEdit(true);
    }
};
#endif // VALVEPARAMEXDLGMODEL_H
