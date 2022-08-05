import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import NChartView 1.0
import FontManager 1.0
import ValveEnumDef 1.0
import ValvePowerFailStatusDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{

    id : dialog

    property var body : null

    titleText   : qsTr("Power fail status")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : false

    bodyWidth : 700 * GUISetting.scale

    function commit()
    {
        dlgModel.onCommandEnablePFO()
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 700 * GUISetting.scale
    }

    ValvePowerFailStatusDlgModel{
        id : dlgModel

        onSignalEventAddedVoltagePoint: {

            var sec = msec / 1000
            var volt = mvolt / 1000

            body.voltChart.onCommandAddPoint(sec,volt, 0, 0, 0)
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias  voltChart : _voltChart
            property real   guiScale  : GUISetting.scale

            height: (GUISetting.line_margin + statusItem.height) + (GUISetting.line_margin + chartItem.height) + (GUISetting.line_margin + btnBox.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = 700 * GUISetting.scale
            }

            Rectangle{
                id : statusItem

                height: (GUISetting.margin + statusTitle.height) + (GUISetting.margin + statusBox.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : statusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("power failure status")
                }

                Item{
                    id : statusBox
                    height: 24 * GUISetting.scale;
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    NText{
                        id : statusLabel
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignLeft
                        text : qsTr("status :")
                        color: "#000000"
                    }

                    NText{
                        anchors.left: statusLabel.right; anchors.leftMargin: 5 * GUISetting.scale; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignLeft
                        text : !dlgModel.mEnablePFO ? qsTr("disabled") : qsTr("enabled")
                        color: !dlgModel.mEnablePFO ? "#FF0000" : "#000000"
                    }


                    NText{
                        id : performedCycleLabel
                        anchors.left: parent.left; anchors.leftMargin: 180 * GUISetting.scale; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignLeft
                        text : qsTr("performed cycles :")
                        color: "#000000"
                    }

                    NText{
                        anchors.left: performedCycleLabel.right; anchors.leftMargin: 5 * GUISetting.scale; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignLeft
                        text : dlgModel.mPerformedCycles
                        color: dlgModel.mErrPerformedCycles ? "#FF0000" : "#000000"
                    }

                }
            }

            Rectangle{
                id : chartItem

                height: (GUISetting.margin + chartTitle.height) + (GUISetting.margin + actualVoltBox.height) + (GUISetting.margin + _voltChart.height) + (GUISetting.margin + chartBtnBox.height) + GUISetting.margin
                anchors.top: statusItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : chartTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("battery voltage chart")
                }

                Item{
                    id : actualVoltBox
                    height: 24 * GUISetting.scale;
                    anchors.top: chartTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    NText{
                        id : actualVoltLabel
                        anchors.right: actualVoltValue.left; anchors.rightMargin: 5 * GUISetting.scale; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignLeft
                        text : qsTr("actual battery voltage :")
                        color: "#000000"
                    }

                    NText{
                        id : actualVoltValue
                        width: 80 * GUISetting.scale;
                        anchors.right: parent.right; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : (dlgModel.mCurrentVoltage / 1000).toFixed(2) + "V"
                        color: dlgModel.mErrCurrentVoltage ? "#FF0000" : "#000000"
                    }
                }

                NChartView{
                    id : _voltChart

                    height: 300 * GUISetting.scale;
                    anchors.top: actualVoltBox.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    mYAxis01Title      : qsTr("battery voltage [V]")
                    mYAxis01Min        : 0
                    mYAxis01Max        : 30
                    mYAxis01LogDecades : 1
                    mYAxis01Factor     : 1
                    mYAxis01Precision  : 8
                    mYAxis01AutoScale  : dlgModel.mAutoScale
                    mYAxis01Log        : false
                    mY01Draw           : true
                    mY01DashDraw       : false

                    mYAxis02Title      : ""
                    mYAxis02Min        : 0
                    mYAxis02Max        : 1
                    mYAxis02LogDecades : 1
                    mYAxis02Factor     : 1
                    mYAxis02Precision  : 0
                    mYAxis02AutoScale  : false
                    mYAxis02Log        : false
                    mY02Draw           : false
                    mY02DashDraw       : false

                    mXRange            : dlgModel.mXRangeSec

                    mPause             : false

                    mDebug             : false

                    Component.onCompleted: {
                        onCommandInit(FontManager.nanumGothicName, 8, "#000000","#FFFFFF", true, false, true, true, true, false, false, false );
                    }
                }

                Item{
                    id : chartBtnBox
                    height: 24 * GUISetting.scale;
                    anchors.top: _voltChart.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    NComboBox{
                        width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.right: scaleBtn.left; anchors.rightMargin: GUISetting.margin

                        textColor: "#000000"

                        model: ["30 seconds","1 minute","2 minutes","5 minutes"]

                        onCurrentIndexChanged: {
                            dlgModel.onCommandSetXRangeIdx(currentIndex);
                        }
                    }


                    NButton{
                        id : scaleBtn
                        height: 24 * GUISetting.scale; width: 150* GUISetting.scale
                        anchors.right: parent.right;

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: dlgModel.mAutoScale ? "#24A7FF" : "#E4E4E4"
                        }

                        onClick: {
                            dlgModel.onCommandSetAutoScale()
                        }

                        text.text : qsTr("Auto scale Y-Axis")
                    }
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: chartItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : enableBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

                    text.text: dlgModel.mEnablePFO ?  qsTr("Disable PFO") :  qsTr("Enable PFO")

                    onClick: {
                        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                        {
                            dialog.openChangeAccessDlg()
                            return;
                        }
                        dialog.commit()
                    }
                }
            }
        }
    }
}
