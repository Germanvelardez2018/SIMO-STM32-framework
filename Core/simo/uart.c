/**
 * @file uart.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "uart.h"
#include "main.h"













    // Estructuras

    #if NUM_SIMO_UART >0
        UART_HandleTypeDef huart1;
        #if SIMO_UART_IRQ   == 1
            static  uart_irq __UART1_IRQ__ ;
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
            static  uart_irq __UART2_IRQ__ ;
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
            static  uart_irq __UART3_IRQ__ ;
            /**
             * @brief This function handles USART2 global interrupt.
             */
            void USART3_IRQHandler(void){
           
            HAL_UART_IRQHandler(&huart3);
            
            }
        #endif
    #endif



 #if SIMO_UART_IRQ   == 1
            void simo_uart_set_irq(SIMO_UART uart, uart_irq callback){
                if (callback != NULL)
                {
                    switch (uart)
                    {
                        #if NUM_SIMO_UART >0
                            case UART_A:
                            __UART1_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_UART >1
                            case UART_B:
                            __UART2_IRQ__ = callback; 
                            break;
                        #endif
                        #if NUM_SIMO_UART >2
                            case UART_C:
                            __UART3_IRQ__ = callback;
                            break;
                        #endif
                            default:
                            break;
                    }
                }
            }
#endif






//--------------------------------------
#if NUM_SIMO_UART > 0

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






void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){

        #if NUM_SIMO_UART >0
            if(huart == &huart1){
            //funcion callback UART1
            if(__UART1_IRQ__ != NULL) __UART1_IRQ__();
            }
            
        #endif
        #if NUM_SIMO_UART >1
              if(huart == &huart2){
            // funcion callbacl UART2
            if(__UART2_IRQ__ != NULL) __UART2_IRQ__();
              }
          
        #endif
        #if NUM_SIMO_UART >2
              if(huart == &huart3){
            // Funcion callback UART3
            if(__UART3_IRQ__ != NULL) __UART3_IRQ__();
              }
    
        #endif



}




void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

        #if NUM_SIMO_UART >0
            if(huart == &huart1){
            //funcion callback UART1
            if(__UART1_IRQ__ != NULL) __UART1_IRQ__();
            }
            
        #endif
        #if NUM_SIMO_UART >1
              if(huart == &huart2){
            // funcion callbacl UART2
            if(__UART2_IRQ__ != NULL) __UART2_IRQ__();
              }
          
        #endif
        #if NUM_SIMO_UART >2
              if(huart == &huart3){
            // Funcion callback UART3
            if(__UART3_IRQ__ != NULL) __UART3_IRQ__();
              }
    
        #endif



}




uint32_t simo_uart_set_callback(SIMO_UART uart,uart_irq callback)
{
    uint32_t res = 0;
   if (callback != NULL){
        res = 1;
        switch (uart)
        {
            #if NUM_SIMO_UART >0
                case UART_A:
                __UART1_IRQ__ = callback;
            
                break;
            #endif
            #if NUM_SIMO_UART >1
                case UART_B:
                __UART1_IRQ__ = callback;
            
                break;
            #endif
            #if NUM_SIMO_UART >2
                case UART_C:
                __UART1_IRQ__ = callback;
            
                break;
            #endif
                default:
                res= 0;
                break;
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

uint32_t simo_uart_read(SIMO_UART uart,uint8_t* data,uint32_t len, uint32_t timeout ){
    uint32_t res = 0;  // retorna error por defecto

        UART_HandleTypeDef* simo_uart = __get_uart(uart);
        if(simo_uart != NULL) {     
            if(HAL_UART_Receive(simo_uart,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
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

#endif  
 // fin de SIMO_UART_ENA
















/**
* @brief UART MSP Initialization
* This function configures the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(huart->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
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

  /* USER CODE BEGIN USART1_MspInit 1 */
   /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration
    PA0-WKUP     ------> USART2_CTS
    PA1     ------> USART2_RTS
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }

}

/**
* @brief UART MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param huart: UART handle pointer
* @retval None
*/
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  if(huart->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();

    /**USART1 GPIO Configuration
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(huart->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();

    /**USART2 GPIO Configuration
    PA0-WKUP     ------> USART2_CTS
    PA1     ------> USART2_RTS
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt DeInit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }

}






 /*
 void MX_USART2_UART_Init(void)
{

 
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  

}

*/