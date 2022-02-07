/**
 * @file i2c.c
 * @author German Velardez (germanvelardez@gmail.com)
 * @brief  Implementacion del driver para el manejo del hardware I2C
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "core.h"
#include "i2c.h"
#include "main.h"




#if SIMO_I2C_ENA == 1

    

    #if NUM_SIMO_I2C >0
        I2C_HandleTypeDef hi2c1;
        #if SIMO_UART_IRQ   == 1


            //MASTER
            static  callback_irq __I2C1_MASTER_TX_IRQ__ ;
            static  callback_irq __I2C1_MASTER_RX_IRQ__ ;


            //SLAVE
            static  callback_irq __I2C1_SLAVE_TX_IRQ__ ;
            static  callback_irq __I2C1_SLAVE_RX_IRQ__ ;

    


      

            /**
             * @brief This function handles I2C1 error interrupt.
             */
            void I2C1_ER_IRQHandler(void)
            {
                HAL_I2C_ER_IRQHandler(&hi2c1);
            }
            /**
             * @brief This function handles I2C2 event interrupt.
             */
            void I2C1_EV_IRQHandler(void)
            {
                HAL_I2C_EV_IRQHandler(&hi2c1);
            }
        #endif
    #endif
    #if NUM_SIMO_I2C >1
        I2C_HandleTypeDef hi2c2;
        #if SIMO_UART_IRQ   == 1


            //MASTER
            static  callback_irq __I2C2_MASTER_TX_IRQ__ ;
            static  callback_irq __I2C2_MASTER_RX_IRQ__ ;
            //SLAVE
            static  callback_irq __I2C2_SLAVE_TX_IRQ__ ;
            static  callback_irq __I2C2_SLAVE_RX_IRQ__ ;

           

            /**
             * @brief This function handles I2C1 error interrupt.
             */

            
            void I2C2_ER_IRQHandler(void)
            {
                HAL_I2C_ER_IRQHandler(&hi2c2);
            }
            /**
             * @brief This function handles I2C2 event interrupt.
             */
            void I2C2_EV_IRQHandler(void)
            {
                HAL_I2C_EV_IRQHandler(&hi2c2);
            }            
        #endif
    #endif
   


/**
 * @brief Obtiene la instancia de UART necesaria
 * 
 * @param uart_enum instancia UART simo : UART_A, UART_B o UART_C
 * @return ** I2C_HandleTypeDef* 
 */

static I2C_HandleTypeDef* __get_i2c(SIMO_I2C uart_enum)
{
    I2C_HandleTypeDef* uart = NULL;
    switch (uart_enum)
    {
        #if NUM_SIMO_I2C >0
            case I2C_A:
            uart = &hi2c1;
            uart->Instance = I2C1;
            break;
        #endif
        #if NUM_SIMO_I2C >1
            case I2C_B:
            uart = &hi2c2;
            uart->Instance = I2C2;
            break;
        #endif
     
            default:
            break;
    }
    return uart;
}







uint32_t simo_i2c_slave_write(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t timeout, uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto
        I2C_HandleTypeDef* simo_i2c = __get_i2c(i2c);
        if(simo_i2c != NULL) {  
            if (ena_callback == 1){
                 if(HAL_I2C_Slave_Transmit_IT(simo_i2c,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_I2C_Slave_Transmit_IT(simo_i2c,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
    }
    return res;
}



uint32_t simo_i2c_master_write(SIMO_I2C i2c,uint16_t address,uint8_t* data,uint32_t len, uint32_t timeout, uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto
        I2C_HandleTypeDef* simo_i2c = __get_i2c(i2c);
        if(simo_i2c != NULL) {  
            if (ena_callback == 1){
                 if(HAL_I2C_Master_Transmit_IT(simo_i2c,address,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_I2C_Master_Transmit(simo_i2c,address,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
    }
    return res;
}

uint32_t simo_i2c_slave_read(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto
        I2C_HandleTypeDef* simo_i2c = __get_i2c(i2c);
        if(simo_i2c != NULL) {  
            if (ena_callback == 1){
                 if(HAL_I2C_Slave_Receive_IT(simo_i2c,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_I2C_Slave_Receive(simo_i2c,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }           
    }
    return res;          
}



uint32_t simo_i2c_master_read(SIMO_I2C i2c,uint8_t* data,uint32_t len, uint32_t timeout,uint32_t ena_callback ){
    uint32_t res = 0;  // retorna error por defecto
        I2C_HandleTypeDef* simo_i2c = __get_i2c(i2c);
        if(simo_i2c != NULL) {  
            if (ena_callback == 1){
                 if(HAL_I2C_Receive_IT(simo_i2c,data,len) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_I2C_Receive(simo_i2c,data,len,timeout) == HAL_OK){
                res = 1; // EXITO EN LA CONFIGURACION
                }
            }           
    }
    return res;          
}


uint32_t simo_i2c_init(SIMO_I2C i2c,uint32_t clock_speed,uint32_t address_7bits, uint32_t master_mode){


    uint32_t ret = 1;


    

    I2C_HandleTypeDef* simo_i2c = __get_i2c(i2c);
    simo_i2c->Init.ClockSpeed = clock_speed;
    simo_i2c->Init.DutyCycle = I2C_DUTYCYCLE_2;
    simo_i2c->Init.OwnAddress1 = 0;
    simo_i2c->Init.AddressingMode = (address_7bits != 0)?I2C_ADDRESSINGMODE_7BIT: I2C_ADDRESSINGMODE_10BIT;
    simo_i2c->Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    simo_i2c->Init.OwnAddress2 = 0;
    simo_i2c->Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    simo_i2c->Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(simo_i2c) != HAL_OK)
  {
    ret = 0;  // Error al iniciar el periferico
  }
  
    
    return ret;
}




void simo_i2c_deinit(SIMO_I2C i2c){
    }




/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspInit 0 */

  /* USER CODE END I2C1_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_8|GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    __HAL_AFIO_REMAP_I2C1_ENABLE();

    /* Peripheral clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
    /* I2C1 interrupt Init */
    HAL_NVIC_SetPriority(I2C1_EV_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_EV_IRQn);
    HAL_NVIC_SetPriority(I2C1_ER_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(I2C1_ER_IRQn);
  /* USER CODE BEGIN I2C1_MspInit 1 */

  /* USER CODE END I2C1_MspInit 1 */
  }
  else if(hi2c->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspInit 0 */

  /* USER CODE END I2C2_MspInit 0 */

    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**I2C2 GPIO Configuration
    PB10     ------> I2C2_SCL
    PB11     ------> I2C2_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_11;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C2_CLK_ENABLE();
  
  }

}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C1)
  {
  /* USER CODE BEGIN I2C1_MspDeInit 0 */

  /* USER CODE END I2C1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C1_CLK_DISABLE();

    /**I2C1 GPIO Configuration
    PB8     ------> I2C1_SCL
    PB9     ------> I2C1_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

  }
  else if(hi2c->Instance==I2C2)
  {
  /* USER CODE BEGIN I2C2_MspDeInit 0 */

  /* USER CODE END I2C2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C2_CLK_DISABLE();

    /**I2C2 GPIO Configuration
    PB10     ------> I2C2_SCL
    PB11     ------> I2C2_SDA
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_10);

    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_11);

  }



}
    #if SIMO_I2C_IRQ   == 1

    #if SIMO_I2C_MASTER_IRQ == 1
    //--------------------
        void HAL_I2C_MasterTxCpltCallback(I2C_HandleTypeDef *hi2c){

            #if NUM_SIMO_UART >0
                if(hi2c == &hi2c1){
                //funcion callback I2C1
                if(__I2C1_MASTER_TX_IRQ__ != NULL) __I2C1_MASTER_TX_IRQ__();
                }    
            #endif
            #if NUM_SIMO_UART >1
                if(hi2c == &hi2c2){
                // funcion callbacl I2C2
                if(__I2C2_MASTER_TX_IRQ__ != NULL) __I2C2_MASTER_TX_IRQ__();
                }
            #endif
           

        }
        void HAL_I2C_MasterRxCpltCallback(I2C_HandleTypeDef *hi2c){

             #if NUM_SIMO_UART >0
                if(hi2c == &hi2c1){
                //funcion callback I2C1
                if(__I2C1_MASTER_RX_IRQ__ != NULL) __I2C1_MASTER_RX_IRQ__();
                }    
            #endif
            #if NUM_SIMO_UART >1
                if(hi2c == &hi2c2){
                // funcion callbacl I2C2
                if(__I2C2_MASTER_RX_IRQ__ != NULL) __I2C2_MASTER_RX_IRQ__();
                }
            #endif

        }
    #endif

    #if SIMO_I2C_SLAVE_IRQ == 1

        void HAL_I2C_SlaveTxCpltCallback(I2C_HandleTypeDef *hi2c){

             #if NUM_SIMO_UART >0
                if(hi2c == &hi2c1){
                //funcion callback I2C1
                if(__I2C1_SLAVE_TX_IRQ__ != NULL) __I2C1_SLAVE_TX_IRQ__();
                }    
            #endif
            #if NUM_SIMO_UART >1
                if(hi2c == &hi2c2){
                // funcion callbacl I2C2
                if(__I2C2_SLAVE_TX_IRQ__ != NULL) __I2C2_SLAVE_TX_IRQ__();
                }
            #endif

        }
        void HAL_I2C_SlaveRxCpltCallback(I2C_HandleTypeDef *hi2c){

             #if NUM_SIMO_UART >0
                if(hi2c == &hi2c1){
                //funcion callback I2C1
                if(__I2C1_SLAVE_RX_IRQ__ != NULL) __I2C1_SLAVE_RX_IRQ__();
                }    
            #endif
            #if NUM_SIMO_UART >1
                if(hi2c == &hi2c2){
                // funcion callbacl I2C2
                if(__I2C2_SLAVE_RX_IRQ__ != NULL) __I2C2_SLAVE_RX_IRQ__();
                }
            #endif

        }
    #endif 


        void HAL_I2C_ErrorCallback(I2C_HandleTypeDef *hi2c){

        }


    //----------------------
        void simo_i2c_ena_irq(SIMO_I2C i2c,uint32_t ena_ev_event,uint32_t ena_er_event){
                IRQn_Type __i2c_ev_event= 0;
                IRQn_Type __i2c_er_event= 0;
                
                switch (i2c){
                    #if NUM_SIMO_I2C >0
                        case I2C_A:
                        __i2c_ev_event= (ena_ev_event)? I2C1_EV_IRQn : 0;
                        __i2c_er_event= (ena_er_event)? I2C1_ER_IRQn : 0;
                        break;
                    #endif
                    #if NUM_SIMO_I2C >1
                        case I2C_B:
                        __i2c_ev_event= (ena_ev_event)? I2C2_EV_IRQn : 0;
                        __i2c_er_event= (ena_er_event)? I2C2_ER_IRQn : 0;
                        break;
                    #endif
                        default:
                        // Por default   0, 0
                        break;
                }
                if(ena_ev_event){
                    //Activo interrupciones
                    HAL_NVIC_SetPriority(__i2c_ev_event, 0, 0);
                    HAL_NVIC_EnableIRQ(__i2c_ev_event);
                }
                else{
                    //Desactivo interrupciones
                    HAL_NVIC_DisableIRQ(__i2c_ev_event);
                }
                if(ena_er_event){
                    //Activo interrupciones
                    HAL_NVIC_SetPriority(__i2c_er_event, 0, 0);
                    HAL_NVIC_EnableIRQ(__i2c_er_event);
                }
                else{
                    //Desactivo interrupciones
                    HAL_NVIC_DisableIRQ(__i2c_er_event);
                }
        }



        #if SIMO_UART_TX_IRQ == 1        
            uint32_t simo_uart_set_master_tx_callback(SIMO_I2C i2c,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (i2c)
                    {
                        #if NUM_SIMO_I2C >0
                            case I2C_A:
                            __I2C1_MASTER_TX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_I2C >1
                            case I2C_B:
                            __I2C2_MASTER_TX_IRQ__ = callback;
                            break;
                        #endif
                       
                            default:
                            res= 0;
                            break;
                    }
            }
                return res;
            }


            uint32_t simo_uart_set_slave_tx_callback(SIMO_I2C i2c,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (i2c)
                    {
                        #if NUM_SIMO_I2C >0
                            case I2C_A:
                            __I2C1_SLAVE_TX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_I2C >1
                            case I2C_B:
                            __I2C2_SLAVE_TX_IRQ__ = callback;
                            break;
                        #endif
                       
                            default:
                            res= 0;
                            break;
                    }
            }
                return res;
            }


        #endif // SIMO_UART_TX_IRQ

        
        #if SIMO_UART_RX_IRQ == 1
           
        
            uint32_t simo_uart_set_master_rx_callback(SIMO_I2C i2c,callback_irq callback)
            {
                uint32_t res = 0;
                if(callback != NULL){
                    res = 1;
                    switch (i2c)
                    {
                        #if NUM_SIMO_I2C >0
                            case I2C_A:
                            __I2C1_MASTER_RX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_I2C >1
                            case I2C_B:
                            __I2C2_MASTER_RX_IRQ__ = callback;
                            break;
                        #endif
                            default:
                            res= 0;
                            break;
                    }
            }
                return res;
            }



            uint32_t simo_uart_set_slave_rx_callback(SIMO_I2C i2c,callback_irq callback)
            {
                uint32_t res = 0;
                if(callback != NULL){
                    res = 1;
                    switch (i2c)
                    {
                        #if NUM_SIMO_I2C >0
                            case I2C_A:
                            __I2C1_SLAVE_RX_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_I2C >1
                            case I2C_B:
                            __I2C2_SLAVE_RX_IRQ__ = callback;
                            break;
                        #endif
                            default:
                            res= 0;
                            break;
                    }
            }
                return res;
            }







        #endif       // SIMO_UART_RX_IRQ

        #endif      // SIMO_UART_IRQ
#endif  // SIMO_UART_ENA 















