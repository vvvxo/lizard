#ifndef _PID_H
#define _PID_H

#include "sys.h"
#include "usart.h"
#include "IN.h"
#include "delay.h"

#define LM 0
#define LS 1
#define RM 2
#define RS 3
#define MOTOR_NUMBER 4

typedef struct
{
    unsigned char motor_num;
    float aim;
    float pid_p;
    float pid_i;
    float pid_d;
    float encoder_one;
    float one_encoder;
    float encoderspeed;
    float present_err;
    float present_err2;
    float sum_motorspeed;
    float sum_motorspeed2;
    float err_all;
    float err_all2;
    short pid_speed;
    short pid_speed2;
    float last_err;
    float ENCODER_DIRECT;
	short encoder;
} motor_num;

void set_angle(int MOTOR, int angle);
void pid_init(void);
void pid(int MOTOR, TIM_TypeDef *TIMx);
int limit(int ENTER, int RETURN);
void send_data(unsigned char MOTOR);
#endif
