#ifndef HEXTOBASE1_CONVERTER_H
#define HEXTOBASE1_CONVERTER_H

#include <QDebug>
#include <QtMath>
#include "source/newmodel/view/converter/tagvalueconverter.h"


class HexToBase10Converter: public TagValueConverter
{
    Q_OBJECT

public:
    static HexToBase10Converter * getInstance()
    {
        static HexToBase10Converter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new HexToBase10Converter();
        }

        return mpSelf;
    }

    explicit HexToBase10Converter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "HexToBase10Converter";
    }
    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() < 1 )
            return;

        bool ok;
        int result = inValue.toInt(&ok, 16);

        if(pTagList->at(0)->ValueType == TagModel::TypeBitmap())
        {
            for(int i = 0; i < pTagList->size(); i ++)
            {
                if(ok){ pTagList->at(i)->SetProtocolBitmapValue(result); }
                else  { pTagList->at(i)->SetProtocolBitmapValue(0     ); }
            }
        }
        else
        {
            if(ok){ pTagList->at(0)->setValue(QString::number(result)); }
            else  { pTagList->at(0)->setValue("");                      }
        }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() < 1 )
            return "";

        bool ok = true;
        int result = 0;

        if(pTagList->at(0)->ValueType == TagModel::TypeBitmap())
        {
            for(int i = 0; i < pTagList->size(); i ++)
            {
                if((pTagList->at(i)->IsEdit == true &&pTagList->at(i)->GetWriteValue() == "1") || (pTagList->at(i)->IsEdit == false &&pTagList->at(i)->Value == "1"))
                {
                    result = result | ( 0x1 << pTagList->at(i)->BitOffset);
                }
            }
        }
        else
        {
            if(pTagList->at(0)->IsEdit == false)
                result = pTagList->at(0)->Value.toInt(&ok, 10);
            else
                result = pTagList->at(0)->GetWriteValue().toInt(&ok, 10);
        }

        // 2단계: 숫자를 십진수 문자열로 변환
        if (ok) {
            return QString::number(result, 16);
        }
        else {
            return "";
        }
    }
};

#endif // HEXTOBASE1_CONVERTER_H
