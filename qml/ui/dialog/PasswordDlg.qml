import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import GUISetting 1.0


NPopup { // khko_todo
    id : dialog

    property var  caller : null
    property bool isOK : true

    signal result(bool value)

    contentHeight: 200 * GUISetting.scale; contentWidth: 250 * GUISetting.scale

    contentItem: Item{
        id : contentContainer

        NPopupTilte{
            id : titleBox
            title: qsTr("Password")

            onClickClose: {
                dialog.close();
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
                    anchors.left: msgIcon.right; anchors.leftMargin: GUISetting.margin * 2; anchors.verticalCenter: msgIcon.verticalCenter
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text : qsTr("Enter password")
                }

                NText{
                    anchors.bottom: inputPIN.top; anchors.bottomMargin: 5 * GUISetting.scale; anchors.left: inputPIN.left;
                    horizontalAlignment: Text.AlignLeft;
                    color : "#FF0000"
                    visible: !dialog.isOK
                    text : qsTr("Check password")
                }

                NInputText{
                    id : inputPIN
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    textField.echoMode: TextInput.Password
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
                        if(inputPIN.textField.text == "7071")
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

                    text.text: qsTr("Cancle")

                    onClick: {
                        dialog.close();
                    }
                }

            }
        }
    }
}
