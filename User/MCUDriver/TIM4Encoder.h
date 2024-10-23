
/***********************************************************************
* @file TIM4Encoder
* Description:
*
**********************************************************************
* File name:      TIM4Encoder.h
* Date:           2021-03-10
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __TIM4Encoder_H__
#define __TIM4Encoder_H__
#include "stdint.h"

#include "stdio.h"
#include "stdint.h"





void TimerEncoderInit(void);
void TimerEncoderReset(void);
int32_t GetTimer4EncoderCnt(void);
void SetTimer4EncoderCnt(int32_t cnt);
float GetTimer4EncoderAngle(void);

#endif //__TIM4Encoder_H__





