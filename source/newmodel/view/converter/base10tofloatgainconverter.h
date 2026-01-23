#ifndef BASE1_TOFLOATGAINCONVERTER_H
#define BASE1_TOFLOATGAINCONVERTER_H

#include "source/service/coreservice.h"
#include "source/newmodel/view/converter/tagvalueconverter.h"

class Base10ToFloatGainConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static Base10ToFloatGainConverter * getInstance()
    {
        static Base10ToFloatGainConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new Base10ToFloatGainConverter();
        }

        return mpSelf;
    }

    explicit Base10ToFloatGainConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "Base10ToFloatGainConverter";
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
            double result = (value / gain);
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
        if(pTagList->size() != 1)
            return "";

        TagModel * pTag = pTagList->at(0);
        bool ok;
        double value;

        if(pTagList->at(0)->IsEdit == false)
        {
            value = pTag->Value.toDouble(&ok);
        }
        else
        {
            value = pTag->GetWriteValue().toDouble(&ok);
        }

        if (ok) {
            double result = value * gain;
            return QString::number(result, 'f', 0);

        }
        else {
            // 변환 실패 시 기본값 (상황에 따라 "0" 또는 원본 리턴)
            return "0";
        }
    }
};
#endif // BASE1_TOFLOATGAINCONVERTER_H
