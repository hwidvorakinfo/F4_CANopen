/*
 * services.h
 *
 *  Created on: Apr 16, 2020
 *      Author: Petr Dvorak
 */

#ifndef INCLUDES_SERVICES_H_
#define INCLUDES_SERVICES_H_

//#include <stm32f4xx_custom.h>
#include "stm32f4xx_conf.h"
#include "leds.h"
#include "scheduler.h"
#include "mcuperipherals.h"
#include "delay.h"


#define MILISEKUND 	/1000

// periody jsou v milisekundach, neboli zakladni periode SysTick casovace
#define LED_SERVICE_PERIOD				(SCHEDULERPERIOD * 500 MILISEKUND)
#define CANOPEN_SERVICE_PERIOD			(SCHEDULERPERIOD * 10 MILISEKUND)

#define FREE			0
#define STARTED			127
#define REQUESTED		64


// sluzby
void LED_service(void);
void Delay_service(void);
void CANopen_service(void);


#endif /* INCLUDES_SERVICES_H_ */
