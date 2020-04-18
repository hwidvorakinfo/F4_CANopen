/*
 * can.c
 *
 *  Created on: 16. 4. 2020
 *      Author: Petr Dvorak
 */

#include "can.h"
#include "scheduler.h"
#include "services.h"

CAN_InitTypeDef        CAN_InitStructure;
CAN_FilterInitTypeDef  CAN_FilterInitStructure;
static volatile CanTxMsg TxMessage;
volatile CanRxMsg RxMessage;

static void can_config(void);
static void can_irq_config(void);
static void Init_RxMes(CanRxMsg *RxMessage);

/**
  * @brief  Configures the CAN environment.
  * @param  None
  * @retval None
  */
void can_init(void)
{
	can_irq_config();
	can_config();

	// zalozeni ulohy posilani CAN zprav
	if(Scheduler_Add_Task(CAN_service, 0, CAN_SERVICE_PERIOD) == SCH_MAX_TASKS)
	{
		// chyba pri zalozeni service
	}
}


/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
static void can_config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	/* CAN GPIOs configuration **************************************************/

	/* Enable GPIO clock */
	RCC_AHB1PeriphClockCmd(CAN_GPIO_CLK, ENABLE);

	/* Connect CAN pins to AF9 */
	GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_RX_SOURCE, CAN_AF_PORT);
	GPIO_PinAFConfig(CAN_GPIO_PORT, CAN_TX_SOURCE, CAN_AF_PORT);

	/* Configure CAN RX and TX pins */
	GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN | CAN_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
	GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

	/* CAN configuration ********************************************************/
	/* Enable CAN clock */
	RCC_APB1PeriphClockCmd(CAN_CLK, ENABLE);
	RCC_APB1PeriphClockCmd(CAN_MASTER_CLK, ENABLE);

	/* CAN register init */
	CAN_DeInit(CANx);
	CAN_DeInit(CAN_MASTER);

	/* CAN cell init */
	CAN_InitStructure.CAN_TTCM = DISABLE;
	CAN_InitStructure.CAN_ABOM = DISABLE;
	CAN_InitStructure.CAN_AWUM = DISABLE;
	CAN_InitStructure.CAN_NART = DISABLE;		// non-resending enabled
	CAN_InitStructure.CAN_RFLM = DISABLE;
	CAN_InitStructure.CAN_TXFP = DISABLE;
	CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;
	CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;

	// CAN Baudrate, APB1 = 42 MHz
	CAN_InitStructure.CAN_BS1 = CAN_BS1_14tq;
	CAN_InitStructure.CAN_BS2 = CAN_BS2_6tq;
	// nastaveno dle https://community.st.com/s/question/0D50X00009XkZxtSAF/can-baud-rate
	//CAN_InitStructure.CAN_Prescaler=1;        // 2000 kbit/s
	//CAN_InitStructure.CAN_Prescaler=2;        // 1000 kbit/s
	//CAN_InitStructure.CAN_Prescaler=4;        //  500 kbit/s
	//CAN_InitStructure.CAN_Prescaler=5;        //  400 kbit/s
	//CAN_InitStructure.CAN_Prescaler=8;        //  250 kbit/s
	//CAN_InitStructure.CAN_Prescaler=10;       //  200 kbit/s
	CAN_InitStructure.CAN_Prescaler=16;       //  125 kbit/s
	//CAN_InitStructure.CAN_Prescaler=20;       //  100 kbit/s
	//CAN_InitStructure.CAN_Prescaler=40;       //   50 kbit/s
	//CAN_InitStructure.CAN_Prescaler=80;       //   40 kbit/s
	//CAN_InitStructure.CAN_Prescaler=200;      //   10 kbit/s

	CAN_Init(CANx, &CAN_InitStructure);
	CAN_Init(CAN_MASTER, &CAN_InitStructure);

	/* CAN filter init */
	CAN_FilterInitStructure.CAN_FilterNumber = 14;
	CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;
	CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;
	CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;
	CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;
	CAN_FilterInitStructure.CAN_FilterFIFOAssignment = 0;
	CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&CAN_FilterInitStructure);

	/* Transmit Structure preparation */
	TxMessage.StdId = 0x321;
	TxMessage.ExtId = 0x01;
	TxMessage.RTR = CAN_RTR_DATA;
	TxMessage.IDE = CAN_ID_STD;
	TxMessage.DLC = 1;

#ifdef CAN_RECEIVER
	/* Receive Structure preparation */
	Init_RxMes((CanRxMsg *)&RxMessage);

	/* Enable FIFO 0 and 1 message pending Interrupt */
	CAN_ITConfig(CANx, CAN_IT_FMP0, ENABLE);
	CAN_ITConfig(CANx, CAN_IT_FMP1, ENABLE);
#endif
}

/**
  * @brief  Configures the NVIC for CAN2.
  * @param  None
  * @retval None
  */
static void can_irq_config(void)
{
	NVIC_InitTypeDef  NVIC_InitStructure;

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = CAN2_RX1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
  * @brief  Initializes the Rx Message.
  * @param  RxMessage: pointer to the message to initialize
  * @retval None
  */
static void Init_RxMes(CanRxMsg *RxMessage)
{
	uint8_t ubCounter = 0;

	RxMessage->StdId = 0x00;
	RxMessage->ExtId = 0x00;
	RxMessage->IDE = CAN_ID_STD;
	RxMessage->DLC = 0;
	RxMessage->FMI = 0;

	for (ubCounter = 0; ubCounter < 8; ubCounter++)
	{
	RxMessage->Data[ubCounter] = 0x00;
	}
}

/**
  * @brief  Configures the CAN.
  * @param  None
  * @retval None
  */
void can_test(void)
{
#ifdef CAN_TRANSMITER
	static volatile uint8_t data = 0x55;
	uint8_t TransmitMailbox = 0;

	TxMessage.Data[0] = data;

	TransmitMailbox = CAN_Transmit(CANx, (CanTxMsg *)&TxMessage);

	while(CAN_TransmitStatus(CANx, TransmitMailbox)  !=  CANTXOK)
	{}

	/* Wait until one of the mailboxes is empty */
	//while((CAN_GetFlagStatus(CANx, CAN_FLAG_RQCP0) !=RESET) || (CAN_GetFlagStatus(CANx, CAN_FLAG_RQCP1) !=RESET) || (CAN_GetFlagStatus(CANx, CAN_FLAG_RQCP2) !=RESET))
	//{}
	data ^= 0xFF;		// 0x55 -> 0xAA -> 0x55 ...
#endif
}

void can_debug(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(CAN_GPIO_CLK, ENABLE);

	GPIO_InitStructure.GPIO_Pin = CAN_RX_PIN | CAN_TX_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(CAN_GPIO_PORT, &GPIO_InitStructure);

	while (1)
	{
		GPIO_SetBits(CAN_GPIO_PORT, CAN_RX_PIN);
		GPIO_ResetBits(CAN_GPIO_PORT, CAN_TX_PIN);

		GPIO_ResetBits(CAN_GPIO_PORT, CAN_RX_PIN);
		GPIO_SetBits(CAN_GPIO_PORT, CAN_TX_PIN);
	}
}
