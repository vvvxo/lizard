# 电机引脚对应(电机控制引脚待定，输入捕获哪里可能存在冲突)(TIM3被使用)
## 左腿
### 主电机
IN1-PE0
IN2-PE1                                                                                   
PC6(TIM8_CH1)
PID:TIM1 PE9,PE11
600(90°转角)
### 从电机
IN1-PE2
IN2_PE3
PC7(TIM8_CH2)
PID:TIM2  PA5.PB3
285

## 右腿
### 主电机
IN1-PB12
IN2-PB13
PC8(TIM8_CH3)
PID:TIM4 PB6 PB7
7000(90°转角)
### 从电机
IN1-PB10
IN2-PB11
PC9(TIM8_CH4)
PID:TIM5 PA0,PA1
900(最大转角)

### 转动(这里封装成函数待修改)
正转:IN1=1,IN2=0
反转:IN1=0,IN2=1
刹车:IN1=1,IN2=1


IN.c为引脚初始化代码,初始状态为所有电机刹车

## CAN这里全部转换为USART最大发送八位数据，需要进行转换
CAN1_RX PA11
CAN1_TX PA12
## PID用掉TIM2

# 编码器
      TIM1 PD6 D8
      TIM2 PA0 PA1
      TIM4 PD12 PD13
      TIM9 PE5 PE6