/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_motenv1.h
  * @author  System Research & Applications Team - Catania Lab.
  * @brief   This file provides code for the configuration FP-SNS-MOTENVWB1
  *          application instances.
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
#ifndef __APP_FP_SNS_MOTENVWB1_H
#define __APP_FP_SNS_MOTENVWB1_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_nucleo.h"

/* Exported Defines ----------------------------------------------------------*/

/* Imported Variables --------------------------------------------------------*/

/* Exported Variables --------------------------------------------------------*/

/* Exported Functions --------------------------------------------------------*/
void MX_MOTENV1_Init(void);
void MX_MOTENV1_Process(void);
void APP_BLE_Key_Button1_Action(void);
void MOTION_Set2G_Accelerometer_FullScale(void);
void set_mems_int_pin(void);
void mems_int_isr(void);

#ifdef __cplusplus
}
#endif

#endif /* __APP_FP_SNS_MOTENVWB1_H */

