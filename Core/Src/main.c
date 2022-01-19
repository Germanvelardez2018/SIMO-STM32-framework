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
#include "rtc.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define TIME_COUNTS 10
#define CS_PIN     SIMO_GPIO_22

/* USER CODE END Includes */



void _check_ret(uint32_t ret){
  if(( ret) == 1 ){
   simo_gpio_write(SIMO_GPIO_18,1);
   HAL_Delay(500);
   simo_gpio_write(SIMO_GPIO_18,0);
}
}


static void __rtc_irq(void){
  simo_gpio_write(SIMO_GPIO_18,1);
}



static void rtc_printf(uint8_t h, uint8_t m , uint8_t s){

  uint8_t buffer[100]={0};
  sprintf(buffer,"\r\n h:m:s ==> %d : %d :%d",h,m,s);
  simo_uart_write(UART_B,buffer,strlen(buffer),200,0);


}



      /**SPI1 GPIO Configuration
       * PB6  como chip select
        PB3     ------> SPI1_SCK
        PB4     ------> SPI1_MISO
        PB5     ------> SPI1_MOSI
        */



/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{


  HAL_Init();

#define BAUDRATE  115200
  /* Configure the system clock */
simo_clock_config();
simo_uart_init(UART_B,BAUDRATE);

 simo_gpio_set(SIMO_GPIO_18,SIMO_GPIO_OUT);
 simo_gpio_set(CS_PIN,SIMO_GPIO_OUT); // spi

 simo_gpio_write(CS_PIN,0);
 simo_gpio_write(SIMO_GPIO_18,0);

  simo_rtc_init();
  simo_rtc_set_alarm_callback(__rtc_irq);
  simo_rtc_ena_irq(1);
  simo_rtc_set_time(18,6,0);
  simo_rtc_set_alarm(18,6,10);

 


  while (1)
  {  

  
  uint8_t  h,m,s ; 

    simo_rtc_get_time(&h,&m,&s);

    rtc_printf(h,m,s);
   

   

    HAL_Delay(1000);

 

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

