#include "stm32f10x.h"
void exti_init(void)
{
	TIM_TimeBaseInitTypeDef  TIM;
	NVIC_InitTypeDef Nvic;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	Nvic.NVIC_IRQChannel = TIM2_IRQn;
	Nvic.NVIC_IRQChannelPreemptionPriority = 0x0;
	Nvic.NVIC_IRQChannelSubPriority = 0x0;
	Nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&Nvic);

	TIM.TIM_Prescaler = 360;    //APB1 is 36MHz PSC
	TIM.TIM_CounterMode = TIM_CounterMode_Down;
	TIM.TIM_ClockDivision = TIM_CKD_DIV1;//不分频为72MHZ
	TIM.TIM_Period = 999;      //ARR
	TIM_TimeBaseInit(TIM2, &TIM);

	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//使能TIM2中断，向上溢出中断
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);	//清除TIM标志位
}
