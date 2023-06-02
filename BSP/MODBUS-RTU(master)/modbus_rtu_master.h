#ifndef __MODBUS_RTU_MASTER_H__
#define __MODBUS_RTU_MASTER_H__

#include "stm32f1xx_hal.h"
#include "usart.h"


/// MODBUS RTU 主机控制结构
///
///
typedef struct
{
	//
	// 收发数据缓存
	//
	uint8_t ucBuf[128];
	
	//
	// 接受数据状态
	//
	uint16_t rx_len;
	
	//
	// 如果使用了RTOS需要进行互斥,那么需要实现以下两个函数的绑定
	//
	void (*lock)(void);
	void (*unlock)(void);
	
	//
	// 微秒延时函数,用于等待超时
	//
	void (*delayms)(uint32_t nms);
	
	//
	// 定时器启动和停止函数
	//
	void (*timerStop)(void);
	void (*timerStart)(void);
	
	//
	// 发送数据函数,可以是串口、TCP等
	//
	uint32_t (*sendData)(const void* buf, uint32_t len);

}MBRTUMaterTypeDef;


#define RS485_RE(x)   do{ x ? \
                          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET) :    \
                          HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET);   \
                      }while(0)

//int MBRTUMasterReadCoils(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint8_t* pucCoilsBuffer);
//int MBRTUMasterReadDiscreteInputs(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint8_t* pucDiscBuffer);
int MBRTUMasterReadHoldingRegisters(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint16_t* pusRegBuffer);
//int MBRTUMasterReadInputRegisters(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, uint16_t usTimeout, uint16_t* pusRegBuffer);
//int MBRTUMasterWriteSingleCoil(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint8_t ucState, uint16_t usTimeout);
//int MBRTUMasterWriteSingleRegister(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usRegVal, uint16_t usTimeout);
//int MBRTUMasterWriteMultipleCoils(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, const uint8_t* pucStateBitsBuf, uint16_t usTimeout);
//int MBRTUMasterWriteMultipleRegisters(MBRTUMaterTypeDef* psModbus, uint8_t ucSlaveAddress, uint16_t usAddress, uint16_t usNum, const uint16_t* pusRegVal, uint16_t usTimeout);
//											
											
											
#endif


