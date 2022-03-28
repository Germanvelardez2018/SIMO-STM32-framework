
#ifndef __SENSOR_SERVICES_H__
#define __SENSOR_SERVICES_H__

#include "core.h"












/**
 * @brief Iniciamos los servicios de almacenamiento 
 *        en memoria flash externa. 
 * 
 * @return ** uint32_t 
 */
uint32_t sensor_services_init(void);

/**
 * @brief Cerramos todos los servicios de memoria flash externa.
 * 
 * @return ** void 
 */
void sensor_services_deinit(void);


uint32_t sensor_services_check(char* buffer, uint8_t len);



/**
 * @brief 
 * 
 * @return ** uint32_t 
 */
uint32_t  sensor_services_get(void);













#endif