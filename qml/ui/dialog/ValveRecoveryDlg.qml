import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import ValveRecoveryDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Valve recovery")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : false

    function reboot()
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
        dlgModel.onCommandReboot()
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth = GUISetting.popup_nor_width
    }

    ValveRecoveryDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real   guiScale                       : GUISetting.scale

            height: (GUISetting.line_margin + valveFatalErrStatusItem.height) + (GUISetting.line_margin + valveSvcRequestItem.height) + (GUISetting.line_margin + btnBox.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : valveFatalErrStatusItem

                height: (GUISetting.margin + fatalErrStatusTitle.height) + (GUISetting.margin + fatalErrStatusContent.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : fatalErrStatusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Fatal error")
                }

                NCircleIndicator{
                    id : fatalErrorIndi
                    width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                    anchors.verticalCenter: fatalErrStatusContent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color: dlgModel.mFatalErrStatus === 0 ? "#24A7FF" : "#FF0000"
                    running: dlgModel.mFatalErrStatus !== 0
                    visible: dialog.progress === 100

                    onRunningChanged: {
                        if(running == false)
                            opacity = 1;
                    }
                }

                NText{
                    id : fatalErrStatusContent
                    height: 24 * GUISetting.scale
                    anchors.top: fatalErrStatusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: fatalErrorIndi.right; anchors.leftMargin: GUISetting.margin;
                    verticalAlignment: Text.AlignVCenter
                    text : dlgModel.mFatalErrStatus === 0 ? qsTr("System OK - No fatal error.") : qsTr("FatalError - " + dlgModel.mFatalErrStatus)
                    visible: dialog.progress === 100
                }
            }

            Rectangle{
                id : valveSvcRequestItem

                height: (GUISetting.margin + svcReqTitle.height) + (GUISetting.margin + svcReqContent.height) + GUISetting.margin
                anchors.top: valveFatalErrStatusItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : svcReqTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Service request")
                }

                NCircleIndicator{
                    id : svcReqIndi
                    width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                    anchors.verticalCenter: svcReqContent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    color: dlgModel.mIsSvcRequest === false ? "#24A7FF" : "#FF0000"
                    running: dlgModel.mIsSvcRequest
                    visible: dialog.progress === 100

                    onRunningChanged: {
                        if(running == false)
                            opacity = 1;
                    }
                }

                NText{
                    id : svcReqContent
                    height: 24 * GUISetting.scale
                    anchors.top: svcReqTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: svcReqIndi.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    verticalAlignment: Text.AlignVCenter
                    text : dlgModel.mIsSvcRequest === false ? qsTr("System OK - No service request.") : qsTr("Service request.")
                    visible: dialog.progress === 100
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: valveSvcRequestItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100
                    visible:  dlgModel.mReConnect == false
                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Reset")

                    onClick: {
                        dialog.reboot()
                    }
                }
            }
        }
    }
}
