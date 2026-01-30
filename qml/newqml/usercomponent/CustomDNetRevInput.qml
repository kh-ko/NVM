import QtQuick 2.0
import QtQuick.Controls 2.5
import FontManager 1.0
import TagModel 1.0

Item {
    id: control
    height: 24
    opacity: enabled ? 1 : 0.3
    enabled: viewTag.IsSupport && control.isEnable && viewTag.IsNotUsed == false
    clip: true

    property alias label : labelComponent

    property TagModel     viewTag  : TagModel{}

    property bool         isEnable : true
    property bool         isDirty  : false


    function updateTagWriteValue()
    {
        if(control.isDirty == false)
            return;

        viewTag.writeMajRevValue(text01Field.text);
        viewTag.writeMinRevValue(text02Field.text);
    }

    function qmlValueChange()
    {
        if((text01Field.text.length < 1 && text02Field.text.length < 1) || ((""+viewTag.MajRev) == text01Field.text && (""+viewTag.MinRev) == text02Field.text) )
        {
            control.isDirty = false;
            return;
        }

        control.isDirty = true;
    }

    function tagValueChange()
    {
        if(control.isDirty)
            return;

        text01Field.text = ""+viewTag.MajRev
        text02Field.text = ""+viewTag.MinRev

        control.isDirty = false;
    }

    Connections {
        target: control.viewTag

        function onSignalEventChangedValue(modelValue){
            tagValueChange()
        }
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

    Item{
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10
        visible: viewTag.IsSupport && viewTag.IsNotUsed == false

        CustomLabel{
            id: dotComponent

            width: 10
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter  : parent.verticalCenter;
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment  : Text.AlignBottom
            text : "."
        }

        BorderImage {
            height: parent.height
            anchors.left: parent.left; anchors.right: dotComponent.left;

            source: "/image/hall-2.png"
            border.left: 6; border.top: 6; border.right: 6; border.bottom: 6
        }

        TextField{
            id : text01Field

            height: parent.height
            anchors.left: parent.left; anchors.right: dotComponent.left;

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

        BorderImage {
            height: parent.height
            anchors.left: dotComponent.right; anchors.right: parent.right;

            source: "/image/hall-2.png"
            border.left: 6; border.top: 6; border.right: 6; border.bottom: 6
        }

        TextField{
            id : text02Field

            height: parent.height
            anchors.left: dotComponent.right; anchors.right: parent.right;

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

    CustomLabel {
        id: notSupportIndi
        height: parent.height
        anchors.left: flagComponent.right; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

        visible: viewTag.IsSupport == false || viewTag.IsNotUsed == true
        text : "Not Support";
    }
}
