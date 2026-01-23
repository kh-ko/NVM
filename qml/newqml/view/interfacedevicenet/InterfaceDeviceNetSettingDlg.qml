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
    width: 1000; height: 500; minWidth : 1000
    title: qsTr("Device NET Settings")

    btnCreateEds.visible: true

    property TagModel valveTypeTag     : TagModel{}
    property TagModel valveRev3Tag     : TagModel{}
    property TagModel firmwareVerTag   : TagModel{}

    function beforeProcApply()
    {
        if(inScalingPosiUnit.isDirty)
            outScalingPosiUnit.isDirty = true;

        if(inScalingPosiGain.isDirty)
            outScalingPosiGain.isDirty = true;

        if(inScalingPresUnit.isDirty)
            outScalingPresUnit.isDirty = true;

        if(inScalingSens1Gain.isDirty)
            outScalingSens1Gain.isDirty = true;

        if(inScalingSens2Gain.isDirty)
            outScalingSens2Gain.isDirty = true;
    }

    Component.onCompleted: {
        valveTypeTag                         = findTag("System.Identification.ID: Valve Type"                                                                   ); // RO
        valveRev3Tag                         = findTag("System.Identification.Valve Revision (3)"                                                               ); // RO
        firmwareVerTag                       = findTag("System.Identification.Firmware.Valve Firmware Version"                                                  ); // RO

        macSwitch.viewTag                    = findTag("Interface DeviceNet.DeviceNet Object.Instance.MAC ID Switch"                                            ); // RO
        mac.viewTag                          = findTag("Interface DeviceNet.DeviceNet Object.Instance.MAC ID"                                                   ); // RW
        baudRate.viewTag                     = findTag("Interface DeviceNet.DeviceNet Object.Instance.Baud Rate"                                                ); // RW

        profile.viewTag                      = findTag("Interface DeviceNet.Connection Object.Profile.Profile"                                                  ); // RW
        dataType.viewTag                     = findTag("Interface DeviceNet.Connection Object.Profile.Data Type"                                                ); // RW
        dataTypeLabel.viewTag                = findTag("Interface DeviceNet.Connection Object.Profile.Data Type"                                                ); // RW

        outAssy.viewTag                      = findTag("Interface DeviceNet.Connection Object.Output.Output IO Consumed Assembly"                               ); // RW
        outName.viewTag                      = findTag("Interface DeviceNet.Connection Object.Output.Output Name"                                               ); // RO
        outLen.viewTag                       = findTag("Interface DeviceNet.Connection Object.Output.Output length (Byte)"                                      ); // RO

        outV1Tb.ctrlMode.viewTag             = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Control Model(1)"                ); // RW
        outV1Tb.setPointInt.viewTag          = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Setpoint-INT(2)"                 ); // RW
        outV1Tb.setPointFloat.viewTag        = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Setpoint-FLOAT(4)"               ); // RW
        outV1Tb.setPointType.viewTag         = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Setpoint type(1)"                ); // RW
        outV1Tb.learn.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Learn(1)"                        ); // RW
        outV1Tb.learnPresLimInt.viewTag      = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Learn pressure limit-INT(2)"     ); // RW
        outV1Tb.learnPresLimFloat.viewTag    = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Learn pressure limit-FLOAT(4)"   ); // RW
        outV1Tb.zero.viewTag                 = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Zero(1)"                         ); // RW
        outV1Tb.presCtrlMode.viewTag         = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Pressure control mode(1)"        ); // RW
        outV1Tb.writeCtrlParam.viewTag       = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Write control parameter(1)"      ); // RW
        outV1Tb.adaptiveGain.viewTag         = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive gain(4)"                ); // RW
        outV1Tb.adaptiveSensDelay.viewTag    = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive sensor delay(4)"        ); // RW
        outV1Tb.adaptiveRampTime.viewTag     = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive ramp time(4)"           ); // RW
        outV1Tb.adaptiveRampMode.viewTag     = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive ramp mode(1)"           ); // RW
        outV1Tb.fixedPGain.viewTag           = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed P-gain(4)"                 ); // RW
        outV1Tb.fixedIGain.viewTag           = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed I-Gain(4)"                 ); // RW
        outV1Tb.fixedRampTime.viewTag        = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed ramp time(4)"              ); // RW
        outV1Tb.fixedRampMode.viewTag        = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed ramp mode(1)"              ); // RW
        outV1Tb.fixedDir.viewTag             = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Fixed direction mode(1)"         ); // RW
        outV1Tb.adaptiveDeltaGain.viewTag    = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Adaptive delta gain(4)"          ); // RW
        outV1Tb.calibration.viewTag          = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Calibration(1)"                  ); // RW
        outV1Tb.dummy.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector Bitmap v1.Dummy(1)"                        ); // RW

        outSelector01.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 01"                                        ); // RW
        outSelector02.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 02"                                        ); // RW
        outSelector03.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 03"                                        ); // RW
        outSelector04.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 04"                                        ); // RW
        outSelector05.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 05"                                        ); // RW
        outSelector06.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 06"                                        ); // RW
        outSelector07.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 07"                                        ); // RW
        outSelector08.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 08"                                        ); // RW
        outSelector09.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 09"                                        ); // RW
        outSelector10.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 10"                                        ); // RW
        outSelector11.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 11"                                        ); // RW
        outSelector12.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 12"                                        ); // RW
        outSelector13.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 13"                                        ); // RW
        outSelector14.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 14"                                        ); // RW
        outSelector15.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 15"                                        ); // RW
        outSelector16.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 16"                                        ); // RW
        outSelector17.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 17"                                        ); // RW
        outSelector18.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 18"                                        ); // RW
        outSelector19.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 19"                                        ); // RW
        outSelector20.viewTag                = findTag("Interface DeviceNet.Connection Object.Output.Output Selector 20"                                        ); // RW

        inAssy.viewTag                       = findTag("Interface DeviceNet.Connection Object.Input.Input IO Produced Assembly"                                 ); // RW
        inName.viewTag                       = findTag("Interface DeviceNet.Connection Object.Input.Input Name"                                                 ); // RO
        inLen.viewTag                        = findTag("Interface DeviceNet.Connection Object.Input.Input length (Byte)"                                        ); // RO

        inV1Tb.exStatus.viewTag              = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Exception Status(1)"               ); // RW
        inV1Tb.presInt.viewTag               = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Pressure-INT(2)"                   ); // RW
        inV1Tb.presFloat.viewTag             = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Pressure-FLOAT(4)"                 ); // RW
        inV1Tb.setPointInt.viewTag           = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Setpoint-INT(2)"                   ); // RW
        inV1Tb.setPointFloat.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Setpoint-FLOAT(4)"                 ); // RW
        inV1Tb.posiInt.viewTag               = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Position-INT(2)"                   ); // RW
        inV1Tb.posiFloat.viewTag             = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Position-FLOAT(4)"                 ); // RW
        inV1Tb.exDetailAlarm.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Exception Detail Alarm(15)"        ); // RW
        inV1Tb.exDetailWarn.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Exception Detail Warning(15)"      ); // RW
        inV1Tb.valveCloseOpenCheck.viewTag   = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Valve Close/Open Check(1)"         ); // RW
        inV1Tb.devStatus2.viewTag            = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Device Status 2(1)"                ); // RW
        inV1Tb.accMode.viewTag               = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Access Mode(1)"                    ); // RW
        inV1Tb.presCtrlMode.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Pressure control Mode(1)"          ); // RW
        inV1Tb.writeCtrlParamAnalyze.viewTag = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Write Control Parameter Analyze(1)"); // RW
        inV1Tb.adaptiveGain.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Gain(4)"                  ); // RW
        inV1Tb.adaptiveSensDelay.viewTag     = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Sensor Delay(4)"          ); // RW
        inV1Tb.adaptiveRampTime.viewTag      = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Ramp Time(4)"             ); // RW
        inV1Tb.adaptiveRampMode.viewTag      = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Ramp Mode(1)"             ); // RW
        inV1Tb.fixedPGain.viewTag            = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed P-Gain(4)"                   ); // RW
        inV1Tb.fixedIGain.viewTag            = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed I-Gain(4)"                   ); // RW
        inV1Tb.fixedRampTime.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed Ramp Time(4)"                ); // RW
        inV1Tb.fixedRampMode.viewTag         = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed Ramp Mode(1)"                ); // RW
        inV1Tb.fixedDir.viewTag              = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Fixed Direction Mode(1)"           ); // RW
        inV1Tb.adaptiveDeltaGain.viewTag     = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Adaptive Delta Gain(4)"            ); // RW
        inV1Tb.sens1PresInt.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor1 Pressure-INT(2)"           ); // RW
        inV1Tb.sens1PresFloat.viewTag        = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor1 Pressure-FLOAT(4)"         ); // RW
        inV1Tb.sens2PresInt.viewTag          = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor2 Pressure-INT(2)"           ); // RW
        inV1Tb.sens2PresFloat.viewTag        = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Sensor2 Pressure-FLOAT(4)"         ); // RW
        inV1Tb.dummy.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector Bitmap v1.Dummy(1)"                          ); // RW

        inSelector01.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 01"                                          ); // RW
        inSelector02.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 02"                                          ); // RW
        inSelector03.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 03"                                          ); // RW
        inSelector04.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 04"                                          ); // RW
        inSelector05.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 05"                                          ); // RW
        inSelector06.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 06"                                          ); // RW
        inSelector07.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 07"                                          ); // RW
        inSelector08.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 08"                                          ); // RW
        inSelector09.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 09"                                          ); // RW
        inSelector10.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 10"                                          ); // RW
        inSelector11.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 11"                                          ); // RW
        inSelector12.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 12"                                          ); // RW
        inSelector13.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 13"                                          ); // RW
        inSelector14.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 14"                                          ); // RW
        inSelector15.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 15"                                          ); // RW
        inSelector16.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 16"                                          ); // RW
        inSelector17.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 17"                                          ); // RW
        inSelector18.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 18"                                          ); // RW
        inSelector19.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 19"                                          ); // RW
        inSelector20.viewTag                 = findTag("Interface DeviceNet.Connection Object.Input.Input Selector 20"                                          ); // RW

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

        reset.viewTag                        = findTag("Interface DeviceNet.Identity Object.Services.Reset"                                                     ); // RW

        doutActivation.viewTag               = findTag("Interface DeviceNet.Input Output.Digital Output.Enable"                                                 ); // RW
        doutFunc.viewTag                     = findTag("Interface DeviceNet.Input Output.Digital Output.Functionality"                                          ); // RW
        doutPolarity.viewTag                 = findTag("Interface DeviceNet.Input Output.Digital Output.Polarity"                                               ); // RW

        dinActivation.viewTag                = findTag("Interface DeviceNet.Input Output.Digital Input.Enable"                                                  ); // RW
        dinFunc.viewTag                      = findTag("Interface DeviceNet.Input Output.Digital Input.Functionality"                                           ); // RW
        dinPolarity.viewTag                  = findTag("Interface DeviceNet.Input Output.Digital Input.Polarity"                                                ); // RW


        regInitTag(valveTypeTag     );
        regInitTag(valveRev3Tag     );
        regInitTag(firmwareVerTag   );


        regAlwaysReadComponent(macSwitch               );
        regRWComponent        (mac                     );
        regRWComponent        (baudRate                );

        regRWComponent        (profile                 );
        regRWComponent        (dataType                );
        regAlwaysReadComponent(dataType                );

        regRWComponent        (outAssy                 );
        regAlwaysReadComponent(outName                 );
        regAlwaysReadComponent(outLen                  );

        regRWComponent        (outV1Tb.ctrlMode         );
        regRWComponent        (outV1Tb.setPointInt      );
        regRWComponent        (outV1Tb.setPointFloat    );
        regRWComponent        (outV1Tb.setPointType     );
        regRWComponent        (outV1Tb.learn            );
        regRWComponent        (outV1Tb.learnPresLimInt  );
        regRWComponent        (outV1Tb.learnPresLimFloat);
        regRWComponent        (outV1Tb.zero             );
        regRWComponent        (outV1Tb.presCtrlMode     );
        regRWComponent        (outV1Tb.writeCtrlParam   );
        regRWComponent        (outV1Tb.adaptiveGain     );
        regRWComponent        (outV1Tb.adaptiveSensDelay);
        regRWComponent        (outV1Tb.adaptiveRampTime );
        regRWComponent        (outV1Tb.adaptiveRampMode );
        regRWComponent        (outV1Tb.fixedPGain       );
        regRWComponent        (outV1Tb.fixedIGain       );
        regRWComponent        (outV1Tb.fixedRampTime    );
        regRWComponent        (outV1Tb.fixedRampMode    );
        regRWComponent        (outV1Tb.fixedDir         );
        regRWComponent        (outV1Tb.adaptiveDeltaGain);
        regRWComponent        (outV1Tb.calibration      );
        regRWComponent        (outV1Tb.dummy            );

        regRWComponent        (outSelector01           );
        regRWComponent        (outSelector02           );
        regRWComponent        (outSelector03           );
        regRWComponent        (outSelector04           );
        regRWComponent        (outSelector05           );
        regRWComponent        (outSelector06           );
        regRWComponent        (outSelector07           );
        regRWComponent        (outSelector08           );
        regRWComponent        (outSelector09           );
        regRWComponent        (outSelector10           );
        regRWComponent        (outSelector11           );
        regRWComponent        (outSelector12           );
        regRWComponent        (outSelector13           );
        regRWComponent        (outSelector14           );
        regRWComponent        (outSelector15           );
        regRWComponent        (outSelector16           );
        regRWComponent        (outSelector17           );
        regRWComponent        (outSelector18           );
        regRWComponent        (outSelector19           );
        regRWComponent        (outSelector20           );

        regRWComponent        (inAssy                  );
        regAlwaysReadComponent(inName                  );
        regAlwaysReadComponent(inLen                   );

        regRWComponent        (inV1Tb.exStatus             );
        regRWComponent        (inV1Tb.presInt              );
        regRWComponent        (inV1Tb.presFloat            );
        regRWComponent        (inV1Tb.setPointInt          );
        regRWComponent        (inV1Tb.setPointFloat        );
        regRWComponent        (inV1Tb.posiInt              );
        regRWComponent        (inV1Tb.posiFloat            );
        regRWComponent        (inV1Tb.exDetailAlarm        );
        regRWComponent        (inV1Tb.exDetailWarn         );
        regRWComponent        (inV1Tb.valveCloseOpenCheck  );
        regRWComponent        (inV1Tb.devStatus2           );
        regRWComponent        (inV1Tb.accMode              );
        regRWComponent        (inV1Tb.presCtrlMode         );
        regRWComponent        (inV1Tb.writeCtrlParamAnalyze);
        regRWComponent        (inV1Tb.adaptiveGain         );
        regRWComponent        (inV1Tb.adaptiveSensDelay    );
        regRWComponent        (inV1Tb.adaptiveRampTime     );
        regRWComponent        (inV1Tb.adaptiveRampMode     );
        regRWComponent        (inV1Tb.fixedPGain           );
        regRWComponent        (inV1Tb.fixedIGain           );
        regRWComponent        (inV1Tb.fixedRampTime        );
        regRWComponent        (inV1Tb.fixedRampMode        );
        regRWComponent        (inV1Tb.fixedDir             );
        regRWComponent        (inV1Tb.adaptiveDeltaGain    );
        regRWComponent        (inV1Tb.sens1PresInt         );
        regRWComponent        (inV1Tb.sens1PresFloat       );
        regRWComponent        (inV1Tb.sens2PresInt         );
        regRWComponent        (inV1Tb.sens2PresFloat       );
        regRWComponent        (inV1Tb.dummy                );

        regRWComponent        (inSelector01            );
        regRWComponent        (inSelector02            );
        regRWComponent        (inSelector03            );
        regRWComponent        (inSelector04            );
        regRWComponent        (inSelector05            );
        regRWComponent        (inSelector06            );
        regRWComponent        (inSelector07            );
        regRWComponent        (inSelector08            );
        regRWComponent        (inSelector09            );
        regRWComponent        (inSelector10            );
        regRWComponent        (inSelector11            );
        regRWComponent        (inSelector12            );
        regRWComponent        (inSelector13            );
        regRWComponent        (inSelector14            );
        regRWComponent        (inSelector15            );
        regRWComponent        (inSelector16            );
        regRWComponent        (inSelector17            );
        regRWComponent        (inSelector18            );
        regRWComponent        (inSelector19            );
        regRWComponent        (inSelector20            );

        regRWComponent        (inScalingPosiUnit       );
        regRWComponent        (inScalingPosiGain       );
        regRWComponent        (inScalingPresUnit       );
        regRWComponent        (inScalingSens1Gain      );
        regRWComponent        (inScalingSens2Gain      );

        regRWComponent        (outScalingPosiUnit      );
        regRWComponent        (outScalingPosiGain      );
        regRWComponent        (outScalingPresUnit      );
        regRWComponent        (outScalingSens1Gain     );
        regRWComponent        (outScalingSens2Gain     );

        regAlwaysReadComponent(serialNum               );
        regAlwaysReadComponent(pdName                  );
        regRWComponent        (revision                );
        regRWComponent        (venderId                );
        regRWComponent        (devType                 );
        regRWComponent        (pdCode                  );

        regRWComponent        (reactEnable             );
        regAlwaysReadComponent(reactState              );
        regRWComponent        (reactfunc               );

        regRWComponent        (reset                   );

        regRWComponent        (doutActivation          );
        regRWComponent        (doutFunc                );
        regRWComponent        (doutPolarity            );
        regRWComponent        (dinActivation           );
        regRWComponent        (dinFunc                 );
        regRWComponent        (dinPolarity             );

        checkApplyBtn()
        refresh()
    }

    Column{
        id : itemContainerLeft

        anchors.top: parent.top; topPadding: 10; anchors.left: parent.left;
        width: minWidth > (win.scrollContainer.width - 10) ? (minWidth - 10) * 0.5 : (win.scrollContainer.width - 10) * 0.5;
        spacing: 10

        CustomLabel       { id: dnetObjTitle           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "DeviceNet Object"  ;}
        CustomValueLabel  { id: macSwitch              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomIntegerInput{ id: mac                    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: baudRate               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider     {}

        CustomLabel       { id: profileTitle           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Profile"           ;}
        CustomComboBox    { id: profile                ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: dataType               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue === 1 && profile.viewTag.IsSupport === true; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboLabel  { id: dataTypeLabel          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue === 0 && profile.viewTag.IsSupport === true; }
        CustomLabel       { height: 24                 ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: ""                  ; visible: !dataType.visible}
        CustomLabel       { height: 24                 ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: ""                  ; }

        CustomDivider     { visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}

        CustomLabel       { id: outputTitle            ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Output"            ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}
        CustomComboBox    { id: outAssy                ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomMultiLine   { id: outName                ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}
        CustomValueLabel  { id: outLen                 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}

        CustomDivider     { visible: profile.selValue === 2 || profile.viewTag.IsSupport === false;}

        InterfaceDeviceNetV1OutTable {id: outV1Tb; visible: profile.selValue === 2 || profile.viewTag.IsSupport === false; onCheckApplyBtn: {win.checkApplyBtn()}}

        CustomDivider     { visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && outAssy.selValue == 0;}

        CustomLabel       { id: outSelV2Title          ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Output Selector V2"; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0;}
        CustomComboBox    { id: outSelector01          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector02          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector03          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector04          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector05          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector06          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector07          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector08          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector09          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector10          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector11          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector12          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector13          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector14          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector15          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector16          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector17          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector18          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector19          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outSelector20          ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true  && outAssy.selValue == 0; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider{}

        CustomLabel       { id: outScalingTitle        ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Output Scaling"    ;}
        CustomComboBox    { id: outScalingPosiUnit     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomFloatInput  { id: outScalingPosiGain     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: outScalingPosiUnit.selValue === 4097; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: outScalingPresUnit     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomFloatInput  { id: outScalingSens1Gain    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: outScalingPresUnit.selValue === 4097; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomFloatInput  { id: outScalingSens2Gain    ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: outScalingPresUnit.selValue === 4097; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider     { }

        CustomLabel       { id: doutTitle              ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Output"    ;}
        CustomComboBox    { id: doutActivation         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: doutFunc               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: doutPolarity           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider     { }

        CustomLabel       { id: dinTitle              ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Digital Input"     ;}
        CustomComboBox    { id: dinActivation         ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: dinFunc               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: dinPolarity           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider     { }

    }

    Rectangle { color : "#ECECEC"; width : 1; height: itemContainerLeft.height; anchors.top: itemContainerLeft.top; anchors.left: itemContainerLeft.right;}

    Column{
        id : itemContainerRigth

        anchors.top: parent.top; topPadding: 10; anchors.left: itemContainerLeft.right; anchors.leftMargin: 1
        width: minWidth > (win.scrollContainer.width - 10) ? (minWidth - 10) * 0.5 : (win.scrollContainer.width - 10) * 0.5;
        spacing: 10

        CustomLabel       { id: identityTitle          ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Identity"          ;}
        CustomValueLabel  { id: serialNum              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}
        CustomValueLabel  { id: pdName                 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ;}

        CustomDivider     {}
        CustomLabel       {                              anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Identity"          ;}
        CustomDNetRevInput{ id: revision               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomIntegerInput{ id: venderId               ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: devType                ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomIntegerInput{ id: pdCode                 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider     { visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}

        CustomLabel       { id: inputTitle             ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Input"             ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}
        CustomComboBox    { id: inAssy                 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomMultiLine   { id: inName                 ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}
        CustomValueLabel  { id: inLen                  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true;}

        CustomDivider     { visible: profile.selValue === 2 || profile.viewTag.IsSupport === false;}

        InterfaceDeviceNetV1InTable { id: inV1Tb; visible: profile.selValue === 2 || profile.viewTag.IsSupport === false; onCheckApplyBtn: {win.checkApplyBtn()}}

        CustomDivider     { visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0;}

        CustomLabel       { id: inSelV2Title           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Input Selector V2" ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0;}
        CustomComboBox    { id: inSelector01           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector02           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector03           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector04           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector05           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector06           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector07           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector08           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector09           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector10           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector11           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector12           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector13           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector14           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector15           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector16           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector17           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector18           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector19           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inSelector20           ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: profile.selValue !== 2 && profile.viewTag.IsSupport === true && inAssy.selValue === 0; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider{}

        CustomLabel       { id: inScalingTitle         ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Input Scaling"     ;}
        CustomComboBox    { id: inScalingPosiUnit      ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomFloatInput  { id: inScalingPosiGain      ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: inScalingPosiUnit.selValue === 4097; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboBox    { id: inScalingPresUnit      ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomFloatInput  { id: inScalingSens1Gain     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: inScalingPresUnit.selValue === 4097; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomFloatInput  { id: inScalingSens2Gain     ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; visible: inScalingPresUnit.selValue === 4097; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider{}

        CustomLabel       { id: reactionTitle          ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Connection Loss Reaction";}
        CustomComboBox    { id: reactEnable            ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}
        CustomComboLabel  { id: reactState             ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150         ;}
        CustomComboBox    { id: reactfunc              ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150          ; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider{}

        CustomLabel       { id: serviceTitle           ; anchors.left: parent.left; anchors.leftMargin: 10; anchors.right: parent.right; anchors.rightMargin:  0; text: "Services";}
        CustomComboBox    { id: reset                  ; anchors.left: parent.left; anchors.leftMargin: 20; anchors.right: parent.right; anchors.rightMargin: 10; label.width: 150         ; onIsDirtyChanged: {win.checkApplyBtn()}}

        CustomDivider{}
    }
}
