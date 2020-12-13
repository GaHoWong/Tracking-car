#include "control.h"
#include "K210.h"
#include "sys.h"

float Kp = 10, Ki = 00.4, Kd = 0;                       //pid����������� 
float error = 0, P = 0, I = 0, D = 0, PID_value = 0; //pidֱ������,��̬���
float previous_error = 0, previous_I = 0;            //���ֵ 
static int initial_motor_speed = 80;                //�����ʼ�ٶ� 

/**************************************************************************
�������ܣ�����ƫ������������ǹ���������裩
��ڲ�������
����  ֵ��ƫ����
��    ����
**************************************************************************/
void tracking_pid(void)
{
  P = error;
  I = I + error;
  D = error - previous_error;
 
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
  if(PID_value > 80)
  {
    PID_value = 80; 
  }
   if(PID_value < 0)
  {
    PID_value = 0; 
  }
  previous_error = error;
}



void K210_PI(void)
{
  P = rho_err;
  I = I + rho_err;
  D = rho_err - previous_error;
 
  PID_value = (Kp * P) + (Ki * I) + (Kd * D);
  if(PID_value > 80)
  {
    PID_value = 80; 
  }
   if(PID_value < 0)
  {
    PID_value = 0; 
  }
  previous_error = rho_err;
}


/**************************************************************************
�������ܣ�����ƫ����
��ڲ�������
����  ֵ��ƫ����
��    ����
**************************************************************************/
int Read_Offset(void)
{	
	int ldr0 = 1;
	int ldr1 = 1;
	int ldr2 = 1;
	int ldr3 = 1;
	int ldr4 = 1;
	int ldr5 = 1;
	int ldr6 = 1;	

	ldr[0]>100 ? ldr0:--ldr0;
	ldr[1]>100 ? ldr1:--ldr1;
	ldr[2]>100 ? ldr2:--ldr2;
	ldr[3]>100 ? ldr3:--ldr3;
	ldr[4]>100 ? ldr4:--ldr4;
	ldr[5]>100 ? ldr5:--ldr5;
	ldr[6]>100 ? ldr6:--ldr6;

	if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = 0;  //�м�Ĵ�����,ֱ�С�0000000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 1)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -2; //΢С��ƫ 001 0 000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 1)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = 2;  //΢С��ƫ 000 0 100
	}else if((ldr[0] == 0)&&(ldr[1] == 1)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -10;//΢��ƫ   010 0 000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 1)&&(ldr[6] == 0)){
	Offset = 10; //΢��ƫ   000 0 010
	}else if((ldr[0] == 1)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -20;  //��ƫ     100 0 000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 1)){
	Offset = 20;  //��ƫ     000 0 001
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -20;   //����ת�� 001 0 000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = 0;
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = 0;
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = 0;
	}else Offset = 0;
	
	return Offset;


}


/**************************************************************************
�������ܣ����Ƶ������
��ڲ�������
����  ֵ����
**************************************************************************/
void motor_control(void)
{
  int left_motor_speed = initial_motor_speed - PID_value;
  int right_motor_speed = initial_motor_speed + PID_value;
  
  if(left_motor_speed < 0){
    left_motor_speed = 0;
  }
  if(left_motor_speed > 80){
    left_motor_speed = 80;
  }
  if(right_motor_speed < 0){
    right_motor_speed = 0;
  }
  if(right_motor_speed > 80){
    right_motor_speed = 80;
  }
  motorsWrite(left_motor_speed,right_motor_speed);
	
}
/**************************************************************************
�������ܣ���ֵ��PWM�Ĵ���
��ڲ��������ҵ�����ٶ�
����  ֵ����
**************************************************************************/
void motorsWrite(int speedL, int speedR)
{
  if (speedR > 0) {
    TIM_PwmSetPulse(1, speedR);
  } else {
    TIM_PwmSetPulse(1, 0);
  }
 
  if (speedL > 0) {
    TIM_PwmSetPulse(2, speedL);
  } else {
    TIM_PwmSetPulse(2, 0);
  }
}


/**************************************************************************
�������ܣ���Ҫ�Ŀ��Ƴ���
��ڲ�������
����  ֵ����
��    ����ѭ��С������Ҫ���Ƴ��������10ms�ж�һ�ε��жϷ������
**************************************************************************/
int Target_velocity=50;  //�趨�ٶȿ��Ƶ�Ŀ���ٶ�Ϊ50������ÿ10ms
int TIM3_IRQHandler(void)
{
 if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)==SET)
 {
   TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //===�����ʱ��1�жϱ�־λ
	 //Read_Offset();                     //��ȡ��������ƫ��ֵֵ
   //Led_Flash(100);                              //LED��˸
	 //tracking_pid();              //����PID
	 K210_PI();
	 motor_control();            //���Ƶ��
 }
 return 0;
}

/**************************************************************************
�������ܣ�����PWMռ�ձ� 
��ڲ�������
����  ֵ����
**************************************************************************/
void  TIM_PwmSetPulse (u8 TIM1_CH,u8 pulse)
{
	u16 compareValue ; 
	compareValue = pulse * 8000 / 100; 	  //����ռ�ձ����ñȽ�ֵ

	switch(TIM1_CH)
	{
		case 1: TIM_SetCompare1(TIM1,compareValue); break;
		case 2: TIM_SetCompare2(TIM1,compareValue); break;	
		default: break;
	}
}


/**************************************************************************
�������ܣ�����ֵ����
��ڲ�����int
����  ֵ��unsigned int
**************************************************************************/
int myabs(int a) //ȡ����ֵ
{ 		   
	 int temp;
	 if(a<0)  temp=-a;  
	 else temp=a;
	 return temp;
}
/**************************************************************************
�������ܣ�����PI������
��ڲ���������������ֵ��Ŀ���ٶ�
����  ֵ�����PWM
��������ʽ��ɢPID��ʽ 
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)������ƫ�� 
e(k-1)������һ�ε�ƫ��  �Դ����� 
pwm�����������
�����ǵ��ٶȿ��Ʊջ�ϵͳ���棬ֻʹ��PI����
pwm+=Kp[e��k��-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (int Encoder,int Target)
{ 	
   float Kp=20,Ki=30;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //����ƫ��
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //����ʽPI������
	 Last_bias=Bias;	                   //������һ��ƫ�� 
	 return Pwm;                         //�������
}
