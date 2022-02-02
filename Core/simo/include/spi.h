/**
 * @file spi.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para manejar hardware SPI
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */






/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SIMO_SPI_H
#define __SIMO_SPI_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core.h"






#if SIMO_SPI_ENA == 1


     typedef enum{

        //!DIVISOR DE CLOCK
         SIMO_SPI_PRESCALER_2 =   2
        //!DIVISOR DE CLOCK
        ,SIMO_SPI_PRESCALER_4 =   4
        //!DIVISOR DE CLOCK
        ,SIMO_SPI_PRESCALER_8 =   8
        //!DIVISOR DE CLOCK
        ,SIMO_SPI_PRESCALER_16 =  16
        //!DIVISOR DE CLOCK
        ,SIMO_SPI_PRESCALER_32 =  32
        //!DIVISOR DE CLOCK
        ,SIMO_SPI_PRESCALER_64 =  64
        //!DIVISOR DE CLOCK
        ,SIMO_SPI_PRESCALER_128 = 128
        //!DIVISOR DE CLOCK
        ,SIMO_SPI_PRESCALER_256 = 256

    } simo_spi_prescaler;








     /**
     * @brief Leer un buffer de datos mediante puerto SPI
     * 
     * @param SPI SPI a iniciar. SPI_A, SPI_B . NUM_SIMO_SPI
     * @param buffer    Buffer para almacenar datos a leer.
     * @param len       Tamanio del buffer de datos a leer.
     * @param timeout   Timeout de la operacion de escritura. En caso de habilitar callback timeout es invalidado
     * @param ena_callback  Habilita la transmicion de datos mediante interrupciones. Modo no bloqueante de operacion
     * @return ** uint32_t 
     */
    uint32_t simo_spi_read(SIMO_SPI spi,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback );




  /**
     * @brief Enviar un buffer de datos mediante puerto SPI
     * 
     * @param SPI SPI a iniciar. SPI_A, SPI_B . NUM_SIMO_SPI
     * @param buffer    Buffer de datos a enviar.
     * @param len       Tamanio del buffer de datos a enviar
     * @param timeout   Timeout de la operacion de escritura. En caso de habilitar callback timeout es invalidado
     * @param ena_callback  Habilita la transmicion de datos mediante interrupciones. Modo no bloqueante de operacion
     * @return ** uint32_t 
     */
    uint32_t simo_spi_write(SIMO_SPI spi,uint8_t* buffer,uint32_t len ,uint32_t timeout,uint32_t ena_callback);




    /**
     * @brief Enviar y recibir un buffer de datos mediante puerto SPI
     * 
     * @param SPI SPI a iniciar. SPI_A, SPI_B . NUM_SIMO_SPI
     * @param buffer_tx Buffer de datos a transmitir
     * @param buffer_rx Buffer para almacenar datos leidos
     * @param len       Tamanio del buffer de datos a enviar
     * @param timeout   Timeout de la operacion de escritura. En caso de habilitar callback timeout es invalidado
     * @param ena_callback  Habilita la transmicion de datos mediante interrupciones. Modo no bloqueante de operacion
     * @return ** uint32_t 
     */
    uint32_t simo_spi_write_read(SIMO_SPI spi,uint8_t* buffer_tx,uint8_t* buffer_rx ,uint32_t len ,uint32_t timeout,uint32_t ena_callback);


    /**
     * @brief Inicia el puerto SPI.
     * 
     * @param SPI SPI a iniciar. SPI_A, SPI_B y SPI_C. NUM_SIMO_SPI
     * @param prescaler  el prescaler puede dividir el clock por un rango de valores( 2, 4 ,8 ,...,256).
     * Recordar que el maximo valor de clock de SPI es 10Mhz.Tambien SPI1 alimentado por APB1 y SP2 alimentado por APB2
     * @return ** uint32_t 
     */
    uint32_t simo_spi_init(SIMO_SPI SPI,simo_spi_prescaler prescaler);


    #if SIMO_SPI_IRQ   == 1

        //Activo o desactivo las interrupciones
        void simo_spi_ena_irq(SIMO_SPI spi,uint32_t ena);
        
        #if SIMO_SPI_TX_IRQ == 1
         /**
         * @brief Configuro una funcion callback para el evento SPI TX
         * 
         * @param SPI SPI a utilizar. SPI_A , SPI_B . Visibilidad depende de NUM_SIMO_SPI
         * @param callback  Funcion sin argumentos y  retorna void 
         * @return ** uint32_t   1 Exitoso, 0 Error
         */
            uint32_t simo_spi_set_tx_callback(SIMO_SPI spi,callback_irq callback);
        #endif
        #if SIMO_SPI_RX_IRQ == 1
         /**
         * @brief Configuro una funcion callback para el evento SPI RX
         * 
         * @param SPI SPI a utilizar. SPI_A , SPI_B . Visibilidad depende de NUM_SIMO_SPI
         * @param callback  Funcion sin argumentos y  retorna void 
         * @return ** uint32_t   1 Exitoso, 0 Error
         */
            uint32_t simo_spi_set_rx_callback(SIMO_SPI spi,callback_irq callback);
        #endif
          #if SIMO_SPI_TX_RX_IRQ == 1
         /**
         * @brief Configuro una funcion callback para el evento SPI tanto TX como RX
         * 
         * @param SPI SPI a utilizar. SPI_A , SPI_B . Visibilidad depende de NUM_SIMO_SPI
         * @param callback  Funcion sin argumentos y  retorna void 
         * @return ** uint32_t   1 Exitoso, 0 Error
         */
            uint32_t simo_spi_set_tx_rx_callback(SIMO_SPI spi,callback_irq callback);
        #endif
    
    #endif

#endif





#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */






