/**
 * @file comm_services.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-04-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef __COMM_SERVICES_H__
#define __COMM_SERVICES_H__

#include "core.h"




/**
 * @brief Iniciamos los servicios de almacenamiento 
 *        en memoria flash externa. 
 * 
 * @return ** uint32_t 
 */
uint32_t comm_services_init(void);


/**
 * @brief Cerramos todos los servicios de memoria flash externa.
 * 
 * @return ** void 
 */
void comm_services_deinit(void);



uint32_t comm_services_check(void);





uint32_t comm_services_gps_init(uint32_t gps_on);


uint32_t comm_services_get_nmea(char* p_buffer);

uint32_t comm_services_open_apn();



















 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_set_mqtt_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_get_mqtt_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_set_id_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_get_id_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_set_pass_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_get_pass_origen(char* buffer,uint8_t len);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_set_pub_topics(char* buffer,uint8_t len,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_get_pub_topics(char* buffer,uint8_t len,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_set_sub_topics(char* buffer,uint8_t len,uint8_t topic_pos);

 /**
  * @brief 
  * 
  * @param buffer 
  * @param len 
  * @return ** uint32_t 
  */
 uint32_t comm_services_get_sub_topics(char* buffer,uint8_t len,uint8_t topic_pos);




 uint32_t comm_services_write_data(char* buffer, uint8_t len, uint16_t pag);



  uint32_t comm_services_read_data(char* buffer, uint8_t len, uint16_t pag);



 uint32_t comm_services_read_data(char* buffer, uint8_t len, uint16_t pag);


#endif