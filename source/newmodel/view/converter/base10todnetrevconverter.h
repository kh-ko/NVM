#ifndef BASE1_TODNETREVCONVERTER_H
#define BASE1_TODNETREVCONVERTER_H

#include <QDebug>

#include "source/newmodel/view/converter/tagvalueconverter.h"
#include "source/newmodel/view/tag/tagmodel.h"

class Base10ToDNetRevConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static Base10ToDNetRevConverter * getInstance()
    {
        static Base10ToDNetRevConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new Base10ToDNetRevConverter();
        }

        return mpSelf;
    }

    explicit Base10ToDNetRevConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        Name = "Base10ToDNetRevConverter";
    }

    void convertToTagValue(QList<TagModel *> * pTagList, QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        bool ok;
        int revValue;

        if(pTagList->size() != 1)
            return;

        revValue = inValue.toInt(&ok, 10);

        if(ok)
        {
            pTagList->at(0)->setMajRev(revValue / 0x100);
            pTagList->at(0)->setMinRev(revValue % 0x100);
        }
        else
        {
            pTagList->at(0)->setMajRev(0);
            pTagList->at(0)->setMinRev(0);
        }
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QList<TagModel *> * pTagList, double gain) override
    {
        Q_UNUSED(gain)

        if(pTagList->size() != 1)
            return "";

        if(pTagList->at(0)->IsEdit == false)
        {
            return QString::number((pTagList->at(0)->getMajRev() * 0x100) + (pTagList->at(0)->getMinRev()));
        }
        else
        {
            return QString::number((pTagList->at(0)->getWriteMajRev() * 0x100) + (pTagList->at(0)->getWriteMinRev()));
        }
    }
};
#endif // BASE1_TODNETREVCONVERTER_H
