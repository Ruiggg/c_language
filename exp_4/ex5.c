#include<stdio.h>

int main()
{
	int i,j,n;
	printf("input n:");
	scanf("%d",&n);
	if(n<0)
	{
		printf("n should be positive!\n");
		return 0;
	}
	double total=0.25;
	for(i=n;i>=1;i--)
		total=(total+0.25*i)/(1.0-1.0/(i+4.0));
	printf("total=%lf\n",total);
	printf("day		left		1/(n+4)		1/(n+4)*0.25	CUPs		cup*0.25\n");
	for(j=1;j<=n;j++)
	{
	printf("day%d	%lf		1/%d		      %lf         	%d		%lf		\n",j,total,j+4,1.0/(j+4.0)*total,j,0.25*j);
	total=total-total/(j+4.0)-j*0.25;
	}
	printf("day%d	%lf\n",n+1,total);
	return 0;
}
