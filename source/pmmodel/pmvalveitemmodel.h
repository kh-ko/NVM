#ifndef PMVALVEITEMMODEL_H
#define PMVALVEITEMMODEL_H

#include <QObject>
#include "source/service/coreservice.h"
#include "source/pmmodel/pmenum.h"

class PmValveItemModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool     IsBlock             READ getIsBlock                              NOTIFY signalEventChangedIsBlock         )
    Q_PROPERTY(bool     IsSupport           READ getIsSupport                            NOTIFY signalEventChangedIsSupport       )
    Q_PROPERTY(QString  UiType              READ getUiType                               NOTIFY signalEventChangedUiType          )
    Q_PROPERTY(QString  Name                READ getName                                 NOTIFY signalEventChangedName            )
    Q_PROPERTY(QString  Value               READ getValue                                NOTIFY signalEventChangedValue           )
    Q_PROPERTY(QString  Min                 READ getMin                                  NOTIFY signalEventChangedMin             )
    Q_PROPERTY(QString  Max                 READ getMax                                  NOTIFY signalEventChangedMax             )
    Q_PROPERTY(PmEnumListModel* modeOptions READ modeOptions CONSTANT                                                             )

public:
    QString mPath = "";

    bool    IsBlock          = false;
    bool    IsSupport        = true;
    QString UiType           = "";
    QString Name             = "";
    QString Value            = "";
    QString Min              = "";
    QString Max              = "";
    PmEnumListModel *m_modeOptions;

    bool    getIsBlock         (){ return IsBlock         ; }
    bool    getIsSupport       (){ return IsSupport       ; }
    QString getUiType          (){ return UiType          ; }
    QString getName            (){ return Name            ; }
    QString getValue           (){ return Value           ; }
    QString getMin             (){ return Min             ; }
    QString getMax             (){ return Max             ; }
    PmEnumListModel* modeOptions() const { return m_modeOptions; }

    void setIsBlock         (bool    value){ if(IsBlock          == value) return; IsBlock          = value; emit signalEventChangedIsBlock         (value);}
    void setIsSupport       (bool    value){ if(IsSupport        == value) return; IsSupport        = value; emit signalEventChangedIsSupport       (value);}
    void setUiType          (QString value){ if(UiType           == value) return; UiType           = value; emit signalEventChangedUiType          (value);}
    void setName            (QString value){ if(Name             == value) return; Name             = value; emit signalEventChangedName            (value);}
    void setValue           (QString value){                                       Value            = value; emit signalEventChangedValue           (value);}
    void setMin             (QString value){ if(Min              == value) return; Min              = value; emit signalEventChangedMin             (value);}
    void setMax             (QString value){ if(Max              == value) return; Max              = value; emit signalEventChangedMax             (value);}

signals:
    void signalEventChangedIsBlock         (bool    value);
    void signalEventChangedIsSupport       (bool    value);
    void signalEventChangedUiType          (QString value);
    void signalEventChangedName            (QString value);
    void signalEventChangedValue           (QString value);
    void signalEventChangedMin             (QString value);
    void signalEventChangedMax             (QString value);

public:
    explicit PmValveItemModel(QObject *parent = nullptr): QObject(parent)
    {
        m_modeOptions = new PmEnumListModel(this);
    }

    explicit PmValveItemModel(QString path, QString readReq, QString readRes, QString writeReq, QString writeRes, int offset, int length, QString uiType, QString min, QString max, PmEnumListModel* pEnumList, QString description, QObject *parent = nullptr): QObject(parent)
    {
        ENABLE_SLOT_VALVE_WRITTEN_PM_SYNC;
        ENABLE_SLOT_VALVE_WRITTEN_PM_COMMIT;

        mPath = path;
        QStringList pathList = mPath.split(".");

        if(pathList.size() > 0)
            setName(pathList[pathList.size() - 1].trimmed());
        else
            setName("Unknown Name");

        mReadReq = readReq;
        mReadRes = readRes;
        mWriteReq = writeReq;
        mWriteRes = writeRes;
        mOffset = offset;
        mLength = length;

        setUiType(uiType);
        setMin(min);
        setMax(max);

        if(pEnumList != nullptr)
        {
            m_modeOptions = pEnumList;
        }
        else
        {
            m_modeOptions = new PmEnumListModel(this);
        }
    }
    ~PmValveItemModel()
    {
    }

public slots:
    void onValveWrittenPmSync(ValveResponseDto dto)
    {
        QString value = nullptr;

        if(dto.mReqDto.mpRef != this)
            return;

        //qDebug() << "[" << Name << "]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(dto.mIsNetworkErr)
        {
            pValveSP->pmSyncRequest(mReadReq, this, 0);
            return;
        }
        if(dto.mResData.startsWith(mReadRes))
        {
            if(mLength == -1){ value = dto.mResData.mid(mReadRes.length() + mOffset         ); }
            else             { value = dto.mResData.mid(mReadRes.length() + mOffset, mLength); }

            setValue(value);
            setIsSupport(true);
        }
        else {
            setIsSupport(false);
        }

        setIsBlock(false);
    }

    void onValveWrittenPmCommit(ValveResponseDto dto)
    {
        QString value = nullptr;

        if(dto.mReqDto.mpRef != this)
            return;

        qDebug() << "[" << Name << "]" << dto.mReqDto.mReqCommand << "," << dto.mResData;

        if(dto.mIsNetworkErr)
        {
            pValveSP->pmCommitRequest(mWriteReq, this, 0);
            return;
        }
        if(dto.mResData.startsWith(mWriteRes))
        {
            if(mLength == -1){ value = dto.mResData.mid(mWriteRes.length() + mOffset         ); }
            else             { value = dto.mResData.mid(mWriteRes.length() + mOffset, mLength); }
            setValue(value);
        }
        else
        {
            // todo error display
        }

        setIsBlock(false);
    }

    Q_INVOKABLE bool remoteSync()
    {
        if(IsBlock)
            return false;

        setIsBlock(true);

        pValveSP->pmSyncRequest(mReadReq, this, 0);

        return true;
    }

    Q_INVOKABLE bool commit(QString inValue)
    {
        if(IsBlock || inValue.length() == 0)
            return false;

        setIsBlock(true);

        pValveSP->pmCommitRequest(QString("%1%2").arg(mWriteReq).arg(inValue), this, 0);

        return true;
    }

private:
    QString mReadReq = "";
    QString mReadRes = "";
    QString mWriteReq = "";
    QString mWriteRes = "";
    int     mOffset = 0;
    int     mLength = -1;
};

#endif // PMVALVEITEMMODEL_H

