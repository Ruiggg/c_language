#include<stdio.h>
int fact(int n);
float sum(int n);
int main()
{	int n;
	printf("Please enter an integer:");
	scanf("%d",&n);
	printf("%d\n",fact(n));
	if(n==0)
	printf("S=1\n");
	else
	printf("S=%f\n",sum(n));
	return 0;
}


int fact(int n)
{	
	int p = 1;
	int i;
	for(i=1;i<=n;i++)
	p=p*i;
	
	return p;
}

float sum(int n)
{	
	int i;
	float sum=1;
	for(i=1;i<=n;i++)
	{
		sum = sum + (1.0/fact(i));
	}
	return sum;
}
