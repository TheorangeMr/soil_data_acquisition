#ifndef __BSP_DHT11_H
#define __BSP_DHT11_H

#include "stm32f1xx_hal.h"

#define  DHT11_DQ_GPIO_CLK           (RCC_APB2Periph_GPIOE)
#define  DHT11_DQ_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DHT11_DQ_GPIO_PORT          GPIOE   
#define  DHT11_DQ_GPIO_PIN           GPIO_Pin_4

/*IO��������*/       //����PD6 	���ڵ����ߴ���  ģʽ�������� , �������
#define DHT11_IO_IN()  {GPIOE->CRL&=0XFFF0FFFF;GPIOE->CRL|=8<<16;}       //��������
#define DHT11_IO_OUT() {GPIOE->CRL&=0XFFF0FFFF;GPIOE->CRL|=3<<16;}       //���������50mhz


///*IO����*/
//#define	DHT11_DQ_OUT PAout(0) //���ݶ˿�	PA0
//#define	DHT11_DQ_IN  PAin(0)  //���ݶ˿�	PA0

#define DHT11_DQ_SET()    {DHT11_DQ_GPIO_PORT->BSRR |= DHT11_DQ_GPIO_PIN;}      //��1
#define DHT11_DQ_RESET()  {DHT11_DQ_GPIO_PORT->BRR  |= DHT11_DQ_GPIO_PIN;}      //����
#define DHT11_DQ_READ()   ((DHT11_DQ_GPIO_PORT->IDR & DHT11_DQ_GPIO_PIN)>>4)   //��ȡgpio����״̬

u8 DHT11_ReadByte(void);
void DHT11_WriteByte(u8 zdata);
u8 DHT11_ReceiveBit(void);
void DHT11_SendBit(u8 dat);
u8 DHT11_Rst(void);
void DHT11_GPIO_Config(void);
u8 PEC_Calculation(u8 pec[]);
void DHT11_ReadMultiTemp(void);

#endif    //__BSP_DHT11_H

