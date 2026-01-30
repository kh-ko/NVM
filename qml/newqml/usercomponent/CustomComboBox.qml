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
    property int          selValue
    property int          selIndex

    property int          emptyIndex   : 0
    property int          unKnownIndex : 1
    property bool         isEnable     : true
    property bool         isDirty      : false

    function updateTagWriteValue()
    {
        if(comboBox.currentIndex == emptyIndex || comboBox.currentIndex == unKnownIndex)
            return;

        var inValue = comboBox.currentValue;

        viewTag.writeValue(""+comboBox.currentValue);
    }

    function qmlValueChange()
    {
        if(comboBox.currentIndex == unKnownIndex || comboBox.currentIndex == emptyIndex)
        {
            control.isDirty = false;
            comboBox.currentIndex = emptyIndex;
            return;
        }

        control.selValue = comboBox.currentValue;

        isDirty = !Object.is(parseInt(tagValue), control.selValue);
    }

    function tagValueChange()
    {
        if(control.isDirty)
            return;

        if(control.tagValue.length == 0)
        {
            comboBox.currentIndex = emptyIndex;
        }
        else
        {
            var tempIndex = comboBox.indexOfValue(parseInt(control.tagValue));
            comboBox.currentIndex = tempIndex < 0 ? unKnownIndex : tempIndex;
        }

        control.selValue = comboBox.currentValue;
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

    ComboBox {
        id: comboBox
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        visible: viewTag.IsSupport && viewTag.IsNotUsed == false
        model : viewTag.modeOptions
        textRole : "text"
        valueRole : "value"

        onActivated: {
            control.qmlValueChange()
        }

        delegate: ItemDelegate {
            width: comboBox.width
            height: 24

            contentItem:Rectangle{
                anchors.fill: parent
                color : highlighted ? "#24A7FF" : "#FFFFFF"

                CustomLabel {
                    anchors.left: parent.left; anchors.leftMargin: 10
                    width: parent.width - 20; height: parent.height
                    text: model.text
                }
            }
            highlighted: comboBox.highlightedIndex === index
        }

        indicator: Item{
            x : comboBox.width - width
            y : 0
            width: 18; height: parent.height

            BorderImage {
                width: parent.width + 20; height: parent.height + 20
                anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter;
                source: "/image/sub-card.png"
                border.left: 15; border.top: 15; border.right: 15; border.bottom: 15
            }

            Rectangle{
                width: parent.width; height: parent.height
                anchors.bottom: parent.bottom
                color: comboBox.pressed ? "#19000000" : comboBox.hovered ? "#29000000" : "#00000000"

                Image { anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter; source: "/image/icon-arrow-down.png" }
            }
        }

        contentItem: Item{
            CustomLabel {
                width: comboBox.width - 40
                anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter

                text: comboBox.displayText
            }
        }

        background: BorderImage {
            source: "/image/hall-2.png"
            border.left: 6; border.top: 6; border.right: 6; border.bottom: 6
        }


        popup: Popup {
            y: comboBox.height - 1
            scale: GUISetting.scale
            transformOrigin: Item.TopLeft;
            width: comboBox.width
            implicitHeight: contentItem.implicitHeight > 200 ? 200 :contentItem.implicitHeight
            padding: 1

            contentItem: ListView {
                clip: true
                implicitHeight: contentHeight
                model: comboBox.popup.visible ? comboBox.delegateModel : null
                currentIndex: comboBox.highlightedIndex

                ScrollIndicator.vertical: ScrollIndicator { }
            }

            background: Rectangle {
                border.color: "#888888"
                radius: 2
            }
        }
    }

    CustomLabel {
        id: notSupportIndi
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        visible: viewTag.IsSupport == false || viewTag.IsNotUsed
        text : "Not Support";
    }

}
