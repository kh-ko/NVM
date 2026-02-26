#ifndef FLOATTOBASE1_CONVERTER_H
#define FLOATTOBASE1_CONVERTER_H

#include <cstring>

#include "source/service/coreservice.h"
#include "source/newmodel/view/converter/tagvalueconverter.h"

class FloatToBase10Converter: public TagValueConverter
{
    Q_OBJECT

public:
    static FloatToBase10Converter * getInstance()
    {
        static FloatToBase10Converter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new FloatToBase10Converter();
        }

        return mpSelf;
    }

    explicit FloatToBase10Converter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "FloatToBase10Converter";
    }

    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        TagModel * pTag = pTagList->at(0);

        bool ok;

        // 1. 입력 문자열을 실수(double)로 변환
        double value = inValue.toDouble(&ok);

        if (ok) {
            int result;
            value = value * gain;
            result = static_cast<int>(value);

            pTag->setValue(QString::number(result, 'f', 0));

        }
        else {
            pTag->setValue("");
        }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return "";

        TagModel * pTag = pTagList->at(0);
        bool ok;
        double value;

        if(pTagList->at(0)->IsEdit == false){
            value = pTag->Value.toDouble(&ok);
        }
        else{
            value = pTag->GetWriteValue().toDouble(&ok);
        }

        value = value / gain;

        if (ok) {
            double absResult = qAbs(value);

            if (value == 0.0)
            {
                return "0";
            }

            int magnitude = qFloor(qLn(absResult)/ qLn(10));

            int precision = 6;
            int decimalPlaces = precision - 1 - (int)magnitude;

            QString str;

            if (decimalPlaces > 0) {
                return QString::number(value, 'f', decimalPlaces);
            }
            else {
                return QString::number(value, 'f', 0);
            }
        }
        else {
            // 변환 실패 시 기본값 (상황에 따라 "0" 또는 원본 리턴)
            return "0";
        }
    }
};
#endif // FLOATTOBASE1_CONVERTER_H
