#ifndef __MOTO_H
#define __MOTO_H
#include "sys.h"


void MOTOR_Init(void);    //��ʼ�����Ƶ�����������
void pwm_Init(u16 arr,u16 psc); //PWM�����ʼ��
#define PWMA   TIM1->CCR1
#define AIN2   PBout(15)
#define AIN1   PBout(14)
#define BIN1   PBout(13)
#define BIN2   PBout(12)
#define PWMB   TIM1->CCR4

#endif

