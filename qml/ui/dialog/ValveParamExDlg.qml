import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import ValveParamExItemModel 1.0
import ValveParamExDlgModel 1.0
import GUISetting 1.0

NWindow{ // khko_todo
    id : dialog

    property var currPageNum : 0
    property var titleText   : qsTr("Valve parameters")
    property var progress    : dlgModel.mProgress
    property var strStatus   : dlgModel.mStrStatus
    property var errMsg      : dlgModel.mErrMsg
    property var errMsg2     : dlgModel.mErrMsg2
    property var access      : ValveEnumDef.ACCESS_LOCAL //dlgModel.mAccessMode
    property var isRS232Test : dlgModel.mIsRS232Test
    property var isEdit      : dlgModel.mIsEdit
    property var connectInfo : ""
    property var valveID     : ""
    property var isCloseAtComplete : false


    function openChangeAccessDlg(interfaceObj)
    {
        var popup = changeAccessDlg.createObject(dialog)
        popup.caller = interfaceObj
        popup.open();
    }

    function openCloseConfirmDlg()
    {
        var popup = closeConfirmDlg.createObject(dialog)
        popup.caller = interfaceController
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

        function setClose(isClose)
        {
            isCloseAtComplete = isClose
        }

        function close()
        {
            dialog.close()
        }

        function apply()
        {
            write()
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

        function write()
        {
            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
            {
                openChangeAccessDlg(interfaceController)
                return;
            }

            commit()
        }
    }

    Item{
        id : interfaceFile

        property var filePath : ""

        function write()
        {
            wFileDialog.open();
        }

        function read()
        {
            rFileDialog.open()
        }
    }

    Item{
        id : interfaceFactoryReset

        function commit()
        {
            dlgModel.onCommandWriteFactoryReset()
        }

        function setClose(isClose)
        {
            isCloseAtComplete = isClose
        }

        function close()
        {
            dialog.close()
        }

        function apply()
        {
            factoryReset()
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

        function factoryReset()
        {
            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
            {
                openChangeAccessDlg(interfaceFactoryReset)
                return;
            }

            commit()
        }
    }

    Item{
        id : interfaceParamReset

        function commit()
        {
            dlgModel.onCommandWriteParamReset()
        }

        function setClose(isClose)
        {
            isCloseAtComplete = isClose
        }

        function close()
        {
            dialog.close()
        }

        function apply()
        {
            paramReset()
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

        function paramReset()
        {
            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
            {
                openChangeAccessDlg(interfaceParamReset)
                return;
            }

            commit()
        }
    }

    function movePage(pageNum)
    {
        dialog.currPageNum = pageNum;
        var startIdx = pageNum * 10;

        itemModel.clear();

        for(var idx = startIdx; idx < startIdx + 10; idx ++)
        {
            itemModel.append({"idxValue":idx})
        }
    }

    onProgressChanged: {
        if(dialog.progress === 100 && dialog.isCloseAtComplete)
            dialog.close()
    }

    ValveParamExDlgModel{
        id : dlgModel

        onSignalEventProcIdx: {
            paramListView.positionViewAtIndex(idx, ListView.Center)
        }

        Component.onCompleted : {
            dialog.movePage(0);
            //for(var idx = 0; idx < 100; idx ++)
            //{
            //    itemModel.append({"idxValue":idx})
            //}
        }
    }

    ListModel{
        id : itemModel
    }

    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    Item {
        id : contentContainer
        height: titleBox.height + body.height + statusBar.height; width: 550 * GUISetting.scale
        anchors.centerIn: parent

        NPopupTilte{
            id : titleBox
            root: dialog
            title: dialog.titleText
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
            height: (GUISetting.line_margin + naviBox.height) + (GUISetting.line_margin + paramListView.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: titleBox.bottom

            color : "#E4E4E4"

            Rectangle{
                id : naviBox
                height : 46 * GUISetting.scale
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin
                color: "#FFFFFF"

                RowLayout{
                    height: parent.height - (GUISetting.margin * 2); width: parent.width - (GUISetting.margin * 2)
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        id : page01Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 0 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 0 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("1")

                        onClick: {
                            if(dialog.currPageNum !== 0)
                                dialog.movePage(0)
                        }
                    }

                    NButton{
                        id : page02Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 1 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 1 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("2")

                        onClick: {
                            if(dialog.currPageNum !== 1)
                                dialog.movePage(1)
                        }
                    }

                    NButton{
                        id : page03Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 2 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 2 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("3")

                        onClick: {
                            if(dialog.currPageNum !== 2)
                                dialog.movePage(2)
                        }
                    }

                    NButton{
                        id : page04Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 3 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 3 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("4")

                        onClick: {
                            if(dialog.currPageNum !== 3)
                                dialog.movePage(3)
                        }
                    }

                    NButton{
                        id : page05Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 4 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 4 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("5")

                        onClick: {
                            if(dialog.currPageNum !== 4)
                                dialog.movePage(4)
                        }
                    }

                    NButton{
                        id : page06Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 5 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 5 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("6")

                        onClick: {
                            if(dialog.currPageNum !== 5)
                                dialog.movePage(5)
                        }
                    }

                    NButton{
                        id : page07Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 6 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 6 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("7")

                        onClick: {
                            if(dialog.currPageNum !== 6)
                                dialog.movePage(6)
                        }
                    }

                    NButton{
                        id : page08Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 7 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 7 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("8")

                        onClick: {
                            if(dialog.currPageNum !== 7)
                                dialog.movePage(7)
                        }
                    }

                    NButton{
                        id : page09Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 8 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 8 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("9")

                        onClick: {
                            if(dialog.currPageNum !== 8)
                                dialog.movePage(8)
                        }
                    }

                    NButton{
                        id : page10Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: dialog.currPageNum === 9 ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === 9 ? "#FFFFFF" : "#000000"
                        text.text: qsTr("10")

                        onClick: {
                            if(dialog.currPageNum !== 9)
                                dialog.movePage(9)
                        }
                    }
                }
            }

            NScrollView{
                id : paramListView
                height: 458 * GUISetting.scale
                anchors.top: naviBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin
                spacing : 0

                model: itemModel

                //040 : ", "050 : ", "063 : " , "080 : " , "100 : " , "160 : " , "200 : " , "250 : "
                delegate : Item{
                    property ValveParamExItemModel paramItemModel : dlgModel.onCommandGetParamItem(idxValue)
                    property string paramTextValue : paramItemModel.mTextValue
                    property string paramDesc : paramItemModel.mDesc
//                        idxValue === 0 ? qsTr("(model)") :
//                                                idxValue === 1 ? qsTr("(type)") :
//                                                idxValue === 2 ? qsTr("(sealing type)") :
//                                                idxValue === 3 ? qsTr("(flange size)") :
//                                                idxValue === 4 ? qsTr("(method of contract)") :
//                                                idxValue === 5 ? qsTr("(body material)") :
//                                                idxValue === 6 ? qsTr("(interface)") :
//                                                idxValue === 7 ? qsTr("(power option)") :
//                                                idxValue === 8 ? qsTr("(quantity of sensors)") :
//                                                idxValue === 9 ? qsTr("(version 01)") :
//                                                idxValue === 10 ? qsTr("(version 02)") :
//                                                idxValue === 11 ? qsTr("(version 03)") :
//                                                idxValue === 12 ? qsTr("(product number)") :
//                                                idxValue === 18 ? qsTr("(hardware safety)") :
//                                                idxValue === 19 ? qsTr("(pressure setting mode)") :
//                                                idxValue === 20 ? qsTr("(rest current)") :
//                                                idxValue === 21 ? qsTr("(sync current)") :
//                                                idxValue === 22 ? qsTr("(min current)") :
//                                                idxValue === 23 ? qsTr("(max current)") :
//                                                idxValue === 24 ? qsTr("(A-DN40/DN25 max speed)") :
//                                                idxValue === 25 ? qsTr("(A-DN50 max speed)") :
//                                                idxValue === 26 ? qsTr("(A-DN63 max speed)") :
//                                                idxValue === 27 ? qsTr("(A-DN80 max speed)") :
//                                                idxValue === 28 ? qsTr("(A-DN100 max speed)") :
//                                                idxValue === 29 ? qsTr("(A-DN160 max speed)") :
//                                                idxValue === 30 ? qsTr("(A-DN200 max speed)") :
//                                                idxValue === 31 ? qsTr("(A-DN250 max speed)") :
//                                                idxValue === 32 ? qsTr("(S-DN40 max speed)") :
//                                                idxValue === 33 ? qsTr("(S-DN50 max speed)") :
//                                                idxValue === 34 ? qsTr("(S-DN63 max speed)") :
//                                                idxValue === 35 ? qsTr("(S-DN80 max speed)") :
//                                                idxValue === 36 ? qsTr("(S-DN100 max speed)") :
//                                                idxValue === 37 ? qsTr("(S-DN160 max speed)") :
//                                                idxValue === 38 ? qsTr("(S-DN200 max speed)") :
//                                                idxValue === 39 ? qsTr("(S-DN250 max speed)") : ""

                    height:(46 * GUISetting.scale); width: parent.width
                    opacity: paramItemModel.mIsPresent ? 1 : 0.3

                    onParamTextValueChanged:
                    {
                        valveInput.textField.text = paramItemModel.mTextValue
                    }

                    Rectangle{
                        width: parent.width; height: parent.height - GUISetting.line_margin
                        color: "#FFFFFF"

                        NText{
                            id : keyLabel
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; //anchors.right: valveInput.left; anchors.rightMargin: 10
                            text : parent.parent.paramItemModel.mTextID
                            color : "#24292E"
                            elide: Text.ElideRight

                        }

                        NText{
                            id : keyDesc
                            width : 300 * GUISetting.scale
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: keyLabel.right; anchors.leftMargin: GUISetting.margin; //anchors.right: valveInput.left; anchors.rightMargin: 10
                            text : parent.parent.paramDesc
                            color : "#24292E"
                            elide: Text.ElideRight

                        }

                        NInputNumber{
                            id : valveInput
                            height: 24 * GUISetting.scale//width: (parent.width - 40) / 2;
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: keyDesc.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                            enabled: dialog.progress === 100 && paramItemModel.mIsPresent

                            textField.validator: IntValidator{} // RegExpValidator { regExp: /[0-9A-Fa-f]{0,8}/ } //IntValidator{}
                            textField.color: parent.parent.paramItemModel.mIsErr ? "#FF0000" : parent.parent.paramItemModel.mIsEdit ? "#24A7FF" : "#000000"
                            textField.text: parent.parent.paramTextValue
                            stepValue : 1; minValue: -1048575; maxValue: 1048575
                            //isHexMode : true
                            fixedN : 0
                            //padN   : 6

                            onChangedValue: {
                                parent.parent.paramItemModel.editValue(value)
                            }
                        }
                    }
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: paramListView.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                RowLayout{
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width - (GUISetting.margin * 2)
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        id : readFromControllerBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        //text.color: "#FFFFFF"
                        text.text: qsTr("Read from<br>controller")

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
                        text.text: qsTr("Read from<br>file")

                        onClick: {
                            interfaceFile.read()
                        }
                    }

                    NButton{
                        id : writeToFileBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Write to<br>file")

                        onClick: {
                            interfaceFile.write()
                        }
                    }

                    NButton{
                        id : writeToControllerBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && dialog.isEdit

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Write to<br>controller")

                        NCircleIndicator{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                            color: "#FF0000"
                            visible: dialog.isEdit
                        }

                        onClick: {
                            interfaceController.write()
                        }
                    }
/*
                    NButton{
                        id : paramResetBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Parameter<br>reset")

                        onClick: {
                            interfaceParamReset.paramReset()
                        }
                    }
                    */

                    NButton{
                        id : factoryResetBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Factory<br>reset")

                        onClick: {
                            var popup = passwordDlg.createObject(dialog); popup.caller = factoryResetBtn; popup.open();

                        }

                        function confirm()
                        {
                            interfaceFactoryReset.factoryReset()
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
            errMsg2     : dialog.errMsg2
            connectInfo : dialog.connectInfo
            valveID     : dialog.valveID
        }
    }

    FileDialog{
        id: wFileDialog
            title: qsTr("Write valve-param as")
            //folder: "./"
            fileMode: FileDialog.SaveFile
            nameFilters: ["Text files (*.txt)"]

            onAccepted: {
                dlgModel.onCommandWriteToFile(currentFile.toString().split("///")[1])
            }
            onRejected: {
            }
            visible : false
    }

    FileDialog{
        id: rFileDialog
            title: qsTr("Read valve-param from file")
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
            contentText: qsTr("Valve parameters not saved.<br>Save valve parameters to file prior to exit?")
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

    Component{
        id : passwordDlg
        PasswordDlg
        {
            onResult: { caller.confirm()}
        }
    }
}

/*

*/
