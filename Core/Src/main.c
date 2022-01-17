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
#include "memory_store.h"
#include "AT45DB041E.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#define TIME_COUNTS 10
#define CS_PIN     SIMO_GPIO_22

/* USER CODE END Includes */









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

 simo_spi_init(SPI_A,SIMO_SPI_PRESCALER_4);
 simo_gpio_write(CS_PIN,0);
 simo_gpio_write(SIMO_GPIO_18,0);
  //AT45DB041E_start_config(SPI_A,CS_PIN);
#define BUFFER_SIZE 100


uint8_t msg[BUFFER_SIZE]="SIMOPRO: SISTEMA DE MONITOREO 4G \r\n";
#define LEN_MSG strlen(msg) -1
uint8_t buffer_rx[BUFFER_SIZE];
#define ADDRESS_PAGE    120

AT45DB041E_write_data(SPI_A,CS_PIN,msg,LEN_MSG,ADDRESS_PAGE,0);
HAL_Delay(2000);

HAL_Delay(2000);

//uint32_t  ret = check_id(SPI_A,CS_PIN);
//AT45DB041E_full_erase(SPI_A,CS_PIN);
  AT45DB041E_write_data(SPI_A,CS_PIN,msg,LEN_MSG,ADDRESS_PAGE,0);
    HAL_Delay(1000);
   // AT45DB041E_write_data(SPI_A,CS_PIN,msg,14,ADDRESS_PAGE,0);
    AT45DB041E_read_data(SPI_A,CS_PIN,buffer_rx,LEN_MSG,ADDRESS_PAGE,0);
  uint32_t ok = 1;
  while (1)
  {  

  
    

   
    simo_uart_write(UART_B,"lectura:\n\r",10,100,0);

    simo_uart_write(UART_B,buffer_rx,LEN_MSG,100,0);
    simo_uart_write(UART_B,"\n",1,100,0);

   

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

