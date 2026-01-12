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

    color : "#24A7FF"

    width: parent.width; height: 30

    RowLayout{
        anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right;
        height: 30
        spacing: 10

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "No"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Freeze"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Setpoint Mode"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Control Mode"

        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 13
            horizontalAlignment: Text.AlignHCenter
            text : "Access Mode"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Target Posi"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Actual Posi"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 10
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Isolated"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 5
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Error"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 7
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Warning"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 7
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Connection"
        }

        PmLabel{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 6
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text : "Air"
        }

        PmTextButton{
            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 7
            enabled:  false
            textColor : "#24A7FF"
            text: "Detail"
        }
    }
}
