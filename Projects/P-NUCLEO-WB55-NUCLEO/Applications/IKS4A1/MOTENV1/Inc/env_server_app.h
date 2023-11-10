
/**
  ******************************************************************************
  * @file    env_server_app.h
  * @brief   Handle HW/Environmental Service/Char
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
#ifndef ENV_SERVER_APP_H
#define ENV_SERVER_APP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/

/**
 * @brief  HW/Environmental Service/Char Context structure definition
 */
typedef struct
{
  uint8_t  NotificationStatus;

  int32_t PressureValue;
  uint16_t HumidityValue;
  int16_t TemperatureValue[2];
  uint8_t hasPressure;
  uint8_t hasHumidity;
  uint8_t hasTemperature;
} ENV_Server_App_Context_t;

/* Exported constants --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void ENV_Context_Init(void);
void ENV_Set_Notification_Status(uint8_t status);
void ENV_Send_Notification_Task(void);
void ENV_Update(void);

#ifdef __cplusplus
}
#endif

#endif /* ENV_SERVER_APP_H */

