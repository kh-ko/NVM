import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import FatalErrorDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    signal clickRecovery();

    titleText   : qsTr("Valve recovery")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : false


    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    FatalErrorDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real guiScale : GUISetting.scale

            height: (2 + valveFatalErrInfoItem.height)+ (2 + valveCorrectionInfoItem.height) + (2 + btnBox.height) + 2
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : valveFatalErrInfoItem

                height: (GUISetting.margin + fatalErrInfoTitle.height) + (GUISetting.margin + errorCodeBox.height)
                        + (GUISetting.line_margin + errDescBox.height) + (GUISetting.line_margin + modeOfOccurBox.height) + (GUISetting.line_margin + failCauseBox.height) + (GUISetting.line_margin + recoveryBox.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: 2; anchors.left: parent.left; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2

                color: "#FFFFFF"

                NText{
                    id : fatalErrInfoTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Fatal error infromation")
                }


                Rectangle{
                    id : errorCodeBox
                    height: 24 * GUISetting.scale
                    anchors.top:fatalErrInfoTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : fatalErrCodeLabel
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("fatal error code")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : fatalErrCodeValue
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: fatalErrCodeLabel.right; anchors.leftMargin: GUISetting.margin;anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : "E "+ dlgModel.mFatalErrStatus
                        visible: dialog.progress === 100
                    }
                }

                Rectangle{
                    id : errDescBox
                    height: 24 * GUISetting.scale
                    anchors.top:errorCodeBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : errDescLabel
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("basic description")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : errDescContent
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: errDescLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : dlgModel.mFatalErrStatus == 20 ? qsTr("check valve orifice, check valve-parameters") :// qsTr("limit stop of valve unit not detected") :
                               dlgModel.mFatalErrStatus == 21 ? qsTr("rotation angle of valve plate limited during power up") :
                               dlgModel.mFatalErrStatus == 22 ? qsTr("rotation angle of valve plate limited during operation") :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("motor driver failure")   :
                               dlgModel.mFatalErrStatus == 23 ? qsTr("failure axis 1 (rotary motion)")   :
                               dlgModel.mFatalErrStatus == 24 ? qsTr("failure axis 2 (stroke motion)")   :
                               dlgModel.mFatalErrStatus == 25 ? qsTr("failure axis 1 and 2")   :
                               dlgModel.mFatalErrStatus == 26 ? qsTr("multiple axis misalignment")   :
                               dlgModel.mFatalErrStatus == 27 ? qsTr("commutation error")   :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("recovery error")   : qsTr("unknown")
                        visible: dialog.progress === 100
                    }
                }

                Rectangle{
                    id : modeOfOccurBox
                    height: 24 * GUISetting.scale
                    anchors.top:errDescBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : modeOfOccurLabel
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("mode of occurence")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : modeOfOccurContent
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: modeOfOccurLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : dlgModel.mFatalErrStatus == 20 ? qsTr("synchronization")     :
                               dlgModel.mFatalErrStatus == 21 ? qsTr("synchronization")     :
                               dlgModel.mFatalErrStatus == 22 ? qsTr("normal operation")    :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("synchronization")     :
                               dlgModel.mFatalErrStatus == 23 ? qsTr("normal operation")    :
                               dlgModel.mFatalErrStatus == 24 ? qsTr("normal operation")    :
                               dlgModel.mFatalErrStatus == 25 ? qsTr("normal operation")    :
                               dlgModel.mFatalErrStatus == 26 ? qsTr("normal operation")    :
                               dlgModel.mFatalErrStatus == 27 ? qsTr("synchronization")     :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("fatal error recovery"): qsTr("unknown")
                        visible: dialog.progress === 100
                    }
                }

                Rectangle{
                    id : failCauseBox
                    height: 24 * GUISetting.scale
                    anchors.top:modeOfOccurBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : failCauseLabel
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("potential failure cause")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : failCauseContent
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: failCauseLabel.right; anchors.leftMargin: GUISetting.margin;anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : dlgModel.mFatalErrStatus == 20 ? qsTr("loose clamp coupling")     :
                               dlgModel.mFatalErrStatus == 21 ? qsTr("valve mechanics, improper valve-parameters")     :
                               dlgModel.mFatalErrStatus == 22 ? qsTr("valve mechanics, heavy contaminated")    :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("motor driver malfunction")     :
                               dlgModel.mFatalErrStatus == 23 ? qsTr("valve mechanics, power loss")    :
                               dlgModel.mFatalErrStatus == 24 ? qsTr("valve mechanics, power loss")    :
                               dlgModel.mFatalErrStatus == 25 ? qsTr("valve mechanics, power loss")    :
                               dlgModel.mFatalErrStatus == 26 ? qsTr("valve mechanics, power loss")    :
                               dlgModel.mFatalErrStatus == 27 ? qsTr("defect encoder, valve mechanics blocked")     :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("unrecoverable failure condition"): qsTr("unknown")
                        visible: dialog.progress === 100
                    }
                }

                Rectangle{
                    id : recoveryBox
                    height: 24 * GUISetting.scale
                    anchors.top:failCauseBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : recoveryLabel
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("possible error recovery")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : recoveryContent
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: recoveryLabel.right; anchors.leftMargin: GUISetting.margin;anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : dlgModel.mFatalErrStatus == 20 ? qsTr("tighten clamp screw")                          :
                               dlgModel.mFatalErrStatus == 21 ? qsTr("check valve orifice, check valve-parameters")  :
                               dlgModel.mFatalErrStatus == 22 ? qsTr("check valve mechanics and orifice")            :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("replace motordriver")                          :
                               dlgModel.mFatalErrStatus == 23 ? qsTr("check mechanics and power supply")             :
                               dlgModel.mFatalErrStatus == 24 ? qsTr("check mechanics and power supply")             :
                               dlgModel.mFatalErrStatus == 25 ? qsTr("check mechanics and power supply")             :
                               dlgModel.mFatalErrStatus == 26 ? qsTr("check mechanics and power supply")             :
                               dlgModel.mFatalErrStatus == 27 ? qsTr("check encoder and mechanics")                  :
                               dlgModel.mFatalErrStatus == 40 ? qsTr("check mechanics and try again")                : qsTr("unkonw")
                    }
                }
            }

            Rectangle{
                id : valveCorrectionInfoItem

                height: (GUISetting.margin + correctionInfoTitle.height) + (GUISetting.margin + error01Box.height) + ( GUISetting.line_margin + error02Box.height) + ( GUISetting.line_margin + error03Box.height)+ GUISetting.margin
                anchors.top: valveFatalErrInfoItem.bottom; anchors.topMargin: 2; anchors.left: parent.left; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2

                color: "#FFFFFF"

                NText{
                    id : correctionInfoTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Correction information")
                }


                Rectangle{
                    id : error01Box
                    height: 24 * GUISetting.scale
                    anchors.top:correctionInfoTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : error01Label
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("error 01")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : error01Position
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: error01Label.right; anchors.leftMargin: GUISetting.margin;anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : dlgModel.mSupport01Pos == false ? qsTr("not support") : qsTr("position : ") + dlgModel.mErr01Pos + " / " + dlgModel.mErr01TotalPos
                        visible: dialog.progress === 100
                    }
                }

                Rectangle{
                    id : error02Box
                    height: 24 * GUISetting.scale
                    anchors.top:error01Box.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : error02Label
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("error 02")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : error02Position
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: error02Label.right; anchors.leftMargin: GUISetting.margin;anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : dlgModel.mSupport02Pos == false ? qsTr("not support") : qsTr("position : ") + dlgModel.mErr02Pos + " / " + dlgModel.mErr02TotalPos
                        visible: dialog.progress === 100
                    }
                }

                Rectangle{
                    id : error03Box
                    height: 24 * GUISetting.scale
                    anchors.top:error02Box.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        id : error03Label
                        width: 150 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                        text : qsTr("error 03")
                        visible: dialog.progress === 100
                    }

                    NText{
                        id : error03Position
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: error03Label.right; anchors.leftMargin: GUISetting.margin;anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text : dlgModel.mSupport03Pos == false ? qsTr("not support") : qsTr("position : ") + dlgModel.mErr03Pos + " / " + dlgModel.mErr03TotalPos
                        visible: dialog.progress === 100
                    }
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: valveCorrectionInfoItem.bottom; anchors.topMargin: 2; anchors.left: parent.left; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Recovery")

                    onClick: {
                        dialog.clickRecovery()
                        dialog.close()
                    }
                }
            }
        }
    }
}
