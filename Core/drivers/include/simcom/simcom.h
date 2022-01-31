/**
 * @file simcom.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-01-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */




#include "core.h"





uint32_t sim_init();

uint32_t sim_check_at();

uint32_t sim_set_echo(uint32_t ena);


uint32_t sim_set_pwr_gps(uint32_t ena);

uint32_t sim_get_gps_info();


uint32_t sim_get_version();

uint8_t sim_deinit();









