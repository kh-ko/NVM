import QtQuick 2.12
import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import FontManager 1.0
import "./"
import "../"
import "../../"
//import LineChartData 1.0

Item {
    id : control

    property var   isRightMode      : false

    property var   lineWidth      : 1
    property var   lineColor      : "#000000"
    property var   isDashLine     : false

    property var   from           : 0.0
    property var   to             : 10.0
    property var   xRange         : 30000

    property LineCanvas currCanvas : null
    property LineCanvas preCanvas : null

    property alias debugId01 : canvas01.debugId
    property alias debugId02 : canvas02.debugId

    function addPoint(x, y)
    {
        model.append({"x":x, "y":y})

        while(model.count > 0 && (x - model.get(0).x) > (panel.xRange))
        {
            model.remove(0);
        }

        if(model.count < 2)
            return;

        drawLine(model.get(model.count - 2).x, model.get(model.count - 2).y, model.get(model.count - 1).x, model.get(model.count - 1).y)
    }

    function clearChart()
    {
        model.clear();
        clearCanvas();
    }

    function clearCanvas()
    {
        canvas01.clear()
        canvas02.clear()
    }

    function reDrawCanvas()
    {
        clearCanvas();

        if(model.count < 2)
            return;

        for(var idx = 1; idx < model.count; idx++)
        {
            drawLine(model.get(idx - 1).x, model.get(idx - 1).y, model.get(idx).x, model.get(idx).y)
        }
    }

    function drawLine(x1,y1,x2,y2)
    {
        if(((x2 - x1) >= xRange) || (canvas01.starX === -1 || canvas02.startX === -1))
        {
            clearCanvas();

            canvas01.startX = x2 - xRange
            canvas02.startX = x2
        }

        if((canvas01.startX + xRange) < (x2 - xRange))
        {
            canvas01.clear()
            canvas01.startX = canvas02.startX + xRange
        }
        if((canvas02.startX + xRange) < (x2 - xRange))
        {
            canvas02.clear()
            canvas02.startX = canvas01.startX + xRange
        }

        canvas01.drawLine(x1, y1, x2, y2)
        canvas02.drawLine(x1, y1, x2, y2)
    }

    onWidthChanged    : {
        timer.stop(); timer.start();
    }
    onHeightChanged   : {
        timer.stop(); timer.start();
    }
    onFromChanged     : { reDrawCanvas();}
    onToChanged       : { reDrawCanvas();}
    onXRangeChanged   : { reDrawCanvas();}
    onImplicitHeightChanged: {
    }

    Timer{
            id : timer
            interval: 1000; running: false; repeat: false
            onTriggered:
            {
                reDrawCanvas();
            }
    }

    ListModel{
        id : model
    }


    Item{
        id : canvasViewPort
        anchors.fill: parent

        clip: true

        LineCanvas{
            id : canvas01

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            lineColor : control.lineColor
            lineWidth : control.lineWidth
            isDashLine : control.isDashLine
            xRange : control.xRange
            from   : control.from
            to     : control.to
        }

        LineCanvas{
            id : canvas02

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            lineColor : control.lineColor
            lineWidth : control.lineWidth
            isDashLine : control.isDashLine
            xRange : control.xRange
            from   : control.from
            to     : control.to
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
