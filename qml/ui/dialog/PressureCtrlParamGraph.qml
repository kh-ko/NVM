import QtQuick 2.0
import "../../control/."
import GUISetting 1.0

Item {
    id: panel
    clip: true

    property var xFrom    : 0
    property var xTo      : 100

    property var yFrom    : 0
    property var yTo      : 100

    function addPoint(x,y)
    {
        graphModel.append({"x":x, "y":y})
    }

    function clear()
    {
        graphModel.clear()
        canvasArea.clearCanvas()
    }

    function drawCanvas()
    {
        canvasArea.clearCanvas()

        if(graphModel.count < 2)
            return;

        var isDrawLastPoint = false
        var y1    = graphModel.get(0).y
        var delta = graphModel.get(1).y - y1
        var x2    = (y1 / delta) * -1

        canvasArea.drawDashLine(0, y1 / 10000, x2, 0)

        for(var pointIdx = 1; pointIdx < graphModel.count; pointIdx++)
        {
            canvasArea.drawLine(pointIdx - 1, graphModel.get(pointIdx-1).x, graphModel.get(pointIdx-1).y / 10000, graphModel.get(pointIdx).x, graphModel.get(pointIdx).y / 10000)

            if((delta * (pointIdx) + y1) !== graphModel.get(pointIdx).y && !isDrawLastPoint)
            {
                drawLastPoint(pointIdx-1, graphModel.get(pointIdx-1).y / 10000)
                isDrawLastPoint = true
            }
        }
    }

    function drawLastPoint(x, y)
    {
        var xPosition
        var yPosition
        var xRange   = panel.xTo - panel.xFrom
        var yRange   = panel.yTo - panel.yFrom

        xPosition = (canvas.width * ((x - panel.xFrom) / xRange))
        yPosition = canvas.height - (canvas.height * ((y - panel.yFrom) / (yRange)))

        lastPointItem.createObject(lastPointView, {"x": xPosition, "y":yPosition})
    }

    function drawGuideLine()
    {
        var xOffset = 0;
        var yOffset = yAxis.height;
        var xRange   = panel.xTo - panel.xFrom
        var yRange   = panel.yTo - panel.yFrom
        var xLineGap = Math.ceil((xRange) / 10)
        var yLineGap = Math.ceil((yRange) / 10)

        for(var i = 0; i < yAxis.children.length; i++)
        {
            yAxis.children[i].destroy();
        }

        for(var j = 0; j < xAxis.children.length; j++)
        {
            xAxis.children[j].destroy();
        }

        for(var xValue = xFrom; xValue < xTo; xValue += xLineGap)
        {
            xOffset = xAxis.width * ((xValue - xFrom) / (xRange))
            xLine.createObject(xAxis, {"x": xOffset, "lineText":xValue})
        }

        if(xOffset !== xAxis.width)
        {
            xLine.createObject(xAxis, {"x": xAxis.width, "lineText":xTo})
        }

        for(var yValue = yFrom; yValue < yTo; yValue += yLineGap)
        {
            yOffset = yAxis.height - (yAxis.height * ((yValue - yFrom) / (yRange)))
            yLine.createObject(yAxis, {"y": yOffset, "lineText":yValue})
        }

        if(yOffset !== 0)
        {
            yLine.createObject(yAxis, {"y": 0, "lineText":yTo})
        }
    }

    function draw(){
        drawGuideLine()
        drawCanvas()
    }

    Component.onCompleted: { draw();}
    onWidthChanged       : { draw();}
    onHeightChanged      : { draw();}
    onXFromChanged       : { draw();}
    onXToChanged         : { draw();}
    onYFromChanged       : { draw();}
    onYToChanged         : { draw();}

    ListModel{
        id : graphModel
    }

    Rectangle{
        id : canvasArea
        anchors.top   : parent.top;    anchors.topMargin   : 10 * GUISetting.scale
        anchors.bottom: parent.bottom; anchors.bottomMargin: 32 * GUISetting.scale
        anchors.left  : parent.left;   anchors.leftMargin  : 60 * GUISetting.scale
        anchors.right : parent.right;  anchors.rightMargin : 50 * GUISetting.scale
        color: "#00000000"
        border.width: 1
        border.color: "#000000"

        function clearCanvas(){

            for(var i = 0; i < lastPointView.children.length; i++)
            {
                lastPointView.children[i].destroy();
            }

            if(canvas.available === false || virtualCanvas.available === false)
                return;

            var ctx = canvas.getContext("2d");
            ctx.reset();
            ctx.lineWidth = 1
            ctx.strokeStyle = "#24A7FF"
            ctx.fillStyle = "#00000000"
            ctx.lineCap = "round"

            //ctx.beginPath()

            canvas.requestPaint();

            ctx = virtualCanvas.getContext("2d");
            ctx.reset();
            ctx.lineWidth = 1
            ctx.strokeStyle = "#33CC33"
            ctx.fillStyle = "#00000000"
            ctx.lineCap = "round"

            ctx.setLineDash([2,2]);
            //ctx.beginPath()

            virtualCanvas.requestPaint();
        }

        function drawLine(idx, x1, y1, x2, y2){

            if(canvas.available === false)
                return;

            var ctx = canvas.getContext("2d")
            var xPosition
            var yPosition
            var xRange   = panel.xTo - panel.xFrom
            var yRange   = panel.yTo - panel.yFrom

            if(idx === 0)
            {
                xPosition = (canvas.width * ((x1 - panel.xFrom) / xRange))
                yPosition = canvas.height - (canvas.height * ((y1 - panel.yFrom) / (yRange)))

                ctx.moveTo(xPosition,yPosition);
            }
            xPosition = (canvas.width * ((x2 - panel.xFrom) / xRange))
            yPosition = canvas.height - (canvas.height * ((y2 - panel.yFrom) / (yRange)))

            ctx.lineTo(xPosition,yPosition);

            ctx.stroke();

            canvas.requestPaint();
        }

        function drawDashLine(x1, y1, x2, y2)
        {
            if(virtualCanvas.available === false)
                return;

            var ctx = virtualCanvas.getContext("2d")

            var xPosition
            var yPosition
            var xRange   = panel.xTo - panel.xFrom
            var yRange   = panel.yTo - panel.yFrom


            xPosition = (virtualCanvas.width * ((x1 - panel.xFrom) / xRange))
            yPosition = virtualCanvas.height - (virtualCanvas.height * ((y1 - panel.yFrom) / (yRange)))

            ctx.moveTo(xPosition,yPosition);

            xPosition = (virtualCanvas.width * ((x2 - panel.xFrom) / xRange))
            yPosition = virtualCanvas.height - (virtualCanvas.height * ((y2 - panel.yFrom) / (yRange)))

            ctx.lineTo(xPosition,yPosition);

            ctx.stroke();

            virtualCanvas.requestPaint();
        }

        Canvas{
            id : canvas
            anchors.fill: parent
            renderTarget : Canvas.FramebufferObject
        }

        Canvas{
            id : virtualCanvas
            anchors.fill: parent
            renderTarget : Canvas.FramebufferObject
        }

        Item{
            id : lastPointView
            anchors.fill: parent
        }
    }

    Item{
        id : yAxisLabelItem
        width: yAxisLabel.height; height: yAxisLabel.height
        anchors.verticalCenter: yAxis.verticalCenter; anchors.left: parent.left
        NText{
            id : yAxisLabel
            text: qsTr("sensor full scale(%)")
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            rotation: -90
        }
    }

    NText{
        id : xAxisLabel
        text: qsTr("open position (%)")
        anchors.bottom: parent.bottom; anchors.horizontalCenter: xAxis.horizontalCenter
    }

    Item{
        id : yAxis
        height: canvasArea.height
        anchors.verticalCenter: canvasArea.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 16 * GUISetting.scale; anchors.right: canvasArea.right; anchors.rightMargin: 0
    }

    Item{
        id : xAxis
        width: canvasArea.width
        anchors.horizontalCenter: canvasArea.horizontalCenter; anchors.bottom: xAxisLabel.top; anchors.bottomMargin: 6 * GUISetting.scale; anchors.top: canvasArea.top; anchors.topMargin: 0
    }

    Component{
        id : xLine

        Item{
            property var lineText

            anchors.bottom: parent.bottom; anchors.top: parent.top
            width: 1

            Rectangle{
                width: 1
                anchors.top: parent.top; anchors.bottom: lineLabel.top; anchors.bottomMargin: 2
                color : "#39000000"
            }

            NText{
                id : lineLabel
                text: lineText
                anchors.bottom: parent.bottom; anchors.horizontalCenter: parent.horizontalCenter
            }
        }
    }

    Component{
        id : yLine

        Item{
            property var lineText
            anchors.left: parent.left; anchors.right: parent.right
            height: 1

            Rectangle{
                height: 1
                anchors.right: parent.right; anchors.left: lineLabel.right; anchors.leftMargin: 2
                color : "#39000000"
            }

            NText{
                id : lineLabel
                width: 40 * GUISetting.scale
                text: lineText
                horizontalAlignment: Text.AlignRight
                anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    Component{
        id : lastPointItem

        Item{
            height: 1; width: 1

            Rectangle{
                id : pointer
                height: 5* GUISetting.scale; width: 5* GUISetting.scale
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                color : "#FF0000"
            }

            NText{
                id : lineLabel
                text: qsTr("Last learn position")
                x : parent.x < (canvas.width/2) ? pointer.x + (10 * GUISetting.scale) : pointer.x - (width + (10 * GUISetting.scale))
                y : parent.y < (canvas.height/2) ? pointer.y + (15 * GUISetting.scale) : pointer.y - (height + (10 * GUISetting.scale))
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
