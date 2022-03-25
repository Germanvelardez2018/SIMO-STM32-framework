#include "power_modes.h"
#include "main.h"
#include "rtc.h"






callback_irq __IRQ_POWER_MODE_EXIT__ = NULL ;

static pwr_modes _DEV_PWR_MODE_ = RUN_MODE; //! Por defecto






pwr_modes power_mode_get_state(void){
    return _DEV_PWR_MODE_;
}





void power_mode_set_callback(callback_irq callback){
    if(callback != NULL) __IRQ_POWER_MODE_EXIT__ = callback;
}





 void power_mode_get_callback(void){
    HAL_ResumeTick();
    if(__IRQ_POWER_MODE_EXIT__ != NULL)  __IRQ_POWER_MODE_EXIT__();
;
    
}




void power_mode_set( pwr_modes mode){

    switch (mode)
    {
        case RUN_MODE:
        HAL_ResumeTick();
        _DEV_PWR_MODE_ = RUN_MODE;

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