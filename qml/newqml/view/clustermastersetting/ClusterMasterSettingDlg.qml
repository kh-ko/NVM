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

CustomWindow{
    id : win
    width: 400; height: 500; minWidth : 400
    title: qsTr("Cluster Master Settings")

    property TagModel firmwareVerTag   : TagModel{}

    Component.onCompleted: {
        firmwareVerTag                 = findTag("System.Identification.Firmware.Valve Firmware Version"); // RO

        numOfValve.viewTag             = findTag("Cluster.Master.Settings.Number of Valves"             );
        clusterAddr.viewTag            = findTag("Cluster.Master.Settings.Cluster Address"              );
        baudrate.viewTag               = findTag("Cluster.Master.Settings.Baud Rate"                    );
        showAddr.viewTag               = findTag("Cluster.Master.Settings.Show Address on Display"      );
        connectionLossReaction.viewTag = findTag("Cluster.Master.Settings.Connection Loss Reaction"     );
        interlockOfSlave.viewTag       = findTag("Cluster.Master.Settings.Disable Interlocks of Slave"  );

        regInitTag    (firmwareVerTag        );
        regRWComponent(numOfValve            );
        regRWComponent(clusterAddr           );
        regRWComponent(showAddr              );
        regRWComponent(baudrate              );
        regRWComponent(connectionLossReaction);
        regRWComponent(interlockOfSlave      );

        checkApplyBtn()
        refresh()
    }

    Column{
        id : itemContainer

        anchors.top: parent.top; topPadding: 10
        width: win.scrollContainer.width - 10
        spacing: 10

        CustomIntegerInput{
            id : numOfValve
            width:parent.width;

            label.width: 150
            onIsDirtyChanged: {win.checkApplyBtn()}
        }

        CustomIntegerInput{
            id : clusterAddr
            width:parent.width;

            label.width: 150
            onIsDirtyChanged: {win.checkApplyBtn()}
        }

        CustomComboBox{
            id : showAddr
            width:parent.width;

            label.width: 150
            onIsDirtyChanged: {win.checkApplyBtn()}
        }

        CustomComboBox{
            id : baudrate
            width:parent.width;

            label.width: 150
            onIsDirtyChanged: {win.checkApplyBtn()}
        }

        CustomComboBox{
            id : connectionLossReaction
            width:parent.width;

            label.width: 150
            onIsDirtyChanged: {win.checkApplyBtn()}
        }

        CustomComboBox{
            id : interlockOfSlave
            width:parent.width;

            label.width: 150
            onIsDirtyChanged: {win.checkApplyBtn()}
        }
    }
}
