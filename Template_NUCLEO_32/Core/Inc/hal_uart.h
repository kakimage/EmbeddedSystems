/*
  Configuração da UART.
*/


#ifndef _HAL_UART_HEADER_SENTRY_
#define _HAL_UART_HEADER_SENTRY_

#include "main.h"
#define BUFFER_LEN  1
uint8_t RX_BUFFER[BUFFER_LEN] = {0};
uint8_t TX_BUFFER[BUFFER_LEN] = {0};
// Prototipe das funções exportadas.

void hal_uart_init(void);
void hal_uart_write(unsigned char dataUart);

void MX_USART2_UART_Init(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle);
void sendDataUart(unsigned char writeUart);

#endif


