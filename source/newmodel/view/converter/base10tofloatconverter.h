#ifndef BASE1_TOFLOATCONVERTER_H
#define BASE1_TOFLOATCONVERTER_H

#include <QtMath>
#include "source/newmodel/view/converter/tagvalueconverter.h"

class Base10ToFloatConverter: public TagValueConverter
{
    Q_OBJECT

public:
    static Base10ToFloatConverter * getInstance()
    {
        static Base10ToFloatConverter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new Base10ToFloatConverter();
        }

        return mpSelf;
    }

    explicit Base10ToFloatConverter(QObject *parent = nullptr):TagValueConverter(parent)
    {

    }

    QString convertToTagValue(QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        bool ok;

        // 1. 입력 문자열을 실수(double)로 변환
        double value = inValue.toDouble(&ok);
        if (ok) {
            // 2. 변환 성공 시: 10으로 나누기
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

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QString inValue, double gain, int length) override
    {
        Q_UNUSED(gain)

        QString result;

        double value = inValue.toDouble() * gain;

        // 정수를 36진수 문자열로 변환 (대문자로 출력)
        result = QString::number(value, 'f', 0);

        return applyLengthConstraint(result, length);
    }
};

#endif // BASE1_TOFLOATCONVERTER_H
