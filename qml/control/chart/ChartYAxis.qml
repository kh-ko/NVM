import QtQuick 2.12
import FontManager 1.0

Item {
    id : control

    property var   graphData     : null

    property var   unitText       : ""
    property var   yAxisItemMargin   : 10
    property var   yAxisLineWidth    : 2
    property var   yAxisLineColor    : "#4dFFFFFF"
    property var   yAxisSubLineColor : "#4dFFFFFF"
    property var   yAxisItemColor    : "#9e9e9e"
    property var   yAxisItemFontSize : 20
    property var   yAxisItemHieght   : 30
    property var   yAxisItemWidth    : 100
    property var   yAxisDivideCount  : 1
    property var   isRightYAxis      : false

    property var   isCenterZero      : false
    property var   displayFactor     : 1
    property var   displayFixedN     : 0

    //visible: control.yAxisDivideCount > 1

    function log10(x) {
      return Math.log(x) / Math.log(10);
    }

    function clear()
    {
        for(var i = 0; i < yAxisItemList.children.length; i ++)
        {
            yAxisItemList.children[i].destroy();
        }
    }

    function draw()
    {
        clear();

        var yRange = graphData.mEndY - graphData.mStartY;
        var gab = Math.ceil(yRange / yAxisDivideCount)
        gab = gab * displayFactor
        gab = gab * Math.pow(10, displayFixedN)
        gab = Math.ceil(gab)
        gab = gab / Math.pow(10, displayFixedN)
        gab = gab / displayFactor

        if(graphData.mIsLogGraph)
        {
            control.yAxisDivideCount = graphData.mEndY - graphData.mStartY + 1
            for(var logLineValue = graphData.mStartY; logLineValue <= graphData.mEndY; logLineValue ++)
            {
                drawItem(logLineValue);
                drawLogSubLine(logLineValue);
            }
        }
        else if(isCenterZero)
        {
            if((control.yAxisDivideCount %2 !== 0) || (-1 * graphData.mStartY) !== (yRange / 2))
            {
                return;
            }

            drawItem(0);

            for(var i = 1; i < yAxisDivideCount / 2; i++)
            {
                drawItem(gab * i)  //yLine.createObject(control, {"height" : control.yAxisItemHieght, "value" : gab * i})
            }
            for(var j = 1; j < yAxisDivideCount / 2; j++)
            {
                drawItem(-1 * (gab * i)) // yLine.createObject(control, {"height" : control.yAxisItemHieght, "value" : -1 * gab * j})
            }
        }
        else
        {
            var lineValue = graphData.mStartY;

            if(gab <= 0)
                return;

            while(lineValue <= graphData.mEndY)
            {
                drawItem(lineValue)

                lineValue += gab;
            }
        }
    }

    function drawItem(value)
    {
        yLine.createObject(yAxisItemList, {"height" : control.yAxisItemHieght, "value" : value})
    }

    function drawLogSubLine(value)
    {
        if(value === 0)
            return;

        var subStartValue = Math.pow(10, value - 1)
        var subValueUnit = subStartValue

        for(var i = 0; i < 10; i ++)
        {
            var lineValue = subStartValue + (i * subValueUnit);

            lineValue = log10(lineValue);

            yLogSubLine.createObject(yAxisItemList, {"height" : control.yAxisItemHieght, "value" : lineValue})
        }
    }

    Text{
        id : unitLabel

        anchors.top: parent.top; anchors.topMargin: 0;
        anchors.left: control.isRightYAxis  ? undefined    : parent.left; anchors.leftMargin : control.isRightYAxis ? undefined : 0
        anchors.right: control.isRightYAxis ? parent.right : undefined  ; anchors.rightMargin: control.isRightYAxis ? 0         : undefined

        color : control.yAxisItemColor

        font.family: FontManager.nanumGothicName; font.pixelSize: control.yAxisItemFontSize;
        text : control.unitText
    }

    Item{
        id : yAxisItemList

        anchors.fill: parent
    }

    Component{
        id : yLine;

        Item{
            property var value

            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * ((value - graphData.mStartY) / (graphData.mEndY - graphData.mStartY)));
            anchors.left:parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

            visible: (-1*anchors.verticalCenterOffset >= 0) && (-1*anchors.verticalCenterOffset <= parent.height)

            Text{
                id : yAxisItem
                height: parent.height; width: control.yAxisItemWidth - control.yAxisItemMargin;
                anchors.right: control.isRightYAxis ? parent.right : undefined; anchors.rightMargin: control.isRightYAxis ? 0 : undefined;
                anchors.left: control.isRightYAxis ? undefined : parent.left; anchors.leftMargin: control.isRightYAxis ? undefined : 0;

                verticalAlignment: Text.AlignVCenter; horizontalAlignment: control.isRightYAxis ? Text.AlignLeft : Text.AlignRight;
                color : control.yAxisItemColor
                elide: Text.ElideRight

                font.family: FontManager.nanumGothicName; font.pixelSize: control.yAxisItemFontSize;
                text : graphData.mIsLogGraph ? (Math.pow(graphData.mLogBase,value) * control.displayFactor).toLocaleString(FontManager.locale, 'f', control.displayFixedN) : (value * control.displayFactor).toLocaleString(FontManager.locale, 'f', control.displayFixedN)
            }

            Rectangle{
                height:control.yAxisLineWidth
                anchors.verticalCenter: parent.verticalCenter;
                anchors.left:control.isRightYAxis ? parent.left : yAxisItem.right; anchors.leftMargin: control.isRightYAxis ? 0 :control.yAxisItemMargin;
                anchors.right: control.isRightYAxis ? yAxisItem.left : parent.right; anchors.rightMargin:  control.isRightYAxis ? control.yAxisItemMargin : 0

                color : control.yAxisLineColor
            }
        }
    }

    Component{
        id : yLogSubLine;

        Item{
            property var value

            anchors.verticalCenter: parent.bottom;
            anchors.verticalCenterOffset: -1 * (parent.height * ((value - graphData.mStartY) / (graphData.mEndY - graphData.mStartY)));
            anchors.left:parent.left; anchors.leftMargin: 0; anchors.right: parent.right; anchors.rightMargin: 0

            visible: (-1*anchors.verticalCenterOffset >= 0) && (-1*anchors.verticalCenterOffset <= parent.height)

            Rectangle{
                height:control.yAxisLineWidth; width: control.yAxisItemMargin;
                anchors.verticalCenter: parent.verticalCenter;
                anchors.right: control.isRightYAxis ? parent.right : undefined; anchors.rightMargin: control.isRightYAxis ? control.yAxisItemWidth - control.yAxisItemMargin : undefined;
                anchors.left: control.isRightYAxis ? undefined : parent.left; anchors.leftMargin: control.isRightYAxis ? undefined : control.yAxisItemWidth - control.yAxisItemMargin;
                color : control.yAxisSubLineColor
            }
        }
    }

}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
