import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.5

ListView {
    id : control

    property color barPressColor : "#39000000"
    property color barColor : "#59000000"

    clip: true

    model : ListModel{
        ListElement{
            name : "item"
        }
    }

    ScrollBar.vertical: ScrollBar {
        id : vSBar

        active: true
        orientation: Qt.Vertical
        width: 6
        height: control.availableHeight
        anchors.right: control.right
        anchors.rightMargin: 4
        policy: height  < control.contentHeight ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

        contentItem: Rectangle
        {
            width: 6
            implicitHeight: 100
            radius: width / 2
            color: vSBar.pressed ?  barPressColor : barColor
        }

        background: Rectangle{
            color : "#00000000"
        }
    }
}
