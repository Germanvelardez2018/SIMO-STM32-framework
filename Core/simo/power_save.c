/**
 * @file power_save.c
 * @author German Velardez (velardezgerman16@gmail.com)
 * @brief  Driver para abstraer las funciones de power save en micros ARM
 * @version 0.1
 * @date 2022-01-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "power_save.h"

typedef enum
{
    NORMAL //! Modo de funcionamineto normal
    ,
    SLEEP //!  CPU apagado perifericos encendidos
    ,
    STOP //!  CPU y perifericos apagados, backup de registros
    ,
    STANDBY //!  APAGAMOS TODO

} simo_pwd_mode;

/* Low Power modes configuration functions ************************************/

//  PWR_SLEEPENTRY_WFI              COnfigura el micro para salir de sleep mode mediante IT
//  PWR_SLEEPENTRY_WFE              COnfigura el micro para salir de sleep mode mediante EVENT

#define SIMO_PWR_SLEEP_MODE PWR_SLEEPENTRY_WFI
#define SIMO_PWR_STOP_MODE PWR_STOPENTRY_WFI

//! Solo se usa este parametro en ST serie L
// PWR_LOWPOWERREGULATOR_ON
#define SIMO_PWR_REGULARO_PARAM PWR_LOWPOWERREGULATOR_ON

#define _SIMO_PWR_BEFORE_SLEEP_             HAL_SuspendTick()
#define _SIMO_PWR_AFTER_SLEEP_              HAL_ResumeTick()

//! Esta rutina vuelve a configurar el micro.
// Se utiliza para configurar el micro despues de un modo de funcionamiento de bajo consumo superior a sleep
static setup_config __SETUP__;

static simo_pwd_mode __MODE__;

void simo_pwr_set_initial_config(setup_config setup){
    if (setup != NULL) __SETUP__ = setup; // En modo sleep no es necesario volver a configurar
}

void simo_pwr_before_change_mode(){
    _SIMO_PWR_BEFORE_SLEEP_;
}

void simo_pwr_return_normal_mode(){
    _SIMO_PWR_AFTER_SLEEP_;
    if ((__SETUP__ != NULL) & ((__MODE__ != SLEEP) & (__MODE__ != NORMAL)))__SETUP__();
    __MODE__ = NORMAL;
}




void simo_pwr_sleep_only_isr(uint32_t ena){
    if (ena == 0){
        HAL_PWR_DisableSleepOnExit();
    }
    else{
        HAL_PWR_EnableSleepOnExit();
    }
}



void simo_pwr_enter_sleep_mode(){
    __MODE__ = SLEEP;
    simo_pwr_before_change_mode();
    HAL_PWR_EnterSLEEPMode(SIMO_PWR_REGULARO_PARAM, SIMO_PWR_SLEEP_MODE);
}

void simo_pwr_enter_stop_mode()
{
    __MODE__ = STOP;
    simo_pwr_before_change_mode();
    HAL_PWR_EnterSTOPMode(SIMO_PWR_REGULARO_PARAM, SIMO_PWR_STOP_MODE);
}

void simo_pwr_standby_mode()
{
    __MODE__ = STANDBY;

    simo_pwr_before_change_mode();
    HAL_PWR_EnterSTANDBYMode();
}
