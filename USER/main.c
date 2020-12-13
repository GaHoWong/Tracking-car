#include "sys.h"


u8 flag_Stop=1;     //停止标志位
int Encoder;        //编码器的脉冲计数
int motor;           //电机PWM变量
int Offset = 0;     //偏移量


 int main(void)
 {	
	 Stm32_Clock_Init(9);      //系统时钟设置
	 delay_init();             //=====延时初始化
	 LED_Init();               //=====初始化与 LED 连接的硬件接口
	 UART_Init(115200);         //=====初始化串口1
	 uart2_init(115200);
	 pwm_Init(7199,0);         //初始化pwm输出，10Khz
	 //Encoder_Init_TIM2();      //初始化计数器（定时器）,循迹小车暂时用不到
	// ADC_Configuration();      //ADC初始化设置,
	 TIM3_Int_Init(99,7199);   //10ms一次中断
	 
	 while(1)
	 {
//		 printf("ldr[0]:%d \r\n",ldr[0]);
//		 printf("ldr[1]:%d \r\n",ldr[1]);
//		 printf("ldr[2]:%d \r\n",ldr[2]);
//		 printf("ldr[3]:%d \r\n",ldr[3]);
//		 printf("ldr[4]:%d \r\n",ldr[4]);
//		 printf("ldr[5]:%d \r\n",ldr[5]);
//		 printf("ldr[6]:%d \r\n",ldr[6]);
//		 delay_ms(300);
	 }
 }

 
 /*
选择IO接口工作方式：
GPIO_Mode_AIN 模拟输入
GPIO_Mode_IN_FLOATING 浮空输入
GPIO_Mode_IPD 下拉输入
GPIO_Mode_IPU 上拉输入
GPIO_Mode_Out_PP 推挽输出
GPIO_Mode_Out_OD 开漏输出
GPIO_Mode_AF_PP 复用推挽输出
GPIO_Mode_AF_OD 复用开漏输出
*/
