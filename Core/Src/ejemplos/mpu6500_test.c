/**
 * @file mpu6500_test.c
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  
 * @version 0.1
 * @date 2022-03-09
 * 
 * @copyright Copyright (c) 2022
 * 
 */



 // Recordar configurar los siguientes elementos los flar para manejar UART (1 solo uart) y TIMER ( 2 timers)



#include "stdio.h"
#include "main.h"

// Simo
#include "uart.h"
#include "gpio.h"
#include "clock_config.h"
#include "delay.h"

#include "mpu_6500.h"

/* USER CODE END Includes */


#define  LED_TOOGLE            SIMO_GPIO_18 // PB2
#define  BAUDRATE              115200
#define  UART_TX               UART_B   //  PA2 TX  PA3 RX   
#define  TIMEOUT               500
#define  modo_tx_irq           0




/**
 * @brief Funcion de inicio de perifericos. 
 * 
 * @return ** void 
 */
static void setup(void){

  // Aqui va la configuracion inicial
  HAL_Init();
  simo_clock_config();
  simo_uart_init(UART_TX,BAUDRATE);
  //! Configuracion inicial de GPIO
  simo_gpio_set(SIMO_GPIO_18, SIMO_GPIO_OUT);

  //! Inicio el sensor mpu6500
  mpu6500_reset();
  mpu6500_init();
  if(mpu6500_check() != 0){
    simo_uart_write(UART_TX,"mpu6500 ready \r\n",strlen("mpu6500 ready \r\n"),TIMEOUT,modo_tx_irq);
  }
  else{
    simo_uart_write(UART_TX,"mpu6500 Error \r\n",strlen("mpu6500 Error \r\n"),TIMEOUT,modo_tx_irq);

  }
    mpu6500_sleep(1);
    mpu6500_set_sample_div(7); //1khz



}





/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void)
{

//Levanto la HAL y Configuro todos los perifericos
setup();

//Configuro para leer datos mediante interrupcion



#define MSG_INIT     "Iniciamos aplicacion\r\n"


simo_uart_write(UART_TX,MSG_INIT,strlen(MSG_INIT),TIMEOUT,modo_tx_irq);


#define MSG_TX_UART    "tx uart \r\n"
int16_t x;
int16_t y;
int16_t z;
int16_t x_offset;
int16_t y_offset;
int16_t z_offset;

mpu_6500_calibration();
char buffer[100]={0};
#define format      "x:%3.2f  y:%.2f  z:%.2f\r\n"
#define lowformat   "x:%ld y:%ld z:%ld \r\n"
#define lowoffset   "(offset)x:%ld y:%ld z:%ld \r\n"
while(1){

    mpu6500_get_aceleration(&x,&y,&z);


    float _x = x/16384.0;  
    float _y = y/16384.0;
    float _z = z/16384.0;
    mpu6500_check();
    simo_delay_ms(4500);
    sprintf(buffer,format,_x,_y,_z);
   // sprintf(buffer,lowformat,x,y,z);
    simo_gpio_toogle(SIMO_GPIO_18);
    simo_uart_write(UART_TX,buffer,strlen(buffer),TIMEOUT,modo_tx_irq);
    mpu_6500_get_offset(&x_offset,&y_offset,&z_offset);
    sprintf(buffer,lowoffset,x_offset,y_offset,z_offset);
    simo_uart_write(UART_TX,buffer,strlen(buffer),TIMEOUT,modo_tx_irq);

}
  

  
}







#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
