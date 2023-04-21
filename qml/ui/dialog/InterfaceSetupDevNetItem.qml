import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import InterfaceSetupEthCATItemModel 1.0
import "../../control/."
import GUISetting 1.0

RowLayout {
    id : item

    property bool   isHeader        : false
    property int    itemSeq         : 0
    property bool   isSelected      : false
    property color  selectedColor   : "#24A7FF"
    property color  unSelectedColor : "#00000000"
    property string item01Name      : ""
    property string item02Name      : ""
    property string item03Name      : ""
    property string item04Name      : ""

    spacing: 1 * GUISetting.scale

    signal clickedCheckBox()

    opacity: enabled ? 1.0 : 0.3

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

        color : item.isHeader ? "#24A7FF" : "#FFFFFF"

        Rectangle{
            width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
            anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter

            radius: width / 4
            border.width: item.isSelected ? 0 : 2 * GUISetting.scale
            border.color: item.isSelected ? unSelectedColor : selectedColor
            color: item.isSelected ? selectedColor : unSelectedColor

            MouseArea{
                anchors.fill: parent

                onClicked: {
                    item.clickedCheckBox()
                }
            }
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

        color : item.isHeader ? "#24A7FF" : "#FFFFFF"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item01Name
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

        color : item.isHeader ? "#24A7FF" : "#FFFFFF"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item02Name
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3

        color : item.isHeader ? "#24A7FF" : "#FFFFFF"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item03Name
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3

        color : item.isHeader ? "#24A7FF" : "#FFFFFF"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item04Name
        }
    }
}
