import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import ControlLearnDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null
    property bool isRunning : dlgModel.mRunning !== ValveEnumDef.LEARN_RUN_STATE_NOT_RUNNING

    titleText    : qsTr("Learn")
    progress     : dlgModel.mProgress
    strStatus    : dlgModel.mStrStatus
    errMsg       : dlgModel.mErrMsg
    errMsg2      : dlgModel.mErrMsg2
    access       : dlgModel.mAccessMode
    isRS232Test  : dlgModel.mIsRS232Test
    isEdit       : false
    doNotDestroy : true

    function openLearnChangeAccessDlg(caller)
    {
        var popup = learnChangeAccessDlg.createObject(dialog)
        popup.caller = caller
        popup.open();
    }

    function learn()
    {
        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            dialog.openLearnChangeAccessDlg(interfaceLearn)
            return;
        }

        interfaceLearn.commit()
    }

    function terminateLearn()
    {
        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            dialog.openLearnChangeAccessDlg(interfaceTerminateLearn)
            return;
        }

        interfaceTerminateLearn.commit()
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyWidth  = GUISetting.popup_nor_width
        //bodyHeight = body.height
    }

    Item{
        id : interfaceLearn

        function commit()
        {
            var pressureLimit = parseFloat(body.pressureLimitInput.textField.text);

            var pressureLimitRatio = Math.round(1000000 * (pressureLimit / dlgModel.mSensorFullScale));
            dlgModel.onCommandLearn(pressureLimitRatio)
        }

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }
    }

    Item{
        id : interfaceTerminateLearn

        function commit()
        {
            body.pressureLimitInput.focusOut();
            var pressureLimit = parseFloat(body.pressureLimitInput.textField.text);

            dlgModel.onCommandTerminateLearn()
        }

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }
    }

    onVisibleChanged: {
        if(visible == false)
            dlgModel.onCommandDlgClosed();
        else
        {
            body.pressureLimitInput.setValue(dlgModel.mSensorFullScale)
            body.pressureLimitInput.maxValue = dlgModel.mSensorFullScale
            dlgModel.onCommandDlgOpened();
        }
    }

    ControlLearnDlgModel{
        id : dlgModel

        Component.onCompleted: {

        }

        onSignalEventChangedRunning: {
            if(mRunning == ValveEnumDef.LEARN_RUN_STATE_NOT_RUNNING && visible == false)
            {
                show();
            }
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias  pressureLimitInput: _PressureLimitInput
            property real   guiScale          : GUISetting.scale

            height: dlgModel.mIsShowState ? learnStateItem.height : learnReadyItem.height
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onHeightChanged: {
                dialog.bodyHeight = height
                dialog.bodyWidth  = GUISetting.popup_nor_width
            }

            onGuiScaleChanged: {
                dialog.bodyHeight = height
                dialog.bodyWidth  = GUISetting.popup_nor_width
            }

            Item {
                id : learnReadyItem
                height: (GUISetting.line_margin + pressureLimitItem.height) + (GUISetting.line_margin + btnBox.height) + GUISetting.line_margin
                anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
                visible: dlgModel.mIsShowState == false

                Rectangle{
                    id : pressureLimitItem

                    height: (GUISetting.margin + pressureLimitTitle.height) + (GUISetting.margin + _PressureLimitInput.height) + GUISetting.margin
                    anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                    color: "#FFFFFF"

                    NText{
                        id : pressureLimitTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text : qsTr("Pressure limit")
                    }

                    NInputNumber{
                        id : _PressureLimitInput
                        width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: pressureLimitTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100 && dlgModel.mIsShowState === false

                        textField.validator: DoubleValidator{}
                        stepValue : 1; minValue: 0.0001; maxValue: 10000
                        fixedN : 4
                    }

                    NText{
                        id : pressureLimitUnit
                        height: 24 * GUISetting.scale
                        anchors.verticalCenter: _PressureLimitInput.verticalCenter; anchors.left: _PressureLimitInput.right; anchors.leftMargin: GUISetting.margin / 2;
                        horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                        text : dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_PA    ? "pa"  :
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_BAR   ? "bar"  :
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_MBAR  ? "mbar" :
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_UBAR  ? "ubar" :
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_TORR  ? "Torr" :
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_MTORR ? "mTorr":
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_ATM   ? "atm"  :
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_PSI   ? "psi"  :
                               dlgModel.mSensorFullScaleUnit === ValveEnumDef.PRESSURE_UNIT_PSF   ? "psf"  : ""
                    }
                }

                Rectangle{
                    id : btnBox
                    height: GUISetting.popup_btnbox_height;
                    anchors.top: pressureLimitItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                    color: "#FFFFFF"

                    RowLayout{
                        height: GUISetting.popup_btnbox_btn_height; width: parent.width * 0.7
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        spacing: GUISetting.margin

                        NButton{
                            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                            enabled: dialog.progress === 100 && dlgModel.mIsShowState === false

                            bgColor: "#24A7FF"
                            text.color: "#FFFFFF"
                            text.text: qsTr("Learn")

                            onClick: {
                                dialog.learn()
                            }
                        }
                    }
                }
            }

            Item{
                id : learnStateItem
                height: (GUISetting.line_margin + stateItem.height) + (GUISetting.line_margin + terminateBtnBox.height) + GUISetting.line_margin
                anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top
                visible: dlgModel.mIsShowState

                Rectangle{
                    id : stateItem
                    height: (GUISetting.margin + stateTitle.height) + (GUISetting.margin + stateIndi.height) + (GUISetting.margin + stateFinishLabel.height) + (GUISetting.margin + abortBox.height) + GUISetting.margin
                    anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                    color: "#FFFFFF"

                    NText{
                        id : stateTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text : qsTr("Learn state")
                    }

                    Item{
                        id : stateIndi
                        width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: stateTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;

                        opacity: dlgModel.mRunning === ValveEnumDef.LEARN_RUN_STATE_RUNNING ? 1 : 0.3

                        NCircleIndicator{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                            running: dlgModel.mRunning === ValveEnumDef.LEARN_RUN_STATE_RUNNING
                            color: "#24A7FF"
                        }
                    }

                    NText{
                        id : stateRunningLabel
                        anchors.verticalCenter: stateIndi.verticalCenter; anchors.left: stateIndi.right; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        opacity: dlgModel.mRunning === ValveEnumDef.LEARN_RUN_STATE_RUNNING ? 1 : 0.3
                        text : qsTr("Learn running")
                    }

                    NText{
                        id : stateFinishLabel
                        anchors.top: stateIndi.bottom; anchors.topMargin: 10; anchors.left: stateIndi.right; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        visible: dlgModel.mRunning !== ValveEnumDef.LEARN_RUN_STATE_RUNNING
                        text : qsTr("Learn finish")
                    }

                    Item{
                        id : abortBox
                        height: (abortIcon.height)
                        anchors.top: stateFinishLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        visible: dlgModel.mRunning !== ValveEnumDef.LEARN_RUN_STATE_RUNNING

                        Image{
                            id : abortIcon
                            width: 24 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: parent.top; anchors.left: parent.left;
                            source: dlgModel.mAbort === ValveEnumDef.LEARN_ABORT_OK ?  "/image/icon-info.png" : "/image/icon-warning.png"
                        }

                        NText{
                            id : stateAbortLabel
                            anchors.verticalCenter: abortIcon.verticalCenter; anchors.left: abortIcon.right; anchors.leftMargin: GUISetting.margin;
                            isBold: true
                            text : dlgModel.mAbort === ValveEnumDef.LEARN_ABORT_OK ? qsTr("Learn completed") :
                                   dlgModel.mAbort === ValveEnumDef.LEARN_ABORT_USER ? qsTr("Fail by user") :
                                   (dlgModel.mAbortCause === ValveEnumDef.LEARN_ABORT_OPEN_PRESSURE_TOO_HEIGHT) ? qsTr("Fail by control unit : > 50% learn pressure limit (gas flow too high)") :
                                   (dlgModel.mAbortCause === ValveEnumDef.LEARN_ABORT_CLOSE_PRESSURE_TOO_LOW  ) ? qsTr("Fail by control unit : < 10% learn pressure limit (gas flow too low)") :
                                   (dlgModel.mAbortCause === ValveEnumDef.LEARN_ABORT_PRESSURE_RAISING        ) ? qsTr("Fail by control unit : pressure not raising during LEARN (gasflow missing)") :
                                   (dlgModel.mAbortCause === ValveEnumDef.LEARN_ABORT_PRESSURE_UNSTABLE       ) ? qsTr("Fail by control unit : sensor unstable during LEARN") :
                                   (dlgModel.mAbortCause === ValveEnumDef.LEARN_ABORT_NEGATIVE_OPEN_PRESSURE  ) ? qsTr("Fail by control unit : negative open pressure") :
                                   (dlgModel.mAbortCause === ValveEnumDef.LEARN_ABORT_IS_NOT_OPEN_PRESSURE    ) ? qsTr("Fail by control unit : valve was not opened at start") : ""
                        }
                    }
                }

                Rectangle{
                    id : terminateBtnBox
                    height: GUISetting.popup_btnbox_height;
                    anchors.top: stateItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                    color: "#FFFFFF"

                    RowLayout{
                        height: GUISetting.popup_btnbox_btn_height; width: parent.width * 0.7
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        spacing: GUISetting.margin
/*
                        NButton{
                            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

                            bgColor: "#24A7FF"
                            text.color: "#FFFFFF"
                            text.text: qsTr("Close")

                            onClick: {
                                dialog.close()
                            }
                        }
*/
                        NButton{
                            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                            enabled: dlgModel.mRunning === ValveEnumDef.LEARN_RUN_STATE_RUNNING

                            bgColor: "#FFFFFF"
                            text.text: qsTr("Terminate learn")

                            onClick: {
                                dialog.terminateLearn()
                            }
                        }
                    }
                }
            }
        }
    }

    Component{
        id : learnChangeAccessDlg
        ChangeAccessDlg{
        }
    }
}
