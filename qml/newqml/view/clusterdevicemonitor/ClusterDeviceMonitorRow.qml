import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import GlobalUiValue 1.0
import GUISetting 1.0

import "../../usercomponent/."
import ViewTagContainerModel 1.0
import TagModel  1.0

Rectangle{
    id : row

    property bool isHeader  : false
    property int deviceAddr : 255
    property alias posiOffsetInput       : posiOffset
    property alias targetPosiInput       : targetPosi
    property alias ctrlModeSetpointCombo : ctrlModeSetpoint
    property alias valveSpeedInput       : valveSpeed
    property alias freeszStatusCombo     : freeszStatus
    property alias restartCombo          : restart

    property TagModel actPosiTag          : TagModel{}
    property TagModel posiOffsetTag       : TagModel{}
    property TagModel restartTag          : TagModel{}
    property TagModel targetPosiTag       : TagModel{}
    property TagModel ctrlModeSetpointTag : TagModel{}
    property TagModel actValveSpeedTag    : TagModel{}
    property TagModel freezeStatusTag     : TagModel{}
    property TagModel accModeTag          : TagModel{}
    property TagModel ctrlModeTag         : TagModel{}
    property TagModel svcReqTag           : TagModel{}
    property TagModel paramErrTag         : TagModel{}
    property TagModel pfoErrTag           : TagModel{}
    property TagModel compressAirFailTag  : TagModel{}
    property TagModel sensFactorWarnTag   : TagModel{}
    property TagModel offlineModeTag      : TagModel{}
    property TagModel romErrTag           : TagModel{}
    property TagModel noInterfaceTag      : TagModel{}
    property TagModel noAdcSigTag         : TagModel{}
    property TagModel noAdcSigOnLogicTag  : TagModel{}
    property TagModel compressAirValueTag : TagModel{}

    property bool isWarn : svcReqTag.Value === "1" || paramErrTag.Value === "1" || pfoErrTag.Value === "1" || compressAirFailTag.Value === "1" || sensFactorWarnTag.Value === "1" || offlineModeTag.Value === "1" || romErrTag.Value === "1" || noInterfaceTag.Value === "1" || noAdcSigTag.Value === "1" || noAdcSigOnLogicTag.Value === "1"
    property bool isExpand : false

    signal clickExpend()
    signal clickApply()

    color : isHeader ? "#24A7FF" : itemMouseArea.containsMouse ? "#3024A7FF" : (deviceAddr % 2) == 0 ? "#00000000" : "#10000000"

    width: parent.width; height: isExpand ? 30 + warnBox.height : 30

    MouseArea{
        id : itemMouseArea

        anchors.fill: parent
        hoverEnabled: true
        enabled: row.enabled && row.isExpand === false
    }

    RowLayout{
        id : generalItemBox
        anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right;
        height: 30
        spacing: 10

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            color: row.isWarn ? "#FF0000" : "#000000"
            text : isHeader? "Addr" : deviceAddr
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 6
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Act Posi" : actPosiTag.Value
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 6
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter

            text : isHeader? "Posi Offset" : posiOffsetTag.Value
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 6
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Act Valve Speed" : actValveSpeedTag.Value
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Fressze" : freezeStatusTag.modeOptions.getTextByValue(freezeStatusTag.Value)

        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 12
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Access Mode" : accModeTag.modeOptions.getTextByValue(accModeTag.Value)
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Control Mode" : ctrlModeTag.modeOptions.getTextByValue(ctrlModeTag.Value)
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 12
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Compressed Air(mbar)" : compressAirValueTag.Value
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4

            visible: isHeader
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : ""
        }

        CustomTextButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4

            visible: isHeader === false
            textColor : "#000000"
            text: row.isExpand ? "Collapse" : "Expand"

            onClick: {
                row.clickExpend();
            }
        }
    }

    Column{
        id : warnBox

        visible: row.isExpand

        anchors.top: generalItemBox.bottom;
        spacing: 10

        width: parent.width
        CustomLabel       { anchors.left: parent.left; anchors.leftMargin : 10; height: 24; text: "Warnings" }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.svcReqTag         }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.paramErrTag       }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.pfoErrTag         }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.compressAirFailTag}
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.sensFactorWarnTag }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.offlineModeTag    }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.romErrTag         }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.noInterfaceTag    }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.noAdcSigTag       }
        CustomCheckBox    {                        anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150; isReadOnly: true; viewTag : row.noAdcSigOnLogicTag}

        CustomLabel       { anchors.left: parent.left; anchors.leftMargin : 10; height: 24; text: "Settings" }
        CustomFloatInput  { id : posiOffset      ; anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150;                    viewTag: row.posiOffsetTag      ; }
        CustomFloatInput  { id : targetPosi      ; anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150;                    viewTag: row.targetPosiTag      ; }
        CustomComboBox    { id : ctrlModeSetpoint; anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150;                    viewTag: row.ctrlModeSetpointTag; }
        CustomIntegerInput{ id : valveSpeed      ; anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150;                    viewTag: row.actValveSpeedTag   ; }
        CustomComboBox    { id : freeszStatus    ; anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150;                    viewTag: row.freezeStatusTag    ; }
        CustomComboBox    { id : restart         ; anchors.left: parent.left; anchors.leftMargin : 10; width: parent.width - 30; label.width: 150;                    viewTag: row.restartTag         ; }

        Item{ width: 10; height : 10}

        Item{
            anchors.right: parent.right; anchors.rightMargin: 20; height: 24; width: parent.width - 30;

            CustomButton{
                id : applyBtn
                anchors.right: parent.right; height: parent.height

                enabled: posiOffset.isDirty || targetPosi.isDirty || ctrlModeSetpoint.isDirty || valveSpeed.isDirty || freeszStatus.isDirty || restart.isDirty
                text : "Apply"

                onClick: {
                    row.clickApply();
                }
            }

            CustomButton{
                id : cancelBtn
                anchors.right: applyBtn.left; anchors.rightMargin: 10; height: parent.height
                text : "Cancel"

                onClick: {
                    row.clickExpend();
                }
            }
        }
        Item{ width: 10; height : 10}
    }
}
