/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main program body
  ******************************************************************************
*/

#include "delay.h"
#include "i2c_soft.h"
#include "my_bmp180.h"
#include "msb.h"


int main(void)
{
	int n=0;
	delay_init(48);
	IIC_Init();
	BMP180_init();
	delay_ms(500);
	HW_msb_init_Sensor();

  while (1)
  {
		n=200;
//		while(n)
//		{
//				BMP180_Routing();
//				delay_ms(50);
//			n--;
//		}
//		HW_msb_send
		BMP180_ResetAlt(0);
		while(1)
		{
	//		HW_msb_send(0x11);
		//	mb_update(0x03,MB_TEMP,BMP180_DATA[2],0x00);
	//		LED_ON;
		delay_ms(5);
	//	LED_OFF;
	
	//delay_ms(100);
				BMP180_read();
				mb_update(0x03,MB_TEMP,BMP180_DATA[2],0x00);
			//		if(HW_MSB_STAT==1)
		{
			if(HW_MSB_DATA==0x03)
			{
					BMP180_Routing();
				delay_us(299);
				HW_msb_send_IT(0x03);
			}
		}
		}
  }
}


