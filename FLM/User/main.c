#include "stm32f10x.h"
#include "sys.h"
#include "REG.h"
#include "can.h"
#include "delay.h"
#include "timer.h"
#include "pid.h"

//转动一圈encoder的值
#define ONE_ENCODER 82000

//左腿主电机和从电机
#define LM_ANGLE 60
#define LS_ANGLE 45

#define LS_SPEED 100
#define LM_SPEED 200

//PB4读取主控的动作
int PB4(void)
{
	int x = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4)==1)
		x = 1;
	return x;
}

int PB5(void)
{
	int x = 1;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)==1)
		x = 0;
	return x;
}
//PB5发送

//初始化
void BspInit(void)
{
	pwm_init1();
	//	CANInit(ID_ML);
	//	encoder_init();
	//	exti_init();
	//TIM3_Cap_Init(50000,1000-1);
}

int main(void)
{
	BspInit();
	int PB_4 = 0;
	contr_motorspeed(0);
	while (!PB_4)
	{
		PB_4 = PB4();
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	contr_motorspeed(200);
	delay_ms(300);
	contr_motorspeed(0);
	int PB_5=0;
	while (PB_5)
	{
		PB_5=PB5();
	}
	contr_motorspeed(-200);
	delay_ms(300);
	contr_motorspeed(0);
}
