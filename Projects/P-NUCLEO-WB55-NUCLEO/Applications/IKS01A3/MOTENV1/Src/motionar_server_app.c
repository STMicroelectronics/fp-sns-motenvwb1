/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motionar_server_app.c
  * @brief   Handle SW/Activity Recognition Service/Char
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
#include "motionar_server_app.h"
#include "remap_conf.h"

#include "MotionAR_Manager.h"

/* Private defines -----------------------------------------------------------*/
#define MOTIONAR_ALGO_FREQ      16U               /* Algorithm frequency [Hz] */
#define MOTIONAR_ALGO_PERIOD    (1000U / MOTIONAR_ALGO_FREQ)  /* Algorithm period [ms] */

#define VALUE_LEN_AR    (2+1)

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief  SW/Activity Recognition Service/Char Context structure definition
  */
typedef struct
{
  uint8_t  NotificationStatus;
  volatile uint32_t TimeStamp;
  MAR_output_t ActivityCode;

} MOTIONAR_Server_App_Context_t;

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

PLACE_IN_SECTION("BLE_APP_CONTEXT") static MOTIONAR_Server_App_Context_t MOTIONAR_Server_App_Context;

/* Global variables ----------------------------------------------------------*/
extern uint8_t a_ManufData[14];

/* Private function prototypes -----------------------------------------------*/
static void ComputeMotionAR(void);
static void ActivityRec_Update(MAR_output_t ActivityCode);

/* Functions Definition ------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Init the SW/Activity Recognition Service/Char Context
  *         and update the ADV data accordingly
  * @param  None
  * @retval None
  */
void MOTIONAR_Context_Init(void)
{
  /* Activity Rec API initialization function */
  MotionAR_manager_init();

  /* Update BLE ADV field (ActivityRec) */
  a_ManufData[7] |= 0x10; /* ActivityRec */

  MOTIONAR_Server_App_Context.TimeStamp = 0;
  MOTIONAR_Set_Notification_Status(0);
  MOTIONAR_Server_App_Context.ActivityCode = MAR_NOACTIVITY;
  ActivityRec_Update(MOTIONAR_Server_App_Context.ActivityCode);
}

/**
  * @brief  Set the notification status (enabled/disabled) and full scale
  * @param  status The new notification status
  * @retval None
  */
void MOTIONAR_Set_Notification_Status(uint8_t status)
{
  MOTIONAR_Server_App_Context.NotificationStatus = status;
  if (status == 1)
  {
    /* Set accelerometer:
     *   - FS   = <-4g, 4g>
     */
    (void)MOTION_SENSOR_SetFullScale(ACCELERO_INSTANCE, MOTION_ACCELERO, 4);
  }
  else
  {
    /* Set accelerometer:
     *   - FS   = <-2g, 2g>
     */
    (void)MOTION_SENSOR_SetFullScale(ACCELERO_INSTANCE, MOTION_ACCELERO, 2);
  }
}

/**
  * @brief  Send a notification for Activity Recognition events
  * @param  None
  * @retval None
  */
void MOTIONAR_Send_Notification_Task(void)
{
  ComputeMotionAR();
  MOTIONAR_Server_App_Context.TimeStamp += MOTIONAR_ALGO_PERIOD;
}

/**
  * @brief  Update the Activity Recognition char value
  * @param  None
  * @retval None
  */
void MOTIONAR_ActivityRec_Update(void)
{
  ActivityRec_Update(MOTIONAR_Server_App_Context.ActivityCode);
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Run the AR Manager and update the Activity Recognition char value
  * @param  None
  * @retval None
  */
static void ComputeMotionAR(void)
{
  MOTION_SENSOR_Axes_t ACC_Value;
  MAR_input_t data_in = {.acc_x = 0.0f, .acc_y = 0.0f, .acc_z = 0.0f};
  static MAR_output_t ActivityCodePrev = MAR_NOACTIVITY;

  /* Read the Acc values */
  (void)MOTION_SENSOR_GetAxes(ACCELERO_INSTANCE, MOTION_ACCELERO, &ACC_Value);

  /* Convert acceleration from [mg] to [g] */
  data_in.acc_x = (float)ACC_Value.x * FROM_MG_TO_G;
  data_in.acc_y = (float)ACC_Value.y * FROM_MG_TO_G;
  data_in.acc_z = (float)ACC_Value.z * FROM_MG_TO_G;

  MotionAR_manager_run(&data_in, &MOTIONAR_Server_App_Context.ActivityCode, MOTIONAR_Server_App_Context.TimeStamp);

  if (ActivityCodePrev != MOTIONAR_Server_App_Context.ActivityCode)
  {
    ActivityCodePrev = MOTIONAR_Server_App_Context.ActivityCode;
    if (MOTIONAR_Server_App_Context.NotificationStatus)
    {
      ActivityRec_Update(MOTIONAR_Server_App_Context.ActivityCode);
    }
    else
    {
#if (CFG_DEBUG_APP_TRACE != 0)
      APP_DBG_MSG("-- MOTIONAR APPLICATION SERVER : CAN'T INFORM CLIENT - NOTIFICATION DISABLED\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
    }
  }
}

/**
  * @brief  Update the Activity Recognition char value
  * @param  ActivityCode Activity Recognized
  * @retval None
  */
static void ActivityRec_Update(MAR_output_t ActivityCode)
{
  uint8_t value[VALUE_LEN_AR];

  /* Timestamp */
  STORE_LE_16(value, (HAL_GetTick() >> 3));
  value[2] = ActivityCode;

#if (CFG_DEBUG_APP_TRACE != 0)
  APP_DBG_MSG("-- MOTIONAR APPLICATION SERVER : NOTIFY CLIENT WITH NEW PARAMETER VALUE \n ");
  APP_DBG_MSG(" \n\r");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  MOTENV_STM_App_Update_Char(ACTIVITY_REC_CHAR_UUID, VALUE_LEN_AR, (uint8_t *)&value);

  return;
}
