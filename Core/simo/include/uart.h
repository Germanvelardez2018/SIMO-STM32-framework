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

    uint32_t simo_uart_read(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback );
    uint32_t simo_uart_write(SIMO_UART uart,uint8_t* buffer,uint32_t len ,uint32_t timeout,uint32_t ena_callback);

    uint32_t simo_uart_init(SIMO_UART uart,uint32_t baudrate);


    #if SIMO_UART_IRQ   == 1

        //Activo o desactivo las interrupciones
        void simo_uart_ena_irq(SIMO_UART uart,uint32_t ena);
        
        #if SIMO_UART_TX_IRQ == 1
            uint32_t simo_uart_set_tx_callback(SIMO_UART uart,uart_irq callback);
        #endif
        #if SIMO_UART_RX_IRQ == 1
            uint32_t simo_uart_set_rx_callback(SIMO_UART uart,uart_irq callback);
        #endif

    
#endif

    

#endif





#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

