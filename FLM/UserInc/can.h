#ifndef _CAN_H
#define _CAN_H
#include "stm32f10x.h"

u8 ReturnOrder(void);
void OpenFilter(uint32_t FilterID);
void Can_ShowShort(short Data,int Pos);
void Can_ShowFloat(float Data,int Pos);
void Can_Send(u8 RECEIVER_ID,u8 VERIFY_WORD, u8 COMMAND);
void CANInit(int SELF_ID);
#endif

