/**
 * @file comm.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __COMM_H_
#define __COMM_H_


#include "core.h"




/**
 * @brief Inicio el hardware necesario para manejar acelerometro (I2C)
 * 
 * @return ** void 
 */
uint32_t comm_init(void);


/**
 * @brief Desactivar el hardware
 * 
 * @return ** void 
 */
void comm_deinit();



/**
 * @brief Reset la configuracion
 * 
 * @return ** void 
 */
void comm_reset();


/**
 * @brief Revisar disponibilidad del sensor
 * 
 * @return ** uint32_t 
 */
uint32_t  comm_check(void);



/**
 * @brief Poner en modo sleep el sensor
 * 
 * @param sleep 
 * @return ** void 
 */
void comm_sleep();


/**
 * @brief 
 * 
 * @return ** void 
 */
void comm_resume();


#endif