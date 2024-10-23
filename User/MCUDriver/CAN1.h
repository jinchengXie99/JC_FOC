/***********************************************************************
* @file CAN1
* Description:
*
**********************************************************************
* File name:      CAN1.h
* Date:           2021-06-14
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __CAN1_H__
#define __CAN1_H__
#include "stdint.h"


void CAN_Init(void);
void CANSendData(uint8_t *data,uint8_t length);
uint8_t CANReceiveData(uint8_t *data, uint8_t *length);
void CAN_Test(void);


#endif //__CAN1_H__