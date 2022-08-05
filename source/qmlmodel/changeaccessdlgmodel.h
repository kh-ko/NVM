#ifndef CHANGEACCESSDLGMODEL_H
#define CHANGEACCESSDLGMODEL_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"


class ChangeAccessDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int      mProgress      READ getProgress    NOTIFY signalEventChangedProgress)

public:
    int     mProgress = 100;

    int     getProgress(){ return mProgress;}

    void    setProgress(int value){ if(value == mProgress)return; mProgress = value; emit signalEventChangedProgress(value);}

signals:
    void signalEventChangedProgress(int  value);
    void signalEventResult         (bool value);

public:
    explicit ChangeAccessDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_WRITTEN_ACCESS;

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

    }
    ~ChangeAccessDlgModel()
    {
    }

public slots:
    Q_INVOKABLE void onCommandChangeLocalMode()
    {
        setProgress(0);
        //pValveSP->setAccess(ValveEnumDef::ACCESS_LOCAL, this);
        startTimer();
    }

    void onValveWrittenAcces(ValveResponseDto dto)
    {
        if(dto.mReqDto.mpRef != this)
            return;

        if(dto.mIsNetworkErr)
        {
            startTimer();
            return;
        }

        if(!dto.mIsSucc)
            qDebug() << "[" <<Q_FUNC_INFO << "]errMsg = " << dto.mErrMsg;

        setProgress(100);
        emit signalEventResult(dto.mIsSucc);
    }

    void onTimeout()
    {
        pValveSP->setAccess(ValveEnumDef::ACCESS_LOCAL, this);
    }
private:
    QTimer mTimer;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }
};
#endif // CHANGEACCESSDLGMODEL_H
