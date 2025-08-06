#ifndef INTERFACESTATUSPROFIBUSDLGMODEL_H
#define INTERFACESTATUSPROFIBUSDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class InterfaceStatusProfibusDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode               READ getAccessMode                NOTIFY signalEventChangedAccessMode               )
    Q_PROPERTY(bool     mIsRS232Test              READ getIsRS232Test               NOTIFY signalEventChangedIsRS232Test              )
    Q_PROPERTY(int      mDIFunction               READ getDIFunction                NOTIFY signalEventChangedDIFunction               )
    Q_PROPERTY(int      mDIMode                   READ getDIMode                    NOTIFY signalEventChangedDIMode                   )
    Q_PROPERTY(int      mDIInput                  READ getDIInput                   NOTIFY signalEventChangedDIInput                  )
    Q_PROPERTY(int      mDOFunction               READ getDOFunction                NOTIFY signalEventChangedDOFunction               )
    Q_PROPERTY(int      mDOMode                   READ getDOMode                    NOTIFY signalEventChangedDOMode                   )
    Q_PROPERTY(int      mDOOutput                 READ getDOOutput                  NOTIFY signalEventChangedDOOutput                 )
    Q_PROPERTY(int      mStatusDI                 READ getStatusDI                  NOTIFY signalEventChangedStatusDI                 )
    Q_PROPERTY(int      mStatusDO                 READ getStatusDO                  NOTIFY signalEventChangedStatusDO                 )
    Q_PROPERTY(bool     mErrDIFunction            READ getErrDIFunction             NOTIFY signalEventChangedErrDIFunction            )
    Q_PROPERTY(bool     mErrDIMode                READ getErrDIMode                 NOTIFY signalEventChangedErrDIMode                )
    Q_PROPERTY(bool     mErrDIInput               READ getErrDIInput                NOTIFY signalEventChangedErrDIInput               )
    Q_PROPERTY(bool     mErrDOFunction            READ getErrDOFunction             NOTIFY signalEventChangedErrDOFunction            )
    Q_PROPERTY(bool     mErrDOMode                READ getErrDOMode                 NOTIFY signalEventChangedErrDOMode                )
    Q_PROPERTY(bool     mErrDOOutput              READ getErrDOOutput               NOTIFY signalEventChangedErrDOOutput              )
    Q_PROPERTY(bool     mErrStatusDI              READ getErrStatusDI               NOTIFY signalEventChangedErrStatusDI              )
    Q_PROPERTY(bool     mErrStatusDO              READ getErrStatusDO               NOTIFY signalEventChangedErrStatusDO              )
    Q_PROPERTY(bool     mIsEdit                   READ getIsEdit                    NOTIFY signalEventChangedIsEdit                   )
    Q_PROPERTY(QString  mStrStatus                READ getStrStatus                 NOTIFY signalEventChangedStrStatus                )
    Q_PROPERTY(QString  mErrMsg                   READ getErrMsg                    NOTIFY signalEventChangedErrMsg                   )
    Q_PROPERTY(int      mProgress                 READ getProgress                  NOTIFY signalEventChangedProgress                 )

public:
    int     mAccessMode               = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test              = false;
    int     mDIFunction               = 0;
    int     mDIMode                   = 0;
    int     mDIInput                  = 0;
    int     mDOFunction               = 0;
    int     mDOMode                   = 0;
    int     mDOOutput                 = 0;
    int     mStatusDI                 = 0;
    int     mStatusDO                 = 0;
    bool    mErrDIFunction            = false;
    bool    mErrDIMode                = false;
    bool    mErrDIInput               = false;
    bool    mErrDOFunction            = false;
    bool    mErrDOMode                = false;
    bool    mErrDOOutput              = false;
    bool    mErrStatusDI              = false;
    bool    mErrStatusDO              = false;
    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    int     mProgress                 = 0 ;

    int     getAccessMode              (){ return mAccessMode              ;}
    bool    getIsRS232Test             (){ return mIsRS232Test             ;}
    int     getDIFunction              (){ return mDIFunction              ;}
    int     getDIMode                  (){ return mDIMode                  ;}
    int     getDIInput                 (){ return mDIInput                 ;}
    int     getDOFunction              (){ return mDOFunction              ;}
    int     getDOMode                  (){ return mDOMode                  ;}
    int     getDOOutput                (){ return mDOOutput                ;}
    int     getStatusDI                (){ return mStatusDI                ;}
    int     getStatusDO                (){ return mStatusDO                ;}
    bool    getErrDIFunction           (){ return mErrDIFunction           ;}
    bool    getErrDIMode               (){ return mErrDIMode               ;}
    bool    getErrDIInput              (){ return mErrDIInput              ;}
    bool    getErrDOFunction           (){ return mErrDOFunction           ;}
    bool    getErrDOMode               (){ return mErrDOMode               ;}
    bool    getErrDOOutput             (){ return mErrDOOutput             ;}
    bool    getErrStatusDI             (){ return mErrStatusDI             ;}
    bool    getErrStatusDO             (){ return mErrStatusDO             ;}
    bool    getIsEdit                  (){ return mIsEdit                  ;}
    QString getStrStatus               (){ return mStrStatus               ;}
    QString getErrMsg                  (){ return mErrMsg                  ;}
    int     getProgress                (){ return mProgress                ;}

    void    setAccessMode                (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode              (value);}
    void    setIsRS232Test               (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test             (value);}
    void    setDIFunction                (int     value){ if(mDIFunction              == value)return; mDIFunction              = value; emit signalEventChangedDIFunction              (value);}
    void    setDIMode                    (int     value){ if(mDIMode                  == value)return; mDIMode                  = value; emit signalEventChangedDIMode                  (value);}
    void    setDIInput                   (int     value){ if(mDIInput                 == value)return; mDIInput                 = value; emit signalEventChangedDIInput                 (value);}
    void    setDOFunction                (int     value){ if(mDOFunction              == value)return; mDOFunction              = value; emit signalEventChangedDOFunction              (value);}
    void    setDOMode                    (int     value){ if(mDOMode                  == value)return; mDOMode                  = value; emit signalEventChangedDOMode                  (value);}
    void    setDOOutput                  (int     value){ if(mDOOutput                == value)return; mDOOutput                = value; emit signalEventChangedDOOutput                (value);}
    void    setStatusDI                  (int     value){ if(mStatusDI                == value)return; mStatusDI                = value; emit signalEventChangedStatusDI                (value);}
    void    setStatusDO                  (int     value){ if(mStatusDO                == value)return; mStatusDO                = value; emit signalEventChangedStatusDO                (value);}
    void    setErrDIFunction             (bool    value){ if(mErrDIFunction           == value)return; mErrDIFunction           = value; emit signalEventChangedErrDIFunction           (value);}
    void    setErrDIMode                 (bool    value){ if(mErrDIMode               == value)return; mErrDIMode               = value; emit signalEventChangedErrDIMode               (value);}
    void    setErrDIInput                (bool    value){ if(mErrDIInput              == value)return; mErrDIInput              = value; emit signalEventChangedErrDIInput              (value);}
    void    setErrDOFunction             (bool    value){ if(mErrDOFunction           == value)return; mErrDOFunction           = value; emit signalEventChangedErrDOFunction           (value);}
    void    setErrDOMode                 (bool    value){ if(mErrDOMode               == value)return; mErrDOMode               = value; emit signalEventChangedErrDOMode               (value);}
    void    setErrDOOutput               (bool    value){ if(mErrDOOutput             == value)return; mErrDOOutput             = value; emit signalEventChangedErrDOOutput             (value);}
    void    setErrStatusDI               (bool    value){ if(mErrStatusDI             == value)return; mErrStatusDI             = value; emit signalEventChangedErrStatusDI             (value);}
    void    setErrStatusDO               (bool    value){ if(mErrStatusDO             == value)return; mErrStatusDO             = value; emit signalEventChangedErrStatusDO             (value);}
    void    setIsEdit                    (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                  (value);}
    void    setStrStatus                 (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus               (value);}
    void    setErrMsg                    (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                  (value);}
    void    setProgress                  (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress                (value);}

signals:
    void signalEventChangedAccessMode              (int     value);
    void signalEventChangedIsRS232Test             (bool    value);
    void signalEventChangedDIFunction              (int     value);
    void signalEventChangedDIMode                  (int     value);
    void signalEventChangedDIInput                 (int     value);
    void signalEventChangedDOFunction              (int     value);
    void signalEventChangedDOMode                  (int     value);
    void signalEventChangedDOOutput                (int     value);
    void signalEventChangedStatusDI                (int     value);
    void signalEventChangedStatusDO                (int     value);
    void signalEventChangedErrDIFunction           (bool    value);
    void signalEventChangedErrDIMode               (bool    value);
    void signalEventChangedErrDIInput              (bool    value);
    void signalEventChangedErrDOFunction           (bool    value);
    void signalEventChangedErrDOMode               (bool    value);
    void signalEventChangedErrDOOutput             (bool    value);
    void signalEventChangedErrStatusDI             (bool    value);
    void signalEventChangedErrStatusDO             (bool    value);
    void signalEventChangedIsEdit                  (bool    value);
    void signalEventChangedStrStatus               (QString value);
    void signalEventChangedErrMsg                  (QString value);
    void signalEventChangedProgress                (int     value);

public:
    explicit InterfaceStatusProfibusDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DI;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DO;
        ENABLE_SLOT_VALVE_READED_IF_STATUS_ETHERCAT;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CONFIG_DI);
    }
    ~InterfaceStatusProfibusDlgModel()
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

    void onValveReadedInterfaceConfigEthCATDi(ValveResponseInterfaceConfigEthCATDiDto dto)
    {
        if(mState != eState::STATE_READ_CONFIG_DI || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setDIFunction(dto.mDIFunction);
        setDIMode    (dto.mDIMode    );
        setDIInput   (dto.mDIInput   );

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceConfigEthCATDo(ValveResponseInterfaceConfigEthCATDoDto dto)
    {
        if(mState != eState::STATE_READ_CONFIG_DO || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {

            setState(mState);
            return;
        }

        setDOFunction(dto.mDOFunction);
        setDOMode    (dto.mDOMode    );
        setDOOutput  (dto.mDOOutput  );

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceStatusEtherCAT(ValveResponseInterfaceStatusEtherCATDto dto)
    {
        if(mState != eState::STATE_READ_STATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setStatusDI(dto.mStatusDI);
        setStatusDO(dto.mStatusDO);

        setState((eState)(mState + 1));

        return;
    }


private:
    enum eState{
        STATE_READ_CONFIG_DI        =  0,
        STATE_READ_CONFIG_DO        =  STATE_READ_CONFIG_DI + 1,
        STATE_READ_STATUS           =  STATE_READ_CONFIG_DO + 1,
        STATE_OVER                  =  STATE_READ_STATUS    + 1,
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CONFIG_DI;
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
            state = eState::STATE_READ_CONFIG_DI;
            mIsFirstRead = false;
        }

        mState = state;

        if(mIsFirstRead)
        {
            setStrStatus("loading");
            setProgress(qFloor((state * 100) / eState::STATE_READ_STATUS));
        }
        else if(state == eState::STATE_READ_CONFIG_DI)
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
        case (int)eState::STATE_READ_CONFIG_DI:
            pValveSP->readInterfaceConfigEthCATDi(this);
            break;

        case (int)eState::STATE_READ_CONFIG_DO:
            pValveSP->readInterfaceConfigEthCATDo(this);
            break;

        case (int)eState::STATE_READ_STATUS:
            pValveSP->readInterfaceStatusEtherCAT(this);
            break;
        }
    }
};
#endif // INTERFACESTATUSPROFIBUSDLGMODEL_H
