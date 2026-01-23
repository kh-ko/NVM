import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0
import Qt.labs.platform 1.1

import GlobalUiValue 1.0
import GUISetting 1.0

import "./."
import ViewTagContainerModel 1.0
import FileHelper 1.0

ApplicationWindow {
    id : baseWin

    property var rwItemArray : []
    property int minWidth : -1
    property double progress : winTagContainer.mProgress

    default property alias body: contentWrapper.data

    property alias fileHelper      : winFileHelper
    property alias tagContainer    : winTagContainer
    property alias scrollContainer : container
    property alias btnApply        : dlgTitle.btnApply
    property alias btnRefresh      : dlgTitle.btnRefresh
    property alias btnCreateEds    : dlgTitle.btnCreateEds

    function findTag(tagPath)
    {
        return winTagContainer.getTag(tagPath)
    }

    function regInitComponent(initComponent)
    {
        winTagContainer.addInitTag(initComponent.viewTag)
    }

    function regInitTag(initTag)
    {
        winTagContainer.addInitTag(initTag)
    }

    function clearInitTagAndComponent()
    {
        winTagContainer.clearInitTag();
    }

    function regMonitoringComponent(monitoringComponent)
    {
        winTagContainer.addMonotoringTag(monitoringComponent.viewTag)
    }

    function regMonitoringTag(monitoringTag)
    {
        winTagContainer.addMonotoringTag(monitoringTag)
    }

    function clearMonitoringTagAndComponent()
    {
        winTagContainer.clearMonitoringTag();
    }

    function regRWComponent(rwComponent)
    {
        winTagContainer.addRWTag(rwComponent.viewTag)
        rwItemArray.push(rwComponent);
    }

    function clearRWComponent()
    {
        winTagContainer.clearRWTag();

        for(var i = 0; i < rwItemArray.length; i ++)
        {
            rwItemArray[i].isDirty = false;
        }

        rwItemArray = [];

        checkApplyBtn();
    }

    function regAlwaysReadComponent(readComponent)
    {
        winTagContainer.addAlwaysReadTag(readComponent.viewTag)
    }

    function clearAlwaysReadComponent()
    {
        winTagContainer.clearAlwaysReadTag();
    }

    function refresh()
    {
        winTagContainer.refresh();
    }

    function beforeProcApply()
    {

    }

    function apply()
    {
        beforeProcApply()

        for(var i = 0; i < rwItemArray.length; i ++)
        {
            if(rwItemArray[i].isDirty && rwItemArray[i].visible)
            {
                rwItemArray[i].updateTagWriteValue();
                rwItemArray[i].isDirty = false;
            }
        }
        winTagContainer.apply();
    }

    function checkApplyBtn()
    {
        for(var i = 0; i < rwItemArray.length; i ++)
        {
            if(rwItemArray[i].isDirty && rwItemArray[i].visible)
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

    ViewTagContainerModel{
        id : winTagContainer
    }

    FileHelper{
        id : winFileHelper
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

            enabled: winTagContainer.mProgress === 1

            onClickedApply: { baseWin.apply() }
            onClickedRefresh: { baseWin.refresh() }
            onClickedCreateEds: { newDNetEdsFileDialog.open() }
        }

        ScrollView{
            id: container
            anchors.left: parent.left; anchors.top: dlgTitle.bottom; anchors.right: parent.right; anchors.bottom: dlgFooter.top

            clip: true

            contentWidth: contentWrapper.width
            contentHeight: contentWrapper.height

            ScrollBar.horizontal.policy: contentWrapper.width > container.width ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff
            ScrollBar.vertical.policy: contentWrapper.height > container.height ? ScrollBar.AlwaysOn : ScrollBar.AlwaysOff

            Item {
                id: contentWrapper

                enabled: winTagContainer.mProgress === 1

                // 자식들이 배치된 영역만큼 자신의 크기를 늘림
                width: childrenRect.width
                height: childrenRect.height
            }
        }

        CustomFooter{
            id : dlgFooter
            progress : winTagContainer.mProgress
        }
    }

    onClosing: {

        // [핵심 해결책]
        // 약간의 지연 후 자신을 파괴하여 타이머를 포함한 모든 자원을 해제
        baseWin.destroy();
    }

    FileDialog{
        id: newDNetEdsFileDialog
        title: qsTr("export assembly settings")
        //folder: "./"
        fileMode: FileDialog.SaveFile
        nameFilters: ["EDS files (*.eds)"]

        onAccepted: {
            winFileHelper.createDNetEdsFile(currentFile.toString().split("///")[1])
        }
        onRejected: {
        }
        visible : false
    }
}
