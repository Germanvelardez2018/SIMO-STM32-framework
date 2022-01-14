/**
 * @file gpio.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para abstraer el hardware GPIO del microcontrolador
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
                 SIMO_GPIO_OUT,
                 SIMO_GPIO_IN,
                #if SIMO_GPIO_ADC_ENA == 1
                    SIMO_GPIO_ADC,
                #endif 
                #if SIMO_GPIO_EXT_IRQ == 1
                    SIMO_GPIO_EXT_IT_RISING,
                    SIMO_GPIO_EXT_IT_FALLING,
                    SIMO_GPIO_EXT_IT_RISING_FALLING,
                #endif   
             }  simo_gpio_mode;


          

   

        //! Instancias de GPIO disponibles 
        typedef enum {
            #if NUM_SIMO_GPIO > 0      
                SIMO_GPIO_0 , SIMO_GPIO_1, SIMO_GPIO_2, SIMO_GPIO_3, SIMO_GPIO_4,
            #endif
            #if NUM_SIMO_GPIO > 5      
                SIMO_GPIO_5 , SIMO_GPIO_6 ,SIMO_GPIO_7 ,SIMO_GPIO_8 ,SIMO_GPIO_9,
            #endif
            #if NUM_SIMO_GPIO > 10     
                SIMO_GPIO_10 , SIMO_GPIO_11, SIMO_GPIO_12, SIMO_GPIO_13, SIMO_GPIO_14,
            #endif
            #if NUM_SIMO_GPIO > 15     
                SIMO_GPIO_15 , SIMO_GPIO_16 ,SIMO_GPIO_17 ,SIMO_GPIO_18 ,SIMO_GPIO_19,
            #endif
            #if NUM_SIMO_GPIO > 20     
                SIMO_GPIO_20 , SIMO_GPIO_21, SIMO_GPIO_22, SIMO_GPIO_23, SIMO_GPIO_24,
            #endif
            #if NUM_SIMO_GPIO > 25     
                SIMO_GPIO_25 , SIMO_GPIO_26 ,SIMO_GPIO_27 ,SIMO_GPIO_28 ,SIMO_GPIO_29,
            #endif
            #if NUM_SIMO_GPIO > 30     
                SIMO_GPIO_30 , SIMO_GPIO_31, SIMO_GPIO_32, SIMO_GPIO_33, SIMO_GPIO_34,
            #endif
            #if NUM_SIMO_GPIO > 35     
                SIMO_GPIO_35 , SIMO_GPIO_36 ,SIMO_GPIO_37 ,SIMO_GPIO_38 ,SIMO_GPIO_39,
            #endif
            #if NUM_SIMO_GPIO > 40     
                SIMO_GPIO_40 , SIMO_GPIO_41, SIMO_GPIO_42, SIMO_GPIO_43, SIMO_GPIO_44,
            #endif
            #if NUM_SIMO_GPIO > 45     
                SIMO_GPIO_45 , SIMO_GPIO_46 ,SIMO_GPIO_47 ,SIMO_GPIO_48 ,SIMO_GPIO_49,
            #endif
           
        }SIMO_GPIO_PIN;


        /**
         * @brief 
         * 
         * @param pin 
         * @param mode 
         * @return ** uint32_t 
         */
        void simo_gpio_set(SIMO_GPIO_PIN simo_pin, simo_gpio_mode mode);



         void simo_gpio_write(SIMO_GPIO_PIN simo_pin, uint32_t value);



        void simo_gpio_toogle(SIMO_GPIO_PIN simo_pin);

        /**
         * @brief 
         * 
         * @param pin 
         * @param mode 
         * @return ** uint32_t 
         */
        uint32_t simo_gpio_deinit(SIMO_GPIO_PIN pin, simo_gpio_mode mode);



        #if SIMO_GPIO_EXT_IRQ   == 1

            /**
             * @brief  Habilita la interrupcion del timer
             * 
             * @param pin Disponibilidad de pins depende de NUM_SIMO_GPIO
             * @param ena  1 para habilitar 0 para deshabilitar
             */
            void simo_gpio_ena_irq(SIMO_GPIO_PIN pin,uint32_t ena);
            


            /**
             * @brief 
             * 
             * @param pin       Disponibilidad de pins depende de NUM_SIMO_GPIO
             * @param evento    Tipo de evento externo
             * @param callback  Funcion a llamar despues del evento de desborde del timer. Funcion sin parametros y retorna void
             * @return ** uint32_t 
             */
            uint32_t simo_gpio_set_extern_event_callback( callback_gpio_ext_it callback);
        
        #endif // SIMO_GPIO_EXT_IRQ

    #endif


    #ifdef __cplusplus
    }
    #endif
#endif /*__ SIMO_GPIO_H */

