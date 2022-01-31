/**
 * @file power_mode.h
 * @author German Velardez (germanvelardez@gmail.com)
 * @brief  Driver  para el manejo de los modos de funcionamiento
 * @version 0.1
 * @date 2022-01-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "core.h"
#include "main.h"



/**
 * @brief PVD Hardware:
 *  1 Sirve como un comparador  de nivel digital para monitorear el pin de fuente VDD.
 *  2 Pueden activarse interrupciones asociadas
 *  3 Se desactiva en modo Standby mode
 *  4 el pin weak-up se utiliza para salir del modo Standby
 *  5 el pin weak-up es PA 0
 * /
 * 
 * 
 * 
 * 
 /**
  *@brief Modos de bajo consumo 
  *  Sleep Mode:
  *  Stop Mode:
  *  Stand by mode
  * 
  * **/





typedef (*setup_config)() ;  //! Funcion con la configuracion inicial. Necesaria para cuando estamos en modos stop o standby donde la configuracion inicial es borrada.





/**
 * @brief Habilita el modo solo isr en Sleep mode
 * 
 * @param ena 
 * @return ** void 
 */
void simo_pwr_sleep_only_isr(uint32_t ena);


/**
 * @brief Secuena de configuracion necesarias antes de cambiar de modo
 * 
 * @return ** void 
 */
void simo_pwr_before_change_mode();



/**
 * @brief Secuena de configuracion necesarias despues de retornar al modo normal 
 * 
 * @return ** void 
 */
void simo_pwr_return_normal_mode();



/**
 * @brief Agregamos una funcion de configuracion inicial. Esta se llama al volver al modo normal desde stop o standbymode.
 * 
 * @param setup 
 * @return ** void 
 */
void simo_pwr_set_initial_config(setup_config setup);



/**
 * @brief Sleep mode, apaga el cpu, deja los perifericos encendidos.
 * 
 * @return ** void 
 */
void simo_pwr_enter_sleep_mode();


/**
 * @brief Stop mode los HSI y LSI se apagan
 * 
 * @return ** void 
 */
 void simo_pwr_enter_stop_mode();




/**
 * @brief Stanby mode, apagamos todo y nos vamos a la mierda.
 * 
 * @return ** void 
 */
 void simo_pwr_standby_mode();