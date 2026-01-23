import QtQuick.Window 2.12
import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.3
import QtGraphicalEffects 1.0

import GlobalUiValue 1.0
import GUISetting 1.0

import "../../usercomponent/."

import ViewTagContainerModel 1.0
import TagModel  1.0

Column {
    id : table

    property var componentArray : []

    property alias exStatus              : exStatus             ;
    property alias presInt               : presInt              ;
    property alias presFloat             : presFloat            ;
    property alias setPointInt           : setPointInt          ;
    property alias setPointFloat         : setPointFloat        ;
    property alias posiInt               : posiInt              ;
    property alias posiFloat             : posiFloat            ;
    property alias exDetailAlarm         : exDetailAlarm        ;
    property alias exDetailWarn          : exDetailWarn         ;
    property alias valveCloseOpenCheck   : valveCloseOpenCheck  ;
    property alias devStatus2            : devStatus2           ;
    property alias accMode               : accMode              ;
    property alias presCtrlMode          : presCtrlMode         ;
    property alias writeCtrlParamAnalyze : writeCtrlParamAnalyze;
    property alias adaptiveGain          : adaptiveGain         ;
    property alias adaptiveSensDelay     : adaptiveSensDelay    ;
    property alias adaptiveRampTime      : adaptiveRampTime     ;
    property alias adaptiveRampMode      : adaptiveRampMode     ;
    property alias fixedPGain            : fixedPGain           ;
    property alias fixedIGain            : fixedIGain           ;
    property alias fixedRampTime         : fixedRampTime        ;
    property alias fixedRampMode         : fixedRampMode        ;
    property alias fixedDir              : fixedDir             ;
    property alias adaptiveDeltaGain     : adaptiveDeltaGain    ;
    property alias sens1PresInt          : sens1PresInt         ;
    property alias sens1PresFloat        : sens1PresFloat       ;
    property alias sens2PresInt          : sens2PresInt         ;
    property alias sens2PresFloat        : sens2PresFloat       ;
    property alias dummy                 : dummy                ;

    signal checkApplyBtn();

    width: parent.width;
    spacing: 5;

    Component.onCompleted: {
        componentArray.push(exStatus             );
        componentArray.push(presInt              );
        componentArray.push(presFloat            );
        componentArray.push(setPointInt          );
        componentArray.push(setPointFloat        );
        componentArray.push(posiInt              );
        componentArray.push(posiFloat            );
        componentArray.push(exDetailAlarm        );
        componentArray.push(exDetailWarn         );
        componentArray.push(valveCloseOpenCheck  );
        componentArray.push(devStatus2           );
        componentArray.push(accMode              );
        componentArray.push(presCtrlMode         );
        componentArray.push(writeCtrlParamAnalyze);
        componentArray.push(adaptiveGain         );
        componentArray.push(adaptiveSensDelay    );
        componentArray.push(adaptiveRampTime     );
        componentArray.push(adaptiveRampMode     );
        componentArray.push(fixedPGain           );
        componentArray.push(fixedIGain           );
        componentArray.push(fixedRampTime        );
        componentArray.push(fixedRampMode        );
        componentArray.push(fixedDir             );
        componentArray.push(adaptiveDeltaGain    );
        componentArray.push(sens1PresInt         );
        componentArray.push(sens1PresFloat       );
        componentArray.push(sens2PresInt         );
        componentArray.push(sens2PresFloat       );
    }

    CustomLabel       { id: selV1Title           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Input Selector V1" ; visible: table.visible;}

    CustomCheckBox    { id: exStatus             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: presInt              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){presFloat.checked = false; presFloat.qmlValueChange()}}
    }
    CustomCheckBox    { id: presFloat            ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){presInt.checked = false; presInt.qmlValueChange()}}
    }
    CustomCheckBox    { id: setPointInt          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){setPointFloat.checked = false; setPointFloat.qmlValueChange()}}
    }
    CustomCheckBox    { id: setPointFloat        ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){setPointInt.checked = false; setPointInt.qmlValueChange()}}
    }
    CustomCheckBox    { id: posiInt              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){posiFloat.checked = false; posiFloat.qmlValueChange()}}
    }
    CustomCheckBox    { id: posiFloat            ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){posiInt.checked = false; posiInt.qmlValueChange()}}
    }
    CustomCheckBox    { id: exDetailAlarm        ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: exDetailWarn         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: valveCloseOpenCheck  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: devStatus2           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: accMode              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: presCtrlMode         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: writeCtrlParamAnalyze; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveGain         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveSensDelay    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveRampTime     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveRampMode     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedPGain           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedIGain           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedRampTime        ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedRampMode        ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedDir             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveDeltaGain    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: sens1PresInt         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){sens1PresFloat.checked = false ; sens1PresFloat.qmlValueChange()}}
    }
    CustomCheckBox    { id: sens1PresFloat       ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){sens1PresInt.checked = false;  sens1PresInt.qmlValueChange()}}
    }
    CustomCheckBox    { id: sens2PresInt         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){sens2PresFloat.checked = false ; sens2PresFloat.qmlValueChange()}}
    }
    CustomCheckBox    { id: sens2PresFloat       ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){sens2PresInt.checked = false;  sens2PresInt.qmlValueChange()}}
    }
    CustomCheckBox    { id: dummy                ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
}
