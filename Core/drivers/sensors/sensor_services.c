#include "sensor_services.h"
//#include "accelerometer.h"
#include "debug.h"
#include "mpu6050.h"
#include "sensor_fake.h"   // sensor de prueba imaginario
#include "batery.h"
#define SERVICES_READY                    "Sensors services READY"
#define SERVICES_ERROR                     "Sensors services ERROR"


#define  LEN_MAX_BUFFER                          (255)

#define __ACCELEROMETER_ON__                    (1)           

#define __CALIBRATION_ON__                      (0)

#define __SIM7000G_ON__                         (0)

#define __BATERY_LEVEL_ON__                       (1)


#define __SENSOR_FAKE_ON__                      (0)





 // Configuracion del SIM7000G
#define MQTT_TOPIC                 "X1111"
#define MQTT_BROKER2               "simointi.cloud.shiftr.io"
#define MQTT_PASS                  "fdZY5b69OhOVsAns"
#define MQTT_ID                    "simointi"
#define MQTT_QOS                    "0"



static uint32_t __init_sensors(){
    uint32_t ret = 0;
    //Iniciamos el acelerometro
    #if (__ACCELEROMETER_ON__ == 1)                 
        
        ret = ACCEL_init();

        #if (__CALIBRATION_ON__ == 1)        
            
            ACCEL_calibration();
            //accelerometer_calibration();
        #endif
    #endif


    #if (__BATERY_LEVEL_ON__ == 1)

        batery_level_init();
        
    #endif


//Iniciamos el SENSOR IMAGINARIO
    #if (__SENSOR_FAKE_ON__ == 1)                 
        sensor_fake_init();
        ret = sensor_fake_check();
  
        #if (__CALIBRATION_ON__ == 1)        
        sensor_fake_calibration();
        #endif
    #endif



    #if (__SIM7000G_ON__ == 1)      
        sim_init();    
        sim_get_default();
        sim_set_echo(0);
        sim_set_pwr_gps(1);
        sim_get_operator();
        sim_get_signal_level();
        sim_open_apn();
        ret =  sim_config_mqtt(MQTT_BROKER2,MQTT_ID,MQTT_PASS,MQTT_QOS);
              
        #if (__CALIBRATION_ON__ == 1)        
        #endif
    
    #endif
    return ret;
}



static void __deinit_sensors(){
    #if (__ACCELEROMETER_ON__ == 1)        
        //accelerometer_deinit();

        ACCEL_deinit();
    #endif

}


uint32_t sensor_services_init(void){
    uint32_t ret = __init_sensors();
    if(ret == 1)debug_print(SERVICES_READY);

    return ret;
}


void sensor_services_deinit(void){
    __deinit_sensors();
}


uint32_t sensor_services_check(char* buffer){
    uint32_t ret = 0;

    #if (__ACCELEROMETER_ON__ == 1)        
         ret = ACCEL_get_measure(buffer, LEN_MAX_BUFFER);
    #endif

    #if (__SENSOR_FAKE_ON__ == 1)
        ret = sensor_fake_get_measure(buffer,LEN_MAX_BUFFER); // 
    #endif
    #if (__BATERY_LEVEL_ON__ == 1)
        ret = batery_level_get_measure(buffer,LEN_MAX_BUFFER); // 
    #endif

   return ret;

}

