#ifndef POSITIONCONVERTER_H
#define POSITIONCONVERTER_H

#include "source/newmodel/view/converter/tagvalueconverter.h"
#include "source/newmodel/view/globalvariable/globalvariable.h"

class PositionConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static PositionConverter * getInstance()
    {
        static PositionConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new PositionConverter();
        }

        return mpSelf;
    }

    explicit PositionConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {
        pGV = GlobalVariable::getInstance();
        pGV->regPosiResolution(this, SLOT(onValueChanged()));
    }

    QString convertToTagValue(QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        bool ok;

        // 1. 입력 문자열을 실수(double)로 변환
        double value = inValue.toDouble(&ok);
        if (ok) {
            // 2. 변환 성공 시: 포지션 해상도로 다시 변환
            gain = 100000 / pGV->PosiResolution;

            double result = value / gain;

            if (value == 0.0)
            {
                return "0";
            }

            int magnitude = qFloor(qLn(gain)/ qLn(10));

            // 3. 'f' 포맷으로 문자열 변환
            QString str = QString::number(result, 'f', magnitude);

            trimeZero(&str);

            return str;
        }
        else {
            // 3. 변환 실패 시 (숫자가 아닌 경우):
            return "0";
        }
    }

    QString convertToProtocolValue(QString inValue, double gain, int length) override
    {
        Q_UNUSED(gain)

        return applyLengthConstraint(inValue, length);
    }

public slots:
    void onValueChanged()
    {
        emit signalEventValueChanged();
    }

private:
    GlobalVariable * pGV;
};

#endif // POSITIONCONVERTER_H
