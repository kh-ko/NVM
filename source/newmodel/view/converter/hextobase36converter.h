#ifndef HEXTOBASE36CONVERTER_H
#define HEXTOBASE36CONVERTER_H

#include <QDebug>
#include <QtMath>
#include "source/newmodel/view/converter/tagvalueconverter.h"


class HexToBase36Converter: public TagValueConverter
{
    Q_OBJECT

public:
    static HexToBase36Converter * getInstance()
    {
        static HexToBase36Converter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new HexToBase36Converter();
        }

        return mpSelf;
    }

    explicit HexToBase36Converter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "HexToBase36Converter";
    }
    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() < 1 )
            return;

        bool ok;
        int result = inValue.toInt(&ok, 16);

        if(ok){ pTagList->at(0)->setValue(QString::number(result, 36)); }
        else  { pTagList->at(0)->setValue("");                          }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() < 1 )
            return "";

        bool ok = true;
        int result = 0;

        if(pTagList->at(0)->IsEdit == false){
            result = pTagList->at(0)->Value.toInt(&ok, 36);
        }
        else{
            result = pTagList->at(0)->GetWriteValue().toInt(&ok, 36);
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
#endif // HEXTOBASE36CONVERTER_H
