/**
 * @file clock_config.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */







#ifndef __SIMO_CLOK_CONFIG_H
#define __SIMO_CLOK_CONFIG_H



    #include "core.h"


    /**
     * @brief  Configura el clock para que todo el sistema funcione.
     * 
     * @return ** void 
     */
    void simo_clock_config(void );


    /**
     * @brief Retorna el valor del clock base, utilizado por el bus ABP
     * 
     * @return ** uint32_t 
     */

    uint32_t simo_clock_get_base(void);


    /**
     * @brief Retorna el valor del clock base del funcionamiento de los timer. Por defecto es 40Mhz
     * 
     * @return ** uint32_t 
     */
    uint32_t simo_clock_get_timer_base(void);




  uint32_t simo_clock_get_APB1();



  uint32_t simo_clock_get_APB2();


#endif