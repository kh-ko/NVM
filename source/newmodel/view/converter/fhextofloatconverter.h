#ifndef FHEXTOFLOATCONVERTER_H
#define FHEXTOFLOATCONVERTER_H

#include <cstring>

#include "source/service/coreservice.h"
#include "source/newmodel/view/converter/tagvalueconverter.h"

class FHexToFloatConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static FHexToFloatConverter * getInstance()
    {
        static FHexToFloatConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new FHexToFloatConverter();
        }

        return mpSelf;
    }

    explicit FHexToFloatConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "FHexToFloatConverter";
    }

    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        TagModel * pTag = pTagList->at(0);

        bool ok;

        // 1. 입력 문자열을 실수(double)로 변환
        int value = inValue.toInt(&ok, 16);

        if (ok) {
            float temp;
            double result;
            std::memcpy(&temp, &value, sizeof(temp));
            result = static_cast<double>(temp);

            double absResult = qAbs(result);

            if (value == 0.0)
            {
                pTag->setValue("0");
            }

            int magnitude = qFloor(qLn(absResult)/ qLn(10));

            int precision = 6;
            int decimalPlaces = precision - 1 - (int)magnitude;

            QString str;

            if (decimalPlaces > 0) {
                str = QString::number(result, 'f', decimalPlaces);
                trimeZero(&str);

                pTag->setValue(str);
            }
            else {
                pTag->setValue(QString::number(result, 'f', 0));
            }
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

        if (ok) {
            float temp = static_cast<double>(value);
            int result;
            std::memcpy(&result, &temp, sizeof(result));
            return QString::number(result, 16);
        }
        else {
            // 변환 실패 시 기본값 (상황에 따라 "0" 또는 원본 리턴)
            return "0";
        }
    }
};
#endif // FHEXTOFLOATCONVERTER_H
