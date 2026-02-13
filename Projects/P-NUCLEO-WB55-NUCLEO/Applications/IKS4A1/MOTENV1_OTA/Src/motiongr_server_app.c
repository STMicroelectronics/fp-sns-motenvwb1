/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motiongr_server_app.c
  * @brief   Handle SW/Gesture Recognition Service/Char
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
#include "motiongr_server_app.h"
#include "remap_conf.h"

#include "motion_gr_manager.h"

/* Private defines -----------------------------------------------------------*/
#define VALUE_LEN_GR    (2+1)

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief  SW/Gesture Recognition Service/Char Context structure definition
  */
typedef struct
{
  uint8_t  NotificationStatus;
  MGR_output_t GestureRecCode;

} MOTIONGR_Server_App_Context_t;

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

PLACE_IN_SECTION("BLE_APP_CONTEXT") static MOTIONGR_Server_App_Context_t MOTIONGR_Server_App_Context;

/* Global variables ----------------------------------------------------------*/
extern uint8_t a_ManufData[14];

/* Private function prototypes -----------------------------------------------*/
static void ComputeMotionGR(void);
static void GestureRec_Update(MGR_output_t GestureRecCode);

/* Functions Definition ------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
  * @brief  Init the SW/Gesture Recognition Service/Char Context
  *         and update the ADV data accordingly
  * @param  None
  * @retval None
  */
void MOTIONGR_Context_Init(void)
{
  /* CarryPosition API initialization function */
  MotionGR_manager_init();

  /* Update BLE ADV field (GestureRec) */
  a_ManufData[7] |= 0x02; /* GestureRec */

  MOTIONGR_Set_Notification_Status(0);
  MOTIONGR_Server_App_Context.GestureRecCode = MGR_NOGESTURE;
  GestureRec_Update(MOTIONGR_Server_App_Context.GestureRecCode);
}

/**
  * @brief  Set the notification status (enabled/disabled) and full scale
  * @param  status The new notification status
  * @retval None
  */
void MOTIONGR_Set_Notification_Status(uint8_t status)
{
  MOTIONGR_Server_App_Context.NotificationStatus = status;
  if (status == 1)
  {
    /* Set accelerometer:
     *   - FS   = <-4g, 4g>
     */
    (void)MOTION_SENSOR_SET_FULL_SCALE(ACCELERO_INSTANCE, MOTION_ACCELERO, 4);
  }
  else
  {
    /* Set accelerometer:
     *   - FS   = <-2g, 2g>
     */
    (void)MOTION_SENSOR_SET_FULL_SCALE(ACCELERO_INSTANCE, MOTION_ACCELERO, 2);
  }
}

/**
  * @brief  Send a notification for Gesture Recognition events
  * @param  None
  * @retval None
  */
void MOTIONGR_Send_Notification_Task(void)
{
  ComputeMotionGR();
}

/**
  * @brief  Update the Gesture Recognition char value
  * @param  None
  * @retval None
  */
void MOTIONGR_GestureRec_Update(void)
{
  GestureRec_Update(MOTIONGR_Server_App_Context.GestureRecCode);
}

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Run the GR Manager and update the Gesture Recognition char value
  * @param  None
  * @retval None
  */
static void ComputeMotionGR(void)
{
  MOTION_SENSOR_AXES_T ACC_Value;
  MGR_input_t data_in = {.AccX = 0.0f, .AccY = 0.0f, .AccZ = 0.0f};
  static MGR_output_t GestureRecCodePrev = MGR_NOGESTURE;

  /* Read the Acc values */
  (void)MOTION_SENSOR_GET_AXES(ACCELERO_INSTANCE, MOTION_ACCELERO, &ACC_Value);

  /* Convert acceleration from [mg] to [g] */
  data_in.AccX = (float)ACC_Value.x * FROM_MG_TO_G;
  data_in.AccY = (float)ACC_Value.y * FROM_MG_TO_G;
  data_in.AccZ = (float)ACC_Value.z * FROM_MG_TO_G;

  MotionGR_manager_run(&data_in, &MOTIONGR_Server_App_Context.GestureRecCode);

  if (GestureRecCodePrev != MOTIONGR_Server_App_Context.GestureRecCode)
  {
    GestureRecCodePrev = MOTIONGR_Server_App_Context.GestureRecCode;
    if (MOTIONGR_Server_App_Context.NotificationStatus)
    {
      GestureRec_Update(MOTIONGR_Server_App_Context.GestureRecCode);
    }
    else
    {
#if (CFG_DEBUG_APP_TRACE != 0)
      APP_DBG_MSG("-- MOTIONGR APPLICATION SERVER : CAN'T INFORM CLIENT - NOTIFICATION DISABLED\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
    }
  }
}

/**
  * @brief  Update the Gesture Recognition char value
  * @param  GestureRecCode Gesture Recognized
  * @retval None
  */
static void GestureRec_Update(MGR_output_t GestureRecCode)
{
  uint8_t value[VALUE_LEN_GR];

  /* Timestamp */
  STORE_LE_16(value, (HAL_GetTick() >> 3));
  value[2] = GestureRecCode;

#if (CFG_DEBUG_APP_TRACE != 0)
  APP_DBG_MSG("-- MOTIONGR APPLICATION SERVER : NOTIFY CLIENT WITH NEW PARAMETER VALUE \n ");
  APP_DBG_MSG(" \n\r");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  MOTENV_STM_App_Update_Char(GESTURE_REC_CHAR_UUID, VALUE_LEN_GR, (uint8_t *)&value);

  return;
}
