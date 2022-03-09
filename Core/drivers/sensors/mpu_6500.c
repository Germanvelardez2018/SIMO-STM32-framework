




#include "mpu_6500.h"
#include "main.h"

#include "i2c.h"




#define MPU6500_I2C_ADDR                         (I2CAddress)
#define ACELEROMETRO_ADDRESS                     (I2CAddress << 1 )
#define ACELEROMETRO_I2C                         I2C_A
#define ACELEROMETRO_SPEED                       (100000)
#define ACELEROMETRO_7BITS_ADDRESS               (1)
#define ACELEROMETRO_TIMEOUT                     (5000)


#ifndef MPU6500_BUFFER_SIZE
#define MPU6500_BUFFER_SIZE   MPU6500_WIDTH * MPU6500_HEIGHT / 8
#endif

#define MPU6500_USE_I2C





static void  __MPU6500_init(){

    simo_i2c_init(ACELEROMETRO_I2C,ACELEROMETRO_SPEED,ACELEROMETRO_7BITS_ADDRESS);

}



static void __MPU6500_deinit(){
    simo_i2c_deinit(ACELEROMETRO_I2C);
}


uint32_t  mpu6500_check(){

    uint32_t res = 0;
    uint8_t check = 0;
    uint8_t REG_READY = 0x00;
    uint8_t callback = 0;
    // HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, );
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      REG_READY,1,&check,1,
                      ACELEROMETRO_TIMEOUT,
                      callback);
    res = (check == 0x68)?1:0;   // 1 OK, 0 ERROR, NO DISPONIBLE

    return res;
    

}

void mpu6500_pwm(uint32_t wake_up){

    if( wake_up){
        //wake up

    data = 0; // Escribir 0 despierta el mpu6500 y lo configura en 8Mhz
    simo_i2c_mem_write( ACELEROMETRO_I2C,
                        ACELEROMETRO_ADDRESS,
                        (0x6b),
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


void mpu6500_set_sample_div(uint8_t freq_div){

    // Set DATA RATE of 1KHz by writing SMPLRT_DIV register in 7
    Data = freq_div;
    simo_i2c_mem_write(     ACELEROMETRO_I2C,
                            ACELEROMETRO_ADDRESS,
                            (0x19),
                            1,
                            &data,
                            1,
                            ACELEROMETRO_TIMEOUT,
                            0);

}


uint32_t mpu6500_get_aceleration(int16_t x, int16_t y , int16_t z){


    uint32_t res = 0;
        // Read 6 BYTES of data starting from ACCEL_XOUT_H register

    uint8_t VALUE_ADDRESS = 0x00;
    uint8_t callback = 0;
    uint8_t Rec_Data[6]={0};
    // HAL_I2C_Mem_Read (&hi2c1, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, );
    simo_i2c_mem_read(ACELEROMETRO_I2C,
                      ACELEROMETRO_ADDRESS,
                      VALUE_ADDRESS,1,&Rec_Data,6,
                      ACELEROMETRO_TIMEOUT,
                      callback);

    x = (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);
    y = (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);
    z = (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);

        /*** convert the RAW values into acceleration in 'g'
             we have to divide according to the Full scale value set in FS_SEL
            I have configured FS_SEL = 0. So I am dividing by 16384.0
            for more details check ACCEL_CONFIG Register              ****/

        //  Ax = Accel_X_RAW/16384.0;  // get the float g
        //  Ay = Accel_Y_RAW/16384.0;
        //  Az = Accel_Z_RAW/16384.0;

    return res;

}




void mpu6500_deinit(){

}
