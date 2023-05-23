import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import GUISetting 1.0
import FirmwareUpdateViaNetworkDlgModel 1.0
import FirmwareUpdateViaNetworkUiStepDef 1.0

NWindow{
    id : nwindow

    property var titleText : qsTr("Firmware update")

    function showErrMessage(msg)
    {
        var popup = messageBox.createObject(nwindow)
        popup.titleText = qsTr("Error")
        popup.contentText = msg
        popup.msgIcon.source = "/image/icon-alret.png"
        popup.open();
    }

    FirmwareUpdateViaNetworkDlgModel{
        id : dlgModel

        Component.onCompleted: {
            comportCombo.displayText = onCommandGetSelComPort()
        }
    }

    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    Item {
        id : contentContainer
        height: titleBox.height + body.height; width: body.width
        anchors.centerIn: parent

        NPopupTilte{
            id : titleBox
            root : nwindow
            title: nwindow.titleText
            enableMinimizeBtn: true

            onClickClose: {
                if(dlgModel.mDFUStep > FirmwareUpdateViaNetworkUiStepDef.START_UPDATE && dlgModel.mDFUStep < FirmwareUpdateViaNetworkUiStepDef.COMPLETE)
                    showErrMessage(qsTr("can not close in updating"))
                else
                    close()
            }

            onClickMinimized: {
                nwindow.showMinimized()
            }
        }

        Rectangle{
            id : body
            height: (GUISetting.line_margin + selComItem.height) + (GUISetting.line_margin + selFileItem.height) + (GUISetting.line_margin + statusItem.height) + GUISetting.line_margin ; width: 500 * GUISetting.scale
            anchors.left: parent.left; anchors.top: titleBox.bottom

            color : "#E4E4E4"

            Rectangle{
                id : selComItem

                height: (GUISetting.margin + selComTitle.height) + (GUISetting.margin + comportCombo.height) + GUISetting.margin;
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : selComTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Select comport")
                }

                NComboBox{
                    id : comportCombo
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: selComTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;

                    //model : ["1", "2"]
                    model : ListModel{
                        id : comportModel
                    }

                    onPressedChanged: {
                        var count = 0;
                        comportModel.clear()

                        dlgModel.onCommandSearchComPort()

                        count = dlgModel.onCommandGetComPortCount()

                        for(var i = 0; i < count; i ++)
                        {
                            var itemText = dlgModel.onCommandGetComPortName(i)

                            comportModel.append({"modelData":itemText})
                        }
                    }

                    onCurrentTextChanged: {
                        if(currentText !== "")
                            displayText  = currentText
                    }
                }
            }

            Rectangle{
                id : selFileItem

                height: (GUISetting.margin + selFileTitle.height)
                        + (GUISetting.margin + cpu1KernelLabel.height)
                        + (GUISetting.margin + cpu2KernelLabel.height)
                        + (GUISetting.margin + cpu1AppLabel.height)
                        + (GUISetting.margin + cpu2AppLabel.height) + GUISetting.margin;
                anchors.top: selComItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : selFileTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Download status")
                }

                NText{
                    id : cpu1KernelLabel
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: selFileTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    verticalAlignment: Text.AlignVCenter
                    text : qsTr("cpu1 kernel file")
                }

                Rectangle{
                    height: 24 * GUISetting.scale;
                    anchors.verticalCenter: cpu1KernelLabel.verticalCenter; anchors.left: cpu1KernelLabel.right; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    Rectangle{
                        height: 24 * GUISetting.scale; width: parent.width * dlgModel.mFtpProgressCpu1Kernel
                        anchors.left: parent.left;

                        color : "#24A7FF"
                    }
                }

                NText{
                    id : cpu2KernelLabel
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: cpu1KernelLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    verticalAlignment: Text.AlignVCenter
                    text : qsTr("cpu2 kernel file")
                }

                Rectangle{
                    height: 24 * GUISetting.scale;
                    anchors.verticalCenter: cpu2KernelLabel.verticalCenter; anchors.left: cpu2KernelLabel.right; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    Rectangle{
                        height: 24 * GUISetting.scale; width: parent.width * dlgModel.mFtpProgressCpu2Kernel
                        anchors.left: parent.left;

                        color : "#24A7FF"
                    }
                }

                NText{
                    id : cpu1AppLabel
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: cpu2KernelLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    verticalAlignment: Text.AlignVCenter
                    text : qsTr("cpu1 App file")
                }

                Rectangle{
                    height: 24 * GUISetting.scale;
                    anchors.verticalCenter: cpu1AppLabel.verticalCenter; anchors.left: cpu1AppLabel.right; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    Rectangle{
                        height: 24 * GUISetting.scale; width: parent.width * dlgModel.mFtpProgressCpu1App
                        anchors.left: parent.left;

                        color : "#24A7FF"
                    }
                }

                NText{
                    id : cpu2AppLabel
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: cpu1AppLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    verticalAlignment: Text.AlignVCenter
                    text : qsTr("cpu2 App file")
                }

                Rectangle{
                    height: 24 * GUISetting.scale;
                    anchors.verticalCenter: cpu2AppLabel.verticalCenter; anchors.left: cpu2AppLabel.right; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    color: "#E4E4E4"

                    Rectangle{
                        height: 24 * GUISetting.scale; width: parent.width * dlgModel.mFtpProgressCpu2App
                        anchors.left: parent.left;

                        color : "#24A7FF"
                    }
                }
            }

            Rectangle{
                id : statusItem

                height: (GUISetting.margin + statusTitle.height + GUISetting.margin) + (60 * GUISetting.scale) + GUISetting.margin;
                anchors.top: selFileItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;  anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : statusTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Note")
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep == FirmwareUpdateViaNetworkUiStepDef.DISCONNECT_CABLE

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("1.Disconnect the service cable (1/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;

                        text.text: qsTr("Next")

                        onClick: {
                            dlgModel.onCommandNext()
                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CONNECT_ADAPTER

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("2.Connect the download adapter to the service port (2/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;

                        text.text: qsTr("Next")

                        onClick: {
                            dlgModel.onCommandNext()
                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CONNECT_CABLE

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("3.Connect the service cable to the download adapter (3/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;

                        text.text: qsTr("Next")

                        onClick: {
                            dlgModel.onCommandNext()
                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep == FirmwareUpdateViaNetworkUiStepDef.REBOOT_VALVE

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("4.If the valve is powered on, power cycle it.If not, turn it on.(4/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;

                        text.text: qsTr("Next")

                        onClick: {
                            dlgModel.onCommandNext()
                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.DOWNLOAD_FILE

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("5.Downloading firmware file. (5/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;
                        enabled : false

                        text.text: qsTr("Next")

                        onClick: {
                            //dlgModel.onCommandNext()
                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.START_UPDATE

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("6.Start firmware update (6/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;

                        text.text: qsTr("Update")

                        onClick: {
                            dlgModel.onCommandUpdate(comportCombo.displayText)
                        }
                    }
                }

//                Item{
//                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

//                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.REBOOT_SCI_MODE

//                    NText{
//                        anchors.verticalCenter: parent.verticalCenter
//                        text : qsTr("6.Rebooting for firmware download (6/17)")
//                    }
//                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CONNECT_SERIAL

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("7.Connecting to valve (7/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU1_DN_KERNEL

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("8.CPU 1 - Download kernel (8/17)")
                    }

                    Rectangle{
                        height: 10 * GUISetting.scale
                        anchors.left:parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom;

                        color: "#ACACAC"

                        Rectangle{
                            height: parent.height - (2 * GUISetting.line_margin);
                            width: (dlgModel.mPercentCpu1Kernel/100) * (parent.width - (2 * GUISetting.line_margin))

                            anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.verticalCenter: parent.verticalCenter

                            color: "#24A7FF"

                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU1_ERASE

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("9.CPU 1 - Erase (9/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU1_DN_APP

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("10.CPU 1 - Download application (10/17)")
                    }

                    Rectangle{
                        height: 10 * GUISetting.scale
                        anchors.left:parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom;

                        color: "#ACACAC"

                        Rectangle{
                            height: parent.height - (2 * GUISetting.line_margin);
                            width: (dlgModel.mPercentCpu1App/100) * (parent.width - (2 * GUISetting.line_margin))

                            anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.verticalCenter: parent.verticalCenter

                            color: "#24A7FF"

                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU1_VERIFY

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("11.CPU 1 - Verify (11/17)")
                    }

                    Rectangle{
                        height: 10 * GUISetting.scale
                        anchors.left:parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom;

                        color: "#ACACAC"

                        Rectangle{
                            height: parent.height - (2 * GUISetting.line_margin);
                            width: (dlgModel.mPercentCpu1Verify/100) * (parent.width - (2 * GUISetting.line_margin))

                            anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.verticalCenter: parent.verticalCenter

                            color: "#24A7FF"

                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU1_RESET

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("12.CPU 1 - Reset (12/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU2_DN_KERNEL

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("13.CPU 2 - Download kernel (13/17)")
                    }

                    Rectangle{
                        height: 10 * GUISetting.scale
                        anchors.left:parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom;

                        color: "#ACACAC"

                        Rectangle{
                            height: parent.height - (2 * GUISetting.line_margin);
                            width: (dlgModel.mPercentCpu2Kernel/100) * (parent.width - (2 * GUISetting.line_margin))

                            anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.verticalCenter: parent.verticalCenter

                            color: "#24A7FF"

                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU2_ERASE

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("14.CPU 2 - Erase (14/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU2_DN_APP

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("15.CPU 2 - Download application (15/17)")
                    }

                    Rectangle{
                        height: 10 * GUISetting.scale
                        anchors.left:parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom;

                        color: "#ACACAC"

                        Rectangle{
                            height: parent.height - (2 * GUISetting.line_margin);
                            width: (dlgModel.mPercentCpu2App/100) * (parent.width - (2 * GUISetting.line_margin))

                            anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.verticalCenter: parent.verticalCenter

                            color: "#24A7FF"

                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU2_VERIFY

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("16.CPU 2 - Verify (16/17)")
                    }

                    Rectangle{
                        height: 10 * GUISetting.scale
                        anchors.left:parent.left; anchors.right: parent.right; anchors.bottom: parent.bottom;

                        color: "#ACACAC"

                        Rectangle{
                            height: parent.height - (2 * GUISetting.line_margin);
                            width: (dlgModel.mPercentCpu2Verify/100) * (parent.width - (2 * GUISetting.line_margin))

                            anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.verticalCenter: parent.verticalCenter

                            color: "#24A7FF"

                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.CPU2_RESET

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("17.CPU 2 - Reset (17/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateViaNetworkUiStepDef.COMPLETE

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("Finish<br>Disconnect the download adapter and reboot the valve")

                        visible: dlgModel.mErrMsg === ""
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : dlgModel.mErrMsg

                        visible: dlgModel.mErrMsg !== ""
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;

                        text.text: dlgModel.mErrMsg === "" ? qsTr("Finish") : qsTr("Confirm")

                        onClick: {
                            close()
                        }
                    }
                }
            }
        }
    }

    //
    //FileDialog{
    //    property int selCpu : -1
    //
    //    id: rFileDialog
    //    title: qsTr("select file")
    //    //folder: "./"
    //    fileMode: FileDialog.OpenFile
    //    nameFilters: ["Text files (*.txt)"]
    //
    //    onAccepted: {
    //        if(selCpu == 1)
    //            cpu1KernelFileText.textField.text = currentFile.toString().split("///")[1]
    //        else if(selCpu == 2)
    //            cpu1AppFileText.textField.text = currentFile.toString().split("///")[1]
    //        if(selCpu == 3)
    //            cpu2KernelFileText.textField.text = currentFile.toString().split("///")[1]
    //        else if(selCpu == 4)
    //            cpu2AppFileText.textField.text = currentFile.toString().split("///")[1]
    //    }
    //    onRejected: {
    //    }
    //    visible : false
    //}

    Component{
        id : messageBox
        NMessageBox{

        }
    }
}

/*

*/
