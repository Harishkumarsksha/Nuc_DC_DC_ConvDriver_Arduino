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
#include "stm32h7xx_hal.h"

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
// void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define UVLO_Pin GPIO_PIN_0
#define UVLO_GPIO_Port GPIOF
#define EN_Pin GPIO_PIN_1
#define EN_GPIO_Port GPIOF
#define DIR_Pin GPIO_PIN_2
#define DIR_GPIO_Port GPIOF
#define nFault_Pin GPIO_PIN_3
#define nFault_GPIO_Port GPIOF
#define Bleed_Pin GPIO_PIN_4
#define Bleed_GPIO_Port GPIOF
#define LD1_Pin GPIO_PIN_0
#define LD1_GPIO_Port GPIOB
#define LD3_Pin GPIO_PIN_14
#define LD3_GPIO_Port GPIOB
#define STLINK_RX_Pin GPIO_PIN_8
#define STLINK_RX_GPIO_Port GPIOD
#define STLINK_TX_Pin GPIO_PIN_9
#define STLINK_TX_GPIO_Port GPIOD
#define USB_OTG_FS_PWR_EN_Pin GPIO_PIN_10
#define USB_OTG_FS_PWR_EN_GPIO_Port GPIOD
#define USB_OTG_FS_OVCR_Pin GPIO_PIN_7
#define USB_OTG_FS_OVCR_GPIO_Port GPIOG
#define LD2_Pin GPIO_PIN_1
#define LD2_GPIO_Port GPIOE



// Cell Nodes 

#define CB1_GPIO_Port GPIOF
#define CB1 GPIO_PIN_5
#define CB2_GPIO_Port GPIOF
#define CB2 GPIO_PIN_6
#define CB3_GPIO_Port GPIOF
#define CB3 GPIO_PIN_7
#define CB4_GPIO_Port GPIOF
#define CB4 GPIO_PIN_8
#define CB5_GPIO_Port GPIOF
#define CB5 GPIO_PIN_9
#define CB6_GPIO_Port GPIOF
#define CB6 GPIO_PIN_10
#define CB7_GPIO_Port GPIOE
#define CB7 GPIO_PIN_2

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
