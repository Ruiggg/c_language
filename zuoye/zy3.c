#include<stdio.h>
int gcd(int m,int n);
int main()
{	int m,n;
	printf("Enter two numbers(m,n):");
	scanf("%d%d",&m,&n);
	printf("gcd(%d,%d)=%d\n",m,n,gcd(m,n));
	printf("lcm(%d,%d)=%d\n",m,n,(m*n)/gcd(m,n));
	return 0;
}

int gcd(int m,int n)
{	
	int r,t;
	if(m<n)
	{
		t = m;
		m = n;
		n = t;
	}
	while((r=m%n)!=0)
	{
		m=n;
		n=r;
	}
	return n;
}
