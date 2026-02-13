/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motioncp_server_app.h
  * @brief   Handle SW/Carry Position Service/Char
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
#ifndef MOTIONCP_SERVER_APP_H
#define MOTIONCP_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTIONCP_Context_Init(void);
void MOTIONCP_Set_Notification_Status(uint8_t status);
void MOTIONCP_Send_Notification_Task(void);
void MOTIONCP_CarryPosition_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONCP_SERVER_APP_H */

