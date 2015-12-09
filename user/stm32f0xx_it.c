/**
  ******************************************************************************
  * @file    Project/STM32F0xx_StdPeriph_Templates/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.5.0
  * @date    05-December-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "msb.h"
#include "delay.h"
#define u8 uint8_t

volatile unsigned char  MSB_DATA=0;
volatile u8 HW_MSB_STAT=0;
volatile u8 HW_MSB_DATA=0;
volatile u8 HW_MSB_ERROR=0;
//volatile unsigned char MSB_Sta;
//volatile u8 msb_i=0;
//volatile	u8 startflag=0;
//volatile 	u8 endflag=0;


/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
	
	void USART1_IRQHandler(void)
	{
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
		{
			  HW_MSB_DATA = USART_ReceiveData(USART1);  
//			HW_MSB_STAT=1;
		}
	} 
	
	//串口一中断的作用在于：总线状态和总线地址的接收
	
	
//	void USART1_IRQHandler(void)
//{
//	// HW_MSB_DATA = USART_ReceiveData(USART1);  
//  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //判断是否为接受中断
//  {
//    /* Read one byte from the receive data register */
//		    HW_MSB_DATA = USART_ReceiveData(USART1);        //接收总线地址
//		
//	//	if((HW_MSB_DATA<=0x0f)&&(  MB_DATA_Update_Status==1)&&(HW_MSB_DATA==mb_data[HW_MSB_DATA].address)		) //msb的地址是否在范围之内？  MB的data 更新过了吗 总线地址是否匹配
//		{
//			if(HW_MSB_DATA==mb_data[HW_MSB_DATA].address)
//			{
//					USART_ITConfig(USART1, USART_IT_RXNE, DISABLE );
//	//				delay_us(1000);
//		 //   HW_MSB_DATA = USART_ReceiveData(USART1);
////					HW_MSB_STAT=1;
//					HW_msb_send_IT(HW_MSB_DATA);                  //回应
//					MB_DATA_Update_Status=0;                      //清除数据更新标志
//					USART_ITConfig(USART1, USART_IT_RXNE, ENABLE );
//			}
//		}
////		else 
//		{
//			HW_MSB_ERROR=HW_MSB_DATA;
////			HW_MSB_STAT=0;
//		}
////    if(RxCounter1 == NbrOfDataToRead1)
//    {
//      /* Disable the USARTy Receive interrupt */
//    }
//  }
//}

//	void USART2_IRQHandler(void)
//{
//  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //判断是否为接受中断
//  {
//    /* Read one byte from the receive data register */
//		    HW_MSB_DATA = USART_ReceiveData(USART2);        //接收总线地址
//		
//		if((HW_MSB_DATA<=0x0f)	) //msb的地址是否在范围之内？  MB的data 更新过了吗 总线地址是否匹配
//		{
////			if(HW_MSB_DATA==mb_data[HW_MSB_DATA].address)
//			{
//					USART_ITConfig(USART2, USART_IT_RXNE, DISABLE );
//					delay_us(1000);
//		 //   HW_MSB_DATA = USART_ReceiveData(USART1);
////					HW_MSB_STAT=1;
//					HW_msb_send_IT(HW_MSB_DATA);                  //回应
//					MB_DATA_Update_Status=0;                      //清除数据更新标志
//					USART_ITConfig(USART2, USART_IT_RXNE, ENABLE );
//			}
//		}
//		else 
//		{
//			HW_MSB_ERROR=HW_MSB_DATA;
////			HW_MSB_STAT=0;
//		}
////    if(RxCounter1 == NbrOfDataToRead1)
//    {
//      /* Disable the USARTy Receive interrupt */
//    }
//  }
//}

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
