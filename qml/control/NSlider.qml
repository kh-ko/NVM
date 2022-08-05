import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3

Slider{
    id : control

    property var isLogType : false
    property var lineColor : "#39000000"
    property var textColor : "#99000000"

    property var minGapHeight :  5.0
    property var minLabelGapHeight :  30.0
    property var fixedN : -1

    property var axisFrom : 0
    property var axisTo   : 100  

    signal selectedValue(var value)

    opacity: enabled ? 1 : 0.3

    function selectValue(newValue, signalCreate = true)
    {
        if(newValue > to)
            value = to
        else if( newValue < from)
            value = from

        value = newValue;

        if(signalCreate)
            control.selectedValue(value);
    }

    orientation: Qt.Vertical

    background: Item{
        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
        width: control.width; height: control.height;

        Rectangle{
            id : bgBar
            width: 4; height: control.availableHeight
            anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: (control.handle.width * 0.5) - (width * 0.5)
            radius: 2
            color: "#E4E4E4"

            Rectangle {
                width: parent.width
                anchors.bottom: parent.bottom
                height: (1 - control.visualPosition) * parent.height
                color: "#5924A7FF"
                radius: 2
            }
        }

        NYAxis{
            id :yAxis
            height: control.availableHeight + 20; width: parent.width - control.handle.width - 2
            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left;

            topPadding: 10; bottomPadding: 10
            isLogType : control.isLogType
            fixedN : control.fixedN
            to : control.axisTo
            from : control.axisFrom

            MouseArea{
                anchors.fill: parent
                hoverEnabled: true
                onPressed: {}
                onReleased: {}
                onClicked: {}
            }
        }
    }

    handle: Rectangle {
        anchors.right: parent.right
        anchors.verticalCenter: parent.bottom; anchors.verticalCenterOffset: -1 * (control.bottomPadding + (1 - control.visualPosition) * control.availableHeight)
        width: 30
        height: 5
        radius: 3
        color: control.pressed ? "#24A7FF" : "#24A7FF"
    }

    onPressedChanged: {
        if(pressed == false)
            control.selectedValue(value)
    }

}

