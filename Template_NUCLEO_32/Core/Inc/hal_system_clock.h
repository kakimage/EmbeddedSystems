/*
  Configuração do sistema interno de clock do uC.
*/


#ifndef _HAL_SYSTEM_CLOCK_HEADER_SENTRY_
#define _HAL_SYSTEM_CLOCK_HEADER_SENTRY_

#include "main.h"

// Prototipe das funções exportadas.

void SystemClock_Config(void);
void hal_system_clock_init(void);

#endif

