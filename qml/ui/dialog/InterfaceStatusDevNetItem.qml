import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import InterfaceSetupEthCATItemModel 1.0
import "../../control/."
import GUISetting 1.0

RowLayout {
    id : item

    property bool   isHeader        : false
    property string item01Name      : ""
    property string item02Name      : ""
    property string item03Name      : ""

    spacing: 1 * GUISetting.scale

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
}
