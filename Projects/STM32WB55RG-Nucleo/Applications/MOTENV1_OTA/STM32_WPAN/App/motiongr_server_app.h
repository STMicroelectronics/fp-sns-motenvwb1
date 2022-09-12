/**
  ******************************************************************************
  * @file    motiongr_server_app.h
  * @brief   Handle SW/Gesture Recognition Service/Char
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
#ifndef MOTIONGR_SERVER_APP_H
#define MOTIONGR_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void MOTIONGR_Context_Init(void);
void MOTIONGR_Set_Notification_Status(uint8_t status);
void MOTIONGR_Send_Notification_Task(void);
void MOTIONGR_GestureRec_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONGR_SERVER_APP_H */

