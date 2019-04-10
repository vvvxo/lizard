#include "can.h"
#include "REG.h"
union {
	char RAWData[4];
	short Resulet[2];
} CANRecive;

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Open_Filter(uint32_t id)
{
	CAN_FilterInitTypeDef CAN_FilterInitStructure;

	id = id & 0x07FF;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0; //选择邮箱
	CAN_FilterInitStructure.CAN_FilterIdHigh = id << 5;
	CAN_FilterInitStructure.CAN_FilterIdLow = id << 5;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;  //屏蔽位模式
	CAN_FilterInitStructure.CAN_FilterNumber = 1;					 //选择过滤器
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_16bit; //十六位ID(11位可用)三十二位ID(29)
	CAN_FilterInit(&CAN_FilterInitStructure);
}

void Can_Send(u8 RECEIVER_ID, u8 VERIFY_WORD, u8 COMMAND)
{
	CanTxMsg TxMessage;

	TxMessage.StdId = RECEIVER_ID;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 4;

	TxMessage.Data[0] = VERIFY_WORD;
	TxMessage.Data[1] = COMMAND;
	TxMessage.Data[2] = 0;
	TxMessage.Data[3] = 0;
	//	TxMessage.Data[4]= 0;
	//	TxMessage.Data[5]= 0;
	//	TxMessage.Data[6]= 0;
	//	TxMessage.Data[7]= 0;

	CAN_Transmit(CAN1, &TxMessage);
}

void Can_ShowShort(short Data, int Pos) //不通过队列发送
{
	CanTxMsg TxMessage;

	TxMessage.StdId = 0x0002; //TFT显示数据；
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 4;

	TxMessage.Data[0] = 0xFE;
	TxMessage.Data[1] = Pos;
	TxMessage.Data[2] = *((char *)(&Data));
	TxMessage.Data[3] = *((char *)(&Data) + 1);
	//	TxMessage.Data[4]= 0;
	//	TxMessage.Data[5]= 0;
	//	TxMessage.Data[6]= 0;
	//	TxMessage.Data[7]= 0;

	CAN_Transmit(CAN1, &TxMessage);
}

void Can_ShowFloat(float Data, int Pos) //不通过队列发送
{
	CanTxMsg TxMessage;

	TxMessage.StdId = 0x0002; //TFT显示数据；
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 8;

	TxMessage.Data[0] = 0xFD;
	TxMessage.Data[1] = Pos;
	TxMessage.Data[2] = *((char *)(&Data));
	TxMessage.Data[3] = *((char *)(&Data) + 1);
	TxMessage.Data[4] = *((char *)(&Data) + 2);
	TxMessage.Data[5] = *((char *)(&Data) + 3);
	TxMessage.Data[6] = 0;
	TxMessage.Data[7] = 0;

	CAN_Transmit(CAN1, &TxMessage);
}

u8 order;
void USB_LP_CAN1_RX0_IRQHandler(void)
{
	CanRxMsg RxMessage;

	CAN_Receive(CAN1, CAN_FIFO0, &RxMessage);
	if (RxMessage.Data[0] == ID_SL)
		order = RxMessage.Data[1];
	return;
	//	if(SELF_LEG == 1)
	//	{
	//		CANRecive.RAWData[0] = RxMessage.Data[0];
	//		CANRecive.RAWData[1] = RxMessage.Data[1];
	//		CANRecive.RAWData[2] = RxMessage.Data[2];
	//		CANRecive.RAWData[3] = RxMessage.Data[3];
	//		CANAngle = JointCaculate(CANRecive.Resulet[0], CANRecive.Resulet[1]);
	//	}
	//	else if(SELF_LEG == 2)
	//	{
	//		CANRecive.RAWData[0] = RxMessage.Data[4];
	//		CANRecive.RAWData[1] = RxMessage.Data[5];
	//		CANRecive.RAWData[2] = RxMessage.Data[6];
	//		CANRecive.RAWData[3] = RxMessage.Data[7];
	//
	//		CANAngle = JointCaculate(CANRecive.Resulet[0], CANRecive.Resulet[1]);
	//	}
}

u8 ReturnOrder(void)
{
	return order;
}

void CANInit(int SELF_ID)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	CAN_InitTypeDef CAN_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_PinRemapConfig(GPIO_Remap1_CAN1, ENABLE);

	CAN_DeInit(CAN1);
	CAN_StructInit(&CAN_InitStructure);

	CAN_InitStructure.CAN_ABOM = DISABLE;		  //是否使用自动离线管理
	CAN_InitStructure.CAN_AWUM = DISABLE;		  //是否使用睡眠自动唤醒
	CAN_InitStructure.CAN_BS1 = CAN_BS1_2tq;	  //影响波特率
	CAN_InitStructure.CAN_BS2 = CAN_BS2_3tq;	  //影响波特率
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal; //正常模式
	CAN_InitStructure.CAN_NART = DISABLE;		  //是否使用非自动重传输
	CAN_InitStructure.CAN_Prescaler = 6;		  //影响波特率					48M/((7+8+1)*6)=500K
	CAN_InitStructure.CAN_RFLM = DISABLE;		  //是否使用FIFO锁定（覆盖旧数据）
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;	  //重新同步跳跃宽度（影响波特率）
	CAN_InitStructure.CAN_TTCM = DISABLE;		  //是否使用时间触发模式
	CAN_InitStructure.CAN_TXFP = DISABLE;		  //是否使用发送优先级（由ID决定）

	CAN_Init(CAN1, &CAN_InitStructure);
	CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);

	NVIC_Config();
	Open_Filter(SELF_ID);
}
