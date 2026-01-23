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

    property var componentArray      : []

    property alias ctrlMode          : ctrlMode         ;
    property alias setPointInt       : setPointInt      ;
    property alias setPointFloat     : setPointFloat    ;
    property alias setPointType      : setPointType     ;
    property alias learn             : learn            ;
    property alias learnPresLimInt   : learnPresLimInt  ;
    property alias learnPresLimFloat : learnPresLimFloat;
    property alias zero              : zero             ;
    property alias presCtrlMode      : presCtrlMode     ;
    property alias writeCtrlParam    : writeCtrlParam   ;
    property alias adaptiveGain      : adaptiveGain     ;
    property alias adaptiveSensDelay : adaptiveSensDelay;
    property alias adaptiveRampTime  : adaptiveRampTime ;
    property alias adaptiveRampMode  : adaptiveRampMode ;
    property alias fixedPGain        : fixedPGain       ;
    property alias fixedIGain        : fixedIGain       ;
    property alias fixedRampTime     : fixedRampTime    ;
    property alias fixedRampMode     : fixedRampMode    ;
    property alias fixedDir          : fixedDir         ;
    property alias adaptiveDeltaGain : adaptiveDeltaGain;
    property alias calibration       : calibration      ;
    property alias dummy             : dummy            ;

    signal checkApplyBtn();

    width: parent.width;
    spacing: 5;

    Component.onCompleted: {
        componentArray.push(ctrlMode         )
        componentArray.push(setPointInt      )
        componentArray.push(setPointFloat    )
        componentArray.push(setPointType     )
        componentArray.push(learn            )
        componentArray.push(learnPresLimInt  )
        componentArray.push(learnPresLimFloat)
        componentArray.push(zero             )
        componentArray.push(presCtrlMode     )
        componentArray.push(writeCtrlParam   )
        componentArray.push(adaptiveGain     )
        componentArray.push(adaptiveSensDelay)
        componentArray.push(adaptiveRampTime )
        componentArray.push(adaptiveRampMode )
        componentArray.push(fixedPGain       )
        componentArray.push(fixedIGain       )
        componentArray.push(fixedRampTime    )
        componentArray.push(fixedRampMode    )
        componentArray.push(fixedDir         )
        componentArray.push(adaptiveDeltaGain)
        componentArray.push(calibration      )
        componentArray.push(dummy            )
    }

    CustomLabel       { id: selV1Title        ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Output Selector V1"; visible: table.visible;}

    CustomCheckBox    { id: ctrlMode          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: setPointInt       ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){setPointFloat.checked = false; setPointFloat.qmlValueChange()}}
    }
    CustomCheckBox    { id: setPointFloat     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){setPointInt.checked = false; setPointInt.qmlValueChange()}}
    }
    CustomCheckBox    { id: setPointType      ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: learn             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: learnPresLimInt   ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){learnPresLimFloat.checked = false; learnPresLimFloat.qmlValueChange()}}
    }
    CustomCheckBox    { id: learnPresLimFloat ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}
        onClick: { if(checked){learnPresLimInt.checked = false; learnPresLimInt.qmlValueChange()}}
    }
    CustomCheckBox    { id: zero              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: presCtrlMode      ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: writeCtrlParam    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveGain      ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveSensDelay ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveRampTime  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveRampMode  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedPGain        ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedIGain        ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedRampTime     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedRampMode     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: fixedDir          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: adaptiveDeltaGain ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: calibration       ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomCheckBox    { id: dummy             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.checkApplyBtn()}}
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }

}
