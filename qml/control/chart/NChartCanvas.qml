import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import NChartCanvasModel 1.0

Canvas {
    id : canvas

    property var lineColor
    property var lineWidth
    property var isDashLine : false

    property real startX    : 0
    property real rangeX    : 0
    property real startY    : 0
    property real rangeY    : 0

    property var debugId    : 0

    x : gModel.mCanvasX;
    clip: true

    renderStrategy : Canvas.Immediate
    renderTarget : Canvas.FramebufferObject

    NChartCanvasModel{
        id :gModel

        // * note : need recalcurate
        mWidth       : canvas.width
        mHeight      : canvas.height
        mStartYValue : canvas.startY
        mRangeYValue : canvas.rangeY

        // * note :  data is changed
        mStartXValue : canvas.startX
        mRangeXValue : canvas.rangeX
    }

    Timer{
        id : timer
        interval: 100; running: true; repeat: true
        onTriggered:
        {
            if(canvas.available === false)
                return;

            canvas.requestPaint();
        }
    }

    onPaint :
    {
        var drawCnt = 0;

        if(gModel.onCommandGetPointCount() === 0)
        {
            paintClear();
            return;
        }

        while(gModel.mReadIdx < gModel.onCommandGetPointCount() && drawCnt < 100)
        {
            drawCnt++;

            if(gModel.mReadIdx == 0)
            {
                paintClear();
            }

            paintDrawLine();
        }
    }

    function clear()
    {
        gModel.onCommandClear()
    }

    function drawLine(x1,y1,x2,y2)
    {
        gModel.onCommandAddLine(x1,y1,x2,y2)
    }

    function paintClear()
    {
        var ctx = canvas.getContext("2d")

        ctx.reset();
    }

    function paintDrawLine()
    {
        var ctx = canvas.getContext("2d")

        /*
        ctx.beginPath();
        ctx.lineWidth = canvas.lineWidth
        ctx.strokeStyle = canvas.lineColor //"#0085FF"
        if(canvas.isDashLine)
        {
            ctx.setLineDash([2,2]);
        }

        ctx.fillStyle = "#00000000"
        ctx.lineCap = "round"
        */

        var xPosition
        var yPosition

        if(gModel.mReadIdx % 1000 === 0)
        {
            ctx.beginPath();
            ctx.lineWidth = canvas.lineWidth
            ctx.strokeStyle = canvas.lineColor //"#0085FF"
            if(canvas.isDashLine)
            {
                ctx.setLineDash([2,2]);
            }

            ctx.fillStyle = "#00000000"
            ctx.lineCap = "round"
        }

        if(gModel.mReadIdx == 0)
        {
            xPosition = gModel.onCommandGetXPos(gModel.mReadIdx);
            yPosition = gModel.onCommandPopYPos();

            ctx.moveTo(xPosition,yPosition);
        }
        else
        {
            if(gModel.mReadIdx % 1000 === 0)
            {
              xPosition = gModel.onCommandGetXPos(gModel.mReadIdx - 1);
              yPosition = gModel.onCommandGetYPos(gModel.mReadIdx - 1);

              ctx.moveTo(xPosition,yPosition);
            }

            xPosition = gModel.onCommandGetXPos(gModel.mReadIdx);
            yPosition = gModel.onCommandPopYPos();

            ctx.lineTo(xPosition,yPosition);
            ctx.stroke();
        }
    }
}
