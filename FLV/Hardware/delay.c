#include "stm32f10x.h"
#include "delay.h"

void delay_us(u32 time)
{
  u32 i=8*time;
  while(i--);
}


void delay_ms(u32 time)
{
  u32 i=8000*time;
  while(i--);
}
