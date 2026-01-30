#ifndef PRESSURECTRLLEARNPARAMDLGMODEL_H
#define PRESSURECTRLLEARNPARAMDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"
#include "source/service/def/datetimeform.h"

class PressureCtrlLearnParamItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsPresent  READ getIsPresent NOTIFY signalEventChangedIsPresent)
    Q_PROPERTY(QString mValueText  READ getValueText NOTIFY signalEventChangedValueText)
    Q_PROPERTY(int     mIdx        READ getIdx       NOTIFY signalEventChangedIdx      )
    Q_PROPERTY(int     mPoint      READ getPoint     NOTIFY signalEventChangedPoint    )
    Q_PROPERTY(bool    mErr        READ getErr       NOTIFY signalEventChangedErr      )

public:
    bool    mIsPresent = false;
    QString mValueText = "";
    int     mIdx       = 0;
    int     mPoint     = 0;
    bool    mErr       = false;

    bool    getIsPresent(){ return mIsPresent;}
    QString getValueText(){ return mValueText;}
    int     getIdx      (){ return mIdx      ;}
    int     getPoint    (){ return mPoint    ;}
    bool    getErr      (){ return mErr      ;}

    void    setIsPresent(bool    value){mIsPresent = value; emit signalEventChangedIsPresent(value);}
    void    setValueText(QString value)
    {
        setErr(value.length() != 11);

        if(mErr)
        {
            int intValue = value.mid(3,8).toInt();
            mValueText = QString("%1%2").arg(mIdx, 3, 10, QChar('0')).arg(intValue, 8, 10, QChar('0'));
        }
        else
        {
            mValueText = value;
        }

        setPoint(mValueText.mid(3,8).toInt());
        emit signalEventChangedValueText(value);
    }
    void    setIdx      (int     value){mIdx       = value; emit signalEventChangedIdx      (value);}
    void    setPoint    (int     value){mPoint     = value; emit signalEventChangedPoint    (value);}
    void    setErr      (bool    value){mErr       = value; emit signalEventChangedErr      (value);}

    void    reset()
    {
        setIsPresent(false); setErr(false); setValueText(QString("%1%2").arg(mIdx, 3, 10, QChar('0')).arg("00000000"));
    }
signals:
    void signalEventChangedIsPresent (bool    value);
    void signalEventChangedValueText (QString value);
    void signalEventChangedIdx       (int     value);
    void signalEventChangedPoint     (int     value);
    void signalEventChangedErr       (bool    value);

public:
    explicit PressureCtrlLearnParamItemModel(QObject *parent = nullptr): QObject(parent)
    {

    }
    explicit PressureCtrlLearnParamItemModel(int idx, QObject *parent = nullptr): QObject(parent)
    {
        setIdx(idx);
    }
    ~PressureCtrlLearnParamItemModel()
    {
    }
};

class PressureCtrlLearnParamDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode             READ getAccessMode           NOTIFY signalEventChangedAccessMode          )
    Q_PROPERTY(bool     mIsRS232Test            READ getIsRS232Test          NOTIFY signalEventChangedIsRS232Test         )
    Q_PROPERTY(double   mTimeConstant           READ getTimeConstant         NOTIFY signalEventChangedTimeConstant        )
    Q_PROPERTY(double   mEndParamIdx            READ getEndParamIdx          NOTIFY signalEventChangedEndParamIdx         )
    Q_PROPERTY(double   mTimeConstantParamIdx   READ getTimeConstantParamIdx NOTIFY signalEventChangedTimeConstantParamIdx)
    Q_PROPERTY(bool     mIsEdit                 READ getIsEdit               NOTIFY signalEventChangedIsEdit              )
    Q_PROPERTY(bool     mIsControllerData       READ getIsControllerData     NOTIFY signalEventChangedIsControllerData    )
    Q_PROPERTY(bool     mIsFileData             READ getIsFileData           NOTIFY signalEventChangedIsFileData          )
    Q_PROPERTY(QString  mStrStatus              READ getStrStatus            NOTIFY signalEventChangedStrStatus           )
    Q_PROPERTY(QString  mErrMsg                 READ getErrMsg               NOTIFY signalEventChangedErrMsg              )
    Q_PROPERTY(QString  mErrMsg2                READ getErrMsg2              NOTIFY signalEventChangedErrMsg2             )
    Q_PROPERTY(int      mProgress               READ getProgress             NOTIFY signalEventChangedProgress            )

public:
    int     mAccessMode           = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test          = false;
    double  mTimeConstant         = -1;
    int     mEndParamIdx          = 103;
    int     mTimeConstantParamIdx = 102;
    bool    mIsEdit               = false;
    bool    mIsControllerData     = false;
    bool    mIsFileData           = false;
    QString mStrStatus            = "ready";
    QString mErrMsg               = "";
    QString mErrMsg2              = "";
    int     mProgress             = 100 ;

    int     getAccessMode          (){ return mAccessMode          ; }
    bool    getIsRS232Test         (){ return mIsRS232Test         ; }
    double  getTimeConstant        (){ return mTimeConstant        ; }
    int     getEndParamIdx         (){ return mEndParamIdx         ; }
    int     getTimeConstantParamIdx(){ return mTimeConstantParamIdx; }
    bool    getIsControllerData    (){ return mIsControllerData    ; }
    bool    getIsFileData          (){ return mIsFileData          ; }
    bool    getIsEdit              (){ return mIsEdit              ; }
    QString getStrStatus           (){ return mStrStatus           ; }
    QString getErrMsg              (){ return mErrMsg              ; }
    QString getErrMsg2             (){ return mErrMsg2             ; }
    int     getProgress            (){ return mProgress            ; }

    void    setAccessMode          (int     value){ if(mAccessMode            == value)return; mAccessMode            = value; emit signalEventChangedAccessMode           (value);}
    void    setIsRS232Test         (bool    value){ if(mIsRS232Test           == value)return; mIsRS232Test           = value; emit signalEventChangedIsRS232Test          (value);}
    void    setTimeConstant        (double  value){ if(mTimeConstant          == value)return; mTimeConstant          = value; emit signalEventChangedTimeConstant         (value);}
    void    setEndParamIdx         (int     value){ if(mEndParamIdx           == value)return; mEndParamIdx           = value; emit signalEventChangedEndParamIdx          (value);}
    void    setTimeConstantParamIdx(int     value){ if(mTimeConstantParamIdx  == value)return; mTimeConstantParamIdx  = value; emit signalEventChangedTimeConstantParamIdx (value);}
    void    setIsEdit              (bool    value){ if(mIsEdit                == value)return; mIsEdit                = value; emit signalEventChangedIsEdit               (value);}
    void    setIsControllerData    (bool    value){ if(mIsControllerData      == value)return; mIsControllerData      = value; emit signalEventChangedIsControllerData     (value);}
    void    setIsFileData          (bool    value){ if(mIsFileData            == value)return; mIsFileData            = value; emit signalEventChangedIsFileData           (value);}
    void    setStrStatus           (QString value){ if(mStrStatus             == value)return; mStrStatus             = value; emit signalEventChangedStrStatus            (value);}
    void    setErrMsg              (QString value){ if(mErrMsg                == value)return; mErrMsg                = value; emit signalEventChangedErrMsg               (value);}
    void    setErrMsg2             (QString value){ if(mErrMsg2               == value)return; mErrMsg2               = value; emit signalEventChangedErrMsg2              (value);}
    void    setProgress            (int     value){ if(mProgress              == value)return; mProgress              = value; emit signalEventChangedProgress             (value);}

signals:
    void signalEventChangedAccessMode          (int         value);
    void signalEventChangedIsRS232Test         (bool        value);
    void signalEventChangedTimeConstant        (double      value);
    void signalEventChangedEndParamIdx         (int         value);
    void signalEventChangedTimeConstantParamIdx(int         value);
    void signalEventChangedIsEdit              (bool        value);
    void signalEventChangedIsControllerData    (bool        value);
    void signalEventChangedIsFileData          (bool        value);
    void signalEventChangedStrStatus           (QString     value);
    void signalEventChangedErrMsg              (QString     value);
    void signalEventChangedErrMsg2             (QString     value);
    void signalEventChangedProgress            (int         value);
    void signalEventProcIdx                    (int         idx  );
    void signalEventLoadData                   (int idx, int data);
    void signalEventUnknowFormat               (             );

public:
    explicit PressureCtrlLearnParamDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_LEARN_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_RESET;

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        for(int i = 0; i < 104; i ++)
        {
            PressureCtrlLearnParamItemModel * pItemModel = new PressureCtrlLearnParamItemModel(i, this);
            mpParamList.append(pItemModel);
        }
    }
    ~PressureCtrlLearnParamDlgModel()
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

    Q_INVOKABLE void onCommandReadFromController()
    {
        setState(eState::STATE_LOAD_START);
        setIsControllerData(true);
        setIsFileData(false);
    }

    void onValveReadedLearnParam(ValveResponseLearnParamDto dto)
    {
        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_LEARN_PARAM).length(), 3).toInt();

        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(id != convertParamID(mState) || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setErrMsg(dto.mErrMsg);
            setState(mState);
            return;
        }

        setErrMsg("");

        QString value = dto.mIsSucc ? dto.mValue : QString("%1%2").arg(id,3,10, QChar('0')).arg("000");
        setParam(value);

        setState(mState + 1);
    }


    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandWriteToController()
    {
        setState(eState::STATE_WRITE_START);
    }

    void onValveWrittenLearnParam(ValveResponseDto dto)
    {
        int id = dto.mReqDto.mReqCommand.mid(QString(REQ_READ_LEARN_PARAM).length(), 3).toInt();

        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

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

    Q_INVOKABLE void onCommandWriteReset()
    {
        setState(eState::STATE_WRITE_RESET);
    }

    void onValveWrittenLearnReset(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_RESET || dto.mReqDto.mpRef != this)
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

        onCommandReadFromController();
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
        int readIdx = 0;

        do{
            QString value = out.readLine();

            if(readIdx == 0)
            {
                if(value.contains(",") == false || value.at(3) != ',')
                {
                    file.close();
                    emit signalEventUnknowFormat();
                    return;
                }
                else
                {
                    bool ok;

                    value.split(",")[0].toInt(&ok, 10);

                    if(ok == false)
                    {
                        file.close();
                        emit signalEventUnknowFormat();
                        return;
                    }
                }

                setState(STATE_LOAD_START, true);

                setIsControllerData(false);
                setIsFileData(true);
            }

            value.replace(",","");

            if(readIdx <= mEndParamIdx )
            {
                readIdx++;
                setParam(value);
            }

        }while(!out.atEnd());

        for(int i = 0; i < mpParamList.size(); i ++)
        {
            if(mpParamList[i]->getIsPresent() == false)
            {
                setParam(QString("%1%2").arg(i,3,10,QChar('0')).arg("0"));
            }
        }
        setState(STATE_READY, true);
        file.close();
    }

    Q_INVOKABLE void onCommandWriteToLocalFile(QString filePath)
    {
        FileWriterEx file;
        int splitIdx = filePath.lastIndexOf("/")+1;
        QString dir = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        if(file.open(dir, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            setErrMsg2("File open failed!");
            return;
        }

        for(int i = 0; i < mpParamList.size(); i ++)
        {
            file.appendLine(QString("%1").arg(mpParamList[i]->getValueText().insert(3, QChar(','))));
        }

        setErrMsg2("");
        file.close();
        return;
    }

    Q_INVOKABLE PressureCtrlLearnParamItemModel * onCommandGetParamItem(int idx)
    {
        if(idx >= mpParamList.count())
            return &mDummyParamItem;

        return mpParamList[idx];
    }

    Q_INVOKABLE int onCommandItemCount()
    {
        return 104;
    }

private:
    QList<PressureCtrlLearnParamItemModel *>  mpParamList;
    PressureCtrlLearnParamItemModel           mDummyParamItem;

private:
    enum eState{
        STATE_WRITE_RESET           =  0,
        STATE_WRITE_START           =  STATE_WRITE_RESET      + 1,
        // ...000 ~ 103 STATE_WRITE_ING
        STATE_WRITE_END             =  STATE_WRITE_START      + 103,
        STATE_READY                 =  STATE_WRITE_END        + 1,
        STATE_LOAD_START            =  STATE_READY            + 1,
        // ... 00 ~ 103 STATE_LOAD_ING   =  1,
        STATE_LOAD_END              =  STATE_LOAD_START       + 103,
        STATE_OVER                  =  STATE_LOAD_END         + 1
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

        if(mState != STATE_LOAD_START && state == STATE_LOAD_START)
        {
            setErrMsg("");
            setErrMsg2("");

            for(int i = 0; i < 104; i ++)
            {
                mpParamList[i]->reset();
            }

            setTimeConstant(-1);
        }
        else if(mState != STATE_WRITE_START && state == STATE_WRITE_START)
        {
            setErrMsg2("");
        }

        mState = state == STATE_OVER ? STATE_READY : state;

        if(mState >= STATE_LOAD_START && mState < STATE_OVER)
        {
            progress = ((state) * 100) / STATE_OVER;
            strStatus = "loading";
        }
        else if(mState == STATE_READY)
        {
            progress = 100;
            strStatus = "ready";
        }
        else if(mState == STATE_WRITE_RESET)
        {
            progress = 50;
            strStatus = "reset";
        }
        else
        {
            progress = ((mState) * 100) / STATE_WRITE_END;
            strStatus = "writting";
        }

        setProgress(progress);
        setStrStatus(strStatus);

        if(!doNotTimer)
            startTimer();
    }

public slots:
    void onTimeout()
    {
        if(mState >= STATE_LOAD_START && mState <= STATE_LOAD_END)
        {
            pValveSP->readLearnParam(convertParamID(mState), this);
        }
        else if(mState >= STATE_WRITE_START && mState <= STATE_WRITE_END)
        {
            pValveSP->setLearnParam(mpParamList[convertParamID(mState)]->getValueText(), this);
        }
        else if(mState == STATE_WRITE_RESET)
        {
            pValveSP->learnReset(this);
        }
    }

private:
    int convertParamID(int state)
    {
        if(state <= eState::STATE_WRITE_END)
            return (int)state - (int)eState::STATE_WRITE_START;
        else if(state <= eState::STATE_LOAD_END)
            return state - (int)eState::STATE_LOAD_START;

        return 0;
    }

    void setParam(QString paramValue)
    {
        if(paramValue.length() < 3)
            return;

        int idx = paramValue.mid(0, 3).toInt();

        if(idx >= mpParamList.size())
            return;

         mpParamList[idx]->setIsPresent(true);
         mpParamList[idx]->setErr(paramValue.length() != 11);
         mpParamList[idx]->setValueText(paramValue);

         if(idx == mTimeConstantParamIdx)
         {
             QByteArray hexBigEndianArray = QByteArray::fromHex(paramValue.mid(3,8).toUtf8());
             float fValue;

             ((char *)(&fValue))[3] = hexBigEndianArray.at(0);
             ((char *)(&fValue))[2] = hexBigEndianArray.at(1);
             ((char *)(&fValue))[1] = hexBigEndianArray.at(2);
             ((char *)(&fValue))[0] = hexBigEndianArray.at(3);

             setTimeConstant(fValue * 10000);
         }

         if(idx < 101)
            emit signalEventLoadData(idx, mpParamList[idx]->getPoint());

         emit signalEventProcIdx(idx);
    }
};

/*
class PressureCtrlLearnParamEnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eItemStatus)

public:
    enum eItemStatus{
        ITEM_STATUS_NOT_READY              = 0,
        ITEM_STATUS_LOADING                = ITEM_STATUS_NOT_READY + 1,
        ITEM_STATUS_READY                  = ITEM_STATUS_LOADING   + 1,
        ITEM_STATUS_WRITTING               = ITEM_STATUS_READY     + 1,
    };
};

class PressureCtrlLearnParamItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mStatus     READ getStatus     NOTIFY signalEventChangedStatus    )
    Q_PROPERTY(QString  mValue      READ getValue      NOTIFY signalEventChangedValue     )
    Q_PROPERTY(QString  mPointValue READ getPointValue NOTIFY signalEventChangedPointValue)
    Q_PROPERTY(bool     mErr        READ getErr        NOTIFY signalEventChangedErr       )


public:
    int     mStatus     = PressureCtrlLearnParamEnumDef::ITEM_STATUS_NOT_READY;
    QString mValue      = "";
    QString mPointValue = "";
    bool    mErr        = false;

    int     getStatus    (){ return mStatus    ; }
    QString getValue     (){ return mValue     ; }
    QString getPointValue(){ return mPointValue; }
    bool    getErr       (){ return mErr       ; }

    void    setStatus    (int     value){ if(mStatus     == value)return; mStatus     = value; emit signalEventChangedStatus    (value);}
    void    setValue     (QString value){ if(mValue      == value)return; mValue      = value; emit signalEventChangedValue     (value);}
    void    setPointValue(QString value){ if(mPointValue == value)return; mPointValue = value; emit signalEventChangedPointValue(value);}
    void    setErr       (bool    value){ if(mErr        == value)return; mErr        = value; emit signalEventChangedErr       (value);}
    void    reset()
    {
        setStatus(PressureCtrlLearnParamEnumDef::ITEM_STATUS_NOT_READY);
        setValue("");
        setPointValue("");
        setErr(false);
    }
signals:
    void signalEventChangedStatus    (int     value);
    void signalEventChangedValue     (QString value);
    void signalEventChangedPointValue(QString value);
    void signalEventChangedErr       (bool    value);

public:
    explicit PressureCtrlLearnParamItemModel(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~PressureCtrlLearnParamItemModel()
    {
    }

};

class PressureCtrlLearnParamDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool     mIsValveConnected     READ getIsValveConnected     NOTIFY signalEventChangedIsValveConnected    )
    Q_PROPERTY(int      mEndParamIdx          READ getEndParamIdx          NOTIFY signalEventChangedEndParamIdx         )
    Q_PROPERTY(int      mTimeConstantParamIdx READ getTimeConstantParamIdx NOTIFY signalEventChangedTimeConstantParamIdx)
    Q_PROPERTY(int      mAccessMode           READ getAccessMode           NOTIFY signalEventChangedAccessMode          )
    Q_PROPERTY(bool     mIsLoaded             READ getIsLoaded             NOTIFY signalEventChangedIsLoaded            )
    Q_PROPERTY(double   mTimeConstant         READ getTimeConstant         NOTIFY signalEventChangedTimeConstant        )
    Q_PROPERTY(QString  mStrStatus            READ getStrStatus            NOTIFY signalEventChangedStrStatus           )
    Q_PROPERTY(QString  mErrMsg               READ getErrMsg               NOTIFY signalEventChangedErrMsg              )
    Q_PROPERTY(QString  mErrMsg2              READ getErrMsg2              NOTIFY signalEventChangedErrMsg2             )
    Q_PROPERTY(int      mProgress             READ getProgress             NOTIFY signalEventChangedProgress            )

public:
    bool    mIsValveConnected     = false;
    int     mEndParamIdx          = 103;
    int     mTimeConstantParamIdx = 102;
    int     mAccessMode        = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsLoaded          = false;
    double  mTimeConstant      = -1;
    QString mStrStatus         = "Loading";
    QString mErrMsg            = "";
    QString mErrMsg2           = "";
    int     mProgress          = 0 ;

    bool    getIsValveConnected    (){ return mIsValveConnected    ;}
    int     getEndParamIdx         (){ return mEndParamIdx         ;}
    int     getTimeConstantParamIdx(){ return mTimeConstantParamIdx;}
    int     getAccessMode          (){ return mAccessMode          ; }
    bool    getIsLoaded            (){ return mIsLoaded            ; }
    double  getTimeConstant        (){ return mTimeConstant        ; }
    QString getStrStatus           (){ return mStrStatus           ; }
    QString getErrMsg              (){ return mErrMsg              ; }
    QString getErrMsg2             (){ return mErrMsg2             ; }
    int     getProgress            (){ return mProgress            ; }

    void    setIsValveConnected    (bool    value){ if(mIsValveConnected  == value)return; mIsValveConnected  = value; emit signalEventChangedIsValveConnected (value);}
    void    setAccessMode          (int     value){ if(mAccessMode        == value)return; mAccessMode        = value; emit signalEventChangedAccessMode       (value);}
    void    setIsLoaded            (bool    value){ if(mIsLoaded          == value)return; mIsLoaded          = value; emit signalEventChangedIsLoaded         (value);}
    void    setTimeConstant        (double  value){ if(mTimeConstant      == value)return; mTimeConstant      = value; emit signalEventChangedTimeConstant     (value);}
    void    setStrStatus           (QString value){ if(mStrStatus         == value)return; mStrStatus         = value; emit signalEventChangedStrStatus        (value);}
    void    setErrMsg              (QString value){ if(mErrMsg            == value)return; mErrMsg            = value; emit signalEventChangedErrMsg           (value);}
    void    setErrMsg2             (QString value){ if(mErrMsg2           == value)return; mErrMsg2           = value; emit signalEventChangedErrMsg2          (value);}
    void    setProgress            (int     value){ if(mProgress          == value)return; mProgress          = value; emit signalEventChangedProgress         (value);}

signals:
    void signalEventChangedIsValveConnected    (bool    value);
    void signalEventChangedEndParamIdx         (int     value);
    void signalEventChangedTimeConstantParamIdx(int     value);
    void signalEventChangedAccessMode          (int     value);
    void signalEventChangedIsLoaded            (bool    value);
    void signalEventChangedTimeConstant        (double  value);
    void signalEventChangedStrStatus           (QString value);
    void signalEventChangedErrMsg              (QString value);
    void signalEventChangedErrMsg2             (QString value);
    void signalEventChangedProgress            (int     value);
    void signalEventAddedParam                 (int idx      );
    void signalEventLoadedParam                (             );

public:
    explicit PressureCtrlLearnParamDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_ISCONNECTED;
        ENABLE_SLOT_VALVE_READED_LEARN_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_PARAM;
        ENABLE_SLOT_VALVE_WRITTEN_LEARN_RESET;

        for(int i = 0; i < 104; i ++)
        {
            mParamList.append(new PressureCtrlLearnParamItemModel(this));
        }

        onValveChangedAccess();
        onValveChangedIsConnected(pValveSP->getIsConnected());

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(STATE_INIT);
    }
    ~PressureCtrlLearnParamDlgModel()
    {
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedIsConnected(bool value)
    {
        Q_UNUSED(value);
        setIsValveConnected(pValveSP->getIsConnected());
    }

    Q_INVOKABLE PressureCtrlLearnParamItemModel * onCommandGetParamItem(int idx)
    {
        if(idx >= mParamList.count())
            return &mDummyParamItem;

        return mParamList[idx];
    }

    Q_INVOKABLE void onCommandReadFromController()
    {
        readReady();
        setState(eState::STATE_READ_CTRL);
    }

    void onValveReadedLearnParam(ValveResponseLearnParamDto dto)
    {
        PressureCtrlLearnParamItemModel * pProcItem = onCommandGetParamItem(mProcParamIdx);
        if(dto.mReqDto.mpRef != pProcItem)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        pProcItem->setStatus(PressureCtrlLearnParamEnumDef::ITEM_STATUS_READY);

        if(mIsWritten)
        {
            pProcItem->setErr(pProcItem->getValue() != dto.mValue);
        }
        else
        {
            pProcItem->setValue(dto.mValue);
            pProcItem->setPointValue(dto.mPointValue);
            pProcItem->setErr(false);
        }

        if(dto.mIdx == mTimeConstantParamIdx)
        {
            QByteArray hexBigEndianArray = QByteArray::fromHex(dto.mPointValue.toUtf8());
            float fValue;

            ((char *)(&fValue))[3] = hexBigEndianArray.at(0);
            ((char *)(&fValue))[2] = hexBigEndianArray.at(1);
            ((char *)(&fValue))[1] = hexBigEndianArray.at(2);
            ((char *)(&fValue))[0] = hexBigEndianArray.at(3);

            setTimeConstant(fValue * 10000);
        }


        if(dto.mIdx == mEndParamIdx)
        {
            mIsWritten = false;
            setState(eState::STATE_READY);
        }
        else
        {
            mProcParamIdx = mProcParamIdx + 1;
            setState(mState);
        }
    }

    Q_INVOKABLE void onCommandWriteToController()
    {
        writeReady();
        setState(eState::STATE_WRITE_CTRL);
    }

    void onValveWrittenLearnParam(ValveResponseDto dto)
    {
        PressureCtrlLearnParamItemModel * pProcItem = onCommandGetParamItem(mProcParamIdx);

        if(dto.mReqDto.mpRef != pProcItem)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        pProcItem->setStatus(PressureCtrlLearnParamEnumDef::ITEM_STATUS_READY);
        setErrMsg2(dto.mErrMsg);

        if(mProcParamIdx == mEndParamIdx)
        {
            onCommandReadFromController();
            mIsWritten = true;
        }
        else
        {
            mProcParamIdx = mProcParamIdx + 1;
            setState(mState);
        }
    }


    Q_INVOKABLE void onCommandWriteReset()
    {
        setState(eState::STATE_WRITE_RESET);
    }

    void onValveWrittenLearnReset(ValveResponseDto dto)
    {
        if(mState != STATE_WRITE_RESET || dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            setState(mState);
            return;
        }

        setErrMsg2(dto.mErrMsg);

        onCommandReadFromController();
    }

    Q_INVOKABLE void onCommandReadFromFile(QString filePath)
    {
        QFile file;
        PressureCtrlLearnParamItemModel * pProcItem; // = onCommandGetParamItem(mProcParamIdx);
        file.setFileName(filePath);
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            setErrMsg("File open failed!");
            return;
        }

        readReady();

        QTextStream out(&file);
        out.setCodec("utf-8");
        int readIdx = 0;
        int waitIdx = 0;

        do{
            QString value = out.readLine();
            QString pointValue = value.mid(3,8);

            readIdx = value.mid(0,3).toInt();

            if(readIdx != waitIdx)
            {
                setErrMsg("invaild index error!");
                setIsLoaded(false);
                return;
            }

            if(readIdx <= mEndParamIdx )
            {
                pProcItem = onCommandGetParamItem(readIdx);

                pProcItem->setStatus(PressureCtrlLearnParamEnumDef::ITEM_STATUS_READY);
                pProcItem->setValue(value);
                pProcItem->setPointValue(pointValue);
                pProcItem->setErr(false);

                if(readIdx == mTimeConstantParamIdx)
                {
                    QByteArray hexBigEndianArray = QByteArray::fromHex(pointValue.toUtf8());
                    float fValue;

                    ((char *)(&fValue))[3] = hexBigEndianArray.at(0);
                    ((char *)(&fValue))[2] = hexBigEndianArray.at(1);
                    ((char *)(&fValue))[1] = hexBigEndianArray.at(2);
                    ((char *)(&fValue))[0] = hexBigEndianArray.at(3);

                    setTimeConstant(fValue * 10000);
                }
            }

            waitIdx ++;

        }while(!out.atEnd());

        file.close();
    }

    Q_INVOKABLE void onCommandWriteToLocalFile(QString filePath)
    {
        FileWriterEx file;
        int splitIdx = filePath.lastIndexOf("/")+1;
        QString dir = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        writeReady();

        if(file.open(dir, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            setErrMsg2("File open failed!");
            return;
        }

        for(int i = 0; i < mParamList.size(); i ++)
        {
            file.appendLine(QString("%1").arg(mParamList[i]->mValue));
        }

        file.close();
        return;
    }

private:
    QList<PressureCtrlLearnParamItemModel *>  mParamList;
    PressureCtrlLearnParamItemModel           mDummyParamItem;

    void readReady()
    {
        mIsWritten = false;
        mProcParamIdx = 0;
        setErrMsg("");
        setTimeConstant(-1);

        setIsLoaded(false);
        foreach(PressureCtrlLearnParamItemModel * pItem, mParamList)
        {
            pItem->reset();
        }
    }

    void writeReady()
    {
        mProcParamIdx = 0;
        setErrMsg2("");
    }

private:
    enum eState{
        STATE_INIT                  = 0,
        STATE_READY                 = STATE_INIT       + 1,
        STATE_READ_CTRL             = STATE_READY      + 1,
        STATE_WRITE_CTRL            = STATE_READ_CTRL  + 1,
        STATE_WRITE_RESET           = STATE_WRITE_CTRL + 1,
    };

    QTimer mTimer;
    bool   mIsWritten     = false;
    eState mState         = eState::STATE_READY;
    int    mProcParamIdx  = 0;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        mState = state;

        switch ((int)state)
        {
        case (int)eState::STATE_INIT:
            setIsLoaded(false);
            setStrStatus("");
            setProgress(100);
            break;
        case (int)eState::STATE_READY:
            setIsLoaded(true);
            setStrStatus("Ready");
            setProgress(100);
            break;
        case (int)eState::STATE_READ_CTRL:
            setStrStatus("Loading");
            setProgress(qFloor(((double)mProcParamIdx / (double)(mEndParamIdx + 1)) * 100.0));
            startTimer();
            break;

        case (int)eState::STATE_WRITE_CTRL:
            setStrStatus("Writting");
            setProgress(qFloor(((double)mProcParamIdx / (double)(mEndParamIdx + 1)) * 100.0));
            startTimer();
            break;

        case (int)eState::STATE_WRITE_RESET:
            setStrStatus("Resetting");
            setProgress(0);
            startTimer();
            break;
        }
    }

public slots:
    void onTimeout()
    {
        PressureCtrlLearnParamItemModel * pProcItem = onCommandGetParamItem(mProcParamIdx);

        switch ((int)mState)
        {
        case (int)eState::STATE_READ_CTRL:
            pProcItem->setStatus(PressureCtrlLearnParamEnumDef::ITEM_STATUS_LOADING);
            pValveSP->readLearnParam(mProcParamIdx, this);
            break;

        case (int)eState::STATE_WRITE_CTRL:
            pProcItem->setStatus(PressureCtrlLearnParamEnumDef::ITEM_STATUS_WRITTING);
            pValveSP->setLearnParam(mParamList[mProcParamIdx]->mValue, this);
            break;

        case (int)eState::STATE_WRITE_RESET:
            pValveSP->learnReset(this);
            break;
        }
    }
};
*/
#endif // PRESSURECTRLLEARNPARAMDLGMODEL_H
