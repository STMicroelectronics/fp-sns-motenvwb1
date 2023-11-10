
/**
  ******************************************************************************
  * @file    MotionFX_Manager.h
  * @author  MEMS Software Solutions Team
  * @brief   This file contains definitions for the MotionFX_Manager.c file.
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
#ifndef MOTIONFX_MANAGER_H
#define MOTIONFX_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "string.h"

#include "motion_fx.h"

/* Extern variables ----------------------------------------------------------*/
/* Exported Macros -----------------------------------------------------------*/
/* Exported Types ------------------------------------------------------------*/
/* Imported Variables --------------------------------------------------------*/
/* Exported Functions Prototypes ---------------------------------------------*/
void MotionFX_manager_init(void);

void MotionFX_manager_run(MFX_input_t *data_in, MFX_output_t *data_out, float delta_time);

void MotionFX_manager_start_6X(void);
void MotionFX_manager_stop_6X(void);
void MotionFX_manager_start_9X(void);
void MotionFX_manager_stop_9X(void);
void MotionFX_manager_get_version(char *version, int *length);

void MotionFX_manager_MagCal_run(MFX_MagCal_input_t *data_in, MFX_MagCal_output_t *data_out);

void MotionFX_manager_MagCal_start(int sampletime);
void MotionFX_manager_MagCal_stop(int sampletime);

char MotionFX_LoadMagCalFromNVM(unsigned short int dataSize, unsigned int *data);
char MotionFX_SaveMagCalInNVM(unsigned short int dataSize, unsigned int *data);

#ifdef __cplusplus
}
#endif

#endif /* MOTIONFX_MANAGER_H */

