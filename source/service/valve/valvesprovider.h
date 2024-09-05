#ifndef VALVESPROVIDER_H
#define VALVESPROVIDER_H
#include <QObject>
#include <QDateTime>
#include <QTimer>
#include <QMap>
#include "source/service/def/filedef.h"
#include "source/service/util/exceptionutil.h"
#include "source/service/valve/valveayncworker.h"
#include "source/service/valve/valvefirmwareupgradeworker.h"

#define pValveSP ValveSProvider::getInstance()

#define ENABLE_SLOT_VALVE_CHANGED_ISRUNNING                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsRunning                      (bool                                            )), this, SLOT(onValveChangedIsRunning                    (bool                                              )))
#define ENABLE_SLOT_VALVE_CHANGED_ISCONNECTED                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsConnected                    (bool                                            )), this, SLOT(onValveChangedIsConnected                  (bool                                              )))
#define ENABLE_SLOT_VALVE_CHANGED_LOAD_PROGRESS                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedLoadProgress                   (int                                             )), this, SLOT(onValveChangedLoadProgress                 (int                                               )))
#define ENABLE_SLOT_VALVE_CHANGED_DFU_STEP                              connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedDFUStep                        (                                                )), this, SLOT(onValveChangedDFUStep                      (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_KERNEL                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedDFUPctCpu1Kernel               (                                                )), this, SLOT(onValveChangedDFUPctCpu1Kernel             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_KERNEL                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedDFUPctCpu2Kernel               (                                                )), this, SLOT(onValveChangedDFUPctCpu2Kernel             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_APP                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedDFUPctCpu1App                  (                                                )), this, SLOT(onValveChangedDFUPctCpu1App                (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_APP                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedDFUPctCpu2App                  (                                                )), this, SLOT(onValveChangedDFUPctCpu2App                (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU1_VERIFY                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedDFUPctCpu1Verify               (                                                )), this, SLOT(onValveChangedDFUPctCpu1Verify             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_DFU_PCT_CPU2_VERIFY                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedDFUPctCpu2Verify               (                                                )), this, SLOT(onValveChangedDFUPctCpu2Verify             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_CONNECTIONINFO                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedConnectionInfo                 (QString                                         )), this, SLOT(onValveChangedConnectionInfo               (QString                                           )))
#define ENABLE_SLOT_VALVE_CHANGED_CURR_POS                              connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedCurrPosition                   (                                                )), this, SLOT(onValveChangedCurrPosition                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_CURR_PRESSURE                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedCurrPressure                   (                                                )), this, SLOT(onValveChangedCurrPressure                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_TARGET_POS                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedTargetPosition                 (                                                )), this, SLOT(onValveChangedTargetPosition               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_TARGET_PRESSURE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedTargetPressure                 (                                                )), this, SLOT(onValveChangedTargetPressure               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_SPEED                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedValveSpeed                     (                                                )), this, SLOT(onValveChangedValveSpeed                   (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_MAX_SPEED                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedValveMaxSpeed                  (                                                )), this, SLOT(onValveChangedValveMaxSpeed                (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_PRESSURE_CTRL_MODE                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedPressureCtrlMode               (                                                )), this, SLOT(onValveChangedPressureCtrlMode             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_ACCESS                                connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedAccess                         (                                                )), this, SLOT(onValveChangedAccess                       (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_MODE                                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedMode                           (                                                )), this, SLOT(onValveChangedMode                         (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_CTRL_MODE                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedControlMode                    (                                                )), this, SLOT(onValveChangedControlMode                  (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_S01_FULLSCALE_PREC                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedS01FullScalePrec               (                                                )), this, SLOT(onValveChangedS01FullScalePrec             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_S02_FULLSCALE_PREC                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedS02FullScalePrec               (                                                )), this, SLOT(onValveChangedS02FullScalePrec             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_S01_FULLSCALE                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedS01FullScale                   (                                                )), this, SLOT(onValveChangedS01FullScale                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_S02_FULLSCALE                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedS02FullScale                   (                                                )), this, SLOT(onValveChangedS02FullScale                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SENSOR_OP                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSensorOperation                (                                                )), this, SLOT(onValveChangedSensorOperation              (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SENSOR_01_OFFSET                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSensor01Offset                 (                                                )), this, SLOT(onValveChangedSensor01Offset               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SENSOR_02_OFFSET                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSensor02Offset                 (                                                )), this, SLOT(onValveChangedSensor02Offset               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_ZERO_ENABLE                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedZeroEnable                     (                                                )), this, SLOT(onValveChangedZeroEnable                   (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_POS_RESOLUTION                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedPositionResolution             (                                                )), this, SLOT(onValveChangedPositionResolution           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_PRESSURE_DB_UNIT                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedPressureDpUnit                 (                                                )), this, SLOT(onValveChangedPressureDpUnit               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_PRESSURE_AXIS_MODE                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedPressureAxisMode               (                                                )), this, SLOT(onValveChangedPressureAxisMode             (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_PRESSURE_DECADES                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedPressureDecades                (                                                )), this, SLOT(onValveChangedPressureDecades              (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_IS_SIM                                connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsSimulation                   (                                                )), this, SLOT(onValveChangedIsSimulation                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_ENABLE_PFO                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedEnablePFO                      (                                                )), this, SLOT(onValveChangedEnablePFO                    (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_IS_TEST_MODE                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsTestMode                     (                                                )), this, SLOT(onValveChangedIsTestMode                   (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_FIELDBUS_ERR                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedFieldBusError                  (                                                )), this, SLOT(onValveChangedFieldBusError                (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_IS_SAVING                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsSaving                       (                                                )), this, SLOT(onValveChangedIsSaving                     (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_IS_ID_MISSING                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsIDMissing                    (                                                )), this, SLOT(onValveChangedIsIDMissing                  (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_IS_PFO_MISSING                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsPFOMissing                   (                                                )), this, SLOT(onValveChangedIsPFOMissing                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_FIRMWARE_ERR                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedFirmwareError                  (                                                )), this, SLOT(onValveChangedFirmwareError                (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_UNKNOW_INTERFACE                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedUnknowInterface                (                                                )), this, SLOT(onValveChangedUnknowInterface              (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_NO_SENSOR_SIG                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedNoSensorSignal                 (                                                )), this, SLOT(onValveChangedNoSensorSignal               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_NO_ANALOG_SIG                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedNoAnalogSignal                 (                                                )), this, SLOT(onValveChangedNoAnalogSignal               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_NETWORK_FAIL                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedNetworkFailure                 (                                                )), this, SLOT(onValveChangedNetworkFailure               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SLAVE_OFFLINE                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSlaveOffline                   (                                                )), this, SLOT(onValveChangedSlaveOffline                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_ISOLATION_VALVE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsolationValve                 (                                                )), this, SLOT(onValveChangedIsolationValve               (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SENSOR_ERR                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSensorError                    (                                                )), this, SLOT(onValveChangedSensorError                  (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SVC_REQ                               connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSvcRequest                     (                                                )), this, SLOT(onValveChangedSvcRequest                   (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_LEARN_NOT_PRESENT                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedLearnNotPresent                (                                                )), this, SLOT(onValveChangedLearnNotPresent              (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_AIR_NOT_READY                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedAirNotReady                    (                                                )), this, SLOT(onValveChangedAirNotReady                  (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_PFO_NOT_READY                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedPFONotReady                    (                                                )), this, SLOT(onValveChangedPFONotReady                  (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_ID                              connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedValveID                        (                                                )), this, SLOT(onValveChangedValveID                      (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_FIRMWARE_VER                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedFirmwareVersion                (                                                )), this, SLOT(onValveChangedFirmwareVersion              (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_IS_SUPPORT_PFO                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsSupportPFO                   (                                                )), this, SLOT(onValveChangedIsSupportPFO                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_IS_SUPPORT_SPS                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsSupportSPS                   (                                                )), this, SLOT(onValveChangedIsSupportSPS                 (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_IS_SUPPORT_ANALOG_OUT           connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsSupportAnalogOut             (                                                )), this, SLOT(onValveChangedIsSupportAnalogOut           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_INTERFACE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedInterface                      (                                                )), this, SLOT(onValveChangedInterface                    (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SENSOR_VERSION                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSensorVersion                  (                                                )), this, SLOT(onValveChangedSensorVersion                (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SCAN_RATE                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedScanRate                       (                                                )), this, SLOT(onValveChangedScanRate                     (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_IS_RS232_TEST                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedIsRS232Test                    (                                                )), this, SLOT(onValveChangedIsRS232Test                  (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_01_POSITION                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint01Position             (                                                )), this, SLOT(onValveChangedSetPoint01Position           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_02_POSITION                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint02Position             (                                                )), this, SLOT(onValveChangedSetPoint02Position           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_03_POSITION                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint03Position             (                                                )), this, SLOT(onValveChangedSetPoint03Position           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_04_POSITION                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint04Position             (                                                )), this, SLOT(onValveChangedSetPoint04Position           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_05_POSITION                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint05Position             (                                                )), this, SLOT(onValveChangedSetPoint05Position           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_06_POSITION                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint06Position             (                                                )), this, SLOT(onValveChangedSetPoint06Position           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_01_PRESSURE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint01Pressure             (                                                )), this, SLOT(onValveChangedSetPoint01Pressure           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_02_PRESSURE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint02Pressure             (                                                )), this, SLOT(onValveChangedSetPoint02Pressure           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_03_PRESSURE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint03Pressure             (                                                )), this, SLOT(onValveChangedSetPoint03Pressure           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_04_PRESSURE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint04Pressure             (                                                )), this, SLOT(onValveChangedSetPoint04Pressure           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_05_PRESSURE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint05Pressure             (                                                )), this, SLOT(onValveChangedSetPoint05Pressure           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_SETPOINT_06_PRESSURE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSetPoint06Pressure             (                                                )), this, SLOT(onValveChangedSetPoint06Pressure           (                                                  )))
#define ENABLE_SLOT_VALVE_CHANGED_VALVE_STATUS                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedValveStatus                    (QString                                         )), this, SLOT(onValveChangedValveStatus                  (QString                                           )))
#define ENABLE_SLOT_VALVE_CHANGED_SENSOR_SETTING                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventChangedSensorSetting                  (QString                                         )), this, SLOT(onValveChangedSensorSetting                (QString                                           )))
#define ENABLE_SLOT_VALVE_RESULT_CONNECT                                connect(ValveSProvider::getInstance(), SIGNAL(signalResultConnect                              (bool, QString                                   )), this, SLOT(onValveResultConnect                       (bool, QString                                     )))
#define ENABLE_SLOT_VALVE_RESULT_DFU                                    connect(ValveSProvider::getInstance(), SIGNAL(signalResultDFU                                  (bool, QString                                   )), this, SLOT(onValveResultDFU                           (bool, QString                                     )))
#define ENABLE_SLOT_VALVE_RESULT_READY_DFU                              connect(ValveSProvider::getInstance(), SIGNAL(signalResultReadyDFU                             (bool                                            )), this, SLOT(onValveResultReadyDFU                      (bool                                              )))
#define ENABLE_SLOT_VALVE_SEARCHED_DEVICE                               connect(ValveSProvider::getInstance(), SIGNAL(signalEventSearchedDevice                        (QStringList                                     )), this, SLOT(onValveSearchedDevice                      (QStringList                                       )))
#define ENABLE_SLOT_VALVE_READED_VALVE_ID                               connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedValveID                         (ValveResponseValveIdDto                         )), this, SLOT(onValveReadedValveID                       (ValveResponseValveIdDto                           )))
#define ENABLE_SLOT_VALVE_READED_HW_CONFIG                              connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedHWConfig                        (ValveResponseHWConfigDto                        )), this, SLOT(onValveReadedHWConfig                      (ValveResponseHWConfigDto                          )))
#define ENABLE_SLOT_VALVE_READED_FIRMWARE_VERSION                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFirmwareVersion                 (ValveResponseFirmwareVersionDto                 )), this, SLOT(onValveReadedFirmwareVersion               (ValveResponseFirmwareVersionDto                   )))
#define ENABLE_SLOT_VALVE_READED_VALVE_STATUS                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedValveStatus                     (ValveResponseValveStatusDto                     )), this, SLOT(onValveReadedValveStatus                   (ValveResponseValveStatusDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSOR_SCALE                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensorScale                     (ValveResponseSensorScaleDto                     )), this, SLOT(onValveReadedSensorScale                   (ValveResponseSensorScaleDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSOR_CONFIG                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensorConfig                    (ValveResponseSensorConfigDto                    )), this, SLOT(onValveReadedSensorConfig                  (ValveResponseSensorConfigDto                      )))
#define ENABLE_SLOT_VALVE_READED_SENSOR_OFFSET                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensorOffset                    (ValveResponseSensorOffsetValuesDto              )), this, SLOT(onValveReadedSensorOffset                  (ValveResponseSensorOffsetValuesDto                )))
#define ENABLE_SLOT_VALVE_READED_SENSOR_VALUE                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensorValue                     (ValveResponseSensorValueDto                     )), this, SLOT(onValveReadedSensorValue                   (ValveResponseSensorValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSOR_SELECTION                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensorSelection                 (ValveResponseSensorSelectionDto                 )), this, SLOT(onValveReadedSensorSelection               (ValveResponseSensorSelectionDto                   )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_SEL                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensorExSelection               (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedSensorExSelection             (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_ANAL_ACTIVE                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExAnalActive                 (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExAnalActive               (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_SRC                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExSource                     (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExSource                   (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_UNIT                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExUnit                       (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExUnit                     (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_FULLSCALE                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExFullScale                  (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExFullScale                (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_DIGI                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExDigiValue                  (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExDigiValue                (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_ENABLE                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExZeroAdjEnable              (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExZeroAdjEnable            (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_MIN                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExZeroAdjOffsetLimMin        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExZeroAdjOffsetLimMin      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_MAX                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExZeroAdjOffsetLimMax        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExZeroAdjOffsetLimMax      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_ZERO_VALUE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExZeroAdjOffsetValue         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExZeroAdjOffsetValue       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_SCALE_OFFSET                connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExScaleOffset                (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExScaleOffset              (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_SCALE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExScale                      (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExScale                    (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_SCALE_Z_POINT               connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExScaleZeroPoint             (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExScaleZeroPoint           (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_FILTER_SEC                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExFilterSec                  (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExFilterSec                (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_LOG_SENS_LINEARIZE          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExLogSensorLinearize         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExLogSensorLinearize       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_LOG_SENS_VOLT_DECADE        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExLogSensorVoltPerDecade     (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExLogSensorVoltPerDecade   (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE     connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS01ExLogSensorVoltAtFullScale   (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS01ExLogSensorVoltAtFullScale (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_ANAL_ACTIVE                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExAnalActive                 (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExAnalActive               (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_SRC                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExSource                     (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExSource                   (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_UNIT                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExUnit                       (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExUnit                     (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_FULLSCALE                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExFullScale                  (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExFullScale                (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_DIGI                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExDigiValue                  (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExDigiValue                (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_ENABLE                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExZeroAdjEnable              (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExZeroAdjEnable            (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_MIN                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExZeroAdjOffsetLimMin        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExZeroAdjOffsetLimMin      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_MAX                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExZeroAdjOffsetLimMax        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExZeroAdjOffsetLimMax      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_ZERO_VALUE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExZeroAdjOffsetValue         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExZeroAdjOffsetValue       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_SCALE_OFFSET                connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExScaleOffset                (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExScaleOffset              (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_SCALE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExScale                      (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExScale                    (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_SCALE_Z_POINT               connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExScaleZeroPoint             (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExScaleZeroPoint           (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_FILTER_SEC                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExFilterSec                  (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExFilterSec                (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_LOG_SENS_LINEARIZE          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExLogSensorLinearize         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExLogSensorLinearize       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_LOG_SENS_VOLT_DECADE        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExLogSensorVoltPerDecade     (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExLogSensorVoltPerDecade   (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE     connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedS02ExLogSensorVoltAtFullScale   (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedS02ExLogSensorVoltAtFullScale (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_MOD                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedCrossoverMod                    (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedCrossoverMod                  (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_LOW                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedCrossoverLow                    (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedCrossoverLow                  (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_HIGH                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedCrossoverHigh                   (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedCrossoverHigh                 (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_SENSEX_CROSSOVER_DELA                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedCrossoverDela                   (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedCrossoverDela                 (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_DP_CONFIG                              connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedDisplayConfig                   (ValveResponseDisplayConfigDto                   )), this, SLOT(onValveReadedDisplayConfig                 (ValveResponseDisplayConfigDto                     )))
#define ENABLE_SLOT_VALVE_READED_PRESSURE_CTRL_CONFIG                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedPressureCtrlConfig              (ValveResponsePressureCtrlConfigDto              )), this, SLOT(onValveReadedPressureCtrlConfig            (ValveResponsePressureCtrlConfigDto                )))
#define ENABLE_SLOT_VALVE_READED_SEL_CONTROL_MODE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSelControlMode                  (ValveResponseSelControlModeDto                  )), this, SLOT(onValveReadedSelControlMode                (ValveResponseSelControlModeDto                    )))
#define ENABLE_SLOT_VALVE_READED_ADAP_GAIN_FACTOR                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedAdapGainFactor                  (ValveResponseGainFactorDto                      )), this, SLOT(onValveReadedAdapGainFactor                (ValveResponseGainFactorDto                        )))
#define ENABLE_SLOT_VALVE_READED_ADAP_DELTA_FACTOR                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedAdapDeltaFactor                 (ValveResponseDeltaFactorDto                     )), this, SLOT(onValveReadedAdapDeltaFactor               (ValveResponseDeltaFactorDto                       )))
#define ENABLE_SLOT_VALVE_READED_ADAP_SENSOR_DELAY                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedAdapSensorDelay                 (ValveResponseSensorDelayDto                     )), this, SLOT(onValveReadedAdapSensorDelay               (ValveResponseSensorDelayDto                       )))
#define ENABLE_SLOT_VALVE_READED_ADAP_RAMP_TIME                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedAdapRampTime                    (ValveResponseRampTimeDto                        )), this, SLOT(onValveReadedAdapRampTime                  (ValveResponseRampTimeDto                          )))
#define ENABLE_SLOT_VALVE_READED_ADAP_RAMP_MODE                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedAdapRampMode                    (ValveResponseRampModeDto                        )), this, SLOT(onValveReadedAdapRampMode                  (ValveResponseRampModeDto                          )))
#define ENABLE_SLOT_VALVE_READED_FIXED1_P_GAIN                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed1PGain                     (ValveResponsePGainDto                           )), this, SLOT(onValveReadedFixed1PGain                   (ValveResponsePGainDto                             )))
#define ENABLE_SLOT_VALVE_READED_FIXED1_I_GAIN                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed1IGain                     (ValveResponseIGainDto                           )), this, SLOT(onValveReadedFixed1IGain                   (ValveResponseIGainDto                             )))
#define ENABLE_SLOT_VALVE_READED_FIXED1_RAMP_TIME                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed1RampTime                  (ValveResponseRampTimeDto                        )), this, SLOT(onValveReadedFixed1RampTime                (ValveResponseRampTimeDto                          )))
#define ENABLE_SLOT_VALVE_READED_FIXED1_RAMP_MODE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed1RampMode                  (ValveResponseRampModeDto                        )), this, SLOT(onValveReadedFixed1RampMode                (ValveResponseRampModeDto                          )))
#define ENABLE_SLOT_VALVE_READED_FIXED1_CTRL_DIR                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed1CtrlDir                   (ValveResponseCtrlDirDto                         )), this, SLOT(onValveReadedFixed1CtrlDir                 (ValveResponseCtrlDirDto                           )))
#define ENABLE_SLOT_VALVE_READED_FIXED2_P_GAIN                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed2PGain                     (ValveResponsePGainDto                           )), this, SLOT(onValveReadedFixed2PGain                   (ValveResponsePGainDto                             )))
#define ENABLE_SLOT_VALVE_READED_FIXED2_I_GAIN                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed2IGain                     (ValveResponseIGainDto                           )), this, SLOT(onValveReadedFixed2IGain                   (ValveResponseIGainDto                             )))
#define ENABLE_SLOT_VALVE_READED_FIXED2_RAMP_TIME                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed2RampTime                  (ValveResponseRampTimeDto                        )), this, SLOT(onValveReadedFixed2RampTime                (ValveResponseRampTimeDto                          )))
#define ENABLE_SLOT_VALVE_READED_FIXED2_RAMP_MODE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed2RampMode                  (ValveResponseRampModeDto                        )), this, SLOT(onValveReadedFixed2RampMode                (ValveResponseRampModeDto                          )))
#define ENABLE_SLOT_VALVE_READED_FIXED2_CTRL_DIR                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFixed2CtrlDir                   (ValveResponseCtrlDirDto                         )), this, SLOT(onValveReadedFixed2CtrlDir                 (ValveResponseCtrlDirDto                           )))
#define ENABLE_SLOT_VALVE_READED_SOFTDUMP_P_GAIN                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSoftDumpPGain                   (ValveResponsePGainDto                           )), this, SLOT(onValveReadedSoftDumpPGain                 (ValveResponsePGainDto                             )))
#define ENABLE_SLOT_VALVE_READED_SOFTDUMP_RAMP_TIME                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSoftDumpRampTime                (ValveResponseRampTimeDto                        )), this, SLOT(onValveReadedSoftDumpRampTime              (ValveResponseRampTimeDto                          )))
#define ENABLE_SLOT_VALVE_READED_SOFTDUMP_RAMP_MODE                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSoftDumpRampMode                (ValveResponseRampModeDto                        )), this, SLOT(onValveReadedSoftDumpRampMode              (ValveResponseRampModeDto                          )))
#define ENABLE_SLOT_VALVE_READED_VALVE_SETUP                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedValveSetup                      (ValveResponseValveSetupDto                      )), this, SLOT(onValveReadedValveSetup                    (ValveResponseValveSetupDto                        )))
#define ENABLE_SLOT_VALVE_READED_VALVE_PARAM                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedValveParam                      (ValveResponseValveParamDto                      )), this, SLOT(onValveReadedValveParam                    (ValveResponseValveParamDto                        )))
#define ENABLE_SLOT_VALVE_READED_FATAL_ERR_STATUS                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFatalErrStatus                  (ValveResponseFatalErrStatusDto                  )), this, SLOT(onValveReadedFatalErrStatus                (ValveResponseFatalErrStatusDto                    )))
#define ENABLE_SLOT_VALVE_READED_FATAL_ERR_01_POS                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFatalErr01Pos                   (ValveResponseFatalErrPosDto                     )), this, SLOT(onValveReadedFatalErr01Pos                 (ValveResponseFatalErrPosDto                       )))
#define ENABLE_SLOT_VALVE_READED_FATAL_ERR_02_POS                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFatalErr02Pos                   (ValveResponseFatalErrPosDto                     )), this, SLOT(onValveReadedFatalErr02Pos                 (ValveResponseFatalErrPosDto                       )))
#define ENABLE_SLOT_VALVE_READED_FATAL_ERR_03_POS                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedFatalErr03Pos                   (ValveResponseFatalErrPosDto                     )), this, SLOT(onValveReadedFatalErr03Pos                 (ValveResponseFatalErrPosDto                       )))
#define ENABLE_SLOT_VALVE_READED_WARNINGS                               connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedWarnings                        (ValveResponseWarningsDto                        )), this, SLOT(onValveReadedWarnings                      (ValveResponseWarningsDto                          )))
#define ENABLE_SLOT_VALVE_READED_LEARN_PARAM                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedLearnParam                      (ValveResponseLearnParamDto                      )), this, SLOT(onValveReadedLearnParam                    (ValveResponseLearnParamDto                        )))
#define ENABLE_SLOT_VALVE_READED_IF_CONFIG_LOGIC                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceConfigLogic            (ValveResponseInterfaceConfigLogicDto            )), this, SLOT(onValveReadedInterfaceConfigLogic          (ValveResponseInterfaceConfigLogicDto              )))
#define ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DI                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceConfigEthCATDi         (ValveResponseInterfaceConfigEthCATDiDto         )), this, SLOT(onValveReadedInterfaceConfigEthCATDi       (ValveResponseInterfaceConfigEthCATDiDto           )))
#define ENABLE_SLOT_VALVE_READED_IF_CONFIG_ETHCAT_DO                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceConfigEthCATDo         (ValveResponseInterfaceConfigEthCATDoDto         )), this, SLOT(onValveReadedInterfaceConfigEthCATDo       (ValveResponseInterfaceConfigEthCATDoDto           )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_DEV_ID                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgEthCATDevID         (ValveResponseInterfaceConfigEthCATDevIDDto      )), this, SLOT(onValveReadedInterfaceCfgEthCATDevID       (ValveResponseInterfaceConfigEthCATDevIDDto        )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_DATA_TYPE            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgEthCATPDODataType   (ValveResponseInterfaceConfigEthCATPDODataTypeDto)), this, SLOT(onValveReadedInterfaceCfgEthCATPDODataType (ValveResponseInterfaceConfigEthCATPDODataTypeDto  )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_ETHCAT_PDO_RANGE                connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgEthCATPDORange      (ValveResponseInterfaceConfigEthCATPDORangeDto   )), this, SLOT(onValveReadedInterfaceCfgEthCATPDORange    (ValveResponseInterfaceConfigEthCATPDORangeDto     )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_MAC                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetMAC             (ValveResponseInterfaceConfigDNetMacDto          )), this, SLOT(onValveReadedInterfaceCfgDNetMAC           (ValveResponseInterfaceConfigDNetMacDto            )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_BAUDRATE                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetBaudrate        (ValveResponseInterfaceConfigDNetBaudrateDto     )), this, SLOT(onValveReadedInterfaceCfgDNetBaudrate      (ValveResponseInterfaceConfigDNetBaudrateDto       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_DATA_TYPE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetDataType        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetDataType      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_POS_UNIT                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetPosUnit         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetPosUnit       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_POS_GAIN                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetPosGain         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetPosGain       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_PRESSURE_UNIT              connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetPressureUnit    (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetPressureUnit  (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_S01_GAIN                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetSensor01Gain    (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetSensor01Gain  (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_S02_GAIN                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetSensor02Gain    (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetSensor02Gain  (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_INPUT_ASS                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetInputAss        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetInputAss      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_OUTPUT_ASS                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetOutputAss       (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetOutputAss     (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_DEV_STATUS                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetDevStatus       (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetDevStatus     (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_DNET_EX_STATUS                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetExStatus        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceCfgDNetExStatus      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DI                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetDi              (ValveResponseInterfaceConfigDNetDiDto           )), this, SLOT(onValveReadedInterfaceCfgDNetDi            (ValveResponseInterfaceConfigDNetDiDto             )))
#define ENABLE_SLOT_VALVE_READED_IF_CONFIG_DNET_DO                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgDNetDo              (ValveResponseInterfaceConfigDNetDoDto           )), this, SLOT(onValveReadedInterfaceCfgDNetDo            (ValveResponseInterfaceConfigDNetDoDto             )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_RS232                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgRS232               (ValveResponseInterfaceConfigRS232Dto            )), this, SLOT(onValveReadedInterfaceCfgRS232             (ValveResponseInterfaceConfigRS232Dto              )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_RS485                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgRS485               (ValveResponseInterfaceConfigRS485Dto            )), this, SLOT(onValveReadedInterfaceCfgRS485             (ValveResponseInterfaceConfigRS485Dto              )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_RS232_RANGE                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgRS232Range          (ValveResponseInterfaceConfigRS232RangeDto       )), this, SLOT(onValveReadedInterfaceCfgRS232Range        (ValveResponseInterfaceConfigRS232RangeDto         )))
#define ENABLE_SLOT_VALVE_READED_ETHERNET_IP                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceEthernetIP             (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceEthernetIP           (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_ETHERNET_SUBNET                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceEthernetSubnet         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceEthernetSubnet       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_ETHERNET_GATEWAY                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceEthernetGateway        (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceEthernetGateway      (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_ETHERNET_DHCP                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceEthernetDHCP           (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceEthernetDHCP         (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_ETHERNET_PORT01                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceEthernetPort01         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceEthernetPort01       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_ETHERNET_PORT02                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceEthernetPort02         (ValveResponseSimpleValueDto                     )), this, SLOT(onValveReadedInterfaceEthernetPort02       (ValveResponseSimpleValueDto                       )))
#define ENABLE_SLOT_VALVE_READED_IF_CFG_FIELDBUS_NODE_ADDR              connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceCfgFieldbusNodeAddr    (ValveResponseInterfaceConfigFieldbusNodeAddrDto )), this, SLOT(onValveReadedInterfaceCfgFieldbusNodeAddr  (ValveResponseInterfaceConfigFieldbusNodeAddrDto   )))
#define ENABLE_SLOT_VALVE_READED_IF_STATUS_LOGIC                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceStatusLogic            (ValveResponseInterfaceStatusLogicDto            )), this, SLOT(onValveReadedInterfaceStatusLogic          (ValveResponseInterfaceStatusLogicDto              )))
#define ENABLE_SLOT_VALVE_READED_IF_STATUS_ETHERCAT                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceStatusEtherCAT         (ValveResponseInterfaceStatusEtherCATDto         )), this, SLOT(onValveReadedInterfaceStatusEtherCAT       (ValveResponseInterfaceStatusEtherCATDto           )))
#define ENABLE_SLOT_VALVE_READED_IF_DNET_FIRMWARE_ID                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceDNetFirmwareID         (ValveResponseInterfaceDNetFirmwareIDDto         )), this, SLOT(onValveReadedInterfaceDNetFirmwareID       (ValveResponseInterfaceDNetFirmwareIDDto           )))
#define ENABLE_SLOT_VALVE_READED_IF_DNET_SERIAL_NUM                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceDNetSerialNum          (ValveResponseInterfaceDNetSerialNumDto          )), this, SLOT(onValveReadedInterfaceDNetSerialNum        (ValveResponseInterfaceDNetSerialNumDto            )))
#define ENABLE_SLOT_VALVE_READED_IF_STATUS_DNET                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceStatusDNet             (ValveResponseInterfaceStatusDNetDto             )), this, SLOT(onValveReadedInterfaceStatusDNet           (ValveResponseInterfaceStatusDNetDto               )))
#define ENABLE_SLOT_VALVE_READED_IF_STATUS_RS232                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedInterfaceStatusRS232            (ValveResponseInterfaceStatusRS232Dto            )), this, SLOT(onValveReadedInterfaceStatusRS232          (ValveResponseInterfaceStatusRS232Dto              )))
#define ENABLE_SLOT_VALVE_READED_CTRL_CYCLE                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedControlCycles                   (ValveResponseControlCyclesDto                   )), this, SLOT(onValveReadedControlCycles                 (ValveResponseControlCyclesDto                     )))
#define ENABLE_SLOT_VALVE_READED_TOTAL_CTRL_CYCLE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedTotalControlCycles              (ValveResponseTotalControlCyclesDto              )), this, SLOT(onValveReadedTotalControlCycles            (ValveResponseTotalControlCyclesDto                )))
#define ENABLE_SLOT_VALVE_READED_ISOL_CYCLE                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedIsolationCycles                 (ValveResponseIsolationCyclesDto                 )), this, SLOT(onValveReadedIsolationCycles               (ValveResponseIsolationCyclesDto                   )))
#define ENABLE_SLOT_VALVE_READED_TOTAL_ISOL_CYCLE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedTotalIsolationCycles            (ValveResponseTotalIsolationCyclesDto            )), this, SLOT(onValveReadedTotalIsolationCycles          (ValveResponseTotalIsolationCyclesDto              )))
#define ENABLE_SLOT_VALVE_READED_SENSOR01_OFFSET                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensor01Offset                  (ValveResponseSensorOffsetDto                    )), this, SLOT(onValveReadedSensor01Offset                (ValveResponseSensorOffsetDto                      )))
#define ENABLE_SLOT_VALVE_READED_SENSOR02_OFFSET                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSensor02Offset                  (ValveResponseSensorOffsetDto                    )), this, SLOT(onValveReadedSensor02Offset                (ValveResponseSensorOffsetDto                      )))
#define ENABLE_SLOT_VALVE_READED_LEARN_PRESSURE_LIMIT                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedLearnPressureLimit              (ValveResponseLearnPressureLimitDto              )), this, SLOT(onValveReadedLearnPressureLimit            (ValveResponseLearnPressureLimitDto                )))
#define ENABLE_SLOT_VALVE_READED_LEARN_STATUS                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedLearnStatus                     (ValveResponseLearnStatusDto                     )), this, SLOT(onValveReadedLearnStatus                   (ValveResponseLearnStatusDto                       )))
#define ENABLE_SLOT_VALVE_READED_SETPOINT_01                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSetPoint01                      (ValveResponseSetPointDto                        )), this, SLOT(onValveReadedSetpoint01                    (ValveResponseSetPointDto                          )))
#define ENABLE_SLOT_VALVE_READED_SETPOINT_02                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSetPoint02                      (ValveResponseSetPointDto                        )), this, SLOT(onValveReadedSetpoint02                    (ValveResponseSetPointDto                          )))
#define ENABLE_SLOT_VALVE_READED_SETPOINT_03                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSetPoint03                      (ValveResponseSetPointDto                        )), this, SLOT(onValveReadedSetpoint03                    (ValveResponseSetPointDto                          )))
#define ENABLE_SLOT_VALVE_READED_SETPOINT_04                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSetPoint04                      (ValveResponseSetPointDto                        )), this, SLOT(onValveReadedSetpoint04                    (ValveResponseSetPointDto                          )))
#define ENABLE_SLOT_VALVE_READED_SETPOINT_05                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSetPoint05                      (ValveResponseSetPointDto                        )), this, SLOT(onValveReadedSetpoint05                    (ValveResponseSetPointDto                          )))
#define ENABLE_SLOT_VALVE_READED_SETPOINT_06                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedSetPoint06                      (ValveResponseSetPointDto                        )), this, SLOT(onValveReadedSetpoint06                    (ValveResponseSetPointDto                          )))
#define ENABLE_SLOT_VALVE_READED_PFO_PERFORMED_CYCLES                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedPFOPerformedCycles              (ValveResponsePFOPerformedCyclesDto              )), this, SLOT(onValveReadedPFOPerformedCycles            (ValveResponsePFOPerformedCyclesDto                )))
#define ENABLE_SLOT_VALVE_READED_PFO_CURRENT_VOLTAGE                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventReadedPFOCurrentVoltage               (ValveResponsePFOCurrentVoltageDto               )), this, SLOT(onValveReadedPFOCurrentVoltage             (ValveResponsePFOCurrentVoltageDto                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_TRACE_MODE                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenTraceMode                      (ValveResponseDto                                )), this, SLOT(onValveWrittenTraceMode                    (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_ACCESS                                connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenAccess                         (ValveResponseDto                                )), this, SLOT(onValveWrittenAcces                        (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_TARGET_POSITION                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenTargetPosition                 (ValveResponseDto                                )), this, SLOT(onValveWrittenTargetPosition               (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_TARGET_PRESSURE                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenTargetPressure                 (ValveResponseDto                                )), this, SLOT(onValveWrittenTargetPressure               (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_VALVE_SPEED                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenValveSpeed                     (ValveResponseDto                                )), this, SLOT(onValveWrittenValveSpeed                   (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_VALVE_SETUP                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenValveSetup                     (ValveResponseDto                                )), this, SLOT(onValveWrittenValveSetup                   (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenValveParam                     (ValveResponseDto                                )), this, SLOT(onValveWrittenValveParam                   (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_START                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenValveParamStart                (ValveResponseDto                                )), this, SLOT(onValveWrittenValveParamStart              (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_END                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenValveParamEnd                  (ValveResponseDto                                )), this, SLOT(onValveWrittenValveParamEnd                (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_FACTORY_RESET                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFactoryReset                   (ValveResponseDto                                )), this, SLOT(onValveWrittenFactoryReset                 (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_LEARN_RESET                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenLearnReset                     (ValveResponseDto                                )), this, SLOT(onValveWrittenLearnReset                   (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_VALVE_PARAM_RESET                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenValveParamReset                (ValveResponseDto                                )), this, SLOT(onValveWrittenValveParamReset              (ValveResponseDto                                  )))
//#define ENABLE_SLOT_VALVE_WRITTEN_FATAL_ERR_RESET                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFatalErrReset                  (ValveSProviderDto                               )), this, SLOT(onValveWrittenFatalErrReset                (ValveSProviderDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_REBOOT                                connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenReboot                         (ValveResponseDto                                )), this, SLOT(onValveWrittenReboot                       (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSOR_CONFIG                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSensorConfig                   (ValveResponseDto                                )), this, SLOT(onValveWrittenSensorConfig                 (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSOR_SCALE                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSensorScale                    (ValveResponseDto                                )), this, SLOT(onValveWrittenSensorScale                  (ValveResponseDto                                  )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_SEL                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSensorExSelection              (ValveResponseDto                                )), this, SLOT(onValveWrittenSensorExSelection             (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ANAL_ACTIVE                connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExAnalActive                (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExAnalActive               (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SRC                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExSource                    (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExSource                   (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_UNIT                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExUnit                      (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExUnit                     (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_FULLSCALE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExFullScale                 (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExFullScale                (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_DIGI                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExDigiValue                 (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExDigiValue                (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_ENABLE                connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExZeroAdjEnable             (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExZeroAdjEnable            (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_MIN                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExZeroAdjOffsetLimMin       (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExZeroAdjOffsetLimMin      (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_MAX                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExZeroAdjOffsetLimMax       (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExZeroAdjOffsetLimMax      (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_ZERO_VALUE                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExZeroAdjOffsetValue        (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExZeroAdjOffsetValue       (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SCALE_OFFSET               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExScaleOffset               (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExScaleOffset              (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SCALE                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExScale                     (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExScale                    (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_SCALE_Z_POINT              connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExScaleZeroPoint            (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExScaleZeroPoint           (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_FILTER_SEC                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExFilterSec                 (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExFilterSec                (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_LOG_SENS_LINEARIZE         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExLogSensorLinearize        (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExLogSensorLinearize       (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_LOG_SENS_VOLT_DECADE       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExLogSensorVoltPerDecade    (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExLogSensorVoltPerDecade   (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE    connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS01ExLogSensorVoltAtFullScale  (ValveResponseDto                                )), this, SLOT(onValveWrittenS01ExLogSensorVoltAtFullScale (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ANAL_ACTIVE                connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExAnalActive                (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExAnalActive               (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SRC                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExSource                    (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExSource                   (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_UNIT                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExUnit                      (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExUnit                     (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_FULLSCALE                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExFullScale                 (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExFullScale                (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_DIGI                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExDigiValue                 (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExDigiValue                (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_ENABLE                connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExZeroAdjEnable             (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExZeroAdjEnable            (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_MIN                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExZeroAdjOffsetLimMin       (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExZeroAdjOffsetLimMin      (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_MAX                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExZeroAdjOffsetLimMax       (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExZeroAdjOffsetLimMax      (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_ZERO_VALUE                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExZeroAdjOffsetValue        (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExZeroAdjOffsetValue       (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SCALE_OFFSET               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExScaleOffset               (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExScaleOffset              (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SCALE                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExScale                     (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExScale                    (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_SCALE_Z_POINT              connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExScaleZeroPoint            (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExScaleZeroPoint           (ValveResponseDto                                 )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_FILTER_SEC                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExFilterSec                 (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExFilterSec                 (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_LOG_SENS_LINEARIZE         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExLogSensorLinearize        (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExLogSensorLinearize        (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_LOG_SENS_VOLT_DECADE       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExLogSensorVoltPerDecade    (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExLogSensorVoltPerDecade    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE    connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenS02ExLogSensorVoltAtFullScale  (ValveResponseDto                                )), this, SLOT(onValveWrittenS02ExLogSensorVoltAtFullScale  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_MOD                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenCrossoverMod                   (ValveResponseDto                                )), this, SLOT(onValveWrittenCrossoverMod                   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_LOW                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenCrossoverLow                   (ValveResponseDto                                )), this, SLOT(onValveWrittenCrossoverLow                   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_HIGH                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenCrossoverHigh                  (ValveResponseDto                                )), this, SLOT(onValveWrittenCrossoverHigh                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSEX_CROSSOVER_DELA                 connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenCrossoverDela                  (ValveResponseDto                                )), this, SLOT(onValveWrittenCrossoverDela                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_DP_CONFIG                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenDisplayConfig                  (ValveResponseDto                                )), this, SLOT(onValveWrittenDisplayConfig                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_PRESSURE_CTRL_CONFIG                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenPressureCtrlConfig             (ValveResponseDto                                )), this, SLOT(onValveWrittenPressureCtrlConfig             (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SEL_CONTROL_MODE                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSelContrlMode                  (ValveResponseDto                                )), this, SLOT(onValveWrittenSelContrlMode                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ADAP_GAIN_FACTOR                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenAdapGainFactor                 (ValveResponseDto                                )), this, SLOT(onValveWrittenAdapGainFactor                 (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ADAP_DELTA_FACTOR                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenAdapDeltaFactor                (ValveResponseDto                                )), this, SLOT(onValveWrittenAdapDeltaFactor                (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ADAP_SENSOR_DELAY                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenAdapSensorDelay                (ValveResponseDto                                )), this, SLOT(onValveWrittenAdapSensorDelay                (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ADAP_RAMP_TIME                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenAdapRampTime                   (ValveResponseDto                                )), this, SLOT(onValveWrittenAdapRampTime                   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ADAP_RAMP_MODE                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenAdapRampMode                   (ValveResponseDto                                )), this, SLOT(onValveWrittenAdapRampMode                   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED1_P_GAIN                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed1PGain                    (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed1PGain                    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED1_I_GAIN                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed1IGain                    (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed1IGain                    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED1_RAMP_TIME                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed1RampTime                 (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed1RampTime                 (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED1_RAMP_MODE                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed1RampMode                 (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed1RampMode                 (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED1_CTRL_DIR                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed1CtrlDir                  (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed1CtrlDir                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED2_P_GAIN                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed2PGain                    (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed2PGain                    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED2_I_GAIN                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed2IGain                    (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed2IGain                    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED2_RAMP_TIME                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed2RampTime                 (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed2RampTime                 (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED2_RAMP_MODE                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed2RampMode                 (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed2RampMode                 (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_FIXED2_CTRL_DIR                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenFixed2CtrlDir                  (ValveResponseDto                                )), this, SLOT(onValveWrittenFixed2CtrlDir                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_LEARN_PARAM                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenLearnParam                     (ValveResponseDto                                )), this, SLOT(onValveWrittenLearnParam                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_LOGIC                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigLogic           (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigLogic           (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_ETHCAT_DI                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigEthCATDi        (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigEthCATDi        (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_ETHCAT_DO                   connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigEthCATDo        (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigEthCATDo        (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_DEV_ID                  connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceCfgEthCATDevID        (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceCfgEthCATDevID        (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_DATA_TYPE           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceCfgEthCATPDODataType  (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceCfgEthCATPDODataType  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_ETHCAT_PDO_RANGE               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceCfgEthCATPDORange     (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceCfgEthCATPDORange     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_DATA_TYPE              connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetDataType    (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetDataType    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_MAC_ADDR               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetMacAddr     (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetMacAddr     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_BAUDRATE               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetBaudrate    (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetBaudrate    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_POS_UNIT               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetPosUnit     (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetPosUnit     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_POS_GAIN               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetPosGain     (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetPosGain     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_PRESSURE_UNIT          connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetPressureUnit(ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetPressureUnit(ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_S01_GAIN               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetSensor01Gain(ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetSensor01Gain(ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_S02_GAIN               connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetSensor02Gain(ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetSensor02Gain(ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_INPUT_ASS              connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetInputAss    (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetInputAss    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_OUTPUT_ASS             connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetOutputAss   (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetOutputAss   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_DI                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetDi          (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetDi          (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CONFIG_DNET_DO                     connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceConfigDNetDo          (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceConfigDNetDo          (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS232                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceCfgRS232              (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceCfgRS232              (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS485                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceCfgRS485              (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceCfgRS485              (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_RS232_RANGE                    connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceCfgRS232Range         (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceCfgRS232Range         (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_IP                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceEthernetIP            (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceEthernetIP            (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_SUBNET                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceEthernetSubnet        (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceEthernetSubnet        (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_GATEWAY                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceEthernetGateway       (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceEthernetGateway       (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_DHCP                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceEthernetDHCP          (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceEthernetDHCP          (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_PORT01                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceEthernetPort01        (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceEthernetPort01        (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ETHERNET_PORT02                       connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceEthernetPort02        (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceEthernetPort02        (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_IF_CFG_FIELDBUS_NODE_ADDR             connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenInterfaceCfgFieldbusNodeAddr   (ValveResponseDto                                )), this, SLOT(onValveWrittenInterfaceCfgFieldbusNodeAddr   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_CTRL_CYCLE_RESET                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenControlCyclesReset             (ValveResponseDto                                )), this, SLOT(onValveWrittenControlCyclesReset             (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ISOL_CYCLE_RESET                      connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenIsolationCyclesReset           (ValveResponseDto                                )), this, SLOT(onValveWrittenIsolationCyclesReset           (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ADC_GAINZERO                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenAdcGainZero                    (ValveResponseDto                                )), this, SLOT(onValveWrittenAdcGainZero                    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SENSOR_ZERO                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSensorZero                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSensorZero                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_LEARN_RUN                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenLearnRun                       (ValveResponseDto                                )), this, SLOT(onValveWrittenLearnRun                       (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SIMULATION                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSimulation                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSimulation                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_HOLD_POS                              connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenHoldPosition                   (ValveResponseDto                                )), this, SLOT(onValveWrittenHoldPosition                   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_OPEN_POS                              connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenOpenPosition                   (ValveResponseDto                                )), this, SLOT(onValveWrittenOpenPosition                   (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_CLOSE_POS                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenClosePosition                  (ValveResponseDto                                )), this, SLOT(onValveWrittenClosePosition                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_01                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSetPoint01                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSetPoint01                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_02                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSetPoint02                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSetPoint02                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_03                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSetPoint03                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSetPoint03                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_04                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSetPoint04                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSetPoint04                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_05                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSetPoint05                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSetPoint05                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SETPOINT_06                           connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSetPoint06                     (ValveResponseDto                                )), this, SLOT(onValveWrittenSetPoint06                     (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ENABLE_PFO                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenEnablePFO                      (ValveResponseDto                                )), this, SLOT(onValveWrittenEnablePFO                      (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SOFT_OPEN                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSoftOpen                       (ValveResponseDto                                )), this, SLOT(onValveWrittenSoftOpen                       (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_SOFT_CLOSE                            connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenSoftClose                      (ValveResponseDto                                )), this, SLOT(onValveWrittenSoftClose                      (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_TEST_MODE                             connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenTestMode                       (ValveResponseDto                                )), this, SLOT(onValveWrittenTestMode                       (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_ENCODER_ZERO                          connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenEncoderZero                    (ValveResponseDto                                )), this, SLOT(onValveWrittenEncoderZero                    (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_WRITTEN_CUSTOM_REQUEST                        connect(ValveSProvider::getInstance(), SIGNAL(signalEventWrittenCustomRequest                  (ValveResponseDto                                )), this, SLOT(onValveWrittenCustomRequest                  (ValveResponseDto                                )))
#define ENABLE_SLOT_VALVE_TRACE                                         connect(ValveSProvider::getInstance(), SIGNAL(signalEventReceivedTraceData                     (QString                                         )), this, SLOT(onValveRecevedTraceData                      (QString                                         )))

class ReqCommandUserData : public QObject
{
    Q_OBJECT

public:
    bool mCancel = false;
    int  mIntegerTag = 0;

    ReqCommandUserData(QObject *parent = nullptr): QObject(parent)
    {

    }
    ~ReqCommandUserData()
    {

    }
};

class ValveSProvider : public QObject
{
    Q_OBJECT

private:
    QThread           * mpASyncWorkerThread = nullptr;
    ValveASyncWorker  * mpASyncWorker       = nullptr;
    QThread           * mpDFUWorkerThread   = nullptr;
    ValveFirmwareUpgradeWorker  * mpDFUWorker         = nullptr;
    qint64              mLastRcvMSec        = 0;
    QList<int>          mPosResolutionOption = {100000, 10000, 1000, 100};
    QList<int>          mPressureDecadesOption = { 1, 2, 3, 4, 5};
    int                 mLogSkipCount       = 100;

    /* properties */
    bool        mIsRunning          = false;
    bool        mIsConnected        = false;
    bool        mRetryConnect       = false;
    int         mLoadProgress       = ValveEnumDef::LOAD_NONE;
    int         mDFUStep            = ValveFirmwareUpgradeDef::eStep::READY;
    int         mDFUPctCpu1Kernel  = 0;
    int         mDFUPctCpu2Kernel  = 0;
    int         mDFUPctCpu1App     = 0;
    int         mDFUPctCpu2App     = 0;
    int         mDFUPctCpu1Verify  = 0;
    int         mDFUPctCpu2Verify  = 0;
    QString     mConnectionInfo     = "";

    qint64      mCurrPosition       = 0;
    qint64      mCurrPressure       = 0;
    qint64      mTargetPosition     = 0;
    qint64      mTargetPressure     = 0; // khko_test
    qint64      mValveSpeed         = 0;
    int         mValveMaxSpeed      = 0;
    int         mPressureCtrlMode   = ValveEnumDef::PRESSURE_CTRL_ADAPTIVE;
    QString     mAdaptiveGainFactor = "0";
    QString     mAdaptiveDeltaFactor= "0";
    QString     mAdaptiveSensorDelay= "0";
    QString     mAdaptiveRampTime   = "0";
    int         mAdaptiveRampMode   = 0;
    QString     mFixed1PGain        = "0";
    QString     mFixed1IGain        = "0";
    QString     mFixed1RampTime     = "0";
    int         mFixed1RampMode     = 0;
    int         mFixed1Dir          = 0;
    QString     mFixed2PGain        = "0";
    QString     mFixed2IGain        = "0";
    QString     mFixed2RampTime     = "0";
    int         mFixed2RampMode     = 0;
    int         mFixed2Dir          = 0;
    int         mAccess             = ValveEnumDef::ACCESS_REMOTE;
    int         mMode               = ValveEnumDef::MODE_OPEN;
    int         mControlMode        = ValveEnumDef::MODE_POSITION;
    int         mS01SullScaleUnit   = ValveEnumDef::PRESSURE_UNIT_MTORR;
    double      mS01FullScale       = 1000000;
    int         mS01FullScalePrec   = 0;
    int         mS02SullScaleUnit   = ValveEnumDef::PRESSURE_UNIT_MTORR;
    double      mS02FullScale       = 1000000;
    int         mS02FullScalePrec   = 0;
    int         mSensorOperation    = ValveEnumDef::SENSOROP_NO_SENSOR;
    int         mSensor01Offset     = 0;
    int         mSensor02Offset     = 0;
    bool        mZeroEnable         = false;
    int         mPositionResolution = 10000;
    int         mPressureDpUnit     = ValveEnumDef::PRESSURE_UNIT_MTORR;
    int         mPressureAxisMode   = ValveEnumDef::PRESSURE_AXIS_LINEAR;
    int         mPressureDecades    = 5;
    bool        mIsSimulation       = false;
    bool        mEnablePFO          = false;
    bool        mIsTestMode         = false;
    bool        mFieldBusError      = false;
    bool        mIsSaving           = false;
    bool        mIsIDMissing        = false;
    bool        mIsPFOMissing       = false;
    bool        mFirmwareError      = false;
    bool        mUnknowInterface    = false;
    bool        mNoSensorSignal     = false;
    bool        mNoAnalogSignal     = false;
    bool        mNetworkFailure     = false;
    bool        mSlaveOffline       = false;
    bool        mIsolationValve     = false;
    bool        mSensorError        = false;
    bool        mSvcRequest         = false;
    bool        mLearnNotPresent    = false;
    bool        mAirNotReady        = false;
    bool        mPFONotReady        = false;
    int         mSetPoint01Position = 0;
    int         mSetPoint02Position = 0;
    int         mSetPoint03Position = 0;
    int         mSetPoint04Position = 0;
    int         mSetPoint05Position = 0;
    int         mSetPoint06Position = 0;
    int         mSetPoint01Pressure = 0;
    int         mSetPoint02Pressure = 0;
    int         mSetPoint03Pressure = 0;
    int         mSetPoint04Pressure = 0;
    int         mSetPoint05Pressure = 0;
    int         mSetPoint06Pressure = 0;

    QString     mValveID            = "";
    QString     mFirmwareVersion    = "0";
    bool        mIsSealingType      = false;
    bool        mIsSupportPFO       = false;
    bool        mIsSupportSPS       = false;
    bool        mIsSupportAnalogOut = false;
    int         mInterface          = ValveEnumDef::INTERFACE_LOGIC;
    int         mSensorVersion      = 1;

    qint64      mScanRate           = -1;

    bool        mIsRS232Test        = false;

public:
    // get properties
    bool        getIsRunning                    (){ return mIsRunning         ;}
    bool        getIsConnected                  (){ return mIsConnected       ;}
    bool        getRetryConnect                 (){ return mRetryConnect      ;}
    int         getLoadProgress                 (){ return mLoadProgress      ;}
    int         getDFUStep                      (){ return mDFUStep           ;}
    int         getDFUPctCpu1Kernel             (){ return mDFUPctCpu1Kernel  ;}
    int         getDFUPctCpu2Kernel             (){ return mDFUPctCpu2Kernel  ;}
    int         getDFUPctCpu1App                (){ return mDFUPctCpu1App     ;}
    int         getDFUPctCpu2App                (){ return mDFUPctCpu2App     ;}
    int         getDFUPctCpu1Verify             (){ return mDFUPctCpu1Verify  ;}
    int         getDFUPctCpu2Verify             (){ return mDFUPctCpu2Verify  ;}
    QString     getConnectionInfo               (){ return mConnectionInfo    ;}

    qint64      getCurrPosition                 (){ return mCurrPosition      ;}
    qint64      getCurrPressure                 (){ return mCurrPressure      ;}
    qint64      getTargetPosition               (){ return mTargetPosition    ;}
    qint64      getTargetPressure               (){ return mTargetPressure    ;}
    qint64      getValveSpeed                   (){ return mValveSpeed        ;}
    int         getValveMaxSpeed                (){ return mValveMaxSpeed     ;}
    int         getPressureCtrlMode             (){ return mPressureCtrlMode  ;}
    QString     getAdaptiveGainFactor           (){ return mAdaptiveGainFactor ;}
    QString     getAdaptiveDeltaFactor          (){ return mAdaptiveDeltaFactor;}
    QString     getAdaptiveSensorDelay          (){ return mAdaptiveSensorDelay;}
    QString     getAdaptiveRampTime             (){ return mAdaptiveRampTime   ;}
    int         getAdaptiveRampMode             (){ return mAdaptiveRampMode   ;}
    QString     getFixed1PGain                  (){ return mFixed1PGain        ;}
    QString     getFixed1IGain                  (){ return mFixed1IGain        ;}
    QString     getFixed1RampTime               (){ return mFixed1RampTime     ;}
    int         getFixed1RampMode               (){ return mFixed1RampMode     ;}
    int         getFixed1Dir                    (){ return mFixed1Dir          ;}
    QString     getFixed2PGain                  (){ return mFixed2PGain        ;}
    QString     getFixed2IGain                  (){ return mFixed2IGain        ;}
    QString     getFixed2RampTime               (){ return mFixed2RampTime     ;}
    int         getFixed2RampMode               (){ return mFixed2RampMode     ;}
    int         getFixed2Dir                    (){ return mFixed2Dir          ;}
    int         getAccess                       (){ return mAccess            ;}
    int         getMode                         (){ return mMode              ;}
    int         getControlMode                  (){ return mControlMode       ;}
    int         getS01SullScaleUnit             (){ return mS01SullScaleUnit  ;}
    double      getS01FullScale                 (){ return mS01FullScale      ;}
    int         getS01FullScalePrec             (){ return mS01FullScalePrec  ;}
    int         getS02SullScaleUnit             (){ return mS02SullScaleUnit  ;}
    double      getS02FullScale                 (){ return mS02FullScale      ;}
    int         getS02FullScalePrec             (){ return mS02FullScalePrec  ;}
    int         getSensorOperation              (){ return mSensorOperation   ;}
    int         getSensor01Offset               (){ return mSensor01Offset    ;}
    int         getSensor02Offset               (){ return mSensor02Offset    ;}
    bool        getZeroEnable                   (){ return mZeroEnable        ;}
    int         getPositionResolution           (){ return mPositionResolution;}
    int         getPressureDpUnit               (){ return mPressureDpUnit    ;}
    int         getPressureAxisMode             (){ return mPressureAxisMode  ;}
    int         getPressureDecades              (){ return mPressureDecades   ;}
    bool        getIsSimulation                 (){ return mIsSimulation      ;}
    bool        getEnablePFO                    (){ return mEnablePFO         ;}
    bool        getIsTestMode                   (){ return mIsTestMode        ;}
    bool        getFieldBusError                (){ return mFieldBusError     ;}
    bool        getIsSaving                     (){ return mIsSaving          ;}
    bool        getIsIDMissing                  (){ return mIsIDMissing       ;}
    bool        getIsPFOMissing                 (){ return mIsPFOMissing      ;}
    bool        getFirmwareError                (){ return mFirmwareError     ;}
    bool        getUnknowInterface              (){ return mUnknowInterface   ;}
    bool        getNoSensorSignal               (){ return mNoSensorSignal    ;}
    bool        getNoAnalogSignal               (){ return mNoAnalogSignal    ;}
    bool        getNetworkFailure               (){ return mNetworkFailure    ;}
    bool        getSlaveOffline                 (){ return mSlaveOffline      ;}
    bool        getIsolationValve               (){ return mIsolationValve    ;}
    bool        getSensorError                  (){ return mSensorError       ;}
    bool        getSvcRequest                   (){ return mSvcRequest        ;}
    bool        getLearnNotPresent              (){ return mLearnNotPresent   ;}
    bool        getAirNotReady                  (){ return mAirNotReady       ;}
    bool        getPFONotReady                  (){ return mPFONotReady       ;}
    int         getSetPoint01Position           (){ return mSetPoint01Position;}
    int         getSetPoint02Position           (){ return mSetPoint02Position;}
    int         getSetPoint03Position           (){ return mSetPoint03Position;}
    int         getSetPoint04Position           (){ return mSetPoint04Position;}
    int         getSetPoint05Position           (){ return mSetPoint05Position;}
    int         getSetPoint06Position           (){ return mSetPoint06Position;}
    int         getSetPoint01Pressure           (){ return mSetPoint01Pressure;}
    int         getSetPoint02Pressure           (){ return mSetPoint02Pressure;}
    int         getSetPoint03Pressure           (){ return mSetPoint03Pressure;}
    int         getSetPoint04Pressure           (){ return mSetPoint04Pressure;}
    int         getSetPoint05Pressure           (){ return mSetPoint05Pressure;}
    int         getSetPoint06Pressure           (){ return mSetPoint06Pressure;}

    QString     getFirmwareVersion              (){ return mFirmwareVersion   ;}
    QString     getValveID                      (){ return mValveID           ;}
    bool        getIsSealingType                (){ return mIsSealingType     ;}
    bool        getIsSupportPFO                 (){ return mIsSupportPFO      ;}
    bool        getIsSupportSPS                 (){ return mIsSupportSPS      ;}
    bool        getIsSupportAnalogOut           (){ return mIsSupportAnalogOut;}
    int         getInterface                    (){ return mInterface         ;}
    int         getSensorVersion                (){ return mSensorVersion     ;}
    qint64      getScanRate                     (){ return mScanRate          ;}
    bool        getIsRS232Test                  (){ return mIsRS232Test       ;}

    // set properties
    void        setIsRunning                    (bool        value){ if(mIsRunning          == value) return; mIsRunning          = value; emit signalEventChangedIsRunning         (value); }
    void        setIsConnected                  (bool        value){ if(mIsConnected        == value) return; mIsConnected        = value; emit signalEventChangedIsConnected       (value); }
    void        setConnectionInfo               (QString     value){ if(mConnectionInfo     == value) return; mConnectionInfo     = value; emit signalEventChangedConnectionInfo    (value); }
    void        setLoadProgress                 (int         value)
    {
        qDebug() << "[ValveSProvider][setLoadProgress]" << value;

        if(mLoadProgress == value)
            return;

        mLoadProgress = value; emit signalEventChangedLoadProgress(value);

        if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED)
            return;

        emit signalEventChangedLoadProgress      (value);

        emit signalEventChangedCurrPosition      (     );
        emit signalEventChangedCurrPressure      (     );
        emit signalEventChangedTargetPosition    (     );
        emit signalEventChangedTargetPressure    (     );
        emit signalEventChangedValveSpeed        (     );
        emit signalEventChangedValveMaxSpeed     (     );
        emit signalEventChangedPressureCtrlMode  (     );
        emit signalEventChangedAccess            (     );
        emit signalEventChangedMode              (     );
        emit signalEventChangedControlMode       (     );
        emit signalEventChangedS01FullScale      (     );
        emit signalEventChangedS02FullScale      (     );
        emit signalEventChangedS01FullScalePrec  (     );
        emit signalEventChangedS02FullScalePrec  (     );
        emit signalEventChangedSensorOperation   (     );
        emit signalEventChangedSensor01Offset    (     );
        emit signalEventChangedSensor02Offset    (     );
        emit signalEventChangedZeroEnable        (     );
        emit signalEventChangedPositionResolution(     );
        emit signalEventChangedPressureDpUnit    (     );
        emit signalEventChangedPressureAxisMode  (     );
        emit signalEventChangedPressureDecades   (     );
        emit signalEventChangedIsSimulation      (     );
        emit signalEventChangedEnablePFO         (     );
        emit signalEventChangedIsTestMode        (     );
        emit signalEventChangedFieldBusError     (     );
        emit signalEventChangedIsSaving          (     );
        emit signalEventChangedIsIDMissing       (     );
        emit signalEventChangedIsPFOMissing      (     );
        emit signalEventChangedFirmwareError     (     );
        emit signalEventChangedUnknowInterface   (     );
        emit signalEventChangedNoSensorSignal    (     );
        emit signalEventChangedNoAnalogSignal    (     );
        emit signalEventChangedNetworkFailure    (     );
        emit signalEventChangedSlaveOffline      (     );
        emit signalEventChangedIsolationValve    (     );
        emit signalEventChangedSensorError       (     );
        emit signalEventChangedSvcRequest        (     );
        emit signalEventChangedLearnNotPresent   (     );
        emit signalEventChangedAirNotReady       (     );
        emit signalEventChangedPFONotReady       (     );
        emit signalEventChangedIsSealingType     (     );
        emit signalEventChangedIsSupportPFO      (     );
        emit signalEventChangedIsSupportSPS      (     );
        emit signalEventChangedIsSupportAnalogOut(     );
        emit signalEventChangedInterface         (     );
        emit signalEventChangedSensorVersion     (     );
        emit signalEventChangedValveID           (     );
        emit signalEventChangedFirmwareVersion   (     );
        emit signalEventChangedSetPoint01Position(     );
        emit signalEventChangedSetPoint02Position(     );
        emit signalEventChangedSetPoint03Position(     );
        emit signalEventChangedSetPoint04Position(     );
        emit signalEventChangedSetPoint05Position(     );
        emit signalEventChangedSetPoint06Position(     );
        emit signalEventChangedSetPoint01Pressure(     );
        emit signalEventChangedSetPoint02Pressure(     );
        emit signalEventChangedSetPoint03Pressure(     );
        emit signalEventChangedSetPoint04Pressure(     );
        emit signalEventChangedSetPoint05Pressure(     );
        emit signalEventChangedSetPoint06Pressure(     );
    }
    void        setDFUStep                      (int         value){if(mDFUStep            == value) return; mDFUStep            = value; emit signalEventChangedDFUStep           ();}
    void        setDFUPctCpu1Kernel             (int         value){if(mDFUPctCpu1Kernel   == value) return; mDFUPctCpu1Kernel   = value; emit signalEventChangedDFUPctCpu1Kernel  ();}
    void        setDFUPctCpu2Kernel             (int         value){if(mDFUPctCpu2Kernel   == value) return; mDFUPctCpu2Kernel   = value; emit signalEventChangedDFUPctCpu2Kernel  ();}
    void        setDFUPctCpu1App                (int         value){if(mDFUPctCpu1App      == value) return; mDFUPctCpu1App      = value; emit signalEventChangedDFUPctCpu1App     ();}
    void        setDFUPctCpu2App                (int         value){if(mDFUPctCpu2App      == value) return; mDFUPctCpu2App      = value; emit signalEventChangedDFUPctCpu2App     ();}
    void        setDFUPctCpu1Verify             (int         value){if(mDFUPctCpu1Verify   == value) return; mDFUPctCpu1Verify   = value; emit signalEventChangedDFUPctCpu1Verify  ();}
    void        setDFUPctCpu2Verify             (int         value){if(mDFUPctCpu2Verify   == value) return; mDFUPctCpu2Verify   = value; emit signalEventChangedDFUPctCpu2Verify  ();}

    void        setCurrPosition                 (qint64      value){if(mCurrPosition       == value) return; mCurrPosition       = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedCurrPosition      ();}
    void        setCurrPressure                 (qint64      value){if(mCurrPressure       == value) return; mCurrPressure       = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedCurrPressure      ();}
    void        setTargetPosition               (qint64      value){if(mTargetPosition     == value) return; mTargetPosition     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedTargetPosition    ();}
    void        setTargetPressure               (qint64      value){if(mTargetPressure     == value) return; mTargetPressure     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedTargetPressure    ();}
    void        setValveSpeed                   (qint64      value){if(mValveSpeed         == value) return; mValveSpeed         = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedValveSpeed        ();}
    void        setValveMaxSpeed                (int         value){if(mValveMaxSpeed      == value) return; mValveMaxSpeed      = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedValveMaxSpeed     ();}
    void        setPressureCtrlMode             (int         value){if(mPressureCtrlMode   == value) return; mPressureCtrlMode   = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedPressureCtrlMode  ();}
    void        setAdaptiveGainFactor           (QString     value){if(mAdaptiveGainFactor == value) return; mAdaptiveGainFactor = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setAdaptiveDeltaFactor          (QString     value){if(mAdaptiveDeltaFactor== value) return; mAdaptiveDeltaFactor= value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setAdaptiveSensorDelay          (QString     value){if(mAdaptiveSensorDelay== value) return; mAdaptiveSensorDelay= value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setAdaptiveRampTime             (QString     value){if(mAdaptiveRampTime   == value) return; mAdaptiveRampTime   = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setAdaptiveRampMode             (int         value){if(mAdaptiveRampMode   == value) return; mAdaptiveRampMode   = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed1PGain                  (QString     value){if(mFixed1PGain        == value) return; mFixed1PGain        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed1IGain                  (QString     value){if(mFixed1IGain        == value) return; mFixed1IGain        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed1RampTime               (QString     value){if(mFixed1RampTime     == value) return; mFixed1RampTime     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed1RampMode               (int         value){if(mFixed1RampMode     == value) return; mFixed1RampMode     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed1Dir                    (int         value){if(mFixed1Dir          == value) return; mFixed1Dir          = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed2PGain                  (QString     value){if(mFixed2PGain        == value) return; mFixed2PGain        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed2IGain                  (QString     value){if(mFixed2IGain        == value) return; mFixed2IGain        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed2RampTime               (QString     value){if(mFixed2RampTime     == value) return; mFixed2RampTime     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed2RampMode               (int         value){if(mFixed2RampMode     == value) return; mFixed2RampMode     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setFixed2Dir                    (int         value){if(mFixed2Dir          == value) return; mFixed2Dir          = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return;                                             }
    void        setAccess                       (int         value){if(mAccess             == value) return; mAccess             = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedAccess            ();}
    void        setMode                         (int         value){if(mMode               == value) return; mMode               = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedMode              ();}
    void        setControlMode                  (int         value){if(mControlMode        == value) return; mControlMode        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedControlMode       ();}
    void        setS01FullScale                 (int unit, double value){if(mS01FullScale  == value && mS01SullScaleUnit == unit) return; mS01FullScale = value;  mS01SullScaleUnit = unit; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedS01FullScale(); }
    void        setS02FullScale                 (int unit, double value){if(mS02FullScale  == value && mS02SullScaleUnit == unit) return; mS02FullScale = value;  mS02SullScaleUnit = unit; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedS02FullScale(); }
    void        setS01FullScalePrec             (int         value){if(mS01FullScalePrec   == value) return; mS01FullScalePrec   = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedS01FullScalePrec  ();}
    void        setS02FullScalePrec             (int         value){if(mS02FullScalePrec   == value) return; mS02FullScalePrec   = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedS02FullScalePrec  ();}
    void        setSensorOperation              (int         value){if(mSensorOperation    == value) return; mSensorOperation    = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSensorOperation   ();}
    void        setSensor01Offset               (int         value){if(mSensor01Offset     == value) return; mSensor01Offset     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSensor01Offset    ();}
    void        setSensor02Offset               (int         value){if(mSensor02Offset     == value) return; mSensor02Offset     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSensor02Offset    ();}
    void        setZeroEnable                   (bool        value){if(mZeroEnable         == value) return; mZeroEnable         = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedZeroEnable        ();}
    void        setPositionResolution           (int         value){if(mPositionResolution == value) return; mPositionResolution = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedPositionResolution();}
    void        setPressureDpUnit               (int         value){if(mPressureDpUnit     == value) return; mPressureDpUnit     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedPressureDpUnit    ();}
    void        setPressureAxisMode             (int         value){if(mPressureAxisMode   == value) return; mPressureAxisMode   = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedPressureAxisMode  ();}
    void        setPressureDecades              (int         value){if(mPressureDecades    == value) return; mPressureDecades    = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedPressureDecades   ();}
    void        setIsSimulation                 (bool        value){if(mIsSimulation       == value) return; mIsSimulation       = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsSimulation      ();}
    void        setEnablePFO                    (bool        value){if(mEnablePFO          == value) return; mEnablePFO          = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedEnablePFO         ();}
    void        setIsTestMode                   (bool        value){if(mIsTestMode         == value) return; mIsTestMode         = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsTestMode        ();}
    void        setFieldBusError                (bool        value){if(mFieldBusError      == value) return; mFieldBusError      = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedFieldBusError     ();}
    void        setIsSaving                     (bool        value){if(mIsSaving           == value) return; mIsSaving           = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsSaving          ();}
    void        setIsIDMissing                  (bool        value){if(mIsIDMissing        == value) return; mIsIDMissing        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsIDMissing       ();}
    void        setIsPFOMissing                 (bool        value){if(mIsPFOMissing       == value) return; mIsPFOMissing       = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsPFOMissing      ();}
    void        setFirmwareError                (bool        value){if(mFirmwareError      == value) return; mFirmwareError      = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedFirmwareError     ();}
    void        setUnknowInterface              (bool        value){if(mUnknowInterface    == value) return; mUnknowInterface    = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedUnknowInterface   ();}
    void        setNoSensorSignal               (bool        value){if(mNoSensorSignal     == value) return; mNoSensorSignal     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedNoSensorSignal    ();}
    void        setNoAnalogSignal               (bool        value){if(mNoAnalogSignal     == value) return; mNoAnalogSignal     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedNoAnalogSignal    ();}
    void        setNetworkFailure               (bool        value){if(mNetworkFailure     == value) return; mNetworkFailure     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedNetworkFailure    ();}
    void        setSlaveOffline                 (bool        value){if(mSlaveOffline       == value) return; mSlaveOffline       = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSlaveOffline      ();}
    void        setIsolationValve               (bool        value){if(mIsolationValve     == value) return; mIsolationValve     = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsolationValve    ();}
    void        setSensorError                  (bool        value){if(mSensorError        == value) return; mSensorError        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSensorError       ();}
    void        setSvcRequest                   (bool        value){if(mSvcRequest         == value) return; mSvcRequest         = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSvcRequest        ();}
    void        setLearnNotPresent              (bool        value){if(mLearnNotPresent    == value) return; mLearnNotPresent    = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedLearnNotPresent   ();}
    void        setAirNotReady                  (bool        value){if(mAirNotReady        == value) return; mAirNotReady        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedAirNotReady       ();}
    void        setPFONotReady                  (bool        value){if(mPFONotReady        == value) return; mPFONotReady        = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedPFONotReady       ();}
    void        setSetPoint01Position           (int         value){if(mSetPoint01Position == value) return; mSetPoint01Position = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint01Position();}
    void        setSetPoint02Position           (int         value){if(mSetPoint02Position == value) return; mSetPoint02Position = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint02Position();}
    void        setSetPoint03Position           (int         value){if(mSetPoint03Position == value) return; mSetPoint03Position = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint03Position();}
    void        setSetPoint04Position           (int         value){if(mSetPoint04Position == value) return; mSetPoint04Position = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint04Position();}
    void        setSetPoint05Position           (int         value){if(mSetPoint05Position == value) return; mSetPoint05Position = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint05Position();}
    void        setSetPoint06Position           (int         value){if(mSetPoint06Position == value) return; mSetPoint06Position = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint06Position();}
    void        setSetPoint01Pressure           (int         value){if(mSetPoint01Pressure == value) return; mSetPoint01Pressure = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint01Pressure();}
    void        setSetPoint02Pressure           (int         value){if(mSetPoint02Pressure == value) return; mSetPoint02Pressure = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint02Pressure();}
    void        setSetPoint03Pressure           (int         value){if(mSetPoint03Pressure == value) return; mSetPoint03Pressure = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint03Pressure();}
    void        setSetPoint04Pressure           (int         value){if(mSetPoint04Pressure == value) return; mSetPoint04Pressure = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint04Pressure();}
    void        setSetPoint05Pressure           (int         value){if(mSetPoint05Pressure == value) return; mSetPoint05Pressure = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint05Pressure();}
    void        setSetPoint06Pressure           (int         value){if(mSetPoint06Pressure == value) return; mSetPoint06Pressure = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSetPoint06Pressure();}

    void        setValveID                      (QString     value){if(mValveID            == value) return; mValveID            = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedValveID           ();}
    void        setFirmwareVersion              (QString     value){if(mFirmwareVersion    == value) return; mFirmwareVersion    = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedFirmwareVersion   ();}
    void        setIsSealingType                (bool        value){if(mIsSealingType      == value) return; mIsSealingType      = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsSealingType     ();}
    void        setIsSupportPFO                 (bool        value){if(mIsSupportPFO       == value) return; mIsSupportPFO       = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsSupportPFO      ();}
    void        setIsSupportSPS                 (bool        value){if(mIsSupportSPS       == value) return; mIsSupportSPS       = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsSupportSPS      ();}
    void        setIsSupportAnalogOut           (bool        value){if(mIsSupportAnalogOut == value) return; mIsSupportAnalogOut = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedIsSupportAnalogOut();}
    void        setInterface                    (int         value){if(mInterface          == value) return; mInterface          = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedInterface         ();}
    void        setSensorVersion                (int         value){if(mSensorVersion      == value) return; mSensorVersion      = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedSensorVersion     ();}

    void        setScanRate                     (qint64      value){if(mScanRate           == value) return; mScanRate           = value; if(mLoadProgress != ValveEnumDef::LOAD_COMPLETED) return; emit signalEventChangedScanRate          ();}
    void        setIsRS232Test                  (bool        value){if(mIsRS232Test        == value) return; mIsRS232Test        = value;                                                           emit signalEventChangedIsRS232Test       ();}

signals:
    //**************************/
    /* property change signals */
    //**************************/
    void signalEventChangedIsRunning                    (bool    value);
    void signalEventChangedIsConnected                  (bool    value);
    void signalEventChangedLoadProgress                 (int     value);
    void signalEventChangedDFUStep                      (             );
    void signalEventChangedDFUPctCpu1Kernel             (             );
    void signalEventChangedDFUPctCpu2Kernel             (             );
    void signalEventChangedDFUPctCpu1App                (             );
    void signalEventChangedDFUPctCpu2App                (             );
    void signalEventChangedDFUPctCpu1Verify             (             );
    void signalEventChangedDFUPctCpu2Verify             (             );
    void signalEventChangedConnectionInfo               (QString value);

    void signalEventChangedCurrPosition                 (             );
    void signalEventChangedCurrPressure                 (             );
    void signalEventChangedTargetPosition               (             );
    void signalEventChangedTargetPressure               (             );
    void signalEventChangedValveSpeed                   (             );
    void signalEventChangedValveMaxSpeed                (             );
    void signalEventChangedPressureCtrlMode             (             );
    void signalEventChangedAccess                       (             );
    void signalEventChangedMode                         (             );
    void signalEventChangedControlMode                  (             );
    void signalEventChangedS01FullScale                 (             );
    void signalEventChangedS02FullScale                 (             );
    void signalEventChangedS01FullScalePrec             (             );
    void signalEventChangedS02FullScalePrec             (             );
    void signalEventChangedSensorOperation              (             );
    void signalEventChangedSensor01Offset               (             );
    void signalEventChangedSensor02Offset               (             );
    void signalEventChangedZeroEnable                   (             );
    void signalEventChangedPositionResolution           (             );
    void signalEventChangedPressureDpUnit               (             );
    void signalEventChangedPressureAxisMode             (             );
    void signalEventChangedPressureDecades              (             );
    void signalEventChangedIsSimulation                 (             );
    void signalEventChangedEnablePFO                    (             );
    void signalEventChangedIsTestMode                   (             );
    void signalEventChangedFieldBusError                (             );
    void signalEventChangedIsSaving                     (             );
    void signalEventChangedIsIDMissing                  (             );
    void signalEventChangedIsPFOMissing                 (             );
    void signalEventChangedFirmwareError                (             );
    void signalEventChangedUnknowInterface              (             );
    void signalEventChangedNoSensorSignal               (             );
    void signalEventChangedNoAnalogSignal               (             );
    void signalEventChangedNetworkFailure               (             );
    void signalEventChangedSlaveOffline                 (             );
    void signalEventChangedIsolationValve               (             );
    void signalEventChangedSensorError                  (             );
    void signalEventChangedSvcRequest                   (             );
    void signalEventChangedLearnNotPresent              (             );
    void signalEventChangedAirNotReady                  (             );
    void signalEventChangedPFONotReady                  (             );
    void signalEventChangedSetPoint01Position           (             );
    void signalEventChangedSetPoint02Position           (             );
    void signalEventChangedSetPoint03Position           (             );
    void signalEventChangedSetPoint04Position           (             );
    void signalEventChangedSetPoint05Position           (             );
    void signalEventChangedSetPoint06Position           (             );
    void signalEventChangedSetPoint01Pressure           (             );
    void signalEventChangedSetPoint02Pressure           (             );
    void signalEventChangedSetPoint03Pressure           (             );
    void signalEventChangedSetPoint04Pressure           (             );
    void signalEventChangedSetPoint05Pressure           (             );
    void signalEventChangedSetPoint06Pressure           (             );
    void signalEventChangedValveStatus                  (QString value);
    void signalEventChangedSensorSetting                (QString value);

    void signalEventChangedValveID                      (             );
    void signalEventChangedFirmwareVersion              (             );
    void signalEventChangedIsSealingType                (             );
    void signalEventChangedIsSupportPFO                 (             );
    void signalEventChangedIsSupportSPS                 (             );
    void signalEventChangedIsSupportAnalogOut           (             );
    void signalEventChangedInterface                    (             );
    void signalEventChangedSensorVersion                (             );

    void signalEventChangedScanRate                     (             );
    void signalEventChangedIsRS232Test                  (             );

    //**************************/
    /* worker result signals   */
    //**************************/
    void signalResultConnect                           (bool, QString                                       );
    void signalResultDFU                               (bool, QString                                       );
    void signalResultReadyDFU                          (bool                                                );
    void signalEventSearchedDevice                     (QStringList devList                                 );
    void signalEventReadedHWConfig                     (ValveResponseHWConfigDto                         dto);
    void signalEventReadedFirmwareVersion              (ValveResponseFirmwareVersionDto                  dto);
    void signalEventReadedValveID                      (ValveResponseValveIdDto                          dto);
    void signalEventReadedSensorConfig                 (ValveResponseSensorConfigDto                     dto);
    void signalEventReadedSensorOffset                 (ValveResponseSensorOffsetValuesDto               dto);
    void signalEventReadedSensorValue                  (ValveResponseSensorValueDto                      dto);
    void signalEventReadedSensorSelection              (ValveResponseSensorSelectionDto                  dto);
    void signalEventReadedSensorExSelection            (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExAnalActive              (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExSource                  (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExUnit                    (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExFullScale               (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExDigiValue               (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExZeroAdjEnable           (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExZeroAdjOffsetLimMin     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExZeroAdjOffsetLimMax     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExZeroAdjOffsetValue      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExScaleOffset             (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExScale                   (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExScaleZeroPoint          (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExFilterSec               (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExLogSensorLinearize      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExLogSensorVoltPerDecade  (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS01ExLogSensorVoltAtFullScale(ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExAnalActive              (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExSource                  (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExUnit                    (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExFullScale               (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExDigiValue               (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExZeroAdjEnable           (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExZeroAdjOffsetLimMin     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExZeroAdjOffsetLimMax     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExZeroAdjOffsetValue      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExScaleOffset             (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExScale                   (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExScaleZeroPoint          (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExFilterSec               (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExLogSensorLinearize      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExLogSensorVoltPerDecade  (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedS02ExLogSensorVoltAtFullScale(ValveResponseSimpleValueDto                      dto);
    void signalEventReadedCrossoverMod                 (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedCrossoverLow                 (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedCrossoverHigh                (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedCrossoverDela                (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedPressureCtrlConfig           (ValveResponsePressureCtrlConfigDto               dto);
    void signalEventReadedSelControlMode               (ValveResponseSelControlModeDto                   dto);
    void signalEventReadedAdapGainFactor               (ValveResponseGainFactorDto                       dto);
    void signalEventReadedAdapDeltaFactor              (ValveResponseDeltaFactorDto                      dto);
    void signalEventReadedAdapSensorDelay              (ValveResponseSensorDelayDto                      dto);
    void signalEventReadedAdapRampTime                 (ValveResponseRampTimeDto                         dto);
    void signalEventReadedAdapRampMode                 (ValveResponseRampModeDto                         dto);
    void signalEventReadedFixed1PGain                  (ValveResponsePGainDto                            dto);
    void signalEventReadedFixed1IGain                  (ValveResponseIGainDto                            dto);
    void signalEventReadedFixed1RampTime               (ValveResponseRampTimeDto                         dto);
    void signalEventReadedFixed1RampMode               (ValveResponseRampModeDto                         dto);
    void signalEventReadedFixed1CtrlDir                (ValveResponseCtrlDirDto                          dto);
    void signalEventReadedFixed2PGain                  (ValveResponsePGainDto                            dto);
    void signalEventReadedFixed2IGain                  (ValveResponseIGainDto                            dto);
    void signalEventReadedFixed2RampTime               (ValveResponseRampTimeDto                         dto);
    void signalEventReadedFixed2RampMode               (ValveResponseRampModeDto                         dto);
    void signalEventReadedFixed2CtrlDir                (ValveResponseCtrlDirDto                          dto);
    void signalEventReadedSoftDumpPGain                (ValveResponsePGainDto                            dto);
    void signalEventReadedSoftDumpRampTime             (ValveResponseRampTimeDto                         dto);
    void signalEventReadedSoftDumpRampMode             (ValveResponseRampModeDto                         dto);
    void signalEventReadedValveSetup                   (ValveResponseValveSetupDto                       dto);
    void signalEventReadedInterfaceConfigLogic         (ValveResponseInterfaceConfigLogicDto             dto);
    void signalEventReadedInterfaceConfigEthCATDi      (ValveResponseInterfaceConfigEthCATDiDto          dto);
    void signalEventReadedInterfaceConfigEthCATDo      (ValveResponseInterfaceConfigEthCATDoDto          dto);
    void signalEventReadedInterfaceCfgEthCATDevID      (ValveResponseInterfaceConfigEthCATDevIDDto       dto);
    void signalEventReadedInterfaceCfgEthCATPDODataType(ValveResponseInterfaceConfigEthCATPDODataTypeDto dto);
    void signalEventReadedInterfaceCfgEthCATPDORange   (ValveResponseInterfaceConfigEthCATPDORangeDto    dto);
    void signalEventReadedInterfaceCfgDNetMAC          (ValveResponseInterfaceConfigDNetMacDto           dto);
    void signalEventReadedInterfaceCfgDNetBaudrate     (ValveResponseInterfaceConfigDNetBaudrateDto      dto);
    void signalEventReadedInterfaceCfgDNetDataType     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetPosUnit      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetPosGain      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetPressureUnit (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetSensor01Gain (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetSensor02Gain (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetInputAss     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetOutputAss    (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetDevStatus    (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetExStatus     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgDNetDi           (ValveResponseInterfaceConfigDNetDiDto            dto);
    void signalEventReadedInterfaceCfgDNetDo           (ValveResponseInterfaceConfigDNetDoDto            dto);
    void signalEventReadedInterfaceCfgRS232            (ValveResponseInterfaceConfigRS232Dto             dto);
    void signalEventReadedInterfaceCfgRS485            (ValveResponseInterfaceConfigRS485Dto             dto);
    void signalEventReadedInterfaceCfgRS232Range       (ValveResponseInterfaceConfigRS232RangeDto        dto);
    void signalEventReadedInterfaceEthernetIP          (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceEthernetSubnet      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceEthernetGateway     (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceEthernetDHCP        (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceEthernetPort01      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceEthernetPort02      (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedInterfaceCfgFieldbusNodeAddr (ValveResponseInterfaceConfigFieldbusNodeAddrDto  dto);
    void signalEventReadedLearnStatus                  (ValveResponseLearnStatusDto                      dto);
    void signalEventReadedLearnPressureLimit           (ValveResponseLearnPressureLimitDto               dto);
    void signalEventReadedFatalErrStatus               (ValveResponseFatalErrStatusDto                   dto);
    void signalEventReadedWarnings                     (ValveResponseWarningsDto                         dto);
    void signalEventReadedSensor01Offset               (ValveResponseSensorOffsetDto                     dto);
    void signalEventReadedSensor02Offset               (ValveResponseSensorOffsetDto                     dto);
    void signalEventReadedControlCycles                (ValveResponseControlCyclesDto                    dto);
    void signalEventReadedIsolationCycles              (ValveResponseIsolationCyclesDto                  dto);
    void signalEventReadedSensorScale                  (ValveResponseSensorScaleDto                      dto);
    void signalEventReadedSetPoint01                   (ValveResponseSetPointDto                         dto);
    void signalEventReadedSetPoint02                   (ValveResponseSetPointDto                         dto);
    void signalEventReadedSetPoint03                   (ValveResponseSetPointDto                         dto);
    void signalEventReadedSetPoint04                   (ValveResponseSetPointDto                         dto);
    void signalEventReadedSetPoint05                   (ValveResponseSetPointDto                         dto);
    void signalEventReadedSetPoint06                   (ValveResponseSetPointDto                         dto);
    void signalEventReadedValveMaxSpeed                (ValveResponseSimpleValueDto                      dto);
    void signalEventReadedDisplayConfig                (ValveResponseDisplayConfigDto                    dto);
    void signalEventReadedValveParam                   (ValveResponseValveParamDto                       dto);
    void signalEventReadedTotalControlCycles           (ValveResponseTotalControlCyclesDto               dto);
    void signalEventReadedTotalIsolationCycles         (ValveResponseTotalIsolationCyclesDto             dto);
    void signalEventReadedPFOPerformedCycles           (ValveResponsePFOPerformedCyclesDto               dto);
    void signalEventReadedPFOCurrentVoltage            (ValveResponsePFOCurrentVoltageDto                dto);
    void signalEventReadedFatalErr01Pos                (ValveResponseFatalErrPosDto                      dto);
    void signalEventReadedFatalErr02Pos                (ValveResponseFatalErrPosDto                      dto);
    void signalEventReadedFatalErr03Pos                (ValveResponseFatalErrPosDto                      dto);
    void signalEventReadedLearnParam                   (ValveResponseLearnParamDto                       dto);
    void signalEventReadedValveStatus                  (ValveResponseValveStatusDto                      dto);
    void signalEventReadedInterfaceStatusLogic         (ValveResponseInterfaceStatusLogicDto             dto);
    void signalEventReadedInterfaceStatusEtherCAT      (ValveResponseInterfaceStatusEtherCATDto          dto);
    void signalEventReadedInterfaceDNetFirmwareID      (ValveResponseInterfaceDNetFirmwareIDDto          dto);
    void signalEventReadedInterfaceDNetSerialNum       (ValveResponseInterfaceDNetSerialNumDto           dto);
    void signalEventReadedInterfaceStatusDNet          (ValveResponseInterfaceStatusDNetDto              dto);
    void signalEventReadedInterfaceStatusRS232         (ValveResponseInterfaceStatusRS232Dto             dto);

    void signalEventWrittenTraceMode                      (ValveResponseDto                                 dto);
    void signalEventWrittenAccess                         (ValveResponseDto                                 dto);
    void signalEventWrittenEnablePFO                      (ValveResponseDto                                 dto);
    void signalEventWrittenControlCyclesReset             (ValveResponseDto                                 dto);
    void signalEventWrittenIsolationCyclesReset           (ValveResponseDto                                 dto);
    void signalEventWrittenReboot                         (ValveResponseDto                                 dto);
    void signalEventWrittenLearnParam                     (ValveResponseDto                                 dto);
    void signalEventWrittenValveParamStart                (ValveResponseDto                                 dto);
    void signalEventWrittenValveParam                     (ValveResponseDto                                 dto);
    void signalEventWrittenValveParamEnd                  (ValveResponseDto                                 dto);
    void signalEventWrittenFactoryReset                   (ValveResponseDto                                 dto);
    void signalEventWrittenValveParamReset                (ValveResponseDto                                 dto);
    void signalEventWrittenLearnReset                     (ValveResponseDto                                 dto);
    void signalEventWrittenSensorConfig                   (ValveResponseDto                                 dto);
    void signalEventWrittenSensorExSelection              (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExAnalActive                (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExSource                    (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExUnit                      (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExFullScale                 (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExDigiValue                 (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExZeroAdjEnable             (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExZeroAdjOffsetLimMin       (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExZeroAdjOffsetLimMax       (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExZeroAdjOffsetValue        (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExScaleOffset               (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExScale                     (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExScaleZeroPoint            (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExFilterSec                 (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExLogSensorLinearize        (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExLogSensorVoltPerDecade    (ValveResponseDto                                 dto);
    void signalEventWrittenS01ExLogSensorVoltAtFullScale  (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExAnalActive                (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExSource                    (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExUnit                      (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExFullScale                 (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExDigiValue                 (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExZeroAdjEnable             (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExZeroAdjOffsetLimMin       (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExZeroAdjOffsetLimMax       (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExZeroAdjOffsetValue        (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExScaleOffset               (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExScale                     (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExScaleZeroPoint            (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExFilterSec                 (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExLogSensorLinearize        (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExLogSensorVoltPerDecade    (ValveResponseDto                                 dto);
    void signalEventWrittenS02ExLogSensorVoltAtFullScale  (ValveResponseDto                                 dto);
    void signalEventWrittenCrossoverMod                   (ValveResponseDto                                 dto);
    void signalEventWrittenCrossoverLow                   (ValveResponseDto                                 dto);
    void signalEventWrittenCrossoverHigh                  (ValveResponseDto                                 dto);
    void signalEventWrittenCrossoverDela                  (ValveResponseDto                                 dto);
    void signalEventWrittenPressureCtrlConfig             (ValveResponseDto                                 dto);
    void signalEventWrittenSelContrlMode                  (ValveResponseDto                                 dto);
    void signalEventWrittenAdapGainFactor                 (ValveResponseDto                                 dto);
    void signalEventWrittenAdapDeltaFactor                (ValveResponseDto                                 dto);
    void signalEventWrittenAdapSensorDelay                (ValveResponseDto                                 dto);
    void signalEventWrittenAdapRampTime                   (ValveResponseDto                                 dto);
    void signalEventWrittenAdapRampMode                   (ValveResponseDto                                 dto);
    void signalEventWrittenFixed1PGain                    (ValveResponseDto                                 dto);
    void signalEventWrittenFixed1IGain                    (ValveResponseDto                                 dto);
    void signalEventWrittenFixed1RampTime                 (ValveResponseDto                                 dto);
    void signalEventWrittenFixed1RampMode                 (ValveResponseDto                                 dto);
    void signalEventWrittenFixed1CtrlDir                  (ValveResponseDto                                 dto);
    void signalEventWrittenFixed2PGain                    (ValveResponseDto                                 dto);
    void signalEventWrittenFixed2IGain                    (ValveResponseDto                                 dto);
    void signalEventWrittenFixed2RampTime                 (ValveResponseDto                                 dto);
    void signalEventWrittenFixed2RampMode                 (ValveResponseDto                                 dto);
    void signalEventWrittenFixed2CtrlDir                  (ValveResponseDto                                 dto);
    void signalEventWrittenValveSetup                     (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigLogic           (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigEthCATDi        (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigEthCATDo        (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceCfgEthCATDevID        (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceCfgEthCATPDODataType  (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceCfgEthCATPDORange     (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetDi          (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetDo          (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetDataType    (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetMacAddr     (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetBaudrate    (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetPosUnit     (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetPosGain     (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetPressureUnit(ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetSensor01Gain(ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetSensor02Gain(ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetInputAss    (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceConfigDNetOutputAss   (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceCfgRS232              (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceCfgRS485              (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceCfgRS232Range         (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceEthernetIP            (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceEthernetSubnet        (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceEthernetGateway       (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceEthernetDHCP          (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceEthernetPort01        (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceEthernetPort02        (ValveResponseDto                                 dto);
    void signalEventWrittenInterfaceCfgFieldbusNodeAddr   (ValveResponseDto                                 dto);
    void signalEventWrittenSensorScale                    (ValveResponseDto                                 dto);
    void signalEventWrittenSetPoint01                     (ValveResponseDto                                 dto);
    void signalEventWrittenSetPoint02                     (ValveResponseDto                                 dto);
    void signalEventWrittenSetPoint03                     (ValveResponseDto                                 dto);
    void signalEventWrittenSetPoint04                     (ValveResponseDto                                 dto);
    void signalEventWrittenSetPoint05                     (ValveResponseDto                                 dto);
    void signalEventWrittenSetPoint06                     (ValveResponseDto                                 dto);
    void signalEventWrittenDisplayConfig                  (ValveResponseDto                                 dto);
    void signalEventWrittenTargetPosition                 (ValveResponseDto                                 dto);
    void signalEventWrittenTargetPressure                 (ValveResponseDto                                 dto);
    void signalEventWrittenValveSpeed                     (ValveResponseDto                                 dto);
    void signalEventWrittenAdcGainZero                    (ValveResponseDto                                 dto);
    void signalEventWrittenSensorZero                     (ValveResponseDto                                 dto);
    void signalEventWrittenLearnRun                       (ValveResponseDto                                 dto);
    void signalEventWrittenSimulation                     (ValveResponseDto                                 dto);
    void signalEventWrittenHoldPosition                   (ValveResponseDto                                 dto);
    void signalEventWrittenOpenPosition                   (ValveResponseDto                                 dto);
    void signalEventWrittenClosePosition                  (ValveResponseDto                                 dto);
    void signalEventWrittenSoftOpen                       (ValveResponseDto                                 dto);
    void signalEventWrittenSoftClose                      (ValveResponseDto                                 dto);
    void signalEventWrittenTestMode                       (ValveResponseDto                                 dto);
    void signalEventWrittenEncoderZero                    (ValveResponseDto                                 dto);
    void signalEventWrittenCustomRequest                  (ValveResponseDto                                 dto);
//    void signalEventWrittenFatalErrReset          (ValveResponseDto                              dto);
    void signalEventReceivedTraceData                     (QString data);
    //****************************/
    /* command signals to worker */
    //****************************/
    void signalCommandSetMonitoringCycle          (qint64 monitoringCycle, ValveRequestDto monitoringDto);
    void signalCommandSearch                      (                             );
    void signalCommandSearchStop                  (                             );
    void signalCommandFirmwareUpdate              (QString comPort, int baudRate, int dataBit, int stopBit, int parity, QString cpu1KernelFile, QString cpu2KernelFile, QString cpu1AppFile, QString cpu2AppFile);
    void signalCommandReadyFirmwareUpdate         (                             );
    void signalCommandConnect                     (int type, QString devAddr    );
    void signalCommandReConnect                   (                             );
    void signalCommandRequest                     (ValveRequestDto         value);
    void signalCommandSetTraceMode                (bool value, ValveRequestDto dto);

public :
    static ValveSProvider * getInstance()
    {
        static ValveSProvider *mpSelf = nullptr;

        if(mpSelf == nullptr)
        {
            mpSelf = new ValveSProvider();
        }

        return mpSelf;
    }

    explicit ValveSProvider(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[ValveSProvider]Create";
    }
    ~ValveSProvider()
    {
        qDebug() << "[ValveSProvider]Destruction";
        stop();
    }

    void start()
    {
        qDebug() << "[ValveSProvider][start]";
        mpASyncWorkerThread = new QThread;
        mpASyncWorker       = new ValveASyncWorker;
        mpASyncWorker->moveToThread(mpASyncWorkerThread);

        connect(mpASyncWorkerThread, &QThread::finished, mpASyncWorker, &QObject::deleteLater);
        connect(mpASyncWorkerThread, SIGNAL(started()), mpASyncWorker, SLOT(onStart()));
        connect(mpASyncWorkerThread, SIGNAL(started()), this, SLOT(onStartWorker()));

        mpASyncWorkerThread->start();

        connect(this         , SIGNAL(signalCommandSetMonitoringCycle (qint64, ValveRequestDto)), mpASyncWorker, SLOT(onCommandSetMonitoringCycle (qint64,ValveRequestDto)));
        connect(this         , SIGNAL(signalCommandSearch             (                       )), mpASyncWorker, SLOT(onCommandSearch             (                      )));
        connect(this         , SIGNAL(signalCommandSearchStop         (                       )), mpASyncWorker, SLOT(onCommandSearchStop         (                      )));
        connect(this         , SIGNAL(signalCommandConnect            (int , QString          )), mpASyncWorker, SLOT(onCommandConnect            (int , QString         )));
        connect(this         , SIGNAL(signalCommandReConnect          (                       )), mpASyncWorker, SLOT(onCommandReConnect          (                      )));
        connect(this         , SIGNAL(signalCommandReadyFirmwareUpdate(                       )), mpASyncWorker, SLOT(onCommandReadyFirmwareUpdate(                      )));
        connect(this         , SIGNAL(signalCommandRequest            (ValveRequestDto        )), mpASyncWorker, SLOT(onCommandRequest            (ValveRequestDto       )));
        connect(this         , SIGNAL(signalCommandSetTraceMode       (bool, ValveRequestDto  )), mpASyncWorker, SLOT(onCommandSetTraceMode       (bool, ValveRequestDto )));

        connect(mpASyncWorker, SIGNAL(signalEventChangedIsConnecting  (bool, bool             )), this         , SLOT(onChangedIsConnecting       (bool, bool            )));
        connect(mpASyncWorker, SIGNAL(signalResultConnect             (bool, QString          )), this         , SLOT(onResultConnect             (bool, QString         )));
        connect(mpASyncWorker, SIGNAL(signalResultReadyFirmwareUpdate (bool                   )), this         , SLOT(onResultReadyFirmwareUpdate (bool                  )));
        connect(mpASyncWorker, SIGNAL(signalEventSearchedDevice       (QStringList            )), this         , SLOT(onSearchedDevice            (QStringList           )));
        connect(mpASyncWorker, SIGNAL(signalEventResponseData         (ValveResponseDto       )), this         , SLOT(onResponseData              (ValveResponseDto      )));
        connect(mpASyncWorker, SIGNAL(signalEventTrace                (QString                )), this         , SLOT(onTraceData                 (QString               )));


        mpDFUWorkerThread = new QThread;
        mpDFUWorker       = new ValveFirmwareUpgradeWorker;
        mpDFUWorker->moveToThread(mpDFUWorkerThread);

        connect(mpDFUWorkerThread, &QThread::finished, mpDFUWorker, &QObject::deleteLater);

        mpDFUWorkerThread->start();

        connect(this         , SIGNAL(signalCommandFirmwareUpdate        (QString, int, int, int, int, QString, QString, QString, QString)), mpDFUWorker, SLOT(onCommandUpgrade          (QString, int, int, int, int, QString, QString, QString, QString)));
        connect(mpDFUWorker  , SIGNAL(signalEventChangedStep             (int                                                            )), this       , SLOT(onChangedDFUStep          (int                                                            )));
        connect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu1Kernel(int                                                            )), this       , SLOT(onChangedDFUPctCpu1Kernel(int                                                            )));
        connect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu2Kernel(int                                                            )), this       , SLOT(onChangedDFUPctCpu2Kernel(int                                                            )));
        connect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu1App   (int                                                            )), this       , SLOT(onChangedDFUPctCpu1App   (int                                                            )));
        connect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu2App   (int                                                            )), this       , SLOT(onChangedDFUPctCpu2App   (int                                                            )));
        connect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu1Verify(int                                                            )), this       , SLOT(onChangedDFUPctCpu1Verify(int                                                            )));
        connect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu2Verify(int                                                            )), this       , SLOT(onChangedDFUPctCpu2Verify(int                                                            )));
        connect(mpDFUWorker  , SIGNAL(signalEventResult                  (bool, QString                                                  )), this       , SLOT(onResultDFU              (bool, QString                                                  )));
    }

    void stop()
    {
        qDebug() << "[ValveSProvider][stop]";

        mIsRunning = false;

        if(mpASyncWorker != nullptr)
        {
            disconnect(this         , SIGNAL(signalCommandSetMonitoringCycle (qint64, ValveRequestDto)), mpASyncWorker, SLOT(onCommandSetMonitoringCycle(qint64, ValveRequestDto)));
            disconnect(this         , SIGNAL(signalCommandSearch             (                       )), mpASyncWorker, SLOT(onCommandSearch            (                       )));
            disconnect(this         , SIGNAL(signalCommandSearchStop         (                       )), mpASyncWorker, SLOT(onCommandSearchStop        (                       )));
            disconnect(this         , SIGNAL(signalCommandConnect            (int , QString          )), mpASyncWorker, SLOT(onCommandConnect           (int , QString          )));
            disconnect(this         , SIGNAL(signalCommandReConnect          (                       )), mpASyncWorker, SLOT(onCommandReConnect         (                       )));
            disconnect(this         , SIGNAL(signalCommandReadyFirmwareUpdate(                       )), mpASyncWorker, SLOT(onCommandReadyFirmwareUpdate(                      )));
            disconnect(this         , SIGNAL(signalCommandRequest            (ValveRequestDto        )), mpASyncWorker, SLOT(onCommandRequest           (ValveRequestDto        )));
            disconnect(this         , SIGNAL(signalCommandSetTraceMode       (bool, ValveRequestDto  )), mpASyncWorker, SLOT(onCommandSetTraceMode       (bool, ValveRequestDto )));
            disconnect(mpASyncWorker, SIGNAL(signalEventChangedIsConnecting  (bool, bool             )), this         , SLOT(onChangedIsConnecting      (bool, bool             )));
            disconnect(mpASyncWorker, SIGNAL(signalResultConnect             (bool, QString          )), this         , SLOT(onResultConnect            (bool, QString          )));
            disconnect(mpASyncWorker, SIGNAL(signalResultReadyFirmwareUpdate (bool                   )), this         , SLOT(onResultReadyFirmwareUpdate (bool                  )));
            disconnect(mpASyncWorker, SIGNAL(signalEventSearchedDevice       (QStringList            )), this         , SLOT(onSearchedDevice           (QStringList            )));
            disconnect(mpASyncWorker, SIGNAL(signalEventResponseData         (ValveResponseDto       )), this         , SLOT(onResponseData             (ValveResponseDto       )));
            disconnect(mpASyncWorker, SIGNAL(signalEventTrace                (QString                )), this         , SLOT(onTraceData                 (QString               )));

            mpASyncWorker= nullptr;
        }

        if(mpASyncWorkerThread != nullptr)
        {
            if(mpASyncWorkerThread->isRunning())
            {
                mpASyncWorkerThread->quit();
                mpASyncWorkerThread->wait();
            }

            mpASyncWorkerThread->deleteLater();

            mpASyncWorkerThread = nullptr;
        }

        if(mpDFUWorker != nullptr)
        {
            disconnect(this         , SIGNAL(signalCommandFirmwareUpdate        (QString, int, int, int, int, QString, QString, QString, QString)), mpDFUWorker, SLOT(onCommandUpgrade         (QString, int, int, int, int, QString, QString, QString, QString)));
            disconnect(mpDFUWorker  , SIGNAL(signalEventChangedStep             (int                                                            )), this       , SLOT(onChangedDFUStep         (int                                                            )));
            disconnect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu1Kernel(int                                                            )), this       , SLOT(onChangedDFUPctCpu1Kernel(int                                                            )));
            disconnect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu2Kernel(int                                                            )), this       , SLOT(onChangedDFUPctCpu2Kernel(int                                                            )));
            disconnect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu1App   (int                                                            )), this       , SLOT(onChangedDFUPctCpu1App   (int                                                            )));
            disconnect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu2App   (int                                                            )), this       , SLOT(onChangedDFUPctCpu2App   (int                                                            )));
            disconnect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu1Verify(int                                                            )), this       , SLOT(onChangedDFUPctCpu1Verify(int                                                            )));
            disconnect(mpDFUWorker  , SIGNAL(signalEventChangedPercentCpu2Verify(int                                                            )), this       , SLOT(onChangedDFUPctCpu2Verify(int                                                            )));
            disconnect(mpDFUWorker  , SIGNAL(signalEventResult                  (bool, QString                                                  )), this       , SLOT(onResultDFU              (bool, QString                                                  )));

            mpDFUWorker= nullptr;
        }

        if(mpDFUWorkerThread != nullptr)
        {
            if(mpDFUWorkerThread->isRunning())
            {
                mpDFUWorkerThread->quit();
                mpDFUWorkerThread->wait();
            }

            mpDFUWorkerThread->deleteLater();

            mpDFUWorkerThread = nullptr;
        }

        setIsRunning(false);
    }

    void setMonitoringCycle(qint64 monitoringCycle)
    {
        qDebug() << "[ValveSProvider][setMonitoringCycle]" << monitoringCycle << "ms";
        emit signalCommandSetMonitoringCycle(monitoringCycle, ValveRequestDto(this, staticProcReadValveStatus, nullptr, REQ_READ_STATUS, REQ_READ_STATUS, RES_STATUS_DATA_LEN, 0, this));
    }

    void search()
    {
        qDebug() << "[ValveSProvider][search]";
        emit signalCommandSearch();
    }

    void searchStop()
    {
        qDebug() << "[ValveSProvider][searchStop]";
        emit signalCommandSearchStop();
    }

    void firmwareUpdate(QString comPort, int baudRate, int dataBit, int stopBit, int parity, QString cpu1KernelFile, QString cpu2KernelFile, QString cpu1AppFile, QString cpu2AppFile)
    {
        qDebug() << "[" <<Q_FUNC_INFO << "]";
        emit signalCommandFirmwareUpdate(comPort, baudRate, dataBit, stopBit, parity, cpu1KernelFile, cpu2KernelFile, cpu1AppFile, cpu2AppFile);
    }

    void readyFirmwareUpdate()
    {
        qDebug() << "[" <<Q_FUNC_INFO << "]";
        emit signalCommandReadyFirmwareUpdate();
    }

    void connectDevice(ValveConnEnumDef::eConnectType connType ,QString devAddr)
    {
        qDebug() << "[ValveSProvider][connectDevice]";
        setMode(ValveEnumDef::MODE_INIT);
        setControlMode(ValveEnumDef::MODE_INIT);
        setTargetPosition(0);
        setCurrPosition(0);
        setTargetPressure(0); // khko_edit
        setCurrPressure(0);
        setConnectionInfo("");
        setLoadProgress(ValveEnumDef::LOAD_NONE);
        emit signalCommandConnect((int)connType, devAddr);
    }

    void reConnectDevice()
    {
        qDebug() << "[ValveSProvider][reConnectDevice]";
        setMode(ValveEnumDef::MODE_INIT);
        setControlMode(ValveEnumDef::MODE_INIT);
        setConnectionInfo("");
        setLoadProgress(ValveEnumDef::LOAD_NONE);
        emit signalCommandReConnect();
    }

    void reLoad()
    {
        qDebug() << "[ValveSProvider][reLoad]";
        setLoadProgress(ValveEnumDef::LOAD_READY);

        readValvedID(this);
    }

    void readHWConfig(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadHWConfig, nullptr, REQ_READ_HW_CONFIG, REQ_READ_HW_CONFIG, RES_HW_CONFIG_DATA_LEN, retryCnt, userData));
    }

    void readFirmwareVersion(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFirmwareVersion, nullptr, REQ_READ_FIRMWARE_VERSION, REQ_READ_FIRMWARE_VERSION, RES_FIRMWARE_VERSION_DATA_LEN, retryCnt, userData));
    }

    void readValvedID(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadValveID, nullptr, REQ_READ_ID, REQ_READ_ID, RES_ID_DATA_LEN, retryCnt, userData));
    }

    void readSensorConfig(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensorConfig, nullptr, REQ_READ_SENSOR_CONFIG, REQ_READ_SENSOR_CONFIG, RES_SENSOR_CONFIG_DATA_LEN, retryCnt, userData));
    }

    void readSensorOffset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensorOffset, nullptr, REQ_READ_SENSOR_OFFSET, REQ_READ_SENSOR_OFFSET, RES_SENSOR_OFFSET_DATA_LEN, retryCnt, userData));
    }

    void readSensorValue(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensorValue, nullptr, REQ_READ_SENSOR_VALUE, REQ_READ_SENSOR_VALUE, RES_SENSOR_VALUE_DATA_LEN, retryCnt, userData));
    }

    void readSensorSelection(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensorSelection, nullptr, REQ_READ_SENSOR_SELECTION, REQ_READ_SENSOR_SELECTION, RES_SENSOR_SELECTION_DATA_LEN, retryCnt, userData));
    }


    //////////////////////////////////
    void readSensorExSelection(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensorExSelection, nullptr, REQ_READ_SENSEX_SEL, REQ_READ_SENSEX_SEL, RES_SENSEX_SEL_DATA_LEN, retryCnt, userData));
    }
    void readS01ExAnalActive(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExAnalActive, nullptr, REQ_READ_SENSEX_S01_ANAL_ACTIVE, REQ_READ_SENSEX_S01_ANAL_ACTIVE, RES_SENSEX_S01_ANAL_ACTIVE_DATA_LEN, retryCnt, userData));
    }
    void readS01ExSource(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExSource, nullptr, REQ_READ_SENSEX_S01_SRC, REQ_READ_SENSEX_S01_SRC, RES_SENSEX_S01_SRC_DATA_LEN, retryCnt, userData));
    }
    void readS01ExUnit(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExUnit, nullptr, REQ_READ_SENSEX_S01_UNIT, REQ_READ_SENSEX_S01_UNIT, RES_SENSEX_S01_UNIT_DATA_LEN, retryCnt, userData));
    }
    void readS01ExFullScale(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExFullScale, nullptr, REQ_READ_SENSEX_S01_FULLSCALE, REQ_READ_SENSEX_S01_FULLSCALE, RES_SENSEX_S01_FULLSCALE_DATA_LEN, retryCnt, userData));
    }
    void readS01ExDigiValue(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExDigiValue, nullptr, REQ_READ_SENSEX_S01_DIGI, REQ_READ_SENSEX_S01_DIGI, RES_SENSEX_S01_DIGI_DATA_LEN, retryCnt, userData));
    }
    void readS01ExZeroAdjEnable(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExZeroAdjEnable, nullptr, REQ_READ_SENSEX_S01_ZERO_ENABLE, REQ_READ_SENSEX_S01_ZERO_ENABLE, RES_SENSEX_S01_ZERO_ENABLE_DATA_LEN, retryCnt, userData));
    }
    void readS01ExZeroAdjOffsetLimMin(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExZeroAdjOffsetLimMin, nullptr, REQ_READ_SENSEX_S01_ZERO_MIN, REQ_READ_SENSEX_S01_ZERO_MIN, RES_SENSEX_S01_ZERO_MIN_DATA_LEN, retryCnt, userData));
    }
    void readS01ExZeroAdjOffsetLimMax(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExZeroAdjOffsetLimMax, nullptr, REQ_READ_SENSEX_S01_ZERO_MAX, REQ_READ_SENSEX_S01_ZERO_MAX, RES_SENSEX_S01_ZERO_MAX_DATA_LEN, retryCnt, userData));
    }
    void readS01ExZeroAdjOffsetValue(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExZeroAdjOffsetValue, nullptr, REQ_READ_SENSEX_S01_ZERO_VALUE, REQ_READ_SENSEX_S01_ZERO_VALUE, RES_SENSEX_S01_ZERO_VALUE_DATA_LEN, retryCnt, userData));
    }
    void readS01ExScaleOffset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExScaleOffset, nullptr, REQ_READ_SENSEX_S01_SCALE_OFFSET, REQ_READ_SENSEX_S01_SCALE_OFFSET, RES_SENSEX_S01_SCALE_OFFSET_DATA_LEN, retryCnt, userData));
    }
    void readS01ExScale(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExScale, nullptr, REQ_READ_SENSEX_S01_SCALE, REQ_READ_SENSEX_S01_SCALE, RES_SENSEX_S01_SCALE_DATA_LEN, retryCnt, userData));
    }
    void readS01ExScaleZeroPoint(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExScaleZeroPoint, nullptr, REQ_READ_SENSEX_S01_SCALE_Z_POINT, REQ_READ_SENSEX_S01_SCALE_Z_POINT, RES_SENSEX_S01_SCALE_Z_POINT_DATA_LEN, retryCnt, userData));
    }

    void readS01ExFilterSec(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExFilterSec, nullptr, REQ_READ_SENSEX_S01_FILTER_SEC, REQ_READ_SENSEX_S01_FILTER_SEC, RES_SENSEX_S01_FILTER_SEC_DATA_LEN, retryCnt, userData));
    }

    void readS01ExLogSensorLinearize(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExLogSensorLinearize, nullptr, REQ_READ_SENSEX_S01_LOG_SENS_LINEARIZE, REQ_READ_SENSEX_S01_LOG_SENS_LINEARIZE, RES_SENSEX_S01_LOG_SENS_LINEARIZE_DATA_LEN, retryCnt, userData));
    }

    void readS01ExLogSensorVoltPerDecade(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExLogSensorVoltPerDecade, nullptr, REQ_READ_SENSEX_S01_LOG_SENS_VOLT_DECADE, REQ_READ_SENSEX_S01_LOG_SENS_VOLT_DECADE, RES_SENSEX_S01_LOG_SENS_VOLT_DECADE_DATA_LEN, retryCnt, userData));
    }

    void readS01ExLogSensorVoltAtFullScale(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS01ExLogSensorVoltAtFullScale, nullptr, REQ_READ_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE, REQ_READ_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE, RES_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE_DATA_LEN, retryCnt, userData));
    }

    void readS02ExAnalActive(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExAnalActive, nullptr, REQ_READ_SENSEX_S02_ANAL_ACTIVE, REQ_READ_SENSEX_S02_ANAL_ACTIVE, RES_SENSEX_S02_ANAL_ACTIVE_DATA_LEN, retryCnt, userData));
    }
    void readS02ExSource(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExSource, nullptr, REQ_READ_SENSEX_S02_SRC, REQ_READ_SENSEX_S02_SRC, RES_SENSEX_S02_SRC_DATA_LEN, retryCnt, userData));
    }
    void readS02ExUnit(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExUnit, nullptr, REQ_READ_SENSEX_S02_UNIT, REQ_READ_SENSEX_S02_UNIT, RES_SENSEX_S02_UNIT_DATA_LEN, retryCnt, userData));
    }
    void readS02ExFullScale(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExFullScale, nullptr, REQ_READ_SENSEX_S02_FULLSCALE, REQ_READ_SENSEX_S02_FULLSCALE, RES_SENSEX_S02_FULLSCALE_DATA_LEN, retryCnt, userData));
    }
    void readS02ExDigiValue(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExDigiValue, nullptr, REQ_READ_SENSEX_S02_DIGI, REQ_READ_SENSEX_S02_DIGI, RES_SENSEX_S02_DIGI_DATA_LEN, retryCnt, userData));
    }
    void readS02ExZeroAdjEnable(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExZeroAdjEnable, nullptr, REQ_READ_SENSEX_S02_ZERO_ENABLE, REQ_READ_SENSEX_S02_ZERO_ENABLE, RES_SENSEX_S02_ZERO_ENABLE_DATA_LEN, retryCnt, userData));
    }
    void readS02ExZeroAdjOffsetLimMin(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExZeroAdjOffsetLimMin, nullptr, REQ_READ_SENSEX_S02_ZERO_MIN, REQ_READ_SENSEX_S02_ZERO_MIN, RES_SENSEX_S02_ZERO_MIN_DATA_LEN, retryCnt, userData));
    }
    void readS02ExZeroAdjOffsetLimMax(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExZeroAdjOffsetLimMax, nullptr, REQ_READ_SENSEX_S02_ZERO_MAX, REQ_READ_SENSEX_S02_ZERO_MAX, RES_SENSEX_S02_ZERO_MAX_DATA_LEN, retryCnt, userData));
    }
    void readS02ExZeroAdjOffsetValue(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExZeroAdjOffsetValue, nullptr, REQ_READ_SENSEX_S02_ZERO_VALUE, REQ_READ_SENSEX_S02_ZERO_VALUE, RES_SENSEX_S02_ZERO_VALUE_DATA_LEN, retryCnt, userData));
    }
    void readS02ExScaleOffset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExScaleOffset, nullptr, REQ_READ_SENSEX_S02_SCALE_OFFSET, REQ_READ_SENSEX_S02_SCALE_OFFSET, RES_SENSEX_S02_SCALE_OFFSET_DATA_LEN, retryCnt, userData));
    }
    void readS02ExScale(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExScale, nullptr, REQ_READ_SENSEX_S02_SCALE, REQ_READ_SENSEX_S02_SCALE, RES_SENSEX_S02_SCALE_DATA_LEN, retryCnt, userData));
    }
    void readS02ExScaleZeroPoint(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExScaleZeroPoint, nullptr, REQ_READ_SENSEX_S02_SCALE_Z_POINT, REQ_READ_SENSEX_S02_SCALE_Z_POINT, RES_SENSEX_S02_SCALE_Z_POINT_DATA_LEN, retryCnt, userData));
    }

    void readS02ExFilterSec(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExFilterSec, nullptr, REQ_READ_SENSEX_S02_FILTER_SEC, REQ_READ_SENSEX_S02_FILTER_SEC, RES_SENSEX_S02_FILTER_SEC_DATA_LEN, retryCnt, userData));
    }

    void readS02ExLogSensorLinearize(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExLogSensorLinearize, nullptr, REQ_READ_SENSEX_S02_LOG_SENS_LINEARIZE, REQ_READ_SENSEX_S02_LOG_SENS_LINEARIZE, RES_SENSEX_S02_LOG_SENS_LINEARIZE_DATA_LEN, retryCnt, userData));
    }

    void readS02ExLogSensorVoltPerDecade(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExLogSensorVoltPerDecade, nullptr, REQ_READ_SENSEX_S02_LOG_SENS_VOLT_DECADE, REQ_READ_SENSEX_S02_LOG_SENS_VOLT_DECADE, RES_SENSEX_S02_LOG_SENS_VOLT_DECADE_DATA_LEN, retryCnt, userData));
    }

    void readS02ExLogSensorVoltAtFullScale(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadS02ExLogSensorVoltAtFullScale, nullptr, REQ_READ_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE, REQ_READ_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE, RES_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE_DATA_LEN, retryCnt, userData));
    }

    void readCrossoverMod(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadCrossoverMod, nullptr, REQ_READ_SENSEX_CROSSOVER_MOD, REQ_READ_SENSEX_CROSSOVER_MOD, RES_SENSEX_CROSSOVER_MOD_DATA_LEN, retryCnt, userData));
    }

    void readCrossoverLow(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadCrossoverLow, nullptr, REQ_READ_SENSEX_CROSSOVER_LOW, REQ_READ_SENSEX_CROSSOVER_LOW, RES_SENSEX_CROSSOVER_LOW_DATA_LEN, retryCnt, userData));
    }

    void readCrossoverHigh(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadCrossoverHigh, nullptr, REQ_READ_SENSEX_CROSSOVER_HIGH, REQ_READ_SENSEX_CROSSOVER_HIGH, RES_SENSEX_CROSSOVER_HIGH_DATA_LEN, retryCnt, userData));
    }

    void readCrossoverDela(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadCrossoverDela, nullptr, REQ_READ_SENSEX_CROSSOVER_DELA, REQ_READ_SENSEX_CROSSOVER_DELA, RES_SENSEX_CROSSOVER_DELA_DATA_LEN, retryCnt, userData));
    }

    void readPressureCtrlConfig(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadPressureCtrlConfig, nullptr, REQ_READ_PRESSURE_CTRL_CONFIG, REQ_READ_PRESSURE_CTRL_CONFIG, RES_PRESSURE_CTRL_CONFIG_DATA_LEN, retryCnt, userData));
    }

    void readSelectControlMode(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSelectControlMode, nullptr, REQ_READ_SELECT_CTRL_MODE, REQ_READ_SELECT_CTRL_MODE, RES_SELECT_CTRL_MODE_DATA_LEN, retryCnt, userData));
    }
    void readAdaptiveControlGainFactor(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadAdaptiveControlGainFactor, nullptr, REQ_READ_ADAP_CTRL_GAIN_FAC, REQ_READ_ADAP_CTRL_GAIN_FAC, RES_ADAP_CTRL_GAIN_FAC_DATA_LEN, retryCnt, userData));
    }
    void readAdaptiveControlDeltaFactor(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadAdaptiveControlDeltaFactor, nullptr, REQ_READ_ADAP_CTRL_DELTA_FAC, REQ_READ_ADAP_CTRL_DELTA_FAC, RES_ADAP_CTRL_DELTA_FAC_DATA_LEN, retryCnt, userData));
    }
    void readAdaptiveControlSensorDelay(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadAdaptiveControlSensorDelay, nullptr, REQ_READ_ADAP_CTRL_SENSOR_DELAY, REQ_READ_ADAP_CTRL_SENSOR_DELAY, RES_ADAP_CTRL_SENSOR_DELAY_DATA_LEN, retryCnt, userData));
    }
    void readAdaptiveControlRampTime(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadAdaptiveControlRampTime, nullptr, REQ_READ_ADAP_CTRL_RAMP_TIME, REQ_READ_ADAP_CTRL_RAMP_TIME, RES_ADAP_CTRL_RAMP_TIME_DATA_LEN, retryCnt, userData));
    }
    void readAdaptiveControlRampMode(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadAdaptiveControlRampMode, nullptr, REQ_READ_ADAP_CTRL_RAMP_MODE, REQ_READ_ADAP_CTRL_RAMP_MODE, RES_ADAP_CTRL_RAMP_MODE_DATA_LEN, retryCnt, userData));
    }
    void readFixed1ControlPGain(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed1ControlPGain, nullptr, REQ_READ_FIXED1_CTRL_P_GAIN, REQ_READ_FIXED1_CTRL_P_GAIN, RES_FIXED1_CTRL_P_GAIN_DATA_LEN, retryCnt, userData));
    }
    void readFixed1ControlIGain(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed1ControlIGain, nullptr, REQ_READ_FIXED1_CTRL_I_GAIN, REQ_READ_FIXED1_CTRL_I_GAIN, RES_FIXED1_CTRL_I_GAIN_DATA_LEN, retryCnt, userData));
    }
    void readFixed1ControlRampTime(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed1ControlRampTime, nullptr, REQ_READ_FIXED1_CTRL_RAMP_TIME, REQ_READ_FIXED1_CTRL_RAMP_TIME, RES_FIXED1_CTRL_RAMP_TIME_DATA_LEN, retryCnt, userData));
    }
    void readFixed1ControlRampMode(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed1ControlRampMode, nullptr, REQ_READ_FIXED1_CTRL_RAMP_MODE, REQ_READ_FIXED1_CTRL_RAMP_MODE, RES_FIXED1_CTRL_RAMP_MODE_DATA_LEN, retryCnt, userData));
    }
    void readFixed1ControlDirection(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed1ControlDirection, nullptr, REQ_READ_FIXED1_CTRL_DIR, REQ_READ_FIXED1_CTRL_DIR, RES_FIXED1_CTRL_DIR_DATA_LEN, retryCnt, userData));
    }
    void readFixed2ControlPGain(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed2ControlPGain, nullptr, REQ_READ_FIXED2_CTRL_P_GAIN, REQ_READ_FIXED2_CTRL_P_GAIN, RES_FIXED2_CTRL_P_GAIN_DATA_LEN, retryCnt, userData));
    }
    void readFixed2ControlIGain(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed2ControlIGain, nullptr, REQ_READ_FIXED2_CTRL_I_GAIN, REQ_READ_FIXED2_CTRL_I_GAIN, RES_FIXED2_CTRL_I_GAIN_DATA_LEN, retryCnt, userData));
    }
    void readFixed2ControlRampTime(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed2ControlRampTime, nullptr, REQ_READ_FIXED2_CTRL_RAMP_TIME, REQ_READ_FIXED2_CTRL_RAMP_TIME, RES_FIXED2_CTRL_RAMP_TIME_DATA_LEN, retryCnt, userData));
    }
    void readFixed2ControlRampMode(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed2ControlRampMode, nullptr, REQ_READ_FIXED2_CTRL_RAMP_MODE, REQ_READ_FIXED2_CTRL_RAMP_MODE, RES_FIXED2_CTRL_RAMP_MODE_DATA_LEN, retryCnt, userData));
    }
    void readFixed2ControlDirection(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFixed2ControlDirection, nullptr, REQ_READ_FIXED2_CTRL_DIR, REQ_READ_FIXED2_CTRL_DIR, RES_FIXED2_CTRL_DIR_DATA_LEN, retryCnt, userData));
    }

    void readValveSetup(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadValveSetup, nullptr, REQ_READ_VALVE_SETUP, REQ_READ_VALVE_SETUP, RES_VALVE_SETUP_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceConfigLogic(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceConfigLogic, nullptr, REQ_READ_INTERFACE_CONFIG_LOGIC, REQ_READ_INTERFACE_CONFIG_LOGIC, RES_INTERFACE_CONFIG_LOGIC_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceConfigEthCATDi(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceConfigEthCATDi, nullptr, REQ_READ_INTERFACE_CONFIG_ETHCAT_DI, REQ_READ_INTERFACE_CONFIG_ETHCAT_DI, RES_INTERFACE_CONFIG_ETHCAT_DI_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceConfigEthCATDo(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceConfigEthCATDo, nullptr, REQ_READ_INTERFACE_CONFIG_ETHCAT_DO, REQ_READ_INTERFACE_CONFIG_ETHCAT_DO, RES_INTERFACE_CONFIG_ETHCAT_DO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigEthCATDevID(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgEthCATDevID, nullptr, REQ_READ_INTERFACE_CFG_ETHCAT_DEV_ID, REQ_READ_INTERFACE_CFG_ETHCAT_DEV_ID, RES_INTERFACE_CFG_ETHCAT_DEV_ID_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigEthCATPDODataType(int idx, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE).arg(idx,2,10,QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgEthCATPDODataType, nullptr, cmd, cmd, RES_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigEthCATPDORange(int idx, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_READ_INTERFACE_CFG_ETHCAT_PDO_RANGE).arg(idx,2,10,QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgEthCATPDORange   , nullptr, cmd, cmd, RES_INTERFACE_CFG_ETHCAT_PDO_RANGE_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceConfigDNetMac(void * userData, int retryCnt = 0)
    {
        qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]";
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetMAC, nullptr, REQ_READ_INTERFACE_CFG_DNET_MAC, REQ_READ_INTERFACE_CFG_DNET_MAC, RES_INTERFACE_CFG_DNET_MAC_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigDNetBaudrate(void * userData, int retryCnt = 0)
    {
        qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]";
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetBaudrate, nullptr, REQ_READ_INTERFACE_CFG_DNET_BAUDRATE, REQ_READ_INTERFACE_CFG_DNET_BAUDRATE, RES_INTERFACE_CFG_DNET_BAUDRATE_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigDNetDataType    (void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetDataType    , nullptr, REQ_READ_INTERFACE_CFG_DNET_DATA_TYPE    , REQ_READ_INTERFACE_CFG_DNET_DATA_TYPE    , RES_INTERFACE_CFG_DNET_DATA_TYPE_DATA_LEN    , retryCnt, userData));}
    void readInterfaceConfigDNetPosUnit     (void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetPosUnit     , nullptr, REQ_READ_INTERFACE_CFG_DNET_POS_UNIT     , REQ_READ_INTERFACE_CFG_DNET_POS_UNIT     , RES_INTERFACE_CFG_DNET_POS_UNIT_DATA_LEN     , retryCnt, userData));}
    void readInterfaceConfigDNetPosGain     (void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetPosGain     , nullptr, REQ_READ_INTERFACE_CFG_DNET_POS_GAIN     , REQ_READ_INTERFACE_CFG_DNET_POS_GAIN     , RES_INTERFACE_CFG_DNET_POS_GAIN_DATA_LEN     , retryCnt, userData));}
    void readInterfaceConfigDNetPressureUnit(void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetPressureUnit, nullptr, REQ_READ_INTERFACE_CFG_DNET_PRESSURE_UNIT, REQ_READ_INTERFACE_CFG_DNET_PRESSURE_UNIT, RES_INTERFACE_CFG_DNET_PRESSURE_UNIT_DATA_LEN, retryCnt, userData));}
    void readInterfaceConfigDNetSensor01Gain(void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetSensor01Gain, nullptr, REQ_READ_INTERFACE_CFG_DNET_S01_GAIN     , REQ_READ_INTERFACE_CFG_DNET_S01_GAIN     , RES_INTERFACE_CFG_DNET_S01_GAIN_DATA_LEN     , retryCnt, userData));}
    void readInterfaceConfigDNetSensor02Gain(void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetSensor02Gain, nullptr, REQ_READ_INTERFACE_CFG_DNET_S02_GAIN     , REQ_READ_INTERFACE_CFG_DNET_S02_GAIN     , RES_INTERFACE_CFG_DNET_S02_GAIN_DATA_LEN     , retryCnt, userData));}
    void readInterfaceConfigDNetInputAss    (void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetInputAss    , nullptr, REQ_READ_INTERFACE_CFG_DNET_IN_ASS       , REQ_READ_INTERFACE_CFG_DNET_IN_ASS       , RES_INTERFACE_CFG_DNET_IN_ASS_DATA_LEN       , retryCnt, userData));}
    void readInterfaceConfigDNetOutputAss   (void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetOutputAss   , nullptr, REQ_READ_INTERFACE_CFG_DNET_OUT_ASS      , REQ_READ_INTERFACE_CFG_DNET_OUT_ASS      , RES_INTERFACE_CFG_DNET_OUT_ASS_DATA_LEN      , retryCnt, userData));}
    void readInterfaceConfigDNetDevStatus   (void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetDevStatus   , nullptr, REQ_READ_INTERFACE_CFG_DNET_DEV_STATUS   , REQ_READ_INTERFACE_CFG_DNET_DEV_STATUS   , RES_INTERFACE_CFG_DNET_DEV_STATUS_DATA_LEN   , retryCnt, userData));}
    void readInterfaceConfigDNetExStatus    (void * userData, int retryCnt = 0){qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]"; emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetExStatus    , nullptr, REQ_READ_INTERFACE_CFG_DNET_EX_STATUS    , REQ_READ_INTERFACE_CFG_DNET_EX_STATUS    , RES_INTERFACE_CFG_DNET_EX_STATUS_DATA_LEN    , retryCnt, userData));}

    void readInterfaceConfigDNetDi(void * userData, int retryCnt = 0)
    {
        qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]";
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetDi, nullptr, REQ_READ_INTERFACE_CFG_DNET_DI, REQ_READ_INTERFACE_CFG_DNET_DI, RES_INTERFACE_CFG_DNET_DI_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigDNetDo(void * userData, int retryCnt = 0)
    {
        qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]";
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgDNetDo, nullptr, REQ_READ_INTERFACE_CFG_DNET_DO, REQ_READ_INTERFACE_CFG_DNET_DO, RES_INTERFACE_CFG_DNET_DO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigRS232(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgRS232, nullptr, REQ_READ_INTERFACE_CONFIG_RS232_IF, REQ_READ_INTERFACE_CONFIG_RS232_IF, RES_INTERFACE_CONFIG_RS232_IF_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigRS485(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgRS485, nullptr, REQ_READ_INTERFACE_CONFIG_RS485_COMM, REQ_READ_INTERFACE_CONFIG_RS485_COMM, RES_INTERFACE_CONFIG_RS485_COMM_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigRS232Range(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgRS232Range, nullptr, REQ_READ_INTERFACE_CONFIG_RS232_COMM, REQ_READ_INTERFACE_CONFIG_RS232_COMM, RES_INTERFACE_CONFIG_RS232_COMM_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceEthernetIP(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceEthernetIP, nullptr, REQ_READ_INTERFACE_ETHERNET_IP, RES_READ_INTERFACE_ETHERNET_INFO, RES_INTERFACE_ETHERNET_INFO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceEthernetSubnet(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceEthernetSubnet, nullptr, REQ_READ_INTERFACE_ETHERNET_SUBNET, RES_READ_INTERFACE_ETHERNET_INFO, RES_INTERFACE_ETHERNET_INFO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceEthernetGateway(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceEthernetGateway, nullptr, REQ_READ_INTERFACE_ETHERNET_GATEWAY, RES_READ_INTERFACE_ETHERNET_INFO, RES_INTERFACE_ETHERNET_INFO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceEthernetDHCP(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceEthernetDHCP, nullptr, REQ_READ_INTERFACE_ETHERNET_DHCP, RES_READ_INTERFACE_ETHERNET_INFO, RES_INTERFACE_ETHERNET_INFO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceEthernetPort01(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceEthernetPort01, nullptr, REQ_READ_INTERFACE_ETHERNET_PORT01, RES_READ_INTERFACE_ETHERNET_INFO, RES_INTERFACE_ETHERNET_INFO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceEthernetPort02(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceEthernetPort02, nullptr, REQ_READ_INTERFACE_ETHERNET_PORT02, RES_READ_INTERFACE_ETHERNET_INFO, RES_INTERFACE_ETHERNET_INFO_DATA_LEN, retryCnt, userData));
    }
    void readInterfaceConfigFieldbusNodeAddr(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceCfgFieldbusNodeAddr, nullptr, REQ_READ_INTERFACE_FIELDBUS_NODE_ADDR, REQ_READ_INTERFACE_FIELDBUS_NODE_ADDR, RES_INTERFACE_CFG_FIELDBUS_NODE_ADDR_DATA_LEN, retryCnt, userData));
    }
    void readLearnStatus(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadLearnStatus, nullptr, REQ_READ_LEARN_STATUS, REQ_READ_LEARN_STATUS, RES_LEARN_STATUS_DATA_LEN, retryCnt, userData));
    }

    void readLearnPressureLimit(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadLearnPressureLimit, nullptr, REQ_READ_LEARN_PRESSURE_LIMIT, REQ_READ_LEARN_PRESSURE_LIMIT, QString(REQ_READ_LEARN_PRESSURE_LIMIT).length(), retryCnt, userData));
    }

    void readFatalErrStatus(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFatalErrStatus, nullptr, REQ_READ_FATAL_ERR_STATUS, REQ_READ_FATAL_ERR_STATUS, RES_FATAL_ERR_STATUS_DATA_LEN, retryCnt, userData));
    }

    void readWarnings(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadWarnings, nullptr, REQ_READ_WARNINGS, REQ_READ_WARNINGS, RES_WARNINGS_DATA_LEN, retryCnt, userData));
    }

    void readSensor01Offset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensor01Offset, nullptr, REQ_READ_SENSOR_01_OFFSET, REQ_READ_SENSOR_01_OFFSET, RES_SENSOR_01_OFFSET_DATA_LEN, retryCnt, userData));
    }

    void readSensor02Offset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensor02Offset, nullptr, REQ_READ_SENSOR_02_OFFSET, REQ_READ_SENSOR_02_OFFSET, RES_SENSOR_02_OFFSET_DATA_LEN, retryCnt, userData));
    }

    void readControlCycles(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadControlCycles, nullptr, REQ_READ_CTRL_CYCLES, REQ_READ_CTRL_CYCLES, RES_CTRL_CYCLES_DATA_LEN, retryCnt, userData));
    }

    void readIsolationCycles(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadIsolationCycles, nullptr, REQ_READ_ISOL_CYCLES, REQ_READ_ISOL_CYCLES, RES_ISOL_CYCLES_DATA_LEN, retryCnt, userData));
    }

    void readSensorScale(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSensorScale, nullptr, REQ_READ_SENSOR_SCALE, REQ_READ_SENSOR_SCALE, RES_SENSOR_SCALE_DATA_LEN, retryCnt, userData));
    }

    void readSetPoint01(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSetPoint01, nullptr, REQ_READ_SETPOINT_01, REQ_READ_SETPOINT_01, RES_SETPOINT_01_DATA_LEN, retryCnt, userData));
    }

    void readSetPoint02(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSetPoint02, nullptr, REQ_READ_SETPOINT_02, REQ_READ_SETPOINT_02, RES_SETPOINT_02_DATA_LEN, retryCnt, userData));
    }

    void readSetPoint03(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSetPoint03, nullptr, REQ_READ_SETPOINT_03, REQ_READ_SETPOINT_03, RES_SETPOINT_03_DATA_LEN, retryCnt, userData));
    }

    void readSetPoint04(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSetPoint04, nullptr, REQ_READ_SETPOINT_04, REQ_READ_SETPOINT_04, RES_SETPOINT_04_DATA_LEN, retryCnt, userData));
    }

    void readSetPoint05(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSetPoint05, nullptr, REQ_READ_SETPOINT_05, REQ_READ_SETPOINT_05, RES_SETPOINT_05_DATA_LEN, retryCnt, userData));
    }

    void readSetPoint06(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadSetPoint06, nullptr, REQ_READ_SETPOINT_06, REQ_READ_SETPOINT_06, RES_SETPOINT_06_DATA_LEN, retryCnt, userData));
    }

    void readValveMaxSpeed(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadValveMaxSpeed, nullptr, REQ_READ_VALVE_MAX_SPEED, REQ_READ_VALVE_MAX_SPEED, RES_VALVE_MAX_SPEED_DATA_LEN, retryCnt, userData));
    }

    void readDisplayConfig(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadDisplayConfig, nullptr, REQ_READ_DP_CONFIG, REQ_READ_DP_CONFIG, RES_DP_CONFIG_DATA_LEN, retryCnt, userData));
    }

    void readValveParam(int id, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_READ_VALVE_PARAM).arg(id,2,10,QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadValveParam, nullptr, cmd, cmd, RES_VALVE_PARAM_DATA_LEN, retryCnt, userData));
    }

    void readTotalControlCycles(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadTotalControlCycles, nullptr, REQ_READ_TOTAL_CTRL_CYCLES, REQ_READ_TOTAL_CTRL_CYCLES, RES_TOTAL_CTRL_CYCLES_DATA_LEN, retryCnt, userData));
    }

    void readTotalIsolationCycles(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadTotalIsolationCycles, nullptr, REQ_READ_TOTAL_ISOL_CYCLES, REQ_READ_TOTAL_ISOL_CYCLES, RES_TOTAL_ISOL_CYCLES_DATA_LEN, retryCnt, userData));
    }

    void readPFOPerformedCycles(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadPFOPerformedCycles, nullptr, REQ_READ_PFO_PERFORMED_CYCLES, REQ_READ_PFO_PERFORMED_CYCLES, RES_PFO_PERFORMED_CYCLES_DATA_LEN, retryCnt, userData));
    }

    void readPFOCurrentVoltage(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadPFOCurrentVoltage, nullptr, REQ_READ_PFO_CURRENT_VALTAGE, REQ_READ_PFO_CURRENT_VALTAGE, RES_PFO_CURRENT_VALTAGE_DATA_LEN, retryCnt, userData));
    }

    void readFatalErr01Pos(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFatalErr01Pos, nullptr, REQ_READ_FATAL_ERR_01_POS, REQ_READ_FATAL_ERR_01_POS, RES_FATAL_ERR_01_POS_DATA_LEN, retryCnt, userData));
    }

    void readFatalErr02Pos(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFatalErr02Pos, nullptr, REQ_READ_FATAL_ERR_02_POS, REQ_READ_FATAL_ERR_02_POS, RES_FATAL_ERR_02_POS_DATA_LEN, retryCnt, userData));
    }

    void readFatalErr03Pos(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadFatalErr03Pos, nullptr, REQ_READ_FATAL_ERR_03_POS, REQ_READ_FATAL_ERR_03_POS, RES_FATAL_ERR_03_POS_DATA_LEN, retryCnt, userData));
    }

    void readLearnParam(int idx, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_READ_LEARN_PARAM).arg(idx, 3, 10, QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadLearnParam, nullptr, cmd, cmd, RES_LEARN_PARAM_DATA_LEN, retryCnt, userData));
    }

    void readValvedStatus(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadValveStatus, nullptr, REQ_READ_STATUS, REQ_READ_STATUS, RES_STATUS_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceStatusLogic(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceStatusLogic, nullptr, REQ_READ_INTERFACE_STATUS_LOGIC, REQ_READ_INTERFACE_STATUS_LOGIC, RES_INTERFACE_STATUS_LOGIC_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceStatusEtherCAT(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceStatusEtherCAT, nullptr, REQ_READ_INTERFACE_STATUS_ETHCAT, REQ_READ_INTERFACE_STATUS_ETHCAT, RES_INTERFACE_STATUS_ETHCAT_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceDNetFirmwareID(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceDNetFirmwareID, nullptr, REQ_READ_INTERFACE_DNET_FIRMWARE_ID, REQ_READ_INTERFACE_DNET_FIRMWARE_ID, RES_INTERFACE_DNET_FIRMWARE_ID_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceDNetSerialNum(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceDNetSerialNum, nullptr, REQ_READ_INTERFACE_DNET_SERIAL_NUM, REQ_READ_INTERFACE_DNET_SERIAL_NUM, RES_INTERFACE_DNET_SERIAL_NUM_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceStatusDNet(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceStatusDNet, nullptr, REQ_READ_INTERFACE_STATUS_DNET, REQ_READ_INTERFACE_STATUS_DNET, RES_INTERFACE_STATUS_DNET_DATA_LEN, retryCnt, userData));
    }

    void readInterfaceStatusRS232(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcReadInterfaceStatusRS232, nullptr, REQ_READ_INTERFACE_STATUS_RS232, REQ_READ_INTERFACE_STATUS_RS232, RES_INTERFACE_STATUS_RS232_DATA_LEN, retryCnt, userData));
    }

    /////////////////////////////////////////////
    ///
    /// Write commands
    ///
    ///
    /////////////////////////////////////////////
    void setTraceMode(bool value, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_TRACE_MODE).arg(value ? "01" : "00");

        qDebug() << "[" << Q_FUNC_INFO << "]" << cmd;
        emit signalCommandSetTraceMode(value, ValveRequestDto(this, staticProcWriteTraceMode, nullptr, cmd, "", 0, retryCnt, userData));
    }
    void setAccess(int access, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_ACCESS).arg(access == ValveEnumDef::ACCESS_LOCAL ? "00" : access == ValveEnumDef::ACCESS_REMOTE ? "01" : "02");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWriteAccess, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void enablePFO(bool isEnable, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_ENABLE_PFO).arg(isEnable? "01" : "00");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenEnablePFO, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void controlCyclesReset(void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_CTRL_CYCLES_RESET).arg("00");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenControlCyclesReset, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void isolationCyclesReset(void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_ISOL_CYCLES_RESET).arg("00");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenIsolationCyclesReset, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void reboot(void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_REBOOT).arg("01");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenReboot, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setLearnParam(QString value, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_LEARN_PARAM).arg(value);
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenLearnParam, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setValveParamStart(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenValveParamStart, nullptr, REQ_WRITE_VALVE_PARAM_START, "", 0, retryCnt, userData));
    }

    void setValveParam(int id, QString value, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3").arg(REQ_WRITE_VALVE_PARAM).arg(id, 2, 10, QChar('0')).arg(value);
        QString checkString = QString("%1%2").arg(REQ_WRITE_VALVE_PARAM).arg(id, 2, 10, QChar('0'));

        qDebug() << "[" << Q_FUNC_INFO << "]" << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenValveParam, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setValveParamEnd(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenValveParamEnd, nullptr, REQ_WRITE_VALVE_PARAM_END, "", 0, retryCnt, userData));
    }

    void factoryReset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFactoryReset, staticProcReadValveStatus, REQ_WRITE_FACTORY_RESET, "", 0, retryCnt, userData));
    }

    void valveParamReset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenValveParamReset, staticProcReadValveStatus, REQ_WRITE_VALVE_PARAM_RESET, "", 0, retryCnt, userData));
    }

    void learnReset(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenLearnReset, staticProcReadValveStatus, REQ_WRITE_LEARN_RESET, "", 0, retryCnt, userData));
    }

    void setSensorConfig(int sensorOp, bool zeroEnable, int highLowRatio, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_SENSOR_CONFIG).arg(sensorOp).arg(zeroEnable ? 1 : 0).arg(highLowRatio, 6, 10, QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSensorConfig, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    // advenced sensor setup
    void setSensorExSelection            (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_SEL                        ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSensorExSelection            , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExAnalActive              (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_ANAL_ACTIVE            ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExAnalActive              , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExSource                  (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_SRC                    ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExSource                  , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExUnit                    (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_UNIT                   ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExUnit                    , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExFullScale               (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_FULLSCALE              ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExFullScale               , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExDigiValue               (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_DIGI                   ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExDigiValue               , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExZeroAdjEnable           (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_ZERO_ENABLE            ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExZeroAdjEnable           , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExZeroAdjOffsetLimMin     (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_ZERO_MIN               ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExZeroAdjOffsetLimMin     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExZeroAdjOffsetLimMax     (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_ZERO_MAX               ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExZeroAdjOffsetLimMax     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExZeroAdjOffsetValue      (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_ZERO_VALUE             ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExZeroAdjOffsetValue      , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExScaleOffset             (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_SCALE_OFFSET           ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExScaleOffset             , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExScale                   (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_SCALE                  ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExScale                   , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExScaleZeroPoint          (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_SCALE_Z_POINT          ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExScaleZeroPoint          , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExFilterSec               (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_FILTER_SEC             ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExFilterSec               , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExLogSensorLinearize      (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_LINEARIZE     ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExLogSensorLinearize      , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExLogSensorVoltPerDecade  (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_DECADE   ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExLogSensorVoltPerDecade  , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS01ExLogSensorVoltAtFullScale(QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS01ExLogSensorVoltAtFullScale, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExAnalActive              (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_ANAL_ACTIVE            ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExAnalActive              , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExSource                  (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_SRC                    ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExSource                  , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExUnit                    (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_UNIT                   ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExUnit                    , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExFullScale               (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_FULLSCALE              ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExFullScale               , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExDigiValue               (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_DIGI                   ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExDigiValue               , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExZeroAdjEnable           (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_ZERO_ENABLE            ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExZeroAdjEnable           , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExZeroAdjOffsetLimMin     (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_ZERO_MIN               ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExZeroAdjOffsetLimMin     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExZeroAdjOffsetLimMax     (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_ZERO_MAX               ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExZeroAdjOffsetLimMax     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExZeroAdjOffsetValue      (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_ZERO_VALUE             ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExZeroAdjOffsetValue      , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExScaleOffset             (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_SCALE_OFFSET           ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExScaleOffset             , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExScale                   (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_SCALE                  ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExScale                   , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExScaleZeroPoint          (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_SCALE_Z_POINT          ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExScaleZeroPoint          , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExFilterSec               (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_FILTER_SEC             ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExFilterSec               , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExLogSensorLinearize      (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_LINEARIZE     ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExLogSensorLinearize      , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExLogSensorVoltPerDecade  (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_DECADE   ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExLogSensorVoltPerDecade  , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setS02ExLogSensorVoltAtFullScale(QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenS02ExLogSensorVoltAtFullScale, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setCrossoverMod                 (int     value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_CROSSOVER_MOD              ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenCrossoverMod                 , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setCrossoverLow                 (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_CROSSOVER_LOW              ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenCrossoverLow                 , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setCrossoverHigh                (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_CROSSOVER_HIGH             ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenCrossoverHigh                , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}
    void setCrossoverDela                (QString value, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SENSEX_CROSSOVER_DELA             ).arg(value);emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenCrossoverDela                , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]" << cmd;}

    void setPressureCtrlConfig(int controlMode, int gainFac, int sensorDelay, int rampTime,void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5%6").arg(REQ_WRITE_PRESSURE_CTRL_CONFIG)
                                               .arg(controlMode)
                                               .arg(convertIntToAbcNumber(gainFac))
                                               .arg(convertIntToAbcNumber(sensorDelay))
                                               .arg(convertIntToAbcNumber(rampTime))
                                               .arg("0000");

        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenPressureCtrlConfig, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setSelectControlMode         (int     selControlMode, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_SEL_CTRL_MODE         ).arg(selControlMode, 1,10,QChar('0'));emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSelectControlMode         , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setAdaptiveControlGainFactor (QString gainFactor    , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_ADAP_CTRL_GAIN_FAC    ).arg(gainFactor                     );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenAdaptiveControlGainFactor , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setAdaptiveControlDeltaFactor(QString deltaFactor   , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_ADAP_CTRL_DELTA_FAC   ).arg(deltaFactor                    );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenAdaptiveControlDeltaFactor, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setAdaptiveControlSensorDelay(QString sensorDelay   , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_ADAP_CTRL_SENSOR_DELAY).arg(sensorDelay                    );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenAdaptiveControlSensorDelay, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setAdaptiveControlRampTime   (QString rampTime      , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_ADAP_CTRL_RAMP_TIME   ).arg(rampTime                       ); qDebug()<< "[" <<Q_FUNC_INFO <<"]cmd = " << cmd;emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenAdaptiveControlRampTime   , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setAdaptiveControlRampMode   (int     rampMode      , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_ADAP_CTRL_RAMP_MODE   ).arg(rampMode      , 1,10,QChar('0'));emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenAdaptiveControlRampMode   , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed1ControlPGain        (QString pgain         , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED1_CTRL_P_GAIN    ).arg(pgain                          );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed1ControlPGain        , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed1ControlIGain        (QString igain         , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED1_CTRL_I_GAIN    ).arg(igain                          );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed1ControlIGain        , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed1ControlRampTime     (QString rampTime      , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED1_CTRL_RAMP_TIME ).arg(rampTime                       );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed1ControlRampTime     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed1ControlRampMode     (int     rampMode      , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED1_CTRL_RAMP_MODE ).arg(rampMode      , 1,10,QChar('0'));emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed1ControlRampMode     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed1ControlDirection    (int     ctrlDir       , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED1_CTRL_DIR       ).arg(ctrlDir       , 1,10,QChar('0'));emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed1ControlDirection    , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed2ControlPGain        (QString pgain         , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED2_CTRL_P_GAIN    ).arg(pgain                          );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed2ControlPGain        , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed2ControlIGain        (QString igain         , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED2_CTRL_I_GAIN    ).arg(igain                          );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed2ControlIGain        , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed2ControlRampTime     (QString rampTime      , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED2_CTRL_RAMP_TIME ).arg(rampTime                       );emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed2ControlRampTime     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed2ControlRampMode     (int     rampMode      , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED2_CTRL_RAMP_MODE ).arg(rampMode      , 1,10,QChar('0'));emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed2ControlRampMode     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}
    void setFixed2ControlDirection    (int     ctrlDir       , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_FIXED2_CTRL_DIR       ).arg(ctrlDir       , 1,10,QChar('0'));emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenFixed2ControlDirection    , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));}

    void setValveSetup(int targetPosSync, int eventSync, int syncMode, int strokeLimitation, int targetPosPowerFail, int targetPosNetworkFail, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5%6%7%8%9").arg(REQ_WRITE_VALVE_SETUP)
                                                   .arg(targetPosSync)
                                                   .arg(targetPosPowerFail)
                                                   .arg(0)
                                                   .arg(strokeLimitation)
                                                   .arg(targetPosNetworkFail)
                                                   .arg(0)
                                                   .arg(eventSync)
                                                   .arg(syncMode);
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenValveSetup, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigLogic(int diOpen, int diClose, int doOpen, int doClose, int learnRange, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5%6%7").arg(REQ_WRITE_INTERFACE_CONFIG_LOGIC)
                                               .arg(diOpen)
                                               .arg(diClose)
                                               .arg(doOpen)
                                               .arg(doClose)
                                               .arg(learnRange)
                                               .arg("000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigLogic, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigEthCATDi(int diFunction, int diMode, int diInput, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DI)
                                           .arg(diFunction)
                                           .arg(diMode)
                                           .arg(diInput)
                                           .arg("000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigEthCATDi, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigEthCATDo(int doFunction, int doMode, int doOutput, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5").arg(REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DO)
                                           .arg(doFunction)
                                           .arg(doMode)
                                           .arg(doOutput)
                                           .arg("000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigEthCATDo, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigEthCATDevID(int devID, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_DEV_ID)
                                           .arg("00")
                                           .arg(devID, 3,10, QChar('0'))
                                           .arg("000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceCfgEthCATDevID, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigEthCATPDODataType(int idx, int dataType, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE)
                                           .arg(idx, 2, 10, QChar('0'))
                                           .arg(dataType, 1, 10, QChar('0'))
                                           .arg("00000");
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "cmd = " <<cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceCfgEthCATPDODataType, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigEthCATPDORange(int idx, QString range, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3").arg(REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_RANGE)
                                           .arg(idx, 2, 10, QChar('0'))
                                           .arg(range);
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "cmd = " <<cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceCfgEthCATPDORange, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigDNetDi(int diActivation, int diFunction, int diPolarity, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DI)
                                           .arg(diFunction)
                                           .arg(diPolarity)
                                           .arg(diActivation)
                                           .arg("000");
        qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetDi, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigDNetDo(int doActivation, int doFunction, int doPolarity, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DO)
                                           .arg(doFunction)
                                           .arg(doPolarity)
                                           .arg(doActivation)
                                           .arg("000");
        qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetDo, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setInterfaceConfigDNetDataType    (QString dataType, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_DATA_TYPE    ).arg(dataType); emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetDataType    , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetMacAddress  (QString macAddr , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_MAC_ADDR     ).arg(macAddr ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetMacAddr     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetBaudrate    (QString baudrate, void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_BAUDRATE     ).arg(baudrate); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetBaudrate    , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetPosUnit     (QString unit    , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_UNIT     ).arg(unit    ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetPosUnit     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetPosGain     (QString gain    , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_POS_GAIN     ).arg(gain    ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetPosGain     , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetPressureUnit(QString unit    , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_PRESSURE_UNIT).arg(unit    ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetPressureUnit, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetSensor01Gain(QString gain    , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S01_GAIN     ).arg(gain    ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetSensor01Gain, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetSensor02Gain(QString gain    , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_S02_GAIN     ).arg(gain    ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetSensor02Gain, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetInputAss    (QString index   , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_IN_ASS       ).arg(index   ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetInputAss    , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }
    void setInterfaceConfigDNetOutputAss   (QString index   , void * userData, int retryCnt = 0){QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_ASS      ).arg(index   ); qDebug() << "[khko_debug]" << Q_FUNC_INFO << "]cmd = "<< cmd; emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceConfigDNetOutputAss   , staticProcReadValveStatus, cmd, "", 0, retryCnt, userData)); }


    void setInterfaceConfigRS232(int baudrateIdx, int parityIdx,int dataLenIdx, int stopBitIdx, int commandSetIdx, int secondAnswerIdx, int diOpenValveIdx, int diCloseValveIdx, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5%6%7%8%9").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_IF)
                                                   .arg(baudrateIdx    )
                                                   .arg(parityIdx      )
                                                   .arg(dataLenIdx     )
                                                   .arg(stopBitIdx     )
                                                   .arg(commandSetIdx  )
                                                   .arg(diOpenValveIdx )
                                                   .arg(diCloseValveIdx)
                                                   .arg(secondAnswerIdx);


        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceCfgRS232, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigRS485(int operationModeIdx, int duplexModeIdx, int devAddr, int terminationIdx, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5%6").arg(REQ_WRITE_INTERFACE_CONFIG_RS485_IF)
                                                   .arg(operationModeIdx)
                                                   .arg(devAddr, 3, 10, QChar('0'))
                                                   .arg(duplexModeIdx)
                                                   .arg(terminationIdx)
                                                   .arg("00");

        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "]cmd = " << cmd;

        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceCfgRS485, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceConfigRS232Range(int posRangeIdx, int pressureRange, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3").arg(REQ_WRITE_INTERFACE_CONFIG_RS232_COMM)
                                       .arg(posRangeIdx)
                                       .arg(pressureRange, 7, 10, QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceCfgRS232Range, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setInterfaceEthernetIP(QString ip, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_EHTERNET_IP).arg(ip);

        qDebug() << "[" << Q_FUNC_INFO << "]cmd = " << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceEthernetIP, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setInterfaceEthernetSubnet(QString subnet, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_EHTERNET_SUBNET).arg(subnet);

        qDebug() << "[" << Q_FUNC_INFO << "]cmd = " << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceEthernetSubnet, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setInterfaceEthernetGateway(QString gateway, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_EHTERNET_GATEWAY).arg(gateway);

        qDebug() << "[" << Q_FUNC_INFO << "]cmd = " << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceEthernetGateway, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setInterfaceEthernetDHCP(QString dhcp, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_EHTERNET_DHCP).arg(dhcp);

        qDebug() << "[" << Q_FUNC_INFO << "]cmd = " << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceEthernetDHCP, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setInterfaceEthernetPort01(QString port01, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_EHTERNET_PORT01).arg(port01);

        qDebug() << "[" << Q_FUNC_INFO << "]cmd = " << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceEthernetPort01, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setInterfaceEthernetPort02(QString port02, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_INTERFACE_EHTERNET_PORT02).arg(port02);

        qDebug() << "[" << Q_FUNC_INFO << "]cmd = " << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceEthernetPort02, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setInterfaceConfigFieldbusNodeAddr(int nodeAddr, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3").arg(REQ_WRITE_INTERFACE_CFG_FIELDBUS_NODE_ADDR)
                                           .arg(nodeAddr, 3,10, QChar('0'))
                                           .arg("00000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenInterfaceCfgFieldbusNodeAddr, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }
    void setSensorScale(int sensor01Unit, int sensor01FullScale, int sensor01SignExp, int sensor01Exp, int sensor02Unit, int sensor02FullScale, int sensor02SignExp, int sensor02Exp, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4%5%6%7%8%9%10").arg(REQ_WRITE_SENSOR_SCALE)
                                                      .arg(sensor01Unit)
                                                      .arg(QString("%1").arg(sensor01FullScale).left(5))
                                                      .arg(sensor01SignExp)
                                                      .arg(sensor01Exp)
                                                      .arg(sensor02Unit)
                                                      .arg(QString("%1").arg(sensor02FullScale).left(5))
                                                      .arg(sensor02SignExp)
                                                      .arg(sensor02Exp)
                                                      .arg("00000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSensorScale, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setSetPoint01(int position, int pressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_SETPOINT_01)
                                         .arg(position, 8, 10, QChar('0'))
                                         .arg(pressure, 8, 10, QChar('0'))
                                         .arg("00000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSetPoint01, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setSetPoint02(int position, int pressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_SETPOINT_02)
                                         .arg(position, 8, 10, QChar('0'))
                                         .arg(pressure, 8, 10, QChar('0'))
                                         .arg("00000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSetPoint02, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setSetPoint03(int position, int pressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_SETPOINT_03)
                                         .arg(position, 8, 10, QChar('0'))
                                         .arg(pressure, 8, 10, QChar('0'))
                                         .arg("00000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSetPoint03, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setSetPoint04(int position, int pressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_SETPOINT_04)
                                         .arg(position, 8, 10, QChar('0'))
                                         .arg(pressure, 8, 10, QChar('0'))
                                         .arg("00000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSetPoint04, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setSetPoint05(int position, int pressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_SETPOINT_05)
                                         .arg(position, 8, 10, QChar('0'))
                                         .arg(pressure, 8, 10, QChar('0'))
                                         .arg("00000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSetPoint05, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setSetPoint06(int position, int pressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2%3%4").arg(REQ_WRITE_SETPOINT_06)
                                         .arg(position, 8, 10, QChar('0'))
                                         .arg(pressure, 8, 10, QChar('0'))
                                         .arg("00000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSetPoint06, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setDisplayConfig(int positionResolution, int pressureDpUnit, int pressureAxisMapping, int pressureDecades, void * userData, int retryCnt = 0)
    {
        int positionResolutionIdx = convertPosResolutionValueToIdx(positionResolution);
        int pressureDecadesIdx    = convertPressureDecadesValueToIdx(pressureDecades);

        QString cmd = QString("%1%2%3%4%5%6%7").arg(REQ_WRITE_DISPLAY_CONFIG)
                                               .arg(convertIntToAbcNumber(positionResolutionIdx))
                                               .arg(12)
                                               .arg(convertIntToAbcNumber(pressureDpUnit))
                                               .arg(convertIntToAbcNumber(pressureAxisMapping))
                                               .arg(convertIntToAbcNumber(pressureDecadesIdx))
                                               .arg("000000000000000000");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenDisplayConfig, nullptr, cmd, "", 0, retryCnt, userData));
    }

    void setTargetPosition(qint64 targetPos, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_POSITION)
                                         .arg(targetPos, 6, 10, QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenPosition, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setTargetPressure(qint64 targetPressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_PRESSURE)
                                     .arg(targetPressure, 8, 10, QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenPressure, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setValveSpeed(int speed, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_VALVE_SPEED)
                                     .arg(speed, 4, 10, QChar('0'));
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenValveSpeed, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setAdcGainZero(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenAdcGainZero, staticProcReadValveStatus, REQ_WRITE_ADC_GAIN_ZERO, "", 0, retryCnt, userData));
    }

    void setSensorZero(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSensorZero, staticProcReadValveStatus, REQ_WRITE_SENSOR_ZERO, "", 0, retryCnt, userData));
    }

    void learnRun(int limitPressure, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_LEARN)
                                     .arg(limitPressure, 8, 10, QChar('0'));

        qDebug() << "[" << Q_FUNC_INFO << "]" << cmd;
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenLearn, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setSimulation(bool isSim, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_SIMULATION)
                                     .arg(isSim ? "01" : "00");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSimulation, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void holdPosition(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenHoldPosition, staticProcReadValveStatus, REQ_WRITE_HOLD_POSITION, "", 0, retryCnt, userData));
    }

    void openPosition(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenOpenPosition, staticProcReadValveStatus, REQ_WRITE_OPEN_POSITION, "", 0, retryCnt, userData));
    }

    void closePosition(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenClosePosition, staticProcReadValveStatus, REQ_WRITE_CLOSE_POSITION, "", 0, retryCnt, userData));
    }

    void softOpen(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSoftOpen, staticProcReadValveStatus, REQ_WRITE_SOFT_OPEN, "", 0, retryCnt, userData));
    }

    void softClose(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenSoftClose, staticProcReadValveStatus, REQ_WRITE_SOFT_CLOSE, "", 0, retryCnt, userData));
    }

    void setTestMode(bool value, void * userData, int retryCnt = 0)
    {
        QString cmd = QString("%1%2").arg(REQ_WRITE_TEST_MODE)
                                     .arg(value ? "01" : "00");
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenTestMode, staticProcReadValveStatus, cmd, "", 0, retryCnt, userData));
    }

    void setEncoderZero(void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenEncoderZero, staticProcReadValveStatus, REQ_WRITE_ENCODER_ZERO, "", 0, retryCnt, userData));
    }

    void customRequest(QString command, void * userData, int retryCnt = 0)
    {
        emit signalCommandRequest(ValveRequestDto(this, staticProcWrittenCustomCommand, nullptr, command, "", 0, retryCnt, userData));
    }

public slots:
    //*******************************/
    /* internal event receive slots */
    //*******************************/
    void onStartWorker()
    {
        qDebug() << "[ValveSProvider][onStartWorker]";
        setIsRunning(true);
    }

    //*******************************/
    /* worker event receive slots   */
    //*******************************/
    void onChangedIsConnecting(bool value, bool retryConnect)
    {
        qDebug() << "[ValveSProvider][onChangedIsConnecting]" << value;
        setIsConnected(value);

        mRetryConnect = retryConnect;

        if(value)
            reLoad(); // khko add proc disconnect
    }
    void onResultConnect(bool isSucc, QString connectionInfo)
    {
        qDebug() << "[ValveSProvider][onResultConnect]isSucc = " << isSucc<< ", connectionInfo = " << connectionInfo;

        if(isSucc)
        {
            setConnectionInfo(connectionInfo);
        }

        emit signalResultConnect(isSucc, connectionInfo);
    }
    void onResultReadyFirmwareUpdate(bool isSucc)
    {
        emit signalResultReadyDFU(isSucc);
    }
    void onSearchedDevice(QStringList devList)
    {
        emit signalEventSearchedDevice(devList);
    }

    void onResponseData(ValveResponseDto dto)
    {
        if(dto.mReqDto.mSubProcFunc != nullptr)
            dto.mReqDto.mSubProcFunc(&dto);

        if(dto.mReqDto.mMainProcFunc != nullptr)
            dto.mReqDto.mMainProcFunc(&dto);
    }

    void onTraceData(QString data)
    {
        emit signalEventReceivedTraceData(data);
    }

    void onChangedDFUStep(int step)
    {
        qDebug() << "[khko_debug][" << Q_FUNC_INFO << "] step = " << step;
        setDFUStep(step);
    }

    void onChangedDFUPctCpu1Kernel(int pct){ setDFUPctCpu1Kernel(pct);}
    void onChangedDFUPctCpu2Kernel(int pct){ setDFUPctCpu2Kernel(pct);}
    void onChangedDFUPctCpu1App   (int pct){ setDFUPctCpu1App   (pct);}
    void onChangedDFUPctCpu2App   (int pct){ setDFUPctCpu2App   (pct);}
    void onChangedDFUPctCpu1Verify(int pct){ setDFUPctCpu1Verify(pct);}
    void onChangedDFUPctCpu2Verify(int pct){ setDFUPctCpu2Verify(pct);}

    void onResultDFU(bool result, QString errMsg)
    {
        qDebug() << "[" << Q_FUNC_INFO << "] result = " << result << ", errMsg = " << errMsg;
        emit signalResultDFU(result, errMsg);
    }


    //******************************
    //
    //
    //
    //******************************
    static void staticProcReadValveID(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadValveID(pResData);}
    void procReadValveID(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseValveIdDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            value.insert( 1,QChar('-'));
            value.insert( 3,QChar('-'));
            value.insert( 5,QChar('-'));
            value.insert( 9,QChar('-'));
            value.insert(11,QChar('-'));
            value.insert(13,QChar('-'));
            value.insert(16,QChar('-'));
            value.insert(18,QChar('-'));
            value.insert(20,QChar('-'));
            value.insert(25,QChar('-'));

            signalDto.mValveID = value;

            setValveID(signalDto.mValveID);
        }while(false);


        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_READY) // khko_todo : resource 문제로 연결 끊겼을때는 어떻게 할 것인가?
        {
            if(signalDto.mIsSucc == false)
            {
                readValvedID(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_VALVE_ID);
                setIsSealingType(signalDto.mValveID.at(12) == QChar('S'));

                readFirmwareVersion(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
            signalEventReadedValveID(signalDto);
    }

    static void staticProcReadFirmwareVersion(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFirmwareVersion(pResData);}
    void procReadFirmwareVersion(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseFirmwareVersionDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mFirmwareVersion = value;

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_VALVE_ID)
        {
            if(signalDto.mIsSucc == false)
            {
                readFirmwareVersion(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIRMWARE_VER);
                setFirmwareVersion(signalDto.mFirmwareVersion);

                readHWConfig(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFirmwareVersion(signalDto);
        }
    }

    static void staticProcReadHWConfig(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadHWConfig(pResData);}
    void procReadHWConfig(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseHWConfigDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            QString strInterface;

            signalDto.mIsSupportPFO = value.mid(startIdx,1).toLongLong(); startIdx += 1;
            signalDto.mIsSupportSPS = value.mid(startIdx,1).toLongLong(); startIdx += 1;
            strInterface            = value.mid(startIdx,1); startIdx += 1;
            signalDto.mInterface    = convertAbcNumberToInt(strInterface);
            signalDto.mSensorVerion = value.mid(startIdx,1).toLongLong(); startIdx += 1;

            // reserved field skip (4)
            startIdx += 4;

            setIsSupportPFO       (signalDto.mIsSupportPFO);
            setIsSupportSPS       (signalDto.mIsSupportSPS);
            setIsSupportAnalogOut (isWithAnalogoutput(signalDto.mInterface));
            setInterface          (signalDto.mInterface   );
            setSensorVersion      (signalDto.mSensorVerion);

            qDebug() << "[khko_debug]interface = " << signalDto.mInterface;

        }while(false);


        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIRMWARE_VER)
        {
            if(signalDto.mIsSucc == false)
            {
                readHWConfig(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_HW_CONFIG);
                readSensorScale(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
            emit signalEventReadedHWConfig(signalDto);
    }

    static void staticProcReadSensorScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensorScale(pResData);}
    void procReadSensorScale(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorScaleDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

           QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            int     unit     = 0;
            double  scale    = 0;
            int     exponent = 0;
            int     sign     = 1;

            unit     = value.mid(startIdx,1).toInt()   ; startIdx += 1;
            scale    = value.mid(startIdx,5).toInt()   ; startIdx += 5;
            sign     = value.mid(startIdx,1).toInt()   ; startIdx += 1;
            exponent = value.mid(startIdx,1).toInt()   ; startIdx += 1;

            signalDto.mSensor01Unit      = unit;
            signalDto.mSensor01Exp       = exponent * (sign == 1 ? 1 : -1);
            signalDto.mSensor01FullScale = scale;

            unit     = value.mid(startIdx,1).toInt()   ; startIdx += 1;
            scale    = value.mid(startIdx,5).toInt()   ; startIdx += 5;
            sign     = value.mid(startIdx,1).toInt()   ; startIdx += 1;
            exponent = value.mid(startIdx,1).toInt()   ; startIdx += 1;

            signalDto.mSensor02Unit      = unit;
            signalDto.mSensor02Exp       = exponent * (sign == 1 ? 1 : -1);
            signalDto.mSensor02FullScale = scale;
            // Unkown field skip (8)
            //startIdx += 6;

            if(signalDto.mReqDto.mpRef == this)
            {
                int precision = ((QString("%1").arg(signalDto.mSensor01FullScale).length() - 4) - 4 + signalDto.mSensor01Exp) * -1;
                setS01FullScalePrec(precision);

                precision     = ((QString("%1").arg(signalDto.mSensor02FullScale).length() - 4) - 4 + signalDto.mSensor02Exp) * -1;
                setS02FullScalePrec(precision);

                setS01FullScale(signalDto.mSensor01Unit, (signalDto.mSensor01FullScale * 0.0001) * qPow(10, signalDto.mSensor01Exp));
                setS02FullScale(signalDto.mSensor02Unit, (signalDto.mSensor02FullScale * 0.0001) * qPow(10, signalDto.mSensor02Exp));
            }

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_HW_CONFIG)
        {
            if(signalDto.mIsSucc == false)
            {
                readSensorScale(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_SENSOR_SCALE);
                readSensorConfig(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensorScale(signalDto);
        }
    }

    static void staticProcReadSensorConfig(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensorConfig(pResData);}
    void procReadSensorConfig(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorConfigDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

           QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mSensorOperation = value.mid(startIdx,1).toInt()                    ; startIdx += 1;
            signalDto.mZeroEnable      = value.mid(startIdx,1).toInt() == 0 ? false : true; startIdx += 1;
            signalDto.mFullScaleRatio  = value.mid(startIdx,5).toLongLong()               ; startIdx += 5;

            if(signalDto.mReqDto.mpRef == this)
            {
                setSensorOperation(signalDto.mSensorOperation);
                setZeroEnable(signalDto.mZeroEnable);
            }

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_SENSOR_SCALE)
        {
            if(signalDto.mIsSucc == false)
            {
                readSensorConfig(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_SENSOR_CONFIG);
                readSensor01Offset(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensorConfig(signalDto);
        }
    }

    static void staticProcReadSensorOffset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensorOffset(pResData);}
    void procReadSensorOffset(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorOffsetValuesDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mS01Offset = value.mid(startIdx,6).toDouble(); startIdx += 6;
            signalDto.mS02Offset = value.mid(startIdx,6).toDouble(); startIdx += 6;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensorOffset(signalDto);
        }
    }

    static void staticProcReadSensorValue(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensorValue(pResData);}
    void procReadSensorValue(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mResultingValue = value.mid(startIdx,8).toDouble(); startIdx += 8;
            signalDto.mS01Value       = value.mid(startIdx,8).toDouble(); startIdx += 8;
            signalDto.mS02Value       = value.mid(startIdx,8).toDouble(); startIdx += 8;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensorValue(signalDto);
        }
    }

    static void staticProcReadSensorSelection(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensorSelection(pResData);}
    void procReadSensorSelection(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorSelectionDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            int selMaskedValue = 0;
            startIdx += 7;

            selMaskedValue = value.mid(startIdx,1).toInt();
            signalDto.mS01Selected = (selMaskedValue & 0x01) == 0 ? false : true;
            signalDto.mS02Selected = (selMaskedValue & 0x02) == 0 ? false : true;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensorSelection(signalDto);
        }
    }

    static void staticProcReadSensorExSelection(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensorExSelection(pResData);}
    void procReadSensorExSelection(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensorExSelection(signalDto);
        }
    }
    static void staticProcReadS01ExAnalActive(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExAnalActive(pResData);}
    void procReadS01ExAnalActive(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExAnalActive(signalDto);
        }
    }

    static void staticProcReadS01ExSource(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExSource(pResData);}
    void procReadS01ExSource(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExSource(signalDto);
        }
    }

    static void staticProcReadS01ExUnit(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExUnit(pResData);}
    void procReadS01ExUnit(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExUnit(signalDto);
        }
    }

    static void staticProcReadS01ExFullScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExFullScale(pResData);}
    void procReadS01ExFullScale(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExFullScale(signalDto);
        }
    }

    static void staticProcReadS01ExDigiValue(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExDigiValue(pResData);}
    void procReadS01ExDigiValue(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExDigiValue(signalDto);
        }
    }

    static void staticProcReadS01ExZeroAdjEnable(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExZeroAdjEnable(pResData);}
    void procReadS01ExZeroAdjEnable(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExZeroAdjEnable(signalDto);
        }
    }

    static void staticProcReadS01ExZeroAdjOffsetLimMin(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExZeroAdjOffsetLimMin(pResData);}
    void procReadS01ExZeroAdjOffsetLimMin(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExZeroAdjOffsetLimMin(signalDto);
        }
    }

    static void staticProcReadS01ExZeroAdjOffsetLimMax(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExZeroAdjOffsetLimMax(pResData);}
    void procReadS01ExZeroAdjOffsetLimMax(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExZeroAdjOffsetLimMax(signalDto);
        }
    }

    static void staticProcReadS01ExZeroAdjOffsetValue(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExZeroAdjOffsetValue(pResData);}
    void procReadS01ExZeroAdjOffsetValue(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExZeroAdjOffsetValue(signalDto);
        }
    }

    static void staticProcReadS01ExScaleOffset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExScaleOffset(pResData);}
    void procReadS01ExScaleOffset(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExScaleOffset(signalDto);
        }
    }

    static void staticProcReadS01ExScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExScale(pResData);}
    void procReadS01ExScale(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExScale(signalDto);
        }
    }

    static void staticProcReadS01ExScaleZeroPoint(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExScaleZeroPoint(pResData);}
    void procReadS01ExScaleZeroPoint(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExScaleZeroPoint(signalDto);
        }
    }

    static void staticProcReadS01ExFilterSec(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExFilterSec(pResData);}
    void procReadS01ExFilterSec(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExFilterSec(signalDto);
        }
    }

    static void staticProcReadS01ExLogSensorLinearize(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExLogSensorLinearize(pResData);}
    void procReadS01ExLogSensorLinearize(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExLogSensorLinearize(signalDto);
        }
    }

    static void staticProcReadS01ExLogSensorVoltPerDecade(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExLogSensorVoltPerDecade(pResData);}
    void procReadS01ExLogSensorVoltPerDecade(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExLogSensorVoltPerDecade(signalDto);
        }
    }

    static void staticProcReadS01ExLogSensorVoltAtFullScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS01ExLogSensorVoltAtFullScale(pResData);}
    void procReadS01ExLogSensorVoltAtFullScale(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS01ExLogSensorVoltAtFullScale(signalDto);
        }
    }

    static void staticProcReadS02ExAnalActive(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExAnalActive(pResData);}
    void procReadS02ExAnalActive(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExAnalActive(signalDto);
        }
    }

    static void staticProcReadS02ExSource(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExSource(pResData);}
    void procReadS02ExSource(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExSource(signalDto);
        }
    }

    static void staticProcReadS02ExUnit(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExUnit(pResData);}
    void procReadS02ExUnit(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExUnit(signalDto);
        }
    }

    static void staticProcReadS02ExFullScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExFullScale(pResData);}
    void procReadS02ExFullScale(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExFullScale(signalDto);
        }
    }

    static void staticProcReadS02ExDigiValue(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExDigiValue(pResData);}
    void procReadS02ExDigiValue(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExDigiValue(signalDto);
        }
    }

    static void staticProcReadS02ExZeroAdjEnable(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExZeroAdjEnable(pResData);}
    void procReadS02ExZeroAdjEnable(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExZeroAdjEnable(signalDto);
        }
    }

    static void staticProcReadS02ExZeroAdjOffsetLimMin(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExZeroAdjOffsetLimMin(pResData);}
    void procReadS02ExZeroAdjOffsetLimMin(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExZeroAdjOffsetLimMin(signalDto);
        }
    }

    static void staticProcReadS02ExZeroAdjOffsetLimMax(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExZeroAdjOffsetLimMax(pResData);}
    void procReadS02ExZeroAdjOffsetLimMax(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExZeroAdjOffsetLimMax(signalDto);
        }
    }

    static void staticProcReadS02ExZeroAdjOffsetValue(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExZeroAdjOffsetValue(pResData);}
    void procReadS02ExZeroAdjOffsetValue(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExZeroAdjOffsetValue(signalDto);
        }
    }

    static void staticProcReadS02ExScaleOffset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExScaleOffset(pResData);}
    void procReadS02ExScaleOffset(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExScaleOffset(signalDto);
        }
    }

    static void staticProcReadS02ExScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExScale(pResData);}
    void procReadS02ExScale(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExScale(signalDto);
        }
    }

    static void staticProcReadS02ExScaleZeroPoint(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExScaleZeroPoint(pResData);}
    void procReadS02ExScaleZeroPoint(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExScaleZeroPoint(signalDto);
        }
    }

    static void staticProcReadS02ExFilterSec(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExFilterSec(pResData);}
    void procReadS02ExFilterSec(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExFilterSec(signalDto);
        }
    }

    static void staticProcReadS02ExLogSensorLinearize(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExLogSensorLinearize(pResData);}
    void procReadS02ExLogSensorLinearize(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExLogSensorLinearize(signalDto);
        }
    }

    static void staticProcReadS02ExLogSensorVoltPerDecade(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExLogSensorVoltPerDecade(pResData);}
    void procReadS02ExLogSensorVoltPerDecade(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExLogSensorVoltPerDecade(signalDto);
        }
    }

    static void staticProcReadS02ExLogSensorVoltAtFullScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadS02ExLogSensorVoltAtFullScale(pResData);}
    void procReadS02ExLogSensorVoltAtFullScale(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedS02ExLogSensorVoltAtFullScale(signalDto);
        }
    }

    static void staticProcReadCrossoverMod(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadCrossoverMod(pResData);}
    void procReadCrossoverMod(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedCrossoverMod(signalDto);
        }
    }

    static void staticProcReadCrossoverLow(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadCrossoverLow(pResData);}
    void procReadCrossoverLow(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedCrossoverLow(signalDto);
        }
    }

    static void staticProcReadCrossoverHigh(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadCrossoverHigh(pResData);}
    void procReadCrossoverHigh(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedCrossoverHigh(signalDto);
        }
    }

    static void staticProcReadCrossoverDela(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadCrossoverDela(pResData);}
    void procReadCrossoverDela(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedCrossoverDela(signalDto);
        }
    }

    static void staticProcReadSensor01Offset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensor01Offset(pResData);}
    void procReadSensor01Offset(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorOffsetDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

           QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mVoltage = value.mid(startIdx,8).toInt(); startIdx += 8;

            if(signalDto.mReqDto.mpRef == this)
                setSensor01Offset(signalDto.mVoltage);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_SENSOR_CONFIG)
        {
            if(signalDto.mIsSucc == false)
            {
                readSensor01Offset(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_SENSOR_01_OFFSET);
                readSensor02Offset(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensor01Offset(signalDto);
        }
    }

    static void staticProcReadSensor02Offset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSensor02Offset(pResData);}
    void procReadSensor02Offset(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorOffsetDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

           QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mVoltage = value.mid(startIdx,8).toInt(); startIdx += 8;

            if(signalDto.mReqDto.mpRef == this)
                setSensor02Offset(signalDto.mVoltage);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_SENSOR_01_OFFSET)
        {
            if(signalDto.mIsSucc == false)
            {
                readSensor02Offset(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_SENSOR_02_OFFSET);
                readDisplayConfig(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSensor02Offset(signalDto);
        }
    }

    static void staticProcReadDisplayConfig(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadDisplayConfig(pResData);}
    void procReadDisplayConfig(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseDisplayConfigDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

           QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mPositionResolution = value.mid(startIdx,1).toInt(); startIdx += 1;
            // Unkown field skip (2)
            startIdx += 2;
            signalDto.mPressureDpUnit      = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mPressureAxisMapping = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mPressureDecades     = value.mid(startIdx,1).toInt(); startIdx += 1;

            // Unkown field skip (18)
            //startIdx += 18;

            signalDto.mPositionResolution = convertPosResolutionIdxToValue(signalDto.mPositionResolution);
            signalDto.mPressureDecades    = convertPressureDecadesIdxToValue(signalDto.mPressureDecades);

            if(signalDto.mReqDto.mpRef == this)
            {
                setPressureDpUnit(signalDto.mPressureDpUnit);
                setPositionResolution(signalDto.mPositionResolution);
                setPressureAxisMode(signalDto.mPressureAxisMapping);
                setPressureDecades(signalDto.mPressureDecades);
            }

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_SENSOR_02_OFFSET)
        {
            if(signalDto.mIsSucc == false)
            {
                readDisplayConfig(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_DP_CONFIG);
                // khko_edit readSelectControlMode(this);
                readAdaptiveControlGainFactor(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedDisplayConfig(signalDto);
        }
    }

    static void staticProcReadAdaptiveControlGainFactor(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadAdaptiveControlGainFactor(pResData);}
    bool procReadAdaptiveControlGainFactor(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseGainFactorDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mGainFactor = value;
            setAdaptiveGainFactor(value);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_DP_CONFIG)
        {
            if(signalDto.mIsSucc == false && !signalDto.mIsNetworkErr)
            {
                readSelectControlMode(this);
            }
            else if(signalDto.mIsSucc == false)
            {
                readAdaptiveControlGainFactor(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_ADAP_GAIN_FACTOR);
                readAdaptiveControlDeltaFactor(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedAdapGainFactor(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadAdaptiveControlDeltaFactor(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadAdaptiveControlDeltaFactor(pResData);}
    bool procReadAdaptiveControlDeltaFactor(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseDeltaFactorDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mDeltaFactor = value;
            setAdaptiveDeltaFactor(value);
        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_ADAP_GAIN_FACTOR)
        {
            if(signalDto.mIsSucc == false)
            {
                readAdaptiveControlDeltaFactor(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_ADAP_DELTA_FACTOR);
                readAdaptiveControlSensorDelay(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedAdapDeltaFactor(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadAdaptiveControlSensorDelay(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadAdaptiveControlSensorDelay(pResData);}
    bool procReadAdaptiveControlSensorDelay(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSensorDelayDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mSensorDelay = value;
            setAdaptiveSensorDelay(value);
        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_ADAP_DELTA_FACTOR)
        {
            if(signalDto.mIsSucc == false)
            {
                readAdaptiveControlSensorDelay(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_ADAP_SENSOR_DELAY);
                readAdaptiveControlRampTime(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedAdapSensorDelay(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadAdaptiveControlRampTime(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadAdaptiveControlRampTime(pResData);}
    bool procReadAdaptiveControlRampTime(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseRampTimeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mRampTime = value;
            setAdaptiveRampTime(value);
        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_ADAP_SENSOR_DELAY)
        {
            if(signalDto.mIsSucc == false)
            {
                readAdaptiveControlRampTime(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_ADAP_RAMP_TIME);
                readAdaptiveControlRampMode(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedAdapRampTime(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadAdaptiveControlRampMode(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadAdaptiveControlRampMode(pResData);}
    bool procReadAdaptiveControlRampMode(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseRampModeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;

            signalDto.mRampMode = value.mid(startIdx,1).toInt(); startIdx += 1;
            setAdaptiveRampMode(signalDto.mRampMode);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_ADAP_RAMP_TIME)
        {
            if(signalDto.mIsSucc == false)
            {
                readAdaptiveControlRampMode(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_ADAP_RAMP_MODE);
                readFixed1ControlPGain(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedAdapRampMode(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed1ControlPGain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed1ControlPGain(pResData);}
    bool procReadFixed1ControlPGain(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponsePGainDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mPGain = value;
            setFixed1PGain(value);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_ADAP_RAMP_MODE)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed1ControlPGain(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED1_P_GAIN);
                readFixed1ControlIGain(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed1PGain(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed1ControlIGain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed1ControlIGain(pResData);}
    bool procReadFixed1ControlIGain(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseIGainDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mIGain = value;
            setFixed1IGain(value);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED1_P_GAIN)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed1ControlIGain(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED1_I_GAIN);
                readFixed1ControlRampTime(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed1IGain(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed1ControlRampTime(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed1ControlRampTime(pResData);}
    bool procReadFixed1ControlRampTime(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseRampTimeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mRampTime = value;
            setFixed1RampTime(value);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED1_I_GAIN)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed1ControlRampTime(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED1_RAMP_TIME);
                readFixed1ControlRampMode(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed1RampTime(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed1ControlRampMode(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed1ControlRampMode(pResData);}
    bool procReadFixed1ControlRampMode(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseRampModeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;

            signalDto.mRampMode = value.mid(startIdx,1).toInt(); startIdx += 1;
            setFixed1RampMode(signalDto.mRampMode);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED1_RAMP_TIME)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed1ControlRampMode(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED1_RAMP_MODE);
                readFixed1ControlDirection(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed1RampMode(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed1ControlDirection(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed1ControlDirection(pResData);}
    bool procReadFixed1ControlDirection(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseCtrlDirDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;

            signalDto.mControlDir = value.mid(startIdx,1).toInt(); startIdx += 1;
            setFixed1Dir(signalDto.mControlDir);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED1_RAMP_MODE)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed1ControlDirection(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED1_CTRL_DIR);
                readFixed2ControlPGain(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed1CtrlDir(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed2ControlPGain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed2ControlPGain(pResData);}
    bool procReadFixed2ControlPGain(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponsePGainDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mPGain = value;
            setFixed2PGain(value);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED1_CTRL_DIR)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed2ControlPGain(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED2_P_GAIN);
                readFixed2ControlIGain(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed2PGain(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed2ControlIGain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed2ControlIGain(pResData);}
    bool procReadFixed2ControlIGain(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseIGainDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mIGain = value;
            setFixed2IGain(value);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED2_P_GAIN)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed2ControlIGain(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED2_I_GAIN);
                readFixed2ControlRampTime(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed2IGain(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed2ControlRampTime(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed2ControlRampTime(pResData);}
    bool procReadFixed2ControlRampTime(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseRampTimeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mRampTime = value;
            setFixed2RampTime(value);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED2_I_GAIN)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed2ControlRampTime(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED2_RAMP_TIME);
                readFixed2ControlRampMode(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed2RampTime(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed2ControlRampMode(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed2ControlRampMode(pResData);}
    bool procReadFixed2ControlRampMode(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseRampModeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;

            signalDto.mRampMode = value.mid(startIdx,1).toInt(); startIdx += 1;
            setFixed2RampMode(signalDto.mRampMode);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED2_RAMP_TIME)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed2ControlRampMode(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED2_RAMP_MODE);
                readFixed2ControlDirection(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed2RampMode(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadFixed2ControlDirection(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFixed2ControlDirection(pResData);}
    bool procReadFixed2ControlDirection(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseCtrlDirDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;

            signalDto.mControlDir = value.mid(startIdx,1).toInt(); startIdx += 1;
            setFixed2Dir(signalDto.mControlDir);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED2_RAMP_MODE)
        {
            if(signalDto.mIsSucc == false)
            {
                readFixed2ControlDirection(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_FIXED2_CTRL_DIR);
                readSelectControlMode(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFixed2CtrlDir(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadPressureCtrlConfig(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadPressureCtrlConfig(pResData);}
    bool procReadPressureCtrlConfig(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponsePressureCtrlConfigDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            QString strGFac;
            QString strSDelay;
            QString strRampTime;

            signalDto.mCtrlMode = value.mid(startIdx,1).toInt(); startIdx += 1;
            strGFac       = value.mid(startIdx,1)        ; startIdx += 1;
            strSDelay     = value.mid(startIdx,1)        ; startIdx += 1;
            strRampTime   = value.mid(startIdx,1)        ; startIdx += 1;
            // Unkown field skip (4)
            //startIdx += 4;

            signalDto.mGainFactor  = convertAbcNumberToInt(strGFac);
            signalDto.mSensorDelay = convertAbcNumberToInt(strSDelay);
            signalDto.mRampTime    = convertAbcNumberToInt(strRampTime);

            setPressureCtrlMode(signalDto.mCtrlMode);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_DP_CONFIG)
        {
            if(signalDto.mIsSucc == false)
            {
                readPressureCtrlConfig(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_CTRL_CONFIG);
                readSetPoint01(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedPressureCtrlConfig(signalDto);
        }

        return signalDto.mIsSucc;
    }

    static void staticProcReadSelectControlMode(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSelectControlMode(pResData);}
    bool procReadSelectControlMode(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSelControlModeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;

            signalDto.mCtrlMode = value.mid(startIdx,1).toInt(); startIdx += 1;

            setPressureCtrlMode(signalDto.mCtrlMode);

        }while(false);

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_FIXED2_CTRL_DIR)
        {
            if(signalDto.mIsSucc == false && !signalDto.mIsNetworkErr)
            {
                readPressureCtrlConfig(this);
            }
            else if(signalDto.mIsSucc == false)
            {
                readSelectControlMode(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_CTRL_CONFIG);
                readSetPoint01(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSelControlMode(signalDto);
        }

        return signalDto.mIsSucc;
    }

    ValveResponseSetPointDto procReadSetPoint(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSetPointDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mPosition = value.mid(startIdx,8).toInt(); startIdx += 8;
            signalDto.mPressure = value.mid(startIdx,8).toInt(); startIdx += 8;

        }while(false);

        return signalDto;
    }

    static void staticProcReadSetPoint01(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSetPoint01(pResData);}
    void procReadSetPoint01(void * pResData)
    {
        ValveResponseSetPointDto signalDto = procReadSetPoint(pResData);

        if(signalDto.mIsSucc)
        {
            setSetPoint01Position(signalDto.mPosition);
            setSetPoint01Pressure(signalDto.mPressure);
        }

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_PRESSURE_CTRL_CONFIG)
        {
            if(signalDto.mIsSucc == false)
            {
                readSetPoint01(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_SET_POINT_01);
                readSetPoint02(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSetPoint01(signalDto);
        }
    }

    static void staticProcReadSetPoint02(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSetPoint02(pResData);}
    void procReadSetPoint02(void * pResData)
    {
        ValveResponseSetPointDto signalDto = procReadSetPoint(pResData);

        if(signalDto.mIsSucc)
        {
            setSetPoint02Position(signalDto.mPosition);
            setSetPoint02Pressure(signalDto.mPressure);
        }

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_PRESSURE_SET_POINT_01)
        {
            if(signalDto.mIsSucc == false)
            {
                readSetPoint02(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_SET_POINT_02);
                readSetPoint03(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSetPoint02(signalDto);
        }
    }

    static void staticProcReadSetPoint03(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSetPoint03(pResData);}
    void procReadSetPoint03(void * pResData)
    {
        ValveResponseSetPointDto signalDto = procReadSetPoint(pResData);

        if(signalDto.mIsSucc)
        {
            setSetPoint03Position(signalDto.mPosition);
            setSetPoint03Pressure(signalDto.mPressure);
        }

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_PRESSURE_SET_POINT_02)
        {
            if(signalDto.mIsSucc == false)
            {
                readSetPoint03(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_SET_POINT_03);
                readSetPoint04(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSetPoint03(signalDto);
        }
    }

    static void staticProcReadSetPoint04(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSetPoint04(pResData);}
    void procReadSetPoint04(void * pResData)
    {
        ValveResponseSetPointDto signalDto = procReadSetPoint(pResData);

        if(signalDto.mIsSucc)
        {
            setSetPoint04Position(signalDto.mPosition);
            setSetPoint04Pressure(signalDto.mPressure);
        }

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_PRESSURE_SET_POINT_03)
        {
            if(signalDto.mIsSucc == false)
            {
                readSetPoint04(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_SET_POINT_04);
                readSetPoint05(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSetPoint04(signalDto);
        }
    }

    static void staticProcReadSetPoint05(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSetPoint05(pResData);}
    void procReadSetPoint05(void * pResData)
    {
        ValveResponseSetPointDto signalDto = procReadSetPoint(pResData);

        if(signalDto.mIsSucc)
        {
            setSetPoint05Position(signalDto.mPosition);
            setSetPoint05Pressure(signalDto.mPressure);
        }

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_PRESSURE_SET_POINT_04)
        {
            if(signalDto.mIsSucc == false)
            {
                readSetPoint05(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_SET_POINT_05);
                readSetPoint06(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSetPoint05(signalDto);
        }
    }

    static void staticProcReadSetPoint06(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadSetPoint06(pResData);}
    void procReadSetPoint06(void * pResData)
    {
        ValveResponseSetPointDto signalDto = procReadSetPoint(pResData);

        if(signalDto.mIsSucc)
        {
            setSetPoint06Position(signalDto.mPosition);
            setSetPoint06Pressure(signalDto.mPressure);
        }

        if(signalDto.mReqDto.mpRef == this && mLoadProgress == ValveEnumDef::LOAD_PRESSURE_SET_POINT_05)
        {
            if(signalDto.mIsSucc == false)
            {
                readSetPoint06(this);
            }
            else
            {
                setLoadProgress(ValveEnumDef::LOAD_PRESSURE_SET_POINT_06);
                readValveMaxSpeed(this);
            }
        }

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedSetPoint06(signalDto);
        }
    }

    static void staticProcReadValveMaxSpeed(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadValveMaxSpeed(pResData);}
    void procReadValveMaxSpeed(void * pResData)
    {
        int speed = 1000;
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        if(signalDto.mIsNetworkErr)
        {
            readValveMaxSpeed(this);
            return;
        }

        if(signalDto.mIsSucc)
        {
            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();
            signalDto.mValue = value;

            speed = signalDto.mValue.toInt();

            speed = speed < 1 ? 1000 : speed;
        }

        setValveMaxSpeed(speed);

        setLoadProgress(ValveEnumDef::LOAD_VALVE_MAX_SPEED);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedValveMaxSpeed(signalDto);
        }
    }

    static void staticProcReadValveStatus(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadValveStatus(pResData);}
    void procReadValveStatus(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseValveStatusDto signalDto(*pResDto);

        if(!pResDto->mResData.startsWith(REQ_READ_STATUS) || pResDto->mResData.length() < RES_STATUS_DATA_LEN + 4)
            return;

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(QString("%1").arg(REQ_READ_STATUS).length()).trimmed();

            int startIdx = 0;
            signalDto.mCurrPosition    = value.mid(startIdx,6).toLongLong(); startIdx += 6;
            signalDto.mCurrPressure    = value.mid(startIdx,8).toLongLong(); startIdx += 8;
            signalDto.mTargetValue     = value.mid(startIdx,8).toLongLong(); startIdx += 8;
            signalDto.mValveSpeed      = value.mid(startIdx,4).toLongLong(); startIdx += 4;
            signalDto.mGainFactor      = value.mid(startIdx,1).toInt()     ; startIdx += 1;
            signalDto.mAccess          = value.mid(startIdx,1).toInt()     ; startIdx += 1;

            QString abcNumber          = value.mid(startIdx,1)             ; startIdx += 1;
            signalDto.mMode            = convertAbcNumberToInt(abcNumber);// value.mid(startIdx,1).toInt()

            abcNumber                  = value.mid(startIdx,1)             ; startIdx += 1;
            signalDto.mControlMode     = convertAbcNumberToInt(abcNumber);

            // dev status mask
            int flags = convertAbcNumberToInt(value.mid(startIdx,1)); startIdx += 1;
            signalDto.mIsSimulation    = (flags & DEVSTATUS_SIM_MASK       ) != 0;
            signalDto.mEnablePFO       = (flags & DEVSTATUS_PFO_MASK       ) != 0;
            signalDto.mTestMode        = (flags & DEVSTATUS_TEST_MODE_MASK ) != 0;

            // error
            flags = convertAbcNumberToInt(value.mid(startIdx,1)); startIdx += 1;
            signalDto.mFieldBusError   = (flags & FIELDBUS_ERR_ORIGINAL_MASK ) != 0;//value.mid(startIdx,1).toInt() == 1; startIdx += 1;
            signalDto.mIsSaving        = (flags & FIELDBUS_ERR_SAVING_MASK   ) != 0;//value.mid(startIdx,1).toInt() == 1; startIdx += 1;
            signalDto.mIsIDMissing     = (flags & FIELDBUS_ERR_ID_MISS_MASK  ) != 0;
            signalDto.mIsPFOMissing    = (flags & FIELDBUS_ERR_PFO_MISS_MASK ) != 0;

            // warring mask
            flags = convertAbcNumberToInt(value.mid(startIdx,1)); startIdx += 1;
            signalDto.mFirmwareError   = (flags & WARNING2_FIRMWARE_MEMORY_MASK ) != 0;
            signalDto.mUnknowInterface = (flags & WARNING2_UNKNOW_INTERFACE_MASK) != 0;
            signalDto.mNoSensorSignal  = (flags & WARNING2_NO_SENSOR_SIG_MASK   ) != 0;
            signalDto.mNoAnalogSignal  = (flags & WARNING2_NO_ANALOG_SIG_MASK   ) != 0;

            flags = convertAbcNumberToInt(value.mid(startIdx,1)); startIdx += 1;
            signalDto.mNetworkFailure  = (flags & WARNING3_NETWORK_FAILURE_MASK) != 0;
            signalDto.mSlaveOffline    = (flags & WARNING3_SLAVE_OFFLINE_MASK  ) != 0;
            signalDto.mIsolationValve  = (flags & WARNING3_ISOLATION_VALVE_MASK) != 0;
            signalDto.mSensorError     = (flags & WARNING3_SENSOR_ERROR_MASK   ) != 0;

            flags = convertAbcNumberToInt(value.mid(startIdx,1)); startIdx += 1;
            signalDto.mSvcRequest      = (flags & WARNING4_SVC_REQ_MASK   ) != 0;
            signalDto.mLearnNotPresent = (flags & WARNING4_LEARN_NOT_MASK ) != 0;
            signalDto.mAirNotReady     = (flags & WARNING4_AIR_NOT_MASK   ) != 0;
            signalDto.mPFONotReady     = (flags & WARNING4_PFO_NOT_MASK   ) != 0;

            // pressure control config
            signalDto.mSensorDelay     = value.mid(startIdx,1).toInt()   ; startIdx += 1;
            signalDto.mRampTime        = value.mid(startIdx,1).toInt()   ; startIdx += 1;

            qint64 rcvMSec = signalDto.mResDateTime.toMSecsSinceEpoch();
            setScanRate(rcvMSec - mLastRcvMSec);
            mLastRcvMSec = rcvMSec;

            setMode             (signalDto.mMode             );
            setPressureCtrlMode (signalDto.mControlMode      );
            setAccess           (signalDto.mAccess           );
            setValveSpeed       (signalDto.mValveSpeed       );
            setIsSimulation     (signalDto.mIsSimulation     );
            setEnablePFO        (signalDto.mEnablePFO        );
            setIsTestMode       (signalDto.mTestMode         );
            setFieldBusError    (signalDto.mFieldBusError    );
            setIsSaving         (signalDto.mIsSaving         );
            setIsIDMissing      (signalDto.mIsIDMissing      );
            setIsPFOMissing     (signalDto.mIsPFOMissing     );
            setFirmwareError    (signalDto.mFirmwareError    );
            setUnknowInterface  (signalDto.mUnknowInterface  );
            setNoSensorSignal   (signalDto.mNoSensorSignal   );
            setNoAnalogSignal   (signalDto.mNoAnalogSignal   );
            setNetworkFailure   (signalDto.mNetworkFailure   );
            setSlaveOffline     (signalDto.mSlaveOffline     );
            setIsolationValve   (signalDto.mIsolationValve   );
            setSensorError      (signalDto.mSensorError      );
            setSvcRequest       (signalDto.mSvcRequest       );
            setLearnNotPresent  (signalDto.mLearnNotPresent  );
            setAirNotReady      (signalDto.mAirNotReady      );
            setPFONotReady      (signalDto.mPFONotReady      );
            setCurrPosition     (signalDto.mCurrPosition     );
            setCurrPressure     (signalDto.mCurrPressure     );



            if(signalDto.mMode != ValveEnumDef::MODE_HOLD && signalDto.mMode != ValveEnumDef::MODE_PRESSURE)
            {
                setControlMode(ValveEnumDef::MODE_POSITION);
            }
            else if(signalDto.mMode != ValveEnumDef::MODE_HOLD)
                setControlMode(ValveEnumDef::MODE_PRESSURE);

            if(getControlMode() == ValveEnumDef::MODE_POSITION)
            {
                setTargetPosition(signalDto.mTargetValue);
                signalDto.mTargetPosition = signalDto.mTargetValue;
                signalDto.mTargetPressure = getTargetPressure();
            }
            else if(getControlMode() == ValveEnumDef::MODE_PRESSURE)
            {
                setTargetPressure(signalDto.mTargetValue);
                signalDto.mTargetPosition = getTargetPosition();
                signalDto.mTargetPressure = signalDto.mTargetValue;
            }
            else
            {
                signalDto.mTargetPosition = 0;
                signalDto.mTargetPressure = 0;
            }

        }while(false);

        emit signalEventChangedValveStatus(signalDto.mResData);
        emit signalEventReadedValveStatus(signalDto);
    }

    static void staticProcReadPFOPerformedCycles(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadPFOPerformedCycles(pResData);}
    void procReadPFOPerformedCycles(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponsePFOPerformedCyclesDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mCycles = value.mid(startIdx,10).toInt(); startIdx += 10;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedPFOPerformedCycles(signalDto);
        }
    }

    static void staticProcReadPFOCurrentVoltage(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadPFOCurrentVoltage(pResData);}
    void procReadPFOCurrentVoltage(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponsePFOCurrentVoltageDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mCurrentVoltage = value.mid(startIdx,8).toInt(); startIdx += 8;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedPFOCurrentVoltage(signalDto);
        }
    }

    static void staticProcReadValveSetup(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadValveSetup(pResData);}
    void procReadValveSetup(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseValveSetupDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mTargetPosSync = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mTargetPosPowerFail = value.mid(startIdx,1).toInt(); startIdx += 1;
            // Unkown field skip (1)
            startIdx += 1;
            signalDto.mStrokeLimitation = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mTargetPosNetworkFail = value.mid(startIdx,1).toInt(); startIdx += 1;
            // Unkown field skip (1)
            startIdx += 1;
            signalDto.mEventSync = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mSyncMode  = value.mid(startIdx,1).toInt(); startIdx += 1;
            // todo sync mode startIdx += 1;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedValveSetup(signalDto);
        }
    }

    static void staticProcReadValveParam(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadValveParam(pResData);}
    void procReadValveParam(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseValveParamDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length() - 2).trimmed();

            int startIdx = 0;
            signalDto.mID = value.mid(startIdx,2).toInt()   ; startIdx += 2;
            //signalDto.mValue = value.mid(startIdx,6).toInt(); startIdx += 6;
            signalDto.mValue = value.mid(startIdx,value.length() - 2); startIdx += value.length() - 2;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedValveParam(signalDto);
        }
    }

    static void staticProcReadFatalErrStatus(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFatalErrStatus(pResData);}
    void procReadFatalErrStatus(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseFatalErrStatusDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mErrorCode = value.mid(startIdx,3).toInt(); startIdx += 3;
            // Unkown field skip (7)
            //startIdx += 7;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFatalErrStatus(signalDto);
        }
    }

    ValveResponseFatalErrPosDto procReadFatalErrPos(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseFatalErrPosDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mErrPosition = value.mid(startIdx,10).toInt(); startIdx += 10;
            signalDto.mTotalPosition = value.mid(startIdx,10).toInt(); startIdx += 10;

        }while(false);

        return signalDto;
    }

    static void staticProcReadFatalErr01Pos(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFatalErr01Pos(pResData);}
    void procReadFatalErr01Pos(void * pResData)
    {
        ValveResponseFatalErrPosDto signalDto = procReadFatalErrPos(pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFatalErr01Pos(signalDto);
        }
    }

    static void staticProcReadFatalErr02Pos(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFatalErr02Pos(pResData);}
    void procReadFatalErr02Pos(void * pResData)
    {
        ValveResponseFatalErrPosDto signalDto = procReadFatalErrPos(pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFatalErr02Pos(signalDto);
        }
    }

    static void staticProcReadFatalErr03Pos(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadFatalErr03Pos(pResData);}
    void procReadFatalErr03Pos(void * pResData)
    {
        ValveResponseFatalErrPosDto signalDto = procReadFatalErrPos(pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedFatalErr03Pos(signalDto);
        }
    }

    static void staticProcReadWarnings(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadWarnings(pResData);}
    void procReadWarnings(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseWarningsDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mIsServiceRequest = value.mid(startIdx,1).toInt(); startIdx += 1;
            // Unkown field skip (7)
            //startIdx += 7;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedWarnings(signalDto);
        }
    }

    static void staticProcReadLearnParam(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadLearnParam(pResData);}
    void procReadLearnParam(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseLearnParamDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length() - 3).trimmed();

            int startIdx = 0;
            signalDto.mIdx        = value.mid(startIdx,3).toInt(); startIdx += 3;
            signalDto.mPointValue = value.mid(startIdx,8);
            signalDto.mValue      = value.mid(0,11);

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedLearnParam(signalDto);
        }
    }

    static void staticProcReadInterfaceConfigLogic(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceConfigLogic(pResData);}
    void procReadInterfaceConfigLogic(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigLogicDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mDIOpen     = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDIClose    = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDOOpen     = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDOClose    = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mLearnRange = value.mid(startIdx,1).toInt(); startIdx += 1;
            // skip unkonw field(3)
            //startIdx += 3;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceConfigLogic(signalDto);
        }
    }

    static void staticProcReadInterfaceConfigEthCATDi(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceConfigEthCATDi(pResData);}
    void procReadInterfaceConfigEthCATDi(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigEthCATDiDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mDIFunction = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDIMode     = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDIInput    = value.mid(startIdx,1).toInt(); startIdx += 1;
            // skip unkonw field(3)
            //startIdx += 3;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceConfigEthCATDi(signalDto);
        }
    }

    static void staticProcReadInterfaceConfigEthCATDo(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceConfigEthCATDo(pResData);}
    void procReadInterfaceConfigEthCATDo(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigEthCATDoDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mDOFunction = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDOMode     = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDOOutput   = value.mid(startIdx,1).toInt(); startIdx += 1;
            // skip unkonw field(3)
            //startIdx += 3;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceConfigEthCATDo(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgEthCATDevID(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgEthCATDevID(pResData);}
    void procReadInterfaceCfgEthCATDevID(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigEthCATDevIDDto signalDto(*pResDto);


        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mDevID = value.mid(startIdx,5).toInt(); startIdx += 5;
            startIdx += 1;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgEthCATDevID(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgEthCATPDODataType(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgEthCATPDODataType(pResData);}
    void procReadInterfaceCfgEthCATPDODataType(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigEthCATPDODataTypeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mDataType = value.mid(startIdx,1).toInt();
            startIdx += 5;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgEthCATPDODataType(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgEthCATPDORange(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgEthCATPDORange(pResData);}
    void procReadInterfaceCfgEthCATPDORange(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigEthCATPDORangeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();
            QStringList valueList = value.split("to");

            signalDto.mRangeFrom = "0";
            signalDto.mRangeTo = "0";

            if(valueList.count() > 0)
                signalDto.mRangeFrom = valueList[0];
            if(valueList.count() > 1)
                signalDto.mRangeTo = valueList[1];

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgEthCATPDORange(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgDNetMAC(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetMAC(pResData);}
    void procReadInterfaceCfgDNetMAC(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigDNetMacDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mMacAddr = value.mid(startIdx,2).toInt(nullptr,16); startIdx += 2;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetMAC(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgDNetBaudrate(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetBaudrate(pResData);}
    void procReadInterfaceCfgDNetBaudrate(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigDNetBaudrateDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mBaudrate = value.mid(startIdx,2).toInt(nullptr,16); startIdx += 2;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetBaudrate(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgDNetDataType(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetDataType(pResData);}
    void procReadInterfaceCfgDNetDataType(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetDataType(signalDto);
        }
    }
    static void staticProcReadInterfaceCfgDNetPosUnit(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetPosUnit(pResData);}
    void procReadInterfaceCfgDNetPosUnit(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetPosUnit(signalDto);
        }
    }
    static void staticProcReadInterfaceCfgDNetPosGain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetPosGain(pResData);}
    void procReadInterfaceCfgDNetPosGain(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetPosGain(signalDto);
        }
    }
    static void staticProcReadInterfaceCfgDNetPressureUnit(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetPressureUnit(pResData);}
    void procReadInterfaceCfgDNetPressureUnit(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetPressureUnit(signalDto);
        }
    }
    static void staticProcReadInterfaceCfgDNetSensor01Gain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetSensor01Gain(pResData);}
    void procReadInterfaceCfgDNetSensor01Gain(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetSensor01Gain(signalDto);
        }
    }
    static void staticProcReadInterfaceCfgDNetSensor02Gain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetSensor02Gain(pResData);}
    void procReadInterfaceCfgDNetSensor02Gain(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetSensor02Gain(signalDto);
        }
    }
    static void staticProcReadInterfaceCfgDNetInputAss(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetInputAss(pResData);}
    void procReadInterfaceCfgDNetInputAss(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetInputAss(signalDto);
        }
    }
    static void staticProcReadInterfaceCfgDNetOutputAss(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetOutputAss(pResData);}
    void procReadInterfaceCfgDNetOutputAss(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetOutputAss(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgDNetDevStatus(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetDevStatus(pResData);}
    void procReadInterfaceCfgDNetDevStatus(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetDevStatus(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgDNetExStatus(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgDNetExStatus(pResData);}
    void procReadInterfaceCfgDNetExStatus(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetExStatus(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgDNetDi(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceConfigDNetDi(pResData);}
    void procReadInterfaceConfigDNetDi(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigDNetDiDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mDIFunction   = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDIPolarity   = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDIActivation = value.mid(startIdx,1).toInt(); startIdx += 1;

            // skip unkonw field(3)
            //startIdx += 3;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetDi(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgDNetDo(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceConfigDNetDo(pResData);}
    void procReadInterfaceConfigDNetDo(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigDNetDoDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mDOFunction   = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDOPolarity   = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDOActivation = value.mid(startIdx,1).toInt(); startIdx += 1;
            // skip unkonw field(3)
            //startIdx += 3;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgDNetDo(signalDto);
        }
    }

    static void staticProcReadInterfaceStatusLogic(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceStatusLogic(pResData);}
    void procReadInterfaceStatusLogic(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceStatusLogicDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mAlogInputVoltage      = value.mid(startIdx,8).toInt(); startIdx += 8;
            signalDto.mStatusDIOpen          = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDIClose         = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDICtrlModel     = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDILearn         = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDIZero          = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDILocked        = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDIHold          = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDISetPointRange = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDOOpen          = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDOClose         = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDOAlarm         = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDOReady         = value.mid(startIdx,1).toInt(); startIdx += 1;
            // skip unkonw field(3)
            //startIdx += 3;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceStatusLogic(signalDto);
        }
    }

    static void staticProcReadInterfaceStatusEtherCAT(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceStatusEtherCAT(pResData);}
    void procReadInterfaceStatusEtherCAT(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceStatusEtherCATDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            startIdx += 1;
            signalDto.mStatusDI = value.mid(startIdx,1).toInt(); startIdx += 1; // dto.mStatusDIOpen
            startIdx += 1;                                                // dto.mStatusDIClose                                           // dto.mStatusDOOpen
            signalDto.mStatusDO = value.mid(startIdx,1).toInt(); startIdx += 1; // dto.mStatusDOClose
            startIdx += 1;
            startIdx += 1;
            startIdx += 1;
            startIdx += 1;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceStatusEtherCAT(signalDto);
        }
    }

    static void staticProcReadInterfaceDNetFirmwareID(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceDNetFirmwareID(pResData);}
    void procReadInterfaceDNetFirmwareID(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceDNetFirmwareIDDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();
            signalDto.mFirmwareID = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceDNetFirmwareID(signalDto);
        }
    }

    static void staticProcReadInterfaceDNetSerialNum(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceDNetSerialNum(pResData);}
    void procReadInterfaceDNetSerialNum(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceDNetSerialNumDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();
            signalDto.mSerialNum = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceDNetSerialNum(signalDto);
        }
    }

    static void staticProcReadInterfaceStatusDNet(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceStatusDNet(pResData);}
    void procReadInterfaceStatusDNet(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceStatusDNetDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            startIdx += 1;
            signalDto.mStatusDI = value.mid(startIdx,1).toInt(); startIdx += 1; // dto.mStatusDIOpen
            startIdx += 1;                                                      // dto.mStatusDIClose                                           // dto.mStatusDOOpen
            signalDto.mStatusDO = value.mid(startIdx,1).toInt(); startIdx += 1; // dto.mStatusDOClose
            startIdx += 1;
            startIdx += 1;
            startIdx += 1;
            startIdx += 1;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceStatusDNet(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgRS232(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgRS232(pResData);}
    void procReadInterfaceCfgRS232(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigRS232Dto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mBaudrateIdx     = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mParityIdx       = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDataLenIdx      = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStopBitIdx      = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mCommandSetIdx   = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDIOpenValveIdx  = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDICloseValveIdx = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mSecondAnswerIdx = value.mid(startIdx,1).toInt(); startIdx += 1;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgRS232(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgRS485(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgRS485(pResData);}
    void procReadInterfaceCfgRS485(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigRS485Dto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mOperationModeIdx = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDevAddr          = value.mid(startIdx,3).toInt(); startIdx += 3;
            signalDto.mDuplexModeIdx    = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mTerminationIdx   = value.mid(startIdx,1).toInt(); startIdx += 1;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgRS485(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgRS232Range(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgRS232Range(pResData);}
    void procReadInterfaceCfgRS232Range(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigRS232RangeDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mPosRangeIdx   = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mPressureRange = value.mid(startIdx,7).toInt(); startIdx += 7;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgRS232Range(signalDto);
        }
    }

    static void staticProcReadInterfaceStatusRS232(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceStatusRS232(pResData);}
    void procReadInterfaceStatusRS232(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceStatusRS232Dto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mStatusDIOpen  = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDIClose = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDOOpen  = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mStatusDOClose = value.mid(startIdx,1).toInt(); startIdx += 1;
            startIdx += 1;
            startIdx += 1;
            startIdx += 1;
            startIdx += 1;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceStatusRS232(signalDto);
        }
    }

    static void staticProcReadInterfaceEthernetIP(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceEthernetIP(pResData);}
    void procReadInterfaceEthernetIP(void * pResData){
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceEthernetIP(signalDto);
        }
    }

    static void staticProcReadInterfaceEthernetSubnet(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceEthernetSubnet(pResData);}
    void procReadInterfaceEthernetSubnet(void * pResData){
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceEthernetSubnet(signalDto);
        }
    }
    static void staticProcReadInterfaceEthernetGateway(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceEthernetGateway(pResData);}
    void procReadInterfaceEthernetGateway(void * pResData){
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceEthernetGateway(signalDto);
        }
    }
    static void staticProcReadInterfaceEthernetDHCP(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceEthernetDHCP(pResData);}
    void procReadInterfaceEthernetDHCP(void * pResData){
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceEthernetDHCP(signalDto);
        }
    }
    static void staticProcReadInterfaceEthernetPort01(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceEthernetPort01(pResData);}
    void procReadInterfaceEthernetPort01(void * pResData){
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceEthernetPort01(signalDto);
        }
    }
    static void staticProcReadInterfaceEthernetPort02(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceEthernetPort02(pResData);}
    void procReadInterfaceEthernetPort02(void * pResData){
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseSimpleValueDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            signalDto.mValue = value;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceEthernetPort02(signalDto);
        }
    }

    static void staticProcReadInterfaceCfgFieldbusNodeAddr(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadInterfaceCfgFieldbusNodeAddr(pResData);}
    void procReadInterfaceCfgFieldbusNodeAddr(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseInterfaceConfigFieldbusNodeAddrDto signalDto(*pResDto);


        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mNodeAddr = value.mid(startIdx,3).toInt(); startIdx += 5;
            startIdx += 1;
        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedInterfaceCfgFieldbusNodeAddr(signalDto);
        }
    }

    static void staticProcReadControlCycles(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadControlCycles(pResData);}
    void procReadControlCycles(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseControlCyclesDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mCycles = value.mid(startIdx,10).toLongLong(); startIdx += 10;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedControlCycles(signalDto);
        }
    }

    static void staticProcReadTotalControlCycles(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadTotalControlCycles(pResData);}
    void procReadTotalControlCycles(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseTotalControlCyclesDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mCycles = value.mid(startIdx,10).toLongLong(); startIdx += 10;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedTotalControlCycles(signalDto);
        }
    }

    static void staticProcReadIsolationCycles(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadIsolationCycles(pResData);}
    void procReadIsolationCycles(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseIsolationCyclesDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mCycles = value.mid(startIdx,10).toLongLong(); startIdx += 10;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedIsolationCycles(signalDto);
        }
    }

    static void staticProcReadTotalIsolationCycles(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadTotalIsolationCycles(pResData);}
    void procReadTotalIsolationCycles(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseTotalIsolationCyclesDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mCycles = value.mid(startIdx,10).toLongLong(); startIdx += 10;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedTotalIsolationCycles(signalDto);
        }
    }

    static void staticProcReadLearnPressureLimit(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadLearnPressureLimit(pResData);}
    void procReadLearnPressureLimit(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseLearnPressureLimitDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mPressureLimit = value.mid(startIdx,8).toInt(); startIdx += 8;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedLearnPressureLimit(signalDto);
        }
    }

    static void staticProcReadLearnStatus(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procReadLearnStatus(pResData);}
    void procReadLearnStatus(void * pResData)
    {
        ValveResponseDto * pResDto = (ValveResponseDto *)pResData; pResDto->mIsParsed = true;
        ValveResponseLearnStatusDto signalDto(*pResDto);

        do{
            if(!signalDto.mIsSucc)
            {
                break;
            }

            QString value = signalDto.mResData.mid(signalDto.mReqDto.mCheckString.length()).trimmed();

            int startIdx = 0;
            signalDto.mRunning           = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mDataSetPresent    = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mAbort             = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mIsOKOpenPressure  = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mIsOKClosePressure = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mPressureRaising   = value.mid(startIdx,1).toInt(); startIdx += 1;
            signalDto.mPressureStability = value.mid(startIdx,1).toInt(); startIdx += 1;

        }while(false);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventReadedLearnStatus(signalDto);
        }
    }

    static void staticProcWriteTraceMode(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWriteTraceMode(pResData);}
    void procWriteTraceMode(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        qDebug() << "[" << Q_FUNC_INFO << "]";

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenTraceMode(signalDto);
        }
    }

    static void staticProcWriteAccess(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWriteAccess(pResData);}
    void procWriteAccess(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenAccess(signalDto);
        }
    }

    static void staticProcWrittenPosition(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenPosition(pResData);}
    void procWrittenPosition(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenTargetPosition(signalDto);
        }
    }

    static void staticProcWrittenPressure(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenPressure(pResData);}
    void procWrittenPressure(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenTargetPressure(signalDto);
        }
    }

    static void staticProcWrittenValveSpeed(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenValveSpeed(pResData);}
    void procWrittenValveSpeed(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenValveSpeed(signalDto);
        }
    }

    static void staticProcWrittenValveSetup(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenValveSetup(pResData);}
    void procWrittenValveSetup(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenValveSetup(signalDto);
        }
    }

    static void staticProcWrittenValveParamStart(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenValveParamStart(pResData);}
    void procWrittenValveParamStart(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenValveParamStart(signalDto);
        }
    }

    // khko_todo
    static void staticProcWrittenValveParam(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenValveParam(pResData);}
    void procWrittenValveParam(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenValveParam(signalDto);
        }
    }

    static void staticProcWrittenValveParamEnd(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenValveParamEnd(pResData);}
    void procWrittenValveParamEnd(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenValveParamEnd(signalDto);
        }
    }

    static void staticProcWrittenFactoryReset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFactoryReset(pResData);}
    void procWrittenFactoryReset(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenFactoryReset(signalDto);
        }
    }

    static void staticProcWrittenValveParamReset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenValveParamReset(pResData);}
    void procWrittenValveParamReset(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenValveParamReset(signalDto);
        }
    }


    static void staticProcWrittenLearnReset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenLearnReset(pResData);}
    void procWrittenLearnReset(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenLearnReset(signalDto);
        }
    }

//    void procWrittenFatalErrReset(void * pResData)
//    {
//        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

//        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
//        {
//            emit signalEventWrittenFatalErrReset(signalDto);
//        }
//    }

    static void staticProcWrittenReboot(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenReboot(pResData);}
    void procWrittenReboot(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenReboot(signalDto);
        }
    }

    static void staticProcWrittenSensorConfig(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSensorConfig(pResData);}
    void procWrittenSensorConfig(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSensorConfig(signalDto);
        }
    }

    static void staticProcWrittenSensorScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSensorScale(pResData);}
    void procWrittenSensorScale(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSensorScale(signalDto);
        }
    }

    static void staticProcWrittenSensorExSelection            (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSensorExSelection            (pResData);}
    static void staticProcWrittenS01ExAnalActive              (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExAnalActive              (pResData);}
    static void staticProcWrittenS01ExSource                  (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExSource                  (pResData);}
    static void staticProcWrittenS01ExUnit                    (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExUnit                    (pResData);}
    static void staticProcWrittenS01ExFullScale               (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExFullScale               (pResData);}
    static void staticProcWrittenS01ExDigiValue               (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExDigiValue               (pResData);}
    static void staticProcWrittenS01ExZeroAdjEnable           (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExZeroAdjEnable           (pResData);}
    static void staticProcWrittenS01ExZeroAdjOffsetLimMin     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExZeroAdjOffsetLimMin     (pResData);}
    static void staticProcWrittenS01ExZeroAdjOffsetLimMax     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExZeroAdjOffsetLimMax     (pResData);}
    static void staticProcWrittenS01ExZeroAdjOffsetValue      (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExZeroAdjOffsetValue      (pResData);}
    static void staticProcWrittenS01ExScaleOffset             (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExScaleOffset             (pResData);}
    static void staticProcWrittenS01ExScale                   (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExScale                   (pResData);}
    static void staticProcWrittenS01ExScaleZeroPoint          (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExScaleZeroPoint          (pResData);}
    static void staticProcWrittenS01ExFilterSec               (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExFilterSec               (pResData);}
    static void staticProcWrittenS01ExLogSensorLinearize      (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExLogSensorLinearize      (pResData);}
    static void staticProcWrittenS01ExLogSensorVoltPerDecade  (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExLogSensorVoltPerDecade  (pResData);}
    static void staticProcWrittenS01ExLogSensorVoltAtFullScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS01ExLogSensorVoltAtFullScale(pResData);}
    static void staticProcWrittenS02ExAnalActive              (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExAnalActive              (pResData);}
    static void staticProcWrittenS02ExSource                  (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExSource                  (pResData);}
    static void staticProcWrittenS02ExUnit                    (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExUnit                    (pResData);}
    static void staticProcWrittenS02ExFullScale               (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExFullScale               (pResData);}
    static void staticProcWrittenS02ExDigiValue               (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExDigiValue               (pResData);}
    static void staticProcWrittenS02ExZeroAdjEnable           (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExZeroAdjEnable           (pResData);}
    static void staticProcWrittenS02ExZeroAdjOffsetLimMin     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExZeroAdjOffsetLimMin     (pResData);}
    static void staticProcWrittenS02ExZeroAdjOffsetLimMax     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExZeroAdjOffsetLimMax     (pResData);}
    static void staticProcWrittenS02ExZeroAdjOffsetValue      (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExZeroAdjOffsetValue      (pResData);}
    static void staticProcWrittenS02ExScaleOffset             (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExScaleOffset             (pResData);}
    static void staticProcWrittenS02ExScale                   (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExScale                   (pResData);}
    static void staticProcWrittenS02ExScaleZeroPoint          (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExScaleZeroPoint          (pResData);}
    static void staticProcWrittenS02ExFilterSec               (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExFilterSec               (pResData);}
    static void staticProcWrittenS02ExLogSensorLinearize      (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExLogSensorLinearize      (pResData);}
    static void staticProcWrittenS02ExLogSensorVoltPerDecade  (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExLogSensorVoltPerDecade  (pResData);}
    static void staticProcWrittenS02ExLogSensorVoltAtFullScale(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenS02ExLogSensorVoltAtFullScale(pResData);}
    static void staticProcWrittenCrossoverMod                 (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenCrossoverMod                 (pResData);}
    static void staticProcWrittenCrossoverLow                 (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenCrossoverLow                 (pResData);}
    static void staticProcWrittenCrossoverHigh                (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenCrossoverHigh                (pResData);}
    static void staticProcWrittenCrossoverDela                (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenCrossoverDela                (pResData);}

    void procWrittenSensorExSelection            (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenSensorExSelection            (signalDto);}}
    void procWrittenS01ExAnalActive              (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExAnalActive              (signalDto);}}
    void procWrittenS01ExSource                  (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExSource                  (signalDto);}}
    void procWrittenS01ExUnit                    (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExUnit                    (signalDto);}}
    void procWrittenS01ExFullScale               (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExFullScale               (signalDto);}}
    void procWrittenS01ExDigiValue               (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExDigiValue               (signalDto);}}
    void procWrittenS01ExZeroAdjEnable           (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExZeroAdjEnable           (signalDto);}}
    void procWrittenS01ExZeroAdjOffsetLimMin     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExZeroAdjOffsetLimMin     (signalDto);}}
    void procWrittenS01ExZeroAdjOffsetLimMax     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExZeroAdjOffsetLimMax     (signalDto);}}
    void procWrittenS01ExZeroAdjOffsetValue      (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExZeroAdjOffsetValue      (signalDto);}}
    void procWrittenS01ExScaleOffset             (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExScaleOffset             (signalDto);}}
    void procWrittenS01ExScale                   (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExScale                   (signalDto);}}
    void procWrittenS01ExScaleZeroPoint          (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExScaleZeroPoint          (signalDto);}}
    void procWrittenS01ExFilterSec               (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExFilterSec               (signalDto);}}
    void procWrittenS01ExLogSensorLinearize      (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExLogSensorLinearize      (signalDto);}}
    void procWrittenS01ExLogSensorVoltPerDecade  (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExLogSensorVoltPerDecade  (signalDto);}}
    void procWrittenS01ExLogSensorVoltAtFullScale(void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS01ExLogSensorVoltAtFullScale(signalDto);}}
    void procWrittenS02ExAnalActive              (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExAnalActive              (signalDto);}}
    void procWrittenS02ExSource                  (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExSource                  (signalDto);}}
    void procWrittenS02ExUnit                    (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExUnit                    (signalDto);}}
    void procWrittenS02ExFullScale               (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExFullScale               (signalDto);}}
    void procWrittenS02ExDigiValue               (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExDigiValue               (signalDto);}}
    void procWrittenS02ExZeroAdjEnable           (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExZeroAdjEnable           (signalDto);}}
    void procWrittenS02ExZeroAdjOffsetLimMin     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExZeroAdjOffsetLimMin     (signalDto);}}
    void procWrittenS02ExZeroAdjOffsetLimMax     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExZeroAdjOffsetLimMax     (signalDto);}}
    void procWrittenS02ExZeroAdjOffsetValue      (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExZeroAdjOffsetValue      (signalDto);}}
    void procWrittenS02ExScaleOffset             (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExScaleOffset             (signalDto);}}
    void procWrittenS02ExScale                   (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExScale                   (signalDto);}}
    void procWrittenS02ExScaleZeroPoint          (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExScaleZeroPoint          (signalDto);}}
    void procWrittenS02ExFilterSec               (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExFilterSec               (signalDto);}}
    void procWrittenS02ExLogSensorLinearize      (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExLogSensorLinearize      (signalDto);}}
    void procWrittenS02ExLogSensorVoltPerDecade  (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExLogSensorVoltPerDecade  (signalDto);}}
    void procWrittenS02ExLogSensorVoltAtFullScale(void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenS02ExLogSensorVoltAtFullScale(signalDto);}}
    void procWrittenCrossoverMod                 (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenCrossoverMod                 (signalDto);}}
    void procWrittenCrossoverLow                 (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenCrossoverLow                 (signalDto);}}
    void procWrittenCrossoverHigh                (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenCrossoverHigh                (signalDto);}}
    void procWrittenCrossoverDela                (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenCrossoverDela                (signalDto);}}

    static void staticProcWrittenDisplayConfig(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenDisplayConfig(pResData);}
    void procWrittenDisplayConfig(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenDisplayConfig(signalDto);
        }
    }

    static void staticProcWrittenPressureCtrlConfig(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenPressureCtrlConfig(pResData);}
    void procWrittenPressureCtrlConfig(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenPressureCtrlConfig(signalDto);
        }
    }
    static void staticProcWrittenSelectControlMode         (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSelectControlMode         (pResData);}
    static void staticProcWrittenAdaptiveControlGainFactor (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenAdaptiveControlGainFactor (pResData);}
    static void staticProcWrittenAdaptiveControlDeltaFactor(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenAdaptiveControlDeltaFactor(pResData);}
    static void staticProcWrittenAdaptiveControlSensorDelay(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenAdaptiveControlSensorDelay(pResData);}
    static void staticProcWrittenAdaptiveControlRampTime   (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenAdaptiveControlRampTime   (pResData);}
    static void staticProcWrittenAdaptiveControlRampMode   (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenAdaptiveControlRampMode   (pResData);}
    static void staticProcWrittenFixed1ControlPGain        (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed1ControlPGain        (pResData);}
    static void staticProcWrittenFixed1ControlIGain        (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed1ControlIGain        (pResData);}
    static void staticProcWrittenFixed1ControlRampTime     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed1ControlRampTime     (pResData);}
    static void staticProcWrittenFixed1ControlRampMode     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed1ControlRampMode     (pResData);}
    static void staticProcWrittenFixed1ControlDirection    (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed1ControlDirection    (pResData);}
    static void staticProcWrittenFixed2ControlPGain        (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed2ControlPGain        (pResData);}
    static void staticProcWrittenFixed2ControlIGain        (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed2ControlIGain        (pResData);}
    static void staticProcWrittenFixed2ControlRampTime     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed2ControlRampTime     (pResData);}
    static void staticProcWrittenFixed2ControlRampMode     (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed2ControlRampMode     (pResData);}
    static void staticProcWrittenFixed2ControlDirection    (void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenFixed2ControlDirection    (pResData);}

    void procWrittenSelectControlMode         (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenSelContrlMode  (signalDto);}}
    void procWrittenAdaptiveControlGainFactor (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenAdapGainFactor (signalDto);}}
    void procWrittenAdaptiveControlDeltaFactor(void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenAdapDeltaFactor(signalDto);}}
    void procWrittenAdaptiveControlSensorDelay(void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenAdapSensorDelay(signalDto);}}
    void procWrittenAdaptiveControlRampTime   (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenAdapRampTime   (signalDto);}}
    void procWrittenAdaptiveControlRampMode   (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenAdapRampMode   (signalDto);}}
    void procWrittenFixed1ControlPGain        (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed1PGain    (signalDto);}}
    void procWrittenFixed1ControlIGain        (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed1IGain    (signalDto);}}
    void procWrittenFixed1ControlRampTime     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed1RampTime (signalDto);}}
    void procWrittenFixed1ControlRampMode     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed1RampMode (signalDto);}}
    void procWrittenFixed1ControlDirection    (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed1CtrlDir  (signalDto);}}
    void procWrittenFixed2ControlPGain        (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed2PGain    (signalDto);}}
    void procWrittenFixed2ControlIGain        (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed2IGain    (signalDto);}}
    void procWrittenFixed2ControlRampTime     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed2RampTime (signalDto);}}
    void procWrittenFixed2ControlRampMode     (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed2RampMode (signalDto);}}
    void procWrittenFixed2ControlDirection    (void * pResData){ValveResponseDto signalDto(*(ValveResponseDto *)pResData);  if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr){emit signalEventWrittenFixed2CtrlDir  (signalDto);}}

    static void staticProcWrittenLearnParam(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenLearnParam(pResData);}
    void procWrittenLearnParam(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenLearnParam(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigLogic(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceConfigLogic(pResData);}
    void procWrittenInterfaceConfigLogic(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigLogic(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigEthCATDi(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceConfigEthCATDi(pResData);}
    void procWrittenInterfaceConfigEthCATDi(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigEthCATDi(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigEthCATDo(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceConfigEthCATDo(pResData);}
    void procWrittenInterfaceConfigEthCATDo(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigEthCATDo(signalDto);
        }
    }

    static void staticProcWrittenInterfaceCfgEthCATDevID(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgEthCATDevID(pResData);}
    void procWrittenInterfaceCfgEthCATDevID(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceCfgEthCATDevID(signalDto);
        }
    }

    static void staticProcWrittenInterfaceCfgEthCATPDODataType(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgEthCATPDODataType(pResData);}
    void procWrittenInterfaceCfgEthCATPDODataType(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceCfgEthCATPDODataType(signalDto);
        }
    }

    static void staticProcWrittenInterfaceCfgEthCATPDORange(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgEthCATPDORange(pResData);}
    void procWrittenInterfaceCfgEthCATPDORange(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceCfgEthCATPDORange(signalDto);
        }
    }


    static void staticProcWrittenInterfaceConfigDNetDi(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetDi(pResData);}
    void procWrittenInterfaceCfgDNetDi(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetDi(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetDo(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetDo(pResData);}
    void procWrittenInterfaceCfgDNetDo(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetDo(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetDataType(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetDataType(pResData);}
    void procWrittenInterfaceCfgDNetDataType(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetDataType(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetMacAddr(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetMacAddr(pResData);}
    void procWrittenInterfaceCfgDNetMacAddr(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetMacAddr(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetBaudrate(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetBaudrate(pResData);}
    void procWrittenInterfaceCfgDNetBaudrate(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetBaudrate(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetPosUnit(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetPosUnit(pResData);}
    void procWrittenInterfaceCfgDNetPosUnit(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetPosUnit(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetPosGain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetPosGain(pResData);}
    void procWrittenInterfaceCfgDNetPosGain(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetPosGain(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetPressureUnit(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetPressureUnit(pResData);}
    void procWrittenInterfaceCfgDNetPressureUnit(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetPressureUnit(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetSensor01Gain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetSensor01Gain(pResData);}
    void procWrittenInterfaceCfgDNetSensor01Gain(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetSensor01Gain(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetSensor02Gain(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetSensor02Gain(pResData);}
    void procWrittenInterfaceCfgDNetSensor02Gain(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetSensor02Gain(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetInputAss(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetInputAss(pResData);}
    void procWrittenInterfaceCfgDNetInputAss(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetInputAss(signalDto);
        }
    }

    static void staticProcWrittenInterfaceConfigDNetOutputAss(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgDNetOutputAss(pResData);}
    void procWrittenInterfaceCfgDNetOutputAss(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceConfigDNetOutputAss(signalDto);
        }
    }

    static void staticProcWrittenInterfaceCfgRS232(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgRS232(pResData);}
    void procWrittenInterfaceCfgRS232(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceCfgRS232(signalDto);
        }
    }

    static void staticProcWrittenInterfaceCfgRS485(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgRS485(pResData);}
    void procWrittenInterfaceCfgRS485(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceCfgRS485(signalDto);
        }
    }

    static void staticProcWrittenInterfaceCfgRS232Range(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgRS232Range(pResData);}
    void procWrittenInterfaceCfgRS232Range(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceCfgRS232Range(signalDto);
        }
    }

    static void staticProcWrittenInterfaceEthernetIP(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceEthernetIP(pResData);}
    void procWrittenInterfaceEthernetIP(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceEthernetIP(signalDto);
        }
    }

    static void staticProcWrittenInterfaceEthernetSubnet(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceEthernetSubnet(pResData);}
    void procWrittenInterfaceEthernetSubnet(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceEthernetSubnet(signalDto);
        }
    }

    static void staticProcWrittenInterfaceEthernetGateway(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceEthernetGateway(pResData);}
    void procWrittenInterfaceEthernetGateway(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceEthernetGateway(signalDto);
        }
    }

    static void staticProcWrittenInterfaceEthernetDHCP(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceEthernetDHCP(pResData);}
    void procWrittenInterfaceEthernetDHCP(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceEthernetDHCP(signalDto);
        }
    }

    static void staticProcWrittenInterfaceEthernetPort01(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceEthernetPort01(pResData);}
    void procWrittenInterfaceEthernetPort01(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceEthernetPort01(signalDto);
        }
    }

    static void staticProcWrittenInterfaceEthernetPort02(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceEthernetPort02(pResData);}
    void procWrittenInterfaceEthernetPort02(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceEthernetPort02(signalDto);
        }
    }

    static void staticProcWrittenInterfaceCfgFieldbusNodeAddr(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenInterfaceCfgFieldbusNodeAddr(pResData);}
    void procWrittenInterfaceCfgFieldbusNodeAddr(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenInterfaceCfgFieldbusNodeAddr(signalDto);
        }
    }

    static void staticProcWrittenControlCyclesReset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenControlCyclesReset(pResData);}
    void procWrittenControlCyclesReset(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenControlCyclesReset(signalDto);
        }
    }

    static void staticProcWrittenIsolationCyclesReset(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenIsolationCyclesReset(pResData);}
    void procWrittenIsolationCyclesReset(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenIsolationCyclesReset(signalDto);
        }
    }

    static void staticProcWrittenAdcGainZero(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenAdcGainZero(pResData);}
    void procWrittenAdcGainZero(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenAdcGainZero(signalDto);
        }
    }

    static void staticProcWrittenSensorZero(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSensorZero(pResData);}
    void procWrittenSensorZero(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSensorZero(signalDto);
        }
    }

    static void staticProcWrittenLearn(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenLearn(pResData);}
    void procWrittenLearn(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenLearnRun(signalDto);
        }
    }

    static void staticProcWrittenSimulation(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSimulation(pResData);}
    void procWrittenSimulation(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSimulation(signalDto);
        }
    }

    static void staticProcWrittenHoldPosition(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenHoldPosition(pResData);}
    void procWrittenHoldPosition(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenHoldPosition(signalDto);
        }
    }

    static void staticProcWrittenOpenPosition(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenOpenPosition(pResData);}
    void procWrittenOpenPosition(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenOpenPosition(signalDto);
        }
    }

    static void staticProcWrittenClosePosition(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenClosePosition(pResData);}
    void procWrittenClosePosition(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenClosePosition(signalDto);
        }
    }

    static void staticProcWrittenSetPoint01(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSetPoint01(pResData);}
    void procWrittenSetPoint01(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSetPoint01(signalDto);
        }
    }

    static void staticProcWrittenSetPoint02(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSetPoint02(pResData);}
    void procWrittenSetPoint02(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSetPoint02(signalDto);
        }
    }

    static void staticProcWrittenSetPoint03(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSetPoint03(pResData);}
    void procWrittenSetPoint03(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSetPoint03(signalDto);
        }
    }

    static void staticProcWrittenSetPoint04(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSetPoint04(pResData);}
    void procWrittenSetPoint04(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSetPoint04(signalDto);
        }
    }

    static void staticProcWrittenSetPoint05(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSetPoint05(pResData);}
    void procWrittenSetPoint05(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSetPoint05(signalDto);
        }
    }

    static void staticProcWrittenSetPoint06(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSetPoint06(pResData);}
    void procWrittenSetPoint06(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSetPoint06(signalDto);
        }
    }

    static void staticProcWrittenCustomCommand(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenCustomCommand(pResData);}
    void procWrittenCustomCommand(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenCustomRequest(signalDto);
        }
    }

    static void staticProcWrittenEnablePFO(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenEnablePFO(pResData);}
    void procWrittenEnablePFO(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenEnablePFO(signalDto);
        }
    }

    static void staticProcWrittenSoftOpen(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSoftOpen(pResData);}
    void procWrittenSoftOpen(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSoftOpen(signalDto);
        }
    }

    static void staticProcWrittenSoftClose(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenSoftClose(pResData);}
    void procWrittenSoftClose(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenSoftClose(signalDto);
        }
    }

    static void staticProcWrittenTestMode(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenTestMode(pResData);}
    void procWrittenTestMode(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenTestMode(signalDto);
        }
    }

    static void staticProcWrittenEncoderZero(void * pResData){ ((ValveSProvider *)(((ValveResponseDto *)pResData)->mReqDto.mpValveSProvider))->procWrittenEncoderZero(pResData);}
    void procWrittenEncoderZero(void * pResData)
    {
        ValveResponseDto signalDto(*(ValveResponseDto *)pResData);

        qDebug() << "[khko_debug]" << signalDto.mReqDto.mReqCommand << ", " << signalDto.mResData;
        if(signalDto.mReqDto.mpRef != this && signalDto.mReqDto.mpRef != nullptr)
        {
            emit signalEventWrittenEncoderZero(signalDto);
        }
    }

public:
    int convertPosResolutionIdxToValue(int idx)
    {
        if(idx >= mPosResolutionOption.count())
            return mPosResolutionOption[0];

        return mPosResolutionOption[idx];
    }

    int convertPosResolutionValueToIdx(int value)
    {
        for(int i = 0; i < mPosResolutionOption.count(); i++ )
        {
            if(mPosResolutionOption[i] == value)
                return i;
        }
        return 0;
    }

    int convertPressureDecadesIdxToValue(int idx)
    {
        if(idx >= mPressureDecadesOption.count())
            return mPressureDecadesOption[0];

        return mPressureDecadesOption[idx];
    }

    int convertPressureDecadesValueToIdx(int value)
    {
        for(int i = 0; i < mPressureDecadesOption.count(); i++ )
        {
            if(mPressureDecadesOption[i] == value)
                return i;
        }
        return 0;
    }

    bool isWithAnalogoutput(int interface)
    {
        switch(interface)
        {
        case (int)ValveEnumDef::INTERFACE_RS232_WITH_ANALOGOUTPUT:
        case (int)ValveEnumDef::INTERFACE_RS485_WITH_ANALOGOUTPUT:
            return true;
        }

        return false;
    }

    int convertAbcNumberToInt(QString str)
    {
        char value = str.toUtf8().constData()[0];
        if('0' <= value && '9' >= value)
            return value - '0';
        if('A' <= value && 'Z' >= value)
            return (value - 'A') + 10;

        return (value - 'a') + 10;
    }

    QString convertIntToAbcNumber(int value)
    {
        char abcNum;
        if(value > 9)
        {
            abcNum = (value -10) + 'A';
            return QString(abcNum);
        }

        return QString("%1").arg(value);
    }
};
#endif // SERIALSPROVIDER_H
