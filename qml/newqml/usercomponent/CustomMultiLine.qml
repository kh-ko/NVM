import QtQuick 2.0

import TagModel 1.0

Item {
    id: control
    height: valueBox.height < 24 ? 24 : valueBox.height
    opacity: enabled ? 1 : 0.3
    enabled: viewTag.IsSupport && control.isEnable
    clip: true

    property alias label : labelComponent

    property TagModel     viewTag  : TagModel{}
    property string       tagValue : viewTag.Value
    property bool         isEnable : true

    CustomLabel{
        id: labelComponent
        height: 24

        anchors.left: parent.left; anchors.leftMargin: 10; anchors.top: parent.top;

        text : viewTag.Name
    }

    CustomLabel {
        id: valueBox
        anchors.left: labelComponent.right; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10
        anchors.verticalCenter: parent.verticalCenter; // 수직 중앙 정렬

        lineHeight: 1.2
        wrapMode: Text.Wrap

        text : viewTag.IsSupport
                       ? (control.tagValue ? control.tagValue.replace(/\//g, "\n") : "")
                       : " Not Support"
    }
}
