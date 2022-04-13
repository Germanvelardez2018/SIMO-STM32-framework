/**
 * @file sensor_fake.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */





#ifndef __ SENSOR_FAKE_H_
#define __ SENSOR_FAKE_H_


#include "core.h"




void  sensor_fake_calibration();


/**
 * @brief Inicio el hardware necesario para manejar acelerometro (I2C)
 * 
 * @return ** void 
 */
void sensor_fake_init(void);


/**
 * @brief Desactivar el hardware
 * 
 * @return ** void 
 */
void sensor_fake_deinit();



/**
 * @brief Reset la configuracion
 * 
 * @return ** void 
 */
void sensor_fake_reset();


/**
 * @brief Revisar disponibilidad del sensor
 * 
 * @return ** uint32_t 
 */
uint32_t  sensor_fake_check(void);



/**
 * @brief Poner en modo sleep el sensor
 * 
 * @param sleep 
 * @return ** void 
 */
void sensor_fake_sleep(uint32_t sleep);



/**
 * @brief 
 * 
 * @param buffer 
 * @param len 
 * @return ** uint32_t 
 */
uint8_t sensor_fake_get_measure(char* buffer, uint8_t len);


#endif