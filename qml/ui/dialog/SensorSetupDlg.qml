import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import StrUtil 1.0
import SensorSetupDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Sensor setup")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : ValveEnumDef.ACCESS_LOCAL // dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function commit()
    {
        body.sens01FullScale.focusOut()
        body.sens02FullScale.focusOut()

        var s01Selection = body.sens01Selection.currentIndex
        var s01Unit      = body.sens01Unit.currentIndex
        var s01FullScale = body.sens01FullScale.textField.text
        var s02Selection = body.sens02Selection.currentIndex
        var s02Unit      = body.sens02Unit.currentIndex
        var s02FullScale = body.sens02FullScale.textField.text
        var isEnableZero = body.zeroSelection.currentIndex === 0 ? false : true
        dlgModel.onCommandApply(s01Selection, s01Unit, s01FullScale, s02Selection, s02Unit, s02FullScale, isEnableZero)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    SensorSetupDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.sens01Selection.currentIndex   = dlgModel.mSensor01Selction
            body.sens01Unit.currentIndex        = dlgModel.mSensor01Unit
            body.sens01FullScale.setValue(dlgModel.mSensor01FullScale)
            body.sens02Selection.currentIndex   = dlgModel.mSensor02Selction
            body.sens02Unit.currentIndex        = dlgModel.mSensor02Unit
            body.sens02FullScale.setValue(dlgModel.mSensor02FullScale)
            body.zeroSelection.currentIndex     = dlgModel.mIsEnableZero === false ? 0 : 1

            onCommandSetEdit(false);
        }

        onSignalEventCompletedApply: {
            dialog.close();
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias  sens01Selection          : _sensor01Selection
            property alias  sens01Unit               : _sensor01Unit
            property alias  sens01FullScale          : _sensor01FullScale
            property alias  sens02Selection          : _sensor02Selection
            property alias  sens02Unit               : _sensor02Unit
            property alias  sens02FullScale          : _sensor02FullScale
            property alias  zeroSelection            : _zeroSelection
            property real   guiScale                 : GUISetting.scale

            height: (GUISetting.line_margin + sensor01Item.height) + (GUISetting.line_margin + sensor02Item.height) + (GUISetting.line_margin + zeroItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : sensor01Item

                height: (GUISetting.margin + _sensor01Title.height) + (GUISetting.margin + _sensor01Selection.height) + (GUISetting.margin + _sensor01Unit.height) + (GUISetting.margin + _sensor01FullScale.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : _sensor01Title
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Sensor port 1")
                }

                NComboBox{
                    id : _sensor01Selection
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor01Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrSensorSelction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not selected", "select"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor01Selection.verticalCenter; anchors.left: _sensor01Selection.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("selection")
                }

                NComboBox{
                    id : _sensor01Unit
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor01Selection.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrFullScale ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["Pa","bar", "mbar", "ubar", "Torr", "mTorr", "atm", "psi", "psf"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor01Unit.verticalCenter; anchors.left: _sensor01Unit.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("unit")
                }

                NInputNumber{
                    id : _sensor01FullScale
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor01Unit.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFullScale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0.0001; maxValue: 10000
                    fixedN : 4

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor01FullScale.verticalCenter; anchors.left: _sensor01FullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("full scale")
                }
            }

            Rectangle{
                id : sensor02Item

                height: (GUISetting.margin + _sensor02Title.height) + (GUISetting.margin + _sensor02Selection.height) + (GUISetting.margin + _sensor02Unit.height) + (GUISetting.margin + _sensor02FullScale.height) + GUISetting.margin
                anchors.top: sensor01Item.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : _sensor02Title
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("sensor port 2")
                }

                NComboBox{
                    id : _sensor02Selection
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor02Title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrSensorSelction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && dlgModel.mIsSensor02Support

                    model: ["not selected", "select"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor02Selection.verticalCenter; anchors.left: _sensor02Selection.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("selection")
                }

                NComboBox{
                    id : _sensor02Unit
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor02Selection.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrFullScale ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && dlgModel.mIsSensor02Support

                    model: ["Pa","bar", "mbar", "ubar", "Torr", "mTorr", "atm", "psi", "psf"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor02Unit.verticalCenter; anchors.left: _sensor02Unit.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("unit")
                }

                NInputNumber{
                    id : _sensor02FullScale
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _sensor02Unit.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100 && dlgModel.mIsSensor02Support

                    textField.validator: DoubleValidator{}
                    textField.color: dlgModel.mErrFullScale ? "#FF0000" : "#000000"
                    stepValue : 1; minValue: 0.0001; maxValue: 10000
                    fixedN : 4

                    onChangedText: {
                        /*
                        var fildteredText
                        var dotIdx = textField.text.indexOf(".")
                        if(dotIdx === -1 || dotIdx > 5)
                        {
                            fildteredText = textField.text.substring(0, 5)
                        }
                        else
                        {
                            fildteredText = textField.text.substring(0, 6)
                        }
                        textField.text = fildteredText;*/
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor02FullScale.verticalCenter; anchors.left: _sensor02FullScale.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("full scale")
                }

                Rectangle{
                    anchors.fill: parent
                    color: "#FFFFFF"
                    visible: !dlgModel.mIsSensor02Support

                    Image{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin * 2
                        source: "/image/icon-warning.png"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        text : qsTr("Sensor 2 is not supported")
                    }
                }
            }

            Rectangle{
                id : zeroItem

                height: (GUISetting.margin + _zeroTitle.height) + (GUISetting.margin + _zeroSelection.height) + GUISetting.margin
                anchors.top: sensor02Item.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : _zeroTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("zero adjust")
                }

                NComboBox{
                    id : _zeroSelection
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _zeroTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrSensorSelction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["disable", "enable"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _zeroSelection.verticalCenter; anchors.left: _zeroSelection.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("zero adjust")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: zeroItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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
