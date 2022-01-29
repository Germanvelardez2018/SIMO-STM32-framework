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


#include "core.h"





#define CMD_DEBUG_PRINT         1

//! Funcion para iniciar el periferico. En caso de necesitar parametros, encapsular en funcion sin parametros
typedef uint32_t (*cmd_init_interface)(void);


typedef uint32_t(*cmd_function)(uint8_t* buff,uint32_t len, uint32_t timeout);




typedef struct{

    uint8_t*   buff;
    uint32_t   len_buff;
    cmd_init_interface init;
    cmd_function read;
    cmd_function write;
    #if CMD_DEBUG_PRINT == 1
        cmd_init_interface debug_init;
        cmd_function debug_print;
    #endif
} cmd_device_t;




cmd_device_t*  cmd_create_device(  uint8_t* buff
                                   ,uint32_t len_buff
                                   ,cmd_init_interface init
                                   ,cmd_function read
                                   ,cmd_function write
                                   #if CMD_DEBUG_PRINT == 1
                                    ,cmd_init_interface debug_init
                                    ,cmd_function debug_print
                                   #endif
                                   );


uint32_t cmd_init_device(cmd_device_t* device);





uint32_t cmd_send_cmd(cmd_device_t* device,uint8_t* cmd_string, uint32_t len_cmd,uint32_t timeout);





void cmd_deinit_device(cmd_device_t* device);