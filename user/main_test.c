#include "delay.h"
#include "i2c_soft.h"
#include "my_bmp180_v2.h"
#include "msb.h"

int a,b,c;
u8 test[1];
float EE=0.0f;
float hhhh=0;
int main(void)
{
	int n=0;
	delay_init(48);
	IIC_Init();
	BMP180_init();
	delay_ms(500);
	HW_msb_init_Sensor();
//	MY_BMP180_init() ;
  while (1)
	{
	//	BMP180_readmem(CHIPID,1,test);
	//	MY_BMP180_Routing(1);
//		delay_ms(100);
//		MY_ALT_CAL(1);
//		EE=filter();
//	MY_ALT_CAL(1,EE);
		if(HW_MSB_DATA==0x04)
		{
		
		EE=filter();
	MY_ALT_CAL(calculate_Methode_1,EE);
		
		}
		if(HW_MSB_DATA==0x03||HW_MSB_DATA==0x04||HW_MSB_DATA==0x05)   //这三种情况的话更新
		{
			delay_us(500);
			mb_update(0x03,MB_ALT,my_A/100,0x00);
			HW_msb_send_IT(0x03);
			HW_MSB_STAT=0;
		}
	}



}