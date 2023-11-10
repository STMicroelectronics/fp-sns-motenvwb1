
/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_motenv1.c
  * @author  System Research & Applications Team - Catania Lab.
  * @brief   This file provides code for FP-SNS-MOTENVWB1 application.
  *
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

/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_motenv1.h"
#include "app_entry.h"
#include "app_debug.h"
#include "app_common.h"
#include "stm32_lpm.h"
#include "stm32_seq.h"
#include "dbg_trace.h"
#include "ToF_server_app.h"

#include "remap_conf.h"
#include "env_server_app.h"
#include "motion_server_app.h"

PLACE_IN_SECTION("BLE_APP_CONTEXT")  ENV_Server_App_Context_t ENV_Server_App_Context;

PLACE_IN_SECTION("BLE_APP_CONTEXT")  MOTION_Server_App_Context_t MOTION_Server_App_Context;

/* Section specific to button management using UART */

#define C_SIZE_CMD_STRING       256U
#define RX_BUFFER_SIZE          8U

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private macro ------------------------------------------------------------*/

/* Private defines -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static uint8_t aRxBuffer[RX_BUFFER_SIZE];
static uint8_t CommandString[C_SIZE_CMD_STRING];
static uint16_t indexReceiveChar = 0;
EXTI_HandleTypeDef H_EXTI_MEMS = {.Line = H_EXTI_LINE_MEMS};
EXTI_HandleTypeDef exti_handle;

/* Private function prototypes -----------------------------------------------*/
static void Init_Debug( void );
static void User_Init(void);
static void Sensors_Init(void);

/* Section specific to button management using UART */
static void Led_Init( void );
static void Button_Init( void );

/* Section specific to button management using UART */
static void RxUART_Init(void);
static void RxCpltCallback(void);
static void UartCmdExecute(void);

void MX_MOTENV1_Init(void)
{
  /* USER CODE BEGIN SV */

  /* USER CODE END SV */

  /* Initialize MOTENV1 application */
  User_Init();

}

/*
 * FP-SNS-MOTENV1 background task
 */
void MX_MOTENV1_Process(void)
{

  /* Process of the MOTENV1 application */
  MX_APPE_Process();

}

static void Init_Debug( void )
{
#if (CFG_DEBUGGER_SUPPORTED == 1)
  /**
   * Keep debugger enabled while in any low power mode
   */
  HAL_DBGMCU_EnableDBGSleepMode();

  /***************** ENABLE DEBUGGER *************************************/
  LL_EXTI_EnableIT_32_63(LL_EXTI_LINE_48);
  LL_C2_EXTI_EnableIT_32_63(LL_EXTI_LINE_48);

#else

  GPIO_InitTypeDef gpio_config = {0};

  gpio_config.Pull = GPIO_NOPULL;
  gpio_config.Mode = GPIO_MODE_ANALOG;

  gpio_config.Pin = GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13;
  __HAL_RCC_GPIOA_CLK_ENABLE();
  HAL_GPIO_Init(GPIOA, &gpio_config);
  __HAL_RCC_GPIOA_CLK_DISABLE();

  gpio_config.Pin = GPIO_PIN_4 | GPIO_PIN_3;
  __HAL_RCC_GPIOB_CLK_ENABLE();
  HAL_GPIO_Init(GPIOB, &gpio_config);
  __HAL_RCC_GPIOB_CLK_DISABLE();

  HAL_DBGMCU_DisableDBGSleepMode();
  HAL_DBGMCU_DisableDBGStopMode();
  HAL_DBGMCU_DisableDBGStandbyMode();

#endif /* (CFG_DEBUGGER_SUPPORTED == 1) */

#if(CFG_DEBUG_TRACE != 0)
  DbgTraceInit();
#endif

  return;
}

static void Led_Init( void )
{
#if (CFG_LED_SUPPORTED == 1)
  /**
   * Leds Initialization
   */

  BSP_LED_Init(LED_BLUE);
  BSP_LED_Init(LED_GREEN);

  BSP_LED_On(LED_GREEN);
#endif

  return;
}

static void Button_Init( void )
{
#if (CFG_BUTTON_SUPPORTED == 1)
  /**
   * Button Initialization
   */

  BSP_PB_Init(BUTTON_USER, BUTTON_MODE_EXTI);

#endif

  return;
}

static void RxUART_Init(void)
{
  HW_UART_Receive_IT((hw_uart_id_t)CFG_DEBUG_TRACE_UART, aRxBuffer, 1U, RxCpltCallback);
}

static void RxCpltCallback(void)
{
  /* Filling buffer and wait for '\r' char */
  if (indexReceiveChar < C_SIZE_CMD_STRING)
  {
    if (aRxBuffer[0] == '\r')
    {
      APP_DBG_MSG("received %s\n", CommandString);

      UartCmdExecute();

      /* Clear receive buffer and character counter*/
      indexReceiveChar = 0;
      memset(CommandString, 0, C_SIZE_CMD_STRING);
    }
    else
    {
      CommandString[indexReceiveChar++] = aRxBuffer[0];
    }
  }

  /* Once a character has been sent, put back the device in reception mode */
  HW_UART_Receive_IT((hw_uart_id_t)CFG_DEBUG_TRACE_UART, aRxBuffer, 1U, RxCpltCallback);
}

static void UartCmdExecute(void)
{
  /* Parse received CommandString */
  if(strcmp((char const*)CommandString, "SW1") == 0)
  {
    APP_DBG_MSG("SW1 OK\n");
    exti_handle.Line = USER_BUTTON_EXTI_LINE;
    HAL_EXTI_GenerateSWI(&exti_handle);
  }
  else if (strcmp((char const*)CommandString, "SW2") == 0)
  {
    APP_DBG_MSG("SW2 OK\n");
  //exti_handle.Line = USER_BUTTON_SW2_EXTI_LINE;
    HAL_EXTI_GenerateSWI(&exti_handle);
  }
  else if (strcmp((char const*)CommandString, "SW3") == 0)
  {
    APP_DBG_MSG("SW3 OK\n");
  //exti_handle.Line = USER_BUTTON_SW3_EXTI_LINE;
    HAL_EXTI_GenerateSWI(&exti_handle);
  }
  else
  {
    APP_DBG_MSG("NOT RECOGNIZED COMMAND : %s\n", CommandString);
  }
}

/**
  * @brief  BSP Push Button callback
  * @param  Button Specifies the pin connected EXTI line
  * @retval None.
  */
void BSP_PB_Callback(Button_TypeDef Button)
{
  APP_BLE_Key_Button1_Action();
}

static void User_Init(void)
{
  Init_Debug();

  /* Initialize 53L3A2 board */
  HW_ToF_Init();

  /* Init code for sensors */
  Sensors_Init();

  /* Init code for STM32_WPAN */
  MX_APPE_Init();
  APPD_Init();

  /**
  * The Standby mode should not be entered before the initialization is over
  * The default state of the Low Power Manager is to allow the Standby Mode so an request is needed here
  */
  UTIL_LPM_SetOffMode(1 << CFG_LPM_APP, UTIL_LPM_DISABLE);

  Led_Init();

  Button_Init();

  set_mems_int_pin();

  RxUART_Init();

}

static void Sensors_Init(void)
{
  ENV_Server_App_Context.hasPressure = 0;
  ENV_Server_App_Context.hasHumidity = 0;
  ENV_Server_App_Context.hasTemperature = 0;

  if(ENV_SENSOR_Init(TEMPERATURE_INSTANCE_1, ENV_TEMPERATURE) == BSP_ERROR_NONE)
  {
    ENV_Server_App_Context.hasTemperature++;
  }
  if(ENV_SENSOR_Init(HUMIDITY_INSTANCE, ENV_HUMIDITY) == BSP_ERROR_NONE)
  {
    ENV_Server_App_Context.hasHumidity = 1;
  }

  if(ENV_SENSOR_Init(PRESS_AND_TEMP_INSTANCE, ENV_TEMPERATURE | ENV_PRESSURE) == BSP_ERROR_NONE)
  {
    ENV_Server_App_Context.hasPressure = 1;
    ENV_Server_App_Context.hasTemperature++;
  }

  APP_DBG_MSG("-- ENV APPLICATION SERVER : NBR_ENV_INSTANCES=%d\n ", NBR_ENV_INSTANCES);

  MOTION_Server_App_Context.hasAcc = 0;
  MOTION_Server_App_Context.hasGyro = 0;
  MOTION_Server_App_Context.hasMag = 0;

  MOTION_Set2G_Accelerometer_FullScale();

  if(MOTION_SENSOR_Init(ACCELERO_AND_GYRO_INSTANCE, MOTION_ACCELERO | MOTION_GYRO) == BSP_ERROR_NONE)
  {
    MOTION_Server_App_Context.hasGyro = 1;
    MOTION_Server_App_Context.hasAcc = 1;
  }

  if(MOTION_SENSOR_Init(ACCELERO_INSTANCE_2, MOTION_ACCELERO) == BSP_ERROR_NONE)
  {
    MOTION_Server_App_Context.hasAcc = 1;
  }

  if(MOTION_SENSOR_Init(MAGNETO_INSTANCE, MOTION_MAGNETO) == BSP_ERROR_NONE)
  {
    MOTION_Server_App_Context.hasMag = 1;
  }
}

void set_mems_int_pin(void)
{
  /* register event irq handler */
  HAL_EXTI_RegisterCallback(&H_EXTI_MEMS, HAL_EXTI_COMMON_CB_ID, mems_int_isr);
}

void mems_int_isr(void)
{
  UTIL_SEQ_SetTask(1<<CFG_TASK_HANDLE_MEMS_IT_ID, CFG_SCH_PRIO_0);
}

/**
 * @brief  Parse the values read by Environmental sensors
 * @param  None
 * @retval None
 */
void ENV_Handle_Sensor(void)
{
  uint8_t tempIndex = 0;
  float pressure, humidity, temperature;
  int32_t decPart, intPart;

  if(ENV_Server_App_Context.hasPressure == 1)
  {
    if (ENV_SENSOR_Get_Value(PRESSURE_INSTANCE, ENV_PRESSURE, &pressure) == BSP_ERROR_NONE)
    {
      MCR_BLUEMS_F2I_2D(pressure, intPart, decPart);
      ENV_Server_App_Context.PressureValue = intPart*100+decPart;
    }
  }

  if(ENV_Server_App_Context.hasHumidity == 1)
  {
    if (ENV_SENSOR_Get_Value(HUMIDITY_INSTANCE, ENV_HUMIDITY, &humidity) == BSP_ERROR_NONE)
    {
      MCR_BLUEMS_F2I_1D(humidity, intPart, decPart);
      ENV_Server_App_Context.HumidityValue = intPart*10+decPart;
    }
  }

  if(ENV_Server_App_Context.hasTemperature >= 1)
  {
    if (ENV_SENSOR_Get_Value(TEMPERATURE_INSTANCE_2, ENV_TEMPERATURE, &temperature) == BSP_ERROR_NONE)
    {
      MCR_BLUEMS_F2I_1D(temperature, intPart, decPart);
      ENV_Server_App_Context.TemperatureValue[tempIndex] = intPart*10+decPart;
      tempIndex++;
    }

    if (ENV_SENSOR_Get_Value(TEMPERATURE_INSTANCE_1, ENV_TEMPERATURE, &temperature) == BSP_ERROR_NONE)
    {
      MCR_BLUEMS_F2I_1D(temperature, intPart, decPart);
      ENV_Server_App_Context.TemperatureValue[tempIndex] = intPart*10+decPart;
      tempIndex++;
    }
  }
}

/**
  * @brief  Set the ACC FS to 2g
  * @param  None
  * @retval None
  */
void MOTION_Set2G_Accelerometer_FullScale(void)
{
  /* Set Full Scale to +/-2g */
  MOTION_SENSOR_SetFullScale(ACCELERO_INSTANCE, MOTION_ACCELERO, 2);
}

/**
 * @brief  Parse the values read by Motion sensors
 * @param  None
 * @retval None
 */
void MOTION_Handle_Sensor(void)
{

  MOTION_SENSOR_Axes_t acceleration;
  MOTION_SENSOR_Axes_t angular_velocity;
  MOTION_SENSOR_Axes_t magnetic_field;

  if(MOTION_Server_App_Context.hasAcc == 1)
  {
    if (MOTION_SENSOR_GetAxes(ACCELERO_INSTANCE, MOTION_ACCELERO, &acceleration) == BSP_ERROR_NONE)
    {
      MOTION_Server_App_Context.acceleration = acceleration;
    }
    if (MOTION_SENSOR_GetAxes(ACCELERO_INSTANCE_2, MOTION_ACCELERO, &acceleration) == BSP_ERROR_NONE)
    {
      MOTION_Server_App_Context.acceleration = acceleration;
    }
  }

  if(MOTION_Server_App_Context.hasGyro == 1)
  {
    if (MOTION_SENSOR_GetAxes(GYRO_INSTANCE, MOTION_GYRO, &angular_velocity) == BSP_ERROR_NONE)
    {
      MOTION_Server_App_Context.angular_velocity = angular_velocity;
    }
  }

  if(MOTION_Server_App_Context.hasMag == 1)
  {
    if (MOTION_SENSOR_GetAxes(MAGNETO_INSTANCE, MOTION_MAGNETO, &magnetic_field) == BSP_ERROR_NONE)
    {
      MOTION_Server_App_Context.magnetic_field = magnetic_field;
    }
  }
}
