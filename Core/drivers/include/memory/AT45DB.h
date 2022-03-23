/**
 * @file A45DB.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef __AT45DB__H
#define __AT45DB__H
#include "core.h"
#include "gpio.h"
#include "spi.h"


#define OFFSET_4MB

typedef struct __flash_storage
{
    int pg_num;
    int pg_shifts;
    uint32_t block_sz;
    uint32_t erase_sz;
    uint32_t n_eraseblocks;
} flash_storage_t;






/**
 * @brief Define el tamanio en bytes de la pagina a utilizar 
 * 
 */
typedef enum {
     pg_256byte     =  8
    ,pg_512bytes    =  9
    ,pg_1024byte    =  10
    ,pg_2048bytes   = 11
}at45db_page_size;





uint32_t AT45DB_init(   SIMO_SPI port,
                        SIMO_GPIO_PIN chip_select,
                        simo_spi_prescaler prescaler);

uint32_t at45db_start( at45db_page_size page_size);





uint32_t AT45DB_read_page(uint8_t* data, uint8_t len_data,uint32_t page,uint8_t pos);




uint32_t AT45DB_write_page(uint8_t* data, uint8_t len_data,uint32_t page,uint8_t pos);


void AT45DB_resumen(void);


void AT45DB_erase_full(void);



void AT45DB_sleep(void);


void AT45DB_stop(void);

#endif