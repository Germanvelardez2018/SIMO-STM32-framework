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
#include "main.h"
#include "wdt.h"
#include "timer.h"
#include "fsm.h"                 // ! Maquina de estados del sistema 
#include "mem_services.h"       // ! memoria para almacenar datos
#include "power_modes.h"         // ! Gestiona el consumo de energia del micro
#include "sensor_services.h"
#include "comm_services.h"      // ! Servicis de comunicacion
#include "comm.h"
#include "uart.h"
#include "delay.h"
#include "rtc.h"
#include "gpio.h"
#include "debug.h"
#include <string.h>


  /**SPI1 GPIO Configuration
   * conexion memoria AT45DB041E
            Iniciamos servicios de memoria
            
            PB3     ------> SPI1_SCK
            PB4     ------> SPI1_MISO
            PB5     ------> SPI1_MOSI
            PA15     ------  SPI1_CS  
            */

 

#define UPDATE_SLEEP            h,m+1,s


#define _WRITE_MQTT_            (0) // ! CON 1 grabo los parametros de mqtt en flash

#define LED_TOOGLE            SIMO_GPIO_18 // PB2

#define BUFFER_SIZE           255



#define SENSOR_BUFFER_LEN   BUFFER_SIZE





static char buffer[BUFFER_SIZE]={0};




#define MSG_ROUTINE   "Realizando rutina  de medicion\r\n"


//Configura la alarma
  #define HOURS               13
  #define MINUTES             8
  #define SECONDS             0
  #define MONTHS              3 // Abril
  #define DAYS                20
  #define YEAR                22  
  #define WEEK                3


  uint8_t h= HOURS;
  uint8_t m = MINUTES;
  uint8_t s = SECONDS;

  uint8_t w = WEEK;
  uint8_t mo = MONTHS;
  uint8_t d = DAYS;
  uint8_t y = YEAR;


  uint8_t sleep = 0; // Poner en 1 cuando EL micro debe estar durmiendo
  

 // estado de la maquina en ram
  fsm_devices DEVICE;
  char buffer_mem[BUFFER_SIZE]= {0};

  uint8_t counter = 0;
  uint8_t counter_max = 0;


static void __CALLBACK_RTC(void){
// ! No hacemos nada. 
// ! Si quisieramos agregar una rutina deberiamos iniciar Systick antes
  sleep = 0; 
}




static void setup(){

 // iniciamos configuracion de clock standar
  simo_clock_init();
  debug_init();
  // Configura el led blink
   //! Configuracion inicial de GPIO
  simo_gpio_set(LED_TOOGLE, SIMO_GPIO_OUT);
  sensor_services_init();
  mem_services_init();


  //GRABO LA URL en memoria, hacer solo una vez
  #if _WRITE_MQTT_ == 1

  
  #define MQTT_TOPIC                 "X1111"
  #define MQTT_URL                   "simointi.cloud.shiftr.io" 
  #define MQTT_PASS                  "fdZY5b69OhOVsAns" 
  #define MQTT_ID                    "simointi"
  #define MQTT_QOS                    "0"
   mem_services_set_mqtt_origen( MQTT_URL);
   mem_services_set_mqtt_id_origen(MQTT_ID);
   mem_services_set_mqtt_pass_origen(MQTT_PASS);
   mem_services_set_mqtt_pub_topics(MQTT_TOPIC,0);
   mem_services_set_mqtt_qos_origen(MQTT_QOS);

  #define MAX_COUNTER          2

  //grabo contador maximo
   mem_services_set_data_counter(MAX_COUNTER); 

    // Seteo el  estado alojado en memoria externa, sincroniza con sram
    fsm_set_state(FSM_ON_FIELD);

  #endif

  simo_rtc_set_alarm_callback(__CALLBACK_RTC);
  simo_rtc_ena_irq(1);
   // Inicio el RTC
  simo_rtc_init();
  // COnfigura el reloj
  //simo_rtc_set_date(w,mo,d,y);
  //simo_rtc_set_time(HOURS,MINUTES,SECONDS);


  simo_rtc_get_time(&h,&m,&s);
  simo_rtc_set_alarm(UPDATE_SLEEP);
  comm_services_init();  
  comm_services_wait_ok(); // EN WHILE HASTA QUE EL CHIP DEVUELVA OK
  comm_services_config_all();




}


static void __refresh_wdt(void){


   power_mode_set( RESUMEN_RUN);

  //Refrescar el WDT
   simo_wdt_refresh();
  //reiniciar timer
 
}


/**
 * @brief  The application entry point.
 * @retval int
 */
#include "uart.h"
int main(void)
{



     // Configuracion
  setup();


 // fsm_set_state(FSM_ON_FIELD);

  simo_wdt_init(4095,WDT_PRE_256); // contador de 12 bits
  debug_print("WDT CONFIGURADO");
  // Configuro el timer con el que voy a refrescar el WDT
   // Configuracion del timer B
  simo_timer_config(TIMER_B,TIME_MS,4000);
  simo_timer_set_event_callback(TIMER_B,__refresh_wdt);
  simo_timer_ena_irq(TIMER_B,1);
  simo_timer_start(TIMER_B);


    // Estado del dispositivo, 
    // transmicion en vivo o transmicion desde memoria memoria.
    //inicio FSM (INICIO FLASH TAMBIEN)
    fsm_init();
    DEVICE = fsm_load_flash();
    DEVICE = fsm_get_state();  // leo desde variable sram sincronizada con mem flash externa
  #define MAX_COUNTER          2

  //grabo contador maximo
   mem_services_set_data_counter(MAX_COUNTER); 
   counter_max = mem_services_get_data_counter();
    //dejemos undefine

    while(1){
    switch (DEVICE)
      {
      case FSM_WITHOUT_CONFIG:
          debug_print("WITHOUT CONFIG");
          //rutina para el dispositivo sin configuracion?
          //  Quiza preguntar al servidor mqtt?
 
          simo_delay_ms(10000);
          break;

      case FSM_ON_FIELD:
          debug_print("ON FIELD");
          // Dormir el microcontrolador

          sleep = 1; // poner en 1 cunado el micro debe dormir
          power_mode_set( SLEEP_MODE);

          // si despierta por timer a dormir nuevamente
          while(sleep == 1){
            power_mode_set( SLEEP_MODE);


          }

          // Despierta mediante interrupcion RTC
          power_mode_set( RESUMEN_RUN);

          //Rutina de trabajo
          debug_print(MSG_ROUTINE);
            //borramos buffer
          memset(buffer,0,BUFFER_SIZE);
          char nmea[120]={0};
          comm_services_get_nmea(nmea);
          sprintf(buffer,"%s",nmea);
          sensor_services_check(buffer);
        // Guardar datos en memoria
          mem_services_write_data(buffer, strlen(buffer),counter);
        // leo desde memoria
          counter ++;
          if(counter == counter_max){
            fsm_set_state(FSM_MEMORY_DOWNLOAD);
             DEVICE = fsm_get_state();
          } 
      else{
          simo_gpio_toogle(LED_TOOGLE);
          simo_delay_ms(100);
          simo_gpio_toogle(LED_TOOGLE);
          // Me preparo para volver a dormir
          simo_rtc_get_time(&h,&m,&s);
          //Configura la alarma
          simo_rtc_set_alarm(UPDATE_SLEEP);
         }    
          break;



      case FSM_MEMORY_DOWNLOAD:

          debug_print(" DONWLOAD\r\n");
          //descargo memoria y vuelvo a estado Field
          // borrar datos que ya se enviaron, y ajustar contador de datos a cero
          // volver al modo datalog
          debug_print("lectura de memoria iniciada\r\n");

          // buffer para los datos leidos en memoria
        //borramos buffer
          
         

          for( uint8_t i=0; i != counter_max; i++ ){
                memset(buffer,0,BUFFER_SIZE);
                mem_services_read_data(buffer,BUFFER_SIZE,i);
                  // enviamos el dato al servidor   
                #define MQTT_TOPIC                 "X1111"
                 
                comm_mqtt_publish(MQTT_TOPIC,buffer, strlen( buffer));
             //   comm_send_mesage("se envio un nuevo frame de mediciones", "3856870066");


                simo_delay_ms(4000);
          }
          debug_print("lectura de memeria finalizada\r\n");


          counter = 0;
        
          fsm_set_state(FSM_ON_FIELD);
          DEVICE = fsm_get_state();

          // a dormir, activar rtc antes
          simo_gpio_toogle(LED_TOOGLE);
          simo_delay_ms(100);
          simo_gpio_toogle(LED_TOOGLE);
          // Me preparo para volver a dormir
          simo_rtc_get_time(&h,&m,&s);
          //Configura la alarma
          simo_rtc_set_alarm(UPDATE_SLEEP);
          break;



      case FSM_UNDEFINED:
          debug_print(" UNDEFINED\r\n");
          uint32_t  ret = comm_check();
          simo_wdt_refresh();

          simo_delay_ms(2000);
          break;


      default:
          debug_print(" DEFAULT\r\n");
          simo_delay_ms(2000);
          break;
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
