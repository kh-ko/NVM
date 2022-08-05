import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import GUISetting 1.0


NPopup {
    id : dialog

    property var caller : null

    contentHeight: 270 * GUISetting.scale; contentWidth: 500 * GUISetting.scale

    contentItem: Item{
        NPopupTilte{
            id : titleBox
            title: qsTr("")

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
                    anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin * 2
                    source: "/image/icon-warning.png"
                }

                NText{
                    anchors.left: _msgIcon.right; anchors.leftMargin: GUISetting.margin * 2; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2; anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text : qsTr("Data processing is in progress!<br>Do you really want to close it?")
                }
            }


            RowLayout{
                id : btnBox
                height: 50 * GUISetting.scale;
                anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;
                spacing: GUISetting.margin

                NButton{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1

                    text.text: qsTr("Yes")

                    onClick: {
                        caller.close();
                        dialog.close();
                    }
                }

                NButton{
                    Layout.fillHeight: true
                    Layout.fillWidth: true
                    Layout.preferredWidth: 1

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("back")

                    onClick: {
                        dialog.close();
                    }
                }
            }
        }
    }
}
