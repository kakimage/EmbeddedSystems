/*
	Tarefa padrão.
*/

#include "task_default.h"
#include "cmsis_os.h"


extern osThreadId defaultTaskHandle;



/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */

void StartDefaultTask(void const * argument)
{
	int led = 0;
	for(;;)
	{
		if (led == 0) {
			HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_SET);		//Turn LED on.
			led = 1;
		}
		else {
			HAL_GPIO_WritePin(GPIOC, LED_Pin, GPIO_PIN_RESET);		//Turn LED off.
			led = 0;
		}	
		osDelay(180);
	}
}
