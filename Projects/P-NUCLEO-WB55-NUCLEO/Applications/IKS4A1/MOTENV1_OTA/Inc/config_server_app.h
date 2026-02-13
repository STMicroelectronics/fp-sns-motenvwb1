/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    config_server_app.h
  * @brief   Handle Configuration Service/Char
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
#ifndef CONFIG_SERVER_APP_H
#define CONFIG_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void CONFIG_Context_Init(void);
void CONFIG_Set_Notification_Status(uint8_t status);
void CONFIG_Set_FirstConnection_Config(uint8_t status);
uint8_t CONFIG_Get_Notification_Status(void);
uint8_t CONFIG_Get_FirstConnection_Config(void);
void CONFIG_Send_Notification(uint32_t Feature, uint8_t Command, uint8_t data);
uint8_t CONFIG_Parse_Command(uint8_t *att_data, uint8_t data_length);

#ifdef __cplusplus
}
#endif

#endif /* CONFIG_SERVER_APP_H */

