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






    #define GET_ID_CMD                0x9F
    #define MANUFACTURER_ID           0x1F    //id byte  1
    #define DEVICE_ID_1               0x24    //id byte  2
    #define DEVICE_ID_2               0x00    //id byte  3
    #define EDI                       0x01    // id byte 4





    /**
     * @brief Obtener el ID de la memoria y compararlo con MANUFACTURER_ID,DEVICE_ID_1,DEVICE_ID_2,EDI
     * 
     * @param port  SIMO SPI a utilizar
     * @param chip_select SIMO_GPIO_PIN a utilizar como Chip select
     * @return ** uint32_t 
     */
    uint32_t  __AT45DB041E_check_id(SIMO_SPI port, SIMO_GPIO_PIN chip_select);

    #endif



#endif