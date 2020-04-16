/*
 * dcmi.c
 *
 *  Created on: 14. 8. 2019
 *      Author: Petr Dvorak
 */


#ifdef USE_DCMI

#include "dcmi.h"
#include "application.h"
#include "camera.h"
#include "delay.h"
#include "ili9341.h"
#include "spi.h"

extern uint8_t rowdata1[640];
extern uint8_t rowdata2[640];

volatile uint8_t *buffer_pointer;
static volatile uint8_t buffer_index = 1;

// vrat index pouziteho bufferu
uint8_t dcmi_get_index(void)
{
	return buffer_index;
}

// zmen pouzity buffer a jeho index v pomocne promenne
void dcmi_set_index(uint8_t value)
{
	buffer_index = value;
	switch (value)
	{
		case 1:
			//buffer_pointer = &rowdata1[0];
			CAMERASTREAM->M0AR = (uint32_t)rowdata1;
			LCDSPI_STREAM->M0AR = (uint32_t)rowdata2;
		break;
		case 2:
			//buffer_pointer = &rowdata2[0];
			CAMERASTREAM->M0AR = (uint32_t)rowdata2;
			LCDSPI_STREAM->M0AR = (uint32_t)rowdata1;
		break;
		default:
			//buffer_pointer = &rowdata1[0];
			CAMERASTREAM->M0AR = (uint32_t)rowdata1;
			LCDSPI_STREAM->M0AR = (uint32_t)rowdata2;
		break;
	}

}
void dcmi_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DCMI_InitTypeDef DCMI_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	dcmi_set_index(1);

	/*** Configures the DCMI GPIOs to interface with the OV7670 camera module ***/
	/* Enable DCMI GPIOs clocks */
	RCC_AHB1PeriphClockCmd(CAMERACLOCKS, ENABLE);

	/* DCMI GPIO configuration */
	GPIO_InitStructure.GPIO_Pin = DATA0PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(DATA0PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA1PIN;
	GPIO_Init(DATA1PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA2PIN;
	GPIO_Init(DATA2PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA3PIN;
	GPIO_Init(DATA3PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA4PIN;
	GPIO_Init(DATA4PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA5PIN;
	GPIO_Init(DATA5PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA6PIN;
	GPIO_Init(DATA6PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = DATA7PIN;
	GPIO_Init(DATA7PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = VSYNCPIN;
	GPIO_Init(VSYNCPORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = HSYNCPIN;
	GPIO_Init(HSYNCPORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = PCLKPIN;
	GPIO_Init(PCLKPORT, &GPIO_InitStructure);

	/* Connect DCMI pins to AF13 */
	GPIO_PinAFConfig(DATA0PORT, DATA0SOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(DATA1PORT, DATA1SOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(DATA2PORT, DATA2SOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(DATA3PORT, DATA3SOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(DATA4PORT, DATA4SOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(DATA5PORT, DATA5SOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(DATA6PORT, DATA6SOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(DATA7PORT, DATA7SOURCE, GPIO_AF_DCMI);

	GPIO_PinAFConfig(VSYNCPORT, VSYNCSOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(HSYNCPORT, HSYNCSOURCE, GPIO_AF_DCMI);
	GPIO_PinAFConfig(PCLKPORT,  PCLKSOURCE,  GPIO_AF_DCMI);


	////////////////////////////////////////////////////////

	/*** Configures the DCMI to interface with the OV7670 camera module ***/
	/* Enable DCMI clock */
	RCC_AHB2PeriphClockCmd(CAMERADCMI, ENABLE);

	/* DCMI configuration */
	DCMI_InitStructure.DCMI_CaptureMode = DCMI_CaptureMode_SnapShot; // DCMI_CaptureMode_SnapShot DCMI_CaptureMode_Continuous
	DCMI_InitStructure.DCMI_SynchroMode = DCMI_SynchroMode_Hardware;
	DCMI_InitStructure.DCMI_PCKPolarity = DCMI_PCKPolarity_Rising;
	DCMI_InitStructure.DCMI_VSPolarity = DCMI_VSPolarity_Low;		// Low meni data v DR, High podle dokumentace, chova se jako blank a data v aktivni urovni jsou ignorovana
	DCMI_InitStructure.DCMI_HSPolarity = DCMI_HSPolarity_Low;		// Low, chova se jako blank a data v aktivni urovni jsou ignorovana
	DCMI_InitStructure.DCMI_CaptureRate = DCMI_CaptureRate_1of4_Frame;
	DCMI_InitStructure.DCMI_ExtendedDataMode = DCMI_ExtendedDataMode_8b;
	DCMI_Init(&DCMI_InitStructure);

	// DCMI IRQ
	DCMI_ITConfig(DCMI_IT_LINE, ENABLE);
	DCMI_ITConfig(DCMI_IT_FRAME, ENABLE);
	DCMI_ITConfig(DCMI_IT_VSYNC, ENABLE);
	DCMI_ITConfig(DCMI_IT_OVF, ENABLE);
	//DCMI_ITConfig(DCMI_IT_ERR, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = DCMI_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

/*
	// DMA IRQ
	DMA_ITConfig(CAMERASTREAM, DMA_IT_TC, ENABLE);
	DMA_ITConfig(CAMERASTREAM, DMA_IT_HT, ENABLE);
	DMA_ITConfig(CAMERASTREAM, DMA_IT_TE, ENABLE);
	DMA_ITConfig(CAMERASTREAM, DMA_IT_FE, ENABLE);
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// Configures the DMAs to transfer Data from DCMI
	RCC_AHB1PeriphClockCmd(CAMERADMA, ENABLE);
	RCC_AHB1PeriphClockCmd(LCDDMA, ENABLE);

	// DMA2 Stream1 Configuration
	DMA_DeInit(CAMERASTREAM);
	DMA_DeInit(LCDSPI_STREAM);

	// memory -> SPI
	DMA_InitStructure.DMA_BufferSize = 640;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable ;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull ;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single ;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_PeripheralBaseAddr = SPI_DR_ADDRESS;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_Channel = LCDSPICHANNEL ;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral ;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rowdata2;
	DMA_Init(LCDSPI_STREAM, &DMA_InitStructure);

	// DCMI -> memory
	DMA_InitStructure.DMA_Channel = CAMERACHANNEL;
	DMA_InitStructure.DMA_PeripheralBaseAddr = DCMI_DR_ADDRESS;
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)rowdata1;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
	DMA_InitStructure.DMA_BufferSize = 320*240/2;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	DMA_Init(CAMERASTREAM, &DMA_InitStructure);
*/
	// SPI DMA
	uint16_t i;
	SPI_Cmd(LCD_SPI, DISABLE);
	SPI_I2S_DMACmd(LCD_SPI, SPI_I2S_DMAReq_Tx, ENABLE);
	DMA_Cmd(LCDSPI_STREAM, ENABLE);
	SPI_Cmd(LCD_SPI, ENABLE);

	// DCMI
	//DMA_Cmd(CAMERASTREAM, ENABLE);
	DCMI_Cmd(ENABLE);

	while(1)
	{
		delay_ms(300);
		DCMI_Cmd(ENABLE);
		DCMI_CaptureCmd(ENABLE);
	}
}

#endif
