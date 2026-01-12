#ifndef VIEWTAGMODEL_H
#define VIEWTAGMODEL_H
#include <QObject>
#include "source/newmodel/view/tag/tagenum.h"

class ViewTagModel : public QObject{
    Q_OBJECT

    Q_PROPERTY(bool     IsBlock              READ getIsBlock           NOTIFY signalEventChangedIsBlock  )
    Q_PROPERTY(bool     IsSupport            READ getIsSupport         NOTIFY signalEventChangedIsSupport)
    Q_PROPERTY(QString  UiType               READ getUiType            NOTIFY signalEventChangedUiType   )
    Q_PROPERTY(QString  Name                 READ getName              NOTIFY signalEventChangedName     )
    Q_PROPERTY(QString  Value                READ getValue             NOTIFY signalEventChangedValue    )
    //Q_PROPERTY(QString  Min                  READ getMin               NOTIFY signalEventChangedMin      )
    //Q_PROPERTY(QString  Max                  READ getMax               NOTIFY signalEventChangedMax      )
    Q_PROPERTY(TagEnumListModel* modeOptions READ modeOptions CONSTANT                                   )

public:
    QString Path = "";
    bool    IsEdit = false;
    QString WriteValue = "";
    QObject * ReadProtocol = nullptr;
    QObject * WriteProtocol = nullptr;

    bool    IsBlock          = false;
    bool    IsSupport        = true;
    QString UiType           = "";
    QString Name             = "";
    QString Value            = "";
    //QString Min              = "";
    //QString Max              = "";
    TagEnumListModel *m_modeOptions;

    bool    getIsBlock         (){ return IsBlock         ; }
    bool    getIsSupport       (){ return IsSupport       ; }
    QString getUiType          (){ return UiType          ; }
    QString getName            (){ return Name            ; }
    QString getValue           (){ return Value           ; }
    //QString getMin             (){ return Min             ; }
    //QString getMax             (){ return Max             ; }
    TagEnumListModel* modeOptions() const { return m_modeOptions;}

    void setIsBlock         (bool    value){ if(IsBlock          == value) return; IsBlock          = value; emit signalEventChangedIsBlock         (value);}
    void setIsSupport       (bool    value){ if(IsSupport        == value) return; IsSupport        = value; emit signalEventChangedIsSupport       (value);}
    void setUiType          (QString value){ if(UiType           == value) return; UiType           = value; emit signalEventChangedUiType          (value);}
    void setName            (QString value){ if(Name             == value) return; Name             = value; emit signalEventChangedName            (value);}
    void setValue           (QString value){                                       Value            = value; emit signalEventChangedValue           (value);}
    ////void setMin             (QString value){ if(Min              == value) return; Min              = value; emit signalEventChangedMin             (value);}
    ////void setMax             (QString value){ if(Max              == value) return; Max              = value; emit signalEventChangedMax             (value);}

signals:
    void signalEventChangedIsBlock         (bool    value);
    void signalEventChangedIsSupport       (bool    value);
    void signalEventChangedUiType          (QString value);
    void signalEventChangedName            (QString value);
    void signalEventChangedValue           (QString value);
    void signalEventChangedMin             (QString value);
    void signalEventChangedMax             (QString value);

public:
    explicit ViewTagModel(QObject *parent = nullptr): QObject(parent){
        m_modeOptions = new TagEnumListModel(this);
    }
    explicit ViewTagModel(QString path, QString uiType, /*QString min, QString max,*/ TagEnumListModel * pEnumList, QObject *parent = nullptr): QObject(parent){
        Path = path;
        QStringList pathList = Path.split(".");

        if(pathList.size() > 0)
            setName(pathList[pathList.size() - 1].trimmed());
        else
            setName("Unknown Name");

        setUiType(uiType);
        //setMin(min);
        //setMax(max);

        if(pEnumList != nullptr)
        {
            m_modeOptions = pEnumList;
        }
        else
        {
            m_modeOptions = new TagEnumListModel(this);
        }
    }
    ~ViewTagModel(){}

    ViewTagModel * CopyTo(QObject * parent)
    {
        return new ViewTagModel(Path, UiType, /*Min, Max,*/ m_modeOptions, parent);
    }

    void SetProtocol(QString accType, QObject * protocol)
    {
        if(accType == "Read")
            ReadProtocol = protocol;
        else
            WriteProtocol = protocol;
    }

    QString GetWriteValue()
    {
        return WriteValue;
    }

    void SetProtocolValue(QString value)
    {
        IsEdit = false;
        setValue(value);
    }


public slots:

    Q_INVOKABLE void writeValue(QString value)
    {
        if(value == getValue())
            return;

        IsEdit = true;
        WriteValue = value;
    }
};
#endif // VIEWTAGMODEL_H
