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

    #include "config.h"

    //Este archivo contiene  los recursos mas importantes disponibles en el microcontrolador.




    #define CLOCK_TIMER                 4000000
    #define SIMO_RTC_ENA                C_SIMO_RTC_ENA



    #define SIMO_UART_ENA               C_SIMO_UART_ENA
    #define SIMO_SPI_ENA                C_SIMO_SPI_ENA
    #define SIMO_TIMER_ENA              C_SIMO_TIMER_ENA
    #define SIMO_GPIO_ENA               C_SIMO_GPIO_ENA                         



    // Cantidad de instancias
    #define NUM_SIMO_UART               C_NUM_SIMO_UART
    #define NUM_SIMO_SPI                C_NUM_SIMO_SPI
    #define NUM_SIMO_GPIO               C_NUM_SIMO_GPIO
    #define NUM_SIMO_TIMER              C_NUM_SIMO_TIMER







    // Interrupciones
    #define SIMO_UART_IRQ           C_SIMO_UART_IRQ
        #if SIMO_UART_IRQ == 1
            //Habilite configuracion para generar interrupciones UART
            #define SIMO_UART_TX_IRQ     C_SIMO_UART_TX_IRQ
            #define SIMO_UART_RX_IRQ     C_SIMO_UART_RX_IRQ
            #else
            #define SIMO_UART_TX_IRQ     0
            #define SIMO_UART_RX_IRQ     0
        #endif



    #define SIMO_SPI_IRQ                C_SIMO_SPI_IRQ
        #if SIMO_SPI_IRQ == 1
            //Habilite configuracion para generar interrupciones SPI
            #define SIMO_SPI_TX_IRQ         C_SIMO_SPI_TX_IRQ
            #define SIMO_SPI_RX_IRQ         C_SIMO_SPI_RX_IRQ
            #define SIMO_SPI_TX_RX_IRQ      C_SIMO_SPI_TX_RX_IRQ
            #else
            #define SIMO_SPI_TX_IRQ     0
            #define SIMO_SPI_RX_IRQ     0
        #endif


#define SIMO_GPIO_EXT_IRQ               C_SIMO_GPIO_EXT_IRQ 
#define SIMO_GPIO_ADC_ENA               C_SIMO_GPIO_ADC_ENA


#if SIMO_GPIO_EXT_IRQ == 1
    typedef void (*callback_gpio_ext_it)(uint16_t);

#endif 

#define SIMO_TIMER_IRQ                  C_SIMO_TIMER_IRQ





    // Deshabilitamos si valores de instancias son 0


    #if NUM_SIMO_TIMER == 0
        #define    SIMO_UART_ENA   0
    #endif



    #if NUM_SIMO_UART == 0
        #define    SIMO_UART_ENA   0
    #endif


    #if NUM_SIMO_SPI == 0
        #define    SIMO_SPI_ENA   0
    #endif







    // CORE TIMER 

    #if SIMO_TIMER_ENA == 1

        typedef enum {
        #if NUM_SIMO_TIMER >0
            TIMER_A,
        #endif
        #if NUM_SIMO_TIMER >1
            TIMER_B,
        #endif
        #if NUM_SIMO_TIMER >2
            TIMER_C
        #endif
        } SIMO_TIMER;

       

    #endif




    //CORE UART
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
    
        } SIMO_SPI;



      

    #endif

    //! Funcion callback asociada a una interupcion por hardware
    typedef void (*callback_irq)(void);

    


#endif



