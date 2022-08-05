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

public:
    bool    mIsWritten = false;
    bool    mIsPresent = false;
    bool    mIsEdit    = false;
    bool    mIsErr     = false;
    int     mId        = 0;
    // khko : edit int to qstring //int     mValue     = 0;
    QString mValue     = "000000";

    bool    getIsWritten(){ return mIsWritten; }
    bool    getIsPresent(){ return mIsPresent; }
    bool    getIsEdit   (){ return mIsEdit   ; }
    bool    getIsErr    (){ return mIsErr    ; }
    QString getTextID   (){ return QString("%1").arg(mId, 2, 10, QChar('0'))   ; }
    // khko : edit int to qstring //QString getTextValue(){ return QString("%1").arg(mValue, 6, 10, QChar('0')); }
    QString getTextValue(){ return mValue    ; }

    void    setIsWritten(bool    value){ if(mIsWritten == value) return; mIsWritten = value;/*emit signalEventChangedIsWritten(value      );*/}
    void    setIsPresent(bool    value){ if(mIsPresent == value) return; mIsPresent = value; emit signalEventChangedIsPresent(value         );}
    void    setIsEdit   (bool    value){ if(mIsEdit    == value) return; mIsEdit    = value; emit signalEventChangedIsEdit   (value         );}
    void    setIsErr    (bool    value){ if(mIsErr     == value) return; mIsErr     = value; emit signalEventChangedIsErr    (value         );}
    void    setId       (int     value){ if(mId        == value) return; mId        = value; emit signalEventChangedTextID   (getTextID()   );}
    // khko : edit int to qstring //void    setValue    (int    value){ if(mValue     == value) return; mValue     = value; emit signalEventChangedTextValue(getTextValue());}
    void    setValue    (QString value){ if(mValue     == value) return; mValue     = value; emit signalEventChangedTextValue(getTextValue());}

    void    reset()
    {
        setIsPresent(false); setIsEdit(false); setIsErr(false); setValue("000000"); setIsWritten(false);
    }

public slots:
//    Q_INVOKABLE void editValue(int value)
//    {
//        setValue(QString("%1").arg(value, 6, 16, QChar('0'))); // khko : edit int to qstring
//        setIsEdit(true);
//    }
    Q_INVOKABLE void editValue(quint32 value)
    {
        setValue(QString("%1").arg(value, 6, 16, QChar('0')).toUpper()); // khko : edit int to qstring
        setIsEdit(true);
    }
signals:
    void signalEventChangedIsPresent(bool    value);
    void signalEventChangedIsEdit   (bool    value);
    void signalEventChangedIsErr    (bool    value);
    void signalEventChangedTextID   (QString value);
    void signalEventChangedTextValue(QString value);

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

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        for(int i = 0; i < 100; i ++)
        {
            ValveParamExItemModel * pItemModel = new ValveParamExItemModel(i, this);
            connect(pItemModel, SIGNAL(signalEventChangedIsEdit(bool)), this, SLOT(onEditItem(bool)));
            mpParamList.append(pItemModel);
        }

        setState(eState::STATE_LOAD);
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
        // reset
        setState(eState::STATE_LOAD);
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

        setParam(dto.mIsSucc, id, dto.mValue);

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
        //mIsWritten = true;
        // setErrMsg2
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

        setState(STATE_LOAD);
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
            setState(STATE_LOAD);
        }
    }

    Q_INVOKABLE void onCommandReadFromFile(QString filePath)
    {
        QFile file;
        file.setFileName(filePath);
        file.open(QFile::ReadOnly);

        setState(eState::STATE_LOAD, true);

        if(file.isOpen() == false)
        {
            setErrMsg("File open failed!");
            setState(eState::STATE_READY, true);
            return;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");

        do{
            QString value = out.readLine();
            int id = value.mid(0,2).toInt();

            if(id < 100)
            {
                setParam(true, id, value.mid(2,value.length() - 2), true);
            }

            emit signalEventProcIdx(id);

        }while(!out.atEnd());

        file.close();
        setState(eState::STATE_READY, true);
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
            //setState(eState::STATE_READY, true);
            return;
        }

        for(int i = 0; i < mpParamList.count(); i ++)
        {
            if(mpParamList[i]->getIsPresent())
            {
                file.appendLine(QString("%1%2").arg(mpParamList[i]->getTextID()).arg(mpParamList[i]->getTextValue()));
                emit signalEventProcIdx(i);
            }
        }

        //setState(eState::STATE_READY, true);
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
        STATE_RE_LOAD               = STATE_WRITE_END         + 1,
        // ... 00 ~ 99 STATE_LOAD_ING  =  1,
        STATE_READY                 = STATE_RE_LOAD           + 100,
        STATE_LOAD                  = STATE_READY             + 1,
        // ... 00 ~ 99 STATE_LOAD_ING  =  1,
        STATE_OVER                  = STATE_LOAD              + 100
    };

    QTimer mTimer;
    int    mState         = eState::STATE_LOAD;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(int state, bool doNotTimer = false)
    {
        int progress = 0;
        QString strStatus;

        mState = state == STATE_OVER ? STATE_READY : state;

        if(mState >= STATE_RE_LOAD && mState < STATE_READY)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "loading";
        }
        else if(mState >= STATE_LOAD && mState < STATE_OVER)
        {
            progress = ((mState) * 100) / STATE_OVER;
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

        if(mState == STATE_LOAD)
        {
            setIsEdit(false);
            setErrMsg("");

            for(int i = 0; i < 100; i ++)
            {
                mpParamList[i]->reset();
            }
        }
        else if(mState == STATE_RE_LOAD)
        {

        }
        else if(mState == STATE_WRITE_START)
        {
            setIsEdit(false);
            setErrMsg2("");

//          for(int i = 0; i < 100; i ++)
//          {
//              mpParamList[i]->setIsEdit(false);
//          }
        }
        else if(mState == STATE_READY)
        {
            for(int i = 0; i < 100; i ++)
            {
                if(mpParamList[i]->getIsErr())
                {
                    setIsEdit(true);
                }

                mpParamList[i]->setIsWritten(false);
            }
        }

        if(!doNotTimer)
            startTimer();
    }

public slots:
    void onTimeout()
    {
        if(mState >= STATE_LOAD && mState < STATE_OVER)
        {
            pValveSP->readValveParam(convertParamID(mState), this);
        }
        else if(mState >= STATE_RE_LOAD && mState < STATE_READY)
        {
            for(;mState < STATE_READY; mState++)
            {
                if(mpParamList[convertParamID(mState)]->getIsWritten())
                {
                    pValveSP->readValveParam(convertParamID(mState), this);
                    return;
                }
            }

            setState(STATE_READY);
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
                    mpParamList[convertParamID(mState)]->setIsWritten(true);
                    pValveSP->setValveParam(convertParamID(mState), mpParamList[convertParamID(mState)]->mValue, this);
                    return;
                }
            }
            setState(STATE_WRITE_END);
        }
        else if(mState == STATE_WRITE_END)
        {
            for(int i = 0; i < 100; i ++)
            {
                mpParamList[i]->setIsEdit(false);
            }
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
            return state - (int)eState::STATE_RE_LOAD;
        else
            return state - (int)eState::STATE_LOAD;
    }

    void setParam(bool isPresent, int paramID, QString paramValue, bool isEdit = false)
    {
        if(mState >= STATE_RE_LOAD && mState < STATE_READY) // 쓰고나서 확인차 읽어오는 과정
        {
            mpParamList[paramID]->setIsErr((mpParamList[paramID]->getTextValue().toUpper() != paramValue.toUpper() && isPresent) || isPresent != mpParamList[paramID]->getIsPresent()); // 이전 표현된 값과 다르면 잘못 저장된 것이다.

            if(isPresent != mpParamList[paramID]->getIsPresent() && isPresent) // 없던것이 생기면 화면에 표시해줘야 한다.
            {
                mpParamList[paramID]->setIsPresent(isPresent);
                mpParamList[paramID]->setId(paramID);
                mpParamList[paramID]->setValue(paramValue);
            }
        }
        else if(mState >= STATE_LOAD && mState < STATE_OVER)// 리셋하고 다시 읽어오는 과정
        {
            mpParamList[paramID]->setIsPresent(isPresent);
            mpParamList[paramID]->setId(paramID);
            mpParamList[paramID]->setValue(isPresent ? paramValue : "000000");

            if(isPresent)
                mpParamList[paramID]->setIsEdit(isEdit); // 파일읽기로 읽오올 경우 읽어온값은 수정된 값으로 설정해서 화면에 수정값으로 표시해야된다. ( 파일읽기는 수동이 아니라 파일을 이용한 배치처리로 edit한 컨셉임 )
        }
    }
};
#endif // VALVEPARAMEXDLGMODEL_H
