/**
 * @file mem_services.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Servicios de almacenamiento en memoria flash (arrays de bytes)
 *   para aplicaciones simples
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#ifndef __MEM_SERVICES_H__
#define __MEM_SERVICES_H__

#include "core.h"




/**
 * @brief Iniciamos los servicios de almacenamiento 
 *        en memoria flash externa. 
 * 
 * @return ** uint32_t 
 */
uint32_t mem_services_init(void);


/**
 * @brief Cerramos todos los servicios de memoria flash externa.
 * 
 * @return ** void 
 */
void mem_services_deinit(void);


/**
 * @brief Borrar todos los datos almacenados en memoria flash externa
 * 
 * @return ** void 
 */
void mem_services_clear_all(void);




/**
 * @brief Cantidad de muestras que se almacenan antes de enviarse por MQTT
 * 
 * @return ** uint8_t 
 */
uint8_t mem_services_get_data_counter();

/**
 * @brief  Cantidad de muestras que se almacenan antes de enviarse por MQTT
 * 
 * @param data_counter 
 * @return ** uint8_t 
 */
uint8_t mem_services_set_data_counter(uint8_t data_counter);



/**
 * @brief  retorna el valor actual de la 
 * FSM directo desde memoria flash (address FSM_ADDRESS )
 * 
 * @return ** fsm_devices 
 */
fsm_devices mem_services_get_fsm(void);


/**
 * @brief Escribe en memoria el estado de la FSM. 
 * Retorna el valor escrito y leido en la memoria FSM_ADDRESS
 * 
 * @param value 
 * @return ** fsm_devices 
 */
fsm_devices mem_services_set_fsm(fsm_devices value);


 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_mqtt_origen(char* buffer);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_mqtt_origen(char* buffer);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_mqtt_id_origen(char* buffer);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_mqtt_id_origen(char* buffer);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_mqtt_pass_origen(char* buffer);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_mqtt_pass_origen(char* buffer);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_mqtt_pub_topics(char* buffer,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_mqtt_pub_topics(char* buffer,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_mqtt_sub_topics(char* buffer,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_mqtt_sub_topics(char* buffer,uint8_t topic_pos);

 uint32_t mem_services_set_mqtt_qos_origen(char* buffer);
 uint32_t mem_services_get_mqtt_qos_origen(char* buffer);


 uint32_t mem_services_write_data(char* buffer, uint8_t len, uint16_t pag);



  uint32_t mem_services_read_data(char* buffer, uint8_t len, uint16_t pag);



 uint32_t mem_services_read_data(char* buffer, uint8_t len, uint16_t pag);


#endif