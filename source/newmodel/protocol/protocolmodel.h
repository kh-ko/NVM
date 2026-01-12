#ifndef PROTOCOLMODEL_H
#define PROTOCOLMODEL_H
#include <QObject>
#include <QDebug>
#include <QList>

#include "source/newmodel/view/converter/tagvalueconverter.h"
#include "source/newmodel/view/tag/viewtagmodel.h"

class ProtocolTagLink : public QObject{
    Q_OBJECT

public:
    int Offset;
    int Length;
    double Gain = 1;
    QString ProtocolValue = "";
    ViewTagModel * TagPointer;
    TagValueConverter * ConverterPointer = nullptr;

    explicit ProtocolTagLink(QObject *parent = nullptr): QObject(parent){}
    ~ProtocolTagLink(){}

    explicit ProtocolTagLink(ViewTagModel * pTag, int offset, int length, TagValueConverter * pConverter, double gain,QObject * parent): QObject(parent)
    {
        TagPointer = pTag;
        Offset = offset;
        Length = length;
        Gain = gain;

        if(ConverterPointer != nullptr)
        {
            ConverterPointer->unRegSignal(this);
        }

        ConverterPointer = pConverter;

        if(pConverter != nullptr)
        {
            ConverterPointer->regSignal(this, SLOT(onValueChanged()));
        }
    }

    void onValueChanged()
    {
        if(TagPointer != nullptr && ConverterPointer != nullptr && ProtocolValue.length() > 0)
        {
            TagPointer->SetProtocolValue(ConverterPointer->convertToTagValue(ProtocolValue, Gain));
        }
    }
};

class ProtocolModel : public QObject{
    Q_OBJECT

public:
    QString Path;
    QString AccType;
    QString ReqProtocol;
    QString RespProtocol;
    QList<ProtocolTagLink *> TagLinkList;

    explicit ProtocolModel(QObject *parent = nullptr): QObject(parent){
    }
    ~ProtocolModel(){}

    explicit ProtocolModel(QString path, QString accType, QString req, QString res, QObject * parent): QObject(parent)
    {
        Path = path;
        AccType = accType;
        ReqProtocol = req;
        RespProtocol = res;
    }

    void SetTag(ViewTagModel * pTag, int offset, int length, TagValueConverter * pConverter, double gain)
    {
        pTag->SetProtocol(AccType, this);
        TagLinkList.append(new ProtocolTagLink(pTag, offset, length, pConverter, gain, this));
    }

    QString MakeReadCmd()
    {
        return ReqProtocol;
    }

    QString MakeWriteCmd()
    {
        QString cmd = ReqProtocol;

        foreach(ProtocolTagLink * pTagLink, TagLinkList)
        {
            if(pTagLink->ConverterPointer == nullptr)
            {
                cmd += pTagLink->TagPointer->GetWriteValue();
            }
            else
            {
                cmd += pTagLink->ConverterPointer->convertToProtocolValue(pTagLink->TagPointer->GetWriteValue(), pTagLink->Gain, pTagLink->Length);
            }
        }

        return cmd;
    }

    void SetReponseData(QString value, bool isPrintDebug = false)
    {
        if(value.startsWith(RespProtocol))
        {
            foreach(ProtocolTagLink * pTagLink, TagLinkList)
            {
                QString param;
                if(pTagLink->ConverterPointer == nullptr)
                {
                    param = pTagLink->Length > 0 ? value.mid(pTagLink->Offset, pTagLink->Length) : value.mid(pTagLink->Offset);
                }
                else
                {
                    param = pTagLink->ConverterPointer->convertToTagValue(pTagLink->Length > 0 ? value.mid(pTagLink->Offset, pTagLink->Length) : value.mid(pTagLink->Offset), pTagLink->Gain);
                }

                if(isPrintDebug)
                    qDebug() << "[" << Q_FUNC_INFO << "]" << param;
                pTagLink->ProtocolValue = param;
                pTagLink->TagPointer->SetProtocolValue(param);
            }
        }
    }

    void SetIsSupport(bool value)
    {
        foreach(ProtocolTagLink * pTagLink, TagLinkList)
        {
            pTagLink->TagPointer->setIsSupport(value);
        }
    }
};
#endif // PROTOCOLMODEL_H
