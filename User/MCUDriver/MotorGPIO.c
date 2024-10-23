#include "MotorGPIO.h"
#include "main.h"

/*************************************************************
** Function name:       SetMotorEnable
** Descriptions:        设置电机使能标志
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetMotorEnable(uint8_t isEnable)
{
    HAL_GPIO_WritePin(Motor_Enable_GPIO_Port,Motor_Enable_Pin, (GPIO_PinState)isEnable);
}

/*************************************************************
** Function name:       GetMotorFaultLeave
** Descriptions:        获取电机故障引脚电平
** Input parameters:    None
** Output parameters:   None
** Returned value:      故障引脚电平
** Remarks:             None
*************************************************************/
uint8_t GetMotorFaultLeave(void)
{
	if(HAL_GPIO_ReadPin(Fault_LED_GPIO_Port, Fault_LED_Pin) == GPIO_PIN_SET) {
		return 1;
	} else {
		return 0;
	}
}

