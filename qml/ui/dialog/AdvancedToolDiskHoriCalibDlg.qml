import QtQuick 2.0

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import AdvancedToolDiskHoriCalibDlgModel 1.0
import ValveEnumDef 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText : qsTr("Disk horizental calibration")
    progress  : dlgModel.mProgress
    strStatus : dlgModel.mStrStatus
    errMsg    : dlgModel.mErrMsg
    access    : dlgModel.mAccessMode
    isEdit    : false
    isModal   : false

    Item{
        id : reboot

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }

        function commit()
        {
            dlgModel.onCommandReboot()
        }
    }

    Item{
        id : setSyncOffset

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }

        function commit()
        {
            dlgModel.onCommandSetSyncOffset(parseInt(body.syncOffsetInput.textField.text))
        }
    }

    Item{
        id : setPosition

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }

        function commit()
        {
            dlgModel.onCommandPosition(parseInt(body.positionInput.textField.text))
        }
    }

    Item{
        id : setCalibration

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }

        function commit()
        {
            var newSyncOffset = dlgModel.mCurrSyncOffset - dlgModel.mCurrPos
            body.syncOffsetInput.textField.text = newSyncOffset;
            dlgModel.onCommandSetSyncOffset(parseInt(body.syncOffsetInput.textField.text))
        }
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    AdvancedToolDiskHoriCalibDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.syncOffsetInput.textField.text = dlgModel.mCurrSyncOffset
            body.positionInput.textField.text = dlgModel.mCurrPos
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias syncOffsetInput  : _syncOffsetInput
            property alias positionInput    : _positionInput

            property real guiScale : GUISetting.scale

            height: (GUISetting.line_margin + syncOffsetItem.height) + (GUISetting.line_margin + positionItem.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : syncOffsetItem

                height: (GUISetting.margin + syncOffsetTitle.height) + (GUISetting.margin + currSyncOffsetLabel.height) + (GUISetting.margin + _syncOffsetInput.height) + (GUISetting.margin + rebootBtn.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : syncOffsetTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Sync offset")
                }

                NText{
                    id : currSyncOffsetLabel
                    anchors.top: syncOffsetTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("Current syncoffset : ")
                }

                NText{
                    anchors.verticalCenter: currSyncOffsetLabel.verticalCenter; anchors.left: currSyncOffsetLabel.right; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : dlgModel.mCurrSyncOffset
                }

                NInputNumber{
                    id : _syncOffsetInput
                    width: 160 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: currSyncOffsetLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.color: dlgModel.mCurrSyncOffset != parseInt(textField.text) ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: -10000; maxValue: 10000
                    fixedN : 0
                }

                NButton{
                    id : syncApply
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: _syncOffsetInput.verticalCenter; anchors.left: _syncOffsetInput.right; anchors.leftMargin: GUISetting.margin
                    enabled: dlgModel.mProgress == 100
                    text.text: qsTr("Apply")
                    onClick: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            setSyncOffset.commit()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = setSyncOffset;  popup.open();
                        }
                    }
                }

                NButton{
                    id : rebootBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: _syncOffsetInput.verticalCenter; anchors.left: syncApply.right; anchors.leftMargin: GUISetting.margin
                    enabled: dlgModel.mProgress == 100
                    text.text: qsTr("Reboot")
                    onClick: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            reboot.commit()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = reboot;  popup.open();
                        }
                    }
                }
            }

            Rectangle{
                id : positionItem

                height: (GUISetting.margin + positionTitle.height) + (GUISetting.margin + currentPosLabel.height) + (GUISetting.margin + _positionInput.height) + (GUISetting.margin + calibBtn.height) + GUISetting.margin
                anchors.top: syncOffsetItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : positionTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Adjustment position")
                }

                NText{
                    id : currentPosLabel
                    anchors.top: positionTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("Current position : ")
                }

                NText{
                    anchors.verticalCenter: currentPosLabel.verticalCenter; anchors.left: currentPosLabel.right; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : dlgModel.mCurrPos
                }

                NInputNumber{
                    id : _positionInput
                    width: 160 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: currentPosLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.color: "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 10000
                    fixedN : 0
                    isEexplicitInputMode : true

                    onChangedValue: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            setPosition.commit()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = setPosition;  popup.open();
                        }
                    }

                    onFocusOutTextField: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            setPosition.commit()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = setPosition;  popup.open();
                        }
                    }
                }

                NButton{
                    id : calibBtn
                    width: 160 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _positionInput.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    enabled: dlgModel.mProgress == 100
                    text.text: qsTr("Calibration")

                    onClick: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            setCalibration.commit()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = setCalibration;  popup.open();
                        }
                    }
                }
            }
        }
    }
}

