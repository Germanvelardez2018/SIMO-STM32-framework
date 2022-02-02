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



#define STOP_MODE             0    // Si es 0 entramos en modo SLEEP, sino modo Stop
#define ISR_ONLY              1
#define BAUDRATE              115200


/* USER CODE END Includes */

volatile uint8_t ena = 0;

static void rtc_print_alarm(uint8_t h, uint8_t m, uint8_t s)
{

  uint8_t buffer[100] = {0};
  sprintf(buffer, "\r\n next alarm h:m:s ==> %d : %d :%d\r\n", h, m, s);
  simo_uart_write(UART_B, buffer, strlen(buffer), 200, 0);
}

static void rtc_printf(uint8_t h, uint8_t m, uint8_t s)
{

  uint8_t buffer[100] = {0};
  sprintf(buffer, "\r\n h:m:s ==> %d : %d :%d", h, m, s);
  simo_uart_write(UART_B, buffer, strlen(buffer), 200, 0);
}

static void __rtc_irq(void)
{

// En caso de estar en modo STOP de  standby ejecutamos la funcion de configuracion inicial (setup())
    simo_pwr_return_normal_mode();
   
// los toogle no sirve en modo STOP, porque el estado de configuracion inicial es siempre el mismo
    simo_gpio_toogle(SIMO_GPIO_18); 
    


    #if ISR_ONLY == 1
        uint8_t h,m,s ; 
        simo_rtc_get_alarm(&h, &m, &s);
        #define RTC_DELAY   1
       m  =m + RTC_DELAY;    // Activar alarmas cada 5 segundos
        simo_rtc_set_alarm(h, m, s);  
        rtc_print_alarm(h, m, s);  
    //    simo_pwr_enter_sleep_mode();
    
    #endif
    

  
       
  
    ena= 1;
}



/**
 * @brief Funcion de inicio de perifericos. 
 * 
 * @return ** void 
 */
static void setup(void){

  // Aqui va la configuracion inicial
  HAL_Init();
  simo_clock_config();
  simo_uart_init(UART_B, BAUDRATE);
  simo_gpio_set(SIMO_GPIO_18, SIMO_GPIO_OUT);

}



/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

 

  setup();
  simo_rtc_set_alarm_callback(__rtc_irq);
  simo_rtc_init();


  #if STOP_MODE == 1
  /**
   * @brief En caso de entrar en modo STOP MODE, la configuracion del micro se pierde y debe volverse a configurar.
   * 
   */
  simo_pwr_set_initial_config(setup);
  
  
  #endif
   uint8_t h,m,s ;
  simo_rtc_ena_irq(1);
  simo_rtc_get_time(&h,&m,&s);
  rtc_printf(h,m,s);
  simo_rtc_set_alarm(h, m, s+5);
  simo_rtc_get_alarm(&h, &m, &s);
  rtc_print_alarm(h, m, s);  

 #if STOP_MODE  == 0
  /**
  * @brief Configuro la funcion setup para cuando volvamos de un sueño muy profundo con el micro todo desconfigurado
  * 
  */

  #if ISR_ONLY == 1
  simo_pwr_sleep_only_isr(1);

  #endif
  simo_pwr_enter_sleep_mode();

#else 
  simo_pwr_enter_stop_mode();
#endif
   while (1)
  {

 #if ISR_ONLY == 0
    if( ena == 1){
        uint8_t h,m,s ; 
        simo_rtc_get_alarm(&h, &m, &s);
        #define RTC_DELAY   1
        m = m+ RTC_DELAY;    // Activar alarmas cada 5 segundos
        simo_rtc_set_alarm(h, m, s);  
        rtc_print_alarm(h, m, s);  
        ena= 0;
        
        #if STOP_MODE  == 0
          simo_pwr_enter_sleep_mode();
        #else 
          simo_pwr_enter_stop_mode();
        #endif
    }
  #endif
  HAL_Delay(500);

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
