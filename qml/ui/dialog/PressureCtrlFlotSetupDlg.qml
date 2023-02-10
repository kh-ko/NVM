import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import PressureCtrlFloatSetupDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property int selControlModel : dlgModel.mSelControl
    property var body : null

    signal signalEventOccurErr()

    titleText   : qsTr("Pressure control setup")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit
    bodyWidth   : 600
    isModal     : false

    function commit()
    {
        dlgModel.onCommandApply(dialog.selControlModel             ,
                                parseFloat(body.adapGainFactor.textField.text ).toFixed(body.adapGainFactor.fixedN ),
                                parseFloat(body.adapDeltaFactor.textField.text).toFixed(body.adapDeltaFactor.fixedN ),
                                parseFloat(body.adapSensorDelay.textField.text).toFixed(body.adapSensorDelay.fixedN),
                                parseFloat(body.adapRampTime.textField.text   ).toFixed(body.adapRampTime.fixedN   ),
                                body.adapRampMode.currentIndex     ,
                                parseFloat(body.fixed1PGain.textField.text    ).toFixed(body.fixed1PGain.fixedN    ),
                                parseFloat(body.fixed1IGain.textField.text    ).toFixed(body.fixed1IGain.fixedN    ),
                                parseFloat(body.fixed1RampTime.textField.text ).toFixed(body.fixed1RampTime.fixedN ),
                                body.fixed1RampMode.currentIndex   ,
                                body.fixed1CtrlDir.currentIndex    ,
                                parseFloat(body.fixed2PGain.textField.text    ).toFixed(body.fixed2PGain.fixedN    ),
                                parseFloat(body.fixed2IGain.textField.text    ).toFixed(body.fixed2IGain.fixedN    ),
                                parseFloat(body.fixed2RampTime.textField.text ).toFixed(body.fixed2RampTime.fixedN ),
                                body.fixed2RampMode.currentIndex   ,
                                body.fixed2CtrlDir.currentIndex    )
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = body.width
    }

    PressureCtrlFloatSetupDlgModel{
        id : dlgModel

        onSignalEventOccurErr: {
            dialog.signalEventOccurErr()
        }

        onSignalEventCompletedLoad: {
            dialog.selControlModel              = dlgModel.mSelControl
            body.adapGainFactor.textField.text  = dlgModel.mAdapGainFactor
            body.adapSensorDelay.textField.text = dlgModel.mAdapSensorDelay
            body.adapRampTime.textField.text    = dlgModel.mAdapRampTime
            body.adapRampMode.currentIndex      = dlgModel.mAdapRampMode
            body.fixed1PGain.textField.text     = dlgModel.mFixed1PGain
            body.fixed1IGain.textField.text     = dlgModel.mFixed1IGain
            body.fixed1RampTime.textField.text  = dlgModel.mFixed1RampTime
            body.fixed1RampMode.currentIndex    = dlgModel.mFixed1RampMode
            body.fixed1CtrlDir.currentIndex     = dlgModel.mFixed1CtrlDir
            body.fixed2PGain.textField.text     = dlgModel.mFixed2PGain
            body.fixed2IGain.textField.text     = dlgModel.mFixed2IGain
            body.fixed2RampTime.textField.text  = dlgModel.mFixed2RampTime
            body.fixed2RampMode.currentIndex    = dlgModel.mFixed2RampMode
            body.fixed2CtrlDir.currentIndex     = dlgModel.mFixed2CtrlDir

            if(dlgModel.mEnableDeltaFactor)
                body.adapDeltaFactor.textField.text = dlgModel.mAdapDeltaFactor

            onCommandSetEdit(false);
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias adapGainFactor  : _adapGainFactor
            property alias adapDeltaFactor : _adapDeltaFactor
            property alias adapSensorDelay : _adapSensorDelay
            property alias adapRampTime    : _adapRampTime
            property alias adapRampMode    : _adapRampMode
            property alias fixed1PGain     : _fixed1PGain
            property alias fixed1IGain     : _fixed1IGain
            property alias fixed1RampTime  : _fixed1RampTime
            property alias fixed1RampMode  : _fixed1RampMode
            property alias fixed1CtrlDir   : _fixed1CtrlDir
            property alias fixed2PGain     : _fixed2PGain
            property alias fixed2IGain     : _fixed2IGain
            property alias fixed2RampTime  : _fixed2RampTime
            property alias fixed2RampMode  : _fixed2RampMode
            property alias fixed2CtrlDir   : _fixed2CtrlDir
            property real  guiScale        : GUISetting.scale

            height: (GUISetting.line_margin + fixed1Item.height) + (GUISetting.line_margin + fixed1Item.height) + (GUISetting.line_margin + btnBox.height + 2);
            width : 800 * GUISetting.scale
            anchors.left: parent.left; /*anchors.right: parent.right;*/ anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = width
            }

            Rectangle{
                id : adapItem

                height:  (GUISetting.margin + adapTitle.height       )
                        +(GUISetting.margin + _adapSelect.height     )
                        +(GUISetting.margin + _adapGainFactor.height )
                        +(GUISetting.margin + _adapDeltaFactor.height)
                        +(GUISetting.margin + _adapSensorDelay.height)
                        +(GUISetting.margin + _adapRampTime.height   )
                        +(GUISetting.margin + _adapRampMode.height   ) + GUISetting.margin
                width: (parent.width - (GUISetting.line_margin * 3)) / 2
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : adapTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("adaptive downstream")
                }

                Item{
                    id : _adapSelect
                    height: 24 * GUISetting.scale
                    anchors.top: adapTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    enabled: dialog.progress === 100

                    NSwitch{
                        id : adapSelSwitch
                        width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.left: parent.left;
                        enabled: parent.enabled
                        isSelect: dialog.selControlModel == ValveEnumDef.PRESSURE_CTRL_ADAPTIVE

                        onSignalEventSelected: {
                            dialog.selControlModel = ValveEnumDef.PRESSURE_CTRL_ADAPTIVE
                            dlgModel.onCommandSetEdit(true)
                            dlgModel.onCommandSetEditSelControl()
                        }
                    }

                    NText{
                        anchors.verticalCenter: adapSelSwitch.verticalCenter; anchors.left: adapSelSwitch.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("active")
                    }
                }

                NInputNumber{
                    id : _adapGainFactor
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _adapSelect.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrAdapGainFactor ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0; maxValue: 100
                    fixedN : 4

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditAdapGainFactor()
                    }
                }

                NText{
                    anchors.verticalCenter: _adapGainFactor.verticalCenter; anchors.left: _adapGainFactor.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("gain factor(0.0000 ~ 100.0000)")
                }

                NInputNumber{
                    id : _adapDeltaFactor
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _adapGainFactor.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100 && dlgModel.mEnableDeltaFactor

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrAdapDeltaFactor ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0; maxValue: 100
                    fixedN : 4

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditAdapDeltaFactor()
                    }
                }

                NText{
                    anchors.verticalCenter: _adapDeltaFactor.verticalCenter; anchors.left: _adapDeltaFactor.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("delta factor(0.0000 ~ 100.0000)")
                }

                NInputNumber{
                    id : _adapSensorDelay
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _adapDeltaFactor.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrAdapSensorDelay ? "#FF0000" : "#000000"
                    stepValue : 0.01; minValue: 0; maxValue: 1
                    fixedN : 2

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditAdapSensorDelay()
                    }
                }

                NText{
                    anchors.verticalCenter: _adapSensorDelay.verticalCenter; anchors.left: _adapSensorDelay.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("sensor delay(0.00 sec ~ 1.00 sec)")
                }

                NInputNumber{
                    id : _adapRampTime
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _adapSensorDelay.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrAdapRampTime ? "#FF0000" : "#000000"
                    stepValue : 0.01; minValue: 0; maxValue: 10000 //9.99
                    fixedN : 2

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditAdapRampTime()
                    }
                }

                NText{
                    anchors.verticalCenter: _adapRampTime.verticalCenter; anchors.left: _adapRampTime.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("ramp time(0.00 sec ~ 10000.00 sec)")
                }


                NComboBox{
                    id : _adapRampMode
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _adapRampTime.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrAdapRampMode ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["constant time", "constant slope"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditAdapRampMode()
                    }
                }

                NText{
                    anchors.verticalCenter: _adapRampMode.verticalCenter; anchors.left: _adapRampMode.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("ramp mode")
                }
            }

            Rectangle{
                id : fixed1Item

                height:   (GUISetting.margin + fixed1Title.height    )
                        + (GUISetting.margin + _fixed1Select.height  )
                        + (GUISetting.margin + _fixed1PGain.height   )
                        + (GUISetting.margin + _fixed1IGain.height   )
                        + (GUISetting.margin + _fixed1RampTime.height)
                        + (GUISetting.margin + _fixed1RampMode.height)
                        + (GUISetting.margin + _fixed1CtrlDir.height ) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: adapItem.right; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : fixed1Title
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("fixed 1")
                }

                Item{
                    id : _fixed1Select

                    height: 24 * GUISetting.scale;
                    anchors.top: fixed1Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    enabled: dialog.progress === 100

                    NSwitch{
                        id : fixed1SelSwitch
                        width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.left: parent.left;
                        enabled: parent.enabled
                        isSelect: dialog.selControlModel == ValveEnumDef.PRESSURE_CTRL_FIXED_DOWN

                        onSignalEventSelected: {
                            dialog.selControlModel = ValveEnumDef.PRESSURE_CTRL_FIXED_DOWN
                            dlgModel.onCommandSetEdit(true)
                            dlgModel.onCommandSetEditSelControl()
                        }
                    }

                    NText{
                        anchors.verticalCenter: fixed1SelSwitch.verticalCenter; anchors.left: fixed1SelSwitch.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("active")
                    }
                }

                NInputNumber{
                    id : _fixed1PGain
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed1Select.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFixed1PGain ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0; maxValue: 100
                    fixedN : 4

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed1PGain()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed1PGain.verticalCenter; anchors.left: _fixed1PGain.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("P-gain(0.0000 ~ 100.0000)")
                }

                NInputNumber{
                    id : _fixed1IGain
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed1PGain.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFixed1IGain ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0.0000; maxValue: 100
                    fixedN : 4

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed1IGain()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed1IGain.verticalCenter; anchors.left: _fixed1IGain.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("I-gain(0.0000 ~ 100.0000)")
                }

                NInputNumber{
                    id : _fixed1RampTime
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed1IGain.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFixed1RampTime ? "#FF0000" : "#000000"
                    stepValue : 0.01; minValue: 0; maxValue: 10000 //9.99//00000
                    fixedN : 2

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed1RampTime()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed1RampTime.verticalCenter; anchors.left: _fixed1RampTime.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("ramp time(0.00 sec ~ 10000.00 sec)")
                }


                NComboBox{
                    id : _fixed1RampMode
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed1RampTime.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrFixed1RampMode ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["constant time", "constant slope"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed1RampMode()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed1RampMode.verticalCenter; anchors.left: _fixed1RampMode.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("ramp mode")
                }

                NComboBox{
                    id : _fixed1CtrlDir
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed1RampMode.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrFixed1CtrlDir ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["downstream", "upstream"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed1CtrlDir()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed1CtrlDir.verticalCenter; anchors.left: _fixed1CtrlDir.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("control direction")
                }
            }

            Rectangle{
                id : fixed2Item

                height:   (GUISetting.margin + fixed2Title.height    )
                        + (GUISetting.margin + _fixed2Select.height  )
                        + (GUISetting.margin + _fixed2PGain.height   )
                        + (GUISetting.margin + _fixed2IGain.height   )
                        + (GUISetting.margin + _fixed2RampTime.height)
                        + (GUISetting.margin + _fixed2RampMode.height)
                        + (GUISetting.margin + _fixed2CtrlDir.height ) + GUISetting.margin
                anchors.top: fixed1Item.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: adapItem.right; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : fixed2Title
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("fixed 2")
                }

                Item{
                    id : _fixed2Select

                    height: 24 * GUISetting.scale;
                    anchors.top: fixed2Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    enabled: dialog.progress === 100

                    NSwitch{
                        id : fixed2SelSwitch
                        width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.left: parent.left;
                        enabled: parent.enabled
                        isSelect: dialog.selControlModel == ValveEnumDef.PRESSURE_CTRL_FIXED_UP

                        onSignalEventSelected: {
                            dialog.selControlModel = ValveEnumDef.PRESSURE_CTRL_FIXED_UP
                            dlgModel.onCommandSetEdit(true)
                            dlgModel.onCommandSetEditSelControl()
                        }
                    }

                    NText{
                        anchors.verticalCenter: fixed2SelSwitch.verticalCenter; anchors.left: fixed2SelSwitch.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("active")
                    }
                }

                NInputNumber{
                    id : _fixed2PGain
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed2Select.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFixed2PGain ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0; maxValue: 100
                    fixedN : 4

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed2PGain()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed2PGain.verticalCenter; anchors.left: _fixed2PGain.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("P-gain(0.0000 ~ 100.0000)")
                }

                NInputNumber{
                    id : _fixed2IGain
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed2PGain.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFixed2IGain ? "#FF0000" : "#000000"
                    stepValue : 0.0001; minValue: 0.0000; maxValue: 100
                    fixedN : 4

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed2IGain()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed2IGain.verticalCenter; anchors.left: _fixed2IGain.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("I-gain(0.0000 ~ 100.0000)")
                }

                NInputNumber{
                    id : _fixed2RampTime
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed2IGain.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFixed2RampTime ? "#FF0000" : "#000000"
                    stepValue : 0.01; minValue: 0; maxValue: 10000// 9.99//00000
                    fixedN : 2

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed2RampTime()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed2RampTime.verticalCenter; anchors.left: _fixed2RampTime.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("ramp time(0.00 sec ~ 10000.00 secs)")
                }


                NComboBox{
                    id : _fixed2RampMode
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed2RampTime.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrFixed2RampMode ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["constant time", "constant slope"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed2RampMode()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed2RampMode.verticalCenter; anchors.left: _fixed2RampMode.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("ramp mode")
                }

                NComboBox{
                    id : _fixed2CtrlDir
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _fixed2RampMode.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrFixed2CtrlDir ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["downstream", "upstream"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                        dlgModel.onCommandSetEditFixed2CtrlDir()
                    }
                }

                NText{
                    anchors.verticalCenter: _fixed2CtrlDir.verticalCenter; anchors.left: _fixed2CtrlDir.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("control direction")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: fixed2Item.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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
                        width: GUISetting.exbtnitem_on_width; height: GUISetting.exbtnitem_on_height
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
