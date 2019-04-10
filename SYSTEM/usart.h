#ifndef _USART_H
#define _USART_H
#include "stm32f4xx.h"

void Usart_Init(void);
void USARTSendFloat(float data, unsigned char pos);
void USARTSendInt(int data,unsigned char pos);

#endif
