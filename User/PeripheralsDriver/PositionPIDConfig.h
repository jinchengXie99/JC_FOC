/***********************************************************************
* @file PositionPIDConfig
* Description:
*
**********************************************************************
* File name:      PositionPIDConfig.h
* Date:           2021-03-31
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __PositionPIDConfig_H__
#define __PositionPIDConfig_H__
#include "stdint.h"



void PositionPIDConfig_Init(void);
void SetPositionPIDConfigTarPosition(float tarPosition);
void PositionPIDConfig_Loop(void);
void PositionPIDConfig_Printf(void);

#endif //__PositionPIDConfig_H__







