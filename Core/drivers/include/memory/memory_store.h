/**
 * @file memory_store.h
 * @author German Velardez (germanvelardez@gmail.com)
 * @brief  Driver para manejar memoria flash AT45DB041E
 * @version 0.1
 * @date 2022-01-17
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _MEMORY_STORE_H
#define _MEMORY_STORE_H

#include "core.h"
#include "spi.h" // Simo SPI
#include "gpio.h"

typedef enum
{
    MEMORY_LOW, //! Modo bajo consumo
    MEMORY_NORMAL, //! Modo normal,
    MEMORY_FAST //! Modo alta velocidad
    
} memory_mode;

typedef struct
{

    SIMO_SPI port;
    SIMO_GPIO_PIN cs_pin;
    memory_mode mode;

} memory_t; //! Instancia de memoria asociada a un puerto SPI



memory_t* memory_create(SIMO_SPI port, SIMO_GPIO_PIN chip_select, memory_mode mode);


uint32_t memory_init(memory_t* mem);

uint32_t memory_deinit(memory_t* mem);


uint32_t memory_low_power(memory_t* mem);

uint32_t memory_read_buffer(memory_t* mem,uint8_t* buffer, uint32_t buffer_len);

uint32_t memory_write_buffer(memory_t* mem,uint8_t* buffer, uint32_t buffer_len);





#endif