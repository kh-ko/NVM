pragma Singleton
import QtQuick 2.0

Item {
    property int refNonModalWindow : 0
    property int refModalWindow : 0
    property bool disableWinCreateBtn : refNonModalWindow > 0
    property bool needDim : refModalWindow > 0

    function addRefNonModalWindow()
    {
        refNonModalWindow = refNonModalWindow + 1

        console.debug("[khko_debug][addRefNonModalWindow]refNonModalWindow = " + refNonModalWindow + ", disableWinCreateBtn = " + disableWinCreateBtn)
    }
    function delRefNonModalWindow()
    {
        refNonModalWindow = refNonModalWindow - 1

        console.debug("[khko_debug][delRefNonModalWindow]refNonModalWindow = " + refNonModalWindow + ", disableWinCreateBtn = " + disableWinCreateBtn)
    }

    function addRefModalWindow()
    {
        refModalWindow = refModalWindow + 1

        console.debug("[khko_debug][addRefModalWindow]refModalWindow = " + refModalWindow)
    }
    function delRefModalWindow()
    {
        refModalWindow = refModalWindow - 1

        console.debug("[khko_debug][delRefModalWindow]refModalWindow = " + refModalWindow)
    }
}
