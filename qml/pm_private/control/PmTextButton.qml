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

    Rectangle{
        anchors.fill: parent
        color : itemMouseArea.containsPress ? "#19000000" : itemMouseArea.containsMouse ? "#29000000" : "#00000000"
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

