#include "timer.h"
#include "can.h"
#include "delay.h"
//arr：自动重装值
//psc：时钟预分频数
//定时器3通道1输入捕获配置

TIM_ICInitTypeDef TIM3_ICInitStructure;

void TIM3_Cap_Init(u16 arr, u16 psc)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);  //使能TIM3时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能GPIOB时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);  //复用时钟开启
    GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);  //重映射

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;     //PB4 清除之前设置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PB4 输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_4); //PB4 下拉

    //初始化定时器3 TIM3
    TIM_TimeBaseStructure.TIM_Period = arr;                     //设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;                  //预分频器
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);             //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位

    //初始化TIM3输入捕获参数
    TIM3_ICInitStructure.TIM_Channel = TIM_Channel_1;                //CC1S=01 	选择输入端 IC1映射到TI1上
    TIM3_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;     //上升沿捕获
    TIM3_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; //映射到TI1上
    TIM3_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;           //配置输入分频,不频
    TIM3_ICInitStructure.TIM_ICFilter = 0x00;                        //IC1F=0000 配置输入滤波器 不滤波
    TIM_ICInit(TIM3, &TIM3_ICInitStructure);

    //中断分组初始化
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;           //TIM3中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //先占优先级2级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        //从优先级0级
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;           //IRQ通道被使能
    NVIC_Init(&NVIC_InitStructure);                           //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

    TIM_ITConfig(TIM3, TIM_IT_Update | TIM_IT_CC1, ENABLE); //允许更新中断 ,允许CC1IE捕获中断

    TIM_Cmd(TIM3, ENABLE); //使能定时器5
}

u8 TIM3CH1_CAPTURE_STA = 0; //输入捕获状态
u16 TIM3CH1_CAPTURE_VAL;    //输入捕获值
u16 STARTHIGH;              //开始位
u16 STOPLOW;                //结束位
u16 ENCODERPWM;

//定时器4中断服务程序
void TIM3_IRQHandler(void)
{

    if ((TIM3CH1_CAPTURE_STA & 0X80) == 0) //还未成功捕获
    {
        if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //捕获2发生捕获事件
        {
            if (TIM3CH1_CAPTURE_STA & 0X40) //已经捕获到高电平了
            {
                STARTHIGH++;
                if (STARTHIGH > 128)
                    ENCODERPWM++;
            }
        }
        if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET) //捕获1发生捕获事件
        {
            if (TIM3CH1_CAPTURE_STA & 0X40) //捕获到一个下降沿
            {
                if (STARTHIGH < 128)
                    ENCODERPWM = 0;
                if (STARTHIGH + ENCODERPWM > 4223)
                    STOPLOW++;
            }
            if (STOPLOW > 127)
                ENCODERPWM = 0;
        }
    }

    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1 | TIM_IT_Update); //清除中断标志位
}

void printencoderpwm(void)
{
	Can_ShowShort(ENCODERPWM,4);
	delay_ms(10);
}
