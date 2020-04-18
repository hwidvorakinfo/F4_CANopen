/*
 * can.h
 *
 *  Created on: 16. 4. 2020
 *      Author: Petr Dvorak
 */

#ifndef CAN_H_
#define CAN_H_

#include "stm32f4xx.h"
#include "defs.h"
#include "stm32f4xx_conf.h"

#define CANx                       CAN2
#define CAN_MASTER				   CAN1
#define CAN_CLK                    RCC_APB1Periph_CAN2
#define CAN_MASTER_CLK			   RCC_APB1Periph_CAN1
#define CAN_RX_PIN                 GPIO_Pin_5
#define CAN_TX_PIN                 GPIO_Pin_6
#define CAN_GPIO_PORT              GPIOB
#define CAN_GPIO_CLK               RCC_AHB1Periph_GPIOB
#define CAN_AF_PORT                GPIO_AF_CAN2
#define CAN_RX_SOURCE              GPIO_PinSource5
#define CAN_TX_SOURCE              GPIO_PinSource6

//#define CAN_RECEIVER
#define CAN_TRANSMITER

/**
  * @brief  Configures the CAN environment.
  * @param  None
  * @retval None
  */
void can_init(void);
/**
  * @brief  Sends CAN messages
  * @param  None
  * @retval None
  */
void can_test(void);
void can_debug(void);


#endif /* CAN_H_ */
