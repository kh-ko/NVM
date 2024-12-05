import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../control/."
import GlobalUiValue 1.0
import GUISetting 1.0
import FontManager 1.0

Rectangle {
    id : panel
    color : isConnected ? "#F5F5F5" : "#59FF0000"
    height: 24; width: 1024

    property var connectInfo  : ""
    property var serialNumber : ""
    property var isConnected  : false
    property var scanRate     : 0
    property var loadProgress : 0

    RowLayout{
        anchors.fill: parent
        spacing: 0
        NText{
            Layout.fillHeight: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 1
            text : panel.connectInfo
        }
        NText{
            Layout.fillHeight: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 3
            font.family: FontManager.codingName
            text : panel.isConnected ? qsTr("connected valve : ") + panel.serialNumber : ""
        }
        NText{
            Layout.fillHeight: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 1
            text : panel.isConnected ? qsTr("status : connect") : qsTr("status : disconnect")
        }
        NText{
            Layout.fillHeight: true
            Layout.fillWidth: true
            horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
            Layout.preferredWidth: 1
            color: panel.scanRate > 1000 ? "#FF0000" : "#000000"
            text : panel.isConnected ? qsTr("scan-rate : ") + panel.scanRate + "ms" : qsTr("scan-rate : -")
        }
        Item{
            Layout.fillHeight: true
            Layout.fillWidth: true

            Rectangle{
                width: parent.width - (40 * GUISetting.scale); height: 10 * GUISetting.scale
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

                color : "#E4E4E4"
                visible: panel.loadProgress !== 0 && panel.loadProgress !== 100

                Rectangle{
                    width : parent.width * ( panel.loadProgress/100); height: parent.height
                    anchors.left: parent.left

                    color : "#24A7FF"
                }
            }
        }
    }
}
