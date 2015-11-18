#include "led.h"


	
	
void led_init(void )
{
	
	  GPIO_InitTypeDef GPIO_InitStructure;
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}