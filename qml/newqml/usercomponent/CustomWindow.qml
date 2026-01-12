import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import GlobalUiValue 1.0
import GUISetting 1.0

import "./."
import GeneralDlgModel 1.0

ApplicationWindow {
    id : baseWin

    property var rwItemArray : []
    property int minWidth : -1

    default property alias body: contentWrapper.data

    property alias viewModel       :  _viewModel
    property alias scrollContainer :  container
    property alias btnApply        :  dlgTitle.btnApply
    property alias btnRefresh      :  dlgTitle.btnRefresh

    function refresh()
    {
        _viewModel.refresh();
    }

    function apply()
    {
        for(var i = 0; i < rwItemArray.length; i ++)
        {
            if(rwItemArray[i].isDirty)
            {
                rwItemArray[i].updateTagWriteValue();
            }
        }
        _viewModel.apply();
    }

    function checkApplyBtn()
    {
        for(var i = 0; i < rwItemArray.length; i ++)
        {
            if(rwItemArray[i].isDirty)
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

    GeneralDlgModel{
        id : _viewModel
    }

    Item {
        id: rootContainer

        x:0; y:0
        transformOrigin: Item.TopLeft;
        scale : GUISetting.scale

        width: baseWin.contentItem.width / GUISetting.scale;
        height: baseWin.contentItem.height / GUISetting.scale

        CustomTitleBar{
            id : dlgTitle
            title : baseWin.title

            onClickedApply: {
                baseWin.apply()
            }
            onClickedRefresh: { baseWin.refresh() }
        }

        ScrollView{
            id: container
            anchors.left: parent.left; anchors.top: dlgTitle.bottom; anchors.right: parent.right; anchors.bottom: dlgFooter.top

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

        CustomFooter{
            id : dlgFooter
        }
    }

    onClosing: {

        // [핵심 해결책]
        // 약간의 지연 후 자신을 파괴하여 타이머를 포함한 모든 자원을 해제
        baseWin.destroy();
    }
}
