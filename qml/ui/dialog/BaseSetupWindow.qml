import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import GUISetting 1.0

NWindow {
    id : dialog

    property var titleText   : "title"
    property var progress    : 0
    property var strStatus   : ""
    property var errMsg      : ""
    property var errMsg2     : ""
    property var access      : ValveEnumDef.ACCESS_REMOTE
    property var isRS232Test : false
    property var isEdit      : false
    property var isCloseAtComplete : false

    property alias titleBox : _titleBox
    property alias contentBody : _contentBody
    property real bodyHeight:50
    property real bodyWidth :500

    onBodyWidthChanged: {console.debug("[khko_debug]onBodyWidthChanged : " + bodyWidth)}

    property alias changeAccessDlg : _changeAccessDlg

    function openChangeAccessDlg()
    {
        var popup = _changeAccessDlg.createObject(dialog)
        popup.caller = dialog
        popup.open();
    }

    function openCloseConfirmDlg()
    {
        var popup = closeConfirmDlg.createObject(dialog)
        popup.caller = dialog
        popup.open();
    }

    function openProgressConfirmDlg()
    {
        var popup = progressConfirmDlg.createObject(dialog)
        popup.caller = dialog
        popup.open();
    }

    function showErrMessage(msg)
    {
        var popup = messageBox.createObject(dialog)
        popup.titleText = qsTr("Error")
        popup.contentText = msg
        popup.msgIcon.source = "/image/icon-alret.png"
        popup.open();
    }
    function showMessage(msg)
    {
        var popup = messageBox.createObject(dialog)
        popup.titleText = qsTr("Information")
        popup.contentText = msg
        popup.msgIcon.source = "/image/icon-info.png"
        popup.open();
    }


    function onResultChangeAccess(value)
    {
        if(value)
        {
            dialog.commit()
            return;
        }
        showErrMessage(qsTr("Mode change failed."))
    }

    function setClose(isClose)
    {
        dialog.isCloseAtComplete = isClose
    }

    function apply()
    {
        if(dialog.isEdit === false)
            return;

        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            dialog.openChangeAccessDlg()
            return;
        }

        dialog.commit()
    }

    onProgressChanged: {
        if(dialog.progress === 100 && dialog.isCloseAtComplete)
            dialog.close()
    }

    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    Item {
        id : contentContainer
        height: _titleBox.height + dialog.bodyHeight + statusBar.height; width: dialog.bodyWidth
        anchors.centerIn: parent

        NPopupTilte{
            id : _titleBox
            title: dialog.titleText
            root: dialog

            onClickClose: {
                if(dialog.doNotDestroy)
                    dialog.close();
                else if(dialog.progress !== 100)
                    dialog.openProgressConfirmDlg()
                else if(dialog.isEdit === false)
                    dialog.close();
                else
                    dialog.openCloseConfirmDlg()
            }
        }

        Item{
            id : _contentBody
            width: dialog.bodyWidth; height: dialog.bodyHeight
            anchors.top: _titleBox.bottom; anchors.left: parent.left
        }

        NPopupStatusBar{
            id : statusBar

            height: 20 * GUISetting.scale; width: parent.width
            anchors.top: _contentBody.bottom; anchors.left: parent.left

            progress : dialog.progress
            status   : dialog.strStatus
            errMsg   : dialog.errMsg
            errMsg2  : dialog.errMsg2
        }
    }


    Component{
        id : _changeAccessDlg
        ChangeAccessDlg{
        }
    }

    Component{
        id : closeConfirmDlg
        CloseConfirmDlg{
        }
    }

    Component{
        id : progressConfirmDlg
        ProgressConfirmDlg{
        }
    }

    Component{
        id : messageBox
        NMessageBox{

        }
    }
}
