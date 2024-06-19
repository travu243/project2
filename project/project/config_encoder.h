
#ifndef _CONFIG_ENCODER_H_
 #define _CONFIG_ENCODER_H_
 
 #include "stm32f4xx.h"
 
 #define OFFSET_ENCODER 32768
 #define OFFSET_32B_ENCODER OFFSET_ENCODER //0XFFFFFFFF/2
 


	void Encoder1_Tim2_Init(void);
	void Encoder2_Tim3_Init(void);
	void Encoder3_Tim4_Init(void);
	void Encoder4_Tim5_Init(void);
	void ClearEncoder(u32 num);
	s32 ReadEncoder(u32 num);
	
	void ConfigEncoder(void);
	
	
	
#endif

