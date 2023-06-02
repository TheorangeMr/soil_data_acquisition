#ifndef __MODBUS_RTU_MASTER_H__
#define __MODBUS_RTU_MASTER_H__

#include "stm32f1xx_hal.h"
#include "usart.h"


/// MODBUS RTU �������ƽṹ
///
///
typedef struct
{
	//
	// �շ����ݻ���
	//
	uint8_t ucBuf[128];
	
	//
	// ��������״̬
	//
	uint16_t rx_len;
	
	//
	// ���ʹ����RTOS��Ҫ���л���,��ô��Ҫʵ���������������İ�
	//
	void (*lock)(void);
	void (*unlock)(void);
	
	//
	// ΢����ʱ����,���ڵȴ���ʱ
	//
	void (*delayms)(uint32_t nms);
	
	//
	// ��ʱ��������ֹͣ����
	//
	void (*timerStop)(void);
	void (*timerStart)(void);
	
	//
	// �������ݺ���,�����Ǵ��ڡ�TCP��
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


