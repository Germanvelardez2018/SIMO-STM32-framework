/**
 * @file gpio.c
 * @author German Velardez(germanvelardez16@gmail.com)
 * @brief  Implementacion del driver para manejo de GPIOS
 * @version 0.1
 * @date 2022-01-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "main.h"
#include "core.h"
#include "gpio.h"





#if SIMO_GPIO_ENA == 1

//! Estructura usada para pasar de simo_pin a un pin de stm32
typedef struct{
    //!Numero de Pin GPIO
    uint32_t index;
    //! Puerto
    GPIO_TypeDef* port;

} __pin__; 



/**
 * @brief Obtiene la instancia de gpio
 * 
 * @param simo_pin instancia SPI simo 
 * @param pin instancia donde se guarda la instancia gpio de STM32
 * @return void
 */

static void __get_pin(SIMO_GPIO_PIN simo_pin,__pin__ *pin )
{
        if( simo_pin <= SIMO_GPIO_15 ) {
            pin->index = simo_pin;
            pin->port=GPIOA;
            __HAL_RCC_GPIOA_CLK_ENABLE();    
            }
        if( (simo_pin >= SIMO_GPIO_16)  && (simo_pin <= SIMO_GPIO_31)) {
            pin->index =  (simo_pin - SIMO_GPIO_16);
            pin->port=GPIOB;
            __HAL_RCC_GPIOB_CLK_ENABLE();
            }
        if( (simo_pin >= SIMO_GPIO_32)  && (simo_pin <= SIMO_GPIO_47)) {
            pin->index = (simo_pin - SIMO_GPIO_32);
            pin->port = GPIOC;
            __HAL_RCC_GPIOC_CLK_ENABLE();
            }
        pin->index = (uint16_t) (1 << (pin->index));
}




        /**
         * @brief 
         * 
         * @param pin 
         * @param mode 
         * @return ** uint32_t 
         */
 void simo_gpio_set(SIMO_GPIO_PIN simo_pin, simo_gpio_mode mode){
     __pin__ pin = {0};
     __get_pin(simo_pin,&pin);
     GPIO_InitTypeDef GPIO_InitStruct = {0};
    switch (mode)  // Salida por default
    {
            case  SIMO_GPIO_OUT:
            GPIO_InitStruct.Mode =  GPIO_MODE_OUTPUT_PP; 
            HAL_GPIO_WritePin(pin.port, pin.index, GPIO_PIN_RESET);// Por seguridad del dispositivo
            break;
            case  SIMO_GPIO_IN:
            GPIO_InitStruct.Mode =GPIO_MODE_INPUT ;
            break;

         #if SIMO_GPIO_ADC_ENA == 1
             case SIMO_GPIO_ADC:
             GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
             break;
         #endif 

       #if SIMO_GPIO_EXT_IRQ == 1

            case  SIMO_GPIO_EXT_IT_RISING: 
            GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
            break;

             case  SIMO_GPIO_EXT_IT_FALLING:
             GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
             break;

             case  SIMO_GPIO_EXT_IT_RISING_FALLING:
             GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
             break;
        #endif
            
         default:
         GPIO_InitStruct.Mode =  GPIO_MODE_OUTPUT_PP; 
         HAL_GPIO_WritePin(pin.port, pin.index, GPIO_PIN_RESET);// Para seguridad del dispositivo
        // GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;

         break;
    }

    GPIO_InitStruct.Pin = pin.index;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(pin.port, &GPIO_InitStruct);
}


void simo_gpio_deinit(SIMO_GPIO_PIN simo_pin){
    // Se podria hacer mas simple?. Probablemente.
    __pin__ pin = {0};
    __get_pin(simo_pin,&pin);
    HAL_GPIO_DeInit(pin.port,pin.index);
}





void simo_gpio_write(SIMO_GPIO_PIN simo_pin, uint32_t value){
   __pin__ pin = {0};
   __get_pin(simo_pin,&pin);
   GPIO_PinState val = (value == 0)? GPIO_PIN_RESET : GPIO_PIN_SET;
   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(pin.port, pin.index, val);
}



void simo_gpio_toogle(SIMO_GPIO_PIN simo_pin){
    __pin__ pin = {0};
    __get_pin(simo_pin,&pin);  
    /*Configure GPIO pin Output Level */
    HAL_GPIO_TogglePin(pin.port, pin.index);
}







        #if SIMO_GPIO_EXT_IRQ   == 1

            /**
             * @brief This function handles EXTI line0 interrupt.
             */
             #if NUM_SIMO_GPIO > 0 

            callback_gpio_ext_it __GPIO_EXT_CALLBACK__ = NULL;
            void EXTI0_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);}
            void EXTI1_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);}
            void EXTI2_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_2);}
            void EXTI3_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_3);}
            void EXTI4_IRQHandler(void){ HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_4);}
            #endif
            #if NUM_SIMO_GPIO > 5 
            uint16_t __GPIO_EXTI9_5_ = 0;
            //Solo podemos tener un solo canal como fuente de esta interrupcion
            void EXTI9_5_IRQHandler(void){
                HAL_GPIO_EXTI_IRQHandler(__GPIO_EXTI9_5_);
            }
            #endif
            #if NUM_SIMO_GPIO > 15 
            uint16_t __GPIO_EXTI15_10_ = 0;
            //Solo podemos tener un solo canal como fuente de esta interrupcion
            void EXTI15_10_IRQHandler(void){
                HAL_GPIO_EXTI_IRQHandler(__GPIO_EXTI15_10_);
            }
            #endif


            /**
             * @brief  Habilita la interrupcion externa del GPIO
             * 
             * @param pin Disponibilidad de pins depende de NUM_SIMO_GPIO
             * @param ena  1 para habilitar 0 para deshabilitar
             */
            void simo_gpio_ena_irq(SIMO_GPIO_PIN pin,uint32_t ena){
                IRQn_Type __GPIO_IRQ= 0;
                switch (pin  % SIMO_GPIO_16){
                     #if NUM_SIMO_GPIO > 0 
                        case SIMO_GPIO_0:
                        __GPIO_IRQ= EXTI0_IRQn;
                        break;
                
                        case SIMO_GPIO_1:
                        __GPIO_IRQ= EXTI1_IRQn;
                        break;
                  
                        case SIMO_GPIO_2:
                        __GPIO_IRQ= EXTI2_IRQn;
                        break;
                         case SIMO_GPIO_3:
                        __GPIO_IRQ= EXTI3_IRQn;
                        break;
                
                        case SIMO_GPIO_4:
                        __GPIO_IRQ= EXTI4_IRQn;
                        break;
                  #endif
                   #if NUM_SIMO_GPIO > 5 
                        case SIMO_GPIO_5:
                        __GPIO_IRQ= EXTI9_5_IRQn;
                        __GPIO_EXTI9_5_ = (1 <<SIMO_GPIO_5);
                        break;
                        case SIMO_GPIO_6:
                        __GPIO_IRQ= EXTI9_5_IRQn;
                        __GPIO_EXTI9_5_ = (1 <<SIMO_GPIO_6);
                        break;
                
                        case SIMO_GPIO_7:
                        __GPIO_IRQ= EXTI9_5_IRQn;
                        __GPIO_EXTI9_5_ = (1 <<SIMO_GPIO_7);
                        break;
                        case SIMO_GPIO_8:
                        __GPIO_IRQ= EXTI9_5_IRQn;
                        __GPIO_EXTI9_5_ = (1 <<SIMO_GPIO_8);
                        break;
                        case SIMO_GPIO_9:
                        __GPIO_IRQ= EXTI9_5_IRQn;
                        __GPIO_EXTI9_5_ = (1 <<SIMO_GPIO_9);
                        
                        break;
                    #endif
                  
                        default:
                    #if NUM_SIMO_GPIO > 15
                        __GPIO_IRQ= EXTI15_10_IRQn; // por default, 
                        __GPIO_EXTI15_10_ = (1 <<(pin  % SIMO_GPIO_16));
                    #endif
                        break;
                }
                if(ena != 0){
                    HAL_NVIC_SetPriority(__GPIO_IRQ, 0, 0);
                    HAL_NVIC_EnableIRQ(__GPIO_IRQ);
                }
                else{
                    HAL_NVIC_DisableIRQ(__GPIO_IRQ);
                }
            }
            


            /**
                 * @brief  EXTI line detection callbacks.
                 * @param  GPIO_Pin: Specifies the pins connected EXTI line
                 * @retval None
                 */
                void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
                {
                    if(__GPIO_EXT_CALLBACK__ != NULL)__GPIO_EXT_CALLBACK__(GPIO_Pin);
                }


         
            simo_state simo_gpio_set_extern_event_callback(callback_gpio_ext_it callback){
                simo_state ret = SIMO_ERROR;
                if( callback != NULL) {
                __GPIO_EXT_CALLBACK__= callback;
                ret = SIMO_OK;
                }
                 return ret;
            }
        #endif

#endif