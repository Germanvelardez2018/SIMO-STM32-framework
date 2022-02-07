
/**
 * @file ejemplo_rtc.c 
 * @author German Velardez (germanvelardez@gmail.com)
 * 
 * @brief Ejemplo de aplicacion de bajo consumo con rtc. 
 * 
 * Configuramos la hora el modulo ( en nuestro ejemplo  0:0:0), 
 *  configuramos alarma para que se ejecute cada 1 minuto...llama al calback
 *  El calback toogle un led, envia un mensaje por uart...luego a dormir de nuevo por un minuto
 * 
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
#include "rtc.h"
#include "gpio.h"
#include "clock_config.h"
#include "delay.h"
#include "power_save.h"


/* USER CODE END Includes */


#define LED_TOOGLE    SIMO_GPIO_18 // PB2
#define BAUDRATE      115200



static volatile uint32_t ena = 0;  // Si ena =1 entonces estamos en modo NORMAL, sino en modo sleep


// Callback para el RTC

static void __CALLBACK_RTC(void){
 

    simo_pwr_return_normal_mode(); // Siempre debe llamarse en el callback de rtc. 
                                    //Sirve para reanudar el micro
    #define CALLBACK_MSG            "CALLBACK RTC \r\n"
    #define ENA_INTERRUPTION        0 
    #define TIMEROUT                500    // Si ENA_INTERRUPTION es 1 entonces no hay timeout  
    simo_uart_write(UART_A,CALLBACK_MSG,strlen(CALLBACK_MSG),TIMEROUT,ENA_INTERRUPTION);
    ena = 1;

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

}





/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

//Levanto la HAL y Configuro todos los perifericos
setup();
#define HOURS       0
#define MINUTES     0
#define SECONDS     0

#define MSG_INIT    "EJEMPLO RTC \r\n"
simo_uart_write(UART_A,MSG_INIT,strlen(MSG_INIT),TIMEROUT,ENA_INTERRUPTION);

simo_rtc_set_alarm_callback(__CALLBACK_RTC);
simo_rtc_ena_irq(1);
simo_rtc_init();
simo_rtc_set_time(HOURS,MINUTES,SECONDS);
simo_rtc_set_alarm(HOURS,MINUTES,SECONDS+15);
simo_pwr_before_change_mode(); // Se llama antes de cambiar de modod NORMAL a sleep
simo_pwr_enter_sleep_mode(); // Entramos a modo sleep


//! Activo los timers


while(1){
    
  // Solo entramoa a este rutina si ena = 1 , 
  // es decir despues de ejecutado el callback del rtc
    if(ena == 1){
        simo_gpio_toogle(SIMO_GPIO_18);
        simo_delay_ms(500);
        simo_gpio_toogle(SIMO_GPIO_18);
        #define NORMAL_MODE_MSG            "Volvemos a modo SLEEP \r\n"
        #define ENA_INTERRUPTION        0 
        #define TIMEROUT                500    // Si ENA_INTERRUPTION es 1 entonces no hay timeout  
        uint8_t h,m,s;
        simo_uart_write(UART_A,NORMAL_MODE_MSG,strlen(NORMAL_MODE_MSG),TIMEROUT,ENA_INTERRUPTION);
        simo_rtc_get_time(&h,&m,&s);

        #define FORMAT_MSG      "Proxima alarma: %d : %d : %d\r\n"
        m = m +1 ; // alarma cada un minuto
        sprintf(buffer,FORMAT_MSG,h,m,s);
        ena = 0;
        simo_rtc_set_alarm(h,m,s);
        simo_pwr_before_change_mode(); // Se llama antes de cambiar de modod NORMAL a sleep
        simo_pwr_enter_sleep_mode(); // Entramos a modo sleep

    }

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
