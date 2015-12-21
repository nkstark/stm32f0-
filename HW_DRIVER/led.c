#include "led.h"


	
	
	//timer 3 ch4 用来控制led
	#define TimerPeriod 1000;
	#define T_Pulse 100;
	
	
void led_init(void )
{
	
	  GPIO_InitTypeDef GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		TIM_OCInitTypeDef  TIM_OCInitStructure;
	
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB,ENABLE);

	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;  
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;   //默认是不亮的
	
	
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
//	LED_ON;
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1); //tim3 是af1
//	 RCC_TIMCLKPresConfig(RCC_TIMPrescActivated);
	
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);
	
	  TIM_TimeBaseStructure.TIM_Prescaler = 47999;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = TimerPeriod;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //分与不分没有影响
 // TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;    //这个只能用于tim1
	
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=T_Pulse;
	TIM_OCInitStructure.TIM_OCIdleState=TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_Low;
	
	TIM_OC4Init(TIM3,&TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM3,ENABLE);
	
	TIM_Cmd(TIM3,ENABLE);
	//TIM_CtrlPWMOutputs(TIM3,ENABLE);
	
}

void LED_PWM(uint16_t ms,unsigned char precent)
{
	TIM3->ARR=ms;
	TIM3->CCR4=ms*precent/100;
}