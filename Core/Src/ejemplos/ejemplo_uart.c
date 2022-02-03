
/**
 * @file ejemplo_uart.c
 * @author German Velardez (germanvelardez@gmail.com)
 * 
 * @brief Ejemplo de aplicacion simple funcionando con 2 uart. 
 * UARTA se configura en modo recepcion, con interrupciones (callback asociada)
 * UARTB se configura en modo transmicion sin interrupcion
 * Recibo datos por UARTA y los envio por UARTB. Agrego un blink en el loop.
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
#include "gpio.h"
#include "clock_config.h"
#include "delay.h"



/* USER CODE END Includes */


#define LED_TOOGLE    SIMO_GPIO_18 // PB2
#define BAUDRATE      115200
#define UART_RX               UART_A
#define UART_TX               UART_B
#define BUFFER_SIZE           100
#define RX_BUFFER             1



#define TIMEOUT     500

#define  modo_rx_irq  1 // 
#define  modo_tx_irq  0


#define END_CHAR        '\n'

static uint8_t   __buffer[BUFFER_SIZE];
static uint8_t  __buffer_rx;
static uint8_t   __counter =0;





//Callback UART rx


static void __CALLBACK_UART_RX(void){

  //  simo_uart_write(UART_TX,&__buffer_rx,1,TIMEOUT,modo_tx_irq);

    if(__buffer_rx == END_CHAR){
        //Termino

       
        simo_uart_write(UART_TX,__buffer,__counter,TIMEOUT,modo_tx_irq);
        simo_uart_write(UART_TX,"\n",1,TIMEOUT,modo_tx_irq);
        //Reiniciamos contador
        __counter = 0;
        

    }
    else{
      __buffer[__counter]= __buffer_rx;
        // Incrementamos el contador y volvemos a llamar interrupcion
        __counter ++;


    }

      simo_uart_read(UART_RX,&(__buffer_rx),RX_BUFFER,TIMEOUT,modo_rx_irq);









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
  simo_uart_init(UART_RX, BAUDRATE);
  simo_uart_init(UART_TX,BAUDRATE);

  //! Configuracion inicial de GPIO
  simo_gpio_set(SIMO_GPIO_18, SIMO_GPIO_OUT);


  //Configuracion del uart UART_RX

  // Agregamos el callback
  simo_uart_set_rx_callback(UART_RX,__CALLBACK_UART_RX);
  // Habilitamos la interrupcion
  simo_uart_ena_irq(UART_RX,1);


    // Configuracion de uart UART_TX
    //NO LLEVA CALLCBACK ni interrupciones
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



// Leo byte por byte hasta encontrar caracter END o alcanzar 
// el tamanio maximo del buffer principal(BUFFER_SIZE)
simo_uart_read(UART_RX,&(__buffer_rx),RX_BUFFER,TIMEOUT,modo_rx_irq);

#define MSG_INIT     "Iniciamos aplicacion\r\n"


simo_uart_write(UART_TX,MSG_INIT,strlen(MSG_INIT),TIMEOUT,modo_tx_irq);



while(1){

simo_delay_ms(500);
simo_gpio_toogle(SIMO_GPIO_18);


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
