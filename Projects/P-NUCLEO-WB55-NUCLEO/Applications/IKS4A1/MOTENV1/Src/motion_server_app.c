/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motion_server_app.c
  * @brief   Handle HW/Motion (Acc/Gyro/Mag) Service/Char
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_common.h"
#include "ble.h"
#include "dbg_trace.h"

#include "motenv_server_app.h"
#include "motion_server_app.h"
#include "motionfx_server_app.h"

#include "motenvwb1_app_conf.h"

/* Private defines -----------------------------------------------------------*/
#define ACC_BYTES               (2)
#define GYRO_BYTES              (2)
#define MAG_BYTES               (2)

#define VALUE_LEN_MOTION        (2+3*ACC_BYTES+3*GYRO_BYTES+3*MAG_BYTES)

/* Private typedef -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

extern MOTION_Server_App_Context_t MOTION_Server_App_Context;

/* Global variables ----------------------------------------------------------*/
extern uint8_t a_ManufData[14];

/* Private function prototypes -----------------------------------------------*/

static void MOTION_GetCaps(void);

/* Functions Definition ------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Init the HW/Motion Service/Char Context
  * @param  None
  * @retval None
  */
void MOTION_Context_Init(void)
{
  MOTION_Set_Notification_Status(0);

  /* Check Motion caps */
  MOTION_GetCaps();
}

/**
  * @brief  Set the notification status (enabled/disabled)
  * @param  status The new notification status
  * @retval None
  */
void MOTION_Set_Notification_Status(uint8_t status)
{
  MOTION_Server_App_Context.NotificationStatus = status;
}

/**
  * @brief  Send a notification for Motion (Acc/Gyro/Mag) char
  * @param  None
  * @retval None
  */
void MOTION_Send_Notification_Task(void)
{
  uint8_t value[VALUE_LEN_MOTION];

  MOTION_SENSOR_AXES_T AXIS;

  /* Read Motion values */
  MOTION_Handle_Sensor();

  /* Timestamp */
  STORE_LE_16(value, (HAL_GetTick() >> 3));

  if (MOTION_Server_App_Context.hasAcc == 1)
  {
    STORE_LE_16(value + 2, MOTION_Server_App_Context.acceleration.x);
    STORE_LE_16(value + 4, MOTION_Server_App_Context.acceleration.y);
    STORE_LE_16(value + 6, MOTION_Server_App_Context.acceleration.z);
  }

  if (MOTION_Server_App_Context.hasGyro == 1)
  {
    MOTION_Server_App_Context.angular_velocity.x /= 100;
    MOTION_Server_App_Context.angular_velocity.y /= 100;
    MOTION_Server_App_Context.angular_velocity.z /= 100;

    STORE_LE_16(value + 8, MOTION_Server_App_Context.angular_velocity.x);
    STORE_LE_16(value + 10, MOTION_Server_App_Context.angular_velocity.y);
    STORE_LE_16(value + 12, MOTION_Server_App_Context.angular_velocity.z);
  }

  if (MOTION_Server_App_Context.hasMag == 1)
  {
    AXIS.x = MOTION_Server_App_Context.magnetic_field.x - MOTIONFX_Get_MAG_Offset()->x;
    AXIS.y = MOTION_Server_App_Context.magnetic_field.y - MOTIONFX_Get_MAG_Offset()->y;
    AXIS.z = MOTION_Server_App_Context.magnetic_field.z - MOTIONFX_Get_MAG_Offset()->z;

    STORE_LE_16(value + 14, AXIS.x);
    STORE_LE_16(value + 16, AXIS.y);
    STORE_LE_16(value + 18, AXIS.z);
  }

  if (MOTION_Server_App_Context.NotificationStatus)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION APPLICATION SERVER : NOTIFY CLIENT WITH NEW MOTION PARAMETER VALUE \n ");
    APP_DBG_MSG(" \n\r");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
    MOTENV_STM_App_Update_Char(MOTION_CHAR_UUID, VALUE_LEN_MOTION, (uint8_t *)&value);
  }
  else
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION APPLICATION SERVER : CAN'T INFORM CLIENT - NOTIFICATION DISABLED\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }

  return;
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Check the Motion active capabilities and set the ADV data accordingly
  * @param  None
  * @retval None
  */
static void MOTION_GetCaps(void)
{
  /* Update BLE ADV field (Motion) */
  if (MOTION_Server_App_Context.hasAcc)
  {
    a_ManufData[5] |= 0x80; /* Acc value */
    a_ManufData[6] |= 0x04; /* Extended Acc events */
  }
  if (MOTION_Server_App_Context.hasGyro)
  {
    a_ManufData[5] |= 0x40; /* Gyro value */
  }
  if (MOTION_Server_App_Context.hasMag)
  {
    a_ManufData[5] |= 0x20; /* Mag value */
  }
}
