#include "moto.h"


/**************************************************************************
函数功能：初始化电机
入口参数：无
返回  值：无
**************************************************************************/
void MOTOR_Init(void)//
{
  GPIO_InitTypeDef GPIO_InitStruct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	//PB12 13 14 15推挽输出
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB,&GPIO_InitStruct);	
}

/**************************************************************************
函数功能：初始化PWM输出
入口参数：arr,psc
返回  值：无
**************************************************************************/

void pwm_Init(u16 arr,u16 psc) //初始化pwm输出引脚
{	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
  GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  //使能定时器1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE); //使能GPIOA的时钟
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;         //复用输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11;   //PA8 PA11
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	TIM_TimeBaseInitStruct.TIM_Period = arr;                     //设定计数器自动重装值 
	TIM_TimeBaseInitStruct.TIM_Prescaler  = psc;                 //设定预分频器
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //TIM向上计数模式
	TIM_TimeBaseInitStruct.TIM_ClockDivision = 0;                //设置时钟分割
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStruct);              //初始化定时器
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM2;              //选择PWM2模式
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;  //比较输出使能
	TIM_OCInitStruct.TIM_Pulse = 0;                             //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;       //设置输出极性
	TIM_OC1Init(TIM1,&TIM_OCInitStruct);                         //初始化输出比较参数
	
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable); //CH1使能预装载寄存器
	 
	TIM_CtrlPWMOutputs(TIM1,ENABLE);                 //高级定时器输出必须设置这句
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);              //使能TIM1在ARR上的预装载寄存器
	
	TIM_Cmd(TIM1,ENABLE);                            //使能定时器1
}

