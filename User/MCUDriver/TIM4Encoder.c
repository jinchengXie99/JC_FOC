#include "TIM4Encoder.h"
//#include "SEGGER_RTT_Conf.h"
//#include "SEGGER_RTT.h"
#include "main.h"

#define CNTZERO 10000
#define ENCODERPLUSE 8192


extern TIM_HandleTypeDef htim4;

struct STimEnc_Struct {
    int32_t Tim4Cnt;        //编码器脉冲数 0-360°
    float angle;			//编码器角度 0-360°
};
typedef struct STimEnc_Struct TimEnc_Struct; /* TimEnc 类型 */
typedef TimEnc_Struct *PTimEnc_Struct;      /* PTimEnc 指针类型 */

TimEnc_Struct gSTTimerEncoder = {
    .Tim4Cnt = 0,
    .angle = 0,
};

/*************************************************************
** Function name:       TimerEncoderInit
** Descriptions:        初始化定时器4
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
void TimerEncoderInit(void)
{
    HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_1|TIM_CHANNEL_2);
    __HAL_TIM_SET_COUNTER(&htim4,CNTZERO);
    gSTTimerEncoder.angle = 0.0;
    gSTTimerEncoder.Tim4Cnt = 0;
}
/*************************************************************
** Function name:       TimerEncoderInit
** Descriptions:        复位定时器4
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
*************************************************************/
void TimerEncoderReset(void)
{
    __HAL_TIM_SET_COUNTER(&htim4,CNTZERO);
    gSTTimerEncoder.angle = 0.0;
    gSTTimerEncoder.Tim4Cnt = 0;
}
/*************************************************************
** Function name:       GetTimer4EncoderCnt
** Descriptions:        获取定时器4编码器模式CNT的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      Timer4->CNT的值
*************************************************************/
int32_t GetTimer4EncoderCnt(void)
{
    gSTTimerEncoder.Tim4Cnt += __HAL_TIM_GET_COUNTER(&htim4) - CNTZERO;
	__HAL_TIM_SET_COUNTER(&htim4,CNTZERO);
	if (gSTTimerEncoder.Tim4Cnt < 0) {
		gSTTimerEncoder.Tim4Cnt += ENCODERPLUSE;
	}
    gSTTimerEncoder.Tim4Cnt = gSTTimerEncoder.Tim4Cnt % ENCODERPLUSE;
    return gSTTimerEncoder.Tim4Cnt;
}
/*************************************************************
** Function name:       SetTimer4EncoderCnt
** Descriptions:        设置Timer4Cnt的值
** Input parameters:    None
** Output parameters:   None
** Returned value:      None
** Remarks:             None
*************************************************************/
void SetTimer4EncoderCnt(int32_t cnt)
{
	gSTTimerEncoder.Tim4Cnt = cnt;
}
/*************************************************************
** Function name:       GetTimerEncoderAngle
** Descriptions:        获取编码器角度
** Input parameters:    None
** Output parameters:   None
** Returned value:      编码器角度
*************************************************************/
float GetTimer4EncoderAngle(void)
{
    gSTTimerEncoder.angle = (float)GetTimer4EncoderCnt() / (float)ENCODERPLUSE * 360.0f;
    if (gSTTimerEncoder.angle < 0) {
        gSTTimerEncoder.angle = gSTTimerEncoder.angle + 360.0f;
    }
    return gSTTimerEncoder.angle;
}
