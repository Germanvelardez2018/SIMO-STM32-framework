#include "sensor_services.h"
#include "mpu_6500.h"




static uint32_t __init_sensors(){
    uint32_t ret = 0;
    //Iniciamos el acelerometro
    accelerometer_init();
    ret = accelerometer_check();
    accelerometer_sleep(0);
    accelerometer_set_sample_div(7); //1khz

    // podria calibrar?



    return ret;
}



static void __deinit_sensors(){


    accelerometer_deinit();

}


uint32_t sensor_services_init(void){
    __init_sensors();
    return 0;

}


void sensor_services_deinit(void){

    __deinit_sensors();

}


uint32_t sensor_services_check(char* buffer, uint8_t len){



   uint32_t ret =  accelerometer_get_measure(buffer,len);

   return ret;

}

