import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupEtherNETDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24
    property var body : null

    property bool isRS485 : dlgModel.mInterface == ValveEnumDef.INTERFACE_RS485 ||  dlgModel.mInterface == ValveEnumDef.INTERFACE_RS485_HV || dlgModel.mInterface == ValveEnumDef.INTERFACE_RS485_WITH_ANALOGOUTPUT || dlgModel.mInterface == ValveEnumDef.INTERFACE_RS485_HV_WITH_ANALOGOUTPUT
    titleText   : qsTr("Interface setup(Ethernet)")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    bodyWidth   : 600


    function commit()
    {
        var ip01      = parseInt(body.ip01Input.textField.text)
        var ip02      = parseInt(body.ip02Input.textField.text)
        var ip03      = parseInt(body.ip03Input.textField.text)
        var ip04      = parseInt(body.ip04Input.textField.text)
        var subnet01  = parseInt(body.subnet01Input.textField.text)
        var subnet02  = parseInt(body.subnet02Input.textField.text)
        var subnet03  = parseInt(body.subnet03Input.textField.text)
        var subnet04  = parseInt(body.subnet04Input.textField.text)
        var gateway01 = parseInt(body.gateway01Input.textField.text)
        var gateway02 = parseInt(body.gateway02Input.textField.text)
        var gateway03 = parseInt(body.gateway03Input.textField.text)
        var gateway04 = parseInt(body.gateway04Input.textField.text)
        var dhcpIdx   = body.dhcpCombo.currentIndex
        var port01    = parseInt(body.port01Input.textField.text)
        var port02    = parseInt(body.port02Input.textField.text)
        var terminationIdx   = body.terminationCombo.currentIndex
        var posRangeIdx     = body.posRangeCombo.currentIndex
        var pressureRange   = parseInt(body.pressureRange.textField.text)
        var commandSetIdx   = body.commandSetCombo.currentIndex
        var secondAnswerIdx = body.secondAnswerCombo.currentIndex

        var diOpenIdx       = body.diOpenCombo.currentIndex
        var diCloseIdx      = body.diCloseCombo.currentIndex

        dlgModel.onCommandApply(ip01, ip02, ip03, ip04, subnet01, subnet02, subnet03, subnet04, gateway01, gateway02, gateway03, gateway04,
                                dhcpIdx, port01, port02, terminationIdx, commandSetIdx, secondAnswerIdx, diOpenIdx, diCloseIdx, posRangeIdx, pressureRange)
    }

    function setCommandSetRelationshipValue()
    {
        if(body == null)
            return

        switch(body.commandSetCombo.currentIndex)
        {
        case 0: // IC
            body.secondAnswerCombo.currentIndex = 0
            break;
        case 1: // PM
            body.posRangeCombo.currentIndex = 0
            body.pressureRange.textField.text = "1000"
            break;
        case 2: // DeviceNET
            body.secondAnswerCombo.currentIndex = 0
            body.posRangeCombo.currentIndex = 0
            body.pressureRange.textField.text = "1000"
            break;
        case 3: // DeviceNET
        case 4: // tylan type1
        case 5: // tylan type1
        case 6: // tylan type1
            body.secondAnswerCombo.currentIndex = 0
            body.posRangeCombo.currentIndex = 2
            body.pressureRange.textField.text = "1000000"
            break;
        }
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 600 * GUISetting.scale
    }

    InterfaceSetupEtherNETDlgModel{
        id : dlgModel

        Component.onCompleted : {
        }

        onSignalEventCompletedLoad: {
            body.ip01Input.textField.text        = dlgModel.mIp01
            body.ip02Input.textField.text        = dlgModel.mIp02
            body.ip03Input.textField.text        = dlgModel.mIp03
            body.ip04Input.textField.text        = dlgModel.mIp04
            body.subnet01Input.textField.text    = dlgModel.mSubNet01
            body.subnet02Input.textField.text    = dlgModel.mSubNet02
            body.subnet03Input.textField.text    = dlgModel.mSubNet03
            body.subnet04Input.textField.text    = dlgModel.mSubNet04
            body.gateway01Input.textField.text   = dlgModel.mGateway01
            body.gateway02Input.textField.text   = dlgModel.mGateway02
            body.gateway03Input.textField.text   = dlgModel.mGateway03
            body.gateway04Input.textField.text   = dlgModel.mGateway04
            body.dhcpCombo.currentIndex          = dlgModel.mDHCPIdx
            body.port01Input.textField.text      = dlgModel.mPort01
            body.port02Input.textField.text      = dlgModel.mPort02
            body.terminationCombo.currentIndex   = dlgModel.mTerminationIdx

            body.posRangeCombo.currentIndex      = dlgModel.mPosRangeIdx
            body.pressureRange.textField.text    = dlgModel.mPressureRange

            body.secondAnswerCombo.currentIndex  = dlgModel.mSecondAnswerIdx

            body.diOpenCombo.currentIndex        = dlgModel.mDIOpenValveIdx
            body.diCloseCombo.currentIndex       = dlgModel.mDICloseValveIdx

            onCommandSetEdit(false);
            //dialog.setCommandSetRelationshipValue()
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias ip01Input          : _ip01Input
            property alias ip02Input          : _ip02Input
            property alias ip03Input          : _ip03Input
            property alias ip04Input          : _ip04Input
            property alias subnet01Input      : _subnet01Input
            property alias subnet02Input      : _subnet02Input
            property alias subnet03Input      : _subnet03Input
            property alias subnet04Input      : _subnet04Input
            property alias gateway01Input     : _gateway01Input
            property alias gateway02Input     : _gateway02Input
            property alias gateway03Input     : _gateway03Input
            property alias gateway04Input     : _gateway04Input
            property alias dhcpCombo          : _dhcpCombo
            property alias port01Input        : _port01Input
            property alias port02Input        : _port02Input
            property alias terminationCombo   : _terminationCombo
            property alias posRangeCombo      : _posRangeCombo
            property alias pressureRange      : _pressureRange
            property alias commandSetCombo    : _commandSetCombo
            property alias secondAnswerCombo  : _secondAnswerCombo
            property alias diOpenCombo        : _diOpenCombo
            property alias diCloseCombo       : _diCloseCombo
            property real  guiScale           : GUISetting.scale

            height: (GUISetting.line_margin + interfaceSettingItem.height) + (GUISetting.line_margin + commSettingItem.height) + (GUISetting.line_margin + dIItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : interfaceSettingItem

                height:   (GUISetting.margin + interfaceSettingTitle.height)
                        + (GUISetting.margin + _ip01Input.height       )
                        + (GUISetting.margin + _subnet01Input.height         )
                        + (GUISetting.margin + _gateway01Input.height        )
                        + (GUISetting.margin + _dhcpCombo.height        ) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : interfaceSettingTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("interface settings")
                }

                NInputNumber{
                    id : _ip01Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: interfaceSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.color: dlgModel.mErrIp ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _ip02Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: interfaceSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _ip01Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrIp ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _ip03Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: interfaceSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _ip02Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrIp ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _ip04Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: interfaceSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _ip03Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrIp ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _ip04Input.verticalCenter; anchors.left: _ip04Input.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("IP")
                }

                NInputNumber{
                    id : _subnet01Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _ip01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.color: dlgModel.mErrSubNet ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _subnet02Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _ip01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _subnet01Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrSubnet ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _subnet03Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _ip01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _subnet02Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrsubnet ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _subnet04Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _ip01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _subnet03Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrSubnet ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _subnet04Input.verticalCenter; anchors.left: _subnet04Input.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("Subnet")
                }

                NInputNumber{
                    id : _gateway01Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _subnet01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.color: dlgModel.mErrGateway ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _gateway02Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _subnet01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _gateway01Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrGateway ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _gateway03Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _subnet01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _gateway02Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrGateway ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NInputNumber{
                    id : _gateway04Input
                    width: 60 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _subnet01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _gateway03Input.right; anchors.leftMargin: GUISetting.line_margin

                    textField.color: dlgModel.mErrGateway ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 0; maxValue: 255
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    id : gatewayLabel
                    anchors.verticalCenter: _gateway04Input.verticalCenter; anchors.left: _gateway04Input.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("Gateway")
                }

                NComboBox{
                    id : _dhcpCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _gateway01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDHCP ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100

                    model: ["OFF","ON"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _dhcpCombo.verticalCenter; anchors.left: _dhcpCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("DHCP")
                }

                Item {
                    anchors.top: interfaceSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.left: gatewayLabel.right; anchors.leftMargin: GUISetting.margin * 2; anchors.right: parent.right;

                    NInputNumber{
                        id : _port01Input
                        width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: parent.top; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textField.color: dlgModel.mErrPort01 ? "#FF0000" : "#000000"
                        enabled: dlgModel.mProgress == 100
                        textField.validator: IntValidator{}
                        stepValue : 1; minValue: 501; maxValue: 2499
                        fixedN : 0

                        onChangedText: {
                            dlgModel.onCommandSetEdit(true)
                        }
                    }

                    NText{
                        anchors.verticalCenter: _port01Input.verticalCenter; anchors.left: _port01Input.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("Port 1")
                    }

                    NInputNumber{
                        id : _port02Input
                        width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: _port01Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textField.color: dlgModel.mErrPort02 ? "#FF0000" : "#000000"
                        enabled: dlgModel.mProgress == 100
                        textField.validator: IntValidator{}
                        stepValue : 1; minValue: 501; maxValue: 2499
                        fixedN : 0

                        onChangedText: {
                            dlgModel.onCommandSetEdit(true)
                        }
                    }

                    NText{
                        anchors.verticalCenter: _port02Input.verticalCenter; anchors.left: _port02Input.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("Port 2")
                    }

                    NComboBox{
                        id : _terminationCombo
                        width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: _port02Input.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrTerminationIdx ? "#FF0000" : "#000000"
                        enabled: dlgModel.mProgress == 100

                        model: ["LF(CR/LF)","CR"]

                        onCurrentIndexChanged: {
                            dlgModel.onCommandSetEdit(true)
                        }
                    }

                    NText{
                        anchors.verticalCenter: _terminationCombo.verticalCenter; anchors.left: _terminationCombo.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("termination")
                    }
                }
            }

            Rectangle{
                id : commSettingItem

                height:   (GUISetting.margin + commSettingTitle.height)
                        + (GUISetting.margin + _posRangeCombo.height  )
                        + (GUISetting.margin + _pressureRange.height  ) + GUISetting.margin
                anchors.top: interfaceSettingItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : commSettingTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("communication settings")
                }

                NComboBox{
                    id : _posRangeCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: commSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dlgModel.mProgress == 100 && _commandSetCombo.currentIndex == 0

                    model: ["0~1000","0~10000","0~100000"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _posRangeCombo.verticalCenter; anchors.left: _posRangeCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("position range")
                }


                NInputNumber{
                    id : _pressureRange
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _posRangeCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.color: dlgModel.mErrPressureRange ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100 && _commandSetCombo.currentIndex == 0
                    textField.validator: IntValidator{}
                    stepValue : 1; minValue: 1; maxValue: 1000000
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureRange.verticalCenter; anchors.left: _pressureRange.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("pressure range")
                }

                NComboBox{
                    id : _commandSetCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: commSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: (parent.width / 2 + GUISetting.margin)

                    textColor: dlgModel.mErrCommandSetIdx ? "#FF0000" : "#000000"
                    enabled: false//dlgModel.mProgress == 100
                    visible: false

                    model: ["IC","PM","DeviceNet","Service","Tylan Type1","Tylan Type2","Tylan Type3"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)

                        dialog.setCommandSetRelationshipValue();
                    }
                }

                NText{
                    anchors.verticalCenter: _commandSetCombo.verticalCenter; anchors.left: _commandSetCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("command set")
                    visible: false
                }

                NComboBox{
                    id : _secondAnswerCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _commandSetCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: _commandSetCombo.left; anchors.leftMargin: 0

                    textColor: dlgModel.mErrSecondAnswerIdx ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100 && _commandSetCombo.currentIndex == 1

                    model: ["disable","enable"]
                    visible: false

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _secondAnswerCombo.verticalCenter; anchors.left: _secondAnswerCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("second answer")
                    visible: false
                }
            }


            Rectangle{
                id : dIItem

                width : (parent.width - (GUISetting.line_margin * 3)) / 2;height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + _diOpenCombo.height) + (GUISetting.margin + _diCloseCombo.height) + GUISetting.margin;
                anchors.top: commSettingItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : diTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital input")
                }

                NComboBox{
                    id : _diOpenCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIOpenValveIdx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not inverted","inverted", "disabled"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diOpenCombo.verticalCenter; anchors.left: _diOpenCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("open valve")
                }

                NComboBox{
                    id : _diCloseCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diOpenCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDICloseValveIdx ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not inverted","inverted", "disabled"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diCloseCombo.verticalCenter; anchors.left: _diCloseCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("close valve")
                }
            }

            Rectangle{
                id : doItem

                width : (parent.width - (GUISetting.line_margin * 3))/ 2;height: (GUISetting.margin + doTitle.height) + (GUISetting.margin + doOpenedCombo.height) + (GUISetting.margin + doClosedCombo.height) + GUISetting.margin;
                anchors.top: dIItem.top; anchors.left: dIItem.right; anchors.leftMargin: 2;

                color: "#FFFFFF"

                NText{
                    id : doTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital outputs")
                }

                NComboBox{
                    id : doOpenedCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: doTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100
                    currentIndex: 0
                    model: ["open"]
                }

                NText{
                    anchors.verticalCenter: doOpenedCombo.verticalCenter; anchors.left: doOpenedCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("opened valve")
                }

                NComboBox{
                    id : doClosedCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: doOpenedCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100
                    currentIndex: 0
                    model: ["close"]
                }

                NText{
                    anchors.verticalCenter: doClosedCombo.verticalCenter; anchors.left: doClosedCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("closed valve")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: doItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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
