import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../control/."
import "./."
import FontManager 1.0
import ValveEnumDef 1.0
import GlobalUiValue 1.0
import GUISetting 1.0

Rectangle {
    id : panel

    property bool isDevMode : false
    property var  company : ValveEnumDef.COMPANY_NOVA
    property var  access : ValveEnumDef.ACCESS_REMOTE
    property var  mode : ValveEnumDef.MODE_INIT
    property bool isOpen  : false
    property bool isClose : false
    property bool connected : false
    property bool isLearnRunning : false


    color: "#FFFFFF"

    signal clickLearn();
    signal clickZero();
    signal clickSimulation();
    signal clickHold();
    signal clickOpen();
    signal clickClose();
    signal clickSoftOpen();
    signal clickSoftClose();

    NText{
        id : title
        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        isBold: true
        text : qsTr("Control")
    }

    Column{
        anchors.top: title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;
        spacing: GUISetting.margin

        NButton{
            height: GUISetting.btn_nor_height; width: parent.width
            text.text: qsTr("Learn")

            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
                     && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
                     && panel.connected && !GlobalUiValue.disableWinCreateBtn

            onClick: { panel.clickLearn()}

            Rectangle{
                width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                radius: (width / 2) + 1
                color: panel.isLearnRunning ? "#24A7FF" : "#E4E4E4"
            }
        }

        NButton{
            height: GUISetting.btn_nor_height; width: parent.width
            text.text: qsTr("Zero")

            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
                     && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
                     && panel.connected
                     && panel.company !== ValveEnumDef.COMPANY_APSYS && !GlobalUiValue.disableWinCreateBtn

            onClick: { panel.clickZero()}
        }

        NButton{
            height: GUISetting.btn_nor_height; width: parent.width
            text.text: qsTr("Hold")

            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
                     && panel.mode !== ValveEnumDef.MODE_CLOSED && panel.mode !== ValveEnumDef.MODE_OPEN && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
                     && panel.connected

            onClick: { panel.clickHold()}

            Rectangle{
                width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                radius: (width / 2) + 1
                color: panel.mode === ValveEnumDef.MODE_HOLD ? "#24A7FF" : "#E4E4E4"
            }
        }

        NButton{
            height: GUISetting.btn_nor_height; width: parent.width
            text.text: qsTr("Open")

            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
                     && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
                     && panel.connected

            onClick: { panel.clickOpen()}

            Rectangle{
                width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                radius: (width / 2) + 1
                color: panel.isOpen ? "#24A7FF" : "#E4E4E4"
            }
        }

        NButton{
            height: GUISetting.btn_nor_height; width: parent.width
            text.text: qsTr("Close")

            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
                     && panel.mode !== ValveEnumDef.MODE_SAFETY  && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
                     && panel.connected

            onClick: { panel.clickClose()}

            Rectangle{
                width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                radius: (width / 2) + 1
                color: panel.isClose ? "#24A7FF" : "#E4E4E4"
            }
        }

        NButton{
            height: GUISetting.btn_nor_height; width: parent.width
            text.text: qsTr("Simulator")

            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
                     && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
                     && panel.connected

            onClick: { panel.clickSimulation()}
        }

//        NButton{
//            height: 24; width: parent.width
//            text.text: qsTr("Soft open")

//            visible: panel.isDevMode
//            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
//                     && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
//                     && panel.connected

//            onClick: { panel.clickSoftOpen()}
//        }

//        NButton{
//            height: 24; width: parent.width
//            text.text: qsTr("Soft close")

//            visible: panel.isDevMode
//            enabled:    panel.access === ValveEnumDef.ACCESS_LOCAL
//                     && panel.mode !== ValveEnumDef.MODE_SAFETY && panel.mode !== ValveEnumDef.MODE_INTERLOCK_CLOSE_DI &&  panel.mode !== ValveEnumDef.MODE_INTERLOCK_OPEN_DI
//                     && panel.connected

//            onClick: { panel.clickSoftClose()}
//        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
