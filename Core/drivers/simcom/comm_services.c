#include "comm_services.h"
#include "comm.h"










#define MQTT_TOPIC                "X1111"
#define MQTT_BROKER2               "simointi.cloud.shiftr.io"
#define MQTT_PASS                  "fdZY5b69OhOVsAns"
#define MQTT_ID                    "simointi"
#define MQTT_QOS                    "0"







uint32_t comm_services_open_apn(){
    uint32_t ret = comm_open_apn();
    return ret;
}

uint32_t comm_services_gps_init(uint32_t gps_on){

    uint32_t ret ;
    ret = comm_set_pwr_gps(gps_on);

    
    return ret;
}



uint32_t comm_services_get_nmea(char* buffer){
    uint32_t ret = 0 ;


    comm_resume();
    ret =  comm_get_gps_info();
    strcpy(buffer, comm_get_buffer());  // si hay error puntero tiene NULL, revisar antes de usar
    comm_sleep();
    return ret;
}





uint32_t comm_services_check(void){


    uint32_t ret =comm_check();

    


    return ret;
}


/**
 * @brief Iniciamos los servicios de almacenamiento 
 *        en memoria flash externa. 
 * 
 * @return ** uint32_t 
 */
uint32_t comm_services_init(void){
    uint32_t ret =0;
    ret = comm_init();
    ret = comm_set_echo(0);
 //   ret = comm_config_mqtt(MQTT_BROKER2,MQTT_ID,MQTT_PASS,MQTT_QOS);
    return ret;
}


/**
 * @brief Cerramos todos los servicios de memoria flash externa.
 * 
 * @return ** void 
 */
void comm_services_deinit(void){
}




