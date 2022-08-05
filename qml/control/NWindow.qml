import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import GlobalUiValue 1.0

ApplicationWindow {
    id : nwindow

    property bool doNotDestroy : false
    property int contentWidth  : 0
    property int contentHeight : 0
    property bool isModal      : true

    modality: Qt.NonModal //modality: Qt.WindowModal
    color: "#00000000"
    flags: Qt.FramelessWindowHint | Qt.Window


    height: contentHeight + 4 ; width: contentWidth + 4

//    Component.completed: {
//        if(modality === Qt.NonModal)
//            GlobalUiValue.addRefNonModalWindow()
//    }

    onVisibleChanged:
    {
        console.debug("[khko_debug]win visible = " + nwindow.visible + ", modality = " + modality)

        if(isModal === false)
        {
            if(nwindow.visible == true)
                GlobalUiValue.addRefNonModalWindow()
            else if(nwindow.visible == false)
                GlobalUiValue.delRefNonModalWindow()
        }
        else
        {
            if(nwindow.visible == true)
                GlobalUiValue.addRefModalWindow()
            else if(nwindow.visible == false)
                GlobalUiValue.delRefModalWindow()
        }

        if(nwindow.visible)
            return;

        if(!doNotDestroy)
        {
            nwindow.destroy();
        }
    }

    background: Item{
        BorderImage {
            id : bgImage
            height: nwindow.height; width: nwindow.width
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            source: "/image/card-flat.png"
            border.left: 2; border.top: 2
            border.right: 2; border.bottom: 2
        }
    }
}
