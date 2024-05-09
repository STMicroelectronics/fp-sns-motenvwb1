/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    remap_conf.h
  * @author  System Research & Applications Team - Catania Lab.
  * @brief   Bluetooth support
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
#ifndef REMAP_CONF_H
#define REMAP_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#include "iks01a3_env_sensors.h"
#include "iks01a3_motion_sensors.h"
#include "iks01a3_motion_sensors_ex.h"
/*************************************/
/*  Remapping istance sensor defines */
/*************************************/
/* Motion Sensor Istance */
#define ACCELERO_AND_GYRO_INSTANCE        IKS01A3_LSM6DSO_0
#define ACCELERO_INSTANCE                 IKS01A3_LSM6DSO_0
#define GYRO_INSTANCE                     IKS01A3_LSM6DSO_0
#define ACCELERO_INSTANCE_2               IKS01A3_LIS2DW12_0
#define MAGNETO_INSTANCE                  IKS01A3_LIS2MDL_0

/* Environmental Sensor Istance */
#define TEMPERATURE_INSTANCE_1            IKS01A3_HTS221_0
#define HUMIDITY_INSTANCE                 IKS01A3_HTS221_0
#define HUM_AND_TEMP_INSTANCE             IKS01A3_HTS221_0
#define TEMPERATURE_INSTANCE_2            IKS01A3_LPS22HH_0
#define PRESSURE_INSTANCE                 IKS01A3_LPS22HH_0
#define PRESS_AND_TEMP_INSTANCE           IKS01A3_LPS22HH_0
#define NBR_ENV_INSTANCES                 IKS01A3_ENV_INSTANCES_NBR
/*************************************/

/********************************/
/*  Remapping APIsensor defines */
/********************************/
/* Environmental Sensor API */
#define ENV_SENSOR_Init                                 IKS01A3_ENV_SENSOR_Init
#define ENV_SENSOR_Get_Value                            IKS01A3_ENV_SENSOR_GetValue

/* Motion Sensor API */
#define MOTION_SENSOR_Init                              IKS01A3_MOTION_SENSOR_Init

#define MOTION_SENSOR_Axes_t                            IKS01A3_MOTION_SENSOR_Axes_t
#define MOTION_SENSOR_Event_Status_t                    IKS01A3_MOTION_SENSOR_Event_Status_t

#define MOTION_SENSOR_GetAxes                           IKS01A3_MOTION_SENSOR_GetAxes
#define MOTION_SENSOR_Get_Event_Status                  IKS01A3_MOTION_SENSOR_Get_Event_Status

#define MOTION_SENSOR_SetFullScale                      IKS01A3_MOTION_SENSOR_SetFullScale

#define MOTION_SENSOR_SetOutputDataRate                 IKS01A3_MOTION_SENSOR_SetOutputDataRate
#define MOTION_SENSOR_GetOutputDataRate                 IKS01A3_MOTION_SENSOR_GetOutputDataRate

#define MOTION_SENSOR_Enable_Tilt_Detection             IKS01A3_MOTION_SENSOR_Enable_Tilt_Detection
#define MOTION_SENSOR_Disable_Tilt_Detection            IKS01A3_MOTION_SENSOR_Disable_Tilt_Detection
#define MOTION_SENSOR_Enable_Wake_Up_Detection          IKS01A3_MOTION_SENSOR_Enable_Wake_Up_Detection
#define MOTION_SENSOR_Disable_Wake_Up_Detection         IKS01A3_MOTION_SENSOR_Disable_Wake_Up_Detection
#define MOTION_SENSOR_Enable_Double_Tap_Detection       IKS01A3_MOTION_SENSOR_Enable_Double_Tap_Detection
#define MOTION_SENSOR_Disable_Double_Tap_Detection      IKS01A3_MOTION_SENSOR_Disable_Double_Tap_Detection
#define MOTION_SENSOR_Enable_Single_Tap_Detection       IKS01A3_MOTION_SENSOR_Enable_Single_Tap_Detection
#define MOTION_SENSOR_Disable_Single_Tap_Detection      IKS01A3_MOTION_SENSOR_Disable_Single_Tap_Detection
#define MOTION_SENSOR_Enable_Pedometer                  IKS01A3_MOTION_SENSOR_Enable_Pedometer
#define MOTION_SENSOR_Disable_Pedometer                 IKS01A3_MOTION_SENSOR_Disable_Pedometer
#define MOTION_SENSOR_Reset_Step_Counter                IKS01A3_MOTION_SENSOR_Reset_Step_Counter
#define MOTION_SENSOR_Get_Step_Count                    IKS01A3_MOTION_SENSOR_Get_Step_Count
#define MOTION_SENSOR_Enable_Free_Fall_Detection        IKS01A3_MOTION_SENSOR_Enable_Free_Fall_Detection
#define MOTION_SENSOR_Set_Tap_Threshold                 IKS01A3_MOTION_SENSOR_Set_Tap_Threshold
#define MOTION_SENSOR_Disable_Free_Fall_Detection       IKS01A3_MOTION_SENSOR_Disable_Free_Fall_Detection
#define MOTION_SENSOR_Set_Free_Fall_Threshold           IKS01A3_MOTION_SENSOR_Set_Free_Fall_Threshold
#define MOTION_SENSOR_Enable_6D_Orientation             IKS01A3_MOTION_SENSOR_Enable_6D_Orientation
#define MOTION_SENSOR_Disable_6D_Orientation            IKS01A3_MOTION_SENSOR_Disable_6D_Orientation
#define MOTION_SENSOR_Get_6D_Orientation_XL             IKS01A3_MOTION_SENSOR_Get_6D_Orientation_XL
#define MOTION_SENSOR_Get_6D_Orientation_XH             IKS01A3_MOTION_SENSOR_Get_6D_Orientation_XH
#define MOTION_SENSOR_Get_6D_Orientation_YL             IKS01A3_MOTION_SENSOR_Get_6D_Orientation_YL
#define MOTION_SENSOR_Get_6D_Orientation_YH             IKS01A3_MOTION_SENSOR_Get_6D_Orientation_YH
#define MOTION_SENSOR_Get_6D_Orientation_ZL             IKS01A3_MOTION_SENSOR_Get_6D_Orientation_ZL
#define MOTION_SENSOR_Get_6D_Orientation_ZH             IKS01A3_MOTION_SENSOR_Get_6D_Orientation_ZH

#ifdef __cplusplus
}
#endif
#endif /*REMAP_CONF_H*/

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
