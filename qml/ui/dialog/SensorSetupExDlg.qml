import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import StrUtil 1.0
import SensorSetupExDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    signal signalEventOccurErr()

    titleText   : qsTr("Sensor setup")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function commit()
    {
        if(body.s01Source.currentIndex === 0)
            body.s01Selection.currentIndex = 0;

        if(body.s02Source.currentIndex === 0)
            body.s02Selection.currentIndex = 0;

        var s01AnalActive               = body.s01AnalActive.isSelect ? 1 : 0
        var s01Selection                = body.s01Selection.currentIndex
        var s01Source                   = body.s01Source.currentIndex
        var s01Unit                     = body.s01Unit.currentIndex
        var s01FullScale                = body.s01FullScale.textField.text
        var s01DigiValue                = body.s01DigiValue.textField.text
        var s01ZeroAdjEnable            = body.s01ZeroAdjEnable.currentIndex
        var s01ZeroAdjOffsetLimMin      = body.s01ZeroAdjOffsetLimMin.textField.text
        var s01ZeroAdjOffsetLimMax      = body.s01ZeroAdjOffsetLimMax.textField.text
        var s01ZeroAdjOffsetValue       = body.s01ZeroAdjOffsetValue.textField.text
        var s01ScaleOffset              = body.s01ScaleOffset.textField.text
        var s01Scale                    = body.s01Scale.textField.text
        var s01ScaleZeroPoint           = body.s01ScaleZeroPoint.currentIndex
        var s01FilterSec                = body.s01FilterSec.textField.text
        var s01LogSensorLinearize       = body.s01LogSensorLinearize.currentIndex
        var s01LogSensorVoltPerDecade   = body.s01LogSensorVoltPerDecade.textField.text
        var s01LogSensorVoltAtFullScale = body.s01LogSensorVoltAtFullScale.textField.text

        var s02AnalActive               = body.s02AnalActive.isSelect ? 1 : 0
        var s02Selection                = body.s02Selection.currentIndex
        var s02Source                   = body.s02Source.currentIndex
        var s02Unit                     = body.s02Unit.currentIndex
        var s02FullScale                = body.s02FullScale.textField.text
        var s02DigiValue                = body.s02DigiValue.textField.text
        var s02ZeroAdjEnable            = body.s02ZeroAdjEnable.currentIndex
        var s02ZeroAdjOffsetLimMin      = body.s02ZeroAdjOffsetLimMin.textField.text
        var s02ZeroAdjOffsetLimMax      = body.s02ZeroAdjOffsetLimMax.textField.text
        var s02ZeroAdjOffsetValue       = body.s02ZeroAdjOffsetValue.textField.text
        var s02ScaleOffset              = body.s02ScaleOffset.textField.text
        var s02Scale                    = body.s02Scale.textField.text
        var s02ScaleZeroPoint           = body.s02ScaleZeroPoint.currentIndex
        var s02FilterSec                = body.s02FilterSec.textField.text
        var s02LogSensorLinearize       = body.s02LogSensorLinearize.currentIndex
        var s02LogSensorVoltPerDecade   = body.s02LogSensorVoltPerDecade.textField.text
        var s02LogSensorVoltAtFullScale = body.s02LogSensorVoltAtFullScale.textField.text

        var crossoverMod                = body.crossoverMod.currentIndex
        var crossoverLow                = body.crossoverLow.textField.text
        var crossoverHigh               = body.crossoverHigh.textField.text
        var crossoverDela               = body.crossoverDela.textField.text

        dlgModel.onCommandApply(s01AnalActive              ,
                                s01Selection               ,
                                s01Source                  ,
                                s01Unit                    ,
                                s01FullScale               ,
                                s01DigiValue               ,
                                s01ZeroAdjEnable           ,
                                s01ZeroAdjOffsetLimMin     ,
                                s01ZeroAdjOffsetLimMax     ,
                                s01ZeroAdjOffsetValue      ,
                                s01ScaleOffset             ,
                                s01Scale                   ,
                                s01ScaleZeroPoint          ,
                                s01FilterSec               ,
                                s01LogSensorLinearize      ,
                                s01LogSensorVoltPerDecade  ,
                                s01LogSensorVoltAtFullScale,
                                s02AnalActive              ,
                                s02Selection               ,
                                s02Source                  ,
                                s02Unit                    ,
                                s02FullScale               ,
                                s02DigiValue               ,
                                s02ZeroAdjEnable           ,
                                s02ZeroAdjOffsetLimMin     ,
                                s02ZeroAdjOffsetLimMax     ,
                                s02ZeroAdjOffsetValue      ,
                                s02ScaleOffset             ,
                                s02Scale                   ,
                                s02ScaleZeroPoint          ,
                                s02FilterSec               ,
                                s02LogSensorLinearize      ,
                                s02LogSensorVoltPerDecade  ,
                                s02LogSensorVoltAtFullScale,
                                crossoverMod               ,
                                crossoverLow               ,
                                crossoverHigh              ,
                                crossoverDela              )
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 900 * GUISetting.scale
    }

    SensorSetupExDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.s01AnalActive.isSelect                     = dlgModel.mS01AnalActive
            body.s01Selection.currentIndex                  = dlgModel.mS01Selection
            body.s01Source.currentIndex                     = dlgModel.mS01SourceIdx
            body.s01Unit.currentIndex                       = dlgModel.mS01UnitIdx
            body.s01FullScale.textField.text                = dlgModel.mS01FullScale
            body.s01DigiValue.textField.text                = dlgModel.mS01DigiValue
            body.s01ZeroAdjEnable.currentIndex              = dlgModel.mS01ZeroAdjEnable
            body.s01ZeroAdjOffsetLimMin.textField.text      = dlgModel.mS01ZeroAdjOffsetLimMin
            body.s01ZeroAdjOffsetLimMax.textField.text      = dlgModel.mS01ZeroAdjOffsetLimMax
            body.s01ZeroAdjOffsetValue.textField.text       = dlgModel.mS01ZeroAdjOffsetValue
            body.s01ScaleOffset.textField.text              = dlgModel.mS01ScaleOffset
            body.s01Scale.textField.text                    = dlgModel.mS01Scale
            body.s01ScaleZeroPoint.currentIndex             = dlgModel.mS01ScaleZeroPoint
            body.s01FilterSec.textField.text                = dlgModel.mS01FilterSec
            body.s01LogSensorLinearize.currentIndex         = dlgModel.mS01LogSensorLinearize
            body.s01LogSensorVoltPerDecade.textField.text   = dlgModel.mS01LogSensorVoltPerDecade
            body.s01LogSensorVoltAtFullScale.textField.text = dlgModel.mS01LogSensorVoltAtFullScale

            body.s02AnalActive.isSelect                     = dlgModel.mS02AnalActive
            body.s02Selection.currentIndex                  = dlgModel.mS02Selection
            if(dlgModel.mIsSensor02Support == false && dlgModel.mS02SourceIdx == 1)
                body.s02Source.currentIndex                 = 0
            else
                body.s02Source.currentIndex                 = dlgModel.mS02SourceIdx
            body.s02Unit.currentIndex                       = dlgModel.mS02UnitIdx
            body.s02FullScale.textField.text                = dlgModel.mS02FullScale
            body.s02DigiValue.textField.text                = dlgModel.mS02DigiValue
            body.s02ZeroAdjEnable.currentIndex              = dlgModel.mS02ZeroAdjEnable
            body.s02ZeroAdjOffsetLimMin.textField.text      = dlgModel.mS02ZeroAdjOffsetLimMin
            body.s02ZeroAdjOffsetLimMax.textField.text      = dlgModel.mS02ZeroAdjOffsetLimMax
            body.s02ZeroAdjOffsetValue.textField.text       = dlgModel.mS02ZeroAdjOffsetValue
            body.s02ScaleOffset.textField.text              = dlgModel.mS02ScaleOffset
            body.s02Scale.textField.text                    = dlgModel.mS02Scale
            body.s02ScaleZeroPoint.currentIndex             = dlgModel.mS02ScaleZeroPoint
            body.s02FilterSec.textField.text                = dlgModel.mS02FilterSec
            body.s02LogSensorLinearize.currentIndex         = dlgModel.mS02LogSensorLinearize
            body.s02LogSensorVoltPerDecade.textField.text   = dlgModel.mS02LogSensorVoltPerDecade
            body.s02LogSensorVoltAtFullScale.textField.text = dlgModel.mS02LogSensorVoltAtFullScale

            body.crossoverMod.currentIndex                  = dlgModel.mCrossoverModIdx
            body.crossoverLow.textField.text                = dlgModel.mCrossoverLow
            body.crossoverHigh.textField.text               = dlgModel.mCrossoverHigh
            body.crossoverDela.textField.text               = dlgModel.mCrossoverDela

            onCommandSetEdit(false);
        }

        onSignalEventCompletedApply: {
            dialog.close();
        }

        onSignalEventOccurErr: {
            dialog.signalEventOccurErr()
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias s01AnalActive               : _s01AnalActive
            property alias s01Selection                : _s01Selection
            property alias s01Source                   : _s01Source
            property alias s01Unit                     : _s01Unit
            property alias s01FullScale                : _s01FullScale
            property alias s01DigiValue                : _s01DigiValue
            property alias s01ZeroAdjEnable            : _s01ZeroAdjEnable
            property alias s01ZeroAdjOffsetLimMin      : _s01ZeroAdjOffsetLimMin
            property alias s01ZeroAdjOffsetLimMax      : _s01ZeroAdjOffsetLimMax
            property alias s01ZeroAdjOffsetValue       : _s01ZeroAdjOffsetValue
            property alias s01ScaleOffset              : _s01ScaleOffset
            property alias s01Scale                    : _s01Scale
            property alias s01ScaleZeroPoint           : _s01ScaleZeroPoint
            property alias s01FilterSec                : _s01FilterSec
            property alias s01LogSensorLinearize       : _s01LogSensorLinearize
            property alias s01LogSensorVoltPerDecade   : _s01LogSensorVoltPerDecade
            property alias s01LogSensorVoltAtFullScale : _s01LogSensorVoltAtFullScale

            property alias s02AnalActive               : _s02AnalActive
            property alias s02Selection                : _s02Selection
            property alias s02Source                   : _s02Source
            property alias s02Unit                     : _s02Unit
            property alias s02FullScale                : _s02FullScale
            property alias s02DigiValue                : _s02DigiValue
            property alias s02ZeroAdjEnable            : _s02ZeroAdjEnable
            property alias s02ZeroAdjOffsetLimMin      : _s02ZeroAdjOffsetLimMin
            property alias s02ZeroAdjOffsetLimMax      : _s02ZeroAdjOffsetLimMax
            property alias s02ZeroAdjOffsetValue       : _s02ZeroAdjOffsetValue
            property alias s02ScaleOffset              : _s02ScaleOffset
            property alias s02Scale                    : _s02Scale
            property alias s02ScaleZeroPoint           : _s02ScaleZeroPoint
            property alias s02FilterSec                : _s02FilterSec
            property alias s02LogSensorLinearize       : _s02LogSensorLinearize
            property alias s02LogSensorVoltPerDecade   : _s02LogSensorVoltPerDecade
            property alias s02LogSensorVoltAtFullScale : _s02LogSensorVoltAtFullScale

            property alias crossoverMod                : _crossoverMod
            property alias crossoverLow                : _crossoverLow
            property alias crossoverHigh               : _crossoverHigh
            property alias crossoverDela               : _crossoverDela

            property real   guiScale                 : GUISetting.scale

            height: (GUISetting.line_margin + sensor01Item.height) + (GUISetting.line_margin + crossoverItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = 900 * GUISetting.scale
            }

            Rectangle{
                id : sensor01Item

                height:   (GUISetting.margin + _sensor01Title.height)
                        + (GUISetting.margin + _s01Selection.height)
                        + (GUISetting.margin + s01SubTitleRange.height + _s01Unit.height)
                        + (GUISetting.margin + s01SubTitleDigital.height + _s01DigiValue.height)
                        + (GUISetting.margin + s01SubTitleZeroAdj.height + _s01ZeroAdjEnable.height + _s01ZeroAdjOffsetLimMin.height)
                        + (GUISetting.margin + s01SubTitleScale.height + _s01ScaleOffset.height + _s01ScaleZeroPoint.height)
                        + (GUISetting.margin + s01SubTitleFilter.height + _s01FilterSec.height)
                        + (GUISetting.margin + s01SubTitleLogSensor.height + _s01LogSensorLinearize.height + _s01LogSensorVoltPerDecade.height) + GUISetting.margin
                width:  (parent.width - (GUISetting.line_margin * 3)) / 2
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : _sensor01Title
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Sensor port 1")
                }

                NText{
                    id : s01AnalActiveText
                    anchors.right: parent.right; anchors.rightMargin : GUISetting.margin; anchors.verticalCenter: _sensor01Title.verticalCenter

                    text : qsTr("analog active")
                }

                NSwitch{
                    id : _s01AnalActive
                    width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                    anchors.right: s01AnalActiveText.left; anchors.rightMargin : GUISetting.margin; anchors.verticalCenter: s01AnalActiveText.verticalCenter

                    enabled: false
                }

                NComboBox{
                    id : _s01Source
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor01Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS01SourceIdx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["none", "analog", "digital"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01SourceIdx()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01Source.verticalCenter; anchors.left: _s01Source.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("source")
                }

                NComboBox{
                    id : _s01Selection
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor01Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    textColor: dlgModel.mErrS01Selection ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not selected", "selected"]

                    visible: _s01Source.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditSelection()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01Selection.verticalCenter; anchors.left: _s01Selection.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("selection")

                    visible: _s01Source.currentIndex != 0
                }

                NText{
                    id: s01SubTitleRange
                    anchors.top: _s01Selection.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("range")
                    color: "#ACACAC"

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s01Unit
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleRange.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS01UnitIdx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["Pa","bar", "mbar", "ubar", "Torr", "mTorr", "atm", "psi", "psf"]

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01UnitIdx()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01Unit.verticalCenter; anchors.left: _s01Unit.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("unit")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01FullScale
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleRange.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01FullScale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 99999999
                    fixedN : 4

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01FullScale()
                    }

                    onChangedValue: {
                        textField.text = dlgModel.onCommandCheckScaleValue(textField.text)
                        _s01DigiValue.textField.text = dlgModel.onCommandCheckDigitalValue(textField.text, _s01DigiValue.textField.text)
                    }
                }

                NText{
                    anchors.verticalCenter: _s01FullScale.verticalCenter; anchors.left: _s01FullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("full scale")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NText{
                    id: s01SubTitleDigital
                    anchors.top: _s01FullScale.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("digital")
                    color: "#ACACAC"

                    visible: _s01Source.currentIndex == 2 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01DigiValue
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleDigital.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01DigiValue ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -1000000000; maxValue: 1000000000
                    fixedN : 6

                    visible: _s01Source.currentIndex == 2 && _s01Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01DigiValue()
                    }

                    onChangedValue: {
                        textField.text = dlgModel.onCommandCheckDigitalValue(_s01FullScale.textField.text, textField.text)
                    }
                }

                NText{
                    anchors.verticalCenter: _s01DigiValue.verticalCenter; anchors.left: _s01DigiValue.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("digital value")

                    visible: _s01Source.currentIndex == 2 && _s01Selection.currentIndex != 0
                }

                NText{
                    id: s01SubTitleZeroAdj
                    anchors.top: _s01DigiValue.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("zero adjust")
                    color: "#ACACAC"

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s01ZeroAdjEnable
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleZeroAdj.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS01ZeroAdjEnable ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["disabled","enabled"]

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onCurrentIndexChanged: {

                        if(currentIndex == 0)
                        {
                            _s01ZeroAdjOffsetValue.textField.text = "0.00"
                            dlgModel.onCommandSetEditS01ZeroAdjOffsetValue()
                        }

                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01ZeroAdjEnable()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01ZeroAdjEnable.verticalCenter; anchors.left: _s01ZeroAdjEnable.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("enable")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01ZeroAdjOffsetValue
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleZeroAdj.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100 && _s01ZeroAdjEnable.currentIndex == 1

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01ZeroAdjOffsetValue ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -100; maxValue: 100
                    fixedN : 2

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01ZeroAdjOffsetValue()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01ZeroAdjOffsetValue.verticalCenter; anchors.left: _s01ZeroAdjOffsetValue.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset value[% SFS]")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01ZeroAdjOffsetLimMin
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s01ZeroAdjOffsetValue.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01ZeroAdjOffsetLimMin ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -100; maxValue: 0
                    fixedN : 2

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01ZeroAdjEnable.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01ZeroAdjOffsetLimMin()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01ZeroAdjOffsetLimMin.verticalCenter; anchors.left: _s01ZeroAdjOffsetLimMin.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset min[% SFS]")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01ZeroAdjEnable.currentIndex != 0
                }

                NInputNumber{
                    id : _s01ZeroAdjOffsetLimMax
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s01ZeroAdjOffsetValue.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01ZeroAdjOffsetLimMax ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 100
                    fixedN : 2

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01ZeroAdjEnable.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01ZeroAdjOffsetLimMax()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01ZeroAdjOffsetLimMax.verticalCenter; anchors.left: _s01ZeroAdjOffsetLimMax.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset max[% SFS]")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01ZeroAdjEnable.currentIndex != 0
                }

                NText{
                    id: s01SubTitleScale
                    anchors.top: _s01ZeroAdjOffsetLimMax.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("scale")
                    color: "#ACACAC"

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01ScaleOffset
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleScale.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01ScaleOffset ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -100; maxValue: 100
                    fixedN : 3

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01ScaleOffset()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01ScaleOffset.verticalCenter; anchors.left: _s01ScaleOffset.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("scale offset[V]")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01Scale
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleScale.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5 //GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01Scale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -10000; maxValue: 10000
                    fixedN : 6

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01Scale()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01Scale.verticalCenter; anchors.left: _s01Scale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("scale")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s01ScaleZeroPoint
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s01Scale.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS01ScaleZeroPoint ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["before scale","after scale"]

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01ScaleZeroPoint()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01ScaleZeroPoint.verticalCenter; anchors.left: _s01ScaleZeroPoint.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("zero point")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NText{
                    id: s01SubTitleFilter
                    anchors.top: _s01ScaleZeroPoint.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("filter")
                    color: "#ACACAC"

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01FilterSec
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleFilter.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01FilterSec ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 1
                    fixedN : 2

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01FilterSec()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01FilterSec.verticalCenter; anchors.left: _s01FilterSec.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("filter time[sec]")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NText{
                    id: s01SubTitleLogSensor
                    anchors.top: _s01FilterSec.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("logarithmic sensor")
                    color: "#ACACAC"

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s01LogSensorLinearize
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s01SubTitleLogSensor.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS01LogSensorLinearize ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["no","yes"]

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01LogSensorLinearize()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01LogSensorLinearize.verticalCenter; anchors.left: _s01LogSensorLinearize.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("linearize")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s01LogSensorVoltPerDecade
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s01LogSensorLinearize.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01LogSensorVoltPerDecade ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -9999.999; maxValue: 9999.999
                    fixedN : 3

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01LogSensorLinearize.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01LogSensorVoltPerDecade()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01LogSensorVoltPerDecade.verticalCenter; anchors.left: _s01LogSensorVoltPerDecade.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("voltage per decade")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01LogSensorLinearize.currentIndex != 0
                }

                NInputNumber{
                    id : _s01LogSensorVoltAtFullScale
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s01LogSensorLinearize.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS01LogSensorVoltAtFullScale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 12
                    fixedN : 6

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01LogSensorLinearize.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS01LogSensorVoltAtFullScale()
                    }
                }

                NText{
                    anchors.verticalCenter: _s01LogSensorVoltAtFullScale.verticalCenter; anchors.left: _s01LogSensorVoltAtFullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("voltage at full scale")

                    visible: _s01Source.currentIndex != 0 && _s01Selection.currentIndex != 0 && _s01LogSensorLinearize.currentIndex != 0
                }
            }

            Rectangle{
                id : sensor02Item

                height:   (GUISetting.margin + _sensor02Title.height)
                        + (GUISetting.margin + _s02Selection.height)
                        + (GUISetting.margin + s02SubTitleRange.height + _s02Unit.height)
                        + (GUISetting.margin + s02SubTitleDigital.height + _s02DigiValue.height)
                        + (GUISetting.margin + s02SubTitleZeroAdj.height + _s02ZeroAdjEnable.height + _s02ZeroAdjOffsetLimMin.height)
                        + (GUISetting.margin + s02SubTitleScale.height + _s02ScaleOffset.height + _s02ScaleZeroPoint.height)
                        + (GUISetting.margin + s02SubTitleFilter.height + _s02FilterSec.height)
                        + (GUISetting.margin + s02SubTitleLogSensor.height + _s02LogSensorLinearize.height + _s02LogSensorVoltPerDecade.height) + GUISetting.margin
                width:  (parent.width - (GUISetting.line_margin * 3)) / 2
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: sensor01Item.right; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : _sensor02Title
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Sensor port 2")
                }

                NText{
                    id : s02AnalActiveText
                    anchors.right: parent.right; anchors.rightMargin : GUISetting.margin; anchors.verticalCenter: _sensor02Title.verticalCenter

                    text : qsTr("analog active")
                }

                NSwitch{
                    id : _s02AnalActive
                    width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                    anchors.right: s02AnalActiveText.left; anchors.rightMargin : GUISetting.margin; anchors.verticalCenter: s02AnalActiveText.verticalCenter

                    enabled: false
                }

                NComboBox{
                    id : _s02Source
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor02Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS02SourceIdx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: dlgModel.mIsSensor02Support ? ["none", "analog", "digital"] : ["none", "undefined", "digital"]

                    onCurrentIndexChanged: {
                        if(dlgModel.mIsSensor02Support == false && currentIndex == 1)
                            currentIndex = 0

                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02SourceIdx()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02Source.verticalCenter; anchors.left: _s02Source.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("source")
                }

                NComboBox{
                    id : _s02Selection
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor02Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    textColor: dlgModel.mErrS02Selection ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not selected", "selected"]

                    visible: _s02Source.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditSelection()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02Selection.verticalCenter; anchors.left: _s02Selection.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("selection")

                    visible: _s02Source.currentIndex != 0
                }

                NText{
                    id: s02SubTitleRange
                    anchors.top: _s02Selection.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("range")
                    color: "#ACACAC"

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s02Unit
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleRange.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS02UnitIdx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["Pa","bar", "mbar", "ubar", "Torr", "mTorr", "atm", "psi", "psf"]

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02UnitIdx()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02Unit.verticalCenter; anchors.left: _s02Unit.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("unit")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02FullScale
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleRange.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02FullScale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 999999999
                    fixedN : 4

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02FullScale()
                    }

                    onChangedValue: {
                        textField.text = dlgModel.onCommandCheckScaleValue(textField.text)
                        _s02DigiValue.textField.text = dlgModel.onCommandCheckDigitalValue(textField.text, _s02DigiValue.textField.text)
                    }
                }

                NText{
                    anchors.verticalCenter: _s02FullScale.verticalCenter; anchors.left: _s02FullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("full scale")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NText{
                    id: s02SubTitleDigital
                    anchors.top: _s02FullScale.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("digital")
                    color: "#ACACAC"

                    visible: _s02Source.currentIndex == 2 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02DigiValue
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleDigital.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02DigiValue ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -1000000000; maxValue: 1000000000
                    fixedN : 6

                    visible: _s02Source.currentIndex == 2 && _s02Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02DigiValue()
                    }

                    onChangedValue: {
                        textField.text = dlgModel.onCommandCheckDigitalValue(_s02FullScale.textField.text, textField.text)
                    }
                }

                NText{
                    anchors.verticalCenter: _s02DigiValue.verticalCenter; anchors.left: _s02DigiValue.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("digital value")

                    visible: _s02Source.currentIndex == 2 && _s02Selection.currentIndex != 0
                }

                NText{
                    id: s02SubTitleZeroAdj
                    anchors.top: _s02DigiValue.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("zero adjust")
                    color: "#ACACAC"

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s02ZeroAdjEnable
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleZeroAdj.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS02ZeroAdjEnable ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["disabled","enabled"]

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onCurrentIndexChanged: {

                        if(currentIndex == 0)
                        {
                            _s02ZeroAdjOffsetValue.textField.text = "0.00"
                            dlgModel.onCommandSetEditS02ZeroAdjOffsetValue()
                        }

                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02ZeroAdjEnable()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02ZeroAdjEnable.verticalCenter; anchors.left: _s02ZeroAdjEnable.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("enable")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02ZeroAdjOffsetValue
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleZeroAdj.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100 && _s02ZeroAdjEnable.currentIndex == 1

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02ZeroAdjOffsetValue ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -14; maxValue: 14
                    fixedN : 2

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02ZeroAdjOffsetValue()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02ZeroAdjOffsetValue.verticalCenter; anchors.left: _s02ZeroAdjOffsetValue.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset value[% SFS]")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02ZeroAdjOffsetLimMin
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s02ZeroAdjOffsetValue.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02ZeroAdjOffsetLimMin ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -100; maxValue: 0
                    fixedN : 2

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02ZeroAdjEnable.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02ZeroAdjOffsetLimMin()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02ZeroAdjOffsetLimMin.verticalCenter; anchors.left: _s02ZeroAdjOffsetLimMin.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset min[% SFS]")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02ZeroAdjEnable.currentIndex != 0
                }

                NInputNumber{
                    id : _s02ZeroAdjOffsetLimMax
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s02ZeroAdjOffsetValue.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02ZeroAdjOffsetLimMax ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 100
                    fixedN : 2

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02ZeroAdjEnable.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02ZeroAdjOffsetLimMax()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02ZeroAdjOffsetLimMax.verticalCenter; anchors.left: _s02ZeroAdjOffsetLimMax.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("offset max[% SFS]")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02ZeroAdjEnable.currentIndex != 0
                }

                NText{
                    id: s02SubTitleScale
                    anchors.top: _s02ZeroAdjOffsetLimMax.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("scale")
                    color: "#ACACAC"

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02ScaleOffset
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleScale.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02ScaleOffset ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -100; maxValue: 100
                    fixedN : 3

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02ScaleOffset()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02ScaleOffset.verticalCenter; anchors.left: _s02ScaleOffset.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("scale offset[V]")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02Scale
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleScale.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5 //GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02Scale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -10000; maxValue: 10000
                    fixedN : 6

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02Scale()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02Scale.verticalCenter; anchors.left: _s02Scale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("scale")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s02ScaleZeroPoint
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s02Scale.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS02ScaleZeroPoint ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["before scale","after scale"]

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02ScaleZeroPoint()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02ScaleZeroPoint.verticalCenter; anchors.left: _s02ScaleZeroPoint.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("zero point")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NText{
                    id: s02SubTitleFilter
                    anchors.top: _s02ScaleZeroPoint.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("filter")
                    color: "#ACACAC"

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02FilterSec
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleFilter.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02FilterSec ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 1
                    fixedN : 2

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02FilterSec()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02FilterSec.verticalCenter; anchors.left: _s02FilterSec.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("filter time[sec]")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NText{
                    id: s02SubTitleLogSensor
                    anchors.top: _s02FilterSec.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("logarithmic sensor")
                    color: "#ACACAC"

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NComboBox{
                    id : _s02LogSensorLinearize
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: s02SubTitleLogSensor.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrS02LogSensorLinearize ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["no","yes"]

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02LogSensorLinearize()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02LogSensorLinearize.verticalCenter; anchors.left: _s02LogSensorLinearize.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("linearize")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0
                }

                NInputNumber{
                    id : _s02LogSensorVoltPerDecade
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s02LogSensorLinearize.bottom; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02LogSensorVoltPerDecade ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: -9999.999; maxValue: 9999.999
                    fixedN : 3

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02LogSensorLinearize.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02LogSensorVoltPerDecade()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02LogSensorVoltPerDecade.verticalCenter; anchors.left: _s02LogSensorVoltPerDecade.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("voltage per decade")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02LogSensorLinearize.currentIndex != 0
                }

                NInputNumber{
                    id : _s02LogSensorVoltAtFullScale
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _s02LogSensorLinearize.bottom; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrS02LogSensorVoltAtFullScale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 12
                    fixedN : 6

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02LogSensorLinearize.currentIndex != 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditS02LogSensorVoltAtFullScale()
                    }
                }

                NText{
                    anchors.verticalCenter: _s02LogSensorVoltAtFullScale.verticalCenter; anchors.left: _s02LogSensorVoltAtFullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("voltage at full scale")

                    visible: _s02Source.currentIndex != 0 && _s02Selection.currentIndex != 0 && _s02LogSensorLinearize.currentIndex != 0
                }
            }

            Rectangle{
                id : crossoverItem

                height: (GUISetting.margin + crossoverTitle.height)
                        + (GUISetting.margin + _crossoverMod.height) //+ (GUISetting.margin + _crossoverDela.height)
                        + (GUISetting.margin + _crossoverLow.height) //+ (GUISetting.margin + _crossoverHigh.height)
                        + GUISetting.margin
                anchors.top: sensor01Item.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : crossoverTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("crossover")
                }

                NComboBox{
                    id : _crossoverMod
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: crossoverTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrCrossoverModIdx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["soft switch", "hard switch", "target pressure", "high sensor disabled"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditCrossoverModIdx()
                    }
                }

                NText{
                    anchors.verticalCenter: _crossoverMod.verticalCenter; anchors.left: _crossoverMod.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("mod")
                }

                NInputNumber{
                    id : _crossoverDela
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: crossoverTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin


                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrCrossoverDela ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 655.34
                    fixedN : 2

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditCrossoverDela()
                    }
                }

                NText{
                    anchors.verticalCenter: _crossoverDela.verticalCenter; anchors.left: _crossoverDela.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("dela[sec]")
                }

                NInputNumber{
                    id : _crossoverLow
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _crossoverMod.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrCrossoverLow ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 120
                    fixedN : 3

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditCrossoverLow()
                    }
                }

                NText{
                    anchors.verticalCenter: _crossoverLow.verticalCenter; anchors.left: _crossoverLow.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("low[% SFS Low Sensor]")
                }

                NInputNumber{
                    id : _crossoverHigh
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _crossoverMod.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: parent.width * 0.5//GUISetting.margin


                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrCrossoverHigh ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0; maxValue: 129
                    fixedN : 3

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditCrossoverHigh()
                    }
                }

                NText{
                    anchors.verticalCenter: _crossoverHigh.verticalCenter; anchors.left: _crossoverHigh.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("high[% SFS Low Sensor]")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: crossoverItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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
                        anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter

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
