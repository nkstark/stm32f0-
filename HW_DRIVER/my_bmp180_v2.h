#ifndef _MY_BMP180_V2
#define _MY_BMP180_V2
#include "stm32f0xx.h"
#include "i2c_soft.h"
#include "delay.h"
#include <math.h>

#define BMP180_ADDR                 0xEE     // default I2C address
#define BUFFER_SIZE                 3

#define AUTO_UPDATE_TEMPERATURE     1    //default is true
        // when true, temperature is measured everytime pressure is measured (Auto).
        // when false, user chooses when to measure temperature (just call calcTrueTemperature()).
        // used for dynamic measurement to increase sample rate (see BMP180 modes below).
       
/* ---- Registers ---- */
#define CAL_AC1           0xAA  // R   Calibration data (16 bits)
#define CAL_AC2           0xAC  // R   Calibration data (16 bits)
#define CAL_AC3           0xAE  // R   Calibration data (16 bits)    
#define CAL_AC4           0xB0  // R   Calibration data (16 bits)
#define CAL_AC5           0xB2  // R   Calibration data (16 bits)
#define CAL_AC6           0xB4  // R   Calibration data (16 bits)
#define CAL_B1            0xB6  // R   Calibration data (16 bits)
#define CAL_B2            0xB8  // R   Calibration data (16 bits)
#define CAL_MB            0xBA  // R   Calibration data (16 bits)
#define CAL_MC            0xBC  // R   Calibration data (16 bits)
#define CAL_MD            0xBE  // R   Calibration data (16 bits)
#define CONTROL           0xF4  // W   Control register 
#define CONTROL_OUTPUT    0xF6  // R   Output registers 0xF6=MSB, 0xF7=LSB, 0xF8=XLSB

// unused registers
#define SOFTRESET         0xE0
#define VERSION           0xD1  // ML_VERSION  pos=0 len=4 msk=0F  AL_VERSION pos=4 len=4 msk=f0
#define CHIPID            0xD0  // pos=0 mask=FF len=8
#define  BMP180_CHIP_ID		0x55

/************************************/
/*    REGISTERS PARAMETERS          */
/************************************/
// BMP180 Modes
#define MODE_ULTRA_LOW_POWER    0 //oversampling=0, internalsamples=1, maxconvtimepressure=4.5ms, avgcurrent=3uA, RMSnoise_hPA=0.06, RMSnoise_m=0.5
#define MODE_STANDARD           1 //oversampling=1, internalsamples=2, maxconvtimepressure=7.5ms, avgcurrent=5uA, RMSnoise_hPA=0.05, RMSnoise_m=0.4
#define MODE_HIGHRES            2 //oversampling=2, internalsamples=4, maxconvtimepressure=13.5ms, avgcurrent=7uA, RMSnoise_hPA=0.04, RMSnoise_m=0.3
#define MODE_ULTRA_HIGHRES      3 //oversampling=3, internalsamples=8, maxconvtimepressure=25.5ms, avgcurrent=12uA, RMSnoise_hPA=0.03, RMSnoise_m=0.25
                  
// Control register
#define READ_TEMPERATURE        0x2E 
#define READ_PRESSURE           0x34 

extern volatile int32_t my_T;
extern volatile int32_t my_P;
extern volatile  float my_A;
extern 	volatile float  K;

extern volatile int32_t Pa[5];
extern volatile int32_t E;
extern volatile int32_t Var;
extern volatile int32_t Pa_quad[5];
extern volatile int32_t E_quad;

#define calculate_Methode_0 0x00
#define calculate_Methode_1	0x01

extern volatile float K0;
extern volatile int32_t b5;

extern float _cm_Offset;  //存入目前的绝对海平面高度
extern float _Pa_Offset;	//海平面气压

void BMP180_init(void) ;
void MY_BMP180_Routing(int rw);
void MY_ALT_CAL(u8 calculate_Methode,float data);
float filter(void);
#endif