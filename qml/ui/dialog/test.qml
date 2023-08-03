import QtQuick 2.0

Item {
    width: 500
    height: 500

    Column {
        id: column

            anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 20
            anchors.verticalCenter: parent.verticalCenter;
            spacing: 10 * GUISetting.Scale

            Text{
                text: "abc"
            }
            Text{
                text: "abc"
            }
            Text{
                text: "abc"
            }
            Text{
                text: "abc"
            }
            Text{
                text: "abc"
            }
            Text{
                text: "abc"
            }

    }

}
