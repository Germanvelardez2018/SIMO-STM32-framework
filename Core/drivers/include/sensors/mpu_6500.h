


    #include "core.h"

void mpu6500_reset();


void mpu6500_init(void);

uint32_t  mpu6500_check(void);

void mpu6500_sleep(uint32_t sleep);
  
void mpu6500_set_sample_div(uint8_t freq_div);

uint32_t mpu6500_get_aceleration(int16_t* x, int16_t* y , int16_t* z);

void mpu6500_deinit();

void mpu_6500_calibration();


uint32_t mpu_6500_set_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset);

uint32_t mpu_6500_get_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset);