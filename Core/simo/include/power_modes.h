/**
 * @file power_modes.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-25
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "core.h"




/**
 * @note Hal systick debe ser 
 * deshabilitado o nos despertada del mode sleep o stop
 * 
 * @note podemos usar WFI(wait for Interruption) o WFE (wait for Event)
 * . En este modulo siempre se usara WFI  
 * 
 * @note soporta  despertar el micro con RTC y PIN WAKE UP(PA0)
 * 
 */



/**
 * @brief 
 * 
 * 
 * @param mode 
 * @return ** void 
 */


/**
 * @brief Funcion de callback. Se acciona al despertar el micro
 * 
 * @param callback 
 * @return ** void 
 */
void power_mode_set_callback(callback_irq callback);



void power_mode_get_callback(void);


void power_mode_set( pwr_modes mode);


void power_mode_get_callback(void );


pwr_modes power_mode_get_state(void);
