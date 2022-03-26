#include "power_modes.h"
#include "main.h"
#include "rtc.h"



static pwr_modes _DEV_PWR_MODE_ = RESUMEN_RUN; //! Por defecto






pwr_modes power_mode_get_state(void){
    return _DEV_PWR_MODE_;
}











void power_mode_set( pwr_modes mode){

    switch (mode)
    {
        case RESUMEN_RUN:
        HAL_ResumeTick();
        _DEV_PWR_MODE_ = RESUMEN_RUN;

        break;

        case SLEEP_MODE:
        HAL_SuspendTick();
        _DEV_PWR_MODE_ = SLEEP_MODE;
        HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
        break;


        case SLEEP_ONLY_ISR_MODE:
        HAL_SuspendTick();
        _DEV_PWR_MODE_ = SLEEP_ONLY_ISR_MODE;
        HAL_PWR_EnableSleepOnExit ();
        break;


        case STOP_MODE:
        HAL_SuspendTick();
        _DEV_PWR_MODE_ = STOP_MODE;
        HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
        break;


    case STANDBY_MODE:      
        /* Now enter the standby mode **/
        /* Clear the WU FLAG */
      //  __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
        /* clear the RTC Wake UP (WU) flag */
      //  __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
         /* Habilitar el PIN DE ACTIVACIÓN */ 
        HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
        HAL_SuspendTick();
        _DEV_PWR_MODE_ = STANDBY_MODE; //! Realmente no importa xq al despertar la sram esta limpia
        HAL_PWR_EnterSTANDBYMode();


        break;
    
    default:

        break;
    }
}