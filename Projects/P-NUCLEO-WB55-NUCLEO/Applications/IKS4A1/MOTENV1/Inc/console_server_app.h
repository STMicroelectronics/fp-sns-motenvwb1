/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    console_server_app.h
  * @brief    andle Console Service/Chars
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
#ifndef CONSOLE_SERVER_APP_H
#define CONSOLE_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CONSOLE_Context_Init(void);
void CONSOLE_Set_Term_Notification_Status(uint8_t status);
void CONSOLE_Term_Update(uint8_t *data, uint8_t length);
void CONSOLE_Term_Update_AfterRead(void);
void CONSOLE_Set_Stderr_Notification_Status(uint8_t status);
void CONSOLE_Stderr_Update(uint8_t *data, uint8_t length);
void CONSOLE_Stderr_Update_AfterRead(void);

#ifdef __cplusplus
}
#endif

#endif /* CONSOLE_SERVER_APP_H */

