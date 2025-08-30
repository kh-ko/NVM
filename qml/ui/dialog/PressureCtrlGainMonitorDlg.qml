import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import PressureCtrlGainMonitorDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Pressure Control Gain Monitor")
    progress    : 100 //dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : ""//dlgModel.mErrMsg
    errMsg2     : ""//dlgModel.mErrMsg2
    access      : ValveEnumDef.ACCESS_LOCAL // dlgModel.mAccessMode
    isRS232Test : false //dlgModel.mIsRS232Test
    isEdit      : false

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    PressureCtrlGainMonitorDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real   guiScale : GUISetting.scale

            height: (GUISetting.line_margin + adapGainItem.height) + (GUISetting.line_margin + fixedGainItem.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : adapGainItem

                height: (GUISetting.margin + adapTitle.height) + (GUISetting.margin + adapGainFactorValue.height) + (GUISetting.margin + adapDelayFactorValue.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: 2; anchors.left: parent.left; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2

                enabled: dlgModel.mPresController == 0
                opacity: dlgModel.mPresController == 0 ? 1 : 0.3
                color: "#FFFFFF"

                NText{
                    id : adapTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Adaptive")
                }

                NText{
                    id : adapGainFactorLabel
                    width: 130 * GUISetting.scale
                    anchors.verticalCenter: adapGainFactorValue.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: false
                    text : qsTr("Gain Factor")
                }

                Rectangle{
                    id : adapGainFactorValue
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: adapTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mAdapGainFac
                        color: "#000000"
                    }
                }

                NText{
                    id : adapDelayFactorLabel
                    width: 130 * GUISetting.scale
                    anchors.verticalCenter: adapDelayFactorValue.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: false
                    text : qsTr("Delta Factor")
                }

                Rectangle{
                    id : adapDelayFactorValue
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: adapGainFactorValue.bottom; anchors.topMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mAdapDeltaFac
                        color: "#000000"
                    }
                }
            }

            Rectangle{
                id : fixedGainItem

                height: (GUISetting.margin + fixedTitle.height) + (GUISetting.margin + fixedPGainValue.height) + (GUISetting.margin + fixedIGainValue.height) + GUISetting.margin
                anchors.top: adapGainItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                enabled: dlgModel.mPresController != 0
                opacity: dlgModel.mPresController != 0 ? 1 : 0.3
                color: "#FFFFFF"

                NText{
                    id : fixedTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("PI/Soft Pump")
                }

                NText{
                    id : fixedPGainLabel
                    width: 130 * GUISetting.scale
                    anchors.verticalCenter: fixedPGainValue.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: false
                    text : qsTr("P-Gain")
                }

                Rectangle{
                    id : fixedPGainValue
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: fixedTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mFixedPGain
                        color: "#000000"
                    }
                }

                NText{
                    id : fixedIGainLabel
                    width: 130 * GUISetting.scale
                    anchors.verticalCenter: fixedIGainValue.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: false
                    text : qsTr("I-Gain")
                }

                Rectangle{
                    id : fixedIGainValue
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: fixedPGainValue.bottom; anchors.topMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mFixedIGain
                        color: "#000000"
                    }
                }
            }
        }
    }
}
