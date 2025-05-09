import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import GUISetting 1.0


NPopup { // khko_todo
    id : dialog

    property var    caller   : null
    property bool   isOK     : true
    property string keyValue : "239874"
    signal result(bool value)
    signal cancel()

    focus: true
    contentHeight: 250 * GUISetting.scale; contentWidth: 450
    Component.onCompleted: {
        inputPIN.focusIn()
    }

    contentItem: Item{
        id : contentContainer

        NPopupTilte{
            id : titleBox
            title: qsTr("Notice")

            onClickClose: {
                dialog.close();
                dialog.cancel();
            }
        }

        Rectangle{
            color : "#FFFFFF"
            anchors.top: titleBox.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right;

            Item{
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: btnBox.top; anchors.bottomMargin: GUISetting.margin

                Image{
                    id : msgIcon
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin * 2
                    source: "/image/icon-warning.png"
                }

                NText{
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin * 2; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2; anchors.top: msgIcon.top
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    lineHeight: 1.5
                    text : qsTr("You have exceeded the download limit.<br>Please obtain an activation code.<br>Contact: gh_ko@novasen.net, chris.chang@novasen.net")
                }

                NText{
                    anchors.bottom: inputPIN.top; anchors.bottomMargin: 5 * GUISetting.scale; anchors.left: inputPIN.left;
                    horizontalAlignment: Text.AlignLeft;
                    color : "#FF0000"
                    visible: !dialog.isOK
                    text : qsTr("Check code")
                }

                NInputText{
                    id : inputPIN
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    textField.echoMode: TextInput.Password

                    onEnterClicked: {
                        if(inputPIN.textField.text == keyValue)
                        {
                            dialog.close();
                            dialog.result(true);
                            return;
                        }

                        dialog.isOK = false
                    }
                }
            }


            RowLayout{
                id : btnBox
                height: GUISetting.popup_btnbox_btn_height;
                anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;
                spacing: GUISetting.margin

                NButton{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Confirm")

                    onClick: {
                        // todo
                        if(inputPIN.textField.text == keyValue)
                        {
                            dialog.close();
                            dialog.result(true);
                            return;
                        }

                        dialog.isOK = false
                    }
                }

                NButton{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1

                    text.text: qsTr("Cancel")

                    onClick: {
                        dialog.close();
                        dialog.cancel();
                    }
                }

            }
        }
    }
}
