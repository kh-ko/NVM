#ifndef VIEWTAGCONTAINERMODEL_H
#define VIEWTAGCONTAINERMODEL_H

#include <QObject>
#include <QList>

#include "source/service/coreservice.h"
#include "source/newmodel/protocol/protocolmanager.h"

class ViewTagContainerModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mAccessMode  READ getAccessMode   NOTIFY signalEventChangedAccessMode )
    Q_PROPERTY(bool    mIsRS232Test READ getIsRS232Test  NOTIFY signalEventChangedIsRS232Test)
    Q_PROPERTY(bool    mIsEdit      READ getIsEdit       NOTIFY signalEventChangedIsEdit     )
    Q_PROPERTY(QString mStrStatus   READ getStrStatus    NOTIFY signalEventChangedStrStatus  )
    Q_PROPERTY(QString mErrMsg      READ getErrMsg       NOTIFY signalEventChangedErrMsg     )
    Q_PROPERTY(QString mErrMsg2     READ getErrMsg2      NOTIFY signalEventChangedErrMsg2    )
    Q_PROPERTY(double  mProgress    READ getProgress     NOTIFY signalEventChangedProgress   )

public:
    int      mAccessMode  = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test = false;
    bool     mIsEdit      = false;
    QString  mStrStatus   = "Loading";
    QString  mErrMsg      = "";
    QString  mErrMsg2     = "";
    double   mProgress    = 0 ;

    int      getAccessMode (){ return mAccessMode ;}
    bool     getIsRS232Test(){ return mIsRS232Test;}
    bool     getIsEdit     (){ return mIsEdit     ;}
    QString  getStrStatus  (){ return mStrStatus  ;}
    QString  getErrMsg     (){ return mErrMsg     ;}
    QString  getErrMsg2    (){ return mErrMsg2    ;}
    double   getProgress   (){ return mProgress   ;}

    void     setAccessMode  (int     value){ if(mAccessMode  == value) return; mAccessMode  = value; emit signalEventChangedAccessMode (value);}
    void     setIsRS232Test (bool    value){ if(mIsRS232Test == value) return; mIsRS232Test = value; emit signalEventChangedIsRS232Test(value);}
    void     setIsEdit      (bool    value){ if(mIsEdit      == value) return; mIsEdit      = value; emit signalEventChangedIsEdit     (value);}
    void     setStrStatus   (QString value){ if(mStrStatus   == value) return; mStrStatus   = value; emit signalEventChangedStrStatus  (value);}
    void     setErrMsg      (QString value){ if(mErrMsg      == value) return; mErrMsg      = value; emit signalEventChangedErrMsg     (value);}
    void     setErrMsg2     (QString value){ if(mErrMsg2     == value) return; mErrMsg2     = value; emit signalEventChangedErrMsg2    (value);}
    void     setProgress    (double  value){ if(mProgress    == value) return; mProgress    = value; emit signalEventChangedProgress   (value);}

signals:
    void signalEventChangedAccessMode (int     value);
    void signalEventChangedIsRS232Test(bool    value);
    void signalEventChangedIsEdit     (bool    value);
    void signalEventChangedStrStatus  (QString value);
    void signalEventChangedErrMsg     (QString value);
    void signalEventChangedErrMsg2    (QString value);
    void signalEventChangedProgress   (double  value);

public:
    explicit ViewTagContainerModel(QObject *parent = nullptr): QObject(parent){
        pProtocolManager = ProtocolManager::getInstance();

        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_WRITTEN_PM_SYNC;
        ENABLE_SLOT_VALVE_WRITTEN_PM_COMMIT;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        mIsWritten = false;
    }
    ~ViewTagContainerModel(){}

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedIsRS232Test()
    {
        setIsRS232Test(pValveSP->getIsRS232Test());
    }

    void onValveWrittenPmSync(ValveResponseDto dto)
    {
        bool bDebug = false;
        ProtocolModel * currentProtocol = getCurrentProtocol();

        if(dto.mReqDto.mpRef != this || dto.mReqDto.mpSubRef != currentProtocol)
            return;

        if (mState != STATE_MONITOR ||((mState == STATE_MONITOR) && (mMonitoringDebugCount%100 == 0)))
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << currentProtocol->Name << ","<< dto.mReqDto.mReqCommand << "," << dto.mResData;
            bDebug = true;
        }

        if(dto.mIsNetworkErr)
        {
            startTimer();
            return;
        }

        if(dto.mResData.startsWith("E:") || dto.mResData.startsWith("E:"))
        {
            currentProtocol->SetIsSupport(false);
        }
        else
        {
            //if(dto.mResData.startsWith("i:9301")){dto.mResData = "i:9301100000+3000010000011000000000000000100000";}
            //if(dto.mResData.startsWith("i:9302")){dto.mResData = "i:9302090000-3000001001020100000000000000010000";}
            //if(dto.mResData.startsWith("i:9303")){dto.mResData = "i:930308000003000000900130010000000000000001000";}
            //if(dto.mResData.startsWith("i:9304")){dto.mResData = "i:930407000000300000800240001000000000000000100";}
            //if(dto.mResData.startsWith("i:9305")){dto.mResData = "i:930506000000030000700050000100000000000000010";}
            //if(dto.mResData.startsWith("i:9306")){dto.mResData = "i:930605000000003000600060000001000000000000001";}
            //if(dto.mResData.startsWith("i:9307")){dto.mResData = "i:930704000000000300500070000000010000000000000";}
            //if(dto.mResData.startsWith("i:9308")){dto.mResData = "i:9308030000+03000004000C0000000001000000000000";}
            //if(dto.mResData.startsWith("i:9309")){dto.mResData = "i:9309020000-00030003000D0000000000100000000000";}
            //if(dto.mResData.startsWith("i:930A")){dto.mResData = "i:930A001000000000000100E0000000000010000000000";}

            currentProtocol->SetIsSupport(true);
            currentProtocol->SetReponseData(dto.mResData, bDebug);
        }

        switch((int)mState)
        {
        case STATE_INIT    : mInitProtocolIdx       ++; setProgress( mInitProtocolIdx/(double)mInitProtocolList.size()); break;
        case STATE_READ    : mReadProtocolIdx       ++; setProgress( mReadProtocolIdx/(double)mReadProtocolList.size()); break;
        case STATE_MONITOR : mMonitoringProtocolIdx ++; break;
        }
        startTimer();
    }

    void onValveWrittenPmCommit(ValveResponseDto dto)
    {
        ProtocolModel * currentProtocol = getCurrentProtocol();

        if(dto.mReqDto.mpRef != this || dto.mReqDto.mpSubRef != currentProtocol)
            return;

        qDebug() << "[" << Q_FUNC_INFO << "]" << currentProtocol->Name << ","<< dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(dto.mIsNetworkErr)
        {
            startTimer();
            return;
        }

        if(dto.mResData.startsWith("E:") || dto.mResData.startsWith("E:"))
        {
            currentProtocol->SetIsSupport(false);
        }

        mWriteProtocolIdx ++;

        setProgress( mWriteProtocolIdx/(double)mWriteProtocolList.size());
        startTimer();
    }

public slots:
    Q_INVOKABLE void createDNetEdsFile(QString path){


    }

    Q_INVOKABLE TagModel * getTag(QString path)
    {
        TagModel * pTag;
        pTag = pProtocolManager->FindTag(path);

        if(pTag == nullptr)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << path << " is null pointer";
        }
        else
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << path;
        }
        return pTag;
    }

    Q_INVOKABLE void addTag(QList<TagModel *> * pTagList, TagModel * pTag)
    {
        if(pTagList->contains(pTag) == false)
            pTagList->append(pTag);
    }

    Q_INVOKABLE void addProtocol(QList<ProtocolModel *> * pProtocolList, TagModel * pTag)
    {
        ProtocolModel * protocol;

        protocol = (ProtocolModel *)pTag->ReadProtocol;

        if(protocol == nullptr)
            return;

        if(pProtocolList->contains(protocol) == false)
            pProtocolList->append(protocol);
    }

    Q_INVOKABLE void addInitTag      (TagModel * pTag){if(pTag==nullptr){qDebug() << "[" << Q_FUNC_INFO << "]null porinter";return;} qDebug() << "[" << Q_FUNC_INFO << "]" << pTag->getName(); addTag(&mInitTagList      , pTag); addProtocol(&mInitProtocolList      , pTag);}
    Q_INVOKABLE void addMonotoringTag(TagModel * pTag){if(pTag==nullptr){qDebug() << "[" << Q_FUNC_INFO << "]null porinter";return;} qDebug() << "[" << Q_FUNC_INFO << "]" << pTag->getName(); addTag(&mMonitoringTagList, pTag); addProtocol(&mMonitoringProtocolList, pTag);}
    Q_INVOKABLE void addRWTag        (TagModel * pTag){if(pTag==nullptr){qDebug() << "[" << Q_FUNC_INFO << "]null porinter";return;} qDebug() << "[" << Q_FUNC_INFO << "]" << pTag->getName(); addTag(&mRWTagList        , pTag); }
    Q_INVOKABLE void addAlwaysReadTag(TagModel * pTag){if(pTag==nullptr){qDebug() << "[" << Q_FUNC_INFO << "]null porinter";return;} qDebug() << "[" << Q_FUNC_INFO << "]" << pTag->getName(); addTag(&mAlwaysReadTagList, pTag); }
    Q_INVOKABLE void clearInitTag      (){ mInitTagList.clear()      ; mInitProtocolList.clear()      ;}
    Q_INVOKABLE void clearMonitoringTag(){ mMonitoringTagList.clear(); mMonitoringProtocolList.clear();}
    Q_INVOKABLE void clearRWTag        (){ mRWTagList.clear()        ;                                 }
    Q_INVOKABLE void clearAlwaysReadTag(){ mAlwaysReadTagList.clear();                                 }


    Q_INVOKABLE void refresh()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
        setProgress(0);

        mInitProtocolIdx       = 0;
        mMonitoringProtocolIdx = 0;
        mReadProtocolIdx       = 0;
        mWriteProtocolIdx      = 0;

        ProtocolModel * protocol;

        mWriteProtocolList.clear();
        mReadProtocolList.clear();

        foreach (TagModel * tempTag, mRWTagList) {
            protocol = (ProtocolModel *)tempTag->ReadProtocol;

            if(protocol == nullptr)
                continue;

            if(mReadProtocolList.contains(protocol) == false)
            {
                mReadProtocolList.append(protocol);
            }
        }

        foreach(TagModel * tempTag, mAlwaysReadTagList) {
            protocol = (ProtocolModel *)tempTag->ReadProtocol;

            if(protocol != nullptr && mReadProtocolList.contains(protocol) == false)
            {
                mReadProtocolList.append(protocol);

                qDebug() << "[" << Q_FUNC_INFO << "]Read = " << protocol->ReqProtocol;
            }
        }

        if(mInitTagList.size() == 0 && mWriteProtocolList.size() == 0 && mReadProtocolList.size() == 0)
        {
            setProgress(1);
        }

        mState = STATE_INIT;

        startTimer();
    }

    Q_INVOKABLE void apply()
    {
        bool isContainedParam = false;
        ProtocolModel * readProtocol;
        ProtocolModel * writeProtocol;

        qDebug() << "[" << Q_FUNC_INFO << "]";
        setProgress(0);

        mReadProtocolIdx  = 0;
        mWriteProtocolIdx = 0;

        mWriteProtocolList.clear();
        mWritePacketList.clear();
        mReadProtocolList.clear();

        foreach (TagModel * tempTag, mRWTagList) {

            if(tempTag->IsEdit == false)
                continue;

            readProtocol = (ProtocolModel *)tempTag->ReadProtocol;
            writeProtocol = (ProtocolModel *)tempTag->WriteProtocol;

            if(mWriteProtocolList.contains(writeProtocol) == false)
            {
                if(writeProtocol->IsParam){ isContainedParam = true; }

                mWriteProtocolList.append(writeProtocol);
                mWritePacketList.append(writeProtocol->MakeWriteCmd());

                qDebug() << "[" << Q_FUNC_INFO << "]Write = " << writeProtocol->MakeWriteCmd();
            }

            if(readProtocol != nullptr && mReadProtocolList.contains(readProtocol) == false)
            {
                mReadProtocolList.append(readProtocol);

                qDebug() << "[" << Q_FUNC_INFO << "]Read = " << readProtocol->ReqProtocol;
            }
        }

        if(isContainedParam)
        {
            mWriteProtocolList.insert(0, pProtocolManager->pParamWriteStartProtocol);
            mWritePacketList.insert(0, pProtocolManager->pParamWriteStartProtocol->MakeWriteCmd());

            mWriteProtocolList.append(pProtocolManager->pParamWriteEndProtocol);
            mWritePacketList.append(pProtocolManager->pParamWriteEndProtocol->MakeWriteCmd());
        }

        foreach (TagModel * tempTag, mRWTagList) {
            tempTag->IsEdit = false;
        }

        foreach(TagModel * tempTag, mAlwaysReadTagList) {
            readProtocol = (ProtocolModel *)tempTag->ReadProtocol;

            if(readProtocol != nullptr && mReadProtocolList.contains(readProtocol) == false)
            {
                mReadProtocolList.append(readProtocol);

                qDebug() << "[" << Q_FUNC_INFO << "]Read = " << readProtocol->ReqProtocol;
            }
        }

        mState = STATE_WRITE;

        startTimer();
    }

    void onTimeout()
    {
        ProtocolModel * pProtocol = nullptr;

        switch((int)mState)
        {
        case (int)STATE_INIT:
            if(mInitProtocolList.size() > mInitProtocolIdx)
            {
                pProtocol = mInitProtocolList[mInitProtocolIdx];
                qDebug() << "[" << Q_FUNC_INFO <<"]STATE_INIT : " << pProtocol->MakeReadCmd();
                pValveSP->pmSyncRequest(pProtocol->MakeReadCmd(), this, pProtocol, 0);
            }
            else
            {
                mState = STATE_READ;
                startTimer();
                return;
            }
            break;

        case (int)STATE_READ:
            if(mReadProtocolList.size() > mReadProtocolIdx)
            {
                pProtocol = mReadProtocolList[mReadProtocolIdx];
                qDebug() << "[" << Q_FUNC_INFO <<"]STATE_READ : " << pProtocol->MakeReadCmd();
                pValveSP->pmSyncRequest(pProtocol->MakeReadCmd(), this, pProtocol, 0);
            }
            else
            {
                mState = STATE_MONITOR;
                startTimer();
                return;
            }
            break;

        case (int)STATE_MONITOR:
            if(mMonitoringProtocolList.size() == 0)
            {
                mState = STATE_NONE;
            }
            else
            {
                if(mMonitoringProtocolList.size() <= mMonitoringProtocolIdx)
                {
                    mMonitoringProtocolIdx = 0;
                    mMonitoringDebugCount ++;
                }

                pProtocol = mMonitoringProtocolList[mMonitoringProtocolIdx];
                pValveSP->pmSyncRequest(pProtocol->MakeReadCmd(), this, pProtocol, 0);
            }
            break;

        case (int)STATE_WRITE:
            if(mWriteProtocolList.size() > mWriteProtocolIdx)
            {
                pProtocol = mWriteProtocolList[mWriteProtocolIdx];
                pValveSP->pmCommitRequest(mWritePacketList[mWriteProtocolIdx], this, pProtocol, 0);
            }
            else
            {
                mState = STATE_READ;
                startTimer();
                return;
            }
            break;
        }
    }

protected:
    enum eState{
        STATE_NONE    = 0,
        STATE_INIT    = 1,
        STATE_READ    = 2,
        STATE_MONITOR = 3,
        STATE_WRITE   = 4,

    };

    ProtocolManager * pProtocolManager;
    QTimer mTimer;
    bool   mIsWritten     = false;

    eState mState = STATE_NONE;
    QList<TagModel *> mInitTagList;
    QList<ProtocolModel *> mInitProtocolList;
    int mInitProtocolIdx = 0;

    QList<TagModel *> mMonitoringTagList;
    QList<ProtocolModel *> mMonitoringProtocolList;
    int mMonitoringProtocolIdx = 0;
    int mMonitoringDebugCount = 0;

    QList<TagModel *> mRWTagList;
    QList<ProtocolModel *> mReadProtocolList;
    int mReadProtocolIdx = 0;
    QList<ProtocolModel *> mWriteProtocolList;
    QStringList mWritePacketList;
    int mWriteProtocolIdx = 0;

    QList<TagModel *> mAlwaysReadTagList;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(20);
    }

    ProtocolModel * getCurrentProtocol()
    {
        switch((int)mState)
        {
        case (int)STATE_INIT:
            if(mInitProtocolList.size() > mInitProtocolIdx)
            {
                return mInitProtocolList[mInitProtocolIdx];
            }
            break;

        case (int)STATE_MONITOR:
            if(mMonitoringProtocolList.size() > mMonitoringProtocolIdx)
            {
                return mMonitoringProtocolList[mMonitoringProtocolIdx];
            }
            break;

        case (int)STATE_READ:
            if(mReadProtocolList.size() > mReadProtocolIdx)
            {
                return mReadProtocolList[mReadProtocolIdx];
            }
            break;

        case (int)STATE_WRITE:
            if(mWriteProtocolList.size() > mWriteProtocolIdx)
            {
                return mWriteProtocolList[mWriteProtocolIdx];
            }
            break;
        }
        return nullptr;
    }
};
#endif // VIEWTAGCONTAINERMODEL_H
