import QtQuick 2.0

Item {
    property int    depth   : 0
    property alias  background : bg

    BorderImage {
        id: depthImage
        //source: "file"
        width: 100; height: 100
        border.left: 5; border.top: 5
        border.right: 5; border.bottom: 5
        visible: depth !== 0
    }

    Rectangle{
        id :bg
        anchors.fill: parent;
        border.width: 0;
    }
}
