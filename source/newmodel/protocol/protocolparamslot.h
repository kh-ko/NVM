#ifndef PROTOCOLPARAMSLOT_H
#define PROTOCOLPARAMSLOT_H

#include <QDebug>

#include "source/newmodel/view/converter/defaultconverter.h"
#include "source/newmodel/view/converter/base10tohexconverter.h"
#include "source/newmodel/view/converter/base10todnetrevconverter.h"
#include "source/newmodel/view/converter/hextobase10converter.h"
#include "source/newmodel/view/converter/userpositionconverter.h"
#include "source/newmodel/view/converter/positionconverter.h"
#include "source/newmodel/view/converter/base10tofloatgainconverter.h"
#include "source/newmodel/view/converter/base36tobase10converter.h"
#include "source/newmodel/view/converter/hextobase36converter.h"
#include "source/newmodel/view/converter/fhextofloatconverter.h"
#include "source/newmodel/view/tag/tagmodel.h"

class ProtocolParamSlot : public QObject{
    Q_OBJECT

public:
    static int TypeString  (){ return 0; }
    static int TypeBase10  (){ return 1; }
    static int TypeBase16  (){ return 2; }
    static int TypeBase36  (){ return 3; }
    static int TypeFloat   (){ return 4; }
    static int TypeBitmap  (){ return 5; }
    static int TypeUserPosi(){ return 6; }
    static int TypeBaseFHex(){ return 7; }

    QString Name = "Unknown";
    QString AccType = "Read";
    int Offset;
    int Length;
    int DataType;
    double Gain = 1;
    QString ProtocolValue   = "" ;

    TagValueConverter * ConverterPointer = nullptr;

    QList<TagModel *> TagList;

    explicit ProtocolParamSlot(QObject *parent = nullptr): QObject(parent){}
    ~ProtocolParamSlot(){}

    explicit ProtocolParamSlot(QString name, QString accType, int offset, int length, int dataType, double gain, QObject * parent): QObject(parent)
    {
        Name = name;
        AccType = accType;
        Offset = offset;
        Length = length;
        DataType = dataType;
        Gain = gain;

        SetConverter(DefaultConverter::getInstance());
    }

    void ClearTagList()
    {
        TagList.clear();
    }

    void SetTag(TagModel * pTag)
    {
        if(pTag == nullptr)
            return;

        TagList.append(pTag);

        pTag->SetProtocol(AccType, parent());

        TagValueConverter * pConverter = GetMatchConverter(pTag);

        if(pConverter != ConverterPointer)
        {
            SetConverter(pConverter);
        }

        return;
    }

    void SetConverter(TagValueConverter * pConverter)
    {
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

    // khko todo :  pTag 의 데이터 타입과 자신의 데이터 타입에 따라서 올바른 값 변환 컨버트를 반환한다.
    TagValueConverter * GetMatchConverter(TagModel * pTag)
    {
        if(DataType == TypeString())
        {
        }
        else if(DataType == TypeBaseFHex())
        {
            if(pTag->ValueType == TagModel::TypeFloat())
            {
                return FHexToFloatConverter::getInstance();
            }
        }
        else if(DataType == TypeBase16())
        {
            if(pTag->ValueType == TagModel::TypeBase10() || pTag->ValueType == TagModel::TypeEnum() || pTag->ValueType == TagModel::TypeBitmap())
            {
                return HexToBase10Converter::getInstance();
            }
            else if(pTag->ValueType == TagModel::TypeBase36())
            {
                return HexToBase36Converter::getInstance();
            }
        }
        else if(DataType == TypeBase10())
        {
            if(pTag->ValueType == TagModel::TypeBase16())
            {
                return Base10ToHexConverter::getInstance();
            }
            else if(pTag->ValueType == TagModel::TypeDNetRevision())
            {
                return Base10ToDNetRevConverter::getInstance();
            }
            else if(pTag->ValueType == TagModel::TypePosi())
            {
                return PositionConverter::getInstance();
            }
            else if(pTag->ValueType == TagModel::TypeFloatGain())
            {
                return Base10ToFloatGainConverter::getInstance();
            }
        }
        else if(DataType == TypeUserPosi())
        {
            if(pTag->ValueType == TagModel::TypePosi())
            {
                return UserPositionConverter::getInstance();
            }
        }
        else if(DataType == TypeBase36())
        {
            if(pTag->ValueType == TagModel::TypeBase10() || pTag->ValueType == TagModel::TypeEnum() || pTag->ValueType == TagModel::TypeEnumSelect())
            {
                return Base36ToBase10Converter::getInstance();
            }
        }
        return DefaultConverter::getInstance();
    }

    void SetProtocolResponseData(QString resp)
    {
        if(Length < 0)
        {
            ProtocolValue = resp.mid(Offset);
        }
        else
        {
            if(resp.length() < Offset + 1)
            {
                qDebug() << "[" << Q_FUNC_INFO << "]Name = " << Name << ", data = " << resp;
                return;
            }
            ProtocolValue = resp.mid(Offset, Length);
        }

        ConverterPointer->convertToTagValue(&TagList, ProtocolValue, Gain);
    }

    QString MakeProtoWriteValue()
    {
        if(DataType != TypeString())
        {
            return applyNumberLengthConstraint(ConverterPointer->convertToProtocolValue(&TagList, Gain), Length);
        }

        return ConverterPointer->convertToProtocolValue(&TagList, Gain);
    }

    void SetIsSupport(bool value)
    {
        foreach(TagModel * pTag, TagList)
        {
            pTag->setIsSupport(value);
        }
    }

public slots:
    void onValueChanged()
    {
        if(AccType == "Write")
            return;

        ConverterPointer->convertToTagValue(&TagList, ProtocolValue, Gain);
    }

private:
    QString applyNumberLengthConstraint(QString result, int length)
    {
        if (length == -1) {
            return result;
        }

        if(result.startsWith("-"))
        {
            QString numberPart = result.mid(1);

            // 2. 부호('-')가 1자리를 차지하므로, 숫자가 사용할 수 있는 길이는 (length - 1)
            int digitsLength = length - 1;

            // 방어 코드: length가 1보다 작아 숫자를 표시할 공간이 없는 경우 0으로 처리
            if (digitsLength < 0) digitsLength = 0;

            if (numberPart.length() > digitsLength) {
                // 숫자 부분이 너무 길면 뒤에서부터 자르고 앞에 '-' 붙임
                // 예: "-12345", length=4 -> digitsLength=3 -> "-345"
                return "-" + numberPart.right(digitsLength);
            } else {
                // 숫자 부분이 짧으면 '0'을 채우고 앞에 '-' 붙임
                // 예: "-5", length=4 -> digitsLength=3 -> "-005"
                return "-" + numberPart.rightJustified(digitsLength, '0');
            }
        }
        else
        {
            if (result.length() > length) {
                // 결과가 length보다 길면 앞에서부터 자름 (오른쪽에서 length만큼 남김)
                // 예: "12345", length=3 -> "345"
                return result.right(length);
            } else {
                // 결과가 length보다 짧으면 앞에 '0'을 채움
                // 예: "12", length=4 -> "0012"
                return result.rightJustified(length, '0');
            }
        }
    }
};
#endif // PROTOCOLPARAMSLOT_H
