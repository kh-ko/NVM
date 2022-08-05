import QtQuick 2.0
import GUISetting 1.0

Item {
    id : control

    property alias textBox : _textBox
    property alias text :  _text
    property bool  isOn : false
    width: parent.width; height: _textBox.height;

    signal clicked()

    opacity: enabled ? 1 : 0.3

    Rectangle{
        id : _textBox

        height: GUISetting.exbtnitem_height; width: parent.width;

        Rectangle{
            width: GUISetting.exbtnitem_on_width; height: GUISetting.exbtnitem_on_height
            anchors.right: parent.right; anchors.rightMargin: GUISetting.right_margin; anchors.verticalCenter: parent.verticalCenter

            visible: control.isOn
            radius: (width / 2) + 1
            color: "#24A7FF"
        }

        NText {
            id: _text
            anchors.left: parent.left; anchors.leftMargin: GUISetting.exbtnitem_left_margin; anchors.verticalCenter: parent.verticalCenter
        }
        MouseArea{
            anchors.fill: parent

            onClicked: {
                control.clicked()
            }
        }
    }
}
