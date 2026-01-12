import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../control/."
import ValveEnumDef 1.0
import ValveCariblationDlgModel 1.0
import GUISetting 1.0
import PmViewModel 1.0
import PmValveItemModel 1.0
import ComponentHelper 1.0

Rectangle{
    id : row
    property int clusterNum : 0
    property PmValveItemModel freezeModel       : PmValveItemModel{}
    property PmValveItemModel setpointModeModel : PmValveItemModel{}
    property PmValveItemModel ctrlModeModel     : PmValveItemModel{}
    property PmValveItemModel accModeModel      : PmValveItemModel{}
    property PmValveItemModel targetPosiModel   : PmValveItemModel{}
    property PmValveItemModel actPosiModel      : PmValveItemModel{}
    property PmValveItemModel isolatedModel     : PmValveItemModel{}
    property PmValveItemModel warnModel         : PmValveItemModel{}
    property PmValveItemModel errModel          : PmValveItemModel{}
    property PmValveItemModel connStatusModel   : PmValveItemModel{}
    property PmValveItemModel airPresModel      : PmValveItemModel{}

    color : itemMouseArea.containsMouse ? "#3024A7FF" : (clusterNum % 2) == 0 ? "#00000000" : "#10000000"

    width: parent.width; height: 30

    MouseArea{
        id : itemMouseArea

        anchors.fill: parent
        hoverEnabled: true
        enabled: true
    }

    RowLayout{
        anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right;
        height: 30
        spacing: 10

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            text : row.clusterNum
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.freezeModel.modeOptions.getTextByValue(row.freezeModel.Value)
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.setpointModeModel.modeOptions.getTextByValue(row.setpointModeModel.Value)
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.ctrlModeModel.modeOptions.getTextByValue(row.ctrlModeModel.Value)

        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 13
            horizontalAlignment: Text.AlignLeft
            text : row.accModeModel.modeOptions.getTextByValue(row.accModeModel.Value)
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            text : row.targetPosiModel.Value
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            text : row.actPosiModel.Value
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.isolatedModel.modeOptions.getTextByValue(row.isolatedModel.Value)
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.errModel.Value.length == 0 ? "" : parseInt(row.errModel.Value) === 0 ? "" : "Error"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 7
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.warnModel.Value.length == 0 ? "" : parseInt(row.warnModel.Value) === 0 ? "" : "Error"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 7
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.connStatusModel.modeOptions.getTextByValue(row.connStatusModel.Value)
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 6
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignLeft
            text : row.airPresModel.modeOptions.getTextByValue(row.airPresModel.Value)
        }

        PmTextButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 7
            textColor : "#24A7FF"
            text: "Detail"
        }
    }
}
