#ifndef __MOTO_H
#define __MOTO_H
#include "sys.h"

void pwm_Init(u16 arr,u16 psc); //PWMÊä³ö³õÊ¼»¯
#define PWMA   TIM1->CCR1
#define AIN2   PBout(15)
#define AIN1   PBout(14)
#define BIN1   PBout(13)
#define BIN2   PBout(12)
#define PWMB   TIM1->CCR4

#endif

