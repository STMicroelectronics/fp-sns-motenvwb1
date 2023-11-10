
/**
  ******************************************************************************
  * @file    motionpm_server_app.h
  * @brief   Handle SW/Motion Intensity Service/Char
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
#ifndef MOTIONPM_SERVER_APP_H
#define MOTIONPM_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTIONPM_Context_Init(void);
void MOTIONPM_Set_Notification_Status(uint8_t status);
void MOTIONPM_Send_Notification_Task(void);
void MOTIONPM_Pedometer_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONPM_SERVER_APP_H */

