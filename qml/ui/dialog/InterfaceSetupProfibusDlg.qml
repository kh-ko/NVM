import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import InterfaceSetupProfibusDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    readonly property int emptyHeight : 24 * GUISetting.scale
    property var body : null
    property var company : ValveEnumDef.COMPANY_NOVA

    titleText   : qsTr("Interface setup(Profibus)")
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
        var type       = body.typeCombo.currentIndex
        var diFunction = body.diFunctionCombo.currentIndex
        var diMode     = body.diModeCombo.currentIndex
        var diInput    = body.diInputCombo.currentIndex
        var doFunction = body.doFunctionCombo.currentIndex
        var doMode     = body.doModeCombo.currentIndex
        var doOutput   = body.doOutputCombo.currentIndex
        var nodeAddr = parseInt(body.nodeAddr.textField.text)

        dlgModel.onCommandApply(type, diFunction, diMode, diInput, doFunction, doMode, doOutput, nodeAddr)
    }

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth  = 800 * GUISetting.scale
    }

    InterfaceSetupProfibusDlgModel{
        id : dlgModel

        Component.onCompleted : {
            pdoListModel.append({"pdoTypeName":"IN", "pdoDataName" : "pressure"                      , "itemIdx":0})
            pdoListModel.append({"pdoTypeName":"IN", "pdoDataName" : "pressure sensor 1"             , "itemIdx":1})
            pdoListModel.append({"pdoTypeName":"IN", "pdoDataName" : "pressure sensor 2"             , "itemIdx":2})
            pdoListModel.append({"pdoTypeName":"IN", "pdoDataName" : "position"                      , "itemIdx":3})
            pdoListModel.append({"pdoTypeName":"IN", "pdoDataName" : "target position"               , "itemIdx":4})
            //pdoListModel.append({"pdoTypeName":"IN", "pdoDataName" : "cluster valve position"        , "itemIdx":5})
            pdoListModel.append({"pdoTypeName":"OUT", "pdoDataName" : "pressure setpoint"            , "itemIdx":6})
            pdoListModel.append({"pdoTypeName":"OUT", "pdoDataName" : "position setpoint"            , "itemIdx":7})
            pdoListModel.append({"pdoTypeName":"OUT", "pdoDataName" : "pressure alignment setpoint"  , "itemIdx":8})
            pdoListModel.append({"pdoTypeName":"OUT", "pdoDataName" : "external digital pressure 1"  , "itemIdx":9})
            pdoListModel.append({"pdoTypeName":"OUT", "pdoDataName" : "external digital pressure 2"  , "itemIdx":10})
            //pdoListModel.append({"pdoTypeName":"OUT", "pdoDataName" : "cluster valve freeze position", "itemIdx":11})
        }

        onSignalEventCompletedLoad: {
            body.typeCombo.currentIndex    = dlgModel.mTypeIdx
            body.diFunctionCombo.currentIndex  = dlgModel.mDIFunction
            body.diModeCombo.currentIndex      = dlgModel.mDIMode
            body.diInputCombo.currentIndex     = dlgModel.mDIInput
            body.doFunctionCombo.currentIndex  = dlgModel.mDOFunction
            body.doModeCombo.currentIndex      = dlgModel.mDOMode
            body.doOutputCombo.currentIndex    = dlgModel.mDOOutput
            body.nodeAddr.textField.text   = ""+dlgModel.mNodeAddr

            onCommandSetEdit(false);
        }
    }

    ListModel{
        id : pdoListModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias typeCombo       : _typeCombo
            property alias diFunctionCombo : _diFunctionCombo
            property alias diModeCombo     : _diModeCombo
            property alias diInputCombo    : _diInputCombo
            property alias doFunctionCombo : _doFunctionCombo
            property alias doModeCombo     : _doModeCombo
            property alias doOutputCombo   : _doOutputCombo
            property alias nodeAddr        : _nodeAddr
            property alias baudRate        : _baudrateCombo
            property real  guiScale        : GUISetting.scale

            height: _typeCombo.currentIndex == 1 ? (GUISetting.line_margin + commParams.height) + (GUISetting.line_margin + pdoDataItem.height) + (GUISetting.line_margin + diItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
                                                 : (GUISetting.line_margin + commParams.height) + (GUISetting.line_margin + diItem.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            //onGuiScaleChanged: {
            //    bodyHeight = height
            //}

            onHeightChanged: {
                bodyHeight = height
                bodyWidth  = 800 * GUISetting.scale
            }

            Rectangle{
                id : commParams

                height: (GUISetting.margin + commParamsTitle.height) + (GUISetting.margin + _nodeAddr.height) + (GUISetting.margin + _baudrateCombo.height) + (GUISetting.margin + _typeCombo.height) + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : commParamsTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Communication parameters")
                }

                NInputNumber{
                    id : _nodeAddr

                    height: 24 * GUISetting.scale; width: 120 * GUISetting.scale
                    anchors.top: commParamsTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dlgModel.mProgress == 100

                    textField.validator: IntValidator{}
                    stepValue : 1; minValue:0; maxValue: 125
                    fixedN : 0

                    onChangedText: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _nodeAddr.verticalCenter; anchors.left: _nodeAddr.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrNodeAddr ? "#FF0000" : "#000000"
                    text : qsTr("Node address")
                }

                NComboBox{
                    id : _baudrateCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _nodeAddr.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dlgModel.mProgress == 100

                    model: ["auto"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _baudrateCombo.verticalCenter; anchors.left: _baudrateCombo.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrBaudrateIdx ? "#FF0000" : "#000000"
                    text : qsTr("baudrate")
                }

                NComboBox{
                    id : _typeCombo
                    width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                    anchors.top: _baudrateCombo.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    enabled: dlgModel.mProgress == 100

                    model: ["v1", "v2"]

                    onCurrentIndexChanged: {
                        dlgModel.onCommandSetEdit(true)
                    }
                }

                NText{
                    anchors.verticalCenter: _typeCombo.verticalCenter; anchors.left: _typeCombo.right; anchors.leftMargin: GUISetting.margin
                    color: dlgModel.mErrBaudrateIdx ? "#FF0000" : "#000000"
                    text : qsTr("type")
                }
            }

            Rectangle{
                id : pdoDataItem

                height: (GUISetting.margin + pdoDataTitle.height) + (GUISetting.margin + pdoListHeader.height) + (GUISetting.line_margin + pdoListView.height) + GUISetting.margin
                anchors.top: commParams.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                visible: _typeCombo.currentIndex == 1
                enabled: _typeCombo.currentIndex == 1
                color: "#FFFFFF"

                NText{
                    id : pdoDataTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("PDO data(1 ~ 12)")
                }

                InterfaceSetupProfibusPDOItem{
                    id : pdoListHeader
                    height: 34 * GUISetting.scale
                    anchors.top: pdoDataTitle.bottom; anchors.topMargin : GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                    isHeader  : true; typeName : qsTr("type"); indexName : qsTr("seq"); item01Name: qsTr("data name"); item02Name: qsTr("data type"); item03Name: qsTr("range(from)"); item04Name: qsTr("range(to)"); itemModel : dlgModel.onCommandGetPDOItem(0)
                }

                NScrollView{
                    id : pdoListView
                    height: 250 * GUISetting.scale
                    anchors.top: pdoListHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: pdoListHeader.left; anchors.right: pdoListHeader.right;
                    spacing : GUISetting.line_margin


                    model: pdoListModel

                    delegate : InterfaceSetupProfibusPDOItem{
                        height: 34 * GUISetting.scale; width: pdoListView.width
                        isHeader  : false; typeName : pdoTypeName; indexName : itemIdx + 1; item01Name: pdoDataName; itemModel: dlgModel.onCommandGetPDOItem(itemIdx)
                        enabled: dlgModel.mProgress == 100 ? true : false

                        onSelDataTypeChanged:
                        {
                            dlgModel.onCommandChangeDataType(selDataType);
                        }
                    }
                }
                Image {
                    width: pdoListView.width; height: 34 * GUISetting.scale;
                    anchors.left: pdoListView.left; anchors.right: pdoListView.right; anchors.bottom: pdoListView.bottom
                    source: "/image/dimming.png"
                    visible: !(pdoListView.contentY >= pdoListView.contentHeight - pdoListView.height)
                }
            }

            Rectangle{
                id : diItem

                height: (GUISetting.margin + diTitle.height) + (GUISetting.margin + _diFunctionCombo.height) + (GUISetting.margin + _diModeCombo.height) + (GUISetting.margin + _diInputCombo.height) + GUISetting.margin;
                width: (parent.width - (GUISetting.line_margin * 3)) / 2
                anchors.top: _typeCombo.currentIndex == 1 ? pdoDataItem.bottom : commParams.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

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
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                    enabled: dialog.progress === 100 && (dialog.company !== ValveEnumDef.COMPANY_APSYS)

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
                        enabled: dialog.progress === 100

                        bgColor: "#FFFFFF"
                        text.text: qsTr("export pdo settings to GSD file")

                        onClick: {
                            wFileDialog.protocolVersion = body.typeCombo.currentIndex;
                            wFileDialog.open();
                        }
                    }
                }
            }
        }
    }

    FileDialog{
        property int protocolVersion : 0

        id: wFileDialog
        title: qsTr("export pdo settings to GSD file")
        //folder: "./"
        fileMode: FileDialog.SaveFile
        nameFilters: ["GSD files (*.gsd)"]

        onAccepted: {
            dlgModel.onCommandExportGSD(protocolVersion, currentFile.toString().split("///")[1])
        }
        onRejected: {
        }
        visible : false
    }
}
