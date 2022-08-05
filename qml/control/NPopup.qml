import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3

Popup {
    id : dialog

    property bool doNotDestroy : false
    modal       : true
    dim         : true
    closePolicy : Popup.NoAutoClose

    contentHeight: 500; contentWidth: 500
    anchors.centerIn : parent
    topInset: 0; bottomInset: 0; leftInset: 0; rightInset: 0; topPadding: 0; bottomPadding: 0; leftPadding: 0; rightPadding: 0

    onVisibleChanged:
    {
        if(dialog.visible)
            return;

        if(!doNotDestroy)
            dialog.destroy();
    }

    background: Item{
        BorderImage {
            id : bgImage
            height: dialog.contentHeight + 100; width: dialog.contentWidth + 100
            anchors.verticalCenter: parent.verticalCenter; anchors.horizontalCenter: parent.horizontalCenter
            source: "/image/card-10.png"
            border.left: 50; border.top: 50
            border.right: 50; border.bottom: 50
        }
    }
}
