#ifndef __BSP_DHT11_H
#define __BSP_DHT11_H

#include "stm32f1xx_hal.h"

#define  DHT11_DQ_GPIO_CLK           (RCC_APB2Periph_GPIOE)
#define  DHT11_DQ_GPIO_APBxClkCmd    RCC_APB2PeriphClockCmd
    
#define  DHT11_DQ_GPIO_PORT          GPIOE   
#define  DHT11_DQ_GPIO_PIN           GPIO_Pin_4

/*IO方向设置*/       //设置PD6 	串口单总线传输  模式上拉输入 , 推挽输出
#define DHT11_IO_IN()  {GPIOE->CRL&=0XFFF0FFFF;GPIOE->CRL|=8<<16;}       //上拉输入
#define DHT11_IO_OUT() {GPIOE->CRL&=0XFFF0FFFF;GPIOE->CRL|=3<<16;}       //推挽输出，50mhz


///*IO操作*/
//#define	DHT11_DQ_OUT PAout(0) //数据端口	PA0
//#define	DHT11_DQ_IN  PAin(0)  //数据端口	PA0

#define DHT11_DQ_SET()    {DHT11_DQ_GPIO_PORT->BSRR |= DHT11_DQ_GPIO_PIN;}      //置1
#define DHT11_DQ_RESET()  {DHT11_DQ_GPIO_PORT->BRR  |= DHT11_DQ_GPIO_PIN;}      //清零
#define DHT11_DQ_READ()   ((DHT11_DQ_GPIO_PORT->IDR & DHT11_DQ_GPIO_PIN)>>4)   //读取gpio引脚状态

u8 DHT11_ReadByte(void);
void DHT11_WriteByte(u8 zdata);
u8 DHT11_ReceiveBit(void);
void DHT11_SendBit(u8 dat);
u8 DHT11_Rst(void);
void DHT11_GPIO_Config(void);
u8 PEC_Calculation(u8 pec[]);
void DHT11_ReadMultiTemp(void);

#endif    //__BSP_DHT11_H

