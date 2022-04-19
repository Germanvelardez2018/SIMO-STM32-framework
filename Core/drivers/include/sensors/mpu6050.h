/**
 * @file mpu6050.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef __MPU6050_H_
#define __MPU6050_H_


#include "core.h"




/**
 * @brief Inicio el hardware necesario para manejar acelerometro (I2C)
 * 
 * @return ** void 
 */
uint32_t  ACCEL_init(void);


/**
 * @brief Desactivar el hardware
 * 
 * @return ** void 
 */
void ACCEL_deinit();



/**
 * @brief Reset la configuracion
 * 
 * @return ** void 
 */
void ACCEL_reset();


/**
 * @brief Revisar disponibilidad del sensor
 * 
 * @return ** uint32_t 
 */
uint32_t  ACCEL_check(void);



/**
 * @brief Poner en modo sleep el sensor
 * 
 * @return ** void 
 */
void ACCEL_sleep(void);


/**
 * @brief 
 * 
 * @return ** void 
 */
void ACCEL_resume(void);




/**
 * @brief Obtener la medicion del sensor
 * 
 * @param x 
 * @param y 
 * @param z 
 * @return ** uint32_t 
 */
uint32_t ACCEL_get_aceleration(int16_t* x, int16_t* y , int16_t* z);



/**
 * @brief Calibrar el sensor
 * 
 * @return ** void 
 */
void ACCEL_calibration();




uint32_t ACCEL_get_measure(char* buffer, uint8_t len);



#endif