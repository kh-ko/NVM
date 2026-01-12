import QtQuick 2.0
import QtQuick.Controls 2.5
import FontManager 1.0
import PmValveItemModel 1.0

Item {
    id : control
    height: 24
    opacity: enabled ? 1 : 0.3
    enabled : !viewItemModel.IsBlock && isEnable
    visible: viewItemModel.IsSupport

    property alias label : labelComponent
    property PmValveItemModel viewItemModel : PmValveItemModel{}
    property int min : parseInt(viewItemModel.Min)
    property int max : parseInt(viewItemModel.Max)
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
        isWriteProc = viewItemModel.commit(textField.text);
    }

    function updateValueByModel()
    {
        if(isWriteProc)
        {
            isWriteProc = false;
            if(Object.is(parseInt(viewItemModel.Value), parseInt(textField.text)))
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
        textField.text = viewItemModel.Value
        isUpdateByModel = false;
    }

    function inValueChange()
    {
        if(isUpdateByModel)
            return;

        var inValue = parseInt(textField.text);

        if(min > inValue)
        {
            textField.text = min;
        }
        else if(max < inValue )
        {
            textField.text = max;
        }

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

    BorderImage {
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        source: "/image/hall-2.png"
        border.left: 6; border.top: 6; border.right: 6; border.bottom: 6
    }

    TextField{
        id : textField

        height: parent.height
        anchors.left: labelComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        font.family : FontManager.nanumGothicName
        font.pixelSize : 10
        bottomPadding : 0; topPadding: 0; leftPadding: 10; rightPadding: 10
        verticalAlignment : Text.AlignVCenter; horizontalAlignment : Text.AlignHCenter
        validator: IntValidator{}

        text: ""
        color: "#000000"

        onTextChanged: {
            control.inValueChange();
        }

        Keys.onReleased:{
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter){
            }
        }

        onActiveFocusChanged: {
            if(activeFocus === true)
            {
                selectAll();
                return;
            }
        }

        onFocusChanged: {

        }

        background: Item{
            anchors.fill: parent
        }
    }
}
