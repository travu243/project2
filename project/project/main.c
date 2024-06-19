
 #include "stm32f4xx.h"
 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <string.h>
 #include "ctype.h"
 
 
 #include "config_encoder.h"
 #include "config_uart.h"
 #include "config_pwm.h" 
 #include "Elec_Compass.h"  
 #include "lcd.h"
 #include "Motor.h"
 #include "config_IO.h"
 

#define PI 3.14159265
#define SPEED_LIMIT 250      // MAX  255
#define NUM_OMNI (PI / 180.0)
#define OFFSET_XOAY 50    // 0-255
//#define DIR_SELECT 1

#define UP 				(1<<12) //0xefff    //12
#define DOWN 			(1<<14) //0xbfff		//14
#define LEFT 			(1<<15)//0x7fff		//15
#define RIGHT 		(1<<13)//0xdfff		//13
#define TRIANGLE 	(1<<4)//0xffef		//4
#define O_KEY 		(1<<5)//0xffdf		//5
#define X_KEY 		(1<<6)//0xffbf		//6
#define SQUASE 		(1<<7)//0xff7f		//7
#define SELECT 		(1<<8)//0xfeff		//8
#define START 		(1<<11)//0xf7ff		//11
#define L1 				(1<<2)//0xfffb		//2
#define L2 				(1<<0)//0xfffe		//0
#define R1 				(1<<3)//0xfff7		//3
#define R2 				(1<<1)//0xfffd		//1


vu32 var_i=0;
u8 i=0;
vu32 tick_time_gu32=0;
vs16 _value_compass;
vs16 G_Z,G_Y,G_X;

vu32 time;
u8 value_speed=240;
int16_t SPEED = 0;

int16_t SPEED_mong_muon;
int16_t SPEED_QUAY = 1;

 float Huong_tinh_tien;
 vs16 Huong_xoay;
 vs16 Toc_doxoay;// so nho quay nhanh
 vs16 SPEED_tinhtien;
 vs16 Beta;
int16_t xoay;
u8 Value_vantoc_goc;
u8 Value_Giatoc;
u32 time_out;
__IO u8 Value_giatoc_pwm = 1;
s8 giatoc_xoay_tai_cho,giatoc;
u8 Enable_rotate_one_spot;
vu32 test1,send_a;

RCC_ClocksTypeDef ClockSys;
vs32 TestencoderTimer3;
vs32 TestencoderTimer2;
vs32 TestencoderTimer4;
vs32 TestencoderTimer1;

u8 value_pwm, dir;

u8 show_lcd;
#define max_buff 10
u8 buff_game[max_buff];
u8 cnt;
u16 value_game;
u16 value_game_Joytic_Left;
u16 value_game_Joytic_Right;
u8 ktra;
u8 Lock_Whell;
u8 Giatoc_tinh_tien;// so cang nho chay cang nhanh
char buff_speed[100];


char Command_compass;
#define MAX_STRLEN 100 // this is the maximum string length of our string in characters
char received_string[MAX_STRLEN+1]; // this will hold the recieved string
char str_rev[MAX_STRLEN];
char str[MAX_STRLEN];

u8 JoysticXL;
u8 JoysticYL;
u8 JoysticXR;
u8 JoysticYR;


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void Delay(__IO uint32_t nCount)
{
  while(nCount--)
  {
  }
}

 //XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
 
u8 Vgetchar1(void)
{
//	while((USART1->SR & USART_FLAG_RXNE) == (uint16_t)RESET); 
//	return USART1->DR;
	
	while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)==RESET);
	return USART_ReceiveData(USART1);
	
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXX
void send_uart2_char(u8 ch)
{
	USART_SendData(USART2, (uint8_t) ch);
	while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
}
//xxxxxxxxxxxx
void Vsend_char(u8 ch)
{
		USART_SendData(USART1, (uint8_t) ch);
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{};		
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
void send_string_uart(u8 *p,u8 num_uart)
{
	
	
	if(num_uart==1)
	{
		while(*p)
		{
			USART_SendData(USART1, (uint8_t) *p++);
			while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
			{};	
		}
	}
	
	else if(num_uart==2)
	{
		while(*p)
		{
			USART_SendData(USART2, (uint8_t) *p++);
			while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
			{};	
		}
	}
	
	else if(num_uart==3)
	{
		while(*p)
		{
			USART_SendData(USART3, (uint8_t) *p++);
			while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET)
			{};	
		}
	}
	
	
	else if(num_uart==4)
	{
		while(*p)
		{
			USART_SendData(UART4, (uint8_t) *p++);
			while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
			{};	
		}
	}
	
}
//xxxxxxxxxxxx


void delay_ms_stick(u32 del)
{
	u32 a;
	a=del+tick_time_gu32;
	while(tick_time_gu32<a);
	
}
//xxxxxxxxxxxxxx
	u8 getchar_u8=0;
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
int16_t huongxoay ;

u8 value_pwm1,value_pwm2,value_pwm3,value_pwm4,value_dir=0;
 
		vs32 sai_so_goc;
		volatile float GocA, GocB, GocC, GocD, value_pwmA, value_pwmB, value_pwmC, value_pwmD;
		volatile float  value_cosA, value_cosB, value_cosC, value_cosD;
MOTOR MotorA = MOTOR_DEFAULTS;
MOTOR MotorB = MOTOR_DEFAULTS;
MOTOR MotorC = MOTOR_DEFAULTS;
MOTOR MotorD = MOTOR_DEFAULTS;
vs16 value_compass;

//__IO uint8_t offsetMotor = 6;  // 


	
void Da_huong_4banh(float Huong_tinh_tien_alpha, vs16 beta , u8 value_locity, u8 SPEED_TINH_TIEN,u8 XOAY_TAI_CHO)
	{
	
		
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

		
		
		value_cosA = cosf(GocA * (float)(NUM_OMNI));
		value_cosB = cosf(GocB * (float)(NUM_OMNI));
		value_cosC = cosf(GocC * (float)(NUM_OMNI));
		value_cosD = cosf(GocD * (float)(NUM_OMNI));
		
		MotorA.Ref = ((int32_t)(SPEED * value_cosA + SPEED_QUAY * sai_so_goc)) ;
		MotorB.Ref = ((int32_t)(SPEED * value_cosB + SPEED_QUAY * sai_so_goc)) ;
		MotorC.Ref = ((int32_t)(SPEED * value_cosC + SPEED_QUAY * sai_so_goc)) ;
		MotorD.Ref = ((int32_t)(SPEED * value_cosD + SPEED_QUAY * sai_so_goc)) ;
		
  
MOTOR_MACRO(MotorA);
MOTOR_MACRO(MotorB);
MOTOR_MACRO(MotorC);
MOTOR_MACRO(MotorD);

value_pwmA = MotorA.AbsPwm;
if(MotorA.Dir == 1) {
#ifdef DIR_SELECT
  DIR1_SET;
#else 
	DIR1_RESET;
#endif
}
else{
#ifdef DIR_SELECT
  DIR1_RESET;
#else 
	DIR1_SET;
#endif
}
	
///////////////////////	
	
value_pwmB = MotorB.AbsPwm;
if(MotorB.Dir == 1) {
#ifdef DIR_SELECT
  DIR2_SET;
#else 
	DIR2_RESET;
#endif
}
else{
#ifdef DIR_SELECT
  DIR2_RESET;
#else 
	DIR2_SET;
#endif
}
	
///////////////////////	
	
value_pwmC = MotorC.AbsPwm;
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
	
	if(XOAY_TAI_CHO == 1)
	{
	if((sai_so_goc > -5)&&(sai_so_goc < 5) && SPEED != 0)
		{
		PWM1 = 2;
    PWM2 = 2;
    PWM3 = 2;
		PWM4 = 2;
		}	
	else if( SPEED == 1) 
		{
		PWM1 = ((value_pwmA>SPEED_LIMIT)?value_pwmA=SPEED_LIMIT:value_pwmA) + giatoc;
		PWM2 = ((value_pwmB>SPEED_LIMIT)?value_pwmB=SPEED_LIMIT:value_pwmB) + giatoc;
		PWM3 = ((value_pwmC>SPEED_LIMIT)?value_pwmC=SPEED_LIMIT:value_pwmC) + giatoc;
		PWM4 = ((value_pwmD>SPEED_LIMIT)?value_pwmD=SPEED_LIMIT:value_pwmD) + giatoc;
		}
	}
	else 
	{
		PWM1 = ((value_pwmA>SPEED_LIMIT)?value_pwmA=SPEED_LIMIT:value_pwmA);
		PWM2 = ((value_pwmB>SPEED_LIMIT)?value_pwmB=SPEED_LIMIT:value_pwmB);
		PWM3 = ((value_pwmC>SPEED_LIMIT)?value_pwmC=SPEED_LIMIT:value_pwmC);
		PWM4 = ((value_pwmD>SPEED_LIMIT)?value_pwmD=SPEED_LIMIT:value_pwmD);	
	}

}
	
void Test_Encoder(void)
{

	SPEED_tinhtien = 50;
	Huong_tinh_tien = 90;
	
	while(ReadEncoder(1) < 106677)
		{
		delay_ms(10);
		}
		
		SPEED_tinhtien = 0;
			while( 1)
		{
			
		}
}

//xxxxxxxxxxxxxxxxxxxxx
void test_chay_xoay(void)
{
	char mang[20];
	
ClearEncoder(4);delay_ms(5);	
	
Huong_tinh_tien=2;
Giatoc_tinh_tien=20;
SPEED_tinhtien=50;
Lock_Whell=1;// 1 cho phep chay da huong 4 banh
Huong_xoay=0;
Toc_doxoay=0;
Enable_rotate_one_spot=0;

while(ReadEncoder(2)<3000)
{
	delay_ms(5);
}	



Huong_xoay=180;
Toc_doxoay=5;
delay_ms(4000);

Lock_Whell=0;
PWM1=PWM2=PWM3=PWM4=2;

while(1)
{
		TestencoderTimer4=ReadEncoder(1);
		sprintf(mang,"E4=%i ",TestencoderTimer4);
		lcd_Goto(3,0 );lcd_Print_Data((u8 *)mang);
		delay_ms(10);
}


}


void test_goc1(void)
{
	char mang[30];
	
ClearEncoder(1);delay_ms(5);	
	
Huong_tinh_tien=45;
Giatoc_tinh_tien=5;
SPEED_tinhtien=30;
Lock_Whell=1;// 1 cho phep chay da huong 4 banh
Huong_xoay=0;
Toc_doxoay=0;
Enable_rotate_one_spot=0;

while(ReadEncoder(1)>-800)
{
	delay_ms(5);
}	
SPEED_tinhtien=50;
while(ReadEncoder(1)>-5800)
{
	delay_ms(5);
}
Giatoc_tinh_tien=2;
SPEED_tinhtien=20;
while(ReadEncoder(1)>-9500)
{
	delay_ms(5);
}


Huong_tinh_tien=90;
SPEED_tinhtien=20;
while(ReadEncoder(1)>-12000)
{
	delay_ms(5);
}

ClearEncoder(1);delay_ms(1);	
Huong_tinh_tien=135;
SPEED_tinhtien=20;
while(ReadEncoder(1)>-1492)// cheo lan 1 135 do
{
	delay_ms(5);
}
SPEED_tinhtien=100;
while(ReadEncoder(1)>-8492)// cheo lan 1 135 do
{
	delay_ms(5);
}
SPEED_tinhtien=20;
while(ReadEncoder(1)>-12492)// cheo lan 1 135 do
{
	delay_ms(5);
}


ClearEncoder(1);delay_ms(1);	
Huong_tinh_tien=45;
SPEED_tinhtien=20;
while(ReadEncoder(1)>-1700) // cheo lan 2 45 do
{
	delay_ms(5);
}
SPEED_tinhtien=80;
while(ReadEncoder(1)>-8000) // cheo lan 2 45 do
{
	delay_ms(5);
}
SPEED_tinhtien=20;
while(ReadEncoder(1)>-11000) // cheo lan 2 45 do
{
	delay_ms(5);
}

ClearEncoder(1);delay_ms(1);	
Huong_tinh_tien=135;
while(ReadEncoder(1)>-7350) // cheo lan 2 135 do
{
	delay_ms(5);
}

ClearEncoder(1);delay_ms(1);	
Huong_tinh_tien=90;
SPEED_tinhtien=50;
while(ReadEncoder(1)>-23000) // chay thang qua song
{
	delay_ms(5);
}
SPEED_tinhtien=20;
while(ReadEncoder(1)>-27000) // chay thang qua song
{
	delay_ms(5);
}


ClearEncoder(2);delay_ms(1);	
Huong_tinh_tien=0;
SPEED_tinhtien=20;
while(ReadEncoder(2)>-5000) // chay qua trao the bai
{
	delay_ms(5);
}

SPEED_tinhtien=80;
while(ReadEncoder(2)>-20000) // chay qua trao the bai
{
	delay_ms(5);
}
SPEED_tinhtien=20;
while(ReadEncoder(2)>-30000) // chay qua trao the bai
{
	delay_ms(5);
}

//SPEED_tinhtien=30;
//Giatoc_tinh_tien=10;
//while(ReadEncoder(4)<46000)
//{
//	delay_ms(5);
//}


Lock_Whell=0;
PWM1=PWM2=PWM3=PWM4=2;

while(1)
{

sprintf(mang,"E1=%i   ",ReadEncoder(1));
lcd_Goto(2,0 );lcd_Print_Data((u8 *)mang);
delay_ms(50);
}
	
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void test_TZ1(void)
{
	
ClearEncoder(4);delay_ms(5);	
	
Huong_tinh_tien=78;
Giatoc_tinh_tien=30;
SPEED_tinhtien=50;
Lock_Whell=1;// 1 cho phep chay da huong 4 banh
Huong_xoay=0;
Toc_doxoay=0;
Enable_rotate_one_spot=0;

while(ReadEncoder(4)<6000)
{
	delay_ms(5);
}	

SPEED_tinhtien=120;
while(ReadEncoder(4)<36000)
{
	delay_ms(5);
}	

SPEED_tinhtien=30;
Giatoc_tinh_tien=10;
while(ReadEncoder(4)<46000)
{
	delay_ms(5);
}

Lock_Whell=0;
PWM1=PWM2=PWM3=PWM4=2;

while(1);


	
}


void test_TZ2(void)
{
	
ClearEncoder(4);delay_ms(5);	
	
Huong_tinh_tien=82;
Giatoc_tinh_tien=20;
SPEED_tinhtien=50;
Lock_Whell=1;// 1 cho phep chay da huong 4 banh
Huong_xoay=0;
Toc_doxoay=0;
Enable_rotate_one_spot=0;

while(ReadEncoder(4)<6000)
{
	delay_ms(5);
}	

SPEED_tinhtien=150;
Giatoc_tinh_tien=10;
while(ReadEncoder(4)<50000)
{
	delay_ms(5);
}	

SPEED_tinhtien=50;
Giatoc_tinh_tien=5;
while(ReadEncoder(4)<64000)
{
	delay_ms(5);
}

Huong_tinh_tien=0;
SPEED_tinhtien=50;
Giatoc_tinh_tien=15;

delay_ms(5000);

Lock_Whell=0;
PWM1=PWM2=PWM3=PWM4=2;

while(1);


	
}

//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void Gamepad_hc05(void){
//	u8 rst_compass;
	
//	if(!(value_game & (L1|UP)))
//	{
//			test_goc1();
//	}
		
	if(value_game == (u16)(~(L1|UP))) // nut UP 
		{
			
////		lcd_Goto(3,0);lcd_Print_Data((u8 *)"UP                 ");
////											Huong_tinh_tien = 90;
////											//Toc_doxoay = 10;
////			Enable_rotate_one_spot = 0; 
////			Lock_Whell = 1;
////			//Test_Encoder();
//			test_TZ1();
			test_goc1();
		}
	else if(value_game == (u16)(~(L1|DOWN))) 
		{
//		lcd_Goto(3,0);lcd_Print_Data((u8 *)"DOWN              ");
//											Huong_tinh_tien = -90;
//				
			test_chay_xoay();
			
		}
	else if(value_game == (u16)(~(LEFT))) 
		{
//		lcd_Goto(3,0);lcd_Print_Data((u8 *)"LEFT              ");
//											Huong_tinh_tien = 0;
//			
				test_TZ2();
//			Lock_Whell=0;
//			PWM1=PWM2=PWM3=PWM4=;
		}
	else if(value_game == (u16)(~(RIGHT))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"RIGHT            ");
											Huong_tinh_tien = 180;
											

		}
	else if(value_game == (u16)(~(TRIANGLE))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"XOAY 90            ");
											Huong_xoay = 90;
											

			
		}
	else if(value_game == (u16)(~(O_KEY))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"XOAY -90              ");
											Huong_xoay = -90;
											

		}
	else if(value_game == (u16)(~(X_KEY))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"Goc 0              ");
											Huong_xoay = 0;
											

		}
	else if(value_game == (u16)(~(SQUASE))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"SQUASE            ");
											Huong_xoay = 90;
											SPEED_tinhtien = 1;
											Enable_rotate_one_spot = 1;
		}
	else if(value_game == (u16)(~(SELECT))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"SELECT            ");
											Huong_xoay = -90;
											SPEED_tinhtien = 1;
											Enable_rotate_one_spot = 1;

		}
	else if(value_game == (u16)(~(START))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"START              ");
											Huong_xoay = 0;
											SPEED_tinhtien = 1;
											Enable_rotate_one_spot = 1;
			
		}
//	else if(value_game == (u16)(~(R1))) 
//		{
//		  lcd_Goto(3,0);lcd_Print_Data((u8 *)"RST RESET                 ");
//			NVIC_SystemReset();
//		}
	else if(value_game == (u16)(~(R2))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"R2                 ");
					Lock_Whell = 0;
					Huong_xoay = 0;
					Command_compass = 'a';
					delay_ms(100);
					Command_compass = 'z';
			
		}
	else if(value_game == (u16)(~(L1))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"L1                 ");
		if(SPEED_tinhtien < 240)
      SPEED_tinhtien ++;
		if(SPEED_tinhtien >= 240) SPEED_tinhtien = 240;
		sprintf(buff_speed,"SPEED : %5d",SPEED_tinhtien);
			lcd_Goto(1,0);lcd_Print_Data((u8 *)buff_speed);
		}
	else if(value_game == (u16)(~(L2))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"L2                 ");
		if(SPEED_tinhtien >= 0)
      SPEED_tinhtien--;
		if(SPEED_tinhtien <=0) SPEED_tinhtien = 0;
		sprintf(buff_speed,"SPEED : %5d",SPEED_tinhtien);
			lcd_Goto(1,0);lcd_Print_Data((u8 *)buff_speed);		
		}
	else if(value_game == (u16)~((UP | O_KEY ))) 
		{
		lcd_Goto(3,0);lcd_Print_Data((u8 *)"UP O_KEY RST COMPASS");

					

		}
//	else if(value_game == (u16)~((UP | O_KEY | TRIANGLE))) {lcd_Goto(3,0);lcd_Print_Data((u8 *)"UP O_KEY TRIANGLE        ");}
//	else if(value_game == (u16)~(( O_KEY | TRIANGLE | R1 | R2 | L1 | L2))) {lcd_Goto(3,0);lcd_Print_Data((u8 *)"O_KEYTRIANGLEL12R12");}
}


u8 Dir1_debug=0,speed_debug=1;


void test_PWM(void)
{
	//u8 i;
	

		PWM1=PWM2=PWM3=PWM4=speed_debug;
		if(Dir1_debug)
		{
			DIR1_SET;DIR2_SET;DIR3_SET;DIR4_SET;
		}
		else
		{
			DIR1_RESET;DIR2_RESET;DIR3_RESET;DIR4_RESET;
		}
		
		delay_ms(10);
	
//	while(1)
//	{
//		
//	for(i=0;i<255;i++)
//	{
//		PWM1=i;
//		delay_ms(50);
//	}
//	
//	for(;i>2;i--)
//	{
//		PWM1=i;
//		delay_ms(50);
//	}
//	
//	DIR1_TOGGLE;
}



int main(void)
{
  
  char mang[100];
	char mang1[100];


	//SCB->VTOR = 0x8004000 ;// SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET;
	
	
	config_uart1(19200);
//config_uart2(115200);
	//config_uart3(115200);
	config_uart4(115200);
	Config_timer67();
	ConfigEncoder();
	config_PWM();
  Config_Input_Digital();
	Config_Output_Digital();
	
	//test_PWM();
	
	MotorA.K = 30;
  MotorB.K = 30;
  MotorC.K = 30;
  MotorD.K = 30;
  
  MotorA.Offset = 0;
  MotorB.Offset = 0;
  MotorC.Offset = 0;
  MotorD.Offset = 0;
  
	config_compass();
	lcd_Init();
	//config_uart2_dma(115200);

	SPEED = 0;
	Giatoc_tinh_tien=30;
	


 // mang="12354";
//	strcpy(mang,"123456"); 


	 if (SysTick_Config(SystemCoreClock / 1000))  // reload value = 1000 --> systick 1ms
   { 
     /* Capture error */ 
     while (1);
   }
//	 send_a=0;
//	  while(++send_a < 5){
//	 	Command_compass = 'a';
//		delay_ms(100);
//	 }
//	 
//ClearEncoder(1);	ClearEncoder(2); ClearEncoder(3);ClearEncoder(4); 
//	Command_compass = 'z';

//	Lock_Whell = 0;  
 
	while (1)
	{  
		

//		lcd_Goto(2,3);lcd_Print_Data((u8 *)"Compass Value");
		
//sprintf(buffer,"%5d",_value_compass);
//lcd_Goto(0,0);lcd_Print_Data((u8 *)buffer);
//		
//sprintf(buffer,"%4X  %4X  %4X   ",value_game,value_game_Joytic_Left,value_game_Joytic_Right);
//lcd_Goto(1,0);lcd_Print_Data((u8 *)buffer);					
					
					
		
				

//sprintf(buffer,"%3.1f  %3.1f  %3.1f   ",MotoA,MotoB,MotoC);	
//lcd_Goto(2,0);lcd_Print_Data((u8 *)buffer);
//sprintf(buffer,"%5d",_value_compass);
		
//sprintf(buffer,"Z=%3d Y=%3d X=%3d ",G_Z,G_Y,G_X);
//		
//lcd_Goto(0,0 );lcd_Print_Data((u8 *)buffer);
//		
//		sprintf(mang, "%2d %2d %2d", SPEED_mong_muon, SPEED_QUAY, Beta);
//		lcd_Goto(3,12 );lcd_Print_Data((u8 *)mang);
	
		
//			RCC_GetClocksFreq(&ClockSys);
//			test1=ClockSys.HCLK_Frequency;
//		sprintf(mang,"xtal=%u  ",test1);
//		lcd_Goto(1,0 );lcd_Print_Data((u8 *)mang);
		TestencoderTimer1=ReadEncoder(1);
		TestencoderTimer2=ReadEncoder(2);
		TestencoderTimer3=ReadEncoder(3);
		TestencoderTimer4=ReadEncoder(4);
		
		sprintf(mang,"E2=%i E1=%i      ",TestencoderTimer2,TestencoderTimer1);
		sprintf(mang1,"E4=%i E3=%i     ",TestencoderTimer4,TestencoderTimer3);
		lcd_Goto(2,0 );lcd_Print_Data((u8 *)mang);
		
		lcd_Goto(3,0 );lcd_Print_Data((u8 *)mang1);
//		test_PWM();
		

Gamepad_hc05();

		
	}
}
