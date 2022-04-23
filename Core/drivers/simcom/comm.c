
#include "comm.h"
#include "uart.h"
#include "gpio.h"



#define SIMCOM_AT_UART             UART_A       //! Pin A10  (TX) y A9 (RX)
#define SIMCOM_DEBUG_UART          UART_B        //! Pin A3 (RX)  y A2 (TX)
#define SIMCOM_BAUDRATE            115200





#define SIMCOM_BUFFER_SIZE                 250
#define SIMCOM_TIMEOUT_TX                  500
#define SIMCOM_TIMEOUT_RX                  1000
static uint8_t __comm_buffer[SIMCOM_BUFFER_SIZE] ={0};     //! Buffer para la respuesta

#define SIMCOM_BUFFER_ARRAY         (__comm_buffer)





//! Pins para manejar el modulo SIM
#define PIN_SIM_BAT                       SIMO_GPIO_28//PB12
#define PIN_SIM_PWRUP                     SIMO_GPIO_29//PB13
#define PIN_SIM_IRQ                     
#define IS_EQUAL                            (0)

#define CMD_AT                               "AT\r\n"
#define  CMD_OK                              "OK\r\n"
#define CMD_VERSION                          "ATI\r\n"
#define CMD_ECHO_ON                          "ATE1\r\n"
#define CMD_ECHO_OFF                         "ATE0\r\n"
#define CMD_GET_SIGNAL                       "AT+CSQ\r\n"
#define CMD_PWR_GPS_ON                       "AT+CGNSPWR=1\r\n"
#define CMD_PWR_GPS_OFF                      "AT+CGNSPWR=0\r\n"
#define CMD_GETGPSINFO                       "AT+CGNSINF\r\n"
#define CMD_GETOPERATOR                       "AT+COPS?\r\n"



//  !APNS
//  !PERSONAL
//!  APN_PERSONAL                 "datos.personal.com"
//!  APN_USR_PASS_PERSONAL        "datos"
//  !TUENTI
//!  APN_TUENTI                   "internet.movil"
//!  APN_USER_PASS_TUENTI         "internet"



#define CMD_OPEN_APN_TUENTI                          "AT+CNACT=1,\"internet.movil\"\r\n"
#define CMD_OPEN_APN_PERSONAL                        "AT+CNACT=1,\"datos.personal.com\"\r\n"

#define CMD_GET_APN                           "AT+CNACT?"       





// ! Modo sleep y resume
#define CMD_LOW_PWR_ON                              "AT+CPSMS=1\r\n"
#define CMD_LOW_PWR_OFF                             "AT+CPSMS=0\r\n"
      



//! Configuracion MQTT
 #define CMD_MQTT               "AT+SMCONF="
 #define CMD_MQTT_URL           " \"URL\""
 #define CMD_MQTT_USER          "\"USERNAME\""
 #define CMD_MQTT_PASSWORD      "\"PASSWORD\""
 #define CMD_MQTT_QOS           "\"QOS\""
 #define CMD_MQTT_COMMIT        "AT+SMCONN\r\n"
 #define CMD_MQTT_PUBLISH       "AT+SMPUB=\"%s\",\"%d\",1,1 \r\n" 








#define COMM_DEBUG                               (1)

/**
 * @brief Iniciamos el hardware asociado
 * 
 * @return ** uint32_t 
 */
static uint32_t  __comm_init(){
    uint32_t ret = 0;
    ret =  simo_uart_init(SIMCOM_AT_UART,SIMCOM_BAUDRATE);
    if(ret != 0 ){
        simo_gpio_set(PIN_SIM_BAT,SIMO_GPIO_OUT);
        simo_gpio_set(PIN_SIM_PWRUP,SIMO_GPIO_OUT);
        simo_gpio_write(PIN_SIM_BAT,1);
        simo_gpio_write(PIN_SIM_PWRUP,1);
    }
    return ret;
}

/**
 * @brief Desconfiguramos el hardware asociado
 * 
 * @return ** void 
 */
static void __comm_deinit(){
    simo_uart_deinit(SIMCOM_AT_UART);
}




static uint8_t* __comm_get_buffer(){
    return SIMCOM_BUFFER_ARRAY;
}


/**
 * @brief Leo la respuesta por puerto rx asociado. Se guarda en __comm_buffer (static)
 * 
 * @return ** uint32_t 
 */
static  uint32_t __comm_read(void){
        uint32_t ret = simo_uart_read(SIMCOM_AT_UART,SIMCOM_BUFFER_ARRAY,SIMCOM_BUFFER_SIZE,SIMCOM_TIMEOUT_RX,0);
        
        return ret;
}


/**
 * @brief Esribo por puerto asociado de salida
 * 
 * @param buff 
 * @param len 
 * @return ** uint32_t 
 */
static  uint32_t __comm_write(uint8_t* buff){
        uint32_t ret = simo_uart_write(SIMCOM_AT_UART,buff,strlen(buff),SIMCOM_TIMEOUT_TX,0);
        return ret;
}



/**
 * @brief Esribo por puerto asociado de salida
 * 
 * @param buff 
 * @param len 
 * @return ** uint32_t 
 */
static  uint32_t __comm_debug_write(uint8_t* buff){
        uint32_t ret = simo_uart_write(SIMCOM_DEBUG_UART,buff,strlen(buff),SIMCOM_TIMEOUT_TX,0);
        return ret;
}


/**
 * @brief Comparo respuesta recibida con respuesta esperada
 * 
 * @param response 
 * @return ** uint32_t 
 */
static uint32_t __comm_check_response(char* response){
    uint32_t len_reponse = strlen(response)  ;
    uint32_t len_buffer = strlen(SIMCOM_BUFFER_ARRAY);
    uint32_t index = len_buffer - len_reponse ;  
    uint32_t res = (  strncmp(&(SIMCOM_BUFFER_ARRAY[index]),response,len_reponse) == IS_EQUAL)?1:0;
   
    return res;
}



/**
 * @brief Envio comando y analiso respuesta
 * 
 * @param cmd_string 
 * @param len_cmd 
 * @return ** uint32_t 
 */
uint32_t __comm_cmd_send(uint8_t* cmd_string, uint8_t* exp_response){
    int32_t ret = 1;
    // envio comando
    //BORRAMOS BUFFER DE RECEPCCION
    memset(SIMCOM_BUFFER_ARRAY,0,SIMCOM_BUFFER_SIZE);
    ret = __comm_write(cmd_string);
    // leo respuesta
   ret = __comm_read();
   #if (COMM_DEBUG == 1)
        __comm_debug_write(cmd_string); // commando
        __comm_debug_write("\n");

   
        __comm_debug_write(SIMCOM_BUFFER_ARRAY);
        __comm_debug_write("\n");

    #endif
    // comparo respuesta con respuesta esperada
   ret = __comm_check_response(exp_response);


    return  ret;

}




//-------------------------------------------------------------------------FUNCIONES PUBLICAS-----------------------------------------------





uint32_t comm_mqtt_publish(char* topic, char* payload, uint8_t len_payload){

    uint32_t ret = 0;
    uint8_t  buffer[255]={0};
    sprintf(buffer,CMD_MQTT_PUBLISH,topic,len_payload);    
    ret = __comm_cmd_send(buffer,CMD_OK);
    simo_delay_ms(1000);
    ret = __comm_cmd_send(payload,CMD_OK);

    return ret;
}














uint8_t* comm_get_buffer(){
    
    return SIMCOM_BUFFER_ARRAY;
}




uint32_t comm_get_apn(void){
    uint32_t ret = __comm_cmd_send(CMD_GET_APN,CMD_OK);
    return ret;
}


uint32_t comm_open_apn(void){
    uint32_t ret = __comm_cmd_send(CMD_OPEN_APN_PERSONAL,CMD_OK);
    return ret;
}










uint32_t comm_set_pwr_gps(uint32_t gps_on){

    uint32_t ret = 0;
    if(gps_on == 0){
        ret = __comm_cmd_send(CMD_PWR_GPS_OFF,CMD_OK);
    }
    else{
        ret = __comm_cmd_send(CMD_PWR_GPS_ON,CMD_OK);
    }

    return ret;   

}


uint32_t comm_get_gps_info(){
    uint32_t ret = 0;
    ret = __comm_cmd_send(CMD_GETGPSINFO,CMD_OK);
    
    return  ret;
}





uint32_t comm_get_signal(){

   uint32_t ret = 0;
    ret = __comm_cmd_send(CMD_GET_SIGNAL,CMD_OK);
    
    return ret;

}




uint32_t comm_get_operator(void){
    uint32_t ret = __comm_cmd_send(CMD_GETOPERATOR,CMD_OK);
    return ret;
}


uint32_t comm_set_echo(uint8_t echo_on){
    uint32_t ret = 0;
    if(echo_on == 0){
        ret = __comm_cmd_send(CMD_ECHO_OFF,CMD_OK);
    }
    else{
        ret = __comm_cmd_send(CMD_ECHO_ON,CMD_OK);
    }

    return ret;
}




uint32_t comm_version(void){
    uint32_t ret = __comm_cmd_send(CMD_VERSION,CMD_OK);
    return ret;
}



uint32_t comm_check(void){

    uint32_t ret = __comm_cmd_send(CMD_AT,CMD_OK);
   
   
    return ret;
}





uint32_t comm_config_mqtt(uint8_t* url, uint8_t* user, uint8_t* password, uint8_t* qos){
    uint32_t ret =  0;
    if ((url == NULL) || ( user == NULL) || (password == NULL) || (qos == NULL)) return 0;
    u_int8_t buffer[120]={};
    sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_URL,url);    
    simo_delay_ms(500);
    ret = __comm_cmd_send(buffer,CMD_OK);
    sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_USER,user);    
    simo_delay_ms(500);
    ret = __comm_cmd_send(buffer,CMD_OK);
    sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_PASSWORD,password);    
    simo_delay_ms(500);
    ret = __comm_cmd_send(buffer,CMD_OK);
    sprintf(buffer,"%s %s,\"%s\" \r\n",CMD_MQTT,CMD_MQTT_QOS,qos);    
    simo_delay_ms(500);
    ret = __comm_cmd_send(buffer,CMD_OK);
    simo_delay_ms(500);
    ret = __comm_cmd_send(CMD_MQTT_COMMIT,CMD_OK);
    simo_delay_ms(500);

return ret;

}








uint32_t comm_init(void ){
    uint32_t ret = 0;
    // inicio  el hardware asociado
    ret =  __comm_init();
    simo_delay_ms(10000);

    return ret;
}



/**
 * @brief Poner en modo sleep el sensor
 * 
 * @param sleep 
 * @return ** void 
 */
void comm_sleep(){
    uint32_t ret = __comm_cmd_send(CMD_LOW_PWR_ON,CMD_OK);
   
   
    return ret;
}


/**
 * @brief 
 * 
 * @return ** void 
 */
void comm_resume(){

      uint32_t ret = __comm_cmd_send(CMD_LOW_PWR_OFF,CMD_OK);
   
   
    return ret;

}
