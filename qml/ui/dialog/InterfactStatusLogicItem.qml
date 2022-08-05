import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import GUISetting 1.0

RowLayout {
    id : item

    property var isON : false
    property var isHeader  : false
    property var col01Text : "column01"
    property var col02Text : "column02"
    property var col03Text : "column03"
    property var col04Text : "column04"

    spacing: 1

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4

        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        Rectangle{
            id : onIndi
            width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

            radius: width / 4
            border.width: item.isON ? 0 : (2 * GUISetting.scale)
            border.color: item.isON ? "#00000000" : "#24A7FF"
            color: item.isON ? "#24A7FF" : "#00000000"

            visible: !item.isHeader
        }

        NText{
            anchors.left: !item.isHeader ? onIndi.right : undefined; anchors.leftMargin: !item.isHeader ? 10 * GUISetting.scale : undefined;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: item.isHeader ? parent.horizontalCenter : undefined

            isBold: item.isHeader
            text : item.col01Text
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        NText{
            anchors.left: !item.isHeader ? parent.left : undefined; anchors.leftMargin: !item.isHeader ? 10 * GUISetting.scale : undefined;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: item.isHeader ? parent.horizontalCenter : undefined

            isBold: item.isHeader
            text : item.col02Text
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        NText{
            anchors.left: !item.isHeader ? parent.left : undefined; anchors.leftMargin: !item.isHeader ? 10 * GUISetting.scale : undefined;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: item.isHeader ? parent.horizontalCenter : undefined

            isBold: item.isHeader
            text : item.col03Text
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 2
        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        NText{
            anchors.left: !item.isHeader ? parent.left : undefined; anchors.leftMargin: !item.isHeader ? 10 * GUISetting.scale : undefined;
            anchors.verticalCenter: parent.verticalCenter;
            anchors.horizontalCenter: item.isHeader ? parent.horizontalCenter : undefined

            isBold: item.isHeader
            text : item.col04Text
        }
    }
}
