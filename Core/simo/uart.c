/**
 * @file uart.c
 * @author German Velardez (germanvelardez@gmail.com)
 * @brief  Implementacion del driver para el manejo del hardware UART
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "core.h"
#include "uart.h"
#include "main.h"


#if SIMO_UART_ENA == 1

    

    #if NUM_SIMO_UART >0
        UART_HandleTypeDef huart1;
        #if SIMO_UART_IRQ   == 1
            static  callback_irq __UART1_TX_IRQ__ ;
            static  callback_irq __UART1_RX_IRQ__ ;
            /**
             * @brief This function handles USART2 global interrupt.
             */
            void USART1_IRQHandler(void){
           
            HAL_UART_IRQHandler(&huart1);
            
            }
        #endif
    #endif
    #if NUM_SIMO_UART >1
        UART_HandleTypeDef huart2;
        #if SIMO_UART_IRQ   == 1
            static  callback_irq __UART2_TX_IRQ__ ;
            static  callback_irq __UART2_RX_IRQ__ ;
            /**
             * @brief This function handles USART2 global interrupt.
             */
            void USART2_IRQHandler(void){
           
            HAL_UART_IRQHandler(&huart2);
            
            }
        #endif
    #endif
    #if NUM_SIMO_UART >2
        UART_HandleTypeDef huart3;
        #if SIMO_UART_IRQ   == 1
            static  callback_irq __UART3_TX_IRQ__ ;
            static  callback_irq __UART3_RX_IRQ__ ;
            /**
             * @brief This function handles USART2 global interrupt.
             */
            void USART3_IRQHandler(void){
            HAL_UART_IRQHandler(&huart3);
            }
        #endif
    #endif





/**
 * @brief Obtiene la instancia de UART necesaria
 * 
 * @param uart_enum instancia UART simo : UART_A, UART_B o UART_C
 * @return ** UART_HandleTypeDef* 
 */

static UART_HandleTypeDef* __get_uart(SIMO_UART uart_enum)
{
    UART_HandleTypeDef* uart = NULL;
    switch (uart_enum)
    {
        #if NUM_SIMO_UART >0
            case UART_A:
            uart = &huart1;
            uart->Instance = USART1;
            break;
        #endif
        #if NUM_SIMO_UART >1
            case UART_B:
            uart = &huart2;
            uart->Instance = USART2;
            break;
        #endif
        #if NUM_SIMO_UART >2
            case UART_C:
            uart = &huart3;
            uart->Instance = USART3;
            break;
        #endif
            default:
            break;
    }
    return uart;
}







    uint8_t simo_uart_rx_available(SIMO_UART uart,uint32_t timeout){
        uint8_t data = 0;
        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL)  HAL_UART_Receive(simo_uart,&data,1,timeout);      
        return data;
    }




/**
 * @brief 
 * 
 * @param uart 
 * @param data 
 * @param len 
 * @param timeout 
 * @return ** uint32_t 
 */


uint32_t simo_uart_write(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout, uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto

        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL) {  
            if (ena_callback == 1){
                 if(HAL_UART_Transmit_IT(simo_uart,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_UART_Transmit(simo_uart,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }

           
    }
    return res;
}



/**
 * @brief 
 * 
 * @param uart 
 * @param data 
 * @param len 
 * @param timeout 
 * @return ** uint32_t 
 */

uint32_t simo_uart_read(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto

        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL) {  
            if (ena_callback == 1){
                 if(HAL_UART_Receive_IT(simo_uart,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_UART_Receive(simo_uart,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }

           
    }
    return res;
           
   
}




/**
 * @brief 
 * 
 * @param uart 
 * @param baudrate 
 * @return ** uint32_t 
 */

uint32_t simo_uart_init(SIMO_UART uart,uint32_t baudrate){
        uint32_t res = 0;  // retorna error por defecto
        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL) {  
        simo_uart->Init.BaudRate = baudrate;
        // Configuracion estandar sin flujo por hardware
        simo_uart->Init.WordLength = UART_WORDLENGTH_8B;
        simo_uart->Init.StopBits = UART_STOPBITS_1;
        simo_uart->Init.Parity = UART_PARITY_NONE;
        simo_uart->Init.Mode = UART_MODE_TX_RX;
        simo_uart->Init.HwFlowCtl = UART_HWCONTROL_NONE;
        simo_uart->Init.OverSampling = UART_OVERSAMPLING_16;
        if (HAL_UART_Init(simo_uart) == HAL_OK){
            res = 1; // EXITO EN LA CONFIGURACION
            
        }    
    }
    return res;
}








/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

    #if NUM_SIMO_UART >0
    if(huart->Instance==USART1)
        {
            /* Peripheral clock enable */
            __HAL_RCC_USART1_CLK_ENABLE();
            __HAL_RCC_GPIOA_CLK_ENABLE();
            /**USART1 GPIO Configuration
            PA9     ------> USART1_TX
            PA10     ------> USART1_RX
            */
            GPIO_InitStruct.Pin = GPIO_PIN_9;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
            GPIO_InitStruct.Pin = GPIO_PIN_10;
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);  
        }
    #endif
    #if NUM_SIMO_UART >1
    if(huart->Instance==USART2)
    {  
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /**USART2 GPIO Configuration
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */
        GPIO_InitStruct.Pin = GPIO_PIN_2;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = GPIO_PIN_3;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    #endif
    #if NUM_SIMO_UART >2
    if(huart->Instance==USART3)
        {
            /* Peripheral clock enable */
            __HAL_RCC_USART3_CLK_ENABLE();
            __HAL_RCC_GPIOB_CLK_ENABLE();
            /**USART3 GPIO Configuration
            PB10     ------> USART3_TX
            PB11     ------> USART3_RX
            */
            GPIO_InitStruct.Pin = GPIO_PIN_10;
            GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
            GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
            GPIO_InitStruct.Pin = GPIO_PIN_11;
            GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
            GPIO_InitStruct.Pull = GPIO_NOPULL;
            HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        }  
    #endif
}



/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{



    #if NUM_SIMO_UART >0
    if(huart->Instance==USART1)
        {
            /* Peripheral clock disable */
            __HAL_RCC_USART1_CLK_DISABLE();
            /**USART1 GPIO Configuration
            PA9     ------> USART1_TX
            PA10     ------> USART1_RX
            */
            HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);
        }
    #endif
    #if NUM_SIMO_UART >1
    if(huart->Instance==USART2)
        {
            /* Peripheral clock disable */
            __HAL_RCC_USART2_CLK_DISABLE();
            /**USART2 GPIO Configuration
             * Control por hardware
           
            PA2     ------> USART2_TX
            PA3     ------> USART2_RX
            */
            HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);
        }
    #endif
    #if NUM_SIMO_UART >2
    if(huart->Instance==USART3)
        {
        
            /* Peripheral clock disable */
            __HAL_RCC_USART3_CLK_DISABLE();
            /**USART3 GPIO Configuration
            PB10     ------> USART3_TX
            PB11     ------> USART3_RX
            */
            HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10|GPIO_PIN_11);
        }
    #endif
    
 
}










    #if SIMO_UART_IRQ   == 1
        void simo_uart_ena_irq(SIMO_UART uart,uint32_t ena){
                IRQn_Type __uart= 0;
                switch (uart){
                    #if NUM_SIMO_UART >0
                        case UART_A:
                        __uart= USART1_IRQn;
            
                        break;
                    #endif
                    #if NUM_SIMO_UART >1
                        case UART_B:
                        __uart= USART2_IRQn;
            
                        break;
                    #endif
                    #if NUM_SIMO_UART >2
                        case UART_C:
                        
                        __uart= USART3_IRQn;
        
                        break;
                    #endif
                        default:
                        __uart= USART1_IRQn; // por default, evita errores
                        break;
                }

                if(ena){
                    HAL_NVIC_SetPriority(__uart, 0, 0);
                    HAL_NVIC_EnableIRQ(__uart);
                }
                else{
                    HAL_NVIC_DisableIRQ(__uart);
                }
        }

        #if SIMO_UART_TX_IRQ == 1
            
            uint32_t simo_uart_set_tx_callback(SIMO_UART uart,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (uart)
                    {
                        #if NUM_SIMO_UART >0
                            case UART_A:
                            __UART1_TX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_UART >1
                            case UART_B:
                            __UART2_TX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_UART >2
                            case UART_C:
                            __UART3_TX_IRQ__ = callback;
                            break;
                        #endif
                            default:
                            res= 0;
                            break;
                    }

            }
                return res;
            }

            void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

            #if NUM_SIMO_UART >0
                if(huart == &huart1){
                //funcion callback UART1
                if(__UART1_TX_IRQ__ != NULL) __UART1_TX_IRQ__();
                }
                
            #endif
            #if NUM_SIMO_UART >1
                if(huart == &huart2){
                // funcion callbacl UART2
                if(__UART2_TX_IRQ__ != NULL) __UART2_TX_IRQ__();
                }
            
            #endif
            #if NUM_SIMO_UART >2
                if(huart == &huart3){
                // Funcion callback UART3
                if(__UART3_TX_IRQ__ != NULL) __UART3_TX_IRQ__();
                }
        
            #endif

            }

        #endif // SIMO_UART_TX_IRQ

        
        #if SIMO_UART_RX_IRQ == 1

            void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

                    #if NUM_SIMO_UART >0
                        if(huart == &huart1){
                        //funcion callback UART1
                        if(__UART1_RX_IRQ__ != NULL) __UART1_RX_IRQ__();
                        }
                    #endif
                    #if NUM_SIMO_UART >1
                        if(huart == &huart2){
                        // funcion callbacl UART2
                        if(__UART2_RX_IRQ__ != NULL) __UART2_RX_IRQ__();
                        }     
                    #endif
                    #if NUM_SIMO_UART >2
                        if(huart == &huart3){
                        // Funcion callback UART3
                        if(__UART3_RX_IRQ__ != NULL) __UART3_RX_IRQ__();
                        } 
                    #endif
            }
        
        
            uint32_t simo_uart_set_rx_callback(SIMO_UART uart,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (uart)
                    {
                        #if NUM_SIMO_UART >0
                            case UART_A:
                            __UART1_RX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_UART >1
                            case UART_B:
                            __UART2_RX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_UART >2
                            case UART_C:
                            __UART3_RX_IRQ__ = callback;   
                            break;
                        #endif
                            default:
                            res= 0;
                            break;
                    }
            }
                return res;
            }
        #endif // SIMO_UART_RX_IRQ

        
        
        #endif      // SIMO_UART_IRQ
#endif  // SIMO_UART_ENA 















