
#ifndef _CONFIG_PWM_H_

#define _CONFIG_PWM_H_
 #include "stm32f4xx.h"
 #include "stm32f4xx_gpio.h"

#define PWM1 		TIM1->CCR4
#define DIR1_SET 		GPIOD->BSRRL=1<<4
#define DIR1_RESET 	GPIOD->BSRRH=1<<4
#define DIR1_TOGGLE 	GPIOD->ODR^=1<<4

#define PWM2 		TIM1->CCR3
#define DIR2_SET 		GPIOD->BSRRL=1<<3
#define DIR2_RESET 	GPIOD->BSRRH=1<<3

#define PWM3 		TIM1->CCR2
#define DIR3_SET 		GPIOD->BSRRL=1<<2
#define DIR3_RESET 	GPIOD->BSRRH=1<<2

#define PWM4 TIM8->CCR2
#define DIR4_SET 		GPIOD->BSRRL=1<<1
#define DIR4_RESET 	GPIOD->BSRRH=1<<1

#define PWM5 TIM8->CCR1
#define DIR5_SET 		GPIOD->BSRRL=1<<0
#define DIR5_RESET 	GPIOD->BSRRH=1<<0


#define PWM6 TIM8->CCR3
#define DIR6_SET 		GPIOD->BSRRL=1<<5
#define DIR6_RESET 	GPIOD->BSRRH=1<<5

#define PWM7 	TIM8->CCR4
#define DIR7_SET 		GPIOD->BSRRL=1<<6
#define DIR7_RESET 	GPIOD->BSRRH=1<<6

#define PWM8 	TIM1->CCR1
#define DIR8_SET 		GPIOD->BSRRL=1<<7
#define DIR8_RESET 	GPIOD->BSRRH=1<<7 


 void config_PWM(void);
 void Config_timer67(void);
 void delay_us(u32 del);
 void delay_ms(u32 del);
 

#endif
