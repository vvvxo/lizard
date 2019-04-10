#include "stm32f10x.h"
#include "sys.h"
#include "REG.h"
#include "can.h"
#include "delay.h"
#include "timer.h"
#include "pid.h"

//转动一圈encoder的值
#define ONE_ENCODER 14500

//左腿主电机和从电机
#define LM_ANGLE 60
#define LS_ANGLE 40

#define LS_SPEED 100
#define LM_SPEED 200

//PB5主电机的动作
int PB5(void)
{
	int x = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_5)==1)
		x = 1;
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
	int PB_5 = 0;
	while (!PB_5)
	{
		PB_5 = PB5();
	}
	GPIO_SetBits(GPIOB,GPIO_Pin_5);
	contr_motorspeed(1000);
	delay_ms(1000);
	contr_motorspeed(-1000);
	delay_ms(1000);
	GPIO_SetBits(GPIOB,GPIO_Pin_4);
	contr_motorspeed(0);
}
