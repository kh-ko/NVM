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

CustomWindow{
    id : win
    width: 400; height: 500; minWidth : 400
    title: qsTr("Power Connector I/O")

    property TagModel valveRev1Tag     : TagModel{}
    property TagModel valveRev2Tag     : TagModel{}
    property TagModel valveRev3Tag     : TagModel{}

    Component.onCompleted: {
        valveRev1Tag                   = findTag("System.Identification.Valve Revision (1)"        );
        valveRev2Tag                   = findTag("System.Identification.Valve Revision (2)"        );
        valveRev3Tag                   = findTag("System.Identification.Valve Revision (3)"        );

        di01Enable.viewTag   = findTag("Power Connector IO.Digital Input 1.Enable"       );
        di01Func.viewTag     = findTag("Power Connector IO.Digital Input 1.Functionality");
        di01Polarity.viewTag = findTag("Power Connector IO.Digital Input 1.Inverted"     );
        di01State.viewTag    = findTag("Power Connector IO.Digital Input 1.State"        );

        di02Enable.viewTag   = findTag("Power Connector IO.Digital Input 2.Enable"       );
        di02Func.viewTag     = findTag("Power Connector IO.Digital Input 2.Functionality");
        di02Polarity.viewTag = findTag("Power Connector IO.Digital Input 2.Inverted"     );
        di02State.viewTag    = findTag("Power Connector IO.Digital Input 2.State"        );

        do01Enable.viewTag   = findTag("Power Connector IO.Digital Output 1.Enable"       );
        do01Func.viewTag     = findTag("Power Connector IO.Digital Output 1.Functionality");
        do01Polarity.viewTag = findTag("Power Connector IO.Digital Output 1.Inverted"     );
        do01State.viewTag    = findTag("Power Connector IO.Digital Output 1.State"        );

        do02Enable.viewTag   = findTag("Power Connector IO.Digital Output 2.Enable"       );
        do02Func.viewTag     = findTag("Power Connector IO.Digital Output 2.Functionality");
        do02Polarity.viewTag = findTag("Power Connector IO.Digital Output 2.Inverted"     );
        do02State.viewTag    = findTag("Power Connector IO.Digital Output 2.State"        );

        regInitTag(valveRev1Tag     );
        regInitTag(valveRev2Tag     );
        regInitTag(valveRev3Tag     );

        regAlwaysReadComponent(di01State);
        regAlwaysReadComponent(di02State);
        regAlwaysReadComponent(do01State);
        regAlwaysReadComponent(do02State);

        regRWComponent(di01Enable  );
        regRWComponent(di01Func    );
        regRWComponent(di01Polarity);
        regRWComponent(di02Enable  );
        regRWComponent(di02Func    );
        regRWComponent(di02Polarity);
        regRWComponent(do01Enable  );
        regRWComponent(do01Func    );
        regRWComponent(do01Polarity);
        regRWComponent(do02Enable  );
        regRWComponent(do02Func    );
        regRWComponent(do02Polarity);

        checkApplyBtn()
        refresh()
    }

    Column{
        id : itemContainer

        anchors.top: parent.top; topPadding: 10; anchors.left: parent.left;
        width: minWidth > (win.scrollContainer.width - 10) ? (minWidth - 10) : (win.scrollContainer.width - 10);
        spacing: 10

        CustomLabel     { id: di01Title   ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Input 1"  ;}
        CustomComboBox  { id: di01Enable  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: di01Func    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: di01Polarity; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboLabel{ id: di01State   ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150;                                        }

        CustomDivider     {}

        CustomLabel     { id: di02Title   ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Input 2"  ;}
        CustomComboBox  { id: di02Enable  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: di02Func    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: di02Polarity; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboLabel{ id: di02State   ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150;                                        }

        CustomDivider     {}

        CustomLabel     { id: do01Title   ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Output 1"  ;}
        CustomComboBox  { id: do01Enable  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: do01Func    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: do01Polarity; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboLabel{ id: do01State   ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150;                                        }

        CustomDivider     {}

        CustomLabel     { id: do02Title   ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Output 2"  ;}
        CustomComboBox  { id: do02Enable  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: do02Func    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox  { id: do02Polarity; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboLabel{ id: do02State   ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150;                                        }

        CustomDivider     {}


    }
}
