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
#define RX_BUFFER_LEN   100
#define TIMER     TIMER_C
#define UART      UART_B
uint32_t count = 0;
uint32_t pos_rx =0;
uint8_t  buffer_rx[RX_BUFFER_LEN]={0};
uint32_t counter = 0;
#define TIME_COUNTS 10
/* USER CODE END Includes */

static void MX_GPIO_Init(void);




static void __irq_spi_tx(){
    // HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin);

     simo_gpio_toogle(SIMO_GPIO_17);

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

  

  /* Initialize all configured peripherals */
  //MX_GPIO_Init();

   simo_gpio_set(SIMO_GPIO_17,SIMO_GPIO_OUT);
 
  
  


 // simo_uart_init(UART,115200);
  simo_spi_init(SPI_A,SIMO_SPI_PRESCALER_4);
  simo_spi_set_tx_rx_callback(SPI_A,__irq_spi_tx);
  simo_spi_ena_irq(SPI_A,1);
  




uint8_t data[4]={0,1,2,3};
uint8_t buffer_rx[4] = {0};
  while (1)
  {


    simo_spi_write_read(SPI_A,data,buffer_rx,4,1000,1);
    HAL_Delay(250);
  
  
  }
  /* USER CODE END 3 */
}









/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);

  /*Configure GPIO pin : PB2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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

