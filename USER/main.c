#include "sys.h"


u8 flag_Stop=1;     //ֹͣ��־λ
int Encoder;        //���������������
int motor;           //���PWM����
vu16 ldr[7];        //ADC��ֵ��ŵı���
int Offset = 0;     //ƫ����


 int main(void)
 {	
	 Stm32_Clock_Init(9);      //ϵͳʱ������
	 delay_init();             //=====��ʱ��ʼ��
	 LED_Init();               //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	 UART_Init(115200);         //=====��ʼ������1
	 MOTOR_Init();              //��ʼ�����Ƶ�������IO
	 pwm_Init(7199,0);         //��ʼ��pwm���
	 //Encoder_Init_TIM2();      //��ʼ������������ʱ����,ѭ��С����ʱ�ò���
	 ADC_Configuration();      //ADC��ʼ������,
	 TIM3_Int_Init(99,7199);   //10msһ���ж�
	 while(1)
	 {
	 //printf("Encoder:%d \r\n",Encoder);
	 }
 }

 
 /*
ѡ��IO�ӿڹ�����ʽ��
GPIO_Mode_AIN ģ������
GPIO_Mode_IN_FLOATING ��������
GPIO_Mode_IPD ��������
GPIO_Mode_IPU ��������
GPIO_Mode_Out_PP �������
GPIO_Mode_Out_OD ��©���
GPIO_Mode_AF_PP �����������
GPIO_Mode_AF_OD ���ÿ�©���
*/
