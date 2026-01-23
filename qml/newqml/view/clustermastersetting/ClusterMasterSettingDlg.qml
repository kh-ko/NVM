import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import GlobalUiValue 1.0
import GUISetting 1.0

import "../../usercomponent/."
import ViewTagContainerModel 1.0

CustomWindow{
    id : win
    width: 400; height: 500; minWidth : 400
    title: qsTr("Cluster Master Settings")

    Component.onCompleted: {
        numOfValve.viewTag             = findTag("Cluster.Master.Settings.Number of Valves"           );
        clusterAddr.viewTag            = findTag("Cluster.Master.Settings.Cluster Address"            );
        showAddr.viewTag               = findTag("Cluster.Master.Settings.Show Address on Display"    );
        connectionLossReaction.viewTag = findTag("Cluster.Master.Settings.Connection Loss Reaction"   );
        interlockOfSlave.viewTag       = findTag("Cluster.Master.Settings.Disable Interlocks of Slave");

        regRWComponent(numOfValve            );
        regRWComponent(clusterAddr           );
        regRWComponent(showAddr              );
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
