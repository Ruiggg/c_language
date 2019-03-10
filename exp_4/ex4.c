#include<stdio.h>
double func(double a,double x);
double abs1(double m);
int main()
{
	double x1,x2,temp,a;
	scanf("%lf",&a);
	if(a<0)
	{printf("a should be positive\n");
	return 0;}
	x1=1.0;
	x2=func(a,x1);
	for(;abs1(x1-x2)>=1e-5;)
	{	temp=x2;
		x2=func(a,x2);
		x1=temp;
	}
	printf("a=%lf,sqrt(a)=%lf\n",a,x2);
	return 0;
}

double func(double a,double x)
{
	return 0.5*(x+a/x);
}

double abs1(double m)
{
	if(m>=0)
		return m;
	else
		return -m;
}
