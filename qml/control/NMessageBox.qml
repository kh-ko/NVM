import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "./."

NPopup {
    id : dialog

    property var titleText : qsTr("Message box")
    property var contentText : qsTr("Message box content")
    property alias msgIcon : _msgIcon
    contentHeight: 200; contentWidth: 500


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

            Image{
                id : _msgIcon
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 20
            }

            NText{
                anchors.left: _msgIcon.right; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20; anchors.verticalCenter: parent.verticalCenter
                horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                text : dialog.contentText
            }
        }
    }
}
