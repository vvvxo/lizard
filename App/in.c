#include "in.h"
#include "usart.h"
#include "sys.h"

void init_in(void)
{
	IN_Init0();
	IN_Init1();
	IN_Init2();
}

void IN_Init0(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉

	GPIO_Init(GPIOB, &GPIO_InitStructure); //初始化
}

void IN_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉

	GPIO_Init(GPIOE, &GPIO_InitStructure);
}

void IN_Init2(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); //使能GPIO时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	  //普通输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //100MHz
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;	 //上拉

	GPIO_Init(GPIOF, &GPIO_InitStructure);
}

int DIR = 1;
void CtrlMotorSpeed(unsigned char MOTOR, int SPEED)
{
	//对速度作出限制
	if (SPEED > MAX_SPEED)
		SPEED = MAX_SPEED;
	if (-SPEED > MAX_SPEED)
		SPEED = -MAX_SPEED;

	//判断正反
	if (SPEED > 0)
	{
		SPEED = SPEED;
		DIR = 1;
	}
	else
	{
		SPEED = -SPEED;
		DIR = -1;
	}
	switch (MOTOR)
	{
	case 0: //LM
		if (DIR > 0)
		{
			PEout(0) = 0;
			PEout(1) = 1;
		}
		else
		{
			PEout(0) = 1;
			PEout(1) = 0;
		}
		TIM_SetCompare1(TIM8, SPEED);
		break;

	case 1: //LS
		if (DIR > 0)
		{

			PEout(2) = 0;
			PEout(4) = 1;
		}
		else
		{
			PEout(2) = 1;
			PEout(4) = 0;
		}
		TIM_SetCompare2(TIM8, SPEED);
		break;

	case 2: //RM
		if (DIR > 0)
		{
			PBout(12) = 1;
			PBout(13) = 0;
		}
		else
		{
			PBout(12) = 0;
			PBout(13) = 1;
		}
		TIM_SetCompare3(TIM8, SPEED);
		break;

	case 3: //RS
		if (DIR > 0)
		{
			PBout(10) = 0;
			PBout(11) = 1;
		}
		else
		{
			PBout(10) = 1;
			PBout(11) = 0;
			break;
		}
		TIM_SetCompare4(TIM8, SPEED);
		break;
	}
}
