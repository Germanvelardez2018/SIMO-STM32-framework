/**
 * @file rtc.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Driver  para manejar  el hardware RTC
 * @version 0.1
 * @date 2022-01-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef __SIMO_RTC_H
#define __SIMO_RTC_H






#include "core.h"
#if SIMO_RTC_ENA == 1


  /** @defgroup RTC_Month_Date_Definitions Month Definitions
    * @{
    */

  /* Coded in BCD format */
  #define SIMO_RTC_MONTH_JANUARY              ((uint8_t)0x01)
  #define SIMO_RTC_MONTH_FEBRUARY             ((uint8_t)0x02)
  #define SIMO_RTC_MONTH_MARCH                ((uint8_t)0x03)
  #define SIMO_RTC_MONTH_APRIL                ((uint8_t)0x04)
  #define SIMO_RTC_MONTH_MAY                  ((uint8_t)0x05)
  #define SIMO_RTC_MONTH_JUNE                 ((uint8_t)0x06)
  #define SIMO_RTC_MONTH_JULY                 ((uint8_t)0x07)
  #define SIMO_RTC_MONTH_AUGUST               ((uint8_t)0x08)
  #define SIMO_RTC_MONTH_SEPTEMBER            ((uint8_t)0x09)
  #define SIMO_RTC_MONTH_OCTOBER              ((uint8_t)0x10)
  #define SIMO_RTC_MONTH_NOVEMBER             ((uint8_t)0x11)
  #define SIMO_RTC_MONTH_DECEMBER             ((uint8_t)0x12)

  /**
    * @}
    */

  /** @defgroup RTC_WeekDay_Definitions WeekDay Definitions
    * @{
    */
  #define SIMO_RTC_WEEKDAY_MONDAY             ((uint8_t)0x01)
  #define SIMO_RTC_WEEKDAY_TUESDAY            ((uint8_t)0x02)
  #define SIMO_RTC_WEEKDAY_WEDNESDAY          ((uint8_t)0x03)
  #define SIMO_RTC_WEEKDAY_THURSDAY           ((uint8_t)0x04)
  #define SIMO_RTC_WEEKDAY_FRIDAY             ((uint8_t)0x05)
  #define SIMO_RTC_WEEKDAY_SATURDAY           ((uint8_t)0x06)
  #define SIMO_RTC_WEEKDAY_SUNDAY             ((uint8_t)0x00)


  #define SIMO_NUM_BACK_REGISTER    ((uint32_t)10)



  /**
   * @brief Inicio el hardware RTC.
   * 
   * @return ** simo_state 
   */
  simo_state simo_rtc_init();









  /**
   * @brief Obtiene el valor de la hora del dispositvo. En caso de error retorna 0 
   * 
   * @param time Esctructura con formato de hora 
   * @return ** simo_state
   */
  simo_state simo_rtc_get_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds);



  /**
   * @brief Obtiene el valor de la hora del dispositvo. En caso de error retorna 0 
   * 
   * @param time Esctructura con formato de hora 
   * @return ** simo_state 
   */
  simo_state simo_rtc_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds);





  /**
   * @brief Obtiene el valor de la fecha del dispositvo. En caso de error retorna 0  
   * 
   * @param date Estructura con el formato de fecha 
   * @return ** simo_state 
   */
  simo_state simo_rtc_get_date(uint8_t* week_day,uint8_t* month, uint8_t* date_day,uint8_t* year);



  /**
   * @brief Obtiene el valor de la fecha del dispositvo. En caso de error retorna 0  
   * 
   * @param date Estructura con el formato de fecha 
   * @return ** simo_state 
   */ 
  simo_state simo_rtc_set_date(uint8_t week_day,uint8_t month, uint8_t date_day,uint8_t year);

  /**
   * @brief Habilita la interrupcion por Alarma RTC
   * 
   * @param ena  0 para deshabilita, diferente de 0
   * @return ** void
   */
  void simo_rtc_ena_irq(uint32_t ena);

  /**
   * @brief Configura la funcion de callback correspondiente
   * 
   * @param callback  Funcion callback
   * @return ** simo_state 
   */
  simo_state simo_rtc_set_alarm_callback(callback_irq callback);



  /**
   * @brief 
   * 
   * @param hours 
   * @param minutes 
   * @param seconds 
   * @return ** simo_state 
   */
  simo_state simo_rtc_set_alarm(uint8_t hours, uint8_t minutes, uint8_t seconds);



  /**
   * @brief 
   * 
   * @param hours 
   * @param minutes 
   * @param seconds 
   * @return ** simo_state 
   */
  simo_state simo_rtc_get_alarm(uint8_t* hours, uint8_t* minutes, uint8_t* seconds);




/**
 * @brief  Escribe un registro del backup
 * 
 * @param addres_reg direccion del registro. Direccuion maxima 5
 * @param data  dato a escribir
 * @return ** void 
 */
  void simo_rtc_write_backup_reg(uint32_t addres_reg,uint32_t data);




  /**
   * @brief Lee un registro de backup
   * 
   * @param addres_reg  direccion del registro. Direccuion maxima 5
   * @return ** uint32_t 
   */
  uint32_t simo_rtc_read_backup_reg(uint32_t addres_reg);

#endif // SIMO_RTC_ENA

#endif



