import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import PressureCtrlSetupDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Pressure control setup")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit
    isModal     : false

    function commit()
    {
        dlgModel.onCommandApply(body.controlModeCombo.currentIndex, body.gainFactorCombo.currentIndex, body.sensorDelayCombo.currentIndex, body.rampTimeCombo.currentIndex)
    }

    Component.onCompleted: {

        console.debug("[khko_debug]float set win modality = " + modality)

        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    PressureCtrlSetupDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.controlModeCombo.currentIndex = dlgModel.mControlMode
            body.gainFactorCombo.currentIndex  = dlgModel.mGainFactor
            body.sensorDelayCombo.currentIndex = dlgModel.mSensorDelay
            body.rampTimeCombo.currentIndex    = dlgModel.mRampTime
            onCommandSetEdit(false);
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias  controlModeCombo : _controlModeCombo
            property alias  gainFactorCombo  : _gainFactorCombo
            property alias  sensorDelayCombo : _sensorDelayCombo
            property alias  rampTimeCombo    : _rampTimeCombo
            property real   guiScale         : GUISetting.scale

            height: GUISetting.line_margin + _pressureCtrlSetupItem.height + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : _pressureCtrlSetupItem

                height: GUISetting.margin + _pressureCtrlSetupTitle.height + GUISetting.margin + _controlModeCombo.height + GUISetting.margin + _gainFactorCombo.height + GUISetting.margin + _sensorDelayCombo.height + GUISetting.margin + _rampTimeCombo.height + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : _pressureCtrlSetupTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Pressure-control configuration")
                }

                NComboBox{
                    id : _controlModeCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _pressureCtrlSetupTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrValue ? "#FF0000" : "#000000"
                    enabled: false //dialog.progress === 100

                    model: ["adaptive downstream","fixed downstream", "fixed upstream", "soft dump"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _controlModeCombo.verticalCenter; anchors.left: _controlModeCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("control-mode selection")
                }

                NComboBox{
                    id : _gainFactorCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _controlModeCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrValue ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["0.1000","0.1300", "0.1800", "0.2300", "0.3200", "0.4200","0.5600","0.7500","1.0000","1.3300","1.7800","2.3700","3.1600","4.2200","5.6200","7.5000","0.0001","0.0003","0.0010","0.0030","0.0100","0.0200","0.0500" ]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _gainFactorCombo.verticalCenter; anchors.left: _gainFactorCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("gain factor")
                }

                NComboBox{
                    id : _sensorDelayCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _gainFactorCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrValue ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["0.00","0.02","0.04","0.06","0.08","0.10","0.15","0.20","0.25","0.30","0.35","0.40","0.50","0.60","0.80","1.00"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensorDelayCombo.verticalCenter; anchors.left: _sensorDelayCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor delay")
                }
/*
                NComboBox{
                    id : _pGainFactorCombo
                    width: 100; height: 24
                    anchors.top: _controlModeCombo.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 10

                    textColor: dlgModel.mErrValue ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["0.1000","0.1300", "0.1800", "0.2300", "0.3200", "0.4200","0.5600","0.7500","1.0000","1.3300","1.7800","2.3700","3.1600","4.2200","5.6200","7.5000","0.0001","0.0003","0.0010","0.0030","0.0100","0.0200","0.0500" ]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pGainFactorCombo.verticalCenter; anchors.left: _pGainFactorCombo.right; anchors.leftMargin: 10
                    text : qsTr("P-gain")
                }

                NComboBox{
                    id : _iGainFactorCombo
                    width: 100; height: 24
                    anchors.top: _gainFactorCombo.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 10

                    textColor: dlgModel.mErrValue ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["0.00","0.02","0.04","0.06","0.08","0.10","0.15","0.20","0.25","0.30","0.35","0.40","0.50","0.60","0.80","1.00"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _iGainFactorCombo.verticalCenter; anchors.left: _iGainFactorCombo.right; anchors.leftMargin: 10
                    text : qsTr("I-gain")
                }
*/

                NComboBox{
                    id : _rampTimeCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensorDelayCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrValue ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["0.0","0.5","1.0","1.5","2.0","2.5","3.0","3.5","4.0","4.5","5.0","5.5","6.0","6.5","7.0","7.5","8.0","8.5","9.0","9.5","10.0"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _rampTimeCombo.verticalCenter; anchors.left: _rampTimeCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("ramp time")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: _pressureCtrlSetupItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: 50 * GUISetting.scale; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Apply")

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                        color: "#FF0000"
                        visible: dialog.isEdit
                    }

                    onClick: {
                        dialog.apply()
                    }
                }
            }
        }
    }
}
