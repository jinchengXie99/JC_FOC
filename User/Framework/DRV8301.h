/***********************************************************************
* @file DRV8301
* Description:
*
**********************************************************************
* File name:      DRV8301.h
* Date:           2021-03-22
* Version:        V1.0
* Author          liuxiang
* @history:
* V1.0 创建文件
***********************************************************************/
#ifndef __DRV8301_H__
#define __DRV8301_H__
#include "stdint.h"

//////////////////////////////////////////////////
#define CURRENT1_7A 0x0000
#define CURRENT0_7A 0x0001
#define CURRENT0_25A 0x0002

#define GATE_RST_NORMAL 0x0000
#define GATE_RST_LATCH 0x0004

#define PHASE6PWM 0x0000
#define PHASE3PWM 0x0008

#define CURRENTLIMIT 0x0000
#define OCLATCHSTDOWN 0x0010
#define REPORTONLY 0x0020
#define OCDISABLED 0x0030

#define OCOTBOTH 0x0000
#define OTONLY 0x0001
#define OCONLY 0x0002
#define OCONLYRSVD 0x0003

#define GAIN10 0x0000
#define GAIN20 0x0004
#define GAIN40 0x0008
#define GAIN80 0x000C

#define CONNECTLOADPH1 0x0000
#define SHORTINPUTPH1 0x0010

#define CONNECTLOADPH2 0x0000
#define SHORTINPUTPH2 0x0020

#define CYCLEBYCYCLE 0x0000
#define OFFTIMECTRL 0x0040

#define DRV8301WRITE (0x00 << 15)
#define DRV8301READ (0x01 << 15)

#define REGSTATUS1 0x00
#define REGSTATUS2 0x01

#define REGCTRL1 0x02
#define REGCTRL2 0x03

typedef struct DRV8301CFG{
    uint16_t GATE_CURRENT;
    uint16_t GATE_RESET;
    uint16_t PWM_MODE;
    uint16_t OCP_MODE;
    uint16_t OC_ADJ_SET;
    uint16_t OCTW_MODE;
    uint16_t GAINVALUE;
    uint16_t DC_CAL_CH1;
    uint16_t DC_CAL_CH2;
    uint16_t OC_TOFF;
}DRV8301Cfg;

struct SDRV8301_Struct
{
    uint8_t rw;
    uint8_t addr;
    uint16_t data;
    void (*SetCSIsEnable)(uint8_t isEnable);
    uint16_t (*ReadData)(void);
    void (*WriteData)(uint16_t data);
	uint16_t (*WriteReadData)(uint16_t data);
    /* data */
};

typedef struct SDRV8301_Struct DRV8301_Struct;
typedef DRV8301_Struct *PDRV8301_Struct;

void enablegate(void);
void DRV8301GPIOInitiate(void);
uint16_t DRV8301IDread(void);
void DRV8301Init(void);

void spi3init(void);
void chipselect(uint8_t status);
void spi3sck(uint8_t clk);
void spi3writeword(uint16_t data);
uint16_t spi3readword(void);
////////////////////////////////////////////////

#define DRV8301_EXPORT(x,xSetCSIsEnable,xReadData,xWriteData,xWriteReadData)   \
DRV8301_Struct x = {                                            \
    .rw = 0,                                                    \
    .addr = 0,                                                  \
    .data = 0,                                                  \
    .SetCSIsEnable = xSetCSIsEnable,                            \
    .ReadData = xReadData,                                      \
    .WriteData = xWriteData,                                    \
	.WriteReadData = xWriteReadData,      						\
};


void DRV8301SetGain(PDRV8301_Struct gDRV8301);
#endif //__DRV8301_H__



