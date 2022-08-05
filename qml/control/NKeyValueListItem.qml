import QtQuick 2.0
import QtQuick.Layouts 1.3
import "./."
import FontManager 1.0
import ValveEnumDef 1.0
import GUISetting 1.0

Rectangle{
    id : control

    property string iconSource : ""
    property string keyText
    property string valueText : ""
    property bool   isHide : valueText === ""

    height: 0; width: parent.width
    color: "#E4E4E4"
    clip: true

    states: [
        State {
            name: "show"
            when: control.isHide == false
            PropertyChanges { target: control; height : GUISetting.keyvalue_nor_height}
        }
    ]

    transitions: Transition
    {
        id : trans
        from: ""
        to: "show"
        reversible: true
        ParallelAnimation {
            NumberAnimation { target: control; properties: "height"; duration: 250; easing.type: Easing.InOutQuad}
        }
    }

    NText{
        id : keyContainer
        width: (parent.width - (GUISetting.margin * 3)) / 2
        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
        text : control.keyText
        color : "#24292E"
        elide: Text.ElideRight

    }

    Image{
        id : image
        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
        anchors.verticalCenter: parent.verticalCenter; anchors.left: keyContainer.right; anchors.leftMargin: GUISetting.margin;
        source: control.iconSource
        visible: control.iconSource !== ""
    }

    NText{
        id : valueContainer

        anchors.verticalCenter: parent.verticalCenter; anchors.left: image.visible ? image.right : keyContainer.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        text : control.valueText
        isBold: true;
        elide: Text.ElideRight
    }
}
