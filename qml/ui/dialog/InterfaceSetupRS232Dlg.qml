import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupRS232DlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24
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
        var baudrateIdx     = body.baudrateCombo.currentIndex
        var parityIdx       = body.parityCombo.currentIndex
        var datalenIdx      = body.datalenCombo.currentIndex
        var stopbitIdx      = body.stopbitCombo.currentIndex

        var posRangeIdx     = body.posRangeCombo.currentIndex
        var pressureRange   = parseInt(body.pressureRange.textField.text)
        var commandSetIdx   = body.commandSetCombo.currentIndex
        var secondAnswerIdx = body.secondAnswerCombo.currentIndex

        var diOpenIdx       = body.diOpenCombo.currentIndex
        var diCloseIdx      = body.diCloseCombo.currentIndex

        dlgModel.onCommandApply(baudrateIdx, parityIdx, datalenIdx, stopbitIdx, commandSetIdx, secondAnswerIdx, diOpenIdx, diCloseIdx, posRangeIdx, pressureRange)
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
        bodyWidth  = GUISetting.popup_nor_width
    }

    InterfaceSetupRS232DlgModel{
        id : dlgModel

        Component.onCompleted : {
        }

        onSignalEventCompletedLoad: {

            body.commandSetCombo.currentIndex  = dlgModel.mCommandSetIdx
            body.baudrateCombo.currentIndex    = dlgModel.mBaudrateIdx
            body.parityCombo.currentIndex      = dlgModel.mParityIdx
            body.datalenCombo.currentIndex     = dlgModel.mDataLenIdx
            body.stopbitCombo.currentIndex     = dlgModel.mStopBitIdx

            body.posRangeCombo.currentIndex    = dlgModel.mPosRangeIdx
            body.pressureRange.textField.text  = dlgModel.mPressureRange

            body.secondAnswerCombo.currentIndex= dlgModel.mSecondAnswerIdx

            body.diOpenCombo.currentIndex      = dlgModel.mDIOpenValveIdx
            body.diCloseCombo.currentIndex     = dlgModel.mDICloseValveIdx

            onCommandSetEdit(false);
            //dialog.setCommandSetRelationshipValue()
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias baudrateCombo    : _baudrateCombo
            property alias parityCombo      : _parityCombo
            property alias datalenCombo     : _datalenCombo
            property alias stopbitCombo     : _stopbitCombo
            property alias posRangeCombo    : _posRangeCombo
            property alias pressureRange    : _pressureRange
            property alias commandSetCombo  : _commandSetCombo
            property alias secondAnswerCombo: _secondAnswerCombo
            property alias diOpenCombo      : _diOpenCombo
            property alias diCloseCombo     : _diCloseCombo
            property real  guiScale         : GUISetting.scale

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
                        + (GUISetting.margin + _baudrateCombo.height       )
                        + (GUISetting.margin + _parityCombo.height         )
                        + (GUISetting.margin + _datalenCombo.height        )
                        + (GUISetting.margin + _stopbitCombo.height        ) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : interfaceSettingTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("interface settings")
                }

                NComboBox{
                    id : _baudrateCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: interfaceSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrBaudrateIdx ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100

                    model: ["600","1200","2400","4800","9600","19200","38400","57600","115200"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _baudrateCombo.verticalCenter; anchors.left: _baudrateCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("baudrate")
                }

                NComboBox{
                    id : _parityCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _baudrateCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrParityIdx ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100

                    model: ["even","odd","mark","space","no"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _parityCombo.verticalCenter; anchors.left: _parityCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("parity")
                }

                NComboBox{
                    id : _datalenCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _parityCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDataLenIdx ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100

                    model: ["7 bit","8 bit"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _datalenCombo.verticalCenter; anchors.left: _datalenCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("data length")
                }

                NComboBox{
                    id : _stopbitCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _datalenCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrStopBitIdx ? "#FF0000" : "#000000"
                    enabled: dlgModel.mProgress == 100

                    model: ["1","2"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _stopbitCombo.verticalCenter; anchors.left: _stopbitCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("stop bits")
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
