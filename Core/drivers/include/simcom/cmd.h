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

//! Funcion para escribir y leer datos de la interfaz  mediante buffers
typedef uint32_t(*cmd_function)(uint8_t* buff,uint32_t len, uint32_t timeout);


//! Objeto utilizado para almacenar los datos de configuracion de un dispostivo que funcione mediante comandos AT

typedef struct{

    //! Buffer de datos recibidos
    uint8_t*   buff;
    //! Tamanio del buffer de recepcion
    uint32_t   len_buff;
    //! Funcion para iniciar la interfaz a utilizar
    cmd_init_interface init;
    //! Funcion para leer un buffer de datos mediante la interfaz
    cmd_function read;
    //! Funcion para escribir un buffer de datos mediante la interfaz
    cmd_function write;
    #if CMD_DEBUG_PRINT == 1
    //! Funcion para iniciar la interfaz de debug
        cmd_init_interface debug_init;
    //! Funcion para escribir un buffer de datos mediante la interfaz de debug
        cmd_function debug_print;
    #endif
} cmd_device_t;



/**
 * @brief  Crea un objeto cmd_device_t
 * 
 */
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



/**
 * @brief Inicia el dispositvo
 * 
 * @param device 
 * @return ** uint32_t 
 */
uint32_t cmd_init_device(cmd_device_t* device);




/**
 * @brief  Escribe un buffer de datos mediante la interfaz y almacena la respuesta en el buffer de datos de recepcion
 * 
 * @param device 
 * @param cmd_string 
 * @param len_cmd 
 * @param timeout 
 * @return ** uint32_t 
 */
uint32_t cmd_send_cmd(cmd_device_t* device,uint8_t* cmd_string, uint32_t len_cmd,uint32_t timeout);




/**
 * @brief  Deshabilita la interfaz y libera los recursos asociados
 * 
 * @param device 
 * @return ** void 
 */
void cmd_deinit_device(cmd_device_t* device);