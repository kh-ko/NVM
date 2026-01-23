#ifndef VERSIONCHECKER_H
#define VERSIONCHECKER_H

#include <QObject>
#include <QDebug>
#include "source/newmodel/view/tag/tagmodel.h"
#include "source/newmodel/protocol/protocolparamslot.h"
#include "source/newmodel/view/converter/dnetv1assyconverter.h"
#include "source/newmodel/view/converter/hextobase10converter.h"

class VersionChecker: QObject
{
    Q_OBJECT
public:
    static VersionChecker * getInstance()
    {
        static VersionChecker *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new VersionChecker();
        }

        return mpSelf;
    }

    explicit VersionChecker(QObject *parent = nullptr):QObject(parent)
    {

    }

    ~VersionChecker(){

    }

    void regIdValveTypeTag(TagModel * pTag)
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedIdValveType(QString)));
    }

    void regValveRevTag(TagModel * pTag)
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedValveRev(QString)));
    }

    void regFirmwareVerTag(TagModel * pTag)
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedFirmwareVer(QString)));
    }

    void setDNetV1TbSlot(ProtocolParamSlot * pOutReadSlot, ProtocolParamSlot * pOutWriteSlot, ProtocolParamSlot * pInReadSlot, ProtocolParamSlot * pInWriteSlot)
    {
        DNetV1OutTbReadSlotPointer  = pOutReadSlot ;
        DNetV1OutTbWriteSlotPointer = pOutWriteSlot;
        DNetV1InTbReadSlotPointer   = pInReadSlot  ;
        DNetV1InTbWriteSlotPointer  = pInWriteSlot ;
    }

    void setDNetV1TbDummyTag(TagModel * pOutDummyTag, TagModel * pInDummyTag)
    {
        DNetV1OutTbDummyTagPointer = pOutDummyTag;
        DNetV1InTbDummyTagPointer = pInDummyTag;
    }


public slots:
    void onTagChangedIdValveType(QString value)
    {
        bool ok;
        idValveTypeIdx = value.toInt(&ok, 10);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value << ", int value = " << idValveTypeIdx;

        if(!ok){ idValveTypeIdx = 1; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}
    }

    void onTagChangedValveRev(QString value)
    {
        bool ok;
        valveRevision3 = value.toInt(&ok, 10);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value << ", int value = " << valveRevision3;

        if(!ok){ valveRevision3 = 0; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}

        checkDeviceNet();
    }

    void onTagChangedFirmwareVer(QString value)
    {
        bool ok;
        firmwareVersion = value.rightRef(4).toInt(&ok, 16);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value.rightRef(4) << ", int value = " << firmwareVersion;

        if(!ok){ firmwareVersion = 0; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}
    }

private:
    int idValveTypeIdx  = 1;
    int valveRevision3  = 0;
    int firmwareVersion = 0;

    ProtocolParamSlot * DNetV1OutTbReadSlotPointer;
    ProtocolParamSlot * DNetV1OutTbWriteSlotPointer;
    ProtocolParamSlot * DNetV1InTbReadSlotPointer;
    ProtocolParamSlot * DNetV1InTbWriteSlotPointer;
    TagModel * DNetV1OutTbDummyTagPointer;
    TagModel * DNetV1InTbDummyTagPointer;

    void checkDeviceNet()
    {
        if(valveRevision3 < 16/*G*/)
        {
            DNetV1OutTbReadSlotPointer->SetConverter(DNetV1AssyConverter::getInstance());
            DNetV1OutTbWriteSlotPointer->SetConverter(DNetV1AssyConverter::getInstance());
            DNetV1InTbReadSlotPointer->SetConverter(DNetV1AssyConverter::getInstance());
            DNetV1InTbWriteSlotPointer->SetConverter(DNetV1AssyConverter::getInstance());
            DNetV1OutTbDummyTagPointer->setIsBlock(true);
            DNetV1InTbDummyTagPointer->setIsBlock(true);
        }
        else
        {
            DNetV1OutTbReadSlotPointer->SetConverter(HexToBase10Converter::getInstance());
            DNetV1OutTbWriteSlotPointer->SetConverter(HexToBase10Converter::getInstance());
            DNetV1InTbReadSlotPointer->SetConverter(HexToBase10Converter::getInstance());
            DNetV1InTbWriteSlotPointer->SetConverter(HexToBase10Converter::getInstance());
            DNetV1OutTbDummyTagPointer->setIsBlock(false);
            DNetV1InTbDummyTagPointer->setIsBlock(false);
        }
    }
};
#endif // VERSIONCHECKER_H
