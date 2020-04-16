/*
 * delay.h
 *
 *  Created on: Apr 16, 2020
 *      Author: Petr Dvorak
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "scheduler.h"
#include "services.h"

#define DELAY_FINISHED		10
#define DELAY_STARTED		0

extern void delay_ms(uint16_t time);
extern void Set_Delay_finished(uint8_t value);

#endif /* DELAY_H_ */
