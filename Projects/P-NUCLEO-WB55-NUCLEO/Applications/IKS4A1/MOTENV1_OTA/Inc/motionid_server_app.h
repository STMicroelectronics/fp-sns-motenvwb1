/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motionid_server_app.h
  * @brief   Handle SW/Motion Intensity Service/Char
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
#ifndef MOTIONID_SERVER_APP_H
#define MOTIONID_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTIONID_Context_Init(void);
void MOTIONID_Set_Notification_Status(uint8_t status);
void MOTIONID_Send_Notification_Task(void);
void MOTIONID_IntensityDet_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONID_SERVER_APP_H */

