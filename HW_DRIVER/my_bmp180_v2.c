#include "my_bmp180_v2.h"

volatile int16_t ac1,ac2,ac3,b1,b2,mb,mc,md;     // 标定的数据  
volatile uint16_t ac4,ac5,ac6;                   // 标定的数据
volatile int32_t b5;                    //温度



uint8_t _buff[BUFFER_SIZE];    // 数据缓冲区
int16_t _oss;                 // 过采样设置

volatile int32_t my_T;
volatile int32_t my_P;
volatile float my_P0=101325;
volatile  float my_A;

	volatile float  K=0.0f;



float _cm_Offset;
float _Pa_Offset;
int32_t _param_datum, _param_centimeters;
volatile unsigned char BPM180_ST;
int32_t last_Temperature,last_Pressure,last_Alt;
int32_t  BMP180_FIFO[2][11]; //先进先出过滤器数组 //最后一个是平均值
int32_t  BMP180_FIFOH[21];	 //先进先出过滤器数组

volatile int32_t BMP180_DATA[4];
////////////////////////////////////////////////////////////////////////////

void BMP180_writemem(uint8_t _addr, uint8_t _val)
	{
  IICwriteByte(BMP180_ADDR,_addr,_val);
	}
/////////////////////////////////////////////////////////////////////////////
void BMP180_readmem(uint8_t _addr, uint8_t _nbytes, uint8_t __buff[]) 
	{
  IICreadBytes(BMP180_ADDR,_addr,_nbytes,__buff);
	}
////////////////////////////////////////////////////////////////////////////
void MY_BMP180_Routing(int rw)
{


	int32_t ut,x1,x2,mctemp,mdtemp;
	
	  volatile int32_t up,x3,b3,b6,p;
  volatile int32_t b4,b7;
  volatile int32_t tmp; 
	
	
  if(rw)                                           //这一段多余
		{
			BMP180_writemem(CONTROL, READ_TEMPERATURE);
			delay_ms(10);                          // min. 4.5ms read Temp delay
			}
  BMP180_readmem(CONTROL_OUTPUT, 2, _buff); 
  ut = ((int32_t)_buff[0] << 8 | ((int32_t)_buff[1]));    // uncompensated temperature value
 
  // calculate temperature
  x1 = (((int32_t)ut - (int32_t)ac6) * (int32_t)ac5) >> 15;
  mctemp= mc;
  mdtemp= md;
  x2 = (mctemp <<11) / (x1 + mdtemp);
  b5 = x1 + x2;
	my_T=(b5+8)>>4;                                   //温度计算到此为止
			
			
	
  BMP180_writemem(CONTROL, READ_PRESSURE+(_oss << 6)); 
  delay_ms(15); 
  
     
  BMP180_readmem(CONTROL_OUTPUT, 3, _buff);  
  up = ((((int32_t)_buff[0] <<16) | ((int32_t)_buff[1] <<8) | ((int32_t)_buff[2])) >> (8-_oss)); // uncompensated pressure value
  
  // calculate true pressure
  b6 = b5 - 4000;             // b5 is updated by calcTrueTemperature().
//	b6=-3800;
  x1 = (b2* ((b6 * b6) >> 12)) >> 11;
  x2 = (ac2 * b6) >> 11;
  x3 = x1 + x2;
  tmp = ac1;
  tmp = (tmp * 4 + x3) << _oss;
  b3 = (tmp + 2) >> 2;
  x1 = (ac3 * b6) >> 13;
  x2 = (b1 * ((b6 * b6) >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (ac4 * (uint32_t) (x3 + 32768)) >> 15;
  b7 = ((uint32_t)up - b3) * (50000 >> _oss);
  if(b7 < 0x80000000)
		{
   p = ((uint32_t)b7 << 1) / b4;
		}
		else
		{
  p = (b7 / b4) << 1;
		}
 // p = b7 < 0x80000000 ? (b7 << 1) / b4 : (b7 / b4) << 1;   //gaidong
  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  my_P = p + ((x1 + x2 + 3791) >> 4);	   //气压单位是pa   气压计算到此为止   这里计算的是绝对气压

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MY_ALT_CAL(u8 calculate_Methode,float data)
{

	
	switch(calculate_Methode)
	{
		case calculate_Methode_0 :
		
			if(my_P0!=0)
			{
				K=data/my_P0;
				my_A=-7790.0f*log(K);
			}
			
		
		break;
	
		case calculate_Methode_1:
		{
		my_A=4433000 * (1 - pow((data / _Pa_Offset), 0.1903))- _cm_Offset; 
		}
			break;
		default : 
			break;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
void BMP180_getCalData(void) 
{
			BMP180_readmem(CAL_AC1, 2, _buff);
			ac1 = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1]));
			BMP180_readmem(CAL_AC2, 2, _buff);
			ac2 = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1]));
			BMP180_readmem(CAL_AC3, 2, _buff);
			ac3 = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1]));
			BMP180_readmem(CAL_AC4, 2, _buff);
			ac4 = ((uint16_t)_buff[0] <<8 | ((uint16_t)_buff[1]));
			BMP180_readmem(CAL_AC5, 2, _buff);
			ac5 = ((uint16_t)_buff[0] <<8 | ((uint16_t)_buff[1]));
			BMP180_readmem(CAL_AC6, 2, _buff);
			ac6 = ((uint16_t)_buff[0] <<8 | ((uint16_t)_buff[1])); 
			BMP180_readmem(CAL_B1, 2, _buff);
			b1 = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1])); 
			BMP180_readmem(CAL_B2, 2, _buff);
			b2 = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1])); 
			BMP180_readmem(CAL_MB, 2, _buff);
			mb = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1]));
			BMP180_readmem(CAL_MC, 2, _buff);
			mc = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1]));
			BMP180_readmem(CAL_MD, 2, _buff);
			md = ((int16_t)_buff[0] <<8 | ((int16_t)_buff[1])); 
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void BMP180_setMode(u8 _BMPMode){
  _oss = _BMPMode;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////
void BMP180_read(void)
{
	if(last_Alt > BMP180_DATA[0])  BMP180_DATA[0]=last_Alt;
	BMP180_DATA[1]=last_Alt;
	BMP180_DATA[2]=last_Temperature;
	BMP180_DATA[3]=last_Pressure;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BMP180_calcTrueTemperature(void){
  int32_t ut,x1,x2,mctemp,mdtemp;
  
  BMP180_writemem(CONTROL, READ_TEMPERATURE);
  delay_ms(10);                          // min. 4.5ms read Temp delay
  
  BMP180_readmem(CONTROL_OUTPUT, 2, _buff); 
  ut = ((int32_t)_buff[0] << 8 | ((int32_t)_buff[1]));    // uncompensated temperature value
 
  // calculate temperature
  x1 = (((int32_t)ut - (int32_t)ac6) * (int32_t)ac5) >> 15;
  mctemp= mc;
  mdtemp= md;
  x2 = (mctemp <<11) / (x1 + mdtemp);
  b5 = x1 + x2;
}
/////////////////////////////////////////////////////
//void BMP180_getAltitude(int32_t *_centimeters,u8 rw){
//  int32_t TruePressure;
//  BMP180_calcTruePressure(&TruePressure,rw); 
//  BMP180_newPressure(TruePressure);
//   TruePressure = last_Pressure;
//  *_centimeters =  4433000 * (1 - pow((TruePressure / (float)_param_datum), 0.1903)) + _cm_Offset;  
//  // converting from float to int32_t truncates toward zero, 100.999985 becomes 100 resulting in 1 cm error (max).
//}
//////////////////////////////////////////////////////////////////////////////////////////////
//void BMP180_setLocalAbsAlt(int32_t _centimeters){  
//  int32_t tmp_Pa;
// 
//  _param_centimeters = _centimeters;   
//  BMP180_getPressure(&tmp_Pa,1);    // calc pressure based on current altitude
//  _param_datum = tmp_Pa;
//}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
//void BMP180_setLocalPressure(int32_t _Pa){   
//  int32_t tmp_alt;
// 
//  _param_datum = _Pa;   
//  BMP180_getAltitude(&tmp_alt,1);    // calc altitude based on current pressure   
//  _param_centimeters = tmp_alt;
//}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

void BMP_init(u8 _BMPMode, int32_t _initVal, u8 _Unitmeters)
	{     
  BMP180_getCalData();               // initialize cal data
  BMP180_calcTrueTemperature();      // initialize b5
  BMP180_setMode(_BMPMode);
 // _Unitmeters>0 ? BMP180_setLocalAbsAlt(_initVal) : BMP180_setLocalPressure(_initVal); 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void BMP180_init(void) 
	{  
		u8 i=0;
		float tempp=0;
  _cm_Offset = 0;
  _Pa_Offset = 0;               // 1hPa = 100Pa = 1mbar	
  BMP_init(MODE_HIGHRES, 0, 1);
//		b5=200;
		for(i=0;i<50;i++)
		{
			tempp=tempp+filter();
		}
		tempp=tempp /50.0f;
		_Pa_Offset=my_P0 ;
		my_P0 =tempp;
		for(i=0;i<10;i++)
		{
		_cm_Offset=4433000 * (1 - pow((tempp / _Pa_Offset), 0.1903)) ; //计算绝对高度
			_Pa_Offset = tempp / pow((1 - _cm_Offset / 4433000), 5.255) ; //用绝对高度算海平面气压
			
		}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
volatile int32_t Pa[5];
volatile int32_t E;
volatile int32_t Var;
volatile int32_t Pa_quad[5];
volatile int32_t E_quad;

volatile float K_filter;
volatile float K0=100.0f; //这个值的设定值得探讨
#define system_err 119.0f

volatile float Ergibnis[3];
//收到数据类型的限制，计算Var的时候发生了溢出，因此计算气压/10的Var
float filter(void)
{
	u8 i=0;
	E=0;
	E_quad =0;
	Ergibnis[0]=Ergibnis[1];
	for(i=0;i<5;i++)
	{
				MY_BMP180_Routing(1);
	//	delay_ms(5);
		Pa[i]=my_P-100000;
			E=E+Pa[i];
		E_quad=Pa[i]*Pa[i]+E_quad;
	
	}
	E=E/(5.0f);
	Ergibnis[1]=E;
	Var=(E_quad/5.0f)-(E)*(E);
	K_filter = (K0+system_err)/(K0+(float)Var+system_err);
	K0=(1-K_filter)*(K0+system_err);
	
	Ergibnis[2]=Ergibnis[0]+(Ergibnis[1]-Ergibnis[0])*K_filter;
	Ergibnis[2]=Ergibnis[2]+100000;
	
	return Ergibnis[2];
}

