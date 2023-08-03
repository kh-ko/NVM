#ifndef FIMPORTSETTING_H
#define FIMPORTSETTING_H

#include <QObject>
#include <QtMath>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

class FImportSetting : public QObject
{
    Q_OBJECT

public:
    int     mProgress                = 0 ;
    int     getProgress   (){ return mProgress  ; }
    void    setProgress   (int     value){if(mProgress                  == value)return; mProgress                = value; emit signalEventChangedProgress   (value);}

signals:
    void signalEventChangedProgress  (int     value);
    void signalEventCompleted        (bool bErr, QString value);


public:
    explicit FImportSetting(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST;

        mTimer.setSingleShot(true);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        setState(eState::STATE_READY);

    }
    ~FImportSetting()
    {
    }

    void run(QString filePath)
    {
        if(mState != STATE_READY)
            return;

        QFile file;
        file.setFileName(filePath);
        file.open(QFile::ReadOnly);

        mImportCmdList.clear();
        mImportCmdIdx = 0;

        if(file.isOpen() == false)
        {
            emit signalEventCompleted(true, "file open failed");
            return;
        }

        QTextStream out(&file);
        out.setCodec("utf-8");

        do{
            QString line = out.readLine();
            mImportCmdList.append(line);
        }while(!out.atEnd());

        file.close();
        setState(eState::STATE_IMPORT);
    }

    void stop()
    {
        setState(STATE_READY);
        mTimer.stop();
    }

public slots:
    void onTimeout()
    {
        switch ((int)mState)
        {
        case STATE_IMPORT:
            pValveSP->customRequest(mImportCmdList.at(mImportCmdIdx), this);
            break;
        }
    }

    void onValveWrittenCustomRequest(ValveResponseDto dto)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO <<"]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(dto.mIsSucc == false && dto.mIsNetworkErr)
        {
            emit signalEventCompleted(true, "communication error");
            setState(eState::STATE_READY);
            return;
        }

        mImportCmdIdx++;

        if(mImportCmdIdx == mImportCmdList.size())
        {
            emit signalEventCompleted(false, "");
            setState(eState::STATE_READY);
            return;
        }

        setState(mState);

        return;
    }

private:
    enum eState{
        STATE_READY               = 0,
        STATE_IMPORT              = STATE_READY + 1,

    };

    int mImportCmdIdx = 0;
    QList<QString> mImportCmdList;

    QTimer mTimer;
    eState mState         = eState::STATE_READY;

    void startTimer()
    {
        mTimer.stop();
        mTimer.start(100);
    }

    void setState(eState state)
    {
        mState = state;

        if(state == eState::STATE_READY)
        {
            setProgress(100);
        }
        else
        {
            setProgress(qFloor((mImportCmdIdx * 100) / mImportCmdList.size()));
            startTimer();
        }
    }
};
#endif // FIMPORTSETTING_H
