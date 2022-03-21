/**
 * @file AT45DB041E.h
 * @author German Velardez (germanvelardez@gmail.com)
 * @brief  Driver para manejar memoria flash AT45DB041E
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _AT45DB041E_H
#define _AT45DB041E_H

#include "core.h"
#include "spi.h" // Simo SPI
#include "gpio.h"






    #if SIMO_SPI_ENA == 1
    typedef enum
    {
        __AT45DB041E_LOW, //! Modo bajo consumo
        __AT45DB041E_NORMAL, //! Modo normal,
        __AT45DB041E_FAST //! Modo alta velocidad
        
    } __AT45DB041E_mode;









    //bits de estado

    #define AT45DB_TIMEOUT          1000

    #define AT45DB_STATUS_PGSIZE  (1 << 0) /* PAGE SIZE */
    #define AT45DB_STATUS_PROTECT (1 << 1) /* PROTECT */
    #define AT45DB_STATUS_COMP    (1 << 6) /* COMP */
    #define AT45DB_STATUS_READY   (1 << 7) /* RDY/BUSY */
    

    //comandos y secuencias

    #define ERASE_SECUENCE		        0xC7, 0x94, 0x80, 0x9A     //secuencia de borrado del chip completo
    #define ERASE_SECUENCE_LEN          4                           
    #define RESUME_CMD                  0xAB                      //salgo del deep sleep_us
    #define GETSTATUS_CMD               0xD7                      //Leo los registros de estado de la memoria

    #define WRITE_WITH_BUFF1            0x82                     // usar buffer 1 para escribir en memoria

    #define AT45DB_PG_SIZE_256_SECUENCE    0x3D, 0x2A, 0x80, 0xA6    //Programa tamaño de pagina en 256
    #define AT45DB_PG_SIZE_256_LEN          4

    #define AT45DB_PG_SIZE_264_SECUENCE     0x3D, 0x2A, 0x80 ,0xA7    //Programa tamaño de pagina en 264
    #define AT45DB_PG_SIZE_264_LEN          4






    #define GET_ID_CMD                0x9F
    #define MANUFACTURER_ID           0x1F    //id byte  1
    #define DEVICE_ID_1               0x24    //id byte  2
    #define DEVICE_ID_2               0x00    //id byte  3
    #define EDI                       0x01    // id byte 4













// escribir en memoria
// !Escribir en memoria principal mediante buffer 1. 
// !Direccion : pagina[15bits] | posicion dentro del buffer[8]
#define WRITE_BUFF1_CMD                    0x82    
#define WRITE_BUFF2_CMD                    0x85    // Escribir en memoria principal mediante buffer 2
#define CMD_FAST_READ                     (0x0B) // max speed 85 MHz. Also its posible to use 0x1B


/* Programacion del tamaño de pagina */

static  uint8_t at45db_pgsize_256_cmd[] = {  AT45DB_PG_SIZE_256_SECUENCE    };
static  uint8_t at45db_pgsize_264_cmd[] = {  AT45DB_PG_SIZE_264_SECUENCE    };


/* Secuencia de borrado de todo el chip*/
static  uint8_t erase_cmd[ERASE_SECUENCE_LEN] = {ERASE_SECUENCE};



/*****************************************************************************/
/*Status Register Format:                                   */
/* ------------------------------------------------------------------------- */
/* | bit7   | bit6   | bit5   | bit4   | bit3   | bit2   | bit1   | bit0   | */
/* |--------|--------|--------|--------|--------|--------|--------|--------| */
/* |RDY/BUSY| COMP   |         device density            |   X    |   X    | */
/* ------------------------------------------------------------------------- */
/* 0:busy   |        |        AT45DB041:0111             | protect|page size */
/* 1:ready  |        |        AT45DB161:1011             |                   */
/* --------------------------------------------------------------------------*/


/**
 *  Memoria utilizada: at45db041E
 * PAGINAS: 2048        DIRECCION DE 11 BITS
 * BLOQUES: 256         DIRECCION DE 8 BITS
 * SECTORES: 8          
 * 
 * Se pueden usar paginas de 264bytes o de 256bytes. 
 * cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)
 * **/
#define PAGE_OFFSET         21   //Deberia ser 13 pero esta pensando para acomodar los dartos en uin32_t
#define POS_OFFSET          13   // y dejar 13 bytes dommies
#define BLOCK_OFFSET        












uint32_t check_id(SIMO_SPI port, SIMO_GPIO_PIN chip_select);


/**
 * @brief Configura tamanio de pagina y lee el id manufacture
 * 
 * @param port 
 * @param chip_select 
 * @return ** void 
 */
void AT45DB041E_start_config(SIMO_SPI port, SIMO_GPIO_PIN chip_select,simo_spi_prescaler prescaler){


/**
 * @brief Borra la memoria completamente
 * 
 * @param port hardware SPI a utilizar
 * @param chip_select gpio a utilizar para funciones chip select
 * @return ** void 
 */
void AT45DB041E_full_erase(SIMO_SPI port, SIMO_GPIO_PIN chip_select);





/**
 * @brief Escribe un buffer de datos en memoria
 * 
 * @param port 
 * @param chip_select 
 * @param buffer 
 * @param buffer_len 
 * @param page 
 * @param position_page 
 */
void AT45DB041E_write_data(SIMO_SPI port, SIMO_GPIO_PIN chip_select,
                                 uint8_t* buffer,
                                 uint32_t buffer_len,
                                 uint32_t page,
                                 uint32_t position_page);


/**
 * @brief Lee un buffer de datos desde memoria
 * 
 * @param port 
 * @param chip_select 
 * @param buffer 
 * @param buffer_len 
 * @param page 
 * @param position_page 
 * @return ** void 
 */
void AT45DB041E_read_data(SIMO_SPI port, SIMO_GPIO_PIN chip_select,
                                uint8_t* buffer,
                                uint32_t buffer_len,
                                uint32_t page,
                                uint32_t position_page);







    





    #endif // SIMO_SṔI_ENA



#endif