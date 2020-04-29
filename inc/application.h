/*
 * application.h
 *
 *  Created on: 13. 8. 2019
 *      Author: Petr Dvorak
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "stm32f4xx.h"
#include "defs.h"
#include "stm32f4xx_conf.h"

#define OUTPUT_CLOCKS		RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF

#define CENTRAL
//#define SENSOR


// modifikace dle verze desky, odkomentovat #define nize podle pozadovane verze
// - VERSION_A je prvni verze
// - VERSION_B je druha verze

#define VERSION_A
//#define VERSION_B

#ifdef VERSION_A

// vystupy na PAx
//#define GPIOA_INIT
#ifdef GPIOA_INIT
#define OUT_PORT_A				GPIOA

// PA14 SWDCLK
//#define RESERVED0				GPIO_Pin_14
// PA13 SWDIO
//#define RESERVED1				GPIO_Pin_13

#define OUT_PORT_A_OUTPUTS
#define GPIOA_RESET_INIT
	#define OUT_PORT_A_RESET_INIT
#define GPIOA_SET_INIT
	#define OUT_PORT_A_SET_INIT
#endif

// vystupy na PBx
#define GPIOB_INIT
#ifdef GPIOB_INIT
#define OUT_PORT_B				GPIOB
#define FUNCTION_LED_PORT		OUT_PORT_B
#define FUNCTION_LED_PIN		GPIO_Pin_0
#define STATUS_LED_PORT			OUT_PORT_B
#define STATUS_LED_PIN			GPIO_Pin_1

#define OUT_PORT_B_OUTPUTS		FUNCTION_LED_PIN | STATUS_LED_PIN
//#define GPIOB_RESET_INIT
	#define OUT_PORT_B_RESET_INIT	0
//#define GPIOB_SET_INIT
	#define OUT_PORT_B_SET_INIT		0
#endif

// vystupy na PCx
//#define GPIOC_INIT
#ifdef GPIOC_INIT
#define OUT_PORT_C				GPIOC
#define OUT_PORT_C_OUTPUTS		0
//#define GPIOC_RESET_INIT
//	#define OUT_PORT_C_RESET_INIT	LEDG_PIN
#define GPIOC_SET_INIT
	#define OUT_PORT_C_SET_INIT		LCD_DC_PIN
#endif

// vystupy na PDx
//#define GPIOD_INIT
#ifdef GPIOD_INIT
#define OUT_PORT_D				GPIOD

#define OUT_PORT_D_OUTPUTS		0
//#define GPIOD_RESET_INIT
	#define OUT_PORT_D_RESET_INIT	0
//#define GPIOD_SET_INIT
	#define OUT_PORT_D_SET_INIT		0
#endif

// vystupy na PEx
//#define GPIOE_INIT
#ifdef GPIOE_INIT
#define OUT_PORT_E				GPIOE

#define OUT_PORT_E_OUTPUTS
//#define GPIOE_RESET_INIT
//	#define OUT_PORT_E_RESET_INIT	0
#define GPIOE_SET_INIT
	#define OUT_PORT_E_SET_INIT		0
#endif

// vystupy na PFx
//#define GPIOF_INIT
#ifdef GPIOF_INIT
#define OUT_PORT_F				GPIOF

#define OUT_PORT_F_OUTPUTS		0
#define GPIOF_RESET_INIT
	#define OUT_PORT_F_RESET_INIT	0
//#define GPIOF_SET_INIT
	#define OUT_PORT_F_SET_INIT		0
#endif

// vstupy na PAx
//#define GPIOA_INPUT
#ifdef GPIOA_INPUT
#define IN_PORT_A				GPIOA
#endif

// vstupy na PBx
//#define GPIOB_INPUT
#ifdef GPIOB_INPUT
#define IN_PORT_B				GPIOB
#define NTCFAULT_PORT			IIN_PORT_B
#define Z_MIN_PORT				IN_PORT_B
#define NTCFAULT_PIN			GPIO_Pin_8
#define Z_MIN_PIN				GPIO_Pin_12
#define MAXTEMP_PORT			IN_PORT_B
#define MAXTEMP_PIN				GPIO_Pin_9

#define IN_PORT_B_INPUTS		NTCFAULT_PIN | Z_MIN_PIN | MAXTEMP_PIN
#endif

// vstupy na PCx
//#define GPIOC_INPUT
#ifdef GPIOC_INPUT
#endif

// vstupy na PFx
//#define GPIOF_INPUT
#ifdef GPIOF_INPUT
#endif

// vstupy ADC
//#define ADC_INIT
#ifdef ADC_INIT
#define ADC_INPUT_CLOCKS		RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB
#define ADC_CLOCKS				RCC_APB2Periph_ADC1
#define DMA_CLOCKS				RCC_AHBPeriph_DMA1
// port PAx
#define ADC_PORTA_INIT
#define ADC_IN_PORT_A			IN_PORT_A
#define ADC_IN_THERM_0			GPIO_Pin_0
#define ADC_IN_THERM_1			GPIO_Pin_1
#define ADC_IN_THERM_2			GPIO_Pin_2
#define ADC_IN_Z_THERM			GPIO_Pin_3
#define ADC_IN_A0				GPIO_Pin_5
// port PBx
#define ADC_PORTB_INIT
#define ADC_IN_PORT_B			IN_PORT_B
#define ADC_IN_A1				GPIO_Pin_0
#define ADC_IN_THERM_3			GPIO_Pin_1

#define ADC_IN_INPUTS_PORTA		ADC_IN_THERM_0 | ADC_IN_THERM_1 | ADC_IN_THERM_2 | ADC_IN_Z_THERM | ADC_IN_A0
#define ADC_IN_INPUTS_PORTB		ADC_IN_A1 | ADC_IN_THERM_3

#define IN_ADC					ADC1
#define IN_ADC_THERM0_CHAN		ADC_Channel_0
#define IN_ADC_THERM1_CHAN		ADC_Channel_1
#define IN_ADC_THERM2_CHAN		ADC_Channel_2
#define IN_ADC_Z_THERM_CHAN		ADC_Channel_3
#define IN_ADC_A0_CHAN			ADC_Channel_5

#define IN_ADC_A1_CHAN			ADC_Channel_8
#define IN_ADC_THERM3_CHAN		ADC_Channel_9

// DMA+ADC
#define ADC_MINVALUE				1000
#define IN_ADC_COUNT				7
#define IN_ADC_DMA_CHAN				DMA1_Channel1
#endif


//#define TIMER
// mereni frekvence casovacem
//#define TIM_CAPTURE
#ifdef TIM_CAPTURE
#define TACH_0_TIMER				TIM14
#define TACH_0_CHANNEL				TIM_Channel_1
#define TACH_0_IRQ					TIM14_IRQn
#define TACH_0_TIMER_CLOCKS			RCC_APB1Periph_TIM14
#define TACH_0_PORT					IN_PORT_A
#define TACH_0_PIN					GPIO_Pin_4
#define TACH_0_SOURCE				GPIO_PinSource4
#define TACH_0_AF					GPIO_AF_4
#define TACH_0_TIMER_IRQHandler		TIM14_IRQHandler

#define TACH_1_PORT					IN_PORT_A
#define TACH_1_PIN					GPIO_Pin_6
#define TACH_1_SOURCE				GPIO_PinSource6
#define TACH_1_AF					GPIO_AF_5
#define TACH_1_TIMER				TIM16
#define TACH_1_CHANNEL				TIM_Channel_1
#define TACH_1_IRQ					TIM16_IRQn
#define TACH_1_TIMER_CLOCKS			RCC_APB2Periph_TIM16
#define TACH_1_TIMER_IRQHandler		TIM16_IRQHandler

#define PWM_AS_PORT					IN_PORT_A
#define PWM_AS_PIN					GPIO_Pin_7
#define PWM_AS_SOURCE				GPIO_PinSource7
#define PWM_AS_AF					GPIO_AF_5
#define PWM_AS_TIMER				TIM17
#define PWM_AS_CHANNEL				TIM_Channel_1
#define PWM_AS_IRQ					TIM17_IRQn
#define PWM_AS_TIMER_CLOCKS			RCC_APB2Periph_TIM17
#define PWM_AS_TIMER_IRQHandler		TIM17_IRQHandler

#define TACH_0_PRESCALER			48000
#define TACH_1_PRESCALER			48000
#define PWM_AS_PRESCALER			48000

#define TACH_0_FREQ_INDEX			0
#define TACH_1_FREQ_INDEX			1
#define PWM_AS_FREQ_INDEX			2
#endif

//#define SPI
#ifdef SPI
#define LCD_SPI						SPI3
#define LCD_SPI_CLK					RCC_APB1Periph_SPI3

#define SPI1_SCK
#ifdef SPI1_SCK
#define LCD_SCK_SOURCE				GPIO_PinSource3
#define LCD_SCK_PIN					GPIO_Pin_3
#define LCD_SCK_PORT				GPIOB
#define LCD_SCK_CLK					RCC_AHB1Periph_GPIOB
#define LCD_SCK_AF					GPIO_AF_SPI3
#endif //SPI1_SCK

#define SPI1_MOSI
#ifdef SPI1_MOSI
#define LCD_MOSI_SOURCE				GPIO_PinSource5
#define LCD_MOSI_PIN				GPIO_Pin_5
#define LCD_MOSI_PORT				GPIOB
#define LCD_MOSI_CLK				RCC_AHB1Periph_GPIOB
#define LCD_MOSI_AF					GPIO_AF_SPI3
#endif //SPI1_MOSI

//#define SPI1_MISO
#ifdef SPI1_MISO
#define LCD_MISO_SOURCE				GPIO_PinSource6
#define LCD_MISO_PIN				GPIO_Pin_6
#define LCD_MISO_PORT				GPIOA
#define LCD_MISO_CLK				RCC_AHBPeriph_GPIOA
#define LCD_MISO_AF					GPIO_AF_SPI1
#endif // SPI1_MISO
#endif //SPI

//#define I2C
#ifdef I2C
#define CAM_I2C			I2C2
#define CAM_I2C_CLK		RCC_APB1Periph_I2C2
#define I2C_PIN_CLOCKS	RCC_AHB1Periph_GPIOB

#define CAM_SCL_PIN		GPIO_Pin_10
#define CAM_SCL_PORT	GPIOB
#define CAM_SCL_CLK		RCC_AHB1Periph_GPIOB
#define CAM_SCL_SOURCE	GPIO_PinSource10
#define CAM_SCL_AF		GPIO_AF_I2C2

#define CAM_SDA_PIN		GPIO_Pin_11
#define CAM_SDA_PORT	GPIOB
#define CAM_SDA_CLK		RCC_AHB1Periph_GPIOB
#define CAM_SDA_SOURCE	GPIO_PinSource11
#define CAM_SDA_AF		GPIO_AF_I2C2
#endif //I2C

//#define USE_DCMI

#endif // VERSION A

#ifdef VERSION_B


#endif


#endif /* APPLICATION_H_ */
