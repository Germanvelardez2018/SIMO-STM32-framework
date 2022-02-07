/**
 * @file I2C.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para manejar el hardware I2C 
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __I2C_H
#define __I2C_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core.h"



#if SIMO_I2C_ENA == 1

    /**
     * @brief 
     * 
     * @param i2c 
     * @param data 
     * @param len 
     * @param timeout 
     * @param ena_callback 
     * @return ** uint32_t 
     */
    uint32_t simo_i2c_slave_write(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t timeout, uint32_t ena_callback );

      
    /**
     * @brief 
     * 
     * @param i2c 
     * @param address 
     * @param data 
     * @param len 
     * @param timeout 
     * @param ena_callback 
     * @return ** uint32_t 
     */
    uint32_t simo_i2c_master_write(SIMO_I2C i2c,uint16_t address,uint8_t* data,uint32_t len, uint32_t timeout, uint32_t ena_callback );
         
    /**
     * @brief 
     * 
     * @param i2c 
     * @param data 
     * @param len 
     * @param timeout 
     * @param ena_callback 
     * @return ** uint32_t 
     */
    uint32_t simo_i2c_slave_read(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback );
        
    /**
     * @brief 
     * 
     * @param i2c 
     * @param data 
     * @param len 
     * @param timeout 
     * @param ena_callback 
     * @return ** uint32_t 
     */
    uint32_t simo_i2c_master_read(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback );
          



    /**
     * @brief Desconfigura el puerto I2C.
     * 
     * @param I2C 
     * @return ** void 
     */
    void simo_i2c_deinit(SIMO_I2C I2C);


    #if SIMO_I2C_IRQ   == 1

        //Activo o desactivo las interrupciones

        /**
         * @brief 
         * 
         * @param i2c 
         * @param ena_ev_event 
         * @param ena_er_ev 
         * @return ** void 
         */

        void simo_i2c_ena_irq(SIMO_I2C i2c,uint32_t ena_ev_event,uint32_t ena_er_ev);
        
        #if SIMO_I2C_TX_IRQ == 1
         /**
         * @brief Configuro una funcion callback para el evento I2C TX
         * 
         * @param I2C I2C a utilizar. I2C_A , I2C_B o I2C_C. Visibilidad depende de NUM_SIMO_I2C
         * @param callback  Funcion sin argumentos y  retorna void 
         * @return ** uint32_t   1 Exitoso, 0 Error
         */
            uint32_t simo_i2c_set_tx_callback(SIMO_I2C I2C,callback_irq callback);
        #endif
        #if SIMO_I2C_RX_IRQ == 1
         /**
         * @brief Configuro una funcion callback para el evento I2C RX
         * 
         * @param I2C I2C a utilizar. I2C_A , I2C_B o I2C_C. Visibilidad depende de NUM_SIMO_I2C
         * @param callback  Funcion sin argumentos y  retorna void 
         * @return ** uint32_t   1 Exitoso, 0 Error
         */
            uint32_t simo_i2c_set_rx_callback(SIMO_I2C I2C,callback_irq callback);
        #endif
    
    #endif

#endif





#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

