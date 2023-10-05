import QtQuick 2.0
import "../control/."
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.3
import FontManager 1.0
import ValveEnumDef 1.0
import UnitUtil 1.0
import MathUtil 1.0
import GlobalUiValue 1.0
import GUISetting 1.0

Rectangle {
    id : panel

    property bool connected               : false
    property var  access                  : ValveEnumDef.ACCESS_REMOTE
    property var  stdFullScale            : 1000000
    property var  mode
    property bool isTestMode              : false
    property var  controlMode
    property var  pressureDpUnit
    property var  isPressureLogType

    property var convertedSensorFullScale : 0
    property var convertedCurrPressure    : 0
    property var convertedTargetPressure  : 0
    property var fixedN                   : 0
    property var pressureDecades          : 5
    property var cmdPressure              : 0
    property var setPointPressure01    : 0
    property var setPointPressure02    : 0
    property var setPointPressure03    : 0
    property var setPointPressure04    : 0
    property var setPointPressure05    : 0
    property var setPointPressure06    : 0

    signal editSetPoint();

    function inputSliderValue(value, signalCreate = true)
    {
        if(panel.isPressureLogType)
            value = MathUtil.log10(value)

        cmdPressureSlider.selectValue(value, signalCreate)
    }

    color: "#FFFFFF"

    NText{
        id : title
        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        isBold: true
        text : qsTr("Pressure")
    }

    NText{
        anchors.verticalCenter: actualPressureValue.verticalCenter; anchors.right: actualPressureValue.left; anchors.rightMargin: GUISetting.margin
        text : qsTr("actual pressure")
    }

    NText{
        id : actualPressureValue
        anchors.top: title.bottom; anchors.topMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        isBold: true
        text : panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PA    ? "pa"  :
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_BAR   ? "bar"  :
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MBAR  ? "mbar" :
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_UBAR  ? "ubar" :
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_TORR  ? "Torr" :
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MTORR ? "mTorr":
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_ATM   ? "atm"  :
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSI   ? "psi"  :
               panel.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSF   ? "psf"  : ""
    }

    Rectangle{
        id : currPressureBox
        width: parent.width - (GUISetting.margin * 2); height: 30 * GUISetting.scale
        anchors.top:actualPressureValue.bottom; anchors.topMargin: 2;  anchors.horizontalCenter: parent.horizontalCenter;

        color: "#E4E4E4"

        NCircleIndicator{
            id : overIndi
            anchors.left: parent.left; anchors.leftMargin: GUISetting.on_indi_width; anchors.verticalCenter: overLabel.verticalCenter
            height: GUISetting.on_indi_height; width: GUISetting.on_indi_width

            color: "#FF0000"
            visible: panel.convertedCurrPressure > panel.convertedSensorFullScale
        }

        NText{
            id : overLabel
            anchors.left: overIndi.right; anchors.leftMargin: GUISetting.on_indi_width; anchors.top: parent.top; anchors.topMargin: GUISetting.on_indi_height
            color: "#FF0000"

            text: qsTr("range")
            visible: panel.convertedCurrPressure > panel.convertedSensorFullScale
        }

        NText{
            id : currPressureValue
            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
            isBold: true
            fontSize: 16 * GUISetting.scale
            horizontalAlignment: Text.AlignRight
            elide: Text.ElideRight
            color: "#FF7F27"
            text : panel.convertedCurrPressure.toFixed(panel.fixedN)//.toLocaleString(FontManager.locale, 'f', panel.fixedN).replace(',', '')
        }
    }

    NText{
        anchors.verticalCenter: targetPressureValue.verticalCenter; anchors.right: targetPressureValue.left; anchors.rightMargin: GUISetting.margin
        text : qsTr("target pressure")
        visible: panel.controlMode === ValveEnumDef.MODE_PRESSURE
    }

    NText{
        id :targetPressureValue
        anchors.top: currPressureBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        isBold: true
        text : panel.convertedTargetPressure.toFixed(panel.fixedN)//.toLocaleString(FontManager.locale, 'f', panel.fixedN).replace(',', '')
        visible: panel.controlMode === ValveEnumDef.MODE_PRESSURE
    }

    ColumnLayout{
        width: (parent.width - (GUISetting.margin * 3)) / 2
        anchors.top: currPressureBox.bottom; anchors.topMargin: 24 * GUISetting.scale; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
        spacing: 8 * GUISetting.scale

        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPressure01).toFixed(panel.fixedN);
            onClick: {panel.inputSliderValue(panel.setPointPressure01)}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPressure02).toFixed(panel.fixedN);
            onClick: {panel.inputSliderValue(panel.setPointPressure02)}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPressure03).toFixed(panel.fixedN);
            onClick: {panel.inputSliderValue(panel.setPointPressure03)}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPressure04).toFixed(panel.fixedN);
            onClick: {panel.inputSliderValue(panel.setPointPressure04)}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPressure05).toFixed(panel.fixedN);
            onClick: {panel.inputSliderValue(panel.setPointPressure05)}
            onRightClick: { panel.editSetPoint()}
        }
        NButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1;
            enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected;
            text.text : (panel.setPointPressure06).toFixed(panel.fixedN);
            onClick: {panel.inputSliderValue(panel.setPointPressure06)}
            onRightClick: { panel.editSetPoint()}
        }
    }

    NSlider{
        id : cmdPressureSlider
        width: (parent.width - (GUISetting.margin * 3)) / 2
        anchors.top: currPressureBox.bottom; anchors.topMargin: 24 * GUISetting.scale; anchors.bottom: cmdPressureInput.top; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected
        handle.width: 22 * GUISetting.scale

        from     : panel.isPressureLogType? MathUtil.floor(MathUtil.log10(panel.convertedSensorFullScale)) - panel.pressureDecades  : 0
        to       : panel.isPressureLogType? MathUtil.log10(panel.convertedSensorFullScale) : panel.convertedSensorFullScale

        isLogType: panel.isPressureLogType
        fixedN   : panel.fixedN
        axisFrom : panel.isPressureLogType? Math.pow(10, from) : 0
        axisTo   : panel.convertedSensorFullScale


        onSelectedValue: {
            if(isLogType)
                cmdPressureInput.setValue(Math.pow(10, value))
            else
                cmdPressureInput.setValue(value);
        }
    }

    NInputNumber{
        id : cmdPressureInput
        width: (parent.width - (GUISetting.margin * 3)) / 2; height: 24 * GUISetting.scale
        anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        enabled: panel.access === ValveEnumDef.ACCESS_LOCAL && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI && panel.connected
        textField.validator: DoubleValidator{}
        fixedN : panel.fixedN
        stepValue : (panel.convertedSensorFullScale * 0.005) ; minValue: 0; maxValue: panel.convertedSensorFullScale
        isEexplicitInputMode : true

        onChangedValue: {
            panel.inputSliderValue(value, false)

            var newPressure

            if(panel.convertedSensorFullScale === 0)
                newPressure = 0
            else
                newPressure = Math.round(panel.stdFullScale * (value / panel.convertedSensorFullScale))

            cmdPressure = newPressure
        }


        onFocusOutTextField: {
            textField.text = panel.convertedTargetPressure.toFixed(panel.fixedN)
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
