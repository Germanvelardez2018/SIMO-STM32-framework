


#include "core.h"



void accelerometer_reset();


void accelerometer_init(void);

uint32_t  accelerometer_check(void);

void accelerometer_sleep(uint32_t sleep);
  
void accelerometer_set_sample_div(uint8_t freq_div);

uint32_t accelerometer_get_aceleration(int16_t* x, int16_t* y , int16_t* z);

void accelerometer_deinit();

void accelerometer_calibration();


uint32_t accelerometer_set_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset);

uint32_t accelerometer_get_offset(int16_t* x_offset, int16_t* y_offset, int16_t* z_offset);


uint32_t accelerometer_get_measure(char* buffer, uint8_t len);
