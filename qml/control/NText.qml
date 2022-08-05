import QtQuick 2.0
import FontManager 1.0
import GUISetting 1.0

Text {
    id : control
    property bool isBold   : false
    property int  fontSize : GUISetting.basic_font_size // 10

    color: "#000000"
    font.family: isBold ? FontManager.nanumGothicBName : FontManager.nanumGothicName
    font.bold: isBold
    font.pixelSize: control.fontSize
    elide: Text.ElideRight
}
