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

#define NUM_SIMO_ADC_CHANNEL     2

#if SIMO_ADC_ENA  == 1
      
      static uint16_t __ADC1_PIN__  = 0;
      
      static uint16_t __ADC2_PIN__  = 0;

      static uint8_t __FLAG_ADC_PORTB__ = 0; // ADC2 usar port A  flag = 0 , usar portb flag = 1
      // ADC2 podria usar GPIOB



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
         
         
         
        #endif
    #endif
  
    #if SIMO_ADC_IRQ   == 1

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

            simo_state simo_adc_set_event_callback(SIMO_ADC adc,callback_irq callback)
            {
              simo_state ret = SIMO_ERROR;
            if (callback != NULL){
                    ret = SIMO_OK;
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
                            break;
                    }
            }
                return ret;
            }


/**
 * @brief Obtengo la instancia de hardware adc
 * 
 * @param adc 
 * @return ** ADC_HandleTypeDef* 
 */
 static ADC_HandleTypeDef* __get_adc(SIMO_ADC adc){
  ADC_HandleTypeDef* ret = NULL;


    switch (adc)
    {
    case ADC_A:
      /* code */
      hadc1.Instance = ADC1;
      ret = &hadc1;
      break;
    
    case ADC_B:
      hadc2.Instance = ADC2;
      ret = &hadc2;
      break;
    
    default:
      // hadc1 por defect
      hadc1.Instance = ADC1;
      ret= &hadc1;
      break;
    }

    return ret;

 }

/**
 * @brief Obtengo el canal del adc a utilizar
 * 
 * @param channel 
 * @return ** uint32_t 
 */
static uint32_t __get_channel( SIMO_ADC_CHANNEL channel){

  uint32_t ret = 0;

  switch (channel)
  {
    case CHANNEL_0:
      ret = ADC_CHANNEL_0 ;
    
      __ADC1_PIN__ = GPIO_PIN_0;
      break;
    
    case CHANNEL_1:
      ret = ADC_CHANNEL_1 ;
      __ADC1_PIN__ = GPIO_PIN_1;
      break;
    
    case CHANNEL_2:
      ret = ADC_CHANNEL_2 ;
      __ADC1_PIN__ = GPIO_PIN_2;
      break;
    
    case CHANNEL_3:
      ret = ADC_CHANNEL_3 ;
      __ADC1_PIN__ = GPIO_PIN_3;
      break;

    case CHANNEL_4:
      ret = ADC_CHANNEL_4 ;
      __ADC1_PIN__ = GPIO_PIN_4;
      break;

    #if NUM_SIMO_ADC_CHANNEL > 5  
    
      case CHANNEL_5:
        ret = ADC_CHANNEL_5 ;
        break;
      
      case CHANNEL_6:
        ret = ADC_CHANNEL_6 ;
        break;
      
      case CHANNEL_7:
        ret = ADC_CHANNEL_7 ;
        break;

      
      case CHANNEL_8:
        ret = ADC_CHANNEL_8 ;
        break;
      
      case CHANNEL_9:
        ret = ADC_CHANNEL_9 ;
        break;
    #endif
  
  default:
   ret = ADC_CHANNEL_0;
    break;
  }


  return ret;

}




uint32_t __get_trigger(simo_adc_trigger trigger){
  uint32_t ret = 0;
  switch (trigger)
  {
    case ADC_TIGGER_SOFTWARE:
    /* code */
      ret = ADC_SOFTWARE_START;
    break;

    #if ADC_TRIGGER_EXT == 1    //Falta implementar esta opcion de trigger.
    case 0 ADC_TRIGGER_EXTERN:
        ret = ADC_SOFTWARE_START;   
    #endif

    #if ADC_TRIGGER_TIMER == 1  // Falta implementar esta opcion de trigger
    case 0 ADC_TRIGGER_TIMMER:
        ret = ADC_SOFTWARE_START;
    #endif
  
  default:
      ret = ADC_SOFTWARE_START;
    break;
  }
  return ret;
}


 simo_state    simo_adc_init(SIMO_ADC adc, SIMO_ADC_CHANNEL channel, simo_adc_trigger trigger){

        simo_state ret = SIMO_OK;

        ADC_HandleTypeDef* ADC = __get_adc(adc);
        ADC->Init.ScanConvMode = ADC_SCAN_DISABLE;
        ADC->Init.ContinuousConvMode = DISABLE;
        ADC->Init.DiscontinuousConvMode = DISABLE;
        ADC->Init.ExternalTrigConv = __get_trigger(trigger);
        ADC->Init.DataAlign = ADC_DATAALIGN_RIGHT;
        ADC->Init.NbrOfConversion = 1;
        if (HAL_ADC_Init(ADC) != HAL_OK)
        {
       //   Error_Handler();
          ret = SIMO_ERROR;
        }
        
        
        
        ADC_ChannelConfTypeDef sConfig = {0};
        
        sConfig.Channel = __get_channel(channel);
        sConfig.Rank = ADC_REGULAR_RANK_1;
        sConfig.SamplingTime = ADC_SAMPLETIME_239CYCLES_5; // Para usos de ADC lentos.
        // DEberia implementarse teniendo en cuenta el main clock, el clock de ADC y
        // el tiempo minimo necesario para la conversion
        if (HAL_ADC_ConfigChannel(ADC, &sConfig) != HAL_OK)
        {
         // Error_Handler();
          ret = SIMO_ERROR;
        }


        return ret;

    }


simo_state simo_adc_start(SIMO_ADC adc,uint32_t ena_interruption){

   simo_state ret = SIMO_ERROR;
   ADC_HandleTypeDef* __adc = __get_adc(adc);
    if(__adc != NULL) {  
            if (ena_interruption == 1){
                 if(HAL_ADC_Start_IT(__adc) == HAL_OK){
                ret = SIMO_OK; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_ADC_Start(__adc) == HAL_OK){
                ret = SIMO_OK; // EXITO EN LA CONFIGURACION
                }
            }
  return ret;
    }
}




simo_state simo_adc_stop(SIMO_ADC adc,uint32_t ena_interruption){

   simo_state ret = SIMO_ERROR;
   ADC_HandleTypeDef* __adc = __get_adc(adc);
    if(__adc != NULL) {  
            if (ena_interruption == 1){
                 if(HAL_ADC_Stop_IT(__adc) == HAL_OK){
                ret = SIMO_OK; // EXITO EN LA CONFIGURACION
                }
            }
            else{
                 if(HAL_ADC_Stop(__adc) == HAL_OK){
                ret = SIMO_OK; // EXITO EN LA CONFIGURACION
                }
            }
  return ret;
    }
}



uint32_t simo_adc_get_value(SIMO_ADC adc){
  ADC_HandleTypeDef* __adc = __get_adc(adc);
  uint32_t ret =  HAL_ADC_GetValue(__adc);
  return ret;
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

  #if NUM_SIMO_ADC_CHANNEL >0
  if(1)

  {
 
    __HAL_RCC_ADC1_CLK_ENABLE();

    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA0-WKUP     ------> ADC1_IN0
    PA1          ------> ADC1_IN1
    PA2          ------> ADC1_IN2
    PA3          ------> ADC1_IN3
    PA4          ------> ADC1_IN4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3 |GPIO_PIN_4;
    //GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

    //GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }
  #endif
  #if NUM_SIMO_ADC_CHANNEL >1
  if(hadc->Instance==ADC2)
  {
 
    __HAL_RCC_ADC2_CLK_ENABLE();


    if( __FLAG_ADC_PORTB__ ){
      __HAL_RCC_GPIOB_CLK_ENABLE() ;

    } else{
       __HAL_RCC_GPIOA_CLK_ENABLE();
    }


  //  GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
   // GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
   // HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    //GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
    //GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    //HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = __ADC2_PIN__;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;

    if(__FLAG_ADC_PORTB__){
      HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    }
   else{
      HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
  }






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














