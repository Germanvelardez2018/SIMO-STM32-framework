


#ifndef __FSM__H
#define __FSM__H

#include "core.h"
//! Comienzan en posicion 48 a 2047









/**
 * @brief SIEMPRE INICIAMOS EN MODO SIN_CONFIGURACION,
 *  LOS DEMAS MODOS SE ACCEDEN DESDE LA MEMORIA FLASH
 * 
 * @return ** void 
 */
uint32_t fsm_init();


/**
 * @brief Cambio el estado de la memoria flash 
 *        donde se almacena el estado. 
 * Luego de esto se debe reiniciar el micro para que se carge el nuevo estado en memoria ram
 * 
 * @param new_state 
 * @return ** void 
 */
void fsm_set_state(fsm_devices new_state);

/**
 * @brief 
 * 
 * @return ** fsm_devices 
 */
fsm_devices fsm_get_state(void);



#endif