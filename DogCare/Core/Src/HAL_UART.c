#include "HAL_UART.h"

//variaveis externas
extern UART_HandleTypeDef huart2;
extern uint8_t Rx_Data;
extern uint8_t Tx_Data;
extern uint8_t ReadCommand;
extern uint8_t DefaultRes_Ok;
extern uint8_t DefaultRes_Error;

//Escrever dados na UART
void HAL_UART_Write(UART_HandleTypeDef *huart2, uint8_t *Tx_Data, uint16_t DataSize, uint32_t Timeout)
{
	HAL_UART_Transmit(huart2, Tx_Data, 16, 50);
}

//Ler dados da UART
void HAL_UART_Read(UART_HandleTypeDef *huart2, uint8_t *Rx_Data, uint16_t DataSize)
{
	HAL_UART_Receive_IT(huart2, Rx_Data, DataSize);
}

//Inicialização da UART
void UART_Init(void)
{
	MX_USART2_UART_Init();
}

static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
	__HAL_UART_ENABLE_IT(&huart2, UART_IT_RXNE); //Inicializa a interrupção da UART
  /* USER CODE END USART2_Init 2 */

}
