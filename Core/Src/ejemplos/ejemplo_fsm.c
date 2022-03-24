/**
 * @file ejemplo_flash_ext.c
 * @author German Velardez (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */



 // Recordar configurar los siguientes elementos los flar para manejar UART (1 solo uart) y TIMER ( 2 timers)



#include "stdio.h"
#include "main.h"

// Simo
#include "uart.h"
#include "gpio.h"
#include "clock_config.h"
#include "delay.h"
#include "fsm.h"

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






/**
 * @brief Funcion de inicio de perifericos. 
 * 
 * @return ** void 
 */
static void setup(void){

  

  // Aqui va la configuracion inicial
  HAL_Init();
  simo_clock_config();
  simo_uart_init(UART_TX,BAUDRATE);

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

//Configuro para leer datos mediante interrupcion



#define MSG_INIT     "Iniciamos aplicacion\r\n"


simo_uart_write(UART_TX,MSG_INIT,strlen(MSG_INIT)
,TIMEOUT,modo_tx_irq);



uint32_t counter = 0;
char    buffer[100];
#define MSG_FORMAT      "counter: %d from %s\r\n"

//inicio FSM (INICIO FLASH TAMBIEN)
fsm_init();
#define MQTT_ORIGEN_URL             "http://www.mqtt.simo.com"
#define LEN_ORIGEN_URL              (strlen(MQTT_ORIGEN_URL)+1)
fsm_devices DEVICE;
DEVICE = fsm_load_flash();


//mem_services_set_mqtt_origen(MQTT_ORIGEN_URL,LEN_ORIGEN_URL);
char buff_origin[50]={0};
mem_services_get_mqtt_origen(buff_origin,50);



while(1){

simo_gpio_toogle(SIMO_GPIO_18);

simo_uart_write(UART_TX,"[from sram]=>",strlen("[from sram]=>"),TIMEOUT,modo_tx_irq);

sprintf(buffer,MSG_FORMAT,counter,"sram");

simo_uart_write(UART_TX,buffer,strlen(buffer),TIMEOUT,modo_tx_irq);
//fsm_set_state(FSM_ON_FIELD);
DEVICE = fsm_get_state();  // leo desde variable sram sincronizada con mem flash externa
switch (DEVICE)
{
case FSM_WITHOUT_CONFIG:
    simo_uart_write(UART_TX,"\r\nFSM:WITHOUT CONFIG\r\n"
                    ,strlen("\r\nFSM:WITHOUT CONFIG\r\n")
                    ,TIMEOUT,modo_tx_irq);

    break;

case FSM_ON_FIELD:
    simo_uart_write(UART_TX,"\r\nFSM:ON FIELD\r\n"
                    ,strlen("\r\nFSM:ON FIELD\r\n")
                    ,TIMEOUT,modo_tx_irq);

    break;

case FSM_MEMORY_DOWNLOAD:
    simo_uart_write(UART_TX,"\r\nFSM: DONWLOAD\r\n"
                    ,strlen("\r\nFSM: DONWLOAD\r\n")
                    ,TIMEOUT,modo_tx_irq);

    break;

case FSM_UNDEFINED:
    simo_uart_write(UART_TX,"\r\nFSM: UNDEFINED\r\n"
                    ,strlen("\r\nFSM: UNDEFINED\r\n")
                    ,TIMEOUT,modo_tx_irq);
    break;


default:
    simo_uart_write(UART_TX,"\r\nFSM:default\r\n"
                    ,strlen("\r\nFSM:default\r\n")
                    ,TIMEOUT,modo_tx_irq);
    break;
}



sprintf(buffer,"mqtt origin: %s\r\n",buff_origin);

simo_uart_write(UART_TX,buffer
                    ,strlen(buffer)
                    ,TIMEOUT,modo_tx_irq);

simo_delay_ms(10000);


counter ++;

}
  

  
}
