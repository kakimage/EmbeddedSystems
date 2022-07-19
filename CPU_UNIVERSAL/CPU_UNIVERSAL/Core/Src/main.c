/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
//
// Includes 
//
#include "main.h"
#include "cmsis_os.h"
#include "hardware.h"
#include "task_default.h" 
#include "task_ble.h"
#include "task_gpio.h"
#include "task_seriais.h"

//
// Variáveis do HAL (definidas pelo fabricante no MX).
//
I2C_HandleTypeDef hi2c1;
SPI_HandleTypeDef hspi1;
UART_HandleTypeDef huart1;

//
// ID das thread(s): definidas para o FreeRTOS pelo MX.
//
osThreadId defaultTaskHandle;
osThreadId ble_TaskHandle;
osThreadId gpio_TaskHandle;
osThreadId seriais_TaskHandle;

//
// Variáveis de comunicação - aplicação.
//
uint8_t dataBLE[3];
uint8_t flagNewDataFromBLE = FALSE;
uint8_t flagNewDataToBLE = FALSE;	
uint8_t flagNewFromGPIO = FALSE;
uint8_t setFlagGPIO = OFF;
uint8_t flagNewDataToI2C = FALSE;	
uint8_t flagNewDataToSPI= FALSE;	
uint8_t flagNewDataToGPIO = FALSE;


/**
  * @brief  Ponto de entrada da aplicação.
  * @retval int
  */
int main(void)
{

  //
  // Funções de inicialização do hardware.
  //	
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();

  //
  // Criação e Instancialização das thread(s).
  //
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	osThreadDef(ble_Task, ble, osPriorityIdle, 0, 128);
	ble_TaskHandle = osThreadCreate(osThread(ble_Task), NULL);

	osThreadDef(gpio_Task, gpio, osPriorityIdle, 0, 128);
	gpio_TaskHandle = osThreadCreate(osThread(gpio_Task), NULL);

	osThreadDef(seriais_Task, seriais, osPriorityIdle, 0, 128);
	seriais_TaskHandle = osThreadCreate(osThread(seriais_Task), NULL);

  //
  // Inicia o escalonador de thread(s).
  //
  osKernelStart();

  while (1) {}
}





/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
