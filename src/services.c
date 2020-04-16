/*
 * services.c
 *
 *  Created on: Apr 16, 2020
 *      Author: Petr Dvorak
 */

#include "services.h"


void LED_service(void)
{
	uint16_t led_port;

	led_port = GPIO_ReadOutputData(KIT_LED_PORT);
	if (led_port & KIT_GREEN_LED)
	{
		GPIO_ResetBits(KIT_LED_PORT, KIT_GREEN_LED);				// orange LED off
	}
	else
	{
		GPIO_SetBits(KIT_LED_PORT, KIT_GREEN_LED);					// orange LED off
	}
}

void Delay_service(void)
{
	Set_Delay_finished(DELAY_FINISHED);
}


