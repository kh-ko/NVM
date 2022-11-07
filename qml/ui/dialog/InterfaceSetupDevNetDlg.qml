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

    titleText   : qsTr("Interface setup(D-Net)")
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
        var posUnitIdx      = body.positionUnitCombo.currentIndex
        var posRange        = parseFloat(body.positionRange.textField.text)
        var pressureUnitIdx = body.pressureUnitCombo.currentIndex

        if(pressureUnitIdx < 2)
        {
            body.sensor02Range.textField.text = body.sensor01Range.textField.text
        }

        var s01Range        = parseFloat(body.sensor01Range.textField.text)
        var s02Range        = parseFloat(body.sensor02Range.textField.text)
        var diActivation    = body.diActivationCombo.currentIndex
        var diFunction      = body.diFunctionCombo.currentIndex
        var diPolarity      = body.diPolarityCombo.currentIndex
        var doActivation    = body.doActivationCombo.currentIndex
        var doFunction      = body.doFunctionCombo.currentIndex
        var doPolarity      = body.doPolarityCombo.currentIndex

        dlgModel.onCommandApply(posUnitIdx, posRange, pressureUnitIdx, s01Range, s02Range, diActivation, diFunction, diPolarity, doActivation, doFunction, doPolarity)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 800 * GUISetting.scale
    }

    InterfaceSetupDevNetDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.macAddr.textField.text          = dlgModel.mMacAddr
            body.baudrateCombo.currentIndex      = dlgModel.mBaudrateIdx
            body.positionUnitCombo.currentIndex  = dlgModel.mPositionUnitIdx
            body.positionRange.setValue(dlgModel.mPositionRange)
            body.pressureUnitCombo.currentIndex  = dlgModel.mPressureUnitIdx
            body.sensor01Range.setValue(dlgModel.mSensor01Range)
            body.sensor02Range.setValue(dlgModel.mSensor02Range)

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
            property alias sensor01Range     : _sensor01Range
            property alias sensor02Range     : _sensor02Range
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
                bodyWidth  = 800 * GUISetting.scale
            }

            Rectangle{
                id : genSettings

                height: (GUISetting.margin + genSettingsTitle.height    )
                        + (GUISetting.margin + _macAddr.height          )
                        + (GUISetting.margin + _baudrateCombo.height    )
                        + (GUISetting.margin + _positionUnitCombo.height)
                        + (GUISetting.margin + _positionRange.height    )
                        + (GUISetting.margin + _pressureUnitCombo.height)
                        + (GUISetting.margin + _sensor01Range.height     )
                        + (GUISetting.margin + _sensor02Range.height     ) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;
                width: 250 * GUISetting.scale

                color: "#FFFFFF"

                NText{
                    id : genSettingsTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("General interface settings")
                }

                NInputNumber{
                    id : _macAddr

                    height: 24 * GUISetting.scale; width: 120 * GUISetting.scale
                    anchors.top: genSettingsTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dlgModel.mEnableMacAddr && dlgModel.mProgress == 100

                    textField.validator: IntValidator{}
                    stepValue : 1; minValue:0; maxValue: 255
                    fixedN : 0
                }

                NText{
                    anchors.verticalCenter: _macAddr.verticalCenter; anchors.left: _macAddr.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("MAC address")
                }

                NComboBox{
                    id : _baudrateCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _macAddr.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dlgModel.mEnableBaudrateIdx && dlgModel.mProgress == 100

                    model: ["125k","250k", "500k", "auto"]
                }

                NText{
                    anchors.verticalCenter: _baudrateCombo.verticalCenter; anchors.left: _baudrateCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("baudrate")
                }

                NComboBox{
                    id : _positionUnitCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _baudrateCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100 && dlgModel.mEnablePositionUnitIdx

                    model: ["counts","percent","degrees"]

                    onCurrentIndexChanged: {

                        if(currentIndex == 1)
                        {
                            _positionRange.fixedN = 0
                            _positionRange.setValue(100)
                        }
                        else if(currentIndex == 2)
                        {

                            _positionRange.fixedN = 0
                            _positionRange.setValue(90)
                        }
                        else
                            _positionRange.fixedN = 3

                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _positionUnitCombo.verticalCenter; anchors.left: _positionUnitCombo.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrPositionUnitIdx ? "#FF0000" : "#000000"
                    text : qsTr("position unit")
                }


                NText{
                    id : positionRangeFromLabel
                    anchors.top: _positionUnitCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("0 ~")
                }

                NInputNumber{
                    id : _positionRange

                    height: 24 * GUISetting.scale; width: 120 * GUISetting.scale
                    anchors.verticalCenter: positionRangeFromLabel.verticalCenter; anchors.left: positionRangeFromLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: _positionUnitCombo.right

                    stepValue : 1; minValue:0; maxValue: 40000
                    fixedN : 0

                    enabled: dialog.progress === 100 && _positionUnitCombo.currentIndex == 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _positionRange.verticalCenter; anchors.left: _positionRange.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrPositionRange ? "#FF0000" : "#000000"
                    text : qsTr("position range")
                }

                NComboBox{
                    id : _pressureUnitCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _positionRange.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dialog.progress === 100  && dlgModel.mEnablePressureUnitIdx

                    model: ["counts","percent","psi","Torr","mTorr","bar","mbar","pa","atm"]


                    onCurrentIndexChanged: {
                        if(currentIndex == 1)
                        {
                            _sensor01Range.fixedN = 0
                            _sensor02Range.fixedN = 0
                            _sensor01Range.setValue(100)
                            _sensor02Range.setValue(100)
                        }
                        else if(currentIndex > 1)
                        {
                            _sensor01Range.fixedN = dlgModel.onCommandGetSensorRange01FixedN(currentIndex)
                            _sensor02Range.fixedN = dlgModel.onCommandGetSensorRange02FixedN(currentIndex)
                            _sensor01Range.setValue(dlgModel.onCommandGetS01FullScale(currentIndex))
                            _sensor02Range.setValue(dlgModel.onCommandGetS02FullScale(currentIndex))
                        }
                        else
                        {
                            _sensor01Range.setValue(10000)
                            _sensor02Range.setValue(10000)
                            _sensor01Range.fixedN = 3
                            _sensor02Range.fixedN = 3
                        }

                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _pressureUnitCombo.verticalCenter; anchors.left: _pressureUnitCombo.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrPressureUnitIdx ? "#FF0000" : "#000000"
                    text : qsTr("pressure unit")
                }

                NText{
                    id : sensor01RangeFromLabel
                    anchors.top: _pressureUnitCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("0 ~")
                }

                NInputNumber{
                    id : _sensor01Range

                    height: 24 * GUISetting.scale; width: 120 * GUISetting.scale
                    anchors.verticalCenter: sensor01RangeFromLabel.verticalCenter; anchors.left: sensor01RangeFromLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: _pressureUnitCombo.right

                    stepValue : 1; minValue:0; maxValue: 40000
                    fixedN : 0

                    enabled: dialog.progress === 100 && _pressureUnitCombo.currentIndex == 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor01Range.verticalCenter; anchors.left: _sensor01Range.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrSensor01Range ? "#FF0000" : "#000000"
                    text : _pressureUnitCombo.currentIndex > 1 ? qsTr("sensor 1 range") : qsTr("sensor range")
                 }

                NText{
                    id : sensor02RangeFromLabel
                    anchors.top: _sensor01Range.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    visible: _pressureUnitCombo.currentIndex > 1
                    text : qsTr("0 ~")
                }

                NInputNumber{
                    id : _sensor02Range

                    height: 24 * GUISetting.scale; width: 120 * GUISetting.scale
                    anchors.verticalCenter: sensor02RangeFromLabel.verticalCenter; anchors.left: sensor02RangeFromLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: _sensor01Range.right

                    stepValue : 1; minValue:0; maxValue: 40000
                    fixedN : 0

                    visible: _pressureUnitCombo.currentIndex > 1
                    enabled: dialog.progress === 100 && _pressureUnitCombo.currentIndex == 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _sensor02Range.verticalCenter; anchors.left: _sensor02Range.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrSensor02Range ? "#FF0000" : "#000000"
                    visible: _pressureUnitCombo.currentIndex > 1
                    text : qsTr("sensor 2 range")
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
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
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
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
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
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doActivationCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOFunction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

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
                    item01Name: qsTr("index")
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
                                enabled: dlgModel.mProgress == 100 ? true : false

                                itemSeq    : parent.assemblyData.mSeq
                                isSelected : parent.assemblyData.mIsSelected
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
                    item01Name: qsTr("index")
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
                                enabled: dlgModel.mProgress == 100 ? true : false

                                itemSeq    : parent.assemblyData.mSeq
                                isSelected : parent.assemblyData.mIsSelected
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
                            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                            {
                                dialog.openChangeAccessDlg()
                                return;
                            }

                            dialog.commit()
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
