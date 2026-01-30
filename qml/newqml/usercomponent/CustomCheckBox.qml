import QtQuick 2.0
import QtQuick.Controls 2.14

import FontManager 1.0
import GUISetting 1.0

import TagModel 1.0

Item {
    id: control
    height: 24
    opacity: enabled ? 1 : 0.3
    enabled: viewTag.IsSupport && control.isEnable && viewTag.IsBlock == false && viewTag.IsNotUsed == false
    clip: true

    property alias label : labelComponent

    property TagModel     viewTag  : TagModel{}
    property string       tagValue : viewTag.Value
    property bool         isReadOnly : false
    property bool         isEnable     : true
    property bool         isDirty      : false

    property bool         checked : false

    signal click()

    function updateTagWriteValue()
    {
        viewTag.writeValue(control.checked ? "1" : "0");
    }

    function qmlValueChange()
    {
        var tagCheckValue = control.tagValue === "1" ? true: false;

        isDirty = control.checked !== tagCheckValue
    }

    function tagValueChange()
    {
        if(control.isDirty)
            return;

        if(control.tagValue.length == 0)
        {
            control.checked = false;
        }
        else
        {
            control.checked = control.tagValue === "1";
        }
        control.isDirty = false;
    }

    Connections {
        target: control.viewTag

        function onSignalEventChangedValue(modelValue) {
            control.tagValueChange();
        }
    }

    onTagValueChanged: {
        control.tagValueChange();
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
        text : control.isDirty ? "*" : ""
    }

    Rectangle {
        id : checkIndicator

        width: parent.height * 0.6; height: parent.height * 0.6
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter

        visible: viewTag.IsSupport && viewTag.IsNotUsed == false
        radius: 3
        border.color: "#ECECEC"

        Rectangle {
            width: parent.width - 4
            height: parent.height - 4
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            radius: 2
            color: "#24A7FF"
            visible: control.checked
        }
    }

    CustomLabel {
        id: notSupportIndi
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        visible: viewTag.IsSupport == false || viewTag.IsNotUsed
        text : "Not Support";
    }


    MouseArea{
        id : itemMouseArea

        anchors.fill: parent
        hoverEnabled: control.enabled
        enabled: control.enabled && control.isReadOnly === false
        acceptedButtons: Qt.LeftButton

        onPressed: {
            focus = true
        }

        onClicked: {
            control.checked = !control.checked
            control.qmlValueChange()
            control.click();
        }
    }
}
