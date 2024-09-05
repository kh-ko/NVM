import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import FontManager 1.0
import ValveEnumDef 1.0
import InterfaceStatusProfibusDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Interface status(Profibus)")
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

    InterfaceStatusProfibusDlgModel{
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

                height:   (GUISetting.margin + diTitle.height)
                        + (GUISetting.margin + diStatusItem.height)
                        + (GUISetting.line_margin + diInputGroundPin.height) + GUISetting.line_margin;
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
                    anchors.top: diTitle.bottom; anchors.topMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("function"); col02Text : qsTr("inverted"); col03Text : qsTr("enabled"); col04Text : qsTr("connector-pin");  col05Text : qsTr("status")
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : dlgModel.mDIFunction === 0 ? qsTr("interlock close")  : qsTr("interlock open");
                        col02Text : dlgModel.mDIMode     === 0 ? qsTr("not inverted") : qsTr("inverted"  );
                        col03Text : dlgModel.mDIInput    === 0 ? qsTr("enabled")      : qsTr("disabled"  );
                        col04Text : qsTr("3 / 1");
                        col05Text : dlgModel.mStatusDI === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDI === 1 ? true : false
                    }
                }

                NText{
                    id : diInputGroundPin
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("input ground = pin 1")
                }
            }

            Rectangle{
                id : doItem

                height: (GUISetting.margin + doTitle.height) + (GUISetting.margin + doStatusItem.height) + (GUISetting.line_margin + doCommPin.height) + GUISetting.line_margin;
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
                    height: 49 * GUISetting.scale; width: parent.width - (GUISetting.margin * 2)
                    anchors.top: doTitle.bottom; anchors.topMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: 1

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1
                        enabled: dialog.progress === 100; isHeader : true

                        col01Text : qsTr("function"); col02Text : qsTr("inverted"); col03Text : qsTr("enabled"); col04Text : qsTr("connector-pin"); col05Text : qsTr("status")
                    }

                    InterfaceStatusEtherCATItem{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredHeight: 1; enabled: dialog.progress === 100;
                        col01Text : dlgModel.mDOFunction === 0 ? qsTr("close")  : dlgModel.mDOFunction === 1 ? qsTr("open") : qsTr("On")
                        col02Text : dlgModel.mDOMode     === 0 ? qsTr("not inverted") : qsTr("inverted"  );
                        col03Text : dlgModel.mDOOutput    === 0 ? qsTr("enabled")      : qsTr("disabled"  );
                        col04Text : qsTr("2 / 4");
                        col05Text : dlgModel.mStatusDO === 1 ? qsTr("ON") : qsTr("OFF")
                        isON: dlgModel.mStatusDO === 1 ? true : false
                    }
                }

                NText{
                    id : doCommPin
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#0000FF"
                    text : qsTr("output common = pin 4")
                }
            }
        }
    }
}
