import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import ControlZeroDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null
    property string versionValue : "0.0.0"
    property int company : 0

    titleText    : qsTr("About")
    progress     : 100
    strStatus    : "ready"
    errMsg       : ""
    access       : ValveEnumDef.ACCESS_LOCAL
    isEdit       : false


    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real guiScale : GUISetting.scale

            height: (GUISetting.line_margin + informationItem.height) + (GUISetting.line_margin + btnBox.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : informationItem

                height: ((50 * GUISetting.scale)  + company.height) + (GUISetting.margin + version.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                Item{
                    id : company
                    height: 200 * GUISetting.scale
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: 50 * GUISetting.scale; anchors.right: parent.right; anchors.rightMargin: 50 * GUISetting.scale
                    Image{
                        anchors.fill: parent
                        source: (dialog.company === ValveEnumDef.COMPANY_NOVA) || (dialog.company === ValveEnumDef.COMPANY_APSYS) ? "/image/img-novasen.png" : "/image/img_soao.png"
                        fillMode: Image.PreserveAspectFit
                    }
                }

                NText{
                    id : versionLabel
                    anchors.bottom: version.bottom; anchors.right: version.left; anchors.rightMargin: GUISetting.margin;
                    horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                    text : qsTr("version")
                }

                NText{
                    id : version
                    anchors.top: company.bottom; anchors.topMargin: GUISetting.margin; anchors.right: company.right;
                    horizontalAlignment: Text.AlignLeft; verticalAlignment: Text.AlignVCenter
                    fontSize: 15 * GUISetting.scale
                    isBold: true
                    text : dialog.versionValue
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: informationItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Close")

                    onClick: {
                        dialog.close()
                    }
                }
            }
        }
    }
}
