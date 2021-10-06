#include "pid.h"
tspid pid;

void PID_init(void){
    pid.SetSpeed=0.0;
    pid.ActualSpeed=150.0;
    pid.err=0.0;
    pid.err_last=0.0;
    pid.voltage=0.0;
    pid.integral=0.0;
    pid.Kp=0.5;//0.2;
    pid.Ki=0.01;//0.015;
    pid.Kd=1;
    pid.CtlMax = 99.9;
    pid.CtlMin = -99.9;
}

float PID_realize(float speed){
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;
    pid.integral+=pid.err;
    pid.voltage=pid.Kp*pid.err+pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    pid.CtlMax = 99.9;
    pid.CtlMin = -99.9;
    return pid.ActualSpeed;
}

float PID_realize_adv(float speed)
{
#if 0
    float index;
    pid.SetSpeed=speed;
    pid.err=pid.SetSpeed-pid.ActualSpeed;

    if(abs(pid.err)>200)           //變積分過程
    {
    	index=0.0;
    }
	else if(abs(pid.err)<180)
	{
    	index=1.0;
    	pid.integral+=pid.err;
    }
	else
	{
    	index=(200-abs(pid.err))/20;
    	pid.integral+=pid.err;
    }
    pid.voltage=pid.Kp*pid.err+index*pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);

    pid.err_last=pid.err;
    pid.ActualSpeed=pid.voltage*1.0;
    return pid.ActualSpeed;
#endif
	float index;
	float TotalRange;
	pid.SetSpeed = speed;
	pid.err=pid.SetSpeed-pid.ActualSpeed;
	TotalRange = abs(pid.SetSpeed-pid.BeginSpeed);

	if(abs(pid.err) > (0.9 * TotalRange))//200)              //上升超過預定設定
	{
		index=1.1;
		pid.integral = pid.integral + pid.err;
		pid.index = index;
	}
	else if(abs(pid.err) < (0.9 * TotalRange) && abs(pid.err)> (0.5 * TotalRange)) //180)   //上升到預定設定的90%之前
	{
		index=1.0;
		pid.integral = pid.integral + pid.err;
		pid.index = index;
	}
	else    //180 < err < 200                  //已上升到預定設定的90%~100%之間
	{
		index = abs(pid.err)/(0.5 * TotalRange);//abs(pid.SetSpeed-pid.BeginSpeed)
		pid.integral = pid.integral + pid.err;
		pid.index = index;
	}
	pid.voltage = pid.Kp*pid.err+index*pid.Ki*pid.integral+pid.Kd*(pid.err-pid.err_last);
	//if(pid.voltage > pid.CtlMax)
	//{
	//	pid.voltage = pid.CtlMax;
//	}
	//else if(pid.voltage < pid.CtlMin)
	//{
	//	pid.voltage = pid.CtlMin;
	//}
	pid.err_last=pid.err;
	//PID_Cal_Adv = pid.voltage //pid.ActualSpeed;
	pid.ActualSpeed=pid.voltage*1.0;
	return pid.ActualSpeed;
}
