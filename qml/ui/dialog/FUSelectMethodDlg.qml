import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Firmware update")

    signal selectedMethod(string method)

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real   guiScale                       : GUISetting.scale

            height: (GUISetting.line_margin + selMethodItem.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : selMethodItem

                height: (GUISetting.margin + selMethodTitle.height) + (GUISetting.margin + btnNet.height) + (GUISetting.margin + btnLocal.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : selMethodTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Select update method")
                }

                NButton{
                    id : btnNet
                    width: 260 * GUISetting.scale; height: 70 * GUISetting.scale
                    anchors.top: selMethodTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    text.text: qsTr("From network")

                    onClick: {
                        selectMethod("network")
                    }
                }

                NButton{
                    id : btnLocal
                    width: 260 * GUISetting.scale; height: 70 * GUISetting.scale
                    anchors.top: btnNet.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter
                    text.text: qsTr("From files")

                    onClick: {
                        selectMethod("local")
                    }
                }
            }
        }
    }

    function selectMethod(method)
    {
        dialog.selectedMethod(method)

        close();
    }
}
