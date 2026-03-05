import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import GUISetting 1.0
import "./."

Popup {
    id : dialog

    property alias msgIcon : _msgIcon

    property bool doNotDestroy : false

    property var titleText : qsTr("title")
    property var contentText : qsTr("Message box content")
    property var okText : qsTr("Ok")
    property var noText : qsTr("No")

    signal result(bool bOk);

    contentHeight: 200 * GUISetting.scale; contentWidth: 500 * GUISetting.scale
    anchors.centerIn : parent
    topInset: 0; bottomInset: 0; leftInset: 0; rightInset: 0; topPadding: 0; bottomPadding: 0; leftPadding: 0; rightPadding: 0

    modal       : true
    dim         : true
    closePolicy : Popup.NoAutoClose


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

    contentItem: Item{
        Rectangle{
            color : "#FFFFFF"
            anchors.top: parent.top; anchors.bottom: parent.bottom; anchors.left: parent.left; anchors.right: parent.right;

            Image{
                id : _msgIcon
                anchors.top: parent.top; anchors.topMargin: GUISetting.margin; anchors.left: parent.left; anchors.leftMargin: GUISetting.margin;
            }

            CustomLabel{
                id : titleMsg
                anchors.verticalCenter: _msgIcon.verticalCenter;
                anchors.left: _msgIcon.right; anchors.leftMargin: GUISetting.margin;
                text : dialog.titleText
            }

            CustomLabel{
                anchors.top: titleMsg.bottom; anchors.topMargin: GUISetting.margin; anchors.bottom: btnBox.top;
                anchors.left: parent.left; anchors.leftMargin: GUISetting.margin; anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;
                lineHeight: 2
                verticalAlignment: Text.AlignVCenter
                text : dialog.contentText
            }

            Item{
                id : btnBox

                height: GUISetting.margin + btnOk.height + GUISetting.margin; width: parent.width
                anchors.bottom: parent.bottom

                CustomButton{
                    id : btnOk
                    height: (30 * GUISetting.scale); width: (160 * GUISetting.scale)

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: btnNo.left; anchors.rightMargin: GUISetting.margin;

                    text: dialog.okText
                    textColor: "#FFFFFF"
                    bgColor: "#24A7FF"

                    onClick: {
                        console.debug("OK-onClick")
                        dialog.result(true)

                        console.debug("OK-onClick : After")
                        dialog.close()
                    }
                }

                CustomButton{
                    id : btnNo
                    height: (30 * GUISetting.scale); width: (160 * GUISetting.scale)

                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right; anchors.rightMargin: GUISetting.margin;

                    text: dialog.noText

                    onClick: {
                        console.debug("Cancel-onClick")
                        dialog.result(false)
                        dialog.close()
                    }
                }
            }
        }
    }
}
