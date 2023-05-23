import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import GUISetting 1.0


NPopup {
    id : dialog

    property string msg : ""

    contentHeight: 270 * GUISetting.scale; contentWidth: 450 * GUISetting.scale

    signal signalConfirm()

    contentItem: Item{
        NPopupTilte{
            id : titleBox
            enableCloseBtn : false
            title: qsTr("Notice")

            onClickClose: {
                dialog.close();
            }
        }

        Rectangle{
            color : "#FFFFFF"
            anchors.top: titleBox.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right;

            Item{
                anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: btnBox.top; anchors.bottomMargin: GUISetting.margin

                NText{
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin * 2; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2; anchors.verticalCenter: parent.verticalCenter
                    horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                    text : msg
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
                    text.text: qsTr("OK")

                    onClick: {
                        dialog.signalConfirm();
                        dialog.close();
                    }
                }
            }
        }
    }
}
