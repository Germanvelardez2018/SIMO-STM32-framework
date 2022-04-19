#include "sensor_fake.h"




/**
 * @brief Inicio el hardware necesario para manejar acelerometro (I2C)
 * 
 * @return ** void 
 */
void sensor_fake_init(void){
    }


/**
 * @brief Desactivar el hardware
 * 
 * @return ** void 
 */
void sensor_fake_deinit(){
    }








void  sensor_fake_calibration(){

}





/**
 * @brief Reset la configuracion
 * 
 * @return ** void 
 */
void sensor_fake_reset(){

 }
/**
 * @brief Revisar disponibilidad del sensor
 * 
 * @return ** uint32_t 
 */
uint32_t  sensor_fake_check(void){
    return 1; // SIEMPRE OK
    }



/**
 * @brief Poner en modo sleep el sensor
 * 
 * @param sleep 
 * @return ** void 
 */
void sensor_fake_sleep(uint32_t sleep){

    }







/**
 * @brief 
 * 
 * @param buffer 
 * @param len 
 * @return ** uint32_t 
 */
uint8_t sensor_fake_get_measure(char* buffer, uint8_t len_max){

    #define PRINT_FAKE          "SENSOR FAKE:\r\n\tMEDICION CORRECTA \r\n" 
    // si tengo espacion en buffer agrego
    uint8_t ret = 0;
    char buff[100];
    uint8_t last_pos = strlen(buffer);
 

    if( (len_max - last_pos)   > ((uint8_t) strlen(PRINT_FAKE)))
    {

        sprintf((buffer+last_pos),"%s",PRINT_FAKE);    
        ret = 1; // se grabo la nueva info
    }


    return ret; // devuelve la ultima posicion utilizada del array

   }
