import QtQuick 2.0
import FontManager 1.0

Item{
    id: control

    property string text : "test"
    property string textColor : "#000000"

    opacity: enabled ? 1 : 0.3
    width: 100; height: 24

    signal click()
    signal rightClick()

    BorderImage {
        height: parent.height + 100; width: parent.width + 100
        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
        source: (itemMouseArea.containsPress || !parent.enabled) ? "/image/card-1.png" : "/image/card-2.png"
        border.left: 50; border.top: 50
        border.right: 50; border.bottom: 50
    }

    Rectangle{
        anchors.fill: parent
        color : itemMouseArea.containsPress ? "#39000000" : itemMouseArea.containsMouse ? "#49000000" : "#00000000"
    }

    Text {
        anchors.fill: parent
        color: control.textColor
        font.family: FontManager.nanumGothicName
        font.pixelSize: 10
        elide: Text.ElideRight

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        text : control.text
    }

    MouseArea{
        id : itemMouseArea

        anchors.fill: parent
        hoverEnabled: control.enabled
        enabled: control.enabled
        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onPressed: {
            focus = true
        }

        onClicked: {
            if (mouse.button === Qt.RightButton)
            {
                control.rightClick();
            }
            else if (mouse.button === Qt.LeftButton)
            {
                control.click();
            }

        }
    }
}

