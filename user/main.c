/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main program body
  ******************************************************************************
*/

#include "led.h"
#include "delay.h"
#include "i2c_soft.h"
#include "my_bmp180.h"

int32_t alt;
uint8_t ID;
uint8_t maxa[1];
int main(void)
{
	int n=0;
	 bmp180_power();
			led_init();
	delay_init(48);
	IIC_Init();
			BMP180_init();
			delay_ms(500);

  while (1)
  {
		n=200;
		while(n)
		{
				BMP180_Routing();
				delay_ms(50);
			n--;
		}
		
		BMP180_ResetAlt(0);
		while(1)
		{
			LED_ON;
		delay_ms(5);
		LED_OFF;
		BMP180_Routing();
	delay_ms(100);
BMP180_test();
		}
  }
}






#ifdef  USE_FULL_ASSERT


void assert_failed(uint8_t* file, uint32_t line)
{ 

  while (1)
  {
		
		
  }
}
#endif
