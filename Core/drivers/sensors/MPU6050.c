

#include "main.h"

#include "i2c.h"
#include "mpu6050.h"


#define NAME_ACCELEROMETER                      "mpu6050"
#define USE_CALLBACK                             (0x00)  //! No modificar, codigo imcompatible con i2c irq


#define accelerometer_ADDR                       0x68
#define accelerometer_I2C_ADDR                   (accelerometer_ADDR)
#define ACELEROMETRO_ADDRESS                     (accelerometer_ADDR )
#define ACELEROMETRO_I2C                         I2C_A
#define ACELEROMETRO_SPEED                       (50000)
#define ACELEROMETRO_7BITS_ADDRESS               (1)
#define ACELEROMETRO_TIMEOUT                     (500)



// BIT(x) regresa el bit x puesto a uno y los demas bits en cero, ej. BIT(3) regresa 00001000
#define BIT(x)               (1<<(x))
// BIT_GET(x,b) regresa el bit b-esimo de x ej. BIT_GET(PINC,3)
#define BIT_GET(x,b)   ((x) & BIT(b))
// BIT_SET(x,b) establece en '1' el bit b de x ej. BIT_SET(PORTD,4)
#define BIT_SET(x,b)   ((x) |= BIT(b))
// BIT_CLEAR(x,b) establece a '0' el bit b de x
#define BIT_CLEAR(x,b) ((x) &= ~BIT(b))
// BIT_TOGGLE(x,b) invierte el valor del bit b de x a su complemento,
#define BIT_TOGGLE(x,b)  ((x) ^= BIT(b))
// BIT_WRITE(x,b,v) establece el valor 'v' de
#define BIT_WRITE(x,b,v) ((v)? BIT_SET(x,b) : BIT_CLEAR(x,b))
 
// ES_PAR(x) regresa 0 cuando x no es par y algo diferente de 0 cuando es par
#define ES_PAR(x) (!BIT_GET(x,0))
 





/**
 * @brief Registro SMPLRT_DIV[7:0]
 * 
 *  Divisor de frecuencia del sensor      Frecuencia de funcionamiento = 1/(1 + SMPLRT_DIV)
 *        
 */
#define SMPLRT_DIV                                  (0x19)


/**
 * @brief Registro CONFIG
 *
 *     Configura la syncronizacion externa y el filtro digital. No lo utilizare
 *       |   X    |    X    |    EXT_SYNC_SET[2:0]    |   DLPF_CFC[2:0] |  
 *  
 */
#define CONFIG                                      (0X1A)


/**
 * @brief  Registro de configuracion de GYRO
 *      Configuramos el sensor giroscopio
 *      |  XG_ST  |  YG_ST  |  ZG_ST  |    FS_SEL[1:0]    |  x  |  x  |  x  |
 * 
 */
#define GYRO_CONFIG                                 (0x1B)


/**
 * @brief  Registro de configuracion de GYRO
 *      Configuramos el sensor giroscopio
 *      |  XA_ST  |  YA_ST  |  ZA_ST  |    AFS_SEL[1:0]    |  x  |  x  |  x  |
 * 
 * 
 *   Elegir escala del sensor
 * 
 *  AFS_SEL[1:0]:
 *          +- 2G     == 0
 *          +- 4G     == 1
 *          +- 8G     == 2
 *          +- 16G    == 3
 * 
 */
#define ACCEL_CONFIG                                 (0x1C)



/**
 * @brief Habilitacion de FiFo
 * Habilitacion de FIFO
 *      |  FIFO_TEMP | FIFO XG_EN | FIFO YG_EN | FIFO ZG_EN | FIFO ACCEL_EN | SLV2_FIFO_EN | SLV1_FIFO_EN | SLV0_FIFO_EN |  
 * 
 
 */
#define FIFO_EN                                      (0x23)



/**
 * @brief Pin de interrupcion config
 * Configuramos el pin de interrupciones
 * 
 *      | INT_LEVEL | INT_OPEN |  LATCH_INT_EN  | INT_RD_CKEAR | FSYNC_INT LEVEL | FSYNC_INT EN | I2C_BYPASS_EN |  X  |
 * 
 
 */
#define INT_PIN_CFG                                   (0x37)


/**
 * @brief  Configuracion de interrupciones
 * 
 *  |  x  |  x   |  x   |  FIFO_OVERFLOW_EN |    I2C_MASTER_EN    |    X    |     X    | DATA_READY_EN   |
 * 
 
 */
#define INT_ENABLE                                     (0x38)



/**
 * @brief  Leer el estatus de la  interrupciones
 * 
 *  |  x  |  x   |  x   |  FIFO_OVERFLOW_STATUS |    I2C_MASTER_STATUS    |    X    |     X    | DATA_READY_STATUS   |
 * 
 */
#define INT_STATUS                                     (0x3A)



/**
 * @brief  Lectura de sensor Acelerometro. Parte Alta
 * 
 *              ACCEL_XOUT_H[7:0]
 * 
 */
#define ACCEL_XOUT_H                                    (0x3B)

/**
 * @brief  Lectura de sensor Acelerometro. Parte Baja
 * 
 *              ACCEL_XOUT_H[7:0]
 * 
 */
#define ACCEL_XOUT_L                                    (0x3C)


/**
 * @brief  Lectura de sensor Acelerometro. Parte Alta
 * 
 *              ACCEL_XOUT_H[7:0]
 * 
 */
#define ACCEL_YOUT_H                                    (0x3D)


/**
 * @brief  Lectura de sensor Acelerometro. Parte Alta
 * 
 *              ACCEL_YOUT_H[7:0]
 * 
 */
#define ACCEL_YOUT_L                                    (0x3E)


/**
 * @brief  Lectura de sensor Acelerometro. Parte Alta
 * 
 *              ACCEL_XOUT_H[7:0]
 * 
 */
#define ACCEL_ZOUT_H                                   (0x3F)


/**
 * @brief  Lectura de sensor Acelerometro. Parte Baja
 * 
 *              ACCEL_XOUT_H[7:0]
 * 
 */
#define ACCEL_ZOUT_L                                    (0x40)


/**
 * @brief  Lectura de sensor Temperatura. Parte Alta
 * 
 *              TEMP_XOUT_H[7:0]
 * 
 */
#define TEMP_OUT_H                                    (0x41)


/**
 * @brief  Lectura de sensor Temperatura. Parte Baja
 * 
 *              TEMP_OUT_H[7:0]
 * 
 */
#define TEMP_OUT_L                                     (0x42)

/**
 * @brief Señal de reset
 * 
 *          |                       X[7:3]            |    RESET GYRO     |     RESET ACCEL     |   RESET TEMP   |             |
 * 
 */
#define SIGNAL_PATH_RESET                              (0x68)




/**
 * @brief  User_ctrl. Configuracion de usuario
 * 
 * 
 *          |  x   |  FIFO_EN  | I2C_MST_EN  |  I2C_IF_DIS  |  X  |   FIFO_RESET  |  I2C_MST_RESET  |  SIG_COND_RESET  |
 * 
 */
#define USER_CTRL                                            (0x6A)


/**
 * @brief Power manager 1 .
 * 
 *      | DEVICE RESET |    SLEEP  |   CYCLE  |       X    |   TEMP_DIS   |  CLK_SELEC[2:0]   |
 * 
 *  valor de reset 0x40
 */
#define PWR_MGMT_1                                            (0x6B)



/**
 * @brief   Power manager 2 
 *     |    LP_WAKE_CTRL[1:0]    |   STBY_XA  |  STBY_YA  |    STBY_ZA     | STBY_XG   | STBY_YG |  STBY_ZG   |
 * 
 */
#define PWR_MGMT_2                                            (0x6C)





/**
 * @brief who_am_i
 * Registro para consulta disponibilidad del sensor
 * 
 *          |     WHO_AM_I[6:1]                        |
 * 
 * Valor de reset     0x68
 */


#define MPU_WHO_IAM                         (0x75) //! Valor predeterminado 0x70


// OFFSET
#define XA_OFFS_H                           (0x06)        
#define XA_OFFS_L                           (0x07)              
#define YA_OFFS_H                           (0x08)              
#define YA_OFFS_L                           (0x09)              
#define ZA_OFFS_H                           (0x0A)              
#define ZA_OFFS_L                           (0x0B)     


static uint8_t __MPU6050_read(uint8_t reg, uint8_t* value){

    //Modificamos configuracion
    uint8_t ret = simo_i2c_mem_read( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (reg),
                        1,
                        value,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);
    return ret; 

}


static uint8_t __MPU6050_write(uint8_t reg, uint8_t* value){

    //Modificamos configuracion
    uint8_t ret = simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (reg),
                        1,
                        value,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);
    return ret; 

}



static uint8_t __MPU6050_read_buffer(uint8_t reg, uint8_t* buffer, uint8_t len){
    //Modificamos configuracion
    uint8_t ret = simo_i2c_mem_read( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (reg),
                        1,
                       buffer,
                        len,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);
    return ret; 

 }




static uint8_t __MPU6050_write_buffer(uint8_t reg, uint8_t* buffer, uint8_t len){
    //Modificamos configuracion
    uint8_t ret = simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (reg),
                        1,
                       buffer,
                        len,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);
    return ret; 

 }

/**
 * @brief Configuramos la escala de medicion
 * 
 * @param scala    valores validos 0 ,1 ,2 ,3
 * @return ** uint8_t 
 */
static uint8_t  __MPU6050_set_scala( uint8_t scala){

    uint8_t value = 0;

    switch (scala)
    {
    case 0: // escala +- 2G
        // value = 0;
        break;
    
    case 1: // escala +- 4G
        BIT_SET(value,3);   // value = 0000 1000
        break;
        
    case 2: // escala +- 8G // value = 0001 0000
        BIT_SET(value,4);
        break;
    case 3: // escala +- 16G
        BIT_SET(value,3);
        BIT_SET(value,4);   // value = 0001 1000
        break;

    default:
        //escala +_ 2G
        //value = 0;
        break;
    }

    //Modificamos configuracion

   uint8_t ret = __MPU6050_write(ACCEL_CONFIG,&value); 

    return ret; 
}


static uint8_t __MPU6060_set_int_pin(){
    uint8_t value = 0;
   // BIT_SET(value,7); // si es 1 , el nivel logico de la int es bajo
   // BIT_SET(value,6); // Si es 1, es open_drain, si es 0 push pull
   // BIT_SET(value,5); // si es 1 el valor del pin en interrupcion es retenido hasta clear, sino solo retinee 50uS
    BIT_SET(value,4); // si es 1, el valor del int status sera limpiado con cualquier operacion de lectura 
    // BIT_SET(value,3); // si es 1 el nivel logico de FSYNC PIN ES BAJO,SI ES 0 entones es ALTO
    // BIT_SET(value,2); // FSYNC INT ENABLE. Con 0 esta deshabilitado
    // BIT_SET(value,1); utilizado es usos complejos del sensor
}




void MPU6050_init(void){

}



void MPU6050_deinit(){

}


void MPU6050_reset(){

}


uint32_t  MPU6050_check(void){

}


void MPU6050_resume(void){

}

void MPU6050_sleep(void){

}

void MPU6050_set_sample_div(uint8_t freq_div){

    uint8_t value = freq_div;
    __MPU6050_write(SMPLRT_DIV,&value);

}



uint32_t MPU6050_get_aceleration(int16_t* x, int16_t* y , int16_t* z){

    uint8_t buffer[6] = {0};
    uint8_t ret = __MPU6050_read_buffer(ACCEL_XOUT_H,buffer,6);

    
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*x) = (int16_t)(buffer[0] << 8 | buffer[1]);   
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*y) = (int16_t)(buffer[2] << 8 | buffer[3]);
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*z) = (int16_t)(buffer[4] << 8 | buffer[5]);

    return ret;

}



void MPU6050_calibration(){
    return 0;
}


uint32_t MPU6050_set_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset){
    return 0;
}


uint32_t MPU6050_get_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset){


     uint8_t buffer[6] = {0};
    uint8_t ret = __MPU6050_read_buffer(XA_OFFS_H,buffer,6);

    
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*x_offset) = (int16_t)(buffer[0] << 8 | buffer[1]);   
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*y_offset) = (int16_t)(buffer[2] << 8 | buffer[3]);
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*z_offset) = (int16_t)(buffer[4] << 8 | buffer[5]);






    return 0;
}


uint8_t MPU6050_get_measure(char* buffer, uint8_t len){
    return 0;
}
