




#include "mpu_6500.h"
#include "main.h"

#include "i2c.h"



#define MPU6500_ADDR                              0xD0
#define MPU6500_I2C_ADDR                         (MPU6500_ADDR)
#define ACELEROMETRO_ADDRESS                     (MPU6500_ADDR )
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
#define MPU6500_USE_I2C


#define XA_OFFS_H                           (0x77)        
#define XA_OFFS_H                           (0x78)              
#define YA_OFFS_H                           (0x7A)              
#define YA_OFFS_H                           (0x7B)              
#define ZA_OFFS_H                           (0x7D)              
#define ZA_OFFS_H                           (0x7E)              
#define XA_OFFS_H                           (0x77)              
#define XA_OFFS_H                           (0x77)              
#define XA_OFFS_H                           (0x77)              



/**
 * @brief Para calibrar de manera horizontal
 *      -aceleración: p_ax=0 , p_ay=0 , p_az=+16384

        -Velocidad angular: p_gx=0 , p_gy=0 , p_gz=0
        Estas son las medidas deseada que debemos tener
 * 
 */




static void _mpu6500_calibration(int16_t x_e, int16_t y_e, int16_t z_e){


int16_t x,y,z ;
mpu6500_get_aceleration(&x,&y,&z);

int16_t delta_x = x_e - x;
int16_t delta_y = y_e - y;
int16_t delta_z = z_e - z;


int16_t x_offset, y_offset, z_offset;
// leo los offset
x_offset = (delta_x >0)? (x_offset+1): (x_offset-0);
y_offset = (delta_y >0)? (y_offset+1): (y_offset-0);
z_offset = (delta_z >0)? (z_offset+1): (z_offset-0);
//recargo los offset
}




/**
 * @brief Como implementar la rutina de bajo consumo en manual (REgsiterMap) pag 43/47
 * 
 * @return ** void 
 */


static void _mpu6500_set_scala(){
    if( 1){
        //wake up

    uint8_t data = 0; // Escribir 0 despierta el mpu6500 y lo configura en 8Mhz
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (0x1B),
                        1,
                        &data,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        0);
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (0x1C),
                        1,
                        &data,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        0);

    }
    else{
        //sleep
    }

}



static void  __MPU6500_init(){

    simo_i2c_init(ACELEROMETRO_I2C,ACELEROMETRO_SPEED,ACELEROMETRO_7BITS_ADDRESS);

}



static void __MPU6500_deinit(){
    simo_i2c_deinit(ACELEROMETRO_I2C);
}


void mpu6500_init(void){
    __MPU6500_init();
}


uint32_t  mpu6500_check(){

    uint32_t res = 0;
    uint8_t check = 0;
    uint8_t callback = 0;
    
    // HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, );
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      0x75,1,&check,1,
                      ACELEROMETRO_TIMEOUT,
                      callback);
    res = (check == 0x70)?1:0;   // 1 OK, 0 ERROR, NO DISPONIBLE

    return res;
    

}

void mpu6500_pwm(uint32_t wake_up){
    if( 1){
        //wake up

    uint8_t data = 0; // Escribir 0 despierta el mpu6500 y lo configura en 8Mhz
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (0x6b),
                        1,
                        &data,
                        1,
                        ACELEROMETRO_TIMEOUT,
                        0);
    _mpu6500_set_scala();

    }
    else{
        //sleep
    }

}




void mpu6500_set_sample_div(uint8_t freq_div){

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

void mpu6500_set_config(){

}

uint32_t mpu6500_get_aceleration(int16_t* x, int16_t* y , int16_t* z){


    uint32_t res = 0;
    // Read 6 BYTES of data starting from ACCEL_XOUT_H register

    uint8_t VALUE_ADDRESS =0x3B;
    uint8_t callback = 0;
    uint8_t Rec_Data[6]={0};
    // HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, );
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      VALUE_ADDRESS,1,&Rec_Data,6,
                      ACELEROMETRO_TIMEOUT,
                      callback);

    (*x) = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
    (*y) = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
    (*z) = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

   
        /*** convert the RAW values into acceleration in 'g'
             we have to divide according to the Full scale value set in FS_SEL
            I have configured FS_SEL = 0. So I am dividing by 16384.0
            for more details check ACCEL_CONFIG Register              ****/

        //x = Accel_X_RAW/16384.0;  // get the float g
       // y = Accel_Y_RAW/16384.0;
        //z = Accel_Z_RAW/16384.0;

    return res;

}




void mpu6500_deinit(){

}
