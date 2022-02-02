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



uint32_t sim_get_signal_level();


uint32_t sim_set_pwr_gps(uint32_t ena);

uint32_t sim_get_gps_info();


uint32_t sim_get_version();

uint8_t sim_deinit();


uint32_t sim_get_operator();

uint32_t sim_open_apn();


uint32_t sim_get_default();



uint32_t sim_config_mqtt(uint8_t* url, uint8_t* user, uint8_t* password, uint8_t* qos);

uint32_t sim_mqtt_publish(char* topic, char* payload,uint16_t len_payload);



uint8_t* sim_get_buffer();