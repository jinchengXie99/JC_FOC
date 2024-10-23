#include "SpeedPIDConfig.h"

#include "SpeedPID.h"

#include "FOCConfig.h"
#include "TIM4Encoder.h"


#define S_KP  4.8f
#define S_KI  0.03f
#define S_KD  0.0f



float GetMotorPreSpeed(void)
{
    static float angle = 0.0;
    static float lastAngle = 0.0;
    float speed;
    angle = GetTimer4EncoderAngle();
    speed = angle - lastAngle;
    if (speed < -180) {
        speed = speed + 360;
    }
    if (speed > 180) {
        speed = speed - 360;
    }
	lastAngle = angle;
    return speed;
}

void  SetMotorCurrent(float current)
{
    SetTarIDIQ(0,current);
}


SPEED_PID_CONTROL_EXPORT(gSpeedPID,0.002,20,GetMotorPreSpeed,SetMotorCurrent)







/*************************************************************
** Function name:       SpeedPIDConfig_Init
** Descriptions:        速度PID初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SpeedPIDConfig_Init(void)
{
    SetSpeedPIDEnable(&gSpeedPID,1);
    SetSpeedPIDParams(&gSpeedPID,S_KP,S_KI,S_KD);
    SetSpeedPIDTar(&gSpeedPID,0.0f);
}

/*************************************************************
** Function name:       SpeedPIDConfig_Init
** Descriptions:        速度PID初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetSpeedPIDConfigTarSpeed(float tarSpeed)
{
    SetSpeedPIDTar(&gSpeedPID,tarSpeed);
}

/*************************************************************
** Function name:       SpeedPIDConfig_Init
** Descriptions:        速度PID初始化
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SpeedPIDConfig_Loop(void)
{
    SpeedPIDCycle(&gSpeedPID);
}
/*************************************************************
** Function name:       SpeedPIDConfig_Printf
** Descriptions:        速度PID信息打印
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SpeedPIDConfig_Printf(void)
{
	SpeedPIDPrintf(&gSpeedPID);
}







