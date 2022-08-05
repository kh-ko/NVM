#ifndef NCHARTCANVASMODEL_H
#define NCHARTCANVASMODEL_H

#include <QObject>
#include <QtMath>

class NChartCanvasModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double mCanvasX      READ getCanvasX       WRITE setCanvasX       NOTIFY signalEventChangedCanvasX      )
    Q_PROPERTY(double mWidth        READ getWidth         WRITE setWidth         NOTIFY signalEventChangedWidth        )
    Q_PROPERTY(double mHeight       READ getHeight        WRITE setHeight        NOTIFY signalEventChangedHeight       )
  //Q_PROPERTY(bool   mIsLogScale   READ getIsLogScale    WRITE setIsLogScale    NOTIFY signalEventChangedIsLogScale   )
    Q_PROPERTY(double mStartXValue  READ getStartXValue   WRITE setStartXValue   NOTIFY signalEventChangedStartXValue  )
    Q_PROPERTY(double mRangeXValue  READ getRangeXValue   WRITE setRangeXValue   NOTIFY signalEventChangedRangeXValue  )
    Q_PROPERTY(double mStartYValue  READ getStartYValue   WRITE setStartYValue   NOTIFY signalEventChangedStartYValue  )
    Q_PROPERTY(double mRangeYValue  READ getRangeYValue   WRITE setRangeYValue   NOTIFY signalEventChangedRangeYValue  )
    Q_PROPERTY(int    mReadIdx      READ getReadIdx       WRITE setReadIdx       NOTIFY signalEventChangedReadIdx      )

public:
    QList<double> mXValuelist;
    QList<double> mYValuelist;

    double mCanvasX    ;
    double mWidth      ;
    double mHeight     ;

    //bool   mIsLogScale     = false;
    double mStartXValue    = 0;
    double mRangeXValue    = 0;
    double mStartYValue    = 0;
    double mRangeYValue    = 0;
    int    mReadIdx        = 0;

    double getCanvasX    (){ return mCanvasX    ; }
    double getWidth      (){ return mWidth      ; }
    double getHeight     (){ return mHeight     ; }
  //bool   getIsLogScale (){ return mIsLogScale ; }
    double getStartXValue(){ return mStartXValue; }
    double getRangeXValue(){ return mRangeXValue; }
    double getStartYValue(){ return mStartYValue; }
    double getRangeYValue(){ return mRangeYValue; }
    int    getReadIdx    (){ return mReadIdx    ; }

    void   setCanvasX    (double value){ if(mCanvasX     == value)return; mCanvasX     = value; emit signalEventChangedCanvasX    (value);}
    void   setReadIdx    (int    value){ if(mReadIdx     == value)return; mReadIdx     = value; emit signalEventChangedReadIdx    (value);}
    void   setWidth      (double value){ if(mWidth       == value)return; mWidth       = value; emit signalEventChangedWidth      (value); recalculate();}
    void   setHeight     (double value){ if(mHeight      == value)return; mHeight      = value; emit signalEventChangedHeight     (value); recalculate();}
    void   setStartYValue(double value){ if(mStartYValue == value)return; mStartYValue = value; emit signalEventChangedStartYValue(value); recalculate();}
    void   setRangeYValue(double value){ if(mRangeYValue == value)return; mRangeYValue = value; emit signalEventChangedRangeYValue(value); recalculate();}
  //void   setIsLogScale (bool   value){ if(mIsLogScale  == value)return; mIsLogScale  = value; emit signalEventChangedIsLogScale (value);}
    void   setStartXValue(double value){ if(mStartXValue == value)return; mStartXValue = value; emit signalEventChangedStartXValue(value); onCommandClear();}
    void   setRangeXValue(double value){ if(mRangeXValue == value)return; mRangeXValue = value; emit signalEventChangedRangeXValue(value); onCommandClear();}


signals:
    void   signalEventChangedCanvasX    (double value);
    void   signalEventChangedWidth      (double value);
    void   signalEventChangedHeight     (double value);
    void   signalEventChangedIsLogScale (bool   value);
    void   signalEventChangedStartXValue(double value);
    void   signalEventChangedRangeXValue(double value);
    void   signalEventChangedStartYValue(double value);
    void   signalEventChangedRangeYValue(double value);
    void   signalEventChangedReadIdx    (int    value);

public slots:
    Q_INVOKABLE void onCommandAddLine(double x1, double y1, double x2, double y2)
    {
        if(mRangeXValue == 0 || mRangeYValue == 0)
            return;

        if(mRangeXValue != 0)
            setCanvasX( mWidth - (mWidth * ((x2 - mStartXValue) / mRangeXValue)) );
        else
            setCanvasX( mWidth );

        if(((mStartXValue + mRangeXValue) <= x1) || (mStartXValue >= x2))
        {
            return;
        }

        if(mXValuelist.count() == 0)
        {
            mXValuelist.append(x1);
            mYValuelist.append(y1);
        }

        mXValuelist.append(x2);
        mYValuelist.append(y2);
    }

    Q_INVOKABLE void onCommandClear()
    {
        setCanvasX(mWidth);
        //setRangeXValue(0);
        //setRangeYValue(0);
        setReadIdx(0);
        mXValuelist.clear();
        mYValuelist.clear();
    }

    Q_INVOKABLE int onCommandGetPointCount()
    {
        return mXValuelist.count();
    }

    Q_INVOKABLE double onCommandGetXPos(int idx)
    {
        double xValue;

        if(idx >= mXValuelist.count() || mRangeXValue == 0)
            return 0;

        xValue = mXValuelist.at(idx);
        return (mWidth * ((xValue - mStartXValue) / mRangeXValue));
    }

    Q_INVOKABLE double onCommandGetYPos(int idx)
    {
        double yValue;

        if(idx >= mYValuelist.count() || mRangeYValue == 0)
            return 0;

        yValue = mYValuelist.at(idx);
        return mHeight - (mHeight * ((yValue - mStartYValue) / (mRangeYValue)));
    }

    Q_INVOKABLE double onCommandPopYPos()
    {
        double yValue;

        if(mReadIdx >= mYValuelist.count() || mRangeYValue == 0)
            return 0;

        yValue = mYValuelist.at(mReadIdx);

        setReadIdx(mReadIdx + 1);

        return mHeight - (mHeight * ((yValue - mStartYValue) / (mRangeYValue)));
    }

public:
    explicit NChartCanvasModel(QObject *parent = nullptr): QObject(parent)
    {
    }
    ~NChartCanvasModel()
    {
    }

private:
    void recalculate()
    {
        setReadIdx(0);

        if(mXValuelist.count() < 2)
            setCanvasX( mWidth );
        else if(mRangeXValue != 0)
            setCanvasX( mWidth - (mWidth * ((mXValuelist.at(mXValuelist.count()-1) - mStartXValue) / mRangeXValue)) );
        else
            setCanvasX( mWidth );
    }

};
#endif // NCHARTMODEL_H
