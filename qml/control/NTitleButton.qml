import QtQuick 2.0

Rectangle{
    id: control

    property alias iconSource : btnIcon.source
    property alias textSource : btnText.text

    signal click()

    width: 150
    height: 50
    color: mouseArea.containsPress ? "#29FFFFFF" : mouseArea.containsMouse ? "#19FFFFFF" : "#00FFFFFF"
    opacity: enabled ? 1 : 0.3
    //border.width: 1
    //border.color:  "#0728FB" : "#00000000"

    Image {
        id: btnIcon
        width: 20
        height: 20
        anchors.verticalCenter: parent.verticalCenter
        anchors.right: btnText.left
        anchors.rightMargin: 20
    }

    NText{
        id : btnText
        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
        isBold: true
        color: "#FFFFFF"
    }

    MouseArea{
        id : mouseArea
        anchors.fill: parent;
        hoverEnabled: control.enabled;
        enabled: control.enabled

        onClicked: {
            control.click();
        }
    }
}
