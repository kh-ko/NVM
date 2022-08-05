import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupDevNetDlgModel 1.0
//import InterfaceSetupEthCATItemModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24 * GUISetting.scale
    property var body : null

    titleText   : qsTr("Interface setup")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit
    //bodyWidth   : 500

    function commit()
    {
        var diActivation = body.diActivationCombo.currentIndex
        var diFunction   = body.diFunctionCombo.currentIndex
        var diPolarity   = body.diPolarityCombo.currentIndex
        var doActivation = body.doActivationCombo.currentIndex
        var doFunction   = body.doFunctionCombo.currentIndex
        var doPolarity   = body.doPolarityCombo.currentIndex

        dlgModel.onCommandApply(diActivation, diFunction, diPolarity, doActivation, doFunction, doPolarity)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    InterfaceSetupDevNetDlgModel{
        id : dlgModel

        Component.onCompleted : {
//            pdoListModel.append({"pdoDataName" : "pressure"                     , "itemIdx":0})
//            pdoListModel.append({"pdoDataName" : "pressure sensor 1"            , "itemIdx":1})
//            pdoListModel.append({"pdoDataName" : "pressure sensor 2"            , "itemIdx":2})
//            pdoListModel.append({"pdoDataName" : "position"                     , "itemIdx":3})
//            pdoListModel.append({"pdoDataName" : "target position"              , "itemIdx":4})
//            pdoListModel.append({"pdoDataName" : "cluster valve position"       , "itemIdx":5})
//            pdoListModel.append({"pdoDataName" : "pressure setpoint"            , "itemIdx":6})
//            pdoListModel.append({"pdoDataName" : "position setpoint"            , "itemIdx":7})
//            pdoListModel.append({"pdoDataName" : "position alignment setpoint"  , "itemIdx":8})
//            pdoListModel.append({"pdoDataName" : "external digital pressure"    , "itemIdx":9})
//            pdoListModel.append({"pdoDataName" : "external digital pressure"    , "itemIdx":10})
//            pdoListModel.append({"pdoDataName" : "cluster valve freeze position", "itemIdx":11})
        }

        onSignalEventCompletedLoad: {
            //body.macAddr.setValue(dlgModel.mMacAddr)
            //body.baudrate.currentIndex           = dlgModel.mBaudrate

            body.diActivationCombo.currentIndex  = dlgModel.mDIActivation
            body.diFunctionCombo.currentIndex    = dlgModel.mDIFunction
            body.diPolarityCombo.currentIndex    = dlgModel.mDIPolarity
            body.doActivationCombo.currentIndex  = dlgModel.mDOActivation
            body.doFunctionCombo.currentIndex    = dlgModel.mDOFunction
            body.doPolarityCombo.currentIndex    = dlgModel.mDOPolarity

            onCommandSetEdit(false);
        }
    }

    ListModel{
        id : pdoListModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias macAddr           : _macAddr
            property alias baudrate          : _baudrate
            property alias diActivationCombo : _diActivationCombo
            property alias diFunctionCombo   : _diFunctionCombo
            property alias diPolarityCombo   : _diPolarityCombo
            property alias doActivationCombo : _doActivationCombo
            property alias doFunctionCombo   : _doFunctionCombo
            property alias doPolarityCombo   : _doPolarityCombo
            property real  guiScale          : GUISetting.scale

            height: (GUISetting.line_margin + genSettings.height) + (GUISetting.line_margin + diItem.height) + (GUISetting.line_margin + doItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : genSettings

                height: (GUISetting.margin + genSettingsTitle.height) + (GUISetting.margin + _macAddr.height) + ( GUISetting.margin + _baudrate.height ) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : genSettingsTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("General interface settings")
                }

                NInputNumber{
                    id : _macAddr

                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: genSettingsTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: false

                    isHexMode : true;
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue:0; maxValue: 255
                    fixedN : 0
                    textField.text: dlgModel.mMacAddr
                }

                NText{
                    anchors.verticalCenter: _macAddr.verticalCenter; anchors.left: _macAddr.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("MAC address")
                }

                NComboBox{
                    id : _baudrate
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _macAddr.bottom; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: false
                    currentIndex: dlgModel.mBaudrate

                    model: ["unknow","125k","250k", "500k"]
                }

                NText{
                    anchors.verticalCenter: _baudrate.verticalCenter; anchors.left: _macAddr.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("baudrate")
                }
            }

            Rectangle{
                id : diItem

                height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + _diActivationCombo.height) + (GUISetting.margin + _diFunctionCombo.height) + (GUISetting.margin + _diPolarityCombo.height) + GUISetting.margin; //width: (parent.width / 2) - 3
                anchors.top: genSettings.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : diTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital input")
                }

                NComboBox{
                    id : _diActivationCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIActivation ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["enable","disable"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diActivationCombo.verticalCenter; anchors.left: _diActivationCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("activation")
                }

                NComboBox{
                    id : _diFunctionCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diActivationCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIFunction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["interlock close","interlock open"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diFunctionCombo.verticalCenter; anchors.left: _diFunctionCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("function")
                }

                NComboBox{
                    id : _diPolarityCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diFunctionCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIPolarity ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not inverted","inverted"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diPolarityCombo.verticalCenter; anchors.left: _diPolarityCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("polarity")
                }
            }

            Rectangle{
                id : doItem

                height: (GUISetting.margin   + doTitle.height           )
                        + (GUISetting.margin + _doActivationCombo.height)
                        + (GUISetting.margin + _doFunctionCombo.height  )
                        + (GUISetting.margin + _doPolarityCombo.height  )
                        + GUISetting.margin; //width: (parent.width / 2) - 3
                anchors.top: diItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : doTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital output")
                }

                NComboBox{
                    id : _doActivationCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: doTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOActivation ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["enable","disable"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doActivationCombo.verticalCenter; anchors.left: _doActivationCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("activation")
                }

                NComboBox{
                    id : _doFunctionCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doActivationCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOFunction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["close","open"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doFunctionCombo.verticalCenter; anchors.left: _doFunctionCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("function")
                }

                NComboBox{
                    id : _doPolarityCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doFunctionCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOPolarity ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not inverted","inverted"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doPolarityCombo.verticalCenter; anchors.left: _doPolarityCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("polarity")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: doItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height ; width: parent.width / 2
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
                        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                        {
                            dialog.openChangeAccessDlg()
                            return;
                        }

                        dialog.commit()
                    }
                }
            }
        }
    }
}
