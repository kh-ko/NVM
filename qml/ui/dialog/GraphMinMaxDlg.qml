import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var    body : null
    property string strUnit : "torr"
    property real   minPressureChart
    property real   maxPressureChart
    property int    pressureFixedN
    property bool   isPressureAutoScale
    property bool   isPressureErr : false
    property string errMinOver : qsTr("Too big min value.")

    titleText   : qsTr("Pressure graph settings(scale)")
    progress    : 100
    strStatus   : ""
    errMsg      : ""
    errMsg2     : ""
    access      : ValveEnumDef.ACCESS_REMOTE
    isRS232Test : false
    isEdit      : false
    isModal     : false

    signal signalChangedMinMax(real min, real max)

    function apply()
    {
        var minPressureValue = parseFloat(body.pressureMin.textField.text )
        var maxPressureValue = parseFloat(body.pressureMax.textField.text )
        if(minPressureValue >= maxPressureValue )
        {
            errMsg = errMinOver
            isPressureErr = true;
        }
        else
        {
            dialog.signalChangedMinMax(minPressureValue,maxPressureValue);
            dialog.close();
        }
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias pressureMin            : _pressureMin
            property alias pressureMax            : _pressureMax

            property real  guiScale                 : GUISetting.scale

            height: (GUISetting.line_margin + pressureMinMaxItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
                  //+ (GUISetting.line_margin + positionMinMaxItem.height)

            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            Component.onCompleted: {
                _pressureMin.setValue(dialog.minPressureChart)
                _pressureMax.setValue(dialog.maxPressureChart)
            }

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : pressureMinMaxItem

                height: (GUISetting.margin + pressureMinMaxTitle.height)
                        + (GUISetting.margin + _pressureMin.height)
                        + (GUISetting.margin + _pressureMax.height) + GUISetting.margin;
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : pressureMinMaxTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Min/Max")
                }

                NText{
                    id : minLabel
                    anchors.verticalCenter: _pressureMin.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                    width: 30 * GUISetting.scale
                    text : qsTr("min")
                }

                NInputNumber{
                    id : _pressureMin
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: pressureMinMaxTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: minLabel.right; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.isPressureAutoScale == false

                    textField.validator: DoubleValidator{}
                    textField.color: dialog.isPressureErr ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0; maxValue: 100000000
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureMin.verticalCenter; anchors.left: _pressureMin.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : dialog.strUnit
                }

                NText{
                    id : maxLabel
                    anchors.verticalCenter: _pressureMax.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                    width: 30 * GUISetting.scale
                    text : qsTr("max")
                }

                NInputNumber{
                    id : _pressureMax
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _pressureMin.bottom; anchors.topMargin: GUISetting.margin; anchors.left: minLabel.right; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.isPressureAutoScale == false

                    textField.validator: DoubleValidator{}
                    textField.color: dialog.isPressureErr ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0; maxValue: 100000000
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureMax.verticalCenter; anchors.left: _pressureMax.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : dialog.strUnit
                }
            }

            //Rectangle{
            //    id : positionMinMaxItem
            //
            //    height: (GUISetting.margin + positionMinMaxTitle.height)
            //            + (GUISetting.margin + _positionMin.height)
            //            + (GUISetting.margin + _positionMax.height) + GUISetting.margin;
            //    anchors.top: pressureMinMaxItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;
            //
            //    color: "#FFFFFF"
            //
            //    NText{
            //        id : positionMinMaxTitle
            //        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
            //        isBold: true
            //        text : qsTr("Position Min/Max")
            //    }
            //
            //    NText{
            //        id : positionMinLabel
            //        anchors.verticalCenter: _positionMin.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
            //        width: 30 * GUISetting.scale
            //        text : qsTr("Min")
            //    }
            //
            //    NInputNumber{
            //        id : _positionMin
            //        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
            //        anchors.top: positionMinMaxTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: positionMinLabel.right; anchors.leftMargin: GUISetting.margin
            //
            //        textField.validator: IntValidator{}
            //        textField.color: "#000000"
            //        stepValue : 0.0001; minValue: 0; maxValue: 10000
            //        fixedN : 0
            //
            //        onChangedText: {
            //        }
            //    }
            //
            //    NText{
            //        id : positionMaxLabel
            //        anchors.verticalCenter: _positionMax.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
            //        width: 30 * GUISetting.scale
            //        text : qsTr("Max")
            //    }
            //
            //    NInputNumber{
            //        id : _positionMax
            //        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
            //        anchors.top: _positionMin.bottom; anchors.topMargin: GUISetting.margin; anchors.left: positionMaxLabel.right; anchors.leftMargin: GUISetting.margin
            //
            //        textField.validator: IntValidator{}
            //        textField.color: "#000000"
            //        stepValue : 0.0001; minValue: 0; maxValue: 10000
            //        fixedN : 0
            //
            //        onChangedText: {
            //        }
            //    }
            //}

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: pressureMinMaxItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Apply")

                    onClick: {
                        apply();
                    }
                }
            }
        }
    }
}
