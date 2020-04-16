/*
 * services.c
 *
 *  Created on: Apr 16, 2020
 *      Author: Petr Dvorak
 */

#include "services.h"
#include "application.h"


void LED_service(void)
{
	uint16_t led_port;

	led_port = GPIO_ReadOutputData(STATUS_LED_PORT);
	if (led_port & STATUS_LED_PIN)
	{
		GPIO_ResetBits(STATUS_LED_PORT, STATUS_LED_PIN);				// orange LED off
	}
	else
	{
		GPIO_SetBits(STATUS_LED_PORT, STATUS_LED_PIN);					// orange LED off
	}
}

void Delay_service(void)
{
	Set_Delay_finished(DELAY_FINISHED);
}


