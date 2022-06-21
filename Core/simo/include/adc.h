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
            CHANNEL_0,
            CHANNEL_1,
            CHANNEL_2,
            CHANNEL_3,
            CHANNEL_4,
        #if NUM_SIMO_ADC_CHANNEL > 5  
            CHANNEL_5,
            CHANNEL_6,
            CHANNEL_7,
            CHANNEL_8,
            CHANNEL_9,
        #endif

    }   SIMO_ADC_CHANNEL;



    typedef enum {
            ADC_A   //! ADC1        
           ,ADC_B   //! ADC2
    } SIMO_ADC;

    typedef enum {
        ADC_TIGGER_SOFTWARE  ,
        #if ADC_TRIGGER_EXT == 1    //Algun dia lo implementare.
        ADC_TRIGGER_EXTERN   ,
        #endif
        #if ADC_TRIGGER_TIMER == 1  // Algun dia lo implementare
        ADC_TRIGGER_TIMMER,
        #endif
    } simo_adc_trigger;






    simo_state  simo_adc_init(SIMO_ADC adc, SIMO_ADC_CHANNEL channel, simo_adc_trigger trigger);





    simo_state simo_adc_start(SIMO_ADC adc,uint32_t ena_interruption);


    /**
     * @brief 
     * 
     * @param adc 
     * @param ena_interruption 
     * @return ** simo_state 
     */
    simo_state simo_adc_stop(SIMO_ADC adc,uint32_t ena_interruption);




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
            simo_state simo_adc_set_event_callback(SIMO_ADC adc,callback_irq callback);
        #endif

    #endif


    #ifdef __cplusplus
    }
    #endif
#endif /*__ ADC_H */

















