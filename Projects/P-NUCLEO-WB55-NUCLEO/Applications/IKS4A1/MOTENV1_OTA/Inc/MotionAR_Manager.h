/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MotionAR_Manager.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the MotionAR_Manager.c file
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
#ifndef MOTIONAR_MANAGER_H
#define MOTIONAR_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <string.h>
#include "motion_ar.h"

/* Exported Functions Prototypes ---------------------------------------------*/
void MotionAR_manager_init(void);
void MotionAR_manager_run(MAR_input_t *data_in, MAR_output_t *data_out, uint32_t timestamp);
void MotionAR_manager_get_version(char *version, uint8_t *length);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONAR_MANAGER_H */

