import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import NCPASettingsDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("NVM settings")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : ValveEnumDef.ACCESS_LOCAL // dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function commit()
    {
        var userPressurePrecisionValue = parseInt(body.userPressurePrecision.textField.text)
        var autoScaleMinMarginRatiovalue = parseFloat(body.autoScaleMinMarginRatio.textField.text)
        var posResolutionIdx       = body.posResolutionCombo.currentIndex + 1
        var pressureDpUnitIdx      = body.pressureDpUnitCombo.currentIndex
        var isDrawCurrPos          = body.posDrawCurrCombo.currentIndex        === 0 ? false : true
        var isDrawTargetPos        = body.posDrawTargetCombo.currentIndex      === 0 ? false : true
        var isDrawCurrPressure     = body.pressureDrawCurrCombo.currentIndex   === 0 ? false : true
        var isDrawTargetPressure   = body.pressureDrawTargetCombo.currentIndex === 0 ? false : true
        var pressureAxisMappingIdx = body.pressureAxisMappingCombo.currentIndex
        var pressureDecadesIdx     = body.pressureDecadesCombo.currentIndex
        var isAutoScalePos         = body.posAutoScaleCombo.currentIndex       === 0 ? false : true
        var isAutoScalePressure    = body.pressureAutoScaleCombo.currentIndex  === 0 ? false : true
        var chartTimeIdx           = body.chartTimeCombo.currentIndex

        dlgModel.onCommandApply(posResolutionIdx, pressureDpUnitIdx, isDrawCurrPos, isDrawTargetPos, isDrawCurrPressure, isDrawTargetPressure, pressureAxisMappingIdx, pressureDecadesIdx, isAutoScalePos, isAutoScalePressure, chartTimeIdx, userPressurePrecisionValue, autoScaleMinMarginRatiovalue)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    NCPASettingsDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.userPressurePrecision.setValue(dlgModel.mUserPressureFixedN)
            body.autoScaleMinMarginRatio.setValue(dlgModel.mAutoScaleMinMargin)
            body.posResolutionCombo.currentIndex       = dlgModel.mPosResolutionIdx - 1
            body.pressureDpUnitCombo.currentIndex      = dlgModel.mPressureDpUnitIdx
            body.posDrawCurrCombo.currentIndex         = dlgModel.mIsDrawCurrPos        ? 1 : 0
            body.posDrawTargetCombo.currentIndex       = dlgModel.mIsDrawTargetPos      ? 1 : 0
            body.pressureDrawCurrCombo.currentIndex    = dlgModel.mIsDrawCurrPressure   ? 1 : 0
            body.pressureDrawTargetCombo.currentIndex  = dlgModel.mIsDrawTargetPressure ? 1 : 0
            body.pressureAxisMappingCombo.currentIndex = dlgModel.mPressureAxisMappingIdx
            body.pressureDecadesCombo.currentIndex     = dlgModel.mPressureDecadesIdx
            body.posAutoScaleCombo.currentIndex        = dlgModel.mIsAutoScalePos       ? 1 : 0
            body.pressureAutoScaleCombo.currentIndex   = dlgModel.mIsAutoScalePressure  ? 1 : 0
            body.chartTimeCombo.currentIndex           = dlgModel.mChartMSecIdx

            onCommandSetEdit(false);
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias posResolutionCombo       : _posResolutionCombo
            property alias pressureDpUnitCombo      : _pressureDpUnitCombo
            property alias posDrawCurrCombo         : _posDrawCurrCombo
            property alias posDrawTargetCombo       : _posDrawTargetCombo
            property alias pressureDrawCurrCombo    : _pressureDrawCurrCombo
            property alias pressureDrawTargetCombo  : _pressureDrawTargetCombo
            property alias pressureAxisMappingCombo : _pressureAxisMappingCombo
            property alias pressureDecadesCombo     : _pressureDecadesCombo
            property alias posAutoScaleCombo        : _posAutoScaleCombo
            property alias pressureAutoScaleCombo   : _pressureAutoScaleCombo
            property alias chartTimeCombo           : _chartTimeCombo
            property alias userPressurePrecision    : _userPressurePrecision
            property alias autoScaleMinMarginRatio  : _autoScaleMinMarginRatio
            property real  guiScale                 : GUISetting.scale

            height: (GUISetting.line_margin + posIndiItem.height) + (GUISetting.line_margin + posChartItem.height) + (GUISetting.line_margin + chartTimeItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : posIndiItem

                height: (GUISetting.margin + posIndiTitle.height)
                        + (GUISetting.margin + _posResolutionCombo.height) + GUISetting.margin;
                width: ((parent.width - (GUISetting.line_margin * 3)) / 2)
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : posIndiTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Position indicator")
                }

                NComboBox{
                    id : _posResolutionCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: posIndiTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrPosResolution ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["10000","1000", "100"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _posResolutionCombo.verticalCenter; anchors.left: _posResolutionCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("displayed resolution")
                }
            }

            Rectangle{
                id : pressureIndiItem

                height: posIndiItem.height; width: posIndiItem.width
                anchors.verticalCenter: posIndiItem.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : pressureIndiTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Pressure indicator")
                }

                NComboBox{
                    id : _pressureDpUnitCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: pressureIndiTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrPressureDpUnit ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["Pa","bar", "mbar", "ubar", "Torr", "mTorr", "atm", "psi", "psf"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureDpUnitCombo.verticalCenter; anchors.left: _pressureDpUnitCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("displayed unit")
                }
            }

            Rectangle{
                id : posChartItem

                height:   (GUISetting.margin + posChartTitle.height      )
                        + (GUISetting.margin + _posDrawCurrCombo.height  )
                        + (GUISetting.margin + _posDrawTargetCombo.height)
                        + (GUISetting.margin + emptyItem01.height        )
                        + (GUISetting.margin + _posAutoScaleCombo.height )
                        + (GUISetting.margin + emptyItem02.height        )
                        + (GUISetting.margin + emptyItem03.height        )
                        + (GUISetting.margin + emptyItem04.height        )
                        + (GUISetting.margin + emptyItem05.height        ) + GUISetting.margin;
                width: ((parent.width - (GUISetting.line_margin * 3)) / 2)
                anchors.top: posIndiItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : posChartTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Chart position axis")
                }

                NComboBox{
                    id : _posDrawCurrCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: posChartTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrIsDrawCurrPos ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["hide","show"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _posDrawCurrCombo.verticalCenter; anchors.left: _posDrawCurrCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("actual position")
                }

                NComboBox{
                    id : _posDrawTargetCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _posDrawCurrCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrIsDrawTargetPos ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["hide","show"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _posDrawTargetCombo.verticalCenter; anchors.left: _posDrawTargetCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("target position")
                }

                Item{
                    id : emptyItem01
                    width: 50 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _posDrawTargetCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                }

                NComboBox{
                    id : _posAutoScaleCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: emptyItem01.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: "#000000"
                    enabled: dialog.progress === 100

                    model: ["fixed","autoscale"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _posAutoScaleCombo.verticalCenter; anchors.left: _posAutoScaleCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("axis scaling")
                }

                Item{
                    id : emptyItem02
                    width: 50 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _posAutoScaleCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                }

                Item{
                    id : emptyItem03
                    width: 50* GUISetting.scale; height: 24* GUISetting.scale
                    anchors.top: emptyItem02.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                }

                Item{
                    id : emptyItem04
                    width: 50* GUISetting.scale; height: 24* GUISetting.scale
                    anchors.top: emptyItem03.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                }

                Item{
                    id : emptyItem05
                    width: 50* GUISetting.scale; height: 24* GUISetting.scale
                    anchors.top: emptyItem04.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                }
            }

            Rectangle{
                id : pressureChartItem

                height: posChartItem.height; width: posChartItem.width
                anchors.verticalCenter: posChartItem.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : pressureChartTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Chart pressure axis")
                }

                NComboBox{
                    id : _pressureDrawCurrCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: pressureChartTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrIsDrawCurrPressure ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["hide","show"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureDrawCurrCombo.verticalCenter; anchors.left: _pressureDrawCurrCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("actual pressure")
                }

                NComboBox{
                    id : _pressureDrawTargetCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _pressureDrawCurrCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrIsDrawTargetPressure ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["hide","show"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureDrawTargetCombo.verticalCenter; anchors.left: _pressureDrawTargetCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("target pressure")
                }

                Item{
                    id : emptyItem
                    width: 50 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _pressureDrawTargetCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                }

                NComboBox{
                    id : _pressureAutoScaleCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: emptyItem.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: "#000000"
                    enabled: dialog.progress === 100

                    model: ["fixed","autoscale"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureAutoScaleCombo.verticalCenter; anchors.left: _pressureAutoScaleCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("axis scaling")
                }

                NComboBox{
                    id : _pressureAxisMappingCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _pressureAutoScaleCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrPressureAxisMapping ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["linear","logarithmic"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureAxisMappingCombo.verticalCenter; anchors.left: _pressureAxisMappingCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("axis mapping")
                }

                NComboBox{
                    id : _pressureDecadesCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _pressureAxisMappingCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrPressureDecades ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["1","2","3","4","5"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureDecadesCombo.verticalCenter; anchors.left: _pressureDecadesCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("decades")
                }

                NInputNumber{
                    id : _userPressurePrecision
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _pressureDecadesCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.validator: IntValidator{}
                    textField.color: "#000000"
                    stepValue : 0.0001; minValue: 0; maxValue: 8
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _userPressurePrecision.verticalCenter; anchors.left: _userPressurePrecision.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("floating point precision")
                }

                NInputNumber{
                    id : _autoScaleMinMarginRatio
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _userPressurePrecision.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.validator: DoubleValidator{}
                    textField.color: "#000000"
                    stepValue : 0.0001; minValue: 0.1; maxValue: 100
                    fixedN : 1

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _autoScaleMinMarginRatio.verticalCenter; anchors.left: _autoScaleMinMarginRatio.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("auto scale<br>minimum margin ratio")
                }
            }

            Rectangle{
                id : chartTimeItem

                height: GUISetting.margin + chartTimeTitle.height + GUISetting.margin + _chartTimeCombo.height + GUISetting.margin;
                anchors.top: posChartItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : chartTimeTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Chart position axis")
                }

                NComboBox{
                    id : _chartTimeCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: chartTimeTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrChartMSec ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["30 seconds","1 minute","2 minute","5 minute"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _chartTimeCombo.verticalCenter; anchors.left: _chartTimeCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("displayed time interval")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: chartTimeItem.bottom; anchors.topMargin: 2; anchors.left: parent.left; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Apply")

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                        color: "#FF0000"
                        visible: dialog.isEdit
                    }

                    onClick: {
                        dialog.apply()
                    }
                }
            }
        }
    }
}
