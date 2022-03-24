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

#include "core.h"
#include "AT45DB.h"



/**
 * @brief NUNCA USAR FUNCIONES AT45DB fuera de este modulo
 * 
 */







#define MODULO_FLASH                     "AT45DB041E"
#define MEMORY_SIZE                      "4MB"
#define N_PAGES                           AT45DB041E_PAGES_DEFAULT //! AT45DB041E 2048




#define FSM_ADDRESS                     (1)
#define COUNTER                         (2)

 
 #define MQTT_ORIGEN                    (5)
 #define MQTT_OPT_1                     (6)    
 #define MQTT_OPT_2                     (7)
 #define MQTT_OPT_3                     (8)
 #define MQTT_ORIGEN_ID                 (9)
 #define MQTT_ORIGEN_PASS               (10)
 #define MQTT_OPT1_ID                   (11)
 #define MQTT_OPT1_PASS                 (12)
 #define MQTT_OPT2_ID                   (13)
 #define MQTT_OPT2_PASS                 (14)
 #define MQTT_OPT3_ID                   (15)
 #define MQTT_OPT3_PASS                 (16)

 #define TOPICS_1                       (20)
 #define TOPICS_2                       (21)
 #define TOPICS_3                       (22)
 #define TOPICS_4                       (23)
 #define TOPICS_5                       (24)


/**
 * @brief Defino mapa de memoria de la aplicacion
 *    
 *    REGISTROS ESPECIALES
 *    PAG_0                     RESERVADO ...
 *    PAG_5                     MQTT_ORIGEN
 *    PAG_6                     MQTT_OPT_1
 *    PAG_7                     MQTT_OPT_2
 *    PAG_8                     MQTT_OPT_3
 *    PAG_9                     MQTT_ORIGEN_ID
 *    PAG_10                    MQTT_ORIGEN_PASS
 *    PAG_15                    TOPICS_1
 *    PAG_16                    TOPICS_2
 *    PAG_17                    TOPICS_3
 *    PAG_18                    TOPICS_4
 *    PAG_19                    TOPICS_5
 *    PAG_47
 * 
 */

#define OFFSET_ESP_REG                  48
#define DATA_PAGES_256                  2000



/**
 * @brief Iniciamos los servicios de almacenamiento 
 *        en memoria flash externa. 
 * 
 * @return ** uint32_t 
 */
uint32_t mem_services_init(void);




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







 uint32_t mem_services_set_mqtt_origen(char* buffer,uint8_t len);
 uint32_t mem_services_get_mqtt_origen(char* buffer,uint8_t len);






 uint32_t mem_services_set_id_origen(char* buffer,uint8_t len);
 uint32_t mem_services_get_id_origen(char* buffer,uint8_t len);




 uint32_t mem_services_set_pass_origen(char* buffer,uint8_t len);
 uint32_t mem_services_get_pass_origen(char* buffer,uint8_t len);






