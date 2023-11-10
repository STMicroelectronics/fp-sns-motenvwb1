
/**
  ******************************************************************************
  * @file    MotionAW_Manager.c
  * @author  MEMS Software Solutions Team
  * @brief   This file contains Activity Recognition Wrist interface functions
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

/* Includes ------------------------------------------------------------------*/
#include "MotionAW_Manager.h"

/** @addtogroup MOTION_APPLICATIONS MOTION APPLICATIONS
 * @{
 */

/** @addtogroup ACTIVITY_RECOGNITION_WRIST ACTIVITY RECOGNITION WRIST
 * @{
 */

/* Private typedef -----------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
 * @brief  Initialises MotionAW algorithm
 * @param  None
 * @retval None
 */
void MotionAW_manager_init(void)
{
  char acc_orientation[3];

  MotionAW_Initialize();

  acc_orientation[0] = 's';
  acc_orientation[1] = 'e';
  acc_orientation[2] = 'u';

  MotionAW_SetOrientation_Acc(acc_orientation);
}

/**
 * @brief  Run activity recognition wrist algorithm. This function collects and scale data from accelerometer and calls the Activity Recognition Wrist Algo
 * @param  data_in  Structure containing input data
 * @param  data_out Structure containing output data
 * @retval None
 */
void MotionAW_manager_run(MAW_input_t *data_in, MAW_activity_t *data_out, int64_t timestamp)
{
  MAW_output_t data;

  MotionAW_Update(data_in, &data, timestamp);
  *data_out = data.current_activity;
}

/**
 * @brief  Get the library version
 * @param  version  Library version string (must be array of 35 char)
 * @param  length  Library version string length
 * @retval None
 */
void MotionAW_manager_get_version(char *version, int *length)
{
  *length = (int)MotionAW_GetLibVersion(version);
}

/**
 * @}
 */

/**
 * @}
 */

