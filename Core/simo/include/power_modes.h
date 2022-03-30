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




#ifndef __SIMO_POWER_MODES_H
#define __SIMO_POWER_MODES_H

#include "core.h"




/**
 * @note Hal systick debe ser 
 * deshabilitado o nos despertada del mode sleep o stop
 * 
 * @note podemos usar WFI(wait for Interruption) o WFE (wait for Event)
 * . En este modulo siempre se usara WFI  
 * 
 * 
 */



/**
 * @brief 
 * 
 * 
 * @param mode 
 * @return ** void 
 */
void power_mode_set( pwr_modes mode);




/**
 * @brief Devuelve el modo de consumo actual.
 * 
 * @return ** pwr_modes 
 */
pwr_modes power_mode_get_state(void);

#endif