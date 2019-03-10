#include<stdio.h>
#define MIN 1e-6
int main()
{	
	float sum=0;
	float deno,item;
	int i=0,sign=1;
	deno = 2*i+1;
	item = 1.0/deno;
	while(item>MIN)
	{
		sum = sum + sign*item;
		i++;
		sign=-sign;
		deno=2*i+1;
		item = 1.0/deno;
	}
	sum = sum*4;
	
	printf("Result = %f \n",sum);
	
	return 0;
}
