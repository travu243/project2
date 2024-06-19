/**
  ******************************************************************************
  * @file    IO_Toggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    19-September-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include "stdlib.h"
#include "stdio.h"
#include "config_encoder.h"
/** @addtogroup STM32F4_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup IO_Toggle
  * @{
  */ 



extern vu32 tick_time_gu32;
extern char Command_compass;

extern int16_t SPEED;
extern int16_t SPEED_mong_muon;
extern int16_t xoay;
extern vs16 Beta;
extern u8 Value_vantoc_goc;
extern u8 Value_Giatoc;
extern u8 getchar_u8;
#define max_buff 10
#define MAX_STRLEN 100 // this is the maximum string length of our string in characters
extern char received_string[MAX_STRLEN+1]; // this will hold the recieved string
extern char str_rev[MAX_STRLEN];
extern char str[MAX_STRLEN];
extern u8 JoysticXL;
extern u8 JoysticYL;
extern u8 JoysticXR;
extern u8 JoysticYR;
extern u8 giatoc_giamtoc;
extern u8 dahuong_exit;
extern u16 value_game;
extern u16 value_game_Joytic_Left;
extern u16 value_game_Joytic_Right;
extern u8 ktra;
extern u8 buff_game[max_buff];
extern u8 cnt;
extern u8 getchar_usart3;
extern u32 time_out;

extern float Huong_tinh_tien;
extern vs16 Huong_xoay;
extern vs16 Toc_doxoay;
extern vs16 SPEED_tinhtien;
extern __IO u8 Value_giatoc_pwm;
vu16 gamepad_timeout = 0;
extern u8 Enable_rotate_one_spot;
extern u8 Lock_Whell;
extern vs32 TestencoderTimer4;
extern u8 Giatoc_tinh_tien;

extern void Da_huong_4banh(float Huong_tinh_tien_alpha, vs16 beta , u8 value_locity, u8 SPEED_TINH_TIEN,u8 XOAY_TAI_CHO);



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

void Tang_giam_SPEED(void)
{
	
		static u8 i;
		static u8 j,k;

if(SPEED != SPEED_mong_muon)
	 {
			if(++i > Giatoc_tinh_tien)
				{
				i=0;
				if(SPEED > SPEED_mong_muon) 
					{
						SPEED--;
						if(SPEED <= SPEED_mong_muon) SPEED = SPEED_mong_muon;
					}
				else 
					{
						SPEED++;
						if(SPEED >= SPEED_mong_muon )SPEED = SPEED_mong_muon;
					}
				}
		}
		
		
		if(xoay != Beta)
			{
				if(++j > Value_vantoc_goc)
					{
						j=0;
						if(xoay < 0)
						{
							Beta--;
							if(Beta <= xoay) Beta = xoay;
						}
						else
						{
							Beta++;
							if(Beta >= xoay) Beta = xoay;
						}
					}
		
		  }
		if(xoay == 0 && Beta != 0){

			if(++k > Value_vantoc_goc){
				k=0;
				if(Beta < 0){
							Beta++;
							if(Beta >= 0) Beta = xoay;
				}
				else if(Beta > 0){
							Beta--;
							if(Beta <= 0) Beta = xoay;
				}
		}
	}
}



//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXx






void SysTick_Handler(void)
{
	static u8 num=0;

	tick_time_gu32++;
		if(++num>4) 
			{
					
				  //if(++Command_compass>122) Command_compass=120;
				  USART2->DR=Command_compass;num=0;
					if(Lock_Whell == 1)
					Da_huong_4banh(Huong_tinh_tien, Huong_xoay, Toc_doxoay, SPEED_tinhtien,Enable_rotate_one_spot);
			}

		Tang_giam_SPEED();
			
		if(++gamepad_timeout > 200)
		{
					
					value_game = 0xffff;
					value_game_Joytic_Left = 0xffff;
					value_game_Joytic_Right = 0xffff;
		}
//		if(++test > 50)
//			{
//				test=0;
//				TestencoderTimer4=ReadEncoder(4);
//				ClearEncoder(4); 
//			}
		

if(value_game == (u16)(~((1<<3)|(1<<1)))) // R1 va R2 = 1<<3
		{
			NVIC_SystemReset();
		}
		
		
}

void USART1_IRQHandler(void) 
{
		if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET) // Cho ky tu
	{       
    TIM7->CNT=0;
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		getchar_u8 = USART1->DR;   
		if(ktra == 4 ){
			buff_game[cnt++] = getchar_u8;
				if(cnt > 5)
				{
					ktra = 0;
					cnt = 0;
					gamepad_timeout = 0;
					value_game = (buff_game[0]<<8) | buff_game[1];
					value_game_Joytic_Left=(buff_game[4]<<8) | buff_game[5];
					value_game_Joytic_Right=(buff_game[2]<<8) | buff_game[3];
				}
		}
		
		if(getchar_u8 == 0xAA) ktra++;
		else if(ktra != 4) 
			{
				ktra = 0;
			}
	}	
}






	
/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
