#include "usart.h"
#include "delay.h"
unsigned char buff[4];
void Usart_Init(void)
{
//	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	

	// NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	// NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
	// NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	// NVIC_Init(&NVIC_InitStructure);
	// USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
 
  //USART_OverSampling8Cmd(USART1, ENABLE);  
		
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_Cmd(USART1,ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	USART_ClearFlag(USART1, USART_FLAG_TC);
}


void Int2Byte4(int data){
	buff[0] = data;
	buff[1] = data >> 8;
	buff[2] = data >> 16;
	buff[3] = data >> 24;
}

void Float2Byte4(float data){
    char* temp;
    temp = (char*)(&data);
    buff[0] = temp[0];
    buff[1] = temp[1];
    buff[2] = temp[2];
    buff[3] = temp[3];
}

void USARTSendInt(int data,unsigned char pos){
	int i = 0;
	USART_SendData(USART1,0xA1);
	while(USART_GetITStatus(USART1,USART_IT_TXE))
		;
	
	delay_ms(10);
	USART_SendData(USART1,0xA2);
	while(USART_GetITStatus(USART1,USART_IT_TXE))
		;
	
	delay_ms(1);	
	Int2Byte4(data);
	while(i < 4){
		USART_SendData(USART1,buff[i]);
		i++;
		while(USART_GetITStatus(USART1,USART_IT_TXE))
			;	
		
		delay_ms(10);	
	}
	
	USART_SendData(USART1,pos);
	while(USART_GetITStatus(USART1,USART_IT_TXE))
		;	
	
	delay_ms(10);	
}

void USARTSendFloat(float data,unsigned char pos){
	int i = 0;
	USART_SendData(USART1,0xA1);
	while(USART_GetITStatus(USART1,USART_IT_TXE))
		;
	
	Delay(1);
	USART_SendData(USART1,0xA3);
	while(USART_GetITStatus(USART1,USART_IT_TXE))
		;
	
	Delay(1);	
	Float2Byte4(data);
	while(i < 4){
		USART_SendData(USART1,buff[i]);
		i++;
		while(USART_GetITStatus(USART1,USART_IT_TXE))
			;	
		Delay(1);
	}
	
	USART_SendData(USART1,pos);
	while(USART_GetITStatus(USART1,USART_IT_TXE))
		;	

	Delay(1);		
}
