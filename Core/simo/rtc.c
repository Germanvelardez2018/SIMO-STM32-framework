/**
 * @file rtc.c
 * @author German Velardez (germanvelardez@gmail.com)
 * @brief  Implementacion del driver de manejo del RTC
 * @version 0.1
 * @date 2022-01-18
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "rtc.h"
#include "power_modes.h" // ! Necesario para llamar a rutinas de wake up
#include "main.h"
#include "clock_config.h" // para activar clock rtc

#define SIMO_RTC_FORMAT         RTC_FORMAT_BIN





static callback_irq __RTC_ALARM_IRQ__ ; 

static RTC_HandleTypeDef __hrtc; //! Estructura de configuracion

/**
  * @brief This function handles RTC alarm interrupt through EXTI line 17.
  */
void RTC_Alarm_IRQHandler(void)
{
 
 HAL_RTC_AlarmIRQHandler(&__hrtc);
  
}



void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc){


    if(__RTC_ALARM_IRQ__ != NULL) __RTC_ALARM_IRQ__();
    pwr_modes state =  power_mode_get_state();
    //! TERMINO LA IRQ, estamos en modo run;
     if(state != RUN_MODE )
     // si estamos modo diferente a Run Mode
     power_mode_get_callback();



}






/**
* @brief RTC MSP Initialization
* This function configures the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{
  if(hrtc->Instance==RTC)
  {

    HAL_PWR_EnableBkUpAccess();
    /* Enable BKP CLK enable for backup registers */
    __HAL_RCC_BKP_CLK_ENABLE();
    /* Peripheral clock enable */
    __HAL_RCC_RTC_ENABLE();

  }

}

/**
* @brief RTC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hrtc: RTC handle pointer
* @retval None
*/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{

  if(hrtc->Instance==RTC)
  {
    __HAL_RCC_RTC_DISABLE();
  }

}





uint32_t simo_rtc_init(){
    uint32_t ret = 1;
    ret =  simo_clock_rtc();
  __hrtc.Instance = RTC;
  __hrtc.Init.AsynchPrediv = RTC_AUTO_1_SECOND;
  __hrtc.Init.OutPut = RTC_OUTPUTSOURCE_ALARM;
  if (HAL_RTC_Init(&__hrtc) != HAL_OK){
    ret = 0; // Error
  }
return ret;
}



uint32_t simo_rtc_set_time(uint8_t hours, uint8_t minutes, uint8_t seconds){
uint32_t ret = 1;
RTC_TimeTypeDef sTime = {0};
sTime.Hours   = hours;
sTime.Minutes = minutes;
sTime.Seconds = seconds;
if (HAL_RTC_SetTime(&__hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK){
    ret = 0;
  }

return ret;
}




uint32_t simo_rtc_get_time(uint8_t* hours, uint8_t* minutes, uint8_t* seconds){
   
  uint32_t ret = 0;
  RTC_TimeTypeDef sTime = {0};

if (HAL_RTC_GetTime(&__hrtc, &sTime, RTC_FORMAT_BIN) == HAL_OK){
    ret = 1;
    (*hours) = sTime.Hours;
    (*minutes) = sTime.Minutes;
    (*seconds) = sTime.Seconds;
  }
   
    return ret;
}









uint32_t simo_rtc_get_date(uint8_t* week_day,uint8_t* month, uint8_t* date_day,uint8_t* year){
    uint32_t ret = 0;
    RTC_DateTypeDef DateToUpdate = {0};
    
    if (HAL_RTC_GetDate(&__hrtc, &DateToUpdate, RTC_FORMAT_BIN) == HAL_OK){
        ret = 1;
        (*week_day)  = DateToUpdate.WeekDay ;
        (*month)     = DateToUpdate.Month ;
        (*date_day)  = DateToUpdate.Date ;
        (*year)      = DateToUpdate.Year ;
    }

    
    return ret;
}



 
uint32_t simo_rtc_set_date(uint8_t week_day,uint8_t month, uint8_t date_day,uint8_t year){
uint32_t ret = 1;
RTC_DateTypeDef DateToUpdate = {0};
DateToUpdate.WeekDay = week_day;
DateToUpdate.Month = month;
DateToUpdate.Date = date_day;
DateToUpdate.Year = year;
if (HAL_RTC_SetDate(&__hrtc, &DateToUpdate, RTC_FORMAT_BIN) != HAL_OK){
    ret = 0;
  }
return ret;
}


void simo_rtc_ena_irq(uint32_t ena){


    if( ena == 0){
        HAL_NVIC_DisableIRQ(RTC_Alarm_IRQn);
    }
    else{
        HAL_NVIC_SetPriority(RTC_Alarm_IRQn, 0, 0);
        HAL_NVIC_EnableIRQ(RTC_Alarm_IRQn);
    }
}


uint32_t simo_rtc_set_alarm_callback(callback_irq callback){

    uint32_t ret = 0;
    if(callback != NULL){
        __RTC_ALARM_IRQ__ = callback;
        ret = 1;
    }
    return ret;
}




uint32_t simo_rtc_set_alarm(uint8_t hours, uint8_t minutes, uint8_t seconds){
    uint32_t ret = 1;
    RTC_AlarmTypeDef sAlarm ={0};
    sAlarm.AlarmTime.Hours = hours;
    sAlarm.AlarmTime.Minutes = minutes;
    sAlarm.AlarmTime.Seconds = seconds;
    sAlarm.Alarm = 1;
    if( HAL_RTC_SetAlarm_IT(&__hrtc, &sAlarm, RTC_FORMAT_BIN) != HAL_OK){
        ret = 0;
    }
    return ret;
}






uint32_t simo_rtc_get_alarm(uint8_t* hours, uint8_t* minutes, uint8_t*seconds){

     uint32_t ret = 0;
     uint32_t counter =0;
    RTC_AlarmTypeDef sAlarm ={0};
  
    sAlarm.Alarm = 1;
    if(  HAL_RTC_GetAlarm(&__hrtc, &sAlarm,&counter,  RTC_FORMAT_BIN) == HAL_OK){
        ret = 1;
        (*hours) = sAlarm.AlarmTime.Hours;
        (*minutes) = sAlarm.AlarmTime.Minutes;
        (*seconds) = sAlarm.AlarmTime.Seconds;
    }
    return ret;

}

void simo_rtc_write_backup_reg(uint32_t addres_reg,uint32_t data){
   if(addres_reg <= SIMO_NUM_BACK_REGISTER )HAL_RTCEx_BKUPWrite(&__hrtc, addres_reg,data);
}

uint32_t simo_rtc_read_backup_reg(uint32_t addres_reg){
uint32_t data = 0;
   if(addres_reg <= SIMO_NUM_BACK_REGISTER ){
       data = HAL_RTCEx_BKUPRead(&__hrtc, addres_reg);
   }

  return data;
}