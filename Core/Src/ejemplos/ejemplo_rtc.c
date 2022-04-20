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

#include "fsm.h"                 // ! Maquina de estados del sistema
#include "power_modes.h"         // ! Gestiona el consumo de energia del micro
#include "sensor_services.h"
#include "comm_services.h"      // ! Servicis de comunicacion
#include "comm.h"
#include "uart.h"
#include "delay.h"
#include "rtc.h"
#include "gpio.h"


  /**SPI1 GPIO Configuration
   * conexion memoria AT45DB041E
            Iniciamos servicios de memoria
            
            PB3     ------> SPI1_SCK
            PB4     ------> SPI1_MISO
            PB5     ------> SPI1_MOSI
            PA15     ------  SPI1_CS  
            */

 /**USART2 GPIO Configuration
  * Conexion Uart Debug
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */


#define LED_TOOGLE            SIMO_GPIO_18 // PB2
#define BAUDRATE              115200
#define UART_TX               UART_B
#define BUFFER_SIZE           250


#define TIMEOUT     500
#define  modo_tx_irq  0
#define SENSOR_BUFFER_LEN   BUFFER_SIZE


static char _sensor_buffer[SENSOR_BUFFER_LEN];



#define STEP_MINUTES   1
#define MSG_INIT      "Iniciamos aplicacion \r\n"
#define MSG_ROUTINE   "Realizando rutina  de medicion\r\n"

#define MAX_COUNTER          1

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

  #define MQTT_ORIGEN_URL             "http://www.mqtt.simo.com"
  #define LEN_ORIGEN_URL              (strlen(MQTT_ORIGEN_URL)+1)



 // estado de la maquina en ram
  fsm_devices DEVICE;


static void __CALLBACK_RTC(void){
// ! No hacemos nada. 
// ! Si quisieramos agregar una rutina deberiamos iniciar Systick antes

}




static void setup(){

 // iniciamos configuracion de clock standar
  simo_clock_init();


  // Configura el led blink

   //! Configuracion inicial de GPIO
  simo_gpio_set(LED_TOOGLE, SIMO_GPIO_OUT);


  //! Configura el uart
  simo_uart_init(UART_TX,BAUDRATE);

   if(sensor_services_init() != 0)
   {
    simo_uart_write(UART_TX,"sensor services readyx \r\n",strlen("sensor services readyx \r\n"),TIMEOUT,modo_tx_irq);
  }
  else{
    simo_uart_write(UART_TX,"sensor services Error \r\n",strlen("sensor services Error \r\n"),TIMEOUT,modo_tx_irq);

  }



  if(mem_services_init() != 0)
    {
      simo_uart_write(UART_TX,"memory services ready \r\n",strlen("memory services ready \r\n"),TIMEOUT,modo_tx_irq);
    }
  else
    {
      simo_uart_write(UART_TX,"memory services Error \r\n",strlen("memory services Error \r\n"),TIMEOUT,modo_tx_irq);
    }

  simo_rtc_set_alarm_callback(__CALLBACK_RTC);
  simo_rtc_ena_irq(1);
   // Inicio el RTC
  simo_rtc_init();
  // COnfigura el reloj
  //simo_rtc_set_date(w,mo,d,y);
  //simo_rtc_set_time(HOURS,MINUTES,SECONDS);


  simo_rtc_get_time(&h,&m,&s);
  simo_rtc_set_alarm(h,m,s+10);







  simo_uart_write(UART_TX,MSG_INIT,strlen(MSG_INIT),1000,0);

  // Mqtt services
    comm_init();



}

 

char buffer_mem[250]= {0};

uint8_t counter = 0;

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

    //inicio FSM (INICIO FLASH TAMBIEN)
    fsm_init();
      
    DEVICE = fsm_load_flash();

    // Seteo el  estado alojado en memoria externa, sincroniza con sram
    //fsm_set_state(FSM_ON_FIELD);
    fsm_set_state(FSM_UNDEFINED);
 
    DEVICE = fsm_get_state();  // leo desde variable sram sincronizada con mem flash externa
     
    while(1){
   
    switch (DEVICE)
      {
      case FSM_WITHOUT_CONFIG:
          simo_uart_write(UART_TX,"FSM:WITHOUT CONFIG\r\n"
                          ,strlen("FSM:WITHOUT CONFIG\r\n")
                          ,TIMEOUT,modo_tx_irq);
                          //rutina para el dispositivo sin configuracion?
                          //  Quiza preguntar al servidor mqtt?
          break;




      case FSM_ON_FIELD:
          simo_uart_write(UART_TX,"FSM:ON FIELD\r\n"
                          ,strlen("FSM:ON FIELD\r\n")
                          ,TIMEOUT,modo_tx_irq);  
          
          // Dormir el microcontrolador
          power_mode_set( SLEEP_MODE);
          // Despierta mediante interrupcion RTC
          power_mode_set( RESUMEN_RUN);
          //Rutina de trabajo
          simo_uart_write(UART_TX,MSG_ROUTINE,strlen(MSG_ROUTINE),1000,0);
          simo_rtc_get_time(&h,&m,&s);


          simo_rtc_get_date(&w,&mo,&d,&y);
            //borramos buffer
          memset(_sensor_buffer,0,1);


          sprintf(_sensor_buffer,"Date %d/%d/%d |%d:%d:%d|\r\n",mo,d,y,h,m,s);

          sensor_services_check(_sensor_buffer);
          
          simo_uart_write(UART_TX,_sensor_buffer,strlen(_sensor_buffer),TIMEOUT,modo_tx_irq);
  
        // Guardar datos en memoria
  
          mem_services_write_data(_sensor_buffer, strlen(_sensor_buffer),counter);

        // leo desde memoria

          counter ++;
          if(counter == MAX_COUNTER){
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
          simo_rtc_set_alarm(h,m,s+10);

         }    
          break;



      case FSM_MEMORY_DOWNLOAD:

          simo_uart_write(UART_TX,"FSM: DONWLOAD\r\n"
                          ,strlen("FSM: DONWLOAD\r\n")
                          ,TIMEOUT,modo_tx_irq);
          simo_delay_ms(1200);

      

          //descargo memoria y vuelvo a estado Field
          
          // borrar datos que ya se enviaron, y ajustar contador de datos a cero
          // volver al modo datalog

           simo_uart_write(UART_TX,"\r\nlectura de memoria iniciada\r\n"
                          ,strlen("\r\nlectura de memoria iniciada\r\n")
                          ,TIMEOUT,modo_tx_irq);


          // buffer para los datos leidos en memoria
          char buff[BUFFER_SIZE];

         

          for( uint8_t i=0; i != MAX_COUNTER; i++ ){

                    simo_uart_write(UART_TX,"\r\nread from mem:\r\n"
                          ,strlen("\r\nread from mem:\r\n")
                          ,TIMEOUT,modo_tx_irq);


                    mem_services_read_data(buff,250,i);
                    simo_uart_write(UART_TX,buff
                    ,strlen(buff)
                    ,TIMEOUT,modo_tx_irq);


          }

          simo_uart_write(UART_TX,"\r\nlectura de moeria finalizada\r\n"
                          ,strlen("\r\nlectura de moeria finalizada\r\n")
                          ,TIMEOUT,modo_tx_irq);
    
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
          simo_rtc_set_alarm(h,m,s+10);



          break;



      case FSM_UNDEFINED:
          simo_uart_write(UART_TX,"FSM: UNDEFINED\r\n"
                          ,strlen("FSM: UNDEFINED\r\n")
                          ,TIMEOUT,modo_tx_irq);
        

          uint32_t comm_ready = comm_services_check();

          if(comm_ready != 0)  simo_uart_write(UART_TX,"\r\nCOMM SERVICES READY\r\n"
                          ,strlen("\r\nCOMM SERVICES READY\r\n")
                          ,TIMEOUT,modo_tx_irq);
 
            simo_delay_ms(2000);
 



          break;


      default:
          simo_uart_write(UART_TX,"FSM:default\r\n"
                          ,strlen("FSM:default\r\n")
                          ,TIMEOUT,modo_tx_irq);
          simo_delay_ms(5000);

          break;
      }









    }


    
}
