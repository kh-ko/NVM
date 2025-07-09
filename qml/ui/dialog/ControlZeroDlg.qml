import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import ControlZeroDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Sensor zero")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit    : false

    function zero()
    {
        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            dialog.openChangeAccessDlg()
            return;
        }

        dialog.commit()
    }

    function commit()
    {
        dlgModel.onCommandZero()
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    ControlZeroDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real guiScale : GUISetting.scale

            height: (GUISetting.line_margin + wizardItem.height) + (GUISetting.line_margin + offsetItem.height) + (GUISetting.line_margin + btnBox.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : wizardItem

                height:   (GUISetting.margin + wizardTitle.height              )
                        + (GUISetting.margin + stepSensorZeroEnableLabel.height)
                        + (GUISetting.margin + stepValveOpenLabel.height       )
                        + (GUISetting.margin + stepGasLabel.height             )
                        + (GUISetting.margin + stepSensorStableLabel.height    ) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : wizardTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Sensor zero")
                }

                Item{
                    id : stepSensorZeroEnableIndi
                    width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter:stepSensorZeroEnableLabel.verticalCenter

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter:parent.verticalCenter
                        running: dlgModel.mZeroEnable ? false : true
                        color: dlgModel.mZeroEnable ? "#24A7FF" : "#FF0000"
                    }
                }

                NText{
                    id : stepSensorZeroEnableLabel
                    width: 150 * GUISetting.scale; height: 50 * GUISetting.scale
                    anchors.top: wizardTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: stepSensorZeroEnableIndi.right; anchors.leftMargin: GUISetting.margin;
                    horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                    text : qsTr("Zero enabled")
                }

                NButton{
                    id : stepSensorZeroEnableBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: stepSensorZeroEnableLabel.verticalCenter; anchors.left: stepSensorZeroEnableLabel.right; anchors.rightMargin: GUISetting.margin
                    enabled: !dlgModel.mZeroEnable && dlgModel.mProgress === 100
                    text.text: qsTr("Enable")

                    onClick: {
                        dlgModel.onCommandZeroEnable();
                    }
                }

                Item{
                    id : stepValveOpenIndi
                    width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter:stepValveOpenLabel.verticalCenter

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter:parent.verticalCenter
                        running: dlgModel.mIsOpenedValve ? false : true
                        color: dlgModel.mIsOpenedValve ? "#24A7FF" : "#FF0000"
                    }
                }

                NText{
                    id : stepValveOpenLabel
                    width: 150 * GUISetting.scale; height: 50 * GUISetting.scale
                    anchors.top: stepSensorZeroEnableLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: stepValveOpenIndi.right; anchors.leftMargin: GUISetting.margin;
                    horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                    text : qsTr("Valve opened")
                }

                NButton{
                    id : stepValveOpenBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: stepValveOpenLabel.verticalCenter; anchors.left: stepValveOpenLabel.right; anchors.rightMargin: GUISetting.margin
                    enabled: !dlgModel.mIsOpenedValve && dlgModel.mProgress === 100
                    text.text: qsTr("Open")

                    onClick: {
                        dlgModel.onCommandOpenValve();
                    }
                }

                NText{
                    id : stepValveOpenCurrPos
                    width: 150 * GUISetting.scale
                    anchors.verticalCenter: stepValveOpenLabel.verticalCenter; anchors.left: stepValveOpenBtn.right; anchors.leftMargin: GUISetting.margin
                    horizontalAlignment: Text.AlignLeft
                    text : dlgModel.mPosPosition.toString().padStart(3,'0') + " %"
                }

                Item{
                    id : stepGasIndi
                    width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter:stepGasLabel.verticalCenter

                    Image{
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter:parent.verticalCenter
                        source: "/image/icon-warning.png"
                    }
                }

                NText{
                    id : stepGasLabel
                    width: 150 * GUISetting.scale; height: 50 * GUISetting.scale
                    anchors.top: stepValveOpenLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: stepGasIndi.right; anchors.leftMargin: GUISetting.margin;
                    horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                    text : qsTr("All gas inlets closed")
                }

                NText{
                    id : stepGasNote
                    width: 150 * GUISetting.scale
                    anchors.verticalCenter: stepGasLabel.verticalCenter; anchors.left: stepGasLabel.right; anchors.rightMargin: GUISetting.margin
                    horizontalAlignment: Text.AlignLeft
                    text : qsTr("(Note)<br>Assure no gas-flow in system.")
                }

                Item{
                    id : stepSensorStableIndi
                    width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter:stepSensorStableLabel.verticalCenter

                    Image{
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter:parent.verticalCenter
                        source: "/image/icon-warning.png"
                    }
                }

                NText{
                    id : stepSensorStableLabel
                    width: 150 * GUISetting.scale; height: 50 * GUISetting.scale
                    anchors.top: stepGasLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: stepSensorStableIndi.right; anchors.leftMargin: GUISetting.margin;
                    horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                    text : qsTr("Sensor stable")
                }

                NText{
                    id : stepSensorStableNote
                    width: 150 * GUISetting.scale
                    anchors.verticalCenter: stepSensorStableLabel.verticalCenter; anchors.left: stepSensorStableLabel.right; anchors.rightMargin: GUISetting.margin
                    horizontalAlignment: Text.AlignLeft
                    text : qsTr("(Note)<br>Wait for stable sensor values.")
                }
            }

            Rectangle{
                id : offsetItem

                height: (GUISetting.margin + offsetTitle.height) + (GUISetting.margin + sensor01Box.height) + (GUISetting.margin + sensor02Box.height) + GUISetting.margin
                anchors.top: wizardItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : offsetTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Offset values")
                }

                Rectangle{
                    id : sensor01Box
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: offsetTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : (dlgModel.mSensor01Offset * 0.00001).toFixed(3) + " Volt"
                        color: dlgModel.mErrSensor01Offset ? "#FF0000" : "#000000"
                    }
                }

                NText{
                    anchors.verticalCenter: sensor01Box.verticalCenter; anchors.left: sensor01Box.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor 1")
                }

                Rectangle{
                    id : sensor02Box
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: sensor01Box.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : (dlgModel.mSensor02Offset * 0.00001).toFixed(3) + " Volt"
                        color: dlgModel.mErrSensor02Offset ? "#FF0000" : "#000000"
                    }
                }

                NText{
                    anchors.verticalCenter: sensor02Box.verticalCenter; anchors.left: sensor01Box.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor 2")
                }

                Rectangle{
                    width: parent.width; height: sensor01Box.height + 4; anchors.verticalCenter: sensor01Box.verticalCenter
                    visible: dlgModel.mSensorOp === ValveEnumDef.SENSOROP_01_SENSOR_02_INPUT

                    Image{
                        id : sensor01NoteImg
                        width: sourceSize.width * GUISetting.scale;height: sourceSize.height * GUISetting.scale;
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        source: "/image/icon-info.png"
                    }

                    NText{
                        anchors.verticalCenter: sensor01NoteImg.verticalCenter; anchors.left: sensor01NoteImg.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("Sensor port 1 not supported!")
                    }
                }

                Rectangle{
                    width: parent.width; height: sensor02Box.height + 4; anchors.verticalCenter: sensor02Box.verticalCenter
                    visible: dlgModel.mSensorOp === ValveEnumDef.SENSOROP_01_SENSOR_01_INPUT

                    Image{
                        id : sensor02NoteImg
                        width: sourceSize.width * GUISetting.scale;height: sourceSize.height * GUISetting.scale;
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        source: "/image/icon-info.png"
                    }

                    NText{
                        anchors.verticalCenter: sensor02NoteImg.verticalCenter; anchors.left: sensor02NoteImg.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("Sensor port 2 not supported!")
                    }
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: offsetItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dlgModel.mIsOpenedValve && dlgModel.mZeroEnable && dlgModel.mProgress === 100

                    bgColor: dlgModel.mZeroEnable && dlgModel.mIsOpenedValve ? "#24A7FF" : "#FFFFFF"
                    text.color: dlgModel.mZeroEnable && dlgModel.mIsOpenedValve ? "#FFFFFF" : "#000000"
                    text.text: qsTr("ZERO")

                    onClick: {
                        dialog.zero()
                    }
                }
            }
        }
    }
}
