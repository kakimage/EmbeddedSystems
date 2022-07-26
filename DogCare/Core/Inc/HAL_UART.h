//Configurações de UART do sistema

#ifndef _HAL_UART_HEADER_SENTRY_
#define _HAL_UART_HEADER_SENTRY_

#include "main.h"

static void MX_USART2_UART_Init(void);
void UART_Init(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart2);
void HAL_UART_Read(UART_HandleTypeDef *huart2, uint8_t *Rx_Data, uint16_t DataSize);
void HAL_UART_Write(UART_HandleTypeDef *huart2, uint8_t *Tx_Data, uint16_t DataSize, uint32_t Timeout);

#endif
