#include "K210.h"

int rho_err;      //����x����
int theta_err;    //�Ƕ�

/**
* @brief  OPENMV_date_anl
* @param  ���յ�һ���ֽ�
* @retval None
*/
void K210_Date(u8 data)
{
	static u8 RxBuffer[10];
	static u8 state = 0;
/*ͨ�Ÿ�ʽ 0xAA 0x55 data1 data2 checkout 0x54*/	
/*����checkout=(data1+data2)�Ͱ�λ  ���� data1=0xe1,data2=0xf3,data1+data2=0x1d4,��checkout=0xd4*/
	if(state==0&&data==0xAA)
		state=1;
	else if(state==1&&data==0x55)
		state=2;
	else if(state==2)
	{
		RxBuffer[0]=data;//x
			state=3;
	}
	else if(state==3)
	{	
		RxBuffer[1]=data;//y
		state = 4;
	}
	else if(state==4)
	{	
		RxBuffer[2]=data;//checkout
		state = 5;
	}

	else if(state==5&&data==0x54)
	{	
		if(RxBuffer[2]==(u8)(RxBuffer[0]+RxBuffer[1]))//У��ɹ�
		{
		rho_err=RxBuffer[0] - 90;
		theta_err=RxBuffer[1];
		}
	
		state = 0;
	}
	else
		state = 0;
}



