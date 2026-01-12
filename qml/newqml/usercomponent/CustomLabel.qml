import QtQuick 2.0
import FontManager 1.0
import GUISetting 1.0

Text {
    id : control

    color: "#000000"
    font.family: FontManager.nanumGothicName
    font.pixelSize: 10
    elide: Text.ElideRight

    verticalAlignment: Text.AlignVCenter
    horizontalAlignment: Text.AlignLeft
}
