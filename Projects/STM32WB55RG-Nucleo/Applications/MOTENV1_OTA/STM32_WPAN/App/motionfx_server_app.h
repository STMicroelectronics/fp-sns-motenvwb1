/**
  ******************************************************************************
  * @file    motionfx_server_app.h
  * @brief   Handle SW/Sensor Data Fusion and ECompass Service/Char
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef MOTIONFX_SERVER_APP_H
#define MOTIONFX_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "iks01a3_motion_sensors.h"
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTIONFX_Context_Init(void);
void MOTIONFX_Set_Quat_Notification_Status(uint8_t status);
void MOTIONFX_Set_ECompass_Notification_Status(uint8_t status);
void MOTIONFX_Send_Quat_Notification_Task(void);
void MOTIONFX_Send_ECompass_Notification_Task(void);

uint8_t MOTIONFX_Get_MagCalStatus(void);
IKS01A3_MOTION_SENSOR_Axes_t *MOTIONFX_Get_MAG_Offset(void);

void MOTIONFX_ReCalibration(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONFX_SERVER_APP_H */
