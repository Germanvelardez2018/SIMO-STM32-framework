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
#ifndef __MEMORY_H__
#define __MEMORY_H__
#include "core.h"
#include "spi.h"    //! Modulo SIMO necesario
#include "gpio.h"   //! Modulo SIMO necesario




#define AT45DB041E_PAGES_DEFAULT    2048   //! En paginas de 256



//! Estrutuca con formato de la memoria, copiada de una libreria de github
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
     pg_256byte     =  8           //! 2048 Paginas totales  
    ,pg_512bytes    =  9           //! 1024 Paginas totales
    ,pg_1024byte    =  10          //! 512  Paginas Totales
    ,pg_2048bytes   =  11          //! 256  Paginas Totales
}mem_page_size;






/**
 * @brief   Iniciando memoria. Hardware SPI
 * 
 * @param port 
 * @param chip_select 
 * @param prescaler 
 * @return ** uint32_t 
 */
uint32_t mem_init(   SIMO_SPI port,
                     SIMO_GPIO_PIN chip_select,
                     SIMO_SPI_PRESCALER prescaler);


/**
 * @brief  Desconfiguramos memoria. 
 * 
 * @return ** void
 */
void mem_deinit();

/**
 * @brief 
 * 
 * @param page_size 
 * @return ** uint32_t 
 */
uint32_t mem_start( mem_page_size page_size);




/**
 * @brief 
 * 
 * @param data          buffer de datos. 
 * @param len_data      256 bytes maximo
 * @param page          paginas  2048 en 256bytes
 * @param pos           posicion 256
 * @return ** uint32_t 
 */
uint32_t mem_read_page(uint8_t* data, uint8_t len_data,uint32_t page,uint8_t pos);



/**
 * @brief 
 * 
 * @param data          buffer de datos
 * @param len_data      256 bytes maximo
 * @param page          paginas  2048 en 256bytes
 * @param pos           posicion 256 
 * @return ** uint32_t 
 */
uint32_t mem_write_page(uint8_t* data, uint8_t len_data,uint32_t page,uint8_t pos);

/**
 * @brief  salir de modo bajo consumo
 * 
 * @return ** void 
 */
void mem_resumen(void);

/**
 * @brief   borrar el chip
 * 
 * @return ** void 
 */
void mem_erase_full(void);


/**
 * @brief  Modo low power
 * 
 * @return ** void 
 */
void mem_sleep(void);




#endif