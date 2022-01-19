/**
 * @file rtc.h
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Abstracion para utilizar el hardware RTC
 * @version 0.1
 * @date 2022-01-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#ifndef __SIMO_RTC_H
#define __SIMO_RTC_H


#include "core.h"

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



typedef struct {
     uint8_t second  ;  //! Segundos
     uint8_t minute;  //! Minutos
     uint8_t hour  ;  //!Hora. Valores maximo y minimo. 23 a 0

} simo_time_t;



typedef struct {
    uint8_t day   ;   //! dia del mes
    uint8_t month ;  //! mes del año. Enero 1, Diciembre 12
    uint8_t year  ;  //!Año. Valores maximos y minimos. 99 y 0

} simo_date_t;





/**
 * @brief Configurar fecha y hora del dispositivo. En caso de formato erroneo retorna 0
 * 
 * @param time 
 * @param date 
 * @return ** uint32_t 
 */
uint32_t simo_rtc_set_all(simo_time_t* time, simo_date_t* date);

/**
 * @brief Obtiene el valor de fecha y hora del dispositvo. En caso de error retorna 0
 * 
 * @param time 
 * @param date 
 * @return ** uint32_t 
 */
uint32_t simo_rtc_get_all(simo_time_t* time, simo_date_t* date);

uint32_t simo_rtc_init();


/**
 * @brief Obtiene el valor de la hora del dispositvo. En caso de error retorna 0 
 * 
 * @param time Esctructura con formato de hora 
 * @return ** uint32_t 
 */
uint32_t simo_rtc_get_time(simo_time_t* time);



/**
 * @brief Obtiene el valor de la hora del dispositvo. En caso de error retorna 0 
 * 
 * @param time Esctructura con formato de hora 
 * @return ** uint32_t 
 */
uint32_t simo_rtc_set_time(simo_time_t* time);





/**
 * @brief Obtiene el valor de la fecha del dispositvo. En caso de error retorna 0  
 * 
 * @param date Estructura con el formato de fecha 
 * @return ** uint32_t 
 */
uint32_t simo_rtc_get_date(simo_date_t* date);



/**
 * @brief Obtiene el valor de la fecha del dispositvo. En caso de error retorna 0  
 * 
 * @param date Estructura con el formato de fecha 
 * @return ** uint32_t 
 */ 
uint32_t simo_rtc_set_date(simo_date_t* date);

/**
 * @brief Habilita la interrupcion por Alarma RTC
 * 
 * @param ena  0 para deshabilita, diferente de 0
 * @return ** uint32_t 
 */
uint32_t simo_rtc_ena_irq(uint32_t ena);

/**
 * @brief Configura la funcion de callback correspondiente
 * 
 * @param callback  Funcion callback
 * @return ** uint32_t 
 */
uint32_t simo_rtc_set_alarm_callback(callback_irq callback);



#endif



