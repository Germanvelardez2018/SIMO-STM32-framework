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



uint32_t mem_services_init(void){
    // Inicio memoria flash
    AT45DB_init( SPI_A,SIMO_GPIO_22,SIMO_SPI_PRESCALER_2);
    simo_delay_ms(1000);
    uint32_t ret = at45db_start( pg_256byte);
    AT45DB_sleep();     // entramos en sleep
    return ret;
}


void mem_services_deinit(void){
    AT45DB_deinit();
}

void mem_services_clear_all(void){
    AT45DB_erase_full();
}


fsm_devices mem_services_get_fsm(void){
    AT45DB_resumen();     // resumen
    uint8_t ret = 0;
    //read from memory
    AT45DB_read_page(&ret,1,FSM_ADDRESS,0);
    AT45DB_sleep();     // entramos en sleep
    return (fsm_devices)ret; 
}


fsm_devices mem_services_set_fsm(fsm_devices value){
    AT45DB_resumen();     // resumen
    uint8_t ret = (uint8_t)value;
    uint8_t last_value;
    //escribo en memoria flash
    AT45DB_write_page(&ret,1,FSM_ADDRESS,0);
    //Verificacion
    AT45DB_read_page(&last_value,1,FSM_ADDRESS,0);
    //last_value = mem_services_get_fsm();
    if( last_value != ret) ret =  FSM_UNDEFINED; // error, lo escrito no coincide con lo leido
    AT45DB_sleep();     // entramos en sleep

    return (fsm_devices)ret;   
    // return siempre es el valor de FSM en SRAM
}




static uint32_t __set_string(char* buffer,uint8_t len,uint8_t address){
    AT45DB_resumen();     // resumen
    //escribo en memoria flash
    uint32_t ret = AT45DB_write_page(buffer,len,address,0);
    AT45DB_sleep();     // entramos en sleep
    return ret;
}

static uint32_t __get_string(char* buffer,uint8_t len,uint8_t address){
    AT45DB_resumen();     // resumen
    //leo en memoria flash
    uint32_t ret = AT45DB_read_page(buffer,len,address,0);
    buffer[len]= 0;
    AT45DB_sleep();     // entramos en sleep
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