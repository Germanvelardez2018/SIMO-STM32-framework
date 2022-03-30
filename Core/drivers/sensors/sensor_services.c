#include "sensor_services.h"
#include "accelerometer.h"

#define __ACCELEROMETER_ON__               (1)           

#define __CALIBRATION_ON__                 (0)

static uint32_t __init_sensors(){
    uint32_t ret = 0;
    //Iniciamos el acelerometro
    #if (__ACCELEROMETER_ON_ == 1)                 
        accelerometer_init();
        ret = accelerometer_check();
      //  accelerometer_sleep(0);
        accelerometer_set_sample_div(7); //1khz
        #if (__CALIBRATION_ON_ == 1)        
        accelerometer_calibration();
        #endif
    
    #endif
    // podria calibrar?
    return ret;
}



static void __deinit_sensors(){
    #if (__ACCELEROMETER_ON_ == 1)        
        accelerometer_deinit();
    #endif

}


uint32_t sensor_services_init(void){
    return __init_sensors();
}


void sensor_services_deinit(void){
    __deinit_sensors();
}


uint32_t sensor_services_check(char* buffer, uint8_t len){
    uint32_t ret = 0;
    #if (__ACCELEROMETER_ON_ == 1)        
       // accelerometer_sleep(0);  //! Sleep OFF
         ret =  accelerometer_get_measure(buffer,len);
       // accelerometer_sleep(1); // ! Sleep ON
    #endif
   return ret;

}

