/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "uart.h"
#include "main.h"
















    // Estructuras

    #if NUM_SIMO_UART >0
        UART_HandleTypeDef huart1;
    #endif
    #if NUM_SIMO_UART >1
        UART_HandleTypeDef huart2;
    #endif
    #if NUM_SIMO_UART >2
        UART_HandleTypeDef huart3;
    #endif


//--------------------------------------
#if NUM_SIMO_UART > 0

static UART_HandleTypeDef* __get_uart(SIMO_UART uart_enum)
{
    UART_HandleTypeDef* uart = NULL;
    switch (uart_enum)
    {
        #if NUM_SIMO_UART >0
            case UART_A:
            uart = &huart1;
            uart->Instance = USART1;
            break;
        #endif
        #if NUM_SIMO_UART >1
            case UART_B:
            uart = &huart2;
            uart->Instance = USART2;
            break;
        #endif
        #if NUM_SIMO_UART >2
            case UART_C:
            uart = &huart3;
            uart->Instance = USART3;
            break;
        #endif
            default:
            break;
    }
    return uart;
}



uint32_t simo_uart_write(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout ){
    uint32_t res = 0;  // retorna error por defecto

        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL) {     
            if(HAL_UART_Transmit(simo_uart,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
            }
    }
    return res;
}





uint32_t simo_uart_read(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout ){
    uint32_t res = 0;  // retorna error por defecto

        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL) {     
            if(HAL_UART_Receive(simo_uart,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
            }
    }
    return res;
           
   
}


uint32_t simo_uart_init(SIMO_UART uart,uint32_t baudrate){
        uint32_t res = 0;  // retorna error por defecto
        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL) {  
        simo_uart->Init.BaudRate = baudrate;
        // Configuracion estandar sin flujo por hardware
        simo_uart->Init.WordLength = UART_WORDLENGTH_8B;
        simo_uart->Init.StopBits = UART_STOPBITS_1;
        simo_uart->Init.Parity = UART_PARITY_NONE;
        simo_uart->Init.Mode = UART_MODE_TX_RX;
        simo_uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
        simo_uart->Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(simo_uart) == HAL_OK){
            res = 1; // EXITO EN LA CONFIGURACION
        }    
    }
    return res;
}

#endif  
 // fin de SIMO_UART_ENA


 /*
 void MX_USART2_UART_Init(void)
{

 
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  

}

*/