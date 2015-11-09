#include "bmp280_SPI.h"


//   ===========================================================================
//                         ##### How to use this driver #####
//    ===========================================================================
//      [..]
//      (#) Enable the GPIO AHB clock using RCC_AHBPeriphClockCmd()
//      (#) Configure the GPIO pin(s) using GPIO_Init()
//          Four possible configuration are available for each pin:
//         (++) Input: Floating, Pull-up, Pull-down.
//         (++) Output: Push-Pull (Pull-up, Pull-down or no Pull)
//                      Open Drain (Pull-up, Pull-down or no Pull).
//              In output mode, the speed is configurable: Low, Medium, Fast or High.
//         (++) Alternate Function: Push-Pull (Pull-up, Pull-down or no Pull)
//                                  Open Drain (Pull-up, Pull-down or no Pull).
//         (++) Analog: required mode when a pin is to be used as ADC channel,
//              DAC output or comparator input.
//      (#) Peripherals alternate function:
//         (++) For ADC, DAC and comparators, configure the desired pin in analog 
//              mode using GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AN
//         (++) For other peripherals (TIM, USART...):
//              (+++) Connect the pin to the desired peripherals' Alternate 
//                    Function (AF) using GPIO_PinAFConfig() function. For PortC, 
//                    PortD and PortF, no configuration is needed.
//              (+++) Configure the desired pin in alternate function mode using
//                    GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF
//              (+++) Select the type, pull-up/pull-down and output speed via 
//                    GPIO_PuPd, GPIO_OType and GPIO_Speed members
//              (+++) Call GPIO_Init() function
//      (#) To get the level of a pin configured in input mode use GPIO_ReadInputDataBit()
//      (#) To set/reset the level of a pin configured in output mode use
//          GPIO_SetBits()/GPIO_ResetBits()
//      (#) During and just after reset, the alternate functions are not active and 
//          the GPIO pins are configured in input floating mode (except JTAG pins).
//      (#) The LSE oscillator pins OSC32_IN and OSC32_OUT can be used as 
//          general-purpose (PC14 and PC15, respectively) when the LSE oscillator 
//          is off. The LSE has priority over the GPIO function.
//      (#) The HSE oscillator pins OSC_IN/OSC_OUT can be used as general-purpose 
//          PD0 and PD1, respectively, when the HSE oscillator is off. The HSE has 
//          priority over the GPIO function.

void bmp_280_SPI_Init(void)
{
		SPI_InitTypeDef SPI_InitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	//   ===========================================================================
//                         ##### GPIO_INIT #####
//    ===========================================================================	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_Level_3;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;  //这个地方要确认下
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource4,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_0);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_0);
	
	
	
	
// ===============================================================================
//                       ##### How to use this driver #####
// ===============================================================================
//    [..]
//        (#) Enable peripheral clock using RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE)
//            function for SPI1 or using RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE)
//            function for SPI2.
//  
//        (#) Enable SCK, MOSI, MISO and NSS GPIO clocks using 
//            RCC_AHBPeriphClockCmd() function. 
//  
//        (#) Peripherals alternate function: 
//            (++) Connect the pin to the desired peripherals' Alternate 
//                 Function (AF) using GPIO_PinAFConfig() function.
//            (++) Configure the desired pin in alternate function by:
//                 GPIO_InitStruct->GPIO_Mode = GPIO_Mode_AF.
//            (++) Select the type, pull-up/pull-down and output speed via 
//                 GPIO_PuPd, GPIO_OType and GPIO_Speed members.
//            (++) Call GPIO_Init() function.
//  
//        (#) Program the Polarity, Phase, First Data, Baud Rate Prescaler, Slave 
//            Management, Peripheral Mode and CRC Polynomial values using the SPI_Init()
//            function.In I2S mode, program the Mode, Standard, Data Format, MCLK 
//            Output, Audio frequency and Polarity using I2S_Init() function.
//  
//        (#) Configure the FIFO threshold using SPI_RxFIFOThresholdConfig() to select 
//            at which threshold the RXNE event is generated.
//            
//        (#) Enable the NVIC and the corresponding interrupt using the function 
//            SPI_ITConfig() if you need to use interrupt mode. 
//  
//        (#) When using the DMA mode 
//            (++) Configure the DMA using DMA_Init() function.
//            (++) Active the needed channel Request using SPI_I2S_DMACmd() function.
//   
//        (#) Enable the SPI using the SPI_Cmd() function or enable the I2S using
//            I2S_Cmd().
//   
//        (#) Enable the DMA using the DMA_Cmd() function when using DMA mode. 
//  
//        (#) Optionally, you can enable/configure the following parameters without
//            re-initialization (i.e there is no need to call again SPI_Init() function):
//            (++) When bidirectional mode (SPI_Direction_1Line_Rx or SPI_Direction_1Line_Tx)
//                 is programmed as Data direction parameter using the SPI_Init() 
//                 function it can be possible to switch between SPI_Direction_Tx 
//                 or SPI_Direction_Rx using the SPI_BiDirectionalLineConfig() function.
//            (++) When SPI_NSS_Soft is selected as Slave Select Management parameter 
//                 using the SPI_Init() function it can be possible to manage the 
//                 NSS internal signal using the SPI_NSSInternalSoftwareConfig() function.
//            (++) Reconfigure the data size using the SPI_DataSizeConfig() function.
//            (++) Enable or disable the SS output using the SPI_SSOutputCmd() function.  
//  
//        (#) To use the CRC Hardware calculation feature refer to the Peripheral 
//            CRC hardware Calculation subsection.	
	
	
//   ===========================================================================
//                         ##### SPI1_Init #####
//    ===========================================================================	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
		
		SPI_Cmd(SPI1,DISABLE);
		
		SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;   //单线发射模式
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                              
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;                          
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;       //说明书上说00 或许11都可以，取决于片选                             
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;  
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;       //是否启用硬件nss？                     
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;   
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;                                     
    SPI_InitStructure.SPI_CRCPolynomial = 7;                                                   
    SPI_Init(SPI1, &SPI_InitStructure);  
  
		SPI_CalculateCRC(SPI1, DISABLE);
//				GPIO_SetBits(GPIOA ,GPIO_Pin_4);
    SPI_Cmd(SPI1,ENABLE);    
	
}