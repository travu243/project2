/* =================================================================================
File name:        MOTOR.H
===================================================================================*/


#ifndef __MOTOR_H__
#define __MOTOR_H__

#include <stdint.h>
#include <core_cm4.h>

typedef struct {
       __IO int32_t Ref;  		// Input: reference
       __IO int32_t Pwm;      // temp:
       __IO int32_t AbsPwm;     // Output:
       __IO int32_t Offset;     // Output:
  
       __IO int32_t K;         		// Parameter: Constant for low-pass filter (pu)
       __IO int32_t Tmp;				//Variable: Temp variable
       __IO int32_t Dir;      // Direct
       } MOTOR;   	// Data type created

/*-----------------------------------------------------------------------------
Default initalizer for the SPEED_MEAS_QEP object.
-----------------------------------------------------------------------------*/                     
#define MOTOR_DEFAULTS   {0,0,0,0, 1,0,0}	

/*------------------------------------------------------------------------------
 MOTOR Macro Definition
------------------------------------------------------------------------------*/


#define MOTOR_MACRO(v)	        \
  if(v.K == 0){                 \
    v.K = 1;}                   \
  v.Tmp = v.Ref/v.K;           \
  if(v.Tmp == 0){               \
    v.Tmp = 1;}                 \
  if(v.Tmp < 0){                \
    v.Tmp = -v.Tmp;}	          \
  if(v.Pwm > v.Ref){      \
    v.Pwm -= v.Tmp;            \
    if(v.Pwm <= v.Ref) {v.Pwm = v.Ref;}}  \
  else {                                              \
    v.Pwm += v.Tmp;                                    \
    if(v.Pwm >= v.Ref ){v.Pwm = v.Ref;}}  \
  if(v.Pwm >= 0){  \
    v.AbsPwm = v.Pwm;  \
    v.Dir = 1;}   \
  else{           \
    v.AbsPwm = -v.Pwm;  \
    v.Dir = 0;}   \
  v.AbsPwm += v.Offset; \
  
#endif // __MOTOR_H__
