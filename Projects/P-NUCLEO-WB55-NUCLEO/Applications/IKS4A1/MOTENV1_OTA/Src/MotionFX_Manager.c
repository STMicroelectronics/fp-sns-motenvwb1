/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    MotionFX_Manager.c
  * @author  MEMS Software Solutions Team
  * @brief   This file contains Datalog Fusion interface functions
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

/* Includes ------------------------------------------------------------------*/
#include "MotionFX_Manager.h"

/** @addtogroup MOTION_APPLICATIONS MOTION APPLICATIONS
  * @{
  */

/** @addtogroup DATALOG_FUSION DATALOG FUSION
  * @{
  */

/* Extern variables ----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
#define SAMPLETODISCARD                 15
#define GBIAS_ACC_TH_SC_6X              (2.0f*0.000765f)
#define GBIAS_GYRO_TH_SC_6X             (2.0f*0.002f)
#define GBIAS_MAG_TH_SC_6X              (2.0f*0.001500f)
#define GBIAS_ACC_TH_SC_9X              (2.0f*0.000765f)
#define GBIAS_GYRO_TH_SC_9X             (2.0f*0.002f)
#define GBIAS_MAG_TH_SC_9X              (2.0f*0.001500f)

#define DECIMATION                      1U

#define STATE_SIZE                      (size_t)(2432)

/* Private variables ---------------------------------------------------------*/
static uint8_t mfxstate_pt[STATE_SIZE];
static MFX_knobs_t iKnobs;
static MFX_knobs_t *ipKnobs = &iKnobs;

static volatile uint32_t sampleToDiscard = SAMPLETODISCARD;
static uint32_t discardedCount = 0;

/* Private typedef -----------------------------------------------------------*/
/* Exported function prototypes ----------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/**
  * @brief  Initialises MotionFX algorithm
  * @param  None
  * @retval None
  */
void MotionFX_manager_init(void)
{
  char acc_orientation[4];
  char gyro_orientation[4];
  char mag_orientation[4];

  acc_orientation[0] = 's';
  acc_orientation[1] = 'e';
  acc_orientation[2] = 'u';

  gyro_orientation[0] = 's';
  gyro_orientation[1] = 'e';
  gyro_orientation[2] = 'u';

  mag_orientation[0] = 'n';
  mag_orientation[1] = 'e';
  mag_orientation[2] = 'u';

  MotionFX_initialize((MFXState_t *)mfxstate_pt);

  MotionFX_getKnobs(mfxstate_pt, ipKnobs);

  (void)strcpy(ipKnobs->acc_orientation, acc_orientation);
  (void)strcpy(ipKnobs->gyro_orientation, gyro_orientation);
  (void)strcpy(ipKnobs->mag_orientation, mag_orientation);

  ipKnobs->gbias_acc_th_sc = GBIAS_ACC_TH_SC_6X;
  ipKnobs->gbias_gyro_th_sc = GBIAS_GYRO_TH_SC_6X;
  ipKnobs->gbias_mag_th_sc = GBIAS_MAG_TH_SC_6X;

  ipKnobs->gbias_acc_th_sc = GBIAS_ACC_TH_SC_9X;
  ipKnobs->gbias_gyro_th_sc = GBIAS_GYRO_TH_SC_9X;
  ipKnobs->gbias_mag_th_sc = GBIAS_MAG_TH_SC_9X;

  ipKnobs->output_type = MFX_ENGINE_OUTPUT_ENU;
  ipKnobs->LMode = 1;
  ipKnobs->modx = DECIMATION;

  MotionFX_setKnobs(mfxstate_pt, ipKnobs);

  MotionFX_enable_6X(mfxstate_pt, MFX_ENGINE_DISABLE);
  MotionFX_enable_9X(mfxstate_pt, MFX_ENGINE_DISABLE);
}

/**
  * @brief  Run sensor fusion algorithm
  * @param  None
  * @retval None
  */
void MotionFX_manager_run(MFX_input_t *data_in, MFX_output_t *data_out, float delta_time)
{
  if (discardedCount == sampleToDiscard)
  {
    MotionFX_propagate(mfxstate_pt, data_out, data_in, &delta_time);
    MotionFX_update(mfxstate_pt, data_out, data_in, &delta_time, NULL);
  }
  else
  {
    discardedCount++;
  }
}

/**
  * @brief  Start 6 axes MotionFX engine
  * @param  None
  * @retval None
  */
void MotionFX_manager_start_6X(void)
{
  MotionFX_enable_6X(mfxstate_pt, MFX_ENGINE_ENABLE);
}

/**
  * @brief  Stop 6 axes MotionFX engine
  * @param  None
  * @retval None
  */
void MotionFX_manager_stop_6X(void)
{
  MotionFX_enable_6X(mfxstate_pt, MFX_ENGINE_DISABLE);
}

/**
  * @brief  Start 9 axes MotionFX engine
  * @param  None
  * @retval None
  */
void MotionFX_manager_start_9X(void)
{
  MotionFX_enable_9X(mfxstate_pt, MFX_ENGINE_ENABLE);
}

/**
  * @brief  Stop 9 axes MotionFX engine
  * @param  None
  * @retval None
  */
void MotionFX_manager_stop_9X(void)
{
  MotionFX_enable_9X(mfxstate_pt, MFX_ENGINE_DISABLE);
}

/**
  * @brief  Get the library version
  * @param  version  Library version string (must be array of 35 char)
  * @param  length  Library version string length
  * @retval None
  */
void MotionFX_manager_get_version(char *version, uint8_t *length)
{
  *length = (uint8_t)MotionFX_GetLibVersion(version);
}

/**
  * @brief  Run magnetometer calibration algorithm
  * @param  None
  * @retval None
  */
void MotionFX_manager_MagCal_run(MFX_MagCal_input_t *data_in, MFX_MagCal_output_t *data_out)
{
  MotionFX_MagCal_run(data_in);
  MotionFX_MagCal_getParams(data_out);
}

/**
  * @brief  Start magnetometer calibration
  * @param  None
  * @retval None
  */
void MotionFX_manager_MagCal_start(int sampletime)
{
  MotionFX_MagCal_init(sampletime, 1);
}

/**
  * @brief  Stop magnetometer calibration
  * @param  None
  * @retval None
  */
void MotionFX_manager_MagCal_stop(int sampletime)
{
  MotionFX_MagCal_init(sampletime, 0);
}

/**
  * @brief  Load calibration parameter from memory
  * @param  dataSize length of the data
  * @param  data pointer to the data
  * @retval (1) fail, (0) success
  */
char MotionFX_LoadMagCalFromNVM(uint16_t dataSize, uint32_t *data)
{
#if ((defined (MOTION_FX_STORE_CALIB_FLASH)))
  RecallCalibrationFromMemory(dataSize / 4, (uint32_t *) data);
  return (char)0;
#else
  return (char)1;
#endif /* defined (MOTION_FX_STORE_CALIB_FLASH) */
}

/**
  * @brief  Save calibration parameter to memory
  * @param  dataSize length of the data
  * @param  data pointer to the data
  * @retval (1) fail, (0) success
  */
char MotionFX_SaveMagCalInNVM(uint16_t dataSize, uint32_t *data)
{
#if ((defined (MOTION_FX_STORE_CALIB_FLASH)))
  SaveCalibrationToMemory(dataSize / 4, (uint32_t *) data);
  return (char)0;
#else
  return (char)1;
#endif /* defined (MOTION_FX_STORE_CALIB_FLASH) */
}

/**
  * @}
  */

/**
  * @}
  */
