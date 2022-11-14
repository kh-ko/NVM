import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import Qt.labs.platform 1.1
import "../../control/."
import ValveEnumDef 1.0
import FontManager 1.0
import NChartView 1.0
import GraphAnalyzeDlgModel 1.0
import GUISetting 1.0

NWindow{ // khko_todo
    id : dialog


    function loadFromChart(srcChart)
    {
        if(srcChart === null)
            return;

        statusBar.errMsg = analyzeChart.onCommandLoadFromChart(srcChart)
        analyzeChart.onCommandUpdate()

    }

    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    GraphAnalyzeDlgModel{
        id :dlgModel
    }

    Item {
        id : contentContainer
        height: titleBox.height + body.height + statusBar.height; width: body.width
        anchors.centerIn: parent

        NPopupTilte{
            id : titleBox
            root: dialog
            enableMinimizeBtn: true
            title: qsTr("Graph analyze")

            onClickClose: {
                dialog.close();
            }
        }

        Rectangle{
            id : body
            height: (GUISetting.line_margin + graphSettingItem.height) + GUISetting.line_margin;
            width: ( GUISetting.line_margin + graphSettingItem.width) + (GUISetting.line_margin + graphItem.width + GUISetting.line_margin)
            anchors.left: parent.left; anchors.top: titleBox.bottom

            color : "#E4E4E4"

            Item{
                id : graphSettingItem

                height: 500 * GUISetting.scale; width: 150 * GUISetting.scale
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin;

                Rectangle{
                    id : posSettingItem

                    width: 150 * GUISetting.scale;
                    height:   (GUISetting.margin + posSettingTitle.height)
                            + (GUISetting.margin + posCurrDrawOn.height  )
                            + (GUISetting.margin + posTargetDrawOn.height)
                            + (GUISetting.margin + posAutoScale.height   ) + GUISetting.margin;
                    anchors.top: parent.top; anchors.left: parent.left;

                    color: "#FFFFFF"

                    NText{
                        id : posSettingTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text : qsTr("position graph settings")
                    }

                    NButton{
                        id : posCurrDrawOn
                        height: 24 * GUISetting.scale
                        anchors.top: posSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("actual on")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: analyzeChart.mY01Draw ? "#24A7FF" : "#E4E4E4"
                        }

                        onClick: {
                            analyzeChart.mY01Draw = !analyzeChart.mY01Draw;
                            analyzeChart.onCommandUpdate()
                        }
                    }

                    NButton{
                        id : posTargetDrawOn
                        height: 24 * GUISetting.scale
                        anchors.top: posCurrDrawOn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("target on")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: analyzeChart.mY01DashDraw ? "#24A7FF" : "#E4E4E4"
                        }

                        onClick: {
                            analyzeChart.mY01DashDraw = !analyzeChart.mY01DashDraw;
                            analyzeChart.onCommandUpdate()
                        }
                    }

                    NButton{
                        id : posAutoScale
                        height: 24 * GUISetting.scale
                        anchors.top: posTargetDrawOn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("Autoscale")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: analyzeChart.mYAxis01AutoScale ? "#24A7FF" : "#E4E4E4"
                        }

                        onClick: {
                            analyzeChart.mYAxis01AutoScale = !analyzeChart.mYAxis01AutoScale;
                            analyzeChart.onCommandUpdate()
                        }
                    }
                }

                Rectangle{
                    id : pressureSettingItem

                    width : 150 * GUISetting.scale
                    height:   (GUISetting.margin + pressureSettingTitle.height )
                            + (GUISetting.margin + pressureCurrDrawOn.height   )
                            + (GUISetting.margin + pressureTargetDrawOn.height )
                            + (GUISetting.margin + pressureLogarithmicOn.height)
                            + (GUISetting.margin + pressureAutoScale.height    ) + GUISetting.margin;
                    anchors.top: posSettingItem.bottom; anchors.topMargin: 2; anchors.left: parent.left;

                    color: "#FFFFFF"

                    NText{
                        id : pressureSettingTitle
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                        isBold: true
                        text : qsTr("pressure graph settings")
                    }

                    NButton{
                        id : pressureCurrDrawOn
                        height: 24 * GUISetting.scale
                        anchors.top: pressureSettingTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("actual on")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: analyzeChart.mY02Draw ? "#33CC33" : "#E4E4E4"
                        }

                        onClick: {
                            analyzeChart.mY02Draw = !analyzeChart.mY02Draw
                            analyzeChart.onCommandUpdate()
                        }
                    }

                    NButton{
                        id : pressureTargetDrawOn
                        height: 24 * GUISetting.scale
                        anchors.top: pressureCurrDrawOn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("target on")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: analyzeChart.mY02DashDraw ? "#33CC33" : "#E4E4E4"
                        }

                        onClick: {
                            analyzeChart.mY02DashDraw = !analyzeChart.mY02DashDraw
                            analyzeChart.onCommandUpdate()
                        }
                    }

                    NButton{
                        id : pressureLogarithmicOn
                        height: 24 * GUISetting.scale
                        anchors.top: pressureTargetDrawOn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("logarithmic on")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: analyzeChart.mYAxis02Log ? "#33CC33" : "#E4E4E4"
                        }

                        onClick: {
                            analyzeChart.mYAxis02Log = !analyzeChart.mYAxis02Log
                            analyzeChart.onCommandUpdate()
                        }
                    }

                    NButton{
                        id : pressureAutoScale
                        height: 24 * GUISetting.scale
                        anchors.top: pressureLogarithmicOn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("Autoscale")

                        Rectangle{
                            width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                            radius: width / 2
                            color: analyzeChart.mYAxis02AutoScale ? "#24A7FF" : "#E4E4E4"
                        }

                        onClick: {
                            analyzeChart.mYAxis02AutoScale = !analyzeChart.mYAxis02AutoScale;
                            analyzeChart.onCommandUpdate()
                        }
                    }
                }

                Rectangle{
                    width: 150 * GUISetting.scale; height: (GUISetting.margin + saveBtn.height) + (GUISetting.margin + loadBtn.height) + GUISetting.margin;
                    anchors.bottom: parent.bottom; anchors.bottomMargin: 2; anchors.left: parent.left;

                    color: "#FFFFFF"

                    NButton{
                        id : saveBtn
                        height: 24 * GUISetting.scale
                        anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("save")

                        onClick: {
                            saveFileDialog.open()
                        }
                    }

                    NButton{
                        id : loadBtn
                        height: 24 * GUISetting.scale
                        anchors.top: saveBtn.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin
                        text.text: qsTr("load")

                        onClick: {
                            loadFileDialog.open()
                        }
                    }
                }
            }

            Rectangle{
                id : graphItem
                height: 500 * GUISetting.scale; width: 800 * GUISetting.scale
                anchors.top: parent.top; anchors.topMargin: GUISetting.line_margin; anchors.left: graphSettingItem.right; anchors.leftMargin: GUISetting.line_margin;

                color: "#FFFFFF"

                NText{
                    id : paramGraphTitle
                    anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin
                    isBold: true
                    text : qsTr("graph")
                }

                NChartView{
                    id : analyzeChart
                    anchors.top: paramGraphTitle.bottom; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin

                    mYAxis01LogDecades : 5
                    mYAxis01Precision  : 8
                    mYAxis02LogDecades : 5
                    mYAxis02Precision  : 8
                    mPause : false
                    mDebug : true

                    Component.onCompleted: {
                        onCommandInit(FontManager.nanumGothicName, 8, "#24A7FF", "#33CC33", false, true, false, false, true, true, true, true)
                    }
                }
            }
        }

        NPopupStatusBar{
            id : statusBar

            height: 20 * GUISetting.scale; width: parent.width
            anchors.bottom: parent.bottom; anchors.left: parent.left

            progress : 100
            status   : ""
            errMsg   : ""
        }
    }

    FileDialog{
        id: saveFileDialog
        title: qsTr("Save graph")
        //folder: "./"
        fileMode: FileDialog.SaveFile
        nameFilters: ["Text files (*.png)"]

        onAccepted: {
            analyzeChart.grabToImage(function(result){
                result.saveToFile(currentFile.toString().split("///")[1]);
                //dlgModel.onCommandSaveToFile(currentFile.toString().split("///")[1], result.image)
                //containerModel.onCommandPrint();
            })

            //dlgModel.onCommandSaveToFile(currentFile.toString().split("///")[1], analyzeChart)
        }
        onRejected: {
        }
        visible : false
    }

    FileDialog{
        id: loadFileDialog
        title: qsTr("Load graph")
        //folder: "./"
        fileMode: FileDialog.OpenFile
        nameFilters: ["Text files (*.txt)"]

        onAccepted: {
            statusBar.errMsg = dlgModel.onCommandLoadFromFile(currentFile.toString().split("///")[1], analyzeChart)
            analyzeChart.onCommandUpdate();
        }
        onRejected: {
        }
        visible : false
    }
}

/*

*/
