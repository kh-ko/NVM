#ifndef INTERFACETRACEDLGMODEL_H
#define INTERFACETRACEDLGMODEL_H

#include <QObject>
#include <QtMath>
#include <QFile>
#include "source/qmlmodel/def/qmlenumdef.h"
#include "source/util/etcutil.h"
#include "source/service/coreservice.h"
#include "source/service/util/filewriterex.h"

#define TRACE_UI_MAX_ROW_CNT 500
class InterfaceTraceDlgModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int     mMaxRowCnt  READ getMaxRowCnt  NOTIFY signalEventChangedMaxRowCnt )
    Q_PROPERTY(bool    mIsRecord   READ getIsRecord   NOTIFY signalEventChangedIsRecord  )
    Q_PROPERTY(QString mRecordTime READ getRecordTime NOTIFY signalEventChangedRecordTime)
    Q_PROPERTY(bool    mIsHold     READ getIsHold     NOTIFY signalEventChangedIsHold    )
    Q_PROPERTY(int     mSortMode   READ getSortMode   NOTIFY signalEventChangedSortMode  )
    Q_PROPERTY(int     mFoundIdx   READ getFoundIdx   NOTIFY signalEventChangedFoundIdx  )
    Q_PROPERTY(int     mFoundCount READ getFoundCount NOTIFY signalEventChangedFoundCount)
    Q_PROPERTY(int     mAccessMode READ getAccessMode NOTIFY signalEventChangedAccessMode)
    Q_PROPERTY(int     mMode       READ getMode       NOTIFY signalEventChangedMode      )
    Q_PROPERTY(bool    mIsEdit     READ getIsEdit     NOTIFY signalEventChangedIsEdit    )
    Q_PROPERTY(QString mStrStatus  READ getStrStatus  NOTIFY signalEventChangedStrStatus )
    Q_PROPERTY(QString mErrMsg     READ getErrMsg     NOTIFY signalEventChangedErrMsg    )
    Q_PROPERTY(int     mProgress   READ getProgress   NOTIFY signalEventChangedProgress  )

public:
    int     mMaxRowCnt   = 500;
    bool    mIsRecord    = false;
    QString mRecordTime  = "";
    bool    mIsHold      = false;
    int     mSortMode    = 0;
    int     mFoundIdx    = -1;
    int     mFoundCount  = 0;
    int     mAccessMode  = ValveEnumDef::ACCESS_LOCAL;
    int     mMode        = ValveEnumDef::MODE_INIT;
    bool    mIsEdit      = false;
    QString mStrStatus   = "Loading";
    QString mErrMsg      = "";
    int     mProgress    = 0 ;


    int     getMaxRowCnt (){ return mMaxRowCnt ;}
    bool    getIsRecord  (){ return mIsRecord  ;}
    QString getRecordTime(){ return mRecordTime;}
    bool    getIsHold    (){ return mIsHold    ;}
    int     getSortMode  (){ return mSortMode  ;}
    int     getFoundIdx  (){ return mFoundIdx  ;}
    int     getFoundCount(){ return mFoundCount;}
    int     getAccessMode(){ return mAccessMode;}
    int     getMode      (){ return mMode      ;}
    bool    getIsEdit    (){ return mIsEdit    ;}
    QString getStrStatus (){ return mStrStatus ;}
    QString getErrMsg    (){ return mErrMsg    ;}
    int     getProgress  (){ return mProgress  ;}


    void    setMaxRowCnt (int     value){if(mMaxRowCnt  == value)return; mMaxRowCnt  = value; emit signalEventChangedMaxRowCnt (value);}
    void    setIsRecord  (bool    value){if(mIsRecord   == value)return; mIsRecord   = value; emit signalEventChangedIsRecord  (value);}
    void    setRecordTime(QString value){if(mRecordTime == value)return; mRecordTime = value; emit signalEventChangedRecordTime(value);}
    void    setIsHold    (bool    value){if(mIsHold     == value)return; mIsHold     = value; emit signalEventChangedIsHold    (value);}
    void    setSortMode  (int     value){if(mSortMode   == value)return; mSortMode   = value; emit signalEventChangedSortMode  (value);}
    void    setFoundIdx  (int     value){if(mFoundIdx   == value)return; mFoundIdx   = value; emit signalEventChangedFoundIdx  (value);}
    void    setFoundCount(int     value){if(mFoundCount == value)return; mFoundCount = value; emit signalEventChangedFoundCount(value);}
    void    setAccessMode(int     value){if(mAccessMode == value)return; mAccessMode = value; emit signalEventChangedAccessMode(value);}
    void    setMode      (int     value){if(mMode       == value)return; mMode       = value; emit signalEventChangedMode      (value);}
    void    setIsEdit    (bool    value){if(mIsEdit     == value)return; mIsEdit     = value; emit signalEventChangedIsEdit    (value);}
    void    setStrStatus (QString value){if(mStrStatus  == value)return; mStrStatus  = value; emit signalEventChangedStrStatus (value);}
    void    setErrMsg    (QString value){if(mErrMsg     == value)return; mErrMsg     = value; emit signalEventChangedErrMsg    (value);}
    void    setProgress  (int     value){if(mProgress   == value)return; mProgress   = value; emit signalEventChangedProgress  (value);}

signals:
    void signalEventChangedMaxRowCnt (int     value);
    void signalEventChangedIsRecord  (bool    value);
    void signalEventChangedRecordTime(QString value);
    void signalEventChangedIsHold    (bool    value);
    void signalEventChangedSortMode  (int     value);
    void signalEventChangedFoundIdx  (int     value);
    void signalEventChangedFoundCount(int     value);
    void signalEventChangedAccessMode(int     value);
    void signalEventChangedMode      (int     value);
    void signalEventChangedIsEdit    (bool    value);
    void signalEventChangedStrStatus (QString value);
    void signalEventChangedErrMsg    (QString value);
    void signalEventChangedProgress  (int     value);

    void signalEventReceived(int insertRowIdx, QString localTime, QString interval, QString receivedData, QString transmittedData);
    void signalEventClear();

public slots:
    Q_INVOKABLE void onCmdRecord(bool value)
    {
        setIsRecord(value);

        if(value)
        {
            mRecordStartSec = QDateTime::currentSecsSinceEpoch();
            onCmdClear();
        }
        else if(getIsHold())
        {
            onCmdHold(false);
        }
        pValveSP->setTraceMode(value, this);
    }

    Q_INVOKABLE void onCmdHold(bool value)
    {
        if(getIsHold() && value == false)
        {
            foreach(QString data, traceHoldDataList)
            {
                traceDataList.append(data);
                procTarceSignal(traceDataList.size() - 1, data);
            }
            traceHoldDataList.clear();
        }
        setIsHold(value);
    }

    Q_INVOKABLE void onCmdClear()
    {
        setRecordTime("");
        setFoundCount(0);
        setFoundIdx(-1);
        traceDataList.clear();
        traceHoldDataList.clear();

        emit signalEventClear();
    }

    Q_INVOKABLE void onCmdSetSortMode(int sortMode)
    {
        int idx = 0;

        if(getSortMode() != sortMode)
        {
            setFoundCount(0);
            setFoundIdx(-1);
            emit signalEventClear();
            foreach(QString data, traceDataList)
            {
                procTarceSignal(idx++, data);
            }
        }

        setSortMode(sortMode);
    }

    Q_INVOKABLE void onCmdSearch(int sortMode, QString value)
    {
        int firstIdx = -1;
        int foundCount = 0;

        do{
            if(value == "")
                break;

            if(sortMode == 0)
            {
                int endIdx = traceDataList.size() - mMaxRowCnt;

                if(endIdx < 0)
                    endIdx = 0;

                for(int i = traceDataList.size() - 1; i > endIdx-1; i--)
                {
                    QString temp = traceDataList[i];

                    if(temp.contains(value))
                    {
                        if(firstIdx == -1)
                            firstIdx = i;

                        foundCount ++;
                    }
                }
            }
            else
            {
                int startIdx = 0 < traceDataList.size() - mMaxRowCnt ? traceDataList.size() - mMaxRowCnt : 0;

                for(int i = startIdx; i < traceDataList.size(); i++)
                {
                    QString temp = traceDataList[i];

                    if(temp.contains(value))
                    {
                        if(firstIdx == -1)
                            firstIdx = i;

                        foundCount ++;
                    }
                }
            }
        }while (0);

        qDebug() << "[" << Q_FUNC_INFO << "]firstIdx = " << firstIdx;

        setFoundIdx(firstIdx);
        setFoundCount(foundCount);
    }

    Q_INVOKABLE void onCmdSearchPre(int sortMode, QString value)
    {
        if(sortMode == 0)
        {
            searchFromStart(value);
        }
        else
        {
            searchFromEnd(value);
        }
    }

    Q_INVOKABLE void onCmdSearchNext(int sortMode, QString value)
    {
        if(sortMode == 0)
        {
            searchFromEnd(value);
        }
        else
        {
            searchFromStart(value);
        }
    }

    Q_INVOKABLE void onCmdOpenFile(QString fileName)
    {
        QFile file;

        onCmdClear();

        file.setFileName(fileName);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        while(!in.atEnd()) {
            QString line = in.readLine();
            traceDataList.append(line);
            procTarceSignal(traceDataList.size() - 1, line);
        }

        file.close();
    }

    Q_INVOKABLE void onCmdSaveFile(QString fileName)
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);

        foreach(QString data, traceDataList)
        {
            out << data << endl;
        }
        file.close();
    }

public:
    QTimer mTimer;
    qint64 mRecordStartSec;
    qint64 mRecordSec;
    QStringList traceDataList;
    QStringList traceHoldDataList;

    explicit InterfaceTraceDlgModel(QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_CHANGED_ACCESS;
        ENABLE_SLOT_VALVE_CHANGED_MODE;
        ENABLE_SLOT_VALVE_TRACE;

        mTimer.setInterval(100);
        connect(&mTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        mTimer.start();
    }
    ~InterfaceTraceDlgModel()
    {
        if(getIsRecord())
            pValveSP->setTraceMode(false, this);
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

    void onValveRecevedTraceData(QString data)
    {
        if(getIsRecord() == false)
            return;

        data = QString("%1 %2").arg(QDateTime::currentDateTime().toString("hh:mm:ss.zzz")).arg(data.remove("\r\n"));

        if(getIsHold())
        {
            traceHoldDataList.append(data);
            return;
        }

        traceDataList.append(data);

        procTarceSignal(traceDataList.size() - 1, data);
    }

    void onTimeout()
    {
        mRecordSec = QDateTime::currentSecsSinceEpoch() - mRecordStartSec;

        if(getIsRecord() && getIsHold() == false)
        {
            setRecordTime(QString("%1:%2:%3").arg(((mRecordSec) / 60 / 60), 2, 10, QChar('0')).arg(((mRecordSec) / 60 % 60), 2, 10, QChar('0')).arg((mRecordSec % 60), 2, 10, QChar('0')));
        }
    }

private:
    void procTarceSignal(int rowIdx, QString data)
    {
        QString localTime = "";
        QString interval = "";
        QString received = "";
        QString transmitted = "";

        QStringList dataList = data.split(" ");

        if(dataList.length() > 0)
            localTime = dataList[0];

        if(dataList.length() > 1)
            interval = dataList[1];

        if(dataList.length() > 2)
            received = dataList[2];

        if(dataList.length() > 3)
            transmitted = dataList[3];

        emit signalEventReceived(rowIdx, localTime, interval, received, transmitted);
    }

    void searchFromEnd(QString value)
    {
        int endIdx = traceDataList.size() - mMaxRowCnt;

        if(endIdx < 0)
            endIdx = 0;

        if(getFoundIdx() > (traceDataList.size() - 1)
           || getFoundIdx() < 0 )
            return;

        for(int i = getFoundIdx() - 1; i > endIdx - 1; i-- )
        {
            QString temp = traceDataList[i];

            if(temp.contains(value))
            {
                setFoundIdx(i);
                break;
            }
        }
    }

    void searchFromStart(QString value)
    {
        int startIdx = getFoundIdx() + 1 < traceDataList.size() - mMaxRowCnt ? traceDataList.size() - mMaxRowCnt : getFoundIdx() + 1;

        if(getFoundIdx() > (traceDataList.size() - 1)
           || getFoundIdx() < 0 )
            return;

        for(int i = startIdx; i < traceDataList.size(); i++)
        {
            QString temp = traceDataList[i];

            if(temp.contains(value))
            {
                setFoundIdx(i);
                break;
            }
        }
    }
};
#endif // INTERFACETRACEDLGMODEL_H
