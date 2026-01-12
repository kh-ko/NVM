import QtQuick 2.0
import QtQuick.Controls 2.14
import FontManager 1.0
import PmValveItemModel 1.0

Item {
    id: control
    height: 24
    opacity: enabled ? 1 : 0.3
    enabled : !viewItemModel.IsBlock && isEnable
    visible: viewItemModel.IsSupport

    property alias label : labelComponent

    readonly property int emptyIndex : 0
    readonly property int unKnownIndex : 1
    property PmValveItemModel viewItemModel : PmValveItemModel{}
    property bool isEnable : true
    property bool isDirty : false
    property bool isError : false
    property bool isWriteProc : false

    property bool isUpdateByModel : false

    function remoteSync()
    {
        isDirty = false; isError = false;
        viewItemModel.remoteSync();
    }

    function commit()
    {
        if(comboBox.currentIndex == unKnownIndex || comboBox.currentIndex == emptyIndex)
            isWriteProc = viewItemModel.commit("");
        else
            isWriteProc = viewItemModel.commit(""+comboBox.currentValue);
    }

    function updateValueByModel()
    {
        if(isWriteProc)
        {
            isWriteProc = false;
            if((comboBox.currentIndex == emptyIndex && viewItemModel.Value.length === 0) || (parseInt(viewItemModel.Value) === comboBox.currentValue))
            {
                control.isError = false;
            }
            else
            {
                control.isError = true;
            }
            control.isDirty = false;
        }

        if(isError || isDirty)
            return;

        isUpdateByModel = true;

        if(viewItemModel.Value.length == 0)
        {
            comboBox.currentIndex = emptyIndex;
        }
        else
        {
            var tempIndex = comboBox.indexOfValue(parseInt(viewItemModel.Value));
            comboBox.currentIndex = tempIndex < 0 ? unKnownIndex : tempIndex;
        }
        isUpdateByModel = false;
    }

    function inValueChange()
    {
        if(isUpdateByModel)
            return;

        if(comboBox.currentIndex == unKnownIndex)
        {
            comboBox.currentIndex = emptyIndex;
        }

        var inValue = comboBox.currentValue;

        if(comboBox.currentIndex == emptyIndex && viewItemModel.Value.length == 0)
            isDirty = false;
        else
            isDirty = !Object.is(parseInt(viewItemModel.Value), inValue);

        control.isError = false;
    }

    Connections {
        target: control.viewItemModel

        function onSignalEventChangedValue(modelValue) {
            control.updateValueByModel()
        }
    }

    PmLabel{
        id: labelComponent

        anchors.left: parent.left; anchors.leftMargin: 10;
        anchors.verticalCenter: parent.verticalCenter;

        text : viewItemModel.Name
    }

    PmLabel{
        id: flagComponent

        width: 10
        anchors.left: labelComponent.right;
        anchors.verticalCenter: parent.verticalCenter;

        color : control.isError ? "#FF0000" : "#24A7FF"
        text : control.isDirty || control.isError ? "*" : ""
    }

    ComboBox {
        id: comboBox
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        model : viewItemModel.modeOptions
        textRole : "text"
        valueRole : "value"

        onActivated: {
            control.inValueChange()
        }

        delegate: ItemDelegate {
            width: comboBox.width
            height: 24

            contentItem:Rectangle{
                anchors.fill: parent
                color : highlighted ? "#24A7FF" : "#FFFFFF"

                PmLabel {
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
            PmLabel {
                width: comboBox.width - /*indicator.width*/ - 20
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
}
