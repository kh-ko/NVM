import QtQuick 2.0
import QtQuick.Controls 2.5
import FontManager 1.0
import StrUtil 1.0
import GUISetting 1.0

Item {
    id : control

    property alias textField : _textField

    opacity: enabled ? 1 : 0.3

    signal enterClicked()
    signal changedValue(var value)
    signal changedText()

    function setTextByValue(value)
    {
        _textField.text = value
    }

    function setValue(value)
    {
        setTextByValue(value)
        control.changedValue(_textField.text)
    }

    function focusOut()
    {
        _textField.focus = false;
    }

    function focusIn()
    {
        _textField.forceActiveFocus()
        _textField.focus = true;
    }

    BorderImage {
        anchors.fill: parent
        source: "/image/hall-2.png"
        border.left: 6; border.top: 6; border.right: 6; border.bottom: 6
    }

    TextField{
        id : _textField

        width: parent.width; height: parent.height;
        anchors.left: parent.left;

        font.family : FontManager.nanumGothicName
        font.pixelSize : 10 * GUISetting.scale
        bottomPadding : 0; topPadding: 0; leftPadding: GUISetting.margin; rightPadding: GUISetting.margin
        verticalAlignment : Text.AlignVCenter; horizontalAlignment : Text.AlignHCenter

        text: ""
        color: "#000000"

        onTextChanged: {
            control.changedText()
        }

        Keys.onReleased:{
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter){
                focus = false
                control.enterClicked();
            }
        }

        onActiveFocusChanged: {
            if(activeFocus === false)
            {
                setTextByValue(text)
                control.changedValue(text)
            }
            else
            {
                _textField.selectAll()
            }
        }

        onFocusChanged: {

        }

        background: Item{
            anchors.fill: parent
        }
    }
}
