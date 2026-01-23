import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.3
import FontManager 1.0

Rectangle{
    id : control

    property real progress : 0

    x:0; anchors.bottom: parent.bottom; width : parent.width; height: 20; color: "#E4E4E4"

    RowLayout{
        anchors.fill: parent

        Item{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
        }
        Item{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

            Rectangle{
                visible: control.progress !== 1

                anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter;
                color: "#24A7FF"

                height: parent.height * 0.5;  width: (parent.width - 10) * control.progress
            }
        }
    }
}
