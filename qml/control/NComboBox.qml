import QtQuick 2.12
import QtQuick.Controls 2.12
import "./."

ComboBox {
    id: control

    property var textColor : "#000000"

    opacity: enabled ? 1 : 0.3

    delegate: ItemDelegate {
        width: control.width
        height: 30

        contentItem:Rectangle{
            anchors.fill: parent
            color : highlighted ? "#24A7FF" : "#FFFFFF"

            NText {
                width: parent.width - 20; height: parent.height
                anchors.horizontalCenter: parent.horizontalCenter
                text: modelData
                verticalAlignment: Text.AlignVCenter
            }
        }

        /*contentItem: NText {
            text: modelData
            verticalAlignment: Text.AlignVCenter
        }*/
        highlighted: control.highlightedIndex === index
    }

    indicator: Item{
        x : control.width - width
        y : 0
        width: 18; height: parent.height

        BorderImage {
            width: parent.width + 20; height: parent.height + 20
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter;
            source: "/image/sub-card.png"
            border.left: 15; border.top: 15; border.right: 15; border.bottom: 15
        }

        Rectangle{
            width: parent.width; height: parent.height
            anchors.bottom: parent.bottom
            color: control.pressed ? "#19000000" : control.hovered ? "#29000000" : "#00000000"

            Image { anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter; source: "/image/icon-arrow-down.png" }
            //MouseArea{ id : indiMouseArea; anchors.fill: parent; hoverEnabled: control.enabled; enabled: control.enabled; onClicked: {control.down = !control.down}}
        }
    }

    contentItem: Item{
        NText {
            width: control.width - indicator.width - 20
            anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter

            text: control.displayText
            color : control.textColor
            verticalAlignment: Text.AlignVCenter
        }
    }

    background: BorderImage {
        source: "/image/hall-2.png"
        border.left: 6; border.top: 6; border.right: 6; border.bottom: 6
    }


    popup: Popup {
        y: control.height - 1
        width: control.width
        implicitHeight: contentItem.implicitHeight > 200 ? 200 :contentItem.implicitHeight
        padding: 1

        contentItem: ListView {
            clip: true
            implicitHeight: contentHeight
            model: control.popup.visible ? control.delegateModel : null
            currentIndex: control.highlightedIndex

            ScrollIndicator.vertical: ScrollIndicator { }
        }

        background: Rectangle {
            border.color: "#888888"
            radius: 2
        }
    }
}
