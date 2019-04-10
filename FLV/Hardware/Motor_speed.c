#include "stm32f10x.h"
#include "sys.h"
void contr_motorspeed(int partvalue_motor_speed)
{

	if (partvalue_motor_speed > 0)
	{
		TIM1->CCER = 0x0580;
	}
	else if (partvalue_motor_speed < 0)
	{
		TIM1->CCER = 0x0850;
		partvalue_motor_speed = -partvalue_motor_speed;
	}
	partvalue_motor_speed = 700 - partvalue_motor_speed;
	if (partvalue_motor_speed <= 10) { partvalue_motor_speed = 10; }
	TIM1->CCR2 = partvalue_motor_speed;
	TIM1->CCR3 = partvalue_motor_speed;
}
