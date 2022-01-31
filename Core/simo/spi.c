/**
 * @file spi.c
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Implementacion del driver para el manejo del hardware SPI
 * @version 0.1
 * @date 2022-01-11
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#include "spi.h"
#include "clock_config.h"
#include "main.h"














#if SIMO_SPI_ENA == 1

    //Señal de reloj maxima soportada por el hardware SPI.Se calcula con el clock base del spi (SPI1 APB1 y SP2 APB2 )y el valor del prescaler
    #define SPI_CLOCK_MAX        10000000 // 10Mhz
  

    #if NUM_SIMO_SPI >0


        // SPI CLOCK APB2. BAUDRATE MAX 10MHZ
        SPI_HandleTypeDef hspi1;
        #if SIMO_SPI_IRQ   == 1
            static  callback_irq __SPI1_TX_IRQ__ ;
            static  callback_irq __SPI1_RX_IRQ__ ;
            static  callback_irq __SPI1_TX_RX_IRQ__;
            /**
             * @brief This function handles USART2 global interrupt.
             */
            void SPI1_IRQHandler(void){
           
            HAL_SPI_IRQHandler(&hspi1);
            
            }
        #endif
    #endif
    #if NUM_SIMO_SPI >1

         // SPI CLOCK APB1. BAUDRATE MAX 10MHZ
        SPI_HandleTypeDef hspi2;
        #if SIMO_SPI_IRQ   == 1
            static  callback_irq __SPI2_TX_IRQ__ ;
            static  callback_irq __SPI2_RX_IRQ__ ;
            static  callback_irq __SPI2_TX_RX_IRQ__;
            /**
             * @brief This function handles USART2 global interrupt.
             */
            void SPI2_IRQHandler(void){
           
            HAL_SPI_IRQHandler(&hspi2);
            
            }
        #endif
    #endif
    







/**
 * @brief Obtiene la instancia de SPI necesaria
 * 
 * @param SPI_enum instancia SPI simo : SPI_A, SPI_B o SPI_C
 * @return ** SPI_HandleTypeDef* 
 */

static uint32_t __get_prescaler(simo_spi_prescaler prescaler)
{
    uint32_t _prescaler = 0;
        switch (prescaler)
        {
            case  SIMO_SPI_PRESCALER_2 :
                _prescaler = SPI_BAUDRATEPRESCALER_2;
                break;
            
            case  SIMO_SPI_PRESCALER_4 :
                _prescaler = SPI_BAUDRATEPRESCALER_4;
                break;

            case  SIMO_SPI_PRESCALER_16 :
                _prescaler = SPI_BAUDRATEPRESCALER_16;
                break;
            case  SIMO_SPI_PRESCALER_32 :
                _prescaler = SPI_BAUDRATEPRESCALER_32;
                break;
            case  SIMO_SPI_PRESCALER_64 :
                _prescaler = SPI_BAUDRATEPRESCALER_64;
                break;

            case  SIMO_SPI_PRESCALER_128 :
                _prescaler = SPI_BAUDRATEPRESCALER_128;
                break;
            case  SIMO_SPI_PRESCALER_256 :
                _prescaler = SPI_BAUDRATEPRESCALER_256;
                break;

            default:
                _prescaler = SPI_BAUDRATEPRESCALER_4;
                break;
        }
    return _prescaler;
}





/**
 * @brief Obtiene la instancia de SPI necesaria
 * 
 * @param SPI_enum instancia SPI simo : SPI_A, SPI_B o SPI_C
 * @return ** SPI_HandleTypeDef* 
 */

static SPI_HandleTypeDef* __get_spi(SIMO_SPI spi_enum)
{
    SPI_HandleTypeDef* SPI = NULL;
    switch (spi_enum)
    {
        #if NUM_SIMO_SPI >0
            case SPI_A:
            SPI = &hspi1;
            SPI->Instance = SPI1;
            break;
        #endif
        #if NUM_SIMO_SPI >1
            case SPI_B:
            SPI = &hspi2;
            SPI->Instance = SPI2;
            break;
        #endif
       
            default:
            break;
    }
    return SPI;
}






uint32_t simo_spi_write(SIMO_SPI spi,uint8_t* data,uint32_t len, uint32_t timeout, uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto

        SPI_HandleTypeDef* simo_spi = __get_spi(spi);
        if(simo_spi != NULL) {  
            if (ena_callback == 1){
                 if(HAL_SPI_Transmit_IT(simo_spi,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_SPI_Transmit(simo_spi,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }

           
    }
    return res;
}




uint32_t simo_spi_read(SIMO_SPI spi,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto

        SPI_HandleTypeDef* simo_spi = __get_spi(spi);
        if(simo_spi != NULL) {  
            if (ena_callback == 1){
                 if(HAL_SPI_Receive_IT(simo_spi,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_SPI_Receive(simo_spi,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }

           
    }
    return res;
           
   
}


uint32_t simo_spi_write_read(SIMO_SPI spi,uint8_t* buffer_tx,uint8_t* buffer_rx ,uint32_t len ,uint32_t timeout,uint32_t ena_callback){
     uint32_t res = 0;  // retorna error por defecto

        SPI_HandleTypeDef* simo_spi = __get_spi(spi);
        if(simo_spi != NULL) {  
            if (ena_callback == 1){
                 if(HAL_SPI_TransmitReceive_IT(simo_spi,buffer_tx,buffer_rx,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_SPI_TransmitReceive(simo_spi,buffer_tx,buffer_rx,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }           
    }
    return res;

}





/**
 * @brief 
 * 
 * @param SPI 
 * @param baudrate 
 * @return ** uint32_t 
 */

uint32_t simo_spi_init(SIMO_SPI SPI,simo_spi_prescaler prescaler){
        uint32_t res = 0;  // retorna error por defecto
        SPI_HandleTypeDef* simo_SPI = __get_spi(SPI);   
        uint32_t __prescaler = __get_prescaler(prescaler);     
        
        if(simo_SPI != NULL) {  
           
            simo_SPI->Init.Mode = SPI_MODE_MASTER;
            simo_SPI->Init.Direction = SPI_DIRECTION_2LINES;
            simo_SPI->Init.DataSize = SPI_DATASIZE_8BIT;
            simo_SPI->Init.CLKPolarity = SPI_POLARITY_LOW;
            simo_SPI->Init.CLKPhase = SPI_PHASE_1EDGE;
            simo_SPI->Init.NSS = SPI_NSS_SOFT;
            simo_SPI->Init.BaudRatePrescaler = __prescaler;
            simo_SPI->Init.FirstBit = SPI_FIRSTBIT_MSB;
            simo_SPI->Init.TIMode = SPI_TIMODE_DISABLE;
            simo_SPI->Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
            simo_SPI->Init.CRCPolynomial = 10;
            if (HAL_SPI_Init(simo_SPI) != HAL_OK)
            {
                Error_Handler();
            }
       
    }
    return res;
}








/**
* @brief SPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hSPI: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

    #if NUM_SIMO_SPI >0
    if(hspi->Instance==SPI1)
    {
        /* Peripheral clock enable */
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI1 GPIO Configuration
        PB3     ------> SPI1_SCK
        PB4     ------> SPI1_MISO
        PB5     ------> SPI1_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_5;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = GPIO_PIN_4;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        __HAL_AFIO_REMAP_SPI1_ENABLE();
    }
    #endif
    #if NUM_SIMO_SPI >1
    if(hspi->Instance==SPI2)
    {
        /* Peripheral clock enable */
        __HAL_RCC_SPI2_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();
        /**SPI2 GPIO Configuration
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI
        */
        GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_15;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
        GPIO_InitStruct.Pin = GPIO_PIN_14;
        GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
       
    }
    #endif
   
}



/**
* @brief SPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hSPI: SPI handle pointer
* @retval None
*/
void HAL_SPI_MspDeInit(SPI_HandleTypeDef* hspi)
{
    #if NUM_SIMO_SPI >0
    if(hspi->Instance==SPI1)
    {
        /* Peripheral clock disable */
        __HAL_RCC_SPI1_CLK_DISABLE();

        /**SPI1 GPIO Configuration
        PB3     ------> SPI1_SCK
        PB4     ------> SPI1_MISO
        PB5     ------> SPI1_MOSI
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5);
    }
    #endif
    #if NUM_SIMO_SPI >1
    if(hspi->Instance==SPI2)
    {
           /* Peripheral clock disable */
        __HAL_RCC_SPI2_CLK_DISABLE();
        /**SPI2 GPIO Configuration
        PB13     ------> SPI2_SCK
        PB14     ------> SPI2_MISO
        PB15     ------> SPI2_MOSI
        */
        HAL_GPIO_DeInit(GPIOB, GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15);
    }
    #endif
}










    #if SIMO_SPI_IRQ   == 1
        void simo_spi_ena_irq(SIMO_SPI spi,uint32_t ena){
                IRQn_Type __SPI= 0;
                switch (spi){
                    #if NUM_SIMO_SPI >0
                        case SPI_A:
                        __SPI= SPI1_IRQn;
            
                        break;
                    #endif
                    #if NUM_SIMO_SPI >1
                        case SPI_B:
                        __SPI= SPI2_IRQn;
            
                        break;
                    #endif
                   
                        default:
                        __SPI= SPI1_IRQn; // por default, evita errores
                        break;
                }

                if(ena){
                    HAL_NVIC_SetPriority(__SPI, 0, 0);
                    HAL_NVIC_EnableIRQ(__SPI);
                }
                else{
                    HAL_NVIC_DisableIRQ(__SPI);
                }
        }

        #if SIMO_SPI_TX_IRQ == 1
            
            uint32_t simo_spi_set_tx_callback(SIMO_SPI spi,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (spi)
                    {
                        #if NUM_SIMO_SPI >0
                            case SPI_A:
                            __SPI1_TX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_SPI >1
                            case SPI_B:
                            __SPI2_TX_IRQ__ = callback;
                            break;
                        #endif
                     
                            default:
                            res= 0;
                            break;
                    }

            }
                return res;
            }

            void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi){

            #if NUM_SIMO_SPI >0
                if(hspi == &hspi1){
                //funcion callback SPI1
                if(__SPI1_TX_IRQ__ != NULL) __SPI1_TX_IRQ__();
                }
                
            #endif
            #if NUM_SIMO_SPI >1
                if(hspi == &hspi2){
                // funcion callbacl SPI2
                if(__SPI2_TX_IRQ__ != NULL) __SPI2_TX_IRQ__();
                }
            
            #endif
           

            }

        #endif // SIMO_SPI_TX_IRQ

        
        #if SIMO_SPI_RX_IRQ == 1

            void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi){

                    #if NUM_SIMO_SPI >0
                        if(hspi == &hspi1){
                        //funcion callback SPI1
                        if(__SPI1_RX_IRQ__ != NULL) __SPI1_RX_IRQ__();
                        }
                    #endif
                    #if NUM_SIMO_SPI >1
                        if(hspi == &hspi2){
                        // funcion callbacl SPI2
                        if(__SPI2_RX_IRQ__ != NULL) __SPI2_RX_IRQ__();
                        }     
                    #endif
                  
            }
        
        
            uint32_t simo_spi_set_rx_callback(SIMO_SPI spi,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (spi)
                    {
                        #if NUM_SIMO_SPI >0
                            case SPI_A:
                            __SPI1_RX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_SPI >1
                            case SPI_B:
                            __SPI2_RX_IRQ__ = callback;
                            break;
                        #endif
                       
                            default:
                            res= 0;
                            break;
                    }
            }
                return res;
            }
        #endif // SIMO_SPI_RX_IRQ




        #if SIMO_SPI_TX_RX_IRQ == 1

            void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi){

                    #if NUM_SIMO_SPI >0
                        if(hspi == &hspi1){
                        //funcion callback SPI1
                        if(__SPI1_TX_RX_IRQ__ != NULL) __SPI1_TX_RX_IRQ__();
                        }
                    #endif
                    #if NUM_SIMO_SPI >1
                        if(hspi == &hspi2){
                        // funcion callbacl SPI2
                        if(__SPI2_TX_RX_IRQ__ != NULL) __SPI2_TX_RX_IRQ__();
                        }     
                    #endif
                  
            }
        
        
            uint32_t simo_spi_set_tx_rx_callback(SIMO_SPI spi,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (spi)
                    {
                        #if NUM_SIMO_SPI >0
                            case SPI_A:
                            __SPI1_TX_RX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_SPI >1
                            case SPI_B:
                            __SPI2_TX_RX_IRQ__ = callback;
                            break;
                        #endif
                       
                            default:
                            res= 0;
                            break;
                    }
            }
                return res;
            }
        #endif // SIMO_SPI_TX_RX_IRQ

        
        
        #endif      // SIMO_SPI_IRQ
#endif  // SIMO_SPI_ENA 















