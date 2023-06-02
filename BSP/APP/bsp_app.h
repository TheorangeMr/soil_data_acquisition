#ifndef __APP_H__
#define __APP_H__

#include "stm32f1xx_hal.h"
#include "usart.h"
#include "modbus_rtu_master.h"


void Usart3_Handle(uint16_t* pusRegBuffer);
void Soil_date_handle(uint8_t count);

#endif


