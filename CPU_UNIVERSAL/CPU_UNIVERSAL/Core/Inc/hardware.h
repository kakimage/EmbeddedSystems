/*
  Configuração do hardware interno do uC.
*/


#ifndef _HARDWARE_HEADER_SENTRY_
#define _HARDWARE_HEADER_SENTRY_

#include "main.h"
	
	//
	// Prototipo das funções exportadas.
	//
	void SystemClock_Config(void);
	void MX_GPIO_Init(void);
	void MX_I2C1_Init(void);
	void MX_SPI1_Init(void);
	void MX_USART1_UART_Init(void);

#endif
