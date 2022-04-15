#include "fsm.h"
#include "mem_services.h"







// Estado de la maquina en memoria SRAM, 
// se sincroniza con estado guardado en memoria externas
static fsm_devices __FSM_DEVICE_ ;




/**
 * @brief SIEMPRE INICIAMOS EN MODO SIN_CONFIGURACION,
 *  LOS DEMAS MODOS SE ACCEDEN DESDE LA MEMORIA FLASH
 * 
 * @return ** void 
 */
uint32_t fsm_init(){
    //INICIO FSM EN SRAM
 __FSM_DEVICE_ = FSM_WITHOUT_CONFIG;
 //uint32_t ret = mem_services_init();
 return 1;
}



fsm_devices fsm_get_state(void){
    
    return __FSM_DEVICE_;  // Devolvemos estado en sram, sincronizado con estado en memoria externa
}

/**
 * @brief Cambio el estado de la memoria flash 
 *        donde se almacena el estado. 
 * Luego de esto se debe reiniciar el micro para que se carge el nuevo estado en memoria ram
 * 
 * @param new_state 
 * @return ** void 
 */
void fsm_set_state(fsm_devices new_state){

    //Cargo el nuevo valor de estado  en flash externa y sincronizo con sram
    __FSM_DEVICE_ = mem_services_set_fsm(new_state);
    
}


void fsm_load_flash(){
    __FSM_DEVICE_ = mem_services_get_fsm();
}