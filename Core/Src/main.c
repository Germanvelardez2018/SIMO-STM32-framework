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

//Simo
#include "stdio.h"
#include "uart.h"
#include "spi.h"     
#include "config.h"
#include "timer.h"
#include "gpio.h"
#include "clock_config.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define TIME_COUNTS 10
/* USER CODE END Includes */


uint32_t volatile ena = 0;


static void __IRQ_GPIO_EXT(uint16_t pin){

     ena = 1;

}




/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{


  HAL_Init();

  

  /* Configure the system clock */
  simo_clock_config();
  simo_gpio_set(SIMO_GPIO_18,SIMO_GPIO_OUT);
  simo_gpio_set(SIMO_GPIO_19,SIMO_GPIO_EXT_IT_RISING);//PB3
  simo_gpio_set_extern_event_callback(__IRQ_GPIO_EXT);
  simo_gpio_ena_irq(SIMO_GPIO_19,1); // Habilito interrupciones
  while (1)
  {  
    HAL_Delay(100);
    if(ena == 1) simo_gpio_toogle(SIMO_GPIO_18);
  }
  /* USER CODE END 3 */
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

