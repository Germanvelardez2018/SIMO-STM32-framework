/**
 * @file delay.c
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Implementacion de la funcion de delay bloqueante
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#include "delay.h"
#include "main.h"


    void simo_delay_ms(uint32_t time){
        HAL_Delay(time);
    }
