#ifndef _CONFIG_COMPASS_H_
 #define _CONFIG_COMPASS_H_
 
 #include "stm32f4xx.h"
 
#define UART2_DR_ADDRESS   ((uint32_t)0x40004404)
 void config_compass(void);
 void config_dma_uart2_rx(int lengt);
 void config_ngat_dma1_uart2_rx_compass(void);
 void DMA1_Stream5_IRQHandler(void);
 void config_uart2_dma(u32 baudrate);
 
#endif
