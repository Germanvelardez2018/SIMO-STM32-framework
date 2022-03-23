/**
 * @file AT45DB041E.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "memory_store.h"




#define FSM_SPI                 SPI_A
#define FSM_SPI_CS              GPIO_10











/**
 * @brief FUncion de transformacion entre memory_mode a prescaler_divisor del spi
 * 
 * @param mode 
 * @return ** simo_spi_prescaler 
 */
static simo_spi_prescaler __set_prescaler_spi( memory_mode mode){
    
    simo_spi_prescaler prescaler = SIMO_SPI_PRESCALER_256;

    switch (mode)
    {
    case MEMORY_LOW:
            prescaler = SIMO_SPI_PRESCALER_32;
        break;
    case MEMORY_NORMAL:
            prescaler = SIMO_SPI_PRESCALER_8;
        break;
    case MEMORY_FAST :
            prescaler = SIMO_SPI_PRESCALER_2;
        break;
    default:
        break;
    }
}

    
memory_t* memory_create(SIMO_SPI port, SIMO_GPIO_PIN chip_select, memory_mode mode){
    
    memory_t* __mem = (memory_t*) malloc(sizeof(memory_t));
    if(__mem == NULL) return NULL;   // fallo en asignar memoria a objeto
    __mem->cs_pin = chip_select;
    __mem->port = port;
    __mem->mode = mode;
    return __mem;
}


uint32_t memory_init(memory_t* mem){
    uint32_t ret = 1;
    if (mem == NULL){
        ret = 0;
    } else{
        simo_spi_prescaler prescaler =  __set_prescaler_spi(mem->mode);
        AT45DB041E_start_config(mem->port , mem->cs_pin,prescaler );

    }

    return ret;
}

uint32_t memory_deinit(memory_t* mem){
    return 0;
}


uint32_t memory_low_power(memory_t* mem){

    uint32_t ret = 1;
    if( mem != NULL){
    mem->mode = MEMORY_LOW;
    }
    else{  ret = 0;
    }

    return ret;
}

uint32_t memory_read_buffer(memory_t* mem,uint8_t* buffer, uint32_t buffer_len){
    return 0;
}

uint32_t memory_write_buffer(memory_t* mem,uint8_t* buffer, uint32_t buffer_len){
    return 0;
}