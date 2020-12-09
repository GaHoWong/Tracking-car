#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"

#define PI 3.14159265
int  TIM3_IRQHandler(void); 
int myabs(int a);
void Set_Pwm(int moto);
void Xianfu_Pwm(void);
int Incremental_PI (int Encoder,int Target);
int Read_Encoder(u8 TIMX);


////////////////////////
void tracking_pid(void);
int Read_Offset(void);
void motor_control(void);
void motorsWrite(int speedL, int speedR);


void  TIM_PwmSetPulse (u8 TIM1_CH,u8 pulse);


#endif

