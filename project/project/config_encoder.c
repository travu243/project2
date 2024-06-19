
#include "config_encoder.h"

vs32 _so_vong_e1=0;
vs32 _so_vong_e2=0;
vs32 _so_vong_e3=0;
vs32 _so_vong_e4=0;

void NVIC_Config_tim3(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}



void NVIC_Config_tim2(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void NVIC_Config_tim4(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void NVIC_Config_tim5(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  /* Enable the TIM2 gloabal Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}


void Encoder2_Tim3_Init(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	

	/* Remap Pin for Encoder mode */
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource4, GPIO_AF_TIM3);
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_TIM3);
	
	/*GPIOC Configuration: TIM3 remap channel 1 and 2 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	
	
	  TIM_TimeBaseInitStructure.TIM_Prescaler=0;
    TIM_TimeBaseInitStructure.TIM_Period=0xFFFF;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStructure);
    
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICFilter=7;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM3, &TIM_ICInitStructure);

   // TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
    TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
    NVIC_Config_tim3();
		
    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM3,ENABLE);
    TIM_SetCounter(TIM3, OFFSET_ENCODER);
}

//xxxxxxxxxxxxxx


void Encoder1_Tim2_Init(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB, ENABLE);
	

	/* Remap Pin for Encoder mode */
   GPIO_PinAFConfig(GPIOB, GPIO_PinSource3, GPIO_AF_TIM2);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource15, GPIO_AF_TIM2);
	
	/*GPIOC Configuration: TIM3 remap channel 1 and 2 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	
	
	  TIM_TimeBaseInitStructure.TIM_Prescaler=0;
    TIM_TimeBaseInitStructure.TIM_Period=0xFFFFFFFF;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
    
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICFilter=7;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM2, &TIM_ICInitStructure);

   // TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
    TIM_EncoderInterfaceConfig(TIM2, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);
    
		
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM2,ENABLE);
    TIM_SetCounter(TIM2, OFFSET_32B_ENCODER);
		
		NVIC_Config_tim2();
}

void Encoder3_Tim4_Init(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	

	/* Remap Pin for Encoder mode */
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
   GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	
	/*GPIOC Configuration: TIM3 remap channel 1 and 2 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	

	
	
	  TIM_TimeBaseInitStructure.TIM_Prescaler=0;
    TIM_TimeBaseInitStructure.TIM_Period=0xFFFF;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseInitStructure);
    
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICFilter=7;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);

   // TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
    TIM_EncoderInterfaceConfig(TIM4, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

		NVIC_Config_tim4();

    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM4,ENABLE);
    TIM_SetCounter(TIM4, OFFSET_ENCODER);
}


void Encoder4_Tim5_Init(void)
{
 	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	

	/* Remap Pin for Encoder mode */
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_TIM5);
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM5);
	
	/*GPIOC Configuration: TIM3 remap channel 1 and 2 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType =GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	

	
	
	  TIM_TimeBaseInitStructure.TIM_Prescaler=0;
    TIM_TimeBaseInitStructure.TIM_Period=0xFFFFFFFF;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseInitStructure);
    
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_1|TIM_Channel_2;
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Falling;
    TIM_ICInitStructure.TIM_ICFilter=7;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;
    TIM_ICInit(TIM5, &TIM_ICInitStructure);

   // TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_BothEdge, TIM_ICPolarity_BothEdge);
    TIM_EncoderInterfaceConfig(TIM5, TIM_EncoderMode_TI12, TIM_ICPolarity_Falling, TIM_ICPolarity_Falling);

		NVIC_Config_tim5();
		
    TIM_ITConfig(TIM5, TIM_IT_Update, ENABLE);
    TIM_Cmd(TIM5,ENABLE);
    TIM_SetCounter(TIM5, OFFSET_32B_ENCODER);
}


s32 ReadEncoder(u32 num)
{
	  if(num==1)
			return ((TIM5->CNT) - OFFSET_32B_ENCODER);
		else if(num==2)
				return (((_so_vong_e3<<16)|TIM4->CNT)- OFFSET_ENCODER);
		else if (num==3)
			 return (((_so_vong_e2<<16)|TIM3->CNT) - OFFSET_ENCODER);
		else 
			return ((TIM2->CNT)-OFFSET_32B_ENCODER);

}	
	
//xxxxxxxxxxxxxxxxxxxxxxxx
void ClearEncoder(u32 num)
{
	 if(num==1)
	 {
		 _so_vong_e4=0;
			TIM5->CNT=OFFSET_ENCODER;
		 
	 }
		else if(num==2)
		{
			_so_vong_e3=0;
			TIM4->CNT=OFFSET_ENCODER;
			
		}
		else if (num==3)
		{
				_so_vong_e2=0;
					TIM3->CNT=OFFSET_ENCODER;
		}
		else
			{
				_so_vong_e1=0;
			TIM2->CNT=OFFSET_ENCODER;
		}
			
}

//xxxxxxxxxxxxxxxxx

void ConfigEncoder(void) // tthis is a function setting all encoder 
{
	 Encoder1_Tim2_Init();
	 Encoder2_Tim3_Init();
	 Encoder3_Tim4_Init();
	 Encoder4_Tim5_Init();
	
	ClearEncoder(1);	ClearEncoder(2); ClearEncoder(3);ClearEncoder(4); 
	
	
}


void TIM2_IRQHandler(void)
	{
		TIM2->SR = (uint16_t)~TIM_IT_Update;
		if( TIM2->CR1&TIM_CounterMode_Down)
					_so_vong_e1--;// down
		else
					_so_vong_e1++;// up
		
	}
	
void TIM3_IRQHandler(void)
	{
		TIM3->SR = (uint16_t)~TIM_IT_Update;
		if( TIM3->CR1&TIM_CounterMode_Down)
					_so_vong_e2--;// down
		else
					_so_vong_e2++;// up
		
	}
	
	
void TIM4_IRQHandler(void)
	{
		TIM4->SR = (uint16_t)~TIM_IT_Update;
		if( TIM4->CR1&TIM_CounterMode_Down)
					_so_vong_e3--;// down
		else
					_so_vong_e3++;// up
		
	}


void TIM5_IRQHandler(void)
	{
		TIM5->SR = (uint16_t)~TIM_IT_Update;
		if( TIM5->CR1&TIM_CounterMode_Down)
					_so_vong_e4--;// down
		else
					_so_vong_e4++;// up
		
	}
	