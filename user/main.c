/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/main.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main program body
  ******************************************************************************
*/
//程序状态
#include "delay.h"
#include "i2c_soft.h"
#include "my_bmp180_v2.h"
#include "msb.h"
#include "led.h"

#define MSB_Display_Pos 0x03


float temp1=0.0f;
float temp2=0.0f;

int16_t ALT=0;
int16_t TEMP=0;
int16_t	MAX_ALT=0;


int main(void)
{
		u8 work_stat=0x55;
	int n=0;
	u8 led_stat=0;
	
	
	delay_init(48);
	led_init();
	LED_PWM(50,10);//50ms 20hz
	IIC_Init();
	BMP180_init();
	delay_ms(500);
	HW_msb_init_Sensor();
	LED_PWM(500,10); //100ms 2hz

	
	
	while(1)
	{
						led_stat=0;
						if((HW_MSB_DATA==MSB_Display_Pos)&&(work_stat==0x55))      //如果位置正确
							{
								led_stat=0x55;
								delay_us(500);
								mb_update(MSB_Display_Pos,MB_ALT,MAX_ALT,0x01);  //如果最大高度改变会报警
								HW_msb_send_IT(0x03);
							work_stat=0x01;
	//							LED_PWM(500,100);
							}
//							else LED_PWM(500,10);
						if((HW_MSB_DATA==(MSB_Display_Pos+1))&&(work_stat==0x01)) //地址正确并且上一个位置已经更新
							{
								led_stat=0x55;
								delay_us(500);
								mb_update(MSB_Display_Pos+1,MB_ALT,ALT,0x00);
								HW_msb_send_IT(MSB_Display_Pos+1);
								work_stat=(work_stat<<2)+0x01; 
		//						LED_PWM(500,100);
							}
//							else LED_PWM(500,10);
						if((HW_MSB_DATA==(MSB_Display_Pos+2))&&(work_stat==0x05))
							{
								led_stat=0x55;
								delay_us(500);
								mb_update(MSB_Display_Pos+2,MB_TEMP,TEMP,0x00);       //温度显示
								HW_msb_send_IT(MSB_Display_Pos+2);
								work_stat=(work_stat<<2)+0x01;     //最后等于0x15
		//						LED_PWM(500,100);
							}
	//						else LED_PWM(500,10);
							
							if((HW_MSB_DATA==(MSB_Display_Pos+3))&&(work_stat==0x15)) //发送完成了！！！进行测量过程，测量过程能不能尽量快？
							{
		//						led_stat=0x55;
		//						USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);									//禁止MSB中断
								
								 USART_Cmd(USART1, DISABLE);
//								LED_PWM(500,100);
								temp1=filter();																						//开始新的测量
								MY_ALT_CAL(calculate_Methode_1,temp1);								//测量值计算高度
								ALT=my_A/100;
								if(ALT>MAX_ALT)
								{
									MAX_ALT=ALT;
								}
								TEMP=my_T;
								work_stat=(work_stat<<2)+0x01; 
								 USART_Cmd(USART1, ENABLE);
	//							USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	//							LED_PWM(500,100);
							}	
//							else if(led_stat!=0x55)
//								LED_PWM(500,10);
	}

//	while(1)
//	{
//		//		//						USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);									//禁止MSB中断
//								
//								 USART_Cmd(USART1, DISABLE);
////								LED_PWM(500,100);
//								temp1=filter();																						//开始新的测量
//								MY_ALT_CAL(calculate_Methode_1,temp1);								//测量值计算高度
//								ALT=my_A/100;
//								if(ALT>MAX_ALT)
//								{
//									MAX_ALT=ALT;
//								}
//								TEMP=my_T;
//								work_stat=(work_stat<<2)+0x01; 
//								 USART_Cmd(USART1, ENABLE);
//	//							USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//	}
}			


//fack you


	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
