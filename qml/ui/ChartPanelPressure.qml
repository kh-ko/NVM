import QtQuick 2.0
import "../control/."
import "../control/chart/."
import ValveEnumDef 1.0
import UnitUtil 1.0
import MathUtil 1.0
import GlobalUiValue 1.0

Item {
    id : panel

    property var isCurrPressureDraw   : true
    property var isTargetPressureDraw : true
    property var isPause              : false

    property var from                 : 0
    property var to                   : 1000000
    property var stdFullScale         : 1000000
    property var pressureConvertFactor: 1
    property var sensorFullScaleUnit  : ValveEnumDef.PRESSURE_UNIT_MTORR
    property var sensorFullScale      : 1000000
    property var convertedFullScale   : 0
    property var pressureDpUnit       : ValveEnumDef.PRESSURE_UNIT_MTORR
    property var xRange               : 30000
    property var isLogType            : false
    property var pressureDecades      : 5


    function clearChart()
    {
        currChart.clearCanvas();
        targetChart.clearCanvas();
    }

    function addPoint(msec, currPressure, targetPressure, memory = true)
    {
        if(panel.isPause)
            return;

        var tempPressure = pressureConvertFactor * currPressure//panel.sensorFullScale * (currPressure / panel.stdFullScale)
        currPressure = UnitUtil.convert(panel.sensorFullScaleUnit, tempPressure, panel.pressureDpUnit)

        tempPressure = pressureConvertFactor * targetPressure//panel.sensorFullScale * (targetPressure / panel.stdFullScale)
        targetPressure = UnitUtil.convert(panel.sensorFullScaleUnit, tempPressure, panel.pressureDpUnit)

        if(isLogType)
        {
            currPressure = MathUtil.log10(currPressure)
            targetPressure = MathUtil.log10(targetPressure)
        }

        currChart.addPoint(msec, currPressure)
        targetChart.addPoint(msec, targetPressure)
    }

    onIsPauseChanged: {
        if(panel.isPause)
            return;
    }

    onConvertedFullScaleChanged: {
       // reDrawChart();
    }

    onIsLogTypeChanged: {
       clearChart();
    }

    NChart{
        id : currChart
        anchors.fill : parent

        visible: panel.isCurrPressureDraw

        lineColor: "#24A7FF"
        xRange: panel.xRange
        to    : panel.to
        from  : panel.from


        debugId01 : 11
        debugId02 : 12
    }


    NChart{
        id : targetChart
        anchors.fill: parent

        visible: panel.isTargetPressureDraw

        lineColor: "#24A7CC"
        isDashLine: true
        xRange: panel.xRange
        to    : panel.to
        from  : panel.from

        debugId01 : 13
        debugId02 : 14
    }
}
