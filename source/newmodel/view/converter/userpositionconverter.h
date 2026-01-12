#ifndef USERPOSITIONCONVERTER_H
#define USERPOSITIONCONVERTER_H

#include "source/newmodel/view/converter/tagvalueconverter.h"

class UserPositionConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static UserPositionConverter * getInstance()
    {
        static UserPositionConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new UserPositionConverter();
        }

        return mpSelf;
    }

    explicit UserPositionConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {

    }

    QString convertToTagValue(QString inValue, double gain) override
    {
        Q_UNUSED(gain)
        return inValue;
    }

    QString convertToProtocolValue(QString inValue, double gain, int length) override
    {
        Q_UNUSED(gain)

        return applyLengthConstraint(inValue, length);
    }
};
#endif // USERPOSITIONCONVERTER_H
