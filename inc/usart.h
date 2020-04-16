/*
 * usart.h
 *
 *  Created on: 3. 5. 2019
 *      Author: daymoon
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f4xx.h"
#include "defs.h"

#define UARTBAUDRATE				115200

#define RXBUFFERSIZE				128
#define TXBUFFERSIZE				128

#define USART_TX_CLOCKS				RCC_AHB1Periph_GPIOA
#define USART_TX_PORT				GPIOA
#define USART_TX_PIN				GPIO_Pin_9
#define USART_TX_SOURCE				GPIO_PinSource9
#define USART_TX_AF					GPIO_AF_USART1

#define USART_RX_CLOCKS				RCC_AHB1Periph_GPIOA
#define USART_RX_PORT				GPIOA
#define USART_RX_PIN				GPIO_Pin_10
#define USART_RX_SOURCE				GPIO_PinSource10
#define USART_RX_AF					GPIO_AF_USART1

#define USART_CLOCKS				RCC_APB2Periph_USART1
#define USART						USART1
#define USART_IRQn					USART1_IRQn
#define USART_IRQHandler			USART1_IRQHandler

typedef enum {
	READYTOSEND = 0,
	READYTORECEIVE,
	TRANSFERING,
	RECEIVING,
	TRANSFERDONE,
	RECEIVEDONE
} USARTSTATUS;

typedef struct {
	uint8_t buffer[TXBUFFERSIZE];
	uint8_t index;
	USARTSTATUS status;
} usart_data_t;


void usart_config(void);
void usart_send_text(uint8_t *text);
void usart_newline(void);
void usart_wait_until_sent(void);
void usart_release_Rx_buffer();
uint8_t *get_Rx_buffer(void);

#endif /* USART_H_ */
