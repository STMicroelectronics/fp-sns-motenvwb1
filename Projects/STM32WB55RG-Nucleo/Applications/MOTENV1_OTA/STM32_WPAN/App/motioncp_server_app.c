/**
  ******************************************************************************
  * @file    motioncp_server_app.c
  * @brief   Handle SW/Carry Position Service/Char
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "app_common.h"
#include "ble.h"
#include "dbg_trace.h"

#include "motenv_server_app.h"
#include "motioncp_server_app.h"
#include "iks01a3_motion_sensors.h"

#include "MotionCP_Manager.h"

/* Private defines -----------------------------------------------------------*/
#define VALUE_LEN_CP    (2+1)

/* Private typedef -----------------------------------------------------------*/
/**
 * @brief  SW/Activity Recognition Service/Char Context structure definition
 */
typedef struct
{
  uint8_t  NotificationStatus;
  MCP_output_t CarryPositionCode;

} MOTIONCP_Server_App_Context_t;

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

PLACE_IN_SECTION("BLE_APP_CONTEXT") static MOTIONCP_Server_App_Context_t MOTIONCP_Server_App_Context;

/* Global variables ----------------------------------------------------------*/
extern uint8_t a_ManufData[14];

/* Private function prototypes -----------------------------------------------*/
static void ComputeMotionCP(void);
static void CarryPosition_Update(MCP_output_t CarryPositionCode);

/* Functions Definition ------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/

/**
 * @brief  Init the SW/Carry Position Service/Char Context
 *         and update the ADV data accordingly
 * @param  None
 * @retval None
 */
void MOTIONCP_Context_Init(void)
{
  /* CarryPosition API initialization function */
  MotionCP_manager_init();

  /* Update BLE ADV field (CarryPosition) */
  a_ManufData[7] |= 0x08; /* CarryPosition */

  MOTIONCP_Set_Notification_Status(0);
  MOTIONCP_Server_App_Context.CarryPositionCode = MCP_UNKNOWN;
  CarryPosition_Update(MOTIONCP_Server_App_Context.CarryPositionCode);
}

/**
 * @brief  Set the notification status (enabled/disabled) and full scale
 * @param  status The new notification status
 * @retval None
 */
void MOTIONCP_Set_Notification_Status(uint8_t status)
{
  MOTIONCP_Server_App_Context.NotificationStatus = status;
  if(status == 1)
  {
    /* Set accelerometer:
     *   - FS   = <-4g, 4g>
     */
    (void)IKS01A3_MOTION_SENSOR_SetFullScale(IKS01A3_LSM6DSO_0, MOTION_ACCELERO, 4);
  }
  else
  {
    /* Set accelerometer:
     *   - FS   = <-2g, 2g>
     */
    (void)IKS01A3_MOTION_SENSOR_SetFullScale(IKS01A3_LSM6DSO_0, MOTION_ACCELERO, 2);
  }
}

/**
 * @brief  Send a notification for Carry Position events
 * @param  None
 * @retval None
 */
void MOTIONCP_Send_Notification_Task(void)
{
  ComputeMotionCP();
}

/**
 * @brief  Update the Carry Position char value
 * @param  None
 * @retval None
 */
void MOTIONCP_CarryPosition_Update(void)
{
  CarryPosition_Update(MOTIONCP_Server_App_Context.CarryPositionCode);
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Run the CP Manager and update the Carry Position char value
 * @param  None
 * @retval None
 */
static void ComputeMotionCP(void)
{
  IKS01A3_MOTION_SENSOR_Axes_t ACC_Value;
  MCP_input_t data_in = {.AccX = 0.0f, .AccY = 0.0f, .AccZ = 0.0f};
  static MCP_output_t CarryPositionCodePrev = MCP_UNKNOWN;

  /* Read the Acc values */
  (void)IKS01A3_MOTION_SENSOR_GetAxes(IKS01A3_LSM6DSO_0, MOTION_ACCELERO, &ACC_Value);

  /* Convert acceleration from [mg] to [g] */
  data_in.AccX = (float)ACC_Value.x * FROM_MG_TO_G;
  data_in.AccY = (float)ACC_Value.y * FROM_MG_TO_G;
  data_in.AccZ = (float)ACC_Value.z * FROM_MG_TO_G;

  MotionCP_manager_run(&data_in, &MOTIONCP_Server_App_Context.CarryPositionCode);

  if(CarryPositionCodePrev != MOTIONCP_Server_App_Context.CarryPositionCode)
  {
    CarryPositionCodePrev = MOTIONCP_Server_App_Context.CarryPositionCode;
    if(MOTIONCP_Server_App_Context.NotificationStatus)
    {
      CarryPosition_Update(MOTIONCP_Server_App_Context.CarryPositionCode);
    }
    else
    {
#if(CFG_DEBUG_APP_TRACE != 0)
      APP_DBG_MSG("-- MOTIONCP APPLICATION SERVER : CAN'T INFORM CLIENT - NOTIFICATION DISABLED\n ");
#endif
    }
  }
}

/**
 * @brief  Update the Carry Position char value
 * @param  CarryPositionCode Carry Position Recognized
 * @retval None
 */
static void CarryPosition_Update(MCP_output_t CarryPositionCode)
{
  uint8_t value[VALUE_LEN_CP];

  /* Timestamp */
  STORE_LE_16(value, (HAL_GetTick()>>3));
  value[2] = CarryPositionCode;

#if(CFG_DEBUG_APP_TRACE != 0)
  APP_DBG_MSG("-- MOTIONCP APPLICATION SERVER : NOTIFY CLIENT WITH NEW PARAMETER VALUE \n ");
  APP_DBG_MSG(" \n\r");
#endif
  MOTENV_STM_App_Update_Char(CARRY_POSITION_CHAR_UUID, VALUE_LEN_CP, (uint8_t *)&value);

  return;
}

