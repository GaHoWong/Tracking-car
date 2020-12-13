#include "control.h"
#include "K210.h"
#include "sys.h"

float Kp = 10, Ki = 00.4, Kd = 0;                       //pid弯道参数参数 
float error = 0, P = 0, I = 0, D = 0, PID_value = 0; //pid直道参数,静态误差
float previous_error = 0, previous_I = 0;            //误差值 
static int initial_motor_speed = 80;                //电机初始速度 

/**************************************************************************
函数功能：计算偏移量（红外或是光敏电阻电阻）
入口参数：无
返回  值：偏移量
描    述：
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
函数功能：计算偏移量
入口参数：无
返回  值：偏移量
描    述：
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
	Offset = 0;  //中间的传感器,直行。0000000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 1)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -2; //微小右偏 001 0 000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 1)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = 2;  //微小左偏 000 0 100
	}else if((ldr[0] == 0)&&(ldr[1] == 1)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -10;//微右偏   010 0 000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 1)&&(ldr[6] == 0)){
	Offset = 10; //微左偏   000 0 010
	}else if((ldr[0] == 1)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -20;  //右偏     100 0 000
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 1)){
	Offset = 20;  //左偏     000 0 001
	}else if((ldr[0] == 0)&&(ldr[1] == 0)&&(ldr[2] == 0)&&(ldr[3] == 0)&&(ldr[4] == 0)&&(ldr[5] == 0)&&(ldr[6] == 0)){
	Offset = -20;   //需左转弯 001 0 000
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
函数功能：控制电机函数
入口参数：无
返回  值：无
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
函数功能：赋值给PWM寄存器
入口参数：左右电机的速度
返回  值：无
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
函数功能：主要的控制程序
入口参数：无
返回  值：无
描    述：循迹小车的主要控制程序都在这个10ms中断一次的中断服务函数里。
**************************************************************************/
int Target_velocity=50;  //设定速度控制的目标速度为50个脉冲每10ms
int TIM3_IRQHandler(void)
{
 if(TIM_GetFlagStatus(TIM3,TIM_FLAG_Update)==SET)
 {
   TIM_ClearITPendingBit(TIM3,TIM_IT_Update);   //===清除定时器1中断标志位
	 //Read_Offset();                     //读取传感器的偏移值值
   //Led_Flash(100);                              //LED闪烁
	 //tracking_pid();              //计算PID
	 K210_PI();
	 motor_control();            //控制电机
 }
 return 0;
}

/**************************************************************************
函数功能：设置PWM占空比 
入口参数：无
返回  值：无
**************************************************************************/
void  TIM_PwmSetPulse (u8 TIM1_CH,u8 pulse)
{
	u16 compareValue ; 
	compareValue = pulse * 8000 / 100; 	  //根据占空比设置比较值

	switch(TIM1_CH)
	{
		case 1: TIM_SetCompare1(TIM1,compareValue); break;
		case 2: TIM_SetCompare2(TIM1,compareValue); break;	
		default: break;
	}
}


/**************************************************************************
函数功能：绝对值函数
入口参数：int
返回  值：unsigned int
**************************************************************************/
int myabs(int a) //取绝对值
{ 		   
	 int temp;
	 if(a<0)  temp=-a;  
	 else temp=a;
	 return temp;
}
/**************************************************************************
函数功能：增量PI控制器
入口参数：编码器测量值，目标速度
返回  值：电机PWM
根据增量式离散PID公式 
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
e(k)代表本次偏差 
e(k-1)代表上一次的偏差  以此类推 
pwm代表增量输出
在我们的速度控制闭环系统里面，只使用PI控制
pwm+=Kp[e（k）-e(k-1)]+Ki*e(k)
**************************************************************************/
int Incremental_PI (int Encoder,int Target)
{ 	
   float Kp=20,Ki=30;	
	 static int Bias,Pwm,Last_bias;
	 Bias=Encoder-Target;                //计算偏差
	 Pwm+=Kp*(Bias-Last_bias)+Ki*Bias;   //增量式PI控制器
	 Last_bias=Bias;	                   //保存上一次偏差 
	 return Pwm;                         //增量输出
}
