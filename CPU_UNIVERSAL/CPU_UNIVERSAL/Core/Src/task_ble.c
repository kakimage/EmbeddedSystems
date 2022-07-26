/*
	Tarefa que trata a comunicação Bluetooth.
*/

#include "task_ble.h"
#include "cmsis_os.h"

extern osThreadId ble_TaskHandle;
extern UART_HandleTypeDef huart1;
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;

extern uint8_t dataBLE[3];
extern uint8_t flagNewDataFromBLE;
extern uint8_t flagNewDataToBLE;	
extern uint8_t flagNewDataToI2C;	
extern uint8_t flagNewDataToSPI;
extern uint8_t flagNewDataToGPIO;
extern uint8_t setFlagGPIO;

/**
* @brief Function implementing the ble_Task thread.
* @param argument: Not used
* @retval None
*/

void ble(void const * argument)
{

  for(;;)
  {
		HAL_UART_Receive(&huart1, dataBLE, 1, HAL_MAX_DELAY);
		if (dataBLE[0] != 0xFF){
			if(dataBLE[0] >= 0x48)
			{
				if (dataBLE[1] == 0x01){
						setFlagGPIO = ON;
						dataBLE[2] = 0xAA;			// Avise App mobile que o Comando é válido.
						HAL_UART_Transmit(&huart1, &dataBLE[0], 1, HAL_MAX_DELAY);
						HAL_GPIO_WritePin(GPIOA, OUT_Pin, GPIO_PIN_SET);
					}
					else{
						setFlagGPIO = OFF;
						dataBLE[2] = 0xAA;			// Avise App mobile que o Comando é válido.
						HAL_UART_Transmit(&huart1, &dataBLE[0], 1, HAL_MAX_DELAY);
						HAL_GPIO_WritePin(GPIOA, OUT_Pin, GPIO_PIN_SET);
					}
			}
			else
			{
				if (dataBLE[1] == 0x01){
						setFlagGPIO = OFF;
						dataBLE[2] = 0xAA;			// Avise App mobile que o Comando é válido.
						HAL_UART_Transmit(&huart1, &dataBLE[0], 1, HAL_MAX_DELAY);
						HAL_GPIO_WritePin(GPIOA, OUT_Pin, GPIO_PIN_RESET);
					}
					else{
						setFlagGPIO = OFF;
						dataBLE[2] = 0xAA;			// Avise App mobile que o Comando é válido.
						HAL_UART_Transmit(&huart1, &dataBLE[0], 1, HAL_MAX_DELAY);
						HAL_GPIO_WritePin(GPIOA, OUT_Pin, GPIO_PIN_RESET);
					}
			}
		}
			
			
			
			dataBLE[0] = 0xFF;						// Limpa byte de recepção.

			taskYIELD();
		}

  }




