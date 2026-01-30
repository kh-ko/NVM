import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import PressureCtrlLearnParamDlgModel 1.0
import PressureCtrlLearnParamItemModel 1.0
import GUISetting 1.0

NWindow{
    id : dialog

    property var titleText   : qsTr("Learn parameters")
    property var progress    : dlgModel.mProgress
    property var strStatus   : dlgModel.mStrStatus
    property var errMsg      : dlgModel.mErrMsg
    property var errMsg2     : dlgModel.mErrMsg2
    property var access      : dlgModel.mAccessMode
    property var isRS232Test : dlgModel.mIsRS232Test
    property var isEdit      : false
    property var connectInfo : ""
    property var valveID     : ""
    property var isCloseAtComplete : false

    function openChangeAccessDlgForReset()
    {
        var popup = changeAccessDlg.createObject(dialog)
        popup.caller = interfaceReset
        popup.open();
    }

    function openChangeAccessDlg()
    {
        var popup = changeAccessDlg.createObject(dialog)
        popup.caller = interfaceController
        popup.open();
    }

    function openCloseConfirmDlg()
    {
        var popup = closeConfirmDlg.createObject(dialog)
        popup.caller = interfaceFile
        popup.open();
    }

    function openProgressConfirmDlg()
    {
        var popup = progressConfirmDlg.createObject(dialog)
        popup.caller = dialog
        popup.open();
    }

    function showErrMessage(msg)
    {
        var popup = messageBox.createObject(dialog)
        popup.titleText = qsTr("Error")
        popup.contentText = msg
        popup.msgIcon.source = "/image/icon-alret.png"
        popup.open();
    }

    Item{
        id : interfaceController

        function commit()
        {
            dlgModel.onCommandWriteToController()
        }

        function read()
        {
            dlgModel.onCommandReadFromController()
        }

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit();
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }

        function apply()
        {
            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
            {
                openChangeAccessDlg()
                return;
            }

            commit()
        }
    }

    Item{
        id : interfaceFile

        property var filePath : ""

        function apply()
        {
            wFileDialog.open();
        }

        function setClose(isClose)
        {
            dialog.isCloseAtComplete = isClose
        }

        function read()
        {
            rFileDialog.open()
        }

        function close()
        {
            dialog.close();
        }
    }

    Item{
        id : interfaceReset

        function commit()
        {
            dlgModel.onCommandWriteReset()
        }

        function onResultChangeAccess(value)
        {
            if(value)
            {
                commit();
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }

        function apply()
        {
            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
            {
                openChangeAccessDlg()
                return;
            }

            commit()
        }
    }

    PressureCtrlLearnParamDlgModel{
        id : dlgModel

        Component.onCompleted: {
            for(var idx = 0; idx < 104;  idx++)
            {
                itemModel.append({"idxValue":idx})
            }
        }

        onSignalEventProcIdx: {
            paramListView.positionViewAtIndex(idx, ListView.Center)

            if(idx == 0)
            {
                graphView.clear()
            }

            if(idx == 100)
            {
                var maxYValue = 0;
                var yValue    = 0;
                var item

                for(var paramIdx = 0; paramIdx < 101;  paramIdx++)
                {
                    item = dlgModel.onCommandGetParamItem(paramIdx)
                    yValue = 0;
                    yValue = parseInt(item.mPoint)

                    if(yValue > maxYValue)
                        maxYValue = yValue;

                    graphView.addPoint(paramIdx, yValue)
                }

                graphView.yFrom = 0;
                graphView.yTo   = Math.ceil(maxYValue / 10000);
            }
        }

        onSignalEventUnknowFormat: {
            showErrMessage("Unknown File Format")
        }
    }

    ListModel{
        id : itemModel
    }


    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    Item {
        id : contentContainer
        height: titleBox.height + body.height + statusBar.height; width: body.width
        anchors.centerIn: parent

        NPopupTilte{
            id : titleBox
            title: dialog.titleText
            root: dialog
            enableMinimizeBtn: true

            onClickClose: {
                if(dialog.progress !== 100)
                    dialog.openProgressConfirmDlg()
                else if(dialog.isEdit === false)
                    dialog.close();
                else
                    dialog.openCloseConfirmDlg()
            }

            onClickMinimized: {
                dialog.showMinimized()
            }
        }

        Rectangle{
            id : body
            height: (GUISetting.line_margin + paramListItem.height) + (GUISetting.line_margin + btnBox.height   + GUISetting.line_margin)
            width : (GUISetting.line_margin + paramListItem.width)  + (GUISetting.line_margin + graphItem.width + GUISetting.line_margin)
            anchors.left: parent.left; anchors.top: titleBox.bottom

            color : "#E4E4E4"

            Rectangle{
                id : paramListItem

                height: 500 * GUISetting.scale; width: 150 * GUISetting.scale
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : paramListTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("parameter list")
                }

                NScrollView{
                    id : paramListView
                    anchors.top   : paramListTitle.bottom ; anchors.topMargin   : GUISetting.margin
                    anchors.bottom: timeConstantLabel.top ; anchors.bottomMargin: GUISetting.margin
                    anchors.left  : parent.left           ; anchors.leftMargin  : GUISetting.margin
                    anchors.right : parent.right          ; anchors.rightMargin : GUISetting.margin
                    spacing : GUISetting.line_margin

                    model: itemModel

                    delegate : Rectangle{
                        property PressureCtrlLearnParamItemModel paramItemModel : dlgModel.onCommandGetParamItem(idxValue)
                        height: 20 * GUISetting.scale; width: paramListView.width
                        color: "#E4E4E4"
                        visible: paramItemModel.mIsPresent

                        NText{
                            id : valueLabel
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                            text : parent.paramItemModel.mValueText

                            opacity: dlgModel.mProgress == 100 ? 1 : 0.3

                            color : "#000000"
                            horizontalAlignment: Text.AlignHCenter
                        }
                    }
                }

                NText{
                    id : timeConstantLabel
                    anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : dlgModel.mTimeConstant > -1 ? "time-constant : " + dlgModel.mTimeConstant.toFixed(2) + " s" : ""
                    color : "#000000"
                    horizontalAlignment: Text.AlignRight
                }
            }

            Rectangle{
                id : graphItem
                height: 500 * GUISetting.scale; width: 700 * GUISetting.scale
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: paramListItem.right; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : paramGraphTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("parameter graph")
                }

                PressureCtrlParamGraph{
                    id : graphView
                    anchors.top    : paramGraphTitle.bottom; anchors.topMargin    : GUISetting.margin
                    anchors.bottom : parent.bottom         ; anchors.bottomMargin : GUISetting.margin
                    anchors.left   : parent.left           ; anchors.leftMargin   : GUISetting.margin
                    anchors.right  : parent.right          ; anchors.rightMargin  : GUISetting.margin
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: paramListItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                RowLayout{
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width * 0.7
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        id : readFromControllerBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100
                        //visible: dlgModel.mIsValveConnected

                        bgColor: "#FFFFFF"
                        //text.color: "#FFFFFF"
                        text.text: qsTr("Read from controller")

                        onClick: {
                            interfaceController.read()
                        }
                    }

                    NButton{
                        id : readFromFileBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        //text.color: "#FFFFFF"
                        text.text: qsTr("Read from file")

                        onClick: {
                            interfaceFile.read()
                        }
                    }

                    NButton{
                        id : writeToFileBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && dlgModel.mIsControllerData

                        bgColor: "#FFFFFF"
                        //text.color: "#FFFFFF"
                        text.text: qsTr("Write to file")

                        onClick: {
                            interfaceFile.apply()
                        }
                    }

                    NButton{
                        id : writeToControllerBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && dlgModel.mIsFileData

                        bgColor: "#FFFFFF"
                        //text.color: "#FFFFFF"
                        text.text: qsTr("Write to controller")
                        //visible: dlgModel.mIsValveConnected

                        onClick: {
                            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                            {
                                dialog.openChangeAccessDlg()
                                return;
                            }
                            interfaceController.apply()
                        }
                    }

                    NButton{
                        id : writeResetBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        //text.color: "#FFFFFF"
                        text.text: qsTr("Reset")
                        //visible: dlgModel.mIsValveConnected

                        onClick: {
                            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                            {
                                dialog.openChangeAccessDlgForReset()
                                return;
                            }
                            interfaceReset.apply()
                        }
                    }
                }
            }
        }

        NPopupStatusBar{
            id : statusBar

            height: 40 * GUISetting.scale; width: parent.width
            anchors.top: body.bottom; anchors.left: parent.left

            progress    : dialog.progress
            status      : dialog.strStatus
            errMsg      : dialog.errMsg
            connectInfo : dialog.connectInfo
            valveID     : dialog.valveID
        }
    }

    FileDialog{
        id: wFileDialog
            title: qsTr("Write learn-param as")
            //folder: "./"
            fileMode: FileDialog.SaveFile
            nameFilters: ["Text files (*.txt)"]

            onAccepted: {
                dlgModel.onCommandWriteToLocalFile(currentFile.toString().split("///")[1])

                if(dialog.isCloseAtComplete)
                    dialog.close()
            }
            onRejected: {
                if(dialog.isCloseAtComplete)
                    dialog.close()
            }
            visible : false
    }

    FileDialog{
        id: rFileDialog
        title: qsTr("Read learn-param from file")
        //folder: "./"
        fileMode: FileDialog.OpenFile
        nameFilters: ["Text files (*.txt)"]

        onAccepted: {
            dlgModel.onCommandReadFromFile(currentFile.toString().split("///")[1])
        }
        onRejected: {
        }
        visible : false
    }

    Component{
        id : changeAccessDlg
        ChangeAccessDlg{
        }
    }

    Component{
        id : closeConfirmDlg
        CloseConfirmDlg{
            titleText: qsTr("Save loaded data")
            contentText: qsTr("Learn parameters not saved.<br>Save learn parameters to file prior to exit?")
        }
    }

    Component{
        id : progressConfirmDlg
        ProgressConfirmDlg{
        }
    }

    Component{
        id : messageBox
        NMessageBox{

        }
    }
}

/*

*/
