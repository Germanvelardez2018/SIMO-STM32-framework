


    #include "core.h"


   
    uint32_t  mpu6500_check(void);

   
    void mpu6500_pwm(uint32_t wake_up);


  
    void mpu6500_set_sample_div(uint8_t freq_div);

    uint32_t mpu6500_get_aceleration(int16_t x, int16_t y , int16_t z);

    void mpu6500_deinit();
