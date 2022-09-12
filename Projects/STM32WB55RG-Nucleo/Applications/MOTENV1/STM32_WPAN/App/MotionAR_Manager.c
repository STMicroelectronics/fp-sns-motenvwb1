/**
  ******************************************************************************
  * @file    MotionAR_Manager.c
  * @author  MEMS Software Solutions Team
  * @brief   This file contains Activity Recognition interface functions
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

/* Includes ------------------------------------------------------------------*/
#include <limits.h>
#include "MotionAR_Manager.h"

/** @addtogroup MOTION_APPLICATIONS MOTION APPLICATIONS
 * @{
 */

/** @addtogroup ACTIVITY_RECOGNITION ACTIVITY RECOGNITION
 * @{
 */

/* Exported functions --------------------------------------------------------*/
/**
 * @brief  Initialize the MotionAR engine
 * @param  None
 * @retval None
 */
void MotionAR_manager_init(void)
{
  char acc_orientation[3];

  MotionAR_Initialize();

#ifdef USE_IKS01A3
  acc_orientation[0] = 's';
  acc_orientation[1] = 'e';
  acc_orientation[2] = 'u';
#endif

  MotionAR_SetOrientation_Acc(acc_orientation);
}

/**
 * @brief  Run Activity Recognition algorithm. This function collects and scale
 *         data from accelerometer and calls the Activity Recognition Algo
 * @param  data_in  Structure containing input data
 * @param  data_out Structure containing output data
 * @param  timestamp  Timestamp in [ms]
 * @retval None
 */
void MotionAR_manager_run(MAR_input_t *data_in, MAR_output_t *data_out, uint32_t timestamp)
{
  MotionAR_Update(data_in, data_out, (long int)(timestamp & LONG_MAX));
}

/**
 * @brief  Get the library version
 * @param  version  Library version string (must be array of 35 char)
 * @param  length  Library version string length
 * @retval None
 */
void MotionAR_manager_get_version(char *version, int *length)
{
  *length = (int)MotionAR_GetLibVersion(version);
}

/**
 * @}
 */

/**
 * @}
 */

