/*
 * services.c
 *
 *  Created on: Apr 16, 2020
 *      Author: Petr Dvorak
 */

#include "services.h"
#include "application.h"
#include "can.h"
#include "CANopen.h"

extern volatile uint16_t CO_timer1ms;

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

void CAN_service(void)
{
	can_test();
}

void CANopen_service(void)
{
	//CO_ReturnError_t err;
	static volatile uint16_t timer1msPrevious;
	volatile uint16_t timer1msCopy;
	volatile uint16_t timer1msDiff;

	timer1msCopy = CO_timer1ms;
	timer1msDiff = timer1msCopy - timer1msPrevious;
	timer1msPrevious = timer1msCopy;

	// CANopen process
	CO_process(CO, timer1msDiff, NULL);

	// PDO process
    if(CO->CANmodule[0]->CANnormal)
    {
        bool_t syncWas;

        /* Process Sync */
        syncWas = CO_process_SYNC(CO, CANOPEN_SERVICE_PERIOD * 1000);

        /* Read inputs */
        CO_process_RPDO(CO, syncWas);

        /* Further I/O or nonblocking application code may go here. */

        /* Write outputs */
        CO_process_TPDO(CO, syncWas, CANOPEN_SERVICE_PERIOD * 1000);

        /* verify timer overflow */
        if(0)
        {
            CO_errorReport(CO->em, CO_EM_ISR_TIMER_OVERFLOW, CO_EMC_SOFTWARE_INTERNAL, 0U);
        }
    }
    CO_OD_RAM.readInput8Bit[0] ^= 0xFF;
}


