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
    int idValveTypeIdx  = 1;
    int valveRevision1  = 0;
    int valveRevision2  = 0;
    int valveRevision3  = 0;
    int valveRevisionValue = 0;
    int firmwareVersion = 0;

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

    void regValveRev1Tag(TagModel * pTag)
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedValveRev1(QString)));
    }

    void regValveRev2Tag(TagModel * pTag)
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedValveRev2(QString)));
    }

    void regValveRev3Tag(TagModel * pTag)
    {
        connect(pTag, SIGNAL(signalEventChangedValue(QString)), this, SLOT(onTagChangedValveRev3(QString)));
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

    void setDNetDIOTag(TagModel * pDOEnableTag, TagModel * pDOFuncTag, TagModel * pDOPolarityTag, TagModel * pDOStateTag, TagModel * pDIEnableTag, TagModel * pDIFuncTag, TagModel * pDIPolarityTag, TagModel * pDIStateTag)
    {
        DNetDOEnableTagPointer     = pDOEnableTag;
        DNetDOFuncTagPointer       = pDOFuncTag;
        DNetDOPolarityTagPointer   = pDOPolarityTag;
        DNetDOStateTagPointer      = pDOStateTag;
        DNetDIEnableTagPointer     = pDIEnableTag;
        DNetDIFuncTagPointer       = pDIFuncTag;
        DNetDIPolarityTagPointer   = pDIPolarityTag;
        DNetDIStateTagPointer      = pDIStateTag;
    }

    void setPwrConnDIOTag(TagModel * pPwrConnDI01EnableTag, TagModel * pPwrConnDI01FuncTag, TagModel * pPwrConnDI01PolarityTag, TagModel * pPwrConnDI01StateTag,
                          TagModel * pPwrConnDI02EnableTag, TagModel * pPwrConnDI02FuncTag, TagModel * pPwrConnDI02PolarityTag, TagModel * pPwrConnDI02StateTag,
                          TagModel * pPwrConnDO01EnableTag, TagModel * pPwrConnDO01FuncTag, TagModel * pPwrConnDO01PolarityTag, TagModel * pPwrConnDO01StateTag,
                          TagModel * pPwrConnDO02EnableTag, TagModel * pPwrConnDO02FuncTag, TagModel * pPwrConnDO02PolarityTag, TagModel * pPwrConnDO02StateTag)
    {
        PwrConnDI01EnableTagPointer   = pPwrConnDI01EnableTag;
        PwrConnDI01FuncTagPointer     = pPwrConnDI01FuncTag;
        PwrConnDI01PolarityTagPointer = pPwrConnDI01PolarityTag;
        PwrConnDI01StateTagPointer    = pPwrConnDI01StateTag;
        PwrConnDI02EnableTagPointer   = pPwrConnDI02EnableTag;
        PwrConnDI02FuncTagPointer     = pPwrConnDI02FuncTag;
        PwrConnDI02PolarityTagPointer = pPwrConnDI02PolarityTag;
        PwrConnDI02StateTagPointer    = pPwrConnDI02StateTag;
        PwrConnDO01EnableTagPointer   = pPwrConnDO01EnableTag;
        PwrConnDO01FuncTagPointer     = pPwrConnDO01FuncTag;
        PwrConnDO01PolarityTagPointer = pPwrConnDO01PolarityTag;
        PwrConnDO01StateTagPointer    = pPwrConnDO01StateTag;
        PwrConnDO02EnableTagPointer   = pPwrConnDO02EnableTag;
        PwrConnDO02FuncTagPointer     = pPwrConnDO02FuncTag;
        PwrConnDO02PolarityTagPointer = pPwrConnDO02PolarityTag;
        PwrConnDO02StateTagPointer    = pPwrConnDO02StateTag;
    }


public slots:
    void onTagChangedIdValveType(QString value)
    {
        bool ok;
        idValveTypeIdx = value.toInt(&ok, 10);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value << ", int value = " << idValveTypeIdx;

        if(!ok){ idValveTypeIdx = 1; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}
    }

    void onTagChangedValveRev1(QString value)
    {
        bool ok;
        valveRevision1 = value.toInt(&ok, 10);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value << ", int value = " << valveRevision1;

        if(!ok){ valveRevision1 = 0; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}
    }

    void onTagChangedValveRev2(QString value)
    {
        bool ok;
        valveRevision2 = value.toInt(&ok, 10);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value << ", int value = " << valveRevision2;

        if(!ok){ valveRevision2 = 0; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}
    }

    void onTagChangedValveRev3(QString value)
    {
        bool ok;
        valveRevision3 = value.toInt(&ok, 10);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value << ", int value = " << valveRevision3;

        if(!ok){ valveRevision3 = 0; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}

        checkRevisionDependency();
    }

    void onTagChangedFirmwareVer(QString value)
    {
        bool ok;
        firmwareVersion = value.rightRef(4).toInt(&ok, 16);

        qDebug() << "[" << Q_FUNC_INFO << "]value = " << value.rightRef(4) << ", int value = " << firmwareVersion;

        if(!ok){ firmwareVersion = 0; qDebug() << "[" << Q_FUNC_INFO << "]Convert Error";}
    }

private:
    ProtocolParamSlot * DNetV1OutTbReadSlotPointer;
    ProtocolParamSlot * DNetV1OutTbWriteSlotPointer;
    ProtocolParamSlot * DNetV1InTbReadSlotPointer;
    ProtocolParamSlot * DNetV1InTbWriteSlotPointer;
    TagModel * DNetV1OutTbDummyTagPointer;
    TagModel * DNetV1InTbDummyTagPointer;

    TagModel * DNetDOEnableTagPointer;
    TagModel * DNetDOFuncTagPointer;
    TagModel * DNetDOPolarityTagPointer;
    TagModel * DNetDOStateTagPointer;
    TagModel * DNetDIEnableTagPointer;
    TagModel * DNetDIFuncTagPointer;
    TagModel * DNetDIPolarityTagPointer;
    TagModel * DNetDIStateTagPointer;

    TagModel * PwrConnDI01EnableTagPointer;
    TagModel * PwrConnDI01FuncTagPointer;
    TagModel * PwrConnDI01PolarityTagPointer;
    TagModel * PwrConnDI01StateTagPointer;
    TagModel * PwrConnDI02EnableTagPointer;
    TagModel * PwrConnDI02FuncTagPointer;
    TagModel * PwrConnDI02PolarityTagPointer;
    TagModel * PwrConnDI02StateTagPointer;
    TagModel * PwrConnDO01EnableTagPointer;
    TagModel * PwrConnDO01FuncTagPointer;
    TagModel * PwrConnDO01PolarityTagPointer;
    TagModel * PwrConnDO01StateTagPointer;
    TagModel * PwrConnDO02EnableTagPointer;
    TagModel * PwrConnDO02FuncTagPointer;
    TagModel * PwrConnDO02PolarityTagPointer;
    TagModel * PwrConnDO02StateTagPointer;


    void checkRevisionDependency()
    {
        valveRevisionValue = (valveRevision1 * 36 * 36) + (valveRevision2 * 36) + valveRevision3;

        // REVISION Flag : 00G 부터 사용자가 Dummy 선택 가능
        if(valveRevisionValue < 16/*Base36 00G */)
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

        // REVISION Flag : 010 부터 PwrConnIo 적용
        if(valveRevisionValue < 36/*Base36 010 */)
        {
            DNetDOEnableTagPointer->setIsNotUsed(false);
            DNetDOFuncTagPointer->setIsNotUsed(false);
            DNetDOPolarityTagPointer->setIsNotUsed(false);
            DNetDOStateTagPointer->setIsNotUsed(false);
            DNetDIEnableTagPointer->setIsNotUsed(false);
            DNetDIFuncTagPointer->setIsNotUsed(false);
            DNetDIPolarityTagPointer->setIsNotUsed(false);
            DNetDIStateTagPointer->setIsNotUsed(false);

            PwrConnDI01EnableTagPointer->setIsNotUsed(true);
            PwrConnDI01FuncTagPointer->setIsNotUsed(true);
            PwrConnDI01PolarityTagPointer->setIsNotUsed(true);
            PwrConnDI01StateTagPointer->setIsNotUsed(true);
            PwrConnDI02EnableTagPointer->setIsNotUsed(true);
            PwrConnDI02FuncTagPointer->setIsNotUsed(true);
            PwrConnDI02PolarityTagPointer->setIsNotUsed(true);
            PwrConnDI02StateTagPointer->setIsNotUsed(true);
            PwrConnDO01EnableTagPointer->setIsNotUsed(true);
            PwrConnDO01FuncTagPointer->setIsNotUsed(true);
            PwrConnDO01PolarityTagPointer->setIsNotUsed(true);
            PwrConnDO01StateTagPointer->setIsNotUsed(true);
            PwrConnDO02EnableTagPointer->setIsNotUsed(true);
            PwrConnDO02FuncTagPointer->setIsNotUsed(true);
            PwrConnDO02PolarityTagPointer->setIsNotUsed(true);
            PwrConnDO02StateTagPointer->setIsNotUsed(true);
        }
        else
        {
            DNetDOEnableTagPointer->setIsNotUsed(true);
            DNetDOFuncTagPointer->setIsNotUsed(true);
            DNetDOPolarityTagPointer->setIsNotUsed(true);
            DNetDOStateTagPointer->setIsNotUsed(true);
            DNetDIEnableTagPointer->setIsNotUsed(true);
            DNetDIFuncTagPointer->setIsNotUsed(true);
            DNetDIPolarityTagPointer->setIsNotUsed(true);
            DNetDIStateTagPointer->setIsNotUsed(true);

            PwrConnDI01EnableTagPointer->setIsNotUsed(false);
            PwrConnDI01FuncTagPointer->setIsNotUsed(false);
            PwrConnDI01PolarityTagPointer->setIsNotUsed(false);
            PwrConnDI01StateTagPointer->setIsNotUsed(false);
            PwrConnDI02EnableTagPointer->setIsNotUsed(false);
            PwrConnDI02FuncTagPointer->setIsNotUsed(false);
            PwrConnDI02PolarityTagPointer->setIsNotUsed(false);
            PwrConnDI02StateTagPointer->setIsNotUsed(false);
            PwrConnDO01EnableTagPointer->setIsNotUsed(false);
            PwrConnDO01FuncTagPointer->setIsNotUsed(false);
            PwrConnDO01PolarityTagPointer->setIsNotUsed(false);
            PwrConnDO01StateTagPointer->setIsNotUsed(false);
            PwrConnDO02EnableTagPointer->setIsNotUsed(false);
            PwrConnDO02FuncTagPointer->setIsNotUsed(false);
            PwrConnDO02PolarityTagPointer->setIsNotUsed(false);
            PwrConnDO02StateTagPointer->setIsNotUsed(false);
        }
    }
};
#endif // VERSIONCHECKER_H
