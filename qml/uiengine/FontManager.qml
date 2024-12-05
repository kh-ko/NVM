pragma Singleton
import QtQuick 2.0
import GUISetting 1.0

Item {
    //property  alias d2CodingName: d2Coding.name
    //property  alias godoBName: godoB.name
    property  alias codingName: coding.name
    property  alias nanumGothicName: nanumGothic.name
    property  alias nanumGothicBName: nanumGothicB.name
    property  var locale : Qt.locale("en-US")

    //FontLoader{
    //    id: d2Coding
    //    source: "qrc:uiengine/font/D2Coding.ttf"
    //}

    //FontLoader{
    //    id: godoB
    //    source: "qrc:uiengine/font/GodoB.ttf"
    //}

    FontLoader{
        id: coding
        source: "qrc:uiengine/font/SourceCodePro-Regular.ttf"
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
