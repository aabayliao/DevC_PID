#ifndef PID_H_INCLUDE
#define PID_H_INCLUDE
typedef struct
{
    float SetSpeed;            //定義設定值
    float ActualSpeed;        //
    float BeginSpeed;
    float err;                //定義偏差值
    float err_last;            //定義上一個偏差值
    float Kp,Ki,Kd;            //定義比例、積分、微分系數
    float voltage;          //定義電壓值（控制執行器的變數）
    float integral;            //定義積分值
    float CtlMax;
    float CtlMin;
    float index;
} tspid;

extern tspid pid;

void PID_init(void);
float PID_realize(float speed);
float PID_realize_adv(float speed);

#endif
