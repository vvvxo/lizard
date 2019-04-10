#ifndef _IN_H
#define _IN_H
#include "sys.h"
#include "pid.h"
void IN_Init0(void);
void IN_Init1(void);
void IN_Init2(void);
void IN_Init3(void);
void IN_Init4(void);
void StandByMotor(unsigned char val);
void ChangeMotorDir(int DIR, int SPEED, int FOOT);
// void LSangle(char ANGLE, int SPEED);
// void LMangle(char ANGLE, int SPEED);
// void RSangle(char ANGLE, int SPEED);
// void RMangle(char ANGLE, int SPEED);

#define L 0
#define R 1

#define LED1 PFout(9)
#define LED0 PFout(10)

#define STAND_BY_LM 1
#define STAND_BY_LS 2
#define STAND_BY_RM 4
#define STAND_BY_RS 8
#define FORWARD 1
#define BACKWARD 2

#endif


