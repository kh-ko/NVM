import QtQuick 2.0
import QtQuick.Controls 2.5
import "../control/."
import "./dialog/."
import GlobalUiValue 1.0
import GUISetting 1.0
import ValveEnumDef 1.0

Rectangle {
    id : panel

    property bool isRunSequencer: false
    property bool isZeroEnable  : false
    property bool isConnected   : false
    property bool isSupportPFO  : false
    property bool isLogoVisible : false
    property bool isApSysCtrlMonitor : true
    property int  company       : 0

    color : "#FFFFFF"

    signal clickValveIdentification()
    signal clickValveSetup()
    signal clickValveParameters()
    signal clickValveCycleCounter()
    signal clickValvePowerFailStatus()
    signal clickValveRecovery()
    signal clickValveCailbration()
    signal clickSensorSetup()
    signal clickSensorAnalysis()
    signal clickPressureCtrlSetup()
    signal clickPressureCtrlAdvanSetup()
    signal clickPressureCtrlLearnParam()
    signal clickPressureCtrlLearnList()
    signal clickPressureCtrlGainMointoring()
    signal clickInterfaceSetup()
    signal clickInterfaceStatus()
    signal clickInterfaceTrace()
    signal clickToolChartAnalyzer()
    signal clickToolSequencer()
    signal clickToolFuSelectMethod()
    signal clickToolFirmwareUpdate()
    signal clickToolFirmwareUpdateViaNet()
    signal clickNCPASettings()
    signal clickAdvToolTest()
    signal clickAdvBackupNRestore()
    signal clickAdvDiskHoriCalibration()
    signal clickHelpManual()
    signal clickHelpAbout()
    signal clickHelpVisitNOVASEN()

    NScrollView{
        id : navigatelist
        //anchors.fill: parent
        anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top; anchors.bottom: logoImg.top; anchors.bottomMargin: GUISetting.navi_list_bottom_margin

        delegate : Item{

            width: parent.width; height: exBtnValve.height + exBtnSensor.height + exBtnPressControl.height + exBtnInterface.height + exBtnTools.height + exBtnNCPA.height + exBtnAdvencedTool.height + exBtnHelp.height;

            NExButton{
                id : exBtnValve
                anchors.top: parent.top

                titleText.text: qsTr("Valve")
                expendHeight : titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height

                enabled: panel.isConnected

                NExButtonItem{
                    id : menuValveIdentification
                    anchors.bottom: menuValveSetup.top
                    text.text: qsTr("Identification")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickValveIdentification()}
                }

                NExButtonItem{
                    id : menuValveSetup
                    anchors.bottom: menuValveCycleCounter.top
                    text.text: qsTr("Setup")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickValveSetup()}
                }

                NExButtonItem{
                    id : menuValveCycleCounter
                    anchors.bottom: menuValvePowerFailStatus.top
                    text.text: qsTr("Cycle counter")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickValveCycleCounter()}
                }

                NExButtonItem{
                    id : menuValvePowerFailStatus
                    anchors.bottom: menuValveParameters.top
                    text.text: qsTr("Power Fail Status")
                    enabled: panel.isConnected && panel.isSupportPFO && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickValvePowerFailStatus()}
                }

                NExButtonItem{
                    id : menuValveParameters
                    anchors.bottom: menuValveRecovery.top
                    text.text: qsTr("Parameters")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickValveParameters()}
                }

                NExButtonItem{
                    id : menuValveRecovery
                    anchors.bottom: menuValveCariblation.top
                    text.text: qsTr("Recovery")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: {panel.clickValveRecovery()}
                }

                NExButtonItem{
                    id : menuValveCariblation
                    anchors.bottom: parent.bottom
                    text.text: qsTr("ADC calibration")
                    enabled: panel.isConnected /*&& !isZeroEnable*/ && !GlobalUiValue.disableWinCreateBtn

                    onClicked: {var popup = passwordDlg.createObject(window); popup.caller = menuValveCariblation; popup.open();}

                    function confirm()
                    {
                        panel.clickValveCailbration()
                    }
                }
            }

            NExButton{
                id : exBtnSensor
                anchors.top: exBtnValve.bottom;
                enabled: panel.isConnected

                titleText.text: qsTr("Sensor")
                expendHeight : titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height // NExButtonItem height is 18

                NExButtonItem{
                    id : menuSensorSetup
                    anchors.bottom: menuSensorAnalysis.top
                    text.text: qsTr("Setup")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickSensorSetup() }
                }

                NExButtonItem{
                    id : menuSensorAnalysis
                    anchors.bottom: parent.bottom
                    text.text: qsTr("Analysis")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickSensorAnalysis() }
                }

                /*
                NExButtonItem{
                    id : menuSensorZero
                    anchors.bottom: menuSensorAnalysis.top
                    text.text: qsTr("Zero")
                }
                NExButtonItem{
                    id : menuSensorAnalysis
                    anchors.bottom: menuSensorSimulation.top
                    text.text: qsTr("Analysis")
                }
                NExButtonItem{
                    id : menuSensorSimulation
                    anchors.bottom: parent.bottom
                    text.text: qsTr("Simulation")
                }
                */
            }

            NExButton{
                id : exBtnPressControl
                anchors.top: exBtnSensor.bottom;

                titleText.text: qsTr("Pressure control")
                expendHeight : isApSysCtrlMonitor ? titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height  : titleBox.height + (children.length - 2) * GUISetting.exbtnitem_height // NExButtonItem height is 18

                NExButtonItem{
                    id : menuPressControlSetup
                    anchors.bottom: menuPressControlAdvanSetup.top
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn
                    text.text: qsTr("Setup")

                    onClicked: { panel.clickPressureCtrlSetup() }
                }

                NExButtonItem{
                    id : menuPressControlAdvanSetup
                    anchors.bottom: menuPressControlLearnParam.top
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn
                    text.text: qsTr("Advanced Setup")

                    onClicked: { panel.clickPressureCtrlAdvanSetup()}
                }

                NExButtonItem{
                    id : menuPressControlLearnParam
                    anchors.bottom: menuPressControlLearnList.top
                    text.text: qsTr("Learn parameter")
                    enabled : !GlobalUiValue.disableWinCreateBtn
                    onClicked: { panel.clickPressureCtrlLearnParam() }
                }
                NExButtonItem{
                    id : menuPressControlLearnList
                    anchors.bottom: panel.isApSysCtrlMonitor ? menuPressCtrlGainMonitor.top : parent.bottom
                    text.text: qsTr("Learn list")
                    enabled : panel.isConnected && !GlobalUiValue.disableWinCreateBtn
                    onClicked: { panel.clickPressureCtrlLearnList() }
                }
                NExButtonItem{
                    id : menuPressCtrlGainMonitor
                    visible: panel.isApSysCtrlMonitor
                    anchors.bottom: parent.bottom
                    text.text: qsTr("Monitoring gain")
                    enabled : panel.isConnected && !GlobalUiValue.disableWinCreateBtn
                    onClicked: { panel.clickPressureCtrlGainMointoring() }
                }
            }

            NExButton{
                id : exBtnInterface
                anchors.top: exBtnPressControl.bottom;
                enabled: panel.isConnected

                titleText.text: qsTr("Interface")
                expendHeight : titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height // NExButtonItem height is 18

                NExButtonItem{
                    id : menuInterfaceSetup
                    anchors.bottom: menuInterfaceStatus.top
                    text.text: qsTr("Setup")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked:{ panel.clickInterfaceSetup() }
                }
                NExButtonItem{
                    id : menuInterfaceStatus
                    anchors.bottom: menuInterfaceTrace.top
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn
                    text.text: qsTr("Status")

                    onClicked:{ panel.clickInterfaceStatus() }
                }

                NExButtonItem{
                    id : menuInterfaceTrace
                    anchors.bottom: parent.bottom
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn
                    text.text: qsTr("Trace")

                    onClicked:{ panel.clickInterfaceTrace() }
                }
            }

            NExButton{
                id : exBtnTools
                anchors.top: exBtnInterface.bottom;
                //enabled: panel.isConnected

                titleText.text: qsTr("Tools")
                expendHeight : titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height // NExButtonItem height is 18

                NExButtonItem{
                    id : menuToolsChartAnalyzer
                    anchors.bottom: menuToolsSequencer.top
                    text.text: qsTr("Chart analyzer")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked:{ panel.clickToolChartAnalyzer() }
                }
                NExButtonItem{
                    id : menuToolsSequencer
                    anchors.bottom: menuToolsFU.top
                    text.text: qsTr("Sequencer")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn
                    isOn : panel.isRunSequencer
                    onClicked:{ panel.clickToolSequencer() }
                }

                NExButtonItem{
                    id : menuToolsFU
                    anchors.bottom: parent.bottom
                    text.text: qsTr("Firmware update")
                    enabled: !GlobalUiValue.disableWinCreateBtn
                    visible: true
                    onClicked:{ panel.clickToolFuSelectMethod() }
                }

                //NExButtonItem{
                //    id : menuToolsFUNet
                //    anchors.bottom: parent.bottom
                //    text.text: qsTr("FU (network)")
                //    enabled: !GlobalUiValue.disableWinCreateBtn
                //    visible: true
                //    onClicked:{ panel.clickToolFirmwareUpdateViaNet() }
                //}
            }


            NExButton{
                id : exBtnNCPA
                anchors.top: exBtnTools.bottom;
                enabled: panel.isConnected

                titleText.text: qsTr("NVM")
                expendHeight : titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height // NExButtonItem height is 18

                NExButtonItem{
                    id : menuNCPASetting
                    anchors.bottom: parent.bottom
                    text.text: qsTr("Settings")
                    enabled: panel.isConnected && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickNCPASettings() }
                }
            }

            NExButton{
                id : exBtnAdvencedTool
                anchors.top: exBtnNCPA.bottom;

                titleText.text: qsTr("Advanced tool")
                expendHeight : titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height // NExButtonItem height is 18

                NExButtonItem{
                    id : menuTest
                    anchors.bottom: menuBackupNRestore.top
                    text.text: qsTr("Test")
                    enabled: !GlobalUiValue.disableWinCreateBtn

                    onClicked: { var popup = passwordDlg.createObject(window); popup.caller = menuTest; popup.open();}

                    function confirm()
                    {
                        panel.clickAdvToolTest()
                    }
                }

                NExButtonItem{
                    id : menuBackupNRestore
                    anchors.bottom: menuDiskHoriCalib.top
                    text.text: qsTr("Backup and resotore")
                    enabled: !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickAdvBackupNRestore()}
                }

                NExButtonItem{
                    id : menuDiskHoriCalib
                    anchors.bottom: parent.bottom
                    text.text: qsTr("Disk Horizontal calib")
                    enabled: !GlobalUiValue.disableWinCreateBtn


                    onClicked: { panel.clickAdvDiskHoriCalibration()}
                }
            }

            NExButton{
                id : exBtnHelp
                anchors.top: exBtnAdvencedTool.bottom;

                titleText.text: qsTr("Help")
                expendHeight : titleBox.height + (children.length - 1) * GUISetting.exbtnitem_height // NExButtonItem height is 18

                /*NExButtonItem{
                    id : menuHelpOperatingManual
                    anchors.bottom: menuHelpAbout.top
                    text.text: qsTr("Operating manual")
                }*/
                NExButtonItem{
                    id : menuHelpAbout
                    anchors.bottom: parent.bottom
                    text.text: qsTr("About")
                    enabled: panel.company !== ValveEnumDef.COMPANY_NONE && !GlobalUiValue.disableWinCreateBtn

                    onClicked: { panel.clickHelpAbout() }
                }
                /*NExButtonItem{
                    id : menuHelpVisitNovasen
                    anchors.bottom: parent.bottom
                    text.text: qsTr("Visit NOVASEN")
                }*/
            }
        }
    }

    Image{
        id : logoImg
        anchors.left: navigatelist.left; anchors.leftMargin: 20; anchors.right: navigatelist.right; anchors.rightMargin: 20; anchors.bottom: parent.bottom; anchors.bottomMargin: panel.company !== ValveEnumDef.COMPANY_NONE ? 20 : 0
        source: (panel.company === ValveEnumDef.COMPANY_NOVA) || (panel.company === ValveEnumDef.COMPANY_APSYS) ? "/image/img_novasen_ex.png" : "/image/img_soao.png"
        fillMode: Image.PreserveAspectFit
        height: panel.company == ValveEnumDef.COMPANY_NONE ? 0 : undefined //panel.isLogoVisible ? undefined : 0
    }

    Component{
        id : passwordDlg
        PasswordDlg
        {
            onResult: { caller.confirm() }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
