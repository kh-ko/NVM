import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import GlobalUiValue 1.0
import GUISetting 1.0

import "../../usercomponent/."
import GeneralDlgModel 1.0
import ViewTagModel 1.0

CustomWindow{
    id : win
    width: 1000; height: 500; minWidth : 400
    title: qsTr("Cluster Slave Monitor")

    btnApply.visible: false
    btnRefresh.visible: false

    property ViewTagModel numOfValveTag  : ViewTagModel{}
    property var rowArray : []
    property int numOfValue     : parseInt(numOfValveTag.Value)

    Component.onCompleted: {
        // 순서상 numOfValveTag를 가장 마지막에 등록해야지 꼬지지 않는다. 중간에 설정되면 onNumOfValueChanged 이 중간에 호출되는 불상사가 발생함.
        // 첫 호출시 refresh() -> onNumOfValueChanged
        // 다음 부터 호출시 numOfValveTag이 설정되는 타이밍에 바로 onNumOfValueChanged이 호출됨
        var tempNumOfValveTag;

        tempNumOfValveTag = viewModel.getTag("Cluster.Master.Settings.Number of Valves");

        viewModel.clearMonitorTag();
        viewModel.addMonotoringTag(tempNumOfValveTag);

        for(var i = 1; i < 31; i ++)
        {
            var row = deviceRow.createObject(rowContainer)

            row.deviceAddr          = i;
            row.actPosiTag          = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Actual Position"            );
            row.posiOffsetTag       = viewModel.getTag("Cluster.Slave.Settings.Device " + i + " Position Offset"           );
            row.actValveSpeedTag    = viewModel.getTag("Cluster.Slave.Settings.Device " + i + " Speed Position Control"    );
            row.freezeStatusTag     = viewModel.getTag("Cluster.Slave.Settings.Device " + i + " Freeze"                    );
            row.accModeTag          = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Access Mode"               );
            row.ctrlModeTag         = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Control Mode"              );
            row.compressAirValueTag = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Compressed Air Value(mbar)");

            row.svcReqTag           = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Service Reqeust"           );
            row.paramErrTag         = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Parameter Error"           );
            row.pfoErrTag           = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " PFO Not Fully Charged"     );
            row.compressAirFailTag  = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Compressed Air Failure"    );
            row.sensFactorWarnTag   = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Sensor Factor Warning"     );
            row.offlineModeTag      = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " Offline Mode"              );
            row.romErrTag           = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " ROM Error"                 );
            row.noInterfaceTag      = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " No Interface Found"        );
            row.noAdcSigTag         = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " No ADC Signal"             );
            row.noAdcSigOnLogicTag  = viewModel.getTag("Cluster.Slave.Status.Device "   + i + " No ADC Siganl On Logic"    );

            rowArray.push(row);
        }

        numOfValveTag = tempNumOfValveTag;

        refresh()
    }

    onNumOfValueChanged: {
        viewModel.clearMonitorTag();
        viewModel.addMonotoringTag(numOfValveTag);

        for(var i = 0; i < numOfValue; i ++)
        {
            viewModel.addMonotoringTag(rowArray[i].actPosiTag);
        }
    }

    Item{
        id : itemContainer

        width: win.scrollContainer.width; height: win.scrollContainer.height

        ClusterDeviceMonitorRow{
            id : tableHeader
            anchors.top: parent.top; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin: 10

            isHeader : true
        }

        ScrollView{
            id: container
            anchors.left: tableHeader.left; anchors.top: tableHeader.bottom; anchors.right: tableHeader.right; anchors.bottom: parent.bottom

            clip: true

            contentWidth: rowWrapper.width
            contentHeight: rowWrapper.height

            ScrollBar.horizontal.policy: ScrollBar.AsNeeded
            ScrollBar.vertical.policy: ScrollBar.AsNeeded

            Item {
                id: rowWrapper

                // 자식들이 배치된 영역만큼 자신의 크기를 늘림
                width: childrenRect.width
                height: childrenRect.height

                Column{
                    id : rowContainer

                    anchors.top: parent.top; topPadding: 10
                    width: win.scrollContainer.width
                    spacing: 0
                }
            }
        }
    }



    Component{
        id : deviceRow
        ClusterDeviceMonitorRow{
            visible: win.numOfValue >= deviceAddr
        }
    }
}
