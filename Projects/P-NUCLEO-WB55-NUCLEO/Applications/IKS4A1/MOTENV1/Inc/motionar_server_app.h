/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motionar_server_app.h
  * @brief   Handle SW/Activity Recognition Service/Char
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MOTIONAR_SERVER_APP_H
#define MOTIONAR_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTIONAR_Context_Init(void);
void MOTIONAR_Set_Notification_Status(uint8_t status);
void MOTIONAR_Send_Notification_Task(void);
void MOTIONAR_ActivityRec_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONAR_SERVER_APP_H */

