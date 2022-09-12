/**
  ******************************************************************************
  * @file    App/motionaw_server_app.h
  * @brief   MOTIONAW Server Application
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
#ifndef MOTIONAW_SERVER_APP_H
#define MOTIONAW_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTIONAW_Context_Init(void);
void MOTIONAW_Set_Notification_Status(uint8_t status);
void MOTIONAW_Send_Notification_Task(void);
void MOTIONAW_ActivityRec_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONAW_SERVER_APP_H */

