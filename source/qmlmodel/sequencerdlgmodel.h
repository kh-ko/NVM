#ifndef SEQUENCERDLGMODEL_H
#define SEQUENCERDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QFile>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

/*
class ReqCommandUserData : public QObject
{
    Q_OBJECT

public:
    bool mCancel = false;

    ReqCommandUserData(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~ReqCommandUserData()
    {

    }
};*/

class SeqTestItemModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool    mIsRunnig     READ getIsRunnig     NOTIFY signalEventChangedIsRunnig    )
    Q_PROPERTY(bool    mComplete     READ getComplete     NOTIFY signalEventChangedComplete    )
    Q_PROPERTY(int     mSentCount    READ getSentCount    NOTIFY signalEventChangedSentCount   )
    Q_PROPERTY(int     mRcvCount     READ getRcvCount     NOTIFY signalEventChangedRcvCount    )
    Q_PROPERTY(int     mItemType     READ getItemType     NOTIFY signalEventChangedItemType    )
    Q_PROPERTY(double  mPositionPct  READ getPositionPct  NOTIFY signalEventChangedPositionPct )
    Q_PROPERTY(double  mPressurePct  READ getPressurePct  NOTIFY signalEventChangedPressurePct )
    Q_PROPERTY(QString mCommand      READ getCommand      NOTIFY signalEventChangedCommand     )
    Q_PROPERTY(int     mDelayMSec    READ getDelayMSec    NOTIFY signalEventChangedDelayMSec   )

public:
    bool    mIsRunnig  = false;
    bool    mComplete  = false;
    int     mSentCount = 0;
    int     mRcvCount  = 0;
    int     mItemType  = QmlEnumDef::SEQ_TYPE_CUSTOM;
    double  mPositionPct = 0;
    double  mPressurePct = 0;
    QString mCommand   = "";
    int     mDelayMSec = 1000;

    bool    getIsRunnig   (){ return mIsRunnig   ;}
    bool    getComplete   (){ return mComplete   ;}
    int     getSentCount  (){ return mSentCount  ;}
    int     getRcvCount   (){ return mRcvCount   ;}
    int     getItemType   (){ return mItemType   ;}
    double  getPositionPct(){ return mPositionPct;}
    double  getPressurePct(){ return mPressurePct;}
    QString getCommand    (){ return mCommand    ;}
    int     getDelayMSec  (){ return mDelayMSec  ;}

    void    setIsRunnig (bool    value){if(mIsRunnig  == value)return; mIsRunnig  = value; emit signalEventChangedIsRunnig (value);}
    void    setComplete (bool    value){if(mComplete  == value)return; mComplete  = value; emit signalEventChangedComplete (value);}
    void    setSentCount(int     value){if(mSentCount == value)return; mSentCount = value; emit signalEventChangedSentCount(value);}
    void    setRcvCount (int     value){if(mRcvCount  == value)return; mRcvCount  = value; emit signalEventChangedRcvCount (value);}
    void    setItemType (int     value)
    {
        if(mItemType  == value)
            return;

        mItemType  = value;

        emit signalEventChangedItemType (value);

        switch (value) {
        case (int)QmlEnumDef::SEQ_TYPE_OPEN    : setCommand("O:")      ;break;
        case (int)QmlEnumDef::SEQ_TYPE_CLOSE   : setCommand("C:")      ;break;
        case (int)QmlEnumDef::SEQ_TYPE_POSITION: setPositionPct(0)     ;break;
        case (int)QmlEnumDef::SEQ_TYPE_PRESSURE: setPressurePct(0)     ;break;
        case (int)QmlEnumDef::SEQ_TYPE_CUSTOM  : setCommand(""        );break;
        }
    }
    void    setPositionPct(double  value)
    {
        mPositionPct = value;

        emit signalEventChangedPositionPct(value);

        setCommand(QString("R:%1").arg(qRound(value * 1000), 6, 10, QChar('0')));
    }
    void    setPressurePct(double value)
    {
        mPressurePct = value;

        emit signalEventChangedPressurePct(value);

        setCommand(QString("S:%1").arg(qRound(value * 10000), 8, 10, QChar('0')));
    }
    void    setCommand    (QString value){if(mCommand   == value)return; mCommand     = value; emit signalEventChangedCommand    (value);}
    void    setDelayMSec  (int     value){if(mDelayMSec == value)return; mDelayMSec   = value; emit signalEventChangedDelayMSec  (value);}

    void    reset()
    {
        setIsRunnig(false);
        setSentCount(0);
        setRcvCount (0);
    }

public slots:
    void onValveWrittenCustomRequest(ValveResponseDto dto)
    {
        if(dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsSucc)
        {
            setRcvCount(getRcvCount() + 1);
            return;
        }
    }

    Q_INVOKABLE void onCommandSetPositionPct(double posPct)
    {
        setPositionPct(posPct);
    }

    Q_INVOKABLE void onCommandSetPressurePct(double pressurePct)
    {
        setPressurePct(pressurePct);
    }

    Q_INVOKABLE void onCommandSetCommand(QString cmd)
    {
        setCommand(cmd);
    }

    Q_INVOKABLE void onCommandSetDelayMSec(int value)
    {
        setDelayMSec(value);
    }
signals:
    void signalEventChangedIsRunnig   (bool    value);
    void signalEventChangedComplete   (bool    value);
    void signalEventChangedSentCount  (int     value);
    void signalEventChangedRcvCount   (int     value);
    void signalEventChangedErrCount   (int     value);
    void signalEventChangedItemType   (int     value);
    void signalEventChangedPositionPct(double  value);
    void signalEventChangedPressurePct(double  value);
    void signalEventChangedCommand    (QString value);
    void signalEventChangedDelayMSec  (int     value);

public:
    explicit SeqTestItemModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;
    }

    explicit SeqTestItemModel(int itemType, QString command, int delayMSec, QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;
        setItemType(itemType);

        if(itemType == QmlEnumDef::SEQ_TYPE_CUSTOM)
            setCommand(command);
        else if(itemType == QmlEnumDef::SEQ_TYPE_POSITION)
        {
            setPositionPct(command.mid(2).toDouble() / 1000.0);
        }
        else if(itemType == QmlEnumDef::SEQ_TYPE_PRESSURE)
        {
            setPressurePct(command.mid(2).toDouble() / 10000.0);
        }
        setDelayMSec(delayMSec);
    }
    ~SeqTestItemModel()
    {
    }
};

class SequencerDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode        READ getAccessMode        NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(int      mMode              READ getMode              NOTIFY signalEventChangedMode                  )
    Q_PROPERTY(bool     mIsRS232Test       READ getIsRS232Test       NOTIFY signalEventChangedIsRS232Test      )
    Q_PROPERTY(int      mRunState          READ getRunState          NOTIFY signalEventChangedRunState         )
    Q_PROPERTY(qint64   mTargetCycles      READ getTargetCycles      NOTIFY signalEventChangedTargetCycles     )
    Q_PROPERTY(qint64   mTotalActualCycles READ getTotalActualCycles NOTIFY signalEventChangedTotalActualCycles)
    Q_PROPERTY(qint64   mActualCycles      READ getActualCycles      NOTIFY signalEventChangedActualCycles     )
    Q_PROPERTY(qint64   mActualIndex       READ getActualIndex       NOTIFY signalEventChangedActualIndex      )
    Q_PROPERTY(bool     mIsEdit            READ getIsEdit            NOTIFY signalEventChangedIsEdit           )
    Q_PROPERTY(QString  mStrStatus         READ getStrStatus         NOTIFY signalEventChangedStrStatus        )
    Q_PROPERTY(QString  mErrMsg            READ getErrMsg            NOTIFY signalEventChangedErrMsg           )
    Q_PROPERTY(int      mProgress          READ getProgress          NOTIFY signalEventChangedProgress         )

public:
    enum eRunState{
        RUN_STATE_STOP  = 0,
        RUN_STATE_RUN   = 1,
        RUN_STATE_PAUSE = 2
    };

    int     mAccessMode        = ValveEnumDef::ACCESS_LOCAL;
    int     mMode              = ValveEnumDef::MODE_INIT;
    bool    mIsRS232Test       = false;
    int     mRunState          = eRunState::RUN_STATE_STOP;
    qint64  mTargetCycles      = 100;
    qint64  mTotalActualCycles = 0;
    qint64  mActualCycles      = 0;
    qint64  mActualIndex       = 0;
    bool    mIsEdit            = false;
    QString mStrStatus         = "Loading";
    QString mErrMsg            = "";
    int     mProgress          = 0 ;

    int     getAccessMode       (){ return mAccessMode       ;}
    int     getMode             (){ return mMode             ;}
    bool    getIsRS232Test      (){ return mIsRS232Test      ;}
    int     getRunState         (){ return mRunState         ;}
    qint64  getTargetCycles     (){ return mTargetCycles     ;}
    qint64  getTotalActualCycles(){ return mTotalActualCycles;}
    qint64  getActualCycles     (){ return mActualCycles     ;}
    qint64  getActualIndex      (){ return mActualIndex      ;}
    bool    getIsEdit           (){ return mIsEdit           ;}
    QString getStrStatus        (){ return mStrStatus        ;}
    QString getErrMsg           (){ return mErrMsg           ;}
    int     getProgress         (){ return mProgress         ;}

    void    setAccessMode       (int     value){ if(mAccessMode        == value)return; mAccessMode        = value; emit signalEventChangedAccessMode       (value);}
    void    setMode             (int     value){ if(mMode              == value)return; mMode              = value; emit signalEventChangedMode             (value);}
    void    setIsRS232Test      (bool    value){ if(mIsRS232Test       == value)return; mIsRS232Test       = value; emit signalEventChangedIsRS232Test      (value);}
    void    setRunState         (int     value){ if(mRunState          == value)return; mRunState          = value; emit signalEventChangedRunState         (value);}
    void    setTargetCycles     (qint64  value){ if(mTargetCycles      == value)return; mTargetCycles      = value; emit signalEventChangedTargetCycles     (value);}
    void    setTotalActualCycles(qint64  value){ if(mTotalActualCycles == value)return; mTotalActualCycles = value; emit signalEventChangedTotalActualCycles(value);}
    void    setActualCycles     (qint64  value){ if(mActualCycles      == value)return; mActualCycles      = value; emit signalEventChangedActualCycles     (value);}
    void    setActualIndex      (qint64  value)
    {
        if(mActualIndex == value)
            return;

        mActualIndex = mSeqTestList.count() == 0 ? -1 : value % mSeqTestList.count();
        emit signalEventChangedActualIndex (mActualIndex);

    }
    void    setIsEdit           (bool    value){ if(mIsEdit            == value)return; mIsEdit            = value; emit signalEventChangedIsEdit           (value);}
    void    setStrStatus        (QString value){ if(mStrStatus         == value)return; mStrStatus         = value; emit signalEventChangedStrStatus        (value);}
    void    setErrMsg           (QString value){ if(mErrMsg            == value)return; mErrMsg            = value; emit signalEventChangedErrMsg           (value);}
    void    setProgress         (int     value){ if(mProgress          == value)return; mProgress          = value; emit signalEventChangedProgress         (value);}

signals:
    void signalEventChangedAccessMode       (int     value);
    void signalEventChangedMode             (int     value);
    void signalEventChangedIsRS232Test      (bool    value);
    void signalEventChangedRunState         (int     value);
    void signalEventChangedTargetCycles     (qint64  value);
    void signalEventChangedTotalActualCycles(qint64  value);
    void signalEventChangedActualCycles     (qint64  value);
    void signalEventChangedActualIndex      (qint64  value);
    void signalEventChangedIsEdit           (bool    value);
    void signalEventChangedStrStatus        (QString value);
    void signalEventChangedErrMsg           (QString value);
    void signalEventChangedProgress         (int     value);

    void signalEventInsertedItem            (int idx, SeqTestItemModel * item);
    void signalEventCompletedSeqTest              ();

public:
    explicit SequencerDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_MODE;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        //ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;
        ENABLE_SLOT_LSETTING_CHANGED_SEQ_PERFORMED_CNT;

        onValveChangedAccess();
        onValveChangedMode();
        onValveChangedIsRS232Test();
        onLSettingChangedSequencerPerformedCnt();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setActualCycles(0);
        setActualIndex(-1);
    }
    ~SequencerDlgModel()
    {
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedMode()
    {
        setMode(pValveSP->getMode());
    }

    void onValveChangedIsRS232Test()
    {
        setIsRS232Test(pValveSP->getIsRS232Test());
    }

    void onLSettingChangedSequencerPerformedCnt()
    {
        setTotalActualCycles(pLSettingSP->mSequencerPerformedCnt);
    }

    Q_INVOKABLE void onCommandLoad(QString filePath)
    {
        mSeqTestList.clear();

        loadSeqTestList(filePath);
        setActualCycles(0);
        setActualIndex(-1);

        resetItem();
    }

    Q_INVOKABLE void onCommandRun()
    {
        if(mSeqTestList.size() < 1 || isAllEmptyCommand())
        {
            return;
        }

        //khko for test
        //static bool isFirst = true;

        switch (getRunState()) {
        case (int)eRunState::RUN_STATE_STOP:
            setActualCycles(0);
            setActualIndex(-1);
            resetItem();
//            if(isFirst)
//            {
//                setActualCycles(271245);
//                foreach(SeqTestItemModel * item, mSeqTestList)
//                {
//                    item->setIsRunnig(false);
//                    item->setSentCount(271245);
//                    item->setRcvCount(271245);
//                }
//            }

        case (int)eRunState::RUN_STATE_PAUSE:
            setRunState((int)eRunState::RUN_STATE_RUN);
            nextRunItem();
            break;

        case (int)eRunState::RUN_STATE_RUN:
            setRunState((int)eRunState::RUN_STATE_PAUSE);
            if(mpReqCmdUserData != nullptr)
                delete mpReqCmdUserData;
            mpReqCmdUserData = nullptr;
            mTimer.stop();
            mSeqTestList.at(getActualIndex())->setIsRunnig(false);
            break;
        }

        //khko for test
        //isFirst = false;
    }

    Q_INVOKABLE void onCommandStop()
    {
        setRunState((int)eRunState::RUN_STATE_STOP);
        if(mpReqCmdUserData != nullptr)
            delete mpReqCmdUserData;
        mpReqCmdUserData = nullptr;
        mTimer.stop();
    }

    Q_INVOKABLE void onCommandResetTotalCycles()
    {
        pLSettingSP->setSequencerPerformedCnt(0);
    }

    Q_INVOKABLE void onCommandInsertItem(int idx, int itemType)
    {
        SeqTestItemModel * pNewItem = new SeqTestItemModel;
        pNewItem->setItemType(itemType);
        mSeqTestList.insert(idx,pNewItem);

        signalEventInsertedItem(idx, pNewItem);
    }

    Q_INVOKABLE void onDeletedItem(SeqTestItemModel * pItem)
    {
        mSeqTestList.removeOne(pItem);
    }

    Q_INVOKABLE void onCommandSetIsEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandSetTargetCycles(int value)
    {
        setTargetCycles(value);
    }

    Q_INVOKABLE void onCommandSaveSeqTestList(QString filePath)
    {
        saveSeqTestList(filePath);

        setIsEdit(false);
    }

    void onTimeout()
    {
        nextRunItem();
    }

    /*
    void onValveWrittenCustomCommand(ValveSProviderDto dto)
    {
        int retryCnt = 0;

        if(dto.mpRef != mpReqCmdUserData)
            return;

        if(mSeqTestList.at(mActualIndex)->getComplete())
        {
            return;
        }

        if(dto.mIsSucc && !dto.mIsNetworkErr)
        {
            mSeqTestList.at(mActualIndex)->setComplete(true);
            return;
        }

        if(dto.mRetryCnt > 1 && (dto.mIsNetworkErr || !dto.mIsSucc))
        {
            mSeqTestList.at(mActualIndex)->setErrCount(mSeqTestList.at(mActualIndex)->getErrCount()+1);
            return;
        }

        retryCnt = dto.mRetryCnt + 1;
        retryItem(retryCnt);
    }
    */

private:    
    QTimer mTimer;

    ReqCommandUserData * mpReqCmdUserData = nullptr;
    QList<SeqTestItemModel *> mSeqTestList;

    void resetItem()
    {
        foreach(SeqTestItemModel * item, mSeqTestList)
        {
            item->setIsRunnig(false);
            item->setSentCount(0);
            item->setRcvCount(0);
        }
    }

    bool isAllEmptyCommand()
    {
        foreach(SeqTestItemModel * item, mSeqTestList)
        {
            if(item->getCommand() != "")
                return false;
        }

        return true;
    }

    void retryItem(int retryCnt)
    {
        SeqTestItemModel * pNextItem = mSeqTestList.at(getActualIndex());

        if(mpReqCmdUserData != nullptr)
            delete mpReqCmdUserData;

        mpReqCmdUserData = new ReqCommandUserData;
        pValveSP->customRequest(pNextItem->getCommand(), mpReqCmdUserData, retryCnt);
    }

    void nextRunItem()
    {
        /*
        if(mpReqCmdUserData != nullptr)
        {
            delete mpReqCmdUserData;
            mpReqCmdUserData = nullptr;
        }

        if(getActualIndex() > -1)
        {
            SeqTestItemModel * pItem = mSeqTestList.at(getActualIndex());
            pItem->setIsRunnig(false);

            if(pItem->getComplete() == false)
            {
                pItem->setErrCount(mSeqTestList.at(mActualIndex)->getErrCount()+1);
            }
        }
        */

        if(getActualIndex() > -1)
        {
            SeqTestItemModel * pItem = mSeqTestList.at(getActualIndex());
            pItem->setIsRunnig(false);
        }

        setActualIndex(getActualIndex() + 1);

        SeqTestItemModel * pNextItem = mSeqTestList.at(getActualIndex());

        if((getMode() == ValveEnumDef::MODE_POWER_FAILURE ||
            getMode() == ValveEnumDef::MODE_SAFETY        ||
            getMode() == ValveEnumDef::MODE_FATAL_ERROR     ) ||
           (getAccessMode() != ValveEnumDef::ACCESS_LOCAL && pNextItem->getItemType() != QmlEnumDef::SEQ_TYPE_CUSTOM))
        {
            setRunState((int)eRunState::RUN_STATE_STOP);
            emit signalEventCompletedSeqTest();
            return;
        }

        if((getActualCycles() >= getTargetCycles()) && (getActualIndex() == 0))
        {
            setRunState((int)eRunState::RUN_STATE_STOP);
            emit signalEventCompletedSeqTest();
            return;
        }

        if(getActualIndex() == mSeqTestList.size() - 1)
        {
            pLSettingSP->setSequencerPerformedCnt(pLSettingSP->mSequencerPerformedCnt + 1);
            setActualCycles(getActualCycles()+1);
        }

        QString command = pNextItem->getCommand();
        pNextItem->setSentCount(pNextItem->getSentCount() + 1);
        pNextItem->setIsRunnig(true);
        pNextItem->setComplete(false);

        //mpReqCmdUserData = new ReqCommandUserData;
        pValveSP->customRequest(command, pNextItem, 0);

        startTimer(pNextItem->mDelayMSec);
    }

    void saveSeqTestList(QString filePath)
    {
        FileWriterEx file;
        int splitIdx = filePath.lastIndexOf("/")+1;
        QString path = filePath.left(splitIdx);
        QString fileName = filePath.mid(splitIdx);

        //if(file.open(QApplication::applicationDirPath(), "seqtest.txt", FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        if(file.open(path, fileName, FileWriterEx::FILE_OPEN_NEWWRITE) == false)
        {
            setErrMsg("File save failed.");
            return;
        }

        file.appendLine(QString("%1").arg(getTargetCycles()));

        foreach(SeqTestItemModel * pItem, mSeqTestList)
        {
            if(pItem->getCommand().length() < 1)
                continue;

            file.appendLine(QString("%1;%2;%3").arg(pItem->getCommand()).arg(pItem->getDelayMSec()).arg(pItem->getItemType()));
        }
        file.close();
    }

    void loadSeqTestList(QString filePath)
    {
        QFile file;
        //file.setFileName(QString("%1/seqtest.txt").arg(QApplication::applicationDirPath()));
        file.setFileName(QString(filePath));
        file.open(QFile::ReadOnly);

        if(file.isOpen() == false)
        {
            //qDebug() << "File open failed! path = " << QApplication::applicationDirPath();
            qDebug() << "File open failed! path = " << filePath;
            onCommandInsertItem(0, QmlEnumDef::SEQ_TYPE_CLOSE);
            return ;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");
        int lineIdx = 0;
        SeqTestItemModel * pItem;

        do{
            QString value = out.readLine();
            QStringList cols;
            int     itemType = QmlEnumDef::SEQ_TYPE_CUSTOM;
            QString cmd;
            int     delayMSec;

            switch (lineIdx) {
            case 0: // times setting
                setTargetCycles(value.toInt());
                break;
            default:
                if(value.length() < 1)
                    break;

                cols = value.split(";");

                if(cols.count() < 2)
                    break;

                if(cols.count() < 3)
                {
                    cmd       = value.split(";")[0];
                    delayMSec = value.split(";")[1].toInt();
                }
                else
                {
                    cmd       = value.split(";")[0];
                    delayMSec = value.split(";")[1].toInt();
                    itemType  = value.split(";")[2].toInt();
                }

                pItem = new SeqTestItemModel(itemType, cmd, delayMSec);
                mSeqTestList.append(pItem);
                emit signalEventInsertedItem(mSeqTestList.size() - 1, pItem);
                break;

            }
            lineIdx++;

        }while(!out.atEnd());

        file.close();

        if(mSeqTestList.count() < 1)
        {
            qDebug() << "can not parsing = " << filePath;
            onCommandInsertItem(0, QmlEnumDef::SEQ_TYPE_CLOSE);
        }
    }

    void startTimer(int delay)
    {
        mTimer.stop();
        mTimer.start(delay);
    }
};

#endif // SEQUENCERDLGMODEL_H
