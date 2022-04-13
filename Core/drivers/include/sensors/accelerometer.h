
#ifndef __ACCELEROMETER_H_
#define __ACCELEROMETER_H_


#include "core.h"




/**
 * @brief Inicio el hardware necesario para manejar acelerometro (I2C)
 * 
 * @return ** void 
 */
void accelerometer_init(void);


/**
 * @brief Desactivar el hardware
 * 
 * @return ** void 
 */
void accelerometer_deinit();



/**
 * @brief Reset la configuracion
 * 
 * @return ** void 
 */
void accelerometer_reset();


/**
 * @brief Revisar disponibilidad del sensor
 * 
 * @return ** uint32_t 
 */
uint32_t  accelerometer_check(void);



/**
 * @brief Poner en modo sleep el sensor
 * 
 * @param sleep 
 * @return ** void 
 */
void accelerometer_sleep(uint32_t sleep);

/**
 * @brief  frecuencia interna del sensor( posiblemente deberia ser static e invisible para UF)
 * 
 * @param freq_div 
 * @return ** void 
 */
void accelerometer_set_sample_div(uint8_t freq_div);



/**
 * @brief Obtener la medicion del sensor
 * 
 * @param x 
 * @param y 
 * @param z 
 * @return ** uint32_t 
 */
uint32_t accelerometer_get_aceleration(int16_t* x, int16_t* y , int16_t* z);



/**
 * @brief Calibrar el sensor
 * 
 * @return ** void 
 */
void accelerometer_calibration();


/**
 * @brief  Setear un offset de la medicion del sensor
 * 
 * @param x_offset 
 * @param y_offset 
 * @param z_offset 
 * @return ** uint32_t 
 */
uint32_t accelerometer_set_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset);


/**
 * @brief Obtener el offset de la medicion del sensor
 * 
 * @param x_offset 
 * @param y_offset 
 * @param z_offset 
 * @return ** uint32_t 
 */
uint32_t accelerometer_get_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset);



/**
 * @brief 
 * 
 * @param buffer 
 * @param len 
 * @return ** uint32_t 
 */
uint8_t accelerometer_get_measure(char* buffer, uint8_t len);


#endif