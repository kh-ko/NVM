import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import GlobalUiValue 1.0
import GUISetting 1.0

import "../../usercomponent/."
import GeneralDlgModel 1.0
import ViewTagModel  1.0

Rectangle{
    id : row

    property bool isHeader  : false
    property int deviceAddr : 255
    property ViewTagModel actPosiTag          : ViewTagModel{}
    property ViewTagModel posiOffsetTag       : ViewTagModel{}
    property ViewTagModel actValveSpeedTag    : ViewTagModel{}
    property ViewTagModel freezeStatusTag     : ViewTagModel{}
    property ViewTagModel accModeTag          : ViewTagModel{}
    property ViewTagModel ctrlModeTag         : ViewTagModel{}
    property ViewTagModel svcReqTag           : ViewTagModel{}
    property ViewTagModel paramErrTag         : ViewTagModel{}
    property ViewTagModel pfoErrTag           : ViewTagModel{}
    property ViewTagModel compressAirFailTag  : ViewTagModel{}
    property ViewTagModel sensFactorWarnTag   : ViewTagModel{}
    property ViewTagModel offlineModeTag      : ViewTagModel{}
    property ViewTagModel romErrTag           : ViewTagModel{}
    property ViewTagModel noInterfaceTag      : ViewTagModel{}
    property ViewTagModel noAdcSigTag         : ViewTagModel{}
    property ViewTagModel noAdcSigOnLogicTag  : ViewTagModel{}
    property ViewTagModel compressAirValueTag : ViewTagModel{}

    color : isHeader ? "#24A7FF" : itemMouseArea.containsMouse ? "#3024A7FF" : (deviceAddr % 2) == 0 ? "#00000000" : "#10000000"

    width: parent.width; height: 30

    RowLayout{
        anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right;
        height: 30
        spacing: 10

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Addr" : deviceAddr
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 9
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : isHeader? "Act Posi" : actPosiTag.Value
        }

        CustomLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 9
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
    }

    MouseArea{
        id : itemMouseArea

        anchors.fill: parent
        hoverEnabled: true
        enabled: true
    }
}
