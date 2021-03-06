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
#include "debug.h"


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


#define  COUNTER_DATA_MAX                (30)
#define  MQTT_QOS_ORIGIN                  (31)      

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
#define CS_PIN                          SIMO_GPIO_24 //! PB8

#define MEM_SERVICES_INIT               "MEM SERVICES READY"







/**
 * @brief Almacenamos datos en memoria
 * 
 * @param buffer 
 * @param len 
 * @param pag 
 * @param pos 
 * @return ** uint32_t 
 */
static uint32_t __write_data(char* buffer, uint8_t len, uint16_t pag, uint8_t pos){
    mem_resumen();     // resumen
    //escribo en memoria flash
    uint32_t ret = mem_write_page(buffer,len,pag + OFFSET_ESP_REG,pos);
    mem_sleep();     // entramos en sleep
    return ret;
}

/**
 * @brief Leemos datos desde memoria
 * 
 * @param buffer 
 * @param len 
 * @param pag 
 * @param pos 
 * @return ** uint32_t 
 */
static uint32_t __read_data(char* buffer, uint8_t len, uint16_t pag,uint8_t pos){

    mem_resumen();     // resumen
    //escribo en memoria flash
    uint32_t ret = mem_read_page(buffer,len,pag + OFFSET_ESP_REG,pos);
    mem_sleep();     // entramos en sleep
    return ret;




  
}




static uint32_t __set_string(char* buffer,uint8_t len , uint8_t address){
    //mem_resumen();     // resumen
    //escribo en memoria flash
    debug_print("writing string in memory:\r\n");
    //uint32_t ret = mem_write_page(buffer,len,address,0);
    //mem_sleep();     // entramos en sleep


    mem_resumen();     // resumen
    //escribo en memoria flash
    debug_print("writing string in memory:\r\n");

    uint32_t ret = 0;
    uint8_t __len=len;
    // guardo el tama??o del buffer en primera posicion
    ret = __write_data(&__len,1,address,0);

    ret= __write_data(buffer,len,address,1);
    mem_sleep();     // entramos en sleep
    return ret;









    return ret;
}

static uint32_t __get_string(char* buffer,uint8_t len,uint8_t address){
   // mem_resumen();     // resumen
    //leo en memoria flash
   // uint32_t ret = mem_read_page(buffer,100,address,0);
   // buffer[len]= 0;
   // mem_sleep();     // entramos en sleep
   // return ret;



    mem_resumen();     // resumen
    //escribo en memoria flash
    uint32_t ret = 0;
    uint8_t __len = 0;
    debug_print( "reading string in memory\r\n");

    ret = __read_data(&__len,1,address,0);
    //ret = (1 )? __read_data(buffer,__len+1,pag,1): 0;  // si el tamanio de datos a leer es mayou que el espacio en buffer, no leo y retorno ret=0
    ret = ( __len  >= len )? __read_data(buffer,__len,address,1): 0;  // si el tamanio de datos a leer es mayou que el espacio en buffer, no leo y retorno ret=0
    debug_print("mem service read:\r\n");
    debug_print(buffer);
    mem_sleep();     // entramos en sleep
    return ret;
}




uint32_t mem_services_init(void){
    // Inicio memoria flash
    mem_init( SPI_A,CS_PIN,SIMO_SPI_PRESCALER_2);
    mem_resumen();     // resumen
    uint32_t ret =mem_start( pg_256byte);
    mem_sleep();     // entramos en sleep

    if( ret == 1) debug_print(MEM_SERVICES_INIT);
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




uint8_t mem_services_get_data_counter(){

    mem_resumen();     // resumen
    uint8_t ret = 0;
    //read from memory
    mem_read_page(&ret,1,COUNTER_DATA_MAX,0);
    mem_sleep();     // entramos en sleep
    return ret; 

} 

uint8_t mem_services_set_data_counter(uint8_t data_counter){

     mem_resumen();     // resumen
    uint8_t value = data_counter;
    uint8_t ret = 0;
    //read from memory
    ret = mem_write_page(&value,1,COUNTER_DATA_MAX,0);
    mem_sleep();     // entramos en sleep
    return ret; 

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




 uint32_t mem_services_set_mqtt_qos_origen(char* buffer){
     if( buffer == NULL)return 0;
     return __set_string(buffer,strlen(buffer),MQTT_QOS_ORIGIN);
}


 uint32_t mem_services_get_mqtt_qos_origen(char* buffer){
     if( buffer == NULL)return 0;
    return __get_string(buffer,strlen(buffer),MQTT_QOS_ORIGIN);
}




 uint32_t mem_services_set_mqtt_origen(char* buffer){
     if( buffer == NULL)return 0;
     return __set_string(buffer,strlen(buffer),MQTT_ORIGEN);
}


 uint32_t mem_services_get_mqtt_origen(char* buffer){
     if( buffer == NULL)return 0;
    return __get_string(buffer,strlen(buffer),MQTT_ORIGEN);
}


 uint32_t mem_services_set_mqtt_id_origen(char* buffer){
     if( buffer == NULL)return 0;
    return __set_string(buffer,strlen(buffer),MQTT_ORIGEN_ID);
}


 uint32_t mem_services_get_mqtt_id_origen(char* buffer){
     if( buffer == NULL)return 0;
    return __get_string(buffer,strlen(buffer),MQTT_ORIGEN_ID);
}


 uint32_t mem_services_set_mqtt_pass_origen(char* buffer){
     if( buffer == NULL)return 0;
    return __set_string(buffer,strlen(buffer),MQTT_ORIGEN_PASS);
}


 uint32_t mem_services_get_mqtt_pass_origen(char* buffer){
     if( buffer == NULL)return 0;
    return __get_string(buffer,strlen(buffer),MQTT_ORIGEN_PASS);
}





 uint32_t mem_services_set_mqtt_pub_topics(char* buffer,uint8_t topic_pos){
     if(topic_pos >= TOPICS_MAX) return 0;
     if(buffer == NULL) return 0;
     return __set_string(buffer,strlen(buffer),(PUB_TOPICS_0 + topic_pos));
}


 uint32_t mem_services_get_mqtt_pub_topics(char* buffer,uint8_t topic_pos){
    if(topic_pos >= TOPICS_MAX) return 0;
    if(buffer == NULL) return 0;
    return __get_string(buffer,strlen(buffer),(PUB_TOPICS_0 + topic_pos));
}


 uint32_t mem_services_set_mqtt_sub_topics(char* buffer,uint8_t topic_pos){
     if(topic_pos >= TOPICS_MAX) return 0;
     if(buffer == NULL) return 0;
     return __set_string(buffer,strlen(buffer),(SUB_TOPICS_0 + topic_pos));
}


 uint32_t mem_services_get_mqtt_sub_topics(char* buffer,uint8_t topic_pos){
    if(topic_pos >= TOPICS_MAX) return 0;
    if(buffer == NULL) return 0;
    return __get_string(buffer,strlen(buffer),(SUB_TOPICS_0 + topic_pos));
}






 uint32_t mem_services_write_data(char* buffer, uint8_t len, uint16_t pag){
    mem_resumen();     // resumen
    //escribo en memoria flash

    uint32_t ret = 0;
    uint8_t __len=len;
    // guardo el tama??o del buffer en primera posicion
    ret = __write_data(&__len,1,pag+OFFSET_ESP_REG,0);

    ret= __write_data(buffer,len,pag+OFFSET_ESP_REG,1);

     debug_print("mem W init:\r\n");
     debug_print(buffer);
     debug_print("mem W end:\r\n");

    mem_sleep();     // entramos en sleep
    return ret;
 }

 

 uint32_t mem_services_read_data(char* buffer, uint8_t len_buff, uint16_t pag){
    mem_resumen();     // resumen
    //escribo en memoria flash
    uint32_t ret = 0;
    uint8_t __len = 0;
    ret = __read_data(&__len,1,OFFSET_ESP_REG+pag,0);
    //ret = (1 )? __read_data(buffer,__len+1,pag,1): 0;  // si el tamanio de datos a leer es mayou que el espacio en buffer, no leo y retorno ret=0
    ret =  __read_data(buffer,__len,OFFSET_ESP_REG+pag,1);  // si el tamanio de datos a leer es mayou que el espacio en buffer, no leo y retorno ret=0
    debug_print("mem  R init:\r\n");
    debug_print(buffer);
    debug_print("mem  R end:\r\n");

    mem_sleep();     // entramos en sleep
    return ret;


 }