/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
//HAL
#include "HAL_SysCLK_Config.h"
#include "HAL_GPIO.h"
#include "HAL_I2C.h"
#include "HAL_TIM2.h"
#include "HAL_UART.h"
#include "HAL_MAX30100.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t Rx_Data[16];
uint8_t MAX30100_ir_sample[16];
uint8_t MAX30100_red_sample[16];
uint8_t ReadCommand[16] = "Read";
uint8_t DefaultRes_Ok[] = "Ok";
uint8_t DefaultRes_Error[] = "Error";

/* USER CODE END PV */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN SysInit */
	SysClock_Config();
  /* USER CODE END SysInit */

  /* USER CODE BEGIN 2 */
	//inicializações de HAL
	GPIO_Init();
	I2C_Init();
	TIM2_Init();
	UART_Init();
	
	//Inicialização da interrupção de leitura da UART
	HAL_UART_Read(&huart2, Rx_Data, 16);
	
	//Inicizalização do sensor (SP, PW, LEDCurrent iniciam no modo default pois não tenho como
	//testar para calibrar o sensor)
	HAL_MAX30100_Init(&hi2c1);
	HAL_MAX30100_SetSpO2SampleRate(MAX30100_SPO2SR_DEFAULT); 
	HAL_MAX30100_SetLEDPulseWidth(MAX30100_LEDPW_DEFAULT);
	HAL_MAX30100_SetLEDCurrent(MAX30100_LEDCURRENT_DEFAULT, MAX30100_LEDCURRENT_DEFAULT);
	HAL_MAX30100_SetMode(MAX30100_IDLE_MODE); //Inicia no modo idle para economia de energia
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

//Trata interrupção de leitura da UART
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart2)
{	
	HAL_UART_Read(huart2, Rx_Data, 16); //reseta flag de interrupção da uart
	
	//le o comando e faz task
	if(strcmp((char *)Rx_Data, (char *)ReadCommand)) //Leitura sob demanda do usuario
	{
		HAL_UART_Write(huart2, DefaultRes_Ok, 16, 50); //responde ao mobile que recebeu comando
		
		//Tira sensor do modo IDLE
		//Qualquer modo, tanto SpO2 quanto HROnly coletam dados de ambos LEDS
		HAL_MAX30100_SetMode(MAX30100_SPO2_MODE);

		//Faz leitura dos dados
		HAL_MAX30100_ReadFIFO();
		
		//Transmite os dados via UART
		HAL_UART_Write(huart2, MAX30100_ir_sample, 16, 50);
		HAL_UART_Write(huart2, MAX30100_red_sample, 16, 50);
		
		//Limpa fifo e coloca sensor no modo IDLE novamente
		HAL_MAX30100_ClearFIFO();
		HAL_MAX30100_SetMode(MAX30100_IDLE_MODE);
	}
	else //comando não existe
	{
		HAL_UART_Write(huart2, DefaultRes_Error, 16, 50); //responde ao mobile "Erro"
	}
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
