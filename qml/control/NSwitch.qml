import QtQuick 2.0

Rectangle {
    id : control

    property bool isSelect : false

    signal signalEventSelected()

    opacity: enabled ? 1.0 : 0.3
    radius: width < height ? width*0.5 : height*0.5
    border.width: 1; border.color: "#24A7FF"
    color: "#00000000"

    Rectangle {
        width: parent.width * 0.6; height: parent.height * 0.6
        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
        radius: width < height ? width*0.5 : height*0.5
        color: "#24A7FF"
        visible: control.isSelect
    }

    MouseArea{
        anchors.fill: parent
        enabled: parent.enabled
        onClicked: {
            if(!control.isSelect)
                control.signalEventSelected()
        }
    }
}
