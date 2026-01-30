import QtQuick 2.0

import TagModel 1.0

Item {
    id: control
    height: 24
    opacity: enabled ? 1 : 0.3
    enabled: viewTag.IsSupport && control.isEnable && viewTag.IsNotUsed == false
    clip: true

    property alias label : labelComponent

    property TagModel     viewTag  : TagModel{}
    property string       tagValue : viewTag.Value
    property bool         isEnable : true
    property int          selValue : 0

    onTagValueChanged: {

        selValue = parseInt(viewTag.Value)

        valueBox.text = viewTag.modeOptions.getTextByValue(parseInt(viewTag.Value));
    }

    CustomLabel{
        id: labelComponent

        anchors.left: parent.left; anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;

        text : viewTag.Name
    }
    CustomLabel{
        id: flagComponent

        width: 10
        anchors.left: labelComponent.right;
        anchors.verticalCenter: parent.verticalCenter;

        color : "#FF0000"
        text : ""
    }

    CustomLabel {
        id: valueBox
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        visible: viewTag.IsSupport && viewTag.IsNotUsed == false
    }

    CustomLabel {
        id: notSupportIndi
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        visible: viewTag.IsSupport == false || viewTag.IsNotUsed
        text : "Not Support";
    }
}
