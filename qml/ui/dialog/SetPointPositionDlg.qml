import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import MathUtil 1.0
import UnitUtil 1.0
import SetPointPositionDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property real convertedFullScale
    property real sensorfullScale
    property int  sensorFullScaleUnit
    property int  pressureDpUnit
    property real stdFullScale
    property real pressureConvertFactor
    property int  pressureFixedN : 0

    property real posStdResolution : 100000
    property int  exponent
    property real calcGainToUi
    property real calcGainToValve

    property var body : null

    titleText   : qsTr("Set-Points Adjustment")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function commit()
    {
        body.setPoint01Pos.focusOut();
        body.setPoint02Pos.focusOut();
        body.setPoint03Pos.focusOut();
        body.setPoint04Pos.focusOut();
        body.setPoint05Pos.focusOut();
        body.setPoint06Pos.focusOut();
        body.setPoint01Pressure.focusOut();
        body.setPoint02Pressure.focusOut();
        body.setPoint03Pressure.focusOut();
        body.setPoint04Pressure.focusOut();
        body.setPoint05Pressure.focusOut();
        body.setPoint06Pressure.focusOut();

        var pos01  = parseInt(body.setPoint01Pos.textField.text) * calcGainToUi
        var pos02  = parseInt(body.setPoint02Pos.textField.text) * calcGainToUi
        var pos03  = parseInt(body.setPoint03Pos.textField.text) * calcGainToUi
        var pos04  = parseInt(body.setPoint04Pos.textField.text) * calcGainToUi
        var pos05  = parseInt(body.setPoint05Pos.textField.text) * calcGainToUi
        var pos06  = parseInt(body.setPoint06Pos.textField.text) * calcGainToUi


        var pressure01 = parseFloat(body.setPoint01Pressure.textField.text)
        pressure01 = Math.round(dialog.stdFullScale * (pressure01 / dialog.convertedFullScale))

        var pressure02 = parseFloat(body.setPoint02Pressure.textField.text)
        pressure02 = Math.round(dialog.stdFullScale * (pressure02 / dialog.convertedFullScale))

        var pressure03 = parseFloat(body.setPoint03Pressure.textField.text)
        pressure03 = Math.round(dialog.stdFullScale * (pressure03 / dialog.convertedFullScale))

        var pressure04 = parseFloat(body.setPoint04Pressure.textField.text)
        pressure04 = Math.round(dialog.stdFullScale * (pressure04 / dialog.convertedFullScale))

        var pressure05 = parseFloat(body.setPoint05Pressure.textField.text)
        pressure05 = Math.round(dialog.stdFullScale * (pressure05 / dialog.convertedFullScale))

        var pressure06 = parseFloat(body.setPoint06Pressure.textField.text)
        pressure06 = Math.round(dialog.stdFullScale * (pressure06 / dialog.convertedFullScale))

        dlgModel.onCommandApply(pos01,pos02,pos03,pos04,pos05,pos06,pressure01,pressure02,pressure03,pressure04,pressure05,pressure06);
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = body.width

        dialog.exponent = MathUtil.log10round(posStdResolution) - MathUtil.log10round(dlgModel.mPosResolution)
        dialog.calcGainToUi = Math.pow(10,exponent)
        dialog.calcGainToValve = Math.pow(10,-1*exponent)
    }

    SetPointPositionDlgModel{
        id : dlgModel

        onSignalEventChangedPosition01: {body.setPoint01Pos.setValue(mPosition01 * dialog.calcGainToValve)}
        onSignalEventChangedPosition02: {body.setPoint02Pos.setValue(mPosition02 * dialog.calcGainToValve)}
        onSignalEventChangedPosition03: {body.setPoint03Pos.setValue(mPosition03 * dialog.calcGainToValve)}
        onSignalEventChangedPosition04: {body.setPoint04Pos.setValue(mPosition04 * dialog.calcGainToValve)}
        onSignalEventChangedPosition05: {body.setPoint05Pos.setValue(mPosition05 * dialog.calcGainToValve)}
        onSignalEventChangedPosition06: {body.setPoint06Pos.setValue(mPosition06 * dialog.calcGainToValve)}

        onSignalEventChangedPressure01: {
            var convertedPressure = UnitUtil.convert(sensorFullScaleUnit, (mPressure01 * dialog.pressureConvertFactor), dialog.pressureDpUnit)
            body.setPoint01Pressure.setValue(convertedPressure)
        }
        onSignalEventChangedPressure02: {
            var convertedPressure = UnitUtil.convert(sensorFullScaleUnit, (mPressure02 * dialog.pressureConvertFactor), dialog.pressureDpUnit)
            body.setPoint02Pressure.setValue(convertedPressure)
        }
        onSignalEventChangedPressure03: {
            var convertedPressure = UnitUtil.convert(sensorFullScaleUnit, (mPressure03 * dialog.pressureConvertFactor), dialog.pressureDpUnit)
            body.setPoint03Pressure.setValue(convertedPressure)
        }
        onSignalEventChangedPressure04: {
            var convertedPressure = UnitUtil.convert(sensorFullScaleUnit, (mPressure04 * dialog.pressureConvertFactor), dialog.pressureDpUnit)
            body.setPoint04Pressure.setValue(convertedPressure)
        }
        onSignalEventChangedPressure05: {
            var convertedPressure = UnitUtil.convert(sensorFullScaleUnit, (mPressure05 * dialog.pressureConvertFactor), dialog.pressureDpUnit)
            body.setPoint05Pressure.setValue(convertedPressure)
        }
        onSignalEventChangedPressure06: {
            var convertedPressure = UnitUtil.convert(sensorFullScaleUnit, (mPressure06 * dialog.pressureConvertFactor), dialog.pressureDpUnit)
            body.setPoint06Pressure.setValue(convertedPressure)
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias setPoint01Pos : _setPoint01Pos
            property alias setPoint02Pos : _setPoint02Pos
            property alias setPoint03Pos : _setPoint03Pos
            property alias setPoint04Pos : _setPoint04Pos
            property alias setPoint05Pos : _setPoint05Pos
            property alias setPoint06Pos : _setPoint06Pos

            property alias setPoint01Pressure : _setPoint01Pressure
            property alias setPoint02Pressure : _setPoint02Pressure
            property alias setPoint03Pressure : _setPoint03Pressure
            property alias setPoint04Pressure : _setPoint04Pressure
            property alias setPoint05Pressure : _setPoint05Pressure
            property alias setPoint06Pressure : _setPoint06Pressure
            property real   guiScale          : GUISetting.scale

            height: (GUISetting.line_margin + setPointPositionItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin);
            width : (GUISetting.line_margin + setPointPositionItem.width) + (GUISetting.line_margin + setPointPressureItem.width) + GUISetting.line_margin
            anchors.left: parent.left; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = width
            }

            Rectangle{
                id : setPointPositionItem

                height: (GUISetting.margin + positionItemTitle.height)
                        + (GUISetting.margin + _setPoint01Pos.height)
                        + (GUISetting.margin + _setPoint02Pos.height)
                        + (GUISetting.margin + _setPoint03Pos.height)
                        + (GUISetting.margin + _setPoint04Pos.height)
                        + (GUISetting.margin + _setPoint05Pos.height)
                        + (GUISetting.margin + _setPoint06Pos.height)
                        + (GUISetting.margin + positionMax.height) + GUISetting.margin;
                width : 250 * GUISetting.scale
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : positionItemTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Position set-points")
                }

                NInputNumber{
                    id : _setPoint01Pos
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: positionItemTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: IntValidator{}
                    textField.color: dlgModel.mErrPosition01 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue:-1 * Math.floor(dlgModel.mPosResolution * ( 99999 / 100000)); maxValue: Math.floor(dlgModel.mPosResolution *  (999999 / 100000))
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint01Pos.verticalCenter; anchors.left: _setPoint01Pos.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 1")
                }

                NInputNumber{
                    id : _setPoint02Pos
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint01Pos.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: IntValidator{}
                    textField.color: dlgModel.mErrPosition02 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue:-1 * Math.floor(dlgModel.mPosResolution * ( 99999 / 100000)); maxValue: Math.floor(dlgModel.mPosResolution *  (999999 / 100000))
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint02Pos.verticalCenter; anchors.left: _setPoint02Pos.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 2")
                }

                NInputNumber{
                    id : _setPoint03Pos
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint02Pos.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: IntValidator{}
                    textField.color: dlgModel.mErrPosition02 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue:-1 * Math.floor(dlgModel.mPosResolution * ( 99999 / 100000)); maxValue: Math.floor(dlgModel.mPosResolution *  (999999 / 100000))
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint03Pos.verticalCenter; anchors.left: _setPoint03Pos.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 3")
                }

                NInputNumber{
                    id : _setPoint04Pos
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint03Pos.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: IntValidator{}
                    textField.color: dlgModel.mErrPosition04 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue:-1 * Math.floor(dlgModel.mPosResolution * ( 99999 / 100000)); maxValue: Math.floor(dlgModel.mPosResolution *  (999999 / 100000))
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint04Pos.verticalCenter; anchors.left: _setPoint04Pos.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 4")
                }

                NInputNumber{
                    id : _setPoint05Pos
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint04Pos.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: IntValidator{}
                    textField.color: dlgModel.mErrPosition05 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue:-1 * Math.floor(dlgModel.mPosResolution * ( 99999 / 100000)); maxValue: Math.floor(dlgModel.mPosResolution *  (999999 / 100000))
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint05Pos.verticalCenter; anchors.left: _setPoint05Pos.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 5")
                }

                NInputNumber{
                    id : _setPoint06Pos
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint05Pos.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: IntValidator{}
                    textField.color: dlgModel.mErrPosition06 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue:-1 * Math.floor(dlgModel.mPosResolution * ( 99999 / 100000)); maxValue: Math.floor(dlgModel.mPosResolution *  (999999 / 100000))//  -1 * (dlgModel.mPosResolution *  ( 99999 / 100000)); maxValue: dlgModel.mPosResolution *  ( 999999 / 100000)
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint06Pos.verticalCenter; anchors.left: _setPoint06Pos.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 6")
                }

                NText{
                    id : positionMax
                    anchors.top: _setPoint06Pos.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#24A7FF"
                    text : qsTr("max position : ") + dlgModel.mPosResolution
                }
            }


            Rectangle{
                id : setPointPressureItem

                height: (GUISetting.margin + pressureItemTitle.height)
                        + (GUISetting.margin + _setPoint01Pressure.height)
                        + (GUISetting.margin + _setPoint02Pressure.height)
                        + (GUISetting.margin + _setPoint03Pressure.height)
                        + (GUISetting.margin + _setPoint04Pressure.height)
                        + (GUISetting.margin + _setPoint05Pressure.height)
                        + (GUISetting.margin + _setPoint06Pressure.height)
                        + (GUISetting.margin + pressureMax.height) + GUISetting.margin;
                width : 250 * GUISetting.scale
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: setPointPositionItem.right; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : pressureItemTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Pressure set-points")
                }

                NInputNumber{
                    id : _setPoint01Pressure
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: pressureItemTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrPressure01 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 1; maxValue: dialog.convertedFullScale
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint01Pressure.verticalCenter; anchors.left: _setPoint01Pressure.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 1")
                }

                NInputNumber{
                    id : _setPoint02Pressure
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint01Pressure.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrPressure02 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 1; maxValue: dialog.convertedFullScale
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint02Pressure.verticalCenter; anchors.left: _setPoint02Pressure.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 2")
                }

                NInputNumber{
                    id : _setPoint03Pressure
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint02Pressure.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrPressure03 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 1; maxValue: dialog.convertedFullScale
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint03Pressure.verticalCenter; anchors.left: _setPoint03Pressure.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 3")
                }

                NInputNumber{
                    id : _setPoint04Pressure
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint03Pressure.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrPressure04 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 1; maxValue: dialog.convertedFullScale
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint04Pressure.verticalCenter; anchors.left: _setPoint04Pressure.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 4")
                }

                NInputNumber{
                    id : _setPoint05Pressure
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint04Pressure.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrPressure05 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 1; maxValue: dialog.convertedFullScale
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint05Pressure.verticalCenter; anchors.left: _setPoint05Pressure.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 5")
                }

                NInputNumber{
                    id : _setPoint06Pressure
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _setPoint05Pressure.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrPressure06 ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 1; maxValue: dialog.convertedFullScale
                    fixedN : dialog.pressureFixedN

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _setPoint06Pressure.verticalCenter; anchors.left: _setPoint06Pressure.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("set-point 6")
                }

                NText{
                    id : pressureMax
                    anchors.top: _setPoint06Pressure.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#24A7FF"
                    text : qsTr("max pressure : ") + (dialog.convertedFullScale).toLocaleString( FontManager.locale, 'f', dialog.pressureFixedN)
                }

                NText{
                    id : pressureUnit
                    anchors.verticalCenter: pressureMax.verticalCenter; anchors.left: pressureMax.right; anchors.leftMargin: GUISetting.margin
                    color: "#24A7FF"
                    text : dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PA    ? "[pa]"   :
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_BAR   ? "[bar]"  :
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MBAR  ? "[mbar]" :
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_UBAR  ? "[ubar]" :
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_TORR  ? "[Torr]" :
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MTORR ? "[mTorr]":
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_ATM   ? "[atm]"  :
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSI   ? "[psi]"  :
                           dialog.pressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSF   ? "[psf]"  : ""
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: setPointPositionItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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
