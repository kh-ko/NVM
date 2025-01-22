import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupEtherCATDlgModel 1.0
import InterfaceSetupEthCATItemModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24 * GUISetting.scale
    property var body : null

    titleText   : qsTr("Interface setup(EtherCAT)")
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
        var diFunction = body.diFunctionCombo.currentIndex
        var diMode     = body.diModeCombo.currentIndex
        var diInput    = body.diInputCombo.currentIndex
        var doFunction = body.doFunctionCombo.currentIndex
        var doMode     = body.doModeCombo.currentIndex
        var doOutput   = body.doOutputCombo.currentIndex
        var ethCATDevID = parseInt(body.ethDevID.text)

        dlgModel.onCommandApply(diFunction, diMode, diInput, doFunction, doMode, doOutput, ethCATDevID)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 700 * GUISetting.scale
    }

    InterfaceSetupEtherCATDlgModel{
        id : dlgModel

        Component.onCompleted : {
            pdoListModel.append({"pdoDataName" : "pressure"                     , "itemIdx":0})
            pdoListModel.append({"pdoDataName" : "pressure sensor 1"            , "itemIdx":1})
            pdoListModel.append({"pdoDataName" : "pressure sensor 2"            , "itemIdx":2})
            pdoListModel.append({"pdoDataName" : "position"                     , "itemIdx":3})
            pdoListModel.append({"pdoDataName" : "target position"              , "itemIdx":4})
            pdoListModel.append({"pdoDataName" : "cluster valve position"       , "itemIdx":5})
            pdoListModel.append({"pdoDataName" : "pressure setpoint"            , "itemIdx":6})
            pdoListModel.append({"pdoDataName" : "position setpoint"            , "itemIdx":7})
            pdoListModel.append({"pdoDataName" : "pressure alignment setpoint"  , "itemIdx":8})
            pdoListModel.append({"pdoDataName" : "external digital pressure 1"  , "itemIdx":9})
            pdoListModel.append({"pdoDataName" : "external digital pressure 2"  , "itemIdx":10})
            pdoListModel.append({"pdoDataName" : "cluster valve freeze position", "itemIdx":11})
        }

        onSignalEventCompletedLoad: {
            body.diFunctionCombo.currentIndex  = dlgModel.mDIFunction
            body.diModeCombo.currentIndex      = dlgModel.mDIMode
            body.diInputCombo.currentIndex     = dlgModel.mDIInput
            body.doFunctionCombo.currentIndex  = dlgModel.mDOFunction
            body.doModeCombo.currentIndex      = dlgModel.mDOMode
            body.doOutputCombo.currentIndex    = dlgModel.mDOOutput

            onCommandSetEdit(false);
        }
    }

    ListModel{
        id : pdoListModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias diFunctionCombo : _diFunctionCombo
            property alias diModeCombo     : _diModeCombo
            property alias diInputCombo    : _diInputCombo
            property alias doFunctionCombo : _doFunctionCombo
            property alias doModeCombo     : _doModeCombo
            property alias doOutputCombo   : _doOutputCombo
            property alias ethDevID        : _ethDevID
            property real  guiScale        : GUISetting.scale

            height: (GUISetting.line_margin + commParams.height) + (GUISetting.line_margin + pdoDataItem.height) + (GUISetting.line_margin + diItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = 700 * GUISetting.scale
            }

            Rectangle{
                id : commParams

                height: (GUISetting.margin + commParamsTitle.height) + (GUISetting.margin + _ethDevID.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : commParamsTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Communication parameters")
                }

                NText{
                    id : _ethDevID
                    height: 24 * GUISetting.scale
                    anchors.top: commParamsTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: false
                    text : qsTr("Device ID :   ") + dlgModel.mDevID
                }
            }

            Rectangle{
                id : pdoDataItem

                height: (GUISetting.margin + pdoDataTitle.height) + (GUISetting.margin + pdoListHeader.height) + (GUISetting.line_margin + pdoListView.height) + GUISetting.margin
                anchors.top: commParams.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : pdoDataTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("PDO data")
                }

                InterfaceSetupEtherCATPDOItem{
                    id : pdoListHeader
                    height: 34 * GUISetting.scale
                    anchors.top: pdoDataTitle.bottom; anchors.topMargin : GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    isHeader  : true; item01Name: qsTr("data name"); item02Name: qsTr("data type"); item03Name: qsTr("range(from)"); item04Name: qsTr("range(to)"); itemModel : dlgModel.onCommandGetPDOItem(0)
                }

                NScrollView{
                    id : pdoListView
                    height: 250 * GUISetting.scale
                    anchors.top: pdoListHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: pdoListHeader.left; anchors.right: pdoListHeader.right;
                    spacing : GUISetting.line_margin

                    model: pdoListModel

                    delegate : InterfaceSetupEtherCATPDOItem{
                        height: 34 * GUISetting.scale; width: pdoListView.width
                        isHeader  : false; item01Name: pdoDataName; itemModel: dlgModel.onCommandGetPDOItem(itemIdx)
                        enabled: dlgModel.mProgress == 100 ? true : false

                        onSelDataTypeChanged:
                        {
                            dlgModel.onCommandChangeDataType(selDataType);
                        }
                    }
                }
            }

            Rectangle{
                id : diItem

                height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + _diFunctionCombo.height) + (GUISetting.margin + _diModeCombo.height) + (GUISetting.margin + _diInputCombo.height) + GUISetting.margin;
                width: (parent.width - (GUISetting.line_margin * 3)) / 2
                anchors.top: pdoDataItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : diTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Digital inputs")
                }

                NComboBox{
                    id : _diFunctionCombo
                    width : 200 * GUISetting.scale
                    height: 24  * GUISetting.scale
                    anchors.top: diTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIFunction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["interlock close","interlock open"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diFunctionCombo.verticalCenter; anchors.left: _diFunctionCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("function")
                }

                NComboBox{
                    id : _diModeCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diFunctionCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDIMode ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["no","yes"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diModeCombo.verticalCenter; anchors.left: _diModeCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("inverted")
                }

                NComboBox{
                    id : _diInputCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _diModeCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left : parent.left; anchors.leftMargin : GUISetting.margin

                    textColor: dlgModel.mErrDIInput ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["no","yes"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _diInputCombo.verticalCenter; anchors.left: _diInputCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("disable")
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
                    id : _doFunctionCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: doTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOFunction ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["close","open", "On"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doFunctionCombo.verticalCenter; anchors.left: _doFunctionCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("function")
                }

                NComboBox{
                    id : _doModeCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doFunctionCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOMode ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["no","yes"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doModeCombo.verticalCenter; anchors.left: _doModeCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("inverted")
                }

                NComboBox{
                    id : _doOutputCombo
                    width: 200 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _doModeCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    textColor: dlgModel.mErrDOOutput ? "#FF0000" : "#000000"
                    enabled: dialog.progress === 100

                    model: ["no","yes"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _doOutputCombo.verticalCenter; anchors.left: _doOutputCombo.right; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    text : qsTr("disable")
                }
            }

            Rectangle{
                id : btnBox
                height: GUISetting.popup_btnbox_height;
                anchors.top: diItem.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

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

                        onClick: {
                            if(dialog.access !== ValveEnumDef.ACCESS_LOCAL && dialog.isRS232Test == false)
                            {
                                dialog.openChangeAccessDlg()
                                return;
                            }

                            dialog.commit()
                        }
                    }

                    NButton{
                        id : exportToEDS
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                        enabled: dialog.progress === 100 && !dialog.isEdit

                        bgColor: "#FFFFFF"
                        text.text: qsTr("export configuration to XML file")

                        onClick: {
                            wFileDialog.open();
                        }
                    }
                }
            }
        }
    }

    FileDialog{
        id: wFileDialog
            title: qsTr("export configuration")
            //folder: "./"
            fileMode: FileDialog.SaveFile
            nameFilters: ["XML files (*.xml)"]

            onAccepted: {
                dlgModel.onCommandExportXML(currentFile.toString().split("///")[1])
            }
            onRejected: {
            }
            visible : false
    }
}
