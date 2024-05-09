/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    env_server_app.c
  * @brief   Handle HW/Environmental Service/Char
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

/* Includes ------------------------------------------------------------------*/
#include "app_common.h"
#include "ble.h"
#include "dbg_trace.h"

#include "motenv_server_app.h"
#include "env_server_app.h"
#include "motionfx_server_app.h"
#include "config_server_app.h"
#include "motenvwb1_app_conf.h"

/* Private defines -----------------------------------------------------------*/
#define PRESSURE_BYTES          (4)
#define HUMIDITY_BYTES          (2)
#define TEMPERATURE_BYTES       (2)

#define VALUE_LEN_ENV           (2+PRESSURE_BYTES+HUMIDITY_BYTES+TEMPERATURE_BYTES/*Temp2*/+TEMPERATURE_BYTES/*Temp1*/)

/* Private typedef -----------------------------------------------------------*/

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/**
  * @brief  Environmental Capabilities
  */
extern ENV_Server_App_Context_t ENV_Server_App_Context;

/* Global variables ----------------------------------------------------------*/
extern uint8_t a_ManufData[14];

/* Private function prototypes -----------------------------------------------*/
static void EnvSensor_GetCaps(void);

/* Functions Definition ------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Init the HW/Environmental Service/Char Context
  * @param  None
  * @retval None
  */
void ENV_Context_Init(void)
{
  /* Env Sensors */

  ENV_Set_Notification_Status(0);

  /* Check Env caps */
  EnvSensor_GetCaps();
}

/**
  * @brief  Set the notification status (enabled/disabled)
  * @param  status The new notification status
  * @retval None
  */
void ENV_Set_Notification_Status(uint8_t status)
{
  ENV_Server_App_Context.NotificationStatus = status;
}

/**
  * @brief  Send a notification for Environmental char
  * @param  None
  * @retval None
  */
void ENV_Send_Notification_Task(void)
{
  /* Notifications of Compass Calibration status */
  if (CONFIG_Get_FirstConnection_Config() == 1)
  {
    CONFIG_Send_Notification(FEATURE_MASK_SENSORFUSION_SHORT, W2ST_COMMAND_CAL_STATUS,
                             MOTIONFX_Get_MagCalStatus() ? 100 : 0);
    CONFIG_Send_Notification(FEATURE_MASK_ECOMPASS, W2ST_COMMAND_CAL_STATUS, MOTIONFX_Get_MagCalStatus() ? 100 : 0);
    CONFIG_Set_FirstConnection_Config(0);
  }

  if (ENV_Server_App_Context.NotificationStatus)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    /*    APP_DBG_MSG("-- ENV APPLICATION SERVER : NOTIFY CLIENT WITH NEW ENV PARAMETER VALUE \n "); */
    /*    APP_DBG_MSG(" \n\r"); */
#endif /* CFG_DEBUG_APP_TRACE != 0 */
    /* Read and update ENV values */
    ENV_Handle_Sensor();
    ENV_Update();
  }
  else
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- ENV APPLICATION SERVER : CAN'T INFORM CLIENT - NOTIFICATION DISABLED\n ");
#endif /* (CFG_DEBUG_APP_TRACE != 0) */
  }

  return;
}

/**
  * @brief  Update the Environmental char value
  * @param  None
  * @retval None
  */
void ENV_Update(void)
{
  uint8_t tempIndex = 0;
  uint8_t value[VALUE_LEN_ENV];
  uint8_t BuffPos = 2;

  /* Timestamp */
  STORE_LE_16(value, (HAL_GetTick() >> 3));

  if (ENV_Server_App_Context.hasPressure == 1)
  {
    STORE_LE_32(&value[BuffPos], ENV_Server_App_Context.PressureValue);
    BuffPos += PRESSURE_BYTES;
  }

  if (ENV_Server_App_Context.hasHumidity == 1)
  {
    STORE_LE_16(&value[BuffPos], ENV_Server_App_Context.HumidityValue);
    BuffPos += HUMIDITY_BYTES;
  }

  for (tempIndex = 0; tempIndex < ENV_Server_App_Context.hasTemperature; tempIndex++)
  {
    STORE_LE_16(&value[BuffPos], ENV_Server_App_Context.TemperatureValue[tempIndex]);
    BuffPos += TEMPERATURE_BYTES;
  }

  MOTENV_STM_App_Update_Char(ENV_CHAR_UUID, VALUE_LEN_ENV, (uint8_t *)&value);

  return;
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Check the Environmental active capabilities and set the ADV data accordingly
  * @param  None
  * @retval None
  */
static void EnvSensor_GetCaps(void)
{
  /* Update BLE ADV field (Env) */
  if (ENV_Server_App_Context.hasTemperature > 1)
  {
    a_ManufData[5] |= 0x05; /* Two Temperature values*/
  }
  else if (ENV_Server_App_Context.hasTemperature == 1)
  {
    a_ManufData[5] |= 0x04; /* One Temperature value*/
  }

  if (ENV_Server_App_Context.hasHumidity)
  {
    a_ManufData[5] |= 0x08; /* Humidity value */
  }

  if (ENV_Server_App_Context.hasPressure)
  {
    a_ManufData[5] |= 0x10; /* Pressure value*/
  }
}
