#include "delay.h"
#include "pid.h"
void Delay(unsigned char delayTime)
{
	int i;
	for (i = 0; i <= 255; i++)
			while (delayTime--)
				;
}

void delay_ms(u32 time)
{
	u32 i = 16000 * time;
	while (i--)
		;
}

void testled1(void)
{
	LED0 = ~LED0;
	delay_ms(1000);
	LED1 = ~LED1;
	delay_ms(1000);
}

void testled(void)
{
	while (1)
	{
		LED0 = ~LED0;
		delay_ms(100);
		LED1 = ~LED1;
		delay_ms(100);
	}
}
