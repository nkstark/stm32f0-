#ifndef __LED_H
#define __LED_H
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_tim.h"

 void led_init(void );
void LED_PWM(uint16_t ms,unsigned char precent);

#define LED_ON GPIO_SetBits(GPIOB,GPIO_Pin_1);
#define LED_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_1);


#endif

