#ifndef HEXTOFLOATGAINCONVERTEH_H
#define HEXTOFLOATGAINCONVERTEH_H

#include "source/service/coreservice.h"
#include "source/newmodel/view/converter/tagvalueconverter.h"

class HexToFloatDivisorConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static HexToFloatDivisorConverter * getInstance()
    {
        static HexToFloatDivisorConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new HexToFloatDivisorConverter();
        }

        return mpSelf;
    }

    explicit HexToFloatDivisorConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "HexToFloatDivisorConverter";
    }

    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        TagModel * pTag = pTagList->at(0);

        bool ok;

        // 1. 입력 문자열을 실수(double)로 변환
        double protocolValue = inValue.toInt(&ok, 16);

        if (ok && protocolValue != 0.0) {
            double result = gain / protocolValue;

            double absResult = qAbs(result);

            int magnitude = qRound(qLn(absResult)/ qLn(10));
            int precision = 6;
            int decimalPlaces = qMax(0, precision - 1 - magnitude);

            QString str = QString::number(result, 'f', decimalPlaces);
            trimeZero(&str); // 기존의 오타(trimeZero) 유지
            pTag->setValue(str);
        }
        else {
            pTag->setValue("");
        }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        if(pTagList->size() != 1)
            return "";

        TagModel * pTag = pTagList->at(0);
        bool ok;
        double tagValue;

        // 편집 중인지에 따라 값 취득
        tagValue = pTag->IsEdit ? pTag->GetWriteValue().toDouble(&ok) : pTag->Value.toDouble(&ok);

        if (ok && tagValue != 0.0) {
            // 요구 공식: { 1 / TagValue * gain } -> 정수 변환
            int result = qRound((1.0 / tagValue) * gain);

            qDebug() << "[" << Q_FUNC_INFO << "]tagValue =" << tagValue << ", Value = " << result;
            return QString::number(result, 16);
        }

        return "0";
    }
};
#endif // HEXTOFLOATGAINCONVERTEH_H
