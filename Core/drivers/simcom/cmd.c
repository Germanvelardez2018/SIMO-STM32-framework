/**
 * @file cmd.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "cmd.h"



#include "uart.h"
#include "gpio.h"




cmd_device_t*  cmd_create_device(  uint8_t* buff, uint32_t len_buff ,cmd_init_interface init
                                   ,cmd_function read ,cmd_function write
                                   #if CMD_DEBUG_PRINT == 1
                                   ,cmd_init_interface debug_init
                                   ,cmd_function debug_print 
                                   #endif
                                   ){
        // Comprobamos todos los parametros importantes

        if((init == NULL) && (read == NULL) && (write == NULL)
        #if CMD_DEBUG_PRINT == 1
            && (debug_print == NULL)
            && (debug_init == NULL)
        #endif
        ) return NULL;  // Error

        // Cargamos los parametros

        cmd_device_t* dev = (cmd_device_t*) malloc(sizeof(cmd_device_t));
        if(dev == NULL) return NULL;  // Error
        dev->buff = buff;
        dev->len_buff = len_buff;
        dev->init = init;
        dev->read = read;
        dev->write = write;
        #if CMD_DEBUG_PRINT == 1
        dev->debug_init = debug_init;
        dev->debug_print= debug_print;

        #endif

        // Retornamos el puntero al dispositivo correctamente asignado
        return dev;
}


uint32_t cmd_init_device(cmd_device_t* device){

    uint32_t res = (device == NULL)?0 : 1;

    // Llamo a la funcion que inicializa la interfaz
    device->init();

    #if CMD_DEBUG_PRINT == 1
    #define INIT_MSG        "\r\n Se inicio el dispositivo \r\n"
    #define CMD_TIMEOUT_DEFAULT     200
    device->debug_init();
    device->debug_print(INIT_MSG,strlen(INIT_MSG),CMD_TIMEOUT_DEFAULT);
    #endif

    return res;

    
}


uint32_t cmd_send_cmd(cmd_device_t* device,uint8_t* cmd_string, uint32_t len_cmd,uint32_t timeout){

    if(device == NULL) return 0;
    // Llamo a la funcion que inicializa la interfaz
    #if CMD_DEBUG_PRINT == 1
        device->debug_print("\r\n-->",5,timeout);
        device->debug_print(cmd_string,len_cmd,timeout);
    #endif

    device->write(cmd_string,len_cmd,100);
    device->read(device->buff,device->buff,timeout);
   // simo_uart_read(UART_B,f,10,2000,0);
    #if CMD_DEBUG_PRINT == 1
        device->debug_print("\r\n<--",5,timeout);
        device->debug_print(device->buff,strlen(device->buff),timeout);
    #endif 
    device->buff[0]=0;
    return 1;

}








void cmd_deinit_device(cmd_device_t* device){

}