#include<stdio.h>
#define MAXVAL 100
int sp=0;
double var[MAXVAL];

void push(double f)
{
	if(sp<MAXVAL)
		var[sp++]=f;
	else
		printf("error: stack full, can't push %g\n",f);
}

double pop(void)
{
	if(sp>0)
		return var[--sp];
	else
	{
		printf("error: stack empty\n");
		return 0.0;
	}
}
