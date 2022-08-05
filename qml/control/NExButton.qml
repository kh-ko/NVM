import QtQuick 2.0
import GUISetting 1.0

Item {
    id : control

    property bool isblock : false
    property bool isExpend : false
    property int  expendHeight : 30
    property alias titleBox : _titleBox
    property alias titleArrow :  _titleArrow
    property alias titleText :  _titleText

    width: parent.width; height: _titleBox.height;
    clip: true;

    states: State
    {
        name: "expend"
        when: control.isExpend
        PropertyChanges { target: control;     height   : expendHeight}
        PropertyChanges { target: _titleArrow; rotation : 90          }
    }

    transitions: Transition
    {
        id : trans
        from: ""
        to: "expend"
        reversible: true
        ParallelAnimation {
            NumberAnimation { target: control;     properties: "height"; duration: 250; easing.type: Easing.InOutQuad}
            NumberAnimation { target: _titleArrow; properties: "rotation"; duration: 250; easing.type: Easing.InOutQuad}
        }
    }

    onEnabledChanged: {
        if(!enabled)
            isExpend = false
    }

    Rectangle{
        id : _titleBox

        height: GUISetting.exbtn_title_height; width: parent.width - 25;
        z : 1
        enabled: control.enabled

        Image {
            id: _titleArrow
            width: GUISetting.exbtn_arrow_width; height: GUISetting.exbtn_arrow_height;
            anchors.left: parent.left; anchors.leftMargin: 10; anchors.verticalCenter: parent.verticalCenter
            opacity: control.enabled ? 1 : 0.3

            source: "/image/icon-arrow.png"
        }
        NText {
            id: _titleText
            anchors.left: _titleArrow.right; anchors.leftMargin: GUISetting.left_margin; anchors.verticalCenter: parent.verticalCenter
            opacity: control.enabled ? 1 : 0.3
            isBold: true
        }
        MouseArea{
            anchors.fill: parent

            onClicked: {
                control.isExpend = !control.isExpend;
            }
        }
    }
}
