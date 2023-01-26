import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import AdvancedToolBackupNRestoreDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText : qsTr("Backup and restore")
    progress  : dlgModel.mProgress
    strStatus : dlgModel.mStrStatus
    errMsg    : dlgModel.mErrMsg
    access    : dlgModel.mAccessMode
    isEdit    : false
    isModal   : false

    Item{
        id : backup

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
            wFileDialog.open()
        }
    }

    Item{
        id : restore

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
            rFileDialog.open()
        }
    }


    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    AdvancedToolBackupNRestoreDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real guiScale : GUISetting.scale

            height: (GUISetting.line_margin + backupItem.height) + (GUISetting.line_margin + restoreItem.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : backupItem

                height: (GUISetting.margin + backupTitle.height) + (GUISetting.margin + backupBtn.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : backupTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Backup")
                }

                NButton{
                    id : backupBtn
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: backupTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text.text: qsTr("Export valve settings")
                    onClick: {
                        if(dlgModel.mAccessMode !== ValveEnumDef.ACCESS_LOCAL && !dlgModel.mIsRS232Test)
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = backup;  popup.open();
                            return;
                        }

                        backup.commit()
                    }
                }
            }

            Rectangle{
                id : restoreItem

                height: (GUISetting.margin + restoreTitle.height) + (GUISetting.margin + restoreBtn.height) + GUISetting.margin
                anchors.top: backupItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : restoreTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Restore")
                }

                NButton{
                    id : restoreBtn
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: restoreTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text.text: qsTr("Import valve settings")

                    onClick: {
                        if(dlgModel.mAccessMode !== ValveEnumDef.ACCESS_LOCAL && !dlgModel.mIsRS232Test)
                        {
                            var popup = dialog.changeAccessDlg.createObject(dialog)
                            popup.caller = restore;  popup.open();
                            return;
                        }

                        restore.commit()
                    }
                }
            }
        }
    }

    FileDialog{
        id: wFileDialog
            title: qsTr("Write valve settings as")
            //folder: "./"
            fileMode: FileDialog.SaveFile
            nameFilters: ["Text files (*.txt)"]

            onAccepted: {
                dlgModel.onCommandWriteToFile(currentFile.toString().split("///")[1])
            }
            onRejected: {
            }
            visible : false
    }

    FileDialog{
        id: rFileDialog
            title: qsTr("Read valve settings from file")
            //folder: "./"
            fileMode: FileDialog.OpenFile
            nameFilters: ["Text files (*.txt)"]

            onAccepted: {
                dlgModel.onCommandReadFromFile(currentFile.toString().split("///")[1])
            }
            onRejected: {
            }
            visible : false
    }
}

