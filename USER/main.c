#include <stdlib.h>
#include "main.h"
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "IN.h"
#include "pid.h"
#include "run.h"
#include "encoder.h"
extern motor_num motor[4];
void Bsp_init(void)
{
	TIM_PWM_Init();
	Usart_Init();
	init_in();
	encoder_init();
	pid_init();
}

int main(void)
{
	Bsp_init();
	while (1)
	{
//		set_angle(LM, 60);
//		while(1);
//		
//		set_angle(LS, 45);
//		wait(LM,60);wait(LS,45);clear_init(LM|LS);
//		
//		set_angle(LS,-45);
//		wait(LS,-45);
//		set_angle(LM,-60);
//		wait(LM,-60);
//		
//				
	}
}
void wait(int MOTOR, int ANGLE)
{
	while (abs(motor[MOTOR].aim) < abs(ANGLE))
	{
	}
}

void clear_init(int MOTOR)
{
	motor[MOTOR].last_err=0;
	motor[MOTOR].sum_motorspeed=0;
	motor[MOTOR].present_err=0;
}
