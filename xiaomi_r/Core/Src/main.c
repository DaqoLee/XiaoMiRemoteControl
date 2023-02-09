/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
#include "stdio.h"
#include "stdarg.h"	
#include "string.h"	
#include "nRF24L01.h"
#include "Remote.h"
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

uint8_t  tmp_buf[32] = {0};
uint8_t  temp1 = 4;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_TIM14_Init();
  MX_TIM16_Init();
  MX_TIM17_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  
  HAL_Delay(50);
  NRF24L01_Init();
  	HAL_Delay(50);
  while(NRF24L01_Check())
	{
		printf("硬件查寻不到NRF24L01无线模块\n"); 
 		HAL_Delay(1000);
	}
		HAL_Delay(50);
	printf("NRF24L01无线模块硬件连接正常\n");
	HAL_Delay(50);
	NRF24L01_RX_Mode();
  printf("进入数据接收模式\n");
  HAL_Delay(50);
  
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim3,TIM_CHANNEL_3);
 //  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 1500);
  HAL_TIM_PWM_Start(&htim14,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim16,TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim17,TIM_CHANNEL_1);
  
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,  1000);
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,  1000);
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,  1000);
  __HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 1000);
  __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 1000);
  __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 1000);
//  
//  HAL_Delay(1000);
  
//  HAL_Delay(500);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int16_t tarx=0,tary=0;
  int16_t speed1=0,speed2=0;
  while (1)
  {
   
		if( Remote_Receive())
    {
      tarx=Remote.ch4 -1500;
      tary=Remote.ch5 -1500;
      
      speed1=(tary+tarx)*2;
      speed1=speed1>=1000?1000:speed1;
      speed1=speed1<=100?0:speed1;
      
      speed2=(tary-tarx)*2;
      speed2=speed2>=1000?1000:speed2;
      speed2=speed2<=100?0:speed2;
      
      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2,  Remote.ch1);//1
      
      __HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, Remote.ch2);
      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1,  Remote.ch3);
      
      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3,  speed1+1000);    
      __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, speed2+1000);
      __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, Remote.ch6);
		 // printf("ch1:%d\t ch2:%d\t ch3:%d\t ch4:%d\t ch5:%d\t ch6:%d KeyL:%d  KeyR:%d\r\n",Remote.ch1,Remote.ch2,speed1,speed2,Remote.ch5,Remote.ch6,Remote.KeyStatusL,Remote.KeyStatusR);		
      printf("d:%d, %d, %d, %d, %d, %d \r\n",Remote.ch1,Remote.ch2,Remote.ch3, Remote.ch4,Remote.ch5,Remote.ch6);
		  //HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET);
    }
    else
    {
      HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET);
    }
    HAL_Delay(5); 
//      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 1200);
//      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 1200);
//      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 1200);
//      __HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 1200);
//      __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 1200);
//      __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 1200);
//    HAL_Delay(1000); 
//      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 1800);
//      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_2, 1800);
//      __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_3, 1800);
//      __HAL_TIM_SetCompare(&htim14, TIM_CHANNEL_1, 1800);
//      __HAL_TIM_SetCompare(&htim16, TIM_CHANNEL_1, 1800);
//      __HAL_TIM_SetCompare(&htim17, TIM_CHANNEL_1, 1800);
//    HAL_Delay(1000); 
//    
//     printf("test\r\n");
//    
//     HAL_Delay(100);
    
//    if(NRF24L01_RxPacket(tmp_buf) == 0)	
//		{
//			unsigned char i;
//			for(i=0;i<22;i++)
//			printf(" %x",tmp_buf[i]);
//			
//			printf("\r\n");
//		}
//    
    
    
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 8;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
