import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Window 2.12
import QmlCoreModel 1.0
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

    property bool isLogoVisible : true
    property ValveRecoveryDlg valveRecoveryDlgObj: null
    property FatalErrorDlg fatalErrorDlgObj: null

    visible: true
    title: qsTr("NVM - NOVASEN Valve Manager")
    //title: "Control Performance Analyzer"

    width: 1024; height: 705
    minimumHeight: 705; minimumWidth: 1024
    //maximumHeight: 1080; maximumWidth: 1920

    function showPortSelection()
    {
        var popup = portSelectionDlg.createObject(window)
        popup.show();
    }

    Component.onCompleted: {
        window.showPortSelection();
    }

    onWidthChanged: {
       GUISetting.scale = (width / minimumWidth) > (height / minimumHeight) ? (height / minimumHeight) : (width / minimumWidth)
    }

    onHeightChanged: {
        GUISetting.scale = (width / minimumWidth) > (height / minimumHeight) ? (height / minimumHeight) : (width / minimumWidth)
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

        onClickChangeAccessMode: {
            var newAccess = title.isLocal ? ValveEnumDef.ACCESS_REMOTE : ValveEnumDef.ACCESS_LOCAL
            model.onCommandWriteAccess(newAccess);
        }
    }

    NavigationPanel{
        id : navigation
        width: GUISetting.navi_panel_width
        anchors.top: title.bottom; anchors.topMargin: 2; anchors.bottom: statusBar.top; anchors.bottomMargin : 2;

        isLogoVisible  : window.isLogoVisible
        isRunSequencer : seqTestDlg.isRun
        isZeroEnable   : model.mZeroEnable
        isConnected    : model.mIsValveConnect
        isSupportPFO   : model.mIsSupportPFO

        onClickValveIdentification    : { var popup = valveIdentificationExDlg.createObject(window) ; popup.show(); }
        onClickValveSetup             : { var popup = valveSetupDlg.createObject(window)            ; popup.show(); }
        onClickValveParameters        : { var popup = valveParamExDlg.createObject(window)          ; popup.show(); }
        onClickValveCycleCounter      : { var popup = valveCycleCounterDlg.createObject(window)     ; popup.show(); }
        onClickValvePowerFailStatus   : { var popup = valvePowerFailStatusDlg.createObject(window)  ; popup.show(); }
        onClickValveRecovery          :
        {
            if(window.valveRecoveryDlgObj !== null)
                return;

            window.valveRecoveryDlgObj = valveRecoveryDlg.createObject(window);
            window.valveRecoveryDlgObj.show();
        }
        onClickValveCailbration       : { var popup = valveCalibrationDlg.createObject(window)      ; popup.show(); }
        onClickSensorSetup            : { var popup = sensorSetupExDlg.createObject(window)         ; popup.show(); }
        onClickPressureCtrlSetup      : { var popup = pressureCtrlFloatSetupDlg.createObject(window); popup.show(); }
        onClickPressureCtrlLearnParam : { var popup = pressureCtrlLearnParamDlg.createObject(window); popup.show(); }//popup.open(); }
        onClickNCPASettings           : { var popup = ncpaSettingsDlg.createObject(window)          ; popup.show(); }
        onClickInterfaceSetup         : {
            var popup
            if(model.mInterface == ValveEnumDef.INTERFACE_ETHERCAT)
            {
                popup = interfaceSetupEtherCATDlg.createObject(window);
            }
            else if(model.mInterface == ValveEnumDef.INTERFACE_DEVICENET)
            {
                popup = interfaceSetupDevNetDlg.createObject(window);
            }
            else if(model.mInterface === ValveEnumDef.INTERFACE_RS232 || model.mInterface === ValveEnumDef.INTERFACE_RS232_WITH_ANALOGOUTPUT)
            {
                popup = interfaceSetupRS232Dlg.createObject(window);
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
            else if(model.mInterface === ValveEnumDef.INTERFACE_RS232 || model.mInterface === ValveEnumDef.INTERFACE_RS232_WITH_ANALOGOUTPUT)
            {
                popup = interfaceStatusRS232Dlg.createObject(window);
            }

            else
            {
                popup = interfaceStatusLogicDlg.createObject(window);
            }

            popup.show();
        }
        onClickToolChartAnalyzer      : { var popup = graphAnalyzeDlg.createObject(window)          ; popup.loadFromChart(chart.chartView); popup.show();}
        onClickToolSequencer          : {seqTestDlg.show(); }
        onClickToolFirmwareUpdate     : { var popup = firmwareUpdateDlg.createObject(window)        ; popup.show(); }
        onClickAdvToolTest            : { var popup = advancedToolTestDlg.createObject(window)      ; popup.show(); }
        onClickHelpAbout              : { var popup = helpAboutDlg.createObject(window)             ; popup.show(); }
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
        fixedN                   : model.mPressureFixedN > 8 ? 8 : model.mPressureFixedN
        pressureDecades          : model.mPressureDecades
        isRecord                 : model.mIsRecord
        recordTime               : model.mRecordTime


        onClickPause  : {model.onCommandClickPause() }
        onClickRecord : {model.onCommandClickRecord()}
        onClickAnalyze: {
            var popup = graphAnalyzeDlg.createObject(window);

            popup.loadFromChart(chart.chartView); popup.show();}
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
            isFirmwareError   : model.mFirmwareError
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
                model.onCommandSaveRecordData(currentFile.toString().split("///")[1] + ".txt")
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
        id : valveIdentificationExDlg
        ValveIdentificationExDlg{}
    }

    Component{
        id : valveSetupDlg
        ValveSetupDlg{}
    }
    Component{
        id : valveParamExDlg
        ValveParamExDlg{}
    }

    Component{
        id : valveRecoveryDlg
        ValveRecoveryDlg
        {
            onClosing: {
                window.valveRecoveryDlgObj = null;
            }
        }
    }
    Component{
        id : sensorSetupDlg
        SensorSetupDlg{}
    }
    Component{
        id : sensorSetupExDlg
        SensorSetupExDlg{
            onSignalEventOccurErr: {
                close()
                var popup = sensorSetupDlg.createObject(window); popup.show();
            }
        }
    }
    Component{
        id : pressureCtrlSetupDlg
        PressureCtrlSetupDlg{}
    }
    Component{
        id : pressureCtrlFloatSetupDlg
        PressureCtrlFlotSetupDlg{
            onSignalEventOccurErr: {
                close()
                var popup = pressureCtrlSetupDlg.createObject(window); popup.show();
            }
        }
    }
    Component{
        id : pressureCtrlLearnParamDlg
        PressureCtrlLearnParamDlg{}
    }
    Component{
        id : ncpaSettingsDlg
        NCPASettingsDlg{}
    }
    Component{
        id : interfaceSetupLogicDlg
        InterfaceSetupLogicDlg{}
    }
    Component{
        id : interfaceSetupEtherCATDlg
        InterfaceSetupEtherCATDlg{}
    }
    Component{
        id : interfaceSetupDevNetDlg
        InterfaceSetupDevNetDlg{}
    }
    Component{
        id : interfaceSetupRS232Dlg
        InterfaceSetupRS232Dlg{}
    }
    Component{
        id : interfaceStatusLogicDlg
        InterfaceStatusLogicDlg{}
    }
    Component{
        id : interfaceStatusEtherCATDlg
        InterfaceStatusEtherCATDlg{}
    }
    Component{
        id : interfaceStatusDNetDlg
        InterfaceStatusDNetDlg{}
    }
    Component{
        id : interfaceStatusRS232Dlg
        InterfaceStatusRS232Dlg{}
    }

    Component{
        id : valveCycleCounterDlg
        ValveCycleCounterDlg{}
    }
    Component{
        id : valvePowerFailStatusDlg
        ValvePowerFailStatusDlg{}
    }

    Component{
        id : valveCalibrationDlg
        ValveCailbrationDlg{}
    }
    Component{
        id :helpAboutDlg
        HelpAboutDlg{ versionValue: model.mNCPAVersion}
    }
    Component{
        id : advancedToolTestDlg
        AdvancedToolTestDlg{}
    }

    Component{
        id : controlZeroDlg
        ControlZeroDlg{}
    }
//    Component{
//        id :controlLearnDlg
//        ControlLearnDlg{}
//    }

    ControlLearnDlg{
        id :controlLearnDlg
    }
    Component{
        id :fatalErrorDlg
        FatalErrorDlg{
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
    }


    Component{
        id : setPointPositionDlg
        SetPointPositionDlg
        {
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
        id : firmwareUpdateDlg

        FirmwareUpdateDlg
        {

        }
    }

    Component{
        id : graphAnalyzeDlg
        GraphAnalyzeDlg
        {

        }
    }
}




/*##^##
Designer {
    D{i:0;formeditorZoom:1.100000023841858}
}
##^##*/
