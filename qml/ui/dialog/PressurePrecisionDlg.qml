import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var    body : null
    property int    minPressureFixedN
    property int    userPressureFixedN
    property bool   isErr : false

    titleText   : qsTr("Pressure floating point percision")
    progress    : 100
    strStatus   : ""
    errMsg      : ""
    errMsg2     : ""
    access      : ValveEnumDef.ACCESS_REMOTE
    isRS232Test : false
    isEdit      : false
    isModal     : false

    signal signalChangedPrecision(int precisionValue)

    function apply()
    {
        var precisionValue = parseInt(body.userFixedN.textField.text )
        dialog.signalChangedPrecision(precisionValue);
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
            property alias userFixedN            : _userFixedN

            property real  guiScale                 : GUISetting.scale

            height: (GUISetting.line_margin + fixedNItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            Component.onCompleted: {
                _userFixedN.setValue(dialog.userPressureFixedN)
            }

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : fixedNItem

                height: (GUISetting.margin   + fixedNTitle.height)
                        + (GUISetting.margin + _userFixedN.height) + GUISetting.margin;
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : fixedNTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("floating point precision")
                }

                NInputNumber{
                    id : _userFixedN
                    width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: fixedNTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textField.validator: IntValidator{}
                    textField.color: "#000000"
                    stepValue : 0.0001; minValue: dialog.minPressureFixedN; maxValue: 8
                    fixedN : 0

                    onChangedText: {
                    }
                }

                NText{
                    anchors.verticalCenter: _userFixedN.verticalCenter; anchors.left: _userFixedN.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("minimum value is ") + dialog.minPressureFixedN
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: fixedNItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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
