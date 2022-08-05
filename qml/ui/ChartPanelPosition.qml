import QtQuick 2.0
import "../control/."
import "../control/chart/."
import ValveEnumDef 1.0
import GlobalUiValue 1.0

Item {
    id : panel

    readonly property int basePosition : 100000

    property var isCurrPosDraw   : true
    property var isTargetPosDraw : true
    property var from            : 0
    property var to              : basePosition
    property var xRange          : 100000
    property var isPause         : false

    property var startX          : 0
    property var lastX           : 0

    function clearChart()
    {
        startX = 0
        lastX  = 0

        currChart.clearCanvas();
        targetChart.clearCanvas();
    }

    function addPoint(msec, currPos, targetPos, memory = true)
    {
        if(panel.isPause)
            return;

        if(startX == 0)
            startX = msec

        lastX = msec - startX

        currChart.addPoint(msec, currPos)
        targetChart.addPoint(msec, targetPos)
    }

    onIsPauseChanged: {

        if(panel.isPause)
            return;
    }

    NChart{
        id : currChart
        anchors.fill : parent

        visible: panel.isCurrPosDraw

        lineColor: "#33FF33"
        xRange: panel.xRange
        to    : panel.to
        from  : panel.from

        debugId01 : 1
        debugId02 : 2
    }


    NChart{
        id : targetChart
        anchors.fill: parent

        visible: panel.isTargetPosDraw

        lineColor: "#33CC33"
        isDashLine: true
        xRange: panel.xRange
        to    : panel.to
        from  : panel.from

        debugId01 : 3
        debugId02 : 4
    }
}
