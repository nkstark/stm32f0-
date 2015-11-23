//--------------------------------------------ģ��msb����------------------------------------------------------//
/* �������ݸ�ʽ�����ߴ���
		�����ʣ�38400
		���ݸ�ʽ��  4bit ADD+4bit ��λ| 7bit��λ����+1bit Alarm| 8bit ��λ����
		�������ݸ�ʽ��4bit ADD+0| byte 2 û�ж��壨����ȫ0) | ��Ӧ���루0-51��
*/

#include "msb.h"
#define USART_msb USART1
#define USART_msb_GPIOX GPIOA
#define USART_msb_PinSource GPIO_PinSource9
#define USART_msb_Pin GPIO_Pin_9
#define MSB_ADDR 0x03


 volatile MB_DATA_T mb_data[16];
 
 volatile u8 MB_DATA_Update_Status=0;
 
 volatile sensor_decoder sensor_decoder_data[16];
 volatile u8 MB_DATA_115200[30]={0};
 volatile	uint16_t amount_order=0;
 volatile u8 amount_sensor=0;
//	 {0x02,0,0x30,0x34,0x34,0,0x40,0x06,0x31,0x78,0x1b,0x22,0x41,0x8c,0xc3,0,0,0,0xab,0x03};
	 

	 	volatile u8 sensor_1[6];


//MB_DATA_T mb_data[16];



/**************************ʵ�ֺ���********************************************
*����ԭ��:		void HW_msb_init_Sensor(void)
*��������:		msb ��������ʼ��
*����ӿڣ�		usart1 ����ģʽ PA9
*******************************************************************************/

void HW_msb_init_Sensor(void)
{
	
	//msb ��������ʼ������
	//�ӿڣ�38400��8��1��0��0 ���ߴ���ģʽ
	//����ӿڣ�PA9
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	  NVIC_InitTypeDef NVIC_InitStructure;
	
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

	
	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_3;
		GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_1);  
 

  
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;  //���ȼ���һ��

  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

   //   RCC_USARTCLKConfig( RCC_USART1CLK_PCLK );
        USART_DeInit( USART1 );

  USART_InitStructure.USART_BaudRate = 38400;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  USART_Init(USART1, &USART_InitStructure);


  USART_HalfDuplexCmd(USART1, ENABLE);
  USART_Cmd(USART1, ENABLE);
	  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);  


}

/**************************ʵ�ֺ���********************************************
*����ԭ��:		void HW_msb_send(uint8_t data)
*��������:		Ӳ��msb���߷���
*����ӿڣ�		keine
*******************************************************************************/
void HW_msb_send(uint8_t data)
{
	//	  USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
	   USART_SendData(USART1,data);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);       
}	
	
	void mb_update(uint8_t adr,uint8_t unit,int16_t value,uint8_t alert)  //ע�������value���ֻ����15bit
		{
  uint8_t b1,b2,b3;
  b1=adr;
  b1<<=4;
  b1+=unit;
 // if (value!=MB_NOVALUE) //???
		{
    value<<=1;
    if (alert==MB_ALERT) value++;
  }
  b2=value;
  b3=(value>>8);
  mb_data[adr].response[0]=b1;
  mb_data[adr].response[1]=b2;
  mb_data[adr].response[2]=b3;
  mb_data[adr].address =adr;
	MB_DATA_Update_Status=1;
//	MSB_INT(1);
}
		
void HW_msb_send_IT(uint8_t ADDR)
{
	u8 i=0;
	
	for(i=0;i<3;i++)
	{
		HW_msb_send(mb_data[ADDR].response[i]);
	}
}






