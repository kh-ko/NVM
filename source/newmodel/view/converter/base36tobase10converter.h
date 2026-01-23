#ifndef BASE36TOBASE1_CONVERTER_H
#define BASE36TOBASE1_CONVERTER_H

#include <QtMath>
#include "source/newmodel/view/converter/tagvalueconverter.h"


class Base36ToBase10Converter: public TagValueConverter
{
    Q_OBJECT

public:
    static Base36ToBase10Converter * getInstance()
    {
        static Base36ToBase10Converter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new Base36ToBase10Converter();
        }

        return mpSelf;
    }

    explicit Base36ToBase10Converter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "Base36ToBase10Converter";
    }
    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        bool ok;
        int result = inValue.toInt(&ok, 36);

        if(ok){ pTagList->at(0)->setValue(QString::number(result)); }
        else  { pTagList->at(0)->setValue("");                      }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return "";

        bool ok;
        int result;

        if(pTagList->at(0)->IsEdit == false){
            result = pTagList->at(0)->Value.toInt(&ok, 10);
        }
        else{
            result = pTagList->at(0)->GetWriteValue().toInt(&ok, 10);
        }

        // 2단계: 숫자를 십진수 문자열로 변환
        if (ok) {
            return QString::number(result, 36);
        }
        else {
            return "";
        }
    }
};

#endif // BASE36TOBASE1_CONVERTER_H
