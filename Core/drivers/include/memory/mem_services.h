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
 uint32_t mem_services_set_mqtt_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_mqtt_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_id_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_id_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_pass_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_pass_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_pub_topics(char* buffer,uint8_t len,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_pub_topics(char* buffer,uint8_t len,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_set_sub_topics(char* buffer,uint8_t len,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t mem_services_get_sub_topics(char* buffer,uint8_t len,uint8_t topic_pos);




 uint32_t mem_services_write_data(char* buffer, uint8_t len, uint16_t pag);



  uint32_t mem_services_read_data(char* buffer, uint8_t len, uint16_t pag);


#endif