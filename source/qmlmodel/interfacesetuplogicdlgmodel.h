#ifndef INTERFACESETUPLOGICDLGMODEL_H
#define INTERFACESETUPLOGICDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class InterfaceSetupLogicDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode          READ getAccessMode          NOTIFY signalEventChangedAccessMode       )
    Q_PROPERTY(bool     mIsRS232Test         READ getIsRS232Test         NOTIFY signalEventChangedIsRS232Test      )
    Q_PROPERTY(int      mDIOpen              READ getDIOpen              NOTIFY signalEventChangedDIOpen           )
    Q_PROPERTY(int      mDIClose             READ getDIClose             NOTIFY signalEventChangedDIClose          )
    Q_PROPERTY(int      mDOOpen              READ getDOOpen              NOTIFY signalEventChangedDOOpen           )
    Q_PROPERTY(int      mDOClose             READ getDOClose             NOTIFY signalEventChangedDOClose          )
    Q_PROPERTY(int      mLearnRange          READ getLearnRange          NOTIFY signalEventChangedLearnRange       )
    //Q_PROPERTY(int      mRangeFactor         READ getRangeFactor         NOTIFY signalEventChangedRangeFactor      )
    Q_PROPERTY(bool     mErrDIOpen           READ getErrDIOpen           NOTIFY signalEventChangedErrDIOpen        )
    Q_PROPERTY(bool     mErrDIClose          READ getErrDIClose          NOTIFY signalEventChangedErrDIClose       )
    Q_PROPERTY(bool     mErrDOOpen           READ getErrDOOpen           NOTIFY signalEventChangedErrDOOpen        )
    Q_PROPERTY(bool     mErrDOClose          READ getErrDOClose          NOTIFY signalEventChangedErrDOClose       )
    Q_PROPERTY(bool     mErrLearnRange       READ getErrLearnRange       NOTIFY signalEventChangedErrLearnRange    )
    //Q_PROPERTY(bool     mErrRangeFactor      READ getErrRangeFactor      NOTIFY signalEventChangedErrRangeFactor   )
    Q_PROPERTY(bool     mIsEdit              READ getIsEdit              NOTIFY signalEventChangedIsEdit           )
    Q_PROPERTY(QString  mStrStatus           READ getStrStatus           NOTIFY signalEventChangedStrStatus        )
    Q_PROPERTY(QString  mErrMsg              READ getErrMsg              NOTIFY signalEventChangedErrMsg           )
    Q_PROPERTY(QString  mErrMsg2             READ getErrMsg2             NOTIFY signalEventChangedErrMsg2          )
    Q_PROPERTY(int      mProgress            READ getProgress            NOTIFY signalEventChangedProgress         )

public:
    int     mAccessMode               = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test              = false;
    int     mDIOpen                   = 0;
    int     mDIClose                  = 0;
    int     mDOOpen                   = 0;
    int     mDOClose                  = 0;
    int     mLearnRange               = 0;
    //int     mRangeFactor              = 0;
    bool    mErrDIOpen                = false;
    bool    mErrDIClose               = false;
    bool    mErrDOOpen                = false;
    bool    mErrDOClose               = false;
    bool    mErrLearnRange            = false;
    //bool    mErrRangeFactor           = false;
    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    QString mErrMsg2                  = "";
    int     mProgress                 = 0 ;

    int     getAccessMode             (){ return mAccessMode             ;}
    bool    getIsRS232Test            (){ return mIsRS232Test            ;}
    int     getDIOpen                 (){ return mDIOpen                 ;}
    int     getDIClose                (){ return mDIClose                ;}
    int     getDOOpen                 (){ return mDOOpen                 ;}
    int     getDOClose                (){ return mDOClose                ;}
    int     getLearnRange             (){ return mLearnRange             ;}
    //int     getRangeFactor            (){ return mRangeFactor            ;}
    bool    getErrDIOpen              (){ return mErrDIOpen              ;}
    bool    getErrDIClose             (){ return mErrDIClose             ;}
    bool    getErrDOOpen              (){ return mErrDOOpen              ;}
    bool    getErrDOClose             (){ return mErrDOClose             ;}
    bool    getErrLearnRange          (){ return mErrLearnRange          ;}
    //bool    getErrRangeFactor         (){ return mErrRangeFactor         ;}
    bool    getIsEdit                 (){ return mIsEdit                 ;}
    QString getStrStatus              (){ return mStrStatus              ;}
    QString getErrMsg                 (){ return mErrMsg                 ;}
    QString getErrMsg2                (){ return mErrMsg2                ;}
    int     getProgress               (){ return mProgress               ;}

    void    setAccessMode             (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode             (value);}
    void    setIsRS232Test            (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test            (value);}
    void    setDIOpen                 (int     value){ if(mDIOpen                  == value)return; mDIOpen                  = value; emit signalEventChangedDIOpen                 (value);}
    void    setDIClose                (int     value){ if(mDIClose                 == value)return; mDIClose                 = value; emit signalEventChangedDIClose                (value);}
    void    setDOOpen                 (int     value){ if(mDOOpen                  == value)return; mDOOpen                  = value; emit signalEventChangedDOOpen                 (value);}
    void    setDOClose                (int     value){ if(mDOClose                 == value)return; mDOClose                 = value; emit signalEventChangedDOClose                (value);}
    void    setLearnRange             (int     value){ if(mLearnRange              == value)return; mLearnRange              = value; emit signalEventChangedLearnRange             (value);}
    //void    setRangeFactor            (int     value){ if(mRangeFactor             == value)return; mRangeFactor             = value; emit signalEventChangedRangeFactor            (value);}
    void    setErrDIOpen              (bool    value){ if(mErrDIOpen               == value)return; mErrDIOpen               = value; emit signalEventChangedErrDIOpen              (value);}
    void    setErrDIClose             (bool    value){ if(mErrDIClose              == value)return; mErrDIClose              = value; emit signalEventChangedErrDIClose             (value);}
    void    setErrDOOpen              (bool    value){ if(mErrDOOpen               == value)return; mErrDOOpen               = value; emit signalEventChangedErrDOOpen              (value);}
    void    setErrDOClose             (bool    value){ if(mErrDOClose              == value)return; mErrDOClose              = value; emit signalEventChangedErrDOClose             (value);}
    void    setErrLearnRange          (bool    value){ if(mErrLearnRange           == value)return; mErrLearnRange           = value; emit signalEventChangedErrLearnRange          (value);}
    //void    setErrRangeFactor         (bool    value){ if(mErrRangeFactor          == value)return; mErrRangeFactor          = value; emit signalEventChangedErrRangeFactor         (value);}
    void    setIsEdit                 (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                 (value);}
    void    setStrStatus              (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus              (value);}
    void    setErrMsg                 (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                 (value);}
    void    setErrMsg2                (QString value){ if(mErrMsg2                 == value)return; mErrMsg2                 = value; emit signalEventChangedErrMsg2                (value);}
    void    setProgress               (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress               (value);}

signals:
    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedDIOpen                 (int     value);
    void signalEventChangedDIClose                (int     value);
    void signalEventChangedDOOpen                 (int     value);
    void signalEventChangedDOClose                (int     value);
    void signalEventChangedLearnRange             (int     value);
    //void signalEventChangedRangeFactor            (int     value);
    void signalEventChangedErrDIOpen              (bool    value);
    void signalEventChangedErrDIClose             (bool    value);
    void signalEventChangedErrDOOpen              (bool    value);
    void signalEventChangedErrDOClose             (bool    value);
    void signalEventChangedErrLearnRange          (bool    value);
    //void signalEventChangedErrRangeFactor         (bool    value);
    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedErrMsg2                (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );

public:
    explicit InterfaceSetupLogicDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_LOGIC;
        ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_LOGIC;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ);
    }
    ~InterfaceSetupLogicDlgModel()
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
    void onValveReadedInterfaceConfigLogic(ValveResponseInterfaceConfigLogicDto dto)
    {
        if(mState != eState::STATE_READ || dto.mReqDto.mpRef != this)
            return;

         setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        if(mIsWritten)
        {
            setErrDIOpen    (dto.mDIOpen     != mWriteDIOpen    );
            setErrDIClose   (dto.mDIClose    != mWriteDIClose   );
            setErrDOOpen    (dto.mDOOpen     != mWriteDOOpen    );
            setErrDOClose   (dto.mDOClose    != mWriteDOClose   );
            setErrLearnRange(dto.mLearnRange != mWriteLearnRange);

            onCommandSetEdit(getErrDIOpen() || getErrDIClose() || getErrDOOpen() || getErrDOClose() || getErrLearnRange());
        }
        else
        {
            setDIOpen     (dto.mDIOpen    );
            setDIClose    (dto.mDIClose   );
            setDOOpen     (dto.mDOOpen    );
            setDOClose    (dto.mDOClose   );
            setLearnRange (dto.mLearnRange);
        }

        setState((eState)(mState + 1));
    }

    Q_INVOKABLE void onCommandSetEdit(bool value)
    {
        setIsEdit(value);
    }

    Q_INVOKABLE void onCommandApply(int diOpen, int diClose, int doOpen, int doClose, int learnRange)
    {
        mIsWritten       = true;
        mWriteDIOpen     = diOpen;
        mWriteDIClose    = diClose;
        mWriteDOOpen     = doOpen;
        mWriteDOClose    = doClose;
        mWriteLearnRange = learnRange;

        setErrMsg2("");

        setState(eState::STATE_WRITE);
    }

    void onValveWrittenInterfaceConfigLogic(ValveResponseDto dto)
    {
        if(mState != eState::STATE_WRITE || dto.mReqDto.mpRef != this)
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
    enum eState{
        STATE_WRITE = 0,
        STATE_READ  = STATE_WRITE + 1,
        STATE_READY = STATE_READ  + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ;

    bool mIsWritten = false;
    int  mWriteDIOpen;
    int  mWriteDIClose;
    int  mWriteDOOpen;
    int  mWriteDOClose;
    int  mWriteLearnRange;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        if(!mIsWritten && state == eState::STATE_READY)
        {
            emit signalEventCompletedLoad();
        }

        mState = state;

        if(state < (int) eState::STATE_READY && state >= (int) eState::STATE_READ)
        {
            setStrStatus("loading");
        }
        else if(state < (int) eState::STATE_READ && state >= (int) eState::STATE_WRITE)
        {
            setStrStatus("writting");
        }
        else
        {
            setStrStatus("ready");
        }

        if(state == eState::STATE_READY)
        {
            setProgress(100);
        }
        else
        {
            setProgress(qFloor((state * 100) / eState::STATE_READY));
            startTimer();
        }
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ:
            pValveSP->readInterfaceConfigLogic(this);
            break;

        case (int)eState::STATE_WRITE:
            pValveSP->setInterfaceConfigLogic(mWriteDIOpen, mWriteDIClose, mWriteDOOpen, mWriteDOClose, mWriteLearnRange, this);
            break;
        }
    }

};
#endif // INTERFACESETUPLOGICDLGMODEL_H
