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

// Simo
#include "stdio.h"
#include "uart.h"
#include "spi.h"
#include "config.h"
#include "timer.h"
#include "gpio.h"
#include "clock_config.h"
#include "rtc.h"
#include "power_save.h"
#include "simcom.h"
#include "string.h"



/* USER CODE END Includes */




/**
 * @brief Funcion de inicio de perifericos. 
 * 
 * @return ** void 
 */
static void setup(void){

  // Aqui va la configuracion inicial
  HAL_Init();
  simo_clock_config();
  simo_gpio_set(SIMO_GPIO_18,SIMO_GPIO_OUT);
  
  sim_init();
  

}



/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

 

 

  setup();

  sim_set_pwr_gps(1);
  sim_get_version();


  uint32_t ena = 1;  // en modo debug ena = 1 ,
    
  while(1){

    // Habilito o deshabilito el echo en la respuesta
  //   sim_set_echo(ena);

      HAL_Delay(2500);
     
      simo_gpio_toogle(SIMO_GPIO_18);
      HAL_Delay(1000);

    
    sim_get_gps_info();
    HAL_Delay(10000);

      

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

#ifdef USE_FULL_ASSERT
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
