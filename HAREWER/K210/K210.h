#ifndef _K210_H
#define	 _K210_H

#include "sys.h" 
#include "usart.h"	
extern int rho_err;      //线中心x偏移量
extern int theta_err;    //角度
void K210_Date(u8 data);
#endif

