#include "pid.h"

int sum_motorspeed = 0;
int encoderspeed = 0;
int Aim_Speed = 100;

int EncoderPID_LM=0;
int Encoderspeed_LM = 0;
int Present_Err_LM = 0;
int Sum_MotorSpeed_LM = 0;

int EncoderPID_LS = 0;
int Encoderspeed_LS = 0;
int Present_Err_LS = 0;
int Sum_MotorSpeed_LS = 0;

int EncoderPID_RM;
int Encoderspeed_RM = 0;
int Present_Err_RM = 0;
int Sum_MotorSpeed_RM = 0;

int EncoderPID_RS;
int Encoderspeed_RS = 0;
int Present_Err_RS = 0;
int Sum_MotorSpeed_RS = 0;

int PID_DIR;
unsigned char motor = 10;
float present_err;
float last_err;

void SetSpeed(unsigned char MOTOR, int SPEED)
{
	motor = MOTOR;
	Aim_Speed = SPEED;
}

void StandByMotor(unsigned char Stand_Motor)
{
	switch (Stand_Motor)
	{
	case LM:
		SetSpeed(LM, 0);
		break;

	case LS:
		SetSpeed(LS, 0);
		break;

	case RM:
		SetSpeed(RM, 0);
		break;

	case RS:
		SetSpeed(RS, 0);
		break;
	default:
		break;
	}
}

void pid()
{
	if (Aim_Speed < 0)
		PID_DIR = 0;
	else if (Aim_Speed == 0)
	{
	}
	else
		PID_DIR = 1;

	switch (motor)
	{
	case LM:
		Encoderspeed_LM = -(short)(TIM1->CNT); //编码器数据反馈
		TIM1->CNT = 0;
		//EncoderValue(encoderspeed);
		Present_Err_LM = Aim_Speed - Encoderspeed_LM; //得到差值
		Present_Err_LM += Present_Err_LM * PID_LM_P + last_err * PID_LM_I;
		last_err = Present_Err_LM;

		CtrlMotorSpeed(LM, abs(Present_Err_LM), PID_DIR);
		break;
	case LS:
		//Encoderspeed_LS = -(short)(TIM4->CNT); //编码器数据反馈
		//TIM4->CNT = 0;
		//EncoderPID_LS += Encoderspeed_LS;
		//USART_SendData(USART1, 1);
		//Present_Err_LS = Aim_Speed - Encoderspeed_LS; //得到差值
		Sum_MotorSpeed_LS += (int)(Present_Err_LS* PID_LS_P);
						while(1)
		{
		LED0=~LED0;
	delay_ms(10);
	LED1=~LED1;
	delay_ms(10);
		}


		last_err = Present_Err_LS;

		CtrlMotorSpeed(LS, abs(Sum_MotorSpeed_LS), -PID_DIR);
		break;
	case RM:
		Encoderspeed_RM = -(short)(TIM5->CNT); //编码器数据反馈
		TIM5->CNT = 0;

		EncoderPID_RM += Encoderspeed_RM;
		Present_Err_RM = Aim_Speed - Encoderspeed_RM; //得到差值
		Sum_MotorSpeed_RM += Present_Err_RM * PID_RM_P + last_err * PID_RM_I;
		last_err = Present_Err_RM;

		CtrlMotorSpeed(RM, Sum_MotorSpeed_RM, PID_DIR);
		break;
	case RS:
		Encoderspeed_RS = -(short)(TIM3->CNT); //编码器数据反馈
		TIM8->CNT = 0;
		EncoderPID_RS += Encoderspeed_RS;
		Present_Err_RS = Aim_Speed - Encoderspeed_RS; //得到差值
		Sum_MotorSpeed_RS += Present_Err_RS * PID_RS_P;
		last_err = Present_Err_RS;

		CtrlMotorSpeed(RS, Sum_MotorSpeed_RS, PID_DIR);
		break;
	default:
		break;
	}
}

void TIM2_IRQHandler(void)
{
	pid();
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
}

//控制电机的速度和方向,PID输入电机和速度,dir制电机正反转
void CtrlMotorSpeed(unsigned char motor, short speed, short DIR)
{
	//分支选择电机及其速度
	switch (motor)
	{
	case LM:
		if (DIR)
		{
			PBout(3) = 1;
			PBout(5) = 0;
		}
		else
		{
			PBout(3) = 0;
			PBout(5) = 1;
		}
		TIM_SetCompare1(TIM8, speed);
		break;

	case LS:
		if (DIR)
		{

			PAout(3) = 1;
			PAout(4) = 0;
		}
		else
		{
			PAout(3) = 0;
			PAout(4) = 1;
		}
		TIM_SetCompare2(TIM8, speed);
		break;

	case RM:
		if (DIR)
		{
			PCout(1) = 1;
			PCout(2) = 0;
		}
		else
		{
			PCout(1) = 0;
			PCout(2) = 1;
		}
		TIM_SetCompare3(TIM8, speed);
		break;

	case RS:
		if (DIR)
		{
			PCout(3) = 1;
			PCout(4) = 0;
		}
		else
		{
			PCout(3) = 0;
			PCout(4) = 1;
		}
		TIM_SetCompare4(TIM8, speed);
		break;

	default:
		break;
	}
}

void PIDInit(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseStructure.TIM_Prescaler = 360 - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x05;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

////打印编码器获得的值
//int dir = 0;
//int buff;
//void EncoderValue(unsigned char motor)
//{
//	buff = encoderCount[motor];
//	while (buff > 255)
//	{
//		SendData(dir++);
//		SendData(0xA2);
//		buff /= 255;
//	}
//	SendData(0xA1);
//	Delay(1);
//	SendData(dir);
//	Delay(1);
//	SendData(0xA2);
//	Delay(1);
//	SendData(buff);
//	Delay(1);
//	SendData(0xA3);
//	Delay(1);
//	Delay(255);
//}
