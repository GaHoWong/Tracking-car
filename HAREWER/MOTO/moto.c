#include "moto.h"


/**************************************************************************
�������ܣ���ʼ�����
��ڲ�������
����  ֵ����
**************************************************************************/
void MOTOR_Init(void)//
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//PB12 13 14 15�������
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStruct);	
}

/**************************************************************************
�������ܣ���ʼ��PWM���
��ڲ�����arr,psc
����  ֵ����
**************************************************************************/

void pwm_Init(u16 arr,u16 psc) //��ʼ��pwm�������
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //ʹ�ܶ�ʱ��1ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //ʹ��GPIOA��ʱ��
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;         //�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;   //PA8 PA11
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;                     //�趨�������Զ���װֵ 
	TIM_TimeBaseInitStruct.TIM_Prescaler  = psc;                 //�趨Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;                //����ʱ�ӷָ�
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);              //��ʼ����ʱ��
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;              //ѡ��PWM2ģʽ
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
	TIM_OCInitStruct.TIM_Pulse = 0;                             //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;       //�����������
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);                         //��ʼ������Ƚϲ���
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //CH1ʹ��Ԥװ�ؼĴ���
	 
	TIM_CtrlPWMOutputs(TIM1,ENABLE);                 //�߼���ʱ����������������
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);              //ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM1,ENABLE);                            //ʹ�ܶ�ʱ��1
}

