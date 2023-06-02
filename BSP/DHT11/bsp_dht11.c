#include "bsp_dht11.h"
//#include "delay.h"
#include "usart.h"

u8 temperature = 0;
u8 humidity = 0;

void DHT11_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	 
	DHT11_DQ_GPIO_APBxClkCmd(DHT11_DQ_GPIO_CLK, ENABLE);	  //使能DHT11_DQ端口时钟
	
	/* DHT11_DQ端口配置 */
	GPIO_InitStructure.GPIO_Pin = DHT11_DQ_GPIO_PIN;	        
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	          
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	          
	GPIO_Init(DHT11_DQ_GPIO_PORT, &GPIO_InitStructure);
}


u8 DHT11_Rst(void)
{
	u8 i = 50; 
	DHT11_IO_OUT();         //推挽输出
	DHT11_DQ_RESET();	      //DQ = 0
	delay_xms(20);           //至少拉低大于18ms
  DHT11_DQ_SET();         //DQ = 1
	delay_us(30);           //主机拉高20~40us
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




//u8 DHT11_ReceiveBit(void)         //时序有问题
//{
//	DHT11_IO_IN();
////	DHT11_DQ_SET();
//	delay_us(50+30);                //延时50ms数据间隔时间+高电平“0”“1”判断延时26~28us
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
	while(DHT11_DQ_READ()&&retry<50)    //原本延时80us的，现在50us也可以，说明由于器件差异，和延时误差，指令时间花消，所导致
	{                                   //采用最小单位循环判断，即可使时序准确，而估计值，由于上述原因，很难准确估计准确而导致时序不正确
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
//	DHT11_IO_OUT();         //推挽输出
//	DHT11_DQ_RESET();	      //DQ = 0
//	delay_xms(20);           //至少拉低大于18ms
//  DHT11_DQ_SET();         //DQ = 1
//	delay_us(30);           //主机拉高20~40us
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
