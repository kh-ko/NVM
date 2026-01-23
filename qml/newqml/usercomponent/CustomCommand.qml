import QtQuick 2.0
import QtQuick.Controls 2.14

import FontManager 1.0
import GUISetting 1.0

import TagModel 1.0

Item {
    id: control
    height: 24
    opacity: enabled ? 1 : 0.3
    enabled: viewTag.IsSupport && control.isEnable
    clip: true

    property alias label : labelComponent

    property TagModel     viewTag  : TagModel{}
    property bool         isEnable     : true

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
}
