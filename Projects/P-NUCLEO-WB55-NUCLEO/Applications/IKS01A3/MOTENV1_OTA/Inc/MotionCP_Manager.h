/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MotionCP_Manager.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the MotionCP_Manager.c file.
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
#ifndef MOTIONCP_MANAGER_H
#define MOTIONCP_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "string.h"
#include "motion_cp.h"

/* Extern variables ----------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Imported Variables --------------------------------------------------------*/
/* Exported Functions Prototypes ---------------------------------------------*/
void MotionCP_manager_init(void);
void MotionCP_manager_run(MCP_input_t *data_in, MCP_output_t *data_out);
void MotionCP_manager_get_version(char *version, uint8_t *length);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONCP_MANAGER_H */
