#ifndef TAGMODEL_H
#define TAGMODEL_H
#include <QObject>
#include "source/newmodel/view/tag/tagenum.h"

class TagModel : public QObject{
    Q_OBJECT

    Q_PROPERTY(bool     IsNotUsed            READ getIsNotUsed         NOTIFY signalEventChangedIsNotUsed )
    Q_PROPERTY(bool     IsBlock              READ getIsBlock           NOTIFY signalEventChangedIsBlock   )
    Q_PROPERTY(bool     IsSupport            READ getIsSupport         NOTIFY signalEventChangedIsSupport )
    Q_PROPERTY(QString  AccType              READ getAccType           NOTIFY signalEventChangedAccType   )
    Q_PROPERTY(QString  Name                 READ getName              NOTIFY signalEventChangedName      )
    Q_PROPERTY(QString  Value                READ getValue             NOTIFY signalEventChangedValue     )
    Q_PROPERTY(int      MajRev               READ getMajRev            NOTIFY signalEventChangedMajRev    )
    Q_PROPERTY(int      MinRev               READ getMinRev            NOTIFY signalEventChangedMinRev    )
    Q_PROPERTY(int      LengthInfo           READ getLengthInfo        NOTIFY signalEventChangedLengthInfo)  //  information for DNet I/O assy
    Q_PROPERTY(TagEnumListModel* modeOptions READ modeOptions CONSTANT                                    )

public:
    static int TypeString         (){ return  0; }
    static int TypeBase10         (){ return  1; }
    static int TypeBase16         (){ return  2; }
    static int TypeBase36         (){ return  3; }
    static int TypeFloat          (){ return  4; }
    static int TypeBitmap         (){ return  5; }
    static int TypeFirmwareVersion(){ return  6; }
    static int TypeEnum           (){ return  7; }
    static int TypeSerialNumber   (){ return  8; }
    static int TypeDNetRevision   (){ return  9; }
    static int TypePosi           (){ return 10; }
    static int TypeFloatGain      (){ return 11; }
    static int TypeEnumSelect     (){ return 12; }

    bool    IsEdit = false;
    int     ValueType = 0;
    int     BitOffset = 0;
    int     BitMask   = 0;
    QString WriteValue = "";
    int     WriteMajRev = 0;
    int     WriteMinRev = 0;
    QObject * ReadProtocol = nullptr ;
    QObject * WriteProtocol = nullptr;

    bool    IsNotUsed        = false;
    bool    IsBlock          = false;
    bool    IsSupport        = true ;
    QString AccType          = ""   ;
    QString Name             = ""   ;
    QString Value            = ""   ;
    int     MajRev           = 0    ;
    int     MinRev           = 0    ;
    int     LengthInfo       = 0    ;
    TagEnumListModel *m_modeOptions;

    bool    getIsNotUsed       (){ return IsNotUsed       ; }
    bool    getIsBlock         (){ return IsBlock         ; }
    bool    getIsSupport       (){ return IsSupport       ; }
    QString getAccType         (){ return AccType         ; }
    QString getName            (){ return Name            ; }
    QString getValue           (){ return Value           ; }
    int     getMajRev          (){ return MajRev          ; }
    int     getMinRev          (){ return MinRev          ; }
    int     getLengthInfo      (){ return LengthInfo      ; }
    TagEnumListModel* modeOptions() const { return m_modeOptions;}

    void setIsNotUsed       (bool    value){ if(IsNotUsed        == value) return; IsNotUsed        = value; emit signalEventChangedIsNotUsed       (value);}
    void setIsBlock         (bool    value){ if(IsBlock          == value) return; IsBlock          = value; emit signalEventChangedIsBlock         (value);}
    void setIsSupport       (bool    value){ if(IsSupport        == value) return; IsSupport        = value; emit signalEventChangedIsSupport       (value);}
    void setAccType         (QString value){ if(AccType          == value) return; AccType          = value; emit signalEventChangedAccType         (value);}
    void setName            (QString value){ if(Name             == value) return; Name             = value; emit signalEventChangedName            (value);}
    void setValue           (QString value){                                       Value            = value; emit signalEventChangedValue           (value);}
    void setMajRev          (int     value){                                       MajRev           = value; emit signalEventChangedMajRev          (value); emit signalEventChangedValue("0");}
    void setMinRev          (int     value){                                       MinRev           = value; emit signalEventChangedMinRev          (value); emit signalEventChangedValue("0");}
    void setLengthInfo      (int     value){                                       LengthInfo       = value; emit signalEventChangedLengthInfo      (value);}

signals:
    void signalEventChangedIsNotUsed       (bool    value);
    void signalEventChangedIsBlock         (bool    value);
    void signalEventChangedIsSupport       (bool    value);
    void signalEventChangedAccType         (QString value);
    void signalEventChangedName            (QString value);
    void signalEventChangedValue           (QString value);
    void signalEventChangedMajRev          (int     value);
    void signalEventChangedMinRev          (int     value);
    void signalEventChangedLengthInfo      (int     value);

public:
    explicit TagModel(QObject *parent = nullptr): QObject(parent){
        m_modeOptions = new TagEnumListModel(this);
    }
    explicit TagModel(QString name, QString accType, int valueType, TagEnumListModel * pEnumList, int bitOffset,QObject *parent = nullptr): QObject(parent){
        setName(name);
        setAccType(accType);

        ValueType = valueType;

        if(pEnumList != nullptr)
        {
            m_modeOptions = pEnumList;
        }
        else
        {
            m_modeOptions = new TagEnumListModel(this);
        }

        BitOffset = bitOffset;
        BitMask = (0x1 << BitOffset);

    }
    ~TagModel(){}

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

    int getWriteMajRev()
    {
        return WriteMajRev;
    }

    int getWriteMinRev()
    {
        return WriteMinRev;
    }

    void SetProtocolValue(QString value)
    {
        setValue(value);
    }

    void SetProtocolBitmapValue(int value)
    {
        if((value & BitMask) == BitMask)
            setValue("1");
        else
            setValue("0");
    }


public slots:
    Q_INVOKABLE void writeValue(QString value)
    {
        //if(value == getValue())
        //    return;

        IsEdit = true;
        WriteValue = value;
    }

    Q_INVOKABLE void writeMajRevValue(QString value)
    {
        bool ok;
        int intValue = value.toInt(&ok, 10);

        if(ok)
        {
            WriteMajRev = intValue;
        }
        else
        {
            WriteMajRev = 0;
        }

        IsEdit = true;
    }

    Q_INVOKABLE void writeMinRevValue(QString value)
    {
        bool ok;
        int intValue = value.toInt(&ok, 10);

        if(ok)
        {
            WriteMinRev = intValue;
        }
        else
        {
            WriteMinRev = 0;
        }

        IsEdit = true;
    }
};
#endif // TAGMODEL_H
