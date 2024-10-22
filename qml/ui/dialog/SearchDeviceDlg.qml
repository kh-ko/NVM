import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import SearchDeviceDlgModel 1.0
import GUISetting 1.0

NWindow {
    id : dialog

    signal selectPort(string connType, string portName)

    function selectPotion(optIdx)
    {
        model.onCommandSelOption(optIdx)
    }

    contentHeight: contentContainer.height; contentWidth: contentContainer.width

    SearchDeviceDlgModel{
        id : model

        Component.onCompleted: {
            for(var i = 0; i < model.onCommandGetOptionCount(); i ++)
            {
                var name = model.onCommandGetOptionName(i);
                var isSelect = model.onCommandGetOptionIsSelect(i);
                listOptModel.append({"optIdx" : i, "optName" : name, "optIsSelect" : isSelect})
            }
        }

        onSignalEventChangedPortList:
        {
            listModel.clear()

            for(var i = 0; i < model.onCommandGetPortListCount(); i ++)
            {
                var connType = model.onCommandGetConnType(i)
                var portName = model.onCommandGetPortName(i);
                var serial   = model.onCommandGetSerial(i);
                var isReady  = model.onCommandIsReady(i);
                listModel.append({"connType":connType,"portName":portName,"serial":serial, "isReady" : isReady })
            }
        }
    }

    Item{
        id : contentContainer
        height: 500 * GUISetting.scale; width: 500 * GUISetting.scale
        anchors.centerIn: parent

        NPopupTilte{
            id : titleBox
            root: dialog
            title: qsTr("Port Selection")

            onClickClose: {
                dialog.close();
            }
        }

        Rectangle{
            color : "#E4E4E4"
            anchors.top: titleBox.bottom; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right;

        }

        Rectangle{
            id : optSelectBox
            color : "#FFFFFF"
            height: 50 * GUISetting.scale
            anchors.top: titleBox.bottom; anchors.topMargin: GUISetting.line_margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.line_margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.line_margin

            ListView {
                id: optList
                anchors.fill: parent; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; orientation: Qt.Horizontal  // 가로 방향 설정
                spacing: GUISetting.margin;
                clip : true

                model : ListModel{
                    id : listOptModel
                }

                delegate: NButton{
                    height: GUISetting.btn_nor_height; width: 150 * GUISetting.scale
                    anchors.verticalCenter: parent.verticalCenter
                    text.text: optName

                    onClick: {
                        optIsSelect = !optIsSelect
                        dialog.selectPotion(optIdx)
                    }

                    Rectangle{
                        width: GUISetting.on_indi_width; height: GUISetting.on_indi_height
                        anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                        radius: (width / 2) + 1
                        color: optIsSelect ? "#24A7FF" : "#E4E4E4"
                    }
                }
            }
        }

        ListView{
            id : portList
            anchors.top: optSelectBox.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: parent.bottom; anchors.bottomMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin

            spacing: GUISetting.margin;
            clip : true

            model : ListModel{
                id : listModel
            }

            delegate : Item{
                id : rowItem

                height: 50 * GUISetting.scale; width: parent.width
                enabled: isReady
                opacity: enabled ? 1 : 0.3

                BorderImage {
                    height: parent.height + 100; width: parent.width + 100
                    anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
                    source: "/image/card-2.png"
                    border.left: 50; border.top: 50
                    border.right: 50; border.bottom: 50
                }

                Rectangle{
                    anchors.fill: parent
                    color : itemMouseArea.containsPress ? "#19000000" : itemMouseArea.containsMouse ? "#29000000" : "#00000000"
                }

                NText{
                    id : portNameText
                    width: 100 * GUISetting.scale;
                    anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                    isBold: true
                    text : portName
                }

                NText{
                    anchors.left: portNameText.right; anchors.leftMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter
                    text : serial
                    color: "#24292e"
                }

                MouseArea{
                    id : itemMouseArea
                    anchors.fill: parent
                    hoverEnabled: isReady
                    enabled: isReady
                    onDoubleClicked: {
                        dialog.selectPort(connType, portName);
                        dialog.close();
                    }
                }
            }
        }
    }
}
