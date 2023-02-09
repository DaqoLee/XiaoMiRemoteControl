/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define BUZZER_Pin GPIO_PIN_13
#define BUZZER_GPIO_Port GPIOC
#define LED1_Pin GPIO_PIN_6
#define LED1_GPIO_Port GPIOA
#define KEY1_Pin GPIO_PIN_7
#define KEY1_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_10
#define KEY3_GPIO_Port GPIOB
#define KEY2_Pin GPIO_PIN_11
#define KEY2_GPIO_Port GPIOB
#define ePA_DC_Pin GPIO_PIN_12
#define ePA_DC_GPIO_Port GPIOB
#define ePA_BUSY_Pin GPIO_PIN_8
#define ePA_BUSY_GPIO_Port GPIOA
#define ePA_RST_Pin GPIO_PIN_11
#define ePA_RST_GPIO_Port GPIOA
#define ePA_CS_Pin GPIO_PIN_12
#define ePA_CS_GPIO_Port GPIOA
#define nRF_IRQ_Pin GPIO_PIN_15
#define nRF_IRQ_GPIO_Port GPIOA
#define nRF_CSN_Pin GPIO_PIN_6
#define nRF_CSN_GPIO_Port GPIOB
#define nRF_CE_Pin GPIO_PIN_7
#define nRF_CE_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
