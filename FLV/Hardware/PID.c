#include "sys.h"
#include "can.h"
#define P  0.05
#define I  0.02
//int encoderplus;
//int can_motor_speed=50;
int can_motor_speed = 0;
long encoderplus = 0;
float present_err = 0;
int encoderP = 0;
int encoderspeed;
int last_err = 0;
int sum_motorspeed = 0;
void TIM2_IRQHandler() //采集两路电机的编码器的值
{
	encoderspeed = -(short)(TIM3->CNT); //编码器数据反馈
	TIM3->CNT = 0;

	encoderplus += encoderspeed;

	present_err = can_motor_speed - encoderspeed; //得到差值

	sum_motorspeed += present_err * P+last_err*I;

	last_err = present_err;
	contr_motorspeed((int)sum_motorspeed);

	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

//encoderplaus值清零
void ClearEncoderplus(void)
{
	encoderplus=0;
	encoderspeed=0;
}

//设置速度
void setspeed(int speed)
{
	can_motor_speed = speed;
}

//设置角度,转动的速度,角度只能为正,通过速度调节方向
void setangle(int ANGLE, int ONE_ENCODER,int SPEED)
{
	can_motor_speed = SPEED;
	while (abs(encoderplus) < (ONE_ENCODER*ANGLE / 360))
	{
	}
	setspeed(0);
}

//打印encoderplus
void encoderplusshowshort(void)
{
	Can_ShowShort(encoderplus, 1);
}
