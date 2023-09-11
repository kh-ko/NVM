#ifndef PROTOCOLDEF_H
#define PROTOCOLDEF_H

#include <QObject>
class ProtocolEnum: public QObject{
    Q_OBJECT
    Q_ENUMS(eProtocolValueType)

public:
    enum eProtocolValueType{
        PROTO_TYPE_INT   = 0                ,
        PROTO_TYPE_FLOAT = PROTO_TYPE_INT   + 1,
        PROTO_TYPE_ENUM  = PROTO_TYPE_FLOAT + 1,
        PROTO_TYPE_HEX   = PROTO_TYPE_ENUM + 1,
        PROTO_TYPE_INT_F = PROTO_TYPE_HEX  + 1,
    };
};

class ProtocolValueInfo: public QObject{
    Q_OBJECT

public:
    ProtocolEnum::eProtocolValueType mType = ProtocolEnum::PROTO_TYPE_INT;
    int         mStartIdx;
    int         mLen;
    double      mDiv;
    QString     mRowValue;

    explicit ProtocolValueInfo(QObject *parent = nullptr): QObject(parent)
    {
    }
    ~ProtocolValueInfo()
    {
    }
};

class ProtocolItem: public QObject{
    Q_OBJECT

public:
    QString       mWriteCmd = "";
    QString       mWriteRes = "";
    QString       mReadCmd = "";
    QString       mReadRes = "";

    QList<ProtocolValueInfo> mWriteValueInfos;
    QList<ProtocolValueInfo> mReadValueInfos;

    explicit ProtocolItem(QObject *parent = nullptr): QObject(parent)
    {
    }
    ~ProtocolItem()
    {
    }
};



#endif // PROTOCOLDEF_H
