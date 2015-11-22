#include <math.h>
#include "stm32f0xx.h"

uint16_t Hm[2]; //高度 预测
uint16_t Hp[2];	//高度 估计

uint16_t Qm[2];  //系统方差 预测
uint16_t Qp[2];		//系统方差 估计

uint16_t K;  //kalman 增益
uint16_t C;  //观测矩阵

uint16_t Err_sys;
uint16_t Err_sen;

void my_kf_init()
{
	
}
void my_kf(uint16_t  Messure)
{
	Hm[1]=Hp[0];  
	Qm[1]=Qp[1]+Err_sys;
	
	K=(C*Qm[1])/(C*C*Qm[1]+Err_sen);
	Hp[1]=Hm[1]+K*(Messure-C*Hm[1]);
	Qp[1]=(1-(K*C))*Qm[1];
	
	
}