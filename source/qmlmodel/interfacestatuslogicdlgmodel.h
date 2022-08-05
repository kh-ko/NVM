#ifndef INTERFACESTATUSLOGICDLGMODEL_H
#define INTERFACESTATUSLOGICDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"

class InterfaceStatusLogicDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode               READ getAccessMode                NOTIFY signalEventChangedAccessMode               )
    Q_PROPERTY(bool     mIsRS232Test              READ getIsRS232Test               NOTIFY signalEventChangedIsRS232Test              )
    Q_PROPERTY(int      mDIOpen                   READ getDIOpen                    NOTIFY signalEventChangedDIOpen                   )
    Q_PROPERTY(int      mDIClose                  READ getDIClose                   NOTIFY signalEventChangedDIClose                  )
    Q_PROPERTY(int      mDOOpen                   READ getDOOpen                    NOTIFY signalEventChangedDOOpen                   )
    Q_PROPERTY(int      mDOClose                  READ getDOClose                   NOTIFY signalEventChangedDOClose                  )
    Q_PROPERTY(int      mLearnRange               READ getLearnRange                NOTIFY signalEventChangedLearnRange               )
    Q_PROPERTY(int      mStatusDIOpen             READ getStatusDIOpen              NOTIFY signalEventChangedStatusDIOpen             )
    Q_PROPERTY(int      mStatusDIClose            READ getStatusDIClose             NOTIFY signalEventChangedStatusDIClose            )
    Q_PROPERTY(int      mStatusDICtrlModel        READ getStatusDICtrlModel         NOTIFY signalEventChangedStatusDICtrlModel        )
    Q_PROPERTY(int      mStatusDILearn            READ getStatusDILearn             NOTIFY signalEventChangedStatusDILearn            )
    Q_PROPERTY(int      mStatusDIZero             READ getStatusDIZero              NOTIFY signalEventChangedStatusDIZero             )
    Q_PROPERTY(int      mStatusDILocked           READ getStatusDILocked            NOTIFY signalEventChangedStatusDILocked           )
    Q_PROPERTY(int      mStatusDIHold             READ getStatusDIHold              NOTIFY signalEventChangedStatusDIHold             )
    Q_PROPERTY(int      mStatusDISetPointRange    READ getStatusDISetPointRange     NOTIFY signalEventChangedStatusDISetPointRange    )
    Q_PROPERTY(int      mStatusDOOpen             READ getStatusDOOpen              NOTIFY signalEventChangedStatusDOOpen             )
    Q_PROPERTY(int      mStatusDOClose            READ getStatusDOClose             NOTIFY signalEventChangedStatusDOClose            )
    Q_PROPERTY(int      mStatusDOAlarm            READ getStatusDOAlarm             NOTIFY signalEventChangedStatusDOAlarm            )
    Q_PROPERTY(int      mStatusDOReady            READ getStatusDOReady             NOTIFY signalEventChangedStatusDOReady            )
    Q_PROPERTY(double   mAnalogInputVoltage       READ getAnalogInputVoltage        NOTIFY signalEventChangedAnalogInputVoltage       )
    Q_PROPERTY(bool     mErrDIOpen                READ getErrDIOpen                 NOTIFY signalEventChangedErrDIOpen                )
    Q_PROPERTY(bool     mErrDIClose               READ getErrDIClose                NOTIFY signalEventChangedErrDIClose               )
    Q_PROPERTY(bool     mErrDOOpen                READ getErrDOOpen                 NOTIFY signalEventChangedErrDOOpen                )
    Q_PROPERTY(bool     mErrDOClose               READ getErrDOClose                NOTIFY signalEventChangedErrDOClose               )
    Q_PROPERTY(bool     mErrLearnRange            READ getErrLearnRange             NOTIFY signalEventChangedErrLearnRange            )
    Q_PROPERTY(bool     mErrStatusDIOpen          READ getErrStatusDIOpen           NOTIFY signalEventChangedErrStatusDIOpen          )
    Q_PROPERTY(bool     mErrStatusDIClose         READ getErrStatusDIClose          NOTIFY signalEventChangedErrStatusDIClose         )
    Q_PROPERTY(bool     mErrStatusDICtrlModel     READ getErrStatusDICtrlModel      NOTIFY signalEventChangedErrStatusDICtrlModel     )
    Q_PROPERTY(bool     mErrStatusDILearn         READ getErrStatusDILearn          NOTIFY signalEventChangedErrStatusDILearn         )
    Q_PROPERTY(bool     mErrStatusDIZero          READ getErrStatusDIZero           NOTIFY signalEventChangedErrStatusDIZero          )
    Q_PROPERTY(bool     mErrStatusDILocked        READ getErrStatusDILocked         NOTIFY signalEventChangedErrStatusDILocked        )
    Q_PROPERTY(bool     mErrStatusDIHold          READ getErrStatusDIHold           NOTIFY signalEventChangedErrStatusDIHold          )
    Q_PROPERTY(bool     mErrStatusDISetPointRange READ getErrStatusDISetPointRange  NOTIFY signalEventChangedErrStatusDISetPointRange )
    Q_PROPERTY(bool     mErrStatusDOOpen          READ getErrStatusDOOpen           NOTIFY signalEventChangedErrStatusDOOpen          )
    Q_PROPERTY(bool     mErrStatusDOClose         READ getErrStatusDOClose          NOTIFY signalEventChangedErrStatusDOClose         )
    Q_PROPERTY(bool     mErrStatusDOAlarm         READ getErrStatusDOAlarm          NOTIFY signalEventChangedErrStatusDOAlarm         )
    Q_PROPERTY(bool     mErrStatusDOReady         READ getErrStatusDOReady          NOTIFY signalEventChangedErrStatusDOReady         )
    Q_PROPERTY(bool     mErrAnalogInputVoltage    READ getErrAnalogInputVoltage     NOTIFY signalEventChangedErrAnalogInputVoltage    )
    Q_PROPERTY(bool     mIsEdit                   READ getIsEdit                    NOTIFY signalEventChangedIsEdit                   )
    Q_PROPERTY(QString  mStrStatus                READ getStrStatus                 NOTIFY signalEventChangedStrStatus                )
    Q_PROPERTY(QString  mErrMsg                   READ getErrMsg                    NOTIFY signalEventChangedErrMsg                   )
    Q_PROPERTY(int      mProgress                 READ getProgress                  NOTIFY signalEventChangedProgress                 )

public:
    int     mAccessMode               = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsRS232Test              = false;
    int     mDIOpen                   = 0;
    int     mDIClose                  = 0;
    int     mDOOpen                   = 0;
    int     mDOClose                  = 0;
    int     mLearnRange               = 0;
    int     mStatusDIOpen             = 0;
    int     mStatusDIClose            = 0;
    int     mStatusDICtrlModel        = 0;
    int     mStatusDILearn            = 0;
    int     mStatusDIZero             = 0;
    int     mStatusDILocked           = 0;
    int     mStatusDIHold             = 0;
    int     mStatusDISetPointRange    = 0;
    int     mStatusDOOpen             = 0;
    int     mStatusDOClose            = 0;
    int     mStatusDOAlarm            = 0;
    int     mStatusDOReady            = 0;
    double  mAnalogInputVoltage       = 0;
    bool    mErrDIOpen                = false;
    bool    mErrDIClose               = false;
    bool    mErrDOOpen                = false;
    bool    mErrDOClose               = false;
    bool    mErrLearnRange            = false;
    bool    mErrStatusDIOpen          = false;
    bool    mErrStatusDIClose         = false;
    bool    mErrStatusDICtrlModel     = false;
    bool    mErrStatusDILearn         = false;
    bool    mErrStatusDIZero          = false;
    bool    mErrStatusDILocked        = false;
    bool    mErrStatusDIHold          = false;
    bool    mErrStatusDISetPointRange = false;
    bool    mErrStatusDOOpen          = false;
    bool    mErrStatusDOClose         = false;
    bool    mErrStatusDOAlarm         = false;
    bool    mErrStatusDOReady         = false;
    bool    mErrAnalogInputVoltage    = false;
    bool    mIsEdit                   = false;
    QString mStrStatus                = "Loading";
    QString mErrMsg                   = "";
    int     mProgress                 = 0 ;

    int     getAccessMode              (){ return mAccessMode              ;}
    bool    getIsRS232Test             (){ return mIsRS232Test             ;}
    int     getDIOpen                  (){ return mDIOpen                  ;}
    int     getDIClose                 (){ return mDIClose                 ;}
    int     getDOOpen                  (){ return mDOOpen                  ;}
    int     getDOClose                 (){ return mDOClose                 ;}
    int     getLearnRange              (){ return mLearnRange              ;}
    int     getStatusDIOpen            (){ return mStatusDIOpen            ;}
    int     getStatusDIClose           (){ return mStatusDIClose           ;}
    int     getStatusDICtrlModel       (){ return mStatusDICtrlModel       ;}
    int     getStatusDILearn           (){ return mStatusDILearn           ;}
    int     getStatusDIZero            (){ return mStatusDIZero            ;}
    int     getStatusDILocked          (){ return mStatusDILocked          ;}
    int     getStatusDIHold            (){ return mStatusDIHold            ;}
    int     getStatusDISetPointRange   (){ return mStatusDISetPointRange   ;}
    int     getStatusDOOpen            (){ return mStatusDOOpen            ;}
    int     getStatusDOClose           (){ return mStatusDOClose           ;}
    int     getStatusDOAlarm           (){ return mStatusDOAlarm           ;}
    int     getStatusDOReady           (){ return mStatusDOReady           ;}
    double  getAnalogInputVoltage      (){ return mAnalogInputVoltage      ;}
    bool    getErrDIOpen               (){ return mErrDIOpen               ;}
    bool    getErrDIClose              (){ return mErrDIClose              ;}
    bool    getErrDOOpen               (){ return mErrDOOpen               ;}
    bool    getErrDOClose              (){ return mErrDOClose              ;}
    bool    getErrLearnRange           (){ return mErrLearnRange           ;}
    bool    getErrStatusDIOpen         (){ return mErrStatusDIOpen         ;}
    bool    getErrStatusDIClose        (){ return mErrStatusDIClose        ;}
    bool    getErrStatusDICtrlModel    (){ return mErrStatusDICtrlModel    ;}
    bool    getErrStatusDILearn        (){ return mErrStatusDILearn        ;}
    bool    getErrStatusDIZero         (){ return mErrStatusDIZero         ;}
    bool    getErrStatusDILocked       (){ return mErrStatusDILocked       ;}
    bool    getErrStatusDIHold         (){ return mErrStatusDIHold         ;}
    bool    getErrStatusDISetPointRange(){ return mErrStatusDISetPointRange;}
    bool    getErrStatusDOOpen         (){ return mErrStatusDOOpen         ;}
    bool    getErrStatusDOClose        (){ return mErrStatusDOClose        ;}
    bool    getErrStatusDOAlarm        (){ return mErrStatusDOAlarm        ;}
    bool    getErrStatusDOReady        (){ return mErrStatusDOReady        ;}
    bool    getErrAnalogInputVoltage   (){ return mErrAnalogInputVoltage   ;}
    bool    getIsEdit                  (){ return mIsEdit                  ;}
    QString getStrStatus               (){ return mStrStatus               ;}
    QString getErrMsg                  (){ return mErrMsg                  ;}
    int     getProgress                (){ return mProgress                ;}

    void    setAccessMode                (int     value){ if(mAccessMode              == value)return; mAccessMode              = value; emit signalEventChangedAccessMode              (value);}
    void    setIsRS232Test               (bool    value){ if(mIsRS232Test             == value)return; mIsRS232Test             = value; emit signalEventChangedIsRS232Test             (value);}
    void    setDIOpen                    (int     value){ if(mDIOpen                  == value)return; mDIOpen                  = value; emit signalEventChangedDIOpen                  (value);}
    void    setDIClose                   (int     value){ if(mDIClose                 == value)return; mDIClose                 = value; emit signalEventChangedDIClose                 (value);}
    void    setDOOpen                    (int     value){ if(mDOOpen                  == value)return; mDOOpen                  = value; emit signalEventChangedDOOpen                  (value);}
    void    setDOClose                   (int     value){ if(mDOClose                 == value)return; mDOClose                 = value; emit signalEventChangedDOClose                 (value);}
    void    setLearnRange                (int     value){ if(mLearnRange              == value)return; mLearnRange              = value; emit signalEventChangedLearnRange              (value);}
    void    setStatusDIOpen              (int     value){ if(mStatusDIOpen            == value)return; mStatusDIOpen            = value; emit signalEventChangedStatusDIOpen            (value);}
    void    setStatusDIClose             (int     value){ if(mStatusDIClose           == value)return; mStatusDIClose           = value; emit signalEventChangedStatusDIClose           (value);}
    void    setStatusDICtrlModel         (int     value){ if(mStatusDICtrlModel       == value)return; mStatusDICtrlModel       = value; emit signalEventChangedStatusDICtrlModel       (value);}
    void    setStatusDILearn             (int     value){ if(mStatusDILearn           == value)return; mStatusDILearn           = value; emit signalEventChangedStatusDILearn           (value);}
    void    setStatusDIZero              (int     value){ if(mStatusDIZero            == value)return; mStatusDIZero            = value; emit signalEventChangedStatusDIZero            (value);}
    void    setStatusDILocked            (int     value){ if(mStatusDILocked          == value)return; mStatusDILocked          = value; emit signalEventChangedStatusDILocked          (value);}
    void    setStatusDIHold              (int     value){ if(mStatusDIHold            == value)return; mStatusDIHold            = value; emit signalEventChangedStatusDIHold            (value);}
    void    setStatusDISetPointRange     (int     value){ if(mStatusDISetPointRange   == value)return; mStatusDISetPointRange   = value; emit signalEventChangedStatusDISetPointRange   (value);}
    void    setStatusDOOpen              (int     value){ if(mStatusDOOpen            == value)return; mStatusDOOpen            = value; emit signalEventChangedStatusDOOpen            (value);}
    void    setStatusDOClose             (int     value){ if(mStatusDOClose           == value)return; mStatusDOClose           = value; emit signalEventChangedStatusDOClose           (value);}
    void    setStatusDOAlarm             (int     value){ if(mStatusDOAlarm           == value)return; mStatusDOAlarm           = value; emit signalEventChangedStatusDOAlarm           (value);}
    void    setStatusDOReady             (int     value){ if(mStatusDOReady           == value)return; mStatusDOReady           = value; emit signalEventChangedStatusDOReady           (value);}
    void    setAnalogInputVoltage        (double  value){ if(mAnalogInputVoltage      == value)return; mAnalogInputVoltage      = value; emit signalEventChangedAnalogInputVoltage      (value);}
    void    setErrDIOpen                 (bool    value){ if(mErrDIOpen               == value)return; mErrDIOpen               = value; emit signalEventChangedErrDIOpen               (value);}
    void    setErrDIClose                (bool    value){ if(mErrDIClose              == value)return; mErrDIClose              = value; emit signalEventChangedErrDIClose              (value);}
    void    setErrDOOpen                 (bool    value){ if(mErrDOOpen               == value)return; mErrDOOpen               = value; emit signalEventChangedErrDOOpen               (value);}
    void    setErrDOClose                (bool    value){ if(mErrDOClose              == value)return; mErrDOClose              = value; emit signalEventChangedErrDOClose              (value);}
    void    setErrLearnRange             (bool    value){ if(mErrLearnRange           == value)return; mErrLearnRange           = value; emit signalEventChangedErrLearnRange           (value);}
    void    setErrStatusDIOpen           (bool    value){ if(mErrStatusDIOpen         == value)return; mErrStatusDIOpen         = value; emit signalEventChangedErrStatusDIOpen         (value);}
    void    setErrStatusDIClose          (bool    value){ if(mErrStatusDIClose        == value)return; mErrStatusDIClose        = value; emit signalEventChangedErrStatusDIClose        (value);}
    void    setErrStatusDICtrlModel      (bool    value){ if(mErrStatusDICtrlModel    == value)return; mErrStatusDICtrlModel    = value; emit signalEventChangedErrStatusDICtrlModel    (value);}
    void    setErrStatusDILearn          (bool    value){ if(mErrStatusDILearn        == value)return; mErrStatusDILearn        = value; emit signalEventChangedErrStatusDILearn        (value);}
    void    setErrStatusDIZero           (bool    value){ if(mErrStatusDIZero         == value)return; mErrStatusDIZero         = value; emit signalEventChangedErrStatusDIZero         (value);}
    void    setErrStatusDILocked         (bool    value){ if(mErrStatusDILocked       == value)return; mErrStatusDILocked       = value; emit signalEventChangedErrStatusDILocked       (value);}
    void    setErrStatusDIHold           (bool    value){ if(mErrStatusDIHold         == value)return; mErrStatusDIHold         = value; emit signalEventChangedErrStatusDIHold         (value);}
    void    setErrStatusDISetPointRange  (bool    value){ if(mErrStatusDISetPointRange== value)return; mErrStatusDISetPointRange= value; emit signalEventChangedErrStatusDISetPointRange(value);}
    void    setErrStatusDOOpen           (bool    value){ if(mErrStatusDOOpen         == value)return; mErrStatusDOOpen         = value; emit signalEventChangedErrStatusDOOpen         (value);}
    void    setErrStatusDOClose          (bool    value){ if(mErrStatusDOClose        == value)return; mErrStatusDOClose        = value; emit signalEventChangedErrStatusDOClose        (value);}
    void    setErrStatusDOAlarm          (bool    value){ if(mErrStatusDOAlarm        == value)return; mErrStatusDOAlarm        = value; emit signalEventChangedErrStatusDOAlarm        (value);}
    void    setErrStatusDOReady          (bool    value){ if(mErrStatusDOReady        == value)return; mErrStatusDOReady        = value; emit signalEventChangedErrStatusDOReady        (value);}
    void    setErrAnalogInputVoltage     (bool    value){ if(mErrAnalogInputVoltage   == value)return; mErrAnalogInputVoltage   = value; emit signalEventChangedErrAnalogInputVoltage   (value);}
    void    setIsEdit                    (bool    value){ if(mIsEdit                  == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit                  (value);}
    void    setStrStatus                 (QString value){ if(mStrStatus               == value)return; mStrStatus               = value; emit signalEventChangedStrStatus               (value);}
    void    setErrMsg                    (QString value){ if(mErrMsg                  == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg                  (value);}
    void    setProgress                  (int     value){ if(mProgress                == value)return; mProgress                = value; emit signalEventChangedProgress                (value);}

signals:
    void signalEventChangedAccessMode              (int     value);
    void signalEventChangedIsRS232Test             (bool    value);
    void signalEventChangedDIOpen                  (int     value);
    void signalEventChangedDIClose                 (int     value);
    void signalEventChangedDOOpen                  (int     value);
    void signalEventChangedDOClose                 (int     value);
    void signalEventChangedLearnRange              (int     value);
    void signalEventChangedStatusDIOpen            (int     value);
    void signalEventChangedStatusDIClose           (int     value);
    void signalEventChangedStatusDICtrlModel       (int     value);
    void signalEventChangedStatusDILearn           (int     value);
    void signalEventChangedStatusDIZero            (int     value);
    void signalEventChangedStatusDILocked          (int     value);
    void signalEventChangedStatusDIHold            (int     value);
    void signalEventChangedStatusDISetPointRange   (int     value);
    void signalEventChangedStatusDOOpen            (int     value);
    void signalEventChangedStatusDOClose           (int     value);
    void signalEventChangedStatusDOAlarm           (int     value);
    void signalEventChangedStatusDOReady           (int     value);
    void signalEventChangedAnalogInputVoltage      (double  value);
    void signalEventChangedErrDIOpen               (bool    value);
    void signalEventChangedErrDIClose              (bool    value);
    void signalEventChangedErrDOOpen               (bool    value);
    void signalEventChangedErrDOClose              (bool    value);
    void signalEventChangedErrLearnRange           (bool    value);
    void signalEventChangedErrStatusDIOpen         (bool    value);
    void signalEventChangedErrStatusDIClose        (bool    value);
    void signalEventChangedErrStatusDICtrlModel    (bool    value);
    void signalEventChangedErrStatusDILearn        (bool    value);
    void signalEventChangedErrStatusDIZero         (bool    value);
    void signalEventChangedErrStatusDILocked       (bool    value);
    void signalEventChangedErrStatusDIHold         (bool    value);
    void signalEventChangedErrStatusDISetPointRange(bool    value);
    void signalEventChangedErrStatusDOOpen         (bool    value);
    void signalEventChangedErrStatusDOClose        (bool    value);
    void signalEventChangedErrStatusDOAlarm        (bool    value);
    void signalEventChangedErrStatusDOReady        (bool    value);
    void signalEventChangedErrAnalogInputVoltage   (bool    value);
    void signalEventChangedIsEdit                  (bool    value);
    void signalEventChangedStrStatus               (QString value);
    void signalEventChangedErrMsg                  (QString value);
    void signalEventChangedProgress                (int     value);

public:
    explicit InterfaceStatusLogicDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;
        ENABLE_SLOT_VALVE_READED_IF_CONFIG_LOGIC;
        ENABLE_SLOT_VALVE_READED_IF_STATUS_LOGIC;

        onValveChangedAccess();
        onValveChangedIsRS232Test();

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READ_CONFIG);
    }
    ~InterfaceStatusLogicDlgModel()
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
        if(mState != eState::STATE_READ_CONFIG || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setDIOpen     (dto.mDIOpen    );
        setDIClose    (dto.mDIClose   );
        setDOOpen     (dto.mDOOpen    );
        setDOClose    (dto.mDOClose   );
        setLearnRange (dto.mLearnRange);

        setState((eState)(mState + 1));

        return;
    }

    void onValveReadedInterfaceStatusLogic(ValveResponseInterfaceStatusLogicDto dto)
    {
        if(mState != eState::STATE_READ_STATUS || dto.mReqDto.mpRef != this)
            return;

        setErrMsg(dto.mErrMsg);

        if(!dto.mIsSucc)
        {
            setState(mState);
            return;
        }

        setStatusDIOpen         (dto.mStatusDIOpen              );
        setStatusDIClose        (dto.mStatusDIClose             );
        setStatusDICtrlModel    (dto.mStatusDICtrlModel         );
        setStatusDILearn        (dto.mStatusDILearn             );
        setStatusDIZero         (dto.mStatusDIZero              );
        setStatusDILocked       (dto.mStatusDILocked            );
        setStatusDIHold         (dto.mStatusDIHold              );
        setStatusDISetPointRange(dto.mStatusDISetPointRange     );
        setStatusDOOpen         (dto.mStatusDOOpen              );
        setStatusDOClose        (dto.mStatusDOClose             );
        setStatusDOAlarm        (dto.mStatusDOAlarm             );
        setStatusDOReady        (dto.mStatusDOReady             );
        setAnalogInputVoltage   ((double)dto.mAlogInputVoltage * 0.00001);

        setState((eState)(mState + 1));

        return;
    }


private:
    enum eState{
        STATE_READ_CONFIG =  0,
        STATE_READ_STATUS =  STATE_READ_CONFIG + 1,
        STATE_OVER        =  STATE_READ_STATUS + 1
    };

    QTimer mTimer;
    eState mState         = eState::STATE_READ_CONFIG;
    bool   mIsFirstRead   = true;
    qint64 mLastScanMSec  = 0;

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
        else if(mState == eState::STATE_READ_CONFIG)
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
            pValveSP->readInterfaceConfigLogic(this);
            break;

        case (int)eState::STATE_READ_STATUS:
            pValveSP->readInterfaceStatusLogic(this);
            break;
        }
    }
};

#endif // INTERFACESTATUSLOGICDLGMODEL_H
