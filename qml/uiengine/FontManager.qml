pragma Singleton
import QtQuick 2.0
import GUISetting 1.0

Item {

    property  alias godoBName: godoB.name
    property  alias nanumGothicName: nanumGothic.name
    property  alias nanumGothicBName: nanumGothicB.name
    property  var locale : Qt.locale("en-US")

    FontLoader{
        id: godoB
        source: "qrc:uiengine/font/GodoB.ttf"
    }

    FontLoader{
        id: nanumGothic
        source: "qrc:uiengine/font/NanumBarunGothic.ttf"
    }

    FontLoader{
        id: nanumGothicB
        source: "qrc:uiengine/font/NanumBarunGothicBold.ttf"
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
