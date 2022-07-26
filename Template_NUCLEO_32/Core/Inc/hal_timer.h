/*
  Configuração do contador para timer TIM2.
*/


#ifndef _HAL_TIMER_HEADER_SENTRY_
#define _HAL_TIMER_HEADER_SENTRY_

#include "main.h"

// Prototipe das funções exportadas.

void hal_timer_init(void);
void atualizaOLED(void);
void MX_TIM2_Init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif

