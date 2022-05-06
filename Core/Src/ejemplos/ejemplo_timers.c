
/**
 * @file ejemplo_timers.c
 * @author German Velardez (germanvelardez@gmail.com)
 * 
 * @brief Ejemplo de aplicacion simple funcionando con 2 timer. 
 * TTMERA se ejecuta cada 500ms y tooglea un led 
 * TIMERB se ejecuta cada 2500ms e imprime un mensaje por puerto UART. sin  UART_A (Pin A3 (RX)  y A2 (TX))
 * @version 0.1
 * @date 2022-02-02
 * 
 * @copyright Copyright (c) 2022
 * 
 */

 // Recordar configurar los siguientes elementos los flar para manejar UART (1 solo uart) y TIMER ( 2 timers)



#include "stdio.h"
#include "main.h"

// Simo
#include "uart.h"
#include "timer.h"
#include "gpio.h"
#include "clock_config.h"
#include "delay.h"



/* USER CODE END Includes */


#define LED_TOOGLE    SIMO_GPIO_18 // PB2
#define BAUDRATE      115200




// Callbacks para los timer


static void __CALLBACK_TIMERA(void){
  simo_gpio_toogle(SIMO_GPIO_18);
}

static void __CALLBACK_TIMERB(void){
  #define CALLBACK_MSG            "Estamos en el callback del timer B \r\n"
  #define ENA_INTERRUPTION        0 
  #define TIMEROUT                500    // Si ENA_INTERRUPTION es 1 entonces no hay timeout  
  simo_uart_write(UART_A,CALLBACK_MSG,strlen(CALLBACK_MSG),TIMEROUT,ENA_INTERRUPTION);

}


/**
 * @brief Funcion de inicio de perifericos. 
 * 
 * @return ** void 
 */
static void setup(void){

  #define BAUDRATE      115200
  #define UART           UART_A     

  // Aqui va la configuracion inicial
  HAL_Init();
  simo_clock_config();
  simo_uart_init(UART, BAUDRATE);

  //! Configuracion inicial de GPIO
  simo_gpio_set(SIMO_GPIO_18, SIMO_GPIO_OUT);

  // Configuracion del timer A
  simo_timer_config(TIMER_A,TIME_MS,500);
  
  simo_timer_set_event_callback(TIMER_A,__CALBACK_TIMERA);


    // Configuracion del timer B
  simo_timer_config(TIMER_B,TIME_MS,2500);
  simo_timer_set_event_callback(TIMER_B,__CALLBACK_TIMERB);

  //! Habilito las interrupciones (configuro EL NVIC)
  simo_timer_ena_irq(TIMER_A,1);
  simo_timer_ena_irq(TIMER_B,1);
 
  

}





/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

//Levanto la HAL y Configuro todos los perifericos
setup();

//! Activo los timers
simo_timer_start(TIMER_A);
simo_timer_start(TIMER_B);

while(1){

  simo_delay_ms(5000);

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
