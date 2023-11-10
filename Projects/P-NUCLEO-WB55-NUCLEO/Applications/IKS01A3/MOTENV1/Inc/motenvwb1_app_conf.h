/**
  ******************************************************************************
  * @file    motenvwb1_app_conf.h
  * @author  System Research & Applications Team - Catania Lab.
  * @brief   Bluetooth support
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MOTENVWB1_APP_CONF_H
#define MOTENVWB1_APP_CONF_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "motenv_stm_conf.h"
/* Private typedef -----------------------------------------------------------*/

/* Exported Defines ----------------------------------------------------------*/
#define MCR_BLUEMS_F2I_1D(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (int32_t)((in-out_int)*10);};
#define MCR_BLUEMS_F2I_2D(in, out_int, out_dec) {out_int = (int32_t)in; out_dec= (int32_t)((in-out_int)*100);};

extern EXTI_HandleTypeDef                hexti10;
#define H_EXTI_LINE_MEMS                 EXTI_LINE_10
#define H_EXTI_10                        hexti10
#define H_EXTI_MEMS                      H_EXTI_10
#define MEMS_INT_PIN                     GPIO_PIN_10
#define MEMS_INT_PORT                    GPIOC

/*Set Tap Threshold*/
#define TAP_THRESHOLD                    0x10

/*Set Free Fall Threshold*/
#define FF_THRESHOLD                     LSM6DSO_FF_TSH_250mg

/*Set interrupt pin*/
#define MOTION_SENSOR_INT_PIN            IKS01A3_MOTION_SENSOR_INT1_PIN

#define CFG_LED_SUPPORTED                1
#define CFG_BUTTON_SUPPORTED             1

/* Exported Functions --------------------------------------------------------*/
void ENV_Handle_Sensor(void);
void MOTION_Handle_Sensor(void);

/**< generic parameters ******************************************************/

/**
 * Define Tx Power
 */
#define CFG_TX_POWER                      (0x18) /* -0.15dBm */

/**
 * Define Advertising parameters
 */
#define CFG_ADV_BD_ADDRESS                (0x7257acd87a6c)

/**
 * Define BD_ADDR type: define proper address. Can only be GAP_PUBLIC_ADDR (0x00) or GAP_STATIC_RANDOM_ADDR (0x01)
 */
#define CFG_IDENTITY_ADDRESS              GAP_PUBLIC_ADDR

/**
 * Define privacy: PRIVACY_DISABLED or PRIVACY_ENABLED
 */
#define CFG_PRIVACY                       PRIVACY_DISABLED

/**
 * Define BLE Address Type
 * Bluetooth address types defined in ble_legacy.h
 * if CFG_PRIVACY equals PRIVACY_DISABLED, CFG_BLE_ADDRESS_TYPE has 2 allowed values: GAP_PUBLIC_ADDR or GAP_STATIC_RANDOM_ADDR
 * if CFG_PRIVACY equals PRIVACY_ENABLED, CFG_BLE_ADDRESS_TYPE has 2 allowed values: GAP_RESOLVABLE_PRIVATE_ADDR or GAP_NON_RESOLVABLE_PRIVATE_ADDR
 */
#define CFG_BLE_ADDRESS_TYPE              GAP_PUBLIC_ADDR

#define CFG_FAST_CONN_ADV_INTERVAL_MIN    (0x80)      /**< 80ms */
#define CFG_FAST_CONN_ADV_INTERVAL_MAX    (0xa0)      /**< 100ms */
#define CFG_LP_CONN_ADV_INTERVAL_MIN      (0x640)     /**< 1s */
#define CFG_LP_CONN_ADV_INTERVAL_MAX      (0xfa0)     /**< 2.5s */

/**
 * Define IO Authentication
 */
#define CFG_BONDING_MODE                 (1)
#define CFG_FIXED_PIN                    (111111)
#define CFG_USED_FIXED_PIN               (0)
#define CFG_ENCRYPTION_KEY_SIZE_MAX      (16)
#define CFG_ENCRYPTION_KEY_SIZE_MIN      (8)

/**
 * Define IO capabilities
 */
#define CFG_IO_CAPABILITY_DISPLAY_ONLY        (0x00)
#define CFG_IO_CAPABILITY_DISPLAY_YES_NO      (0x01)
#define CFG_IO_CAPABILITY_KEYBOARD_ONLY       (0x02)
#define CFG_IO_CAPABILITY_NO_INPUT_NO_OUTPUT  (0x03)
#define CFG_IO_CAPABILITY_KEYBOARD_DISPLAY    (0x04)

#define CFG_IO_CAPABILITY                     CFG_IO_CAPABILITY_DISPLAY_YES_NO

/**
 * Define MITM modes
 */
#define CFG_MITM_PROTECTION_NOT_REQUIRED      (0x00)
#define CFG_MITM_PROTECTION_REQUIRED          (0x01)

#define CFG_MITM_PROTECTION                   CFG_MITM_PROTECTION_REQUIRED

/**
 * Define PHY
 */
#define ALL_PHYS_PREFERENCE                             0x00
#define RX_2M_PREFERRED                                 0x02
#define TX_2M_PREFERRED                                 0x02
#define TX_1M                                           0x01
#define TX_2M                                           0x02
#define RX_1M                                           0x01
#define RX_2M                                           0x02

/**
*   Identity root key used to derive LTK and CSRK
*/
#define CFG_BLE_IRK     {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0, 0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0}

/**
* Encryption root key used to derive LTK and CSRK
*/
#define CFG_BLE_ERK     {0xFE, 0xDC, 0xBA, 0x09, 0x87, 0x65, 0x43, 0x21, 0xFE, 0xDC, 0xBA, 0x09, 0x87, 0x65, 0x43, 0x21}

#define P2P_SERVER1    1    /*1 = Device is Peripherique*/
#define P2P_SERVER2    0
#define P2P_SERVER3    0
#define P2P_SERVER4    0
#define P2P_SERVER5    0
#define P2P_SERVER6    0

#define CFG_DEV_ID_P2P_SERVER1                  (0x83)
#define CFG_DEV_ID_P2P_SERVER2                  (0x84)
#define CFG_DEV_ID_P2P_SERVER3                  (0x87)
#define CFG_DEV_ID_P2P_SERVER4                  (0x88)
#define CFG_DEV_ID_P2P_SERVER5                  (0x89)
#define CFG_DEV_ID_P2P_SERVER6                  (0x8A)
#define CFG_DEV_ID_P2P_ROUTER                   (0x85)

#define  RADIO_ACTIVITY_EVENT   1          /* 1 for OOB Demo */

/**
* AD Element - Group B Feature
*/
/* LSB - First Byte */
#define CFG_FEATURE_THREAD_SWITCH               (0x40)

/* LSB - Second Byte */
#define CFG_FEATURE_OTA_REBOOT                  (0x20)

#define CONN_L(x) ((int)((x)/0.625f))
#define CONN_P(x) ((int)((x)/1.25f))

  /*  L2CAP Connection Update request parameters used for test only with smart Phone */
#define MOTENVWB1_L2CAP_REQUEST_NEW_CONN_PARAM             0

#define L2CAP_INTERVAL_MIN              CONN_P(1000) /* 1s */
#define L2CAP_INTERVAL_MAX              CONN_P(1000) /* 1s */
#define L2CAP_SLAVE_LATENCY             0x0000
#define L2CAP_TIMEOUT_MULTIPLIER        0x1F4

/* USER CODE BEGIN Specific_Parameters */

/* USER CODE END Specific_Parameters */

/******************************************************************************
 * BLE Stack
 ******************************************************************************/
/**
 * Maximum number of simultaneous connections that the device will support.
 * Valid values are from 1 to 8
 */
#define CFG_BLE_NUM_LINK            2

/**
 * Maximum number of Services that can be stored in the GATT database.
 * Note that the GAP and GATT services are automatically added so this parameter should be 2 plus the number of user services
 */
#define CFG_BLE_NUM_GATT_SERVICES   8

/**
 * Maximum number of Attributes
 * (i.e. the number of characteristic + the number of characteristic values + the number of descriptors, excluding the services)
 * that can be stored in the GATT database.
 * Note that certain characteristics and relative descriptors are added automatically during device initialization
 * so this parameters should be 9 plus the number of user Attributes
 */
#define CFG_BLE_NUM_GATT_ATTRIBUTES 68

/**
 * Maximum supported ATT_MTU size
 * This parameter is ignored by the CPU2 when CFG_BLE_OPTIONS has SHCI_C2_BLE_INIT_OPTIONS_LL_ONLY flag set
 */
#define CFG_BLE_MAX_ATT_MTU             (156)

/**
 * Size of the storage area for Attribute values
 *  This value depends on the number of attributes used by application. In particular the sum of the following quantities (in octets) should be made for each attribute:
 *  - attribute value length
 *  - 5, if UUID is 16 bit; 19, if UUID is 128 bit
 *  - 2, if server configuration descriptor is used
 *  - 2*DTM_NUM_LINK, if client configuration descriptor is used
 *  - 2, if extended properties is used
 *  The total amount of memory needed is the sum of the above quantities for each attribute.
 * This parameter is ignored by the CPU2 when CFG_BLE_OPTIONS has SHCI_C2_BLE_INIT_OPTIONS_LL_ONLY flag set
 */
#define CFG_BLE_ATT_VALUE_ARRAY_SIZE    (1344)

/**
 * Prepare Write List size in terms of number of packet
 * This parameter is ignored by the CPU2 when CFG_BLE_OPTIONS has SHCI_C2_BLE_INIT_OPTIONS_LL_ONLY flag set
 */
#define CFG_BLE_PREPARE_WRITE_LIST_SIZE         BLE_PREP_WRITE_X_ATT(CFG_BLE_MAX_ATT_MTU)

/**
 * Number of allocated memory blocks
 * This parameter is overwritten by the CPU2 with an hardcoded optimal value when the parameter CFG_BLE_OPTIONS has SHCI_C2_BLE_INIT_OPTIONS_LL_ONLY flag set
 */
#define CFG_BLE_MBLOCK_COUNT            (BLE_MBLOCKS_CALC(CFG_BLE_PREPARE_WRITE_LIST_SIZE, CFG_BLE_MAX_ATT_MTU, CFG_BLE_NUM_LINK))

/**
 * Enable or disable the Extended Packet length feature. Valid values are 0 or 1.
 */
#define CFG_BLE_DATA_LENGTH_EXTENSION   1

/**
 * Sleep clock accuracy in Slave mode (ppm value)
 */
#define CFG_BLE_SLAVE_SCA   500

/**
 * Sleep clock accuracy in Master mode
 * 0 : 251 ppm to 500 ppm
 * 1 : 151 ppm to 250 ppm
 * 2 : 101 ppm to 150 ppm
 * 3 : 76 ppm to 100 ppm
 * 4 : 51 ppm to 75 ppm
 * 5 : 31 ppm to 50 ppm
 * 6 : 21 ppm to 30 ppm
 * 7 : 0 ppm to 20 ppm
 */
#define CFG_BLE_MASTER_SCA   0

/**
 * LsSource
 * Some information for Low speed clock mapped in bits field
 * - bit 0:   1: Calibration for the RF system wakeup clock source   0: No calibration for the RF system wakeup clock source
 * - bit 1:   1: STM32WB5M Module device                             0: Other devices as STM32WBxx SOC, STM32WB1M module
 * - bit 2:   1: HSE/1024 Clock config                               0: LSE Clock config
 */
#if defined(STM32WB5Mxx)
  #define CFG_BLE_LS_SOURCE  (SHCI_C2_BLE_INIT_CFG_BLE_LS_NOCALIB | SHCI_C2_BLE_INIT_CFG_BLE_LS_MOD5MM_DEV | SHCI_C2_BLE_INIT_CFG_BLE_LS_CLK_LSE)
#else
  #define CFG_BLE_LS_SOURCE  (SHCI_C2_BLE_INIT_CFG_BLE_LS_NOCALIB | SHCI_C2_BLE_INIT_CFG_BLE_LS_OTHER_DEV | SHCI_C2_BLE_INIT_CFG_BLE_LS_CLK_LSE)
#endif

/**
 * Start up time of the high speed (16 or 32 MHz) crystal oscillator in units of 625/256 us (~2.44 us)
 */
#define CFG_BLE_HSE_STARTUP_TIME  0x148

/**
 * Maximum duration of the connection event when the device is in Slave mode in units of 625/256 us (~2.44 us)
 */
#define CFG_BLE_MAX_CONN_EVENT_LENGTH  (0xFFFFFFFF)

/**
 * Viterbi Mode
 * 1 : enabled
 * 0 : disabled
 */
#define CFG_BLE_VITERBI_MODE  1

/**
 * BLE stack Options flags to be configured with:
 * - SHCI_C2_BLE_INIT_OPTIONS_LL_ONLY
 * - SHCI_C2_BLE_INIT_OPTIONS_LL_HOST
 * - SHCI_C2_BLE_INIT_OPTIONS_NO_SVC_CHANGE_DESC
 * - SHCI_C2_BLE_INIT_OPTIONS_WITH_SVC_CHANGE_DESC
 * - SHCI_C2_BLE_INIT_OPTIONS_DEVICE_NAME_RO
 * - SHCI_C2_BLE_INIT_OPTIONS_DEVICE_NAME_RW
 * - SHCI_C2_BLE_INIT_OPTIONS_EXT_ADV
 * - SHCI_C2_BLE_INIT_OPTIONS_NO_EXT_ADV
 * - SHCI_C2_BLE_INIT_OPTIONS_CS_ALGO2
 * - SHCI_C2_BLE_INIT_OPTIONS_NO_CS_ALGO2
 * - SHCI_C2_BLE_INIT_OPTIONS_REDUC_GATTDB_NVM
 * - SHCI_C2_BLE_INIT_OPTIONS_FULL_GATTDB_NVM
 * - SHCI_C2_BLE_INIT_OPTIONS_GATT_CACHING_USED
 * - SHCI_C2_BLE_INIT_OPTIONS_GATT_CACHING_NOTUSED
 * - SHCI_C2_BLE_INIT_OPTIONS_POWER_CLASS_1
 * - SHCI_C2_BLE_INIT_OPTIONS_POWER_CLASS_2_3
 * which are used to set following configuration bits:
 * (bit 0): 1: LL only
 *          0: LL + host
 * (bit 1): 1: no service change desc.
 *          0: with service change desc.
 * (bit 2): 1: device name Read-Only
 *          0: device name R/W
 * (bit 3): 1: extended advertizing supported
 *          0: extended advertizing not supported
 * (bit 4): 1: CS Algo #2 supported
 *          0: CS Algo #2 not supported
 * (bit 5): 1: Reduced GATT database in NVM
 *          0: Full GATT database in NVM
 * (bit 6): 1: GATT caching is used
 *          0: GATT caching is not used
 * (bit 7): 1: LE Power Class 1
 *          0: LE Power Class 2-3
 * other bits: complete with Options_extension flag
 */
#define CFG_BLE_OPTIONS  (SHCI_C2_BLE_INIT_OPTIONS_LL_HOST | SHCI_C2_BLE_INIT_OPTIONS_WITH_SVC_CHANGE_DESC | SHCI_C2_BLE_INIT_OPTIONS_DEVICE_NAME_RW | SHCI_C2_BLE_INIT_OPTIONS_NO_EXT_ADV | SHCI_C2_BLE_INIT_OPTIONS_NO_CS_ALGO2 | SHCI_C2_BLE_INIT_OPTIONS_FULL_GATTDB_NVM | SHCI_C2_BLE_INIT_OPTIONS_GATT_CACHING_NOTUSED | SHCI_C2_BLE_INIT_OPTIONS_POWER_CLASS_2_3)

/**
 * BLE stack Options_extension flags to be configured with:
 * - SHCI_C2_BLE_INIT_OPTIONS_APPEARANCE_WRITABLE
 * - SHCI_C2_BLE_INIT_OPTIONS_APPEARANCE_READONLY
 * - SHCI_C2_BLE_INIT_OPTIONS_ENHANCED_ATT_SUPPORTED
 * - SHCI_C2_BLE_INIT_OPTIONS_ENHANCED_ATT_NOTSUPPORTED
 * which are used to set following configuration bits:
 * (bit 0): 1: appearance Writable
 *          0: appearance Read-Only
 * (bit 1): 1: Enhanced ATT supported
 *          0: Enhanced ATT not supported
 * other bits: reserved (shall be set to 0)
 */
#define CFG_BLE_OPTIONS_EXT  (SHCI_C2_BLE_INIT_OPTIONS_APPEARANCE_READONLY | SHCI_C2_BLE_INIT_OPTIONS_ENHANCED_ATT_NOTSUPPORTED)

#define CFG_BLE_MAX_COC_INITIATOR_NBR   (32)

#define CFG_BLE_MIN_TX_POWER            (-40)

#define CFG_BLE_MAX_TX_POWER            (6)

/**
 * BLE Rx model configuration flags to be configured with:
 * - SHCI_C2_BLE_INIT_RX_MODEL_AGC_RSSI_LEGACY
 * - SHCI_C2_BLE_INIT_RX_MODEL_AGC_RSSI_BLOCKER
 * which are used to set following configuration bits:
 * (bit 0): 1: agc_rssi model improved vs RF blockers
 *          0: Legacy agc_rssi model
 * other bits: reserved (shall be set to 0)
 */

#define CFG_BLE_RX_MODEL_CONFIG         (SHCI_C2_BLE_INIT_RX_MODEL_AGC_RSSI_LEGACY)

/* Maximum number of advertising sets.
 * Range: 1 .. 8 with limitation:
 * This parameter is linked to CFG_BLE_MAX_ADV_DATA_LEN such as both compliant with allocated Total memory computed with BLE_EXT_ADV_BUFFER_SIZE based
 * on Max Extended advertising configuration supported.
 * This parameter is considered by the CPU2 when CFG_BLE_OPTIONS has SHCI_C2_BLE_INIT_OPTIONS_EXT_ADV flag set
 */

#define CFG_BLE_MAX_ADV_SET_NBR     (3)

 /* Maximum advertising data length (in bytes)
 * Range: 31 .. 1650 with limitation:
 * This parameter is linked to CFG_BLE_MAX_ADV_SET_NBR such as both compliant with allocated Total memory computed with BLE_EXT_ADV_BUFFER_SIZE based
 * on Max Extended advertising configuration supported.
 * This parameter is considered by the CPU2 when CFG_BLE_OPTIONS has SHCI_C2_BLE_INIT_OPTIONS_EXT_ADV flag set
 */

#define CFG_BLE_MAX_ADV_DATA_LEN    (1650)

 /* RF TX Path Compensation Value (16-bit signed integer). Units: 0.1 dB.
  * Range: -1280 .. 1280
  */

#define CFG_BLE_TX_PATH_COMPENS    (0)

 /* RF RX Path Compensation Value (16-bit signed integer). Units: 0.1 dB.
  * Range: -1280 .. 1280
  */

#define CFG_BLE_RX_PATH_COMPENS    (0)

  /* BLE core version (16-bit signed integer).
   * - SHCI_C2_BLE_INIT_BLE_CORE_5_2
   * - SHCI_C2_BLE_INIT_BLE_CORE_5_3
   * which are used to set: 11(5.2), 12(5.3).
   */

#define CFG_BLE_CORE_VERSION   (SHCI_C2_BLE_INIT_BLE_CORE_5_3)

/**< Add in that list all tasks that may send a ACI/HCI command */
typedef enum
{
  MOTENVWB1_CFG_TASK_ADV_CANCEL_ID,
#if (MOTENVWB1_L2CAP_REQUEST_NEW_CONN_PARAM != 0 )
  CFG_TASK_CONN_UPDATE_REG_ID,
#endif
  MOTENVWB1_CFG_TASK_HCI_ASYNCH_EVT_ID,
  /* USER CODE BEGIN CFG_Task_Id_With_HCI_Cmd_t */
  CFG_TASK_SW1_BUTTON_PUSHED_ID,
  CFG_TASK_SW2_BUTTON_PUSHED_ID,
  CFG_TASK_SW3_BUTTON_PUSHED_ID,
  CFG_TASK_NOTIFY_ACC_GYRO_MAG_ID,
  CFG_TASK_NOTIFY_ENVIRONMENT_ID,
  CFG_TASK_NOTIFY_TOF_ID,
  CFG_TASK_NOTIFY_MOTIONFX_ID,
  CFG_TASK_NOTIFY_ECOMPASS_ID,
  CFG_TASK_NOTIFY_ACTIVITY_REC_ID,
  CFG_TASK_NOTIFY_CARRY_POSITION_ID,
  CFG_TASK_NOTIFY_GESTURE_REC_ID,
  CFG_TASK_NOTIFY_PEDOMETER_ID,
  CFG_TASK_NOTIFY_INTENSITY_DET_ID,
  CFG_TASK_HANDLE_MEMS_IT_ID,
  /* USER CODE END CFG_Task_Id_With_HCI_Cmd_t */
  MOTENVWB1_CFG_LAST_TASK_ID_WITH_HCICMD,                                               /**< Shall be LAST in the list */
} MOTENVWB1_CFG_Task_Id_With_HCI_Cmd_t;

#ifdef __cplusplus
}
#endif
#endif /*MOTENVWB1_APP_CONF_H*/

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/