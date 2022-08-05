import QtQuick 2.0

Rectangle{
    id: control

    property alias text   : textBox
    property var   bgColor: "#00000000"

    opacity: enabled ? 1 : 0.3

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
        color : control.bgColor
    }

    Rectangle{
        anchors.fill: parent
        color : itemMouseArea.containsPress ? "#19000000" : itemMouseArea.containsMouse ? "#29000000" : "#00000000"
    }

    NText{
        id : textBox
        anchors.fill: parent
        horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter

        elide: Text.ElideRight
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

