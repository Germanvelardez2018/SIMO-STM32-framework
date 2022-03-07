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

#ifndef __ADC_H
#define __ADC_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core.h"
    #if SIMO_ADC_ENA == 1
        
    #include "core.h"

    //!  ADC hardware esta en puerto APB2.. y tiene como CLOCK MAXIMO 12MHz

    typedef enum {
            ADC_A   //! ADC1        
           ,ADC_B   //! ADC2
    } SIMO_ADC;

    typedef enum {
        ADC_TIGGER_SOFTWARE = 0,
        ADC_TIGGER_TIMERB = 1,
    } simo_adc_tigger_modes;


    /**
     * @brief  Configuramos el hardware adc converter
     * 
     * @param adc 
     * @param channel 
     * @param tigger 
     * @param continuos 
     * @return ** uint32_t 
     */
    uint32_t simo_adc_config( SIMO_ADC adc, 
                            uint32_t channel,
                            uint32_t tigger,
                            uint32_t continuos);


    uint32_t simo_adc_set_channel(SIMO_ADC adc, uint32_t channel);

    /**
     * @brief 
     * 
     * @param adc 
     * @param ena_interruption 
     * @return ** uint32_t 
     */
    uint32_t simo_adc_start(SIMO_ADC adc,uint32_t ena_interruption);


    /**
     * @brief 
     * 
     * @param adc 
     * @param ena_interruption 
     * @return ** uint32_t 
     */
    uint32_t simo_adc_stop(SIMO_ADC adc,uint32_t ena_interruption);




    uint32_t simo_adc_get_value(SIMO_ADC adc);



    /**
     * @brief 
     * 
     * @param adc 
     * @return ** void 
     */
    void simo_adc_deinit( SIMO_ADC adc);


        #if SIMO_ADC_IRQ   == 1

          /**
           * @brief 
           * 
           * @param adc 
           * @param ena 
           * @return ** void 
           */
            void simo_adc_ena_irq(SIMO_ADC adc,uint32_t ena);
            // Configurar callback

          /**
           * @brief 
           * 
           * @param adc 
           * @param callback 
           * @return ** uint32_t 
           */
            uint32_t simo_adc_set_event_callback(SIMO_ADC adc,callback_irq callback);
        #endif

    #endif


    #ifdef __cplusplus
    }
    #endif
#endif /*__ ADC_H */

















