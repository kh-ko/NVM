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

    function reCalAddr() {
        var currentOffset = 0; // 주소 누적값 초기화 (필요시 시작 주소로 변경)

        for (var i = 0; i < componentArray.length; i++) {
            var item = componentArray[i];

            if (item.checked === false) {
                // checked가 false이면 addr = 0
                item.addr = 0;
            } else {
                // checked가 true이면 현재 누적된 주소 할당
                item.addr = currentOffset;

                // Name에서 증가폭 추출 로직
                // 예: "My Name(4)" -> 4 추출
                var nameStr = item.viewTag.Name;
                var size = 0;

                // 정규표현식: 괄호 '(' 뒤에 숫자 '\d+' 가 있고 괄호 ')' 로 닫히는 패턴 찾기
                var match = nameStr.match(/\((\d+)\)/);

                if (match && match.length > 1) {
                    size = parseInt(match[1]); // 추출된 문자열을 정수로 변환
                } else {
                    console.warn("Size extraction failed for: " + nameStr);
                }

                // 다음 요소를 위해 주소 증가
                currentOffset += size;
            }
        }

        checkApplyBtn();
    }

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

    InterfaceDeviceNetV1CheckItem    { isHeader: true        ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; }
    InterfaceDeviceNetV1CheckItem    { id: ctrlMode          ; seqId: 1; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: setPointInt       ; seqId: 2; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){setPointFloat.checked = false; setPointFloat.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: setPointFloat     ; seqId: 3; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){setPointInt.checked = false; setPointInt.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: setPointType      ; seqId: 4; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: learn             ; seqId: 5; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: learnPresLimInt   ; seqId: 6; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){learnPresLimFloat.checked = false; learnPresLimFloat.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: learnPresLimFloat ; seqId: 7; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){learnPresLimInt.checked = false; learnPresLimInt.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: zero              ; seqId: 8; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: presCtrlMode      ; seqId: 9; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: writeCtrlParam    ; seqId: 10; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveGain      ; seqId: 11; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveSensDelay ; seqId: 12; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveRampTime  ; seqId: 13; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveRampMode  ; seqId: 14; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedPGain        ; seqId: 15; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedIGain        ; seqId: 16; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedRampTime     ; seqId: 17; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedRampMode     ; seqId: 18; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedDir          ; seqId: 19; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveDeltaGain ; seqId: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: calibration       ; seqId: 21; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: dummy             ; seqId: 22; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }
    CustomLabel       { height: 24; text:" " }

}
