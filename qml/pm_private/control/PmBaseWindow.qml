import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import GlobalUiValue 1.0
import GUISetting 1.0

ApplicationWindow {
    id : baseWin

    property var itemArray : []
    property int minWidth : -1

    default property alias body: contentWrapper.data

    property alias scrollContainer :  container
    property alias btnApply        :  dlgTitle.btnApply
    property alias btnRefresh      :  dlgTitle.btnRefresh

    function refresh()
    {
        for(var i = 0; i < itemArray.length; i ++)
        {
            itemArray[i].remoteSync();
        }
    }

    function apply()
    {
        for(var i = 0; i < itemArray.length; i ++)
        {
            if(itemArray[i].isDirty)
            {
                itemArray[i].commit();
            }
        }
    }

    function checkApplyBtn()
    {
        for(var i = 0; i < itemArray.length; i ++)
        {
            if(itemArray[i].isDirty)
            {
                baseWin.btnApply.enabled = true;
                return;
            }
        }

        baseWin.btnApply.enabled = false;
    }

    background : Rectangle{
        id : background
        color: "#FFFFFF"
    }

    PmDialogTitle{
        id : dlgTitle
        title : baseWin.title
        x: 0; y: 0;
        width: (parent.width / GUISetting.scale) < minWidth ? minWidth : (parent.width / GUISetting.scale);
        height: 30

        transformOrigin: Item.TopLeft
        scale : GUISetting.scale

        onClickedApply: { baseWin.apply()}
        onClickedRefresh: { baseWin.refresh() }
    }

    Item {
        id: rootContainer
        anchors.left :parent.left; anchors.top: parent.top; anchors.topMargin: dlgTitle.height * GUISetting.scale; anchors.right: parent.right; anchors.bottom: parent.bottom; anchors.bottomMargin: dlgFooter.height * GUISetting.scale

        ScrollView{
            id: container
            x: 0; y: 0;

            width: rootContainer.width / GUISetting.scale;
            height: rootContainer.height / GUISetting.scale

            transformOrigin: Item.TopLeft
            scale : GUISetting.scale

            clip: true

            contentWidth: contentWrapper.width
            contentHeight: contentWrapper.height

            ScrollBar.horizontal.policy: ScrollBar.AsNeeded
            ScrollBar.vertical.policy: ScrollBar.AsNeeded

            Item {
                id: contentWrapper

                // 자식들이 배치된 영역만큼 자신의 크기를 늘림
                width: childrenRect.width
                height: childrenRect.height
            }
        }
    }

    PmDialogFooter{
        id : dlgFooter
        transformOrigin: Item.BottomLeft
        scale : GUISetting.scale
    }

    onClosing: {

        // [핵심 해결책]
        // 약간의 지연 후 자신을 파괴하여 타이머를 포함한 모든 자원을 해제
        baseWin.destroy();
    }
}
