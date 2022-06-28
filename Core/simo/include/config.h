/**
 * @file config.h
 * @author German Velardez (you@domain.com)
 * @brief Archivo para configurar el proyecto.
 *  Se basa en compilacion condicional y definiciones.
 * @version 0.1
 * @date 2022-01-06
 *
 * @copyright Copyright (c) 2022
 *
 */



#include "uart.h"
// ! Mensaje de debug

#define C_DEBUG_NAME                                ("SIMO STM32")
#define C_DEBUG_ON                                   (1)
#define C_DEBUG_UART                              (UART_A)       // PA9  > USART1_TX           PA10   > USART1_RX
            
#define C_DEBUG_BAUDRATE                          (115200)


/**
 * @brief Archivo de configuracion del framework
 *
 */

//!Habilita el uso del hardware RTC
#define C_SIMO_RTC_ENA                          1
//!Habilita el uso hardware UART
#define C_SIMO_UART_ENA                         1
//!Habilita el uso hardware SPI
#define C_SIMO_SPI_ENA                          1
//!Habilita el uso del hardware I2C             
#define C_SIMO_I2C_ENA                          1
//!Habilita el uso hardware Timer                 
#define C_SIMO_TIMER_ENA                        1
//!Habilita el uso hardware GPIO                 
#define C_SIMO_GPIO_ENA                         1
//! Habilita el hardware ADC
#define C_SIMO_ADC_ENA                          0


//! Cantidad de instancias
//! Numero de instancias disponibles. Verificar  valores maximos y conflictos. Maximo: 3 instancias 
#define C_NUM_SIMO_TIMER                        2    
//! Numero de instancias disponibles. Verificar  valores maximos y conflictos. Maximo: 3 instancias 
#define C_NUM_SIMO_UART                         3    
//! Numero de instancias disponibles. Verificar  valores maximos y conflictos. Maximo: 2 instancias. Con 2 instancias conflicto SPI2 y UART3 
#define C_NUM_SIMO_SPI                          1
//! Numero de instancias disponibles. Verificar valores maximos y conclictos. Maximo: 2 instancias
#define C_NUM_SIMO_I2C                          2     //Tiene 2 I2C pero genera conclicto con UART3
//! Numero de instancias disponibles. Verificar  valores maximos y conflictos 
#define C_NUM_SIMO_GPIO                         47   // 48 Pines,0 ....al 47

#define C_NUM_SIMO_ADC                          2



// Interrupciones


//TIMER GLOBAL IRQ
//! Habilita interrupcion. Se debe configurar el callback correspondientes, habilitar la interrupcion y llamar a la funcion con ena_callback = 1
#define  C_SIMO_TIMER_IRQ                          1
#define  C_SIMO_TIMER_EVENT_IRQ                    1


//UART GLOBAL  IRQ
//! Habilita interrupcion. Se debe configurar el callback correspondientes, habilitar la interrupcion y llamar a la funcion con ena_callback = 1
#define  C_SIMO_UART_IRQ                           1

//!UART INTERRUPCIONES: TX
#define  C_SIMO_UART_TX_IRQ                        1
//!UART INTERRUPCIONES: RX
#define  C_SIMO_UART_RX_IRQ                        1



#define C_SIMO_I2C_MASTER_ENA                       1
#define C_SIMO_I2C_SLAVE_ENA                        0
//I2C GLOBAL   IRQ
#define C_SIMO_I2C_IRQ                              1
#define C_SIMO_I2C_ERROR_IRQ                        1



//! Habilita interrupcion. Se debe configurar el callback correspondientes, habilitar la interrupcion y llamar a la funcion con ena_callback = 1
#define  C_SIMO_SPI_IRQ                            1


//Habilita configuracion de interrupciones SPI
//!SPI INTERRUPCIONES: TX 
#define  C_SIMO_SPI_TX_IRQ                         1
//!SPI INTERRUPCIONES: RX
#define  C_SIMO_SPI_RX_IRQ                         1
//!SPI INTERRUPCIONES: TX RX
#define  C_SIMO_SPI_TX_RX_IRQ                      1


#define C_SIMO_GPIO_EXT_IRQ                        1
#define C_SIMO_ADC_IRQ                             1






