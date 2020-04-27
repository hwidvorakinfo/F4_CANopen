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
#include "clock.h"
#include "mcuperipherals.h"
#include "scheduler.h"
#include "can.h"
#include "CANopen.h"
			
int main(void)
{
	Clock_config();
	Scheduler_init();									// inicializace kooperativniho scheduleru a jeho odstartovani
	Scheduler_start();									// nyni je jiz mozne zakladat tasky
	mcuperipherals_init();								// inicializace periferii
	leds_config();										// stavova led
	can_init();
	//can_debug();

	while (1)
	{
		Scheduler_Dispatch_Tasks();						// sprava tasku - spousti tasky, maze neplatne tasky
	}
}
