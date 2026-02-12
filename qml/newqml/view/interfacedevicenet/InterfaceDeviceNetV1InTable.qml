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
        componentArray.push(dummy                );
    }

    CustomLabel       { id: selV1Title           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Input Selector V1" ; visible: table.visible;}

    InterfaceDeviceNetV1CheckItem    { isHeader: true           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; }
    InterfaceDeviceNetV1CheckItem    { id: exStatus             ; seqId: 1; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: presInt              ; seqId: 2; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){presFloat.checked = false; presFloat.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: presFloat            ; seqId: 3; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){presInt.checked = false; presInt.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: setPointInt          ; seqId: 4; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){setPointFloat.checked = false; setPointFloat.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: setPointFloat        ; seqId: 5; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){setPointInt.checked = false; setPointInt.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: posiInt              ; seqId: 6; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){posiFloat.checked = false; posiFloat.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: posiFloat            ; seqId: 7; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){posiInt.checked = false; posiInt.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: exDetailAlarm        ; seqId: 8 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: exDetailWarn         ; seqId: 9 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: valveCloseOpenCheck  ; seqId: 10; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: devStatus2           ; seqId: 11; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: accMode              ; seqId: 12; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: presCtrlMode         ; seqId: 13; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: writeCtrlParamAnalyze; seqId: 14; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveGain         ; seqId: 15; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveSensDelay    ; seqId: 16; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveRampTime     ; seqId: 17; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveRampMode     ; seqId: 18; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedPGain           ; seqId: 19; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedIGain           ; seqId: 20; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedRampTime        ; seqId: 21; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedRampMode        ; seqId: 22; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: fixedDir             ; seqId: 23; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: adaptiveDeltaGain    ; seqId: 24; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
    InterfaceDeviceNetV1CheckItem    { id: sens1PresInt         ; seqId: 25; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){sens1PresFloat.checked = false ; sens1PresFloat.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: sens1PresFloat       ; seqId: 26; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){sens1PresInt.checked = false;  sens1PresInt.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: sens2PresInt         ; seqId: 27; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){sens2PresFloat.checked = false ; sens2PresFloat.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: sens2PresFloat       ; seqId: 28; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}
        onClick: { if(checked){sens2PresInt.checked = false;  sens2PresInt.qmlValueChange()}}
    }
    InterfaceDeviceNetV1CheckItem    { id: dummy                ; seqId: 29; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200; visible: table.visible; onIsDirtyChanged: {table.reCalAddr()}}
}
