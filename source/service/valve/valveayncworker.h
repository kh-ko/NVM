#ifndef VALVEASYNCWORKER_H
#define VALVEASYNCWORKER_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QThread>
#include <QDateTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QtMath>

#include "source/service/util/unitutil.h"
#include "source/service/valve/ValveConnection.h"
#include "source/service/valve/valvesproviderdtoex.h"

#define DEVSTATUS_SIM_MASK        0x01
#define DEVSTATUS_PFO_MASK        0x02
#define DEVSTATUS_TEST_MODE_MASK  0x04

#define WARNING_SVC_REQ_MASK   0x01
#define WARNING_LEARN_NOT_MASK 0x02
#define WARNING_AIR_NOT_MASK   0x04
#define WARNING_PFO_NOT_MASK   0x08

#define WARNING_SENSOR_ERROR_MASK    0x01
#define WARNING_ISOLATION_VALVE_MASK 0x02
#define WARNING_SLAVE_OFFLINE_MASK   0x04
#define WARNING_NETWORK_FAILURE_MASK 0x08

#define REQ_READY_DFU                                  "W:"
#define RES_READY_DFU_DATA_LEN                          0
#define REQ_READ_HW_CONFIG                              "i:80"
#define RES_HW_CONFIG_DATA_LEN                          8
#define REQ_READ_FIRMWARE_VERSION                       "i:82"
#define RES_FIRMWARE_VERSION_DATA_LEN                   0
#define REQ_READ_ID                                     "i:83"
#define RES_ID_DATA_LEN                                 0

/*valve max speed*/
#define REQ_READ_VALVE_MAX_SPEED                        "i:69"
#define RES_VALVE_MAX_SPEED_DATA_LEN                    6

/* defalut sensor setup*/
#define REQ_READ_SENSOR_CONFIG                          "i:01"
#define RES_SENSOR_CONFIG_DATA_LEN                      8

/* advenced sensor setup*/
#define REQ_READ_SENSEX_SEL                             "i:12000"
#define RES_SENSEX_SEL_DATA_LEN                         1
#define REQ_READ_SENSEX_S01_ANAL_ACTIVE                 "i:12121"
#define RES_SENSEX_S01_ANAL_ACTIVE_DATA_LEN             1
#define REQ_READ_SENSEX_S01_SRC                         "i:12120"
#define RES_SENSEX_S01_SRC_DATA_LEN                     1
#define REQ_READ_SENSEX_S01_UNIT                        "i:12110"
#define RES_SENSEX_S01_UNIT_DATA_LEN                    1
#define REQ_READ_SENSEX_S01_FULLSCALE                   "i:12111"
#define RES_SENSEX_S01_FULLSCALE_DATA_LEN               0
#define REQ_READ_SENSEX_S01_DIGI                        "i:12102"
#define RES_SENSEX_S01_DIGI_DATA_LEN                    0
#define REQ_READ_SENSEX_S01_ZERO_ENABLE                 "i:12131"
#define RES_SENSEX_S01_ZERO_ENABLE_DATA_LEN             1
#define REQ_READ_SENSEX_S01_ZERO_MIN                    "i:12132"
#define RES_SENSEX_S01_ZERO_MIN_DATA_LEN                0
#define REQ_READ_SENSEX_S01_ZERO_MAX                    "i:12133"
#define RES_SENSEX_S01_ZERO_MAX_DATA_LEN                0
#define REQ_READ_SENSEX_S01_ZERO_VALUE                  "i:12130"
#define RES_SENSEX_S01_ZERO_VALUE_DATA_LEN              0
#define REQ_READ_SENSEX_S01_SCALE_OFFSET                "i:12118"
#define RES_SENSEX_S01_SCALE_OFFSET_DATA_LEN            0
#define REQ_READ_SENSEX_S01_SCALE                       "i:12119"
#define RES_SENSEX_S01_SCALE_DATA_LEN                   0
#define REQ_READ_SENSEX_S01_SCALE_Z_POINT               "i:12134"
#define RES_SENSEX_S01_SCALE_Z_POINT_DATA_LEN           1
#define REQ_READ_SENSEX_S01_FILTER_SEC                  "i:12117"
#define RES_SENSEX_S01_FILTER_SEC_DATA_LEN              0
#define REQ_READ_SENSEX_S01_LOG_SENS_LINEARIZE          "i:12113"
#define RES_SENSEX_S01_LOG_SENS_LINEARIZE_DATA_LEN      1
#define REQ_READ_SENSEX_S01_LOG_SENS_VOLT_DECADE        "i:12115"
#define RES_SENSEX_S01_LOG_SENS_VOLT_DECADE_DATA_LEN    0
#define REQ_READ_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE     "i:12116"
#define RES_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE_DATA_LEN 0
#define REQ_READ_SENSEX_S02_ANAL_ACTIVE                 "i:12221"
#define RES_SENSEX_S02_ANAL_ACTIVE_DATA_LEN             1
#define REQ_READ_SENSEX_S02_SRC                         "i:12220"
#define RES_SENSEX_S02_SRC_DATA_LEN                     1
#define REQ_READ_SENSEX_S02_UNIT                        "i:12210"
#define RES_SENSEX_S02_UNIT_DATA_LEN                    1
#define REQ_READ_SENSEX_S02_FULLSCALE                   "i:12211"
#define RES_SENSEX_S02_FULLSCALE_DATA_LEN               0
#define REQ_READ_SENSEX_S02_DIGI                        "i:12202"
#define RES_SENSEX_S02_DIGI_DATA_LEN                    0
#define REQ_READ_SENSEX_S02_ZERO_ENABLE                 "i:12231"
#define RES_SENSEX_S02_ZERO_ENABLE_DATA_LEN             1
#define REQ_READ_SENSEX_S02_ZERO_MIN                    "i:12232"
#define RES_SENSEX_S02_ZERO_MIN_DATA_LEN                0
#define REQ_READ_SENSEX_S02_ZERO_MAX                    "i:12233"
#define RES_SENSEX_S02_ZERO_MAX_DATA_LEN                0
#define REQ_READ_SENSEX_S02_ZERO_VALUE                  "i:12230"
#define RES_SENSEX_S02_ZERO_VALUE_DATA_LEN              0
#define REQ_READ_SENSEX_S02_SCALE_OFFSET                "i:12218"
#define RES_SENSEX_S02_SCALE_OFFSET_DATA_LEN            0
#define REQ_READ_SENSEX_S02_SCALE                       "i:12219"
#define RES_SENSEX_S02_SCALE_DATA_LEN                   0
#define REQ_READ_SENSEX_S02_SCALE_Z_POINT               "i:12234"
#define RES_SENSEX_S02_SCALE_Z_POINT_DATA_LEN           1
#define REQ_READ_SENSEX_S02_FILTER_SEC                  "i:12217"
#define RES_SENSEX_S02_FILTER_SEC_DATA_LEN              0
#define REQ_READ_SENSEX_S02_LOG_SENS_LINEARIZE          "i:12213"
#define RES_SENSEX_S02_LOG_SENS_LINEARIZE_DATA_LEN      1
#define REQ_READ_SENSEX_S02_LOG_SENS_VOLT_DECADE        "i:12215"
#define RES_SENSEX_S02_LOG_SENS_VOLT_DECADE_DATA_LEN    0
#define REQ_READ_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE     "i:12216"
#define RES_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE_DATA_LEN 0
#define REQ_READ_SENSEX_CROSSOVER_MOD                   "i:12001"
#define RES_SENSEX_CROSSOVER_MOD_DATA_LEN               1
#define REQ_READ_SENSEX_CROSSOVER_LOW                   "i:12003"
#define RES_SENSEX_CROSSOVER_LOW_DATA_LEN               0
#define REQ_READ_SENSEX_CROSSOVER_HIGH                  "i:12004"
#define RES_SENSEX_CROSSOVER_HIGH_DATA_LEN              0
#define REQ_READ_SENSEX_CROSSOVER_DELA                  "i:12002"
#define RES_SENSEX_CROSSOVER_DELA_DATA_LEN              0
#define REQ_READ_PRESSURE_CTRL_CONFIG                   "i:02"
#define RES_PRESSURE_CTRL_CONFIG_DATA_LEN               8
#define REQ_READ_SELECT_CTRL_MODE                       "i:02Z00"
#define RES_SELECT_CTRL_MODE_DATA_LEN                   1
#define REQ_READ_ADAP_CTRL_GAIN_FAC                     "i:02A04"
#define RES_ADAP_CTRL_GAIN_FAC_DATA_LEN                 0
#define REQ_READ_ADAP_CTRL_DELTA_FAC                    "i:02A05"
#define RES_ADAP_CTRL_DELTA_FAC_DATA_LEN                0
#define REQ_READ_ADAP_CTRL_SENSOR_DELAY                 "i:02A00"
#define RES_ADAP_CTRL_SENSOR_DELAY_DATA_LEN             0
#define REQ_READ_ADAP_CTRL_RAMP_TIME                    "i:02A01"
#define RES_ADAP_CTRL_RAMP_TIME_DATA_LEN                0
#define REQ_READ_ADAP_CTRL_RAMP_MODE                    "i:02A02"
#define RES_ADAP_CTRL_RAMP_MODE_DATA_LEN                1
#define REQ_READ_FIXED1_CTRL_P_GAIN                     "i:02B04"
#define RES_FIXED1_CTRL_P_GAIN_DATA_LEN                 0
#define REQ_READ_FIXED1_CTRL_I_GAIN                     "i:02B05"
#define RES_FIXED1_CTRL_I_GAIN_DATA_LEN                 0
#define REQ_READ_FIXED1_CTRL_RAMP_TIME                  "i:02B01"
#define RES_FIXED1_CTRL_RAMP_TIME_DATA_LEN              0
#define REQ_READ_FIXED1_CTRL_RAMP_MODE                  "i:02B02"
#define RES_FIXED1_CTRL_RAMP_MODE_DATA_LEN              1
#define REQ_READ_FIXED1_CTRL_DIR                        "i:02B03"
#define RES_FIXED1_CTRL_DIR_DATA_LEN                    1
#define REQ_READ_FIXED2_CTRL_P_GAIN                     "i:02C04"
#define RES_FIXED2_CTRL_P_GAIN_DATA_LEN                 0
#define REQ_READ_FIXED2_CTRL_I_GAIN                     "i:02C05"
#define RES_FIXED2_CTRL_I_GAIN_DATA_LEN                 0
#define REQ_READ_FIXED2_CTRL_RAMP_TIME                  "i:02C01"
#define RES_FIXED2_CTRL_RAMP_TIME_DATA_LEN              0
#define REQ_READ_FIXED2_CTRL_RAMP_MODE                  "i:02C02"
#define RES_FIXED2_CTRL_RAMP_MODE_DATA_LEN              1
#define REQ_READ_FIXED2_CTRL_DIR                        "i:02C03"
#define RES_FIXED2_CTRL_DIR_DATA_LEN                    1
#define REQ_READ_VALVE_SETUP                            "i:04"
#define RES_VALVE_SETUP_DATA_LEN                        8
#define REQ_READ_INTERFACE_CONFIG_LOGIC                 "i:20"
#define RES_INTERFACE_CONFIG_LOGIC_DATA_LEN             8

/* ethercat interface setup*/
#define REQ_READ_INTERFACE_CONFIG_ETHCAT_DI             "i:2601"
#define RES_INTERFACE_CONFIG_ETHCAT_DI_DATA_LEN         6
#define REQ_READ_INTERFACE_CONFIG_ETHCAT_DO             "i:2611"
#define RES_INTERFACE_CONFIG_ETHCAT_DO_DATA_LEN         6
#define REQ_READ_INTERFACE_CFG_ETHCAT_DEV_ID            "i:25"
#define RES_INTERFACE_CFG_ETHCAT_DEV_ID_DATA_LEN        8
#define REQ_READ_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE     "i:23"
#define RES_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE_DATA_LEN 6
#define REQ_READ_INTERFACE_CFG_ETHCAT_PDO_RANGE         "i:24"
#define RES_INTERFACE_CFG_ETHCAT_PDO_RANGE_DATA_LEN     0

/* devicenet interface setup*/
#define REQ_READ_INTERFACE_CFG_DNET_MAC                 "a:72500001"
#define RES_INTERFACE_CFG_DNET_MAC_DATA_LEN             2
#define REQ_READ_INTERFACE_CFG_DNET_BAUDRATE            "a:72500002"
#define RES_INTERFACE_CFG_DNET_BAUDRATE_DATA_LEN        2
#define REQ_READ_INTERFACE_CFG_DNET_DATA_TYPE           "a:72500003"
#define RES_INTERFACE_CFG_DNET_DATA_TYPE_DATA_LEN       2
#define REQ_READ_INTERFACE_CFG_DNET_POS_UNIT            "a:7250000B"
#define RES_INTERFACE_CFG_DNET_POS_UNIT_DATA_LEN        4
#define REQ_READ_INTERFACE_CFG_DNET_POS_GAIN            "a:7250000F"
#define RES_INTERFACE_CFG_DNET_POS_GAIN_DATA_LEN        8
#define REQ_READ_INTERFACE_CFG_DNET_PRESSURE_UNIT       "a:7250000A"
#define RES_INTERFACE_CFG_DNET_PRESSURE_UNIT_DATA_LEN   4
#define REQ_READ_INTERFACE_CFG_DNET_S01_GAIN            "a:7250000D"
#define RES_INTERFACE_CFG_DNET_S01_GAIN_DATA_LEN        8
#define REQ_READ_INTERFACE_CFG_DNET_S02_GAIN            "a:7250000E"
#define RES_INTERFACE_CFG_DNET_S02_GAIN_DATA_LEN        8
#define REQ_READ_INTERFACE_CFG_DNET_IN_ASS              "a:72500005"
#define RES_INTERFACE_CFG_DNET_IN_ASS_DATA_LEN          8
#define REQ_READ_INTERFACE_CFG_DNET_OUT_ASS             "a:72500004"
#define RES_INTERFACE_CFG_DNET_OUT_ASS_DATA_LEN         8
#define REQ_READ_INTERFACE_CFG_DNET_DEV_STATUS          "a:72500008"
#define RES_INTERFACE_CFG_DNET_DEV_STATUS_DATA_LEN      2
#define REQ_READ_INTERFACE_CFG_DNET_EX_STATUS           "a:72500009"
#define RES_INTERFACE_CFG_DNET_EX_STATUS_DATA_LEN       2
#define REQ_READ_INTERFACE_CFG_DNET_DI                  "i:2601"
#define RES_INTERFACE_CFG_DNET_DI_DATA_LEN              6
#define REQ_READ_INTERFACE_CFG_DNET_DO                  "i:2611"
#define RES_INTERFACE_CFG_DNET_DO_DATA_LEN              6

/* rs232 interface setup*/
#define REQ_READ_INTERFACE_CONFIG_RS232_IF              "i:20"
#define RES_INTERFACE_CONFIG_RS232_IF_DATA_LEN          8
#define REQ_READ_INTERFACE_CONFIG_RS232_COMM            "i:21"
#define RES_INTERFACE_CONFIG_RS232_COMM_DATA_LEN        8
#define REQ_READ_INTERFACE_CONFIG_RS485_COMM            "i:22"
#define RES_INTERFACE_CONFIG_RS485_COMM_DATA_LEN        8
#define REQ_READ_INTERFACE_CONFIG_RS232_DI_01           "i:2600"
#define RES_INTERFACE_CONFIG_ETHCAT_DI_01_DATA_LEN      6
#define REQ_READ_INTERFACE_CONFIG_RS232_DI_02           "i:2601"
#define RES_INTERFACE_CONFIG_ETHCAT_DO_02_DATA_LEN      6
#define REQ_READ_INTERFACE_CONFIG_RS232_DO_01           "i:2610"
#define RES_INTERFACE_CONFIG_ETHCAT_DO_01_DATA_LEN      6
#define REQ_READ_INTERFACE_CONFIG_RS232_DO_02           "i:2611"
#define RES_INTERFACE_CONFIG_ETHCAT_DO_02_DATA_LEN      6

/*learn status*/
#define REQ_READ_LEARN_STATUS                           "i:32"
#define RES_LEARN_STATUS_DATA_LEN                       8
#define REQ_READ_LEARN_PRESSURE_LIMIT                   "i:34"
#define RES_LEARN_PRESSURE_LIMIT_DATA_LEN               8
#define REQ_READ_FATAL_ERR_STATUS                       "i:50"
#define RES_FATAL_ERR_STATUS_DATA_LEN                   3
#define REQ_READ_WARNINGS                               "i:51"
#define RES_WARNINGS_DATA_LEN                           8
#define REQ_READ_SENSOR_01_OFFSET                       "i:60"
#define RES_SENSOR_01_OFFSET_DATA_LEN                   8
#define REQ_READ_SENSOR_02_OFFSET                       "i:61"
#define RES_SENSOR_02_OFFSET_DATA_LEN                   8
#define REQ_READ_CTRL_CYCLES                            "i:70"
#define RES_CTRL_CYCLES_DATA_LEN                        10
#define REQ_READ_ISOL_CYCLES                            "i:71"
#define RES_ISOL_CYCLES_DATA_LEN                        10
#define REQ_READ_SENSOR_SCALE                           "j:00"
#define RES_SENSOR_SCALE_DATA_LEN                       24
#define REQ_READ_SETPOINT_01                            "j:01"
#define RES_SETPOINT_01_DATA_LEN                        8
#define REQ_READ_SETPOINT_02                            "j:02"
#define RES_SETPOINT_02_DATA_LEN                        8
#define REQ_READ_SETPOINT_03                            "j:03"
#define RES_SETPOINT_03_DATA_LEN                        8
#define REQ_READ_SETPOINT_04                            "j:04"
#define RES_SETPOINT_04_DATA_LEN                        8
#define REQ_READ_SETPOINT_05                            "j:05"
#define RES_SETPOINT_05_DATA_LEN                        8
#define REQ_READ_SETPOINT_06                            "j:06"
#define RES_SETPOINT_06_DATA_LEN                        8
#define REQ_READ_DP_CONFIG                              "j:07"
#define RES_DP_CONFIG_DATA_LEN                          24
#define REQ_READ_VALVE_PARAM                            "b:10"
#define RES_VALVE_PARAM_DATA_LEN                        6
#define REQ_READ_TOTAL_CTRL_CYCLES                      "b:3070"
#define RES_TOTAL_CTRL_CYCLES_DATA_LEN                  10
#define REQ_READ_TOTAL_ISOL_CYCLES                      "b:3071"
#define RES_TOTAL_ISOL_CYCLES_DATA_LEN                  10
#define REQ_READ_PFO_PERFORMED_CYCLES                   "b:3044"
#define RES_PFO_PERFORMED_CYCLES_DATA_LEN               10
#define REQ_READ_PFO_CURRENT_VALTAGE                    "b:3244"
#define RES_PFO_CURRENT_VALTAGE_DATA_LEN                8
#define REQ_READ_FATAL_ERR_01_POS                       "b:3310"
#define RES_FATAL_ERR_01_POS_DATA_LEN                   20
#define REQ_READ_FATAL_ERR_02_POS                       "b:3311"
#define RES_FATAL_ERR_02_POS_DATA_LEN                   20
#define REQ_READ_FATAL_ERR_03_POS                       "b:3312"
#define RES_FATAL_ERR_03_POS_DATA_LEN                   20
#define REQ_READ_LEARN_PARAM                            "u:"
#define RES_LEARN_PARAM_DATA_LEN                        8
#define REQ_READ_STATUS                                 "x:10"
#define RES_STATUS_DATA_LEN                             37
#define REQ_READ_INTERFACE_STATUS_LOGIC                 "x:02"
#define RES_INTERFACE_STATUS_LOGIC_DATA_LEN             20
#define REQ_READ_INTERFACE_STATUS_ETHCAT                "i:40"
#define RES_INTERFACE_STATUS_ETHCAT_DATA_LEN            8
#define REQ_READ_INTERFACE_DNET_FIRMWARE_ID             "b:7200"
#define RES_INTERFACE_DNET_FIRMWARE_ID_DATA_LEN         0
#define REQ_READ_INTERFACE_DNET_SERIAL_NUM              "b:7201"
#define RES_INTERFACE_DNET_SERIAL_NUM_DATA_LEN          0
#define REQ_READ_INTERFACE_STATUS_DNET                  "i:40"
#define RES_INTERFACE_STATUS_DNET_DATA_LEN              8
#define REQ_READ_INTERFACE_STATUS_RS232                 "i:40"
#define RES_INTERFACE_STATUS_RS232_DATA_LEN             8

/* sensor offset, sensor value */
#define REQ_READ_SENSOR_OFFSET                          "x:06"
#define RES_SENSOR_OFFSET_DATA_LEN                      12
#define REQ_READ_SENSOR_VALUE                           "x:03"
#define RES_SENSOR_VALUE_DATA_LEN                       24
#define REQ_READ_SENSOR_SELECTION                       "b:3005"
#define RES_SENSOR_SELECTION_DATA_LEN                   8


#define REQ_WRITE_ACCESS                                "c:01"
#define REQ_WRITE_ENABLE_PFO                            "c:10"
#define REQ_WRITE_CTRL_CYCLES_RESET                     "c:20"
#define REQ_WRITE_ISOL_CYCLES_RESET                     "c:21"
#define REQ_WRITE_REBOOT                                "c:82"
#define REQ_WRITE_LEARN_PARAM                           "d:"
#define REQ_WRITE_VALVE_PARAM_START                     "a:9901"
#define REQ_WRITE_VALVE_PARAM                           "a:10"
#define REQ_WRITE_VALVE_PARAM_END                       "a:9900"
#define REQ_WRITE_FACTORY_RESET                         "f:01"
#define REQ_WRITE_LEARN_RESET                           "f:02"
#define REQ_WRITE_VALVE_PARAM_RESET                     "f:03"

/* default sensor setup*/
#define REQ_WRITE_SENSOR_CONFIG                      "s:01"

/* advenced sensor setup*/
#define REQ_WRITE_SENSEX_SEL                         "s:12000"
#define REQ_WRITE_SENSEX_S01_ANAL_ACTIVE             "s:12121"
#define REQ_WRITE_SENSEX_S01_SRC                     "s:12120"
#define REQ_WRITE_SENSEX_S01_UNIT                    "s:12110"
#define REQ_WRITE_SENSEX_S01_FULLSCALE               "s:12111"
#define REQ_WRITE_SENSEX_S01_DIGI                    "s:12102"
#define REQ_WRITE_SENSEX_S01_ZERO_ENABLE             "s:12131"
#define REQ_WRITE_SENSEX_S01_ZERO_MIN                "s:12132"
#define REQ_WRITE_SENSEX_S01_ZERO_MAX                "s:12133"
#define REQ_WRITE_SENSEX_S01_ZERO_VALUE              "s:12130"
#define REQ_WRITE_SENSEX_S01_SCALE_OFFSET            "s:12118"
#define REQ_WRITE_SENSEX_S01_SCALE                   "s:12119"
#define REQ_WRITE_SENSEX_S01_SCALE_Z_POINT           "s:12134"
#define REQ_WRITE_SENSEX_S01_FILTER_SEC              "s:12117"
#define REQ_WRITE_SENSEX_S01_LOG_SENS_LINEARIZE      "s:12113"
#define REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_DECADE    "s:12115"
#define REQ_WRITE_SENSEX_S01_LOG_SENS_VOLT_FULLSCALE "s:12116"
#define REQ_WRITE_SENSEX_S02_ANAL_ACTIVE             "s:12221"
#define REQ_WRITE_SENSEX_S02_SRC                     "s:12220"
#define REQ_WRITE_SENSEX_S02_UNIT                    "s:12210"
#define REQ_WRITE_SENSEX_S02_FULLSCALE               "s:12211"
#define REQ_WRITE_SENSEX_S02_DIGI                    "s:12202"
#define REQ_WRITE_SENSEX_S02_ZERO_ENABLE             "s:12231"
#define REQ_WRITE_SENSEX_S02_ZERO_MIN                "s:12232"
#define REQ_WRITE_SENSEX_S02_ZERO_MAX                "s:12233"
#define REQ_WRITE_SENSEX_S02_ZERO_VALUE              "s:12230"
#define REQ_WRITE_SENSEX_S02_SCALE_OFFSET            "s:12218"
#define REQ_WRITE_SENSEX_S02_SCALE                   "s:12219"
#define REQ_WRITE_SENSEX_S02_SCALE_Z_POINT           "s:12234"
#define REQ_WRITE_SENSEX_S02_FILTER_SEC              "s:12217"
#define REQ_WRITE_SENSEX_S02_LOG_SENS_LINEARIZE      "s:12213"
#define REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_DECADE    "s:12215"
#define REQ_WRITE_SENSEX_S02_LOG_SENS_VOLT_FULLSCALE "s:12216"
#define REQ_WRITE_SENSEX_CROSSOVER_MOD               "s:12001"
#define REQ_WRITE_SENSEX_CROSSOVER_LOW               "s:12003"
#define REQ_WRITE_SENSEX_CROSSOVER_HIGH              "s:12004"
#define REQ_WRITE_SENSEX_CROSSOVER_DELA              "s:12002"

#define REQ_WRITE_PRESSURE_CTRL_CONFIG               "s:02"
#define REQ_WRITE_SEL_CTRL_MODE                      "s:02Z00"
#define REQ_WRITE_ADAP_CTRL_GAIN_FAC                 "s:02A04"
#define REQ_WRITE_ADAP_CTRL_DELTA_FAC                "s:02A05"
#define REQ_WRITE_ADAP_CTRL_SENSOR_DELAY             "s:02A00"
#define REQ_WRITE_ADAP_CTRL_RAMP_TIME                "s:02A01"
#define REQ_WRITE_ADAP_CTRL_RAMP_MODE                "s:02A02"
#define REQ_WRITE_FIXED1_CTRL_P_GAIN                 "s:02B04"
#define REQ_WRITE_FIXED1_CTRL_I_GAIN                 "s:02B05"
#define REQ_WRITE_FIXED1_CTRL_RAMP_TIME              "s:02B01"
#define REQ_WRITE_FIXED1_CTRL_RAMP_MODE              "s:02B02"
#define REQ_WRITE_FIXED1_CTRL_DIR                    "s:02B03"
#define REQ_WRITE_FIXED2_CTRL_P_GAIN                 "s:02C04"
#define REQ_WRITE_FIXED2_CTRL_I_GAIN                 "s:02C05"
#define REQ_WRITE_FIXED2_CTRL_RAMP_TIME              "s:02C01"
#define REQ_WRITE_FIXED2_CTRL_RAMP_MODE              "s:02C02"
#define REQ_WRITE_FIXED2_CTRL_DIR                    "s:02C03"
#define REQ_WRITE_VALVE_SETUP                        "s:04"

/* logic interface */
#define REQ_WRITE_INTERFACE_CONFIG_LOGIC             "s:20"

/* ethercat interface */
#define REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DI         "s:2601"
#define REQ_WRITE_INTERFACE_CONFIG_ETHCAT_DO         "s:2611"
#define REQ_WRITE_INTERFACE_CFG_ETHCAT_DEV_ID        "s:25"
#define REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_DATA_TYPE "s:23"
#define REQ_WRITE_INTERFACE_CFG_ETHCAT_PDO_RANGE     "s:24"
/* devicenet interface */
#define REQ_WRITE_INTERFACE_CONFIG_DNET_DI           "s:2601"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_DO           "s:2611"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_DATA_TYPE     "a:72500103"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_POS_UNIT      "a:7250010B"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_POS_GAIN      "a:7250010F"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_PRESSURE_UNIT "a:7250010A"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_S01_GAIN      "a:7250010D"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_S02_GAIN      "a:7250010E"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_IN_ASS        "a:72500105"
#define REQ_WRITE_INTERFACE_CONFIG_DNET_OUT_ASS       "a:72500104"

/* rs232 interface */
#define REQ_WRITE_INTERFACE_CONFIG_RS232_IF          "s:20"
#define REQ_WRITE_INTERFACE_CONFIG_RS485_IF          "s:22"
#define REQ_WRITE_INTERFACE_CONFIG_RS232_COMM        "s:21"

#define REQ_WRITE_SENSOR_SCALE                       "J:00"
#define REQ_WRITE_SETPOINT_01                        "J:01"
#define REQ_WRITE_SETPOINT_02                        "J:02"
#define REQ_WRITE_SETPOINT_03                        "J:03"
#define REQ_WRITE_SETPOINT_04                        "J:04"
#define REQ_WRITE_SETPOINT_05                        "J:05"
#define REQ_WRITE_SETPOINT_06                        "J:06"
#define REQ_WRITE_DISPLAY_CONFIG                     "J:07"
#define REQ_WRITE_POSITION                           "R:"
#define REQ_WRITE_PRESSURE                           "S:"
#define REQ_WRITE_VALVE_SPEED                        "V:00"
#define REQ_WRITE_ADC_GAIN_ZERO                      "G:"
#define REQ_WRITE_SENSOR_ZERO                        "Z:"
#define REQ_WRITE_LEARN                              "L:"
#define REQ_WRITE_SIMULATION                         "c:90"
#define REQ_WRITE_HOLD_POSITION                      "H:"
#define REQ_WRITE_OPEN_POSITION                      "O:"
#define REQ_WRITE_CLOSE_POSITION                     "C:"
#define REQ_WRITE_SOFT_OPEN                          "OS:"
#define REQ_WRITE_SOFT_CLOSE                         "CS:"
#define REQ_WRITE_TEST_MODE                          "n:01"
#define REQ_WRITE_ENCODER_ZERO                       "n:0201"

#define REQ_WRITE_FU                                 "W:"

class ValveEnumDef: public QObject{
    Q_OBJECT
    Q_ENUMS(eSensorOp)
    Q_ENUMS(ePressureUnit)
    Q_ENUMS(ePosResolution)
    Q_ENUMS(ePressureCtrlMode)
    Q_ENUMS(eAccess)
    Q_ENUMS(eMode)
    Q_ENUMS(ePressureAxisMode)
    Q_ENUMS(eTargetPosAfterSync)
    Q_ENUMS(eTargetPosNetworkFail)
    Q_ENUMS(eEventSync)
    Q_ENUMS(eLoadStep)
    Q_ENUMS(eLearnRunState)
    Q_ENUMS(eLearnDataSet)
    Q_ENUMS(eLearnAbort)
    Q_ENUMS(eLearnOpenPressure)
    Q_ENUMS(eLearnClosePressure)
    Q_ENUMS(eLearnPressureRaising)
    Q_ENUMS(eLearnPressureStable)
    Q_ENUMS(eInterface)

public:
    enum eSensorOp{
        SENSOROP_NO_SENSOR                 = 0,
        SENSOROP_01_SENSOR_01_INPUT        = 1,
        SENSOROP_02_SENSOR_LOW_02_HIGHT_01 = 2,
        SENSOROP_01_SENSOR_02_INPUT        = 3,
        SENSOROP_02_SENSOR_LOW_01_HIGHT_02 = 4,
    };

    enum ePressureUnit{
        PRESSURE_UNIT_PA    = UnitUtilEnumDef::PRESSURE_UNIT_PA   ,
        PRESSURE_UNIT_BAR   = UnitUtilEnumDef::PRESSURE_UNIT_BAR  ,
        PRESSURE_UNIT_MBAR  = UnitUtilEnumDef::PRESSURE_UNIT_MBAR ,
        PRESSURE_UNIT_UBAR  = UnitUtilEnumDef::PRESSURE_UNIT_UBAR ,
        PRESSURE_UNIT_TORR  = UnitUtilEnumDef::PRESSURE_UNIT_TORR ,
        PRESSURE_UNIT_MTORR = UnitUtilEnumDef::PRESSURE_UNIT_MTORR,
        PRESSURE_UNIT_ATM   = UnitUtilEnumDef::PRESSURE_UNIT_ATM  ,
        PRESSURE_UNIT_PSI   = UnitUtilEnumDef::PRESSURE_UNIT_PSI  ,
        PRESSURE_UNIT_PSF   = UnitUtilEnumDef::PRESSURE_UNIT_PSF  ,
    };

    enum ePosResolution{
        POS_RESOLUTION_100000 = 100000,
        POS_RESOLUTION_10000  = 10000,
        POS_RESOLUTION_1000   = 1000,
        POS_RESOLUTION_100    = 100,
    };

    enum ePressureCtrlMode{
        PRESSURE_CTRL_ADAPTIVE   = 0,
        PRESSURE_CTRL_FIXED_DOWN = 1,
        PRESSURE_CTRL_FIXED_UP   = 2,
        PRESSURE_CTRL_SOFT_DUMP  = 3,
    };

    enum ePressureCtrlGainFac{
        PRESSURE_CTRL_GAIN_0_1     = 0,
        PRESSURE_CTRL_GAIN_0_13    = 1,
        PRESSURE_CTRL_GAIN_0_18    = 2,
        PRESSURE_CTRL_GAIN_0_23    = 3,
        PRESSURE_CTRL_GAIN_0_32    = 4,
        PRESSURE_CTRL_GAIN_0_42    = 5,
        PRESSURE_CTRL_GAIN_0_56    = 6,
        PRESSURE_CTRL_GAIN_0_75    = 7,
        PRESSURE_CTRL_GAIN_1_0     = 8,
        PRESSURE_CTRL_GAIN_1_33    = 9,
        PRESSURE_CTRL_GAIN_1_78    = 10,
        PRESSURE_CTRL_GAIN_2_37    = 11,
        PRESSURE_CTRL_GAIN_3_16    = 12,
        PRESSURE_CTRL_GAIN_4_22    = 13,
        PRESSURE_CTRL_GAIN_5_62    = 14,
        PRESSURE_CTRL_GAIN_7_5     = 15,
        PRESSURE_CTRL_GAIN_0_0001  = 16,
        PRESSURE_CTRL_GAIN_0_0003  = 17,
        PRESSURE_CTRL_GAIN_0_001   = 18,
        PRESSURE_CTRL_GAIN_0_003   = 19,
        PRESSURE_CTRL_GAIN_0_01    = 20,
        PRESSURE_CTRL_GAIN_0_02    = 21,
        PRESSURE_CTRL_GAIN_0_05    = 22,
    };

    enum ePressureCtrlSDelay{
        PRESSURE_CTRL_S_DELAY_0    = 0,
        PRESSURE_CTRL_S_DELAY_0_02 = 0,
        PRESSURE_CTRL_S_DELAY_0_04 = 0,
        PRESSURE_CTRL_S_DELAY_0_06 = 0,
        PRESSURE_CTRL_S_DELAY_0_08 = 0,
        PRESSURE_CTRL_S_DELAY_0_1  = 0,
        PRESSURE_CTRL_S_DELAY_0_15 = 0,
        PRESSURE_CTRL_S_DELAY_0_20 = 0,
        PRESSURE_CTRL_S_DELAY_0_25 = 0,
        PRESSURE_CTRL_S_DELAY_0_30 = 0,
        PRESSURE_CTRL_S_DELAY_0_35 = 0,
        PRESSURE_CTRL_S_DELAY_0_40 = 0,
        PRESSURE_CTRL_S_DELAY_0_50 = 0,
        PRESSURE_CTRL_S_DELAY_0_60 = 0,
        PRESSURE_CTRL_S_DELAY_0_80 = 0,
        PRESSURE_CTRL_S_DELAY_1    = 0,
    };

    enum ePressureCtrlRampTime{
        PRESSURE_CTRL_RAMP_0    = 0,
        PRESSURE_CTRL_RAMP_0_5  = 0,
        PRESSURE_CTRL_RAMP_1    = 0,
        PRESSURE_CTRL_RAMP_1_5  = 0,
        PRESSURE_CTRL_RAMP_2    = 0,
        PRESSURE_CTRL_RAMP_2_5  = 0,
        PRESSURE_CTRL_RAMP_3    = 0,
        PRESSURE_CTRL_RAMP_3_5  = 0,
        PRESSURE_CTRL_RAMP_4    = 0,
        PRESSURE_CTRL_RAMP_4_5  = 0,
        PRESSURE_CTRL_RAMP_5    = 0,
        PRESSURE_CTRL_RAMP_5_5  = 0,
        PRESSURE_CTRL_RAMP_6    = 0,
        PRESSURE_CTRL_RAMP_6_5  = 0,
        PRESSURE_CTRL_RAMP_7    = 0,
        PRESSURE_CTRL_RAMP_7_5  = 0,
        PRESSURE_CTRL_RAMP_8    = 0,
        PRESSURE_CTRL_RAMP_8_5  = 0,
        PRESSURE_CTRL_RAMP_9    = 0,
        PRESSURE_CTRL_RAMP_9_5  = 0,
        PRESSURE_CTRL_RAMP_10   = 0,
    };

    enum eAccess{
        ACCESS_LOCAL         = 0,
        ACCESS_REMOTE        = 1,
        ACCESS_LOCKED_REMOTE = 2,
    };

    enum eMode{
        MODE_INIT               =  0,
        MODE_SYNC               =  1,
        MODE_POSITION           =  2,
        MODE_CLOSED             =  3,
        MODE_OPEN               =  4,
        MODE_PRESSURE           =  5,
        MODE_HOLD               =  6,
        MODE_LEARN              =  7,
        MODE_INTERLOCK_OPEN_DI  =  8,
        MODE_INTERLOCK_CLOSE_DI =  9,
        MODE_UNKONW_01          = 10,
        MODE_UNKONW_02          = 11,
        MODE_POWER_FAILURE      = 12,
        MODE_SAFETY             = 13,
        MODE_FATAL_ERROR        = 14,
    };

    enum ePressureAxisMode{
        PRESSURE_AXIS_LINEAR = 0,
        PRESSURE_AXIS_LOG    = 1,
    };

    enum eTargetPosAfterSync{
        TARGET_POS_SYNC_CLOSE = 0,
        TARGET_POS_SYNC_OPEN  = 1,
    };

    enum eEventSync{
        EVENT_SYNC_DEFAULT = 0,
        EVENT_SYNC_SELECTED_CMD = 1,
        EVENT_SYNC_OPEN_CMD = 2,
        EVENT_SYNC_ANY_CMD = 3,
    };

    enum eTargetPosPowerFail{
        TARGET_POS_PF_CLOSE = 0,
        TARGET_POS_PF_OPEN  = 1,
    };

    enum eTargetPosNetworkFail{
        TARGET_POS_NF_CLOSE     = 0,
        TARGET_POS_NF_OPEN      = 1,
        TARGET_POS_NF_KEEP_POS  = 21,
    };

    enum eLoadStep{
        LOAD_NONE                  = 0,
        LOAD_READY                 = LOAD_NONE                  + 1,
        LOAD_VALVE_ID              = LOAD_READY                 + 1,
        LOAD_FIRMWARE_VER          = LOAD_VALVE_ID              + 1,
        LOAD_HW_CONFIG             = LOAD_FIRMWARE_VER          + 1,
        LOAD_SENSOR_SCALE          = LOAD_HW_CONFIG             + 1,
        LOAD_SENSOR_CONFIG         = LOAD_SENSOR_SCALE          + 1,
        LOAD_SENSOR_01_OFFSET      = LOAD_SENSOR_CONFIG         + 1,
        LOAD_SENSOR_02_OFFSET      = LOAD_SENSOR_01_OFFSET      + 1,
        LOAD_DP_CONFIG             = LOAD_SENSOR_02_OFFSET      + 1,
        LOAD_PRESSURE_CTRL_CONFIG  = LOAD_DP_CONFIG             + 1,
        LOAD_PRESSURE_SET_POINT_01 = LOAD_PRESSURE_CTRL_CONFIG  + 1,
        LOAD_PRESSURE_SET_POINT_02 = LOAD_PRESSURE_SET_POINT_01 + 1,
        LOAD_PRESSURE_SET_POINT_03 = LOAD_PRESSURE_SET_POINT_02 + 1,
        LOAD_PRESSURE_SET_POINT_04 = LOAD_PRESSURE_SET_POINT_03 + 1,
        LOAD_PRESSURE_SET_POINT_05 = LOAD_PRESSURE_SET_POINT_04 + 1,
        LOAD_PRESSURE_SET_POINT_06 = LOAD_PRESSURE_SET_POINT_05 + 1,
        LOAD_VALVE_MAX_SPEED       = LOAD_PRESSURE_SET_POINT_06 + 1,
        LOAD_COMPLETED             = LOAD_VALVE_MAX_SPEED
    };
    enum eLearnRunState{
        LEARN_RUN_STATE_NOT_RUNNING = 0,
        LEARN_RUN_STATE_RUNNING     = 1,
    };

    enum eLearnDataSet{
        LEARN_DATASET_PRESENT     = 0,
        LEARN_DATASET_NOT_PRESENT = 1,
    };

    enum eLearnAbort{
        LEARN_ABORT_OK        = 0,
        LEARN_ABORT_USER      = 1,
        LEARN_ABORT_CTRL_UNIT = 2,
    };

    enum eLearnOpenPressure{
        LEARN_OPEN_PRESSURE_OK       = 0,
        LEARN_OPEN_PRESSURE_GAS_HIGH = 1,
        LEARN_OPEN_PRESSURE_NO_GAS   = 2,
    };

    enum eLearnClosePressure{
        LEARN_CLOSE_PRESSURE_OK      = 0,
        LEARN_CLOSE_PRESSURE_GAS_LOW = 1,
    };

    enum eLearnPressureRaising{
        LEARN_PRESSURE_RAISING_OK       = 0,
        LEARN_PRESSURE_RAISING_MISSING  = 1,
    };

    enum eLearnPressureStable{
        LEARN_PRESSURE_STABLE_OK       = 0,
        LEARN_PRESSURE_STABLE_UNSTABLE = 1,
    };

    enum eInterface{
        INTERFACE_LOGIC                      =  1,
        INTERFACE_RS232                      =  2,
        INTERFACE_RS232_WITH_ANALOGOUTPUT    =  3,
        INTERFACE_DEVICENET                  =  4,
        INTERFACE_ETHERNET                   =  6,
        INTERFACE_ETHERNET_WITH_ANALOGOUTPUT =  7,
        INTERFACE_RS485                      =  8,
        INTERFACE_RS485_WITH_ANALOGOUTPUT    =  9,
        INTERFACE_BUSMODULE                  = 10,
        INTERFACE_BUSMODULE_UNKNOW           = 11,
        INTERFACE_PROFIBUS                   = 12,
        INTERFACE_RS485_HV                   = 14,
        INTERFACE_RS485_HV_WITH_ANALOGOUTPUT = 15, // F
        INTERFACE_LOGIC_4_20mA               = 16, // G
        INTERFACE_LOGIC_4_20mA_SPECIAL       = 17, // H
        INTERFACE_CCLINK                     = 18, // I
        INTERFACE_ETHERCAT                   = 19, // J
    };
};

class ValveASyncWorker : public QObject
{
    Q_OBJECT
private:
    /* properties */
    bool mIsConnecting = false;
    bool mRetryConnect = false;
    qint64 mLastSuccMsec = 0;
    int  mFailCount = 0;

    /* member */
    QTimer          * mpTimer          = nullptr;
    ValveConnection   mConn            ;
    qint64            mMonitoringCycle = 20;
    qint64            mTimeout         = 100;
    bool              mIsSearching     = false;
    ValveRequestDto   mMonitoringDto   ;

signals:
    /* property changed signal */
    void signalEventChangedIsConnecting(bool value, bool retryConnect       );

    /* function signal */
    void signalResultConnect            (bool isSucc, QString connectionInfo);
    void signalResultReadyFirmwareUpdate(bool isSucc                        );
    void signalEventSearchedDevice      (QStringList devList                );
    void signalEventResponseData        (ValveResponseDto dto               );

public slots:
    /* slots for internal signal */
    void onStart()
    {
    }

    void onTimeout()
    {
        QString readData;
        qint64  delay = 0;

        if(mIsSearching)
        {
            QStringList devList = mConn.searchDevice("");
            emit signalEventSearchedDevice(devList);
        }

        if(mMonitoringDto.mpValveSProvider != nullptr)
            onCommandRequest(ValveRequestDto(mMonitoringDto));

        delay = mIsConnecting ? mMonitoringCycle : 1000; // khko add proc disconnect

        startTimer(delay);
    }

    void onCommandSetMonitoringCycle(qint64 monitoringCycle, ValveRequestDto monitoringDto)
    {
        qDebug() << "[ValveASyncWorker][onCommandSetMonitoringCycle]" << monitoringCycle;

        stopTimer();

        mpTimer = new QTimer;
        mpTimer->setSingleShot(true);
        connect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));

        mMonitoringCycle = monitoringCycle;
        mMonitoringDto = monitoringDto;

        startTimer(mMonitoringCycle);
    }

    void onCommandSearch()
    {
        qDebug() << "[ValveASyncWorker][onCommandSearch]";
        mIsSearching = true;
    }

    void onCommandSearchStop()
    {
        qDebug() << "[ValveASyncWorker][onCommandSearchStop]";
        mIsSearching = false;
    }

    void onCommandConnect(int type, QString devAddr)
    {
        qDebug() << "[ValveASyncWorker][onCommandConnect]type = " <<type<< ", devAddr=" << devAddr;

        setIsConnecting(false, false);// khko add proc disconnect

        if(mConn.connectValve((ValveConnEnumDef::eConnectType)type, devAddr))
        {
            mFailCount = 0;
            setIsConnecting(true, false); // khko add proc disconnect
            emit signalResultConnect(true, mConn.getConnectionInfo());
        }
        else
        {
            emit signalResultConnect(false, mConn.getConnectionInfo());
        }
    }

    void onCommandReConnect()
    {
        qDebug() << "[ValveASyncWorker][onCommandReConnect]";

        setIsConnecting(false, false);// khko add proc disconnect

        if(mConn.reConnectValve())
        {
            setIsConnecting(true, false);// khko add proc disconnect
            emit signalResultConnect(true, mConn.getConnectionInfo());
        }
        else
        {
            emit signalResultConnect(false, mConn.getConnectionInfo());
        }
    }

    void onCommandReadyFirmwareUpdate()
    {
        IValve::eValveError err = IValve::NoError;
        QString response;
        bool isSucc;

        qDebug() << "[" << Q_FUNC_INFO << "]";

        isSucc = mConn.sendCmd(REQ_READY_DFU, "", REQ_READY_DFU, RES_READY_DFU_DATA_LEN, response, mTimeout, &err);

        if(!isSucc && err != IValve::ResourceError)
        {
            isSucc = mConn.sendCmd(REQ_READY_DFU, "", REQ_READY_DFU, RES_READY_DFU_DATA_LEN, response, mTimeout, &err);
        }

        if(isSucc)
        {
            mConn.disconnectValve();
            emit signalResultReadyFirmwareUpdate(true);
            setIsConnecting(false, false);
            return;
        }

        if(!isSucc && err == IValve::ResourceError)
        {
            mConn.disconnectValve();
            emit signalResultReadyFirmwareUpdate(false);
            setIsConnecting(false, false);
            return;
        }

        emit signalResultReadyFirmwareUpdate(false);

        setIsConnecting(false, true);
    }

    void onCommandRequest(ValveRequestDto  dto)
    {
        IValve::eValveError err = IValve::NoError;
        QString response;
        ValveResponseDto resDto;
        bool retryConnect = true;
        bool netSucc = true;

        resDto.mReqDto = dto;
        resDto.mIsParsed = false;
        resDto.mIsSucc = mConn.sendCmd(dto.mReqCommand,"",dto.mCheckString, dto.mCheckLen, response, mTimeout, &err);
        resDto.mIsNetworkErr = !resDto.mIsSucc;

        if(mConn.IsConnected() == false)
        {
            retryConnect = false;
        }
        else if(!resDto.mIsSucc && err != IValve::ResourceError && err != IValve::WriteError)
        {
            resDto.mIsSucc = mConn.sendCmd(dto.mReqCommand,"",dto.mCheckString, dto.mCheckLen, response, mTimeout, &err);
            resDto.mIsNetworkErr = !resDto.mIsSucc;
        }
        else if(!resDto.mIsSucc && (err == IValve::ResourceError || err == IValve::WriteError))
        {
            retryConnect = false;
            mConn.disconnectValve();
        }

        netSucc = resDto.mIsSucc;
        resDto.mResDateTime = QDateTime::currentDateTime();

        if(resDto.mIsSucc)
        {
            resDto.mResData = response;

            if(resDto.mResData.startsWith("E:"))
            {
                resDto.mIsSucc = false;
                resDto.mErrMsg = resDto.mResData;
            }
        }
        else
        {
            resDto.mErrMsg = "protocol error";
        }

        emit signalEventResponseData(resDto);

        if(netSucc || (netSucc == false && (resDto.mResDateTime.currentMSecsSinceEpoch() - mLastSuccMsec > 3000)) || (err == IValve::ResourceError))
            setIsConnecting(netSucc, retryConnect);

        if(netSucc)
            mLastSuccMsec = resDto.mResDateTime.currentMSecsSinceEpoch();
    }

public:
    explicit ValveASyncWorker(QObject *parent = nullptr):QObject(parent)
    {
        qDebug() << "[ValveASyncWorker]Create";
    }
    ~ValveASyncWorker()
    {
        qDebug() << "[ValveASyncWorker]Destruction";
        stopTimer();
    }

private:
    qint64 mLastSentMSec; // khko_debug

    /* get() set() for properties */
    bool getIsConnecting(          ){ return mIsConnecting; }
    void setIsConnecting(bool value, bool retryConnect)
    {
        if(value == mIsConnecting && mRetryConnect == retryConnect)
            return;

        mIsConnecting = value;
        mRetryConnect = retryConnect;

        emit signalEventChangedIsConnecting(value, retryConnect);
    }

    /* function for internal process*/
    void startTimer(qint64 monitoringCycle)
    {
        mpTimer->stop();
        mpTimer->start(monitoringCycle);
    }

    void stopTimer()
    {
        if(mpTimer != nullptr)
        {
            disconnect(mpTimer, SIGNAL(timeout()), this, SLOT(onTimeout()));
            mpTimer->stop();
            mpTimer->deleteLater();
            mpTimer = nullptr;
        }
    }
};


#endif // SERIALASYNCWORKER_H
