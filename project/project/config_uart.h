#ifndef _CONFIG_USART_H_
 #define _CONFIG_USART_H_
 
 #define EN_IT_USART1_RX
 #define EN_IT_USART2_RXv 
 
 #include "stm32f4xx.h"
 
 void config_uart1(int baudrate);
 void config_uart2(int baudrate);
 void config_uart3(uint32_t baudrate);
 void config_uart4(uint32_t baudrate);
 
#endif
