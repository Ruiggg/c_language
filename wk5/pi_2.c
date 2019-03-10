#include<stdio.h>
#define MIN 1e-6
int main()
{	
	float sum=0;
	float deno,item;
	int sign=1;
	deno = 1.0;
	while((item=1.0/deno)>=MIN)
	{
		sum = sum + sign*item;
		sign=-sign;
		deno=deno+2;
	}
	sum = sum*4;
	
	printf("Result = %f \n",sum);
	
	return 0;
}
