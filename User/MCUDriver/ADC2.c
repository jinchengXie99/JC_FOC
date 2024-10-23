#include "ADC2.h"
#include "main.h"


extern ADC_HandleTypeDef hadc2;

//一介低通滤波系数
#define FILTER_KP 0.8f


struct SADC2_Struct{
	int adValue;
	int lastAdValue;
};
struct SADC2_Struct gADC2 = {0};



/*************************************************************
** Function name:       ADC2_Init
** Descriptions:        ADC2初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void ADC2_Init(void)
{
	HAL_ADC_Start_DMA(&hadc2, (uint32_t*)gADC2.adValue, 1);
}
/*************************************************************
** Function name:       GetADC2Channel10Value
** Descriptions:        获取ADC通道10的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
int32_t GetADC2Channel10Value(void)
{
	int32_t value;
	value = (int32_t)(FILTER_KP * (float)gADC2.adValue + (1-FILTER_KP) * (float)gADC2.lastAdValue);
	gADC2.lastAdValue = value;
	return value;
}




