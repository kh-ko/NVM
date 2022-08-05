import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import FontManager 1.0
import ValveEnumDef 1.0
import InterfaceStatusLogicDlgModel 1.0
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
        bodyWidth  = GUISetting.popup_nor_width
    }

    InterfaceStatusLogicDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real guiScale : GUISetting.scale

            height: (GUISetting.line_margin + diItem.height) + (GUISetting.line_margin + doItem.height) + (GUISetting.line_margin +  aiItem.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : diItem

                height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + diStatusItem.height) + (GUISetting.line_margin + iCommContactCtrl.height) + (GUISetting.line_margin + iCommVoltageCtrl.height) + GUISetting.line_margin;
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : diTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital inputs")
                }

                ColumnLayout{
                    id : diStatusItem
                    height: 278 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1

                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("digital input"); col02Text : qsTr("configuration"); col03Text : qsTr("connector-pin"); col04Text : qsTr("status")
                    }

                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("open"); col02Text : dlgModel.mDIOpen === 0 ? qsTr("not inverted") : qsTr("inverted"); col03Text : qsTr("17"); col04Text : dlgModel.mStatusDIOpen ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDIOpen === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("close"); col02Text : dlgModel.mDIClose === 0 ? qsTr("not inverted") : qsTr("inverted"); col03Text : qsTr("15"); col04Text : dlgModel.mStatusDIClose ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDIClose === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("control mode"); col02Text : qsTr("-"); col03Text : qsTr("7"); col04Text : dlgModel.mStatusDICtrlModel ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDICtrlModel === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("learn"); col02Text : dlgModel.mLearnRange === 0 ? qsTr("fullrange") : qsTr("analog input"); col03Text : qsTr("19"); col04Text : dlgModel.mStatusDILearn ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDILearn === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("zero"); col02Text : qsTr("-"); col03Text : qsTr("3"); col04Text : dlgModel.mStatusDIZero ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDIZero === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("locked"); col02Text : qsTr("-"); col03Text : qsTr("18"); col04Text : dlgModel.mStatusDILocked ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDILocked === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("hold"); col02Text : qsTr("-"); col03Text : qsTr("16"); col04Text : dlgModel.mStatusDIHold ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDIHold === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("set point range"); col02Text : qsTr("-"); col03Text : qsTr("5"); col04Text : dlgModel.mStatusDISetPointRange ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDISetPointRange === 1 ? true : false
                    }
                }

                NText{
                    id : iCommContactCtrl
                    anchors.bottom: iCommVoltageCtrl.top; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("input common, contact control = pin 6")
                }

                NText{
                    id : iCommVoltageCtrl
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("input common, voltage control = pin 4")
                }
            }

            Rectangle{
                id : doItem

                height: (GUISetting.margin + doTitle.height) + (GUISetting.margin + doStatusItem.height) + (GUISetting.line_margin + oComm.height) + GUISetting.line_margin;
                anchors.top: diItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : doTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital outputs")
                }

                ColumnLayout{
                    id : doStatusItem
                    height: 154 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: doTitle.bottom; anchors.topMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1

                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("digital output"); col02Text : qsTr("configuration"); col03Text : qsTr("connector-pin"); col04Text : qsTr("status")
                    }

                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("valve opened"); col02Text : dlgModel.mDOOpen === 0 ? qsTr("open") : qsTr("warning"); col03Text : qsTr("8"); col04Text : dlgModel.mStatusDOOpen ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDOOpen === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("valve closed"); col02Text : dlgModel.mDOClose === 0 ? qsTr("close") : qsTr("warning"); col03Text : qsTr("9"); col04Text : dlgModel.mStatusDOClose ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDOClose === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("alarm"); col02Text : qsTr("-"); col03Text : qsTr("22"); col04Text : dlgModel.mStatusDOAlarm ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDOAlarm === 1 ? true : false
                    }
                    InterfactStatusLogicItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("ready"); col02Text : qsTr("-"); col03Text : qsTr("21"); col04Text : dlgModel.mStatusDOReady ? qsTr("ON") : qsTr("OFF"); isON: dlgModel.mStatusDOReady === 1 ? true : false
                    }
                }

                NText{
                    id : oComm
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("output common = pin 20")
                }
            }

            Rectangle{
                id : aiItem

                height: (GUISetting.margin + aiTitle.height) + (GUISetting.margin + aiVolt.height) + (GUISetting.line_margin + analogGround.height) + GUISetting.line_margin;
                anchors.top: doItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : aiTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Analog input")
                }

                Rectangle{
                    id : aiVolt
                    height: 30 * GUISetting.scale; width: 100 * GUISetting.scale
                    color: "#E4E4E4"
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.top : aiTitle.bottom; anchors.topMargin: GUISetting.margin;

                    NText{
                        width: parent.width - 20; anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        horizontalAlignment: Text.AlignRight
                        isBold: true
                        text : dlgModel.mAnalogInputVoltage.toFixed(3) + " volt"
                    }
                }

                NText{
                    anchors.verticalCenter:aiVolt.verticalCenter; anchors.left: aiVolt.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("analog input voltage")
                }

                NText{
                    id : analogGround
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("analog ground = pin 13")
                }
            }
        }
    }
}
