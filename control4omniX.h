/*
Author: Tra Vu
Date:6/14/2024
Reference: Thegioichip

control 4 omni X

USE FOR STM32F103C8T6

ham` Da_huong_4banh() co' 5 tham so':

Huong_tinh_tien: huong' di chuyen? cua? robot
Huong_xoay: huong' mat. cua? robot
Toc_doxoay: toc' do. xoay cua? robot neu' robot co' xoay
SPEED_tinhtien: toc' do. di chuyen' cua? robot
Enable_rotate_one_spot: cho phep' quay tai. cho~ (bat. cai' nay` thi` ko di chuyen? dc, chi? dung' im fix goc')


vi du:

Da_huong_4banh(0,90,10,60,0);

Huong_tinh_tien=0;
Huong_xoay=90;
Toc_doxoay=10;				(cang` tang cang` cham.)
SPEED_tinhtien=60;			(max: SPEED_LIMIT)
Enable_rotate_one_spot=0;	(ko cho phep' xoay tai. cho~)

*/

#include "main.h"


#include <math.h>
#include <stdint.h>
#include <core_cm3.h>


#define PI 3.14159265
#define SPEED_LIMIT 250      // MAX  255
#define NUM_OMNI (PI / 180.0)
#define OFFSET_XOAY 50    // 0-255


//timer4 is used for pwm

#define dir4 ((uint16_t)0x8000)						//B15
#define dir3 ((uint16_t)0x4000)						//B14
#define dir2 ((uint16_t)0x2000)						//B13
#define dir1 ((uint16_t)0x1000)						//B12

#define PWM1	 									TIM4->CCR4										
#define DIR1_SET			  				GPIOB->BSRR = dir4
#define DIR1_RESET							GPIOB->BSRR = (uint32_t)(dir4<<16u)

#define PWM2	 									TIM4->CCR3
#define DIR2_RESET							GPIOB->BSRR = (uint32_t)(dir3<<16u)
#define DIR2_SET								GPIOB->BSRR = dir3

#define PWM3	 									TIM4->CCR2
#define DIR3_RESET							GPIOB->BSRR = dir2
#define DIR3_SET								GPIOB->BSRR = (uint32_t)(dir2<<16u)

#define PWM4	 									TIM4->CCR1		 							
#define DIR4_RESET							GPIOB->BSRR = (uint32_t)(dir1<<16u)
#define DIR4_SET								GPIOB->BSRR = dir1



/*-----------------------------------------------------------------------------
														MOTOR OBJECT INIT
-----------------------------------------------------------------------------*/  

typedef struct {
	__IO int32_t Ref;  				// Input: reference
	__IO int32_t Pwm;
	__IO int32_t AbsPwm;
	__IO int32_t Offset;

	__IO int32_t K;         		// Parameter: Constant for low-pass filter (pu)
	__IO int32_t Tmp;
	__IO uint8_t Dir;
} MOTOR;

                 
#define MOTOR_DEFAULTS {0,0,0,0,1,0,0}	



void MOTOR_MACRO(MOTOR v){
	
	if(v.K == 0) v.K = 1;
	  
	v.Tmp = v.Ref/v.K;
	  
	if(v.Tmp == 0) v.Tmp = 1;
	if(v.Tmp < 0) v.Tmp = -v.Tmp;
	
	if(v.Pwm > v.Ref){
		v.Pwm -= v.Tmp;
		if(v.Pwm <= v.Ref) v.Pwm = v.Ref;
	}
	else{
		v.Pwm += v.Tmp;
		if(v.Pwm >= v.Ref ) v.Pwm = v.Ref;
	}
	
	if(v.Pwm >= 0){
		v.AbsPwm = v.Pwm;
		v.Dir = 1;
	}
	else{
		v.AbsPwm = -v.Pwm;
		v.Dir = 0;
	}
	
	v.AbsPwm += v.Offset;
}



/*-----------------------------------------------------------------------------
															DEFINE IN MAIN.C
-----------------------------------------------------------------------------*/  

volatile int16_t _value_compass;
uint8_t value_speed=240;
int16_t SPEED = 0;

int16_t SPEED_mong_muon;
int16_t SPEED_QUAY = 1;

float Huong_tinh_tien;
volatile int16_t Huong_xoay;
volatile int16_t Toc_doxoay=20;// so nho quay nhanh
volatile int16_t SPEED_tinhtien;
volatile int16_t Beta;
int16_t xoay;
uint8_t Value_vantoc_goc;
uint8_t Value_Giatoc;

int8_t giatoc;
uint8_t Enable_rotate_one_spot;


uint8_t value_pwm, dir;

uint8_t Lock_Whell;
uint8_t Giatoc_tinh_tien=10;// so cang nho chay cang nhanh

int16_t huongxoay;


uint8_t value_pwm1,value_pwm2,value_pwm3,value_pwm4,value_dir=0;
 
volatile int32_t sai_so_goc;
volatile float GocA, GocB, GocC, GocD, value_pwmA, value_pwmB, value_pwmC, value_pwmD;
volatile float  value_cosA, value_cosB, value_cosC, value_cosD;
		
MOTOR MotorA = MOTOR_DEFAULTS;
MOTOR MotorB = MOTOR_DEFAULTS;
MOTOR MotorC = MOTOR_DEFAULTS;
MOTOR MotorD = MOTOR_DEFAULTS;

volatile int16_t value_compass;



/*-----------------------------------------------------------------------------
													WRITE IN MAIN FUNCTION
-----------------------------------------------------------------------------*/  

/*

	MotorA.K = 30;
	MotorB.K = 30;
	MotorC.K = 30;
	MotorD.K = 30;

	MotorA.Offset = 0;
	MotorB.Offset = 0;
	MotorC.Offset = 0;
	MotorD.Offset = 0;

*/

/*-----------------------------------------------------------------------------
		DEFINE IN STM32FXxx_IT.C FOR INTERRUPT TO UPDATE PWM OF EACH WHEEL
-----------------------------------------------------------------------------*/  
/*


extern int16_t SPEED;
extern int16_t SPEED_mong_muon;
extern int16_t xoay;
extern volatile int16_t Beta;
extern uint8_t Value_vantoc_goc;
extern uint8_t Value_Giatoc;


extern uint8_t giatoc_giamtoc;
extern uint8_t dahuong_exit;
extern uint16_t value_game;


extern float Huong_tinh_tien;
extern volatile int16_t Huong_xoay;
extern volatile int16_t Toc_doxoay;
extern volatile int16_t SPEED_tinhtien;
extern __IO uint8_t Value_giatoc_pwm;

extern uint8_t Enable_rotate_one_spot;
extern uint8_t Lock_Whell;

extern uint8_t Giatoc_tinh_tien;

extern void Da_huong_4banh(float Huong_tinh_tien_alpha, volatile int16_t beta , uint8_t value_locity, uint8_t SPEED_TINH_TIEN,uint8_t XOAY_TAI_CHO);


uint8_t num=0;



void Tang_giam_SPEED(void)
{
	static uint8_t i;
	static uint8_t j,k;

	if(SPEED != SPEED_mong_muon){
		if(++i > Giatoc_tinh_tien){
			i=0;
			if(SPEED > SPEED_mong_muon) {
				SPEED--;
				if(SPEED <= SPEED_mong_muon) SPEED = SPEED_mong_muon;
			}
			else{
				SPEED++;
				if(SPEED >= SPEED_mong_muon )SPEED = SPEED_mong_muon;
			}
		}
	}
	
	
	if(xoay != Beta){
		if(++j > Value_vantoc_goc){
			j=0;
			if(xoay < 0){
				Beta--;
				if(Beta <= xoay) Beta = xoay;
			}
			else{
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


*/


/*-----------------------------------------------------------------------------
			THROW INTO TIMx_IROHandler FOR UPDATE PWM OF EACH WHEEL (1ms interrupt)
-----------------------------------------------------------------------------*/  

/*

if(++num>4){
		num=0;
		if(Lock_Whell == 1)
		Da_huong_4banh(Huong_tinh_tien, Huong_xoay, Toc_doxoay, SPEED_tinhtien,Enable_rotate_one_spot);
	}

		Tang_giam_SPEED();

*/




/*-----------------------------------------------------------------------------
										HAM TINH TOAN PWM VA DIR 4 BANH OMNI
-----------------------------------------------------------------------------*/  

void Da_huong_4banh(float Huong_tinh_tien_alpha, volatile int16_t beta , uint8_t value_locity, uint8_t SPEED_TINH_TIEN,uint8_t XOAY_TAI_CHO){
		
	xoay = beta;
	Value_vantoc_goc = value_locity;
	SPEED_mong_muon = SPEED_TINH_TIEN;
	value_compass = _value_compass;
	
	sai_so_goc = value_compass/10 - Beta;
	
	if(sai_so_goc > 0 && xoay != 0) giatoc = -(sai_so_goc/2 - 45);
	else if(sai_so_goc < 0 && xoay != 0) giatoc = sai_so_goc/2 + 45;
	else giatoc=0;
	if(giatoc >= 30) giatoc = 30;

	
	
	GocA = Huong_tinh_tien_alpha + value_compass/10 - 135;		
	GocB = Huong_tinh_tien_alpha + value_compass/10 + 135;		
	GocC = Huong_tinh_tien_alpha + value_compass/10 + 45;		
	GocD = Huong_tinh_tien_alpha + value_compass/10 - 45;

	
	
	value_cosA = cosf(GocA * NUM_OMNI);
	value_cosB = cosf(GocB * NUM_OMNI);
	value_cosC = cosf(GocC * NUM_OMNI);
	value_cosD = cosf(GocD * NUM_OMNI);
	
	MotorA.Ref = ((int32_t)(SPEED * value_cosA + SPEED_QUAY * sai_so_goc)) ;
	MotorB.Ref = ((int32_t)(SPEED * value_cosB + SPEED_QUAY * sai_so_goc)) ;
	MotorC.Ref = ((int32_t)(SPEED * value_cosC + SPEED_QUAY * sai_so_goc)) ;
	MotorD.Ref = ((int32_t)(SPEED * value_cosD + SPEED_QUAY * sai_so_goc)) ;
		
  
	MOTOR_MACRO(MotorA);
	MOTOR_MACRO(MotorB);
	MOTOR_MACRO(MotorC);
	MOTOR_MACRO(MotorD);
	
	value_pwmA = MotorA.AbsPwm;
	if(MotorC.Dir == 1) {
		#ifdef DIR_SELECT
			DIR3_SET;
		#else 
			DIR3_RESET;
		#endif
	}
	else{
		#ifdef DIR_SELECT
			DIR3_RESET;
		#else 
			DIR3_SET;
		#endif
	}
		
	///////////////////////	
		
	value_pwmD = MotorD.AbsPwm;
	if(MotorD.Dir == 1) {
		#ifdef DIR_SELECT
			DIR4_SET;
		#else 
			DIR4_RESET;
		#endif
	}
	else{
		#ifdef DIR_SELECT
			DIR4_RESET;
		#else 
			DIR4_SET;
		#endif
	}
	
	
	if(SPEED == 0){
		PWM1 = 0;
		PWM2 = 0;
		PWM3 = 0;
		PWM4 = 0;	
	}
	
	if(XOAY_TAI_CHO == 1){
		if((sai_so_goc > -5)&&(sai_so_goc < 5) && SPEED != 0){
			PWM1 = 2;
	    	PWM2 = 2;
	    	PWM3 = 2;
			PWM4 = 2;
		}	
		else if( SPEED == 1){
			PWM1 = ((value_pwmA>SPEED_LIMIT)?value_pwmA=SPEED_LIMIT:value_pwmA) + giatoc;
			PWM2 = ((value_pwmB>SPEED_LIMIT)?value_pwmB=SPEED_LIMIT:value_pwmB) + giatoc;
			PWM3 = ((value_pwmC>SPEED_LIMIT)?value_pwmC=SPEED_LIMIT:value_pwmC) + giatoc;
			PWM4 = ((value_pwmD>SPEED_LIMIT)?value_pwmD=SPEED_LIMIT:value_pwmD) + giatoc;
		}
	}
	else{
		PWM1 = ((value_pwmA>SPEED_LIMIT)?value_pwmA=SPEED_LIMIT:value_pwmA);
		PWM2 = ((value_pwmB>SPEED_LIMIT)?value_pwmB=SPEED_LIMIT:value_pwmB);
		PWM3 = ((value_pwmC>SPEED_LIMIT)?value_pwmC=SPEED_LIMIT:value_pwmC);
		PWM4 = ((value_pwmD>SPEED_LIMIT)?value_pwmD=SPEED_LIMIT:value_pwmD);	
	}
}













