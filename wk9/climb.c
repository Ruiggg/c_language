#include<stdio.h>

int nstairs(int n);
int main()
{	
	int n,m;
	printf("input the number of stairs:");
	scanf("%d",&n);
	m=nstairs(n);
	if(m>0)
		printf("the number of ways to climb %d stairs is %d\n",n,m);
	return 0;
}

int nstairs(int n)
{
	if(n<=0)
	{	
		printf("error:the number of stairs should be a positive integer!\n");
		return -1;
	}
	else if(n==1)
		return 1;
	else if(n==2)
		return 2;
	else
	{
		return (nstairs(n-1)+nstairs(n-2)); //第一步走两级或走一级
	}
	
}
