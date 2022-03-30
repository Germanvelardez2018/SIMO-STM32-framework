/**
 * @file clock_config.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para configuracion del clock del sistema
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
   * @brief Iniciamos la HAL de bajo nivel del sistema
   * 
   * @return ** void 
   */
   void simo_clock_init(void);


    /**
     * @brief Configura el rtc con el crista LSE de 32khz
     * 
     * @return ** uint32_t 
     */
    uint32_t simo_clock_rtc(void);




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



  /**
   * @brief Obtengo el valor del clock source del BUS APB1
   * 
   * @return ** uint32_t 
   */

  uint32_t simo_clock_get_APB1();


  /**
   * @brief Obtengo el valor del clock source del BUS APB2
   * 
   * @return ** uint32_t 
   */
  uint32_t simo_clock_get_APB2();


#endif