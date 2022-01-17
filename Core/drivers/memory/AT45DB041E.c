/**
 * @file AT45DB041E.c
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para el modelo de memoria espeficiado
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "AT45DB041E.h"
#include "delay.h"


#define TIMEOUT_SPI     100

#if SIMO_SPI_ENA == 1   // Sin SPI no hay memoria





static inline  void __AT45DB041E_start(SIMO_SPI port, SIMO_GPIO_PIN chip_select);

static inline uint8_t __AT45DB041E_get_status(SIMO_SPI port, SIMO_GPIO_PIN chip_select);

static inline uint32_t  __AT45DB041E_check_id(SIMO_SPI port, SIMO_GPIO_PIN chip_select);

static inline uint32_t __AT45DB041E_is_bussy(SIMO_SPI port, SIMO_GPIO_PIN chip_select);










/**
 * @brief  Secuencia de inicio de la memoria.
 * 
 * @param mem 
 * @return ** void 
 */
static inline void  __AT45DB041E_start(SIMO_SPI port, SIMO_GPIO_PIN chip_select)
{
    simo_gpio_write(chip_select,1);
    simo_gpio_write(chip_select,0);
    simo_spi_write(port,(uint8_t*)RESUME_CMD,1,TIMEOUT_SPI,0);
    simo_gpio_write(chip_select,1);
    //obtengo el id del producto
    if(!__AT45DB041E_check_id(port,chip_select)) return ;
    
    //configuro tamaño de pagina y buffer: 256

    if(!(__AT45DB041E_is_bussy(port,chip_select) & AT45DB_STATUS_PGSIZE)) 
    //pregunto si page_size es 264. Si es true, configuro en 256
    {
        simo_gpio_write(chip_select,0);
        simo_spi_write(port,(uint8_t*)at45db_pgsize_256_cmd,AT45DB_PG_SIZE_264_LEN,TIMEOUT_SPI,0);
        simo_gpio_write(chip_select,1);
    }
}


uint32_t check_id(SIMO_SPI port, SIMO_GPIO_PIN chip_select){
    return  __AT45DB041E_check_id(port,chip_select);
}


/**
 * @brief Obtener el ID de la memoria y compararlo con MANUFACTURER_ID,DEVICE_ID_1,DEVICE_ID_2,EDI
 * 
 * @param port  SIMO SPI a utilizar
 * @param chip_select SIMO_GPIO_PIN a utilizar como Chip select
 * @return ** uint32_t 
 */
static inline uint32_t  __AT45DB041E_check_id(SIMO_SPI port, SIMO_GPIO_PIN chip_select){

    uint32_t ret = 1;
    uint8_t cmd[5]= {GET_ID_CMD,0,0,0,0};
    uint8_t  data[5]={0,0,0,0,0};
    simo_gpio_write(chip_select,0);
    simo_spi_write_read(port,cmd,data,5,TIMEOUT_SPI,0); // Transaccion sin IT
    simo_gpio_write(chip_select,1);
    //checkeo respuesta correcta
    if( data[1] != MANUFACTURER_ID    
        || data[2] != DEVICE_ID_1        
        || data[3] != DEVICE_ID_2        
        || data[4] != EDI) {
        ret = 0;  //fallo checkeo de ID
    }
        return ret;
}



/*
 * @brief 
 *   Retorna el primer byte de estatus del chip
 * @param mem 
 * @return ** uint8_t 
 */
static inline uint8_t __AT45DB041E_get_status(SIMO_SPI port, SIMO_GPIO_PIN chip_select)
{
    uint8_t cmd[2]={GETSTATUS_CMD,0};
    uint8_t status[2]={0,0};

            //flanco ascendente 
     //en alto el CS Pin
    simo_gpio_write(chip_select,0);
    simo_spi_write_read(port,cmd,status,2,TIMEOUT_SPI,0);    //leo el primer byte del registro estado

     //en alto el CS Pin
    simo_gpio_write(chip_select,1);
    return  status[1];
}


/**
 * @brief  Espero que la memoria este disponible y retorno el primer byte de status
 * 
 * @param mem  objeto memoria
 * @return ** uint32_t 
 */
static inline uint32_t __AT45DB041E_is_bussy(SIMO_SPI port, SIMO_GPIO_PIN chip_select)
{
    uint32_t ret;

    uint32_t counter= 0;
    while(!((ret =__AT45DB041E_get_status(port,chip_select)) & AT45DB_STATUS_READY) || !(counter > AT45DB_TIMEOUT))  //mientras este ocupado, espere
    {
       //Delay
        //simo_delay_ms(1);
        counter+=1;
    }
    return ret;  //es el primer byte del registro de estados
}







void AT45DB041E_start_config(SIMO_SPI port, SIMO_GPIO_PIN chip_select){
    __AT45DB041E_start(port,chip_select);
}


void AT45DB041E_full_erase(SIMO_SPI port, SIMO_GPIO_PIN chip_select)
{
    simo_gpio_write(chip_select,0);    
    simo_spi_write(port,erase_cmd,ERASE_SECUENCE_LEN,ERASE_SECUENCE_LEN*TIMEOUT_SPI,0);
    simo_gpio_write(chip_select,1);

}



    void AT45DB041E_write_data(SIMO_SPI port, SIMO_GPIO_PIN chip_select,
                                    uint8_t* buffer,
                                    uint32_t buffer_len,
                                    uint32_t page,
                                    uint32_t position_page)
    {


        // cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)

        uint32_t _page = (uint32_t) (page << PAGE_OFFSET);
        uint32_t _pos = (uint32_t)  (position_page << POS_OFFSET);
        uint32_t address = (uint32_t)  _page + _pos;
        
        uint8_t cmd[4] ;    
        

        cmd[0] = WRITE_BUFF1_CMD;
        cmd[1] = (address >> 24)  & 0xff;
        cmd[2] = (address >> 16)  & 0xff;
        cmd[3] = (address >> 8)& 0xff;

        //inicia (pulso en bajo)

        simo_gpio_write(chip_select, 0); 
    
        simo_spi_write(port,cmd,4,TIMEOUT_SPI,0);   // envio comandos

        
        simo_spi_write(port,buffer,(uint32_t)buffer_len,TIMEOUT_SPI,0); // escribo en memoria
        // finaliza (pulso en alto)
        simo_gpio_write(chip_select, 1); 

         __AT45DB041E_is_bussy(port,chip_select);

    }



    void AT45DB041E_read_data(SIMO_SPI port, SIMO_GPIO_PIN chip_select,
                                    uint8_t* buffer,
                                    uint32_t buffer_len,
                                    uint32_t page,
                                    uint32_t position_page)
    {

        // cmd escribir | 3bytes de direccion(  11 bits pagina (0 a 2048| 8 bytes posicion de la pagina | 5 dummy bits)

        uint32_t _page = (uint32_t) (page << PAGE_OFFSET);
        uint32_t _pos = (uint32_t)  (position_page << POS_OFFSET);
        uint32_t address = (uint32_t)  _page + _pos;
        uint8_t cmd[5] ;    
        
        cmd[0] = CMD_FAST_READ;
        cmd[1] = (address >> 24) & 0xff;
        cmd[2] = (address >> 16) & 0xff;
        cmd[3] = (address >> 8)  & 0xff;
        cmd[4] = 0;
        //inicia (pulso en bajo)

        simo_gpio_write(chip_select, 0); 
        
        
        simo_spi_write(port,cmd,5,TIMEOUT_SPI,0);    //  Envio secuencia de commandos

        simo_spi_read(port,buffer,buffer_len,TIMEOUT_SPI,0);    //buffer a escribir
        // finaliza (pulso en alto)
        simo_gpio_write(chip_select, 1); 

         __AT45DB041E_is_bussy(port,chip_select);

    }








#endif

