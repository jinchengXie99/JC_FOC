#ifndef MotorGPIO_h
#define MotorGPIO_h

#include "stdint.h"


void SetMotorEnable(uint8_t isEnable);
uint8_t GetMotorFaultLeave(void);

#endif /* MotorGPIO_h */
