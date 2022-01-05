/**
 * @file uart.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USART_H
#define __USART_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core.h"



#if SIMO_UART_ENA == 1

uint32_t simo_uart_read(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout );
uint32_t simo_uart_write(SIMO_UART uart,uint8_t* buffer,uint32_t len ,uint32_t timeout,uint32_t ena_callback);

uint32_t simo_uart_init(SIMO_UART uart,uint32_t baudrate);


#if SIMO_UART_IRQ   == 1

    uint32_t simo_uart_set_callback(SIMO_UART uart,uart_irq callback);

    #if NUM_SIMO_UART >0
    void USART1_IRQHandler(void);

        
    #endif
    #if NUM_SIMO_UART >1
    void USART2_IRQHandler(void);
        
    #endif
    #if NUM_SIMO_UART >2
    void USART3_IRQHandler(void);
        
    #endif


#endif


#endif





#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

