/*
 * leds.c
 *
 *  Created on: Dec 28, 2014
 *      Author: daymoon
 */

#include "leds.h"

void leds_config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(KIT_LED_CLOCKS, ENABLE);

	// LED zelena
	GPIO_InitStructure.GPIO_Pin = KIT_GREEN_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(KIT_LED_PORT, &GPIO_InitStructure);

	// zalozeni ulohy blikani oranzove led
	if(Scheduler_Add_Task(LED_service, 0, LED_SERVICE_PERIOD) == SCH_MAX_TASKS)
	{
		// chyba pri zalozeni service
	}

}
