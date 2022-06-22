/**
 * @file wdt.h
 * @author German Velardez (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-05-05
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __WDT_H__
#define __WDT_H__


#include "main.h"
#include "core.h"




typedef enum {
             WDT_PRE_4 
            ,WDT_PRE_8
            ,WDT_PRE_16
            ,WDT_PRE_32
            ,WDT_PRE_64
            ,WDT_PRE_128
            ,WDT_PRE_256
} WDT_PRE;




/**
 * @brief Inicio el contador del wdt
 * 
 * @param reload_value 
 * @param prescaler 
 * @return ** simo_state 
 */
simo_state  simo_wdt_init(uint32_t reload_value, WDT_PRE prescaler );



/**
 * @brief  refresco la cuenta del wdt 
 * 
 * @return ** void  
 */
void  simo_wdt_refresh(void);


# endif