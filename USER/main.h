
#ifndef __MAIN_H
#define __MAIN_H
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void TimingDelay_Decrement(void);
void wait(int MOTOR, int ANGLE);
void clear_init(int MOTOR);

#endif /* __MAIN_H */

    /************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
