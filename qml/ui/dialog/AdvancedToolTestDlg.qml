import QtQuick 2.0

import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import AdvancedToolTestDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText : qsTr("Advanced test")
    progress  : dlgModel.mProgress
    strStatus : dlgModel.mStrStatus
    errMsg    : dlgModel.mErrMsg
    access    : dlgModel.mAccessMode
    isEdit    : false
    isModal   : false

    Item{
        id : softOpen

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
            dlgModel.onCommandSoftOpen()
        }
    }

    Item{
        id : softClose

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
            dlgModel.onCommandSoftClose()
        }
    }

    Item{
        id : testModeOn

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
            dlgModel.onCommandSetTestMode(true)
        }
    }

    Item{
        id : testModeOff

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
            dlgModel.onCommandSetTestMode(false)
        }
    }

    Item{
        id : encoderZero

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
            dlgModel.onCommandEncoderZero()
        }
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    AdvancedToolTestDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real guiScale : GUISetting.scale

            height: (GUISetting.line_margin + softOpenCloseItem.height) + (GUISetting.line_margin + testModeItem.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : softOpenCloseItem

                height: (GUISetting.margin + softOpenCloseTitle.height) + (GUISetting.margin + softOpenBtn.height) + (GUISetting.margin + softCloseBtn.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : softOpenCloseTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Soft open/close")
                }

                NButton{
                    id : softOpenBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: softOpenCloseTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text.text: qsTr("Soft open")
                    onClick: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            dlgModel.onCommandSoftOpen()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = softOpen;  popup.open();
                        }
                    }
                }

                NButton{
                    id : softCloseBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: softOpenBtn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text.text: qsTr("Soft close")

                    onClick: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            dlgModel.onCommandSoftClose()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = softClose;  popup.open();
                        }
                    }
                }
            }

            Rectangle{
                id : testModeItem

                height: (GUISetting.margin + testModeTitle.height) + (GUISetting.margin + testOnBtn.height) + (GUISetting.margin + rs232TestOnBtn.height) + (GUISetting.margin + encZeroBtn.height) + GUISetting.margin
                anchors.top: softOpenCloseItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : testModeTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Test mode")
                }

                NButton{
                    id : testOnBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: testModeTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text.text: dlgModel.mIsTestMode ? qsTr("Test mode off") : qsTr("Test mode on")

                    onClick: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            dlgModel.onCommandSetTestMode(!dlgModel.mIsTestMode)
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = dlgModel.mIsTestMode? testModeOff : testModeOn;  popup.open();
                        }
                    }
                }

                NButton{
                    id : rs232TestOnBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: testOnBtn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text.text: dlgModel.mIsRS232Test ? qsTr("RS232 Test off") : qsTr("RS232 Test on")

                    onClick: {
                        dlgModel.onCommandSetIsRS232Test(!dlgModel.mIsRS232Test)
                    }
                }

                NButton{
                    id : encZeroBtn
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: rs232TestOnBtn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text.text: qsTr("Encoder zero")

                    onClick: {
                        if(dlgModel.mAccessMode == ValveEnumDef.ACCESS_LOCAL || dlgModel.mIsRS232Test)
                            dlgModel.onCommandEncoderZero()
                        else
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = encoderZero;  popup.open();
                        }
                    }
                }
            }
        }
    }
}

