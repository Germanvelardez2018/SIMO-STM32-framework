/**
 * @file timer.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para manejar el hardware timer 
 * @version 0.1
 * @date 2022-01-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "core.h"
    #if SIMO_TIMER_ENA == 1
        //! Unidades utilizada para configurar los periodos del timer. 
        typedef enum {
            TIME_US = 100000,
            TIME_MS = 1000,
        }TIMER_UNIT;



        /**
         * @brief  Configura el timer para generar eventos de desborde en intervalos definidos de tiempo
         * 
         * @param timer  timer a utilizar: TIMER_A, TIMER_B o TIMER_C. Todos son de 16 bits. Depende de NUM_SIMO_TIMER
         * @param unit   unidades del periodo seleccionado. MS(milisegundos) o US (microseg)
         * @param time   valor del periodo entre eventos
         * @return ** simo_state 
         */
        simo_state simo_timer_config(SIMO_TIMER timer,TIMER_UNIT unit,uint16_t time);


        /**
        * @brief Desconfigura el timer, liberando recursos asociados
        * 
        * @param timer timer a utilizar: TIMER_A, TIMER_B o TIMER_C. Todos son de 16 bits. Depende de NUM_SIMO_TIMER

        * @return ** void 
         */
        void simo_timer_deconfig(SIMO_TIMER timer);

        /**
         * @brief Activa el timer y la interrupcion asociada. Si no se configura  la interrupcion el evento  no llama  a la funcion callback
         * 
         * @param timer  timer a activar: TIMER_A, TIMER_B o TIMER_C. Todos son de 16 bits. Depende de NUM_SIMO_TIMER
         * @return ** simo_state 
         */
        simo_state simo_timer_start(SIMO_TIMER timer);
        
        
      /**
         * @brief Desactiva el timer y la interrupcion asociada.
         * 
         * @param timer  timer a desactivar: TIMER_A, TIMER_B o TIMER_C. Todos son de 16 bits. Depende de NUM_SIMO_TIMER
         * @return ** simo_state 
         */
        simo_state simo_timer_stop(SIMO_TIMER timer);



        /**
         * @brief Retorna el valor actual del timer
         * @param timer  timer a desactivar: TIMER_A, TIMER_B o TIMER_C. Todos son de 16 bits. Depende de NUM_SIMO_TIMER
         * @return ** uint32_t 
         */
        uint16_t simo_timer_get_conter(SIMO_TIMER timer);


        #if SIMO_TIMER_IRQ   == 1

            /**
             * @brief  Habilita la interrupcion del timer
             * 
             * @param timer timer a desactivar: TIMER_A, TIMER_B o TIMER_C. Todos son de 16 bits. Depende de NUM_SIMO_TIMER
             * @param ena  1 para habilitar 0 para deshabilitar
             */
            void simo_timer_ena_irq(SIMO_TIMER timer,uint32_t ena);
            // Configurar callback


            /**
             * @brief 
             * 
             * @param timer timer a desactivar: TIMER_A, TIMER_B o TIMER_C. Todos son de 16 bits. Depende de NUM_SIMO_TIMER
             * @param callback  Funcion a llamar despues del evento de desborde del timer. Funcion sin parametros y retorna void
             * @return ** simo_state 
             */
            simo_state simo_timer_set_event_callback(SIMO_TIMER timer,callback_irq callback);
        #endif

    #endif


    #ifdef __cplusplus
    }
    #endif
#endif /*__ TIMER_H */

