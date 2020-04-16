/*
 * leds.h
 *
 *  Created on: Dec 28, 2014
 *      Author: daymoon
 */

#ifndef INCLUDES_LEDS_H_
#define INCLUDES_LEDS_H_

#include "stm32f4xx.h"
#include "stm32f4xx_conf.h"
#include "scheduler.h"
#include "defs.h"
#include "services.h"

#define KIT_LED_PORT	GPIOB
#define KIT_LED_CLOCKS	RCC_AHB1Periph_GPIOB
#define KIT_GREEN_LED	GPIO_Pin_1

extern void leds_config(void);

#endif /* INCLUDES_LEDS_H_ */
