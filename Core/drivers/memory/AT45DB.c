

#include "AT45DB.h"
#include "delay.h"
#include "stdlib.h"
#include "stdio.h"

#define AT45DB_TIMEOUT          1000
#define TIMEOUT_SPI             100
#define MEMORY_SPI_PRESCALER    SIMO_SPI_PRESCALER_2


static  SIMO_GPIO_PIN       __chip_select; //! Pin de Chip Select
static  SIMO_SPI            __port ;       //! Port SPI Definido 
static flash_storage_t      __flash;       //! Estructura de memoria. Depende de capacidad y tamaño de pagina 



#define RESUME_CMD                          0xAB       //salgo del deep sleep_us
#define PG_PER_BLOCK                        (8)
#define PG_PER_SECTOR                       (256)

#define AT45DB_RDDEVID                      0x9f /* Product ID, Manufacturer ID and density read */
#define AT45DB_RDSR                         0xd7 /* SR */
#define AT45DB_RESUME                       0xab /* Resume flash */

#define AT45DB_MANUFACT_ATMEL               0x1F /* Atmel manufacturer */
#define AT45DB_DENSITY_MSK                  0x1f /* Density Mask */
#define AT45DB_FAM_MSK                      0xe0 /* Family Mask */
#define AT45DB_FAM_DATAFLASH                0x20 /* DataFlash device */
#define AT45DB_DENSITY_64MBIT               0x08 /* AT45DB641 */
/* Read */
#define AT45DB_RDARRAYHF                    0x0b /* Continuous array read (high frequency) */
/* Erase */
#define AT45DB_PGERASE                      0x81 /* Page Erase */
#define AT45DB_MNTHRUBF1                    0x82 /* Main memory page program through buffer 1 */

/* PageSize reporgramming sequence */
#define AT45DB_PGSIZE_SIZE 4
static const uint8_t at45db_pgsize_cmd[] = {
    0x3D, 0x2A, 0x80, 0xA6
};

#define MANUFACTURER_ID                      0x1F    //id byte  1
#define DEVICE_ID_1                          0x24    //id byte  2
#define DEVICE_ID_2                          0x00    //id byte  3
#define EDI                                  0x01    // id byte 4


#define AT45DB_STATUS_PGSIZE                (1 << 0) /* PAGE SIZE */
#define AT45DB_STATUS_PROTECT               (1 << 1) /* PROTECT */
#define AT45DB_STATUS_COMP                  (1 << 6) /* COMP */
#define AT45DB_STATUS_READY                 (1 << 7) /* RDY/BUSY */

#define AT45DB_LOW_POWER                    (0x9B)  // INTO LOW POWER



inline void __at45db_resumen(void);

static inline uint8_t __at45db_bsy(void);
static inline uint8_t __at45db_get_status(void);


static void __set_AT45DB641E(at45db_page_size page_size){
    #define AT45DB641E_PAGES_DEFAULT    32768
    uint8_t offset = page_size - 8 ;     // ejemplo si las pag sno 1024, tenemos en total page_default ( 2 a la offset) 
    /* TODO: Add other densities, atm only AT45DB641E */
    __flash.pg_shifts     = page_size;                     //Lo que hace es paginas de 1024 bytes potencia(2,10)
    __flash.pg_num        = AT45DB641E_PAGES_DEFAULT / (1 << offset) ;                    //pagina de 1024 son 8192
    __flash.block_sz      = 1 << __flash.pg_shifts;  // Una pagina(1024) por block?
    __flash.erase_sz      = __flash.block_sz;
    __flash.n_eraseblocks = __flash.pg_num;    
}


static void __set_AT45DB041E(at45db_page_size page_size){
    #define AT45DB041E_PAGES_DEFAULT    512
    uint8_t offset = page_size - 8 ;     // ejemplo si las pag sno 1024, tenemos en total page_default ( 2 a la offset) 
    /* TODO: Add other densities, atm only AT45DB041E*/
    __flash.pg_shifts     = page_size;                     //Lo que hace es paginas de 1024 bytes potencia(2,10)
    __flash.pg_num        = AT45DB041E_PAGES_DEFAULT / (1 << offset) ;                    //512 PAGINAS DE 256 BYTES
    __flash.block_sz      = 1 << __flash.pg_shifts;  // Una pagina(1024) por block?
    __flash.erase_sz      = __flash.block_sz;
    __flash.n_eraseblocks = __flash.pg_num;
}


static inline uint8_t __at45db_get_status(void){
    uint8_t cmd[2]={AT45DB_RDSR,0};
    uint8_t status[2]={0,0};
    //flanco ascendente 
     //en alto el CS Pin
    simo_gpio_write(__chip_select,0);
    simo_spi_write_read(__port,cmd,status,2,TIMEOUT_SPI,0);    //leo el primer byte del registro estado
     //en alto el CS Pin
    simo_gpio_write(__chip_select,1);
    return  status[1];
}


static inline uint8_t __at45db_bsy(void){
    uint32_t ret = 0;
    uint32_t counter= 0;
    while(!((ret =__at45db_get_status()) & AT45DB_STATUS_READY) || !(counter > AT45DB_TIMEOUT))  //mientras este ocupado, espere
    {
        //simo_delay_ms(1);
        counter+=1;
    }
    return ret;  //es el primer byte del registro de estados
}




uint32_t AT45DB_init(   SIMO_SPI port,
                        SIMO_GPIO_PIN chip_select,
                        simo_spi_prescaler prescaler){
    uint32_t ret = 0;
//! verifico parametros del usuario
    ret = simo_spi_init(port,prescaler);
    simo_gpio_set(chip_select,SIMO_GPIO_OUT);
    __port =  port;
    __chip_select = chip_select;

return ret;    
}





uint32_t at45db_start(ATDB45_DENSITY mem_size, at45db_page_size page_size)
{

    __at45db_resumen();
    simo_delay_ms(1); // deberia ser del orde de los 50/35 ns

    uint32_t ret = 1;
    uint8_t  cmd[5]= {AT45DB_RDDEVID,0,0,0,0};
    uint8_t  data[5]={0,0,0,0,0};
    simo_gpio_write(__chip_select,0);
    simo_spi_write_read(__port,cmd,data,5,TIMEOUT_SPI,0); // Transaccion sin IT
    simo_gpio_write(__chip_select,1);


    //checkeo respuesta correcta, este es solo para AT45DB041E, reformular
    if( data[1] != AT45DB_MANUFACT_ATMEL    
        || data[2] != DEVICE_ID_1        
        || data[3] != DEVICE_ID_2        
        || data[4] != EDI) {
        return 0;  //fallo checkeo de ID
    }
 
   /* Configuro en modo 256 por pagina*/
    if(!(__at45db_bsy() & AT45DB_STATUS_PGSIZE)) 
    {   //pregunto si page_size es 264. Si es true, configuro en 256
        simo_gpio_write(__chip_select,0);
        simo_spi_write(__port,(uint8_t*)at45db_pgsize_cmd,AT45DB_PGSIZE_SIZE,TIMEOUT_SPI,0);
        simo_gpio_write(__chip_select,1);
    }
    if( mem_size ==  AT45DB_4MB){
        __set_AT45DB041E(page_size);
    }
    else{
        __set_AT45DB641E(page_size);
    }
    return ret; // Exito
}



void AT45DB_erase_full(void){

    uint8_t cmd[4];

    cmd[0] = 0xc7;
    cmd[1] = 0x94;
    cmd[2] = 0x80;
    cmd[3] = 0x9a;
    simo_gpio_write(__chip_select,0);
    simo_spi_write(__port,(uint8_t*)cmd,4,TIMEOUT_SPI,0);
    simo_gpio_write(__chip_select,1);
    __at45db_bsy();

}








static inline void __at45db_page_erase(uint32_t sector)
{
    uint8_t cmd[4];
    uint32_t off;

    off = sector << __flash.pg_shifts;

    cmd[0] = AT45DB_PGERASE;
    cmd[1] = (off >> 16) & 0xff;
    cmd[2] = (off >> 8) & 0xff;
    cmd[3] = off & 0xff;

  

    simo_gpio_write(__chip_select,1);
    simo_gpio_write(__chip_select,0);
    simo_spi_write(__port,(uint8_t*)cmd,4,TIMEOUT_SPI,0);
    simo_gpio_write(__chip_select,1);
    __at45db_bsy();


}




uint32_t AT45DB_start(void){
return 0;    
}


void AT45DB_write_page(uint8_t* data, uint8_t len_data,uint32_t page){
    // CONS 256 PAGEADDRESS[15]|DUMMY[1]|BUFFERADDRES[8]
        uint32_t offset = page << __flash.pg_shifts;
                //uint32_t offset = page << 9;

        uint8_t cmd[4] ;    
        cmd[0] = AT45DB_MNTHRUBF1;
        cmd[1] = (offset >> 16)  & 0xff;
        cmd[2] = (offset >> 8)   & 0xff;
        cmd[3] = offset & 0xff;
        //inicia (pulso en bajo)
        simo_gpio_write(__chip_select, 0); 
        simo_spi_write(__port,cmd,4,TIMEOUT_SPI,0);   // envio comandos
        simo_spi_write(__port,data,(uint32_t)len_data,TIMEOUT_SPI,0); // escribo en memoria
        // finaliza (pulso en alto)
        simo_gpio_write(__chip_select, 1); 
        __at45db_bsy();

}

void AT45DB_read_page(uint8_t* data, uint8_t len_data,uint32_t page){

        // CONS 256 PAGEADDRESS[23]| DUMMY[1]|DUMMY[8]

        uint8_t cmd[5] ;    
        //uint32_t offset = page << 9;

        uint32_t offset = page << __flash.pg_shifts;
        cmd[0] = AT45DB_RDARRAYHF;
        cmd[1] = (offset >> 16) & 0xff;
        cmd[2] = (offset >> 8) & 0xff;
        cmd[3] = offset & 0xff;
        cmd[4] = 0;
        //inicia (pulso en bajo)
        simo_gpio_write(__chip_select, 0); 
        simo_spi_write(__port,cmd,5,TIMEOUT_SPI,0);    //  Envio secuencia de commandos
        simo_spi_read(__port,data,len_data,TIMEOUT_SPI,0);    //data a escribir
        // finaliza (pulso en alto)
        simo_gpio_write(__chip_select, 1); 
        __at45db_bsy();
       
}






inline void __at45db_resumen(void){
    simo_gpio_write(__chip_select,1);
    simo_gpio_write(__chip_select,0);
    simo_spi_write(__port,(uint8_t*)RESUME_CMD,1,TIMEOUT_SPI,0);
    simo_gpio_write(__chip_select,1);
    __at45db_bsy();

}




void AT45DB_resumen(void){
    __at45db_resumen();
}


void AT45DB_sleep(void){

    simo_gpio_write(__chip_select,1);
    simo_gpio_write(__chip_select,0);
    simo_spi_write(__port,(uint8_t*)AT45DB_LOW_POWER,1,TIMEOUT_SPI,0);
    simo_gpio_write(__chip_select,1);
    __at45db_bsy();

}


void AT45DB_stop(void);




