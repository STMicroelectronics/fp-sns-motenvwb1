
/**
  ******************************************************************************
  * @file    motion_ext_server_app.h
  * @brief   Handle HW/Motion Extended (Acc Events) Service/Char
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MOTION_EXT_SERVER_APP_H
#define MOTION_EXT_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/

/**
 * @brief  Pedometer event
 */
#define EXT_HWF_PEDOMETER        (1   )
/**
 * @brief  Free Fall event
 */
#define EXT_HWF_FREE_FALL        (1<<1)
/**
 * @brief  Double tap event
 */
#define EXT_HWF_DOUBLE_TAP       (1<<2)
/**
 * @brief  Single tap event
 */
#define EXT_HWF_SINGLE_TAP       (1<<3)
/**
 * @brief  WakeUp event
 */
#define EXT_HWF_WAKE_UP          (1<<4)
/**
 * @brief  Tilt event
 */
#define EXT_HWF_TILT             (1<<5)
/**
 * @brief  6D Orientation event
 */
#define EXT_HWF_6D_ORIENTATION   (1<<6)
/**
 * @brief  Multiple events
 */
#define EXT_HWF_MULTIPLE_EVENTS  (1<<7)

/* Exported functions ------------------------------------------------------- */
void MOTION_EXT_Context_Init(void);
void MOTION_EXT_Set_Notification_Status(uint8_t status);
void MOTION_EXT_Enable_Feature(uint8_t feature);
void MOTION_EXT_Disable_Feature(uint8_t feature);
void MOTION_EXT_ReadCB(void);
void MOTION_EXT_Handle_IT(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTION_EXT_SERVER_APP_H */

