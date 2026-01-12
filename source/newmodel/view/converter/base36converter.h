#ifndef BASE36CONVERTER_H
#define BASE36CONVERTER_H
#include "source/newmodel/view/converter/tagvalueconverter.h"

class Base36Converter: public TagValueConverter
{
    Q_OBJECT

public:
    static Base36Converter * getInstance()
    {
        static Base36Converter *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new Base36Converter();
        }

        return mpSelf;
    }

    explicit Base36Converter(QObject *parent = nullptr):TagValueConverter(parent)
    {

    }

    QString convertToTagValue(QString inValue, double gain) override
    {
        Q_UNUSED(gain)

        QString result;

        bool ok;
        // 36진수 문자열을 숫자로 변환 (최대 64비트 정수 지원)
        int value = inValue.toInt(&ok, 36);

        if (!ok){ result = "0"; } // 변환 실패 시 기본값 반환
        else    { result =  QString::number(value); }

        return result;
    }

    // 반올림 되는점 유의하기
    QString convertToProtocolValue(QString inValue, double gain, int length) override
    {
        Q_UNUSED(gain)

        QString result;

        int value = inValue.toInt();

        // 정수를 36진수 문자열로 변환 (대문자로 출력)
        result = QString::number(value, 36).toUpper();

        return applyLengthConstraint(result, length);
    }
};

#endif // BASE36CONVERTER_H
