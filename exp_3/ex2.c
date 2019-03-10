#include<stdio.h>
int is_wan(int n);
int Printwan(int n);
int main(){
	int i;
	for(i=1;i<=1000;i++)
		if(is_wan(i))
			Printwan(i);
	return 0;
}

int is_wan(int n)
{
	int j,sum;
	sum=0;
	for(j=1;j<n;j++)
	{
		if(n%j==0)
		sum+=j;
	}
	
	if(sum==n)
		return 1;
	else
		return 0;
}

int Printwan(int n)
{	
	printf("\n %6d:",n);
	int i;
	for(i=1;i<n;i++)
	{	
		if(n%i==0)
			printf(" %4d ",i);
	}
}
