import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import GUISetting 1.0
import FirmwareUpdateExDlgModel 1.0

NWindow{
    id : nwindow

    property var titleText : qsTr("Firmware update")
    property string method : ""
    property int step : 0

    signal clickRestoreSettings()

    function showMessage(msg)
    {
        var popup = messageBox.createObject(nwindow)
        popup.contentText = msg
        popup.open();
    }

    onMethodChanged: {
        console.debug("[debug_khko]" + nwindow.method)

        if(nwindow.method == "network")
        {
            versionCombo.displayText = "LASTEST"
            dlgModel.onCommandSearchVersion();
        }
    }

    FirmwareUpdateExDlgModel{
        id : dlgModel

        onSignalEventResultUpdate: {
            console.debug("bErr = " + bErr + ", errMsg = " + errMsg)
            if(bErr)
            {
                showMessage("Error message : " + errMsg)
            }
            else
            {
                showMessage("The firmware has been successfully written to the valve.")
                step = step + 1;
            }
        }

        onSignalEventResultSearchVer: {
            var count = 0;
            versionModel.clear()

            count = dlgModel.onCommandGetVersionCount()

            for(var i = 0; i < count; i ++)
            {
                var itemText = dlgModel.onCommandGetVersionName(i)

                versionModel.append({"modelData":itemText})
            }
        }

        Component.onCompleted: {
            comportCombo.displayText = dlgModel.onCommandGetSelComPort()
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
                if(dlgModel.mIsUpdating)
                    showMessage(qsTr("can not close in updating"))
                else
                    close()
            }

            onClickMinimized: {
                nwindow.showMinimized()
            }
        }

        Rectangle{
            id : body
            height: (GUISetting.line_margin + stepItem.height) + (GUISetting.line_margin + contentItem.height) + GUISetting.line_margin ; width: 500 * GUISetting.scale
            anchors.left: parent.left; anchors.top: titleBox.bottom

            color : "#E4E4E4"

            Rectangle{
                id : stepItem

                height: (GUISetting.margin + stepTitle.height) + (GUISetting.margin + stepProgressBox.height) + GUISetting.margin;
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : stepTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Step")
                }

                Row{
                    id : stepProgressBox
                    height: 24 * GUISetting.scale
                    anchors.top: stepTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.horizontalCenter: parent.horizontalCenter

                    spacing: 5 * GUISetting.scale

                    Rectangle{ height: parent.height; width: height * 2; color: nwindow.step >= 0 ? "#24A7FF" : "#ACACAC"; NText{ anchors.centerIn: parent; isBold: true; text : qsTr("1")}}
                    NText{ anchors.verticalCenter: parent.verticalCenter; isBold: true; text : qsTr("→")}
                    Rectangle{ height: parent.height; width: height * 2; color: nwindow.step >= 1 ? "#24A7FF" : "#ACACAC"; NText{ anchors.centerIn: parent; isBold: true; text : qsTr("2")}}
                    NText{ anchors.verticalCenter: parent.verticalCenter; isBold: true; text : qsTr("→")}
                    Rectangle{ height: parent.height; width: height * 2; color: nwindow.step >= 2 ? "#24A7FF" : "#ACACAC"; NText{ anchors.centerIn: parent; isBold: true; text : qsTr("3")}}
                    NText{ anchors.verticalCenter: parent.verticalCenter; isBold: true; text : qsTr("→")}
                    Rectangle{ height: parent.height; width: height * 2; color: nwindow.step >= 3 ? "#24A7FF" : "#ACACAC"; NText{ anchors.centerIn: parent; isBold: true; text : qsTr("4")}}
                    NText{ anchors.verticalCenter: parent.verticalCenter; isBold: true; text : qsTr("→")}
                    Rectangle{ height: parent.height; width: height * 2; color: nwindow.step >= 4 ? "#24A7FF" : "#ACACAC"; NText{ anchors.centerIn: parent; isBold: true; text : qsTr("5")}}
                    NText{ anchors.verticalCenter: parent.verticalCenter; isBold: true; text : qsTr("→")}
                    Rectangle{ height: parent.height; width: height * 2; color: nwindow.step >= 5 ? "#24A7FF" : "#ACACAC"; NText{ anchors.centerIn: parent; isBold: true; text : qsTr("6")}}
                }
            }
            Rectangle{
                id : contentItem

                height: 400 * GUISetting.scale
                anchors.top: stepItem.bottom; anchors.topMargin: GUISetting.line_margin;
                anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                Item{
                    anchors.fill: parent

                    visible: step == 0

                    NScrollView{
                        id : readyNoteBox
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: btnNextInReady.top; anchors.bottomMargin: GUISetting.margin;

                        onContentHeightChanged: {
                            positionViewAtBeginning()
                        }

                        delegate : Column{
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;
                            spacing: GUISetting.margin

                            NText{
                                anchors.left: parent.left; anchors.right: parent.right;
                                isBold: true
                                text : qsTr("1. Connect the update adapter to the valve's service port.")
                            }

                            Image{
                                anchors.left: parent.left; anchors.right: parent.right;
                                source: "/image/fu_notice_ready01.png"
                                fillMode: Image.PreserveAspectFit
                            }

                            NText{
                                anchors.left: parent.left; anchors.right: parent.right;
                                isBold: true
                                text : qsTr("2. Set the boot mode switch to 'up'.")
                            }

                            Image{
                                anchors.left: parent.left; anchors.right: parent.right;
                                source: "/image/fu_notice_ready02.png"
                                fillMode: Image.PreserveAspectFit
                            }

                            NText{
                                anchors.left: parent.left; anchors.right: parent.right;
                                isBold: true
                                lineHeight: 2
                                text : qsTr("3. Click the reset button.<br>   (If the valve version is older than 'R006', turn the power off and on.)")
                            }

                            Image{
                                anchors.left: parent.left; anchors.right: parent.right;
                                source: "/image/fu_notice_ready03.png"
                                fillMode: Image.PreserveAspectFit
                            }
                        }
                    }

                    NButton{
                        id : btnNextInReady
                        height: 70 * GUISetting.scale; width: 160 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;
                        anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Next step")

                        onClick: {
                            if(comportCombo.displayText == "")
                                step = step + 1
                            else
                                step = step + 2
                        }
                    }
                }

                Item{
                    anchors.fill: parent

                    visible: step == 1

                    NText{
                        id : setPortTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text : qsTr("Select the COM port connected to the valve.")
                    }

                    NComboBox{
                        id : comportCombo
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.top: setPortTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;

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

                    NButton{
                        height: 70 * GUISetting.scale; width: 160 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;
                        anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;

                        enabled: comportCombo.displayText != ""

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Next step")

                        onClick: {
                            step = step + 1
                        }
                    }
                }

                Item{
                    anchors.fill: parent

                    visible: step == 2 && nwindow.method == "local"

                    NText{
                        id : selFileTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text : qsTr("Select firmware files.")
                    }

                    NInputText{
                        id : cpu1AppFileText
                        height: 24 * GUISetting.scale;
                        anchors.top: selFileTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: cpu1AppFileBtn.left; anchors.rightMargin: GUISetting.margin * 2
                    }

                    NButton{
                        id : cpu1AppFileBtn
                        height: 24 * GUISetting.scale; width: 130 * GUISetting.scale
                        anchors.verticalCenter: cpu1AppFileText.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2

                        text.text: qsTr("cpu1 App file")

                        onClick: {
                            rFileDialog.selCpu = 1
                            rFileDialog.open()
                        }
                    }

                    NInputText{
                        id : cpu2AppFileText
                        height: 24 * GUISetting.scale;
                        anchors.top: cpu1AppFileText.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: cpu2AppFileBtn.left; anchors.rightMargin: GUISetting.margin * 2
                    }

                    NButton{
                        id : cpu2AppFileBtn
                        height: 24 * GUISetting.scale; width: 130 * GUISetting.scale
                        anchors.verticalCenter: cpu2AppFileText.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2

                        text.text: qsTr("cpu2 App file")

                        onClick: {
                            rFileDialog.selCpu = 2
                            rFileDialog.open()
                        }
                    }

                    NButton{
                        height: 70 * GUISetting.scale; width: 160 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;
                        anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;

                        enabled: cpu1AppFileText.textField.text != "" && cpu2AppFileText.textField.text != ""
                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Update start")

                        onClick: {
                            dlgModel.onCommandUpdateFromLocal(comportCombo.displayText, cpu1AppFileText.textField.text, cpu2AppFileText.textField.text)

                            step = step + 1
                        }
                    }
                }

                Item{
                    anchors.fill: parent

                    visible: step == 2 && nwindow.method == "network"

                    NText{
                        id : selVerTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text : qsTr("Select version.")
                    }

                    NComboBox{
                        id : versionCombo
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.top: selVerTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;

                        enabled: dlgModel.mIsVersionProc == false
                        //model : ["1", "2"]
                        model : ListModel{
                            id : versionModel
                        }

                        //onPressedChanged: {
                        //    var count = 0;
                        //    count = dlgModel.onCommandGetVersionCount()
                        //
                        //    if(count == 0)
                        //        dlgModel.onCommandSearchVersion()
                        //}

                        onCurrentTextChanged: {
                            if(currentText !== "")
                                displayText  = currentText
                        }
                    }

                    NText{
                        anchors.verticalCenter: versionCombo.verticalCenter; anchors.left: versionCombo.right; anchors.leftMargin: GUISetting.margin
                        color: dlgModel.mIsErrVersion  ? "#FF0000" : "#24A7FF"
                        text:  dlgModel.mIsErrVersion  ? qsTr("Failed to get firmware version.") :
                               dlgModel.mIsVersionProc ? qsTr("Getting firmware version information.") : ""
                    }

                    NButton{
                        height: 70 * GUISetting.scale; width: 160 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;
                        anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;

                        enabled: nwindow.method == "network" && versionCombo.displayText != ""
                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Update start")

                        onClick: {
                            dlgModel.onCommandUpdateFromNetwork(comportCombo.displayText, versionCombo.displayText)
                            step = step + 1
                        }
                    }
                }

                Item{
                    anchors.fill: parent

                    visible: step == 3

                    NText{
                        id : updateStepTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text: dlgModel.mUpdateStep < 2 ? qsTr("preparing ") + "(" + (dlgModel.mUpdateStep + 1) + "/12)" : qsTr("writting ") + "(" + (dlgModel.mUpdateStep + 1) + "/12)"
                    }

                    Rectangle{
                        id : updateStepProgress
                        height: 24 * GUISetting.scale;
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        anchors.top: updateStepTitle.bottom; anchors.topMargin: GUISetting.line_margin
                        color : "#ACACAC";

                        Rectangle{
                            height: parent.height;
                            width: (parent.width * dlgModel.mUpdateProgress) / 100
                            color : "#24A7FF";
                        }
                    }

                    NText{
                        id : updateTotalStepTitle
                        anchors.top: updateStepProgress.bottom; anchors.topMargin: GUISetting.margin
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text: qsTr("Total")
                    }

                    RowLayout{
                        height: 24 * GUISetting.scale
                        anchors.top: updateTotalStepTitle.bottom; anchors.topMargin: GUISetting.line_margin
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                        spacing: 0

                        Rectangle{visible: nwindow.method == "network"; Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDnPctCpu1App    ) / 100; color : "#24A7FF"}}
                        Rectangle{visible: nwindow.method == "network"; Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDnPctCpu2App    ) / 100; color : "#24A7FF"}}
                        Rectangle{Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDFUPctCpu1Kernel) / 100; color : "#24A7FF"}}
                        Rectangle{Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDFUPctCpu1App   ) / 100; color : "#24A7FF"}}
                        Rectangle{Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDFUPctCpu1Verify) / 100; color : "#24A7FF"}}
                        Rectangle{Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDFUPctCpu2Kernel) / 100; color : "#24A7FF"}}
                        Rectangle{Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDFUPctCpu2App   ) / 100; color : "#24A7FF"}}
                        Rectangle{Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1; color : "#ACACAC"; Rectangle{height: parent.height; width: (parent.width * dlgModel.mDFUPctCpu2Verify) / 100; color : "#24A7FF"}}
                    }
                }

                Item{
                    anchors.fill: parent

                    visible: step == 4

                    NScrollView{
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.right: parent.right; anchors.bottom: btnNextInReboot.top; anchors.bottomMargin: GUISetting.margin;

                        onContentHeightChanged: {
                            positionViewAtBeginning()
                        }

                        delegate : Column{
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;
                            spacing: GUISetting.margin

                            NText{
                                anchors.left: parent.left; anchors.right: parent.right;
                                isBold: true
                                text : qsTr("1. Set the boot mode switch to 'nor'.")
                            }

                            Image{
                                anchors.left: parent.left; anchors.right: parent.right;
                                source: "/image/fu_notice_reboot01.png"
                                fillMode: Image.PreserveAspectFit
                            }

                            NText{
                                anchors.left: parent.left; anchors.right: parent.right;
                                isBold: true
                                lineHeight: 2
                                text : qsTr("2. Click the reset button.<br>   (If the valve version is older than 'R006', turn the power off and on.)")
                            }

                            Image{
                                anchors.left: parent.left; anchors.right: parent.right;
                                source: "/image/fu_notice_ready03.png"
                                fillMode: Image.PreserveAspectFit
                            }

                            NText{
                                anchors.left: parent.left; anchors.right: parent.right;
                                isBold: true
                                text : qsTr("3. Wait for reboot.")
                            }
                        }
                    }

                    NButton{
                        id : btnNextInReboot
                        height: 70 * GUISetting.scale; width: 160 * GUISetting.scale
                        anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin;
                        anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Next step")

                        onClick: {
                            if(dlgModel.mIsReboot == false)
                            {
                                showMessage(qsTr("After rebooting the valve,<br>wait for the reboot to complete."))
                                return;
                            }

                            step = step + 1
                        }
                    }
                }

                Item{
                    anchors.fill: parent

                    visible: step == 5

                    Column{
                        width: parent.width * 0.5;
                        anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                        spacing: GUISetting.margin

                        NButton{
                            id : btnRestore
                            height: 70 * GUISetting.scale; width: parent.width

                            text.text: qsTr("Restore settings")

                            onClick: {
                                nwindow.clickRestoreSettings()
                                close()
                            }
                        }

                        NButton{
                            id : btnFactoryReset
                            height: 70 * GUISetting.scale; width: parent.width

                            text.text: qsTr("Factory reset")

                            onClick: {
                                dlgModel.onCommandFactoryReset()
                                close()
                            }
                        }

                        NButton{
                            id : btnExit
                            height: 70 * GUISetting.scale; width: parent.width

                            bgColor: "#24A7FF"
                            text.color: "#FFFFFF"
                            text.text: qsTr("Exit")

                            onClick: {
                                close()
                            }
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
                cpu1AppFileText.textField.text = currentFile.toString().split("///")[1]
            else if(selCpu == 2)
                cpu2AppFileText.textField.text = currentFile.toString().split("///")[1]
        }
        onRejected: {
        }
        visible : false
    }

    Component{
        id : messageBox
        NConfirmMsgBox{
            contentWidth: 400 * GUISetting.scale
        }
    }
}
