#include "PerDriverMain.h"
#include "main.h"

#include "LEDConfig.h"
#include "SvpwmConfig.h"
#include "Timer.h"
#include "FOCConfig.h"

#include "SpeedPIDConfig.h"
#include "PositionPIDConfig.h"
/*************************************************************
** Function name:      PerDriverMain_Init
** Descriptions:       外设初始化
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
void PerDriverMain_Init(void)
{
	HAL_Delay(2000);
	LEDConfig_Init();
	FOCConfig_Init();
	SpeedPIDConfig_Init();
	PositionPIDConfig_Init();
	
}

/*************************************************************
** Function name:      PerDriverMain_Loop
** Descriptions:       外设循环
** Input parameters:   none
** Output parameters:  none
** Returned value:     none
** Created by:         none
** Created date:       none
*************************************************************/
int debugFlag = 0;
float angle = 0;
void PerDriverMain_Loop(void)
{
	//打印调试信息
	RUN_BY_LIMIT_BLOCK(10,
		//FOCConfig_Printf();
		//SpeedPIDConfig_Printf();
		PositionPIDConfig_Printf();
	)	
	//3环调试
	RUN_BY_LIMIT_BLOCK(4000,
		if (debugFlag == 0) {
			debugFlag = 1;
			//SetTarIDIQ(0,0.8);
			//SetSpeedPIDConfigTarSpeed(5.0f);
			SetPositionPIDConfigTarPosition(90.0);
		} else if (debugFlag == 1){
			debugFlag = 0;
			//SetTarIDIQ(0,0.5);
			//SetSpeedPIDConfigTarSpeed(1.0f);
			SetPositionPIDConfigTarPosition(45.0);
		}
	)
//	//位置环应用
//	RUN_BY_LIMIT_BLOCK(10,
//		angle += 0.04;
//		if(angle >= 360) {
//			angle = 0;
//		}
//		SetPositionPIDConfigTarPosition(180 - angle);
//		SetPositionPIDConfigTarPosition(180 - angle);
//	)
	//速度闭环
	SpeedPIDConfig_Loop();
	//位置闭环
	PositionPIDConfig_Loop();
	LEDConfig_Loop();
}


