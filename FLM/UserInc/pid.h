#ifndef _PID_H
#define _PID_H
void TIM2_IRQHandler(void);
void setspeed(int i);
void setangle(int ANGLE, int ONE_ENCODER,int SPEED);
void encoderplusshowshort(void);
void ClearEncoderplus(void);
#endif
