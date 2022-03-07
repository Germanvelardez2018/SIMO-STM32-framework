/**
 * @file adc.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "adc.h"
#include "main.h"




#if SIMO_ADC_ENA  == 1
    #if NUM_SIMO_ADC >0
        ADC_HandleTypeDef hadc1;
        #if SIMO_ADC_IRQ   == 1
            static  callback_irq __ADC1_COMPLETE_CONVER_IRQ__ ;
            void ADC1_2_IRQHandler(void){
                 HAL_ADC_IRQHandler(&hadc1);
            }
        #endif
    #endif

    #if NUM_SIMO_ADC >1
        ADC_HandleTypeDef hadc2;
        #if SIMO_ADC_IRQ   == 1
            static  callback_irq __ADC2_COMPLETE_CONVER_IRQ__ ;   
         
         
         //   void ADC1_2_IRQHandler(void){
         //     HAL_ADC_IRQHandler(&hadc2);
         //  }
        #endif
    #endif
  
    #if SIMO_TIMER_IRQ   == 1

        void simo_adc_ena_irq(SIMO_ADC adc,uint32_t ena){
                IRQn_Type __adc= 0;
                switch (adc){
                    #if NUM_SIMO_ADC >0
                            case ADC_A:
                            __adc= ADC1_2_IRQn;
                            break;
                    #endif
                    
                    #if NUM_SIMO_ADC >1
                            case ADC_B:
                            __adc= ADC1_2_IRQn;
                            break;

                    #endif
                            default:
                            __adc= ADC1_2_IRQn; // por default, evita errores
                            break;
                    }
                    if(ena){
                        HAL_NVIC_SetPriority(__adc, 0, 0);
                        HAL_NVIC_EnableIRQ(__adc);
                    }
                    else{
                        HAL_NVIC_DisableIRQ(__adc);
                    }
        }


        void HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc){

        }
       
            //CALLBACK ADC COMPLETE
            void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc){
            #if NUM_SIMO_UART >0
                if(hadc->Instance == ADC1){
                //funcion callback ADC
                if(__ADC1_COMPLETE_CONVER_IRQ__ != NULL) __ADC1_COMPLETE_CONVER_IRQ__();
                }
            #endif
            #if NUM_SIMO_ADC >1
                if(hadc->Instance == ADC2){
                // funcion callback ADC
                if(__ADC2_COMPLETE_CONVER_IRQ__ != NULL) __ADC2_COMPLETE_CONVER_IRQ__();
                }
            
            #endif
            

            }

            //setea el callback

            uint32_t simo_adc_set_event_callback(SIMO_ADC adc,callback_irq callback)
            {
              uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (adc)
                    {
                        #if NUM_SIMO_ADC >0
                            case ADC_A:
                            __ADC1_COMPLETE_CONVER_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_ADC >1
                            case ADC_B:
                            __ADC2_COMPLETE_CONVER_IRQ__ = callback;
                            break;
                        #endif
                            default:
                            __ADC1_COMPLETE_CONVER_IRQ__ = callback;
                            res= 0;
                            break;
                    }
            }
                return res;
            }


    /**
     * @brief Obtiene la instancia de TIM
     * 
     * @param timer_enum 
     * @return ** TIM_HandleTypeDef* 
     */
    static ADC_HandleTypeDef* __get_adc(SIMO_ADC adc_enum)
    {
        ADC_HandleTypeDef* adc = NULL;
        switch (adc_enum)
        {
            #if NUM_SIMO_ADC >0
                case ADC_A:
                adc = &hadc1;
                adc->Instance = ADC1;
                break;
            #endif
            #if NUM_SIMO_ADC >1
                case ADC_B:
                adc = &hadc2;
                adc->Instance = ADC2;
                break;
            #endif
            
                default:
                adc = &hadc1;
                adc->Instance = ADC1;
                break;
        }
        return adc;
    }


  uint32_t __get_channel(uint32_t channel){
    uint32_t __channel = 0;
    switch (channel)
    {


      case  0:
      __channel = ADC_CHANNEL_0 ;
          break;                      
      case  1:
      __channel = ADC_CHANNEL_1 ;

        break;      
      case  2:
      __channel = ADC_CHANNEL_2 ;

        break;
      case  3:
      __channel = ADC_CHANNEL_3 ;

        break;
      case  4:
      __channel = ADC_CHANNEL_4 ;

        break;
      case  5:
      __channel = ADC_CHANNEL_5 ;

        break;
      case  6:
      __channel = ADC_CHANNEL_6 ;

        break;
      case  7:
      __channel = ADC_CHANNEL_7 ;

        break;
      case  8:
      __channel = ADC_CHANNEL_8 ;

        break;
      case  9:
      __channel = ADC_CHANNEL_9 ;

        break;
      case  10:
      __channel = ADC_CHANNEL_10;

        break;
    default:
      __channel = ADC_CHANNEL_0;
      break;
    }
    return __channel;
  }











    uint32_t simo_adc_( SIMO_ADC adc, 
                        uint32_t channel,
                        uint32_t tigger,
                        uint32_t continuos){

      uint32_t ret = 1;
      //ADC_ChannelConfTypeDef sConfig = {0};
      ADC_HandleTypeDef hadc2;
      hadc2.Instance = ADC2;
      hadc2.Init.ScanConvMode = ADC_SCAN_DISABLE;
      hadc2.Init.ContinuousConvMode = DISABLE;
      hadc2.Init.DiscontinuousConvMode = DISABLE;
      hadc2.Init.ExternalTrigConv = (tigger == ADC_TIGGER_SOFTWARE)?ADC_SOFTWARE_START : ADC_EXTERNALTRIGINJECCONV_T2_TRGO;
      hadc2.Init.DataAlign = ADC_DATAALIGN_RIGHT;
      hadc2.Init.NbrOfConversion = 1;
      if (HAL_ADC_Init(&hadc2) != HAL_OK)
      {
      ret = 0;
      }

      return ret;
    }









uint32_t simo_adc_start(SIMO_ADC adc,uint32_t ena_interruption){

   uint32_t ret = 1;
   ADC_HandleTypeDef* __adc = __get_adc(adc);
    if(__adc != NULL) {  
            if (ena_interruption == 1){
                 if(HAL_ADC_Start_IT(__adc) == HAL_OK){
                ret = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_ADC_Start(__adc) == HAL_OK){
                ret = 1; // EXITO EN LA CONFIGURACION
                }
            }
  return ret;
    }
}


uint32_t simo_adc_config_channel(SIMO_ADC adc, uint32_t channel ){
    uint32_t ret= 1;
      ADC_HandleTypeDef* __adc = __get_adc(adc);


      ADC_ChannelConfTypeDef sConfig = {0};

      sConfig.Rank = ADC_REGULAR_RANK_1;
      sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
   
      sConfig.Channel = __get_channel(channel);
         if(HAL_ADC_ConfigChannel(__adc,&sConfig ) == HAL_OK){
                ret = 0; // EXITO EN LA CONFIGURACION
                }
      return ;

}


uint32_t simo_adc_stop(SIMO_ADC adc,uint32_t ena_interruption){

   uint32_t ret = 1;
   ADC_HandleTypeDef* __adc = __get_adc(adc);
    if(__adc != NULL) {  
            if (ena_interruption == 1){
                 if(HAL_ADC_Stop_IT(__adc) == HAL_OK){
                ret = 1; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_ADC_Stop(__adc) == HAL_OK){
                ret = 1; // EXITO EN LA CONFIGURACION
                }
            }
  return ret;
    }
}



uint32_t simo_adc_get_value(SIMO_ADC adc){
  ADC_HandleTypeDef* __adc = __get_adc(adc);
  return  HAL_ADC_GetValue(__adc);

}


void simo_adc_deinit( SIMO_ADC adc){
  ADC_HandleTypeDef* __adc = __get_adc(adc);
   HAL_ADC_DeInit(__adc);


}

  





/**
* @brief ADC MSP Initialization
* This function configures the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  #if NUM_SIMO_ADC >0
  if(hadc->Instance==ADC1)
  {
 
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    PA4     ------> ADC1_IN4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
  #endif
  #if NUM_SIMO_ADC >1
  if(hadc->Instance==ADC2)
  {
 
    __HAL_RCC_ADC2_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC2 GPIO Configuration
    PA5     ------> ADC2_IN5
    PA6     ------> ADC2_IN6
    PA7     ------> ADC2_IN7
    PB0     ------> ADC2_IN8
    PB1     ------> ADC2_IN9
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  #endif
  }

}

/**
* @brief ADC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hadc: ADC handle pointer
* @retval None
*/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc)
{
  #if NUM_SIMO_ADC >0
  if(hadc->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();

    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PA3     ------> ADC1_IN3
    PA4     ------> ADC1_IN4
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
  
  #endif
  #if NUM_SIMO_ADC >1
  if(hadc->Instance==ADC2)
  {
  /* USER CODE BEGIN ADC2_MspDeInit 0 */

  /* USER CODE END ADC2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC2_CLK_DISABLE();

    /**ADC2 GPIO Configuration
    PA5     ------> ADC2_IN5
    PA6     ------> ADC2_IN6
    PA7     ------> ADC2_IN7
    PB0     ------> ADC2_IN8
    PB1     ------> ADC2_IN9
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_0|GPIO_PIN_1);

  }
  #endif

}


    #endif   // simo IRQ ADC ENABLED



#endif // fin de SIMO_ADC_ENA














