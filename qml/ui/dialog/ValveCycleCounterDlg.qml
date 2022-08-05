import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import ValveCycleCounterDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property var body : null

    titleText   : qsTr("Valve cycle counter")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : false

    function cycleReset(funcItem)
    {
        if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
        {
            var popup = changeAccessDlg.createObject(dialog)
            popup.caller = funcItem
            popup.open();
            return;
        }

        funcItem.onResultChangeAccess(true)
    }

    Item{
        id : controlCycleFunc

        function onResultChangeAccess(value)
        {
            if(value)
            {
                dlgModel.onCommandControlCycleReset()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }
    }

    Item{
        id : isolationCycleFunc

        function onResultChangeAccess(value)
        {
            if(value)
            {
                dlgModel.onCommandIsolationCycleReset()
                return;
            }
            showErrMessage(qsTr("Mode change failed."))
        }
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    ValveCycleCounterDlgModel{
        id : dlgModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real   guiScale : GUISetting.scale

            height: (GUISetting.line_margin + controlCycleItem.height) + (GUISetting.line_margin + isolationCycleItem.height) + GUISetting.line_margin
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : controlCycleItem

                height: (GUISetting.margin + controlCycleTitle.height) + (GUISetting.margin + controlCycleBox.height) + (GUISetting.margin + totalControlCycleBox.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: 2; anchors.left: parent.left; anchors.leftMargin: 2; anchors.right: parent.right; anchors.rightMargin: 2

                color: "#FFFFFF"

                NText{
                    id : controlCycleTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Control cycles")
                }

                Rectangle{
                    id : controlCycleBox
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: controlCycleTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mControlCycles
                        color: dlgModel.mErrControlCycles ? "#FF0000" : "#000000"
                    }
                }

                NText{
                    anchors.verticalCenter: controlCycleBox.verticalCenter; anchors.left: controlCycleBox.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("control cycles")
                }

                NButton{
                    width: 70 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: controlCycleBox.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text.text: qsTr("Reset")
                    enabled: dlgModel.mProgress == 100

                    onClick: { dialog.cycleReset(controlCycleFunc);}
                }

                Rectangle{
                    id : totalControlCycleBox
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: controlCycleBox.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mTotalControlCycles
                        color: dlgModel.mErrTotalControlCycles ? "#FF0000" : "#000000"
                    }
                }

                NText{
                    anchors.verticalCenter: totalControlCycleBox.verticalCenter; anchors.left: controlCycleBox.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("total control cycles ( not resettable)")
                }
            }

            Rectangle{
                id : isolationCycleItem

                height: (GUISetting.margin + isolationCycleTitle.height) + (GUISetting.margin + isolationCycleBox.height) + (GUISetting.margin + totalIsolationCycleBox.height) + GUISetting.margin
                anchors.top: controlCycleItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : isolationCycleTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Isolation cycles")
                }

                Rectangle{
                    id : isolationCycleBox
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: isolationCycleTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mIsolationCycles
                        color: dlgModel.mErrIsolationCycles ? "#FF0000" : "#000000"
                    }
                }

                NText{
                    anchors.verticalCenter: isolationCycleBox.verticalCenter; anchors.left: isolationCycleBox.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("isolation cycles")
                }

                NButton{
                    width: 70 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: isolationCycleBox.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text.text: qsTr("Reset")
                    enabled: dlgModel.mProgress == 100

                    onClick: { dialog.cycleReset(isolationCycleFunc);}
                }

                Rectangle{
                    id : totalIsolationCycleBox
                    height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                    anchors.top: isolationCycleBox.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    color: "#E4E4E4"

                    NText{
                        width: parent.width - (GUISetting.margin * 2)
                        anchors.horizontalCenter: parent.horizontalCenter; anchors.verticalCenter: parent.verticalCenter
                        verticalAlignment: Text.AlignRight
                        text : dlgModel.mTotalIsolationCycles
                        color: dlgModel.mErrTotalIsolationCycles ? "#FF0000" : "#000000"
                    }
                }

                NText{
                    anchors.verticalCenter: totalIsolationCycleBox.verticalCenter; anchors.left: totalIsolationCycleBox.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("total isolation cycles ( not resettable)")
                }
            }
        }
    }
}
