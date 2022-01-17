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


#if SIMO_SPI_ENA == 1   // Sin SPI no hay memoria


uint32_t  __AT45DB041E_check_id(SIMO_SPI port, SIMO_GPIO_PIN chip_select){

    uint32_t ret = 1;
    uint8_t cmd[5]= {GET_ID_CMD,0,0,0,0};
    uint8_t  data[5]={0,0,0,0,0};
    simo_gpio_write(chip_select,0);
    simo_spi_write_read(port,cmd,data,5,1000,0); // Transaccion sin IT
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

#endif

