#include "sys.h"
#include "K210.h"

u8 flag_Stop=1;     //ֹͣ��־λ
int Encoder;        //���������������
int motor;           //���PWM����
int Offset = 0;     //ƫ����


 int main(void)
 {	
	 Stm32_Clock_Init(9);      //ϵͳʱ������
	 delay_init();             //=====��ʱ��ʼ��
	 pwm_Init(7199,0);         //��ʼ��pwm�����10Khz
	 LED_Init();               //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
	 UART_Init(115200);         //=====��ʼ������1
	// uart2_init(115200);
		USART2_Init(115200);
	 //Encoder_Init_TIM2();      //��ʼ������������ʱ����,ѭ��С����ʱ�ò���
	// ADC_Configuration();      //ADC��ʼ������,
	 TIM3_Int_Init(99,7199);   //10msһ���ж�
	 
	 while(1)
	 {		 
		 //printf("%d \r\n",rho_err);
	//	 printf("OK \r\n",rho_err);
		 delay_ms(200);
//		 printf("ldr[1]:%d \r\n",ldr[1]);
//		 printf("ldr[2]:%d \r\n",ldr[2]);
//		 printf("ldr[3]:%d \r\n",ldr[3]);
//		 printf("ldr[4]:%d \r\n",ldr[4]);
//		 printf("ldr[5]:%d \r\n",ldr[5]);
//		 printf("ldr[6]:%d \r\n",ldr[6]);
//		 delay_ms(300);
	//	 TIM_PwmSetPulse(1,10);
	//	 TIM_PwmSetPulse(2,10);
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
