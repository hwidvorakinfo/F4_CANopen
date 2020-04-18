/*
 * leds.c
 *
 *  Created on: Dec 28, 2014
 *      Author: daymoon
 */

#include "leds.h"
#include "application.h"

void leds_config(void)
{
	// zalozeni ulohy blikani oranzove led
	if(Scheduler_Add_Task(LED_service, 0, LED_SERVICE_PERIOD) == SCH_MAX_TASKS)
	{
		// chyba pri zalozeni service
	}
}

void leds_set_function_led(uint8_t state)
{
	if (state)
	{
		GPIO_SetBits(FUNCTION_LED_PORT, FUNCTION_LED_PIN);
	}
	else
	{
		GPIO_ResetBits(FUNCTION_LED_PORT, FUNCTION_LED_PIN);
	}
}
