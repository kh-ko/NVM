import QtQuick 2.0
import QtQuick.Controls 2.14
import FontManager 1.0

Rectangle {
    id : control

    property string title : ""

    property alias btnApply   :  btnApplyComponent
    property alias btnRefresh :  btnRefreshComponent

    signal clickedApply();
    signal clickedRefresh();

    x:0; y:0; width : parent.width; height: 30; color: "#24292e"

    Text {
        anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter

        color: "#FFFFFF"
        font.family: FontManager.nanumGothicName
        font.pixelSize: 10
        elide: Text.ElideRight

        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignLeft

        text : control.title
    }

    Row{
        height: parent.height
        anchors.right: parent.right; anchors.rightMargin: 10; anchors.verticalCenter: parent.verticalCenter


        CustomTextButton{
            id : btnRefreshComponent
            height: parent.height
            textColor : "#FFFFFF"
            text : qsTr("Refresh")

            onClick: {control.clickedRefresh()}
        }

        CustomTextButton{
            id : btnApplyComponent
            height: parent.height
            textColor : "#FFFFFF"
            text : qsTr("Apply")

            onClick: {control.clickedApply()}
        }
    }
}
