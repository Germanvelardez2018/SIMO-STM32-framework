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

    #include "config.h"
    #include <string.h>
    #include <stdint.h>
    #include <stdlib.h>


 

  

    //Este archivo contiene  los recursos mas importantes disponibles en el microcontrolador.




    #define CLOCK_TIMER                 4000000
    #define SIMO_RTC_ENA                C_SIMO_RTC_ENA



    #define SIMO_UART_ENA               C_SIMO_UART_ENA
    #define SIMO_SPI_ENA                C_SIMO_SPI_ENA
    #define SIMO_I2C_ENA                C_SIMO_I2C_ENA
    #define SIMO_TIMER_ENA              C_SIMO_TIMER_ENA
    #define SIMO_GPIO_ENA               C_SIMO_GPIO_ENA  
    #define SIMO_ADC_ENA                C_SIMO_ADC_ENA                       



    // Cantidad de instancias
    #define NUM_SIMO_UART               C_NUM_SIMO_UART
    #define NUM_SIMO_I2C                C_NUM_SIMO_I2C
    #define NUM_SIMO_SPI                C_NUM_SIMO_SPI
    #define NUM_SIMO_GPIO               C_NUM_SIMO_GPIO
    #define NUM_SIMO_TIMER              C_NUM_SIMO_TIMER
    #define NUM_SIMO_ADC                C_NUM_SIMO_ADC







    // Interrupciones
    #define SIMO_UART_IRQ                       C_SIMO_UART_IRQ
        #if SIMO_UART_IRQ == 1
            //Habilite configuracion para generar interrupciones UART
            #define SIMO_UART_TX_IRQ            C_SIMO_UART_TX_IRQ
            #define SIMO_UART_RX_IRQ            C_SIMO_UART_RX_IRQ
            #else
            #define SIMO_UART_TX_IRQ     0
            #define SIMO_UART_RX_IRQ     0
        #endif


    #define SIMO_I2C_IRQ                        C_SIMO_I2C_IRQ
    #define SIMO_I2C_ERROR_IRQ                  C_SIMO_I2C_ERROR_IRQ

        #if SIMO_I2C_IRQ == 1
            #define  SIMO_I2C_MASTER_ENA        C_SIMO_I2C_MASTER_ENA                       
            #define  SIMO_I2C_SLAVE_ENA         C_SIMO_I2C_SLAVE_ENA
        #else                         
            #define  SIMO_I2C_MASTER_ENA         0                       
            #define  SIMO_I2C_SLAVE_ENA          0
        #endif


        #if  (SIMO_I2C_MASTER_ENA + SIMO_I2C_SLAVE_ENA) == 0
            #define    SIMO_I2C_ENA   0
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
#define SIMO_ADC_IRQ                    C_SIMO_ADC_IRQ


#if SIMO_GPIO_EXT_IRQ == 1
    typedef void (*callback_gpio_ext_it)(uint16_t);
#endif 

#define SIMO_TIMER_IRQ                  C_SIMO_TIMER_IRQ





    // Deshabilitamos si valores de instancias son 0


    #if NUM_SIMO_TIMER == 0
        #define    SIMO_UART_ENA   0
    #endif

    #if NUM_SIMO_I2C == 0
        #define    SIMO_I2C_ENA   0
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




    //CORE I2C
    #if SIMO_I2C_ENA == 1
        typedef enum {
        #if NUM_SIMO_I2C >0
            I2C_A
        #endif
        #if NUM_SIMO_I2C >1
            ,I2C_B
        #endif
        } SIMO_I2C;
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

    
    //! Estados del sistema
    typedef enum {
      FSM_UNDEFINED        = 2
    , FSM_WITHOUT_CONFIG   =3         //! Sin configuracion
    , FSM_ON_FIELD         =4      //! Transmicion desde campo
    , FSM_MEMORY_DOWNLOAD  =5    //! Transmicion desde memoria

    } fsm_devices;


    //! Modos del sistema

typedef enum {
        RESUMEN_RUN = 0     //! Normal modo de operacion (default)
    ,   SLEEP_ONLY_ISR_MODE   //! Sleep, despierta para realizar IQR y vuelve a dormir 
    ,   SLEEP_MODE       //! CPU OFF, Perifericos funcionando
    ,   STOP_MODE        //! CPU OFF, Perifericos OFF,Todos las fuentes de clock off
    ,   STANDBY_MODE     //! 1.2 V domain powered off
}pwr_modes;


typedef enum {
    S_OUTPUT_INT
    ,S_OUTPUT_FLOAT
    ,S_OUTPUT_STRING
} sensor_output;


typedef struct{
    char *format;
    uint8_t len;
} sensor_format;


typedef uint32_t (*check_sensor)(sensor_format);




#endif



