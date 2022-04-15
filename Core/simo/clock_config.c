/**
 * @file clock_config.c
 * @author German Velardez (germanvelardez16@gmail.com)
 * @brief  Implementacion de la api para configurar el clock del sistema
 * @version 0.1
 * @date 2022-01-31
 * 
 * @copyright Copyright (c) 2022
 * 
 */



#include "main.h"
#include "clock_config.h"









    // VALORES DEFAULT

    #define CLOCK_LSI                   8
    #define CLOCK_LSI_DIV               2
    #define CLOCK_LSI_MUL               10
    #define CLOCK_ABH_DIV               1

    #define CLOCK_APB1_DIV              2
    #define CLOCK_APB2_DIV              1






    #define USED_CLOCK_LSI               8
    #define USED_CLOCK_LSI_DIV           RCC_PLLSOURCE_HSI_DIV2
    #define USED_CLOCK_LSI_MUL           RCC_PLL_MUL10
    #define USED_CLOCK_APB1_DIV          RCC_HCLK_DIV2
    #define USED_CLOCK_APB2_DIV          RCC_HCLK_DIV1




    #define CLOCK_BASE              (CLOCK_LSI / CLOCK_LSI_DIV) * CLOCK_LSI_MUL   // 40MHZ

    #define CLOCK_BASE_MAX          72
    #define CLOCK_APB1_MAX          36
    #define CLOCK_APB2_MAX          72




void simo_clock_init(void){
   // Aqui va la configuracion inicial
  HAL_Init();
  simo_clock_config();

}


uint32_t simo_clock_rtc(void){
  uint32_t ret = 1;
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC|RCC_PERIPHCLK_ADC;
    PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
    PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV4;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK) {
    ret = 0;
  }
  return ret;
}



void simo_clock_config(void){
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
     * in the RCC_OscInitTypeDef structure.
     */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = USED_CLOCK_LSI_DIV;
    RCC_OscInitStruct.PLL.PLLMUL = USED_CLOCK_LSI_MUL;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
     */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }

  }



  uint32_t simo_clock_get_base(void){
    return (1000000)* ((CLOCK_LSI / CLOCK_LSI_DIV) * CLOCK_LSI_MUL);

  }



  uint32_t simo_clock_get_timer_base(){
    return (simo_clock_get_base() * CLOCK_APB2_DIV) ;
  }



  uint32_t simo_clock_get_APB1(){
    return (simo_clock_get_base() / CLOCK_APB1_DIV) ;
  }



  uint32_t simo_clock_get_APB2(){
    return (simo_clock_get_base() / CLOCK_APB2_DIV) ;
  }