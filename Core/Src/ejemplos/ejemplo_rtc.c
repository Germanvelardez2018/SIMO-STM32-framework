
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


#include "power_modes.h" // ! Gestiona el consumo de energia del micro
#include "sensor_services.h"
#include "uart.h"
#include "delay.h"
#include "rtc.h"
#include "gpio.h"
// Simo



/* USER CODE END Includes */


 /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */


#define LED_TOOGLE            SIMO_GPIO_18 // PB2
#define BAUDRATE              115200
#define UART_TX               UART_B
#define BUFFER_SIZE           100



#define TIMEOUT     500

#define  modo_tx_irq  0

#define SENSOR_BUFFER_LEN   250


static char _sensor_buffer[SENSOR_BUFFER_LEN];





#define STEP_MINUTES   1


#define MSG_INIT      "Iniciamos aplicacion \r\n"

#define MSG_ROUTINE   "Realizando rutina  de medicion\r\n"



//Configura la alarma
  #define HOURS       10
  #define MINUTES     30
  #define SECONDS      0




  uint8_t h= HOURS;
  uint8_t m = MINUTES;
  uint8_t s = SECONDS;

static void __CALLBACK_RTC(void){
// ! No hacemos nada. 
// ! Si quisieramos agregar una rutina deberiamos iniciar Systick antes

}




static void setup(){


  simo_clock_init();

  simo_clock_config();

  // Configura el led blink

   //! Configuracion inicial de GPIO
  simo_gpio_set(LED_TOOGLE, SIMO_GPIO_OUT);


  //! Configura el uart
  simo_uart_init(UART_TX,BAUDRATE);

   if(sensor_services_init() != 0){
    simo_uart_write(UART_TX,"sensor services readyx \r\n",strlen("sensor services readyx \r\n"),TIMEOUT,modo_tx_irq);
  }
  else{
    simo_uart_write(UART_TX,"sensor services Error \r\n",strlen("sensor services Error \r\n"),TIMEOUT,modo_tx_irq);

  }



  simo_rtc_set_alarm_callback(__CALLBACK_RTC);
  simo_rtc_ena_irq(1);


   // Inicio el RTC
  simo_rtc_init();
  
  
  // COnfigura el reloj
  simo_rtc_set_time(HOURS,MINUTES,SECONDS);

  simo_rtc_set_alarm(HOURS,MINUTES,SECONDS+10);

  simo_uart_write(UART_TX,MSG_INIT,strlen(MSG_INIT),1000,0);








}



/**
 * @brief  The application entry point.
 * @retval int
 */

int main(void)
{

     // Configuracion
    setup();
    // Estado del dispositivo, 
    // transmicion en vivo o transmicion desde memoria memoria.


 


    while(1){
    
    // Dormir el microcontrolador

    power_mode_set( SLEEP_MODE);




    // Despierta mediante interrupcion RTC
    power_mode_set( RESUMEN_RUN);


    //Rutina de trabajo


    simo_uart_write(UART_TX,MSG_ROUTINE,strlen(MSG_ROUTINE),1000,0);
    uint8_t pos= sensor_services_check(_sensor_buffer,SENSOR_BUFFER_LEN);
    simo_uart_write(UART_TX,_sensor_buffer,pos,TIMEOUT,modo_tx_irq);

    simo_uart_write(UART_TX,_sensor_buffer,pos,TIMEOUT,modo_tx_irq);

    simo_gpio_toogle(LED_TOOGLE);
    simo_delay_ms(100);
    simo_gpio_toogle(LED_TOOGLE);


    // Me preparo para volver a dormir
    simo_rtc_get_time(&h,&m,&s);

    //Configura la alarma
    simo_rtc_set_alarm(h,(m+STEP_MINUTES),s);
    }


    
}
