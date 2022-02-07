/**
 * @file delay.h
 * @author GErman Velardez (germanvelardez16@gmail.com)
 * @brief  Driver para manejo de retardos bloqueantes
 * @version 0.1
 * @date 2022-01-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "core.h"



#ifndef __SIMO_DELAY_H
#define __SIMO_DELAY_H
/**
 * @brief Delay basado en Systick y HAL STM32
 * 
 * @param time 
 * @return ** void 
 */
    void simo_delay_ms(uint32_t time);
#endif