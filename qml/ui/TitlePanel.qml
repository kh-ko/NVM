import QtQuick 2.0
import QtQuick.Controls 2.3
import "../control/."
import GlobalUiValue 1.0
import GUISetting 1.0

Rectangle {
    id : panel
    property bool isLocal : false
    property bool isRS232Test : false
    property string version : "---"
    property bool connected : false

    signal clickChangeAccessMode()
    signal clickPortSelection()

    width: 1024; height: 36
    color: "#24292e"
    //border.width: 1; border.color: "#000000"

    NTitleButton{
        id : btnAccessMode
        width: GUISetting.title_btn_access_width; height: parent.height
        iconSource: "/image/icon-key.png"
        textSource: panel.isLocal && panel.isRS232Test == false? qsTr("Remote") :
                    panel.isLocal && panel.isRS232Test == true ? qsTr("Remote(RS232 Test)") :
                    panel.isLocal == false && panel.isRS232Test == false? qsTr("Local") :
                    panel.isLocal == false && panel.isRS232Test == true ? qsTr("Local(RS232 Test)") : ""

        enabled   : connected

        onClick: {
            panel.clickChangeAccessMode()
        }

        Rectangle{
            width: 1; height: parent.height
            anchors.right: parent.right;

            color: "#000000"
        }
    }

    NTitleButton{
        id : btnPortSelection
        width: GUISetting.title_btn_portselection_width; height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        iconSource: "/image/icon-port.png"
        textSource: qsTr("Port selection")
        enabled   : !GlobalUiValue.disableWinCreateBtn

        onClick: {
            panel.clickPortSelection()
        }

        Rectangle{
            width: 1; height: parent.height
            anchors.left: parent.left;

            color: "#000000"
        }

        Rectangle{
            width: 1; height: parent.height
            anchors.right: parent.right;

            color: "#000000"
        }
    }


    NText{
        color : "#ACACAC"
        text : panel.version
        anchors.right: parent.right; anchors.rightMargin: GUISetting.right_margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.title_ver_bottom_margin
    }
}
