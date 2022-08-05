import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import GUISetting 1.0

NPopup {
    id : dialog

    property var titleText :  qsTr("Save changed data")
    property var contentText :  qsTr("Modified value settings!<br>Save changed prior to exit?")
    property var caller : null

    contentHeight: 270 * GUISetting.scale; contentWidth: 450 * GUISetting.scale

    contentItem: Item{
        NPopupTilte{
            id : titleBox
            title: dialog.titleText

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
                    id : _msgIcon
                    width: sourceSize.width * GUISetting.scale;height: sourceSize.height * GUISetting.scale;
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin * 2
                    source: "/image/icon-warning.png"
                }

                NText{
                    anchors.left: _msgIcon.right; anchors.leftMargin: GUISetting.margin * 2; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2; anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text : dialog.contentText
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
                    text.text: qsTr("Save")
                    text.color: "#FFFFFF"

                    onClick: {
                        caller.setClose(true);
                        caller.apply();
                        dialog.close();
                    }
                }

                NButton{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1

                    text.text: qsTr("Don't Save")

                    onClick: {
                        caller.setClose(false);
                        caller.close();
                        dialog.close();
                    }
                }

            }
        }
    }
}
