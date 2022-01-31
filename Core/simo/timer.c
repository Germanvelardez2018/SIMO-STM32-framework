/**
 * @file timer.c
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Implementacion del driver para el manejo de timers por hardware
 * @version 0.1
 * @date 2022-01-07
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "timer.h"
#include "clock_config.h"  
#include "main.h"



#if SIMO_TIMER_ENA  == 1
   // Estructuras

    #if NUM_SIMO_TIMER >0
        TIM_HandleTypeDef htim1;
        #if SIMO_TIMER_IRQ   == 1
            static  callback_irq __TIMER1_EVENT_IRQ__ ;
            void TIM1_UP_IRQHandler(void){
                  HAL_TIM_IRQHandler(&htim1);
            }
        #endif
    #endif
    #if NUM_SIMO_TIMER >1
        TIM_HandleTypeDef htim2;
        #if SIMO_TIMER_IRQ   == 1
            static  callback_irq __TIMER2_EVENT_IRQ__ ;   
            void TIM2_IRQHandler(void){
                HAL_TIM_IRQHandler(&htim2);
           }
        #endif
    #endif
    #if NUM_SIMO_TIMER >2
        TIM_HandleTypeDef htim3;
        #if SIMO_TIMER_IRQ   == 1
            static  callback_irq __TIMER3_EVENT_IRQ__ ;
            void TIM3_IRQHandler(void){
                HAL_TIM_IRQHandler(&htim3);
            }
        #endif
    #endif

    #if SIMO_TIMER_IRQ   == 1

        void simo_timer_ena_irq(SIMO_TIMER timer,uint32_t ena){
                IRQn_Type __timer= 0;
                switch (timer){
                    #if NUM_SIMO_TIMER >0
                            case TIMER_A:
                            __timer= TIM1_UP_IRQn;
                            break;
                    #endif
                    
                    #if NUM_SIMO_TIMER >1
                            case TIMER_B:
                            __timer= TIM2_IRQn;
                            break;

                    #endif
                        
                    #if NUM_SIMO_TIMER >2
                            case TIMER_C:            
                            __timer= TIM3_IRQn;
                            break;
                    #endif
                            default:
                            __timer= TIM1_UP_IRQn; // por default, evita errores
                            break;
                    }
                    if(ena){
                        HAL_NVIC_SetPriority(__timer, 0, 0);
                        HAL_NVIC_EnableIRQ(__timer);
                    }
                    else{
                        HAL_NVIC_DisableIRQ(__timer);
                    }
        }


       
            //CALLBACK TX UART
            void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
            #if NUM_SIMO_UART >0
                if(htim->Instance == TIM1){
                //funcion callback UART1
                if(__TIMER1_EVENT_IRQ__ != NULL) __TIMER1_EVENT_IRQ__();
                }
            #endif
            #if NUM_SIMO_TIMER >1
                if(htim->Instance == TIM2){
                // funcion callbacl TIMER2
                if(__TIMER2_EVENT_IRQ__ != NULL) __TIMER2_EVENT_IRQ__();
                }
            
            #endif
            #if NUM_SIMO_TIMER >2
                if(htim->Instance == TIM3){
                // Funcion callback TIMER3
                if(__TIMER3_EVENT_IRQ__ != NULL) __TIMER3_EVENT_IRQ__();
                }
            #endif

            }

            //setea el callback

            uint32_t simo_timer_set_event_callback(SIMO_TIMER timer,callback_irq callback)
            {
                uint32_t res = 0;
            if (callback != NULL){
                    res = 1;
                    switch (timer)
                    {
                        #if NUM_SIMO_TIMER >0
                            case TIMER_A:
                            __TIMER1_EVENT_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_TIMER >1
                            case TIMER_B:
                            __TIMER2_EVENT_IRQ__ = callback;
                            break;
                        #endif
                        #if NUM_SIMO_TIMER >2
                            case TIMER_C:
                            __TIMER3_EVENT_IRQ__ = callback;
                            break;
                        #endif
                            default:
                            __TIMER1_EVENT_IRQ__ = callback;
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
    static TIM_HandleTypeDef* __get_timer(SIMO_TIMER timer_enum)
    {
        TIM_HandleTypeDef* timer = NULL;
        switch (timer_enum)
        {
            #if NUM_SIMO_TIMER >0
                case TIMER_A:
                timer = &htim1;
                timer->Instance = TIM1;
                break;
            #endif
            #if NUM_SIMO_TIMER >1
                case TIMER_B:
                timer = &htim2;
                timer->Instance = TIM2;
                break;
            #endif
            #if NUM_SIMO_TIMER >2
                case TIMER_C:
                timer = &htim3;
                timer->Instance = TIM3;
                break;
            #endif
                default:
                break;
        }
        return timer;
    }





    uint32_t simo_timer_config(SIMO_TIMER timer,TIMER_UNIT unit,uint16_t time){
    uint32_t clock_base = simo_clock_get_base(); // Default 40 MHz
    uint32_t res = 0;
    //CLOCK_TIMER == 40M
    TIM_HandleTypeDef* tim = __get_timer(timer);
    // si unit es uS   => unit = 100 , si unit es mS => unit = 1
    tim->Init.Prescaler = (uint32_t)(clock_base / unit);
    tim->Init.CounterMode = TIM_COUNTERMODE_UP;
    tim->Init.Period = (1* time) ;
    tim->Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; // MAX DIV 4
    tim->Init.RepetitionCounter = 0;
    tim->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    if (HAL_TIM_Base_Init(tim) == HAL_OK){
        res = 1;
    }
    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};   
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    if (HAL_TIM_ConfigClockSource(tim, &sClockSourceConfig) != HAL_OK){
        res= 0;
    }
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    if (HAL_TIMEx_MasterConfigSynchronization(tim, &sMasterConfig) != HAL_OK){
        res = 0;
    }
       return res;
    }






    uint32_t simo_timer_start(SIMO_TIMER timer){
        uint32_t res = 0;
        TIM_HandleTypeDef* tim = __get_timer(timer);
        if(HAL_TIM_Base_Start_IT(tim) == HAL_OK){
            res = 1; // EXITO EN LA CONFIGURACION
        }
        return  res;
    }



    uint32_t simo_timer_stop(SIMO_TIMER timer){
          uint32_t res = 0;
        TIM_HandleTypeDef* tim = __get_timer(timer);
        if(HAL_TIM_Base_Stop_IT(tim) == HAL_OK){
            res = 1; // EXITO EN LA CONFIGURACION
        }
        return  res;
    }
    uint16_t simo_timer_get_conter(SIMO_TIMER timer){
        //Falta implementacion
        return 0;
    }



    /**
    * @brief TIM_Base MSP Initialization
    * This function configures the hardware resources used in this example
    * @param htim_base: TIM_Base handle pointer
    * @retval None
    */
    void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* htim_base)
    {

    #if NUM_SIMO_TIMER >0
        if(htim_base->Instance==TIM1){
           __HAL_RCC_TIM1_CLK_ENABLE();
        }
    #endif
        
    #if NUM_SIMO_TIMER >1
        if(htim_base->Instance==TIM2){
            __HAL_RCC_TIM2_CLK_ENABLE();
        }
    #endif

    #if NUM_SIMO_TIMER >2
        if ((htim_base->Instance==TIM3)){
            __HAL_RCC_TIM3_CLK_ENABLE();
        }
    #endif
    }

            


    /**
    * @brief TIM_Base MSP De-Initialization
    * This function freeze the hardware resources used in this example
    * @param htim_base: TIM_Base handle pointer
    * @retval None
    */
    void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* htim_base)
    {

    #if NUM_SIMO_TIMER >0
        if(htim_base->Instance==TIM1){
        __HAL_RCC_TIM1_CLK_DISABLE();
        }
     #endif

     #if NUM_SIMO_TIMER >1
        if(htim_base->Instance==TIM2){
        __HAL_RCC_TIM2_CLK_DISABLE();
        }
     #endif

     #if NUM_SIMO_TIMER >2
        if ((htim_base->Instance==TIM3)){
        __HAL_RCC_TIM3_CLK_DISABLE();
         }
     #endif

    }









    #endif   // simo IRQ TIMER ENABLED



#endif // fin de SIMO_TIMER_ENA








