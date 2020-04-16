/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    16-April-2020
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f4xx.h"
#include "leds.h"
			
int main(void)
{
	leds_config();

	while (1)
	{
		Scheduler_Dispatch_Tasks();						// sprava tasku - spousti tasky, maze neplatne tasky
	}
}
