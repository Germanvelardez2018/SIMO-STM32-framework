#include "batery.h"
#include "gpio.h"

#include "adc.h"
#include "delay.h"


#define BATTERY_OK                      "BATT OK "
#define BATTERY_LOW                     "BATT LOW"
#define MIN_LEVEL                       (2.5)    // DEBAJO DE LOS 2.5 BATERY LOW
#define BATERRY_MIN_LEVEL                 3103  //(MIN_LEVEL / 3.3) * 4096     // 3.3V

#define FORMAT_BATT_SIZE                 strlen(BATTERY_OK)

#define PIN_BATTERY_LEVEL               (SIMO_GPIO_0)         //PA0
#define DELAY_CONVERTION                (50)


/**
 * @brief Inicio el hardware necesario para manejar acelerometro (I2C)
 * 
 * @return ** void 
 */
void batery_level_init(void){
    simo_adc_init(ADC_A,CHANNEL_0,ADC_TIGGER_SOFTWARE);
}



/**
 * @brief Desactivar el hardware
 * 
 * @return ** void 
 */
void batery_level_deinit(){
    simo_adc_deinit(ADC_A);
}




static uint32_t __baterry_level_get_measure(){ 
    uint32_t ret = 0;
    // si medicion de batery es correcta devuelvo 1 sino 0
    simo_adc_start(ADC_A,0);
    simo_delay_ms(DELAY_CONVERTION);
    uint32_t value = simo_adc_get_value(ADC_A);

    ret = ( value > (uint32_t)BATERRY_MIN_LEVEL ? 1: 0 ); // 0 bateria baja, 1 bateria ok
    return ret ;
}

uint32_t  batery_level_get_measure(char* buffer, uint8_t len_max)
{
     
    #define BATERY_LEVEL_FORMAT          "BATERY LEVEL:\r\n\t %s \r\n" 
    // si tengo espacion en buffer agrego
    uint8_t ret = 0;
    char buff[100];
    uint8_t last_pos = strlen(buffer);
 

    if( (len_max - last_pos)   > ((uint8_t) strlen(BATERY_LEVEL_FORMAT) + FORMAT_BATT_SIZE))
    {

        int index = __baterry_level_get_measure(); // 1 o 0
        sprintf((buffer+last_pos),BATERY_LEVEL_FORMAT,index ? BATTERY_OK: BATTERY_LOW);    
        ret = 1; // se grabo la nueva info
    }


    return ret; // devuelve la ultima posicion utilizada del array

}









