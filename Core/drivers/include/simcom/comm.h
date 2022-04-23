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






uint8_t* comm_get_buffer();


uint32_t comm_get_signal();


uint32_t comm_set_echo(uint8_t echo_on);





uint32_t comm_set_pwr_gps(uint32_t gps_on);

uint32_t comm_get_gps_info();

uint32_t comm_get_operator(void);



uint32_t comm_get_apn(void);


uint32_t comm_open_apn(void);


uint32_t comm_config_mqtt(uint8_t* url, uint8_t* user, uint8_t* password, uint8_t* qos);


uint32_t comm_mqtt_publish(char* topic, char* payload, uint8_t len_payload);


#endif