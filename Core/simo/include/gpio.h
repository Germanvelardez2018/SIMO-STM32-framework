/**
 * @file gpio.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para manejo del hardware GPIO del microcontrolador
 * @version 0.1
 * @date 2022-01-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */



/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _SIMO_GPIO_H
#define _SIMO_GPIO_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core.h"
    #if SIMO_GPIO_ENA == 1
            //! Modos de funcionamiento
             typedef enum{
                 SIMO_GPIO_OUT //! Salida digital
                 ,SIMO_GPIO_IN //! Entrada digital
                #if SIMO_GPIO_ADC_ENA == 1
                    ,SIMO_GPIO_ADC //! Entrada analogica
                #endif 
                #if SIMO_GPIO_EXT_IRQ == 1
                    ,SIMO_GPIO_EXT_IT_RISING//! Interrupcion por flanco ascendente 
                    ,SIMO_GPIO_EXT_IT_FALLING//! Interrupcion por flanco descendente
                    ,SIMO_GPIO_EXT_IT_RISING_FALLING//! Interrupcion por flanco ascendente y descendente
                #endif   
             }  simo_gpio_mode;


        //! Instancias de GPIO disponibles. SIMO_GPIO_0 a SIMO_GPIO_15 son A0 a A15, SIMO_GPIO_16 B0 y SIMO_GPIO_31 B15
        typedef enum {

            //GPIOA
            #if NUM_SIMO_GPIO > 0  
            //!En STM32 es PA0   
                SIMO_GPIO_0 , SIMO_GPIO_1, SIMO_GPIO_2, SIMO_GPIO_3, SIMO_GPIO_4,
            #endif
            #if NUM_SIMO_GPIO > 5   
            //!En STM32 es PA5   
   
                SIMO_GPIO_5 , SIMO_GPIO_6 ,SIMO_GPIO_7 ,SIMO_GPIO_8 ,SIMO_GPIO_9,SIMO_GPIO_10 ,
            #endif
            #if NUM_SIMO_GPIO > 10  
            //!En STM32 es PA11   
                 SIMO_GPIO_11, SIMO_GPIO_12, SIMO_GPIO_13, SIMO_GPIO_14,SIMO_GPIO_15 ,
            #endif


            // GPIOB 
            #if NUM_SIMO_GPIO > 15
            //!En STM32 es PB0   
     
                 SIMO_GPIO_16 ,SIMO_GPIO_17 ,SIMO_GPIO_18 ,SIMO_GPIO_19, SIMO_GPIO_20 ,
            #endif
            #if NUM_SIMO_GPIO > 20 
            //!En STM32 es PB5   
    
                SIMO_GPIO_21, SIMO_GPIO_22, SIMO_GPIO_23, SIMO_GPIO_24, SIMO_GPIO_25 ,
            #endif
            #if NUM_SIMO_GPIO > 25
            //!En STM32 es PB10   
                SIMO_GPIO_26 ,SIMO_GPIO_27 ,SIMO_GPIO_28 ,SIMO_GPIO_29,SIMO_GPIO_30 ,SIMO_GPIO_31
            #endif


            //GPIOC
            #if NUM_SIMO_GPIO > 31
            //!En STM32 es PC0   
                 , SIMO_GPIO_32, SIMO_GPIO_33, SIMO_GPIO_34, SIMO_GPIO_35 ,
            #endif
            #if NUM_SIMO_GPIO > 35    
            //! En STM32 es PC5 
                SIMO_GPIO_36 ,SIMO_GPIO_37 ,SIMO_GPIO_38 ,SIMO_GPIO_39, SIMO_GPIO_40 ,
            #endif
            #if NUM_SIMO_GPIO > 40
            //! En STM32 es PC10     
                SIMO_GPIO_41, SIMO_GPIO_42, SIMO_GPIO_43, SIMO_GPIO_44, SIMO_GPIO_45 ,
            #endif
            #if NUM_SIMO_GPIO > 45
            //! En STM32 es PC15     
                SIMO_GPIO_46 
                ,SIMO_GPIO_47 //! En STM32 es PE0,PD0 o PF0. No implementado en gpio.c 
                ,SIMO_GPIO_48 //! En STM32 es PE0,PD0 o PF0. No implementado en gpio.c 
                ,SIMO_GPIO_49,//! En STM32 es PE0,PD0 o PF0. No implementado en gpio.c 
            #endif
           
        }SIMO_GPIO_PIN;


        /**
         * @brief 
         * 
         * @param pin  Pin a configurar:    Ejemplos de conversion SIMO_GPIO_N a ST32 Pin
         *                  SIMO_GPIO_2 == GPIOA, PIN2     
         *                  SIMO_GPIO_20 == GPIOB, PIN4
         *                  SIMO_GPIO_41 == GPIOC,PIN9
         * @param mode 
         * @return ** uint32_t 
         */
        void simo_gpio_set(SIMO_GPIO_PIN simo_pin, simo_gpio_mode mode);


        /**
         * @brief Escribir en el pin GPIO
         * 
         * @param simo_pin  pin  simo gpio a utilizar
         * @param value     valor . 0 es valor bajo, diferente de 0 es valor alto
         * @return ** void 
         */
         void simo_gpio_write(SIMO_GPIO_PIN simo_pin, uint32_t value);


        /**
         * @brief Conmuta el pin seleccionado
         * 
         * @param simo_pin pin simo gpio a utilizar
         * @return ** void 
         */
        void simo_gpio_toogle(SIMO_GPIO_PIN simo_pin);

        /**
         * @brief Deshabilitamos el pin
         * 
         * @param pin pin simo gpio a utilizar
         * @param mode El modo de funcionamiento del pin. Puede ser entrada, salida o pin de interrupcion externa
         * @return ** uint32_t 
         */
        uint32_t simo_gpio_deinit(SIMO_GPIO_PIN pin, simo_gpio_mode mode);



        #if SIMO_GPIO_EXT_IRQ   == 1

            /**
             * @brief  Habilita la interrupcion externa del pin
             * 
             * @param pin Disponibilidad de pins depende de NUM_SIMO_GPIO
             * @param ena  1 para habilitar 0 para deshabilitar
             */
            void simo_gpio_ena_irq(SIMO_GPIO_PIN pin,uint32_t ena);
            


            /**
             * @brief  Agregamos la funcion callback para atender interrupcion externa. 
             * Solo existe un callback para todas las interrupciones externas.
             * @param callback Esta funcion debe retornar void y recibir un uint16_t (pin).
             * @return ** uint32_t 
             */
            uint32_t simo_gpio_set_extern_event_callback( callback_gpio_ext_it callback);
        
        #endif // SIMO_GPIO_EXT_IRQ

    #endif


    #ifdef __cplusplus
    }
    #endif
#endif /*__ SIMO_GPIO_H */

