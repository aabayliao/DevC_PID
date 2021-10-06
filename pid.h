#ifndef PID_H_INCLUDE
#define PID_H_INCLUDE
typedef struct
{
    float SetSpeed;            //�w�q�]�w��
    float ActualSpeed;        //
    float BeginSpeed;
    float err;                //�w�q���t��
    float err_last;            //�w�q�W�@�Ӱ��t��
    float Kp,Ki,Kd;            //�w�q��ҡB�n���B�L���t��
    float voltage;          //�w�q�q���ȡ]������澹���ܼơ^
    float integral;            //�w�q�n����
    float CtlMax;
    float CtlMin;
    float index;
} tspid;

extern tspid pid;

void PID_init(void);
float PID_realize(float speed);
float PID_realize_adv(float speed);

#endif
