/**
 * @file modos.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "config.h"





#define FMS_STATE_MEMORY_ADDRESS        10


typedef enum {
  WITHOUT_CONFIG          //! Sin configuracion
, ON_FIELD             //! Transmicion desde campo
, MEMORY_DOWNLOAD      //! Transmicion desde memoria

} fsm_devices;

static fsm_devices __FSM_DEVICE_ ;




/**
 * @brief SIEMPRE INICIAMOS EN MODO SIN_CONFIGURACION,
 *  LOS DEMAS MODOS SE ACCEDEN DESDE LA MEMORIA FLASH
 * 
 * @return ** void 
 */
void fsm_init();


/**
 * @brief Cambio el estado de la memoria flash 
 *        donde se almacena el estado. 
 * Luego de esto se debe reiniciar el micro para que se carge el nuevo estado en memoria ram
 * 
 * @param new_state 
 * @return ** void 
 */
int32_t fsm_set_state(fsm_devices new_state);





/**
 * @brief Leo el estado del dispositvo desde la memoria flash y lo almaceno en ram.
 *        Esta rutina se llama al princio del programa.
 * 
 * @return ** int32_t 
 */
int32_t fsm_charge_state();