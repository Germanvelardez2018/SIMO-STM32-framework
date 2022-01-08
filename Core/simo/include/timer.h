
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core.h"
    #if SIMO_TIMER_ENA == 1

        typedef enum {
            TIME_US = 1,
            TIME_MS = 100,
            
        
        }TIMER_UNIT;


        uint32_t simo_timer_config(SIMO_TIMER timer,TIMER_UNIT unit,uint32_t time);
        uint32_t simo_timer_start(SIMO_TIMER timer);
        uint32_t simo_timer_stop();
        uint32_t simo_timer_get_conter();


        #if SIMO_TIMER_IRQ   == 1

            //Activo o desactivo las interrupciones
            void simo_timer_ena_irq(SIMO_TIMER timer,uint32_t ena);
            // Configurar callback
            uint32_t simo_timer_set_event_callback(SIMO_TIMER timer,timer_irq callback);
        #endif

    #endif


    #ifdef __cplusplus
    }
    #endif
#endif /*__ TIMER_H */

