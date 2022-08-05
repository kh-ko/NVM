import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import InterfaceSetupEthCATItemModel 1.0
import "../../control/."
import GUISetting 1.0

RowLayout {
    id : item

    property var isHeader  : false
    property var item01Name: ""
    property var item02Name: ""
    property var item03Name: ""
    property var item04Name: ""
    property InterfaceSetupEthCATItemModel itemModel
    property string fromValue : itemModel.mRangeFrom
    property string toValue : itemModel.mRangeTo
    property int    selDataType : itemModel.mDataType
    spacing: 1 * GUISetting.scale

    onFromValueChanged: {
        rangeFrom.textField.text = fromValue
    }

    onToValueChanged: {
        rangeTo.textField.text = toValue
    }

    IntValidator{
        id : intValidator
    }

    DoubleValidator{
        id : doubleValidator
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4

        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item01Name
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4

        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item02Name
            visible: item.isHeader
        }

        NComboBox{
            id : dataType
            height: 24 * GUISetting.scale
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;

            textColor: itemModel.mErrDataType ? "#FF0000" : "#000000"
            visible: !item.isHeader
            enabled: item.enabled
            currentIndex: itemModel.mDataType

            model: ["signed integer","floating"]

            onCurrentIndexChanged: {
                itemModel.mDataType = currentIndex
            }
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4

        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item03Name
            visible: item.isHeader
        }

        NInputNumber{
            id : rangeFrom

            height: 24 * GUISetting.scale
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;

            visible: !item.isHeader
            enabled: item.enabled

            textField.validator: item.itemModel.mDataType == 0 ?  intValidator : doubleValidator
            textField.color: itemModel.mErrRangeFrom ? "#FF0000" : "#000000"
            stepValue : 1; minValue:-1000000; maxValue: 1000000
            fixedN : item.itemModel.mDataType == 0 ? 0 : 5

            onFixedNChanged: {
                setTextByValue(parseFloat(itemModel.mRangeFrom))
                itemModel.mRangeFrom = textField.text
            }

            onChangedValue: {
                itemModel.mRangeFrom = textField.text
            }
        }
    }

    Rectangle{
        Layout.fillHeight: true; Layout.fillWidth: true; Layout.preferredWidth: 4

        color : item.isHeader ? "#24A7FF" : "#E4E4E4"

        NText{
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;
            isBold: item.isHeader
            text : item.item04Name
            visible: item.isHeader
        }

        NInputNumber{
            id : rangeTo

            height: 24 * GUISetting.scale
            anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin; anchors.verticalCenter: parent.verticalCenter;

            visible: !item.isHeader
            enabled: item.enabled

            textField.validator: item.itemModel.mDataType == 0 ?  intValidator : doubleValidator
            textField.color: itemModel.mErrRangeTo ? "#FF0000" : "#000000"
            stepValue : 1; minValue:-1000000; maxValue: 1000000
            fixedN : item.itemModel.mDataType == 0 ? 0 : 5

            onFixedNChanged: {
                setTextByValue(parseFloat(itemModel.mRangeTo))
                itemModel.mRangeTo = textField.text
            }

            onChangedValue: {
                itemModel.mRangeTo = textField.text
            }
        }
    }
}
