/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motenvwb1_app_conf.h
  * @author  System Research & Applications Team - Catania Lab.
  * @brief   Bluetooth support
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE END Header */

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
  * if CFG_PRIVACY equals PRIVACY_DISABLED, CFG_BLE_ADDRESS_TYPE has 2 allowed values:
  * GAP_PUBLIC_ADDR or GAP_STATIC_RANDOM_ADDR
  * if CFG_PRIVACY equals PRIVACY_ENABLED, CFG_BLE_ADDRESS_TYPE has 2 allowed values:
  * GAP_RESOLVABLE_PRIVATE_ADDR or GAP_NON_RESOLVABLE_PRIVATE_ADDR
  */
#define CFG_BLE_ADDRESS_TYPE              GAP_PUBLIC_ADDR

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

/**< Add in that list all tasks that may send a ACI/HCI command */
typedef enum
{
  MOTENVWB1_CFG_TASK_ADV_CANCEL_ID,
#if (MOTENVWB1_L2CAP_REQUEST_NEW_CONN_PARAM != 0 )
  CFG_TASK_CONN_UPDATE_REG_ID,
#endif /* MOTENVWB1_L2CAP_REQUEST_NEW_CONN_PARAM != 0 */
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
  MOTENVWB1_CFG_LAST_TASK_ID_WITH_HCICMD, /**< Shall be LAST in the list */
} MOTENVWB1_CFG_Task_Id_With_HCI_Cmd_t;

#ifdef __cplusplus
}
#endif
#endif /*MOTENVWB1_APP_CONF_H*/

/**
  * @}
  */
