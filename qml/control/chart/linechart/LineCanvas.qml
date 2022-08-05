import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import NChartModel 1.0

Canvas {
    id : canvas

    property var lineColor
    property var lineWidth
    property var isDashLine : false

    property var startX : -1
    property var xRange : 100
    property var from   : 0
    property var to     : 100

    property var isClear : true

    property var debugId : 0
    //property var isReqPaint: false;
    property var isPainted : true

    x : 0;

    renderStrategy : Canvas.Threaded
    renderTarget : Canvas.Image

    NChartModel{
        id :gModel
    }

    Timer{
        id : timer
        interval: 100; running: true; repeat: true
        onTriggered:
        {
            if(canvas.available === false)
                return;

            if(gModel.mReadIdx < gModel.onCommandGetPointCount() && isPainted)
                canvas.requestPaint();
            /*
            if(paintModel.count > 0 && isPainted)
            {
                canvas.requestPaint();
            }
            */
        }
    }

    onPainted :
    {
        canvas.isPainted = true
    }

    onPaint :
    {
        var paintIdx

        if(paintModel.count < 1)
            return;

        for(paintIdx = 0; paintIdx < paintModel.count && paintIdx < 1000; paintIdx++)
        {
            var paintValue = paintModel.get(paintIdx);
            if(paintValue.isClear)
            {
                if(paintClear())
                    canvas.isPainted = false;
            }
            else
            {
                if(paintDrawLine(paintValue.x1, paintValue.y1, paintValue.x2, paintValue.y2))
                    canvas.isPainted = false;
            }
        }

        paintModel.remove(0,paintIdx)
    }

    function clear()
    {
        startX = -1;
        //isReqPaint = true;
        paintModel.append({"isClear":true,"x1":0,"y1":0,"x2":0,"y2":0})
    }

    function drawLine(x1,y1,x2,y2)
    {
        //isReqPaint = true;
        paintModel.append({"isClear":false,"x1":x1,"y1":y1,"x2":x2,"y2":y2})
    }

    function paintClear()
    {
        isClear = true;

        if(canvas.available === false)
            return false;

        var ctx = canvas.getContext("2d")

        ctx.reset();
        ctx.lineWidth = canvas.lineWidth
        ctx.strokeStyle = canvas.lineColor //"#0085FF"
        if(canvas.isDashLine)
        {
            ctx.setLineDash([2,2]);
        }

        ctx.fillStyle = "#00000000"
        ctx.lineCap = "round"

        return true
    }

    function paintDrawLine(x1,y1,x2,y2)
    {
        if(canvas.available === false || startX == -1 )
        {
            return false;
        }

        var yRange = to - from;


        if(xRange === 0 || yRange === 0)
        {
            x = 0;
            return false;
        }

        x = -1 * (width * ((x2 - (startX + xRange)) / xRange)) ;

        if(((startX + xRange) < x1) || (startX > x2))
        {
            return false;
        }

        var ctx = canvas.getContext("2d")
        var xPosition
        var yPosition

        if(isClear)
        {
            xPosition = (canvas.width * ((x1 - startX) / xRange))
            yPosition = canvas.height - (canvas.height * ((y1 - from) / (yRange)))

            ctx.moveTo(xPosition,yPosition);
        }
        xPosition = (canvas.width * ((x2 - startX) / xRange))
        yPosition = canvas.height - (canvas.height * ((y2 - from) / (yRange)))

        ctx.lineTo(xPosition,yPosition);

        ctx.stroke();

        isClear = false;

        return true
    }

    //ListModel{
    //    id : paintModel
    //}
}
