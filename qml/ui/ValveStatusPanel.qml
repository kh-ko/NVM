import QtQuick 2.0
import QtQuick.Layouts 1.3
import "../control/."
import "./."
import FontManager 1.0
import ValveEnumDef 1.0
import GUISetting 1.0

Rectangle {
    id : panel
    property var    mode
    property var    access
    property var    speed
    property var    ctrlAlgo
    property var    isDisablePFO
    property var    isSimulation
    property var    isTestMode
    property var    isFieldBusError
    property var    isFirmwareError
    property var    unknowInterface
    property var    noSensorSignal
    property var    noAnalogSignal
    property var    isNetworkFailure
    property var    isSlaveOffline
    property var    isIsolationValve
    property var    isSensorError
    property var    isSvcRequest
    property var    isLearnNotPresent
    property var    isAirNotReady
    property var    isPFONotReady
    property var    loadProgress

    color: "#FFFFFF"

    NText{
        id : title
        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
        isBold: true
        text : qsTr("Valve status")
    }

    NScrollView{
        id : navigatelist
        anchors.top: title.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;

        delegate : Item{
            width: parent.width; height: modeItem.height + accessItem.height + speedItem.height + ctrlAlgoItem.height + simulationItem.height + pfoItem.height + fieldbusItem.height + firmwareItem.height + unknowInterfaceItem.height + noSensorSignalItem.height + noAnalogSignalItem.height + networkFailItem.height + slaveOfflineItem.height + isolationValveItem.height + sensorErrItem.height + svcRequestItem.height + learnParamItem.height + compressedAirItem.height + pfoNotReadyItem.height

            NKeyValueListItem{
                id : modeItem
                anchors.top: parent.top;
                keyText: qsTr("mode")
                iconSource: panel.mode === ValveEnumDef.MODE_FATAL_ERROR || panel.mode === ValveEnumDef.MODE_SAFETY ? "/image/icon-alret.png" : ""
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.mode === ValveEnumDef.MODE_INIT               ? panel.isTestMode ? qsTr("(t) initialize"      ) : qsTr("initialize"      ) :
                           panel.mode === ValveEnumDef.MODE_SYNC               ? panel.isTestMode ? qsTr("(t) synchronize"     ) : qsTr("synchronize"     ) :
                           panel.mode === ValveEnumDef.MODE_POSITION           ? panel.isTestMode ? qsTr("(t) position"        ) : qsTr("position"        ) :
                           panel.mode === ValveEnumDef.MODE_CLOSED             ? panel.isTestMode ? qsTr("(t) close"           ) : qsTr("close"           ) :
                           panel.mode === ValveEnumDef.MODE_OPEN               ? panel.isTestMode ? qsTr("(t) open"            ) : qsTr("open"            ) :
                           panel.mode === ValveEnumDef.MODE_PRESSURE           ? panel.isTestMode ? qsTr("(t) pressure"        ) : qsTr("pressure"        ) :
                           panel.mode === ValveEnumDef.MODE_HOLD               ? panel.isTestMode ? qsTr("(t) hold"            ) : qsTr("hold"            ) :
                           panel.mode === ValveEnumDef.MODE_LEARN              ? panel.isTestMode ? qsTr("(t) learn"           ) : qsTr("learn"           ) :
                           panel.mode === ValveEnumDef.MODE_INTERLOCK_OPEN_DI  ? panel.isTestMode ? qsTr("(t) inter lock open" ) : qsTr("inter lock open" ) :
                           panel.mode === ValveEnumDef.MODE_INTERLOCK_CLOSE_DI ? panel.isTestMode ? qsTr("(t) inter lock close") : qsTr("inter lock close") :
                           panel.mode === ValveEnumDef.MODE_POWER_FAILURE      ? panel.isTestMode ? qsTr("(t) power failure"   ) : qsTr("power failure"   ) :
                           panel.mode === ValveEnumDef.MODE_SAFETY             ? panel.isTestMode ? qsTr("(t) safety"          ) : qsTr("safety"          ) :
                           panel.mode === ValveEnumDef.MODE_FATAL_ERROR        ? panel.isTestMode ? qsTr("(t) fatal error"     ) : qsTr("fatal error"     ) :""
            }

            NKeyValueListItem{
                id : accessItem
                anchors.top: modeItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                keyText: qsTr("access")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.access === ValveEnumDef.ACCESS_LOCAL         ? qsTr("local"        ) :
                           panel.access === ValveEnumDef.ACCESS_REMOTE        ? qsTr("remote"       ) :
                           panel.access === ValveEnumDef.ACCESS_LOCKED_REMOTE ? qsTr("locked remote") : ""
            }

            NKeyValueListItem{
                id : speedItem
                anchors.top: accessItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                keyText: qsTr("speed")
                valueText: panel.loadProgress !== 100 ? "" : (panel.speed).toFixed(0)// toLocaleString(FontManager.locale, 'f', 0)
            }

            NKeyValueListItem{
                id : ctrlAlgoItem
                anchors.top: speedItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                keyText: qsTr("control-algorithm")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.ctrlAlgo === ValveEnumDef.PRESSURE_CTRL_ADAPTIVE   ? qsTr("adaptive"        ) :
                           panel.ctrlAlgo === ValveEnumDef.PRESSURE_CTRL_FIXED_DOWN ? qsTr("fixed downstream") :
                           panel.ctrlAlgo === ValveEnumDef.PRESSURE_CTRL_FIXED_UP   ? qsTr("fixed upstream"  ) :
                           panel.ctrlAlgo === ValveEnumDef.PRESSURE_CTRL_SOFT_DUMP  ? qsTr("soft dump"       ) : ""
            }

            NKeyValueListItem{
                id : simulationItem
                anchors.top: ctrlAlgoItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isSimulation ? "/image/icon-warning.png" : ""
                keyText: qsTr("simulation")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isSimulation ? qsTr("simulation") : ""
            }

            NKeyValueListItem{
                id : pfoItem
                anchors.top: simulationItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isDisablePFO ? "/image/icon-warning.png" : ""
                keyText: qsTr("PFO")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isDisablePFO ? qsTr("disabled") : ""
            }

            NKeyValueListItem{
                id : fieldbusItem
                anchors.top: pfoItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isFieldBusError ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isFieldBusError ? qsTr("fieldbus error") : ""
            }

            NKeyValueListItem{
                id : firmwareItem
                anchors.top: fieldbusItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isFirmwareError ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isFirmwareError ? qsTr("firmware error") : ""
            }

            NKeyValueListItem{
                id : unknowInterfaceItem
                anchors.top: firmwareItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.unknowInterface ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.unknowInterface ? qsTr("unknow interface") : ""
            }

            NKeyValueListItem{
                id : noSensorSignalItem
                anchors.top: unknowInterfaceItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.noSensorSignal ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.noSensorSignal ? qsTr("no sensor signal") : ""
            }

            NKeyValueListItem{
                id : noAnalogSignalItem
                anchors.top: noSensorSignalItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.noAnalogSignal ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.noAnalogSignal ? qsTr("no analog signal") : ""
            }

            NKeyValueListItem{
                id : networkFailItem
                anchors.top: noAnalogSignalItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isNetworkFailure ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isNetworkFailure ? qsTr("network failure") : ""
            }

            NKeyValueListItem{
                id : slaveOfflineItem
                anchors.top: networkFailItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isSlaveOffline ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isSlaveOffline ? qsTr("slave offline") : ""
            }

            NKeyValueListItem{
                id : isolationValveItem
                anchors.top: slaveOfflineItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isIsolationValve ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.isIsolationValve !== 100 ? "" :
                           panel.isDisablePFO ? qsTr("isolation valve") : ""
            }

            NKeyValueListItem{
                id : sensorErrItem
                anchors.top: isolationValveItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isSensorError ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isSensorError ? qsTr("sensor error") : ""
            }

            NKeyValueListItem{
                id :svcRequestItem
                anchors.top: sensorErrItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isSvcRequest ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isSvcRequest ? qsTr("service request") : ""
            }

            NKeyValueListItem{
                id : learnParamItem
                anchors.top: svcRequestItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isLearnNotPresent ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isLearnNotPresent ? qsTr(" learn parameter") : ""
            }

            NKeyValueListItem{
                id : compressedAirItem
                anchors.top: learnParamItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isAirNotReady ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isAirNotReady ? qsTr("compressed air") : ""
            }

            NKeyValueListItem{
                id : pfoNotReadyItem
                anchors.top: compressedAirItem.bottom; anchors.topMargin: height != 0 ? GUISetting.line_margin : 0
                iconSource: panel.loadProgress === 100 && panel.isPFONotReady ? "/image/icon-warning.png" : ""
                keyText: qsTr("warning")
                valueText: panel.loadProgress !== 100 ? "" :
                           panel.isPFONotReady ? qsTr("PFO not ready") : ""
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
