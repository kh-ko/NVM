import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import ValveCalibrationExDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null
    property string selectBtn : ""

    titleText   : qsTr("ADC calibration")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : false

    function adcGainCalibration(btnName)
    {
        selectBtn = btnName

        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            var popup = changeAccessDlg.createObject(dialog)
            popup.caller = adcGainCalibFunc
            popup.open();
            return;
        }

        adcGainCalibFunc.onResultChangeAccess(true)
    }

    function adcZeroCalibration(btnName)
    {
        selectBtn = btnName

        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            var popup = changeAccessDlg.createObject(dialog)
            popup.caller = adcZeroCalibFunc
            popup.open();
            return;
        }

        adcZeroCalibFunc.onResultChangeAccess(true)
    }

    Item{
        id : adcGainCalibFunc

        function onResultChangeAccess(value)
        {
            if(value)
            {
                dlgModel.onCommandGainCalibration(selectBtn)
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }
    }

    Item{
        id : adcZeroCalibFunc

        function onResultChangeAccess(value)
        {
            if(value)
            {
                dlgModel.onCommandZeroCalibration(selectBtn)
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth = GUISetting.popup_nor_width
    }

    ValveCalibrationExDlgModel{
        id : dlgModel

        onSignalEventResult:
        {
            if(isSucc)
            {
                showMessage(qsTr("Caribration is Completed"))
            }
            else
            {
                showErrMessage(errMsg)
            }
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real guiScale : GUISetting.scale

            height:(GUISetting.line_margin + gainItem.height) + (GUISetting.line_margin + zeroItem.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : gainItem

                height: (GUISetting.margin + gainTitle.height) + (GUISetting.margin + gainContent.height) + (GUISetting.margin + gainCalibBtnBox.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : gainTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("ADC Gain calibration")
                }

                NText{
                    id : gainContent
                    anchors.top: gainTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    lineHeight: 1.5
                    text : qsTr("Enter 5V into the three ADC channels<br>and then click the \"Calibration\" button.")
                    visible: dialog.progress === 100
                }

                RowLayout{
                    id : gainCalibBtnBox
                    height: 50 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: gainContent.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Sensor 01")

                        onClick: {
                            dialog.adcGainCalibration("Sensor 01")
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Sensor 02")

                        onClick: {
                            dialog.adcGainCalibration("Sensor 02")
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Analog input")

                        onClick: {
                            dialog.adcGainCalibration("Analog input")
                        }
                    }
                }
            }

            Rectangle{
                id : zeroItem

                height: (GUISetting.margin + zeroTitle.height) + (GUISetting.margin + zeroContent.height) + (GUISetting.margin + zeroCalibBtnBox.height) + GUISetting.margin
                anchors.top: gainItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : zeroTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("ADC Zero calibration")
                }

                NText{
                    id : zeroContent
                    anchors.top: zeroTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    lineHeight: 1.5
                    text : qsTr("Enter 0V into the three ADC channels<br>and then click the \"Calibration\" button.")
                    visible: dialog.progress === 100
                }

                RowLayout{
                    id : zeroCalibBtnBox
                    height: 50 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: zeroContent.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Sensor 01")

                        onClick: {
                            dialog.adcZeroCalibration("Sensor 01")
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Sensor 02")

                        onClick: {
                            dialog.adcZeroCalibration("Sensor 02")
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Analog input")

                        onClick: {
                            dialog.adcZeroCalibration("Analog input")
                        }
                    }
                }
            }
        }
    }
}
