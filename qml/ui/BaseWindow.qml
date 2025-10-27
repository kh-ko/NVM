import QtQuick 2.12
import QtQuick.Window 2.12
import QmlCoreModel 1.0
import DebuggingModel 1.0
import "./."
import "../control/."
import "./dialog/."
//import ViewManager 1.0
//import MainModel 1.0
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import ValveEnumDef 1.0
import UnitUtil 1.0
import MathUtil 1.0
import GlobalUiValue 1.0
import GUISetting 1.0

Window {
    id: window

    property ValveRecoveryDlg valveRecoveryDlgObj: null
    property FatalErrorDlg fatalErrorDlgObj: null

    visible: true
    title: (model.mCompany !== ValveEnumDef.COMPANY_NOVA) && (model.mCompany !== ValveEnumDef.COMPANY_APSYS) ? qsTr("New Valve Manager") : qsTr("NVM - NOVASEN Valve Manager")

    width: 1024; height: 705
    minimumHeight: 705; minimumWidth: 1024
    //maximumHeight: 1080; maximumWidth: 1920

    function showPortSelection()
    {
        var popup = portSelectionDlg.createObject(window)
        popup.show();
    }

    Component.onCompleted: {
        console.debug("model.mIsWithoutLogo = " + model.mIsWithoutLogo)
        window.showPortSelection();
    }

    onWidthChanged: {
       GUISetting.scale = (width / minimumWidth) > (height / minimumHeight) ? (height / minimumHeight) : (width / minimumWidth)
    }

    onHeightChanged: {
        GUISetting.scale = (width / minimumWidth) > (height / minimumHeight) ? (height / minimumHeight) : (width / minimumWidth)
    }


    onClosing: {
        if(model.mIsRecord)
        {
            model.onCommandSaveRecordData("")
        }
    }

    DebuggingModel{

    }

    QmlCoreModel{
        id : model

        onSignalEventAddGraphPoint: {
            chart.addPoint(msec, currPos, currPressure, targetPos, targetPressure)
        }

        onSignalEventChangedIsRecord: {
            if(mIsRecord == false)
                fileDialog.open();
        }

        onSignalEventOccurError: {
            //var popup = alertPopup.createObject(window)
            //popup.titleText = qsTr("Error")
            //popup.contentText = value
            //popup.msgIcon.source = "/image/icon-alret.png"
            //popup.open();
        }

        onSignalEventChangedMode:
        {
            if(mMode === ValveEnumDef.MODE_FATAL_ERROR)
            {
                if(window.fatalErrorDlgObj != null)
                    return;

                if(window.valveRecoveryDlgObj != null)
                    window.valveRecoveryDlgObj.close()

                window.fatalErrorDlgObj = fatalErrorDlg.createObject(window);
                window.fatalErrorDlgObj.show();
            }
        }
    }

    Rectangle{
        color: "#E4E4E4"
        anchors.fill: parent
    }

    TitlePanel{
        id : title
        height: GUISetting.title_panel_height
        anchors.left: parent.left; anchors.right: parent.right

        connected : model.mIsValveConnect
        isLocal: model.mAccess == ValveEnumDef.ACCESS_LOCAL
        isRS232Test : model.mIsRS232Test
        version: "Vserion " + model.mNCPAVersion

        onClickPortSelection: {
            window.showPortSelection();
        }

        onClickRemoteMode: {
            model.onCommandWriteAccess(ValveEnumDef.ACCESS_REMOTE);
        }

        onClickLocalMode: {
            var newAccess = title.isLocal ? ValveEnumDef.ACCESS_REMOTE : ValveEnumDef.ACCESS_LOCAL

            if(title.isLocal == false)
            {
                var popup = changeAccessDlg.createObject(window)
                popup.open();
            }
        }
    }

    NavigationPanel{
        id : navigation
        width: GUISetting.navi_panel_width
        anchors.top: title.bottom; anchors.topMargin: 2; anchors.bottom: statusBar.top; anchors.bottomMargin : 2;

        isLogoVisible     : !model.mIsWithoutLogo
        isRunSequencer    : seqTestDlg.isRun
        isZeroEnable      : model.mZeroEnable
        isConnected       : model.mIsValveConnect
        isSupportPFO      : model.mIsSupportPFO
        isApSysCtrlMonitor: parseInt(model.mFirmwareVersion.slice(-4), 16) > 0x590 && model.mCompany === ValveEnumDef.COMPANY_APSYS
        company           : model.mCompany

        onClickValveIdentification    : { var popup = valveIdentificationExDlg.createObject(window) ; popup.show(); }
        onClickValveSetup             : { var popup = valveSetupDlg.createObject(window)            ; popup.show(); }
        onClickValveParameters        :
        {
            var lastValue = parseInt(model.mFirmwareVersion.slice(-4), 16);

            if(lastValue > 0x601)
            {
                var popup = valveParamPMDlg.createObject(window)          ; popup.show();
            }
            else
            {
                var popup = valveParamExDlg.createObject(window)          ; popup.show();
            }
        }
        onClickValveCycleCounter      : { var popup = valveCycleCounterDlg.createObject(window)     ; popup.show(); }
        onClickValvePowerFailStatus   : { var popup = valvePowerFailStatusDlg.createObject(window)  ; popup.show(); }
        onClickValveRecovery          :
        {
            if(window.valveRecoveryDlgObj !== null)
                return;

            window.valveRecoveryDlgObj = valveRecoveryDlg.createObject(window);
            window.valveRecoveryDlgObj.show();
        }
        onClickValveCailbration       :
        {
            var popup;
            var lastValue = parseInt(model.mFirmwareVersion.slice(-4), 16);
            if (lastValue > 0x479) {
                popup = valveCalibrationExDlg.createObject(window)    ; popup.show();
            } else {
                popup = valveCalibrationDlg.createObject(window)      ; popup.show();
            }
        }
        onClickSensorSetup                : { var popup = sensorSetupExDlg.createObject(window)          ; popup.show(); }
        onClickSensorAnalysis             : { var popup = sensorAnalysisDlg.createObject(window)         ; popup.show(); }
        onClickPressureCtrlSetup          : { var popup = pressureCtrlFloatSetupDlg.createObject(window) ; popup.show(); }
        onClickPressureCtrlAdvanSetup     : { var popup = pressureCtrlAdvanSetupDlg.createObject(window) ; popup.show(); }
        onClickPressureCtrlLearnParam     : { var popup = pressureCtrlLearnParamDlg.createObject(window) ; popup.show(); }//popup.open(); }
        onClickPressureCtrlLearnList      : { var popup = pressureCtrlLearnListDlg.createObject(window)  ; popup.show(); }//popup.open(); }
        onClickPressureCtrlGainMointoring : { var popup = pressureCtrlGainMonitorDlg.createObject(window); popup.show(); }
        onClickNCPASettings               : { var popup = ncpaSettingsDlg.createObject(window)           ; popup.show(); }
        onClickInterfaceSetup             : {
            var popup
            if(model.mInterface == ValveEnumDef.INTERFACE_ETHERCAT)
            {
                popup = interfaceSetupEtherCATDlg.createObject(window);
            }
            else if(model.mInterface == ValveEnumDef.INTERFACE_DEVICENET)
            {
                popup = interfaceSetupDevNetDlg.createObject(window);
            }
            else if(model.mInterface === ValveEnumDef.INTERFACE_RS232 || model.mInterface === ValveEnumDef.INTERFACE_RS232_WITH_ANALOGOUTPUT || model.mInterface === ValveEnumDef.INTERFACE_RS485 ||  model.mInterface === ValveEnumDef.INTERFACE_RS485_WITH_ANALOGOUTPUT)
            {
                popup = interfaceSetupRS232Dlg.createObject(window);
            }
            else if(model.mInterface === ValveEnumDef.INTERFACE_ETHERNET || model.mInterface === ValveEnumDef.INTERFACE_ETHERNET_WITH_ANALOGOUTPUT)
            {
                popup = interfaceSetupEtherNETDlg.createObject(window);
            }
            else if(model.mInterface == ValveEnumDef.INTERFACE_PROFIBUS)
            {
                popup = interfaceSetupProfibusDlg.createObject(window);
            }
            else
            {
                popup = interfaceSetupLogicDlg.createObject(window);
            }

            popup.show();
        }
        onClickInterfaceStatus        : {
            var popup
            if(model.mInterface == ValveEnumDef.INTERFACE_ETHERCAT)
            {
                popup = interfaceStatusEtherCATDlg.createObject(window);
            }
            else if(model.mInterface == ValveEnumDef.INTERFACE_DEVICENET)
            {
                popup = interfaceStatusDNetDlg.createObject(window);
            }
            else if(model.mInterface === ValveEnumDef.INTERFACE_RS232 || model.mInterface === ValveEnumDef.INTERFACE_RS232_WITH_ANALOGOUTPUT || model.mInterface === ValveEnumDef.INTERFACE_RS485 ||  model.mInterface === ValveEnumDef.INTERFACE_RS485_WITH_ANALOGOUTPUT || model.mInterface === ValveEnumDef.INTERFACE_ETHERNET || model.mInterface === ValveEnumDef.INTERFACE_ETHERNET_WITH_ANALOGOUTPUT)
            {
                popup = interfaceStatusRS232Dlg.createObject(window);
            }
            else if(model.mInterface == ValveEnumDef.INTERFACE_PROFIBUS)
            {
                popup = interfaceStatusProfibusDlg.createObject(window);
            }
            else
            {
                popup = interfaceStatusLogicDlg.createObject(window);
            }

            popup.show();
        }

        onClickInterfaceTrace         : { var popup = interfaceTraceDlg.createObject(window)            ; popup.show(); }
        onClickToolChartAnalyzer      : { var popup = graphAnalyzeDlg.createObject(window)              ; popup.loadFromChart(chart.chartView); popup.show();}
        onClickToolSequencer          : {seqTestDlg.show(); }
        onClickToolFuSelectMethod     : { var popup = fuSelMethodDlg.createObject(window)               ; popup.show(); }
        //onClickToolFirmwareUpdate      : { var popup = firmwareUpdateDlg.createObject(window)            ; popup.show(); }
        //onClickToolFirmwareUpdateViaNet: { var popup = firmwareUpdateViaNetDlg.createObject(window)     ; popup.show(); }
        onClickAdvToolTest            : { var popup = advancedToolTestDlg.createObject(window)          ; popup.show(); }
        onClickAdvBackupNRestore      : { var popup = advancedToolBackupNRestoreDlg.createObject(window); popup.show(); }
        onClickAdvDiskHoriCalibration : { var popup = advancedToolDiskHoriCalibDlg.createObject(window) ; popup.show(); }
        onClickHelpAbout              : { var popup = helpAboutDlg.createObject(window)                 ; popup.show(); }
    }

    ChartPanel{
        id :chart

        anchors.left: navigation.right; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2; anchors.top: title.bottom; anchors.topMargin: 2; anchors.bottom: statusContainer.top; anchors.bottomMargin: 2;

        isConnected              : model.mIsValveConnect
        isCurrPosDraw            : model.mIsCurrPosDraw
        isCurrPressureDraw       : model.mIsCurrPressureDraw
        isTargetPosDraw          : model.mIsTargetPosDraw
        isTargetPressureDraw     : model.mIsTargetPressureDraw
        isAutoScalePos           : model.mIsPosAutoScaling
        isAutoScalePressure      : model.mIsPressureAutoScaling
        isPause                  : model.mIsPause
        xRange                   : model.mChartMSec
        isPressureLogType        : model.mIsPressureLogType
        loadProgress             : model.mLoadProgress
        posResolution            : model.mPosResolution
        pressureDpUnit           : model.mPressureDpUnit
        sensorfullScale          : model.mFullScale
        sensorFullScaleUnit      : model.mFullScaleUnit
        stdFullScale             : model.mStdFullScale
        convertedSensorFullScale : model.mConvertedFullScale
        convertedCurrPressure    : model.mConvertedRTPressure
        convertedTargetPressure  : model.mConvertedTPressure
        minPressure              : model.mMinMainPressureChart
        maxPressure              : model.mMaxMainPressureChart
        fixedN                   : model.mPressureFixedN > 8 ? 8 : model.mPressureFixedN
        autoScaleMinMargin       : model.mAutoScaleMinMargin
        pressureDecades          : model.mPressureDecades
        isRecord                 : model.mIsRecord
        isAutoRecord             : model.mIsAutoRecord
        recordTime               : model.mRecordTime
        autoRecordTime           : model.mAutoRecordTime


        onClickPause     : {model.onCommandClickPause()     }
        onClickRecord    : {model.onCommandClickRecord()    }
        onClickAutoRecord: {model.onCommandClickAutoRecord()}
        onClickAnalyze: {
            var popup = graphAnalyzeDlg.createObject(window);

            popup.loadFromChart(chart.chartView); popup.show();
        }

        MouseArea {
            anchors.top: parent.top; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.chart_ctrlbox_height + GUISetting.margin
            acceptedButtons: Qt.RightButton

            onPressed: {
                focus = true
            }

            onClicked: {
                if (mouse.button === Qt.RightButton)
                    contextMenu.open()
            }

            Menu {
                id: contextMenu

                MenuItem {
                    text: qsTr("Set pressure graph(min/max)")
                    onTriggered: {
                        var popup = graphMinMaxDlg.createObject(window);
                        popup.show();
                    }
                }
            }
        }
    }

    RowLayout{
        id : statusContainer
        height: GUISetting.status_container_height
        anchors.left: navigation.right; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2; anchors.bottom: statusBar.top; anchors.bottomMargin: 2;
        spacing: 2

        ValveStatusPanel{
            Layout.preferredWidth: 246; Layout.fillHeight: true; Layout.fillWidth: true
            mode              : model.mMode
            access            : model.mAccess
            speed             : model.mValveSpeed
            ctrlAlgo          : model.mCtrlAlgo
            isDisablePFO      : model.mIsSupportPFO && !model.mEnablePFO
            isSimulation      : model.mIsSimulation
            isTestMode        : model.mIsTestMode
            isFieldBusError   : model.mFieldBusError
            isSaving          : model.mIsSaving
            isFirmwareError   : model.mFirmwareError
            unknowInterface   : model.mUnknowInterface
            noSensorSignal    : model.mNoSensorSignal
            noAnalogSignal    : model.mNoAnalogSignal
            isNetworkFailure  : model.mNetworkFailure
            isSlaveOffline    : model.mSlaveOffline
            isIsolationValve  : model.mIsolationValve
            isSensorError     : model.mSensorError
            isSvcRequest      : model.mSvcRequest
            isLearnNotPresent : model.mLearnNotPresent
            isAirNotReady     : model.mAirNotReady
            isPFONotReady     : model.mPFONotReady
            loadProgress : model.mLoadProgress
        }
        ControlPanel{
            Layout.preferredWidth: 118; Layout.fillHeight: true; Layout.fillWidth: true

            isDevMode      : model.mIsDevMode
            company        : model.mCompany
            access         : model.mIsRS232Test ? ValveEnumDef.ACCESS_LOCAL : model.mAccess
            mode           : model.mMode
            isOpen         : model.mIsOpen
            isClose        : model.mIsClose
            connected      : model.mIsValveConnect
            isLearnRunning : controlLearnDlg.isRunning

            onClickZero          : { var popup = controlZeroDlg.createObject(window)       ; popup.show(); }
            onClickSimulation    : { model.onCommandSimulation()                                           }
            onClickLearn         : { controlLearnDlg.show();/*var popup = controlLearnDlg.createObject(window)      ; popup.show();*/}
            onClickHold          : { model.onCommandHoldPosition();                                        }
            onClickOpen          : { model.onCommandOpenPosition();                                        }
            onClickClose         : { model.onCommandClosePosition();                                       }
            onClickSoftOpen      : { model.onCommandSoftOpen();                                            }
            onClickSoftClose     : { model.onCommandSoftClose();                                           }
        }
        PositionPanel{
            Layout.preferredWidth: 240; Layout.fillHeight: true; Layout.fillWidth: true

            connected     : model.mIsValveConnect
            access        : model.mIsRS232Test ? ValveEnumDef.ACCESS_LOCAL : model.mAccess
            posResolution : model.mPosResolution
            currPos       : model.mCurrPos
            targetPos     : model.mTargetPos
            mode          : model.mMode
            isTestMode    : model.mIsTestMode
            controlMode   : model.mControlMode
            setPointPos01 : model.mSetPoint01Position
            setPointPos02 : model.mSetPoint02Position
            setPointPos03 : model.mSetPoint03Position
            setPointPos04 : model.mSetPoint04Position
            setPointPos05 : model.mSetPoint05Position
            setPointPos06 : model.mSetPoint06Position

            onCmdPosChanged: {
                var newPos = Math.round(cmdPos);
                model.onCommandWritePosition(newPos)
            }

            onEditSetPoint: { var popup = setPointPositionDlg.createObject(window); popup.show(); }
        }
        PressurePanel{
            id : pressurePanel

            Layout.preferredWidth: 240; Layout.fillHeight: true; Layout.fillWidth: true   

            connected                : model.mIsValveConnect
            access                   : model.mIsRS232Test ? ValveEnumDef.ACCESS_LOCAL : model.mAccess
            mode                     : model.mMode
            isTestMode               : model.mIsTestMode
            controlMode              : model.mControlMode
            pressureDpUnit           : model.mPressureDpUnit
            isPressureLogType        : model.mIsPressureLogType

            stdFullScale             : model.mStdFullScale
            convertedSensorFullScale : model.mConvertedFullScale
            convertedCurrPressure    : model.mConvertedRTPressure
            convertedTargetPressure  : model.mConvertedTPressure
            fixedN                   : model.mPressureFixedN > 8 ? 8 : model.mPressureFixedN
            pressureDecades          : model.mPressureDecades

            setPointPressure01 : model.mSetPoint01Pressure
            setPointPressure02 : model.mSetPoint02Pressure
            setPointPressure03 : model.mSetPoint03Pressure
            setPointPressure04 : model.mSetPoint04Pressure
            setPointPressure05 : model.mSetPoint05Pressure
            setPointPressure06 : model.mSetPoint06Pressure

            onCmdPressureChanged: {
                model.onCommandWritePressure(cmdPressure)
            }

            onEditSetPoint: { var popup = setPointPositionDlg.createObject(window); popup.show(); }
        }
    }

    Rectangle{
        anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
        color: "#59000000"

        visible: GlobalUiValue.needDim

        MouseArea{
            anchors.fill: parent
            hoverEnabled: true
            onPressed: {}
        }
    }

    StatusBar{
        id : statusBar
        height: GUISetting.status_bar_height
        anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right

        connectInfo  : model.mConnectionInfo

        serialNumber : model.mValveID
        isConnected  : model.mIsValveConnect
        scanRate     : model.mScanRate
        loadProgress : model.mLoadProgress
        //errMsg       : model.mErrMsg
    }

    FileDialog{
        id: fileDialog
            title: qsTr("Save record as")
            fileMode: FileDialog.SaveFile
            nameFilters: ["Text files (*.txt)"]

            onAccepted: {
                model.onCommandSaveRecordData(currentFile.toString().split("///")[1])
            }
            onRejected: {
            }
            visible : false
    }

    Component{
        id : portSelectionDlg
        SearchDeviceDlg{
            onSelectPort: {
                model.onCommandConnect(connType, portName)
            }
        }
    }

    Component{
        id : alertPopup
        NMessageBox{}
    }

    Component{
        id : changeAccessDlg
        ChangeAccessDlg{
        }
    }

    Component{
        id : valveIdentificationExDlg
        ValveIdentificationExDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : valveSetupDlg
        ValveSetupDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : valveParamExDlg
        ValveParamExDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : valveParamPMDlg
        ValveParamPMDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : valveRecoveryDlg
        ValveRecoveryDlg
        {
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID

            onClosing: {
                window.valveRecoveryDlgObj = null;
            }
        }
    }
    Component{
        id : sensorSetupDlg
        SensorSetupDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : sensorSetupExDlg
        SensorSetupExDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID

            onSignalEventOccurErr: {
                close()
                var popup = sensorSetupDlg.createObject(window); popup.show();
            }
        }
    }
    Component{
        id : sensorAnalysisDlg
        SensorAnalyzerDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : pressureCtrlSetupDlg
        PressureCtrlSetupDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : pressureCtrlFloatSetupDlg
        PressureCtrlFlotSetupDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID

            onSignalEventOccurErr: {
                close()
                var popup = pressureCtrlSetupDlg.createObject(window); popup.show();
            }
        }
    }
    Component{
        id : pressureCtrlAdvanSetupDlg
        PressureCtrlForPmProtoDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID

            onSignalEventOccurErr: {
                close()
                var popup = pressureCtrlSetupDlg.createObject(window); popup.show();
            }
        }
    }

    Component{
        id : pressureCtrlLearnParamDlg
        PressureCtrlLearnParamDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : pressureCtrlLearnListDlg
        PressureLearnList{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : pressureCtrlGainMonitorDlg
        PressureCtrlGainMonitorDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : ncpaSettingsDlg
        NCPASettingsDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : interfaceSetupLogicDlg
        InterfaceSetupLogicDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : interfaceSetupEtherCATDlg
        InterfaceSetupEtherCATDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
            company    : model.mCompany
        }
    }
    Component{
        id : interfaceSetupDevNetDlg
        InterfaceSetupDevNetDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
            company    : model.mCompany
            firmwareVer: parseInt(model.mFirmwareVersion.slice(-4), 16)

            onClickRangeSetting: {
                 var popup = interfaceSetupDevNetRangeDlg.createObject(window) ; popup.show();
            }
        }
    }

    Component{
        id : interfaceSetupDevNetRangeDlg
        InterfaceSetupDevNetRangeDlg{

        }
    }

    Component{
        id : interfaceSetupRS232Dlg
        InterfaceSetupRS232Dlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : interfaceSetupEtherNETDlg
        InterfaceSetupEtherNETDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : interfaceSetupProfibusDlg
        InterfaceSetupProfibusDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
            company    : model.mCompany
        }
    }


    Component{
        id : interfaceStatusLogicDlg
        InterfaceStatusLogicDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : interfaceStatusEtherCATDlg
        InterfaceStatusEtherCATDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : interfaceStatusDNetDlg
        InterfaceStatusDNetDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : interfaceStatusRS232Dlg
        InterfaceStatusRS232Dlg{
            connectInfo    : model.mConnectionInfo
            valveID        : model.mValveID
            userInterface  : model.mInterface
        }
    }
    Component{
        id : interfaceStatusProfibusDlg
        InterfaceStatusProfibusDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : interfaceTraceDlg
        InterfaceTraceDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
            userInterface  : model.mInterface
        }
    }

    Component{
        id : valveCycleCounterDlg
        ValveCycleCounterDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : valvePowerFailStatusDlg
        ValvePowerFailStatusDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : valveCalibrationDlg
        ValveCailbrationDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : valveCalibrationExDlg
        ValveCalibrationExDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id :helpAboutDlg
        HelpAboutDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
            versionValue: model.mNCPAVersion
            company     : model.mCompany
        }
    }
    Component{
        id : advancedToolTestDlg
        AdvancedToolTestDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
    Component{
        id : advancedToolBackupNRestoreDlg
        AdvancedToolBackupNRestoreDlg{
            property string firmwareUpdateMethod : ""
            onClosing: {
                var popup
                if(firmwareUpdateMethod == "network")
                {
                    popup = firmwareUpdateDlg.createObject(window);
                    popup.method = firmwareUpdateMethod
                    popup.show();
                }
                else if(firmwareUpdateMethod == "local")
                {
                    popup = firmwareUpdateDlg.createObject(window);
                    popup.method = firmwareUpdateMethod
                    popup.show();
                }
            }
        }
    }
    Component{
        id : advancedToolDiskHoriCalibDlg
        AdvancedToolDiskHoriCalibDlg{

        }
    }
    Component{
        id : controlZeroDlg
        ControlZeroDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }
//    Component{
//        id :controlLearnDlg
//        ControlLearnDlg{}
//    }

    ControlLearnDlg{
        id :controlLearnDlg
        connectInfo: model.mConnectionInfo
        valveID    : model.mValveID
    }
    Component{
        id :fatalErrorDlg
        FatalErrorDlg{
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID

            onClosing: {
                window.fatalErrorDlgObj = null;
            }

            onClickRecovery: {
                if(window.valveRecoveryDlgObj == null)
                {
                    window.valveRecoveryDlgObj = valveRecoveryDlg.createObject(window);
                    window.valveRecoveryDlgObj.show();
                }
            }
        }
    }

    SequencerDlg{
        id : seqTestDlg

        connectInfo: model.mConnectionInfo
        valveID    : model.mValveID
    }


    Component{
        id : setPointPositionDlg
        SetPointPositionDlg
        {
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID

            convertedFullScale    : model.mConvertedFullScale
            sensorfullScale       : model.mFullScale
            sensorFullScaleUnit   : model.mFullScaleUnit
            stdFullScale          : model.mStdFullScale
            pressureConvertFactor : model.mPressureConvertFactor
            pressureFixedN        : model.mPressureFixedN
            pressureDpUnit        : model.mPressureDpUnit
        }
    }

    Component{
        id : fuSelMethodDlg

        FUSelectMethodDlg
        {
            onSelectedMethod: {
                if(model.mIsValveConnect)
                {
                     var msgBox = questionExportSettingDMsgBox.createObject(window);
                    msgBox.method = method
                    msgBox.open()
                    return
                }
                var popup = firmwareUpdateDlg.createObject(window)
                popup.method = method
                popup.show();
            }
        }
    }

    Component{
        id : questionExportSettingDMsgBox

        NOKMessageBox
        {
            property string method : ""

            //function onReslut()
            contentText : qsTr("When the firmware is updated, all settings are initialized.<br>Would you like to back up your settings before updating the firmware?")
            okText : qsTr("Backup")
            noText: qsTr("Skip")
            contentHeight: 170 * GUISetting.scale; contentWidth: 400 * GUISetting.scale

            onResult:
            {
                var popup

                if(bOk)
                {
                    popup = advancedToolBackupNRestoreDlg.createObject(window);
                    popup.show();
                    popup.firmwareUpdateMethod = method
                    popup.isForUpdate = true;
                    popup.fnBackup();
                }
                else
                {
                    popup = firmwareUpdateDlg.createObject(window)
                    popup.method = method
                    popup.show();
                }
            }
        }
    }

    Component{
        id : firmwareUpdateDlg

        FirmwareUpdateExDlg
        {
            onClickRestoreSettings: {
                var popup = advancedToolBackupNRestoreDlg.createObject(window);
                popup.show();
                popup.fnRestore();
            }
        }
    }

    Component{
        id : firmwareUpdateViaNetDlg

        FirmwareUpdateViaNetworkDlg
        {
        }
    }

    Component{
        id : graphAnalyzeDlg
        GraphAnalyzeDlg
        {
            connectInfo: model.mConnectionInfo
            valveID    : model.mValveID
        }
    }

    Component{
        id : graphMinMaxDlg
        GraphMinMaxDlg
        {
            minPressureChart : model.mMinMainPressureChart
            maxPressureChart : model.mMaxMainPressureChart
            pressureFixedN   : model.mPressureFixedN
            strUnit : model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PA    ? "pa"  :
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_BAR   ? "bar"  :
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MBAR  ? "mbar" :
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_UBAR  ? "ubar" :
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_TORR  ? "Torr" :
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_MTORR ? "mTorr":
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_ATM   ? "atm"  :
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSI   ? "psi"  :
                      model.mPressureDpUnit === ValveEnumDef.PRESSURE_UNIT_PSF   ? "psf"  : ""

            onSignalChangedMinMax: {
                model.onCommandSetMinMaxPressureChart(min, max)
            }
        }
    }
}




/*##^##
Designer {
    D{i:0;formeditorZoom:1.100000023841858}
}
##^##*/
