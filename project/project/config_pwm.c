
#include "config_pwm.h"

void config_PWM(void){
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
  /* GPIOA, GPIOB and GPIOE Clocks enable */
  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC|RCC_AHB1Periph_GPIOD , ENABLE);
  
  /* GPIOA Configuration: Channel 1, 3 and 4 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_10 | GPIO_Pin_11; // OUT PWM TIM1
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9|GPIO_Pin_6 | GPIO_Pin_7;// OUT PWM TIM8
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
//  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = 0x00ff;// OUT DIR 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_TIM1);// TIM1 CH1
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_TIM1);// TIM1 CH2
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_TIM1);// TIM1 CH3
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_TIM1);// TIM1 CH4
	

  GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_TIM8);// TIM8 CH1
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_TIM8);// TIM8 CH2
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource8, GPIO_AF_TIM8);// TIM8 CH3
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_TIM8);// TIM8 CH4
	
	 /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1|RCC_APB2Periph_TIM8 , ENABLE);
  
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler = 1000;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 255;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM8, &TIM_TimeBaseStructure);

  /* Channel 1, 2,3 and 4 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
  TIM_OCInitStructure.TIM_Pulse = 255;
  TIM_OCInitStructure.TIM_OCPolarity =TIM_OCPolarity_Low; // standar for ic modul st Lowside
  TIM_OCInitStructure.TIM_OCNPolarity =TIM_OCNPolarity_High;// standar for ic modul st highside
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Set;//TIM_OCIdleState_Reset;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC4Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);
	TIM_OC3Init(TIM8, &TIM_OCInitStructure);
	TIM_OC4Init(TIM8, &TIM_OCInitStructure);

// /* Automatic Output enable, Break, dead time and lock configuration*/
//  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;
//  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;
//  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_OFF;
//  TIM_BDTRInitStructure.TIM_DeadTime = 150;
//  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Disable;
//  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;
//  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;

//  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);
	
	
	

//  TIM_OCInitStructure.TIM_Pulse = 0;
//  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

//  TIM_OCInitStructure.TIM_Pulse = 0;
//  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

//  TIM_OCInitStructure.TIM_Pulse = 0;
//  TIM_OC4Init(TIM1, &TIM_OCInitStructure);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
  /* TIM1 Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM8, ENABLE);
	
	//TIM1->CNT = TIM8->CNT = 255;

				PWM1 = 0;
				PWM2 = 0;
				PWM3 = 0;
				PWM4 = 0;
				PWM5 = 0;
				PWM6 = 0;
				PWM7 = 0;
				PWM8 = 0;

 }

 void Config_timer67(void)//
{
	
 	  TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6|RCC_APB1Periph_TIM7, ENABLE);
	
	  TIM_TimeBaseInitStructure.TIM_Prescaler=(SystemCoreClock/2000000)-1;
    TIM_TimeBaseInitStructure.TIM_Period=0xFFFF;
    TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	  TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStructure);
	
	 // TIM_TimeBaseInitStructure.TIM_Prescaler=99;
	  TIM_TimeBaseInit(TIM7, &TIM_TimeBaseInitStructure);

		TIM_ARRPreloadConfig(TIM6, ENABLE);
    TIM_SetCounter(TIM6, 0);
    TIM_Cmd(TIM6,ENABLE);
	
	  TIM_ARRPreloadConfig(TIM7, ENABLE);
    TIM_SetCounter(TIM7, 0);
    TIM_Cmd(TIM7,ENABLE);
	
	
}


void delay_us(u32 del)
{
 
 TIM6->CNT=0;
 while(TIM6->CNT<del);
}
 
 //XXXXXXXXXXXXXXXXXXXXXXXXXXXXX
void delay_ms(u32 del){
	 while(del--)
	 {
		 delay_us(1000);
	 }
}
 
 
 











