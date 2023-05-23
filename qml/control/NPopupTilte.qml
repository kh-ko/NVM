import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import GUISetting 1.0

Rectangle {
    id : control

    property bool  enableMinimizeBtn : false
    property bool  enableCloseBtn : true
    property alias title : titleText.text

    property NWindow root : null
    property int  previousX
    property int  previousY

    signal clickClose()
    signal clickMinimized()

    width: parent.width; height: GUISetting.popup_title_height
    color: "#24292e"

    Label {
        id : titleText
        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        color: "#FFFFFF"

        font.pixelSize: 12 * GUISetting.scale
        text : qsTr("Port Selection")
    }

    MouseArea {
        anchors.fill: parent
        // We set the shape of the cursor so that it is clear that this resizing
        onPressed: {
            previousX = mouseX
            previousY = mouseY
        }

        onMouseXChanged: {
            var dx = mouseX - previousX

            if(root != null)
                root.setX(root.x + dx)
        }

        onMouseYChanged: {
            var dy = mouseY - previousY

            if(root != null)
                root.setY(root.y + dy)
        }
    }

    Rectangle{
        visible: control.enableMinimizeBtn
        width: parent.height; height: parent.height
        anchors.right: closeBtn.left; anchors.rightMargin: GUISetting.margin
        color: minimizeMouseArea.containsPress ? "#29FFFFFF" : minimizeMouseArea.containsMouse ? "#19FFFFFF" : "#00FFFFFF"

        Image{
            anchors.fill: parent
            source: "/image/icon-minimized.png"
        }

        MouseArea{
            id : minimizeMouseArea
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                control.clickMinimized();
            }
        }
    }

    Rectangle{
        id : closeBtn
        visible: enableCloseBtn
        width: parent.height; height: parent.height
        anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        color: mouseArea.containsPress ? "#29FFFFFF" : mouseArea.containsMouse ? "#19FFFFFF" : "#00FFFFFF"

        Image{
            anchors.fill: parent
            source: "/image/icon-close.png"
        }

        MouseArea{
            id : mouseArea
            anchors.fill: parent
            hoverEnabled: true

            onClicked: {
                control.clickClose();
            }
        }
    }
}
