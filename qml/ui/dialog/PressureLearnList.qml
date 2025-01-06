import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import PressureCtrlLearnListItemModel 1.0
import PressureCtrlLearnListDlgModel 1.0
import GUISetting 1.0

NWindow{ // khko_todo
    id : dialog

    property var currPageNum : 0
    property var pageBtnStartValue: 0

    property var titleText   : qsTr("Learning list")
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
            dlgModel.onCommandWriteLearnListReset()
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

    function updatePageBtnValue()
    {
        var valueIdx = 0;
        var startPage = dialog.currPageNum - 2
        var endPage   = startPage + 5

        if (startPage < 0) {
            startPage = 0
            endPage = startPage + 5
        }

        if (endPage > (dialog.mTotalPageCnt - 1)) {
            endPage = dlgModel.mTotalPageCnt - 1
            startPage = endPage - 5
            if (startPage < 0) {
                startPage = 0
            }
        }

        dialog.pageBtnStartValue = startPage;
    }

    function movePage()
    {
        dialog.updatePageBtnValue();

        console.debug(dlgModel.mItemCountPerPage)

        itemModel.clear();

        for(var idx = 0; idx < dlgModel.mItemCountPerPage; idx += 4)
        {
            var item01 = dlgModel.onCommandGetListItemInPage(dialog.currPageNum, idx)
            var item02 = dlgModel.onCommandGetListItemInPage(dialog.currPageNum, idx + 1)
            var item03 = dlgModel.onCommandGetListItemInPage(dialog.currPageNum, idx + 2)
            var item04 = dlgModel.onCommandGetListItemInPage(dialog.currPageNum, idx + 3)
            var item01Idx = -1;
            var item02Idx = -1;
            var item03Idx = -1;
            var item04Idx = -1;
            var groupId   = 0;
            var value01    = 0.0;
            var isEnable01 = false;
            var isErr01    = false;
            var isEdit01   = false;
            var value02    = 0.0;
            var isEnable02 = false;
            var isErr02    = false;
            var isEdit02   = false;
            var value03    = 0.0;
            var isEnable03 = false;
            var isErr03    = false;
            var isEdit03   = false;
            var value04    = 0.0;
            var isEnable04 = false;
            var isErr04    = false;
            var isEdit04   = false;
            console.debug("current page = " + dialog.currPageNum + ", idx = " + idx)

            if(item01 === null)
                break;

            if(item01 !== null)
            {
                item01Idx = (dialog.currPageNum * dlgModel.mItemCountPerPage) + idx;
                value01    = item01.mFloatValue
                isEnable01 = item01.mIsEnable
                isErr01    = item01.mIsErr
                isEdit01   = item01.mIsEdit

                groupId    = item01.mIntID < 1 ? 0 : item01.mIntID / 4;
            }
            if(item02 !== null)
            {
                item02Idx = (dialog.currPageNum * dlgModel.mItemCountPerPage) + idx + 1;
                value02    = item02.mFloatValue
                isEnable02 = item02.mIsEnable
                isErr02    = item02.mIsErr
                isEdit02   = item02.mIsEdit
            }
            if(item03 !== null)
            {
                item03Idx = (dialog.currPageNum * dlgModel.mItemCountPerPage) + idx + 2;
                value03    = item03.mFloatValue
                isEnable03 = item03.mIsEnable
                isErr03    = item03.mIsErr
                isEdit03   = item03.mIsEdit
            }
            if(item04 !== null)
            {
                item04Idx = (dialog.currPageNum * dlgModel.mItemCountPerPage) + idx + 3;
                value04    = item04.mFloatValue
                isEnable04 = item04.mIsEnable
                isErr04    = item04.mIsErr
                isEdit04   = item04.mIsEdit
            }

            itemModel.append({"idx01Arg":item01Idx, "idx02Arg":item02Idx, "idx03Arg":item03Idx, "idx04Arg":item04Idx, "groupIDArg" : groupId,
                              "value01Arg" : value01, "isEnable01Arg" : isEnable01, "isErr01Arg" : isErr01, "isEdit01Arg" : isEdit01,
                              "value02Arg" : value02, "isEnable02Arg" : isEnable02, "isErr02Arg" : isErr02, "isEdit02Arg" : isEdit02,
                              "value03Arg" : value03, "isEnable03Arg" : isEnable03, "isErr03Arg" : isErr03, "isEdit03Arg" : isEdit03,
                              "value04Arg" : value04, "isEnable04Arg" : isEnable04, "isErr04Arg" : isErr04, "isEdit04Arg" : isEdit04})


        }
    }

    function onPageClick(btnIdx)
    {
        console.debug(btnIdx)
        switch (btnIdx) {
            case 0:
                // << (처음 페이지로)
                dialog.currPageNum = 0
                break
            case 1:
                // < (이전 페이지)
                if (dialog.currPageNum > 0)
                    dialog.currPageNum --
                break
            case 8:
                // > (다음 페이지)
                if (dialog.currPageNum <  dlgModel.mTotalPageCnt - 1)
                    dialog.currPageNum++
                break
            case 9:
                // >> (마지막 페이지)
                if( dlgModel.mTotalPageCnt > 0)
                    dialog.currPageNum =  dlgModel.mTotalPageCnt - 1
                break
            default:
                // 가운데 번호 버튼(2~7)
                var pageNumber = dialog.pageBtnStartValue + (btnIdx - 2)
                if (pageNumber !== -1) {
                    if (pageNumber >= 0 && pageNumber <= dlgModel.mTotalPageCnt - 1)
                        dialog.currPageNum = pageNumber
                }
        }

        // 이동 이후, 버튼 라벨 재계산
        dialog.movePage()
    }



    onProgressChanged: {
        if(dialog.progress === 100 && dialog.isCloseAtComplete)
            dialog.close()
        else if(dialog.progress === 100)
            dialog.onPageClick(dialog.currPageNum);
    }

    PressureCtrlLearnListDlgModel{
        id : dlgModel

        Component.onCompleted : {
        }
    }

    ListModel{
        id : itemModel
    }

    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    Item {
        id : contentContainer
        height: titleBox.height + body.height + statusBar.height; width: 800 * GUISetting.scale
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

                        bgColor: "#FFFFFF"
                        text.color: "#000000"
                        text.text: qsTr("First")

                        onClick: {
                            dialog.onPageClick(0);
                        }
                    }

                    NButton{
                        id : page02Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.color:  "#000000"
                        text.text: qsTr("Pre")

                        onClick: {
                            dialog.onPageClick(1);
                        }
                    }

                    NButton{
                        id : page03Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && (dialog.pageBtnStartValue < dlgModel.mTotalPageCnt)

                        bgColor: dialog.currPageNum === dialog.pageBtnStartValue ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === dialog.pageBtnStartValue ? "#FFFFFF" : "#000000"
                        text.text: dialog.pageBtnStartValue + 1

                        onClick: {
                            dialog.onPageClick(2);
                        }
                    }

                    NButton{
                        id : page04Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && ((dialog.pageBtnStartValue + 1) < dlgModel.mTotalPageCnt)

                        bgColor: dialog.currPageNum === (dialog.pageBtnStartValue + 1) ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === (dialog.pageBtnStartValue + 1) ? "#FFFFFF" : "#000000"
                        text.text: (dialog.pageBtnStartValue + 1) + 1

                        onClick: {
                            dialog.onPageClick(3);
                        }
                    }

                    NButton{
                        id : page05Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && ((dialog.pageBtnStartValue + 2) < dlgModel.mTotalPageCnt)

                        bgColor: dialog.currPageNum === (dialog.pageBtnStartValue + 2) ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === (dialog.pageBtnStartValue + 2) ? "#FFFFFF" : "#000000"
                        text.text: (dialog.pageBtnStartValue + 2) + 1

                        onClick: {
                            dialog.onPageClick(4);
                        }
                    }

                    NButton{
                        id : page06Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && ((dialog.pageBtnStartValue + 3) < dlgModel.mTotalPageCnt)

                        bgColor   : dialog.currPageNum === (dialog.pageBtnStartValue + 3) ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === (dialog.pageBtnStartValue + 3) ? "#FFFFFF" : "#000000"
                        text.text: (dialog.pageBtnStartValue + 3) + 1

                        onClick: {
                            dialog.onPageClick(5);
                        }
                    }

                    NButton{
                        id : page07Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && ((dialog.pageBtnStartValue + 4) < dlgModel.mTotalPageCnt)

                        bgColor   : dialog.currPageNum === (dialog.pageBtnStartValue + 4) ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === (dialog.pageBtnStartValue + 4) ? "#FFFFFF" : "#000000"
                        text.text: (dialog.pageBtnStartValue + 4) + 1

                        onClick: {
                            dialog.onPageClick(6);
                        }
                    }

                    NButton{
                        id : page08Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && ((dialog.pageBtnStartValue + 5) < dlgModel.mTotalPageCnt)

                        bgColor   : dialog.currPageNum === (dialog.pageBtnStartValue + 5) ? "#24A7FF" : "#FFFFFF"
                        text.color: dialog.currPageNum === (dialog.pageBtnStartValue + 5) ? "#FFFFFF" : "#000000"
                        text.text: (dialog.pageBtnStartValue + 5) + 1

                        onClick: {
                            dialog.onPageClick(7);
                        }
                    }

                    NButton{
                        id : page09Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.color:"#000000"
                        text.text: qsTr("Next")

                        onClick: {
                            dialog.onPageClick(8);
                        }
                    }

                    NButton{
                        id : page10Btn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.color: "#000000"
                        text.text: qsTr("Last")

                        onClick: {
                            dialog.onPageClick(9);
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

                delegate : Item{
                    property int    idx01      : idx01Arg
                    property int    idx02      : idx02Arg
                    property int    idx03      : idx03Arg
                    property int    idx04      : idx04Arg
                    property int    groupID    : groupIDArg
                    property real   value01    : value01Arg
                    property bool   isEnable01 : isEnable01Arg
                    property bool   isErr01    : isErr01Arg
                    property bool   isEdit01   : isEdit01Arg
                    property real   value02    : value02Arg
                    property bool   isEnable02 : isEnable02Arg
                    property bool   isErr02    : isErr02Arg
                    property bool   isEdit02   : isEdit02Arg
                    property real   value03    : value03Arg
                    property bool   isEnable03 : isEnable03Arg
                    property bool   isErr03    : isErr03Arg
                    property bool   isEdit03   : isEdit03Arg
                    property real   value04    : value04Arg
                    property bool   isEnable04 : isEnable04Arg
                    property bool   isErr04    : isErr04Arg
                    property bool   isEdit04   : isEdit04Arg


                    height:(46 * GUISetting.scale); width: parent.width

                    onValue01Changed:
                    {
                        valveInput01.setFloatValue(value01);
                    }
                    onValue02Changed:
                    {
                        valveInput02.setFloatValue(value02);
                    }
                    onValue03Changed:
                    {
                        valveInput03.setFloatValue(value03);
                    }
                    onValue04Changed:
                    {
                        valveInput04.setFloatValue(value04);
                    }

                    Rectangle{
                        width: parent.width; height: parent.height - GUISetting.line_margin
                        color: "#FFFFFF"

                        NText{
                            id : keyLabel
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
                            text : (parent.parent.groupID )
                            color : "#24292E"
                            elide: Text.ElideRight

                        }

                        RowLayout{
                            height: 24 * GUISetting.scale;
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: keyLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                            spacing: GUISetting.margin

                            NInputNumber{
                                id : valveInput01
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

                                enabled: dialog.progress === 100 && isEnable01

                                textField.validator: DoubleValidator{}
                                textField.color: parent.parent.parent.isErr01 ? "#FF0000" : parent.parent.parent.isEdit01 ? "#24A7FF" : "#000000"
                                textField.text: parent.parent.parent.value01
                                stepValue : 1; minValue: -9999999999; maxValue: 9999999999
                                isSpecialFloatNode: true

                                onChangedValue: {
                                    var item = dlgModel.onCommandGetListItem(idx01);
                                    item.editFloatValue(parseFloat(textField.text))
                                    if(item.mIsEdit)
                                    {
                                        parent.parent.parent.isEdit01 = true
                                        dlgModel.onCommandSetEdit(true);
                                    }
                                }
                            }

                            NInputNumber{
                                id : valveInput02
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

                                enabled: dialog.progress === 100 && isEnable02

                                textField.validator: DoubleValidator{}
                                textField.color: parent.parent.parent.isErr02 ? "#FF0000" : parent.parent.parent.isEdit02 ? "#24A7FF" : "#000000"
                                textField.text: parent.parent.parent.value02
                                stepValue : 1; minValue: -9999999999; maxValue: 9999999999
                                isSpecialFloatNode: true

                                onChangedValue: {
                                    var item = dlgModel.onCommandGetListItem(idx02);
                                    item.editFloatValue(parseFloat(textField.text))

                                    if(item.mIsEdit)
                                    {
                                        parent.parent.parent.isEdit02 = true
                                        dlgModel.onCommandSetEdit(true);
                                    }
                                }
                            }

                            NInputNumber{
                                id : valveInput03
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

                                enabled: dialog.progress === 100 && isEnable03

                                textField.validator: DoubleValidator{}
                                textField.color: parent.parent.parent.isErr03 ? "#FF0000" : parent.parent.parent.isEdit03 ? "#24A7FF" : "#000000"
                                textField.text: parent.parent.parent.value03
                                stepValue : 1; minValue: -9999999999; maxValue: 9999999999
                                isSpecialFloatNode: true

                                onChangedValue: {
                                    var item = dlgModel.onCommandGetListItem(idx03);
                                    item.editFloatValue(parseFloat(textField.text))
                                    if(item.mIsEdit)
                                    {
                                        parent.parent.parent.isEdit03 = true
                                        dlgModel.onCommandSetEdit(true);
                                    }
                                }
                            }

                            NInputNumber{
                                id : valveInput04
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

                                enabled: dialog.progress === 100 && isEnable04

                                textField.validator: DoubleValidator{}
                                textField.color: parent.parent.parent.isErr04 ? "#FF0000" : parent.parent.parent.isEdit04 ? "#24A7FF" : "#000000"
                                textField.text: parent.parent.parent.value04
                                stepValue : 1; minValue: -9999999999; maxValue: 9999999999
                                isSpecialFloatNode: true

                                onChangedValue: {
                                    var item = dlgModel.onCommandGetListItem(idx04);
                                    item.editFloatValue(parseFloat(textField.text))
                                    if(item.mIsEdit)
                                    {
                                        parent.parent.parent.isEdit04 = true
                                        dlgModel.onCommandSetEdit(true);
                                    }
                                }
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
                        id : factoryResetBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Reset")

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
