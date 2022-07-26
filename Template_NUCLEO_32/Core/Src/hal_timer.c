//
// HAL para definição do timer geral TIM2.
//

  #include "hal_timer.h"
	#include "ssd1306.h" 
	#include "fonts.h" 
	#include "test.h" 
	#include <stdio.h>
	#include "acs712.h"
	
	extern uint32_t value;
	extern uint32_t adc1, adc2;
	extern TIM_HandleTypeDef htim2;
  
	float valorR1 = 30000.0; //VALOR DO RESISTOR 1 DO DIVISOR DE TENSÃO
  float valorR2 = 7500.0; // VALOR DO RESISTOR 2 DO DIVISOR DE TENSÃO
	float tensaoEntrada = 0.0; //VARIÁVEL PARA ARMAZENAR O VALOR DE TENSÃO DE ENTRADA DO SENSOR
  int tensaoMedida = 0; //VARIÁVEL PARA ARMAZENAR O VALOR DA TENSÃO MEDIDA PELO SENSOR
	
  //
  // Variáveis Externas.
  //
  extern TIM_HandleTypeDef htim2;
  
  //
  // Inicialização dos parâmetros do Timer2.
  //
  void hal_timer_init(void){
	  MX_TIM2_Init();
  }
  
  // -------------------------------------------------------------------
  // Funções do fabricante.
  // -------------------------------------------------------------------
  
  void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){  
	  /* 
	  Nesta função de Callback você precisa colocar contadores, e usar funções 
	  de escrita em GPIO para acender e apagar o LED3, por exemplo.
	  */
		if(htim->Instance == TIM2) 
		{
				HAL_GPIO_TogglePin(LED_GPIO_Port,  LED_Pin);	
				atualizaOLED();   														
				HAL_Delay(100);
				HAL_GPIO_TogglePin(LED_GPIO_Port,  LED_Pin);	
    }
  }

      
/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 65535;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

void atualizaOLED(void)
{
	char Valor1[10];
	char Valor2[10];
		
	  tensaoEntrada = (adc1 * 5.0) / 1024.0; //VARIÁVEL RECEBE O RESULTADO DO CÁLCULO
    tensaoMedida = tensaoEntrada / (valorR2/(valorR1+valorR2)); //VARIÁVEL RECEBE O VALOR DE TENSÃO DC MEDIDA PELO SENSOR
 
		float SensorRead = adc2*(5.0 / 1023.0);     //We read the sensor output  
    int current = (SensorRead-2.5)/0.100;
	
	
		sprintf(Valor1, "%uint32_t", tensaoMedida);
	  sprintf(Valor2, "%uint32_t", current);
	
		SSD1306_Fill((SSD1306_COLOR_t)0);
		SSD1306_UpdateScreen();
		
		SSD1306_GotoXY(10,10);
		SSD1306_Puts((char*)"Tensao: ", (FontDef_t*)&Font_11x18,(SSD1306_COLOR_t)1);
		
		SSD1306_GotoXY(10,30);  
		SSD1306_Puts(Valor1,  (FontDef_t*)&Font_11x18,  (SSD1306_COLOR_t)1 );
	
	  SSD1306_GotoXY(10,50);
		SSD1306_Puts((char*)"V", (FontDef_t*)&Font_11x18,(SSD1306_COLOR_t)1);
	
		SSD1306_GotoXY(20,10);
		SSD1306_Puts((char*)"Corrente: ", (FontDef_t*)&Font_11x18,(SSD1306_COLOR_t)1);
		
		SSD1306_GotoXY(20,30);  
		SSD1306_Puts(Valor2,  (FontDef_t*)&Font_11x18,  (SSD1306_COLOR_t)1 );
		
		SSD1306_GotoXY(20,50);
		SSD1306_Puts((char*)"A", (FontDef_t*)&Font_11x18,(SSD1306_COLOR_t)1);
	
		SSD1306_UpdateScreen();
}

