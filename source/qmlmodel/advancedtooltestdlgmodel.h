#ifndef ADVANCEDTOOLTESTDLGMODEL_H
#define ADVANCEDTOOLTESTDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class AdvancedToolTestDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mAccessMode              READ getAccessMode               NOTIFY signalEventChangedAccessMode         )
    Q_PROPERTY(bool     mIsTestMode              READ getIsTestMode               NOTIFY signalEventChangedIsTestMode         )
    Q_PROPERTY(bool     mIsRS232Test             READ getIsRS232Test              NOTIFY signalEventChangedIsRS232Test        )
    Q_PROPERTY(bool     mIsEdit                  READ getIsEdit                   NOTIFY signalEventChangedIsEdit             )
    Q_PROPERTY(QString  mStrStatus               READ getStrStatus                NOTIFY signalEventChangedStrStatus          )
    Q_PROPERTY(QString  mErrMsg                  READ getErrMsg                   NOTIFY signalEventChangedErrMsg             )
    Q_PROPERTY(int      mProgress                READ getProgress                 NOTIFY signalEventChangedProgress           )

public:
    int     mAccessMode              = ValveEnumDef::ACCESS_LOCAL;
    bool    mIsTestMode              = false;
    bool    mIsEdit                  = false;
    QString mStrStatus               = "ready";
    QString mErrMsg                  = "";
    int     mProgress                = 100 ;

    int     getAccessMode (){ return mAccessMode; }
    bool    getIsTestMode (){ return mIsTestMode; }
    bool    getIsRS232Test(){ return pValveSP->getIsRS232Test(); }
    bool    getIsEdit     (){ return mIsEdit    ; }
    QString getStrStatus  (){ return mStrStatus ; }
    QString getErrMsg     (){ return mErrMsg    ; }
    int     getProgress   (){ return mProgress  ; }

    void    setAccessMode (int     value){if(mAccessMode                == value)return; mAccessMode              = value; emit signalEventChangedAccessMode (value);}
    void    setIsTestMode (bool    value){if(mIsTestMode                == value)return; mIsTestMode              = value; emit signalEventChangedIsTestMode (value);}
    void    setIsEdit     (bool    value){if(mIsEdit                    == value)return; mIsEdit                  = value; emit signalEventChangedIsEdit     (value);}
    void    setStrStatus  (QString value){if(mStrStatus                 == value)return; mStrStatus               = value; emit signalEventChangedStrStatus  (value);}
    void    setErrMsg     (QString value){if(mErrMsg                    == value)return; mErrMsg                  = value; emit signalEventChangedErrMsg     (value);}
    void    setProgress   (int     value){if(mProgress                  == value)return; mProgress                = value; emit signalEventChangedProgress   (value);}

signals:

    void signalEventChangedAccessMode             (int     value);
    void signalEventChangedIsTestMode             (bool    value);
    void signalEventChangedIsRS232Test            (bool    value);
    void signalEventChangedIsEdit                 (bool    value);
    void signalEventChangedStrStatus              (QString value);
    void signalEventChangedErrMsg                 (QString value);
    void signalEventChangedProgress               (int     value);
    void signalEventCompletedLoad                 (             );
    void signalEventCompletedApply                (             );


public:
    explicit AdvancedToolTestDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_IS_TEST_MODE;
        ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST;

        ENABLE_SLOT_VALVE_WRITTEN_ENCODER_ZERO;
        ENABLE_SLOT_VALVE_WRITTEN_SOFT_OPEN;
        ENABLE_SLOT_VALVE_WRITTEN_SOFT_CLOSE;

        onValveChangedAccess();
        onValveChangedIsTestMode();
        onValveChangedIsRS232Test();

//        mTimer.setSingleShot(true);
//        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

//        setState(eState::STATE_READ_SPEED);

    }
    ~AdvancedToolTestDlgModel()
    {
    }

public slots:
    void onValveChangedAccess()
    {
        setAccessMode(pValveSP->getAccess());
    }

    void onValveChangedIsTestMode()
    {
        setIsTestMode(pValveSP->getIsTestMode());
    }

    void onValveChangedIsRS232Test()
    {
        emit signalEventChangedIsRS232Test(getIsRS232Test());
    }

    Q_INVOKABLE void onCommandSetTestMode(bool value)
    {
        setErrMsg("");
        pValveSP->setTestMode(value, this);
    }

    Q_INVOKABLE void onCommandSetIsRS232Test(bool value)
    {
        pValveSP->setIsRS232Test(value);
    }

    void onValveWrittenTestMode(ValveResponseDto dto)
    {
        if(!dto.mIsSucc)
            setErrMsg(dto.mErrMsg);
    }

    Q_INVOKABLE void onCommandEncoderZero()
    {
        setErrMsg("");
        pValveSP->setEncoderZero(this);
    }

    void onValveWrittenEncoderZero(ValveResponseDto dto)
    {
        if(!dto.mIsSucc)
            setErrMsg(dto.mErrMsg);
    }

    Q_INVOKABLE void onCommandSoftOpen()
    {
        setErrMsg("");
        pValveSP->softOpen(this);
    }

    void onValveWrittenSoftOpen(ValveResponseDto dto)
    {
        if(!dto.mIsSucc)
            setErrMsg(dto.mErrMsg);
    }

    Q_INVOKABLE void onCommandSoftClose()
    {
        setErrMsg("");
        pValveSP->softClose(this);
    }

    void onValveWrittenSoftClose(ValveResponseDto dto)
    {
        if(!dto.mIsSucc)
            setErrMsg(dto.mErrMsg);
    }
};
#endif // ADVANCEDTOOLTESTDLGMODEL_H
