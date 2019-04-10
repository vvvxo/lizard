#ifndef _TIMER_H
#define _TIMER_H
#include "stm32f10x.h"
void TIM3_Cap_Init(u16 arr, u16 psc);
void TIM3_IRQHandler(void);
void printencoderpwm(void);
#endif
