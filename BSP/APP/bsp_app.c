#include "bsp_app.h"

extern uint8_t rx_buffer[30];
extern uint8_t rx_flag;
uint16_t usBuf[10];
int ret;
uint8_t time1_flag = 1;

uint16_t wendu = 0;
uint16_t phz = 0;
uint16_t shuifen = 0;
uint16_t conductivity  = 0;

static void delayms(uint32_t nms)
{
    HAL_Delay(nms);
}

static uint32_t sendData(const void* buf, uint32_t len)
{
	RS485_RE(1);
    if(HAL_UART_Transmit(&huart2, (uint8_t *)buf, len, 0xffff) != HAL_OK)
    {
        len = 0;
    }
	RS485_RE(0);
    return len;
}

	MBRTUMaterTypeDef MBRTUHandle =
{
    .delayms                      = delayms,
    .sendData                     = sendData,
};

void Soil_date_handle(uint8_t count)
{
	if(time1_flag == 1)
	{
	  ret = MBRTUMasterReadHoldingRegisters(&MBRTUHandle, 1, 0, count, 500, usBuf);
    printf(" read hold regs %s. \r\n", ret < 0 ? "failed" : "ok");
		if(ret >= 0)
		{
			time1_flag = 0;
			shuifen = usBuf[0];
			wendu = usBuf[1];
			conductivity = usBuf[2];
			phz = usBuf[3];
			printf("ˮ�� = %.1f%% ,�¶� = %f��,�絼�� = %d us/cm,PHֵ = %.1f \r\n",shuifen*1.0/10,wendu*1.0/10,conductivity,phz*1.0/10);		
		}
		Usart3_Handle(usBuf);
		if(shuifen*1.0/10 <= 20)
		{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_SET);
		}
		else
		{
				HAL_GPIO_WritePin(GPIOA,GPIO_PIN_8,GPIO_PIN_RESET);
		}
	}
	else
	{
		
	}
}



void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint16_t tim1_count = 0;
	if(htim->Instance == TIM1)
	{
		printf("��ʱ��1�����ж�\r\n");
		tim1_count++;
		if(tim1_count >= 3)                    //��Сʱ
		{
			time1_flag = 1;
		}
	}
}


void Usart3_Handle(uint16_t* pusRegBuffer)
{
	uint8_t us3Buf[20];
	uint8_t j = 0,i = 0;
	for(i = 0;i+2;i<4)
	{
		j = i;
		us3Buf[j] = ((usBuf[i] & 0XFF00) >> 8);         //��λ
		us3Buf[j++] = (usBuf[i] & 0XFF);
	}
	HAL_UART_Transmit(&huart3,&us3Buf[i], 8, 0xffff);
}

