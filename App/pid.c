#include <stdlib.h>
#include "pid.h"
motor_num motor[4] = {
	{LM, 0, 2.20, 0.100, 0.000, 98588, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{LS, 0, 0.20, 0.000, 0.000, 24195, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{RM, 0, 0.00, 0.000, 0.000, 20116, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{RS, 0, 0.25, 0.000, 0.000, 50832, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

void set_angle(int MOTOR, int angle)
{
	
	motor[MOTOR].aim = angle;
}

void pid(int MOTOR, TIM_TypeDef *TIMx)
{
	motor[MOTOR].encoder += -(short)TIMx->CNT;
	TIMx->CNT = 0;
	motor[MOTOR].pid_speed = (int)motor[MOTOR].encoder;
	motor[MOTOR].present_err = motor[MOTOR].aim - (motor[MOTOR].pid_speed * 10 / motor[MOTOR].encoder_one) * 36;
	motor[MOTOR].err_all += limit(motor[MOTOR].present_err, 300);

	motor[MOTOR].sum_motorspeed = motor[MOTOR].present_err * motor[MOTOR].pid_p +
								  limit(motor[MOTOR].err_all, 100) * motor[MOTOR].pid_i -
								  limit((motor[MOTOR].present_err - motor[MOTOR].last_err), 1000) *
									  motor[MOTOR].pid_d;
	motor[MOTOR].last_err = motor[MOTOR].present_err;
	
	//motor[MOTOR].pid_speed2 += motor[MOTOR].sum_motorspeed - motor[MOTOR].pid_speed;
	USARTSendFloat(motor[RS].present_err,1);USARTSendInt(motor[RS].pid_speed,1);
	CtrlMotorSpeed(MOTOR, motor[MOTOR].sum_motorspeed);
}

int limit(int ENTER, int RETURN)
{
	if (abs(ENTER) > abs(RETURN))
		return RETURN;
	else
		return ENTER;
}

void pid_init(void)
{

	TIM_TimeBaseInitTypeDef TIM;
	NVIC_InitTypeDef Nvic;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);

	Nvic.NVIC_IRQChannel = TIM7_IRQn;
	Nvic.NVIC_IRQChannelPreemptionPriority = 0x0;
	Nvic.NVIC_IRQChannelSubPriority = 0x0;
	Nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&Nvic);

	TIM.TIM_Period = 100 - 1;//最大计数值
	TIM.TIM_Prescaler = 480 - 1;//时钟预分频
	TIM.TIM_CounterMode = TIM_CounterMode_Up;
	TIM.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM7, &TIM);

	TIM_Cmd(TIM7, ENABLE);
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE); //使能TIM7中断 向上溢出中断
	TIM_ClearFlag(TIM7, TIM_FLAG_Update);	  //清除TIM标志位
}

void TIM7_IRQHandler(void)
{
	pid(LM, TIM1);
	pid(LS, TIM2);
	pid(RM, TIM4);
	pid(RS, TIM5);
	TIM_ClearFlag(TIM7, TIM_IT_Update);
}

void send_data(unsigned char MOTOR)
{
	USARTSendInt(1, motor[MOTOR].pid_speed);
}
