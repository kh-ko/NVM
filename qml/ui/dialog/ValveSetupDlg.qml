import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import ValveSetupDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Valve setup")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function commit()
    {
        var speed  = parseInt(body.valveSpeedInput.textField.text)
        dlgModel.onCommandApply(speed,
                                body.valveTargetPosSyncCombo.currentIndex,
                                body.valveEventSyncCombo.currentIndex,
                                body.valveSyncModeCombo.currentIndex,
                                body.valveLimitationCombo.currentIndex,
                                body.valveTargetPosPowerFailCombo.currentIndex,
                                body.valveTargetPosNetworkFailCombo.currentIndex);
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    ValveSetupDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.valveSpeedInput.focusOut()
            body.valveSpeedInput.setValue(mValveSpeed)
            body.valveTargetPosSyncCombo.currentIndex        = mTargetPosSync
            body.valveEventSyncCombo.currentIndex            = mEventSync
            body.valveSyncModeCombo.currentIndex             = mSyncMode
            body.valveLimitationCombo.currentIndex           = mStrokeLimitation
            body.valveTargetPosPowerFailCombo.currentIndex   = mTargetPosPowerFail
            body.valveTargetPosNetworkFailCombo.currentIndex = mTargetPosNetworkFail
            onCommandSetEdit(false);
        }

        onSignalEventCompletedApply: {
            dialog.close();
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias  valveSpeedInput                : _valveSpeedInput
            property alias  valveTargetPosSyncCombo        : _valveTargetPosSyncCombo
            property alias  valveEventSyncCombo            : _valveEventSyncCombo
            property alias  valveSyncModeCombo             : _valveSyncModeCombo
            property alias  valveLimitationCombo           : _valveLimitationCombo
            property alias  valveTargetPosPowerFailCombo   : _valveTargetPosPowerFailCombo
            property alias  valveTargetPosNetworkFailCombo : _valveTargetPosNetworkFailCombo
            property real   guiScale                       : GUISetting.scale

            height: (GUISetting.line_margin + valveSpeedItem.height)
                    + (GUISetting.line_margin + valveSyncItem.height)
                    + (GUISetting.line_margin + valveLimitationItem.height)
                    + (GUISetting.line_margin + valveConditionItem.height)
                    + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : valveSpeedItem

                height: (GUISetting.margin + valveSpeedTitle.height) + (GUISetting.margin + _valveSpeedInput.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : valveSpeedTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Valve speed")
                }

                NInputNumber{
                    id : _valveSpeedInput
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: valveSpeedTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: IntValidator{}
                    textField.color: dlgModel.mErrValveSpeed ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 1; maxValue: dlgModel.mValveMaxSpeed
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _valveSpeedInput.verticalCenter; anchors.left: _valveSpeedInput.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("Valve speed(" + dlgModel.mValveMaxSpeed + ")")
                }
            }

            Rectangle{
                id : valveSyncItem

                height: (GUISetting.margin + valveSyncTitle.height) + (GUISetting.margin + _valveTargetPosSyncCombo.height) + (GUISetting.margin + _valveEventSyncCombo.height) + (GUISetting.margin + _valveSyncModeCombo.height) + GUISetting.margin
                anchors.top: valveSpeedItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : valveSyncTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Synchronization")
                }

                NComboBox{
                    id : _valveTargetPosSyncCombo
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: valveSyncTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrTargetPosSync ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["close","open"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _valveTargetPosSyncCombo.verticalCenter; anchors.left: _valveTargetPosSyncCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("target-position after synchronization")
                }

                NComboBox{
                    id : _valveEventSyncCombo
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _valveTargetPosSyncCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrEventSync ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["default[not sealed]","selected command","open command","any command"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _valveEventSyncCombo.verticalCenter; anchors.left: _valveEventSyncCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("event to start synchronization")
                }

                NComboBox{
                    id : _valveSyncModeCombo
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _valveEventSyncCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrSyncMode ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["short","extended"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _valveSyncModeCombo.verticalCenter; anchors.left: _valveSyncModeCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("synchronization mode")
                }
            }

            Rectangle{
                id : valveLimitationItem

                height: (GUISetting.margin + valveLimitationTtle.height) + (GUISetting.margin + _valveLimitationCombo.height) + GUISetting.margin
                anchors.top: valveSyncItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : valveLimitationTtle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Control stroke limitation")
                }

                NComboBox{
                    id : _valveLimitationCombo
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: valveLimitationTtle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100
                    textColor: dlgModel.mErrStrokeLimitation ? "#FF0000" : "#000000"

                    model: ["disabled","enabled"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _valveLimitationCombo.verticalCenter; anchors.left: _valveLimitationCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("control stroke limitation")
                }
            }

            Rectangle{
                id : valveConditionItem

                height: (GUISetting.margin + valveConditionTtle.height) + (GUISetting.margin + _valveTargetPosPowerFailCombo.height) + (GUISetting.margin + _valveTargetPosNetworkFailCombo.height) + GUISetting.margin
                anchors.top: valveLimitationItem.bottom; anchors.topMargin: 2; anchors.left: parent.left; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2

                color: "#FFFFFF"

                NText{
                    id : valveConditionTtle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Behaviour under specific conditions")
                }

                NComboBox{
                    id : _valveTargetPosPowerFailCombo
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: valveConditionTtle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrTargetPosPowerFail ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && dlgModel.mIsSupportPFO

                    model: ["close","open"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _valveTargetPosPowerFailCombo.verticalCenter; anchors.left: _valveTargetPosPowerFailCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("target-position at power-failure")
                }

                NComboBox{
                    id : _valveTargetPosNetworkFailCombo
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _valveTargetPosPowerFailCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrTargetPosNetworkFail ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 /*&& dlgModel.mInterface !== ValveEnumDef.INTERFACE_LOGIC*/

                    model: ["close","open", "keep position"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _valveTargetPosNetworkFailCombo.verticalCenter; anchors.left: _valveTargetPosNetworkFailCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("target-position at network-failure")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: valveConditionItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
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
