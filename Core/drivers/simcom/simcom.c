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


#include "cmd.h"
#include "uart.h"
#include "gpio.h"
#include "string.h"





#define SIMCOM_AT_UART             UART_B       //! Pin A10  (TX) y A9 (RX)
#define SIMCOM_DEBUG_UART          UART_A        //! Pin A3 (RX)  y A2 (TX)
#define SIMCOM_BAUDRATE            115200


#define SIMCOM_BUFFER_SIZE          150





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
       cmd_init_device(__SIMCOM__);
       
        res =1;
    }
    return res;

}





uint32_t sim_check_at(){

    uint32_t res = 0;
    if ( __SIMCOM__ != NULL){
        #define CMD_AT      "AT\r\n"
         res = cmd_send_cmd(__SIMCOM__,(uint8_t*)CMD_AT,strlen(CMD_AT),1000);
    }
    return  res;
}



uint32_t sim_get_version(){

     uint32_t res = 0;
    if ( __SIMCOM__ != NULL){
        #define CMD_GETVERSION      "ATI\r\n"
         res = cmd_send_cmd(__SIMCOM__,CMD_GETVERSION,strlen(CMD_GETVERSION),3000);
    }
    return  res;

}



uint32_t sim_set_echo(uint32_t ena){
    uint32_t res = 0;
    if ( __SIMCOM__ != NULL){
        #define CMD_ECHO_ON         "ATE1\r\n"
        #define CMD_ECHO_OFF        "ATE0\r\n"
        if(ena == 0){
            res = cmd_send_cmd(__SIMCOM__,CMD_ECHO_OFF,strlen(CMD_ECHO_OFF),1000);
        }
         else{
            res = cmd_send_cmd(__SIMCOM__,CMD_ECHO_ON,strlen(CMD_ECHO_ON),1000);
         }
    }
    return  res;

}








uint32_t sim_set_pwr_gps(uint32_t ena){
    uint32_t res = 0;
    if ( __SIMCOM__ != NULL){
        #define CMD_PWR_GPS_ON         "AT+CGNSPWR=1\r\n"
        #define CMD_PWR_GPS_OFF        "AT+CGNSPWR=0\r\n"
        if(ena == 0){
            res = cmd_send_cmd(__SIMCOM__,CMD_PWR_GPS_OFF,strlen(CMD_PWR_GPS_OFF),1000);
        }
         else{
            res = cmd_send_cmd(__SIMCOM__,CMD_PWR_GPS_ON,strlen(CMD_PWR_GPS_ON),1000);
         }
    }
    return  res;

}


uint32_t sim_get_gps_info(){

    uint32_t res = 0;
    if ( __SIMCOM__ != NULL){
        #define CMD_GETGPSINFO      "AT+CGNSINF\r\n"
         res = cmd_send_cmd(__SIMCOM__,CMD_GETGPSINFO,strlen(CMD_GETGPSINFO),3000);
    }
    return  res;
}





uint8_t sim_deinit(){
    return 0;
}





