import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import GlobalUiValue 1.0
import GUISetting 1.0

import "../../usercomponent/."
import ViewTagContainerModel 1.0
import TagModel 1.0

CustomWindow{
    id : win
    width: 900; height: 500; minWidth : 900
    title: qsTr("Cluster Slave Monitor")

    btnApply.visible: false
    btnRefresh.visible: false

    property bool isInit : false;
    property TagModel numOfValveTag        : TagModel{}
    property TagModel rs232ScalingUnitTag  : TagModel{}
    property TagModel rs232ClosestPosiTag  : TagModel{}
    property TagModel rs232OpenPosiTag     : TagModel{}
    property var rowArray : []
    property int numOfValue     : parseInt(numOfValveTag.Value)

    property int expandDevAddr: 0

    Component.onCompleted: {

        numOfValveTag       = findTag("Cluster.Master.Settings.Number of Valves");

        rs232ScalingUnitTag = findTag("Interface RS232/RS485.Scaling.Position.Position Unit");
        rs232ClosestPosiTag = findTag("Interface RS232/RS485.Scaling.Position.Value Closest Position");
        rs232OpenPosiTag    = findTag("Interface RS232/RS485.Scaling.Position.Value Open Position");

        clearMonitoringTagAndComponent();
        regMonitoringTag(numOfValveTag);

        for(var i = 1; i < 31; i ++)
        {
            var row = deviceRow.createObject(rowContainer)

            row.deviceAddr          = i;
            row.actPosiTag          = findTag("Cluster.Slave.Settings.Device " + i + " Actual Position"           );
            row.posiOffsetTag       = findTag("Cluster.Slave.Settings.Device " + i + " Position Offset"           );
            row.actValveSpeedTag    = findTag("Cluster.Slave.Settings.Device " + i + " Speed Position Control"    );
            row.freezeStatusTag     = findTag("Cluster.Slave.Settings.Device " + i + " Freeze"                    );
            row.restartTag          = findTag("Cluster.Slave.Settings.Device " + i + " Restart Controller"        );
            row.targetPosiTag       = findTag("Cluster.Slave.Settings.Device " + i + " Target Position"           );
            row.ctrlModeSetpointTag = findTag("Cluster.Slave.Settings.Device " + i + " Control Mode SetPoint"     );
            row.accModeTag          = findTag("Cluster.Slave.Settings.Device "   + i + " Access Mode"               );
            row.ctrlModeTag         = findTag("Cluster.Slave.Settings.Device "   + i + " Control Mode"              );
            row.compressAirValueTag = findTag("Cluster.Slave.Settings.Device "   + i + " Compressed Air Value(mbar)");

            row.svcReqTag           = findTag("Cluster.Slave.Settings.Device "   + i + " Service Reqeust"           );
            row.paramErrTag         = findTag("Cluster.Slave.Settings.Device "   + i + " Parameter Error"           );
            row.pfoErrTag           = findTag("Cluster.Slave.Settings.Device "   + i + " PFO Not Fully Charged"     );
            row.compressAirFailTag  = findTag("Cluster.Slave.Settings.Device "   + i + " Compressed Air Failure"    );
            row.sensFactorWarnTag   = findTag("Cluster.Slave.Settings.Device "   + i + " Sensor Factor Warning"     );
            row.offlineModeTag      = findTag("Cluster.Slave.Settings.Device "   + i + " Offline Mode"              );
            row.romErrTag           = findTag("Cluster.Slave.Settings.Device "   + i + " ROM Error"                 );
            row.noInterfaceTag      = findTag("Cluster.Slave.Settings.Device "   + i + " No Interface Found"        );
            row.noAdcSigTag         = findTag("Cluster.Slave.Settings.Device "   + i + " No ADC Signal"             );
            row.noAdcSigOnLogicTag  = findTag("Cluster.Slave.Settings.Device "   + i + " No ADC Siganl On Logic"    );

            rowArray.push(row);
        }

        regInitTag(rs232ScalingUnitTag)
        regInitTag(rs232ClosestPosiTag)
        regInitTag(rs232OpenPosiTag   )

        refresh()
        win.isInit = true;
    }

    onNumOfValueChanged: {

        if(win.isInit == false)
            return;

        clearMonitoringTagAndComponent();
        regMonitoringTag(numOfValveTag);

        for(var i = 0; i < numOfValue; i ++)
        {
            regMonitoringTag(rowArray[i].actPosiTag);
        }
    }

    Item{
        id : itemContainer

        width: minWidth > (win.scrollContainer.width - 10) ? minWidth : (win.scrollContainer.width - 10); height: win.scrollContainer.height

        ClusterDeviceMonitorRow{
            id : tableHeader
            anchors.top: parent.top; anchors.topMargin: 10; anchors.left: parent.left; anchors.leftMargin: 10;
            width: parent.width - 20

            isHeader : true
        }

        ScrollView{
            id: container
            anchors.left: tableHeader.left; anchors.top: tableHeader.bottom; anchors.right: tableHeader.right; anchors.bottom: parent.bottom

            clip: true

            contentWidth: rowWrapper.width
            contentHeight: rowWrapper.height

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: rowWrapper.height > container.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

            Item {
                id: rowWrapper

                // 자식들이 배치된 영역만큼 자신의 크기를 늘림
                width: childrenRect.width
                height: childrenRect.height

                Column{
                    id : rowContainer

                    anchors.top: parent.top;
                    width: tableHeader.width
                    spacing: 0
                }
            }
        }
    }

    Component{
        id : deviceRow
        ClusterDeviceMonitorRow{
            visible: win.numOfValue >= deviceAddr
            isExpand: win.expandDevAddr === deviceAddr

            onClickExpend: {
                win.clearRWComponent()

                if(isExpand)
                {
                    win.expandDevAddr = 0;
                    return;
                }

                win.expandDevAddr = deviceAddr

                win.regRWComponent(posiOffsetInput      )
                win.regRWComponent(targetPosiInput      )
                win.regRWComponent(ctrlModeSetpointCombo)
                win.regRWComponent(valveSpeedInput      )
                win.regRWComponent(freeszStatusCombo    )
                win.regRWComponent(restartCombo         )

                win.refresh();
            }

            onClickApply: {
                win.apply();
            }
        }
    }
}
