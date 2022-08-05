#ifndef NCHARTPOINTBUFFER_H
#define NCHARTPOINTBUFFER_H
#include <QObject>

class NChartPointData
{
public:
    double mKey             ;
    double mYAxis01Value    ;
    double mYAxis01DashValue;
    double mYAxis02Value    ;
    double mYAxis02DashValue;

    NChartPointData(){}
    NChartPointData(double key, double yaxis01Value, double yaxis01DashValue, double yaxis02Value, double yaxis02DashValue)
    {
        mKey              = key              ;
        mYAxis01Value     = yaxis01Value    ;
        mYAxis01DashValue = yaxis01DashValue;
        mYAxis02Value     = yaxis02Value    ;
        mYAxis02DashValue = yaxis02DashValue;
    }
    NChartPointData(const NChartPointData& copy) :
        mKey             (copy.mKey             ),
        mYAxis01Value    (copy.mYAxis01Value    ),
        mYAxis01DashValue(copy.mYAxis01DashValue),
        mYAxis02Value    (copy.mYAxis02Value    ),
        mYAxis02DashValue(copy.mYAxis02DashValue){}

    ~NChartPointData(){}

    NChartPointData& operator=(const NChartPointData& other)
    {
        mKey              = other.mKey             ;
        mYAxis01Value     = other.mYAxis01Value    ;
        mYAxis01DashValue = other.mYAxis01DashValue;
        mYAxis02Value     = other.mYAxis02Value    ;
        mYAxis02DashValue = other.mYAxis02DashValue;

        return *this;
    }
};
Q_DECLARE_METATYPE(NChartPointData);

#define NCHART_POINT_BUFF_LEN 30000
class NChartPointBuffer
{
public:
    int          mBegin = 0;
    int          mEnd   = 0;
    NChartPointData mBuffer[NCHART_POINT_BUFF_LEN];

    NChartPointBuffer(){}
    ~NChartPointBuffer(){}

    void addPoint(double beginKey, double addKey, double yaxis01Value, double yaxis01DashValue, double yaxis02Value, double yaxis02DashValue)
    {
        for(int i = mBegin; i != mEnd; i = (i + 1) % NCHART_POINT_BUFF_LEN)
        {
            if(beginKey > mBuffer[i].mKey)
            {
                mBegin = (mBegin + 1) % NCHART_POINT_BUFF_LEN;
            }
            else
                break;
        }

        mBuffer[mEnd].mKey              = addKey;
        mBuffer[mEnd].mYAxis01Value     = yaxis01Value;
        mBuffer[mEnd].mYAxis01DashValue = yaxis01DashValue;
        mBuffer[mEnd].mYAxis02Value     = yaxis02Value;
        mBuffer[mEnd].mYAxis02DashValue = yaxis02DashValue;

        mEnd = (mEnd + 1) % NCHART_POINT_BUFF_LEN;

        if(mBegin == mEnd)
        {
            mBegin = (mBegin + 1) % NCHART_POINT_BUFF_LEN;
        }
    }

    void clear()
    {
        mBegin = 0;
        mEnd   = 0;
    }

    int count()
    {
        if(mBegin <= mEnd)
            return mEnd - mBegin;
        else
            return (NCHART_POINT_BUFF_LEN - mBegin) + mEnd;
    }

    NChartPointData at(int idx)
    {
        idx = mBegin + idx;
        return mBuffer[idx % NCHART_POINT_BUFF_LEN];
    }
};
#endif // NCHARTPOINTBUFFER_H
