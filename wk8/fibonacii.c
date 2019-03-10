#include<stdio.h>

int f(int n);
int main()
{
	int n;
	printf("input:");
	scanf("%d",&n);
	printf("\nf(%d)=%d\n",n,f(n));
}

int f(int n)
{
	if(n==0)
		return 0;
	else if(n==1)
		return 1;
	else
		return (f(n-1)+f(n-2));
}
