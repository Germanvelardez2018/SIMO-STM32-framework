/**
 * @file config.h
 * @author German Velardez (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-01-06
 *
 * @copyright Copyright (c) 2022
 *
 */

/**
 * @brief Archivo de configuracion del framework
 *
 */

// Este archivo contiene  los recursos mas importantes disponibles en el microcontrolador.


//Habilitamos el hardware UART
#define C_SIMO_UART_ENA                         1
//Habilitamos el hardware SPI
#define C_SIMO_SPI_ENA                          1
//Habilitamos el hardware Timer                 
#define C_SIMO_TIMER_ENA                        1


// Cantidad de instancias
#define C_NUM_SIMO_TIMER                        3
#define C_NUM_SIMO_UART                         3
#define C_NUM_SIMO_SPI                          2

#define C_NUM_SIMO_GPIO                         10



// Interrupciones


//TIMER GLOBAL IRQ
#define  C_SIMO_TIMER_IRQ                          1
//Habilitamos configuracion de interrupciones
#define  C_SIMO_TIMER_EVENT_IRQ                    1


//UART GLOBAL  IRQ
#define  C_SIMO_UART_IRQ                       1

// Habilite configuracion para generar interrupciones UART
#define  C_SIMO_UART_TX_IRQ                    1
#define  C_SIMO_UART_RX_IRQ                    1


//SPI GLOBAL IRQ
#define  C_SIMO_SPI_IRQ                        1

//Habilitamos configuracion de interrupciones SPI
#define  C_SIMO_SPI_TX_IRQ                          1
#define  C_SIMO_SPI_RX_IRQ                          1










