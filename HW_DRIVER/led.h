#ifndef __LED_H
#define __LED_H
#include "stm32f0xx_gpio.h"

 void led_init(void );

#define LED_ON GPIO_SetBits(GPIOA,GPIO_Pin_9);
#define LED_OFF GPIO_ResetBits(GPIOA,GPIO_Pin_9);


#endif

