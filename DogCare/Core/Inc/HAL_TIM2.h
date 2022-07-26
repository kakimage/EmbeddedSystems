//COnfigurações do TIM2 do sistema

#ifndef _HAL_TIM2_HEADER_SENTRY_
#define _HAL_TIM2_HEADER_SENTRY_

#include "main.h"

static void MX_TIM2_Init(void);
void TIM2_Init(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

#endif
