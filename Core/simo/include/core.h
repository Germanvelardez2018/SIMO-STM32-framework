/**
 * @file core.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef __SIMO_CORE_H
#define __SIMO_CORE_H


//INCLUDES DE C STANDAR
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

//Este archivo contiene  los recursos mas importantes disponibles en el microcontrolador.

#define SIMO_UART_ENA          1
#define SIMO_SPI_ENA           1


// Cantidad de instancias
#define NUM_SIMO_UART          2
#define NUM_SIMO_SPI           2



#define NUM_SIMO_PINS          10
#define NUM_TIME               2



// Interrupciones
#define SIMO_UART_IRQ        1
#define SIMO_SPI_IRQ         1
#define SIMO_TIMER_IRQ       1



// Deshabilitamos si valores de instancias son 0

#if NUM_SIMO_UART == 0
    #define    SIMO_UART_ENA   2
#endif


#if NUM_SIMO_SPI == 0
    #define    SIMO_SPI_ENA   0
#endif





//CORE UART 

// CORE UART 

#if SIMO_UART_ENA == 1

    typedef enum {
    #if NUM_SIMO_UART >0
        UART_A,
    #endif
    #if NUM_SIMO_UART >1
        UART_B,
    #endif
    #if NUM_SIMO_UART >2
        UART_C
    #endif
    } SIMO_UART;

#if SIMO_UART_IRQ   == 1

    typedef void (*uart_irq)(void);

#endif


#if SIMO_SPI_IRQ   == 1

    typedef void (*spi_irq)(void);

#endif


#if SIMO_TIMER_IRQ   == 1

    typedef void (*timer_irq)(void);

#endif

#endif


// CORE SPI 

#if SIMO_SPI_ENA == 1
    typedef enum {
    #if NUM_SIMO_SPI >0
        SPI_A,
    #endif
    #if NUM_SIMO_SPI >1
        SPI_B,
    #endif
    #if NUM_SIMO_SPI >2
        SPI_C
    #endif
    } SIMO_SPI;

#endif










#endif



