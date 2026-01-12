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

PmBaseWindow {
    id : win
    width: 1000; height: 600; minWidth : 1000
    title: qsTr("Cluster Monitor")

    property PmValveItemModel clusterCountModel : PmValveItemModel{}
    property bool isInit        : false;
    property bool isSetInitData : false;
    property int  slaveCount    : parseInt(clusterCountModel.Value)
    property int itemModelIdx : 0
    property var itemModelArray : []

    Component.onCompleted: {
        win.btnApply.visible = false;
        win.btnRefresh.visible = false;

        clusterCountModel = viewModel.findItemModel("Cluster.Settings.Number of Valves");
    }

    function onTimerTick()
    {
        //console.log("onTimerTick");

        if(isInit == false)
        {
            isInit = clusterCountModel.remoteSync();
            return;
        }

        if(isSetInitData == false)
            return;

        itemModelArray[itemModelIdx++].remoteSync();

        if(itemModelIdx == itemModelArray.length)
            itemModelIdx = 0;
    }

    Connections {
        target: win.clusterCountModel

        function onSignalEventChangedValue(modelValue) {
            if(win.isSetInitData)
                return;

            var slaveCount = parseInt(modelValue)

            for(var i = 1; i < itemContainer.children.length && i < slaveCount + 1; i ++)
            {
                var uiRow = itemContainer.children[i];
                uiRow.freezeModel       = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Freeze"               ); itemModelArray.push(uiRow.freezeModel      )
                uiRow.setpointModeModel = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Control Mode Setpoint"); itemModelArray.push(uiRow.setpointModeModel)
                uiRow.ctrlModeModel     = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Control Mode"         ); itemModelArray.push(uiRow.ctrlModeModel    )
                uiRow.accModeModel      = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Access Mode"          ); itemModelArray.push(uiRow.accModeModel     )
                uiRow.targetPosiModel   = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Target Position"      ); itemModelArray.push(uiRow.targetPosiModel  )
                uiRow.actPosiModel      = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Actual Position"      ); itemModelArray.push(uiRow.actPosiModel     )
                uiRow.isolatedModel     = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Isolated"             ); itemModelArray.push(uiRow.isolatedModel    )
                uiRow.warnModel         = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Warning Bitmap"       ); itemModelArray.push(uiRow.warnModel        )
                uiRow.errModel          = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Error Bitmap"         ); itemModelArray.push(uiRow.errModel         )
                uiRow.connStatusModel   = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Connection Status"    ); itemModelArray.push(uiRow.connStatusModel  )
                uiRow.airPresModel      = viewModel.findItemModel("Cluster.Slave "+ (i - 1) + ".Air Pressure"         ); itemModelArray.push(uiRow.airPresModel     )
            }

            win.isSetInitData = true;
        }
    }

    Timer {
        id: refreshTimer
        interval: 50       // 1000ms = 1초 간격
        repeat: true         // true: 계속 반복, false: 한 번만 실행하고 멈춤
        running: window.visible

        // (선택 사항) true로 하면 타이머 시작과 동시에 즉시 한 번 실행함
        triggeredOnStart: true

        // 3. 시간이 될 때마다 실행되는 부분
        onTriggered: {
            win.onTimerTick();
        }
    }

    PmViewModel{
        id : viewModel
    }

    onClosing: {
        console.log("창을 닫습니다. 앱을 종료합니다.");
    }

    Column{
        id : itemContainer

        anchors.top: parent.top;
        width: (win.scrollContainer.width - 2) < minWidth ? minWidth : (win.scrollContainer.width - 2)

        ClusterMonitorHeaderRow{ }

        ClusterMonitorRow{ clusterNum:  0 ; visible: win.slaveCount >  0 }
        ClusterMonitorRow{ clusterNum:  1 ; visible: win.slaveCount >  1 }
        ClusterMonitorRow{ clusterNum:  2 ; visible: win.slaveCount >  2 }
        ClusterMonitorRow{ clusterNum:  3 ; visible: win.slaveCount >  3 }
        ClusterMonitorRow{ clusterNum:  4 ; visible: win.slaveCount >  4 }
        ClusterMonitorRow{ clusterNum:  5 ; visible: win.slaveCount >  5 }
        ClusterMonitorRow{ clusterNum:  6 ; visible: win.slaveCount >  6 }
        ClusterMonitorRow{ clusterNum:  7 ; visible: win.slaveCount >  7 }
        ClusterMonitorRow{ clusterNum:  8 ; visible: win.slaveCount >  8 }
        ClusterMonitorRow{ clusterNum:  9 ; visible: win.slaveCount >  9 }
        ClusterMonitorRow{ clusterNum: 10 ; visible: win.slaveCount > 10 }
        ClusterMonitorRow{ clusterNum: 11 ; visible: win.slaveCount > 11 }
        ClusterMonitorRow{ clusterNum: 12 ; visible: win.slaveCount > 12 }
        ClusterMonitorRow{ clusterNum: 13 ; visible: win.slaveCount > 13 }
        ClusterMonitorRow{ clusterNum: 14 ; visible: win.slaveCount > 14 }
        ClusterMonitorRow{ clusterNum: 15 ; visible: win.slaveCount > 15 }
        ClusterMonitorRow{ clusterNum: 16 ; visible: win.slaveCount > 16 }
        ClusterMonitorRow{ clusterNum: 17 ; visible: win.slaveCount > 17 }
        ClusterMonitorRow{ clusterNum: 18 ; visible: win.slaveCount > 18 }
        ClusterMonitorRow{ clusterNum: 19 ; visible: win.slaveCount > 19 }

    }
}
