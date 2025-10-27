#ifndef MATHUTIL_H
#define MATHUTIL_H

#include <QObject>
#include <QDebug>
#include <QtMath>

#define MATHUTIL_LOG10ROUND(x) MathUtil::getInstance()->log10round(x)
#define MATHUTIL_LOG10FLOOR(x) MathUtil::getInstance()->log10floor(x)
#define MATHUTIL_ABS_LOG10FLOOR(x) MathUtil::getInstance()->abslog10Floor(x)
#define MATHUTIL_ABS_LOG10CEIL(x)  MathUtil::getInstance()->abslog10Ceil(x)

class MathUtil
{
public:
    static MathUtil * getInstance()
    {
        static MathUtil *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new MathUtil();
        }

        return mpSelf;
    }

    int log10round(double value)
    {
        if(value == 0 || value < 0)
        {
            value = 0.00000000000001;
        }
        return qRound(qLn(value)/ qLn(10));
    }
    int log10floor(double value)
    {
        if(value == 0 || value < 0)
        {
            value = 0.00000000000001;
        }
        return qFloor(qLn(value)/ qLn(10));
    }

    int abslog10Floor(double value)
    {
        //value = qAbs(value);

        if(value <= 0)
        {
            return 0;
        }

        return qFloor((qLn(value)/ qLn(10)) + 0.000000001);
    }

    int abslog10Ceil(double value)
    {
        //value = qAbs(value);

        if(value <= 0)
        {
            return 0;
        }

        return qCeil((qLn(value)/ qLn(10)) + 0.000000001) ;
    }


    static bool DoubleEqual(QString v1, QString v2){
        bool ret = false;

        double dv1 = v1.toDouble();
        double dv2 = v2.toDouble();

        double min = qMin(dv1,dv2);
        double diff = qAbs(dv1 - dv2);

        min = qAbs(min);

        ret = (diff <= min * 0.000001);

        return ret;
    }


    MathUtil(){}
    ~MathUtil(){}


};
#endif // MATHUTIL_H
