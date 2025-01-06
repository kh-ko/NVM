import QtQuick 2.0
import QtQuick.Controls 2.5
import FontManager 1.0
import StrUtil 1.0
import GUISetting 1.0

Item {
    id : control

    property bool  isEexplicitInputMode : false
    property var   stepValue : 0
    property var   minValue : 0
    property var   maxValue : 0
    property var   fixedN   : 0
    property var   padN     : 0
    property bool  isHexMode : false
    property bool  isSpecialFloatNode : false
    property alias textField : _textField
    property string test

    opacity: enabled ? 1 : 0.3

    signal focusOutTextField()
    signal changedValue(var value)
    signal changedText()

    function setFloatValue(value)
    {
        control.textField.text = value.toPrecision(6);
        control.procFloatString();
    }

    function setTextByValue(value)
    {
        if(isHexMode)
        {
            _textField.text = value.toString(16).toUpperCase().padStart(control.padN,'0')
        }
        else if(control.isSpecialFloatNode)
        {
            control.procFloatString();
        }
        else
        {
            var tempStr = value.toFixed(control.fixedN)//.toLocaleString(FontManager.locale, 'f', control.fixedN);
            if(tempStr === "NaN")
                tempStr = "0"
            //tempStr = tempStr.replace(",","")
            //var tempFixedN = StrUtil.realNumberCalcFixedN(tempStr, control.fixedN);
            //tempStr = value.toFixed(tempFixedN)//.toLocaleString(FontManager.locale, 'f', tempFixedN);
            _textField.text = tempStr.padStart(control.padN,'0')// tempStr.replace(",","").padStart(control.padN,'0');
        }
    }

    function setValue(value)
    {
        setTextByValue(value)

        if(isHexMode)
        {
            control.changedValue(parseInt(_textField.text, 16))
        }
        else
        {
            control.changedValue(parseFloat(_textField.text))
        }
    }

    function focusOut()
    {
        _textField.focus = false;
    }

    function procFloatString() {
        var strFloat = control.textField.text;
        var retString;

        // 1) 문자열 -> 숫자로 변환
        var floatVal = parseFloat(strFloat);

        // 2) 변환된 숫자가 유효한지 체크
        if (!isNaN(floatVal)) {
            // 3) toPrecision(prec) 메서드를 이용해 유효 자릿수를 prec로 설정
            retString = floatVal.toPrecision(6);
        } else {
            // 숫자로 변환할 수 없는 경우 "nan"으로 처리
            control.textField.text = "nan";
            return;
        }

        floatVal = parseFloat(retString);

        // 4) 결과 문자열 반환
        control.textField.text = floatVal.toString();;
    }
    BorderImage {
        anchors.fill: parent
        source: "/image/hall-2.png"
        border.left: 6; border.top: 6; border.right: 6; border.bottom: 6
    }

    Item{
        id : upDownBtn
        width: 18 * GUISetting.scale; height: parent.height
        anchors.right: parent.right

        BorderImage {
            width: parent.width + 20; height: parent.height + 20
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter;
            source: "/image/sub-card.png"
            border.left: 15; border.top: 15; border.right: 15; border.bottom: 15
        }

        Rectangle{
            width: parent.width; height: parent.height * 0.5
            anchors.top: parent.top
            color: upMouseArea.containsPress ? "#19000000" : upMouseArea.containsMouse ? "#29000000" : "#00000000"

            Image { anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter; source: "/image/icon-arrow-up.png" }
            MouseArea{ id : upMouseArea; anchors.fill: parent; hoverEnabled: control.enabled; enabled: control.enabled; onClicked: {_textField.upValue()}}
        }

        Rectangle{
            width: parent.width; height: parent.height * 0.5
            anchors.bottom: parent.bottom
            color: downMouseArea.containsPress ? "#19000000" : downMouseArea.containsMouse ? "#29000000" : "#00000000"

            Image { anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter; source: "/image/icon-arrow-down.png" }
            MouseArea{ id : downMouseArea; anchors.fill: parent; hoverEnabled: control.enabled; enabled: control.enabled; onClicked: {_textField.downValue()}}
        }
    }



    TextField{
        property bool isEexplicitInput : false
        id : _textField
        selectByMouse: true

        function getStepValue()
        {
            var idx = 0
            var stepStr = "0"
            var targetIdx = cursorPosition

            if(control.isHexMode)
                return 1

            if(targetIdx !== 0 && (text.charAt(targetIdx - 1) >= '0' &&text.charAt(targetIdx - 1) <= '9')) // 커서 앞에 숫자가 나올 경우
            {
                targetIdx = targetIdx - 1

                for(idx = 0; idx < text.length; idx++)
                {
                    if(text.charAt(idx) == '.')
                    {
                        stepStr = stepStr + '.'
                    }
                    else if(idx == targetIdx)
                    {
                        stepStr = stepStr + '1'
                    }
                    else
                        stepStr = stepStr + '0'
                }
            }
            else if((targetIdx === 0 && (text.charAt(targetIdx) >= '0' &&text.charAt(targetIdx) <= '9')) // 커서가 제일 앞에 있고 뒤에 숫자가 있는경우
                    ||(text.charAt(targetIdx - 1) === '.' && (text.charAt(targetIdx) >= '0' && text.charAt(targetIdx) <= '9'))) // 커서 앞에 '.'이 있고 뒤에 숫자가 있는 경우
            {

                for(idx = 0; idx < text.length; idx++)
                {
                    if(text.charAt(idx) == '.')
                    {
                        stepStr = stepStr + '.'
                    }
                    else if(idx == targetIdx)
                    {
                        stepStr = stepStr + '1'
                    }
                    else
                        stepStr = stepStr + '0'
                }
            }

            return parseFloat(stepStr)
        }

        function upValue()
        {
            var oldCursorPos = text.length - cursorPosition
            var step = getStepValue()
            var value = control.isHexMode ? parseInt(text, 16) + step : parseFloat(text) + step

            if(value > control.maxValue)
                return;

            setTextByValue(value)

            if(control.isHexMode)
            {
                control.changedValue(parseInt(text, 16))
            }
            else
            {
                control.changedValue(parseFloat(text))
            }

            var newPos = text.length - oldCursorPos
            cursorPosition = newPos < 1 ? 1 : newPos > text.length ? text.length : newPos
        }

        function downValue()
        {
            var oldCursorPos = text.length - cursorPosition
            var step = getStepValue()
            var value = control.isHexMode ? parseInt(text, 16) - step : parseFloat(text) - step

            if(value < control.minValue)
                return;

            setTextByValue(value)

            if(control.isHexMode)
            {
                control.changedValue(parseInt(text, 16))
            }
            else
            {
                control.changedValue(parseFloat(text))
            }

            var newPos = text.length - oldCursorPos
            cursorPosition = newPos < 1 ? 1 : newPos > text.length ? text.length : newPos
        }

        width: parent.width - upDownBtn.width; height: parent.height;
        anchors.left: parent.left;

        font.family : FontManager.nanumGothicName
        font.pixelSize : 10 * GUISetting.scale
        bottomPadding : 0; topPadding: 0; leftPadding: 10 * GUISetting.scale; rightPadding: 10 * GUISetting.scale
        verticalAlignment : Text.AlignVCenter; horizontalAlignment : Text.AlignHCenter
        validator: DoubleValidator{}

        text: "0"
        color: "#000000"

        onTextChanged: {
            control.changedText()
        }

        Keys.onReleased:{
            if (event.key === Qt.Key_Return || event.key === Qt.Key_Enter){

                if(isEexplicitInputMode)
                {

                    isEexplicitInput = true;
                }
                focus = false
            }
        }

        onActiveFocusChanged: {
            if(activeFocus === false && isEexplicitInputMode === true && isEexplicitInput == false)
            {
                control.focusOutTextField()
                return;
            }

            isEexplicitInput = false;

            if(activeFocus === false)
            {
                var value = control.isHexMode ? parseInt(text, 16) : parseFloat(text)

                if(value > control.maxValue)
                {
                    value = control.maxValue;
                }
                else if(value < control.minValue)
                {
                    value = control.minValue;
                }

                setTextByValue(value)

                if(control.isHexMode)
                {
                    control.changedValue(parseInt(text, 16))
                }
                else
                {
                    control.changedValue(parseFloat(text))
                }
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
