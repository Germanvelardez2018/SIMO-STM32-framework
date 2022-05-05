


#include "debug.h"
#include "uart.h"



/**USART2 GPIO Configuration
  * Conexion Uart Debug
        PA2     ------> USART2_TX
        PA3     ------> USART2_RX
        */


#define DEBUG_PRINT_ON                                DEBUG_ON

#define DEBUG_PRINT_BAUDRATE                          DEBUG_BAUDRATE
#define DEBUG_PRINT_NAME                              DEBUG_NAME
#define DEBUG_PRINT_UART                              DEBUG_UART
#define DEBUG_PRINT_FORMAT                           "[%s] \t\t%s" //! DEBUG NAME , MESSAGE
#define DEBUG_PRINT_TIMEOUT                           (1000)
#define DEBUG_BUFFER_SIZE                             (300)
#define DEBUG_PRINT_MSG_INIT                          "DEBUG ON"


#if DEBUG_PRINT_ON == 1

    char __debug_buffer[DEBUG_BUFFER_SIZE];
    uint8_t __DEBUG_INIT__ = 0;

#endif


uint32_t debug_init(void){
        uint32_t ret = 0;
   #if DEBUG_PRINT_ON == 1    
        ret = simo_uart_init(DEBUG_PRINT_UART,DEBUG_PRINT_BAUDRATE);
        if(ret == 1 )__DEBUG_INIT__ = 1;
        debug_print(DEBUG_PRINT_MSG_INIT);
    #endif
        return ret;

}



uint32_t debug_print(char* buff){
    uint32_t ret= 0;
    #if DEBUG_PRINT_ON == 1
        if(__DEBUG_INIT__ == 0) debug_init();
        if( buff != NULL){
            sprintf(__debug_buffer,DEBUG_PRINT_FORMAT,DEBUG_PRINT_NAME,(buff== NULL)?"NULL":buff);
            ret =  simo_uart_write(DEBUG_PRINT_UART,__debug_buffer,strlen(__debug_buffer),DEBUG_PRINT_TIMEOUT,0);
        }
        
    #endif
    
    return  ;
}