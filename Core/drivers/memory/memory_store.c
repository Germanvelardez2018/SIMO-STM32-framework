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



    
memory_t* memory_create(SIMO_SPI port, SIMO_GPIO_PIN chip_select, memory_mode mode){
    memory_t* __mem = (memory_t*) malloc(sizeof(memory_t));
    if(__mem == NULL) return NULL;   // fallo en asignar memoria a objeto
    __mem->cs_pin = chip_select;
    __mem->port = port;
    __mem->mode = mode;
    return __mem;
}


uint32_t memory_init(memory_t* mem){
    return 0;
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