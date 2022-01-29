/**
 * @file uart.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para abstraer el hardware UART 
 * @version 0.1
 * @date 2022-01-14
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



    /**
     * @brief  Verificar si hay datos en buffer rx
     * 
     * @param uart 
     * @param timeout
     * @return ** uint8_t 
     */
    uint8_t simo_uart_rx_available(SIMO_UART uart,uint32_t timeout);


     /**
     * @brief Leer un buffer de datos mediante puerto UART
     * 
     * @param uart UART a iniciar. UART_A, UART_B y UART_C. NUM_SIMO_UART
     * @param buffer    Buffer para almacenar datos a leer.
     * @param len       Tamanio del buffer de datos a leer.
     * @param timeout   Timeout de la operacion de escritura. En caso de habilitar callback timeout es invalidado
     * @param ena_callback  Habilita la transmicion de datos mediante interrupciones. Modo no bloqueante de operacion
     * @return ** uint32_t 
     */
    uint32_t simo_uart_read(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback );


    /**
     * @brief Enviar un buffer de datos mediante puerto UART
     * 
     * @param uart UART a iniciar. UART_A, UART_B y UART_C. NUM_SIMO_UART
     * @param buffer    Buffer de datos a enviar.
     * @param len       Tamanio del buffer de datos a enviar
     * @param timeout   Timeout de la operacion de escritura. En caso de habilitar callback timeout es invalidado
     * @param ena_callback  Habilita la transmicion de datos mediante interrupciones. Modo no bloqueante de operacion
     * @return ** uint32_t 
     */
    uint32_t simo_uart_write(SIMO_UART uart,uint8_t* buffer,uint32_t len ,uint32_t timeout,uint32_t ena_callback);


    /**
     * @brief Inicia el puerto UART.
     * 
     * @param uart UART a iniciar. UART_A, UART_B y UART_C. NUM_SIMO_UART
     * @param baudrate  Baudios de la comunicacion
     * @return ** uint32_t 
     */
    uint32_t simo_uart_init(SIMO_UART uart,uint32_t baudrate);


    #if SIMO_UART_IRQ   == 1

        //Activo o desactivo las interrupciones
        void simo_uart_ena_irq(SIMO_UART uart,uint32_t ena);
        
        #if SIMO_UART_TX_IRQ == 1
         /**
         * @brief Configuro una funcion callback para el evento UART TX
         * 
         * @param uart Uart a utilizar. UART_A , UART_B o UART_C. Visibilidad depende de NUM_SIMO_UART
         * @param callback  Funcion sin argumentos y  retorna void 
         * @return ** uint32_t   1 Exitoso, 0 Error
         */
            uint32_t simo_uart_set_tx_callback(SIMO_UART uart,callback_irq callback);
        #endif
        #if SIMO_UART_RX_IRQ == 1
         /**
         * @brief Configuro una funcion callback para el evento UART RX
         * 
         * @param uart Uart a utilizar. UART_A , UART_B o UART_C. Visibilidad depende de NUM_SIMO_UART
         * @param callback  Funcion sin argumentos y  retorna void 
         * @return ** uint32_t   1 Exitoso, 0 Error
         */
            uint32_t simo_uart_set_rx_callback(SIMO_UART uart,callback_irq callback);
        #endif
    
    #endif

#endif





#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

