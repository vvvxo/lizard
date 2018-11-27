#ifndef _IN_H
#define _IN_H
#include "sys.h"
#include "pid.h"
void init_in(void);
void IN_Init0(void);
void IN_Init1(void);
void IN_Init2(void);
void StandByMotor(unsigned char val);
void CtrlMotorSpeed(unsigned char motor, int speed);
// void LSangle(char ANGLE, int SPEED);
// void LMangle(char ANGLE, int SPEED);
// void RSangle(char ANGLE, int SPEED);
// void RMangle(char ANGLE, int SPEED);

#define LAG_L 0
#define LAG_R 1

#define LED1 PFout(9)
#define LED0 PFout(10)

#define STAND_BY_LM 1
#define STAND_BY_LS 2
#define STAND_BY_RM 4
#define STAND_BY_RS 8
#define FORWARD 1
#define BACKWARD 2

#endif
