import QtQuick 2.0
import QtQuick.Controls 2.5
import FontManager 1.0
import ViewTagModel 1.0

Item {
    id : control
    height: 24
    opacity: enabled ? 1 : 0.3
    enabled: viewTag.IsSupport && control.isEnable
    clip: true

    property alias label           : labelComponent

    property ViewTagModel viewTag  : ViewTagModel{}
    property string       tagValue : viewTag.Value
    //property int          min      : parseInt(viewTag.Min)
    //property int          max      : parseInt(viewTag.Max)

    property bool isEnable         : true
    property bool isDirty          : false

    function updateTagWriteValue()
    {
        if(textField.text.length < 1 || tagValue == textField.text)
            return;

        viewTag.writeValue(textField.text);
    }

    function qmlValueChange()
    {
        if(textField.text.length < 1 || tagValue == textField.text)
        {
            control.isDirty = false;
            return;
        }

        control.isDirty = true;

        //var inValue = parseInt(textField.text);

        //if(min > inValue)
        //{
        //    textField.text = control.min;
        //}
        //else if(max < inValue )
        //{
        //    textField.text = control.max;
        //}
    }

    function tagValueChange()
    {
        textField.text = control.tagValue
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

        color : "#FF0000" /* control.isDirty ?  :  "#24A7FF" */
        text : control.isDirty ? "*" : ""
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
            control.qmlValueChange();
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
