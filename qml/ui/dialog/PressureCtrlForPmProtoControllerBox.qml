import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import PressureCtrlControllerItem 1.0
import GUISetting 1.0

Rectangle {
    id : root

    property int    progress : 0
    property string title : ""
    property bool   isSelected : false

    property PressureCtrlControllerItem itemModel : PressureCtrlControllerItem{}

    signal changeValue();

    border.width: isSelected ? 2 : 0
    border.color: "#24A7FF"

    Connections {
        target: root.itemModel

        function onMControllerAlgorithmModeChanged     (value) { algorithmItem.currentIndex = value     }
        function onMControllerGainFactorChanged        (value) { gainFactorItem.textField.text = value  }
        function onMControllerDeltaFactorChanged       (value) { deltaFactorItem.textField.text = value }
        function onMControllerSensorDelayChanged       (value) { sensorDelayItem.textField.text = value }
        function onMControllerLearnDataSelectionChanged(value) { learnDataItem.currentIndex = value     }
        function onMControllerDirectionChanged         (value) { directionItem.currentIndex = value     }
        function onMControllerPGainFactorChanged       (value) { pgainFactorItem.textField.text = value }
        function onMControllerIGainFactorChanged       (value) { igainFactorItem.textField.text = value }
        function onMControllerPressureScalerChanged    (value) { pressureScalerItem.currentIndex = value}
        function onMControllerRampEnableChanged        (value) { rampEnableItem.currentIndex = value    }
        function onMControllerRampTimeChanged          (value) { rampTimeItem.textField.text = value    }
        function onMControllerRampSlopeChanged         (value) { rampSlopeItem.textField.text = value   }
        function onMControllerRampModeChanged          (value) { rampModeItem.currentIndex = value      }
        function onMControllerRampStartValueChanged    (value) { rampStartValueItem.currentIndex = value}
        function onMControllerRampTypeChanged          (value) { rampTypeItem.currentIndex = value      }

        function onMIsEditControllerAlgorithmModeChanged(value){ console.debug("qml changed value = " + value)}
    }

    color : "#FFFFFF"
    height : 325

    NText{
        id : titleItem
        anchors.top: parent.top; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        isBold: true
        text : root.title
    }

    NComboBox{
        id : algorithmItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: titleItem.bottom; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerAlgorithmMode    ? "#FF0000" :
                   root.itemModel.mIsEditControllerAlgorithmMode ? "#24A7FF" : "#000000"
        enabled: root.progress === 100

        model: ["0:Adaptive", "1:PI", "2: Soft Pump"]

        onCurrentIndexChanged: { root.itemModel.onCommandSetEditControllerAlgorithmMode(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: algorithmItem.verticalCenter; anchors.left: algorithmItem.right; anchors.leftMargin: GUISetting.margin
        text : qsTr("algorithm")
    }

    NInputNumber{
        id : gainFactorItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: algorithmItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex == 0
        enabled: root.progress === 100

        textField.validator: DoubleValidator{}
        textField.color: root.itemModel.mErrControllerGainFactor    ? "#FF0000" :
                         root.itemModel.mIsEditControllerGainFactor ? "#24A7FF" : "#000000"
        stepValue : 0.0001; minValue: 0; maxValue: 100
        fixedN : 4

        onChangedText: { root.itemModel.onCommandSetEditControllerGainFactor(textField.text); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: gainFactorItem.verticalCenter; anchors.left: gainFactorItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex == 0

        text : qsTr("gain factor(0 ~ 100)")
    }

    NInputNumber{
        id : deltaFactorItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: gainFactorItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex == 0
        enabled: root.progress === 100

        textField.validator: DoubleValidator{}
        textField.color: root.itemModel.mErrControllerDeltaFactor    ? "#FF0000" :
                         root.itemModel.mIsEditControllerDeltaFactor ? "#24A7FF" : "#000000"
        stepValue : 0.0001; minValue: 0; maxValue: 100
        fixedN : 4

        onChangedText: { root.itemModel.onCommandSetEditControllerDeltaFactor(textField.text); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: deltaFactorItem.verticalCenter; anchors.left: deltaFactorItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex == 0

        text : qsTr("delta factor(0 ~ 100)")
    }

    NInputNumber{
        id : sensorDelayItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: deltaFactorItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex == 0
        enabled: root.progress === 100

        textField.validator: DoubleValidator{}
        textField.color: root.itemModel.mErrControllerSensorDelay    ? "#FF0000" :
                         root.itemModel.mIsEditControllerSensorDelay ? "#24A7FF" : "#000000"
        stepValue : 0.01; minValue: 0; maxValue: 1
        fixedN : 2

        onChangedText: { root.itemModel.onCommandSetEditControllerSensorDelay(textField.text); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: sensorDelayItem.verticalCenter; anchors.left: sensorDelayItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex == 0

        text : qsTr("sensor delay(0 sec ~ 1 sec)")
    }

    NComboBox{
        id : learnDataItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: sensorDelayItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerLearnDataSelection    ? "#FF0000" :
                   root.itemModel.mIsEditControllerLearnDataSelection ? "#24A7FF" : "#000000"

        visible: algorithmItem.currentIndex == 0
        enabled: root.progress === 100

        model: ["0: Learn Bank 1", "1: Learn Bank 2", "2: Learn Bank 3", "3: Learn Bank 4"]

        onCurrentIndexChanged: { root.itemModel.onCommandSetEditControllerLearnDataSelection(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: learnDataItem.verticalCenter; anchors.left: learnDataItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex == 0

        text : qsTr("learn data selection")
    }

    NComboBox{
        id : directionItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: algorithmItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerDirection    ? "#FF0000" :
                   root.itemModel.mIsEditControllerDirection ? "#24A7FF" : "#000000"
        visible: algorithmItem.currentIndex != 0
        enabled: root.progress === 100

        model: ["0: Downstream", "1:Upstream"]

        onCurrentIndexChanged: { root.itemModel.onCommandSetEditControllerDirection(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: directionItem.verticalCenter; anchors.left: directionItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex != 0

        text : qsTr("direction")
    }

    NInputNumber{
        id : pgainFactorItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: directionItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex != 0
        enabled: root.progress === 100

        textField.validator: DoubleValidator{}
        textField.color: root.itemModel.mErrControllerPGainFactor    ? "#FF0000" :
                         root.itemModel.mIsEditControllerPGainFactor ? "#24A7FF" : "#000000"
        stepValue : 0.0001; minValue: 0; maxValue: 100
        fixedN : 4

        onChangedText: { root.itemModel.onCommandSetEditControllerPGainFactor(textField.text); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: pgainFactorItem.verticalCenter; anchors.left: pgainFactorItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex != 0

        text : qsTr("P gain factor(0 ~ 100)")
    }

    NInputNumber{
        id : igainFactorItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: pgainFactorItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex != 0
        enabled: root.progress === 100

        textField.validator: DoubleValidator{}
        textField.color: root.itemModel.mErrControllerIGainFactor    ? "#FF0000" :
                         root.itemModel.mIsEditControllerIGainFactor ? "#24A7FF" : "#000000"
        stepValue : 0.0001; minValue: 0; maxValue: 100
        fixedN : 4

        onChangedText: { root.itemModel.onCommandSetEditControllerIGainFactor(textField.text); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: igainFactorItem.verticalCenter; anchors.left: igainFactorItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex != 0

        text : qsTr("I gain factor(0 ~ 100)")
    }

    NComboBox{
        id : pressureScalerItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: igainFactorItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerPressureScaler    ? "#FF0000" :
                   root.itemModel.mIsEditControllerPressureScaler ? "#24A7FF" : "#000000"

        visible: algorithmItem.currentIndex != 0
        enabled: root.progress === 100

        model: ["0: Linear", "1: Logarithmic"]

        onCurrentIndexChanged: {root.itemModel.onCommandSetEditControllerPressureScaler(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: pressureScalerItem.verticalCenter; anchors.left: pressureScalerItem.right; anchors.leftMargin: GUISetting.margin

        visible: algorithmItem.currentIndex != 0

        text : qsTr("pressure scaler")
    }

    NComboBox{
        id : rampEnableItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: pressureScalerItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerRampEnable    ? "#FF0000" :
                   root.itemModel.mIsEditControllerRampEnable ? "#24A7FF" : "#000000"
        enabled: root.progress === 100

        model: ["0: Disable", "1:Enable"]

        onCurrentIndexChanged: { root.itemModel.onCommandSetEditControllerRampEnable(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: rampEnableItem.verticalCenter; anchors.left: rampEnableItem.right; anchors.leftMargin: GUISetting.margin

        text : qsTr("ramp enable")
    }

    NInputNumber{
        id : rampTimeItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: rampEnableItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        visible: rampEnableItem.currentIndex == 1
        enabled: root.progress === 100

        textField.validator: DoubleValidator{}
        textField.color: root.itemModel.mErrControllerRampTime    ? "#FF0000" :
                         root.itemModel.mIsEditControllerRampTime ? "#24A7FF" : "#000000"
        stepValue : 0.01; minValue: 0; maxValue: 1000000
        fixedN : 2

        onChangedText: { root.itemModel.onCommandSetEditControllerRampTime(textField.text); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: rampTimeItem.verticalCenter; anchors.left: rampTimeItem.right; anchors.leftMargin: GUISetting.margin

        visible: rampEnableItem.currentIndex == 1
        text : qsTr("ramp time(sec)")
    }

    NInputNumber{
        id : rampSlopeItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: rampTimeItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        visible: rampEnableItem.currentIndex == 1
        enabled: root.progress === 100

        textField.validator: DoubleValidator{}
        textField.color: root.itemModel.mErrControllerRampSlope    ? "#FF0000" :
                         root.itemModel.mIsEditControllerRampSlope ? "#24A7FF" : "#000000"
        stepValue : 0.0001; minValue: 0; maxValue: 1000000
        fixedN : 4

        onChangedText: { root.itemModel.onCommandSetEditControllerRampSlope(textField.text); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: rampSlopeItem.verticalCenter; anchors.left: rampSlopeItem.right; anchors.leftMargin: GUISetting.margin

        visible: rampEnableItem.currentIndex == 1
        text : qsTr("ramp slop(pressure/sec)")
    }

    NComboBox{
        id : rampModeItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: rampSlopeItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerRampMode    ? "#FF0000" :
                   root.itemModel.mIsEditControllerRampMode ? "#24A7FF" : "#000000"

        visible: rampEnableItem.currentIndex == 1
        enabled: root.progress === 100

        model: ["0: Use Ramp Time", "1: Use Ramp Slope"]

        onCurrentIndexChanged: { root.itemModel.onCommandSetEditControllerRampMode(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: rampModeItem.verticalCenter; anchors.left: rampModeItem.right; anchors.leftMargin: GUISetting.margin

        visible: rampEnableItem.currentIndex == 1
        text : qsTr("ramp mode")
    }

    NComboBox{
        id : rampStartValueItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: rampModeItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerRampStartValue    ? "#FF0000" :
                   root.itemModel.mIsEditControllerRampStartValue ? "#24A7FF" : "#000000"

        visible: rampEnableItem.currentIndex == 1
        enabled: root.progress === 100

        model: ["0: Previous Ramp Value", "1: Actual Pressure Value"]

        onCurrentIndexChanged: { root.itemModel.onCommandSetEditControllerRampStartValue(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: rampStartValueItem.verticalCenter; anchors.left: rampStartValueItem.right; anchors.leftMargin: GUISetting.margin

        visible: rampEnableItem.currentIndex == 1
        text : qsTr("ramp start value")
    }

    NComboBox{
        id : rampTypeItem
        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
        anchors.top: rampStartValueItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

        textColor: root.itemModel.mErrControllerRampType    ? "#FF0000" :
                   root.itemModel.mIsEditControllerRampType ? "#24A7FF" : "#000000"

        visible: rampEnableItem.currentIndex == 1
        enabled: root.progress === 100
        model: ["0:Linear", "1: Logarithmic", "2: Exponential"]

        onCurrentIndexChanged: { root.itemModel.onCommandSetEditControllerRampType(currentIndex); root.changeValue() }
    }

    NText{
        anchors.verticalCenter: rampTypeItem.verticalCenter; anchors.left: rampTypeItem.right; anchors.leftMargin: GUISetting.margin

        visible: rampEnableItem.currentIndex == 1
        text : qsTr("ramp type")
    }
}
