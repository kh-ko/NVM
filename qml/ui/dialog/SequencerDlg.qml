import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import QmlEnumDef 1.0
import SequencerDlgModel 1.0
import SeqTestItemModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var  body : null
    property bool isRun : dlgModel.mRunState == 1

    titleText     : qsTr("Sequence Test")
    progress      : 100
    strStatus     : dlgModel.mStrStatus
    errMsg        : dlgModel.mErrMsg
    access        : dlgModel.mAccessMode
    isRS232Test   : dlgModel.mIsRS232Test
    isEdit        : dlgModel.mIsEdit
    doNotDestroy  : true
    //bodyWidth     : 700

    function runTest()
    {
        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            dialog.openChangeAccessDlg()
            return;
        }

        dialog.commit()
    }

    function commit()
    {
        dlgModel.onCommandRun()
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth = 700 * GUISetting.scale

        dlgModel.onCommandInsertItem(0, QmlEnumDef.SEQ_TYPE_CLOSE)
    }

    SequencerDlgModel{
        id : dlgModel

        onSignalEventChangedActualIndex: {
            var idx = mActualIndex > -1 ? mActualIndex : 0;
            body.stepListView.positionViewAtIndex(idx, ListView.bottom)
        }

        onSignalEventInsertedItem: {
            itemModel.insert(idx, {"pItemModel":item})
        }
    }

    ListModel{
        id : itemModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias  testNumOfTimesInput : _testNumOfTimesInput
            property alias  stepListView        : _stepListView
            property real   guiScale            : GUISetting.scale

            height: (GUISetting.line_margin + setupItem.height) + (GUISetting.line_margin + counterItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = 700 * GUISetting.scale
            }

            Rectangle{
                id : setupItem

                height: GUISetting.margin + setupTitle.height + GUISetting.margin + commSettingBox.height + GUISetting.margin + stepListBox.height + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : setupTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Setup")
                }

                Item{
                    id : commSettingBox
                    height: 24 * GUISetting.scale; width : parent.width
                    anchors.top: setupTitle.bottom; anchors.topMargin: GUISetting.margin

                    NText{
                        id : testNumOfTimesLabel
                        width: 120 * GUISetting.scale;
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text : qsTr("target cycles")
                    }

                    NInputNumber{
                        id : _testNumOfTimesInput
                        width: 100 * GUISetting.scale; height: parent.height
                        anchors.verticalCenter: testNumOfTimesLabel.verticalCenter; anchors.left: testNumOfTimesLabel.right; anchors.leftMargin: GUISetting.margin

                        enabled: dlgModel.mRunState == 0

                        textField.text: (dlgModel.mTargetCycles).toString()
                        textField.validator: IntValidator{}
                        textField.color: "#000000"
                        stepValue : 1; minValue: 1; maxValue: 10000000
                        fixedN : 0

                        onChangedValue: {
                            dlgModel.onCommandSetTargetCycles(value);
                            dlgModel.onCommandSetIsEdit(true)
                        }
                    }
                }

                Rectangle{
                    id : stepListBox
                    width: parent.width - (GUISetting.margin * 2); height: 200 * GUISetting.scale
                    anchors.top: commSettingBox.bottom; anchors.topMargin: 10; anchors.horizontalCenter: parent.horizontalCenter
                    color: "#E4E4E4"

                    NScrollView{
                        id : _stepListView
                        anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin
                        spacing : GUISetting.line_margin

                        model: itemModel

                        delegate : Rectangle{
                            id : seqItem

                            property SeqTestItemModel seqItemModel : pItemModel
                            height: 44 * GUISetting.scale; width: parent.width
                            color: "#FFFFFF"

                            Rectangle{
                                id : itemRunIndi
                                width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                                anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                                radius: width / 2
                                color: seqItem.seqItemModel.mIsRunnig ? "#24A7FF" : "#E4E4E4"
                            }

                            Item{
                                height: parent.height;
                                anchors.left: itemRunIndi.right; anchors.leftMargin: GUISetting.margin; anchors.right: errCntText.left; anchors.rightMargin: (GUISetting.margin * 2)

                                Item {
                                    id : cmdBox
                                    height: parent.height; width: parent.width * 0.6
                                    anchors.left: parent.left

                                    NText{
                                        id : commandLabel
                                        width: 60 * GUISetting.scale
                                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left
                                        text: seqItem.seqItemModel.mItemType == QmlEnumDef.SEQ_TYPE_OPEN     ? qsTr("Open"       ) :
                                              seqItem.seqItemModel.mItemType == QmlEnumDef.SEQ_TYPE_CLOSE    ? qsTr("Close"      ) :
                                              seqItem.seqItemModel.mItemType == QmlEnumDef.SEQ_TYPE_POSITION ? qsTr("Position(%)") :
                                              seqItem.seqItemModel.mItemType == QmlEnumDef.SEQ_TYPE_CUSTOM   ? qsTr("Custom"     ) : ""
                                    }

                                    NInputNumber{
                                        id : posInput
                                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                                        anchors.verticalCenter: parent.verticalCenter; anchors.left: commandLabel.right; anchors.leftMargin: GUISetting.margin;
                                        visible: seqItem.seqItemModel.mItemType == QmlEnumDef.SEQ_TYPE_POSITION
                                        textField.validator: DoubleValidator{}
                                        stepValue : 1; minValue: 0; maxValue: 100
                                        fixedN : 3

                                        textField.text: seqItem.seqItemModel.mPositionPct.toFixed(fixedN)

                                        onChangedValue: {
                                            seqItem.seqItemModel.onCommandSetPositionPct(value)
                                            dlgModel.onCommandSetIsEdit(true)
                                        }
                                    }

                                    NInputText{
                                        id : valveInput
                                        height: 24 * GUISetting.scale
                                        anchors.verticalCenter: parent.verticalCenter; anchors.left: posInput.visible ? posInput.right : commandLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin * 2

                                        enabled: dlgModel.mRunState == 0 && (seqItem.seqItemModel.mItemType == QmlEnumDef.SEQ_TYPE_CUSTOM)

                                        textField.color: "#000000"
                                        textField.text: seqItem.seqItemModel.mCommand

                                        onChangedValue: {
                                            seqItem.seqItemModel.onCommandSetCommand(value)
                                            dlgModel.onCommandSetIsEdit(true)
                                        }
                                    }
                                }
                                Item {
                                    id : durationBox
                                    height: parent.height; width: parent.width * 0.4
                                    anchors.left: cmdBox.right

                                    NText{
                                        id : durationLabel
                                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left;
                                        text: qsTr("Duration(msec)")
                                    }

                                    NInputNumber{
                                        id : durationInput
                                        height: 24 * GUISetting.scale
                                        anchors.verticalCenter: parent.verticalCenter; anchors.left: durationLabel.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right;

                                        enabled: dlgModel.mRunState == 0

                                        textField.color: "#000000"
                                        textField.text: seqItem.seqItemModel.mDelayMSec
                                        textField.validator: IntValidator{}
                                        stepValue : 1; minValue: 1; maxValue: 1000000
                                        fixedN : 0

                                        onChangedValue: {
                                            seqItem.seqItemModel.onCommandSetDelayMSec(value)
                                            dlgModel.onCommandSetIsEdit(true)
                                        }
                                    }
                                }
                            }

                            NText{
                                id : errCntText
                                width: 150 * GUISetting.scale;
                                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                                color: "#000000"
                                horizontalAlignment: Text.AlignRight
                                text :seqItem.seqItemModel.mRcvCount +  " / " + seqItem.seqItemModel.mSentCount
                                //visible: seqItem.seqItemModel.mErrCount !== 0
                            }

                            MouseArea {
                                anchors.fill: parent
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

                                    Menu{
                                        title: qsTr("Insert row above")

                                        MenuItem {
                                            text: qsTr("open")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {

                                                        dlgModel.onCommandInsertItem(i, QmlEnumDef.SEQ_TYPE_OPEN)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }

                                        MenuItem {
                                            text: qsTr("close")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {

                                                        dlgModel.onCommandInsertItem(i, QmlEnumDef.SEQ_TYPE_CLOSE)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }

                                        MenuItem {
                                            text: qsTr("position")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {

                                                        dlgModel.onCommandInsertItem(i, QmlEnumDef.SEQ_TYPE_POSITION)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }

                                        MenuItem {
                                            text: qsTr("custom")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {

                                                        dlgModel.onCommandInsertItem(i, QmlEnumDef.SEQ_TYPE_CUSTOM)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    Menu{
                                        title: qsTr("Insert row below")

                                        MenuItem {
                                            text: qsTr("open")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {
                                                        dlgModel.onCommandInsertItem(i + 1, QmlEnumDef.SEQ_TYPE_OPEN)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }

                                        MenuItem {
                                            text: qsTr("close")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {
                                                        dlgModel.onCommandInsertItem(i + 1, QmlEnumDef.SEQ_TYPE_CLOSE)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }

                                        MenuItem {
                                            text: qsTr("position")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {
                                                        dlgModel.onCommandInsertItem(i + 1, QmlEnumDef.SEQ_TYPE_POSITION)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }

                                        MenuItem {
                                            text: qsTr("custom")
                                            enabled: dlgModel.mRunState == 0
                                            onTriggered: {
                                                for(var i = 0; i < itemModel.count; i ++)
                                                {
                                                    var item = itemModel.get(i)

                                                    if(item.pItemModel === seqItem.seqItemModel)
                                                    {
                                                        dlgModel.onCommandInsertItem(i + 1, QmlEnumDef.SEQ_TYPE_CUSTOM)
                                                        dlgModel.onCommandSetIsEdit(true)
                                                        return;
                                                    }
                                                }
                                            }
                                        }
                                    }

                                    MenuItem {
                                        text: qsTr("Delete row")
                                        enabled: itemModel.count > 1 && dlgModel.mRunState == 0
                                        onTriggered: {
                                            for(var i = 0; i < itemModel.count; i ++)
                                            {
                                                var item = itemModel.get(i)

                                                if(item.pItemModel ===  seqItem.seqItemModel)
                                                {
                                                    itemModel.remove(i);
                                                    dlgModel.onDeletedItem( seqItem.seqItemModel);
                                                    dlgModel.onCommandSetIsEdit(true)
                                                    return;
                                                }
                                            }
                                        }
                                    }
                                }
                            }

                            /*
                            NButton{
                                id : delBtn
                                height: 24; width: 100
                                anchors.verticalCenter: parent.verticalCenter; anchors.right: parent.right; anchors.rightMargin: 10

                                text.text: qsTr("remove")
                                enabled: !dlgModel.mIsRunning

                                onClick: {
                                    for(var i = 0; i < itemModel.count; i ++)
                                    {
                                        var item = itemModel.get(i)

                                        if(item.pItemModel === parent.seqItemModel)
                                        {
                                            itemModel.remove(i);
                                            dlgModel.onDeletedItem(seqItemModel);
                                            return;
                                        }
                                    }
                                }
                            }*/
                        }
                    }
                }
            }

            Rectangle{
                id : counterItem

                height: GUISetting.margin + counterTitle.height + GUISetting.margin + totalCounterLabel.height + GUISetting.margin + counterLabel.height + GUISetting.margin + indexLabel.height + GUISetting.margin
                anchors.top: setupItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : counterTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Status")
                }

                NText{
                    id : totalCounterLabel
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: counterTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("total actual cycles")
                }

                Rectangle{
                    id : totalCounterBox
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.verticalCenter: totalCounterLabel.verticalCenter; anchors.left: totalCounterLabel.right; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mTotalActualCycles
                        color: "#000000"
                    }
                }

                NButton{
                    width: 70 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: totalCounterBox.verticalCenter; anchors.right: parent.right; anchors.rightMargin:  GUISetting.margin
                    text.text: qsTr("Reset")
                    enabled: !dlgModel.mIsRunning

                    onClick: { dlgModel.onCommandResetTotalCycles();}
                }

                NText{
                    id : counterLabel
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: totalCounterLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("actual cycles")
                }

                Rectangle{
                    id : counterBox
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.verticalCenter: counterLabel.verticalCenter; anchors.left: counterLabel.right; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mActualCycles
                        color: "#000000"
                    }
                }

                NText{
                    id : indexLabel
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: counterLabel.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    text : qsTr("actual index")
                }

                Rectangle{
                    id : indexBox
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.verticalCenter: indexLabel.verticalCenter; anchors.left: indexLabel.right; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mActualIndex
                        color: "#000000"
                    }
                }
            }


            Rectangle{
                id : btnBox
                height: 70 * GUISetting.scale;
                anchors.top: counterItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                RowLayout{
                    height: 50 * GUISetting.scale; width: parent.width * 0.7
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dlgModel.mRunState == 0

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Save to file")

                        onClick: {
                            //dlgModel.onCommandSaveSeqTestList()
                            wFileDialog.open()
                        }

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter

                            radius: width / 2
                            visible: dialog.isEdit
                            color: "#24A7FF"
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dlgModel.mRunState == 0

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Load from file")

                        onClick: {
                            rFileDialog.open()
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        //enabled: && dlgModel.mRunState != 0

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: dlgModel.mRunState == 0 ? qsTr("Run") :
                                   dlgModel.mRunState == 1 ? qsTr("Pause") : qsTr("Resume")

                        onClick: {
                            dialog.runTest()
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dlgModel.mRunState != 0

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Stop")

                        onClick: {
                            dlgModel.onCommandStop()
                        }
                    }
                }
            }
        }
    }

    FileDialog{
        id: wFileDialog
            title: qsTr("Save to file")
            //folder: "./"
            fileMode: FileDialog.SaveFile
            nameFilters: ["Text files (*.txt)"]

            onAccepted: {
                dlgModel.onCommandSaveSeqTestList(currentFile.toString().split("///")[1])
            }
            onRejected: {
            }
            visible : false
    }

    FileDialog{
        id: rFileDialog
        title: qsTr("Load from file")
        //folder: "./"
        fileMode: FileDialog.OpenFile
        nameFilters: ["Text files (*.txt)"]

        onAccepted: {
            itemModel.clear()
            dlgModel.onCommandLoad(currentFile.toString().split("///")[1])
            body.testNumOfTimesInput.textField.text = dlgModel.mTargetCycles.toString()
            dlgModel.onCommandSetIsEdit(false)
        }
        onRejected: {
        }
        visible : false
    }
}
