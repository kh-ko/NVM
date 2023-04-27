import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var    body : null
    property real   autoScaleMargin
    property bool   isErr : false

    titleText   : qsTr("Auto scale minimum margin")
    progress    : 100
    strStatus   : ""
    errMsg      : ""
    errMsg2     : ""
    access      : ValveEnumDef.ACCESS_REMOTE
    isRS232Test : false
    isEdit      : false
    isModal     : false

    signal signalChangedAutoScaleMargin(real marginValue)

    function apply()
    {
        var marginValue = parseFloat(body.marginInput.textField.text )
        dialog.signalChangedAutoScaleMargin(marginValue);
        dialog.close();
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias marginInput : _marginInput

            property real  guiScale    : GUISetting.scale

            height: (GUISetting.line_margin + marginItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            Component.onCompleted: {
                _marginInput.setValue(dialog.autoScaleMargin)
            }

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : marginItem

                height: (GUISetting.margin   + marginTitle.height)
                        + (GUISetting.margin + _marginInput.height) + GUISetting.margin;
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : marginTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("minimum margin")
                }

                NInputNumber{
                    id : _marginInput
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: marginTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.validator: DoubleValidator{}
                    textField.color: "#000000"
                    stepValue : 0.0001; minValue: 0.1; maxValue: 10
                    fixedN : 2

                    onChangedText: {
                    }
                }

                NText{
                    anchors.verticalCenter: _marginInput.verticalCenter; anchors.left: _marginInput.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("auto scale minimum margin ( 0.1 ~ 10 )")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: marginItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Apply")

                    onClick: {
                        apply();
                    }
                }
            }
        }
    }
}
