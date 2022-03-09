/**
 * @file olessd130g.c
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */




#include "main.h"
// Simo
#include "delay.h"
#include "stdio.h"

#include "config.h"
#include "gpio.h"
#include "clock_config.h"
#include "ssd1306_tests.h"


//Drivers

#include "ssd1306.h"



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


  
}








/**
 * @brief  The application entry point.
 * @retval int
 */

int main2(void)
{


setup();

  simo_gpio_toogle(SIMO_GPIO_18);
  simo_delay_ms(500);
  simo_gpio_toogle(SIMO_GPIO_18);
  simo_delay_ms(500);
  simo_gpio_toogle(SIMO_GPIO_18);
  simo_delay_ms(500);


  while(1){

    
    ssd1306_TestAll();
    simo_gpio_toogle(SIMO_GPIO_18);
    simo_delay_ms(500);
    
  }
    
}



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