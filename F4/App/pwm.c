#include "pwm.h"
#include "usart.h"

//TIM14 PWM部分初始化
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM_PWM_Init(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM8);//TIM8_CH1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource7,GPIO_AF_TIM8);//TIM8_CH2 
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource8,GPIO_AF_TIM8);//TIM8_CH1
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM8);//TIM8_CH2 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;		   //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	   //复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	   //上拉
	GPIO_Init(GPIOC, &GPIO_InitStructure);			   //初始化PF9
	
	TIM_DeInit(TIM8);
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;					//定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1;						//自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure); //初始化定时器14

	//初始化TIM14 Channel1 PWM模式
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			  //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	  //输出极性:TIM输出比较极性低
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC1PreloadConfig(TIM8, TIM_OCPreload_Enable); //使能TIM14在CCR1上的预装载寄存器
	
	
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable); //使能TIM14在CCR1上的预装载寄存器
	
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC3PreloadConfig(TIM8, TIM_OCPreload_Enable); //使能TIM14在CCR1上的预装载寄存器
	
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);					  //根据T指定的参数初始化外设TIM1 4OC1
	TIM_OC4PreloadConfig(TIM8, TIM_OCPreload_Enable); //使能TIM14在CCR1上的预装载寄存器
	
	TIM_ARRPreloadConfig(TIM8, ENABLE); //ARPE使能
	TIM_CtrlPWMOutputs(TIM8,ENABLE);
	TIM_Cmd(TIM8, ENABLE); 
}
