#ifndef _MSB_H
#define _MSB_H
#include "stm32f0xx_gpio.h"
#include "delay.h"
//#include "stm32f0xx_exti.h"
//#include "misc.h"
#include "stm32f0xx.h"
#include "stm32f0xx_usart.h"
#include "stm32f0xx_it.h"
//#include "GUI_SENSOR.h"

//#define MB_SPECIAL		0
//#define MB_VOLTAGE		1
//#define MB_CURRENT		2
//#define MB_VARIO		3
//#define MB_SPEED		4
//#define MB_RPM			5
//#define MB_TEMP			6
//#define MB_DIR			7
//#define MB_ALT			8
//#define MB_TANK			9
//#define MB_LQI			10
//#define MB_CAP			11
//#define MB_FLUID		12
//#define MB_LDIST		13

#define MB_SPECIAL		0
#define MB_VOLTAGE		1
#define MB_CURRENT		2
#define MB_VARIO		3
#define MB_SPEED		4
#define MB_RPM			5
#define MB_TEMP			6
#define MB_DIR			7
#define MB_ALT			8
#define MB_TANK			9
#define MB_LQI			10
#define MB_CAP			11
#define MB_FLUID		12
#define MB_LDIST		13

//2015//8/25 msb 特殊命令(总共52条，测试前8条)

#define off 			0
#define	START			1
#define	Ignite		2
#define	acceler		3
#define	Stabilise	4
#define	LearnHI		5
#define	LearnLO		6
#define	RUN				7





#define MB_MAX_ADRESS 16
 
#define MB_NOALERT		0
#define MB_ALERT		1
#define MB_BITLEN 26

#define MSB_P GPIOA
#define MSB_N GPIO_Pin_2

#define MB_BUS_LO()		GPIO_ResetBits(MSB_P, MSB_N)
#define MB_BUS_HI()   GPIO_SetBits(MSB_P, MSB_N) 

//#define ReadValue = GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7);

//定义数据结构体，active =1 数据已经更新
 //volatile u8 MSB_DATA=0;
 
 typedef struct MB_DATA
{
	  uint8_t address;
  uint8_t response[3];
} MB_DATA_T;

typedef struct sensor_dec_str
{
//	uint8_t add;
	uint8_t unit;
	int16_t sensor;
} sensor_decoder;

 
 extern volatile MB_DATA_T mb_data[16];
extern volatile unsigned char MSB_Sta;
 extern volatile u8 MB_DATA_115200[30];
//extern volatile u8 crc;
extern	 	volatile u8 sensor_1[6];
 extern volatile sensor_decoder sensor_decoder_data[16];
extern volatile	uint16_t amount_order;
 extern volatile u8 amount_sensor;
 extern volatile u8 MB_DATA_Update_Status;

void mb_init(void);

//u8 mb_receive(void);
//void MSB_INT(u8 control);
//void MSB_GPIO_IN(void);
//void MSB_GPIO_OUT(void);
//void mb_send(uint8_t data);
//void mb_update(uint8_t adr,uint8_t unit,int16_t value,uint8_t alert);
//void mb_requestDetected(uint8_t adress);
//void mb_sonderdaten(uint16_t daten,u8 adress);
void HW_msb_init_Sensor(void);
void HW_msb_send(uint8_t data);
void HW_msb_init_eScreen(void);
void HW_msb_send_IT(uint8_t ADDR);
	void mb_update(uint8_t adr,uint8_t unit,int16_t value,uint8_t alert) ;
//u8 HW_msb_crc(void);
//u8 HW_msb_data_cal(void);
//void msb_data_decoder(void);
//void Lcd_data_update(void);
//void unit_display(u8 x,u8 y,u8 i,u16 data,u16 bc,u16 fc);
//void sensor_counter(void);
//void display_block(u8 x,u8 y,u8 i,u16 data,u16 bc,u16 fc,u8 mode);
//void Lcd_display_type1(void);

#endif
