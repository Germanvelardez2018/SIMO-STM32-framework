/**
 * @file simcom.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "simcom.h"

#include "stdio.h"
#include "cmd.h"
#include "uart.h"
#include "gpio.h"
#include "string.h"
#include "delay.h"




#define SIMCOM_AT_UART             UART_A       //! Pin A10  (TX) y A9 (RX)
#define SIMCOM_DEBUG_UART          UART_B        //! Pin A3 (RX)  y A2 (TX)
#define SIMCOM_BAUDRATE            115200


#define SIMCOM_BUFFER_SIZE          150






//! Pins para manejar el modulo SIM
#define PIN_SIM_BAT                       SIMO_GPIO_28//PB12
#define PIN_SIM_PWRUP                     SIMO_GPIO_29//PB13
#define PIN_SIM_IRQ                     


//! Configuracion MQTT
 #define CMD_MQTT               "AT+SMCONF="
 #define CMD_MQTT_URL           " \"URL\""
 #define CMD_MQTT_USER          "\"USERNAME\""
 #define CMD_MQTT_PASSWORD      "\"PASSWORD\""
 #define CMD_MQTT_QOS           "\"QOS\""
 #define CMD_MQTT_COMMIT        "AT+SMCONN\r\n"
 #define CMD_MQTT_PUBLISH       "AT+SMPUB=\"%s\",\"%d\",1,1 \r\n"    // PARAMS 1TOPIC, 2LENMESSAGE


#define CMD_OK                  "OK\r\n"
#define LEN_CMD_OK               4
#define IS_EQUAL                0



static uint32_t __check_response(char* buffer,char* response){
    uint32_t len_reponse = strlen(response)  ;
    uint32_t len_buffer = strlen(buffer);
    uint32_t index = len_buffer - len_reponse ;  
    uint32_t res = (  strncmp(&(buffer[index]),response,len_reponse) == IS_EQUAL)?1:0;
    return res;
}




static cmd_device_t* __SIMCOM__;

static uint8_t __buffer[SIMCOM_BUFFER_SIZE];


static void __init_device(){
     simo_uart_init(SIMCOM_AT_UART,SIMCOM_BAUDRATE);
}


static void __init_debug(){
     simo_uart_init(SIMCOM_DEBUG_UART,SIMCOM_BAUDRATE);
}

static  uint32_t __debug_print(uint8_t* buff,uint32_t len, uint32_t timeout){
     return simo_uart_write(SIMCOM_DEBUG_UART,buff,len,timeout,0);    
}

static  uint32_t __write(uint8_t* buff,uint32_t len, uint32_t timeout){
         return simo_uart_write(SIMCOM_AT_UART,buff,len,timeout,0);
}


static  uint32_t __read(uint8_t* buff,uint32_t len, uint32_t timeout){
      return simo_uart_read(SIMCOM_AT_UART,buff,len,timeout,0);
}

//---------------------------------------------------------------------

uint32_t sim_init(){
     uint32_t res = 0;
    __SIMCOM__ = cmd_create_device(__buffer,SIMCOM_BUFFER_SIZE,__init_device,__read,__write
    #if CMD_DEBUG_PRINT == 1
    ,__init_debug,__debug_print
    #endif
    );
    if(__SIMCOM__ != NULL) {
      // iniciamos los pines correspondientes
      simo_gpio_set(PIN_SIM_BAT,SIMO_GPIO_OUT);
      simo_gpio_set(PIN_SIM_PWRUP,SIMO_GPIO_OUT);
      res = cmd_init_device(__SIMCOM__);
      simo_gpio_write(PIN_SIM_BAT,1);
      simo_gpio_write(PIN_SIM_PWRUP,1); 
    }
    return res;

}





uint32_t sim_check_at(){

    uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_AT      "AT\r\n"
         cmd_send_cmd(__SIMCOM__,(uint8_t*)CMD_AT,strlen(CMD_AT),1000);
         res = __check_response(__buffer,CMD_OK);
    }
    return  res;
}



uint32_t sim_get_version(){

     uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_GETVERSION      "ATI\r\n"
         cmd_send_cmd(__SIMCOM__,CMD_GETVERSION,strlen(CMD_GETVERSION),2000);
         res = __check_response(__buffer,CMD_OK);

    }
    return  res;

}



uint32_t sim_set_echo(uint32_t ena){
    uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_ECHO_ON         "ATE1\r\n"
        #define CMD_ECHO_OFF        "ATE0\r\n"
        if(ena == 0){
             cmd_send_cmd(__SIMCOM__,CMD_ECHO_OFF,strlen(CMD_ECHO_OFF),1000);
        }
         else{
             cmd_send_cmd(__SIMCOM__,CMD_ECHO_ON,strlen(CMD_ECHO_ON),1000);
         }

          res = __check_response(__buffer,CMD_OK);
    }
    return  res;

}




uint32_t sim_get_signal_level(){

     uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_GETVERSION      "AT+CSQ\r\n"
         cmd_send_cmd(__SIMCOM__,CMD_GETVERSION,strlen(CMD_GETVERSION),2000);
         res = __check_response(__buffer,CMD_OK);
    }
    return  res;

}



uint32_t sim_set_pwr_gps(uint32_t ena){
    uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_PWR_GPS_ON         "AT+CGNSPWR=1\r\n"
        #define CMD_PWR_GPS_OFF        "AT+CGNSPWR=0\r\n"
        if(ena == 0){
            cmd_send_cmd(__SIMCOM__,CMD_PWR_GPS_OFF,strlen(CMD_PWR_GPS_OFF),1000);
        }
         else{
            cmd_send_cmd(__SIMCOM__,CMD_PWR_GPS_ON,strlen(CMD_PWR_GPS_ON),1000);
         }
          res = __check_response(__buffer,CMD_OK);
    }
    return  res;

}


uint32_t sim_get_gps_info(){
    uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_GETGPSINFO      "AT+CGNSINF\r\n"
        cmd_send_cmd(__SIMCOM__,CMD_GETGPSINFO,strlen(CMD_GETGPSINFO),2000);
        res = __check_response(__buffer,CMD_OK);
    }
    return  res;
}



uint32_t sim_get_operator(){
     uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_GETOPERATOR      "AT+COPS?\r\n"
        cmd_send_cmd(__SIMCOM__,CMD_GETOPERATOR,strlen(CMD_GETOPERATOR),2500);
        res = __check_response(__buffer,CMD_OK);
    }
    return  res;

}


uint32_t sim_open_apn(){
      uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_OPEN_APN      "AT+CNACT=1,\"internet.movil\"\r\n"
        cmd_send_cmd(__SIMCOM__,CMD_OPEN_APN,strlen(CMD_OPEN_APN),3000);
    }
    res = __check_response(__buffer,CMD_OK);
    return  res;

}

uint32_t sim_get_apn(){
      uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
            #define CMD_GET_APN    "AT+CNACT?"       
        cmd_send_cmd(__SIMCOM__,CMD_GET_APN,strlen(CMD_GET_APN),2000);
    }
    res = __check_response(__buffer,CMD_OK);
    return  res;
}


uint8_t sim_deinit(){
    return 0;
}


uint32_t sim_get_default(){
       uint32_t res = 1;
    if ( __SIMCOM__ != NULL){
        #define CMD_GET_DEFAULT      "ATZ\r\n"
        cmd_send_cmd(__SIMCOM__,CMD_GET_DEFAULT,strlen(CMD_GET_DEFAULT),2500);
    }
        res = __check_response(__buffer,CMD_OK);

    return  res;

}


uint32_t sim_config_mqtt(uint8_t* url, uint8_t* user, uint8_t* password, uint8_t* qos){

    uint32_t res = 1;
    // Si algun argumento es invalido, devolvemos 0.
   // if( (url == NULL) || (user == NULL) ||
    //    (password == NULL) || (qos == NULL) )return 0;
     
    if ( __SIMCOM__ != NULL){
         
        u_int8_t buffer[100]={};
        sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_URL,url);    
        cmd_send_cmd(__SIMCOM__,buffer,strlen(buffer),2000);
         sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_USER,user);    
        cmd_send_cmd(__SIMCOM__,buffer,strlen(buffer),2000);
         sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_PASSWORD,password);    
        cmd_send_cmd(__SIMCOM__,buffer,strlen(buffer),2000);
         sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_QOS,qos);    
        cmd_send_cmd(__SIMCOM__,buffer,strlen(buffer),2000);
        cmd_send_cmd(__SIMCOM__,CMD_MQTT_COMMIT,strlen(CMD_MQTT_COMMIT),3000);
    }

        res = __check_response(__buffer,CMD_OK);


    return res;

}




uint32_t sim_mqtt_publish(char* topic, char* payload,uint16_t len_payload){

    uint32_t res = 0;
    if ( __SIMCOM__ != NULL){
        u_int8_t buffer[250]={};
        sprintf(buffer,CMD_MQTT_PUBLISH,topic,len_payload);    
        res = cmd_send_cmd(__SIMCOM__,buffer,strlen(buffer),2000);
        res = cmd_send_cmd(__SIMCOM__,payload,strlen(payload),2000);
    }
    return res;
}


uint8_t* sim_get_buffer(){
    return &__buffer[0];
}






uint32_t sim_low_pwr_mode(uint32_t ena ){
    uint32_t res = 0;
    if ( __SIMCOM__ != NULL){
        #define CMD_LOW_PWR_ON         "AT+CPSMS=1\r\n"
        #define CMD_LOW_PWR_OFF        "AT+CPSMS=0\r\n"
        if(ena == 0){
            res = cmd_send_cmd(__SIMCOM__,CMD_LOW_PWR_OFF,strlen(CMD_LOW_PWR_OFF),1000);
        }
         else{
            res = cmd_send_cmd(__SIMCOM__,CMD_LOW_PWR_ON,strlen(CMD_LOW_PWR_ON),1000);
         }
    }
    return  res;
}