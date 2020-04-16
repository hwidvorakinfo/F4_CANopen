/*
 * adc.c
 *
 *  Created on: 14. 8. 2019
 *      Author: Petr Dvorak
 */

#include "adc.h"
#include "application.h"

void adc_init(void)
{
#ifdef ADC_INIT
#ifdef ADC_PORTA_INIT
	// ADC vstup kanalu ADC_IN_PORT_A
	RCC_AHBPeriphClockCmd(ADC_INPUT_CLOCKS, ENABLE);
	RCC_APB2PeriphClockCmd(ADC_CLOCKS, ENABLE);
	GPIO_InitStructure.GPIO_Pin = ADC_IN_INPUTS_PORTA;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(ADC_IN_PORT_A, &GPIO_InitStructure);
#endif

#ifdef ADC_PORTB_INIT
	// ADC vstup kanalu ADC_IN_PORT_B
	GPIO_InitStructure.GPIO_Pin = ADC_IN_INPUTS_PORTB;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
	GPIO_Init(ADC_IN_PORT_B, &GPIO_InitStructure);
#endif

	// inicializace ADC1
	ADC_DeInit(IN_ADC);
	ADC_StructInit(&ADC_InitStructure);
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Upward;
	ADC_Init(IN_ADC, &ADC_InitStructure);

	/* Convert the ADC1 Channel x with 239.5 Cycles as sampling time */
	// na portu PAx
	ADC_ChannelConfig(IN_ADC, IN_ADC_THERM0_CHAN, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(IN_ADC, IN_ADC_THERM1_CHAN, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(IN_ADC, IN_ADC_THERM2_CHAN, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(IN_ADC, IN_ADC_Z_THERM_CHAN, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(IN_ADC, IN_ADC_A0_CHAN, ADC_SampleTime_239_5Cycles);
	// na portu PBx
	ADC_ChannelConfig(IN_ADC, IN_ADC_A1_CHAN, ADC_SampleTime_239_5Cycles);
	ADC_ChannelConfig(IN_ADC, IN_ADC_THERM3_CHAN, ADC_SampleTime_239_5Cycles);

	/* DMA1 clock enable */
	RCC_AHBPeriphClockCmd(DMA_CLOCKS, ENABLE);

	/* DMA1 Channel1 Config */
	DMA_DeInit(IN_ADC_DMA_CHAN);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)ADC1_BASE+0x40;	// adresa ADC_DR registru, ADC1_BASE + ADC_DR address offset
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)dma_data;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = IN_ADC_COUNT;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(IN_ADC_DMA_CHAN, &DMA_InitStructure);
	DMA_Cmd(IN_ADC_DMA_CHAN, ENABLE);

	ADC_GetCalibrationFactor(IN_ADC);
	ADC_DMARequestModeConfig(IN_ADC, ADC_DMAMode_Circular);
	ADC_DMACmd(IN_ADC, ENABLE);
	ADC_Cmd(IN_ADC, ENABLE);

	/* Wait the ADRDY flag */
	while(!ADC_GetFlagStatus(IN_ADC, ADC_FLAG_ADRDY));
	/* ADC1 regular Software Start Conv */
	ADC_StartOfConversion(IN_ADC);
#endif
}
