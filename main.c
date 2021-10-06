#include <stdio.h>
#include <stdlib.h>
#include "pid.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	int count=0;
	float speed,DesireSpeed;
	PID_init();
	DesireSpeed = 230;

	
    while(count<1000)
    {
        speed=PID_realize_adv(DesireSpeed);
        printf("spd= %.1f,err= %.1f,int= %.1f,idx= %.1f\n",speed,pid.err,pid.integral,pid.index);
        count++;
    }
    getch();
	return 0;
}
