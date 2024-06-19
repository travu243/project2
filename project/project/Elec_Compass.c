
#include "Elec_Compass.h"
#include "config_uart.h"
extern vs16 _value_compass;
extern char Command_compass;
extern vs16 G_Z,G_Y,G_X;
vu8 _Rx2Buffer[2];
vu8 RX_USART2[2];
 void config_compass(void)
 {
	config_uart2(115200);
	config_dma_uart2_rx(2);
  config_ngat_dma1_uart2_rx_compass(); 
 }
 
 void config_uart2_dma(u32 baudrate)
{		
		DMA_InitTypeDef DMA_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
    USART_InitTypeDef USART_InitStructure;
		GPIO_InitTypeDef GPIO_InitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
   /*-------------------------- GPIO Configuration ----------------------------*/
   GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
   GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
   GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
   GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
   GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
   GPIO_Init(GPIOA, &GPIO_InitStructure);
   /* Connect USART pins to AF */
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

   USART_InitStructure.USART_BaudRate = baudrate;
   USART_InitStructure.USART_WordLength = USART_WordLength_8b;
   USART_InitStructure.USART_StopBits = USART_StopBits_1;
   USART_InitStructure.USART_Parity = USART_Parity_No;
   USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
   USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx; 
   USART_Init(USART2, &USART_InitStructure); 
   USART_Cmd(USART2, ENABLE);

/////////////////////////////////////////////	   
   
   /* Configure the Priority Group to 2 bits */
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
   /* Enable the UART4 RX DMA Interrupt */
   NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;
   NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
   NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
   NVIC_Init(&NVIC_InitStructure);
	
	 DMA_DeInit(DMA1_Stream5);
   DMA_InitStructure.DMA_Channel = DMA_Channel_4;
   DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; // Receive
   DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)RX_USART2;
   DMA_InitStructure.DMA_BufferSize = 2;//(uint16_t)sizeof(Buffer);
   DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&USART2->DR;
   DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
   DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
   DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
   DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
   DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
   DMA_InitStructure.DMA_Priority = DMA_Priority_High;
   DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
   DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
   DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
   DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single; 
   DMA_Init(DMA1_Stream5, &DMA_InitStructure); 
   /* Enable DMA Stream Half Transfer and Transfer Complete interrupt */
   USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE); // Enable USART Rx DMA Request
	 DMA_ITConfig(DMA1_Stream5, DMA_IT_TC, ENABLE);  
   /* Enable the DMA RX Stream */
   DMA_Cmd(DMA1_Stream5, ENABLE);
	 
}

void config_dma_uart2_rx(int lengt){
		DMA_InitTypeDef       DMA_InitStructure;
  
  /*  DMA1 and GPIO clocks ****************************************/
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);

	
    /* Configure DMA controller to manage USART TX and RX DMA request ----------*/  
		DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory; 
	
    DMA_InitStructure.DMA_PeripheralBaseAddr = (int32_t)&USART2->DR;//UART2_DR_ADDRESS;
	  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&_Rx2Buffer[0];
    DMA_InitStructure.DMA_BufferSize =(uint16_t)2;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA_Mode_Normal;//
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Enable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
 
	
   DMA_Init(DMA1_Stream5, &DMA_InitStructure);

	
	 /* Enable the USART Tx DMA request */                
    USART_DMACmd(USART2, USART_DMAReq_Rx, ENABLE);

//     /* Clear the rx bit in the SR register by writing 0 to it */
  USART_ClearFlag(USART2, USART_FLAG_RXNE);

    /* Enable DMA USART Rx Stream */
    DMA_Cmd(DMA1_Stream5, ENABLE);
}

void config_ngat_dma1_uart2_rx_compass(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Stream5_IRQn;// 
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 13; // muc do uu tien ngat thu 15
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;// cho phep su dung ngat
  	NVIC_Init(&NVIC_InitStructure);  	// cau hinh cho bang vector ngat
	
	DMA_ITConfig(DMA1_Stream5,DMA_IT_TC,ENABLE);
	
}
//u8 dem;
void DMA1_Stream5_IRQHandler(void)// receive compass
{
	if(DMA_GetFlagStatus(DMA1_Stream5, DMA_IT_TCIF5) != RESET)
    {      
			DMA_ClearITPendingBit(DMA1_Stream5,DMA_IT_TCIF5);
			//_var_dma_end_rx2_compass=1;
			DMA_Cmd(DMA1_Stream5, ENABLE);
			_value_compass=(_Rx2Buffer[0]<<8)|_Rx2Buffer[1];
			switch (Command_compass)
			{
				case 'z': G_Z=_value_compass; break;
				case 'y': G_Y=_value_compass; break;
				case 'x': G_X=_value_compass; break;
			}
			
			//dem++;
		//	GPIOD->ODR^=1<<15;
		}
}
