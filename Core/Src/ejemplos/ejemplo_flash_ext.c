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
#include "AT45DB.h"

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


 /**SPI1 GPIO Configuration
        PB3     ------> SPI1_SCK
        PB4     ------> SPI1_MISO
        PB5     ------> SPI1_MOSI
        PB6     ------> CS (SIMO_GPIO_22)
        */



static void init_memory(){
    AT45DB_init(   SPI_A,SIMO_GPIO_22,SIMO_SPI_PRESCALER_2);
   // AT45DB_erase_full();
    simo_delay_ms(1000);
    uint32_t success = at45db_start(AT45DB_4MB, pg_256byte);
    if(success != 0){

simo_uart_write(UART_TX,
                    "inicio exitosamente la memoria \r\n",
                    strlen("inicio exitosamente la memoria \r\n")
                    ,TIMEOUT,modo_tx_irq);
    } 
    else{
        simo_uart_write(UART_TX,
                    "fallo la memoria \r\n",
                    strlen("fallo la memoria \r\n")
                    ,TIMEOUT,modo_tx_irq);
    }



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
  simo_uart_init(UART_TX,BAUDRATE);

  //! Configuracion inicial de GPIO
  simo_gpio_set(SIMO_GPIO_18, SIMO_GPIO_OUT);
  init_memory();
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


simo_uart_write(UART_TX,MSG_INIT,strlen(MSG_INIT),TIMEOUT,modo_tx_irq);



uint32_t counter = 0;
char    buffer[100];
char    buffer_mem[100] = {0};
#define MSG_FORMAT      "counter: %d from %s\r\n"

while(1){

simo_delay_ms(1500);
simo_gpio_toogle(SIMO_GPIO_18);

simo_uart_write(UART_TX,"[from sram]=>",strlen("[from sram]=>"),TIMEOUT,modo_tx_irq);

sprintf(buffer,MSG_FORMAT,counter,"sram");

simo_uart_write(UART_TX,buffer,strlen(buffer),TIMEOUT,modo_tx_irq);

// guardar en memoria
#define PAGE_DEFAULT        0
AT45DB_write_page(buffer,strlen(buffer)+1,PAGE_DEFAULT);

//lEER EL DATO DESDE MEMORIA

AT45DB_read_page(buffer_mem,strlen(buffer),PAGE_DEFAULT);
simo_uart_write(UART_TX,"[from memory]=>",strlen("[from memory]=>"),TIMEOUT,modo_tx_irq);

simo_uart_write(UART_TX,buffer_mem,strlen(buffer_mem),TIMEOUT,modo_tx_irq);


counter ++;

}
  

  
}
