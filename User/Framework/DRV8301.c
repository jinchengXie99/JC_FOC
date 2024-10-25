#include "DRV8301.h"
#include "main.h"

#include "stdio.h"
#include "vofa.h"
//#include "SEGGER_RTT.h"
//#include "SEGGER_RTT_Conf.h"



#define STATUS_REG_1 0x00
#define STATUS_REG_2 0x01
#define CONTROL_REG_1 0x02
#define CONTROL_REG_2 0x03

void DRV8301SetGain(PDRV8301_Struct gDRV8301)
{
    gDRV8301->SetCSIsEnable(0);
	HAL_Delay(2);
//	USBV_printf("GAIN:%d\r\n",gDRV8301->WriteReadData(0x180C));
//	USBV_printf("GAIN:%d\r\n",gDRV8301->WriteReadData(0x1800));
	gDRV8301->SetCSIsEnable(1);
}

void chipselect(uint8_t status)
{
    if (status)
    {
        HAL_GPIO_WritePin(NSCS_DRV8301_GPIO_Port, NSCS_DRV8301_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(NSCS_DRV8301_GPIO_Port, NSCS_DRV8301_Pin, GPIO_PIN_RESET);
    }

    // if (status)
    // {
    //     GPIOD->BSRRL |= 0x01 << 2;
    // }
    // else
    // {
    //     GPIOD->BSRRH |= 0x01 << 2;
    // }
}

void spi3sck(uint8_t clk)
{
    if (clk)
    {
        HAL_GPIO_WritePin(SCLK_DRV8301_GPIO_Port, SCLK_DRV8301_Pin, GPIO_PIN_SET);
    }
    else
    {
        HAL_GPIO_WritePin(SCLK_DRV8301_GPIO_Port, SCLK_DRV8301_Pin, GPIO_PIN_RESET);
    }

    // if (clk)
    // {
    //     GPIOC->BSRRL |= 0x01 << 10;
    // }
    // else
    // {
    //     GPIOC->BSRRH |= 0x01 << 10;
    // }
}

void spi3writeword(uint16_t data)
{
    uint8_t i;
    chipselect(0);
    for (i = 0; i < 16; i++)
    {
        spi3sck(1);
        if (data & 0x8000 >> i)
        {
            HAL_GPIO_WritePin(SDI_DRV8301_GPIO_Port, SDI_DRV8301_Pin, GPIO_PIN_SET);
        }
        else
        {
            HAL_GPIO_WritePin(SDI_DRV8301_GPIO_Port, SDI_DRV8301_Pin, GPIO_PIN_RESET);
        }
        spi3sck(0);
    }
    HAL_GPIO_WritePin(SDI_DRV8301_GPIO_Port, SDI_DRV8301_Pin, GPIO_PIN_RESET);
    chipselect(1);

    // uint8_t i;
    // chipselect(0);
    // for (i = 0; i < 16; i++)
    // {
    //     spi3sck(1);
    //     if (data & 0x8000 >> i)
    //     {
    //         GPIOC->BSRRL |= 0x01 << 12;
    //     }
    //     else
    //     {
    //         GPIOC->BSRRH |= 0x01 << 12;
    //     }
    //     spi3sck(0);
    // }
    // GPIOC->BSRRH |= 0x01 << 12;
    // chipselect(1);
}
uint16_t spi3readword(void){
    uint8_t i;
    uint16_t data = 0;
    chipselect(0);
    for(i = 0; i < 16; i++){
        spi3sck(1);
        spi3sck(0);
        if(HAL_GPIO_ReadPin(SDO_DRV8301_GPIO_Port, SDO_DRV8301_Pin)){
            data |= 0x8000 >> i;
        }
    }
    chipselect(1);
    return data;

    // uint8_t i;
    // uint16_t data = 0;
    // chipselect(0);
    // for(i = 0; i < 16; i++){
    //     spi3sck(1);
    //     spi3sck(0);
    //     if(GPIOC->IDR & 0x01 << 11){
    //         data |= 0x8000 >> i;
    //     }
    // }
    // chipselect(1);
    // return data;
}




void DRV8301Init(void){
	
	DRV8301Cfg cfg = {
			.GATE_CURRENT = CURRENT0_7A,//","
			.GATE_RESET = GATE_RST_NORMAL,
			.PWM_MODE = PHASE6PWM,
			.OCP_MODE = OCLATCHSTDOWN,
			.OC_ADJ_SET = 18,
			.OCTW_MODE = OCOTBOTH,
			.GAINVALUE = GAIN10,
			.DC_CAL_CH1 = CONNECTLOADPH1,
			.DC_CAL_CH2 = CONNECTLOADPH2,
			.OC_TOFF = CYCLEBYCYCLE//Ã»ÓÐ","
		};
	
	HAL_GPIO_WritePin(EN_GATE_GPIO_Port, EN_GATE_Pin, GPIO_PIN_SET);//使能drv8301
	
	HAL_Delay(5000);
	
	
	uint16_t wconfig = 0;
    uint16_t rconfig = 0;
    uint16_t regvalue = 0;

    wconfig = DRV8301WRITE | REGCTRL1 << 11 | cfg.GATE_CURRENT | cfg.GATE_RESET | cfg.PWM_MODE | cfg.OCP_MODE | cfg.OC_ADJ_SET;
    spi3writeword(wconfig);
	
	wconfig = DRV8301WRITE | REGCTRL1 << 11 | cfg.GATE_CURRENT | cfg.GATE_RESET | cfg.PWM_MODE | cfg.OCP_MODE | cfg.OC_ADJ_SET;
    spi3writeword(wconfig);
    USBV_printf("wconfig1 = %o\r\n", wconfig);
    
    rconfig = DRV8301READ | REGCTRL1 << 11;
    spi3writeword(rconfig);
    regvalue = spi3readword();
    USBV_printf("regvalue1 = %o\r\n", regvalue);

    // if((regvalue & 0x07ff) != (wconfig &0x07ff)){
    //     return 1;
    // }

    wconfig = 0;
    wconfig = DRV8301WRITE | REGCTRL2 << 11 | cfg.OCTW_MODE | cfg.GAINVALUE | cfg.DC_CAL_CH1 | cfg.DC_CAL_CH2 | cfg.OC_TOFF << 6;
    spi3writeword(wconfig);
    USBV_printf("wconfig2 = %o\r\n", wconfig);

    rconfig = DRV8301READ | REGCTRL2 << 11;
    spi3writeword(rconfig);
    regvalue = spi3readword();
    USBV_printf("regvalue2 = %o\r\n", regvalue);

    // if((regvalue & 0x007f) != (wconfig & 0x007f)){
    //     return 2;
    // }
    // return 0;

}

uint16_t DRV8301IDread(void){
    uint16_t command = 0;
    uint16_t regvalue = 0;

    command = DRV8301READ | REGSTATUS2 << 11;
    USBV_printf("command = %d\r\n", command);
    spi3writeword(command);
    regvalue = spi3readword();

    return regvalue & 0x0f;
}
//////////////////////////////////////////



