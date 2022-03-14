/**
 * @file main.c  ( manejo del modulo SIM7000G)
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-03
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "main.h"
// Simo

#include "memory_store.h" // Necesario para almacenar los datos en memoria flash externa
#include "power_save.h"   //Necesario para almacenar datos en backup register del RTC







/**
 * @brief  The application entry point.
 * @retval int
 */

int main2(void)
{

    // Estado del dispositivo, 
    // transmicion en vivo o transmicion desde memoria memoria.


    // Configuracion
    while(1){
    

    

    // Dormir el microcontrolador


    // Despertar

    //Tomar medicion y transmitirlos





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
