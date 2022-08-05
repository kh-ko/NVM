#ifndef INTERFACESTATUSRS232DLGMODEL_H
#define INTERFACESTATUSRS232DLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class InterfaceStatusRS232DlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode               READ getAccessMode                NOTIFY signalEventChangedAccessMode               )
    Q_PROPERTY(bool     mIsRS232Test              READ getIsRS232Test               NOTIFY signalEventChangedIsRS232Test              )
    Q_PROPERTY(int      mDIOpenValveIdx           READ getDIOpenValveIdx            NOTIFY signalEventChangedDIOpenValveIdx           )
    Q_PROPERTY(int      mDICloseValveIdx          READ getDICloseValveIdx           NOTIFY signalEventChangedDICloseValveIdx          )
    Q_PROPERTY(int      mStatusDIOpen             READ getStatusDIOpen              NOTIFY signalEventChangedStatusDIOpen             )
    Q_PROPERTY(int      mStatusDIClose            READ getStatusDIClose             NOTIFY signalEventChangedStatusDIClose            )
    Q_PROPERTY(int      mStatusDOOpen             READ getStatusDOOpen              NOTIFY signalEventChangedStatusDOOpen             )
    Q_PROPERTY(int      mStatusDOClose            READ getStatusDOClose             NOTIFY signalEventChangedStatusDOClose            )
    Q_PROPERTY(bool     mErrDIOpenValveIdx        READ getErrDIOpenValveIdx         NOTIFY signalEventChangedErrDIOpenValveIdx        )
    Q_PROPERTY(bool     mErrDICloseValveIdx       READ getErrDICloseValveIdx        NOTIFY signalEventChangedErrDICloseValveIdx       )
    Q_PROPERTY(bool     mErrStatusDIOpen          READ getErrStatusDIOpen           NOTIFY signalEventChangedErrStatusDIOpen          )
    Q_PROPERTY(bool     mErrStatusDIClose         READ getErrStatusDIClose          NOTIFY signalEventChangedErrStatusDIClose         )
    Q_PROPERTY(bool     mErrStatusDOOpen          READ getErrStatusDOOpen           NOTIFY signalEventChangedErrStatusDOOpen          )
    Q_PROPERTY(bool     mErrStatusDOClose         READ getErrStatusDOClose          NOTIFY signalEventChangedErrStatusDOClose         )
    Q_PROPERTY(bool     mIsEdit                   READ getIsEdit                    NOTIFY signalEventChangedIsEdit                   )
    Q_PROPERTY(QString  mStrStatus                READ getStrStatus                 NOTIFY signalEventChangedStrStatus                )
    Q_PROPERTY(QString  mErrMsg                   READ getErrMsg                    NOTIFY signalEventChangedErrMsg                   )
    Q_PROPERTY(int      mProgress                 READ getProgress                  NOTIFY signalEventChangedProgress                 )

public:
    int     mAccessMode               = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test              = false;
    int     mDIOpenValveIdx           = 0;
    int     mDICloseValveIdx          = 0;
    int     mStatusDIOpen             = 0;
    int     mStatusDIClose            = 0;
    int     mStatusDOOpen             = 0;
    int     mStatusDOClose            = 0;
    bool    mErrDIOpenValveIdx        = false;
    bool    mErrDICloseValveIdx       = false;
    bool    mErrStatusDIOpen          = false;
    bool    mErrStatusDIClose         = false;
    bool    mErrStatusDOOpen          = false;
    bool    mErrStatusDOClose         = false;
    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    int     mProgress                 = 0 ;

    int     getAccessMode              (){ return mAccessMode              ;}
    bool    getIsRS232Test             (){ return mIsRS232Test             ;}
    int     getDIOpenValveIdx          (){ return mDIOpenValveIdx          ;}
    int     getDICloseValveIdx         (){ return mDICloseValveIdx         ;}
    int     getStatusDIOpen            (){ return mStatusDIOpen            ;}
    int     getStatusDIClose           (){ return mStatusDIClose           ;}
    int     getStatusDOOpen            (){ return mStatusDOOpen            ;}
    int     getStatusDOClose           (){ return mStatusDOClose           ;}
    bool    getErrDIOpenValveIdx       (){ return mErrDIOpenValveIdx       ;}
    bool    getErrDICloseValveIdx      (){ return mErrDICloseValveIdx      ;}
    bool    getErrStatusDIOpen         (){ return mErrStatusDIOpen         ;}
    bool    getErrStatusDIClose        (){ return mErrStatusDIClose        ;}
    bool    getErrStatusDOOpen         (){ return mErrStatusDOOpen         ;}
    bool    getErrStatusDOClose        (){ return mErrStatusDOClose        ;}
    bool    getIsEdit                  (){ return mIsEdit                  ;}
    QString getStrStatus               (){ return mStrStatus               ;}
    QString getErrMsg                  (){ return mErrMsg                  ;}
    int     getProgress                (){ return mProgress                ;}

    void    setAccessMode                (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode              (value);}
    void    setIsRS232Test               (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test             (value);}
    void    setDIOpenValveIdx            (int     value){ if(mDIOpenValveIdx          == value)return; mDIOpenValveIdx          = value; emit signalEventChangedDIOpenValveIdx          (value);}
    void    setDICloseValveIdx           (int     value){ if(mDICloseValveIdx         == value)return; mDICloseValveIdx         = value; emit signalEventChangedDICloseValveIdx         (value);}
    void    setStatusDIOpen              (int     value){ if(mStatusDIOpen            == value)return; mStatusDIOpen            = value; emit signalEventChangedStatusDIOpen            (value);}
    void    setStatusDIClose             (int     value){ if(mStatusDIClose           == value)return; mStatusDIClose           = value; emit signalEventChangedStatusDIClose           (value);}
    void    setStatusDOOpen              (int     value){ if(mStatusDOOpen            == value)return; mStatusDOOpen            = value; emit signalEventChangedStatusDOOpen            (value);}
    void    setStatusDOClose             (int     value){ if(mStatusDOClose           == value)return; mStatusDOClose           = value; emit signalEventChangedStatusDOClose           (value);}
    void    setErrDIOpenValveIdx         (bool    value){ if(mErrDIOpenValveIdx       == value)return; mErrDIOpenValveIdx       = value; emit signalEventChangedErrDIOpenValveIdx       (value);}
    void    setErrDICloseValveIdx        (bool    value){ if(mErrDICloseValveIdx      == value)return; mErrDICloseValveIdx      = value; emit signalEventChangedErrDICloseValveIdx      (value);}
    void    setErrStatusDIOpen           (bool    value){ if(mErrStatusDIOpen         == value)return; mErrStatusDIOpen         = value; emit signalEventChangedErrStatusDIOpen         (value);}
    void    setErrStatusDIClose          (bool    value){ if(mErrStatusDIClose        == value)return; mErrStatusDIClose        = value; emit signalEventChangedErrStatusDIClose        (value);}
    void    setErrStatusDOOpen           (bool    value){ if(mErrStatusDOOpen         == value)return; mErrStatusDOOpen         = value; emit signalEventChangedErrStatusDOOpen         (value);}
    void    setErrStatusDOClose          (bool    value){ if(mErrStatusDOClose        == value)return; mErrStatusDOClose        = value; emit signalEventChangedErrStatusDOClose        (value);}
    void    setIsEdit                    (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                  (value);}
    void    setStrStatus                 (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus               (value);}
    void    setErrMsg                    (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                  (value);}
    void    setProgress                  (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress                (value);}

signals:
    void signalEventChangedAccessMode              (int     value);
    void signalEventChangedIsRS232Test             (bool    value);
    void signalEventChangedDIOpenValveIdx          (int     value);
    void signalEventChangedDICloseValveIdx         (int     value);
    void signalEventChangedStatusDIOpen            (int     value);
    void signalEventChangedStatusDIClose           (int     value);
    void signalEventChangedStatusDOOpen            (int     value);
    void signalEventChangedStatusDOClose           (int     value);
    void signalEventChangedErrDIOpenValveIdx       (bool    value);
    void signalEventChangedErrDICloseValveIdx      (bool    value);
    void signalEventChangedErrStatusDIOpen         (bool    value);
    void signalEventChangedErrStatusDIClose        (bool    value);
    void signalEventChangedErrStatusDOOpen         (bool    value);
    void signalEventChangedErrStatusDOClose        (bool    value);
    void signalEventChangedIsEdit                  (bool    value);
    void signalEventChangedStrStatus               (QString value);
    void signalEventChangedErrMsg                  (QString value);
    void signalEventChangedProgress                (int     value);

public:
    explicit InterfaceStatusRS232DlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CFG_RS232;
        ENABLE_SLOT_VALVE_READED_IF_STATUS_RS232;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CONFIG);
    }
    ~InterfaceStatusRS232DlgModel()
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

    void onValveReadedInterfaceCfgRS232(ValveResponseInterfaceConfigRS232Dto dto)
    {
        if(mState != eState::STATE_READ_CONFIG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setDIOpenValveIdx (dto.mDIOpenValveIdx);
        setDICloseValveIdx(dto.mDICloseValveIdx);

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceStatusRS232(ValveResponseInterfaceStatusRS232Dto dto)
    {
        if(mState != eState::STATE_READ_STATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {

            setState(mState);
            return;
        }

        setStatusDIOpen (dto.mStatusDIOpen );
        setStatusDIClose(dto.mStatusDIClose);
        setStatusDOOpen (dto.mStatusDOOpen );
        setStatusDOClose(dto.mStatusDOClose);

        setState((eState)(mState + 1));

        return;
    }

private:
    enum eState{
        STATE_READ_CONFIG        =  0,
        STATE_READ_STATUS        =  STATE_READ_CONFIG + 1,
        STATE_OVER               =  STATE_READ_STATUS + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CONFIG;
    qint64 mLastScanMSec  = 0;
    bool   mIsFirstRead   = false;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        qint64 currMSec;

        if(state == eState::STATE_OVER)
        {
            state = eState::STATE_READ_CONFIG;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_STATUS));
        }
        else if(state == eState::STATE_READ_CONFIG)
        {
            currMSec = QDateTime::currentMSecsSinceEpoch();
            setStrStatus(QString("scan-rate %1 ms").arg(currMSec - mLastScanMSec));
            setProgress(100);
            mLastScanMSec = currMSec;
        }

        startTimer();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case (int)eState::STATE_READ_CONFIG:
            pValveSP->readInterfaceConfigRS232(this);
            break;

        case (int)eState::STATE_READ_STATUS:
            pValveSP->readInterfaceStatusRS232(this);
            break;
        }
    }
};
#endif // INTERFACESTATUSRS232DLGMODEL_H
