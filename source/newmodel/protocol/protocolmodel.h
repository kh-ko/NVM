#ifndef PROTOCOLMODEL_H
#define PROTOCOLMODEL_H
#include <QObject>
#include <QDebug>
#include <QList>

#include "source/newmodel/protocol/protocolparamslot.h"

class ProtocolModel : public QObject{
    Q_OBJECT

public:
    bool    IsParam = false;
    QString Name;
    QString AccType;
    QString ReqProtocol;
    QString RespProtocol;
    QList<ProtocolParamSlot *> SlotList;

    explicit ProtocolModel(QObject *parent = nullptr): QObject(parent){
    }
    ~ProtocolModel(){}

    explicit ProtocolModel(QString name, QString accType, bool isParam, QString req, QString res, QObject * parent): QObject(parent)
    {
        Name = name;
        AccType = accType;
        IsParam = isParam;
        ReqProtocol = req;
        RespProtocol = res;
    }

    ProtocolParamSlot * AppendSlot(QString name, int offset, int length, int dataType, double gain)
    {
        ProtocolParamSlot * pSlot = new ProtocolParamSlot(name, AccType, offset, length, dataType, gain, this);
        SlotList.append(pSlot);

        return pSlot;
    }

    QString MakeReadCmd()
    {
        return ReqProtocol;
    }

    QString MakeWriteCmd()
    {
        QString cmd = ReqProtocol;

        foreach(ProtocolParamSlot * pSlot, SlotList)
        {
            cmd += pSlot->MakeProtoWriteValue();
        }

        return cmd;
    }

    void SetReponseData(QString value, bool isPrintDebug = false)
    {
        if(isPrintDebug)
            qDebug() << "[" << Q_FUNC_INFO << "]" << value;

        if(value.startsWith(RespProtocol))
        {
            foreach(ProtocolParamSlot * pSlot, SlotList)
            {
                pSlot->SetProtocolResponseData(value);
            }
        }
    }

    void SetIsSupport(bool value)
    {
        foreach(ProtocolParamSlot * pSlot, SlotList)
        {
            pSlot->SetIsSupport(value);
        }
    }
};
#endif // PROTOCOLMODEL_H
