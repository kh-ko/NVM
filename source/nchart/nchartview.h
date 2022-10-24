#ifndef NCHARTVIEW_H
#define NCHARTVIEW_H
#include <QtQuick>
#include "source/nchart/nchartcontrol.h"
#include "source/nchart/nchartpointbuffer.h"
#include "source/service/util/mathutil.h"
#include "source/service/util/unitutil.h"
#include "source/service/util/exceptionutil.h"

class NChartControl;

class NChartView : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QString mYAxis01Title         READ getYAxis01Title         WRITE setYAxis01Title         NOTIFY signalEventChangedYAxis01Title        )
    Q_PROPERTY(double  mYAxis01Min           READ getYAxis01Min           WRITE setYAxis01Min           NOTIFY signalEventChangedYAxis01Min          )
    Q_PROPERTY(double  mYAxis01Max           READ getYAxis01Max           WRITE setYAxis01Max           NOTIFY signalEventChangedYAxis01Max          )
    Q_PROPERTY(int     mYAxis01LogDecades    READ getYAxis01LogDecades    WRITE setYAxis01LogDecades    NOTIFY signalEventChangedYAxis01LogDecades   )
    Q_PROPERTY(double  mYAxis01Factor        READ getYAxis01Factor        WRITE setYAxis01Factor        NOTIFY signalEventChangedYAxis01Factor       )
    Q_PROPERTY(int     mYAxis01Precision     READ getYAxis01Precision     WRITE setYAxis01Precision     NOTIFY signalEventChangedYAxis01Precision    )
    Q_PROPERTY(bool    mYAxis01AutoScale     READ getYAxis01AutoScale     WRITE setYAxis01AutoScale     NOTIFY signalEventChangedYAxis01AutoScale    )
    Q_PROPERTY(bool    mYAxis01Log           READ getYAxis01Log           WRITE setYAxis01Log           NOTIFY signalEventChangedYAxis01Log          )
    Q_PROPERTY(bool    mY01Draw              READ getY01Draw              WRITE setY01Draw              NOTIFY signalEventChangedY01Draw             )
    Q_PROPERTY(bool    mY01DashDraw          READ getY01DashDraw          WRITE setY01DashDraw          NOTIFY signalEventChangedY01DashDraw         )

    Q_PROPERTY(QString mYAxis02Title         READ getYAxis02Title         WRITE setYAxis02Title         NOTIFY signalEventChangedYAxis02Title        )
    Q_PROPERTY(double  mYAxis02Min           READ getYAxis02Min           WRITE setYAxis02Min           NOTIFY signalEventChangedYAxis02Min          )
    Q_PROPERTY(double  mYAxis02Max           READ getYAxis02Max           WRITE setYAxis02Max           NOTIFY signalEventChangedYAxis02Max          )
    Q_PROPERTY(int     mYAxis02LogDecades    READ getYAxis02LogDecades    WRITE setYAxis02LogDecades    NOTIFY signalEventChangedYAxis02LogDecades   )
    Q_PROPERTY(double  mYAxis02Factor        READ getYAxis02Factor        WRITE setYAxis02Factor        NOTIFY signalEventChangedYAxis02Factor       )
    Q_PROPERTY(int     mYAxis02Precision     READ getYAxis02Precision     WRITE setYAxis02Precision     NOTIFY signalEventChangedYAxis02Precision    )
    Q_PROPERTY(bool    mYAxis02AutoScale     READ getYAxis02AutoScale     WRITE setYAxis02AutoScale     NOTIFY signalEventChangedYAxis02AutoScale    )
    Q_PROPERTY(bool    mYAxis02Log           READ getYAxis02Log           WRITE setYAxis02Log           NOTIFY signalEventChangedYAxis02Log          )
    Q_PROPERTY(bool    mY02Draw              READ getY02Draw              WRITE setY02Draw              NOTIFY signalEventChangedY02Draw             )
    Q_PROPERTY(bool    mY02DashDraw          READ getY02DashDraw          WRITE setY02DashDraw          NOTIFY signalEventChangedY02DashDraw         )

    Q_PROPERTY(double  mMiniumScale          READ getMiniumScale          WRITE setMiniumScale          NOTIFY signalEventChangedMiniumScale         )
    Q_PROPERTY(double  mXRange               READ getXRange               WRITE setXRange               NOTIFY signalEventChangedXRange              )

    Q_PROPERTY(bool    mPause                READ getPause                WRITE setPause                NOTIFY signalEventChangedPause               )

    Q_PROPERTY(bool    mDebug                READ getDebug                WRITE setDebug                NOTIFY signalEventChangedDebug               )


public:
    NChartView( QQuickItem* parent = 0 ): QQuickPaintedItem( parent ), m_CustomPlot( nullptr )
    {
        setFlag( QQuickItem::ItemHasContents, true );
        setAcceptedMouseButtons( Qt::AllButtons );

        connect( this, &QQuickPaintedItem::widthChanged, this, &NChartView::updateCustomPlotSize );
        connect( this, &QQuickPaintedItem::heightChanged, this, &NChartView::updateCustomPlotSize );
    }
    virtual ~NChartView()
    {
        delete m_CustomPlot;
        m_CustomPlot = nullptr;
    }

    void paint( QPainter* painter ){
        CHECK_PTR_RETURN(m_CustomPlot);
        QPixmap    picture( boundingRect().size().toSize() );
        NChartPainter qcpPainter( &picture );
        m_CustomPlot->toPainter( &qcpPainter );

        painter->drawPixmap( QPoint(), picture );
    }

public:
    QString mYAxis01Title      = ""   ;
    double  mYAxis01Min        = 0    ;
    double  mYAxis01Max        = 1    ;
    int     mYAxis01LogDecades = 1    ;
    double  mYAxis01Factor     = 1    ;
    int     mYAxis01Precision  = 0    ;
    bool    mYAxis01AutoScale  = true ;
    bool    mYAxis01Log        = false;
    bool    mY01Draw           = true ;
    bool    mY01DashDraw       = true ;
    QString mYAxis02Title      = ""   ;
    double  mYAxis02Min        = 0    ;
    double  mYAxis02Max        = 1    ;
    int     mYAxis02LogDecades = 1    ;
    double  mYAxis02Factor     = 1    ;
    int     mYAxis02Precision  = 0    ;
    bool    mYAxis02AutoScale  = true ;
    bool    mYAxis02Log        = false;
    bool    mY02Draw           = true ;
    bool    mY02DashDraw       = true ;
    double  mMiniumScale        = -1  ;
    double  mXRange            = 30   ;
    bool    mPause             = false;
    bool    mDebug             = false;

    QString getYAxis01Title     (){ return mYAxis01Title     ; }
    double  getYAxis01Min       (){ return mYAxis01Min       ; }
    double  getYAxis01Max       (){ return mYAxis01Max       ; }
    int     getYAxis01LogDecades(){ return mYAxis01LogDecades; }
    double  getYAxis01Factor    (){ return mYAxis01Factor    ; }
    int     getYAxis01Precision (){ return mYAxis01Precision ; }
    bool    getYAxis01AutoScale (){ return mYAxis01AutoScale ; }
    bool    getYAxis01Log       (){ return mYAxis01Log       ; }
    bool    getY01Draw          (){ return mY01Draw          ; }
    bool    getY01DashDraw      (){ return mY01DashDraw      ; }
    QString getYAxis02Title     (){ return mYAxis02Title     ; }
    double  getYAxis02Min       (){ return mYAxis02Min       ; }
    double  getYAxis02Max       (){ return mYAxis02Max       ; }
    int     getYAxis02LogDecades(){ return mYAxis02LogDecades; }
    double  getYAxis02Factor    (){ return mYAxis02Factor    ; }
    int     getYAxis02Precision (){ return mYAxis02Precision ; }
    bool    getYAxis02AutoScale (){ return mYAxis02AutoScale ; }
    bool    getYAxis02Log       (){ return mYAxis02Log       ; }
    bool    getY02Draw          (){ return mY02Draw          ; }
    bool    getY02DashDraw      (){ return mY02DashDraw      ; }
    double  getMiniumScale      (){ return mMiniumScale      ; }
    double  getXRange           (){ return mXRange           ; }
    bool    getPause            (){ return mPause            ; }
    bool    getDebug            (){ return mDebug            ; }

    void setYAxis01Title     (QString value){ if(mYAxis01Title      == value) return; mYAxis01Title      = value; emit signalEventChangedYAxis01Title     (value);}
    void setYAxis01Min       (double  value){ if(mYAxis01Min        == value) return; mYAxis01Min        = value; emit signalEventChangedYAxis01Min       (value);}
    void setYAxis01Max       (double  value){ if(mYAxis01Max        == value) return; mYAxis01Max        = value; emit signalEventChangedYAxis01Max       (value);}
    void setYAxis01LogDecades(int     value){ if(mYAxis01LogDecades == value) return; mYAxis01LogDecades = value; emit signalEventChangedYAxis01LogDecades(value);}
    void setYAxis01Factor    (double  value){ if(mYAxis01Factor     == value) return; mYAxis01Factor     = value; emit signalEventChangedYAxis01Factor    (value); procChangeFac();}
    void setYAxis01Precision (int     value){ if(mYAxis01Precision  == value) return; mYAxis01Precision  = value; emit signalEventChangedYAxis01Precision (value);}
    void setYAxis01AutoScale (bool    value){ if(mYAxis01AutoScale  == value) return; mYAxis01AutoScale  = value; emit signalEventChangedYAxis01AutoScale (value);}
    void setYAxis01Log       (bool    value){ if(mYAxis01Log        == value) return; mYAxis01Log        = value; emit signalEventChangedYAxis01Log       (value);}
    void setY01Draw          (bool    value){ if(mY01Draw           == value) return; mY01Draw           = value; emit signalEventChangedY01Draw          (value);}
    void setY01DashDraw      (bool    value){ if(mY01DashDraw       == value) return; mY01DashDraw       = value; emit signalEventChangedY01DashDraw      (value);}
    void setYAxis02Title     (QString value){ if(mYAxis02Title      == value) return; mYAxis02Title      = value; emit signalEventChangedYAxis02Title     (value);}
    void setYAxis02Min       (double  value){ if(mYAxis02Min        == value) return; mYAxis02Min        = value; emit signalEventChangedYAxis02Min       (value);}
    void setYAxis02Max       (double  value){ if(mYAxis02Max        == value) return; mYAxis02Max        = value; emit signalEventChangedYAxis02Max       (value);}
    void setYAxis02LogDecades(int     value){ if(mYAxis02LogDecades == value) return; mYAxis02LogDecades = value; emit signalEventChangedYAxis02LogDecades(value);}
    void setYAxis02Factor    (double  value){ if(mYAxis02Factor     == value) return; mYAxis02Factor     = value; emit signalEventChangedYAxis02Factor    (value); procChangeFac();}
    void setYAxis02Precision (int     value){ if(mYAxis02Precision  == value) return; mYAxis02Precision  = value; emit signalEventChangedYAxis02Precision (value);}
    void setYAxis02AutoScale (bool    value){ if(mYAxis02AutoScale  == value) return; mYAxis02AutoScale  = value; emit signalEventChangedYAxis02AutoScale (value);}
    void setYAxis02Log       (bool    value){ if(mYAxis02Log        == value) return; mYAxis02Log        = value; emit signalEventChangedYAxis02Log       (value);}
    void setY02Draw          (bool    value){ if(mY02Draw           == value) return; mY02Draw           = value; emit signalEventChangedY02Draw          (value);}
    void setY02DashDraw      (bool    value){ if(mY02DashDraw       == value) return; mY02DashDraw       = value; emit signalEventChangedY02DashDraw      (value);}
    void setMiniumScale      (double  value){ if(mMiniumScale       == value) return; mMiniumScale       = value; emit signalEventChangedMiniumScale      (value);}
    void setXRange           (double  value){ if(mXRange            == value) return; mXRange            = value; emit signalEventChangedXRange           (value);}
    void setPause            (bool    value){ if(mPause             == value) return; mPause             = value; emit signalEventChangedPause            (value); procPauseData();}
    void setDebug            (bool    value){ if(mDebug             == value) return; mDebug             = value; emit signalEventChangedDebug            (value);}

signals:
    void signalEventChangedYAxis01Title     (QString value);
    void signalEventChangedYAxis01Min       (double  value);
    void signalEventChangedYAxis01Max       (double  value);
    void signalEventChangedYAxis01LogDecades(int     value);
    void signalEventChangedYAxis01Factor    (double  value);
    void signalEventChangedYAxis01Precision (int     value);
    void signalEventChangedYAxis01AutoScale (bool    value);
    void signalEventChangedYAxis01Log       (bool    value);
    void signalEventChangedY01Draw          (bool    value);
    void signalEventChangedY01DashDraw      (bool    value);
    void signalEventChangedYAxis02Title     (QString value);
    void signalEventChangedYAxis02Min       (double  value);
    void signalEventChangedYAxis02Max       (double  value);
    void signalEventChangedYAxis02LogDecades(int     value);
    void signalEventChangedYAxis02Factor    (double  value);
    void signalEventChangedYAxis02Precision (int     value);
    void signalEventChangedYAxis02AutoScale (bool    value);
    void signalEventChangedYAxis02Log       (bool    value);
    void signalEventChangedY02Draw          (bool    value);
    void signalEventChangedY02DashDraw      (bool    value);
    void signalEventChangedMiniumScale      (double  value);
    void signalEventChangedXRange           (double  value);
    void signalEventChangedPause            (bool    value);
    void signalEventChangedDebug            (bool    value);

public slots:
    Q_INVOKABLE QString onCommandLoadFromChart(NChartView * srcChart)
    {
        CHECK_FALSE_RETURN_Y((srcChart != nullptr), "src chart not ready");

        mY01Enable     = srcChart->getY01Enable    ();
        mY01DashEnable = srcChart->getY01DashEnable();
        mY02Enable     = srcChart->getY02Enable    ();
        mY02DashEnable = srcChart->getY02DashEnable();

        onCommandClearGraph();

        setYAxis01Title     (srcChart->getYAxis01Title     ());
        setYAxis01Min       (srcChart->getYAxis01Min       ());
        setYAxis01Max       (srcChart->getYAxis01Max       ());
        setYAxis01Factor    (srcChart->getYAxis01Factor    ());

        setYAxis02Title     (srcChart->getYAxis02Title     ());
        setYAxis02Min       (srcChart->getYAxis02Min       ());
        setYAxis02Max       (srcChart->getYAxis02Max       ());
        setYAxis02Factor    (srcChart->getYAxis02Factor    ());

        setXRange           (srcChart->getXRange           ());

        setYAxis01AutoScale (true );
        setYAxis01Log       (false);
        setY01Draw          (true );
        setY01DashDraw      (true );

        setYAxis02AutoScale (true );
        setYAxis02Log       (false);
        setY02Draw          (true );
        setY02DashDraw      (true );

        NChartPointBuffer * pSrcPointBuff = srcChart->getPointBufferPtr();

        CHECK_FALSE_RETURN_Y((m_CustomPlot != nullptr), "dst chart not ready");

        int srcPointCnt = pSrcPointBuff->count();

        if(getDebug())
            qDebug() << "[khko_debug][onCommandLoadFromChart] srcPointCnt = " << srcPointCnt;

        double startKey = srcPointCnt > 0 ? pSrcPointBuff->at(srcPointCnt - 1).mKey - srcChart->getXRange() : 0;

        for(int i = 0; i <srcPointCnt; i ++)
        {
            NChartPointData point = pSrcPointBuff->at(i);
            onCommandAddPoint(point.mKey - startKey, point.mYAxis01Value, point.mYAxis01DashValue, point.mYAxis02Value, point.mYAxis02DashValue);
        }

        //setYAxis01LogDecades(srcChart->getYAxis01LogDecades());
        //setYAxis01Precision (srcChart->getYAxis01Precision ());

        //setYAxis02LogDecades(srcChart->getYAxis02LogDecades());
        //setYAxis02Precision (srcChart->getYAxis02Precision ());

        //setPause            (srcChart->getPause            ());
        //setDebug            (srcChart->getDebug            ());

        return "";
    }
    Q_INVOKABLE QString onCommandLoadFromFile(QString filePath){ return ""; }

    Q_INVOKABLE void   onCommandClearGraph(){
        mPointBuffer.clear();
        mPauseBuffer.clear();

        CHECK_PTR_RETURN(m_CustomPlot);

        m_CustomPlot->graph(0)->clearData();
        m_CustomPlot->graph(1)->clearData();
        m_CustomPlot->graph(2)->clearData();
        m_CustomPlot->graph(3)->clearData();
    }
    Q_INVOKABLE void   onCommandAddPoint(double key, double y01, double y01Dash, double y02, double y02Dash)
    {
        CHECK_PTR_RETURN(m_CustomPlot);

        NChartPointBuffer * buffer = mPause ? &mPauseBuffer : &mPointBuffer;

        buffer->addPoint(key - mXRange, key, y01, y01Dash, y02, y02Dash);

        CHECK_FALSE_RETURN(!mPause);

        y01     = y01     * mYAxis01Factor;
        y01Dash = y01Dash * mYAxis01Factor;
        y02     = y02     * mYAxis02Factor;
        y02Dash = y02Dash * mYAxis02Factor;

        if(mY01Enable)
        {
            m_CustomPlot->graph(0)->addData(key, y01);
            m_CustomPlot->graph(0)->removeBeforeData(key - mXRange);
        }
        if(mY01DashEnable)
        {
            m_CustomPlot->graph(1)->addData(key, y01Dash);
            m_CustomPlot->graph(1)->removeBeforeData(key - mXRange);
        }
        if(mY02Enable)
        {
            m_CustomPlot->graph(2)->addData(key, y02);
            m_CustomPlot->graph(2)->removeBeforeData(key - mXRange);
        }
        if(mY02DashEnable)
        {
            m_CustomPlot->graph(3)->addData(key, y02Dash);
            m_CustomPlot->graph(3)->removeBeforeData(key - mXRange);
        }
    }
    Q_INVOKABLE void   onCommandInit(QString family, int fontSize, QString strYAxis01Color, QString strYAxis02Color, bool simpleXAxis, bool zoomEnable, bool fmtTime, bool rtUpdate, bool y01Enable, bool y01DashEnable, bool y02Enable, bool y02DashEnable)
    {
        if(getDebug())
            qDebug() << "[khko_debug][onCommandInit]y01Enable = " << y01Enable <<", y01DashEnable = " << y01DashEnable << ", y02Enable = " << y02Enable << ", y02DashEnable" << y02DashEnable;

        QFont labelFont(family, fontSize);
        QFont tickFont(family, fontSize);
        tickFont.setBold(true);
        QColor yAxis01Color(strYAxis01Color);
        QColor yAxis02Color(strYAxis02Color);
        QPen yAxis01LinePen;
        QPen yAxis01GridPen;
        QPen yAxis01DashPen;
        QPen yAxis01TickPen;
        QPen yAxis02LinePen;
        QPen yAxis02GridPen;
        QPen yAxis02DashPen;
        QPen yAxis02TickPen;
        QVector<qreal> pattern = {1,2};

        yAxis01LinePen.setColor(yAxis01Color);
        yAxis01LinePen.setWidth(1); // 2
        yAxis01GridPen.setColor(yAxis01Color);
        yAxis01GridPen.setWidth(1);
        yAxis01DashPen.setStyle(Qt::PenStyle::DotLine);
        yAxis01DashPen.setColor(yAxis01Color);
        yAxis01DashPen.setWidth(1); // 2
        yAxis01TickPen.setColor(yAxis01Color);
        yAxis01TickPen.setWidth(1);

        yAxis02LinePen.setColor(yAxis02Color);
        yAxis02LinePen.setWidth(1); // 2
        yAxis02GridPen.setColor(yAxis02Color);
        yAxis02GridPen.setWidth(1);
        yAxis02DashPen.setStyle(Qt::PenStyle::DotLine);
        yAxis02DashPen.setColor(yAxis02Color);
        yAxis02DashPen.setWidth(1); // 2
        yAxis02TickPen.setColor(yAxis01Color);
        yAxis02TickPen.setWidth(1);

        mY01Enable     = y01Enable    ;
        mY01DashEnable = y01DashEnable;
        mY02Enable     = y02Enable    ;
        mY02DashEnable = y02DashEnable;

        m_CustomPlot = new NChartControl();

        updateCustomPlotSize();

        m_CustomPlot->setBackground(QBrush(QColor("#00000000")));

        if(mY01Enable || mY01DashEnable)
        {
            m_CustomPlot->yAxis->setVisible(true);
            m_CustomPlot->yAxis->setLabelFont(labelFont);
            m_CustomPlot->yAxis->setLabelColor(yAxis01Color);
            m_CustomPlot->yAxis->setLabel( mYAxis01Title );
            m_CustomPlot->yAxis->setTickLabelFont(tickFont);
            m_CustomPlot->yAxis->setTickLabelColor(yAxis01Color);
            m_CustomPlot->yAxis->setBasePen(yAxis01TickPen);
            m_CustomPlot->yAxis->setTickPen(yAxis01TickPen);
            m_CustomPlot->yAxis->setSubTickPen(yAxis01TickPen);
            m_CustomPlot->yAxis->grid()->setVisible(true);

            mMargin.setLeft(10);
        }
        else
        {
            m_CustomPlot->yAxis->setVisible(false);
            mMargin.setLeft(30);
        }

        if(mY02Enable || mY02DashEnable)
        {
            m_CustomPlot->yAxis2->setVisible(true);
            m_CustomPlot->yAxis2->setLabelFont(labelFont);
            m_CustomPlot->yAxis2->setLabelColor(yAxis02Color);
            m_CustomPlot->yAxis2->setLabel( mYAxis02Title );
            m_CustomPlot->yAxis2->setTickLabelFont(tickFont);
            m_CustomPlot->yAxis2->setTickLabelColor(yAxis02Color);
            m_CustomPlot->yAxis2->setBasePen(yAxis02TickPen);
            m_CustomPlot->yAxis2->setTickPen(yAxis02TickPen);
            m_CustomPlot->yAxis2->setSubTickPen(yAxis02TickPen);
            m_CustomPlot->yAxis2->grid()->setVisible(true);

            mMargin.setRight(10);
        }
        else
        {
            m_CustomPlot->yAxis2->setVisible(false);
            mMargin.setRight(30);
        }

        if(fmtTime)
        {
            QSharedPointer<NChartAxisTickerTime> timeTicker(new NChartAxisTickerTime);
            m_CustomPlot->xAxis->setTicker(timeTicker);
        }

        m_CustomPlot->xAxis->setRange(0, mXRange, Qt::AlignRight);
        m_CustomPlot->xAxis->setOnlyVisibleStartEnd(simpleXAxis);
        m_CustomPlot->xAxis->setTickLengthOut(5);
        m_CustomPlot->xAxis->setTickLengthIn(0);
        m_CustomPlot->xAxis->setSubTickLengthOut(3);
        m_CustomPlot->xAxis->setSubTickLengthIn(0);
        m_CustomPlot->xAxis->setVisible(true);
        m_CustomPlot->xAxis->grid()->setVisible(false);
        m_CustomPlot->xAxis->setTickLabelFont(tickFont);

        m_CustomPlot->addGraph(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
        m_CustomPlot->graph(0)->setPen( yAxis01LinePen );
        m_CustomPlot->addGraph(m_CustomPlot->xAxis, m_CustomPlot->yAxis);
        m_CustomPlot->graph(1)->setPen( yAxis01DashPen );
        m_CustomPlot->addGraph(m_CustomPlot->xAxis, m_CustomPlot->yAxis2);
        m_CustomPlot->graph(2)->setPen( yAxis02LinePen );
        m_CustomPlot->addGraph(m_CustomPlot->xAxis, m_CustomPlot->yAxis2);
        m_CustomPlot->graph(3)->setPen( yAxis02DashPen );

        if(zoomEnable)
        {
            m_CustomPlot->setInteractions(NChart::iRangeDrag |NChart::iRangeZoom | NChart::iSelectPlottables);

            QList<NChartAxis*> axes;
            axes.append(m_CustomPlot->yAxis);
            axes.append(m_CustomPlot->yAxis2);
            axes.append(m_CustomPlot->xAxis);
            m_CustomPlot->axisRect()->setRangeDragAxes(axes);
            m_CustomPlot->axisRect()->setRangeZoomAxes(axes);
        }
        else
        {
            m_CustomPlot->setInteractions(NChart::iSelectPlottables);
        }

        connect( m_CustomPlot, SIGNAL( plottableClick( NChartAbstractPlottable*, int, QMouseEvent* ) ), this, SLOT( graphClicked( NChartAbstractPlottable* ) ) );
        connect( m_CustomPlot, &NChartControl::afterReplot, this, &NChartView::onCustomReplot );

        if(rtUpdate)
        {
            mTimer.setInterval(100);
            connect(&mTimer, SIGNAL(timeout()), this, SLOT(onUpdateGraph()));
            mTimer.start();
        }
    }
    Q_INVOKABLE void onCommandUpdate(){ onUpdateGraph();}

public:
    NChartPointBuffer * getPointBufferPtr(){ return &mPointBuffer;}
    NChartControl     * getCustomPlotPtr (){ return m_CustomPlot ;}
    bool getY01Enable    (){ return mY01Enable    ;}
    bool getY01DashEnable(){ return mY01DashEnable;}
    bool getY02Enable    (){ return mY02Enable    ;}
    bool getY02DashEnable(){ return mY02DashEnable;}

protected:
    void routeMouseEvents( QMouseEvent* event )
    {
        CHECK_PTR_RETURN(m_CustomPlot);
        QMouseEvent* newEvent = new QMouseEvent( event->type(), event->localPos(), event->button(), event->buttons(), event->modifiers() );
        QCoreApplication::postEvent( m_CustomPlot, newEvent );

    }
    void routeWheelEvents( QWheelEvent* event )
    {
        CHECK_PTR_RETURN(m_CustomPlot);
        QWheelEvent* newEvent = new QWheelEvent( event->posF(), event->globalPosF(), event->pixelDelta(), event->angleDelta(), event->delta(), event->orientation(),
                                                     event->buttons(), event->modifiers(), event->phase(), event->source(), event->inverted());
        QCoreApplication::postEvent( m_CustomPlot, newEvent );
    }

    virtual void mousePressEvent      ( QMouseEvent* event ){ routeMouseEvents( event ) ;}
    virtual void mouseReleaseEvent    ( QMouseEvent* event ){ routeMouseEvents( event ) ;}
    virtual void mouseMoveEvent       ( QMouseEvent* event ){ routeMouseEvents( event ) ;}
    virtual void mouseDoubleClickEvent( QMouseEvent* event ){ routeMouseEvents( event ) ;}
    virtual void wheelEvent           ( QWheelEvent* event ){ routeWheelEvents( event ) ;}

private:
    QTimer            mTimer;
    int               mUpdateCnt;

    NChartPointBuffer mPointBuffer;
    NChartPointBuffer mPauseBuffer;
    NChartControl*    m_CustomPlot = nullptr;

    bool              mY01Enable = true;
    bool              mY01DashEnable = true;
    bool              mY02Enable = true;
    bool              mY02DashEnable = true;
    QMargins          mMargin = {10,15,10,10};

    void procPauseData()
    {
        if(getPause())
        {
            mPauseBuffer.clear();
        }
        else
        {
            int pauseDataCnt = mPauseBuffer.count();

            for(int i = 0; i < pauseDataCnt; i ++)
            {
                onCommandAddPoint(mPauseBuffer.at(i).mKey, mPauseBuffer.at(i).mYAxis01Value, mPauseBuffer.at(i).mYAxis01DashValue, mPauseBuffer.at(i).mYAxis02Value, mPauseBuffer.at(i).mYAxis02DashValue);
            }
        }
    }

    void procChangeFac()
    {
        int pointCnt;

        CHECK_PTR_RETURN(m_CustomPlot);

        if(getDebug())
            qDebug() << "[khko_debug]["<< Q_FUNC_INFO <<"] mYAxis01Factor = " << mYAxis01Factor << ", mYAxis02Factor = " << mYAxis02Factor;

        m_CustomPlot->graph(0)->clearData();
        m_CustomPlot->graph(1)->clearData();
        m_CustomPlot->graph(2)->clearData();
        m_CustomPlot->graph(3)->clearData();

        pointCnt = mPointBuffer.count();

        for(int i = 0; i < pointCnt; i ++)
        {
            NChartPointData data = mPointBuffer.at(i);

            if(mY01Enable)
                m_CustomPlot->graph(0)->addData(data.mKey, data.mYAxis01Value        * mYAxis01Factor);
            if(mY01DashEnable)
                m_CustomPlot->graph(1)->addData(data.mKey, data.mYAxis01DashValue    * mYAxis01Factor);
            if(mY02Enable)
                m_CustomPlot->graph(2)->addData(data.mKey, data.mYAxis02Value        * mYAxis02Factor);
            if(mY02DashEnable)
                m_CustomPlot->graph(3)->addData(data.mKey, data.mYAxis02DashValue    * mYAxis02Factor);
        }
    }
    bool searchMinMax(NChartGraph * graph, bool minMaxIsSet, double &min, double &max)
    {
        int dataCnt = graph->data()->size();
        double value;

        if(graph->visible() == false)
            return false;

        CHECK_FALSE_RETURN_Y((dataCnt > 0), false);

        if(!minMaxIsSet)
        {
            max = min = graph->data()->at(0)->value;
        }

        for(int i = 0; i < dataCnt; i ++)
        {
            value = graph->data()->at(i)->value;
            if(value > max)
                max = value;
            if(value < min)
                min = value;
        }

        if(getDebug())
            qDebug() << "[khko_debug]["<< Q_FUNC_INFO <<"] min = " << min << ", max = " << max;

        return true;
    }

    void procLogarithmicMinMax(bool autoScale, int logDecades, double max, double foundMin, double foundMax, double &procMin, double &procMax)
    {
        double minLimit = qPow(10,(MATHUTIL_ABS_LOG10FLOOR(max) - logDecades));

        if(!autoScale || foundMax <= minLimit)
        {
            procMax = max;
            procMin = minLimit;
            return;
        }

        procMax = qPow(10,(MATHUTIL_ABS_LOG10CEIL(foundMax)));

        if(foundMin < 0)
            procMin = minLimit;
        else
        {
            procMin = qPow(10,(MATHUTIL_ABS_LOG10FLOOR(foundMin)));
            procMin = qMax(procMin, minLimit);
        }
    }

    void procLinerMinMax(bool autoScale, double min, double max, double foundMin, double foundMax, double &procMin, double &procMax)
    {
        double minimumScale = mMiniumScale < 0 ? max / 1000 : mMiniumScale;
        double diff = foundMax - foundMin;// = (foundMax - foundMin) < (max / 1000) ? (max / 1000) : (foundMax - foundMin);
        double centerValue = foundMax - (diff / 2);

        if(!autoScale)
        {
            procMax = max;
            procMin = min;
            return;
        }

        if(diff < minimumScale)
        {
            foundMax = centerValue + (minimumScale / 2);
            foundMin = centerValue - (minimumScale / 2);
        }

        diff = foundMax - foundMin;

        procMax = foundMax + diff * 0.1;
        procMin = foundMin - diff * 0.1;
    }

    void setYAxisRange(int axisIdx, bool drawLine, bool drawDash, bool autoScale, bool logarithmic, int logDecades, double min, double max)
    {
        bool   minMaxIsSet = false;
        double foundMax = max;
        double foundMin = min;
        double procMin;
        double procMax;

        if(drawLine)
            minMaxIsSet = searchMinMax(m_CustomPlot->graph(axisIdx * 2 + 0), minMaxIsSet, foundMin, foundMax);
        if(drawDash)
            minMaxIsSet = searchMinMax(m_CustomPlot->graph(axisIdx * 2 + 1), minMaxIsSet, foundMin, foundMax);

        if(logarithmic)
        {
            procLogarithmicMinMax(autoScale && (drawLine || drawDash), logDecades, max, foundMin, foundMax, procMin, procMax);
        }
        else
        {
            procLinerMinMax(autoScale && (drawLine || drawDash), min, max, foundMin, foundMax, procMin, procMax);
        }

        if(axisIdx == 0 && (mY01Enable || mY01DashEnable))
            m_CustomPlot->yAxis->setRange(procMin, procMax);
        if(axisIdx == 1 && (mY02Enable || mY02DashEnable))
            m_CustomPlot->yAxis2->setRange(procMin, procMax);
    }

private slots:
    void graphClicked( NChartAbstractPlottable* plottable ){ Q_UNUSED(plottable)}
    void onCustomReplot()
    {
        CHECK_PTR_RETURN(m_CustomPlot);
        m_CustomPlot->axisRect()->setMinimumMargins(mMargin);
        update();
    }
    void updateCustomPlotSize()
    {
        CHECK_PTR_RETURN(m_CustomPlot);
        m_CustomPlot->setGeometry( 0, 0, width(), height() );
    }
    void onUpdateGraph()
    {
        CHECK_PTR_RETURN(m_CustomPlot);

        if(getDebug())
            qDebug() << "[khko_debug][onUpdateGraph]";

        mUpdateCnt++;

        m_CustomPlot->graph(0)->setVisible(mY01Draw);
        m_CustomPlot->graph(1)->setVisible(mY01DashDraw);
        m_CustomPlot->graph(2)->setVisible(mY02Draw);
        m_CustomPlot->graph(3)->setVisible(mY02DashDraw);

        // y range
        if((mUpdateCnt % 10 == 1) || mTimer.isActive() == false)
        {
            if(getDebug())
                qDebug() << "[khko_debug][onUpdateGraph] update YAxis, 01Max = " << mYAxis01Max << ", 02Max = " << mYAxis02Max;

            mUpdateCnt = 1;
            setYAxisRange(0, mY01Draw, mY01DashDraw, mYAxis01AutoScale, mYAxis01Log, mYAxis01LogDecades, mYAxis01Min, mYAxis01Max);
            setYAxisRange(1, mY02Draw, mY02DashDraw, mYAxis02AutoScale, mYAxis02Log, mYAxis02LogDecades, mYAxis02Min, mYAxis02Max);

            if(mTimer.isActive())
                return;
        }

        if(getDebug())
            qDebug() << "[khko_debug][onUpdateGraph] proc";

        // precision
        m_CustomPlot->yAxis->setNumberPrecision(mYAxis01Precision);
        m_CustomPlot->yAxis2->setNumberPrecision(mYAxis02Precision);

        // ticker
        if(m_CustomPlot->yAxis->scaleType() == NChartAxis::ScaleType::stLogarithmic && !mYAxis01Log)
        {
            QSharedPointer<NChartAxisTicker> ticker(new NChartAxisTicker);
            m_CustomPlot->yAxis->setScaleType(NChartAxis::ScaleType::stLinear);
            m_CustomPlot->yAxis->setTicker(ticker);
        }
        else if(m_CustomPlot->yAxis->scaleType() == NChartAxis::ScaleType::stLinear && mYAxis01Log)
        {
            QSharedPointer<NChartAxisTickerLog> ticker(new NChartAxisTickerLog);
            m_CustomPlot->yAxis->setScaleType(NChartAxis::ScaleType::stLogarithmic);
            m_CustomPlot->yAxis->setTicker(ticker);
        }

        if(m_CustomPlot->yAxis2->scaleType() == NChartAxis::ScaleType::stLogarithmic && !mYAxis02Log)
        {
            QSharedPointer<NChartAxisTicker> ticker(new NChartAxisTicker);
            m_CustomPlot->yAxis2->setScaleType(NChartAxis::ScaleType::stLinear);
            m_CustomPlot->yAxis2->setTicker(ticker);
        }
        else if(m_CustomPlot->yAxis2->scaleType() == NChartAxis::ScaleType::stLinear && mYAxis02Log)
        {
            QSharedPointer<NChartAxisTickerLog> ticker(new NChartAxisTickerLog);
            m_CustomPlot->yAxis2->setScaleType(NChartAxis::ScaleType::stLogarithmic);
            m_CustomPlot->yAxis2->setTicker(ticker);
        }

        // title
        m_CustomPlot->yAxis->setLabel(getYAxis01Title());
        m_CustomPlot->yAxis2->setLabel(getYAxis02Title());

        // x range
        double lastKey = mPointBuffer.count() > 0 ? mPointBuffer.at(mPointBuffer.count() - 1).mKey : 0;

        m_CustomPlot->xAxis->setRange(lastKey, getXRange(), Qt::AlignRight);

        m_CustomPlot->replot();
    }
};
#endif // NCHARTVIEW_H
