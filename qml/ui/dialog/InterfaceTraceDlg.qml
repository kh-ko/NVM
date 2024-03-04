import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import QmlEnumDef 1.0
import InterfaceTraceDlgModel 1.0
import GUISetting 1.0

BaseSetupWindow{
    id : dialog

    property int  foundCount : 0
    property var  body : null

    titleText     : qsTr("Sequence Test")
    progress      : 100
    strStatus     : dlgModel.mStrStatus
    errMsg        : dlgModel.mErrMsg
    access        : dlgModel.mAccessMode
    isRS232Test   : dlgModel.mIsRS232Test
    isEdit        : dlgModel.mIsEdit

    Component.onCompleted: {
        body = bodyImpl.createObject(contentBody)
        bodyHeight = body.height
        bodyWidth = 700 * GUISetting.scale
    }

    InterfaceTraceDlgModel{
        id : dlgModel

        onSignalEventChangedFoundIdx: {
            if(mFoundIdx > (body.traceListModel.count -1) || mFoundIdx < 0)
                return;

            if(body.sortMode == 0)
            {
                body.dataListBody.positionViewAtIndex((body.traceListModel.count - 1) - mFoundIdx, ListView.Center)
            }
            else
            {
                body.dataListBody.positionViewAtIndex(0, ListView.Center)
            }
        }

        onSignalEventReceived: {
            if(body.sortMode == 0)
            {
                body.traceListModel.insert(0, {"rowIdx" : body.traceListModel.count, "localTime" : localTime, "interval" : interval, "receviedData" : receivedData, "transmittedData": transmittedData})
            }
            else
            {
                body.traceListModel.append({"rowIdx" : body.traceListModel.count, "localTime" : localTime, "interval" : interval, "receviedData" : receivedData, "transmittedData": transmittedData})
            }
        }

        onSignalEventClear: {
            body.traceListModel.clear();
        }
    }

    ListModel{
        id : itemModel
    }

    Component{
        id : bodyImpl

        Rectangle{
            property alias sortMode : sortCombo.currentIndex
            property alias dataListBody : _dataListBody
            property alias traceListModel : _traceListModel
            property real   guiScale            : GUISetting.scale

            height: (GUISetting.line_margin + recordBox.height) + (GUISetting.line_margin + searchBox.height) + (GUISetting.line_margin + tableBox.height) + (GUISetting.line_margin + btnBox.height + GUISetting.line_margin)
            anchors.left: parent.left; anchors.right: parent.right; anchors.top: parent.top

            color : "#E4E4E4"

            onGuiScaleChanged: {
                bodyHeight = height
                bodyWidth  = 700 * GUISetting.scale
            }

            Rectangle{
                id : recordBox
                height: GUISetting.margin + recordTitle.height + GUISetting.margin + recordCtrl.height + GUISetting.margin + recordSort.height + GUISetting.margin
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : recordTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Record")
                }

                Item{
                    id : recordCtrl
                    height: 44 * GUISetting.scale; width : parent.width
                    anchors.top: recordTitle.bottom; anchors.topMargin: GUISetting.margin

                    NButton{
                        id : recordButton
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin : GUISetting.margin
                        text.text: qsTr("Record")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                            radius: width * 0.5; color: "#24A7FF"
                            visible: dlgModel.mIsRecord
                        }

                        onClick: {
                            dlgModel.onCmdRecord(!dlgModel.mIsRecord, sortCombo.currentIndex)
                        }
                    }

                    NText{
                        id : recordTime
                        width: 70 * GUISetting.scale;
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: recordButton.right; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mRecordTime
                    }

                    NButton{
                        id : holdButton
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: recordTime.right; anchors.leftMargin : GUISetting.margin
                        enabled: dlgModel.mIsRecord
                        text.text: qsTr("Hold")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                            radius: width * 0.5; color: "#24A7FF"
                            visible: dlgModel.mIsHold
                        }
                        onClick: {
                            dlgModel.onCmdHold(!dlgModel.mIsHold)
                        }
                    }

                    NButton{
                        id : clearButton
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: holdButton.right; anchors.leftMargin : GUISetting.margin
                        text.text: qsTr("Clear")

                        onClick: dlgModel.onCmdClear()
                    }
                }

                Item{
                    id : recordSort
                    height: 44 * GUISetting.scale; width : parent.width
                    anchors.top: recordCtrl.bottom; anchors.topMargin: GUISetting.margin

                    NComboBox{
                        id : sortCombo
                        width: 120 * GUISetting.scale; height: 24 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        currentIndex: 0
                        enabled : !dlgModel.mIsRecord
                        model: ["Appened to Top","Append to Bottom"]

                        onCurrentIndexChanged: {
                            dlgModel.onCmdSetSortMode(currentIndex);
                        }
                    }

                    NText{
                        width: 120 * GUISetting.scale;
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: sortCombo.right; anchors.leftMargin: GUISetting.margin
                        text : qsTr("data acquisition")
                    }
                }
            }

            Rectangle{
                id : searchBox
                height: GUISetting.margin + searchTitle.height + GUISetting.margin + searchCtrl.height + GUISetting.margin + searchResult.height + GUISetting.margin
                anchors.top: recordBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : searchTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Search")
                }

                Item{
                    id : searchCtrl
                    height: 44 * GUISetting.scale; width : parent.width
                    anchors.top: searchTitle.bottom; anchors.topMargin: GUISetting.margin

                    NInputText{
                        id : searchText
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale;
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin

                    }

                    NButton{
                        id : searchButton
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: searchText.right; anchors.leftMargin : GUISetting.margin
                        text.text: qsTr("Search")

                        onClick: {
                            dlgModel.onCmdSearch(sortCombo.currentIndex, searchText.textField.text)
                        }
                    }

                    NButton{
                        id : preButton
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: searchButton.right; anchors.leftMargin : GUISetting.margin
                        text.text: qsTr("Pre")

                        onClick: {
                            console.debug("search pre")
                            dlgModel.onCmdSearchPre(sortCombo.currentIndex, searchText.textField.text)
                        }
                    }

                    NButton{
                        id : nextButton
                        height: 24 * GUISetting.scale; width: 100 * GUISetting.scale
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: preButton.right; anchors.leftMargin : GUISetting.margin
                        text.text: qsTr("Next")

                        onClick: {
                            console.debug("search next")
                            dlgModel.onCmdSearchNext(sortCombo.currentIndex, searchText.textField.text)
                        }
                    }
                }

                Item{
                    id : searchResult
                    height: 24 * GUISetting.scale; width : parent.width
                    anchors.top: searchCtrl.bottom; anchors.topMargin: GUISetting.margin

                    NText{
                        id : searchResultLabel
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        text: qsTr("total count : ")
                    }

                    NText{
                        anchors.verticalCenter: parent.verticalCenter; anchors.left: searchResultLabel.right; anchors.leftMargin: GUISetting.margin
                        text : dlgModel.mFoundCount
                    }
                }
            }

            Rectangle{
                id : tableBox
                height: GUISetting.margin + tableTitle.height + GUISetting.margin + dataList.height + GUISetting.margin
                anchors.top: searchBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                NText{
                    id : tableTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("Trace data")
                }

                Rectangle{
                    id : dataList
                    height: 300 * GUISetting.scale;
                    anchors.top: tableTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;
                    color : "#E4E4E4"

                    RowLayout
                    {
                        id : dataListHeader
                        height: 24 * GUISetting.scale;
                        anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;
                        spacing: GUISetting.line_margin

                        Rectangle{
                            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                            color : "#24A7FF"
                            NText{
                                anchors.fill: parent
                                color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                                text: qsTr("local time")
                            }
                        }

                        Rectangle{
                            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                            color : "#24A7FF"
                            NText{
                                anchors.fill: parent
                                color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                                text: qsTr("interval(msec)")
                            }
                        }

                        Rectangle{
                            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
                            color : "#24A7FF"
                            NText{
                                anchors.fill: parent
                                color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                                text: qsTr("received data")
                            }
                        }

                        Rectangle{
                            Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
                            color : "#24A7FF"
                            NText{
                                anchors.fill: parent
                                color: "#FFFFFF"; horizontalAlignment: Text.AlignHCenter; verticalAlignment: Text.AlignVCenter
                                text: qsTr("transmitted data")
                            }
                        }
                    }

                    NScrollView
                    {
                        id : _dataListBody
                        anchors.top: dataListHeader.bottom; anchors.topMargin: GUISetting.line_margin; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right
                        spacing: GUISetting.line_margin;
                        model : ListModel{
                            id : _traceListModel
                        }

                        delegate: RowLayout
                        {
                            property int    _rowIdx          : rowIdx
                            property string _localTime       : localTime
                            property string _interval        : interval
                            property string _receviedData    : receviedData
                            property string _transmittedData : transmittedData

                            height: 24 * GUISetting.scale;
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin;
                            spacing: GUISetting.line_margin

                            Rectangle{
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                                color : _rowIdx == dlgModel.mFoundIdx ? "#24A7FF" : "#FFFFFF"
                                NText{
                                    height: parent.height; width: parent.width - (GUISetting.margin) * 2
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    color: "#000000"; verticalAlignment: Text.AlignVCenter
                                    text: _localTime
                                }
                            }

                            Rectangle{
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1
                                color : _rowIdx == dlgModel.mFoundIdx ? "#24A7FF" : "#FFFFFF"
                                NText{
                                    height: parent.height; width: parent.width - (GUISetting.margin) * 2
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    color: "#000000"; verticalAlignment: Text.AlignVCenter
                                    text: interval
                                }
                            }

                            Rectangle{
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
                                color : _rowIdx == dlgModel.mFoundIdx ? "#24A7FF" : "#FFFFFF"
                                NText{
                                    height: parent.height; width: parent.width - (GUISetting.margin) * 2
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    color: "#000000"; verticalAlignment: Text.AlignVCenter
                                    text: receviedData
                                }
                            }

                            Rectangle{
                                Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 3
                                color : _rowIdx == dlgModel.mFoundIdx ? "#24A7FF" : "#FFFFFF"
                                NText{
                                    height: parent.height; width: parent.width - (GUISetting.margin) * 2
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    color: "#000000"; verticalAlignment: Text.AlignVCenter
                                    text: transmittedData
                                }
                            }
                        }
                    }
                }
            }

            Rectangle{
                id : btnBox
                height: 70 * GUISetting.scale;
                anchors.top: tableBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

                color: "#FFFFFF"

                RowLayout{
                    height: 50 * GUISetting.scale; width: parent.width * 0.7
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    spacing: GUISetting.margin

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

                        enabled: !dlgModel.mIsRecord
                        bgColor: "#FFFFFF"
                        text.text: qsTr("Open")

                        onClick: {
                            rFileDialog.open()
                        }
                    }

                    NButton{
                        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 1

                        bgColor: "#FFFFFF"
                        text.text: qsTr("Save")

                        onClick: {
                            wFileDialog.open()
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
                dlgModel.onCmdSaveFile(currentFile.toString().split("///")[1])
                //dlgModel.onCommandSaveSeqTestList()
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
            dlgModel.onCmdOpenFile(currentFile.toString().split("///")[1])
        }
        onRejected: {
        }
        visible : false
    }
}
