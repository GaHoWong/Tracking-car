#ifndef __MOTO_H
#define __MOTO_H
#include "sys.h"


void MOTOR_Init(void);    //初始化控制电机所需的引脚
void pwm_Init(u16 arr,u16 psc); //PWM输出初始化
#define PWMA   TIM1->CCR1
#define AIN2   PBout(15)
#define AIN1   PBout(14)
#define BIN1   PBout(13)
#define BIN2   PBout(12)
#define PWMB   TIM1->CCR4

#endif

