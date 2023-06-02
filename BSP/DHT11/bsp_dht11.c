#include "bsp_dht11.h"
//#include "delay.h"
#include "usart.h"

u8 temperature = 0;
u8 humidity = 0;

void DHT11_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
	DHT11_DQ_GPIO_APBxClkCmd(DHT11_DQ_GPIO_CLK, ENABLE);	  //ʹ��DHT11_DQ�˿�ʱ��
	
	/* DHT11_DQ�˿����� */
	GPIO_InitStructure.GPIO_Pin = DHT11_DQ_GPIO_PIN;	        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	          
	GPIO_Init(DHT11_DQ_GPIO_PORT, &GPIO_InitStructure);
}


u8 DHT11_Rst(void)
{
	u8 i = 50; 
	DHT11_IO_OUT();         //�������
	DHT11_DQ_RESET();	      //DQ = 0
	delay_xms(20);           //�������ʹ���18ms
  DHT11_DQ_SET();         //DQ = 1
	delay_us(30);           //��������20~40us
	DHT11_IO_IN();
	while(i--)
	{
		if(!DHT11_DQ_READ())
		{
			delay_us(80);
			if(DHT11_DQ_READ())
			{			
//				delay_us(40);
				return 0;
			}
		}
	}
	return 1;
}




//u8 DHT11_ReceiveBit(void)         //ʱ��������
//{
//	DHT11_IO_IN();
////	DHT11_DQ_SET();
//	delay_us(50+30);                //��ʱ50ms���ݼ��ʱ��+�ߵ�ƽ��0����1���ж���ʱ26~28us
//	if(DHT11_DQ_READ())
//	{
//		return 1;
////		printf("1");		
//	}
//	else
//	{
//		return 0;
////		printf("0");
//	}
//}

u8 DHT11_ReceiveBit(void)
{
	u8 retry = 0;
	while(DHT11_DQ_READ()&&retry<50)    //ԭ����ʱ80us�ģ�����50usҲ���ԣ�˵�������������죬����ʱ��ָ��ʱ�仨����������
	{                                   //������С��λѭ���жϣ�����ʹʱ��׼ȷ��������ֵ����������ԭ�򣬺���׼ȷ����׼ȷ������ʱ����ȷ
		retry++;
		delay_us(1);
//		printf("0");
	}
	retry = 0;
	while(!DHT11_DQ_READ()&&retry<80)
	{
		retry++;
		delay_us(1);		
//		printf("1");
	}
	delay_us(40);
	if(DHT11_DQ_READ())
		return 1;
	else
		return 0;
}

u8 DHT11_ReadByte(void)
{
	u8 i = 0;
	u8 bdat = 0;

	for(i = 0; i < 8;i++)
	{
		bdat <<= 1;
		bdat |= DHT11_ReceiveBit();
	}
	return bdat;
}

u8 PEC_Calculation(u8* pec)
{
	u8 i,sum = 0;
	for(i = 0; i < 4;i++)
	{
		sum += pec[i];
	}
	return sum;
}


void DHT11_ReadMultiTemp(void)
{
	u8 i,j = 0;
	u8 TempBuffer[5] = {0};
//	DHT11_Check();
	j = DHT11_Rst();
	if(j == 1)
	{
		printf("error\r\n");
	}
	else
	{
		for(i = 0;i < 5;i++)
		{
			TempBuffer[i] = DHT11_ReadByte();
//			printf("TempBuffer = %d\r\n",TempBuffer[i]);
		}
		if(PEC_Calculation(TempBuffer) == TempBuffer[4])
		{
			humidity = TempBuffer[0];
			temperature = TempBuffer[2];
		}
		else
		{
			printf("error\r\n");
		}
	}
}


//void DHT11_WriteByte(u8 zdata)
//{
//	u8 i;
//	u8 bit = 0;
//	for(i = 0;i < 8;i++ )
//	{
//		if((zdata&0x80)>>8)
//		{
//			 bit = 1;
//		}
//		else
//		{
//			 bit = 0;
//		}
//		DHT11_SendBit(bit);
//		zdata <<= 1;
//	}
//}

//void DHT11_SendBit(u8 dat)
//{
//	if(dat)
//	{
//		DHT11_IO_OUT();
//		DHT11_DQ_RESET();
//		delay_us(50);
//		DHT11_DQ_SET();
//		delay_us(70);
//		DHT11_DQ_RESET();
//	}
//	else
//	{
//		DHT11_IO_OUT();
//		DHT11_DQ_RESET();
//		delay_us(50);
//		DHT11_DQ_SET();
//		delay_us(27);
//		DHT11_DQ_RESET();	
//	}
//}


//void DHT11_Rst(void)
//{
//	DHT11_IO_OUT();         //�������
//	DHT11_DQ_RESET();	      //DQ = 0
//	delay_xms(20);           //�������ʹ���18ms
//  DHT11_DQ_SET();         //DQ = 1
//	delay_us(30);           //��������20~40us
//}

//u8 DHT11_Check(void)
//{
//	u8 retry = 0;
//	DHT11_IO_IN();	
//	while(DHT11_DQ_READ()&&retry<100)
//	{
//		retry++;
//		delay_us(1);
//	}
//	if(retry >= 100)
//	{return 1;}
//	else
//	{retry = 0;}
//	while(!DHT11_DQ_READ()&&retry<100)
//	{
//		retry++;
//		delay_us(1);
//	}
//	if(retry>=100)return 1;
//	else 
//		return 0;
//}
