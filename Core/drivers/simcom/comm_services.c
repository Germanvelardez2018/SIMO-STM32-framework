#include "comm_services.h"
#include "comm.h"







uint32_t comm_services_check(void){
    uint32_t ret = comm_check();

    return ret;
}


/**
 * @brief Iniciamos los servicios de almacenamiento 
 *        en memoria flash externa. 
 * 
 * @return ** uint32_t 
 */
uint32_t comm_services_init(void){
    return 0;
}


/**
 * @brief Cerramos todos los servicios de memoria flash externa.
 * 
 * @return ** void 
 */
void comm_services_deinit(void){
}




