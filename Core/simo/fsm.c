
#include "memory_store.h" // Necesario para almacenar los datos en memoria flash externa
#include "power_save.h"   //Necesario para almacenar datos en backup register del RTC
#include "fsm.h"





void fsm_init(){

    //ponemos en modo  SIN_CONFIGURACION a 
    __FSM_DEVICE_ = WITHOUT_CONFIG;

}



int32_t fsm_set_state(fsm_devices new_state){

    int32_t ret = 0;


    return ret;


}






int32_t fsm_charge_state(){
    int32_t ret= 0;
    
    return ret;
}