#include "comm_services.h"
#include "mem_services.h"
#include "comm.h"
#include "debug.h"
#include "delay.h"


#define MQTT_WAIT_MSG                   "Wait\r\n"
#define MQTT_READY_MSG                  "COMM SERVICES READY\r\n"






#define HARD_CODER_CREDENTIALS              0


#define CREDENTIAL_SIZE_MAX                 35



#if HARD_CODER_CREDENTIALS     == 1

char MQTT_TOPIC[CREDENTIAL_SIZE_MAX]={0};
char MQTT_URL[CREDENTIAL_SIZE_MAX]={0};
char MQTT_PASS[CREDENTIAL_SIZE_MAX]={0};
char MQTT_ID[CREDENTIAL_SIZE_MAX]={0};
char MQTT_QOS[CREDENTIAL_SIZE_MAX]={0};



#define MQTT_TOPIC                  (MQTT_TOPIC )
#define MQTT_URL                    (MQTT_URL )
#define MQTT_PASS                   (MQTT_PASS )
#define MQTT_ID                     (MQTT_ID )
#define MQTT_QOS                    (MQTT_QOS )

#else



#define CREDENTIALS_MQTT_TOPIC                 "X1111"
#define CREDENTIALS_MQTT_URL                   "simointi.cloud.shiftr.io"
#define CREDENTIALS_MQTT_PASS                  "fdZY5b69OhOVsAns"
#define CREDENTIALS_MQTT_ID                    "simointi"
#define CREDENTIALS_MQTT_QOS                    "0"



char MQTT_TOPIC[35]=    CREDENTIALS_MQTT_TOPIC  ;
char MQTT_URL[35]=      CREDENTIALS_MQTT_URL  ;
char MQTT_PASS[35]=     CREDENTIALS_MQTT_PASS  ;
char MQTT_ID[35]=       CREDENTIALS_MQTT_ID  ;
char MQTT_QOS[35]=      CREDENTIALS_MQTT_QOS  ;



#endif











uint32_t comm_services_config_all(void){
   comm_set_echo(0);
   comm_get_operator();
   simo_delay_ms(500);
   comm_services_open_apn();
   simo_delay_ms(500);
   comm_services_gps_init(1);
   debug_print("configurando mqtt  con datos desde mem\r\n");
   #if HARD_CODER_CREDENTIALS     == 1
    // Si HARD_CODER es 1 , no usamos memoria externa para cargar credenciales MQTT
        mem_services_get_mqtt_origen(MQTT_URL);
        mem_services_get_mqtt_id_origen(MQTT_ID);
        mem_services_get_mqtt_pass_origen(MQTT_PASS);
        mem_services_get_mqtt_pub_topics(MQTT_TOPIC,0);
        mem_services_get_mqtt_qos_origen(MQTT_QOS);

   #endif
   comm_config_mqtt(MQTT_URL ,MQTT_ID,MQTT_PASS,MQTT_QOS);

}

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



uint32_t comm_services_wait_ok(void){
    uint32_t ready = 0;
    debug_print(MQTT_WAIT_MSG);
    while(ready == 0){
    ready =  comm_services_check();
    simo_delay_ms(500);

    }
    debug_print(MQTT_READY_MSG);
    return 1;
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




