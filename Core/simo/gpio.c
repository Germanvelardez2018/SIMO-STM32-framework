/**
 * @file gpio.c
 * @author your name (you@domain.com)
 * @brief 
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


typedef struct{
    uint32_t index;
    GPIO_TypeDef* port;

} __pin__; 



/**
 * @brief Obtiene la instancia de SPI necesaria
 * 
 * @param SPI_enum instancia SPI simo : SPI_A, SPI_B o SPI_C
 * @return ** SPI_HandleTypeDef* 
 */

static void __get_pin(SIMO_GPIO_PIN simo_pin,__pin__ *pin )
{

    __HAL_RCC_GPIOA_CLK_ENABLE();
        if( simo_pin < SIMO_GPIO_15 ) {
            pin->index = simo_pin;

            pin->port=GPIOA;
            __HAL_RCC_GPIOA_CLK_ENABLE();    
            }
        if( simo_pin > SIMO_GPIO_15  && simo_pin < SIMO_GPIO_30) {
            pin->index =  (simo_pin - SIMO_GPIO_15);
            pin->port=GPIOB;
            __HAL_RCC_GPIOB_CLK_ENABLE();
            }
        if( simo_pin > SIMO_GPIO_30  && simo_pin < SIMO_GPIO_44) {
            pin->index = (simo_pin - SIMO_GPIO_30);
            pin->port = GPIOC;
            __HAL_RCC_GPIOC_CLK_ENABLE();
            }

               pin->index = (uint16_t) (1 << (pin->index));
           //  pin->index = 4;
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
        /*Configure GPIO pin Output Level */
        HAL_GPIO_WritePin(pin.port, pin.index, GPIO_PIN_RESET);

        /*Configure GPIO pin : PB2 */
        GPIO_InitStruct.Pin = pin.index;
        GPIO_InitStruct.Mode = (mode == SIMO_GPIO_IN)?  GPIO_MODE_INPUT  :GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_HIGH;
        HAL_GPIO_Init(pin.port, &GPIO_InitStruct);

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
           // HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_2);


        }



        /**
         * @brief 
         * 
         * @param pin 
         * @param mode 
         * @return ** uint32_t 
         */
        uint32_t simo_gpio_deinit(SIMO_GPIO_PIN pin, simo_gpio_mode mode){
            return 0;
        }



        #if SIMO_GPIO_EXT_IRQ   == 1

            /**
             * @brief  Habilita la interrupcion del timer
             * 
             * @param pin Disponibilidad de pins depende de NUM_SIMO_GPIO
             * @param ena  1 para habilitar 0 para deshabilitar
             */
            void simo_gpio_ena_irq(SIMO_GPIO_PIN pin,uint32_t ena){
                
            }
            


            /**
             * @brief 
             * 
             * @param pin       Disponibilidad de pins depende de NUM_SIMO_GPIO
             * @param evento    Tipo de evento externo
             * @param callback  Funcion a llamar despues del evento de desborde del timer. Funcion sin parametros y retorna void
             * @return ** uint32_t 
             */
            uint32_t simo_gpio_set_extern_event_callback(SIMO_GPIO_PIN Pin,simo_gpio_event evento,timer_irq callback){
                return 0;
            }
        #endif

    #endif