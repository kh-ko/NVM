#ifndef VALVEPARAMPMDLGMODEL_H
#define VALVEPARAMPMDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QFile>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/filewriterex.h"
#include "source/service/coreservice.h"

class ValveParamPMItemModel : public QObject
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

    Q_INVOKABLE void setEmptyValue()
    {
        setValue("");
        setIsEdit(false);
    }

signals:

    void signalEventChangedIsPresent(bool    value);
    void signalEventChangedIsEdit   (bool    value);
    void signalEventChangedIsErr    (bool    value);
    void signalEventChangedTextID   (QString value);
    void signalEventChangedTextValue(QString value);
    void signalEventChangedDesc     (QString value);

public:
    explicit ValveParamPMItemModel(QObject *parent = nullptr): QObject(parent)
    {
    }

    explicit ValveParamPMItemModel(int id, QObject *parent = nullptr): QObject(parent)
    {
        setId(id);
    }
    ~ValveParamPMItemModel()
    {
    }

};

class ValveParamPMDlgModel : public QObject
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
    void signalEventChangedErrMsg2          (QString value);
    void signalEventChangedProgress         (int     value);
    void signalEventProcIdx                 (int     idx  );
    void signalEventUnknowFormat            (             );

public:
    explicit ValveParamPMDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;
        ENABLE_SLOT_VALVE_WRITTEN_FACTORY_RESET;
        ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_RESET;

        pConfigSP->loadValveParams();
        setStateValue();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        for(int i = 0; i < pConfigSP->getValveParamDescCount(); i ++)
        {
            ValveParamPMItemModel * pItemModel = new ValveParamPMItemModel(i, this);
            pItemModel->setDesc(pConfigSP->getValveParamDesc(i));
            connect(pItemModel, SIGNAL(signalEventChangedIsEdit(bool)), this, SLOT(onEditItem(bool)));
            mpParamList.append(pItemModel);
        }

        setState(STATE_READY);
    }
    ~ValveParamPMDlgModel()
    {
        //if(mState <= STATE_WRITE_END && mState >= STATE_WRITE_START)
        //    pValveSP->setValveParamEnd(nullptr);

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
        setState(STATE_TOTAL_LOAD);
    }

    void onValveWrittenCustomRequest(ValveResponseDto dto){

        if(dto.mIsNetworkErr || (dto.mResData.startsWith("p:00") == false && dto.mReqDto.mReqCommand.startsWith("p:01")))
        {
            setErrMsg("receive protocol error");
            setState(mState);
            return;
        }

        if(dto.mReqDto.mReqCommand.startsWith("p:0B"))
        {
            onValveReadedValveParam(dto);
        }
        else if(dto.mReqDto.mReqCommand.startsWith("p:01"))
        {
            onValveWrittenValveParam(dto);
        }
    }

    void onValveReadedValveParam(ValveResponseDto dto)
    {
        int id    = dto.mReqDto.mReqCommand.mid(QString("p:01B0000100").length(), 2).toInt(nullptr, 16);

        if(id != convertParamID(mState) || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[" << Q_FUNC_INFO << "]" << dto.mReqDto.mReqCommand << ", res = " << dto.mResData;

        setErrMsg("");


        if(dto.mResData.startsWith("p:00") == false)
        {
            setParamByController(false, id, 0);
        }
        else
        {
            int value = dto.mResData.mid(QString("p:0001B000010000").length()).toInt();
            setParamByController(dto.mIsSucc, id, value);
        }
        emit signalEventProcIdx(convertParamID(mState));
        setState(mState + 1);
    }


    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandWriteToController(bool isReboot = false)
    {
        //mRebootCheck = isReboot;
        setState(STATE_WRITE);
    }

    void onValveWrittenValveParam(ValveResponseDto dto)
    {
        int id    = dto.mResData.mid(QString("p:000BB0000100").length(), 2).toInt(nullptr, 16);

        if(id != convertParamID(mState) || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[" << Q_FUNC_INFO << "]" << dto.mReqDto.mReqCommand << ", res = " << dto.mResData;

        if(id != convertParamID(mState) || dto.mReqDto.mpRef != this)
            return;

        emit signalEventProcIdx(convertParamID(mState));

        setState(mState + 1);
    }

    Q_INVOKABLE void onCommandWriteFactoryReset()
    {
        setErrMsg2("");
        setState(STATE_WRITE_FR);
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
        setState(STATE_WRITE_PARAM_RESET);
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
            bool idok;
            bool valueok;
            QString value = out.readLine();
            int id       = value.mid(0,2).toInt(&idok, 16);
            int intValue = value.mid(2).toInt(&valueok, 10);

            if(idok == false || valueok == false || id == 0)
            {
                file.close();
                emit signalEventUnknowFormat();
                return;
            }

            if(id < pConfigSP->getValveParamDescCount())
            {
                setParamByFile(true, id, intValue);
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
            // id 부분은 백업에서 제외 + pos offset도 제외 : 20241210 - 김부장님 요청사항
            if(i < 17 || i == 51)
                continue;

            if(mpParamList[i]->getIsPresent() && mpParamList[i]->getTextValue().length() > 0)
            {
                file.appendLine(QString("%1%2").arg(i, 2, 16, QChar('0')).arg(mpParamList[i]->mIntValue));
                emit signalEventProcIdx(i);
            }
        }

        file.close();
        return;
    }


    Q_INVOKABLE ValveParamPMItemModel * onCommandGetParamItem(int idx)
    {
        if(idx >= mpParamList.count())
        {
            if(mpDummyParamItem == nullptr)
                mpDummyParamItem = new ValveParamPMItemModel(this);
            return mpDummyParamItem;
        }

        return mpParamList[idx];
    }

    Q_INVOKABLE int onCommandItemCount()
    {
        return mpParamList.count();
    }

private:
    bool                            mRebootCheck = false;
    QList<ValveParamPMItemModel *>  mpParamList;
    ValveParamPMItemModel *         mpDummyParamItem = nullptr;

private:
    int STATE_WRITE_REBOOT          = 0;
    int STATE_WRITE_REBOOT_WAIT     = STATE_WRITE_REBOOT      + 1;
    int STATE_WRITE_FR              = STATE_WRITE_REBOOT_WAIT + 1;
    int STATE_WRITE_PARAM_RESET     = STATE_WRITE_FR          + 1;
    int STATE_WRITE                 = STATE_WRITE_PARAM_RESET + 1;
    int STATE_LOAD_ONLY_WRITTEN     = STATE_WRITE             + 1;
    int STATE_READY                 = STATE_LOAD_ONLY_WRITTEN + 100;
    int STATE_TOTAL_LOAD            = STATE_READY             + 1;
    int STATE_TOTAL_LOAD_END        = STATE_TOTAL_LOAD        + 100;

    QTimer mTimer;
    int    mState = STATE_READY;

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
            progress = ((mState) * 100) / (STATE_LOAD_ONLY_WRITTEN - 1);
            strStatus = "writting";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        if(mState == STATE_TOTAL_LOAD)
        {
            setIsEdit(false);
            setErrMsg("");

            for(int i = 0; i < mpParamList.count(); i ++)
            {
                mpParamList[i]->reset();
            }
        }
        else if(mState == STATE_WRITE)
        {
            setIsEdit(false);
            setErrMsg2("");
        }
        else if(mState == STATE_READY)
        {
            pValveSP->printSettingsAboutPressureCtrl();
            for(int i = 0; i < mpParamList.count(); i ++)
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
                    pValveSP->customRequest( QString("p:0BB0000100%1").arg(convertParamID(mState), 2, 16, QChar('0')), this);
                    return;
                }
            }

            setState(STATE_READY);
        }
        if(mState >= STATE_TOTAL_LOAD && mState < STATE_TOTAL_LOAD_END)
        {
            pValveSP->customRequest( QString("p:0BB0000100%1").arg(convertParamID(mState), 2, 16, QChar('0')), this);
        }
        else if(mState >= STATE_WRITE && mState < STATE_LOAD_ONLY_WRITTEN)
        {
            for(;mState < STATE_LOAD_ONLY_WRITTEN; mState++)
            {
                if(mpParamList[convertParamID(mState)]->getIsPresent() && mpParamList[convertParamID(mState)]->getIsEdit())
                {
                    pValveSP->customRequest( QString("p:01B0000100%1%2").arg(convertParamID(mState), 2, 16, QChar('0')).arg(mpParamList[convertParamID(mState)]->mIntValue), this);
                    return;
                }
            }
            setState(STATE_LOAD_ONLY_WRITTEN);
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
        if(state < STATE_LOAD_ONLY_WRITTEN)
            return state - STATE_WRITE;
        else if(state < STATE_READY)
            return state - STATE_LOAD_ONLY_WRITTEN;
        else if(state < STATE_TOTAL_LOAD_END)
            return state - STATE_TOTAL_LOAD;

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

    void setStateValue()
    {
        STATE_WRITE_REBOOT          = 0;
        STATE_WRITE_REBOOT_WAIT     = STATE_WRITE_REBOOT      + 1;
        STATE_WRITE_FR              = STATE_WRITE_REBOOT_WAIT + 1;
        STATE_WRITE_PARAM_RESET     = STATE_WRITE_FR          + 1;
        STATE_WRITE                 = STATE_WRITE_PARAM_RESET + 1;
        STATE_LOAD_ONLY_WRITTEN     = STATE_WRITE             + pConfigSP->getValveParamDescCount();
        STATE_READY                 = STATE_LOAD_ONLY_WRITTEN + pConfigSP->getValveParamDescCount();
        STATE_TOTAL_LOAD            = STATE_READY             + 1;
        STATE_TOTAL_LOAD_END        = STATE_TOTAL_LOAD        + pConfigSP->getValveParamDescCount();
    }
};
#endif // VALVEPARAMPMDLGMODEL_H
