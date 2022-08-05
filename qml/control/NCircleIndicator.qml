import QtQuick 2.12
import QtQuick.Controls 2.12
import "./."

Rectangle {
    id: control
    property var running : true
    radius: width < height ? width/2 : height/2

    SequentialAnimation on opacity {
            loops: Animation.Infinite
            running:control.running

            PropertyAnimation { to: 1; duration : 500; easing.type : Easing.InOutExpo}
            PropertyAnimation { to: 0; duration : 500; easing.type : Easing.InOutExpo }
    }

}
