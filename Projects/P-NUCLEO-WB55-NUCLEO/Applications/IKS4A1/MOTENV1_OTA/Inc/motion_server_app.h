/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    motion_server_app.h
  * @brief   Handle Motion (Acc/Gyro/Mag) Service
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
#ifndef MOTION_SERVER_APP_H
#define MOTION_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "iks4a1_motion_sensors.h"
/* Exported types ------------------------------------------------------------*/

/**
  * @brief  Motion Service/Char Context structure definition
  */
typedef struct
{
  uint8_t  NotificationStatus;

  IKS4A1_MOTION_SENSOR_Axes_t acceleration;
  IKS4A1_MOTION_SENSOR_Axes_t angular_velocity;
  IKS4A1_MOTION_SENSOR_Axes_t magnetic_field;
  uint8_t hasAcc;
  uint8_t hasGyro;
  uint8_t hasMag;
} MOTION_Server_App_Context_t;

/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTION_Context_Init(void);
void MOTION_Set_Notification_Status(uint8_t status);
void MOTION_Send_Notification_Task(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTION_SERVER_APP_H */

