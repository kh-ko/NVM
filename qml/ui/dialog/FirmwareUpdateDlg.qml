import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import GUISetting 1.0
import FirmwareUpdateDlgModel 1.0
import FirmwareUpdateUiStepDef 1.0

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

    FirmwareUpdateDlgModel{
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
                if(dlgModel.mDFUStep > FirmwareUpdateUiStepDef.START_UPDATE && dlgModel.mDFUStep < FirmwareUpdateUiStepDef.COMPLETE)
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
                        + (GUISetting.margin + cpu1KernelFileText.height)
                        + (GUISetting.margin + cpu1AppFileText.height)
                        + (GUISetting.margin + cpu2KernelFileText.height)
                        + (GUISetting.margin + cpu2AppFileText.height) + GUISetting.margin;
                anchors.top: selComItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : selFileTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Select firmware files")
                }

                NInputText{
                    id : cpu1KernelFileText
                    height: 24 * GUISetting.scale;
                    anchors.top: selFileTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: cpu1KernelFileBtn.left; anchors.rightMargin: GUISetting.margin * 2
                    enabled: dlgModel.mCpu1KernelFile == "" ? true : false
                    textField.text : dlgModel.mCpu1KernelFile
                }

                NButton{
                    id : cpu1KernelFileBtn
                    height: 24 * GUISetting.scale; width: 130 * GUISetting.scale
                    anchors.verticalCenter: cpu1KernelFileText.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2

                    enabled: dlgModel.mCpu1KernelFile == "" ? true : false

                    text.text: qsTr("cpu1 kernel file")

                    onClick: {
                        rFileDialog.selCpu = 1
                        rFileDialog.open()
                    }
                }

                NInputText{
                    id : cpu1AppFileText
                    height: 24 * GUISetting.scale;
                    anchors.top: cpu1KernelFileText.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: cpu1AppFileBtn.left; anchors.rightMargin: GUISetting.margin * 2
                }

                NButton{
                    id : cpu1AppFileBtn
                    height: 24 * GUISetting.scale; width: 130 * GUISetting.scale
                    anchors.verticalCenter: cpu1AppFileText.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2

                    text.text: qsTr("cpu1 App file")

                    onClick: {
                        rFileDialog.selCpu = 2
                        rFileDialog.open()
                    }
                }

                NInputText{
                    id : cpu2KernelFileText
                    height: 24 * GUISetting.scale;
                    anchors.top: cpu1AppFileText.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: cpu2KernelFileBtn.left; anchors.rightMargin: GUISetting.margin * 2
                    enabled: dlgModel.mCpu2KernelFile == "" ? true : false
                    textField.text : dlgModel.mCpu2KernelFile
                }

                NButton{
                    id : cpu2KernelFileBtn
                    height: 24 * GUISetting.scale; width: 130 * GUISetting.scale
                    anchors.verticalCenter: cpu2KernelFileText.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2
                    enabled: dlgModel.mCpu2KernelFile == "" ? true : false

                    text.text: qsTr("cpu2 kernel file")

                    onClick: {
                        rFileDialog.selCpu = 3
                        rFileDialog.open()
                    }
                }

                NInputText{
                    id : cpu2AppFileText
                    height: 24 * GUISetting.scale;
                    anchors.top: cpu2KernelFileText.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: cpu2AppFileBtn.left; anchors.rightMargin: GUISetting.margin * 2
                }

                NButton{
                    id : cpu2AppFileBtn
                    height: 24 * GUISetting.scale; width: 130 * GUISetting.scale
                    anchors.verticalCenter: cpu2AppFileText.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2

                    text.text: qsTr("cpu2 App file")

                    onClick: {
                        rFileDialog.selCpu = 4
                        rFileDialog.open()
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

                    visible: dlgModel.mDFUStep == FirmwareUpdateUiStepDef.DISCONNECT_CABLE

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CONNECT_ADAPTER

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CONNECT_CABLE

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

                    visible: dlgModel.mDFUStep == FirmwareUpdateUiStepDef.REBOOT_VALVE

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("1.Reboot the valve (4/17)")
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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.SELECT_FILE_PORT

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("4.Select this firmeware files and connected port (5/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;
                        enabled : comportCombo.displayText !== ""
                                 && cpu1KernelFileText.textField.text !== ""
                                 && cpu1AppFileText.textField.text !== ""
                                 && cpu2KernelFileText.textField.text !== ""
                                 && cpu2AppFileText.textField.text !== ""

                        text.text: qsTr("Next")

                        onClick: {
                            dlgModel.onCommandNext()
                        }
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.START_UPDATE

                    NText{
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top;
                        text : qsTr("5.Start firmware update (6/17)")
                    }

                    NButton{
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.right: parent.right;

                        text.text: qsTr("Update")

                        onClick: {
                            dlgModel.onCommandUpdate(comportCombo.displayText, cpu1KernelFileText.textField.text, cpu1AppFileText.textField.text, cpu2KernelFileText.textField.text, cpu2AppFileText.textField.text)
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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CONNECT_SERIAL

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("7.Connecting to valve (7/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU1_DN_KERNEL

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU1_ERASE

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("9.CPU 1 - Erase (9/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU1_DN_APP

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU1_VERIFY

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU1_RESET

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("12.CPU 1 - Reset (12/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU2_DN_KERNEL

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU2_ERASE

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("14.CPU 2 - Erase (14/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU2_DN_APP

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU2_VERIFY

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

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.CPU2_RESET

                    NText{
                        anchors.verticalCenter: parent.verticalCenter
                        text : qsTr("17.CPU 2 - Reset (17/17)")
                    }
                }

                Item{
                    anchors.top: statusTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    visible: dlgModel.mDFUStep === FirmwareUpdateUiStepDef.COMPLETE

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

    FileDialog{
        property int selCpu : -1

        id: rFileDialog
        title: qsTr("select file")
        //folder: "./"
        fileMode: FileDialog.OpenFile
        nameFilters: ["Text files (*.txt)"]

        onAccepted: {
            if(selCpu == 1)
                cpu1KernelFileText.textField.text = currentFile.toString().split("///")[1]
            else if(selCpu == 2)
                cpu1AppFileText.textField.text = currentFile.toString().split("///")[1]
            if(selCpu == 3)
                cpu2KernelFileText.textField.text = currentFile.toString().split("///")[1]
            else if(selCpu == 4)
                cpu2AppFileText.textField.text = currentFile.toString().split("///")[1]
        }
        onRejected: {
        }
        visible : false
    }

    Component{
        id : messageBox
        NMessageBox{

        }
    }
}

/*

*/
