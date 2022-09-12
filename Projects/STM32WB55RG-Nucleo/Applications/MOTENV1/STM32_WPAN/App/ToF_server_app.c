/**
  ******************************************************************************
  * @file    ToF_server_app.c
  * @brief   Handle HW/ToF/Char
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
#include "ToF_server_app.h"
#include "config_server_app.h"
   
uint8_t ToFMObjPresence= 0;

/* Private defines -----------------------------------------------------------*/
#define VALUE_LEN_TOF   (2+(2*4)+1)
   
/* Range distances where identify the human presence */
#define PRESENCE_MIN_DISTANCE_RANGE 300
#define PRESENCE_MAX_DISTANCE_RANGE 800

/* Private typedef -----------------------------------------------------------*/

/**
 * @brief  HW/ToF Service/Char Context structure definition
 */
typedef struct
{
  uint8_t  NotificationStatus;

  uint16_t ObjectsDistance[4];
  uint8_t HumanPresence;
  uint8_t hasBuiltInDevice;
} ToF_Server_App_Context_t;

/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/**
 * @brief  Environmental Capabilities
 */

PLACE_IN_SECTION("BLE_APP_CONTEXT") static ToF_Server_App_Context_t ToF_Server_App_Context;

/* Global variables ----------------------------------------------------------*/
extern uint8_t a_ManufData[14];

/* Private function prototypes -----------------------------------------------*/
static void ToF_Handle_Sensor(void);
static void ToF_Sensor_GetCaps(void);

/* Functions Definition ------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
 * @brief  Init the HW ToF
 * @param  None
 * @retval None
 */
void HW_ToF_Init(void)
{
  int32_t ret;
  
  ToF_BoardPresent= 0;
  ToF_Server_App_Context.hasBuiltInDevice= 0;
  
  ret = VL53L3A2_RANGING_SENSOR_Init(VL53L3A2_DEV_CENTER);
  
  if (ret == BSP_ERROR_NONE)
  {
    ToF_Sensor_GetCaps();
  }
  
  ToF_BoardPresent= ToF_Server_App_Context.hasBuiltInDevice;
}

/**
 * @brief  Init the ToF Service/Char Context
 * @param  None
 * @retval None
 */
void ToF_Context_Init(void)
{
  ToF_Server_App_Context.ObjectsDistance[0] =0;
  ToF_Server_App_Context.ObjectsDistance[1] =0;
  ToF_Server_App_Context.ObjectsDistance[2] =0;
  ToF_Server_App_Context.ObjectsDistance[3] =0;
  
  ToF_Set_Notification_Status(0);
}

/**
 * @brief  Set the notification status (enabled/disabled)
 * @param  status The new notification status
 * @retval None
 */
void ToF_Set_Notification_Status(uint8_t status)
{
  ToF_Server_App_Context.NotificationStatus = status;
}

/**
 * @brief  Send a notification for Environmental char
 * @param  None
 * @retval None
 */
void ToF_Send_Notification_Task(void)
{
  if(ToF_Server_App_Context.NotificationStatus)
  {
#if(CFG_DEBUG_APP_TRACE != 0)
//    APP_DBG_MSG("-- TOF APPLICATION SERVER : NOTIFY CLIENT WITH NEW TOF PARAMETER VALUE \n ");
//    APP_DBG_MSG(" \n\r");
#endif
    ToF_Update();
  }
  else
  {
#if(CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- TOF APPLICATION SERVER : CAN'T INFORM CLIENT - NOTIFICATION DISABLED\n ");
#endif
  }

  return;
}

/**
 * @brief  Update the Environmental char value
 * @param  None
 * @retval None
 */
void ToF_Update(void)
{
  int32_t Number;
  uint8_t value[VALUE_LEN_TOF];
  uint8_t BuffPos = 2;

  /* Read ToF values */
  ToF_Handle_Sensor();

  STORE_LE_16(value   ,(HAL_GetTick()>>3));

  if(ToFMObjPresence!=0U) {
    value[BuffPos] = ToF_Server_App_Context.HumanPresence;
    BuffPos++;
  } else {
    for(Number=0;Number<4;Number++)
    {
      if(ToF_Server_App_Context.ObjectsDistance[Number] != (uint16_t)0 ) {
        STORE_LE_16(value+BuffPos ,ToF_Server_App_Context.ObjectsDistance[Number]);
        BuffPos+=2U;
      }
    }
  }

  MOTENV_STM_App_Update_Char(TOF_CHAR_UUID, BuffPos, (uint8_t *)&value);

  return;
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Parse the values read by ToF sensors
 * @param  None
 * @retval None
 */
static void ToF_Handle_Sensor(void)
{
  uint32_t ret;
  uint8_t i, j;
  
  RANGING_SENSOR_Result_t Result;
 
  /* Polling mode */
  ret = VL53L3A2_RANGING_SENSOR_GetDistance(VL53L3A2_DEV_CENTER, &Result);
  
  if (ret == BSP_ERROR_NONE)
  {
    for (i = 0; i < RANGING_SENSOR_MAX_NB_ZONES; i++)
    {
      /* Number of the detected distances from the ToF sensor */
      APP_DBG_MSG("\r\nNumber of objects detected= %ld\r\n", Result.ZoneResult[i].NumberOfTargets);
   
      /* Reset the objects distance data */
      for(j=0;j<4;j++)
        ToF_Server_App_Context.ObjectsDistance[j]= 0;
    
      /* Reset the Human Presence data */
     ToF_Server_App_Context.HumanPresence= 0;

      for (j = 0; j < Result.ZoneResult[i].NumberOfTargets; j++)
      {
        APP_DBG_MSG("\tObject= %d status= %ld D= %5ldmm ",
                       j+1,
                       Result.ZoneResult[i].Status[j],
                       Result.ZoneResult[i].Distance[j]);
      
        if(Result.ZoneResult[i].Status[j] == 0)
        {
          ToF_Server_App_Context.ObjectsDistance[j]= Result.ZoneResult[i].Distance[j];
        
          if( (Result.ZoneResult[i].Distance[j] >= PRESENCE_MIN_DISTANCE_RANGE) &&
              (Result.ZoneResult[i].Distance[j] <= PRESENCE_MAX_DISTANCE_RANGE) )
          {
            ToF_Server_App_Context.HumanPresence++;
            APP_DBG_MSG("Human Presence= %d", ToF_Server_App_Context.HumanPresence);
          }
        
          APP_DBG_MSG("\r\n");
        }
        else
        {
          APP_DBG_MSG("Not Valid Measure \r\n");
        }
      }
    }
  }

  //HAL_Delay(POLLING_PERIOD);
}

/**
 * @brief  Check the ToF active capabilities and set the ADV data accordingly
 * @param  None
 * @retval None
 */
static void ToF_Sensor_GetCaps(void)
{
  uint32_t Id;
  int32_t ret;
  
  RANGING_SENSOR_Capabilities_t Cap;
  RANGING_SENSOR_ProfileConfig_t Profile;
  
  ret= VL53L3A2_RANGING_SENSOR_ReadID(VL53L3A2_DEV_CENTER, &Id);
  
  if(ret == BSP_ERROR_NONE)
  {
    ret= VL53L3A2_RANGING_SENSOR_GetCapabilities(VL53L3A2_DEV_CENTER, &Cap);
    
    if(ret == BSP_ERROR_NONE)
    {
      Profile.RangingProfile = RS_MULTI_TARGET_LONG_RANGE;
      /* 16 ms < TimingBudget < 500 ms */
      Profile.TimingBudget = 30;
      /* Not necessary in simple ranging */
      Profile.Frequency = 0;
      /* Enable Ambient profile - Enable: 1, Disable: 0 */
      Profile.EnableAmbient = 1;
      /* Enable Signal profile - Enable: 1, Disable: 0 */
      Profile.EnableSignal = 1;
    
      /* Set the profile if different from default one */
      ret= VL53L3A2_RANGING_SENSOR_ConfigProfile(VL53L3A2_DEV_CENTER, &Profile);
      
      if(ret == BSP_ERROR_NONE)
        ToF_Server_App_Context.hasBuiltInDevice= 1;
        
    
    APP_DBG_MSG("X-NUCLEO-53L3A2 initialized\r\n");
    APP_DBG_MSG("\tSensor Id: %04lX\r\n", Id);
    APP_DBG_MSG("\tNumberOfZones: %lu\r\n", Cap.NumberOfZones);
    APP_DBG_MSG("\tMaxNumberOfTargetsPerZone: %lu\r\n", Cap.MaxNumberOfTargetsPerZone);
    APP_DBG_MSG("\tCustomROI: %lu\r\n", Cap.CustomROI);
    APP_DBG_MSG("\tThresholdDetection: %lu\r\n", Cap.ThresholdDetection);
    
    if (ret != BSP_ERROR_NONE)
      APP_DBG_MSG("\tSet profile failed\r\n\n");
    else
      APP_DBG_MSG("\tSet profile ok\r\n\n");
    }
  }
}

