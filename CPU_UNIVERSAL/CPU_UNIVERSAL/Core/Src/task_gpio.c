/*
	Tarefa que trata pinos de GPIO.
*/

#include "task_gpio.h"
#include "cmsis_os.h"

extern osThreadId gpio_TaskHandle;
extern uint8_t flagNewFromGPIO;
extern uint8_t setFlagGPIO;
extern uint8_t flagNewDataToGPIO;
extern uint8_t dataFromInput;
extern uint8_t dataBLE[3];

/**
* @brief Function implementing the gpio_Task thread.
* @param argument: Not used
* @retval None
*/

void gpio(void const * argument)
{	
  for(;;)
  {															    //		
		if (setFlagGPIO == ON)								// Escrita: dado enviado pelo App mobile.
			HAL_GPIO_WritePin(GPIOA, OUT_Pin, GPIO_PIN_SET);	//
		else													//
			HAL_GPIO_WritePin(GPIOA, OUT_Pin, GPIO_PIN_RESET);	//
		
		taskYIELD();	  
  }

}
