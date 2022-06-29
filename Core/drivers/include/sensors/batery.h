

#ifndef __BATERY_H_
#define __BATERY_H_


        #include "core.h"



/**
 * @brief Inicio el hardware necesario para manejar acelerometro (I2C)
 * 
 * @return ** void 
 */
void batery_level_init(void);


void batery_level_deinit();


static uint32_t __baterry_level_get_measure();



uint32_t  batery_level_get_measure(char* buffer, uint8_t len_max);





#endif