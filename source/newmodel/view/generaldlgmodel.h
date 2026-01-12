#ifndef GENERALDLGMODEL_H
#define GENERALDLGMODEL_H

#include <QObject>
#include <QList>

#include "source/service/coreservice.h"
#include "source/newmodel/view/tag/viewtagmanager.h"

class GeneralDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mAccessMode  READ getAccessMode   NOTIFY signalEventChangedAccessMode )
    Q_PROPERTY(bool    mIsRS232Test READ getIsRS232Test  NOTIFY signalEventChangedIsRS232Test)
    Q_PROPERTY(bool    mIsEdit      READ getIsEdit       NOTIFY signalEventChangedIsEdit     )
    Q_PROPERTY(QString mStrStatus   READ getStrStatus    NOTIFY signalEventChangedStrStatus  )
    Q_PROPERTY(QString mErrMsg      READ getErrMsg       NOTIFY signalEventChangedErrMsg     )
    Q_PROPERTY(QString mErrMsg2     READ getErrMsg2      NOTIFY signalEventChangedErrMsg2    )
    Q_PROPERTY(int     mProgress    READ getProgress     NOTIFY signalEventChangedProgress   )

public:
    int      mAccessMode  = ValveEnumDef::ACCESS_LOCAL;
    bool     mIsRS232Test = false;
    bool     mIsEdit      = false;
    QString  mStrStatus   = "Loading";
    QString  mErrMsg      = "";
    QString  mErrMsg2     = "";
    int      mProgress    = 0 ;

    int      getAccessMode (){ return mAccessMode ;}
    bool     getIsRS232Test(){ return mIsRS232Test;}
    bool     getIsEdit     (){ return mIsEdit     ;}
    QString  getStrStatus  (){ return mStrStatus  ;}
    QString  getErrMsg     (){ return mErrMsg     ;}
    QString  getErrMsg2    (){ return mErrMsg2    ;}
    int      getProgress   (){ return mProgress   ;}

    void     setAccessMode  (int     value){ if(mAccessMode  == value) return; mAccessMode  = value; emit signalEventChangedAccessMode (value);}
    void     setIsRS232Test (bool    value){ if(mIsRS232Test == value) return; mIsRS232Test = value; emit signalEventChangedIsRS232Test(value);}
    void     setIsEdit      (bool    value){ if(mIsEdit      == value) return; mIsEdit      = value; emit signalEventChangedIsEdit     (value);}
    void     setStrStatus   (QString value){ if(mStrStatus   == value) return; mStrStatus   = value; emit signalEventChangedStrStatus  (value);}
    void     setErrMsg      (QString value){ if(mErrMsg      == value) return; mErrMsg      = value; emit signalEventChangedErrMsg     (value);}
    void     setErrMsg2     (QString value){ if(mErrMsg2     == value) return; mErrMsg2     = value; emit signalEventChangedErrMsg2    (value);}
    void     setProgress    (int     value){ if(mProgress    == value) return; mProgress    = value; emit signalEventChangedProgress   (value);}

signals:
    void signalEventChangedAccessMode (int     value);
    void signalEventChangedIsRS232Test(bool    value);
    void signalEventChangedIsEdit     (bool    value);
    void signalEventChangedStrStatus  (QString value);
    void signalEventChangedErrMsg     (QString value);
    void signalEventChangedErrMsg2    (QString value);
    void signalEventChangedProgress   (int     value);

public:
    explicit GeneralDlgModel(QObject *parent = nullptr): QObject(parent){
        pTagManager = ViewTagManager::getInstance();

        initalizeTag();

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
    ~GeneralDlgModel(){}

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
        QString value = nullptr;
        ProtocolModel * currentProtocol = getCurrentProtocol();
        if(dto.mReqDto.mpRef != currentProtocol)
            return;

        if (mState != STATE_MONITOR ||((mState == STATE_MONITOR) && (mMonitorDebugCount%100 == 0)))
        {
            qDebug() << "[" << Q_FUNC_INFO << "]" << dto.mReqDto.mReqCommand << "," << dto.mResData;
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
            currentProtocol->SetIsSupport(true);
            currentProtocol->SetReponseData(dto.mResData, bDebug);
        }

        switch((int)mState)
        {
        case STATE_INIT    : mInitProtocolIdx    ++; break;
        case STATE_REFRESH : mReadProtocolIdx    ++; break;
        case STATE_MONITOR : mMonitorProtocolIdx ++; break;
        }
        startTimer();
    }

    void onValveWrittenPmCommit(ValveResponseDto dto)
    {
        QString value = nullptr;
        ProtocolModel * currentProtocol = getCurrentProtocol();
        if(dto.mReqDto.mpRef != currentProtocol)
            return;

        qDebug() << "[" << Q_FUNC_INFO << "]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

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
        startTimer();
    }

public slots:
    Q_INVOKABLE ViewTagModel * loadInitTag(QString path)
    {
        qDebug() << "[" << Q_FUNC_INFO << "]" << path;

        ViewTagModel * pTag;
        pTag = pTagManager->GetTag(path);
        mUseTagList.append(pTag);

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

    Q_INVOKABLE ViewTagModel * getTag(QString path)
    {



        ViewTagModel * pTag;
        pTag = pTagManager->GetTag(path);

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

    Q_INVOKABLE void addMonotoringTag(ViewTagModel * pTag)
    {
        if(pTag == nullptr)
        {
            qDebug() << "[" << Q_FUNC_INFO << "]null porinter";
            return;
        }

        qDebug() << "[" << Q_FUNC_INFO << "]" << pTag->getName();

        ProtocolModel * protocol;

        protocol = (ProtocolModel *)pTag->ReadProtocol;

        if(protocol == nullptr)
            return;

        if(mMonitorProtocolList.contains(protocol) == false)
        {
            mMonitorProtocolList.append(protocol);
        }
    }

    Q_INVOKABLE void clearMonitorTag()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
        mMonitorProtocolList.clear();
    }

    Q_INVOKABLE void refresh()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";
        mReadProtocolIdx = 0;
        mState = STATE_REFRESH;

        ProtocolModel * protocol;

        mReadProtocolList.clear();

        foreach (ViewTagModel * tempTag, mUseTagList) {
            protocol = (ProtocolModel *)tempTag->ReadProtocol;

            if(protocol == nullptr)
                continue;

            if(mReadProtocolList.contains(protocol) == false)
            {
                mReadProtocolList.append(protocol);
            }
        }

        startTimer();
    }

    Q_INVOKABLE void apply()
    {
        qDebug() << "[" << Q_FUNC_INFO << "]";

        mWriteProtocolIdx = 0;
        mState = STATE_WRITE;

        ProtocolModel * writeProtocol;
        ProtocolModel * readProtocol;

        mWriteProtocolList.clear();
        mReadProtocolList.clear();

        foreach (ViewTagModel * tempTag, mUseTagList) {
            readProtocol = (ProtocolModel *)tempTag->ReadProtocol;
            writeProtocol = (ProtocolModel *)tempTag->WriteProtocol;

            if(tempTag->IsEdit == false)
                continue;

            if(mWriteProtocolList.contains(writeProtocol) == false)
            {
                mWriteProtocolList.append(writeProtocol);

                qDebug() << "[" << Q_FUNC_INFO << "]Write = " << writeProtocol->Path;
            }

            if(readProtocol != nullptr && mReadProtocolList.contains(readProtocol) == false)
            {
                mReadProtocolList.append(readProtocol);

                qDebug() << "[" << Q_FUNC_INFO << "]Read = " << readProtocol->Path;
            }
        }
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
                pValveSP->pmSyncRequest(pProtocol->MakeReadCmd(), pProtocol, 0);
            }
            else
            {
                mState = STATE_REFRESH;
                startTimer();
                return;
            }
            break;

        case (int)STATE_REFRESH:
            if(mReadProtocolList.size() > mReadProtocolIdx)
            {
                pProtocol = mReadProtocolList[mReadProtocolIdx];
                qDebug() << "[" << Q_FUNC_INFO <<"]STATE_REFRESH : " << pProtocol->MakeReadCmd();
                pValveSP->pmSyncRequest(pProtocol->MakeReadCmd(), pProtocol, 0);
            }
            else
            {
                mState = STATE_MONITOR;
                startTimer();
                return;
            }
            break;

        case (int)STATE_MONITOR:
            if(mMonitorProtocolList.size() == 0)
            {
                mState = STATE_NONE;
            }
            else
            {
                if(mMonitorProtocolList.size() <= mMonitorProtocolIdx)
                {
                    mMonitorProtocolIdx = 0;
                    mMonitorDebugCount ++;
                }

                pProtocol = mMonitorProtocolList[mMonitorProtocolIdx];
                pValveSP->pmSyncRequest(pProtocol->MakeReadCmd(), pProtocol, 0);
            }
            break;

        case (int)STATE_WRITE:
            if(mWriteProtocolList.size() > mWriteProtocolIdx)
            {
                pProtocol = mWriteProtocolList[mWriteProtocolIdx];
                pValveSP->pmCommitRequest(pProtocol->MakeWriteCmd(), pProtocol, 0);
            }
            else
            {
                mReadProtocolIdx = 0;
                mState = STATE_REFRESH;
                startTimer();
                return;
            }
            break;
        }
    }

protected:
    enum eState{
        STATE_NONE = 0,
        STATE_INIT = 1,
        STATE_REFRESH = 2,
        STATE_WRITE = 3,
        STATE_MONITOR = 4
    };

    ViewTagManager * pTagManager;
    QTimer mTimer;
    bool   mIsWritten     = false;

    eState mState = STATE_NONE;
    QList<ViewTagModel *> mUseTagList;
    QList<ProtocolModel *> mInitProtocolList;
    int mInitProtocolIdx = 0;
    QList<ProtocolModel *> mMonitorProtocolList;
    int mMonitorProtocolIdx = 0;
    int mMonitorDebugCount;
    QList<ProtocolModel *> mReadProtocolList;
    int mReadProtocolIdx = 0;
    QList<ProtocolModel *> mWriteProtocolList;
    int mWriteProtocolIdx = 0;

    void initalizeTag()
    {
        //ViewTagModel * tag;
        //tag = pTagManager->GetTag("Cluster.Settings.Number of Valves"           ); mUseTagList.append(tag);
        //tag = pTagManager->GetTag("Cluster.Settings.Cluster Address"            ); mUseTagList.append(tag);
        //tag = pTagManager->GetTag("Cluster.Settings.Show Address on Display"    ); mUseTagList.append(tag);
        //tag = pTagManager->GetTag("Cluster.Settings.Connection Loss Reaction"   ); mUseTagList.append(tag);
        //tag = pTagManager->GetTag("Cluster.Settings.Disable Interlocks of Slave"); mUseTagList.append(tag);
    }

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
            if(mMonitorProtocolList.size() > mMonitorProtocolIdx)
            {
                return mMonitorProtocolList[mMonitorProtocolIdx];
            }
            break;

        case (int)STATE_REFRESH:
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
#endif // GENERALDLGMODEL_H
