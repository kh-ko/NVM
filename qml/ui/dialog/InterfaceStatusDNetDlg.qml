import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import FontManager 1.0
import ValveEnumDef 1.0
import InterfaceStatusDNetDlgModel 1.0
import InterfaceSetupDevNetAssemblyItemModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Interface status")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function commit()
    {
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 900 * GUISetting.scale
    }

    InterfaceStatusDNetDlgModel{
        id : dlgModel

        Component.onCompleted: {
            var i
            var rowCount = dlgModel.onCommandGetInputAssemblyItemCount()

            for(i = 1; i <= rowCount; i ++)
            {
                inputAssemblyListModel.append({"itemSeq":(i)})
            }

            rowCount = dlgModel.onCommandGetOutputAssemblyItemCount()

            for(i = 1; i <= rowCount; i ++)
            {
                outputAssemblyListModel.append({"itemSeq":(i)})
            }
        }
    }

    ListModel{
        id : inputAssemblyListModel
    }

    ListModel{
        id : outputAssemblyListModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            //property alias devStatus              : _devStatus
            //property alias alarmDevComm           : _alarmDevComm
            //property alias alarmDevSpecific       : _alarmDevSpecific
            //property alias alarmMenuSpecific      : _alarmMenuSpecific
            //property alias warningDevComm         : _warningDevComm
            //property alias warningDevSpecific     : _warningDevSpecific
            //property alias warningMenuSpecific    : _warningMenuSpecific
            //property alias expandedMode           : _expandedMode
            //property alias macValue               : _macValue
            //property alias firmwareValue          : _firmwareValue
            //property alias serialNumValue         : _serialNumValue
            //property alias inputAssemblyValue     : _inputAssemblyValue
            //property alias outputAssemblyValue    : _outputAssemblyValue
            //property alias positionUnitValue      : _positionUnitValue
            //property alias positionRangeValue     : _positionRangeValue
            //property alias pressureUnitValue      : _pressureUnitValue
            //property alias sensor01RangeValue     : _sensor01RangeValue
            //property alias sensor02RangeValue     : _sensor02RangeValue


            property real guiScale : GUISetting.scale

            height: (GUISetting.line_margin + devStatusItem.height) + (GUISetting.line_margin + exceptionStatusItem.height) + (GUISetting.line_margin + diItem.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = 900 * GUISetting.scale// GUISetting.popup_nor_width
            }

            Rectangle{
                id : devStatusItem

                height: (GUISetting.margin + devStatusTitle.height) + (GUISetting.margin + devStatusBox.height) + GUISetting.margin;
                width: (parent.width - (GUISetting.line_margin * 4)) / 3
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : devStatusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Device status")
                }

                Rectangle{
                    id : devStatusBox
                    height: 30 * GUISetting.scale
                    anchors.top: devStatusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color:  "#E4E4E4"

                    NText{
                        id : _devStatus
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mDevStatus
                    }
                }
            }

            Rectangle{
                id : exceptionStatusItem

                width: devStatusItem.width
                anchors.top: devStatusItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: diItem.top; anchors.bottomMargin : GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : exceptionStatusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("exception status")
                }

                Item{
                    id : alarmDevCommBox
                    height: 24 * GUISetting.scale
                    anchors.top: exceptionStatusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _alarmDevComm

                        property bool isON : dlgModel.mAlarmDevComm

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _alarmDevComm.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("ALARM/device-common")
                    }
                }

                Item{
                    id : alarmDevSpecificBox
                    height: 24 * GUISetting.scale
                    anchors.top: alarmDevCommBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _alarmDevSpecific

                        property bool isON : dlgModel.mAlarmDevSpecific

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _alarmDevSpecific.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("ALARM/device-specific")
                    }
                }

                Item{
                    id : alarmMenuSpecificBox
                    height: 24 * GUISetting.scale
                    anchors.top: alarmDevSpecificBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _alarmMenuSpecific

                        property bool isON : dlgModel.mAlarmMenuSpecific

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _alarmMenuSpecific.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("ALARM/manufacturer-specific")
                    }
                }

                Item{
                    id : undefinedBox
                    height: 24 * GUISetting.scale
                    anchors.top: alarmMenuSpecificBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _undefined

                        property bool isON : false

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _undefined.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("undefined")
                    }
                }

                Item{
                    id : warningDevCommBox
                    height: 24 * GUISetting.scale
                    anchors.top: undefinedBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _warningDevComm

                        property bool isON : dlgModel.mWarningDevComm

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _warningDevComm.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("WARNING/device-common")
                    }
                }

                Item{
                    id : warningDevSpecificBox
                    height: 24 * GUISetting.scale
                    anchors.top: warningDevCommBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _warningDevSpecific

                        property bool isON : dlgModel.mWarningDevSpecific

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _warningDevSpecific.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("WARNING/device-specific")
                    }
                }

                Item{
                    id : warningMenuSpecificBox
                    height: 24 * GUISetting.scale
                    anchors.top: warningDevSpecificBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _warningMenuSpecific

                        property bool isON : dlgModel.mWarningMenuSpecific

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _warningMenuSpecific.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("WARNING/manufacturer-specific")
                    }
                }

                Item{
                    id : expandedModeBox
                    height: 24 * GUISetting.scale
                    anchors.top: warningMenuSpecificBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    Rectangle{
                        id : _expandedMode

                        property bool isON : dlgModel.mExpandedMode

                        width: 10 * GUISetting.scale; height: 10 * GUISetting.scale
                        anchors.left: parent.left; anchors.verticalCenter: parent.verticalCenter

                        radius: width / 4
                        border.width: isON ? 0 : 2 * GUISetting.scale
                        border.color: isON ? "#00000000" : "#24A7FF"
                        color: isON ? "#24A7FF" : "#00000000"
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: _expandedMode.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("expanded mode")
                    }
                }

                Rectangle{
                    anchors.top: exceptionStatusTitle.bottom; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom;
                    color: "#FFFFFF"

                    visible: !dlgModel.mEnableExStatus

                    Image{
                        id : exceptionStatusNotSupportedImg
                        width: sourceSize.width * GUISetting.scale;height: sourceSize.height * GUISetting.scale;
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        source: "/image/icon-info.png"
                    }

                    NText{
                        anchors.verticalCenter: exceptionStatusNotSupportedImg.verticalCenter; anchors.left: exceptionStatusNotSupportedImg.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("not supported!")
                    }
                }

            }

            Rectangle{
                id : generalSettingsItem

                height: (GUISetting.margin + generalSettingsTitle.height + GUISetting.margin) + ((macBox.height + GUISetting.line_margin) * 15) + GUISetting.margin;
                width: (parent.width - (GUISetting.line_margin * 4)) / 3
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: devStatusItem.right; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : generalSettingsTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("General interface settings")
                }

                Rectangle{
                    id : macBox
                    height: 30 * GUISetting.scale
                    anchors.top: generalSettingsTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("MAC address")
                    }

                    NText{
                        id : _macValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mMacValue
                    }
                }

                Rectangle{
                    id : baudrateBox
                    height: 30 * GUISetting.scale
                    anchors.top: macBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("baudrate")
                    }

                    NText{
                        id : _baudrateValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : qsTr("auto")
                    }
                }

                Rectangle{
                    id : firmwareBox
                    height: 30 * GUISetting.scale
                    anchors.top: baudrateBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("firmware")
                    }

                    NText{
                        id : _firmwareValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mFirmwareValue
                    }
                }

                Rectangle{
                    id : serialNumBox
                    height: 30 * GUISetting.scale
                    anchors.top: firmwareBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("serial number")
                    }

                    NText{
                        id : _serialNumValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mSerialNumValue
                    }
                }

                /*
                Rectangle{
                    id : inputAssemblyBox
                    height: 30 * GUISetting.scale
                    anchors.top: serialNumBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("input assembly")
                    }

                    NText{
                        id : _inputAssemblyValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : qsTr("0")
                    }
                }

                Rectangle{
                    id : outputAssemblyBox
                    height: 30 * GUISetting.scale
                    anchors.top: inputAssemblyBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("output assembly")
                    }

                    NText{
                        id : _outputAssemblyValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : qsTr("0")
                    }
                }
                */

                Rectangle{
                    id : positionUnitBox
                    height: 30 * GUISetting.scale
                    anchors.top: serialNumBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("position unit")
                    }

                    NText{
                        id : _positionUnitValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mPositionUnitValue
                    }
                }

                Rectangle{
                    id : positionRangeBox
                    height: 30 * GUISetting.scale
                    anchors.top: positionUnitBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("position range")
                    }

                    NText{
                        id : _positionRangeValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mPositionRangeValue
                    }
                }

                Rectangle{
                    id : pressureUnitBox
                    height: 30 * GUISetting.scale
                    anchors.top: positionRangeBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("pressure unit")
                    }

                    NText{
                        id : _pressureUnitValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mPressureUnitValue
                    }
                }

                Rectangle{
                    id : sensor01RangeBox
                    height: 30 * GUISetting.scale
                    anchors.top: pressureUnitBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("sensor 1 range")
                    }

                    NText{
                        id : _sensor01RangeValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mSensor01RangeValue
                    }
                }

                Rectangle{
                    id : sensor02RangeBox
                    height: 30 * GUISetting.scale
                    anchors.top: sensor01RangeBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("sensor 2 range")
                    }

                    NText{
                        id : _sensor02RangeValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: parent.width / 2
                        isBold: true
                        text : dlgModel.mSensor02RangeValue
                    }
                }
            }

            Rectangle{
                id : inputAssemblyItem

                height: (generalSettingsItem.height - GUISetting.line_margin) / 2
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: generalSettingsItem.right; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : inputAssemblyTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Input assembly")
                }

                InterfaceStatusDevNetItem{
                    id : iAssemblyHeader
                    height: 24 * GUISetting.scale
                    anchors.top: inputAssemblyTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    isHeader: true
                    item01Name: qsTr("index")
                    item02Name: qsTr("length")
                    item03Name: qsTr("object")
                }

                Rectangle{
                    anchors.top: iAssemblyHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NScrollView{
                        id : iAssemblyListView
                        anchors.fill: parent
                        anchors.margins: GUISetting.line_margin

                        model: inputAssemblyListModel

                        delegate : Item{
                            property InterfaceSetupDevNetAssemblyItemModel assemblyData : dlgModel.onCommandGetInputAssemblyItem(itemSeq)

                            height  : assemblyData.mIsSelected ? ((24 * GUISetting.scale) + GUISetting.line_margin) : 0; width: iAssemblyListView.width
                            visible : assemblyData.mIsSelected

                            InterfaceStatusDevNetItem{
                                id : iItemContents
                                height: parent.height - GUISetting.line_margin; width: parent.width
                                anchors.top: parent.top

                                isHeader  : false;

                                item01Name : parent.assemblyData.mIndex
                                item02Name : parent.assemblyData.mLength
                                item03Name : parent.assemblyData.mName
                            }
                        }
                    }
                }
            }

            Rectangle{
                id : outputAssemblyItem

                anchors.top: inputAssemblyItem.bottom; anchors.topMargin: GUISetting.line_margin;
                anchors.bottom: generalSettingsItem.bottom;
                anchors.left: generalSettingsItem.right; anchors.leftMargin: GUISetting.line_margin;
                anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : outputAssemblyTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Output assembly")
                }

                InterfaceStatusDevNetItem{
                    id : oAssemblyHeader
                    height: 24 * GUISetting.scale
                    anchors.top: outputAssemblyTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    isHeader: true
                    item01Name: qsTr("index")
                    item02Name: qsTr("length")
                    item03Name: qsTr("object")
                }

                Rectangle{
                    anchors.top: oAssemblyHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NScrollView{
                        id : oAssemblyListView
                        anchors.fill: parent
                        anchors.margins: GUISetting.line_margin

                        model: outputAssemblyListModel

                        delegate : Item{
                            property InterfaceSetupDevNetAssemblyItemModel assemblyData : dlgModel.onCommandGetOutputAssemblyItem(itemSeq)

                            height  : assemblyData.mIsSelected ? ((24 * GUISetting.scale) + GUISetting.line_margin) : 0; width: oAssemblyListView.width
                            visible : assemblyData.mIsSelected

                            InterfaceStatusDevNetItem{
                                id : oItemContents
                                height:  parent.height - GUISetting.line_margin; width: parent.width
                                anchors.top: parent.top

                                isHeader  : false;

                                item01Name : parent.assemblyData.mIndex
                                item02Name : parent.assemblyData.mLength
                                item03Name : parent.assemblyData.mName
                            }
                        }
                    }
                }
            }

            Rectangle{
                id : diItem

                height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + diStatusItem.height) + /*(2 + diInputGroundPin.height)*/ + GUISetting.margin;
                width: (parent.width - (GUISetting.margin * 3)) / 2
                anchors.top  : generalSettingsItem.bottom; anchors.topMargin  : GUISetting.line_margin;
                anchors.left : parent.left               ; anchors.leftMargin : GUISetting.line_margin;
                //anchors.top: generalSettingsItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : diTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital inputs")
                }

                ColumnLayout{
                    id : diStatusItem
                    height: 49 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1 * GUISetting.scale

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("function"); col02Text : qsTr("polarity"); col03Text : qsTr("enabled"); col04Text : qsTr("connector-pin");  col05Text : qsTr("status")
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : dlgModel.mDIFunction   === 0 ? qsTr("interlock close")  : qsTr("interlock open");
                        col02Text : dlgModel.mDIPolarity   === 0 ? qsTr("not inverted") : qsTr("inverted"  );
                        col03Text : dlgModel.mDIActivation === 0 ? qsTr("enabled")      : qsTr("disabled"  );
                        col04Text : qsTr("-");
                        col05Text : dlgModel.mStatusDI === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDI === 1 ? true : false
                    }
                }
            }

            Rectangle{
                id : doItem

                height: diItem.height
                anchors.top   : diItem.top
                anchors.bottom: diItem.bottom
                anchors.left  : diItem.right ; anchors.leftMargin : GUISetting.line_margin
                anchors.right : parent.right ; anchors.rightMargin: GUISetting.line_margin
                //height: (GUISetting.margin + doTitle.height) + (GUISetting.margin + doStatusItem.height) /*+ (2 + doCommPin.height)*/ + GUISetting.margin;
                //anchors.top: diItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : doTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital outputs")
                }

                ColumnLayout{
                    id : doStatusItem
                    height: 49 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: doTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("function"); col02Text : qsTr("polarity"); col03Text : qsTr("enabled"); col04Text : qsTr("connector-pin"); col05Text : qsTr("status")
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : dlgModel.mDOFunction   === 0 ? qsTr("close")  : dlgModel.mDOFunction === 1 ? qsTr("open") : dlgModel.mDOFunction === 2 ? qsTr("constantly ON") : qsTr("On")
                        col02Text : dlgModel.mDOPolarity   === 0 ? qsTr("not inverted") : qsTr("inverted"  );
                        col03Text : dlgModel.mDOActivation === 0 ? qsTr("enabled")      : qsTr("disabled"  );
                        col04Text : qsTr("-");
                        col05Text : dlgModel.mStatusDO === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDO === 1 ? true : false
                    }
                }
            }
        }
    }
}
