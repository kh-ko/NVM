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

    property NChartCanvas currCanvas : null
    property NChartCanvas preCanvas : null

    property bool  isSetLastPos : false
    property real  lastPosX
    property real  lastPosY
    property alias debugId01 : canvas01.debugId
    property alias debugId02 : canvas02.debugId

    function addPoint(x, y)
    {
        if(isSetLastPos === true)
        {
            drawLine(lastPosX, lastPosY, x, y)
        }
        else
        {
            canvas01.startX = x - xRange
            canvas02.startX = x
        }

        isSetLastPos = true;
        lastPosX = x; lastPosY = y;
    }

    function clearCanvas()
    {
        isSetLastPos = false;
        canvas01.clear()
        canvas02.clear()
    }

    function drawLine(x1,y1,x2,y2)
    {
        if((x2 - x1) >= xRange)
        {
            canvas01.startX = x2 - xRange
            canvas02.startX = x2
        }

        if((canvas01.startX + xRange) < (x2 - xRange))
        {
            canvas01.startX = canvas02.startX + xRange
        }
        if((canvas02.startX + xRange) < (x2 - xRange))
        {
            canvas02.startX = canvas01.startX + xRange
        }

        canvas01.drawLine(x1, y1, x2, y2)
        canvas02.drawLine(x1, y1, x2, y2)
    }

    Item{
        id : canvasViewPort
        anchors.fill: parent

        clip: true

        NChartCanvas{
            id : canvas01

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            lineColor  : control.lineColor
            lineWidth  : control.lineWidth
            isDashLine : control.isDashLine

            rangeX   : control.xRange
            startY   : control.from
            rangeY   : control.to - control.from

            debugId  : control.debugId01
        }

        NChartCanvas{
            id : canvas02

            height: parent.height; width: parent.width
            anchors.verticalCenter: parent.verticalCenter

            lineColor  : control.lineColor
            lineWidth  : control.lineWidth
            isDashLine : control.isDashLine

            rangeX   : control.xRange
            startY   : control.from
            rangeY   : control.to - control.from

            debugId  : control.debugId01
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
