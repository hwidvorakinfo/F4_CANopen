/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.3.0
  * @date    13-November-2013
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "scheduler.h"
#include "can.h"
#include "leds.h"
#include "CO_driver_target.h"
#include "CANopen.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

extern CanRxMsg RxMessage;
extern volatile uint16_t CO_timer1ms;

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	// spust pruchod schedulerem
	Run_scheduler();

	CO_timer1ms++;
}

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  This function handles CAN2 RX0 request.
  * @param  None
  * @retval None
  */
void CAN2_RX0_IRQHandler(void)
{
	// FIFO0
	CO_CANinterrupt_Rx0(CO->CANmodule[0]);
#ifdef CAN_RECEIVER
	volatile uint8_t data;
	CAN_Receive(CANx, CAN_FIFO0, &RxMessage);

	if ((RxMessage.StdId == 0x321) && (RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 1))
	{
		if (RxMessage.Data[0] == 0x55)
		{
			leds_set_function_led(1);
		}
		else
		if (RxMessage.Data[0] == 0xAA)
		{
			leds_set_function_led(0);
		}
	}
#endif
}

/**
  * @brief  This function handles CAN2 RX1 request.
  * @param  None
  * @retval None
  */
void CAN2_RX1_IRQHandler(void)
{
	// FIFO1
	CO_CANinterrupt_Rx1(CO->CANmodule[0]);
#ifdef CAN_RECEIVER
	volatile uint8_t data;
	CAN_Receive(CANx, CAN_FIFO1, &RxMessage);

	if ((RxMessage.StdId == 0x321) && (RxMessage.IDE == CAN_ID_STD) && (RxMessage.DLC == 1))
	{
		if (RxMessage.Data[0] == 0x55)
		{
			leds_set_function_led(1);
		}
		else
		if (RxMessage.Data[0] == 0xAA)
		{
			leds_set_function_led(0);
		}
	}
#endif
}

/**
  * @brief  This function handles CAN2 TX event.
  * @param  None
  * @retval None
  */
void CAN2_TX_IRQHandler(void)
{
	// transimit mailbox empty
	CO_CANinterrupt_Tx(CO->CANmodule[0]);
#ifdef CAN_TRANSMITER

#endif
}

/**
  * @brief  This function handles CAN2 SCE event.
  * @param  None
  * @retval None
  */
void CAN2_SCE_IRQHandler(void)
{
	// status change error
#ifdef CAN_TRANSMITER

#endif
}


/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
