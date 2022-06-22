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




 /**I2C1 UNICO HARDWARE DISPONIBLE EN EL FRAMEWORK
    PB6     ------> I2C1_SCL
    PB7     ------> I2C1_SDA
    */



#if SIMO_I2C_ENA == 1
    
   #if SIMO_I2C_MASTER_ENA == 1

    /**
     * @brief 
     * 
     * @param i2c 
     * @param clock_speed 
     * @param address_7bits 
     * @return ** simo_state 
     */
    
    simo_state simo_i2c_init(SIMO_I2C i2c,uint32_t clock_speed,uint32_t address_7bits);
    
    
    /**
     * @brief Desconfigura el puerto I2C.
     * 
     * @param I2C 
     * @return ** void 
     */
    void simo_i2c_deinit(SIMO_I2C I2C);




    simo_state simo_i2c_mem_write(   SIMO_I2C i2c,
                                uint16_t address,
                                uint16_t mem_address,
                                uint16_t mem_size,
                                uint8_t* data,
                                uint32_t len,
                                uint32_t timeout,
                                uint32_t ena_callback );


    simo_state simo_i2c_mem_read(   SIMO_I2C i2c,
                                uint16_t address,
                                uint16_t mem_address,
                                uint16_t mem_size,
                                uint8_t* data,
                                uint32_t len,
                                uint32_t timeout,
                                uint32_t ena_callback );







    /**
    * @brief 
    * 
    * @param i2c 
    * @param address 
    * @param data 
    * @param len 
    * @param timeout 
    * @param ena_callback 
    * @return ** simo_state 
    */
    simo_state simo_i2c_master_read(SIMO_I2C i2c,uint16_t address,uint8_t* data,uint32_t len,uint32_t timeout,uint32_t ena_callback );


    /**
     * @brief 
     * 
     * @param i2c 
     * @param address 
     * @param data 
     * @param len 
     * @param timeout 
     * @param ena_callback 
     * @return ** simo_state 
     */
    simo_state simo_i2c_master_write(SIMO_I2C i2c,uint16_t address,uint8_t* data,uint32_t len, uint32_t timeout, uint32_t ena_callback );








        // Transmicion de datos mediante interfaz I2C
        #if SIMO_I2C_IRQ == 1

        /**
         * @brief 
         * 
         * @param i2c 
         * @param callback 
         * @return ** simo_state 
         */
        simo_state simo_i2c_set_master_rx_callback(SIMO_I2C i2c,callback_irq callback);
       
       
       /**
        * @brief 
        * 
        * @param i2c 
        * @param callback 
        * @return ** uint32_t 
        */
            
        simo_state simo_i2c_set_master_tx_callback(SIMO_I2C i2c,callback_irq callback);
        

        //Modo  manejo de memoria


        #endif // I2C IRQ






    #endif //SIMO MASTER ENABLE

    #if SIMO_I2C_SLAVE_ENA == 1
    /**
     * @brief 
     * 
     * @param i2c 
     * @param data 
     * @param len 
     * @param timeout 
     * @param ena_callback 
     * @return ** simo_state 
     */
    simo_state simo_i2c_slave_read(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback );
        
   
    /**
     * @brief 
     * 
     * @param i2c 
     * @param data 
     * @param len 
     * @param timeout 
     * @param ena_callback 
     * @return ** simo_state 
     */
    simo_state simo_i2c_slave_write(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t ena_callback );



        #if SIMO_I2C_IRQ == 1
         
        

        /**
         * @brief 
         * 
         * @param I2C 
         * @param callback 
         * @return ** simo_state 
         */
        simo_state simo_i2c_set_slave_tx_callback(SIMO_I2C I2C,callback_irq callback);

        /**
         * @brief 
         * 
         * @param i2c 
         * @param callback 
         * @return ** simo_state 
         */
        simo_state simo_uart_set_slave_rx_callback(SIMO_I2C i2c,callback_irq callback);

        #endif



    #endif // SIMO SLAVE ENA
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
        



    
    #endif

#endif





#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

