import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupDevNetDlgModel 1.0
import InterfaceSetupDevNetAssemblyItemModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24 * GUISetting.scale
    property var body : null
    property var company : ValveEnumDef.COMPANY_NOVA
    property int firmwareVer : 0

    signal clickRangeSetting()

    titleText   : qsTr("Interface setup(D-Net)")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit
    //bodyWidth   : 500

    function openNoticeDlg()
    {
        var popup = noticeDlg.createObject(dialog)
        popup.open();
    }

    function commit()
    {
        var macAddr         = parseInt(body.macAddr.textField.text)
        var baudrateIdx     = body.baudrateCombo.currentIndex
        var posUnitIdx      = body.positionUnitCombo.currentIndex
        var posRange        = parseFloat(body.positionRange.textField.text)
        var pressureUnitIdx = body.pressureUnitCombo.currentIndex
        var sensorRange     = parseFloat(body.sensorRange.textField.text)
        var outPosUnitIdx      = body.outPositionUnitCombo.currentIndex
        var outPosRange        = parseFloat(body.outPositionRange.textField.text)
        var outPressureUnitIdx = body.outPressureUnitCombo.currentIndex
        var outSensorRange     = parseFloat(body.outSensorRange.textField.text)
        var diActivation    = body.diActivationCombo.currentIndex
        var diFunction      = body.diFunctionCombo.currentIndex
        var diPolarity      = body.diPolarityCombo.currentIndex
        var doActivation    = body.doActivationCombo.currentIndex
        var doFunction      = body.doFunctionCombo.currentIndex
        var doPolarity      = body.doPolarityCombo.currentIndex

        dlgModel.onCommandApply(macAddr, baudrateIdx, posUnitIdx, posRange, pressureUnitIdx, sensorRange, outPosUnitIdx, outPosRange, outPressureUnitIdx, outSensorRange, diActivation, diFunction, diPolarity, doActivation, doFunction, doPolarity)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 900 * GUISetting.scale
    }

    InterfaceSetupDevNetDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.macAddr.textField.text          = dlgModel.mMacAddr
            body.baudrateCombo.currentIndex      = dlgModel.mBaudrateIdx
            body.positionUnitCombo.currentIndex  = dlgModel.mPositionUnitIdx
            body.positionRange.setValue(dlgModel.mPositionRange)
            body.pressureUnitCombo.currentIndex  = dlgModel.mPressureUnitIdx
            body.sensorRange.setValue(dlgModel.mSensorRange)
            body.outPositionUnitCombo.currentIndex  = dlgModel.mOutPositionUnitIdx
            body.outPositionRange.setValue(dlgModel.mOutPositionRange)
            body.outPressureUnitCombo.currentIndex  = dlgModel.mOutPressureUnitIdx
            body.outSensorRange.setValue(dlgModel.mOutSensorRange)

            body.diActivationCombo.currentIndex  = dlgModel.mDIActivation
            body.diFunctionCombo.currentIndex    = dlgModel.mDIFunction
            body.diPolarityCombo.currentIndex    = dlgModel.mDIPolarity
            body.doActivationCombo.currentIndex  = dlgModel.mDOActivation
            body.doFunctionCombo.currentIndex    = dlgModel.mDOFunction
            body.doPolarityCombo.currentIndex    = dlgModel.mDOPolarity

            var i
            var itemSeq
            var isSelected
            var lengthItem
            var objectItem
            var addInfoItem
            var rowCount = dlgModel.onCommandGetInputAssemblyItemCount()

            for(i = 1; i <= rowCount; i ++)
            {
                var itemAssemblyData = dlgModel.onCommandGetInputAssemblyItem(i);

                iAssemblyListModel.append({"itemAssemblyData": itemAssemblyData})
            }
            console.debug("end");

            rowCount = dlgModel.onCommandGetOutputAssemblyItemCount()

            for(i = 1; i <= rowCount; i ++)
            {
                oAssemblyListModel.append({"itemSeq":i})
            }

            onCommandSetEdit(false);
        }
    }

    ListModel{
        id : iAssemblyListModel
    }

    ListModel{
        id : oAssemblyListModel
    }

    ListModel{
        id : iAssemblyTableIdxModel
    }

    ListModel{
        id : oAssemblyTableIdxModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias macAddr           : _macAddr
            property alias baudrateCombo     : _baudrateCombo
            property alias positionUnitCombo : _positionUnitCombo
            property alias positionRange     : _positionRange
            property alias pressureUnitCombo : _pressureUnitCombo
            property alias sensorRange       : _sensorRange
            property alias outPositionUnitCombo : _outPositionUnitCombo
            property alias outPositionRange     : _outPositionRange
            property alias outPressureUnitCombo : _outPressureUnitCombo
            property alias outSensorRange       : _outSensorRange
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
                bodyWidth  = 900 * GUISetting.scale
            }

            ScrollView{
                id : genSettings
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;
                height: 269 * GUISetting.scale; width: 250 * GUISetting.scale
                clip: true
                padding: GUISetting.margin


                background: Rectangle { color: "#ffffff" }

                ScrollBar.vertical {
                    id : vSBar

                    active: true
                    orientation: Qt.Vertical
                    width: 6
                    height: genSettings.availableHeight
                    anchors.right: genSettings.right
                    anchors.rightMargin: 4
                    policy: height  < genSettings.contentHeight ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

                    contentItem: Rectangle
                    {
                        width: 6
                        //implicitHeight: 100
                        radius: width / 2
                        color: vSBar.pressed ?  "#39000000" : "#59000000"
                    }

                    background: Rectangle{
                        anchors.fill: parent
                        color : "#00000000"
                    }
                }

                /*ScrollBar.vertical: ScrollBar {
                    id : vSBar

                    active: true
                    orientation: Qt.Vertical
                    width: 6
                    height: genSettings.availableHeight
                    anchors.right: genSettings.right
                    anchors.rightMargin: 4
                    policy: height  < genSettings.contentHeight ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

                    contentItem: Rectangle
                    {
                        width: 6
                        //implicitHeight: 100
                        radius: width / 2
                        color: vSBar.pressed ?  "#39000000" : "#59000000"
                    }

                    background: Rectangle{
                        anchors.fill: parent
                        color : "#00000000"
                    }
                }*/

                ColumnLayout{
                    width: parent.availableWidth
                    spacing: GUISetting.margin

                    NText{
                        id : genSettingsTitle
                        Layout.fillWidth: true; isBold: true
                        text : qsTr("General interface settings")
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;
                        NInputNumber{
                            id : _macAddr
                            height : parent.height; width: 120 * GUISetting.scale;
                            enabled: dlgModel.mProgress == 100

                            textField.validator: IntValidator{}
                            stepValue : 1; minValue:0; maxValue: 63; fixedN : 0

                            onChangedText: { dlgModel.onCommandSetEdit(true) }
                        }

                        NText{
                            anchors.verticalCenter: _macAddr.verticalCenter; anchors.left: _macAddr.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrMacAddr ? "#FF0000" : "#000000"
                            text : qsTr("MAC address")
                        }
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;

                        NComboBox{
                            id : _baudrateCombo
                            height : parent.height; width: 120 * GUISetting.scale;

                            enabled: dlgModel.mProgress == 100

                            model: ["125k","250k", "500k", "auto"]

                            onCurrentIndexChanged: {
                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _baudrateCombo.verticalCenter; anchors.left: _baudrateCombo.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrBaudrateIdx ? "#FF0000" : "#000000"
                            text : qsTr("baudrate")
                        }
                    }

                    NText{
                        Layout.fillWidth: true; isBold: true
                        text : firmwareVer > 0x603 ?  qsTr("In Range") : qsTr("In/Out Range")
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;

                        NComboBox{
                            id : _positionUnitCombo
                            height : parent.height; width: 120 * GUISetting.scale;

                            enabled: dialog.progress === 100

                            model: ["counts","percent","degrees"]

                            onCurrentIndexChanged: {

                                if(currentIndex == 0)
                                {
                                    _positionRange.setValue(dlgModel.mPositionRange)
                                }

                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _positionUnitCombo.verticalCenter; anchors.left: _positionUnitCombo.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrPositionUnitIdx ? "#FF0000" : "#000000"

                            text : qsTr("position unit")
                        }
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;
                        visible: _positionUnitCombo.currentIndex == 0

                        NInputNumber{
                            id : _positionRange
                            height : parent.height; width: 120 * GUISetting.scale;

                            enabled: dialog.progress === 100 && _positionUnitCombo.currentIndex == 0

                            textField.validator: DoubleValidator{}
                            stepValue : 1; minValue:0; maxValue: 999999999
                            fixedN : 3

                            onChangedText: {
                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _positionRange.verticalCenter; anchors.left: _positionRange.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrPositionRange ? "#FF0000" : "#000000"

                            text : qsTr("Max")
                        }
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;

                        NComboBox{
                            id : _pressureUnitCombo
                            height : parent.height; width: 120 * GUISetting.scale;

                            enabled: dialog.progress === 100

                            model: ["counts","percent","psi","Torr","mTorr","bar","mbar","pa","atm"]


                            onCurrentIndexChanged: {
                                if(currentIndex == 0)
                                {
                                    _sensorRange.setValue(dlgModel.mSensorRange)
                                }
                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _pressureUnitCombo.verticalCenter; anchors.left: _pressureUnitCombo.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrPressureUnitIdx ? "#FF0000" : "#000000"

                            text : qsTr("pressure unit")
                        }
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;
                        visible: _pressureUnitCombo.currentIndex == 0

                        NInputNumber{
                            id : _sensorRange
                            height : parent.height; width: 120 * GUISetting.scale;

                            enabled: dialog.progress === 100 && _pressureUnitCombo.currentIndex == 0

                            textField.validator: DoubleValidator{}
                            stepValue : 1; minValue:0; maxValue: 999999999
                            fixedN : 4

                            onChangedText: {
                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _sensorRange.verticalCenter; anchors.left: _sensorRange.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrSensorRange ? "#FF0000" : "#000000"

                            text : qsTr("MAX")
                        }
                    }

                    NText{
                        Layout.fillWidth: true; isBold: true
                        visible: firmwareVer > 0x603
                        text : qsTr("Out Range")
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;
                        visible: firmwareVer > 0x603

                        NComboBox{
                            id : _outPositionUnitCombo
                            height : parent.height; width: 120 * GUISetting.scale;

                            enabled: dialog.progress === 100

                            model: ["counts","percent","degrees"]

                            onCurrentIndexChanged: {

                                if(currentIndex == 0)
                                {
                                    _outPositionRange.setValue(dlgModel.mOutPositionRange)
                                }

                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _outPositionUnitCombo.verticalCenter; anchors.left: _outPositionUnitCombo.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrOutPositionUnitIdx ? "#FF0000" : "#000000"

                            text : qsTr("position unit")
                        }
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;
                        visible: _outPositionUnitCombo.currentIndex == 0 && firmwareVer > 0x603

                        NInputNumber{
                            id : _outPositionRange
                            height : parent.height; width: 120 * GUISetting.scale;
                            enabled: dialog.progress === 100 && _outPositionUnitCombo.currentIndex == 0

                            textField.validator: DoubleValidator{}
                            stepValue : 1; minValue:0; maxValue: 999999999
                            fixedN : 3

                            onChangedText: {
                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _outPositionRange.verticalCenter; anchors.left: _outPositionRange.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrOutPositionRange ? "#FF0000" : "#000000"

                            text : qsTr("Max")
                        }
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;
                        visible: firmwareVer > 0x603

                        NComboBox{
                            id : _outPressureUnitCombo
                            height : parent.height; width: 120 * GUISetting.scale;

                            enabled: dialog.progress === 100

                            model: ["counts","percent","psi","Torr","mTorr","bar","mbar","pa","atm"]


                            onCurrentIndexChanged: {
                                if(currentIndex == 0)
                                {
                                    _outSensorRange.setValue(dlgModel.mOutSensorRange)
                                }
                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _outPressureUnitCombo.verticalCenter; anchors.left: _outPressureUnitCombo.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrOutPressureUnitIdx ? "#FF0000" : "#000000"

                            text : qsTr("pressure unit")
                        }
                    }

                    Item{
                        Layout.fillWidth: true; height: 24 * GUISetting.scale;
                        visible: _outPressureUnitCombo.currentIndex == 0 && firmwareVer > 0x603

                        NInputNumber{
                            id : _outSensorRange
                            height : parent.height; width: 120 * GUISetting.scale;
                            enabled: dialog.progress === 100 && _outPressureUnitCombo.currentIndex == 0

                            textField.validator: DoubleValidator{}
                            stepValue : 1; minValue:0; maxValue: 999999999
                            fixedN : 4

                            onChangedText: {
                                dlgModel.onCommandSetEdit(true)
                            }
                        }

                        NText{
                            anchors.verticalCenter: _outSensorRange.verticalCenter; anchors.left: _outSensorRange.right; anchors.leftMargin: GUISetting.margin
                            color: dlgModel.mErrOutSensorRange ? "#FF0000" : "#000000"
                            text : qsTr("MAX")
                        }
                    }
                }
            }

            Rectangle{
                id : diItem

                height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + _diActivationCombo.height) + (GUISetting.margin + _diFunctionCombo.height) + (GUISetting.margin + _diPolarityCombo.height) + GUISetting.margin; //width: (parent.width / 2) - 3
                width: genSettings.width
                anchors.top: genSettings.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : diTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital input")
                }

                NComboBox{
                    id : _diActivationCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIActivation ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diActivationCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIFunction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diFunctionCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIPolarity ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                width: genSettings.width
                anchors.top: diItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : doTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital output")
                }

                NComboBox{
                    id : _doActivationCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: doTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOActivation ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doActivationCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOFunction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

                    model: ["close","open", "constantly ON"]

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
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doFunctionCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOPolarity ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                id : iAssemblyItem

                height: genSettings.height
                anchors.top: genSettings.top; anchors.topMargin: 0; anchors.left: genSettings.right; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : iAssemblyTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Input assembly data list")
                }

                InterfaceSetupDevNetItem{
                    id : iAssemblyListHeader
                    height: 24 * GUISetting.scale
                    anchors.top: iAssemblyTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    isHeader: true
                    item00Name: qsTr("id")
                    item01Name: qsTr("address")
                    item02Name: qsTr("length")
                    item03Name: qsTr("object")
                    item04Name: qsTr("addinational information")

                    onClickedCheckBox: {
                        isSelected = !isSelected
                        dlgModel.onCommandSelectInputAssemblyAllItem(isSelected)
                    }
                }

                Rectangle{
                    anchors.top: iAssemblyListHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NScrollView{
                        id : iAssemblyListView
                        anchors.fill: parent
                        anchors.margins: GUISetting.line_margin

                        model: iAssemblyListModel

                        delegate : Item{
                            property InterfaceSetupDevNetAssemblyItemModel assemblyData : itemAssemblyData /*dlgModel.onCommandGetInputAssemblyItem(itemSeq)*/

                            height: (24 * GUISetting.scale) + GUISetting.line_margin; width: iAssemblyListView.width

                            InterfaceSetupDevNetItem{
                                id : iItemContents
                                height: parent.height - GUISetting.line_margin; width: parent.width
                                anchors.top: parent.top

                                isHeader  : false;
                                enabled: dlgModel.mProgress == 100 &&  parent.assemblyData.mEnable ? true : false

                                itemSeq    : parent.assemblyData.mSeq
                                isSelected : parent.assemblyData.mIsSelected
                                item00Name : "" + parent.assemblyData.mSeq
                                item01Name : parent.assemblyData.mIndex < 0 ? "-" : ""+parent.assemblyData.mIndex
                                item02Name : parent.assemblyData.mLength
                                item03Name : parent.assemblyData.mName
                                item04Name : parent.assemblyData.mAddInfo

                                onClickedCheckBox: {
                                    dlgModel.onCommandSelectInputAssemblyItem(parent.assemblyData.mSeq, !isSelected)
                                    dlgModel.onCommandSetEdit(true)
                                }
                            }
                        }
                    }
                }
            }

            Rectangle{
                id : oAssemblyItem

                height: genSettings.height
                anchors.top: iAssemblyItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: btnBox.top; anchors.bottomMargin: GUISetting.line_margin; anchors.left: genSettings.right; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : oAssemblyTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Output assembly")
                }

                InterfaceSetupDevNetItem{
                    id : oAssemblyListHeader
                    height: 24 * GUISetting.scale
                    anchors.top: oAssemblyTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    isHeader: true
                    item00Name: qsTr("id")
                    item01Name: qsTr("address")
                    item02Name: qsTr("length")
                    item03Name: qsTr("object")
                    item04Name: qsTr("addinational information")

                    onClickedCheckBox: {
                        isSelected = !isSelected
                        //dlgModel.onCommandSelectOutputAssemblyAllItem(isSelected)
                    }
                }

                Rectangle{
                    anchors.top: oAssemblyListHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NScrollView{
                        id : oAssemblyListView
                        anchors.fill: parent
                        anchors.margins: GUISetting.line_margin
                        spacing : 0

                        model: oAssemblyListModel

                        delegate : Item{
                            property InterfaceSetupDevNetAssemblyItemModel assemblyData : dlgModel.onCommandGetOutputAssemblyItem(itemSeq)

                            height: (24 * GUISetting.scale) + GUISetting.line_margin; width: oAssemblyListView.width

                            InterfaceSetupDevNetItem{
                                id : oItemContents
                                height: parent.height - GUISetting.line_margin; width: parent.width
                                anchors.top: parent.top

                                isHeader  : false;
                                enabled: dlgModel.mProgress == 100 &&  parent.assemblyData.mEnable ? true : false

                                isSelected : parent.assemblyData.mIsSelected
                                item00Name : ""+parent.assemblyData.mSeq
                                item01Name : parent.assemblyData.mIndex < 0 ? "-" : ""+parent.assemblyData.mIndex
                                item02Name : parent.assemblyData.mLength
                                item03Name : parent.assemblyData.mName
                                item04Name : parent.assemblyData.mAddInfo

                                onClickedCheckBox: {
                                    dlgModel.onCommandSelectOutputAssemblyItem(parent.assemblyData.mSeq, !isSelected)
                                    dlgModel.onCommandSetEdit(true)
                                }
                            }
                        }
                    }
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: doItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                RowLayout{
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width * 0.7
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        id : applyBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
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

                            if(((dlgModel.mValveID < dlgModel.mNewDevNetValveRev) && !dlgModel.onCommandIsSelEvenBytes())
                               ||(!(dlgModel.mValveID < dlgModel.mNewDevNetValveRev) && dlgModel.onCommandGetIsSelDummy()))
                            {
                                dialog.openNoticeDlg();
                            }
                            else
                            {
                                if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                                {
                                    dialog.openChangeAccessDlg()
                                    return;
                                }
                                dialog.commit()
                            }
                        }
                    }

                    NButton{
                        id : exportToEDS
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && !dialog.isEdit

                        bgColor: "#FFFFFF"
                        text.text: qsTr("export assembly settings to EDS file")

                        onClick: {
                            wFileDialog.open();
                        }
                    }
                }
            }
        }
    }

    Component{
        id : noticeDlg
        NoticeDlg{
            msg : (dlgModel.mValveID < dlgModel.mNewDevNetValveRev) ? qsTr("Added a dummy parameter to match even bytes.") : qsTr("The total byte count has been set to an odd number of bytes.<br><br>If an even number of bytes is required,<br>please check the dummy parameter and reapply.")

            onSignalConfirm: {
                if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                {
                    dialog.openChangeAccessDlg()
                    return;
                }
                dialog.commit()
            }
        }
    }

    FileDialog{
        id: wFileDialog
            title: qsTr("export assembly settings")
            //folder: "./"
            fileMode: FileDialog.SaveFile
            nameFilters: ["EDS files (*.eds)"]

            onAccepted: {
                dlgModel.onCommandExportEDS(currentFile.toString().split("///")[1])
            }
            onRejected: {
            }
            visible : false
    }
}
