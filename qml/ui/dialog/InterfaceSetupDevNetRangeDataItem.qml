import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import "../../control/."
import GUISetting 1.0

import InterfaceSetupDevNetRangeItemModel 1.0
import GUISetting 1.0


RowLayout {
    id : root
    property int    progress : 0
    property InterfaceSetupDevNetRangeItemModel itemModel : InterfaceSetupDevNetRangeItemModel{}

    signal changeValue();

    Connections {
        target: root.itemModel

        function onMTypeChanged(value){ console.debug("type = " + value) }
        function onMFromChanged(value){ fromItem.textField.text = value }
        function onMToChanged  (value){ toItem.textField.text   = value }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4; color : "#E4E4E4"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter; isBold: true;
            text : itemModel.mName
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4; color : "#E4E4E4"

        NInputNumber{
            id : fromItem
            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

            enabled: root.progress === 100

            textField.validator: DoubleValidator{}
            textField.color: root.itemModel.mErrFrom    ? "#FF0000" :
                             root.itemModel.mIsEditFrom ? "#24A7FF" : "#000000"
            stepValue : 0.0000001; minValue: 0; maxValue: 10000000000
            fixedN : 4

            onChangedText: { root.itemModel.onCommandSetEditFrom(textField.text); root.changeValue() }
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4; color : "#E4E4E4"

        NInputNumber{
            id : toItem
            width: 150 * GUISetting.scale; height: 24 * GUISetting.scale
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter

            enabled: root.progress === 100

            textField.validator: DoubleValidator{}
            textField.color: root.itemModel.mErrTo    ? "#FF0000" :
                             root.itemModel.mIsEditTo ? "#24A7FF" : "#000000"
            stepValue : 0.0000001; minValue: 0; maxValue: 10000000000
            fixedN : 4

            onChangedText: { root.itemModel.onCommandSetEditTo(textField.text); root.changeValue() }
        }
    }

}
