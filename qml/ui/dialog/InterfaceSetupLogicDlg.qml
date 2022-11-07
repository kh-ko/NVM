import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupLogicDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24
    property var body : null

    titleText   : qsTr("Interface setup(Logic)")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : dlgModel.mIsEdit

    function commit()
    {
        var diOpen       = body.diOpenCombo.currentIndex
        var diClose      = body.diCloseCombo.currentIndex
        var doOpen       = body.doOpenCombo.currentIndex
        var doClose      = body.doCloseCombo.currentIndex
        var learnRange   = body.learnRangeCombo.currentIndex

        dlgModel.onCommandApply(diOpen, diClose, doOpen, doClose, learnRange)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = GUISetting.popup_nor_width
    }

    InterfaceSetupLogicDlgModel{
        id : dlgModel

        onSignalEventCompletedLoad: {
            body.diOpenCombo.currentIndex         = dlgModel.mDIOpen
            body.diCloseCombo.currentIndex        = dlgModel.mDIClose
            body.doOpenCombo.currentIndex         = dlgModel.mDOOpen
            body.doCloseCombo.currentIndex        = dlgModel.mDOClose
            body.learnRangeCombo.currentIndex     = dlgModel.mLearnRange

            onCommandSetEdit(false);
        }
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias diOpenCombo       : _diOpenCombo
            property alias diCloseCombo      : _diCloseCombo
            property alias doOpenCombo       : _doOpenCombo
            property alias doCloseCombo      : _doCloseCombo
            property alias learnRangeCombo   : _learnRangeCombo
            property real  guiScale          : GUISetting.scale

            height: (GUISetting.line_margin + diItem.height) + (GUISetting.line_margin + learnRangeItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = GUISetting.popup_nor_width
            }

            Rectangle{
                id : diItem

                height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + _diOpenCombo.height) + (GUISetting.margin + _diCloseCombo.height) + GUISetting.margin;
                width: (parent.width - (GUISetting.line_margin * 3)) / 2
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : diTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital inputs")
                }

                NComboBox{
                    id : _diOpenCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIOpen ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not inverted","inverted"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diOpenCombo.verticalCenter; anchors.left: _diOpenCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("open input")
                }

                NComboBox{
                    id : _diCloseCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diOpenCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOOpen ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["not inverted","inverted"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diCloseCombo.verticalCenter; anchors.left: _diCloseCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("close input")
                }
            }

            Rectangle{
                id : doItem

                height: diItem.height; width: diItem.width
                anchors.verticalCenter: diItem.verticalCenter; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : doTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital output")
                }

                NComboBox{
                    id : _doOpenCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: doTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOOpen ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["open","warning"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doOpenCombo.verticalCenter; anchors.left: _doOpenCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("open output")
                }

                NComboBox{
                    id : _doCloseCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doOpenCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOClose ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["close","warning"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doCloseCombo.verticalCenter; anchors.left: _doCloseCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("close output")
                }
            }

            Rectangle{
                id : learnRangeItem

                height: GUISetting.margin + learnRangeTitle.height + GUISetting.margin + _learnRangeCombo.height + GUISetting.margin;
                anchors.top: diItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : learnRangeTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Learn range")
                }

                NComboBox{
                    id : _learnRangeCombo
                    width: 100 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: learnRangeTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrLearnRange ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["fullrange","analog input"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _learnRangeCombo.verticalCenter; anchors.left: _learnRangeCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("learn range")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: learnRangeItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NButton{
                    id : applyBtn
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width / 2
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    enabled: dialog.progress === 100

                    bgColor: "#24A7FF"
                    text.color: "#FFFFFF"
                    text.text: qsTr("Apply")

                    NCircleIndicator{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter

                        color: "#FF0000"
                        visible: dialog.isEdit
                    }

                    onClick: {
                        dialog.apply()
                    }
                }
            }
        }
    }
}
