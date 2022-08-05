import FontManager 1.0
import QtQuick 2.12
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import MathUtil 1.0
import StrUtil 1.0

Item{
    property var topPadding        : 0
    property var bottomPadding     : 0
    property var labelWidth        : -1
    //property var lineWidth       : 6
    property var isRightMode       : false
    property var isExtendLine      : false
    property var minGapHeight      :  4.0
    property var minLabelGapHeight :  20.0
    property var lineColor         : "#39000000"
    property var textColor         : "#CC000000"
    property var lineHeight        : 2

    property real from     : 0
    property real to       : 10

    property var fixedN    : -1

    property var isLogType : false

    property var availableHieght : height - topPadding - bottomPadding
    property var labelGapHeight  : 0

    id : control

    clip: true

    signal changedValue(var value)

    function calcExp(minGapValue)
    {
        var expIdx = 0;
        var retExpValue = 1;
        var strValue = minGapValue.toFixed(15)

        if(minGapValue < 1)
        {
            for(expIdx = 0; expIdx < strValue.length; expIdx++)
            {
                if(strValue.charAt(expIdx) === '0')
                {
                    retExpValue = retExpValue * 10;
                }
                else if(strValue.charAt(expIdx) !== '0' && strValue.charAt(expIdx) !== '.')
                {
                    break;
                }
            }
        }
        else if(minGapValue >= 10)
        {
            var dotIdx = strValue.indexOf(".");

            if(dotIdx === -1)
            {
               retExpValue =  Math.pow(10, -1 * (strValue.length - 1));
            }
            else
            {
                retExpValue =  Math.pow(10, -1 * (dotIdx - 1));
            }
        }
        else
            return 1;

        return retExpValue
    }

    function calLineGapValue(value, expValue)
    {
        value = value * expValue;

        if(value === 1)
        {
            return ( 1 / expValue )
        }
        else if(value <= 2)
        {
            return ( 2 / expValue )
        }
        else if(value <= 2.5)
        {
            return ( 2.5 / expValue )
        }
        else if(value <= 5)
        {
            return ( 5 / expValue )
        }
        else
        {
            return ( 10 / expValue )
        }
    }

    function calLabelIdxGap(lineGapValue, lineGapHeight)
    {
        if(lineGapValue === 1)
        {
            if(lineGapHeight > minLabelGapHeight)
            {
                return 1
            }
            else if(lineGapHeight * 2 > minLabelGapHeight)
            {
                return 2
            }

            return 5

        }
        else if(lineGapValue <= 2)
        {
            if(lineGapHeight > minLabelGapHeight)
            {
                return 1
            }

            return 5

        }
        else if(lineGapValue <= 2.5)
        {
            if(lineGapHeight > minLabelGapHeight)
            {
                return 1
            }
            else if((lineGapHeight * 2) > minLabelGapHeight)
            {
                return 2
            }

            return 4
        }
        else if(lineGapValue <= 5)
        {
            if(lineGapHeight > minLabelGapHeight)
            {
                return 1
            }
            else if((lineGapHeight * 2) > minLabelGapHeight)
            {
                return 2
            }
            else if((lineGapHeight * 4) > minLabelGapHeight)
            {
                return 4
            }
            return 5
        }

        if(lineGapHeight > minLabelGapHeight)
        {
            return 1
        }
        else if((lineGapHeight * 2) > minLabelGapHeight)
        {
            return 2
        }

        return 5
    }

    function clear()
    {
        for(var i = 0; i < yLineBox.children.length; i++)
        {
            yLineBox.children[i].destroy();
        }

        for(var j = 0; j < yLabelBox.children.length; j++)
        {
            yLabelBox.children[j].destroy();
        }
    }

    function calFixedValue(value, expValue)
    {
        var fixedValue = MathUtil.log10(expValue)

        value = value * expValue;

        if(value > 2 && value <= 2.5)
        {
            fixedValue =  fixedValue + 1;
        }

        if(fixedValue < 0)
        {
            fixedValue = 0;
        }

        if(fixedValue < control.fixedN)
            fixedValue = control.fixedN

        return fixedValue;

    }

    function calcLog()
    {
        var yPosValue;
        var yLinearSubPosValue;
        var i,j;
        var fixedValue;
        var label;

        if(from === 0 || to === 0)
        {
            clear()
            return;
        }

        var rangeWidth = MathUtil.log10(to) -MathUtil.log10(from)
        var lineGapValue = Math.ceil(rangeWidth * ( minLabelGapHeight / control.availableHieght));
        var lineGapHeight = control.availableHieght * (lineGapValue / rangeWidth)

        clear()

        for(i = 0, yPosValue = MathUtil.log10(from); yPosValue < MathUtil.log10(to); i++, yPosValue = MathUtil.floor(yPosValue + 1))
        {
            addLine(yPosValue, true)

            if(i !== 0)
            {
                label = "" + Math.pow(10, yPosValue)
                fixedValue = yPosValue < 0 ? -1 * yPosValue : 0
                addLabel(yPosValue, fixedValue, false, label)
            }
            else
            {
                label = ("" + from)
                fixedValue = StrUtil.realNumberCalcFixedN(label, control.fixedN)
                addLabel(yPosValue, fixedValue, true, label)
            }

            var linearGapValue = Math.pow(10,MathUtil.floor(yPosValue))

            for(j = 0, yLinearSubPosValue = linearGapValue + linearGapValue; j < 8; yLinearSubPosValue += linearGapValue, j++)
            {
                if(yLinearSubPosValue < to)
                 addLine(MathUtil.log10(yLinearSubPosValue), false)
            }
        }

        addLine(MathUtil.log10(to), true)
        label = ("" + to)
        fixedValue = StrUtil.realNumberCalcFixedN(label, control.fixedN)
        addLabel(MathUtil.log10(to), fixedValue, true, label)
    }

    function calcLinear()
    {
        clear()

        if(control.availableHieght < 1)
        {
            return;
        }

        var rangeWidth = (to - from)
        var templineGapValue = (rangeWidth * ( minGapHeight / control.availableHieght));
        var expValue = calcExp(templineGapValue)

        var lineGapValue = calLineGapValue(templineGapValue, expValue)
        var lineGapHeight = control.availableHieght * (lineGapValue / rangeWidth)

        var labelIdxGap = calLabelIdxGap(templineGapValue, lineGapHeight)
        var fixedValue  = calFixedValue(templineGapValue, expValue)

        labelGapHeight = lineGapHeight * labelIdxGap;

        addLine(from, true, true)
        addLabel(from, fixedValue, true)

        for(var labelIdx = 0, yPosValue = lineGapValue * Math.ceil(from / lineGapValue); yPosValue < to; yPosValue += lineGapValue, labelIdx++)
        {

            if((labelIdx % labelIdxGap) == 0)
            {
                addLine(yPosValue, true, false)
                addLabel(yPosValue, fixedValue, false)
            }
            else
            {
                addLine(yPosValue, false, false)
            }
        }

        addLine(to, true, true)
        addLabel(to, fixedValue, true)
    }

    function calc()
    {
        if(isLogType)
            calcLog()
        else
            calcLinear()
    }

    function addLine(value, isMainLine, forceDraw)
    {
        var rangeWidth
        var fromValue

        if(isLogType)
        {
            rangeWidth = MathUtil.log10(to) - MathUtil.log10(from)
            fromValue = MathUtil.log10(from)
        }
        else
        {
            rangeWidth = (to - from)
            fromValue = from
        }

        var yOffset = control.availableHieght * ((value - fromValue)/ rangeWidth)

        if(forceDraw === false)
        {
            if((control.availableHieght - yOffset) < minGapHeight)
                return;

            if(yOffset < minGapHeight)
                return;
        }

        yLine.createObject(yLineBox, {"yOffset": yOffset, "isMainLine":isMainLine})
    }

    function addLabel(value, fixedValue, forceDraw, labelValue = 0)
    {
        var rangeWidth
        var fromValue

        if(isLogType)
        {
            rangeWidth =MathUtil.log10(to) - MathUtil.log10(from)
            fromValue = MathUtil.log10(from)
        }
        else
        {
            rangeWidth = (to - from)
            fromValue = from
        }

        var yOffset = control.availableHieght * ((value - fromValue)/ rangeWidth)
        var strYLabel

        if(isLogType)
        {
            strYLabel = labelValue

            if( !forceDraw )
            {
                if((control.availableHieght - yOffset) < (minLabelGapHeight -1))
                {
                    return;
                }

                if(yOffset < (minLabelGapHeight - 1))
                    return;
            }
        }
        else
        {
            strYLabel = (value).toFixed(fixedValue)

            if( !forceDraw )
            {
                if((control.availableHieght - yOffset) < (labelGapHeight -1))
                {
                    return;
                }

                if(yOffset < (labelGapHeight - 1))
                    return;
            }
        }



        //strYLabel = strYLabel.replaceAll(',','')
        yLabel.createObject(yLabelBox, {"yOffset": yOffset, "text" : strYLabel})

    }

    onIsLogTypeChanged: {
        control.calc()
    }

    onAvailableHieghtChanged: {
        control.calc()
    }

    onToChanged: {
        control.calc()
    }

    onFromChanged: {
        control.calc()
    }

    onFixedNChanged: {
        control.calc()
    }

    Item{
        id : yLabelBox

        width: isExtendLine ? labelWidth : parent.width - 8

        anchors.top    : parent.top   ; anchors.topMargin   : control.topPadding
        anchors.bottom : parent.bottom; anchors.bottomMargin: control.bottomPadding

        anchors.left   : !control.isRightMode ? parent.left : undefined
        anchors.right  : !control.isRightMode ? undefined   : parent.right
    }

    Item{
        id : yLineBox

        width: isExtendLine ? parent.width - labelWidth - 2 :  6

        anchors.top    : parent.top   ; anchors.topMargin   : control.topPadding
        anchors.bottom : parent.bottom; anchors.bottomMargin: control.bottomPadding

        anchors.right  : !control.isRightMode ? parent.right : undefined
        anchors.left   : !control.isRightMode ? undefined    : parent.left
    }

    Component{
        id : yLabel

        NText{
            property var yOffset

            width: parent.width;
            anchors.verticalCenter: parent.bottom; anchors.verticalCenterOffset: -1 * yOffset
            color: control.textColor;
            horizontalAlignment: control.isRightMode ? Text.AlignLeft : Text.AlignRight
            isBold: true
            text: strYValue
        }
    }



    Component{
        id : yLine


        Rectangle
        {
            property var yOffset
            property var isMainLine

            width : isMainLine ? parent.width : 4; height: control.lineHeight;

            anchors.left        : !control.isRightMode ? parent.left        : undefined
            anchors.leftMargin  : !control.isRightMode ? isMainLine ? 0 : 2 : undefined
            anchors.right       : !control.isRightMode ? undefined          : parent.right
            anchors.rightMargin : !control.isRightMode ? undefined          : isMainLine ? 0 : 2

            anchors.verticalCenter: parent.bottom; anchors.verticalCenterOffset: -1 * yOffset

            color: control.lineColor;
        }
    }

    Component.onCompleted : {
        control.calc()
    }
}

