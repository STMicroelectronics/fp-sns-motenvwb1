/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motion_ext_server_app.c
  * @brief   Handle HW/Motion Extended (Acc Events) Service/Char
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
#include "motion_ext_server_app.h"
#include "config_server_app.h"

#include "motenvwb1_app_conf.h"
#include "remap_conf.h"

/* Private defines -----------------------------------------------------------*/
#define EXT_CHECK_HW_FEATURE(Feature) ((HWExtFeaturesStatus&(Feature)) ? 1 : 0)
#define EXT_ON_HW_FEATURE(Feature)    (HWExtFeaturesStatus|=(Feature))
#define EXT_OFF_HW_FEATURE(Feature)   (HWExtFeaturesStatus&=(~Feature))

/* Private typedef -----------------------------------------------------------*/
/**
  * @brief  Enumerate the Acc event type
  */
typedef enum
{
  ACC_NOT_USED     = 0x00,
  ACC_6D_OR_TOP    = 0x01,
  ACC_6D_OR_LEFT   = 0x02,
  ACC_6D_OR_BOTTOM = 0x03,
  ACC_6D_OR_RIGTH  = 0x04,
  ACC_6D_OR_UP     = 0x05,
  ACC_6D_OR_DOWN   = 0x06,
  ACC_TILT         = 0x08,
  ACC_FREE_FALL    = 0x10,
  ACC_SINGLE_TAP   = 0x20,
  ACC_DOUBLE_TAP   = 0x40,
  ACC_WAKE_UP      = 0x80
} MOTION_EXT_Server_App_AccEvent_t;

/**
  * @brief  HW/Motion Extended (Acc Events) Service/Char Context structure definition
  */
typedef struct
{
  uint8_t NotificationStatus;
  uint8_t MultiEventEnabled;
  uint16_t PedometerStepCount;
  float defaultODR;
} MOTION_EXT_Server_App_Context_t;

/* Private variables ---------------------------------------------------------*/
PLACE_IN_SECTION("BLE_APP_CONTEXT") static MOTION_EXT_Server_App_Context_t MOTION_EXT_Server_App_Context;

static uint32_t HWExtFeaturesStatus = 0;

/* Private function prototypes -----------------------------------------------*/
static void EnableExtFeatures(void);
static void DisableExtFeatures(void);
static void AccEvent_Notify(uint8_t acc_events, uint16_t num_steps);
static void Enable_Pedometer(void);
static void Disable_Pedometer(void);
static void Enable_FreeFall(void);
static void Disable_FreeFall(void);
static void Enable_DoubleTap(void);
static void Disable_DoubleTap(void);
static void Enable_SingleTap(void);
static void Disable_SingleTap(void);
static void Enable_WakeUp(void);
static void Disable_WakeUp(void);
static void Enable_Tilt(void);
static void Disable_Tilt(void);
static void Enable_6D_Orientation(void);
static void Disable_6D_Orientation(void);
static void Enable_MultiEvent(void);
static void Disable_MultiEvent(void);
static MOTION_EXT_Server_App_AccEvent_t GetHWOrientation6D(void);

/* Functions Definition ------------------------------------------------------*/

/* Public functions ----------------------------------------------------------*/
/**
  * @brief  Init the HW/Motion Extended (Acc Events) Service/Char Context
  * @param  None
  * @retval None
  */
void MOTION_EXT_Context_Init(void)
{
  int32_t decPart;
  int32_t intPart;

  /* Save the initial Output Data Rate */
  MOTION_SENSOR_GET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO, &MOTION_EXT_Server_App_Context.defaultODR);
  MCR_BLUEMS_F2I_2D(MOTION_EXT_Server_App_Context.defaultODR, intPart, decPart);
  MOTION_EXT_Server_App_Context.defaultODR = intPart * 100 + decPart;

#if (CFG_DEBUG_APP_TRACE != 0)
  APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ODR=%d.%02d [Hz] \n ", (int)intPart, (int)decPart);
  APP_DBG_MSG(" \n\r");
#endif /* CFG_DEBUG_APP_TRACE != 0 */

  MOTION_EXT_Set_Notification_Status(0);

  MOTION_EXT_Server_App_Context.MultiEventEnabled = 0;
}

/**
  * @brief  Set the notification status (enabled/disabled)
  * @param  status The new notification status
  * @retval None
  */
void MOTION_EXT_Set_Notification_Status(uint8_t status)
{
  MOTION_EXT_Server_App_Context.NotificationStatus = status;

  if (!MOTION_EXT_Server_App_Context.NotificationStatus)
  {
    DisableExtFeatures();
  }
}

/**
  * @brief  Enable a specific Extended feature according to the request GATT Client (ST BLE Sensor App)
  * @param  feature The feature to be enabled
  * @retval None
  */
void MOTION_EXT_Enable_Feature(uint8_t feature)
{
  if (MOTION_EXT_Server_App_Context.MultiEventEnabled == 1)
  {
    DisableExtFeatures();
  }

  switch (feature)
  {
    case EXT_HWF_PEDOMETER:
      Enable_Pedometer();
      break;

    case EXT_HWF_FREE_FALL:
      Enable_FreeFall();
      break;

    case EXT_HWF_DOUBLE_TAP:
      Enable_DoubleTap();
      break;

    case EXT_HWF_SINGLE_TAP:
      Enable_SingleTap();
      break;

    case EXT_HWF_WAKE_UP:
      Enable_WakeUp();
      break;

    case EXT_HWF_TILT:
      Enable_Tilt();
      break;

    case EXT_HWF_6D_ORIENTATION:
      Enable_6D_Orientation();
      break;

    case EXT_HWF_MULTIPLE_EVENTS:
      Enable_MultiEvent();
      break;
  }

}

/**
  * @brief  Disable a specific Extended feature according to the request GATT Client (ST BLE Sensor App)
  * @param  feature The feature to be disabled
  * @retval None
  */
void MOTION_EXT_Disable_Feature(uint8_t feature)
{
  switch (feature)
  {
    case EXT_HWF_PEDOMETER:
      Disable_Pedometer();
      break;

    case EXT_HWF_FREE_FALL:
      Disable_FreeFall();
      break;

    case EXT_HWF_DOUBLE_TAP:
      Disable_DoubleTap();
      break;

    case EXT_HWF_SINGLE_TAP:
      Disable_SingleTap();
      break;

    case EXT_HWF_WAKE_UP:
      Disable_WakeUp();
      break;

    case EXT_HWF_TILT:
      Disable_Tilt();
      break;

    case EXT_HWF_6D_ORIENTATION:
      Disable_6D_Orientation();
      break;

    case EXT_HWF_MULTIPLE_EVENTS:
      Disable_MultiEvent();
      break;
  }
}

/**
  * @brief  Send a notification for Step Count on read request from GATT Client (ST BLE Sensor App)
  * @param  None
  * @retval None
  */
void MOTION_EXT_ReadCB(void)
{
  uint16_t StepCount = 0;

  if (EXT_CHECK_HW_FEATURE(EXT_HWF_PEDOMETER))
  {
    MOTION_SENSOR_GET_STEP_COUNT(ACCELERO_INSTANCE, &StepCount);
  }
  AccEvent_Notify(0, StepCount);
}

/**
  * @brief  Send a notification when there is an interrupt from MEMS
  * @param  None
  * @retval None
  */
void MOTION_EXT_Handle_IT(void)
{
  MOTION_SENSOR_EVENT_STATUS_T status;

  uint8_t AccEvents = 0;
  uint8_t NeedToSend = 0;

  if (MOTION_SENSOR_GET_EVENT_STATUS(ACCELERO_INSTANCE, &status) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR GETTING EVENT STATUS\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
    return;
  }

  if (!EXT_CHECK_HW_FEATURE(EXT_HWF_PEDOMETER))
  {
    MOTION_EXT_Server_App_Context.PedometerStepCount = 0;
  }

  if ((EXT_CHECK_HW_FEATURE(EXT_HWF_PEDOMETER)) ||
      (EXT_CHECK_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS)))
  {
    /* Check if the interrupt is due to Pedometer */
    if (status.StepStatus != 0)
    {
      MOTION_SENSOR_GET_STEP_COUNT(ACCELERO_INSTANCE, &MOTION_EXT_Server_App_Context.PedometerStepCount);
      NeedToSend = 1;
    }
  }

  if ((EXT_CHECK_HW_FEATURE(EXT_HWF_FREE_FALL)) ||
      (EXT_CHECK_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS)))
  {
    /* Check if the interrupt is due to Free Fall */
    if (status.FreeFallStatus != 0)
    {
      NeedToSend = 1;
      AccEvents |= ACC_FREE_FALL;
    }
  }

  if ((EXT_CHECK_HW_FEATURE(EXT_HWF_SINGLE_TAP)) ||
      (EXT_CHECK_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS)))
  {
    /* Check if the interrupt is due to Single Tap */
    if (status.TapStatus != 0)
    {
      NeedToSend = 1;
      AccEvents |= ACC_SINGLE_TAP;
    }
  }

  if ((EXT_CHECK_HW_FEATURE(EXT_HWF_DOUBLE_TAP)) ||
      (EXT_CHECK_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS)))
  {
    /* Check if the interrupt is due to Double Tap */
    if (status.DoubleTapStatus != 0)
    {
      NeedToSend = 1;
      AccEvents |= ACC_DOUBLE_TAP;
    }
  }

  if ((EXT_CHECK_HW_FEATURE(EXT_HWF_TILT)) ||
      (EXT_CHECK_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS)))
  {
    /* Check if the interrupt is due to Tilt */
    if (status.TiltStatus != 0)
    {
      NeedToSend = 1;
      AccEvents |= ACC_TILT;
    }
  }

  if ((EXT_CHECK_HW_FEATURE(EXT_HWF_6D_ORIENTATION)) ||
      (EXT_CHECK_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS)))
  {
    /* Check if the interrupt is due to 6D Orientation */
    if (status.D6DOrientationStatus != 0)
    {
      MOTION_EXT_Server_App_AccEvent_t Orientation = GetHWOrientation6D();
      NeedToSend = 1;
      AccEvents |= Orientation;
    }
  }

  if (EXT_CHECK_HW_FEATURE(EXT_HWF_WAKE_UP))
  {
    /* Check if the interrupt is due to Wake Up */
    if (status.WakeUpStatus != 0)
    {
      NeedToSend = 1;
      AccEvents |= ACC_WAKE_UP;
    }
  }

  if (NeedToSend)
  {
    AccEvent_Notify(AccEvents, MOTION_EXT_Server_App_Context.PedometerStepCount);
  }
}

/* Private functions ---------------------------------------------------------*/
/**
  * @brief  Enable Pedometer Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_Pedometer(void)
{
  if (MOTION_SENSOR_ENABLE_PEDOMETER(ACCELERO_INSTANCE, MOTION_SENSOR_INT_PIN) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR ENABLING PEDOMETER\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_ON_HW_FEATURE(EXT_HWF_PEDOMETER);
  }
  MOTION_SENSOR_RESET_STEP_COUNTER(ACCELERO_INSTANCE);
}

/**
  * @brief  Disable Pedometer Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_Pedometer(void)
{
  if (MOTION_SENSOR_DISABLE_PEDOMETER(ACCELERO_INSTANCE) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR DISABLING PEDOMETER\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_OFF_HW_FEATURE(EXT_HWF_PEDOMETER);
  }
  if (MOTION_SENSOR_SET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO,
                                         MOTION_EXT_Server_App_Context.defaultODR) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING DEFAULT ODR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Enable Free Fall Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_FreeFall(void)
{
  if (MOTION_SENSOR_ENABLE_FREE_FALL_DETECTION(ACCELERO_INSTANCE, MOTION_SENSOR_INT_PIN) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR ENABLING FREE FALL\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_ON_HW_FEATURE(EXT_HWF_FREE_FALL);
  }
  if (MOTION_SENSOR_SET_FREE_FALL_THRESHOLD(ACCELERO_INSTANCE, FF_THRESHOLD) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING FF_TSH\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Disable Free Fall Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_FreeFall(void)
{
  if (MOTION_SENSOR_DISABLE_FREE_FALL_DETECTION(ACCELERO_INSTANCE) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR DISABLING FREE FALL\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_OFF_HW_FEATURE(EXT_HWF_FREE_FALL);
  }
  if (MOTION_SENSOR_SET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO,
                                         MOTION_EXT_Server_App_Context.defaultODR) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING DEFAULT ODR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Enable DoubleTap Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_DoubleTap(void)
{
  if (MOTION_SENSOR_ENABLE_DOUBLE_TAP_DETECTION(ACCELERO_INSTANCE, MOTION_SENSOR_INT_PIN) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR ENABLING DOUBLE TAP\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_ON_HW_FEATURE(EXT_HWF_DOUBLE_TAP);
  }
  if (MOTION_SENSOR_SET_TAP_THRESHOLD(ACCELERO_INSTANCE, TAP_THRESHOLD) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING TAP_TSH\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  if (MOTION_SENSOR_SET_TAP_DURATION_TIME(ACCELERO_INSTANCE, TAP_DURATION) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING TAP_DUR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Disable DoubleTap Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_DoubleTap(void)
{
  if (MOTION_SENSOR_DISABLE_DOUBLE_TAP_DETECTION(ACCELERO_INSTANCE) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR DISABLING DOUBLE TAP\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_OFF_HW_FEATURE(EXT_HWF_DOUBLE_TAP);
  }
  if (MOTION_SENSOR_SET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO,
                                         MOTION_EXT_Server_App_Context.defaultODR) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING DEFAULT ODR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Enable SingleTap Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_SingleTap(void)
{
  if (MOTION_SENSOR_ENABLE_SINGLE_TAP_DETECTION(ACCELERO_INSTANCE, MOTION_SENSOR_INT_PIN) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR ENABLING SINGLE TAP\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_ON_HW_FEATURE(EXT_HWF_SINGLE_TAP);
  }
}

/**
  * @brief  Disable SingleTap Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_SingleTap(void)
{
  if (MOTION_SENSOR_DISABLE_SINGLE_TAP_DETECTION(ACCELERO_INSTANCE) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR DISABLING SINGLE TAP\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_OFF_HW_FEATURE(EXT_HWF_SINGLE_TAP);
  }
  if (MOTION_SENSOR_SET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO,
                                         MOTION_EXT_Server_App_Context.defaultODR) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING DEFAULT ODR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Enable WakeUp Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_WakeUp(void)
{
  if (MOTION_SENSOR_ENABLE_WAKE_UP_DETECTION(ACCELERO_INSTANCE, MOTION_SENSOR_INT_PIN) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR ENABLING WAKE UP\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_ON_HW_FEATURE(EXT_HWF_WAKE_UP);
  }
  if (MOTION_SENSOR_SET_WAKE_UP_THRESHOLD(ACCELERO_INSTANCE, WAKE_UP_THRESHOLD) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING WAKE_UP_THS\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Disable WakeUp Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_WakeUp(void)
{
  if (MOTION_SENSOR_DISABLE_WAKE_UP_DETECTION(ACCELERO_INSTANCE) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR DISABLING WAKE UP\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_OFF_HW_FEATURE(EXT_HWF_WAKE_UP);
  }
  if (MOTION_SENSOR_SET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO,
                                         MOTION_EXT_Server_App_Context.defaultODR) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING DEFAULT ODR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Enable Tilt Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_Tilt(void)
{
  if (MOTION_SENSOR_ENABLE_TILT_DETECTION(ACCELERO_INSTANCE, MOTION_SENSOR_INT_PIN) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR ENABLING TILT\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_ON_HW_FEATURE(EXT_HWF_TILT);
  }
}

/**
  * @brief  Disable Tilt Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_Tilt(void)
{
  if (MOTION_SENSOR_DISABLE_TILT_DETECTION(ACCELERO_INSTANCE) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR DISABLING TILT\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_OFF_HW_FEATURE(EXT_HWF_TILT);
  }
  if (MOTION_SENSOR_SET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO,
                                         MOTION_EXT_Server_App_Context.defaultODR) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING DEFAULT ODR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Enable 6D Orientation Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_6D_Orientation(void)
{
  if (MOTION_SENSOR_ENABLE_6D_ORIENTATION(ACCELERO_INSTANCE, MOTION_SENSOR_INT_PIN) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR ENABLING 6D ORIENTATION\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_ON_HW_FEATURE(EXT_HWF_6D_ORIENTATION);
  }
}

/**
  * @brief  Disable 6D Orientation Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_6D_Orientation(void)
{
  if (MOTION_SENSOR_DISABLE_6D_ORIENTATION(ACCELERO_INSTANCE) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR DISABLING 6D ORIENTATION\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  else
  {
    EXT_OFF_HW_FEATURE(EXT_HWF_6D_ORIENTATION);
  }
  if (MOTION_SENSOR_SET_OUTPUT_DATA_RATE(ACCELERO_INSTANCE, MOTION_ACCELERO,
                                         MOTION_EXT_Server_App_Context.defaultODR) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : ERROR SETTING DEFAULT ODR\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
}

/**
  * @brief  Enable Multi Event Extended Feature
  * @param  None
  * @retval None
  */
static void Enable_MultiEvent(void)
{
  DisableExtFeatures();
  EnableExtFeatures();

  MOTION_EXT_Server_App_Context.PedometerStepCount = 0;
  AccEvent_Notify(0, MOTION_EXT_Server_App_Context.PedometerStepCount);
  EXT_ON_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS);
  MOTION_SENSOR_RESET_STEP_COUNTER(ACCELERO_INSTANCE);
}

/**
  * @brief  Disable Multi Event Extended Feature
  * @param  None
  * @retval None
  */
static void Disable_MultiEvent(void)
{
  DisableExtFeatures();
  EXT_OFF_HW_FEATURE(EXT_HWF_MULTIPLE_EVENTS);
}

/**
  * @brief  Enable all Extended Features
  * @param  None
  * @retval None
  */
static void EnableExtFeatures(void)
{
  /* Do not change the enable sequenze of the HW events */
  /* It depends on the ODR value (from minor value to max value) */
  Enable_Pedometer();
  Enable_Tilt();
  Enable_FreeFall();
  Enable_SingleTap();
  Enable_DoubleTap();
  Enable_6D_Orientation();

  MOTION_EXT_Server_App_Context.MultiEventEnabled = 1;
}

/**
  * @brief  Disable all Extended Features
  * @param  None
  * @retval None
  */
static void DisableExtFeatures(void)
{
  /* Disable Pedometer */
  if (EXT_CHECK_HW_FEATURE(EXT_HWF_PEDOMETER))
  {
    Disable_Pedometer();
  }

  /* Disable Free Fall */
  if (EXT_CHECK_HW_FEATURE(EXT_HWF_FREE_FALL))
  {
    Disable_FreeFall();
  }

  /* Disable Double Tap */
  if (EXT_CHECK_HW_FEATURE(EXT_HWF_DOUBLE_TAP))
  {
    Disable_DoubleTap();
  }

  /* Disable Single Tap */
  if (EXT_CHECK_HW_FEATURE(EXT_HWF_SINGLE_TAP))
  {
    Disable_SingleTap();
  }

  /* Disable Wake Up */
  if (EXT_CHECK_HW_FEATURE(EXT_HWF_WAKE_UP))
  {
    Disable_WakeUp();
  }

  /* Disable Tilt */
  if (EXT_CHECK_HW_FEATURE(EXT_HWF_TILT))
  {
    Disable_Tilt();
  }

  /* Disable 6D Orientation */
  if (EXT_CHECK_HW_FEATURE(EXT_HWF_6D_ORIENTATION))
  {
    Disable_6D_Orientation();
  }

  MOTION_EXT_Server_App_Context.MultiEventEnabled = 0;
}

/**
  * @brief  Return the HW's 6D Orientation result
  * @param  None
  * @retval AccEventType 6D Orientation Found
  */
static MOTION_EXT_Server_App_AccEvent_t GetHWOrientation6D(void)
{
  MOTION_EXT_Server_App_AccEvent_t OrientationResult = ACC_NOT_USED;

  uint8_t xl = 0;
  uint8_t xh = 0;
  uint8_t yl = 0;
  uint8_t yh = 0;
  uint8_t zl = 0;
  uint8_t zh = 0;

  if (MOTION_SENSOR_GET_6D_ORIENTATION_XL(ACCELERO_INSTANCE, &xl) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : Error getting 6D orientation XL axis from sensor "
                "- accelerometer.\r\n");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  if (MOTION_SENSOR_GET_6D_ORIENTATION_XH(ACCELERO_INSTANCE, &xh) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : Error getting 6D orientation XH axis from sensor "
                "- accelerometer.\r\n");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  if (MOTION_SENSOR_GET_6D_ORIENTATION_YL(ACCELERO_INSTANCE, &yl) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : Error getting 6D orientation YL axis from sensor "
                "- accelerometer.\r\n");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  if (MOTION_SENSOR_GET_6D_ORIENTATION_YH(ACCELERO_INSTANCE, &yh) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : Error getting 6D orientation YH axis from sensor "
                "- accelerometer.\r\n");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  if (MOTION_SENSOR_GET_6D_ORIENTATION_ZL(ACCELERO_INSTANCE, &zl) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : Error getting 6D orientation ZL axis from sensor "
                "- accelerometer.\r\n");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }
  if (MOTION_SENSOR_GET_6D_ORIENTATION_ZH(ACCELERO_INSTANCE, &zh) != BSP_ERROR_NONE)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : Error getting 6D orientation ZH axis from sensor "
                "- accelerometer.\r\n");
#endif  /* CFG_DEBUG_APP_TRACE != 0 */
  }

  if (xl == 0U && yl == 0U && zl == 0U && xh == 0U && yh == 1U && zh == 0U)
  {
    OrientationResult = ACC_6D_OR_RIGTH;
  }
  else if (xl == 1U && yl == 0U && zl == 0U && xh == 0U && yh == 0U && zh == 0U)
  {
    OrientationResult = ACC_6D_OR_TOP;
  }
  else if (xl == 0U && yl == 0U && zl == 0U && xh == 1U && yh == 0U && zh == 0U)
  {
    OrientationResult = ACC_6D_OR_BOTTOM;
  }
  else if (xl == 0U && yl == 1U && zl == 0U && xh == 0U && yh == 0U && zh == 0U)
  {
    OrientationResult = ACC_6D_OR_LEFT;
  }
  else if (xl == 0U && yl == 0U && zl == 0U && xh == 0U && yh == 0U && zh == 1U)
  {
    OrientationResult = ACC_6D_OR_UP;
  }
  else if (xl == 0U && yl == 0U && zl == 1U && xh == 0U && yh == 0U && zh == 0U)
  {
    OrientationResult = ACC_6D_OR_DOWN;
  }
  else
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : None of the 6D orientation axes is set in sensor "
                "- accelerometer.\r\n");
#endif  /* CFG_DEBUG_APP_TRACE != 0 */
  }
  return OrientationResult;
}

/**
  * @brief  Send a notification when the DS3 detects one Acceleration event
  * @param  Command to Send
  * @param  dimByte Num of Command bytes
  * @retval None
  */
static void AccEvent_Notify(uint8_t acc_events, uint16_t num_steps)
{
  uint8_t buff[2 + 3];
  STORE_LE_16(buff, (HAL_GetTick() / 10U));
  buff[2] = acc_events;
  STORE_LE_16(buff + 3, num_steps);

  if (MOTION_EXT_Server_App_Context.NotificationStatus)
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : NOTIFY CLIENT WITH NEW MOTION PARAMETER VALUE \n ");
    APP_DBG_MSG(" \n\r");
#endif /* CFG_DEBUG_APP_TRACE != 0 */

    MOTENV_STM_App_Update_Char(ACC_EVENT_CHAR_UUID, 2 + 3, (uint8_t *)&buff);
  }
  else
  {
#if (CFG_DEBUG_APP_TRACE != 0)
    APP_DBG_MSG("-- MOTION EXT APPLICATION SERVER : CAN'T INFORM CLIENT - NOTIFICATION DISABLED\n ");
#endif /* CFG_DEBUG_APP_TRACE != 0 */
  }

  return;
}
