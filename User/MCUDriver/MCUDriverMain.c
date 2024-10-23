 #include "MCUDriverMain.h"
#include "main.h"
//定时器1PWM生成函数
#include "TIM1PWM.h"
//定时器4编码器读取函数
#include "TIM4Encoder.h"
//定时任务函数
#include "timer.h"
//编码器Z轴中断
#include "GPIONVIC.h"
//LED引脚
#include "LEDGPIO.h"
//电机引脚
#include "MotorGPIO.h"
////系统电源
//#include "ADC2.h"
////通讯
//#include "CAN1.h"
/*************************************************************
** Function name:      MCUDriverMain_Init
** Descriptions:       芯片初始化
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void MCUDriverMain_Init(void)
{
	TIM1_Init();
	TimerEncoderInit();
	GPIONVIC_Init();
//	ADC2_Init();
//	CAN_Init();
}

/*************************************************************
** Function name:      MCUDriverMain_Loop
** Descriptions:       芯片循环
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void MCUDriverMain_Loop(void)
{
	// RUN_BY_LIMIT_BLOCK(20,
	// 	printf("1:%d\r\n",GetTimer4EncoderCnt());
	// 	printf("2:%f\r\n",GetTimer4EncoderAngle());
	// )
	//故障检测
	RUN_BY_LIMIT_BLOCK(20,
		SetFaultLedLeave(GetMotorFaultLeave());
	)
//	RUN_BY_LIMIT_BLOCK(500,
//		CAN_Test();
//	)
//	RUN_BY_LIMIT_BLOCK(100,
//		printf("1:%d\r\n",GetADC2Channel10Value());
//	)
}


