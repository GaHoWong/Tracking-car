#ifndef __LDR_H
#define __LDR_H 			   
#include "sys.h"


#define ADC1_DR_Address    ((uint32_t)0x4001244C) //ADC1�������ĵ�ַ����ο��ֲ�ó���

//����ADC�ӿ�PA1-7
#define ADC_CH1		GPIO_Pin_1	//����ADC�ӿ� 
#define ADC_CH2		GPIO_Pin_2  //����ADC�ӿ� 
#define ADC_CH3		GPIO_Pin_3  //����ADC�ӿ� 
#define ADC_CH4		GPIO_Pin_4	//����ADC�ӿ� 
#define ADC_CH5		GPIO_Pin_5	//����ADC�ӿ� 
#define ADC_CH6		GPIO_Pin_6	//����ADC�ӿ� 
#define ADC_CH7		GPIO_Pin_7	//����ADC�ӿ� 




void ADC_DMA_Init(void);
void ADC_GPIO_Init(void);
void ADC_Configuration(void);

#endif





























