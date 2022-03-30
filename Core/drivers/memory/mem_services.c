/**
 * @file mem_services.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "mem_services.h"

#include "memory.h" //!



/**
 * @brief NUNCA USAR FUNCIONES de memory.h fuera de este modulo 
 * 
 */







#define MODULO_FLASH                     "AT45DB041E"
#define MEMORY_SIZE                      "4Megabits"
#define N_PAGES                           AT45DB041E_PAGES_DEFAULT //! AT45DB041E 2048




#define FSM_ADDRESS                     (1)
#define COUNTER                         (2)

 
 #define MQTT_ORIGEN                    (5)
 #define MQTT_OPT_1                     (6)    
 #define MQTT_OPT_2                     (7)
 #define MQTT_OPT_3                     (8)

 #define MQTT_ORIGEN_ID                 (9)
 #define MQTT_OPT1_ID                   (10)
 #define MQTT_OPT2_ID                   (11)
 #define MQTT_OPT3_ID                   (12)


 #define MQTT_ORIGEN_PASS               (13)
 #define MQTT_OPT1_PASS                 (14)
 #define MQTT_OPT2_PASS                 (15)
 #define MQTT_OPT3_PASS                 (16)



//! pub 
 #define PUB_TOPICS_0                   (20)
 #define PUB_TOPICS_1                   (21)
 #define PUB_TOPICS_2                   (22)
 #define PUB_TOPICS_3                   (23)
 #define PUB_TOPICS_4                   (24)

 //! sub
 #define SUB_TOPICS_0                   (25)
 #define SUB_TOPICS_1                   (26)
 #define SUB_TOPICS_2                   (27)
 #define SUB_TOPICS_3                   (28)
 #define SUB_TOPICS_4                   (29)
#define  TOPICS_MAX                     (5)

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
#define CS_PIN                          SIMO_GPIO_25 //! PB8


uint32_t mem_services_init(void){
    // Inicio memoria flash
    mem_init( SPI_A,CS_PIN,SIMO_SPI_PRESCALER_2);
    simo_delay_ms(1000);
    uint32_t ret =mem_start( pg_256byte);
    mem_sleep();     // entramos en sleep
    return ret;
}


void mem_services_deinit(void){
   mem_deinit();
}

void mem_services_clear_all(void){
   mem_erase_full();
}


fsm_devices mem_services_get_fsm(void){
    mem_resumen();     // resumen
    uint8_t ret = 0;
    //read from memory
    mem_read_page(&ret,1,FSM_ADDRESS,0);
    mem_sleep();     // entramos en sleep
    return (fsm_devices)ret; 
}


fsm_devices mem_services_set_fsm(fsm_devices value){
    mem_resumen();     // resumen
    uint8_t ret = (uint8_t)value;
    uint8_t last_value;
    //escribo en memoria flash
    mem_write_page(&ret,1,FSM_ADDRESS,0);
    //Verificacion
    mem_read_page(&last_value,1,FSM_ADDRESS,0);
    //last_value = mem_services_get_fsm();
    if( last_value != ret) ret =  FSM_UNDEFINED; // error, lo escrito no coincide con lo leido
    mem_sleep();     // entramos en sleep

    return (fsm_devices)ret;   
    // return siempre es el valor de FSM en SRAM
}




static uint32_t __set_string(char* buffer,uint8_t len,uint8_t address){
    mem_resumen();     // resumen
    //escribo en memoria flash
    uint32_t ret = mem_write_page(buffer,len,address,0);
    mem_sleep();     // entramos en sleep
    return ret;
}

static uint32_t __get_string(char* buffer,uint8_t len,uint8_t address){
    mem_resumen();     // resumen
    //leo en memoria flash
    uint32_t ret = mem_read_page(buffer,len,address,0);
    buffer[len]= 0;
    mem_sleep();     // entramos en sleep
    return ret;
}






 uint32_t mem_services_set_mqtt_origen(char* buffer,uint8_t len){
     return __set_string(buffer,len,MQTT_ORIGEN);
}


 uint32_t mem_services_get_mqtt_origen(char* buffer,uint8_t len){
    return __get_string(buffer,len,MQTT_ORIGEN);
}


 uint32_t mem_services_set_id_origen(char* buffer,uint8_t len){
    return __set_string(buffer,len,MQTT_ORIGEN_ID);
}


 uint32_t mem_services_get_id_origen(char* buffer,uint8_t len){
    return __get_string(buffer,len,MQTT_ORIGEN_ID);
}


 uint32_t mem_services_set_pass_origen(char* buffer,uint8_t len){
    return __set_string(buffer,len,MQTT_ORIGEN_PASS);
}


 uint32_t mem_services_get_pass_origen(char* buffer,uint8_t len){
    return __get_string(buffer,len,MQTT_ORIGEN_PASS);
}





 uint32_t mem_services_set_pub_topics(char* buffer,uint8_t len,uint8_t topic_pos){
     if(topic_pos >= TOPICS_MAX) return 0;
     return __set_string(buffer,len,(PUB_TOPICS_0 + topic_pos));
}


 uint32_t mem_services_get_pub_topics(char* buffer,uint8_t len,uint8_t topic_pos){
    if(topic_pos >= TOPICS_MAX) return 0;
    return __get_string(buffer,len,(PUB_TOPICS_0 + topic_pos));
}





 uint32_t mem_services_set_sub_topics(char* buffer,uint8_t len,uint8_t topic_pos){
     if(topic_pos >= TOPICS_MAX) return 0;
     return __set_string(buffer,len,(SUB_TOPICS_0 + topic_pos));
}


 uint32_t mem_services_get_sub_topics(char* buffer,uint8_t len,uint8_t topic_pos){
    if(topic_pos >= TOPICS_MAX) return 0;
    return __get_string(buffer,len,(SUB_TOPICS_0 + topic_pos));
}