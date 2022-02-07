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
#include "stdio.h"
#include "uart.h"
#include "config.h"
#include "gpio.h"
#include "clock_config.h"
#include "simcom.h"
#include "string.h"




#define MQTT_TOPIC                "X1111"
#define MQTT_BROKER2               "simointi.cloud.shiftr.io"
#define MQTT_PASS                  "fdZY5b69OhOVsAns"
#define MQTT_ID                    "simointi"
#define MQTT_QOS                    "0"



static volatile uint32_t ena = 0;  // Si ena =1 entonces estamos en modo NORMAL, sino en modo sleep



// Callback para el RTC

static void __CALLBACK_RTC(void){
  simo_pwr_return_normal_mode(); // Siempre debe llamarse en el callback de rtc. 
                                    //Sirve para reanudar el micro
  //simo_gpio_toogle(SIMO_GPIO_18);
  //HAL_Delay(50);
  //simo_gpio_toogle(SIMO_GPIO_18);
  ena = 1;

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
  simo_gpio_set(SIMO_GPIO_18,SIMO_GPIO_OUT);


  // Configuracion SIMCOM
  sim_init();
  sim_get_default(); 
  sim_set_echo(0);
  sim_set_pwr_gps(1);
  sim_get_operator();
  sim_get_signal_level();
  sim_open_apn();
  sim_config_mqtt(MQTT_BROKER2,MQTT_ID,MQTT_PASS,MQTT_QOS);
  while(sim_check_at() != 1); 
  #define MSG_PUBLISHED    "SIMO LISTO \r\n"
  sim_mqtt_publish(MQTT_TOPIC,MSG_PUBLISHED,strlen(MSG_PUBLISHED));
  sim_low_pwr_mode(1); // A dormir
 
  
}








/**
 * @brief  The application entry point.
 * @retval int
 */

int main(void)
{


 setup();
 
 #define HOURS       0
 #define MINUTES     0
 #define SECONDS     0


simo_rtc_set_alarm_callback(__CALLBACK_RTC);
simo_rtc_ena_irq(1);
simo_rtc_init();
simo_rtc_set_time(HOURS,MINUTES,SECONDS);
simo_rtc_set_alarm(HOURS,MINUTES,SECONDS+15);
simo_pwr_before_change_mode(); // Se llama antes de cambiar de modod NORMAL a sleep
simo_pwr_enter_sleep_mode(); // Entramos a modo sleep



  char* p_gps_info;
  uint8_t nmea[100];
  uint8_t h,m,s;

  while(1){



    if( ena == 1){
    sim_low_pwr_mode(0); // Despiero el modulo SIM
    simo_gpio_toogle(SIMO_GPIO_18);
    simo_delay_ms(500);
    simo_gpio_toogle(SIMO_GPIO_18);
    // Habilito o deshabilito el echo en la respuesta
    sim_get_gps_info();
    p_gps_info = (char*)sim_get_buffer(); // Devuelve el puntero al buffer rx que recibe las respuesta del SIM7000G
    strncpy((char*)nmea,p_gps_info,strlen(p_gps_info)+1);  // Copio este buffer rx.                                                      // Porque al ejecutarse un nuevo comandos se borrara la info anterior
    #define MSG_PUBLISHED               (nmea) // correr dos posiciones
    sim_mqtt_publish(MQTT_TOPIC,MSG_PUBLISHED,strlen(MSG_PUBLISHED));



    // Recargar la alarma del RTC 
    ena = 0;

    
    // Obtengo el valor de la hora actual
    simo_rtc_get_time(&h,&m,&s);

    m = m +1 ; // alarma cada un minuto
    simo_rtc_set_alarm(h,m,s);
    simo_pwr_before_change_mode(); // Se llama antes de cambiar de modod NORMAL a sleep
    simo_pwr_enter_sleep_mode(); // Entramos a modo sleep

    }

    
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
