import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import FontManager 1.0
import ValveEnumDef 1.0
import InterfaceStatusRS232DlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Interface status(RS232/RS485)")
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

    InterfaceStatusRS232DlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real   guiScale : GUISetting.scale

            height: (GUISetting.line_margin + diItem.height) + (GUISetting.line_margin + doItem.height) + GUISetting.line_margin
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
                    height: 49 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("digital input"); col02Text : qsTr("configuration"); col03Text : qsTr("enabled"); col04Text : qsTr("connector-pin");  col05Text : qsTr("status")
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("interlock open");
                        col02Text : dlgModel.mDIOpenValveIdx === 0 ? qsTr("not inverted") :
                                    dlgModel.mDIOpenValveIdx === 1 ? qsTr("inverted"    ) : qsTr("-"         );
                        col03Text : dlgModel.mDIOpenValveIdx !== 2 ? qsTr("enabled"     ) : qsTr("disabled"  );
                        col04Text : qsTr("17");
                        col05Text : dlgModel.mStatusDIOpen === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDIOpen === 1 ? true : false
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("interlock close");
                        col02Text : dlgModel.mDICloseValveIdx === 0 ? qsTr("not inverted") :
                                    dlgModel.mDICloseValveIdx === 1 ? qsTr("inverted"    ) : qsTr("-"         );
                        col03Text : dlgModel.mDICloseValveIdx !== 2 ? qsTr("enabled"     ) : qsTr("disabled"  );
                        col04Text : qsTr("15");
                        col05Text : dlgModel.mStatusDIClose === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDIClose === 1 ? true : false
                    }
                }

                NText{
                    id : iCommContactCtrl
                    anchors.bottom: iCommVoltageCtrl.top; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin:  GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("input common, contact control = pin 23")
                }

                NText{
                    id : iCommVoltageCtrl
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin:  GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("input common, voltage control = pin 25")
                }
            }

            Rectangle{
                id : doItem

                height: ( GUISetting.margin + doTitle.height) + ( GUISetting.margin + doStatusItem.height) + (GUISetting.line_margin + doCommPin.height) + GUISetting.line_margin;
                anchors.top: diItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : doTitle
                    anchors.top: parent.top; anchors.topMargin:  GUISetting.margin; anchors.left: parent.left; anchors.leftMargin:  GUISetting.margin
                    isBold: true
                    text : qsTr("Digital outputs")
                }

                ColumnLayout{
                    id : doStatusItem
                    height: 49 * GUISetting.scale; width: parent.width - ( GUISetting.margin * 2)
                    anchors.top: doTitle.bottom; anchors.topMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("digital output"); col02Text : qsTr("configuration"); col03Text : qsTr("enabled"); col04Text : qsTr("connector-pin"); col05Text : qsTr("status")
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("opened");
                        col02Text : qsTr("-"         );
                        col03Text : qsTr("enabled"   )
                        col04Text : qsTr("8");
                        col05Text : dlgModel.mStatusDOOpen === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDOOpen === 1 ? true : false
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : qsTr("closed");
                        col02Text : qsTr("-"         );
                        col03Text : qsTr("enabled"   )
                        col04Text : qsTr("9");
                        col05Text : dlgModel.mStatusDOClose === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDOClose === 1 ? true : false
                    }
                }

                NText{
                    id : doCommPin
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin:  GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("output common = pin 10")
                }
            }
        }
    }
}
