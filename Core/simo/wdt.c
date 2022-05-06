#include "wdt.h"
#include "stm32f1xx_hal_iwdg.h"

// Contador de 12 bits


static IWDG_HandleTypeDef __hiwdg;



static void  __set_parameter(WDT_PRE pre, uint32_t reload){

    switch (pre)
    {
    case WDT_PRE_4:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_4 ;
        break;

    case WDT_PRE_8:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_8 ;
        break;

    case WDT_PRE_16:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_16 ;
        break;

    case WDT_PRE_32:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_32 ;
        break;

    case WDT_PRE_64:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_64 ;
        break;

    case WDT_PRE_128:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_128 ;
        break;

    case WDT_PRE_256:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_256 ;
        break;
    
    default:
        __hiwdg.Init.Prescaler = IWDG_PRESCALER_256 ;

        break;
    }
    __hiwdg.Init.Reload = reload;

}



uint32_t  simo_wdt_init(uint32_t reload_value, WDT_PRE prescaler ){
    uint32_t ret = 0;
    __hiwdg.Instance = IWDG;
    __set_parameter(prescaler,reload_value);
      if (HAL_IWDG_Init(&__hiwdg) == HAL_OK)
  {
     ret = 1;
  }
  return ret;
}



 void simo_wdt_refresh(void){
    HAL_IWDG_Refresh(&__hiwdg);
}

