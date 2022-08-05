import QtQuick 2.0
import "../control/."
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import FontManager 1.0
import ValveEnumDef 1.0
import MathUtil 1.0
import GlobalUiValue 1.0
import GUISetting 1.0

Rectangle {
    id : panel

    property bool connected        : false
    property var  access           : ValveEnumDef.ACCESS_REMOTE
    property var  posStdResolution : 100000
    property var  posResolution    : 10000
    property var  currPos          : 10000
    property var  targetPos        : 10000
    property var  setPointPos01    : 0
    property var  setPointPos02    : 0
    property var  setPointPos03    : 0
    property var  setPointPos04    : 0
    property var  setPointPos05    : 0
    property var  setPointPos06    : 0
    property var  mode
    property bool isTestMode       : false
    property var  controlMode
    property var  cmdPos           : 0

    property var  fixedN           : (MathUtil.log10round(posStdResolution) - MathUtil.log10round(posResolution)) - 1
    property var  posCalcBaseValue : Math.pow(10, (-1 * (fixedN + 1)))

    signal editSetPoint();

    color: "#FFFFFF"

    NText{
        id : title
        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        isBold: true
        text : qsTr("Position")
    }

    NText{
        anchors.verticalCenter: actualPositionValue.verticalCenter; anchors.right: actualPositionValue.left; anchors.rightMargin: GUISetting.margin
        text : qsTr("actual position")
    }

    NText{
        id : actualPositionValue
        anchors.top: title.bottom; anchors.topMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        isBold: true
        text : "[MAX]" + (panel.posResolution).toFixed(0) //.toLocaleString(FontManager.locale, 'f', 0).replace(',', '')
    }

    Rectangle{
        id : currPosBox
        width: parent.width - (GUISetting.margin * 2); height: 30 * GUISetting.scale
        anchors.top:actualPositionValue.bottom; anchors.topMargin: GUISetting.line_margin;  anchors.horizontalCenter: parent.horizontalCenter;

        color: "#E4E4E4"

        NText{
            id : currPosValue
            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
            isBold: true
            fontSize: 16 * GUISetting.scale
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideRight
            color: "#24A7FF"
            text : (panel.currPos * panel.posCalcBaseValue).toFixed(panel.fixedN)//.toLocaleString(FontManager.locale, 'f', panel.fixedN).replace(',', '')

        }
    }

    NText{
        anchors.verticalCenter: targetPositionValue.verticalCenter; anchors.right: targetPositionValue.left; anchors.rightMargin: GUISetting.margin
        text : qsTr("target position")
        visible: panel.controlMode === ValveEnumDef.MODE_POSITION && panel.mode !== ValveEnumDef.MODE_SAFETY
    }

    NText{
        id :targetPositionValue
        anchors.top: currPosBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        isBold: true
        text : (panel.targetPos * panel.posCalcBaseValue).toFixed(panel.fixedN)// toLocaleString(FontManager.locale, 'f', panel.fixedN).replace(',', '')
        visible: panel.controlMode === ValveEnumDef.MODE_POSITION && panel.mode !== ValveEnumDef.MODE_SAFETY
    }

    ColumnLayout{
        width: (parent.width - (GUISetting.margin * 3)) / 2
        anchors.top: currPosBox.bottom; anchors.topMargin: 24 * GUISetting.scale; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        spacing: 8 * GUISetting.scale

        /*
        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; text.text : (panel.posStdResolution * panel.posCalcBaseValue).toFixed(0) + qsTr("(Open)") ;

            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL

            NSwitch{
                width: 10; height: 10
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 6
                isSelect: panel.posStdResolution === panel.currPos;
            }

            onClick: {cmdPosSlider.selectValue(panel.posStdResolution)}
        }*/
        NButton{ Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPos01 * panel.posCalcBaseValue).toFixed(0);
            onClick: {cmdPosSlider.selectValue(Math.round(panel.setPointPos01))}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{ Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPos02 * panel.posCalcBaseValue).toFixed(0);
            onClick: {cmdPosSlider.selectValue(Math.round(panel.setPointPos02))}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{ Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPos03 * panel.posCalcBaseValue).toFixed(0);
            onClick: {cmdPosSlider.selectValue(Math.round(panel.setPointPos03))}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{ Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPos04 * panel.posCalcBaseValue).toFixed(0);
            onClick: {cmdPosSlider.selectValue(Math.round(panel.setPointPos04))}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{ Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPos05 * panel.posCalcBaseValue).toFixed(0);
            onClick: {cmdPosSlider.selectValue(Math.round(panel.setPointPos05))}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{ Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPos06 * panel.posCalcBaseValue).toFixed(0);
            onClick: {cmdPosSlider.selectValue(Math.round(panel.setPointPos06))}
            onRightClick: { panel.editSetPoint()}
        }
        /*
        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; text.text : qsTr("0(Close)") ;

            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL

            NSwitch{
                width: 10; height: 10
                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: 6
                isSelect: 0 === panel.currPos;
            }
            onClick: {cmdPosSlider.selectValue(0)}
        }
        */
    }

    NSlider{
        id : cmdPosSlider
        width: (parent.width - (GUISetting.margin * 3)) / 2
        anchors.top: currPosBox.bottom; anchors.topMargin: 24 * GUISetting.scale; anchors.bottom: cmdPosInput.top; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        handle.width: 22 * GUISetting.scale
        enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected
        fixedN: 0
        axisFrom : 0
        axisTo   : panel.posStdResolution * panel.posCalcBaseValue
        from     : 0
        to       : panel.posStdResolution

        onSelectedValue: {
            cmdPosInput.setValue(Math.round(value * panel.posCalcBaseValue));
        }
    }

    NInputNumber{
        id : cmdPosInput
        width: (parent.width - (GUISetting.margin * 3)) / 2; height: 24 * GUISetting.scale
        anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin:  GUISetting.margin
        enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected
        textField.validator: IntValidator{}
        stepValue : 1; minValue: panel.isTestMode ? -1 * Math.floor(panel.posResolution * ( 99999 / 100000)) : 0; maxValue: panel.isTestMode ? Math.floor(panel.posResolution *  (999999 / 100000)) :  panel.posResolution
        fixedN : 0
        isEexplicitInputMode : true

        onChangedValue: {
            var newPos = Math.round(value * Math.pow(10, panel.fixedN + 1))

            cmdPosSlider.value = newPos
            cmdPos = newPos
        }

        onFocusOutTextField: {
            textField.text = (panel.targetPos * panel.posCalcBaseValue).toFixed(0)
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
