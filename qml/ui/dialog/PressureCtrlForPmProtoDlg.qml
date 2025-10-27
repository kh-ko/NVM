import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import PressureCtrlForPmProtoDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    signal signalEventOccurErr()

    titleText   : qsTr("Pressure control advanced setup")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : ValveEnumDef.ACCESS_LOCAL //dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit
    bodyWidth   : 1024
    isModal     : false

    function commit()
    {
        dlgModel.onCommandApply()
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = body.width
    }

    PressureCtrlForPmProtoDlgModel{
        id : dlgModel

        onSignalEventOccurErr: {
            dialog.signalEventOccurErr()
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real  guiScale        : GUISetting.scale

            height: (GUISetting.line_margin + controller1Item.height) + (GUISetting.line_margin + controller3Item.height) + GUISetting.line_margin;
            width : 1024 * GUISetting.scale
            anchors.left: parent.left; /*anchors.right: parent.right;*/ anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = width
            }

            PressureCtrlForPmProtoControllerBox{
                id : controller1Item
                width: (parent.width - (GUISetting.line_margin * 4)) / 3
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                progress   : dialog.progress
                title      : qsTr("Controller 1")
                isSelected : dlgModel.mControllerSelectorUsed == 1
                itemModel  : dlgModel.onCommandGetControllerItem(0)

                onChangeValue: {dlgModel.onCommandSetEditController()}
            }

            PressureCtrlForPmProtoControllerBox{
                id : controller2Item
                width: (parent.width - (GUISetting.line_margin * 4)) / 3
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: controller1Item.right; anchors.leftMargin: GUISetting.line_margin;

                progress   : dialog.progress
                title : qsTr("Controller 2")
                isSelected : dlgModel.mControllerSelectorUsed == 2
                itemModel  : dlgModel.onCommandGetControllerItem(1)

                onChangeValue: {dlgModel.onCommandSetEditController()}
            }

            PressureCtrlForPmProtoControllerBox{
                id : controller3Item
                width: (parent.width - (GUISetting.line_margin * 4)) / 3
                anchors.top: controller1Item.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                progress   : dialog.progress
                title : qsTr("Controller 3")
                isSelected : dlgModel.mControllerSelectorUsed == 3
                itemModel  : dlgModel.onCommandGetControllerItem(2)

                onChangeValue: {dlgModel.onCommandSetEditController()}
            }

            PressureCtrlForPmProtoControllerBox{
                id : controller4Item
                width: (parent.width - (GUISetting.line_margin * 4)) / 3
                anchors.top: controller1Item.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: controller3Item.right; anchors.leftMargin: GUISetting.line_margin;

                progress   : dialog.progress
                title : qsTr("Controller 4")
                isSelected : dlgModel.mControllerSelectorUsed == 4
                itemModel  : dlgModel.onCommandGetControllerItem(3)

                onChangeValue: {dlgModel.onCommandSetEditController()}
            }

            Rectangle{
                id : generalItem
                anchors.top: controller1Item.top; anchors.left: controller2Item.right; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;
                height: (controller1Item.height * 2) - GUISetting.popup_btnbox_height - GUISetting.line_margin

                color : "#FFFFFF"

                Item{
                    //property PressureCtrlForPmProtoDlgModel argDlgModel : dlgModel
                    Connections {
                        target: dlgModel

                        function onSignalEventChangedControllerSelector          (value) { controllerSelectItem.currentIndex             = value }
                        function onSignalEventChangedPresCtrlSpeed               (value) { presCtrlSpeedItem.textField.text              = value }
                        function onSignalEventChangedCtrlPosiRestrictionEnable   (value) { ctrlPosiRestricEnableItem.currentIndex        = value }
                        function onSignalEventChangedCtrlPosiRestrictionMax      (value) { ctrlPosiRestricMaxItem.textField.text         = value }
                        function onSignalEventChangedCtrlPosiRestrictionMin      (value) { ctrlPosiRestricMinItem.textField.text         = value }
                        function onSignalEventChangedAutoControllerSelectEnable  (value) { autoControllerEnableItem.currentIndex         = value }
                        function onSignalEventChangedAutoControllerSelectMode    (value) { autoControllerModeItem.currentIndex           = value }
                        function onSignalEventChangedAutoControllerPresRising    (value) { autoControllerPresRisingItem.currentIndex     = value }
                        function onSignalEventChangedAutoControllerPresFalling   (value) { autoControllerFallingItem.currentIndex        = value }
                        function onSignalEventChangedAutoControllerThreCondition (value) { autoControllerThresConditionItem.currentIndex = value }
                        function onSignalEventChangedAutoController1ThreValue    (value) { threshold1Item.textField.text                 = value }
                        function onSignalEventChangedAutoController2ThreValue    (value) { threshold2Item.textField.text                 = value }
                        function onSignalEventChangedAutoController3ThreValue    (value) { threshold3Item.textField.text                 = value }
                        function onSignalEventChangedAutoController4ThreValue    (value) { threshold4Item.textField.text                 = value }

                        //function onMAutoControllerSelectBitmapChanged (value){ autoControllerSelectBitmapItem}
                    }

                    anchors.left: parent.left; anchors.right: parent.right;
                    height : 750 * GUISetting.scale

                    NText{
                        id : basicLabel
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold : true; text : qsTr("Basic")
                    }

                    NInputNumber{
                        id : presCtrlSpeedItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: basicLabel.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100

                        textField.validator: DoubleValidator{}
                        textField.color: dlgModel.mErrPresCtrlSpeed ? "#FF0000" :
                                         dlgModel.mIsEditPresCtrlSpeed ? "#24A7FF" : "#000000"
                        stepValue : 0.0001; minValue: 0; maxValue: 1
                        fixedN : 3

                        onChangedText: { dlgModel.onCommandSetEditPresCtrlSpeed(textField.text) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("pressure control speed(0.001 ~ 1)")
                        }
                    }

                    NText{
                        id : ctrlPosiRestrictionLabel
                        anchors.top: presCtrlSpeedItem.bottom; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold : true; text : qsTr("Control Position Restriction")
                    }

                    NComboBox{
                        id : ctrlPosiRestricEnableItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: ctrlPosiRestrictionLabel.bottom; anchors.topMargin: GUISetting.margin*0.4; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrCtrlPosiRestrictionEnable ? "#FF0000" :
                                   dlgModel.mIsEditCtrlPosiRestrictionEnable ? "#24A7FF" : "#000000"

                        enabled: dialog.progress === 100

                        model: ["0: disable", "1: enable"]

                        onCurrentIndexChanged: { dlgModel.onCommandSetEditCtrlPosiRestrictionEnable(currentIndex) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("enable")
                        }
                    }

                    NInputNumber{
                        id : ctrlPosiRestricMaxItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: ctrlPosiRestricEnableItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100 && ctrlPosiRestricEnableItem.currentIndex == 1

                        textField.validator: DoubleValidator{}
                        textField.color: dlgModel.mErrCtrlPosiRestrictionMax ? "#FF0000" :
                                         dlgModel.mIsEditCtrlPosiRestrictionMax ? "#24A7FF" : "#000000"
                        stepValue : 0.0001; minValue: 0; maxValue: 10000000
                        fixedN : 3

                        onChangedText: { dlgModel.onCommandSetEditCtrlPosiRestrictionMax(textField.text) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("max (pos)")
                        }
                    }

                    NInputNumber{
                        id : ctrlPosiRestricMinItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: ctrlPosiRestricMaxItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100 && ctrlPosiRestricEnableItem.currentIndex == 1

                        textField.validator: DoubleValidator{}
                        textField.color: dlgModel.mErrCtrlPosiRestrictionMin ? "#FF0000" :
                                         dlgModel.mIsEditCtrlPosiRestrictionMin ? "#24A7FF" : "#000000"
                        stepValue : 0.0001; minValue: 0; maxValue: 10000000
                        fixedN : 3

                        onChangedText: { dlgModel.onCommandSetEditCtrlPosiRestrictionMin(textField.text) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("min (pos)")
                        }
                    }

                    NText{
                        id : defaultControllerLabel
                        anchors.top: ctrlPosiRestricMinItem.bottom; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold : true; text : qsTr("default Controller Selector")
                    }

                    NComboBox{
                        id : controllerSelectItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: defaultControllerLabel.bottom; anchors.topMargin: GUISetting.margin*0.4; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrControllerSelector ? "#FF0000" :
                                   dlgModel.mIsEditControllerSelector ? "#24A7FF" : "#000000"

                        enabled: dialog.progress === 100

                        model: ["0: none", "1: controller 1", "2: controller 2", "3: controller 3", "4: controller 4"]

                        onCurrentIndexChanged: { dlgModel.onCommandSetEditControllerSelector(currentIndex) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("default controller")
                        }
                    }

                    NText{
                        id : autoControllerLabel
                        anchors.top: controllerSelectItem.bottom; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold : true; text : qsTr("Auto Controller Selector")
                    }

                    NComboBox{
                        id : autoControllerEnableItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: autoControllerLabel.bottom; anchors.topMargin: GUISetting.margin*0.4; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrAutoControllerSelectEnable ? "#FF0000" :
                                   dlgModel.mIsEditAutoControllerSelectEnable ? "#24A7FF" : "#000000"

                        enabled: dialog.progress === 100

                        model: ["0: disable", "1: enable"]

                        onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerSelectEnable(currentIndex) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("enable")
                        }
                    }

                    NComboBox{
                        id : autoControllerModeItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: autoControllerEnableItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrAutoControllerSelectMode    ? "#FF0000" :
                                   dlgModel.mIsEditAutoControllerSelectMode ? "#24A7FF" : "#000000"

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                        model: ["0:threshold", "1: pressure direction"]

                        onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerSelectMode(currentIndex) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("mode")
                        }
                    }

                    NComboBox{
                        id : autoControllerPresRisingItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: autoControllerModeItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrAutoControllerPresRising    ? "#FF0000" :
                                   dlgModel.mIsEditAutoControllerPresRising ? "#24A7FF" : "#000000"

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex != 0

                        model: ["0:none", "1:Controller 1", "2:Controller 2", "3:Controller 3", "4:Controller 4"]

                        onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerPresRising(currentIndex) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("controller pressure rising")
                        }
                    }

                    NComboBox{
                        id : autoControllerFallingItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: autoControllerPresRisingItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrAutoControllerPresFalling ? "#FF0000" :
                                   dlgModel.mIsEditAutoControllerPresFalling ? "#24A7FF" : "#000000"

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex != 0

                        model: ["0:none", "1:Controller 1", "2:Controller 2", "3:Controller 3", "4:Controller 4"]

                        onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerPresFalling(currentIndex) }


                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("controller pressure falling")
                        }
                    }

                    NText{
                        id : autoControllerSelect1Item
                        height: 24 * GUISetting.scale
                        anchors.top: autoControllerFallingItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                        verticalAlignment: Text.AlignVCenter; text : qsTr("select controller1")

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0
                        opacity: enabled ? 1 : 0.3
                        color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                        Rectangle{
                            property color  selectedColor   : "#24A7FF"
                            property color  unSelectedColor : "#00000000"
                            property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x01) == 0x01

                            width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                            anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                            radius: width / 4
                            border.width: isSelected ? 0 : 2 * GUISetting.scale
                            border.color: isSelected ? unSelectedColor : selectedColor
                            color: isSelected ? selectedColor : unSelectedColor

                            MouseArea{
                                anchors.fill: parent

                                onClicked: {
                                    parent.isSelected = !parent.isSelected
                                    dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 0);
                                }
                            }
                        }
                    }

                    NText{
                        id : autoControllerSelect2Item
                        height: 24 * GUISetting.scale
                        anchors.top: autoControllerSelect1Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                        verticalAlignment: Text.AlignVCenter; text : qsTr("select controller2")

                        enabled: dialog.progress === 100&& autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0
                        opacity: enabled ? 1 : 0.3
                        color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                        Rectangle{
                            property color  selectedColor   : "#24A7FF"
                            property color  unSelectedColor : "#00000000"
                            property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x02) == 0x02

                            width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                            anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                            radius: width / 4
                            border.width: isSelected ? 0 : 2 * GUISetting.scale
                            border.color: isSelected ? unSelectedColor : selectedColor
                            color: isSelected ? selectedColor : unSelectedColor

                            MouseArea{
                                anchors.fill: parent

                                onClicked: {
                                    parent.isSelected = !parent.isSelected
                                    dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 1);
                                }
                            }
                        }
                    }

                    NText{
                        id : autoControllerSelect3Item
                        height: 24 * GUISetting.scale
                        anchors.top: autoControllerSelect2Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                        verticalAlignment: Text.AlignVCenter; text : qsTr("select controller3")

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0
                        opacity: enabled ? 1 : 0.3
                        color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                        Rectangle{
                            property color  selectedColor   : "#24A7FF"
                            property color  unSelectedColor : "#00000000"
                            property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x04) == 0x04

                            width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                            anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                            radius: width / 4
                            border.width: isSelected ? 0 : 2 * GUISetting.scale
                            border.color: isSelected ? unSelectedColor : selectedColor
                            color: isSelected ? selectedColor : unSelectedColor

                            MouseArea{
                                anchors.fill: parent

                                onClicked: {
                                    parent.isSelected = !parent.isSelected
                                    dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 2);
                                }
                            }
                        }
                    }

                    NText{
                        id : autoControllerSelect4Item
                        height: 24 * GUISetting.scale
                        anchors.top: autoControllerSelect3Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                        verticalAlignment: Text.AlignVCenter; text : qsTr("select controller4")

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0
                        opacity: enabled ? 1 : 0.3
                        color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                        Rectangle{
                            property color  selectedColor   : "#24A7FF"
                            property color  unSelectedColor : "#00000000"
                            property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x08) == 0x08

                            width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                            anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                            radius: width / 4
                            border.width: isSelected ? 0 : 2 * GUISetting.scale
                            border.color: isSelected ? unSelectedColor : selectedColor
                            color: isSelected ? selectedColor : unSelectedColor

                            MouseArea{
                                anchors.fill: parent

                                onClicked: {
                                    parent.isSelected = !parent.isSelected
                                    dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 3);
                                }
                            }
                        }
                    }

                    NComboBox{
                        id : autoControllerThresConditionItem
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: autoControllerSelect4Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        textColor: dlgModel.mErrAutoControllerThreCondition ? "#FF0000" :
                                   dlgModel.mIsEditAutoControllerThreCondition ? "#24A7FF" : "#000000"

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0

                        model: ["0: Lower Or Equal", "1: Equal"]

                        onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerThreCondition(currentIndex) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("threshold condition")
                        }
                    }

                    NInputNumber{
                        id : threshold1Item
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: autoControllerThresConditionItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0

                        textField.validator: DoubleValidator{}
                        textField.color: dlgModel.mErrAutoController1ThreValue    ? "#FF0000" :
                                         dlgModel.mIsEditAutoController1ThreValue ? "#24A7FF" : "#000000"
                        stepValue : 0.0001; minValue: 0; maxValue: 100000000
                        fixedN : 4

                        onChangedText: { dlgModel.onCommandSetEditAutoController1ThreValue(textField.text) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("controller 1 threshold")
                        }
                    }

                    NInputNumber{
                        id : threshold2Item
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: threshold1Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0

                        textField.validator: DoubleValidator{}
                        textField.color: dlgModel.mErrAutoController2ThreValue    ? "#FF0000" :
                                         dlgModel.mIsEditAutoController2ThreValue ? "#24A7FF" : "#000000"
                        stepValue : 0.0001; minValue: 0; maxValue: 100000000
                        fixedN : 4

                        onChangedText: { dlgModel.onCommandSetEditAutoController2ThreValue(textField.text) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("controller 2 threshold")
                        }
                    }

                    NInputNumber{
                        id : threshold3Item
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: threshold2Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0

                        textField.validator: DoubleValidator{}
                        textField.color: dlgModel.mErrAutoController3ThreValue    ? "#FF0000" :
                                         dlgModel.mIsEditAutoController3ThreValue ? "#24A7FF" : "#000000"
                        stepValue : 0.0001; minValue: 0; maxValue: 100000000
                        fixedN : 4

                        onChangedText: { dlgModel.onCommandSetEditAutoController3ThreValue(textField.text) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("controller 3 threshold")
                        }
                    }

                    NInputNumber{
                        id : threshold4Item
                        width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.top: threshold3Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0 && autoControllerModeItem.currentIndex == 0

                        textField.validator: DoubleValidator{}
                        textField.color: dlgModel.mErrAutoController4ThreValue    ? "#FF0000" :
                                         dlgModel.mIsEditAutoController4ThreValue ? "#24A7FF" : "#000000"
                        stepValue : 0.0001; minValue: 0; maxValue: 100000000
                        fixedN : 4

                        onChangedText: { dlgModel.onCommandSetEditAutoController4ThreValue(textField.text) }

                        NText{
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                            text : qsTr("controller 4 threshold")
                        }
                    }
                }
            }





            /*
                NScrollView{
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;

                    delegate : Item{
                        property PressureCtrlForPmProtoDlgModel argDlgModel : dlgModel
                        Connections {
                            target: argDlgModel

                            function onSignalEventChangedControllerSelector          (value) { controllerSelectItem.currentIndex             = value }
                            function onSignalEventChangedPresCtrlSpeed               (value) { presCtrlSpeedItem.textField.text              = value }
                            function onSignalEventChangedCtrlPosiRestrictionEnable   (value) { ctrlPosiRestricEnableItem.currentIndex        = value }
                            function onSignalEventChangedCtrlPosiRestrictionMax      (value) { ctrlPosiRestricMaxItem.textField.text         = value }
                            function onSignalEventChangedCtrlPosiRestrictionMin      (value) { ctrlPosiRestricMinItem.textField.text         = value }
                            function onSignalEventChangedAutoControllerSelectEnable  (value) { autoControllerEnableItem.currentIndex         = value }
                            function onSignalEventChangedAutoControllerSelectMode    (value) { autoControllerModeItem.currentIndex           = value }
                            function onSignalEventChangedAutoControllerPresRising    (value) { autoControllerPresRisingItem.currentIndex     = value }
                            function onSignalEventChangedAutoControllerPresFalling   (value) { autoControllerFallingItem.currentIndex        = value }
                            function onSignalEventChangedAutoControllerThreCondition (value) { autoControllerThresConditionItem.currentIndex = value }
                            function onSignalEventChangedAutoController1ThreValue    (value) { threshold1Item.textField.text                 = value }
                            function onSignalEventChangedAutoController2ThreValue    (value) { threshold2Item.textField.text                 = value }
                            function onSignalEventChangedAutoController3ThreValue    (value) { threshold3Item.textField.text                 = value }
                            function onSignalEventChangedAutoController4ThreValue    (value) { threshold4Item.textField.text                 = value }

                            //function onMAutoControllerSelectBitmapChanged (value){ autoControllerSelectBitmapItem}
                        }

                        anchors.left: parent.left; anchors.right: parent.right;
                        height : 750 * GUISetting.scale

                        //Rectangle{
                        //    id : conductanceItem
                        //    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                        //    anchors.top: parent.top; anchors.topMargin: GUISetting.margin * 0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        //    color : "#E4E4E4"

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        //        text : dlgModel.mConductance
                        //    }

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                        //        horizontalAlignment: Text.AlignRight; text : qsTr("conductance (l/s)")
                        //    }
                        //}

                        //Rectangle{
                        //    id : mfcFlowItem
                        //    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                        //    anchors.top: conductanceItem.bottom; anchors.topMargin: GUISetting.margin * 0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        //    color : "#E4E4E4"

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        //        text : dlgModel.mMfcFlow
                        //    }

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                        //        horizontalAlignment: Text.AlignRight; text : qsTr("MFC flow")
                        //    }
                        //}

                        //Rectangle{
                        //    id : mfcFlowUnitItem
                        //    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                        //    anchors.top: mfcFlowItem.bottom; anchors.topMargin: GUISetting.margin * 0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        //    color : "#E4E4E4"

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        //        text : dlgModel.mMfcFlowUnit == 0 ? "slm"      :
                        //               dlgModel.mMfcFlowUnit == 1 ? "sccm"     :
                        //               dlgModel.mMfcFlowUnit == 2 ? "mbar l/s" :
                        //               dlgModel.mMfcFlowUnit == 3 ? "Pa m^3/s" : "unknown"
                        //    }

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                        //        text : qsTr("MFC flow unit")
                        //    }
                        //}

                        //Rectangle{
                        //    id : chamberVolItem
                        //    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                        //    anchors.top: mfcFlowUnitItem.bottom; anchors.topMargin: GUISetting.margin * 0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        //    color : "#E4E4E4"

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        //        horizontalAlignment: Text.AlignRight; text : dlgModel.mChamberVol
                        //    }

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                        //        text : qsTr("chamber volume (L)")
                        //    }
                        //}

                        //Rectangle{
                        //    id : adaptiveConductanceGainItem
                        //    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                        //    anchors.top: chamberVolItem.bottom; anchors.topMargin: GUISetting.margin * 0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        //    color : "#E4E4E4"

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        //        horizontalAlignment: Text.AlignRight; text : dlgModel.mAdaptiveConductanceGain
                        //    }

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                        //        text : qsTr("adaptive conductance gain")
                        //    }
                        //}

                        //Rectangle{
                        //    id : adaptiveFlowGainItem
                        //    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                        //    anchors.top: adaptiveConductanceGainItem.bottom; anchors.topMargin: GUISetting.margin * 0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        //    color : "#E4E4E4"

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        //        horizontalAlignment: Text.AlignRight; text : dlgModel.mAdaptiveFlowGain
                        //    }

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                        //        text : qsTr("adaptive flow gain")
                        //    }
                        //}

                        //Rectangle{
                        //    id : adaptiveTotalGainItem
                        //    height: 24 * GUISetting.scale; width: 150 * GUISetting.scale
                        //    anchors.top: adaptiveFlowGainItem.bottom; anchors.topMargin: GUISetting.margin * 0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                        //    color : "#E4E4E4"

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        //        text : dlgModel.mAdaptiveTotalGain
                        //    }

                        //    NText{
                        //        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                        //        horizontalAlignment: Text.AlignRight; text : qsTr("adaptive total gain")
                        //    }
                        //}

                        NText{
                            id : basicLabel
                            anchors.top: adaptiveTotalGainItem.bottom; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                            isBold : true; text : qsTr("Basic")
                        }

                        NInputNumber{
                            id : presCtrlSpeedItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: basicLabel.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            enabled: dialog.progress === 100

                            textField.validator: DoubleValidator{}
                            textField.color: dlgModel.mErrPresCtrlSpeed ? "#FF0000" :
                                             dlgModel.mIsEditPresCtrlSpeed ? "#24A7FF" : "#000000"
                            stepValue : 0.0001; minValue: 0; maxValue: 1
                            fixedN : 3

                            onChangedText: { dlgModel.onCommandSetEditPresCtrlSpeed(textField.text) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("pressure control speed(0.001 ~ 1)")
                            }
                        }

                        NText{
                            id : ctrlPosiRestrictionLabel
                            anchors.top: presCtrlSpeedItem.bottom; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                            isBold : true; text : qsTr("Control Position Restriction")
                        }

                        NComboBox{
                            id : ctrlPosiRestricEnableItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: ctrlPosiRestrictionLabel.bottom; anchors.topMargin: GUISetting.margin*0.4; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            textColor: dlgModel.mErrCtrlPosiRestrictionEnable ? "#FF0000" :
                                       dlgModel.mIsEditCtrlPosiRestrictionEnable ? "#24A7FF" : "#000000"

                            enabled: dialog.progress === 100

                            model: ["0: disable", "1: enable"]

                            onCurrentIndexChanged: { dlgModel.onCommandSetEditCtrlPosiRestrictionEnable(currentIndex) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("enable")
                            }
                        }

                        NInputNumber{
                            id : ctrlPosiRestricMaxItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: ctrlPosiRestricEnableItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            enabled: dialog.progress === 100 && ctrlPosiRestricEnableItem.currentIndex == 1

                            textField.validator: DoubleValidator{}
                            textField.color: dlgModel.mErrCtrlPosiRestrictionMax ? "#FF0000" :
                                             dlgModel.mIsEditCtrlPosiRestrictionMax ? "#24A7FF" : "#000000"
                            stepValue : 0.0001; minValue: 0; maxValue: 10000000
                            fixedN : 3

                            onChangedText: { dlgModel.onCommandSetEditCtrlPosiRestrictionMax(textField.text) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("max (pos)")
                            }
                        }

                        NInputNumber{
                            id : ctrlPosiRestricMinItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: ctrlPosiRestricMaxItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            enabled: dialog.progress === 100 && ctrlPosiRestricEnableItem.currentIndex == 1

                            textField.validator: DoubleValidator{}
                            textField.color: dlgModel.mErrCtrlPosiRestrictionMin ? "#FF0000" :
                                             dlgModel.mIsEditCtrlPosiRestrictionMin ? "#24A7FF" : "#000000"
                            stepValue : 0.0001; minValue: 0; maxValue: 10000000
                            fixedN : 3

                            onChangedText: { dlgModel.onCommandSetEditCtrlPosiRestrictionMin(textField.text) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("min (pos)")
                            }
                        }

                        NText{
                            id : autoControllerLabel
                            anchors.top: ctrlPosiRestricMinItem.bottom; anchors.topMargin: GUISetting.margin*0.7; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                            isBold : true; text : qsTr("Auto Controller Selector")
                        }

                        NComboBox{
                            id : autoControllerEnableItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: autoControllerLabel.bottom; anchors.topMargin: GUISetting.margin*0.4; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            textColor: dlgModel.mErrAutoControllerSelectEnable ? "#FF0000" :
                                       dlgModel.mIsEditAutoControllerSelectEnable ? "#24A7FF" : "#000000"

                            enabled: dialog.progress === 100

                            model: ["0: disable", "1: enable"]

                            onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerSelectEnable(currentIndex) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("enable")
                            }
                        }

                        NComboBox{
                            id : controllerSelectItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: autoControllerEnableItem.bottom; anchors.topMargin: GUISetting.margin*0.4; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            textColor: dlgModel.mErrControllerSelector ? "#FF0000" :
                                       dlgModel.mIsEditControllerSelector ? "#24A7FF" : "#000000"

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex == 0

                            model: ["0: none", "1: controller 1", "2: controller 2", "3: controller 3", "4: controller 4"]

                            onCurrentIndexChanged: { dlgModel.onCommandSetEditControllerSelector(currentIndex) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("controller selector for manual mode")
                            }
                        }

                        NComboBox{
                            id : autoControllerModeItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: controllerSelectItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            textColor: dlgModel.mErrAutoControllerSelectMode    ? "#FF0000" :
                                       dlgModel.mIsEditAutoControllerSelectMode ? "#24A7FF" : "#000000"

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            model: ["0:threshold", "1: pressure direction"]

                            onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerSelectMode(currentIndex) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("mode")
                            }
                        }

                        NComboBox{
                            id : autoControllerPresRisingItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: autoControllerModeItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            textColor: dlgModel.mErrAutoControllerPresRising    ? "#FF0000" :
                                       dlgModel.mIsEditAutoControllerPresRising ? "#24A7FF" : "#000000"

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            model: ["0:unknown", "1:Controller 1", "2:Controller 2", "3:Controller 3", "4:Controller 4"]

                            onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerPresRising(currentIndex) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("controller pressure rising")
                            }
                        }

                        NComboBox{
                            id : autoControllerFallingItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: autoControllerPresRisingItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            textColor: dlgModel.mErrAutoControllerPresFalling ? "#FF0000" :
                                       dlgModel.mIsEditAutoControllerPresFalling ? "#24A7FF" : "#000000"

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            model: ["0:unknown", "1:Controller 1", "2:Controller 2", "3:Controller 3", "4:Controller 4"]

                            onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerPresFalling(currentIndex) }


                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("controller pressure falling")
                            }
                        }

                        NText{
                            id : autoControllerSelect1Item
                            height: 24 * GUISetting.scale
                            anchors.top: autoControllerFallingItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                            verticalAlignment: Text.AlignVCenter; text : qsTr("select controller1")

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0
                            opacity: enabled ? 1 : 0.3
                            color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                    dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                            Rectangle{
                                property color  selectedColor   : "#24A7FF"
                                property color  unSelectedColor : "#00000000"
                                property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x01) == 0x01

                                width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                                anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                                radius: width / 4
                                border.width: isSelected ? 0 : 2 * GUISetting.scale
                                border.color: isSelected ? unSelectedColor : selectedColor
                                color: isSelected ? selectedColor : unSelectedColor

                                MouseArea{
                                    anchors.fill: parent

                                    onClicked: {
                                        parent.isSelected = !parent.isSelected
                                        dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 0);
                                    }
                                }
                            }
                        }

                        NText{
                            id : autoControllerSelect2Item
                            height: 24 * GUISetting.scale
                            anchors.top: autoControllerSelect1Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                            verticalAlignment: Text.AlignVCenter; text : qsTr("select controller2")

                            enabled: dialog.progress === 100&& autoControllerEnableItem.currentIndex != 0
                            opacity: enabled ? 1 : 0.3
                            color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                    dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                            Rectangle{
                                property color  selectedColor   : "#24A7FF"
                                property color  unSelectedColor : "#00000000"
                                property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x02) == 0x02

                                width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                                anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                                radius: width / 4
                                border.width: isSelected ? 0 : 2 * GUISetting.scale
                                border.color: isSelected ? unSelectedColor : selectedColor
                                color: isSelected ? selectedColor : unSelectedColor

                                MouseArea{
                                    anchors.fill: parent

                                    onClicked: {
                                        parent.isSelected = !parent.isSelected
                                        dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 1);
                                    }
                                }
                            }
                        }

                        NText{
                            id : autoControllerSelect3Item
                            height: 24 * GUISetting.scale
                            anchors.top: autoControllerSelect2Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                            verticalAlignment: Text.AlignVCenter; text : qsTr("select controller3")

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0
                            opacity: enabled ? 1 : 0.3
                            color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                    dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                            Rectangle{
                                property color  selectedColor   : "#24A7FF"
                                property color  unSelectedColor : "#00000000"
                                property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x04) == 0x04

                                width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                                anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                                radius: width / 4
                                border.width: isSelected ? 0 : 2 * GUISetting.scale
                                border.color: isSelected ? unSelectedColor : selectedColor
                                color: isSelected ? selectedColor : unSelectedColor

                                MouseArea{
                                    anchors.fill: parent

                                    onClicked: {
                                        parent.isSelected = !parent.isSelected
                                        dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 2);
                                    }
                                }
                            }
                        }

                        NText{
                            id : autoControllerSelect4Item
                            height: 24 * GUISetting.scale
                            anchors.top: autoControllerSelect3Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: (GUISetting.margin * 2) + (10 * GUISetting.scale)
                            verticalAlignment: Text.AlignVCenter; text : qsTr("select controller4")

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0
                            opacity: enabled ? 1 : 0.3
                            color : dlgModel.mErrAutoControllerSelectBitmap    ? "FF0000" :
                                    dlgModel.mIsEditAutoControllerSelectBitmap ? "#24A7FF" : "#000000"

                            Rectangle{
                                property color  selectedColor   : "#24A7FF"
                                property color  unSelectedColor : "#00000000"
                                property bool isSelected : (dlgModel.mAutoControllerSelectBitmap & 0x08) == 0x08

                                width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                                anchors.right: parent.left; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                                radius: width / 4
                                border.width: isSelected ? 0 : 2 * GUISetting.scale
                                border.color: isSelected ? unSelectedColor : selectedColor
                                color: isSelected ? selectedColor : unSelectedColor

                                MouseArea{
                                    anchors.fill: parent

                                    onClicked: {
                                        parent.isSelected = !parent.isSelected
                                        dlgModel.onCommandSetEditAutoControllerSelectBitmap(parent.isSelected, 3);
                                    }
                                }
                            }
                        }

                        NComboBox{
                            id : autoControllerThresConditionItem
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: autoControllerSelect4Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            textColor: dlgModel.mErrAutoControllerThreCondition ? "#FF0000" :
                                       dlgModel.mIsEditAutoControllerThreCondition ? "#24A7FF" : "#000000"

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            model: ["0: Lower Or Equal", "1: Equal"]

                            onCurrentIndexChanged: { dlgModel.onCommandSetEditAutoControllerThreCondition(currentIndex) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("threshold condition")
                            }
                        }

                        NInputNumber{
                            id : threshold1Item
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: autoControllerThresConditionItem.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            textField.validator: DoubleValidator{}
                            textField.color: dlgModel.mErrAutoController1ThreValue    ? "#FF0000" :
                                             dlgModel.mIsEditAutoController1ThreValue ? "#24A7FF" : "#000000"
                            stepValue : 0.0001; minValue: 0; maxValue: 100000000
                            fixedN : 4

                            onChangedText: { dlgModel.onCommandSetEditAutoController1ThreValue(textField.text) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("controller 1 threshold(^mbar/sec)")
                            }
                        }

                        NInputNumber{
                            id : threshold2Item
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: threshold1Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            textField.validator: DoubleValidator{}
                            textField.color: dlgModel.mErrAutoController2ThreValue    ? "#FF0000" :
                                             dlgModel.mIsEditAutoController2ThreValue ? "#24A7FF" : "#000000"
                            stepValue : 0.0001; minValue: 0; maxValue: 100000000
                            fixedN : 4

                            onChangedText: { dlgModel.onCommandSetEditAutoController2ThreValue(textField.text) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("controller 2 threshold(^mbar/sec)")
                            }
                        }

                        NInputNumber{
                            id : threshold3Item
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: threshold2Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            textField.validator: DoubleValidator{}
                            textField.color: dlgModel.mErrAutoController3ThreValue    ? "#FF0000" :
                                             dlgModel.mIsEditAutoController3ThreValue ? "#24A7FF" : "#000000"
                            stepValue : 0.0001; minValue: 0; maxValue: 100000000
                            fixedN : 4

                            onChangedText: { dlgModel.onCommandSetEditAutoController3ThreValue(textField.text) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("controller 3 threshold(^mbar/sec)")
                            }
                        }

                        NInputNumber{
                            id : threshold4Item
                            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                            anchors.top: threshold3Item.bottom; anchors.topMargin: GUISetting.margin*0.3; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                            enabled: dialog.progress === 100 && autoControllerEnableItem.currentIndex != 0

                            textField.validator: DoubleValidator{}
                            textField.color: dlgModel.mErrAutoController4ThreValue    ? "#FF0000" :
                                             dlgModel.mIsEditAutoController4ThreValue ? "#24A7FF" : "#000000"
                            stepValue : 0.0001; minValue: 0; maxValue: 100000000
                            fixedN : 4

                            onChangedText: { dlgModel.onCommandSetEditAutoController4ThreValue(textField.text) }

                            NText{
                                anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.right; anchors.leftMargin: GUISetting.margin
                                text : qsTr("controller 4 threshold(^mbar/sec)")
                            }
                        }
                    }
                }
            }*/

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: generalItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: generalItem.left; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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
