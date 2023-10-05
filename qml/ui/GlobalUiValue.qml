pragma Singleton
import QtQuick 2.0

Item {
    property int refNonModalWindow : 0
    property int refModalWindow : 0
    property bool disableWinCreateBtn : refNonModalWindow > 0
    property bool needDim : false // refModalWindow > 0

    function addRefNonModalWindow()
    {
        refNonModalWindow = refNonModalWindow + 1
    }
    function delRefNonModalWindow()
    {
        refNonModalWindow = refNonModalWindow - 1
    }

    function addRefModalWindow()
    {
        refModalWindow = refModalWindow + 1
    }
    function delRefModalWindow()
    {
        refModalWindow = refModalWindow - 1
    }
}
