#ifndef DNETV1ASSYCONVERTER_H
#define DNETV1ASSYCONVERTER_H

#include <QDebug>
#include <QtMath>
#include "source/newmodel/view/converter/tagvalueconverter.h"


class DNetV1AssyConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static DNetV1AssyConverter * getInstance()
    {
        static DNetV1AssyConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new DNetV1AssyConverter();
        }

        return mpSelf;
    }

    explicit DNetV1AssyConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "DNetV1AssyConverter";
    }
    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() < 1 )
            return;

        bool ok;
        int result = inValue.toInt(&ok, 16);
        int byteSize = 0;

        for(int i = 0; i < pTagList->size() - 1; i ++)
        {
            if(ok){
                pTagList->at(i)->SetProtocolBitmapValue(result);

                if(pTagList->at(i)->Value == "1")
                {
                    byteSize = byteSize + pTagList->at(i)->LengthInfo;
                }
            }
            else  {
                pTagList->at(i)->SetProtocolBitmapValue(0     );
            }
        }

        if((byteSize % 2) != 0)
        {
            pTagList->at(pTagList->size() - 1)->setValue("1");
        }
        else
        {
            pTagList->at(pTagList->size() - 1)->setValue("0");
        }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        qDebug() << "[" << Q_FUNC_INFO << "]" << Name << ", size = " << pTagList->size();

        if(pTagList->size() < 1 )
            return "";

        bool ok = true;
        int result = 0;
        int byteSize = 0;

        for(int i = 0; i < pTagList->size() - 1; i ++)
        {
            //qDebug() << "[" << Q_FUNC_INFO << "]" << pTagList->at(i)->Name << ", Write Value = " << pTagList->at(i)->GetWriteValue();
            if((pTagList->at(i)->IsEdit == false && pTagList->at(i)->Value == "1") || (pTagList->at(i)->IsEdit == true && pTagList->at(i)->GetWriteValue() == "1")){
                byteSize = byteSize + pTagList->at(i)->LengthInfo;
                result = result | ( 0x1 << pTagList->at(i)->BitOffset);
            }
        }

        //qDebug() << "[" << Q_FUNC_INFO << "] byteSize =" << byteSize;

        if((byteSize % 2) != 0)
        {
            result = result | ( 0x1 << pTagList->at(pTagList->size() - 1)->BitOffset);
        }

        //qDebug() << "[" << Q_FUNC_INFO << "] result =" << result;
        // 2단계: 숫자를 십진수 문자열로 변환
        if (ok) {
            return QString::number(result, 16);
        }
        else {
            return "";
        }
    }
};
#endif // DNETV1ASSYCONVERTER_H
