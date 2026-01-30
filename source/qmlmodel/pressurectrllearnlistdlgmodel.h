#ifndef PRESSURECTRLLEARNLISTDLGMODEL_H
#define PRESSURECTRLLEARNLISTDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QFile>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/util/filewriterex.h"
#include "source/service/coreservice.h"

class PressureCtrlLearnListItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mIntID            READ getIntID       NOTIFY signalEventChangedIntID     )
    Q_PROPERTY(QString mTextID           READ getTextID      NOTIFY signalEventChangedTextID    )
    Q_PROPERTY(float   mFloatValue       READ getFloatValue  NOTIFY signalEventChangedFloatValue)
    Q_PROPERTY(bool    mIsEnable         READ getIsEnable    NOTIFY signalEventChangedIsEnable  )
    Q_PROPERTY(bool    mIsEdit           READ getIsEdit      NOTIFY signalEventChangedIsEdit    )
    Q_PROPERTY(bool    mIsErr            READ getIsErr       NOTIFY signalEventChangedIsErr     )

public:
    int     mIntID      = 0;

    float   mFloatValue = 0.0f;
    bool    mIsEdit     = false;
    bool    mIsErr      = false;
    bool    mIsEnable   = true;

    int     getIntID     (){ return mIntID; }
    QString getTextID    (){ return QString("%1").arg(mIntID, 4, 10, QChar('0')); }
    float   getFloatValue(){ return mFloatValue; }
    bool    getIsEdit    (){ return mIsEdit    ; }
    bool    getIsErr     (){ return mIsErr     ; }
    bool    getIsEnable  (){ return mIsEnable  ; }

    void    setIntId        (int     value){ if(mIntID       == value) return; mIntID      = value; emit signalEventChangedTextID(getTextID()); emit signalEventChangedIntID(value); }
    void    setFloatValue   (float   value){ if(mFloatValue  == value) return; mFloatValue = value; emit signalEventChangedFloatValue(value); }
    void    setIsEdit       (bool    value){ if(mIsEdit      == value) return; mIsEdit     = value; emit signalEventChangedIsEdit    (value);}
    void    setIsErr        (bool    value){ if(mIsErr       == value) return; mIsErr      = value; emit signalEventChangedIsErr     (value);}
    void    setIsEnable     (bool    value){ if(mIsEnable    == value) return; mIsEnable   = value; emit signalEventChangedIsEnable  (value);}

    void    reset()
    {
        setIsEdit(false);
        setIsErr (false);
        setFloatValue(0.0f);
    }

public slots:
    Q_INVOKABLE void editFloatValue(float value)
    {
        if(!compareFloat(value, mFloatValue))
        {
            setFloatValue(value);
            setIsEdit(true);
        }
    }
signals:
    void signalEventChangedIntID     (int     value);
    void signalEventChangedTextID    (QString value);
    void signalEventChangedFloatValue(float value);
    void signalEventChangedIsEdit    (bool    value);
    void signalEventChangedIsErr     (bool    value);
    void signalEventChangedIsEnable  (bool    value);

public:
    explicit PressureCtrlLearnListItemModel(QObject *parent = nullptr): QObject(parent)
    {
    }

    explicit PressureCtrlLearnListItemModel(int id, QObject *parent = nullptr): QObject(parent)
    {
        setIntId(id);
    }
    ~PressureCtrlLearnListItemModel()
    {
    }

    bool compareFloat(float a, float b) {

        // 절댓값 기준으로 큰 수 찾기
        float maxVal = qMax(qFabs(a), qFabs(b));

        // 유효숫자에 따른 최소 차이값 계산
        float epsilon = qPow(10, qCeil(qLn(maxVal) / qLn(10)) - 6);

        QString temp = QString("epsilon = %1, a = %2, b = %3").arg(epsilon,0,'f',10).arg(a,0,'f',10).arg(b,0,'f',10);


        // 두 숫자의 차이가 epsilon보다 작거나 같은지 확인
        return qFabs(a - b) <= (epsilon/2);
    }

};

class PressureCtrlLearnListDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode        READ getAccessMode       NOTIFY signalEventChangedAccessMode      )
    Q_PROPERTY(bool     mIsRS232Test       READ getIsRS232Test      NOTIFY signalEventChangedIsRS232Test     )
    Q_PROPERTY(bool     mIsEdit            READ getIsEdit           NOTIFY signalEventChangedIsEdit          )
    Q_PROPERTY(QString  mStrStatus         READ getStrStatus        NOTIFY signalEventChangedStrStatus       )
    Q_PROPERTY(QString  mErrMsg            READ getErrMsg           NOTIFY signalEventChangedErrMsg          )
    Q_PROPERTY(QString  mErrMsg2           READ getErrMsg2          NOTIFY signalEventChangedErrMsg2         )
    Q_PROPERTY(int      mProgress          READ getProgress         NOTIFY signalEventChangedProgress        )
    Q_PROPERTY(int      mItemCountPerPage  READ getItemCountPerPage NOTIFY signalEventChangedItemCountPerPage)
    Q_PROPERTY(int      mTotalPageCnt      READ getTotalPageCnt     NOTIFY signalEventChangedTotalPageCnt    )

public:
    int     mAccessMode        = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test       = false;
    bool    mIsEdit            = false;
    QString mStrStatus         = "Loading";
    QString mErrMsg            = "";
    QString mErrMsg2           = "";
    int     mProgress          = 0 ;
    int     mItemCountPerPage  = 40;
    int     mTotalPageCnt      = 0 ;

    int     getAccessMode       (){ return mAccessMode       ; }
    bool    getIsRS232Test      (){return mIsRS232Test       ; }
    bool    getIsEdit           (){ return mIsEdit           ; }
    QString getStrStatus        (){ return mStrStatus        ; }
    QString getErrMsg           (){ return mErrMsg           ; }
    QString getErrMsg2          (){ return mErrMsg2          ; }
    int     getProgress         (){ return mProgress         ; }
    int     getItemCountPerPage (){ return mItemCountPerPage ; }
    int     getTotalPageCnt     (){ return mTotalPageCnt     ; }

    void    setAccessMode       (int     value){ if(mAccessMode        == value)return; mAccessMode        = value; emit signalEventChangedAccessMode       (value);}
    void    setIsRS232Test      (bool    value){ if(mIsRS232Test       == value)return; mIsRS232Test       = value; emit signalEventChangedIsRS232Test      (value);}
    void    setIsEdit           (bool    value){ if(mIsEdit            == value)return; mIsEdit            = value; emit signalEventChangedIsEdit           (value);}
    void    setStrStatus        (QString value){ if(mStrStatus         == value)return; mStrStatus         = value; emit signalEventChangedStrStatus        (value);}
    void    setErrMsg           (QString value){ if(mErrMsg            == value)return; mErrMsg            = value; emit signalEventChangedErrMsg           (value);}
    void    setErrMsg2          (QString value){ if(mErrMsg2           == value)return; mErrMsg2           = value; emit signalEventChangedErrMsg2          (value);}
    void    setProgress         (int     value){ if(mProgress          == value)return; mProgress          = value; emit signalEventChangedProgress         (value);}
    void    setItemCountPerPage (int     value){ if(mItemCountPerPage  == value)return; mItemCountPerPage  = value; emit signalEventChangedItemCountPerPage (value);}
    void    setTotalPageCnt     (int     value){ if(mTotalPageCnt      == value)return; mTotalPageCnt      = value; emit signalEventChangedTotalPageCnt     (value);}

signals:
    void signalEventChangedAccessMode       (int     value);
    void signalEventChangedIsRS232Test      (bool    value);
    void signalEventChangedIsEdit           (bool    value);
    void signalEventChangedStrStatus        (QString value);
    void signalEventChangedErrMsg           (QString value);
    void signalEventChangedErrMsg2          (QString value);
    void signalEventChangedProgress         (int     value);
    void signalEventChangedItemCountPerPage (int     value);
    void signalEventChangedTotalPageCnt     (int     value);
    void signalEventUnknowFormat            (             );

public:
    explicit PressureCtrlLearnListDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_LEARN_LIST;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_LIST;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_LIST_START;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_LIST_END;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_LIST_RESET;

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mDummyLearnItem.setIsEnable(false);

        qDebug() << "[PressureCtrlLearnListDlgModel]";
        setState(eState::STATE_TOTAL_LOAD);
    }
    ~PressureCtrlLearnListDlgModel()
    {
        if(mState <= STATE_WRITE_END && mState >= STATE_WRITE_START)
            pValveSP->setLearnListEnd(nullptr);

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

    Q_INVOKABLE void onCommandReadFromController()
    {
        mpLearnList.clear();
        setState(eState::STATE_TOTAL_LOAD);
    }

    void onValveReadedLearnList(ValveResponseSimpleValueDto dto)
    {
        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_VALVE_PARAM).length(), 4).toInt();

        if(id != convertListItemID(mState) || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }

        if(!dto.mIsSucc){
            setState(STATE_READY);
            setTotalPageCnt((id + mItemCountPerPage) / mItemCountPerPage );

            for(int i = 0; i < mpLearnList.count(); i ++)
            {
                if(mpLearnList[i]->mIntID == id)
                {
                    QList<PressureCtrlLearnListItemModel *>::iterator it = mpLearnList.begin() + i;
                    mpLearnList.erase(it, mpLearnList.end());
                    break;
                }
            }

            for(int i = 0; i < mpLearnList.count(); i ++)
            {
                if(mpLearnList[i]->getIsErr())
                {
                    setIsEdit(true);
                    break;
                }
            }
            return;
        }

        setErrMsg("");

        float floatValue;

        floatValue = hexCodeToFloat(dto.mValue.mid(4));

        if(mpLearnList.count() == 0 || mpLearnList.last()->mIntID < id)
        {
            PressureCtrlLearnListItemModel * itemModel = new PressureCtrlLearnListItemModel(this);
            itemModel->setIntId(id);
            itemModel->setFloatValue(floatValue);
            mpLearnList.append(itemModel);
            setState(mState + 1);
        }
        else
        {
            for(int i = 0; i < mpLearnList.count(); i ++)
            {
                if(mpLearnList[i]->mIntID == id)
                {
                    mpLearnList[i]->setIsEdit(false);
                    mpLearnList[i]->setIsErr(!mpLearnList[i]->compareFloat(mpLearnList[i]->mFloatValue, floatValue));
                    mpLearnList[i]->setFloatValue(floatValue);
                    mpLearnList[i]->setIsEnable(true);
                    break;
                }
            }

            setState(mState + 1);
            mpLearnList[id]->setFloatValue(floatValue);
        }
    }


    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandWriteToController()
    {
        qDebug() << "[onCommandWriteToController]";
        setIsEdit(false);
        setState(eState::STATE_WRITE_START);
    }

    void onValveWrittenLearnListStart(ValveResponseDto dto)
    {
        qDebug() << "[onValveWrittenLearnListStart]";
        if(mState != STATE_WRITE_START || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
            setState(mState);
            return;
        }

        for(int nextId = 0; nextId < mpLearnList.size(); nextId++)
        {
            if(mpLearnList[nextId]->getIsEdit())
            {
                setState(STATE_WRITE + nextId);
                return;
            }
        }

        if(mpLearnList.count() > 0)
        {
            setState((eState)(STATE_WRITE));
        }
        else
        {
            setState((eState)(STATE_READY));
        }
    }

    void onValveWrittenLearnList(ValveResponseDto dto)
    {
        qDebug() << "[onValveWrittenLearnList]";

        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_LEARN_LIST).length(), 4).toInt();

        if(id != convertListItemID(mState) || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
            setState(mState);
            return;
        }

        if(mpLearnList.last()->mIntID > id)
        {
            setState((eState)(mState + 1));
        }
        else
        {
            setState((eState)(STATE_WRITE_END));
        }
    }

    void onValveWrittenLearnListEnd(ValveResponseDto dto)
    {
        qDebug() << "[onValveWrittenLearnListEnd]";

        if(mState != STATE_WRITE_END || dto.mReqDto.mpRef != this)
            return;

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
            setState(mState);
            return;
        }

        for(int nextId = 0; nextId < mpLearnList.size(); nextId++)
        {
            if(mpLearnList[nextId]->getIsEdit())
            {
                setState(STATE_TOTAL_LOAD + nextId);
                return;
            }
        }

        setState(STATE_READY);
    }

    Q_INVOKABLE void onCommandWriteLearnListReset()
    {
        setErrMsg2("");
        setState(eState::STATE_WRITE_LEARN_LIST_RESET);
    }

    void onValveWrittenLearnListReset(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_LEARN_LIST_RESET || dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[khko_debug][onValveWrittenLearnListReset]" << dto.mResData << ", isSucc = " << dto.mIsSucc;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        if(!dto.mIsSucc)
        {
            setErrMsg2(dto.mErrMsg);
        }

        mpLearnList.clear();
        setState(STATE_TOTAL_LOAD);
    }

    Q_INVOKABLE void onCommandReadFromFile(QString filePath)
    {
        QFile file;
        file.setFileName(filePath);
        file.open(QFile::ReadOnly);

        setProgress(0);

        if(file.isOpen() == false)
        {
            setErrMsg("File open failed!");
            setProgress(100);
            return;
        }

        mpLearnList.clear();

        QTextStream out(&file);
        out.setCodec("utf-8");

        do{
            bool intOk;
            bool floatOk;
            int  tempValue = 0;

            QString value = out.readLine();
            int id = value.mid(0,4).toInt(&intOk, 10);
            value = value.mid(4,value.length() - 4);
            tempValue = value.toInt(&floatOk, 16);

            if(value.length() != 8 || intOk == false || floatOk == false)
            {
                qDebug() << "[" << Q_FUNC_INFO << "]" << value << ", int = " << intOk << ", float = " << floatOk << ", len = " << value.length() ;

                mpLearnList.clear();
                file.close();
                setProgress(100);
                emit signalEventUnknowFormat();
                return;
            }

            if(mpLearnList.count() == id)
            {
                float floatValue = hexCodeToFloat(value);
                PressureCtrlLearnListItemModel * itemModel = new PressureCtrlLearnListItemModel(this);
                itemModel->setIntId(id);
                itemModel->setFloatValue(floatValue);
                itemModel->setIsEdit(true);
                mpLearnList.append(itemModel);
            }
            else
            {
                PressureCtrlLearnListItemModel * itemModel = new PressureCtrlLearnListItemModel(this);
                itemModel->setIntId(id);
                itemModel->setFloatValue(0.0f);
                itemModel->setIsEnable(false);
                mpLearnList.append(itemModel);
            }

        }while(!out.atEnd());

        file.close();

        setIsEdit(true);
        setProgress(100);
    }

    Q_INVOKABLE void onCommandWriteToFile(QString filePath)
    {
        FileWriterEx file;
        int splitIdx = filePath.lastIndexOf("/")+1;
        QString dir = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        setErrMsg2("");

        if(file.open(dir, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            setErrMsg2("File open failed!");
            return;
        }

        for(int i = 0; i < mpLearnList.count(); i ++)
        {
            QString hexCode = floatToHexCode(mpLearnList[i]->mFloatValue);
            file.appendLine(QString("%1%2").arg(i, 4, 10, QChar('0')).arg(hexCode));
        }

        file.close();
        return;
    }

    Q_INVOKABLE PressureCtrlLearnListItemModel * onCommandGetListItemInPage(int pageNum, int idx)
    {
        int indexInTotal = (pageNum * mItemCountPerPage) + idx;

        if(indexInTotal < mpLearnList.size())
        {
            return mpLearnList[indexInTotal];
        }

        return nullptr;
    }

    Q_INVOKABLE PressureCtrlLearnListItemModel * onCommandGetListItem(int idx)
    {
        qDebug() << "[onCommandGetListItem]" << "[list size-"  << mpLearnList.size() << "][idx-" << idx << "]" << "intid = " << mpLearnList[idx]->mIntID << ", floatValue = " << mpLearnList[idx]->mFloatValue;

        if(idx < 0)
            return &mDummyLearnItem;

        return mpLearnList[idx];
    }

private:
    QList<PressureCtrlLearnListItemModel *>  mpLearnList;
    PressureCtrlLearnListItemModel mDummyLearnItem;

private:
    enum eState{
        STATE_WRITE_LEARN_LIST_RESET     = 0,

        // START,0000 ~ FFFF,END STATE_WRITE_ING
        STATE_WRITE_START                = STATE_WRITE_LEARN_LIST_RESET + 1,
        STATE_WRITE                      = STATE_WRITE_START            + 1,
        STATE_WRITE_END                  = STATE_WRITE                  + 65535,

        // ...0000 ~ FFFF STATE_LOAD_ING
        STATE_TOTAL_LOAD                 = STATE_WRITE_END              + 1,
        STATE_READY                      = STATE_TOTAL_LOAD             + 65535
    };

    QTimer mTimer;
    int    mState       = eState::STATE_READY;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(int state)
    {
        int progress = 0;
        QString strStatus;

        qDebug() << "[setState]" << state;

        mState = state;

        if(mState == STATE_WRITE_LEARN_LIST_RESET)
        {
            progress = 50;
            strStatus = "param reset";
        }
        if(mState >= STATE_WRITE_START && mState < STATE_TOTAL_LOAD)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "writting";
        }
        else if(mState >= STATE_TOTAL_LOAD && mState < STATE_READY)
        {
            progress = ((mState) * 100) / STATE_READY;
            strStatus = "loading";
        }
        else if(mState == STATE_READY)
        {
            progress = 100;
            strStatus = "ready";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        if(mState == STATE_TOTAL_LOAD)
        {
            setErrMsg("");
        }
        else if(mState == STATE_WRITE_START)
        {
            setErrMsg2("");
        }

        startTimer();
    }

public slots:
    void onTimeout()
    {
        if(mState >= STATE_TOTAL_LOAD && mState < STATE_READY)
        {
            pValveSP->readLearnList(convertListItemID(mState), this);
        }
        else if(mState == STATE_WRITE_START)
        {
            pValveSP->setLearnListStart(this);
        }
        else if(mState >= STATE_WRITE && mState <STATE_WRITE_END)
        {
            int id = convertListItemID(mState);
            QString temp = floatToHexCode(mpLearnList[id]->mFloatValue);
            pValveSP->setLearnList(id, temp, this);
        }
        else if(mState == STATE_WRITE_END)
        {
            pValveSP->setLearnListEnd(this);
        }
        else if(mState == STATE_WRITE_LEARN_LIST_RESET)
        {
            pValveSP->learnListReset(this);
        }
    }

private:
    int convertListItemID(int state)
    {
        if(state < eState::STATE_WRITE_END)
            return (int)state - (int)eState::STATE_WRITE;
        else if(state < eState::STATE_READY)
            return state - (int)eState::STATE_TOTAL_LOAD;

        return 0;
    }

    QString floatToHexCode(float value) {
        // float 값을 저장할 4바이트 배열
        unsigned char bytes[4];

        // float 값을 바이트 배열로 복사
        memcpy(bytes, &value, 4);

        // 바이트 배열을 16진수 문자열로 변환
        QString hexString;
        for (size_t i = 0; i < 4; ++i) {
            hexString.append(QString("%1").arg(bytes[3-i], 2, 16, QChar('0')).toUpper());
        }

        return hexString;
    }

    float hexCodeToFloat(QString hex) {
        // float 값을 저장할 4바이트 배열

        if(hex.length() != 8)
            return 0;

        float retValue;
        unsigned char bytes[4];
        QByteArray byteArray = QByteArray::fromHex(hex.toLatin1());

        bytes[3] = byteArray[0];
        bytes[2] = byteArray[1];
        bytes[1] = byteArray[2];
        bytes[0] = byteArray[3];
        // float 값을 바이트 배열로 복사
        memcpy(&retValue, bytes, 4);

        return retValue;
    }
};

#endif // PRESSURECTRLLEARNLISTDLGMODEL_H
