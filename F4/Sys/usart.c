#include "usart.h"


union
{
	float float_resulte;
	int	  int_resulte;	
	char  raw_data[4];
}UsartData;

void Usart_Init(void)
{
//	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	

//	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2; 
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);
//	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

	USART_OverSampling8Cmd(USART1, ENABLE);  
		
	USART_InitStructure.USART_BaudRate = 38400;
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

void SendFloatDataToComputer(float data, unsigned char pos)
{
	UsartData.float_resulte = data;

	USART_SendData(USART1,0x55);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	USART_SendData(USART1,0x52);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	
	for(int i = 0; i < 4; i++)
	{
		USART_SendData(USART1,UsartData.raw_data[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);		
	}
	
	USART_SendData(USART1,0xFD);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	
	USART_SendData(USART1,pos);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	return;
}

void SendIntDataToComputer(int data, unsigned char pos)
{
	UsartData.int_resulte = data;
	
	USART_SendData(USART1,0x55);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	USART_SendData(USART1,0x52);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	for(int i = 0; i < 4; i++)
	{
		USART_SendData(USART1,UsartData.raw_data[i]);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);		
	}
	
	USART_SendData(USART1,0xFE);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	USART_SendData(USART1,pos);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);

	return;
}
