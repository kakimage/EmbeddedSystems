/*
  Thread que trata das seriais I2C e SPI.
*/

#include "task_seriais.h"
#include "cmsis_os.h"

extern osThreadId seriais_TaskHandle;
extern I2C_HandleTypeDef hi2c1;
extern SPI_HandleTypeDef hspi1;

extern uint8_t dataBLE[3];
extern uint8_t flagNewDataToI2C;	
extern uint8_t flagNewDataToSPI;



/* USER CODE BEGIN Header_seriais */
/**
* @brief Function implementing the seriais_Task thread.
* @param argument: Not used
* @retval None
*/
void seriais(void const * argument)
{
  for(;;)
  {
	  if (flagNewDataToI2C == TRUE){
		  flagNewDataToI2C = FALSE;
		  HAL_I2C_Master_Transmit(&hi2c1, 0, &dataBLE[1], 1, HAL_MAX_DELAY);
	  }
	  if (flagNewDataToSPI == TRUE){
		  flagNewDataToSPI = FALSE;
		  HAL_SPI_Transmit(&hspi1, &dataBLE[1], 1, HAL_MAX_DELAY);
	  }  
	  taskYIELD();
  }
}


