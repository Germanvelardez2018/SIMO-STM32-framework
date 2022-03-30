




#include "accelerometer.h"
#include "main.h"

#include "i2c.h"



#define accelerometer_ADDR                       0xD0
#define accelerometer_I2C_ADDR                   (accelerometer_ADDR)
#define ACELEROMETRO_ADDRESS                     (accelerometer_ADDR )
#define ACELEROMETRO_I2C                         I2C_A
#define ACELEROMETRO_SPEED                       (50000)
#define ACELEROMETRO_7BITS_ADDRESS               (1)
#define ACELEROMETRO_TIMEOUT                     (1000)



// Registers



// OFFSET GYROSCOPIO
#define OFFSET_GXH                              (0x13)
#define OFFSET_GXL                              (0x14)
#define OFFSET_GYH                              (0x15)
#define OFFSET_GYL                              (0x16)
#define OFFSET_GZH                              (0x17)
#define OFFSET_GZL                              (0x18)
#define DIV_FREQ_SAMPLE                         (0x19) //! SAMṔLE RATE = INTERNAL SAMPLE /(1+DIV_SAMPLE)
// OUTPUTS
#define ACCEL_XOUT_H                             (0x3B)
#define ACCEL_XOUT_L                             (0x3C)
#define ACCEL_YOUT_H                             (0x3D)
#define ACCEL_YOUT_L                             (0x3E)
#define ACCEL_ZOUT_H                             (0x3F)
#define ACCEL_ZOUT_L                             (0x40)
#define ACCEL_TOUT_H                             (0x41)
#define ACCEL_TOUT_L                             (0x42)



//CONFIGURACION
#define CONFIG                                  (0x1A)

/**
 * @brief REGISTRO CONFIG
 * 
 *          |               |     EXT_SYNC_SET [2:0]          |      FIFO_MODE( 1 == ON)     | 7(RESERVADO) |
 */



#define GYRO_CONFIG                            (0x1B)
/**
 * @brief GIRO FULLL SCALE SELECT 
 *  2 BITS    [4:3]
 *      00 = ±250dps
        01=  ±500dps
        10 = ±1000dps
        11 = ±2000dps
 */



#define ACCEL_CONFIG                            (0x1C)
/**
 * @brief ACCELEROMETER FULLL SCALE SELECT 
 *  2 BITS    [4:3]
 *      00 = +-2G
        01=  +-4G
        10 = +-8G
        11 = +-16G
 */




#define ACCEL_LOWPOWER_CONTROL                      (0x1E)
/**
 * @brief  [3:0] bits de configuracion de la frecuencia en bajo consumo
 * |bits| salida de frecuencia | 
 *  0   |     0.24
    1   |     0.49
    2   |     0.98
    3   |     1.95
    4   |     3.91
    5   |     7.81
    6   |     15.63
    7   |     31.25
    8   |     62.50
    9   |     125
    10  |     250
    11  |     500
    12  |     15 Reserved
 * 
 */

#define WAKEON_MOTIONTHRESHOLD              (0x1F)
/**
 * @brief Este valor tiene el umbral para que 
 *          la interrupcion en aceleracion se accione
 * LSB= 4mg.
 * el rango es de 0mg a 1020mg
 * 
 */



#define FIFO_ENA                                    (0x23)
#define INT_CONFIG                                  (0x37)
/**
 * @brief  Configuracion de interrupcion
 *  | ACTL[7]   |   OPEN[6] |   LATCH_INT_EN[5] |   INT_ANY_RD_CLEAR[4] |
 *  | ACTL_FSYNC[3]| FSYNC_INT_MODE_EN[2] | BYPASS_EN[1] | RESERVADO [0]
 
 */

#define INT_ENABLE                                   (0x38)
/**
 * @brief  Habilitaciones de interrupcion
 * 
 *   |RESERVADO [7] | WAKE MOTION INT EN[6] |
 *   | RESERVADO[5] | FIFO_OVERFLOW[4]      |
 *   |FSYNC_INT_EN[3] |   RESERVADOR[2:1]   |
 *   |RAW_RDY_ENA[0]    
 
 */

#define INT_ENABLE                                   (0x3A)
/**
 * @brief  Habilitaciones de interrupcion
 * 
 *   |RESERVADO [7]   | WAKE MOTION INT EN[6] |
 *   | RESERVADO[5]   |   FIFO_OVERFLOW[4]    |
 *   | FSYNC_INT[3]   |
 *   |  DMP_INT[2]    |   RESERVADOR[1]       |
 *   |RAW_RDY_INT[0]  |   
 
 */

#define ACCEL_INTEL_CTRL                                (Ox69)
/**
 * @brief  Habilitaciones de interrupcion
 * 
 *   | ACCEL_INTEL_EN [7] | ACCEL_INTEL_MODE[6] |
 *  ACCEL_INTEL_EN EN 1 habilita la deteccion de movimiento (wakeOnMotion logic)
 * 
 */


#define USER_CTRL                                       (0x6A)
/**
 * @brief 
*       DMP_EN                  | habilita DMP 
*       FIFO_EN                 | habilita FIFO
*       I2C_MST_EN              | habilita modo maestro i2c
        I2C_IF_DIS              |
        DMP_RST 
        FIFO_RST                | Resetea la FIFO
        I2C_MST_RST
        SIG_COND_RST
 * 
 */


#define PWR_MGMT_1                              (0x6A)
/**
 * @brief power manager 1
 *  | Reset[7]      Resetea todo los registros si escribimos un 1. Autoclear
 *  | SLEEP[6]      Modo SLEEP con un 1.
 *  | CYCLE[5]      
 *  | GYRO_STANDBY[4]  
 *  | TEMP_DIS      SI esta en 1, se apaga sensor de temperatura
 *  | clksel[2:0]
 *              0   Internal 20MHz oscillator
                1   Auto selects the best available clock source – PLL if ready, else
                    use the Internal oscillator
                2   Auto selects the best available clock source – PLL if ready, else
                    use the Internal oscillator
                3   Auto selects the best available clock source – PLL if ready, else
                    use the Internal oscillator
                4   Auto selects the best available clock source – PLL if ready, else
                   use the Internal oscillator
                5  Auto selects the best available clock source – PLL if ready, else
                   use the Internal oscillator
                6  Internal 20MHz oscillator
                7  Stops the clock and keeps timing generator in reset
 * 
 */ 
#define PWR_MGMT_2                              (0x6B)
/**
 * @brief 
*   [7:6] LP_WAKE_CTRL[1:0] Specifies the frequency of wake-ups during Accelerometer Only Low Power
                            Mode.
    [5] DISABLE_XA
                            1 – X accelerometer is disabled
                            0 – X accelerometer is on
    [4] DISABLE_YA
                            1 – Y accelerometer is disabled
                            0 – Y accelerometer is on
    [3] DISABLE_ZA
                            1 – Z accelerometer is disabled
                            0 – Z accelerometer is on
    [2] DISABLE_XG
                            1 – X gyro is disabled
                            0 – X gyro is on
    [1] DISABLE_YG
                            1 – Y gyro is disabled
                            0 – Y gyro is on
    [0] DISABLE_ZG
                            1 – Z gyro is disabled
                            0 – Z gyro is on
 */


#define FIFO_COUNT_H                        (Ox72)  //! {0:4] parte alta de contador
#define FIFO_COUNT_L                        (0x73) //! 0:8 parte baja del contador
#define FIFO_R_W                            (0x74)  //! Dirreccion de escritura o lectura de FIFO

#define MPU_WHO_IAM                         (0x75) //! Valor predeterminado 0x70
#define accelerometer_USE_I2C


#define XA_OFFS_H                           (0x77)        
#define XA_OFFS_H                           (0x78)              
#define YA_OFFS_H                           (0x7A)              
#define YA_OFFS_H                           (0x7B)              
#define ZA_OFFS_H                           (0x7D)              
#define ZA_OFFS_H                           (0x7E)              
#define XA_OFFS_H                           (0x77)              
#define XA_OFFS_H                           (0x77)              
#define XA_OFFS_H                           (0x77)              

#define USE_CALLBACK                         (0x00)  //! No modificar, codigo imcompatible con i2c irq


//! Configuracion de freq de muestreo en bajo consumo
typedef enum 
{
     LOW =0        //!    0.24 Hz (  0  )
    ,MEDIUM= 7     //!    41.25Hz (  7  )
    ,HIGH = 11    //!    500Hz   ( 11  )


}_FREQ_LOWPWR;



/**
 * @brief Configura la frecuencia de muestreo en modo sleep
 * 
 * @param freq 
 * @return ** void 
 */

void __mpu6500_set_lposc(_FREQ_LOWPWR freq){

     int8_t config = freq;
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (ACCEL_LOWPOWER_CONTROL),
                        1,
                        &config,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);

}



void __mpu6500_config_sensors(int32_t off){
     int8_t old_config =0;

    // Leemos configuracion
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      PWR_MGMT_2,1,&old_config,1,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);

    int8_t config = 0;
        if (off!= 0){
        config = old_config | 0x3F;//disabled
        }
        else{
        config = old_config & 0xC0;  //  enabled 1100 0000 
        }

    //Modificamos configuracion
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (PWR_MGMT_2),
                        1,
                        &config,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);


}

void accelerometer_reset(){


     int8_t old_config =0;

    // Leemos configuracion
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      PWR_MGMT_1,1,&old_config,1,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);

    int8_t config =old_config| (1 << 7); // 1 en bit7, reseteo
       
    //Modificamos configuracion
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (PWR_MGMT_1),
                        1,
                        &config,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);

}








/**
 * @brief Para calibrar de manera horizontal
 *      -aceleración: p_ax=0 , p_ay=0 , p_az=+16384

        -Velocidad angular: p_gx=0 , p_gy=0 , p_gz=0
        Estas son las medidas deseada que debemos tener
 * 
 */




// x = 0 , y= 0 z= 16384

static void _mpu6500_calibration(int16_t x_e, int16_t y_e, int16_t z_e){


#define TIMES       400


int16_t x,y,z ;
int16_t delta_x = 0;
int16_t delta_y = 0;
int16_t delta_z = 0;

int16_t x_offset=0;
int16_t y_offset = 0;
int16_t z_offset = 0;


for(int16_t i= 0; i< TIMES; i++){


accelerometer_get_aceleration(&x,&y,&z);

 delta_x = x_e - x;
 delta_y = y_e - y;
 delta_z = z_e - z;

// offset en cero
accelerometer_set_offset(&x_offset,&y_offset,&z_offset);
//corrijo los offset
if(delta_x !=0)x_offset = (delta_x >0)? (x_offset+1): (x_offset-1);
if(delta_y !=0)y_offset = (delta_y >0)? (y_offset+1): (y_offset-1);
if(delta_z !=0)z_offset = (delta_z >0)? (z_offset+1): (z_offset-1);
//recargo los offset
accelerometer_set_offset(&x_offset, &y_offset, &z_offset);

}




}



void accelerometer_calibration(){
    _mpu6500_calibration(0,0,16384);
}


/**
 * @brief Como implementar la rutina de bajo consumo en manual (REgsiterMap) pag 43/47
 * 
 * @return ** void 
 */


static void _mpu6500_set_scala(){
    

    uint8_t data = 0; // Escribir 0 despierta el mpu6500 y lo configura en 8Mhz
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (0x1B),
                        1,
                        &data,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (0x1C),
                        1,
                        &data,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);

}



static void  __MPU6500_init(){

    simo_i2c_init(ACELEROMETRO_I2C,ACELEROMETRO_SPEED,ACELEROMETRO_7BITS_ADDRESS);

}



static void __MPU6500_deinit(){
    simo_i2c_deinit(ACELEROMETRO_I2C);
}


void accelerometer_init(void){
    __MPU6500_init();
}


uint32_t  accelerometer_check(){

    uint32_t res = 0;
    uint8_t check = 0;
    
    
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      0x75,1,&check,1,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);
    res = (check == 0x70)?1:0;   // 1 OK, 0 ERROR, NO DISPONIBLE

    return res;
    

}

void accelerometer_sleep(uint32_t sleep){
    
    int8_t old_config =0;

    // Leemos configuracion
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      PWR_MGMT_1,1,&old_config,1,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);

    int8_t config = (sleep != 0)?   
                    (old_config| (1 << 6)) // entro en modo sleep
                     :(old_config & 0x00 ); // salgo del modo sleep
                    
    //Modificamos configuracion
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (PWR_MGMT_1),
                        1,
                        &config,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        USE_CALLBACK);


    
    if( sleep != 0){
        //wake up

    //disabled sensors
    __mpu6500_config_sensors(1);


    }
    _mpu6500_set_scala();

    
   

}




void accelerometer_set_sample_div(uint8_t freq_div){
    // Set DATA RATE of 1KHz by writing SMPLRT_DIV register in 7
    uint8_t data = freq_div;
    simo_i2c_mem_write(     ACELEROMETRO_I2C,
                            ACELEROMETRO_ADDRESS,
                            (0x19),
                            1,
                            &data,
                            1,
                            ACELEROMETRO_TIMEOUT,
                            0);

}

void accelerometer_set_config(){

}


uint32_t accelerometer_set_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset){
uint32_t res = 1;
    int8_t x_buff[2] = {0}; // h and l
    x_buff[0] = (int8_t) (*x_offset >> 8); // parte alta
    x_buff[1] = (int8_t) (*x_offset ); // parte baja

    int8_t y_buff[2] = {0}; // h and l
    y_buff[0] = (int8_t) (*y_offset >> 8); // parte alta
    y_buff[1] = (int8_t) (*y_offset ); // parte baja
    
    int8_t z_buff[2] = {0}; // h and l
    z_buff[0] = (int8_t) (*z_offset >> 8); // parte alta
    z_buff[1] = (int8_t) (*z_offset ); // parte baja



   
    simo_i2c_mem_write(     ACELEROMETRO_I2C,
                            ACELEROMETRO_ADDRESS,
                            0x77//XA_OFFSET
                            ,1,
                            x_offset,
                            2,
                            ACELEROMETRO_TIMEOUT,
                            0);
    simo_i2c_mem_write(     ACELEROMETRO_I2C,
                            ACELEROMETRO_ADDRESS,
                            0x7A//YA_OFFSET
                            ,1,
                            y_offset,
                            2,
                            ACELEROMETRO_TIMEOUT,
                            0);
    simo_i2c_mem_write(     ACELEROMETRO_I2C,
                            ACELEROMETRO_ADDRESS,
                            0x7D//ZA_OFFSET
                            ,1,
                            z_offset,
                            2,
                            ACELEROMETRO_TIMEOUT,
                            0);

return res;
}





uint32_t accelerometer_get_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset){
uint32_t res = 1;
    
    uint8_t Rec_Data[2]={0};
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      0x77//XA_OFFSET
                      ,1,&Rec_Data,2,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*x_offset) = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      0x7A //YA_OFFSET
                      ,1,&Rec_Data,2,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*y_offset) = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      0x7D //ZA_OFFSET
                      ,1,&Rec_Data,2,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);
    //! Primera posicion de memoria del vector, parte alta del int16_t
    (*z_offset) = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
return res;
}


uint32_t accelerometer_get_aceleration(int16_t* x, int16_t* y , int16_t* z){
    uint32_t ret = 0;
    // Read 6 BYTES of data starting from ACCEL_XOUT_H register
    uint8_t VALUE_ADDRESS =0x3B;
    uint8_t Rec_Data[6]={0};
    // HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, );
    ret =simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      VALUE_ADDRESS,1,&Rec_Data,6,
                      ACELEROMETRO_TIMEOUT,
                      USE_CALLBACK);
    (*x) = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
    (*y) = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
    (*z) = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

    return ret;

}




void accelerometer_deinit(){
    simo_i2c_deinit(I2C_A);

}




uint32_t accelerometer_get_measure(char* buffer, uint8_t len){

    #define format      "accelerometer: x:%3.2f-y:%.2f-z:%.2f\r\n"
    uint32_t ret = 0;
    int16_t x;
    int16_t y;
    int16_t z;
    if(accelerometer_check() == 0 ) {
        sprintf(buffer,"sensor no disponible \r\n");  
        return 0;  
    }

    ret = accelerometer_get_aceleration(&x,&y,&z);
    if(ret != 0){
        float fx = x/16384.0;  
        float fy = y/16384.0;
        float fz = z/16384.0;
        sprintf(buffer,format,fx,fy,fz);
    }
    else{
         sprintf(buffer,"error en medicion \r\n");    
    }
    ret = strlen(buffer); // devuelve la ultima posicion utilizada del array
    return ret;
}