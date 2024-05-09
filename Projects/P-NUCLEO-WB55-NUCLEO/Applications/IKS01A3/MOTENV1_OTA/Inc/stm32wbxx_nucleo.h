/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file  : stm32wbxx_nucleo.h
  * @brief : header file for the BSP Common driver
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
#ifndef __STM32WBXX_NUCLEO_H
#define __STM32WBXX_NUCLEO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_nucleo_conf.h"
#include "stm32wbxx_nucleo_errno.h"
#include "main.h"

#if (USE_BSP_COM_FEATURE > 0)
  #if (USE_COM_LOG > 0)
    #if defined(__ICCARM__) || defined(__CC_ARM) || (defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) /* For IAR and ARM Compiler 5 and 6*/
      #include <stdio.h>
    #endif
  #endif
#endif
/** @addtogroup BSP
 * @{
 */

/** @defgroup STM32WBXX_NUCLEO
 * @{
 */

/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL
 * @{
 */

/** @defgroup STM32L4XX_NUCLEO_LOW_LEVEL_Exported_Constants LOW LEVEL Exported Constants
  * @{
  */
/**
 * @brief STM32WBXX NUCLEO BSP Driver version number V1.0.0
 */
#define __STM32WBXX_NUCLEO_BSP_VERSION_MAIN   (uint32_t)(0x01) /*!< [31:24] main version */
#define __STM32WBXX_NUCLEO_BSP_VERSION_SUB1   (uint32_t)(0x00) /*!< [23:16] sub1 version */
#define __STM32WBXX_NUCLEO_BSP_VERSION_SUB2   (uint32_t)(0x00) /*!< [15:8]  sub2 version */
#define __STM32WBXX_NUCLEO_BSP_VERSION_RC     (uint32_t)(0x00) /*!< [7:0]  release candidate */
#define __STM32WBXX_NUCLEO_BSP_VERSION        ((__STM32WBXX_NUCLEO_BSP_VERSION_MAIN << 24)\
                                                    |(__STM32WBXX_NUCLEO_BSP_VERSION_SUB1 << 16)\
                                                    |(__STM32WBXX_NUCLEO_BSP_VERSION_SUB2 << 8 )\
                                                    |(__STM32WBXX_NUCLEO_BSP_VERSION_RC))

/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL_Exported_Types STM32WBXX_NUCLEO LOW LEVEL Exported Types
 * @{
 */

 /**
  * @brief Define for STM32WBXX_NUCLEO board
  */
#if !defined (USE_STM32WBXX_NUCLEO)
 #define USE_STM32WBXX_NUCLEO
#endif
#ifndef USE_BSP_COM_FEATURE
   #define USE_BSP_COM_FEATURE                  0U
#endif

/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL_LED STM32WBXX_NUCLEO LOW LEVEL LED
 * @{
 */

/** Define number of LED            **/
#define LEDn                              2U

/**  Definition for BSP USER LED _BLUE   **/

#define BUS_GPIO_INSTANCE GPIO
#define BUS_BSP_LED__BLUE_GPIO_PIN GPIO_PIN_5
#define BUS_BSP_LED__BLUE_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_BSP_LED__BLUE_GPIO_CLK_DISABLE() __HAL_RCC_GPIOB_CLK_DISABLE()
#define BUS_BSP_LED__BLUE_GPIO_PORT GPIOB

#define LED_BLUE_PIN                          GPIO_PIN_5
#define LED_BLUE_GPIO_PORT                    GPIOB
#define LED_BLUE_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED_BLUE_GPIO_CLK_DISABLE()           __HAL_RCC_GPIOB_CLK_DISABLE()

/**  Definition for BSP USER LED _GREEN   **/

#define BUS_GPIO_INSTANCE GPIO
#define BUS_BSP_LED__GREEN_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define BUS_BSP_LED__GREEN_GPIO_PORT GPIOB
#define BUS_BSP_LED__GREEN_GPIO_PIN GPIO_PIN_0
#define BUS_BSP_LED__GREEN_GPIO_CLK_DISABLE() __HAL_RCC_GPIOB_CLK_DISABLE()

#define LED_GREEN_PIN                          GPIO_PIN_0
#define LED_GREEN_GPIO_PORT                    GPIOB
#define LED_GREEN_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOB_CLK_ENABLE()
#define LED_GREEN_GPIO_CLK_DISABLE()           __HAL_RCC_GPIOB_CLK_DISABLE()

/**
 * @}
 */

/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL_BUTTON STM32WBXX_NUCLEO LOW LEVEL BUTTON
 * @{
 */
/* Button state */
#define BUTTON_RELEASED                   0U
#define BUTTON_PRESSED                    1U
/** Define number of BUTTON            **/
#define BUTTONn                           1U

/**
 * @brief User push-button
 */
  /**  Definition for BSP USER BUTTON   **/

#define BUS_GPIO_INSTANCE GPIO
#define BUS_BSP_BUTTON_GPIO_CLK_ENABLE() __HAL_RCC_GPIOC_CLK_ENABLE()
#define BUS_BSP_BUTTON_GPIO_PIN GPIO_PIN_4
#define BUS_BSP_BUTTON_GPIO_CLK_DISABLE() __HAL_RCC_GPIOC_CLK_DISABLE()
#define BUS_BSP_BUTTON_GPIO_PORT GPIOC

#define USER_BUTTON_PIN	                  GPIO_PIN_4
#define USER_BUTTON_GPIO_PORT              GPIOC
#define USER_BUTTON_EXTI_IRQn              EXTI4_IRQn
#define USER_BUTTON_EXTI_LINE              EXTI_LINE_4
#define H_EXTI_4			  hpb_exti[BUTTON_USER]
/**
 * @}
 */
/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL_COM STM32WBXX_NUCLEO LOW LEVEL COM
 * @{
 */
/**
 * @}
 */

/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL_Exported_Types LOW LEVEL Exported Types
  * @{
  */
#ifndef USE_BSP_COM
  #define USE_BSP_COM                           0U
#endif

#ifndef USE_COM_LOG
  #define USE_COM_LOG                           1U
#endif

#ifndef BSP_BUTTON_USER_IT_PRIORITY
  #define BSP_BUTTON_USER_IT_PRIORITY            15U
#endif

typedef enum
{
  LED_BLUE = 0,
  LED_GREEN = 1,
}Led_TypeDef;

typedef enum
{
  BUTTON_USER = 0U,
}Button_TypeDef;

/* Keep compatibility with CMSIS Pack already delivered */
#define BUTTON_KEY BUTTON_USER

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;

#if (USE_BSP_COM_FEATURE > 0)
typedef enum
{
  COM1 = 0U,
  COMn
}COM_TypeDef;

typedef enum
{
 COM_WORDLENGTH_8B     =   UART_WORDLENGTH_8B,
 COM_WORDLENGTH_9B     =   UART_WORDLENGTH_9B,
}COM_WordLengthTypeDef;

typedef enum
{
 COM_STOPBITS_1     =   UART_STOPBITS_1,
 COM_STOPBITS_2     =   UART_STOPBITS_2,
}COM_StopBitsTypeDef;

typedef enum
{
 COM_PARITY_NONE     =  UART_PARITY_NONE,
 COM_PARITY_EVEN     =  UART_PARITY_EVEN,
 COM_PARITY_ODD      =  UART_PARITY_ODD,
}COM_ParityTypeDef;

typedef enum
{
 COM_HWCONTROL_NONE    =  UART_HWCONTROL_NONE,
 COM_HWCONTROL_RTS     =  UART_HWCONTROL_RTS,
 COM_HWCONTROL_CTS     =  UART_HWCONTROL_CTS,
 COM_HWCONTROL_RTS_CTS =  UART_HWCONTROL_RTS_CTS,
}COM_HwFlowCtlTypeDef;

typedef struct
{
  uint32_t             BaudRate;
  COM_WordLengthTypeDef  WordLength;
  COM_StopBitsTypeDef  StopBits;
  COM_ParityTypeDef    Parity;
  COM_HwFlowCtlTypeDef HwFlowCtl;
}COM_InitTypeDef;
#endif

#define MX_UART_InitTypeDef          COM_InitTypeDef
#define MX_UART_StopBitsTypeDef      COM_StopBitsTypeDef
#define MX_UART_ParityTypeDef        COM_ParityTypeDef
#define MX_UART_HwFlowCtlTypeDef     COM_HwFlowCtlTypeDef

/**
 * @}
 */

/**
 * @}
 */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL_Exported_Variables LOW LEVEL Exported Constants
  * @{
  */
extern EXTI_HandleTypeDef hpb_exti[BUTTONn];
/**
  * @}
  */

/** @defgroup STM32WBXX_NUCLEO_LOW_LEVEL_Exported_Functions STM32WBXX_NUCLEO LOW LEVEL Exported Functions
 * @{
 */

int32_t  BSP_GetVersion(void);
int32_t  BSP_LED_Init(Led_TypeDef Led);
int32_t  BSP_LED_DeInit(Led_TypeDef Led);
int32_t  BSP_LED_On(Led_TypeDef Led);
int32_t  BSP_LED_Off(Led_TypeDef Led);
int32_t  BSP_LED_Toggle(Led_TypeDef Led);
int32_t  BSP_LED_GetState(Led_TypeDef Led);
int32_t  BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
int32_t  BSP_PB_DeInit(Button_TypeDef Button);
int32_t  BSP_PB_GetState(Button_TypeDef Button);
void     BSP_PB_Callback(Button_TypeDef Button);
void     BSP_PB_IRQHandler (Button_TypeDef Button);

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* __STM32WBXX_NUCLEO__H */

