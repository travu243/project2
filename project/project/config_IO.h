#ifndef _CONFIG_IO_H_
 #define _CONFIG_IO_H_
 
 #include "stm32f4xx.h"
 
// #define OFFSET_ENCODER 32768
// #define OFFSET_32B_ENCODER OFFSET_ENCODER //0XFFFFFFFF/2
 #define ADC1_DR_ADDRESS    ((uint32_t)0x4001204C)
 



#define OUTPUT0_SET 		GPIOE->BSRRL=1<<4
#define OUTPUT0_RESET 	GPIOE->BSRRH=1<<4

#define OUTPUT1_SET 		GPIOE->BSRRL=1<<3
#define OUTPUT1_RESET 	GPIOE->BSRRH=1<<3

#define OUTPUT2_SET 		GPIOE->BSRRL=1<<2
#define OUTPUT2_RESET 	GPIOE->BSRRH=1<<2

#define OUTPUT3_SET 		GPIOE->BSRRL=1<<1
#define OUTPUT3_RESET 	GPIOE->BSRRH=1<<1

#define OUTPUT4_SET 		GPIOE->BSRRL=1<<0
#define OUTPUT4_RESET 	GPIOE->BSRRH=1<<0

#define OUTPUT5_SET 		GPIOB->BSRRL=1<<9
#define OUTPUT5_RESET 	GPIOB->BSRRH=1<<9

#define OUTPUT6_SET 		GPIOB->BSRRL=1<<8
#define OUTPUT6_RESET 	GPIOB->BSRRH=1<<8

#define OUTPUT7_SET 		GPIOC->BSRRL=1<<12
#define OUTPUT7_RESET 	GPIOC->BSRRH=1<<12

#define OUTPUT8_SET 		GPIOC->BSRRL=1<<3
#define OUTPUT8_RESET 	GPIOC->BSRRH=1<<3

#define OUTPUT9_SET 		GPIOC->BSRRL=1<<2
#define OUTPUT9_RESET 	GPIOC->BSRRH=1<<2

#define OUTPUT10_SET 		GPIOC->BSRRL=1<<1
#define OUTPUT10_RESET 	GPIOC->BSRRH=1<<1

#define OUTPUT11_SET 		GPIOC->BSRRL=1<<0
#define OUTPUT11_RESET 	GPIOC->BSRRH=1<<0

#define OUTPUT12_SET 		GPIOE->BSRRL=1<<6
#define OUTPUT12_RESET 	GPIOE->BSRRH=1<<6

#define OUTPUT13_SET 		GPIOE->BSRRL=1<<5
#define OUTPUT13_RESET 	GPIOE->BSRRH=1<<5


#define INPUT17 		(GPIOA->IDR&(1<<12))
#define INPUT16 		(GPIOC->IDR&(1<<15))
#define INPUT15 		(GPIOC->IDR&(1<<14))
#define INPUT14 		(GPIOC->IDR&(1<<13))
#define INPUT13 		(GPIOE->IDR&(1<<15))
#define INPUT12 		(GPIOE->IDR&(1<<14))
#define INPUT11 		(GPIOE->IDR&(1<<13))
#define INPUT10 		(GPIOE->IDR&(1<<12))

#define INPUT9 		(GPIOE->IDR&(1<<11))
#define INPUT8 		(GPIOE->IDR&(1<<10))
#define INPUT7 		(GPIOE->IDR&(1<<9))
#define INPUT6 		(GPIOE->IDR&(1<<8))
#define INPUT5 		(GPIOE->IDR&(1<<7))
#define INPUT4 		(GPIOB->IDR&(1<<2))

#define INPUT3 		(GPIOB->IDR&(1<<1))	 // ADC1-IN9
#define INPUT2 		(GPIOB->IDR&(1<<0))  // ADC1-IN8
#define INPUT1 		(GPIOC->IDR&(1<<5))	// ADC1-IN15
#define INPUT0 		(GPIOC->IDR&(1<<4)) // ADC1-IN14

#define SPI1_MOSI 		(GPIOA->IDR&(1<<7)) // ADC1-IN7
#define SPI1_MISO 		(GPIOA->IDR&(1<<6)) // ADC1-IN6
#define SPI1_SCK 		(GPIOA->IDR&(1<<5)) // ADC1-IN5
#define SPI1_NSS 		(GPIOA->IDR&(1<<4)) // ADC1-IN4

#define SPI2_MOSI 		(GPIOB->IDR&(1<<15)) 
#define SPI2_MISO 		(GPIOB->IDR&(1<<14)) 
#define SPI2_SCK 		(GPIOB->IDR&(1<<13)) 
#define SPI2_NSS 		(GPIOB->IDR&(1<<12)) 

 void Config_Input_Digital(void);
 
 void Config_Output_Digital(void);
 
 void Config_ADC1_CH7_DMA(void);
 


	
	
	
#endif
