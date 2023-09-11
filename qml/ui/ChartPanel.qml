import QtQuick 2.12
import QtQuick.Controls 2.5
import "../control/."
import "../control/chart/linechart/."
import ValveEnumDef 1.0
import UnitUtil 1.0
import MathUtil 1.0
import StrUtil 1.0
import FontManager 1.0
import NChartView 1.0
import GlobalUiValue 1.0
import GUISetting 1.0

Rectangle {
    id : panel

    property var isConnected : false
    property var isCurrPosDraw
    property var isCurrPressureDraw
    property var isTargetPosDraw
    property var isTargetPressureDraw
    property var isAutoScalePos
    property var isAutoScalePressure
    property var isPause
    property var xRange
    property var isPressureLogType
    property var loadProgress
    property var posResolution
    property var pressureDpUnit
    property var sensorfullScale
    property var sensorFullScaleUnit
    property var stdFullScale
    property var pressureConvertFactor : 1
    property var posConvertFactor : 1
    property var convertedSensorFullScale
    property var convertedCurrPressure
    property var convertedTargetPressure
    property var minPressure
    property var maxPressure
    property var fixedN
    property var autoScaleMinMargin
    property var pressureDecades
    property bool isRecord     : false
    property bool isAutoRecord : false
    property var recordTime
    property var autoRecordTime

    property alias chartView : chart

    signal clickPause()
    signal clickRecord()
    signal clickAutoRecord()
    signal clickAnalyze()

    color: "#FFFFFF"

    function addPoint(msec, currPos, currPressure, targetPos, targetPressure)
    {
        chart.onCommandAddPoint(msec * 0.001, currPos, targetPos, currPressure, targetPressure)
        //chartPos.addPoint(msec, currPos, targetPos)
        //chartPressure.addPoint(msec, currPressure, targetPressure)
    }

    onIsConnectedChanged: {
        if(panel.isConnected)
            chart.onCommandClearGraph()
    }

    onConvertedSensorFullScaleChanged: {
        panel.pressureConvertFactor = panel.convertedSensorFullScale / panel.stdFullScale
    }

    onPosResolutionChanged: {
        panel.posConvertFactor = panel.posResolution / 100000
    }

    Item{
        anchors.fill : parent

        NChartView{
            id : chart

            property string strUnit : panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PA    ? "pa"  :
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_BAR   ? "bar"  :
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MBAR  ? "mbar" :
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_UBAR  ? "ubar" :
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_TORR  ? "Torr" :
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MTORR ? "mTorr":
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_ATM   ? "atm"  :
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSI   ? "psi"  :
                                      panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSF   ? "psf"  : ""

            anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.bottom: controlBox.top; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

            mYAxis01Title      : qsTr("Position")
            mYAxis01Min        : 0
            mYAxis01Max        : panel.posResolution
            mYAxis01LogDecades : 1
            mYAxis01Factor     : panel.posConvertFactor
            mYAxis01Precision  : 8
            mYAxis01AutoScale  : panel.isAutoScalePos
            mYAxis01Log        : false
            mY01Draw           : panel.isCurrPosDraw
            mY01DashDraw       : panel.isTargetPosDraw

            mYAxis02Title      : qsTr("Pressure (") + strUnit + ")"
            //mYAxis02Min        : 0
            //mYAxis02Max        : panel.convertedSensorFullScale
            mYAxis02Min        : panel.minPressure
            mYAxis02Max        : panel.maxPressure
            mYAxis02LogDecades : panel.pressureDecades
            mYAxis02Factor     : panel.pressureConvertFactor
            mYAxis02Precision  : 8
            mYAxis02AutoScale  : panel.isAutoScalePressure
            mYAxis02Log        : panel.isPressureLogType
            mY02Draw           : panel.isCurrPressureDraw
            mY02DashDraw       : panel.isTargetPressureDraw

            mAutoScaleMinMargin: panel.autoScaleMinMargin
            mMiniumScale       : Math.pow(10, (panel.fixedN * -1)) * 10
            mXRange            : panel.xRange * 0.001

            mPause             : panel.isPause

            mDebug             : false

            Component.onCompleted: {

                onCommandInit(FontManager.nanumGothicName, 8, "#24A7FF","#33CC33", true, false, true, true, true, true, true, true );
            }
        }

        Row{
            id : controlBox
            height: GUISetting.chart_ctrlbox_height;
            anchors.horizontalCenter: parent.horizontalCenter; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin
            spacing: GUISetting.margin * 2

            Item{
                height : parent.height; width: recordBtn.width + GUISetting.line_margin + recordTime.width
                NButton{
                    id : recordBtn
                    width: 100 * GUISetting.scale; height : parent.height;
                    text.text : qsTr("Record")
                    onClick: {
                        panel.clickRecord()
                    }

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                        color: "#FF0000"
                        visible: panel.isRecord
                    }
                }

                Rectangle{
                    id : recordTime
                    width: 70 * GUISetting.scale; height : parent.height;
                    anchors.right: parent.right;
                    color : "#E4E4E4"

                    NText{
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                        text : StrUtil.msecToString(panel.recordTime)
                    }
                }
            }

            Item{
                height : parent.height; width: autoRecordBtn.width + GUISetting.line_margin + autoRecordTime.width
                NButton{
                    id : autoRecordBtn
                    width: 100 * GUISetting.scale; height : parent.height;
                    text.text : qsTr("Auto Record")
                    onClick: {
                        panel.clickAutoRecord()
                    }

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                        color: "#FF0000"
                        visible: panel.isAutoRecord
                    }
                }

                Rectangle{
                    id : autoRecordTime
                    width: 70 * GUISetting.scale; height : parent.height;
                    anchors.right: parent.right;
                    color : "#E4E4E4"

                    NText{
                        anchors.fill: parent
                        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                        text : StrUtil.msecToString(panel.autoRecordTime)
                    }
                }
            }

            NButton{
                id : pauseBtn
                width: GUISetting.chart_ctrlbtn_width; height : parent.height;
                text.text : qsTr("Pause")
                onClick: {
                    panel.clickPause()
                }

                NCircleIndicator{
                    width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                    color: "#FF0000"
                    visible: panel.isPause
                }
            }

            NButton{
                id : clearBtn
                width: GUISetting.chart_ctrlbtn_width; height : parent.height;
                text.text : qsTr("Clear")
                onClick: {
                    chart.onCommandClearGraph()
                }
            }

            NButton{
                id : analyzeBtn
                width: GUISetting.chart_ctrlbtn_width; height : parent.height;
                text.text : qsTr("Analyze")
                enabled: !GlobalUiValue.disableWinCreateBtn
                onClick: {
                    panel.clickAnalyze()
                }
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
