/*
 * dcmi.h
 *
 *  Created on: 14. 8. 2019
 *      Author: Petr Dvorak
 */

#ifndef DCMI_H_
#define DCMI_H_

#include "stm32f4xx.h"
#include "defs.h"
#include "stm32f4xx_conf.h"

#define DCMI_DR_ADDRESS		(uint32_t)(DCMI_BASE + 0x28)
#define SPI_DR_ADDRESS		(uint32_t)(&(LCD_SPI->DR))

uint8_t dcmi_get_index(void);
void dcmi_set_index(uint8_t value);
void dcmi_init(void);

#endif /* DCMI_H_ */
