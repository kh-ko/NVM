#ifndef DEFAULTCONVERTER_H
#define DEFAULTCONVERTER_H

#include "source/newmodel/view/converter/tagvalueconverter.h"
#include "source/newmodel/view/tag/tagmodel.h"

class DefaultConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static DefaultConverter * getInstance()
    {
        static DefaultConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new DefaultConverter();
        }

        return mpSelf;
    }

    explicit DefaultConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "DefaultConverter";
    }

    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return;

        pTagList->at(0)->setValue(inValue);
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return "";

        if(pTagList->at(0)->IsEdit == false){
            return pTagList->at(0)->Value;
        }
        else{
            return pTagList->at(0)->WriteValue;
        }
    }
};

#endif // DEFAULTCONVERTER_H
