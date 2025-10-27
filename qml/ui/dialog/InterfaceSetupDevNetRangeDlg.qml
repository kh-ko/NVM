import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupDevNetRangeDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24 * GUISetting.scale
    property var body : null

    titleText   : qsTr("DNet Interface Range")
    progress    : dlgModel.mProgress
    strStatus   : dlgModel.mStrStatus
    errMsg      : dlgModel.mErrMsg
    errMsg2     : dlgModel.mErrMsg2
    access      : dlgModel.mAccessMode
    isRS232Test : dlgModel.mIsRS232Test
    isEdit      : false//dlgModel.mIsEdit
    //bodyWidth   : 700

    function commit()
    {
        dlgModel.onCommandApply()
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 800 * GUISetting.scale
    }

    InterfaceSetupDevNetRangeDlgModel{
        id : dlgModel

        Component.onCompleted : {
            pdoListModel.append({})
        }
    }

    ListModel{
        id : pdoListModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property real  guiScale        : GUISetting.scale

            height: 600
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = 800 * GUISetting.scale
            }

            Rectangle{
                id : mainContents
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.bottom: btnBox.top; anchors.bottomMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color : "#FFFFFF"

                NComboBox{
                    id : posiUnitCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    model: ["counts","percent","degrees"]

                    onCurrentIndexChanged: { dlgModel.onCommandAutoPosiRange(currentIndex) }
                }

                NText{
                    id : posiUnitLabel
                    anchors.verticalCenter: posiUnitCombo.verticalCenter; anchors.left: posiUnitCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("position unit")
                }

                NComboBox{
                    id : presUnitCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.verticalCenter: posiUnitLabel.verticalCenter; anchors.left: posiUnitLabel.right; anchors.leftMargin: GUISetting.margin * 2

                    model: ["counts","percent","psi","Torr","mTorr","bar","mbar","pa","atm"]

                    onCurrentIndexChanged: { dlgModel.onCommandAutoPressRange(currentIndex) }
                }

                NText{
                    anchors.verticalCenter: presUnitCombo.verticalCenter; anchors.left: presUnitCombo.right; anchors.leftMargin: GUISetting.margin
                    text : qsTr("pressure unit")
                }

                RowLayout{
                    id : listHeader
                    height: 24 * GUISetting.scale
                    anchors.top: posiUnitCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    spacing: 1 * GUISetting.scale

                    Rectangle{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4; color : "#24A7FF"

                        NText{
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter; isBold: true;
                            text : qsTr("data name")
                        }
                    }

                    Rectangle{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4; color : "#24A7FF"

                        NText{
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter; isBold: true;
                            text : qsTr("from")
                        }
                    }

                    Rectangle{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4; color : "#24A7FF"

                        NText{
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter; isBold: true;
                            text : qsTr("to")
                        }
                    }
                }

                NScrollView{
                    id : rangeList
                    anchors.top: listHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

                    model: pdoListModel

                    delegate : Item{
                        //property InterfaceSetupDevNetRangeDlgModel argDlgModel

                        height: 400 * GUISetting.scale; width : rangeList.width;

                        InterfaceSetupDevNetRangeDataItem{
                            id : item01;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: parent.top; anchors.left: parent.left
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(0);

                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item02;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item01.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(1);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item03;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item02.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(2);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item04;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item03.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(3);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item05;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item04.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(4);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item06;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item05.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(5);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item07;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item06.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(6);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item08;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item07.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(7);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item09;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item08.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(8);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item10;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item09.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(9);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item11;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item10.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(10);
                            onChangeValue: {dlgModel.onCommandSetEdit(true)}
                        }

                        InterfaceSetupDevNetRangeDataItem{
                            id : item12;
                            height: 34 * GUISetting.scale; width: rangeList.width
                            anchors.top: item11.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left;
                            progress: dialog.progress;

                            itemModel : dlgModel.onCommandGetItemModel(11);
                            onChangeValue: {dlgModel.onCommandSetEdit(true); console.debug("call onCommandSetEdit")}
                        }
                    }
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                RowLayout{
                    height: GUISetting.popup_btnbox_btn_height; width: parent.width * 0.7
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        id : applyBtn
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100

                        bgColor: "#24A7FF"
                        text.color: "#FFFFFF"
                        text.text: qsTr("Apply")

                        NCircleIndicator{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter

                            color: "#FF0000"
                            visible: dlgModel.mIsEdit
                        }

                        onClick: {
                            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                            {
                                dialog.openChangeAccessDlg()
                                return;
                            }

                            dialog.commit()
                        }
                    }
                }
            }
        }
    }
}
