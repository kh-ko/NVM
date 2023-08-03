import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import GUISetting 1.0
import "./."

NPopup {
    id : dialog

    //property var titleText : qsTr("Message box")
    //property alias msgIcon : _msgIcon
    property var contentText : qsTr("Message box content")
    property var btnText : qsTr("Confirm")

    signal confirm();

    contentHeight: 200 * GUISetting.scale; contentWidth: 500 * GUISetting.scale


    contentItem: Item{
        Rectangle{
            color : "#FFFFFF"
            anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right;

            NText{
                anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.bottom: btnBox.top;
                anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;
                lineHeight: 2
                verticalAlignment: Text.AlignVCenter
                text : dialog.contentText
            }

            Item{
                id : btnBox

                height: GUISetting.margin + btnConfirm.height + GUISetting.margin; width: parent.width
                anchors.bottom: parent.bottom

                NButton{
                    id : btnConfirm
                    height: (70 * GUISetting.scale); width: (160 * GUISetting.scale)

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;

                    text.text: dialog.btnText

                    bgColor: "#24A7FF"
                    onClick: {
                        dialog.confirm()
                        close()
                    }
                }
            }
        }
    }
}
