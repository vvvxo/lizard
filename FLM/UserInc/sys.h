#ifndef _sys_h
#define _sys_h
#include "stm32f10x.h"
void delay_nus(u16 time);
void delay_nms(u16 time);
void can_init(void);

int Get_MotorState(int Motor_Num);
//int Clear_MotorState(int Motor_Num);
void Can_SendDiPan(int date);
void CAN_SendSignal1(void);

void pwm_init1(void);
void contr_motorspeed(int partvalue_motor_speed);

void exti_init(void);
void encoder_init(void);
#endif
