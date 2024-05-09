/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ToF_server_app.h
  * @brief   Handle HW/ToF/Char
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
#ifndef TOF_SERVER_APP_H
#define TOF_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

extern uint8_t ToFMObjPresence;

/* Includes ------------------------------------------------------------------*/
#include "53l3a2_ranging_sensor.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void HW_ToF_Init(void);
void ToF_Context_Init(void);
void ToF_Set_Notification_Status(uint8_t status);
void ToF_Send_Notification_Task(void);
void ToF_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* TOF_SERVER_APP_H */

