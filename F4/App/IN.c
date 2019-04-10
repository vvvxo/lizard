#include "IN.h"
#include "usart.h"

void IN_Init0(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉

	GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化

	GPIO_SetBits(GPIOA, GPIO_Pin_3 | GPIO_Pin_4);
}
void IN_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_5;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉

	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化

	GPIO_SetBits(GPIOB, GPIO_Pin_3 | GPIO_Pin_5);
}

void IN_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //使能GPIO时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉

	GPIO_Init(GPIOC, &GPIO_InitStructure); //初始化
}

void IN_Init3(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure);

	GPIO_SetBits(GPIOE, GPIO_Pin_2 | GPIO_Pin_3);
}

void IN_Init4(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	GPIO_SetBits(GPIOF, GPIO_Pin_9 | GPIO_Pin_10);
}
void Motor_Speed_Dir_Foot(int SPEED,int DIR, int FOOT)
{
	switch (FOOT)
	{
	case 0: //LM
		if(DIR)
		{
			PBout(3) = 1;
			PBout(5) = 0;
		}
		else
		{
			PBout(3) = 0;
			PBout(5) = 1;
		}
		
		TIM_SetCompare1(TIM8, SPEED);
		break;

	case 1: //LS
		if(DIR)
		{

			PAout(3) = 1;
			PAout(4) = 0;
		}
		else
		{
			PAout(3) = 0;
			PAout(4) = 1;
		}
		TIM_SetCompare2(TIM8, SPEED);
		break;

	case 2: //RM
		if(DIR)
		{
			PCout(1) = 1;
			PCout(2) = 0;
		}
		else
		{
			PCout(1) = 0;
			PCout(2) = 1;
		}
		TIM_SetCompare3(TIM8, SPEED);
		break;

	case 3: //RS
	if(DIR)
		{
			PCout(3) = 1;
			PCout(4) = 0;
		}
		else
		{
			PCout(3) = 0;
			PCout(4) = 1;
			break;
		}
		TIM_SetCompare2(TIM8, SPEED);
		break;
	}
}

// void LMDIRECTION(char DIRECTION, int SPEED)
// {
// 	switch (DIRECTION)
// 	{
// 	case 1:

// 		LM_IN1 = 1;
// 		LM_IN2 = 0;
// 		break;
// 	case 2:
// 		LM_IN1 = 0;
// 		LM_IN2 = 1;
// 		break;
// 	}
// 	TIM_SetCompare1(TIM8, SPEED);
// }

// void LSDIRECTION(char DIRECTION, int SPEED)
// {
// 	switch (DIRECTION)
// 	{
// 	case 1:

// 		PAout(3) = 1;
// 		PAout(4) = 0;
// 		break;
// 	case 2:
// 		PAout(3) = 0;
// 		PAout(4) = 1;
// 		break;
// 	}
// 	TIM_SetCompare2(TIM8, SPEED);
// }

// void RMDIRECTION(char DIRECTION, int SPEED)
// {
// 	switch (DIRECTION)
// 	{
// 	case 1:

// 		PCout(1) = 1;
// 		PCout(2) = 0;
// 		break;
// 	case 2:
// 		PCout(1) = 0;
// 		PCout(2) = 1;
// 		break;
// 	}
// 	TIM_SetCompare3(TIM8, SPEED);
// }

// void RSDIRECTION(char DIRECTION, int SPEED)
// {
// 	switch (DIRECTION)
// 	{
// 	case 1:

// 		PAout(3) = 1;
// 		PAout(4) = 0;
// 		break;
// 	case 2:
// 		PAout(3) = 0;
// 		PAout(4) = 1;
// 		break;
// 	}
// 	TIM_SetCompare2(TIM8, SPEED);
// }
