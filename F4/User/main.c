#include "main.h"
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "IN.h"
#include "pid.h"
#include "run.h"
#include "encoder.h"
void Bsp_init(void)
{
//	TIM_PWM_Init();
	IN_Init0();
	IN_Init1();
	IN_Init2();
	IN_Init3();
	IN_Init4();
//	Usart_Init();
//	EncoderInit();
//	PIDInit();
}
int main(void)
{
	Bsp_init();
	while(1)
		{
			LED0=~LED0;
			Delay(10);
			LED1=~LED1;
			Delay(10);
		}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

