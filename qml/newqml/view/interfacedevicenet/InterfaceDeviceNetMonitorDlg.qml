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
    width: 500; height: 500; minWidth : 500
    title: qsTr("Device NET Status")

    btnApply.visible: false
    btnRefresh.visible: false

    property TagModel valveTypeTag     : TagModel{}
    property TagModel valveRev1Tag     : TagModel{}
    property TagModel valveRev2Tag     : TagModel{}
    property TagModel valveRev3Tag     : TagModel{}
    property TagModel firmwareVerTag   : TagModel{}

    Component.onCompleted: {
        valveRev1Tag                         = findTag("System.Identification.Valve Revision (1)"                                                               ); // RO
        valveRev2Tag                         = findTag("System.Identification.Valve Revision (2)"                                                               ); // RO
        valveRev3Tag                         = findTag("System.Identification.Valve Revision (3)"                                                               ); // RO

        dnetStatus.viewTag                   = findTag("Interface DeviceNet.Status.Status"                                                                      ); // RO
        alarmDevComm.viewTag                 = findTag("Interface DeviceNet.Exception Status.ALARM/device-common"                                                );
        alarmDevSpecific.viewTag             = findTag("Interface DeviceNet.Exception Status.ALARM/device-specific"                                              );
        alarmMenuSpecific.viewTag            = findTag("Interface DeviceNet.Exception Status.ALARM/manufacturer-specific"                                        );
        warningDevComm.viewTag               = findTag("Interface DeviceNet.Exception Status.WARNING/device-common"                                              );
        warningDevSpecific.viewTag           = findTag("Interface DeviceNet.Exception Status.WARNING/device-specific"                                            );
        warningMenuSpecifi.viewTag           = findTag("Interface DeviceNet.Exception Status.WARNING/manufacturer-specific"                                      );
        expandedMode.viewTag                 = findTag("Interface DeviceNet.Exception Status.expanded mode"                                                      );

        macSwitch.viewTag                    = findTag("Interface DeviceNet.DeviceNet Object.Instance.MAC ID Switch"                                            ); // RO
        mac.viewTag                          = findTag("Interface DeviceNet.DeviceNet Object.Instance.MAC ID"                                                   ); // RW
        baudRate.viewTag                     = findTag("Interface DeviceNet.DeviceNet Object.Instance.Baud Rate"                                                ); // RW

        profile.viewTag                      = findTag("Interface DeviceNet.Connection Object.Profile.Profile"                                                  ); // RW
        dataType.viewTag                     = findTag("Interface DeviceNet.Connection Object.Profile.Data Type"                                                ); // RW

        //outName.viewTag                      = findTag("Interface DeviceNet.Connection Object.Output.Output Name"                                               ); // RO
        //outLen.viewTag                       = findTag("Interface DeviceNet.Connection Object.Output.Output length (Byte)"                                      ); // RO

        //outV1Tb.ctrlMode.viewTag             = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Control Model(1)"                ); // RW
        //outV1Tb.setPointInt.viewTag          = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Setpoint-INT(2)"                 ); // RW
        //outV1Tb.setPointFloat.viewTag        = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Setpoint-FLOAT(4)"               ); // RW
        //outV1Tb.setPointType.viewTag         = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Setpoint type(1)"                ); // RW
        //outV1Tb.learn.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Learn(1)"                        ); // RW
        //outV1Tb.learnPresLimInt.viewTag      = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Learn pressure limit-INT(2)"     ); // RW
        //outV1Tb.learnPresLimFloat.viewTag    = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Learn pressure limit-FLOAT(4)"   ); // RW
        //outV1Tb.zero.viewTag                 = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Zero(1)"                         ); // RW
        //outV1Tb.presCtrlMode.viewTag         = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Pressure control mode(1)"        ); // RW
        //outV1Tb.writeCtrlParam.viewTag       = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Write control parameter(1)"      ); // RW
        //outV1Tb.adaptiveGain.viewTag         = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive gain(4)"                ); // RW
        //outV1Tb.adaptiveSensDelay.viewTag    = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive sensor delay(4)"        ); // RW
        //outV1Tb.adaptiveRampTime.viewTag     = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive ramp time(4)"           ); // RW
        //outV1Tb.adaptiveRampMode.viewTag     = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive ramp mode(1)"           ); // RW
        //outV1Tb.fixedPGain.viewTag           = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed P-gain(4)"                 ); // RW
        //outV1Tb.fixedIGain.viewTag           = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed I-Gain(4)"                 ); // RW
        //outV1Tb.fixedRampTime.viewTag        = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed ramp time(4)"              ); // RW
        //outV1Tb.fixedRampMode.viewTag        = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed ramp mode(1)"              ); // RW
        //outV1Tb.fixedDir.viewTag             = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed direction mode(1)"         ); // RW
        //outV1Tb.adaptiveDeltaGain.viewTag    = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive delta gain(4)"          ); // RW
        //outV1Tb.calibration.viewTag          = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Calibration(1)"                  ); // RW
        //outV1Tb.dummy.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Dummy(1)"                        ); // RW

        //inName.viewTag                       = findTag("Interface DeviceNet.Connection Object.Input.Input Name"                                                 ); // RO
        //inLen.viewTag                        = findTag("Interface DeviceNet.Connection Object.Input.Input length (Byte)"                                        ); // RO

        //inV1Tb.exStatus.viewTag              = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Exception Status(1)"               ); // RW
        //inV1Tb.presInt.viewTag               = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Pressure-INT(2)"                   ); // RW
        //inV1Tb.presFloat.viewTag             = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Pressure-FLOAT(4)"                 ); // RW
        //inV1Tb.setPointInt.viewTag           = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Setpoint-INT(2)"                   ); // RW
        //inV1Tb.setPointFloat.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Setpoint-FLOAT(4)"                 ); // RW
        //inV1Tb.posiInt.viewTag               = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Position-INT(2)"                   ); // RW
        //inV1Tb.posiFloat.viewTag             = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Position-FLOAT(4)"                 ); // RW
        //inV1Tb.exDetailAlarm.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Exception Detail Alarm(15)"        ); // RW
        //inV1Tb.exDetailWarn.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Exception Detail Warning(15)"      ); // RW
        //inV1Tb.valveCloseOpenCheck.viewTag   = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Valve Close/Open Check(1)"         ); // RW
        //inV1Tb.devStatus2.viewTag            = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Device Status 2(1)"                ); // RW
        //inV1Tb.accMode.viewTag               = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Access Mode(1)"                    ); // RW
        //inV1Tb.presCtrlMode.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Pressure control Mode(1)"          ); // RW
        //inV1Tb.writeCtrlParamAnalyze.viewTag = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Write Control Parameter Analyze(1)"); // RW
        //inV1Tb.adaptiveGain.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Gain(4)"                  ); // RW
        //inV1Tb.adaptiveSensDelay.viewTag     = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Sensor Delay(4)"          ); // RW
        //inV1Tb.adaptiveRampTime.viewTag      = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Ramp Time(4)"             ); // RW
        //inV1Tb.adaptiveRampMode.viewTag      = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Ramp Mode(1)"             ); // RW
        //inV1Tb.fixedPGain.viewTag            = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed P-Gain(4)"                   ); // RW
        //inV1Tb.fixedIGain.viewTag            = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed I-Gain(4)"                   ); // RW
        //inV1Tb.fixedRampTime.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed Ramp Time(4)"                ); // RW
        //inV1Tb.fixedRampMode.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed Ramp Mode(1)"                ); // RW
        //inV1Tb.fixedDir.viewTag              = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed Direction Mode(1)"           ); // RW
        //inV1Tb.adaptiveDeltaGain.viewTag     = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Delta Gain(4)"            ); // RW
        //inV1Tb.sens1PresInt.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor1 Pressure-INT(2)"           ); // RW
        //inV1Tb.sens1PresFloat.viewTag        = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor1 Pressure-FLOAT(4)"         ); // RW
        //inV1Tb.sens2PresInt.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor2 Pressure-INT(2)"           ); // RW
        //inV1Tb.sens2PresFloat.viewTag        = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor2 Pressure-FLOAT(4)"         ); // RW
        //inV1Tb.dummy.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Dummy(1)"                          ); // RW

        outScalingPosiUnit.viewTag           = findTag("Interface DeviceNet.Scaling.Output.Position Setpoint Unit"                                              ); // RW
        outScalingPosiGain.viewTag           = findTag("Interface DeviceNet.Scaling.Output.Position Setpoint Gain"                                              ); // RW
        outScalingPresUnit.viewTag           = findTag("Interface DeviceNet.Scaling.Output.Pressure Setpoint Unit"                                              ); // RW
        outScalingSens1Gain.viewTag          = findTag("Interface DeviceNet.Scaling.Output.Pressure Setpoint Sensor1 Gain"                                      ); // RW
        outScalingSens2Gain.viewTag          = findTag("Interface DeviceNet.Scaling.Output.Pressure Setpoint Sensor2 Gain"                                      ); // RW

        inScalingPosiUnit.viewTag            = findTag("Interface DeviceNet.Scaling.Input.Position Setpoint Unit"                                               ); // RW
        inScalingPosiGain.viewTag            = findTag("Interface DeviceNet.Scaling.Input.Position Setpoint Gain"                                               ); // RW
        inScalingPresUnit.viewTag            = findTag("Interface DeviceNet.Scaling.Input.Pressure Setpoint Unit"                                               ); // RW
        inScalingSens1Gain.viewTag           = findTag("Interface DeviceNet.Scaling.Input.Pressure Setpoint Sensor1 Gain"                                       ); // RW
        inScalingSens2Gain.viewTag           = findTag("Interface DeviceNet.Scaling.Input.Pressure Setpoint Sensor2 Gain"                                       ); // RW

        serialNum.viewTag                    = findTag("Interface DeviceNet.Identity Object.Instance.Serial Number(Hex)"                                        ); // RO
        pdName.viewTag                       = findTag("Interface DeviceNet.Identity Object.Instance.Product Name"                                              ); // RO
        revision.viewTag                     = findTag("Interface DeviceNet.Identity Object.Instance.Revision"                                                  ); // RW
        venderId.viewTag                     = findTag("Interface DeviceNet.Identity Object.Instance.Vendor ID"                                                 ); // RW
        devType.viewTag                      = findTag("Interface DeviceNet.Identity Object.Instance.Device Type"                                               ); // RW
        pdCode.viewTag                       = findTag("Interface DeviceNet.Identity Object.Instance.Product Code"                                              ); // RW

        reactEnable.viewTag                  = findTag("Interface DeviceNet.Connection Loss Reaction.Enable"                                                    ); // RW
        reactState.viewTag                   = findTag("Interface DeviceNet.Connection Loss Reaction.State"                                                     ); // RO
        reactfunc.viewTag                    = findTag("Interface DeviceNet.Connection Loss Reaction.Functionality"                                             ); // RW

        doutActivation.viewTag               = findTag("Interface DeviceNet.Input Output.Digital Output.Enable"                                                 ); // RW
        doutFunc.viewTag                     = findTag("Interface DeviceNet.Input Output.Digital Output.Functionality"                                          ); // RW
        doutPolarity.viewTag                 = findTag("Interface DeviceNet.Input Output.Digital Output.Polarity"                                               ); // RW
        doutStatus.viewTag                   = findTag("Interface DeviceNet.Input Output.DIO Status.Digital Out Status"                                         ); // RW

        dinActivation.viewTag                = findTag("Interface DeviceNet.Input Output.Digital Input.Enable"                                                  ); // RW
        dinFunc.viewTag                      = findTag("Interface DeviceNet.Input Output.Digital Input.Functionality"                                           ); // RW
        dinPolarity.viewTag                  = findTag("Interface DeviceNet.Input Output.Digital Input.Polarity"                                                ); // RW
        dinStatus.viewTag                    = findTag("Interface DeviceNet.Input Output.DIO Status.Digital In Status"                                          ); // RW

        regInitTag(valveRev1Tag);
        regInitTag(valveRev2Tag);
        regInitTag(valveRev3Tag);

        regInitComponent(macSwitch                );
        regInitComponent(mac                      );
        regInitComponent(baudRate                 );

        regInitComponent(profile                  );
        regInitComponent(dataType                 );

        //regMonitoringComponent(outName                  );
        //regMonitoringComponent(outLen                   );

        //regMonitoringComponent(outV1Tb.ctrlMode         );
        //regMonitoringComponent(outV1Tb.setPointInt      );
        //regMonitoringComponent(outV1Tb.setPointFloat    );
        //regMonitoringComponent(outV1Tb.setPointType     );
        //regMonitoringComponent(outV1Tb.learn            );
        //regMonitoringComponent(outV1Tb.learnPresLimInt  );
        //regMonitoringComponent(outV1Tb.learnPresLimFloat);
        //regMonitoringComponent(outV1Tb.zero             );
        //regMonitoringComponent(outV1Tb.presCtrlMode     );
        //regMonitoringComponent(outV1Tb.writeCtrlParam   );
        //regMonitoringComponent(outV1Tb.adaptiveGain     );
        //regMonitoringComponent(outV1Tb.adaptiveSensDelay);
        //regMonitoringComponent(outV1Tb.adaptiveRampTime );
        //regMonitoringComponent(outV1Tb.adaptiveRampMode );
        //regMonitoringComponent(outV1Tb.fixedPGain       );
        //regMonitoringComponent(outV1Tb.fixedIGain       );
        //regMonitoringComponent(outV1Tb.fixedRampTime    );
        //regMonitoringComponent(outV1Tb.fixedRampMode    );
        //regMonitoringComponent(outV1Tb.fixedDir         );
        //regMonitoringComponent(outV1Tb.adaptiveDeltaGain);
        //regMonitoringComponent(outV1Tb.calibration      );
        //regMonitoringComponent(outV1Tb.dummy            );

        //regMonitoringComponent(inName                   );
        //regMonitoringComponent(inLen                    );

        //regMonitoringComponent(inV1Tb.exStatus             );
        //regMonitoringComponent(inV1Tb.presInt              );
        //regMonitoringComponent(inV1Tb.presFloat            );
        //regMonitoringComponent(inV1Tb.setPointInt          );
        //regMonitoringComponent(inV1Tb.setPointFloat        );
        //regMonitoringComponent(inV1Tb.posiInt              );
        //regMonitoringComponent(inV1Tb.posiFloat            );
        //regMonitoringComponent(inV1Tb.exDetailAlarm        );
        //regMonitoringComponent(inV1Tb.exDetailWarn         );
        //regMonitoringComponent(inV1Tb.valveCloseOpenCheck  );
        //regMonitoringComponent(inV1Tb.devStatus2           );
        //regMonitoringComponent(inV1Tb.accMode              );
        //regMonitoringComponent(inV1Tb.presCtrlMode         );
        //regMonitoringComponent(inV1Tb.writeCtrlParamAnalyze);
        //regMonitoringComponent(inV1Tb.adaptiveGain         );
        //regMonitoringComponent(inV1Tb.adaptiveSensDelay    );
        //regMonitoringComponent(inV1Tb.adaptiveRampTime     );
        //regMonitoringComponent(inV1Tb.adaptiveRampMode     );
        //regMonitoringComponent(inV1Tb.fixedPGain           );
        //regMonitoringComponent(inV1Tb.fixedIGain           );
        //regMonitoringComponent(inV1Tb.fixedRampTime        );
        //regMonitoringComponent(inV1Tb.fixedRampMode        );
        //regMonitoringComponent(inV1Tb.fixedDir             );
        //regMonitoringComponent(inV1Tb.adaptiveDeltaGain    );
        //regMonitoringComponent(inV1Tb.sens1PresInt         );
        //regMonitoringComponent(inV1Tb.sens1PresFloat       );
        //regMonitoringComponent(inV1Tb.sens2PresInt         );
        //regMonitoringComponent(inV1Tb.sens2PresFloat       );
        //regMonitoringComponent(inV1Tb.dummy                );

        regInitComponent(outScalingPosiUnit          );
        regInitComponent(outScalingPosiGain          );
        regInitComponent(outScalingPresUnit          );
        regInitComponent(outScalingSens1Gain         );
        regInitComponent(outScalingSens2Gain         );

        regInitComponent(inScalingPosiUnit           );
        regInitComponent(inScalingPosiGain           );
        regInitComponent(inScalingPresUnit           );
        regInitComponent(inScalingSens1Gain          );
        regInitComponent(inScalingSens2Gain          );

        regInitComponent(serialNum                   );
        regInitComponent(pdName                      );
        regInitComponent(revision                    );
        regInitComponent(venderId                    );
        regInitComponent(devType                     );
        regInitComponent(pdCode                      );

        regInitComponent(reactEnable                 );
        regMonitoringComponent(reactState            );
        regInitComponent(reactfunc                   );

        regInitComponent(doutActivation              );
        regInitComponent(doutFunc                    );
        regInitComponent(doutPolarity                );
        regMonitoringComponent(doutStatus            );
        regInitComponent(dinActivation               );
        regInitComponent(dinFunc                     );
        regInitComponent(dinPolarity                 );
        regMonitoringComponent(dinStatus             );

        regMonitoringComponent(dnetStatus            );
        regMonitoringComponent(alarmDevComm          );
        regMonitoringComponent(alarmDevSpecific      );
        regMonitoringComponent(alarmMenuSpecific     );
        regMonitoringComponent(warningDevComm        );
        regMonitoringComponent(warningDevSpecific    );
        regMonitoringComponent(warningMenuSpecifi    );
        regMonitoringComponent(expandedMode          );

        refresh()
    }

    Column{
        id : itemContainerLeft

        anchors.top: parent.top; topPadding: 10; anchors.left: parent.left;
        width: minWidth > (win.scrollContainer.width - 10) ? (minWidth - 10): (win.scrollContainer.width - 10);
        spacing: 10

        CustomLabel       { id: dnetStatusTitle        ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Status"            ;}
        CustomComboLabel  { id: dnetStatus             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider     { }

        CustomLabel       { id: warnStatusTitle                     ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Exception Status"  ;}
        CustomCheckBox    { id: alarmDevComm      ; isReadOnly: true; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200          ;}
        CustomCheckBox    { id: alarmDevSpecific  ; isReadOnly: true; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200          ;}
        CustomCheckBox    { id: alarmMenuSpecific ; isReadOnly: true; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200          ;}
        CustomCheckBox    { id: warningDevComm    ; isReadOnly: true; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200          ;}
        CustomCheckBox    { id: warningDevSpecific; isReadOnly: true; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200          ;}
        CustomCheckBox    { id: warningMenuSpecifi; isReadOnly: true; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200          ;}
        CustomCheckBox    { id: expandedMode      ; isReadOnly: true; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 200          ;}

        CustomDivider     { }

        CustomLabel       { id: doutTitle              ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Output"    ;}
        CustomComboLabel  { id: doutActivation         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: doutFunc               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: doutPolarity           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: doutStatus             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider     { }

        CustomLabel       { id: dinTitle              ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Input"      ;}
        CustomComboLabel  { id: dinActivation         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150           ;}
        CustomComboLabel  { id: dinFunc               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150           ;}
        CustomComboLabel  { id: dinPolarity           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150           ;}
        CustomComboLabel  { id: dinStatus             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150           ;}

        CustomDivider     { }

        CustomLabel       { id: reactionTitle          ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Connection Loss Reaction";}
        CustomComboLabel  { id: reactEnable            ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: reactState             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: reactfunc              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider{}

        CustomLabel       { id: dnetObjTitle           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "DeviceNet Object"  ;}
        CustomValueLabel  { id: macSwitch              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: mac                    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: baudRate               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider     {}

        CustomLabel       { id: identityTitle          ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Identity"          ;}
        CustomValueLabel  { id: serialNum              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: pdName                 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomDNetRevLabel{ id: revision               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: venderId               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: devType                ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: pdCode                 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider     {}

        CustomLabel       { id: profileTitle           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Profile"           ;}
        CustomComboLabel  { id: profile                ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: dataType               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.tagValue !== "2" && profile.viewTag.IsSupport === true;}

        CustomDivider     { }

        CustomLabel       { id: outScalingTitle        ;                                                anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Output Scaling"    ;}
        CustomComboLabel  { id: outScalingPosiUnit     ;                                                anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: outScalingPosiGain     ; visible: outScalingPosiUnit.selValue === 4097; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: outScalingPresUnit     ;                                                anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: outScalingSens1Gain    ; visible: outScalingPresUnit.selValue === 4097; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: outScalingSens2Gain    ; visible: outScalingPresUnit.selValue === 4097; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider{}

        CustomLabel       { id: inScalingTitle         ;                                               anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Input Scaling"     ;}
        CustomComboLabel  { id: inScalingPosiUnit      ;                                               anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: inScalingPosiGain      ; visible: inScalingPosiUnit.selValue === 4097; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomComboLabel  { id: inScalingPresUnit      ;                                               anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: inScalingSens1Gain     ; visible: inScalingPresUnit.selValue === 4097; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: inScalingSens2Gain     ; visible: inScalingPresUnit.selValue === 4097; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider     { }

    }
}
