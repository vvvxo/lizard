#ifndef __PID_H_
#define __PID_H_

#include "sys.h"
#include "usart.h"
#include "IN.h"
#include "delay.h"
#include <stdlib.h>

#define LM 0
#define LS 1
#define RM 2
#define RS 3
#define MOTOR_NUM 4

#define LM_COUNT_TO_ANGLE 1
#define LS_COUNT_TO_ANGLE 1
#define RM_COUNT_TO_ANGLE 1
#define RS_COUNT_TO_ANGLE 1

#define RM_COUNT_OF_CIRCLE 108000
#define LM_COUNT_OF_CIRCLE 108000
#define RS_COUNT_OF_CIRCLE 108000
#define LS_COUNT_OF_CIRCLE 108000

#define PID_LM_P 0.00f
#define PID_LM_I 0.00f
#define PID_LS_P 0.06f
#define PID_LS_I 0.00f
#define PID_RM_P 0.00f
#define PID_RM_I 0.00f
#define PID_RS_P 0.01f
#define PID_RS_I 0.00f

void SetSpeed(unsigned char MOTOR,int SPEED);
void SetAngle(unsigned char MOTOR_ANGLE, short Angle, short SPEED);
void EncoderValue(unsigned char motor);
void StandByMotor(unsigned char motor);
void TIM2_IRQHandler(void);
void CtrlMotorSpeed(unsigned char motor,short speed,short DIR);
void PIDInit(void);
#endif
