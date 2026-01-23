#ifndef BASE1_TOHEXCONVERTER_H
#define BASE1_TOHEXCONVERTER_H

#include <QtMath>
#include "source/newmodel/view/converter/tagvalueconverter.h"

class Base10ToHexConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static Base10ToHexConverter * getInstance()
    {
        static Base10ToHexConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new Base10ToHexConverter();
        }

        return mpSelf;
    }

    explicit Base10ToHexConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "Base10ToHexConverter";
    }
    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        bool ok;

        int result = inValue.toInt(&ok, 10);

        if(ok){pTagList->at(0)->setValue(QString::number(result, 16));}
        else  {pTagList->at(0)->setValue(""                         );}
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
            result = pTagList->at(0)->Value.toInt(&ok, 16);
        }
        else{
            result = pTagList->at(0)->GetWriteValue().toInt(&ok, 16);
        }


        // 2단계: 숫자를 십진수 문자열로 변환
        if(ok){ return QString::number(result); }
        else  { return "";                      }
    }
};

#endif // BASE1_TOHEXCONVERTER_H
