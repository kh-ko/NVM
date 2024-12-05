import QtQuick 2.0
import QtQuick.Layouts 1.3
import GUISetting 1.0
import FontManager 1.0

Rectangle {
    id : control

    property var progress : 0
    property var status   : ""
    property var errMsg   : ""
    property var errMsg2   : ""
    property var connectInfo : ""
    property var valveID     : ""

    color: "#FFFFFF"

    Rectangle{
        id : connectInfoBox
        height: parent.height * 0.5
        anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom

        color: "#E4E4E4"

        NText{
            anchors.fill: parent; anchors.leftMargin: GUISetting.margin;
            verticalAlignment: Text.AlignVCenter
            font.family: FontManager.codingName
            text : connectInfo + "      " + valveID
        }
    }

    RowLayout{
        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.top: parent.top; anchors.bottom: connectInfoBox.top
        spacing: 10

        NText{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 2
            verticalAlignment: Text.AlignVCenter
            text : control.status
        }

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 5

            Item{
                width: parent.width / 2; height: parent.height

                Image{
                    id : errIcon
                    width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                    anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                    source: "/image/icon-alret.png"
                    visible: control.errMsg !== ""
                }

                NText{
                    anchors.left: errIcon.right; anchors.leftMargin: 6 * GUISetting.scale; anchors.right: parent.right; anchors.rightMargin: 0; anchors.verticalCenter: parent.verticalCenter
                    text : control.errMsg
                }
            }

            Item{
                width: parent.width / 2; height: parent.height
                anchors.right: parent.right

                Image{
                    id : errIcon2
                    width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                    anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter
                    source: "/image/icon-alret.png"
                    visible: control.errMsg2 !== ""
                }

                NText{
                    anchors.left: errIcon2.right; anchors.leftMargin: 6 * GUISetting.scale; anchors.right: parent.right; anchors.rightMargin: 0; anchors.verticalCenter: parent.verticalCenter
                    text : control.errMsg2
                }
            }

        }

        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true
            Layout.preferredWidth: 2

            Rectangle{
                width: parent.width - (40 * GUISetting.scale); height: 10 * GUISetting.scale
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

                color : "#E4E4E4"
                visible: control.progress !== 100

                Rectangle{
                    width : parent.width * ( control.progress/100); height: parent.height
                    anchors.left: parent.left

                    color : "#24A7FF"
                }
            }
        }
    }

}
